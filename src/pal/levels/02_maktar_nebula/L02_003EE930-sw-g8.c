#include "include_asm.h"

#include "common.h"
extern int g_swing_platform_initialized __attribute__((sda));
extern int g_swing_platform_direction __attribute__((sda));
extern float g_swing_platform_speed __attribute__((sda));
extern float g_swing_platform_angle_step __attribute__((sda));
extern int g_frame_l02_counter;
typedef struct { unsigned char pad[3]; unsigned char active; } OwnerFlagView;
extern OwnerFlagView g_game_flag_table __attribute__((nosda));
extern char g_sound_state[], g_drive_velocity_view[];
extern void swing_platform_init_group(void *);
extern int flag_is_third_pending_set(void *);
extern int MemcardSave(int, int);
extern int PlayMobySound(int, int, void *);
extern void group_set_moby_states_from_mode(void *);
extern float math_fabs(float);
extern int swing_platform_is_leading(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float FastAddRotations(float, float);
extern int group_are_mobys_settled(void *);
extern void snd_stop_voice(int);
extern void group_reset_moby_hit_points(void *);
extern float ApproachValue(float *, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int group_update_effect_mobys(void *, void *);
extern float FastVecDot(void *, void *);
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void gfx_draw_energy_sheet(char *);
typedef union { int i[0x20]; float f[0x20]; } PlatState;

/* Updates the platform's activation, swing, travel and scrolling surface. */
void swing_platform_update_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float angles[4], rotation[12], inverse[16], offset[4];
    float speed, distance, target_speed;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
    swing_platform_init_group(moby);
    return;
    case 2:
    if (g_swing_platform_initialized == 0) {
        unsigned int timer, next;
        if (!flag_is_third_pending_set(moby)) return;
        next = *(unsigned short *)(moby + 0x96);
        timer = next;
        next++;
        *(unsigned short *)(moby + 0x96) = next;
        if (timer < 6) return;
    }
    if (*(int *)(state + 4)) { g_game_flag_table.active = 1; MemcardSave(0, -1); }
    *(int *)(state + 0x2C) = PlayMobySound(0, 4, moby);
    group_set_moby_states_from_mode(moby);
    return;
    case 3:
    if (!(math_fabs((float)g_frame_l02_counter - **(float **)(state + 0x28)) > 8.0f)) return;
    if (swing_platform_is_leading(moby)) {
        **(float **)(state + 0x28) = (float)g_frame_l02_counter;
        moby_set_state(moby, 4, -1);
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
        *(float *)(state + 0xC) = 0;
    }
    return;
    case 4:
    speed = 0.024f;
    if (flag_set_first_pending(moby)) speed = 6e+01f;
    qzero(angles);
    angles[2] = *(float *)(state + 0x3C);
    euler_rotation_basis(rotation, angles);
    matrix_from_basis_rows(inverse, rotation);
    FastVecSub(offset, moby + 0x10, state + 0x30);
    matrix_mul_vec3(offset, offset, inverse);
    distance = math_fabs(offset[1]);
    if (distance <= math_fabs(*(float *)(state + 0xC))) {
        offset[1] = 0;
        moby_set_state(moby, 5, -1);
    } else math_step_value_toward_target(offset + 1, state + 0xC, 0.0f, speed, speed, 1.2f);
    matrix_mul_vec3(offset, offset, rotation);
    FastVecAdd(moby + 0x10, state + 0x30, offset);
    return;
    case 5:
    if (flag_set_first_pending(moby)) {
        qcopy(state + 0x40, moby + 0x10);
        *(float *)(state + 0x10) = 0;
        *(float *)(state + 0xC) = 0;
    }
    distance = math_fabs(*(float *)(state + 0x10) - 1.0f);
    if (distance < math_fabs(*(float *)(state + 0xC))) {
        *(float *)(state + 0x10) = 1.0f;
        moby_set_state(moby, 6, -1);
    } else math_step_value_toward_target(state + 0x10, state + 0xC, 1.0f, 0.004f, 0.004f, 0.20000002f);
    lerp_vector(moby + 0x10, state + 0x40, state + 0x30, *(float *)(state + 0x10));
    *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(state + 0x3C), (1.0f - *(float *)(state + 0x10)) * 1.5707965f);
    *(float *)(moby + 0xF0) = (1.0f - *(float *)(state + 0x10)) * 3.1415927f;
    return;
    case 7:
    if (group_are_mobys_settled(moby)) {
        int voice_index = *(int *)(state + 0x2C);
        if (voice_index != -1) {
            char *slot = g_sound_state + voice_index * 0x70;
            if (*(char **)(slot + 0x88) == moby && *(unsigned char *)(slot + 0x74)) snd_stop_voice(voice_index);
        }
        *(int *)(state + 0x2C) = -1;
        group_reset_moby_hit_points(moby);
        moby_set_state(moby, 8, -1);
    }
    return;
    case 8:
    target_speed = (float)g_swing_platform_direction * 0.080000006f;
    ApproachValue(&g_swing_platform_speed, target_speed, 0.0064000003f);
    vec_scale_to_length(angles, moby + 0xD0, g_swing_platform_speed);
    if (group_update_effect_mobys(moby, angles)) {
        if (g_swing_platform_speed == target_speed) {
            if (FastVecDot(g_drive_velocity_view, angles) < -0.001f) {
                if (++((PlatState *)state)->i[8] > 25) g_swing_platform_direction = -g_swing_platform_direction;
            } else ((PlatState *)state)->i[8] = 0;
        } else ((PlatState *)state)->i[8] = 0;
    }
    ((PlatState *)state)->f[5] = FastAddRotations(((PlatState *)state)->f[5], g_swing_platform_angle_step * 0.0003490659f);
    ((PlatState *)state)->f[6] += g_swing_platform_speed * 0.5f;
    if (((PlatState *)state)->f[6] > 1.0f) ((PlatState *)state)->f[6] -= 1.0f;
    else if (((PlatState *)state)->f[6] < -1.0f) ((PlatState *)state)->f[6] += 1.0f;
    ApproachValue(&((PlatState *)state)->f[7], 1.0f, 0.020000001f);
    gfx_add_draw_callback_first(gfx_draw_energy_sheet, moby);
    case 1:
    case 6:
        return;
    }
}
