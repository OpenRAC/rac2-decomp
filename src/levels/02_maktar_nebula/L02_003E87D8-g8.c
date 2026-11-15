#include "common.h"

extern char *g_moby_l02_pool;
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x530];
    char *captured;
    char pad5c4[0xE90];
    unsigned short captureMode;
} Hero003E87D8;
/* Prefix of the resident hero: position, captured actor and capture mode. */
extern char g_hero_state[];
extern char g_sound_state[];
extern unsigned short D_0018CA6C NOT_SDA;
extern float D_L02_001B0B80 __attribute__((sda));
extern float D_L02_001B0B84 __attribute__((sda));
extern float D_L02_001B0B88 __attribute__((sda));
extern float D_L02_001B0B8C __attribute__((sda));
extern float D_L02_001B0B90 __attribute__((sda));
extern float D_L02_001B0B94 __attribute__((sda));
extern float D_L02_001B0BA0 __attribute__((sda));
extern float D_L02_001B0BF0[4] __attribute__((sda, aligned(16)));
/* The vector address uses GP; its fourth component uses the absolute view. */
extern float effectOffset003E87D8[4] SDATA(D_L02_001B0BF0);
typedef struct { char pad[0x34]; unsigned short flags; } Actor003E87D8;
extern void moby_set_state(void *, int, int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void moby_set_flag_bit(void *, int);
extern void vec_clear_128(void *);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern float math_approach_target_with_direction_mode(void *, void *, int, float, float, float, float);
extern void tether_pull_entity(void *);
extern int PlayMobySound(int, int, void *);
extern void cam_set_strength_and_steer_target(char *, float, float);
extern void cam_set_lock_flag(void);
extern void cam_set_speeds_if_nonzero(float, float);
extern int flag_set_first_pending(void *);
extern int tether_swing_entity(void *);
extern void path_enemy_start_fall(void *, void *);
extern void platform_start_fall(void *, void *);
extern float math_fabs(float);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int flag_is_third_pending_set(void *);
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void DrawMirroredRibbons(char *);
/* Updates a tether actor's capture, release, turning and attached effect. */
void tether_update(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *target = g_moby_l02_pool + *(int *)state * 0x100;
    float effect_point[4] __attribute__((aligned(16)));
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(float *)(state + 0x48) = *(float *)(actor + 0xF8);
        if (*(int *)state != -1) {
            moby_set_state(actor, 1, -1);
            if (*(short *)(g_moby_l02_pool + *(int *)state * 0x100 + 0xAA) == 0x9BC /* moby class 2492 */) {
                char *effect = CreateMoby(0xA61 /* moby class 2657 */);
                *(char **)(state + 0x54) = effect;
                if (effect) {
                    moby_init_child_from_parent(effect, actor);
                    *(unsigned short *)(*(char **)(state + 0x54) + 0x34) |= 2;
                }
            }
        } else {
            moby_set_state(actor, 4, -1);
        }
        break;
    case 1:
        if ((*(unsigned short *)(target + 0x34) & 0x1000) && ((Hero003E87D8 *)g_hero_state)->captured == target &&
            vec_distance_xy(target + 0x10, actor + 0x10) < D_L02_001B0B80) {
            moby_set_flag_bit(target, 1);
            vec_clear_128(state + 0x10);
            moby_set_state(actor, 2, -1);
            break;
        }
        break;
    case 2:
        {
            float separation;
            float turnStep, turnLimit;
            float angle = FastAddRotations(mat_fast_helper_a(
                *(float *)(target + 0x10) - *(float *)(actor + 0x10),
                *(float *)(target + 0x14) - *(float *)(actor + 0x14)), 3.1415927f);
            if (FastDiffRots(angle, *(float *)(actor + 0xF8)) > 1.5707964f)
                angle = FastAddRotations(angle, 3.1415927f);
            turnStep = D_L02_001B0B88 * 0.0000048481375f;
            turnLimit = D_L02_001B0B8C * 0.00029088825f;
            math_approach_target_with_direction_mode(actor + 0xF8, state + 0x40, 0, angle, turnStep, turnStep * 3.0f, turnLimit);
            tether_pull_entity(actor);
            separation = vec_distance_xy(actor + 0x10, ((Hero003E87D8 *)g_hero_state)->position);
            if (((Hero003E87D8 *)g_hero_state)->captured != target || separation > D_L02_001B0BA0) {
                float distance, scaledDistance;
                ((Hero003E87D8 *)g_hero_state)->captured = 0;
                distance = fast_vec_dist(actor + 0x10, ((Hero003E87D8 *)g_hero_state)->position) - D_L02_001B0B84;
                if (distance < 0.0f)
                    distance = 0.0f;
                scaledDistance = distance * 0.016666668f;
                ((Actor003E87D8 *)target)->flags &= 0xEFFF;
                *(float *)(state + 0x44) = D_L02_001B0B90 * 0.016666668f + D_L02_001B0B94 * scaledDistance;
                PlayMobySound(0, 0, actor);
                moby_set_state(actor, 3, -1);
            } else {
                ((Hero003E87D8 *)g_hero_state)->captureMode = 2;
                cam_set_strength_and_steer_target(actor + 0x10, 0.78539824f, 0.0f);
                cam_set_lock_flag();
                cam_set_speeds_if_nonzero(0.03f, 0.2f);
                if (*(unsigned short *)(target + 0x34) & 0x1000)
                    break;
                moby_set_state(actor, 1, -1);
            }
        }
        break;
    case 3:
        if (flag_set_first_pending(actor)) {
            qzero_nc(state + 0x10);
            PlayMobySound(0, 0, actor);
        }
        if (tether_swing_entity(actor)) {
            moby_set_flag_bit(target, 0);
            if (*(short *)(target + 0xAA) == 0x9BC /* moby class 2492 */) {
                path_enemy_start_fall(target, state + 0x10);
                D_0018CA6C = 0xFFFF;
            } else {
                platform_start_fall(target, state + 0x10);
            }
            moby_set_state(actor, 1, -1);
        }
        break;
    }
    if (math_fabs(*(float *)(state + 0x40)) > 0.004363324f) {
        char *slot = g_sound_state + *(int *)(state + 0x58) * 0x70;
        if (*(char **)(slot + 0x88) != actor || *(unsigned char *)(slot + 0x74) == 0)
            *(int *)(state + 0x58) = PlayMobySound(1, 4, actor);
        if (*(unsigned char *)(actor + 0x20) != 2)
            *(float *)(state + 0x40) = 0;
    } else {
        int index = *(int *)(state + 0x58);
        if (index != -1) {
            char *slot = g_sound_state + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74))
                snd_stop_voice(index);
        }
        *(int *)(state + 0x58) = -1;
    }
    if (*(char **)(state + 0x54)) {
        matrix_mul_vec3(effect_point, effectOffset003E87D8, actor + 0xC0);
        FastVecAdd(*(char **)(state + 0x54) + 0x10, effect_point, actor + 0x10);
        *(float *)(*(char **)(state + 0x54) + 0xF8) = *(float *)(actor + 0xF8);
        *(float *)(*(char **)(state + 0x54) + 0x2C) = *(float *)(*(char **)(*(char **)(state + 0x54) + 0x24) + 0x24) * D_L02_001B0BF0[3];
    }
    if (flag_is_third_pending_set(target))
        gfx_add_draw_callback_first(DrawMirroredRibbons, actor);
}
