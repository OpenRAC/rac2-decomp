#include "include_asm.h"
#include "names.h"

extern int *g_placement_object_current __attribute__((sda));
extern char g_hero_state[];
extern int g_pad_held_flags __attribute__((nosda));
extern int g_game_l00_mode;
extern int g_input_lock_state;
extern int g_hero_action_blocked_flag;
extern void moby_transform_joint_to_world(void *obj, int a, void *out);
extern void CalculateAimedLaunchVelocity(void *out, void *pos, int a, int b, float c, float d, float e, float f);
extern int coll_trace_projectile_to_impact_pal(void *a, void *b, void *c, void *d, void *e, void *f, void *g, float h);
extern int weapon_get_group(int surface);
extern void moby_get_facing_direction(void *a, void *b);
extern float FastVecDot(void *a, void *b);
extern int math_fast_float_d(void *timer);
extern int weapon_spend_ammo(int a, int b);
extern int ForceClaimNotice(int a, int b, int c);
extern void func_PAL_L00_002AF458(void);
extern int PlayMobySound(int a, int b, void *obj);
extern void cancel_hero_item_animation_pal(void);
extern char *spider_bot_create(void *pos, void *offset);
extern void ref_L00_004029E8_00(void (*f)(char *), char *arg);
extern void object_run_effect_if_active_pal(char *arg);

/* per-frame update of a four-state object: probes the ground below it (ctx+44 set means
   "not usable now": global flags, a blocking surface, some player states or attached/hit
   object types, or a ground normal too steep), then 0/1 wait for the player's input to
   start (player+0x1E0 = 120 and a sound), 2 spawns a func_L00_004005B0 object after the
   ctx+32 timer, 3 returns to 1 after the timer; D_00189E20 is the player block */
void placement_object_update_pal(char *obj)
{
    float pos[4], offset[4], normal[4];
    char *hit;
    int surface, blocked, ready;
    char *ctx = *(char **)(obj + 104);

    {
        char *player = g_hero_state;

        if (*(int *)(player + 0x1244) == 3)
            g_placement_object_current = 0;
        moby_transform_joint_to_world(obj, 0, pos);
        *(int *)(ctx + 44) = 0;
        CalculateAimedLaunchVelocity(offset, pos, 0, 0, 1.6f, *(int *)(player + 0x2294) == 29 ? 11.0f : 4.5f,
                      0.16000001f, 0.0044f);
    }
    *(int *)(ctx + 36) = coll_trace_projectile_to_impact_pal(pos, offset, ctx, ctx + 16, obj, &hit, &surface, 0.0044f);
    blocked = weapon_get_group(surface);
    if (g_game_l00_mode != 0 || g_input_lock_state != -2)
        *(int *)(ctx + 44) = 1;
    if (g_hero_action_blocked_flag != 0 && *(float *)(ctx + 8) < 462.43f)
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
                    && (*(short *)(attached + 170) == 0x330 || *(short *)(attached + 170) == 0xB21))
                   || (hit != 0 && (*(short *)(hit + 170) == 0xB21 || *(short *)(hit + 170) == 0xB5B))) {
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
            *(int *)(player + 0x2534) = 33;
        }
    }
    switch (*(unsigned char *)(obj + 32)) {
    case 0:
        g_placement_object_current = (int *)obj;
        obj[32] = 1;
        *(int *)(ctx + 40) = 1;
        *(int *)(ctx + 36) = 0;
    case 1: {
        char *player = g_hero_state;

        if ((g_pad_held_flags & *(int *)(player + 0x1230)) && ready && !*(unsigned char *)(player + 0x22BC)
            && !*(int *)(ctx + 44)) {
            if (weapon_spend_ammo(-1, 1)) {
                *(short *)(player + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                func_PAL_L00_002AF458();
                obj[32] = 2;
                *(int *)(ctx + 32) = 10;
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
            cancel_hero_item_animation_pal();
            obj[32] = 3;
            *(int *)(ctx + 32) = 4;
        }
        break;
    case 3:
        if (math_fast_float_d(ctx + 32))
            obj[32] = 1;
        break;
    }
    ref_L00_004029E8_00(object_run_effect_if_active_pal, obj);
}

#include "common.h"
extern int g_spider_bot_moby __attribute__((sda));
extern void linked_object_activate_data(void);
extern int g_level_data_pointer __attribute__((sda));

/* Writes the object's state byte (7 when arg0 is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value in the object's slot - 10 when it is -1. */
void func_PAL_L00_004071F0(int arg0, int arg1)
{
    char *p = (char *)g_level_data_pointer;
    int a = arg1;
    char *q;

    if (p == 0)
        return;
    q = *(char **)(p + 0x68);
    if (arg0 != 0)
        p[0x20] = 5;
    else
        p[0x20] = 7;
    linked_object_activate_data();
    if (a != -1)
        *(int *)(q + 0x60) = ((s32)(a) * 5 + 2) / 6;
    else
        *(int *)(q + 0x60) = 8;
}
