/* func_PAL_L20_0039FEA0, the PAL copy of func_L20_0039CF58: the same C, where 20 becomes 17 (three
 * func_L20_0039DB50 calls), 0.25f becomes 0.3f, `> 120` becomes `> 100`, and six callees take their
 * PAL names. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct {
    unsigned char reserved_00[0x18];
    unsigned char enabled, count, kind;
    unsigned char reserved_1b[0x65];
    unsigned char payload[1];
} DispatchContext;
extern unsigned long moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void trooper_setup_stats_target_pal(unsigned char *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern unsigned char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void SetDeathBits_pal(void *, int, int);
extern void trooper_destroy_parts(char *);
extern void trooper_play_anim_with_torso(char *, int, int, float);
extern int flag_set_first_pending(unsigned char *);
extern void trooper_choose_target(char *);
extern void trooper_choose_stand_point(void *);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(int, float);
extern float FastDiffRots(float, float);
extern int moby_l01_turn_toward_target_pal(char *, char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern int PlayMobySound(int, int, char *);
extern unsigned char *moby_spawn_aimed_effect_pal(void *, void *, void *, float);
extern void trooper_update_body_pal(char *);
extern int g_hero_vehicle_mode[] __attribute__((sda));
extern int g_level_l20_progress_stage;

/* Per-frame update of the Megacorp trooper: it picks a target, walks, turns and shoots, and breaks apart when it is hit. */
void trooper_update_pal(unsigned char *object) {
    Vector position, velocity;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *child, *target;
    unsigned long flags;
    int mode, code, hand;
    unsigned int tick;
    float angle;
    {
        unsigned char *initial = *(unsigned char **)(state + 0x254);
        if (initial) *(int *)(initial + 0x98) = 0;
    }
    trooper_setup_stats_target_pal(object);
    if (g_hero_vehicle_mode[0] == 2) {
        if (g_level_l20_progress_stage < 5) return;
        child = *(unsigned char **)(state + 0x258);
        if (child) moby_mark_spawned(child);
        child = *(unsigned char **)(state + 0x25C);
        if (child) moby_mark_spawned(child);
        child = *(unsigned char **)(state + 0x254);
        if (child) moby_mark_spawned(child);
        moby_mark_spawned(object);
        return;
    }
    mode = object[0x95];
    if (mode == 1) {
        flags = moby_dispatch_action_by_kind(object, (DispatchContext *)(state + 0x140));
        if ((flags & 1UL) == 1UL) {
            position.q = *(Quadword *)(object + 0x10);
            position.f[2] += 0.5f;
            SpawnExplosion_pal(&position, 0, 25, 20, 20, 20, 45, 0, mode, 0, 0, 0, 0.5f, 20.0f);
            SetDeathBits_pal(object, 0, 3);
            trooper_destroy_parts((char *)object);
        } else if ((flags & 2UL) == 2UL) {
            moby_set_state(object, 3, 0);
            trooper_play_anim_with_torso((char *)object, 0, 17, 0.0f);
        }
    }
    code = object[0x20];
    switch (code) {
    case 6:
        goto finished;
    case 2:
        if (object[0x60] & 2) moby_set_state(object, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            trooper_choose_target((char *)object);
            trooper_choose_stand_point(object);
            trooper_play_anim_with_torso((char *)object, 11, 17, 0.0f);
        }
        if (*(float *)(state + 0x11C) <= *(float *)(state + 0x84)) {
            unsigned char *aim_target = *(unsigned char **)(state + 0x200);
            angle = mat_fast_helper_a(*(float *)(aim_target + 0x10) - *(float *)(object + 0x10),
                                  *(float *)(aim_target + 0x14) - *(float *)(object + 0x14));
            moby_start_effect_from_entry((int)object, angle);
            if (FastDiffRots(*(float *)(object + 0xF8), angle) < 0.05235988274216652f)
                moby_set_state(object, 4, -1);
        } else {
            moby_l01_turn_toward_target_pal((char *)object, (char *)state + 0x260);
        }
        break;
    case 4:
        if (flag_set_first_pending(object)) trooper_play_anim_with_torso((char *)object, 10, 17, 0.0f);
        *(float *)(state + 0x284) = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(object + 0x10),
                                                *(float *)(state + 0x1F4) - *(float *)(object + 0x14));
        tick = *(unsigned short *)(object + 0x96) % 20;
        if (tick == 0 || tick == 10) {
            hand = tick == 0 ? 4 : 0;
            moby_transform_joint_to_world(*(char **)(hand + state + 0x258), 0, (char *)&position);
            FastVecSub(&velocity, state + 0x1F0, &position);
            vec_scale_to_length(&velocity, &velocity, 0.3f);
            PlayMobySound(1, 0, *(char **)(state + 0x254));
            moby_spawn_aimed_effect_pal(object, &velocity, &position, (float)state[0x34]);
        }
        if (*(unsigned short *)(object + 0x96) > 100 || ((target = *(unsigned char **)(state + 0x280)) && (*(unsigned short *)(target + 0x34) & 1)))
            moby_set_state(object, 3, -1);
        break;
    }
    trooper_update_body_pal((char *)object);
    child = *(unsigned char **)(state + 0x254);
    if (child) *(int *)(child + 0x98) = *(int *)(*(unsigned char **)(child + 0x24) + 0x10);
finished:
    return;
}
