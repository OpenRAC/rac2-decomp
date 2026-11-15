#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern void FastVecSub(f32 *, f32 *, f32 *);
extern f32 FastVecLength(f32 *);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void FastVecAdd(f32 *, f32 *, f32 *);
extern f32 FastDiffRots(f32, f32);
extern int moby_move_over_ground(char *, char *, char *, f32, f32, f32, f32, int);
extern f32 ApproachValue(f32 *, f32, f32);
extern void math_step_value_toward_target(f32 *, char *, f32, f32, f32, f32);
extern void math_approach_target_with_direction_mode(char *, f32, f32, f32, f32, char *, int);
extern int ComputeRegionRouteHeading(char *, int, f32 *, char *, int, char *, char *, f32, f32);

/* Turns the object toward the point the caller names: it measures the angle between the
   object's own direction and that point, keeps the two angles it stores in its state, and
   reports whether the state changed. */
int tribesman_turn_toward_point(char *object, char *point, f32 value, f32 rate, f32 limit, f32 extra)
{
    char *vars = *(char **)(object + 0x68);
    f32 toTarget[4];
    f32 scaled[4];
    f32 nextPos[4];
    f32 speedOut = 0.0f;
    f32 targetAngle;
    f32 distance;
    f32 stepRate;
    int result = 0;

    FastVecSub(toTarget, (f32 *)point, (f32 *)(object + 0x10));
    toTarget[2] = 0.0f;
    distance = FastVecLength(toTarget);
    stepRate = rate * 0.0008333333535119891f;
    if (limit < distance) {
        int nodeIndex = *(int *)(vars + 0x520);

        targetAngle = 0.0f;
        ComputeRegionRouteHeading(object + 0x10, (int)point, &targetAngle, vars + 0x320, nodeIndex, vars + 0x530,
                          vars + 0x534, extra, 0.4f);
        math_approach_target_with_direction_mode(object + 0xF8, targetAngle, 0.006981317885220051f,
                      0.0034906589426100254f, 0.20943954586982727f, vars + 0x27C, 0);
        if (FastDiffRots(*(f32 *)(object + 0xF8), targetAngle) < 0.52359885f) {
            math_step_value_toward_target(&speedOut, vars + 0x538, distance, stepRate, stepRate, rate * 0.01666666753590107f);
        } else {
            *(f32 *)(vars + 0x538) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(object + 0xF8, value, 0.006981317885220051f, 0.2f,
                      0.20943954586982727f, vars + 0x27C, 0);
        ApproachValue((f32 *)(vars + 0x538), 0.0f, stepRate);
        if (*(f32 *)(vars + 0x538) == 0.0f) {
            if (FastDiffRots(*(f32 *)(object + 0xF8), value) < 0.0872664749622345f) {
                *(f32 *)(vars + 0x27C) = 0.0f;
                result = 1;
            }
        }
    }
    vec_scale_to_length(scaled, (f32 *)(object + 0xC0), *(f32 *)(vars + 0x538));
    FastVecAdd(nextPos, scaled, (f32 *)(object + 0x10));
    if (moby_move_over_ground(object, object + 0x10, (char *)nextPos, 0.75f, 0.75f, 0.4f,
                     0.52359885f, 0) == 0) {
        *(int *)(vars + 0x53C) = *(int *)(vars + 0x53C) + 1;
    }
    /* The counter at +0x53C wraps at 0x1E, and the object then reports the change. */
    if (*(int *)(vars + 0x53C) < 0x1E) {
        goto done;
    }
    *(int *)(vars + 0x53C) = 0;
    result = 1;
done:
    return result;
}

extern void func_003315A0(char *object, char *p);
extern void func_00300180(char *p);
extern void func_003357E0(char *object, char *p, int kind, float f12, float f13);
extern void func_00338398(char *object, char *p, int kind, int a3, float f12);

/* re-arms the object's two guard nodes and restarts its measurement window */
void tribesman_rearm_guard_nodes(char *object)
{
    char *vars = *(char **)(object + 0x68);

    func_003315A0(object, vars + 0x50);
    func_00300180(vars + 0x260);
    func_00300180(vars + 0x26);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_003357E0(object, vars + 0x2A0, 4, 0.03f, 0.3f);
    func_00338398(object, vars + 0x2A0, 4, 1, 3.5f);
}

extern s16 *g_group_id_lists[];
extern int g_moby_l11_table __attribute__((sda));

/* Walks the object's group list and, for every live member of class 0xCF5 (Joba Tribesman) or 0xCF6,
   marks it (0x266 = 1) and counts the visit at 0x560; class 0xCF5 members also count
   at 0x584 while the object's own state value at +0x20 is at most zero. */
void tribesman_alert_group(char *object)
{
    s16 *list;
    s16 *cursor;
    char *mobyTable;
    char *member;
    char *vars;

    if (((u8 *)object)[0x21] == 0xFF) {
        return;
    }
    list = g_group_id_lists[((u8 *)object)[0x21]];
    object = *(char **)(object + 0x68);
    if (list == 0) {
        return;
    }
    mobyTable = (char *)g_moby_l11_table;
    cursor = list;
    do {
        member = mobyTable + ((*(u16 *)cursor & 0x7FFF) << 8);
        if (((s8 *)member)[0x20] >= 0 && *(s16 *)(member + 0xAA) == MOBY_CLASS_JOBA_TRIBESMAN) {
            vars = *(char **)(member + 0x68);
            *(u16 *)(vars + 0x266) = 1;
            *(int *)(vars + 0x560) += 1;
            if (*(f32 *)(object + 0x20) <= 0.0f) {
                *(int *)(vars + 0x584) += 1;
            }
        }
        if (((s8 *)member)[0x20] >= 0 && *(s16 *)(member + 0xAA) == 0xCF6 /* moby class 3318 */) {
            vars = *(char **)(member + 0x68);
            *(u16 *)(vars + 0x266) = 1;
            *(int *)(vars + 0x560) += 1;
        }
    } while (*cursor++ >= 0);
}

extern char *func_0032F000(char *cursor, int a1, int a2);

/* ticks the object's clock down by the rate the linked node states */
int tribesman_tick_linked_clock(char *object)
{
    char *vars = *(char **)(object + 0x68);
    char *node = func_0032F000(*(char **)(vars + 0x280), 0x10000, 0);

    if (node != 0) {
        *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(node + 0x2C);
        return 1;
    }
    return 0;
}
