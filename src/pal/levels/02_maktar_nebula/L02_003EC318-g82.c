#include "include_asm.h"

#include "common.h"
extern char *g_moby_l02_pool;
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x530];
    char *captured;
    char pad5c4[0xE90];
    unsigned short capture_mode;
} Hero003E87D8;
extern char g_hero_state[];
extern char g_sound_state[];
extern unsigned short g_tether_link_id NOT_SDA;
extern float g_tether_capture_distance __attribute__((sda));
extern float g_tether_distance_offset __attribute__((sda));
extern float g_tether_turn_step __attribute__((sda));
extern float g_tether_turn_limit __attribute__((sda));
extern float g_tether_speed_base __attribute__((sda));
extern float g_tether_speed_scale __attribute__((sda));
extern float g_tether_break_separation __attribute__((sda));
extern float g_tether_strand_params[4] __attribute__((sda, aligned(16)));
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
extern void tether_pull_entity_pal(void *);
extern int PlayMobySound(int, int, void *);
extern void cam_set_strength_and_steer_target(char *, float, float);
extern void cam_set_lock_flag(void);
extern void cam_set_speeds_if_nonzero(float, float);
extern int flag_set_first_pending(void *);
extern int tether_swing_entity_pal(void *);
extern void path_enemy_start_fall(void *, void *);
extern void platform_start_fall(void *, void *);
extern float math_fabs(float);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int flag_is_third_pending_set(void *);
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void DrawMirroredRibbons_pal(char *);

/* Updates a tether actor's capture, release, turning and attached effect. */
void tether_update_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *target = g_moby_l02_pool + *(int *)state * 0x100;
    float local[4] __attribute__((aligned(16)));
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(state + 0x48) = *(float *)(moby + 0xF8);
        if (*(int *)state != -1) {
            moby_set_state(moby, 1, -1);
            if (*(short *)(g_moby_l02_pool + *(int *)state * 0x100 + 0xAA) == 0x9BC) {
                char *effect = CreateMoby(0xA61);
                *(char **)(state + 0x54) = effect;
                if (effect) {
                    moby_init_child_from_parent(effect, moby);
                    *(unsigned short *)(*(char **)(state + 0x54) + 0x34) |= 2;
                }
            }
        } else {
            moby_set_state(moby, 4, -1);
        }
        break;
    case 1:
        if ((*(unsigned short *)(target + 0x34) & 0x1000) && ((Hero003E87D8 *)g_hero_state)->captured == target &&
            vec_distance_xy(target + 0x10, moby + 0x10) < g_tether_capture_distance) {
            moby_set_flag_bit(target, 1);
            vec_clear_128(state + 0x10);
            moby_set_state(moby, 2, -1);
            break;
        }
        break;
    case 2:
        {
            float separation;
            float turn_step, turn_limit;
            float angle = FastAddRotations(mat_fast_helper_a(
                *(float *)(target + 0x10) - *(float *)(moby + 0x10),
                *(float *)(target + 0x14) - *(float *)(moby + 0x14)), 3.1415927f);
            if (FastDiffRots(angle, *(float *)(moby + 0xF8)) > 1.5707964f)
                angle = FastAddRotations(angle, 3.1415927f);
            turn_step = g_tether_turn_step * 6.981318e-06f;
            turn_limit = g_tether_turn_limit * 0.0003490659f;
            math_approach_target_with_direction_mode(moby + 0xF8, state + 0x40, 0, angle, turn_step, turn_step * 3.0f, turn_limit);
            tether_pull_entity_pal(moby);
            separation = vec_distance_xy(moby + 0x10, ((Hero003E87D8 *)g_hero_state)->position);
            if (((Hero003E87D8 *)g_hero_state)->captured != target || separation > g_tether_break_separation) {
                float distance, scaled_distance;
                ((Hero003E87D8 *)g_hero_state)->captured = 0;
                distance = fast_vec_dist(moby + 0x10, ((Hero003E87D8 *)g_hero_state)->position) - g_tether_distance_offset;
                if (distance < 0.0f)
                    distance = 0.0f;
                scaled_distance = distance * 0.020000001f;
                ((Actor003E87D8 *)target)->flags &= 0xEFFF;
                *(float *)(state + 0x44) = g_tether_speed_base * 0.020000001f + g_tether_speed_scale * scaled_distance;
                PlayMobySound(0, 0, moby);
                moby_set_state(moby, 3, -1);
            } else {
                ((Hero003E87D8 *)g_hero_state)->capture_mode = 2;
                cam_set_strength_and_steer_target(moby + 0x10, 0.78539824f, 0.0f);
                cam_set_lock_flag();
                cam_set_speeds_if_nonzero(0.03f, 0.2f);
                if (*(unsigned short *)(target + 0x34) & 0x1000)
                    break;
                moby_set_state(moby, 1, -1);
            }
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            qzero_nc(state + 0x10);
            PlayMobySound(0, 0, moby);
        }
        if (tether_swing_entity_pal(moby)) {
            moby_set_flag_bit(target, 0);
            if (*(short *)(target + 0xAA) == 0x9BC) {
                path_enemy_start_fall(target, state + 0x10);
                g_tether_link_id = 0xFFFF;
            } else {
                platform_start_fall(target, state + 0x10);
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    }
    if (math_fabs(*(float *)(state + 0x40)) > 0.0052359886f) {
        char *slot = g_sound_state + *(int *)(state + 0x58) * 0x70;
        if (*(char **)(slot + 0x88) != moby || *(unsigned char *)(slot + 0x74) == 0)
            *(int *)(state + 0x58) = PlayMobySound(1, 4, moby);
        if (*(unsigned char *)(moby + 0x20) != 2)
            *(float *)(state + 0x40) = 0;
    } else {
        int voice_index = *(int *)(state + 0x58);
        if (voice_index != -1) {
            char *slot = g_sound_state + voice_index * 0x70;
            if (*(char **)(slot + 0x88) == moby && *(unsigned char *)(slot + 0x74))
                snd_stop_voice(voice_index);
        }
        *(int *)(state + 0x58) = -1;
    }
    if (*(char **)(state + 0x54)) {
        matrix_mul_vec3(local, effectOffset003E87D8, moby + 0xC0);
        FastVecAdd(*(char **)(state + 0x54) + 0x10, local, moby + 0x10);
        *(float *)(*(char **)(state + 0x54) + 0xF8) = *(float *)(moby + 0xF8);
        *(float *)(*(char **)(state + 0x54) + 0x2C) = *(float *)(*(char **)(*(char **)(state + 0x54) + 0x24) + 0x24) * g_tether_strand_params[3];
    }
    if (flag_is_third_pending_set(target))
        gfx_add_draw_callback_first(DrawMirroredRibbons_pal, moby);
}
