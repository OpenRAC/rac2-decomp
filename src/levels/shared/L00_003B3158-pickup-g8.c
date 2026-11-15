#include "common.h"

extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_fast_float_d(char *);
extern char g_hero_state[];
extern void CalculateAimedLaunchVelocity(void *, void *, int, int, float, float, float, float);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, void *, char **, int *, float);
extern int weapon_get_group(int);
extern void moby_get_facing_direction(void *, void *);
extern float FastVecDot(void *, void *);
extern int weapon_spend_ammo(int, int);
extern int ForceClaimNotice(int, int, int);
extern void start_equipped_item_animation(void);
extern void cancel_hero_item_animation(void);
extern void PlayMobySound(int, int, void *);
extern char *spider_bot_spawn(void *, void *);
extern void ref_L00_003B7D48_00(void (*)(void *), void *);
extern void helper_update_hit_test(void *);
typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;

extern OBJ2 *D_L00_001AFBC0 __attribute__((sda));
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001A8F08 MACRO_ADDR;
extern int D_L00_001A8FF4 MACRO_ADDR;
extern int D_00138324 NOT_SDA;

/* Updates the Spiderbot Glove pickup. When the player presses the button near it and nothing blocks the way, the glove is picked up and the player's pickup action starts. */
void spiderbot_glove_pickup_update(char *m) {
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
            D_L00_001AFBC0 = 0;
        moby_transform_joint_to_world(m, 0, pos);
        *(int *)(d + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(g + 0x2294) == 29) ? 11.0f : 4.5f;
        CalculateAimedLaunchVelocity(sweep, pos, 0, 0, 1.6f, height, 0.13333334028720856f, 0.003055555745959282f);
    }
    *(int *)(d + 0x24) = coll_trace_projectile_to_impact(pos, sweep, d, d + 0x10, m, &hit, &aux, 0.003055555745959282f);
    result = weapon_get_group(aux);
    if (D_L00_001A8F00 || D_L00_001A8F08 != -2)
        *(int *)(d + 0x2C) = 1;
    if (D_L00_001A8FF4 && *(float *)(d + 8) < 462.42999267578125f)
        *(int *)(d + 0x2C) = 1;
    if (result || !*(int *)(d + 0x24) || !*(int *)(d + 0x28))
        goto blocked;
    {
        char *g = g_hero_state;

        state = *(int *)(g + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(g + 0x33C) && (*(short *)(*(char **)(g + 0x33C) + 0xAA) == MOBY_CLASS_TAXI ||
                                      *(short *)(*(char **)(g + 0x33C) + 0xAA) == 0xB21 /* moby class 2849 */))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 /* moby class 2849 */ || *(short *)(hit + 0xAA) == 0xB5B /* moby class 2907 */))
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
            *(int *)(g + 0x2534) = 40;
    }
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        D_L00_001AFBC0 = (OBJ2 *)m;
        *(unsigned char *)(m + 0x20) = 1;
        *(int *)(d + 0x28) = 1;
        *(int *)(d + 0x24) = 0;
        /* falls through */
    case 1: {
        char *g = g_hero_state;

        if ((D_00138324 & *(int *)(g + 0x1230)) && !*(unsigned char *)(g + 0x22BC) &&
            !*(int *)(d + 0x2C) && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                *(short *)(g + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                *(short *)(g + 0x1D2) = 0;
                start_equipped_item_animation();
                *(unsigned char *)(m + 0x20) = 2;
                *(int *)(d + 0x20) = 12;
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
            cancel_hero_item_animation();
            *(unsigned char *)(m + 0x20) = 3;
            *(int *)(d + 0x20) = 5;
        }
        break;
    case 3:
        if (math_fast_float_d(d + 0x20))
            *(unsigned char *)(m + 0x20) = 1;
        break;
    }
    ref_L00_003B7D48_00(helper_update_hit_test, m);
}
