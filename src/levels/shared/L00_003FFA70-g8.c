#include "include_asm.h"
#include "names.h"

extern unsigned char *D_L00_001B0CA0 __attribute__((sda));

extern int D_L00_001B2C14 __attribute__((sda));

extern int *D_L00_001B0DB0 __attribute__((sda));

/* Tells whether the global object exists and is in one of its three busy states. */
int global_object_is_busy(char *arg)
{
    unsigned char *p = D_L00_001B0CA0;
    if (!p) {
        return 0;
    }
    return (unsigned int)(p[32] - 5) < 3;
}

/* Returns the stored flag value if the global object exists, otherwise zero. */
int global_object_get_flag(void)
{
    if (!D_L00_001B0CA0) {
        return 0;
    }
    return D_L00_001B2C14;
}

/* Marks the linked object's private data as active. */
void linked_object_activate_data(char *arg)
{
    int *p = D_L00_001B0DB0;
    if (p) {
        int *q = (int *)p[26];
        q[10] = 1;
    }
}

extern void linked_object_activate_data(char *arg);

/* Puts the global object into its start state and stores a countdown value (10 by default). */
void global_object_start(char *arg, int value)
{
    unsigned char *p = D_L00_001B0CA0;
    int *o;

    if (!p) {
        return;
    }
    o = *(int **)(p + 104);
    p[32] = (arg != 0) ? 5 : 7;
    linked_object_activate_data(arg);
    if (value != -1) {
        o[24] = value;
    } else {
        o[24] = 10;
    }
}

extern int D_L00_001B19C8_1[] __attribute__((sda));
extern char *D_L00_001B1EA8_1[] __attribute__((sda));
extern float D_L00_001B0C90 __attribute__((sda));

extern float func_002EE2B0(char *a, char *b);
extern void func_00381F80(char *a, char *b);

/* walks the object list once the shared flag is set, stopping at either special state and
   otherwise acting on the entries whose handle reports type 0x13 */
void nearby_typed_objects_notify(char *arg)
{
    char *o;

    if ((D_L00_001B19C8_1[0] & 1) == 0)
        return;

    for (o = D_L00_001B1EA8_1[0]; o != 0; o = *(char **)(o + 40)) {
        unsigned char state = *(unsigned char *)(o + 32);

        if (state == 0xFE)
            return;
        if (state == 0xFD)
            return;
        if (o == 0 || *(int *)(o + 36) == 0 || *(short *)(*(int *)(o + 36) + 70) != 0x13)
            continue;
        if (func_002EE2B0(o + 16, arg + 16) < D_L00_001B0C90)
            func_00381F80(o, arg);
    }
}

extern char g_hero_state[];
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001A8F00;
extern int D_L00_001A8F08;
extern int D_L00_001A8FF4;
extern void moby_transform_joint_to_world(void *obj, int a, void *out);
extern void CalculateAimedLaunchVelocity(void *out, void *pos, int a, int b, float c, float d, float e, float f);
extern int coll_trace_projectile_to_impact(void *a, void *b, void *c, void *d, void *e, void *f, void *g, float h);
extern int weapon_get_group(int surface);
extern void moby_get_facing_direction(void *a, void *b);
extern float FastVecDot(void *a, void *b);
extern int math_fast_float_d(void *timer);
extern int weapon_spend_ammo(int a, int b);
extern int ForceClaimNotice(int a, int b, int c);
extern void start_equipped_item_animation(void);
extern int PlayMobySound(int a, int b, void *obj);
extern void cancel_hero_item_animation(void);
extern char *spider_bot_create(void *pos, void *offset);
/* func_L00_002E6EF8 in most levels; another function in levels 08, 09, 19 and 30 */
extern void ref_L00_004029E8_00(void (*f)(char *), char *arg);
extern void object_run_effect_if_active(char *arg);

/* per-frame update of a four-state object: probes the ground below it (ctx+44 set means
   "not usable now": global flags, a blocking surface, some player states or attached/hit
   object types, or a ground normal too steep), then 0/1 wait for the player's input to
   start (player+0x1E0 = 120 and a sound), 2 spawns a func_L00_004005B0 object after the
   ctx+32 timer, 3 returns to 1 after the timer; D_00189E20 is the player block */
void placement_object_update(char *obj)
{
    float pos[4], offset[4], normal[4];
    char *hit;
    int surface, blocked, ready;
    char *ctx = *(char **)(obj + 104);

    {
        char *player = g_hero_state;

        if (*(int *)(player + 0x1244) == 3)
            D_L00_001B0DB0 = 0;
        moby_transform_joint_to_world(obj, 0, pos);
        *(int *)(ctx + 44) = 0;
        CalculateAimedLaunchVelocity(offset, pos, 0, 0, 1.6f, *(int *)(player + 0x2294) == 29 ? 11.0f : 4.5f,
                      0.13333334f, 0.0030555557f);
    }
    *(int *)(ctx + 36) = coll_trace_projectile_to_impact(pos, offset, ctx, ctx + 16, obj, &hit, &surface, 0.0030555557f);
    blocked = weapon_get_group(surface);
    if (D_L00_001A8F00 != 0 || D_L00_001A8F08 != -2)
        *(int *)(ctx + 44) = 1;
    if (D_L00_001A8FF4 != 0 && *(float *)(ctx + 8) < 462.43f)
        *(int *)(ctx + 44) = 1;
    if (blocked || *(int *)(ctx + 36) == 0 || *(int *)(ctx + 40) == 0) {
        *(int *)(ctx + 44) = 1;
    } else {
        char *player = g_hero_state;
        int state = *(int *)(player + 0x2294);
        char *attached;

        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6
            || state == 116 || state == 129) {
            *(int *)(ctx + 44) = 1;
        } else if (((attached = *(char **)(player + 0x33C)) != 0
                    && (*(short *)(attached + 170) == 0x330 /* Taxi */ || *(short *)(attached + 170) == 0xB21 /* moby class 2849 */))
                   || (hit != 0 && (*(short *)(hit + 170) == 0xB21 /* moby class 2849 */ || *(short *)(hit + 170) == 0xB5B /* moby class 2907 */))) {
            *(int *)(ctx + 44) = 1;
        } else {
            moby_get_facing_direction(ctx, normal);
            if (FastVecDot(ctx + 16, normal) < 0.75f)
                *(int *)(ctx + 44) = 1;
        }
    }
    {
        char *player = g_hero_state;

        ready = 1;
        if (*(int *)(player + 0x2294) == 29) {
            if (!math_fast_float_d(player + 0x2534))
                ready = 0;
        } else {
            *(int *)(player + 0x2534) = 40;
        }
    }
    switch (*(unsigned char *)(obj + 32)) {
    case 0:
        D_L00_001B0DB0 = (int *)obj;
        obj[32] = 1;
        *(int *)(ctx + 40) = 1;
        *(int *)(ctx + 36) = 0;
    case 1: {
        char *player = g_hero_state;

        if ((D_00138324 & *(int *)(player + 0x1230)) && ready && !*(unsigned char *)(player + 0x22BC)
            && !*(int *)(ctx + 44)) {
            if (weapon_spend_ammo(-1, 1)) {
                *(short *)(player + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                start_equipped_item_animation();
                obj[32] = 2;
                *(int *)(ctx + 32) = 12;
                *(int *)(ctx + 40) = 0;
            } else {
                PlayMobySound(0, 0, obj);
            }
        }
        break;
    }
    case 2:
        if (math_fast_float_d(ctx + 32)) {
            char *spawn = spider_bot_create(pos, offset);

            *(char **)(spawn + 184) = obj;
            cancel_hero_item_animation();
            obj[32] = 3;
            *(int *)(ctx + 32) = 5;
        }
        break;
    case 3:
        if (math_fast_float_d(ctx + 32))
            obj[32] = 1;
        break;
    }
    ref_L00_004029E8_00(object_run_effect_if_active, obj);
}
