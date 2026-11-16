#include "include_asm.h"

#include "common.h"
extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_fast_float_d(char *);
extern char g_hero_state[];
extern void CalculateAimedLaunchVelocity(void *, void *, int, int, float, float, float, float);
extern int coll_trace_projectile_to_impact_pal(void *, void *, void *, void *, void *, char **, int *, float);
extern int weapon_get_group(int);
extern void moby_get_facing_direction(void *, void *);
extern float FastVecDot(void *, void *);
extern int weapon_spend_ammo(int, int);
extern int ForceClaimNotice(int, int, int);
extern void func_PAL_L00_002AF458(void);
extern void cancel_hero_item_animation_pal(void);
extern int PlayMobySound(int, int, void *);
extern char *spider_bot_spawn(void *, void *);
extern void ref_L00_003B7D48_00(void (*)(void *), void *);
extern void helper_update_hit_test_pal(void *);
typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;
extern OBJ2 *g_active_pickup_object __attribute__((sda));
extern int g_game_l00_mode MACRO_ADDR;
extern int g_input_lock_state MACRO_ADDR;
extern int g_hero_action_blocked_flag MACRO_ADDR;
extern int g_pad_held_flags NOT_SDA;

void func_PAL_L00_003BB8F0(char *m) {
    float pos[4], sweep_storage[4], normal[4];
    float *sweep;
    char *hit;
    int aux;
    char *d = *(char **)(m + 0x68);
    int result, state, ready;
    float height;

    {
        char *g = g_hero_state;

        if (*(int *)(g + 0x1244) == 3)
            g_active_pickup_object = 0;
        moby_transform_joint_to_world(m, 0, pos);
        *(int *)(d + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(g + 0x2294) == 29) ? 11.0f : 4.5f;
        CalculateAimedLaunchVelocity(sweep, pos, 0, 0, 1.6f, height, 0.16000001f, 0.0044f);
    }
    *(int *)(d + 0x24) = coll_trace_projectile_to_impact_pal(pos, sweep, d, d + 0x10, m, &hit, &aux, 0.0044f);
    result = weapon_get_group(aux);
    if (g_game_l00_mode || g_input_lock_state != -2)
        *(int *)(d + 0x2C) = 1;
    if (g_hero_action_blocked_flag && *(float *)(d + 8) < 462.42999267578125f)
        *(int *)(d + 0x2C) = 1;
    if (result || !*(int *)(d + 0x24) || !*(int *)(d + 0x28))
        goto blocked;
    {
        char *g = g_hero_state;

        state = *(int *)(g + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(g + 0x33C) && (*(short *)(*(char **)(g + 0x33C) + 0xAA) == 0x330 ||
                                      *(short *)(*(char **)(g + 0x33C) + 0xAA) == 0xB21))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 || *(short *)(hit + 0xAA) == 0xB5B))
            goto blocked;
    }
    moby_get_facing_direction(d, normal);
    if (!(FastVecDot(d + 0x10, normal) < 0.75f))
        goto timer;
blocked:
    *(int *)(d + 0x2C) = 1;
timer:
    {
        char *g = g_hero_state;

        ready = 1;
        if (*(int *)(g + 0x2294) == 29) {
            if (!math_fast_float_d(g + 0x2534))
                ready = 0;
        } else
            *(int *)(g + 0x2534) = 33;
    }
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        g_active_pickup_object = (OBJ2 *)m;
        *(unsigned char *)(m + 0x20) = 1;
        *(int *)(d + 0x28) = 1;
        *(int *)(d + 0x24) = 0;
        /* falls through */
    case 1: {
        char *g = g_hero_state;

        if ((g_pad_held_flags & *(int *)(g + 0x1230)) && !*(unsigned char *)(g + 0x22BC) &&
            !*(int *)(d + 0x2C) && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                *(short *)(g + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                *(short *)(g + 0x1D2) = 0;
                func_PAL_L00_002AF458();
                *(unsigned char *)(m + 0x20) = 2;
                *(int *)(d + 0x20) = 10;
                *(int *)(d + 0x28) = 0;
            } else
                PlayMobySound(0, 0, m);
        }
        break;
    }
    case 2:
        if (math_fast_float_d(d + 0x20)) {
            char *p = spider_bot_spawn(pos, sweep);

            if (p)
                *(char **)(p + 0xB8) = m;
            PlayMobySound(1, 0, m);
            cancel_hero_item_animation_pal();
            *(unsigned char *)(m + 0x20) = 3;
            *(int *)(d + 0x20) = 4;
        }
        break;
    case 3:
        if (math_fast_float_d(d + 0x20))
            *(unsigned char *)(m + 0x20) = 1;
        break;
    }
    ref_L00_003B7D48_00(helper_update_hit_test_pal, m);
}
