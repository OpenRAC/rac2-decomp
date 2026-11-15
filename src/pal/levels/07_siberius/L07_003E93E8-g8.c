#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
extern int PlayMobySound(int, int, char *);
extern int func_PAL_002B1A50(char *, void *, int);
extern void entity_set_group_alert_a(char *);
extern void func_PAL_L07_003E9FD0(char *);
extern void entity_follow_platform(char *);
extern int weapon_select_aim_target(char *, int, void *, int, float, float);
extern float D_L07_001B0AA0 __attribute__((sda));
extern float D_L07_001B0AA4 __attribute__((sda));
extern char D_L07_001B9200[];
extern char g_sound_state[];

/* In state 0, set up the object's state block (offsets in ascending order, with +0x98 first and
   +0x30 last, as retail's store schedule requires). Then: within 24 units of D_L07_001B9200 while
   +0x31 is set, call func_002A93B0; restart the sound when its slot no longer belongs to the
   object; run func_L07_003E5AC8 and func_PAL_L07_003E9FD0 on a func_PAL_002B1A50 count of two or more or
   when +0x2E is 2; and follow the platform at +0x260 unless the state byte is 8. */
void func_PAL_L07_003E9908(char *arg)
{
    char *o = *(char **)(arg + 0x68);
    char *slot;
    float f, g;

    if (*(unsigned char *)(arg + 0x20) == 0) {
        *(unsigned char *)(o + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(o + 0x4A) = FloatToInt(2.4f);
        *(unsigned char *)(o + 0x60) = 7;
        *(unsigned char *)(o + 0x2E) = 1;
        *(unsigned char *)(o + 0xC7) = 1;
        f = D_L07_001B0AA0;
        g = D_L07_001B0AA4;
        f *= 0.00040000002f;
        g *= 0.020000001f;
        *(int *)(o + 0x98) = 3;
        *(float *)(o + 0x80) = 0.5f;
        *(int *)(o + 0x84) = 0;
        *(float *)(o + 0x8C) = 0.15f;
        *(float *)(o + 0xA8) = 1.0f;
        *(float *)(o + 0xAC) = 1.0f;
        *(float *)(o + 0x120) = 0.45f;
        *(int *)(o + 0x124) = 0;
        *(float *)(o + 0x140) = f;
        *(float *)(o + 0x144) = f;
        *(float *)(o + 0x148) = g;
        *(int *)(o + 0x158) |= 0x15;
        *(int *)(o + 0x30) = 0;
        qcopy(o + 0x220, arg + 0x10);
        if (*(short *)(o + 0x218))
            moby_set_state(arg, 1, 0);
        else {
            *(int *)(arg + 0x98) = 0;
            *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(arg, 8, 4);
        }
    }
    if (*(unsigned char *)(arg + 0x31) && fast_vec_dist(arg + 0x10, D_L07_001B9200) < 24.0f) {
        moby_update_ground_check(arg);
        *(unsigned char *)(arg + 0x6F) = 22;
    }
    if (*(unsigned char *)(arg + 0x95) != 4) {
        slot = g_sound_state + *(int *)(o + 0x264) * 0x70;
        if (*(char **)(slot + 0x88) != arg || !*(unsigned char *)(slot + 0x74))
            *(int *)(o + 0x264) = PlayMobySound(1, 4, arg);
    }
    if (func_PAL_002B1A50(arg, o + 0x50, 0) >= 2 || *(unsigned char *)(o + 0x2E) == 2) {
        entity_set_group_alert_a(arg);
        func_PAL_L07_003E9FD0(arg);
    }
    weapon_select_aim_target(arg, *(int *)(o + 0x214), 0, 0, 0.0f, 0.0f);
    if (*(int *)(o + 0x260) && *(unsigned char *)(arg + 0x20) != 8)
        entity_follow_platform(arg);
}

typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;
typedef struct {
    u8 pad000[0x1C8];
    f32 cam[9];
    f32 f1EC;
    u8 pad1F0[0x220 - 0x1F0];
    f32 home[4];
    u8 pad230[0x260 - 0x230];
    u8 *target;
} Vars_L07_003E5910;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars_L07_003E5910 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 rot[4];
} Moby_L07_003E5910;
extern char g_hero_state[];
extern f32 D_L07_001B0AA0 __attribute__((sda));
extern f32 D_L07_001B0AA4 __attribute__((sda));
extern f32 D_L07_001B0AA8 __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern int func_PAL_002B5BA8(void *, float *, float);

/* Follow the camera height between the moby's home and the hero, never under the floor. */
float func_PAL_L07_003E9B60(Moby_L07_003E5910 *m, float *arg1, float arg2)
{
    f32 pos[4] __attribute__((aligned(16)));
    Vars_L07_003E5910 *v = m->vars;
    f32 lo, hi, h, floor;

    if (v->target != 0) {
        matrix_mul_vec3(pos, v->home, m->rot);
        FastVecAdd(pos, pos, v->target + 0x10);
    } else {
        qcopy(pos, v->home);
    }
    lo = pos[2] - 2.0f;
    hi = lo + 5.0f;
    h = ((Hero *)g_hero_state)->f[0x2D8 / 4] + D_L07_001B0AA8;
    if (hi < h) h = hi;
    else if (h < lo) h = lo;
    floor = coll_probe_ground_height_below(m->pos, 0, 0.5f) + D_L07_001B0AA8;
    if (h < floor) h = floor;
    math_approach_target_with_braking(v->cam, h - m->pos[2], D_L07_001B0AA0 * 0.00040000002f, D_L07_001B0AA0 * 0.00040000002f,
                  D_L07_001B0AA4 * 0.020000001f);
    func_PAL_002B5BA8(m, arg1, arg2);
    return v->f1EC;
}
