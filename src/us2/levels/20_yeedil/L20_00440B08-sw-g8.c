#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
extern int g_hero_vehicle_mode, g_frame_l20_counter;
extern int g_level_l20_progress_stage[];
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero g_hero_state;
extern char g_hero_position[];
extern float g_yeedil_small_speed_a __attribute__((sda));
extern float g_yeedil_small_speed_b __attribute__((sda));
extern float g_yeedil_small_accel_a __attribute__((sda));
extern float g_yeedil_small_near_distance __attribute__((sda));
extern float g_yeedil_small_leave_distance __attribute__((sda));
extern float g_yeedil_small_blend_frames __attribute__((sda));
extern float g_yeedil_small_speed_c __attribute__((sda));
extern float g_yeedil_small_accel_b __attribute__((sda));
extern float g_yeedil_small_far_distance;
extern Vector g_yeedil_small_local_vec SDATA(D_L20_001B2010);
extern void yeedil_small_enemy_init_damage_us2(char *), moby_mark_spawned(char *);
extern int flag_set_second_pending(char *), math_random_int_below(int), moby_dispatch_action_by_kind(char *, void *);
extern void SetDeathBits_us2(char *, int, int), part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_enter_state_six(char *), moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void anim_start_blended(char *, int, int, int);
extern float vec_distance_xy(void *, void *);
extern int moby_turn_toward_target_and_step(char *, void *, float);
extern int yeedil_small_enemy_can_attack(char *);
extern float moby_get_anim_value(char *);
extern int moby_l01_turn_toward_target(char *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int math_is_value_within_step_us2(char *, float);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern void euler_rotation_basis(void *, void *);
extern s32 cam_moby_update(char *);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern f32 ApproachValue(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_advance_frame_counter(char *);

/* Runs the small Yeedil enemy each frame (moby class 4510). It circles the hero, chases, shoots when lined up, and falls over when it is hurt (USA v2.00). */
void yeedil_small_enemy_update_us2(char *moby) {
    Vector v;
    Q matrix[3];
    float length;
    char *vars = *(char **)(moby + 0x68);
    int hit;

    yeedil_small_enemy_init_damage_us2(moby);
    if (g_hero_vehicle_mode == 2) {
        if (g_level_l20_progress_stage[0] >= 5) moby_mark_spawned(moby);
        return;
    }
    switch (*(u8 *)(moby + 0x95)) {
    case 0:
        break;
    case 1:
        if (flag_set_second_pending(moby)) *(int *)(vars + 0x284) = math_random_int_below(2);
        break;
    case 2:
        hit = moby_dispatch_action_by_kind(moby, vars + 0x140);
        if (hit & 1) {
            *(int *)(vars + 0x280) = 0;
            SetDeathBits_us2(moby, 0, 3);
            part_queue_moby_for_glow(moby, 0, moby_enter_state_six);
        } else if (hit & 2) moby_set_state(moby, 3, 1);
        break;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 2: {
        float distance;
        if (flag_set_first_pending(moby)) {
            if (*(u8 *)(moby + 0x43) != 2) anim_start_blended(moby, 2, 0, 20);
            *(float *)(vars + 0x78) = g_yeedil_small_speed_a * 0.0166666675f;
            *(float *)(vars + 0x288) = 1.0471977f;
        }
        distance = vec_distance_xy(moby + 0x10, g_hero_position);
        if (distance < g_yeedil_small_near_distance) *(float *)(vars + 0x288) = 2.0943954f;
        else if (g_yeedil_small_far_distance < distance) *(float *)(vars + 0x288) = 1.0471977f;
        if (*(int *)(vars + 0xD0) == 60) {
            *(int *)(vars + 0xD0) = 0;
            *(int *)(vars + 0x284) = (*(int *)(vars + 0x284) + 1) & 1;
        }
        moby_turn_toward_target_and_step(moby, g_hero_position, *(int *)(vars + 0x284) ? *(float *)(vars + 0x288) : - *(float *)(vars + 0x288));
        if ((g_frame_l20_counter & 15) == (((int)moby >> 8) & 15) && yeedil_small_enemy_can_attack(moby)) {
            *(int *)(vars + 0x280) = 1;
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) {
            if (*(u8 *)(moby + 0x43) != 2) anim_start_blended(moby, 2, 0, 10);
            *(float *)(vars + 0x78) = g_yeedil_small_speed_b * 0.0166666675f;
        }
        moby_turn_toward_target_and_step(moby, g_hero_position, 0.0f);
        if (*(float *)(vars + 0x11C) < g_yeedil_small_leave_distance) moby_set_state(moby, 4, -1);
        break;
    case 4: {
        float distance;
        if (flag_set_first_pending(moby)) {
            if (*(u8 *)(moby + 0x43) != 4) anim_start_blended(moby, 4, (int)g_yeedil_small_blend_frames, 10);
        }
        distance = moby_get_anim_value(moby);
        if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43) && distance >= 9.0f && distance <= 17.0f) {
            float accel = g_yeedil_small_accel_b * 0.00027777778f;
            float speed = g_yeedil_small_speed_c * 0.0166666675f;
            *(float *)(vars + 0x74) = accel;
            *(float *)(vars + 0x78) = speed;
            *(float *)(vars + 0x70) = accel;
            moby_l01_turn_toward_target(moby, g_hero_position);
        } else {
            moby_start_effect_from_entry(moby, mat_fast_helper_a(
                g_hero_state.pos[0] - *(float *)(moby + 0x10),
                g_hero_state.pos[1] - *(float *)(moby + 0x14)));
        }
        {
            float accel = g_yeedil_small_accel_a * 0.00027777778f;
            float speed = g_yeedil_small_speed_b * 0.0166666675f;
            *(float *)(vars + 0x74) = accel;
            *(float *)(vars + 0x78) = speed;
            *(float *)(vars + 0x70) = accel;
        }
        if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43) && math_is_value_within_step_us2(moby, 14.0f)) {
            matrix_mul_vec3(&v, &g_yeedil_small_local_vec, moby + 0xC0);
            FastVecAdd(&v, &v, moby + 0x10);
            coll_sweep_from_object(moby, &v, 0x04000001, 0, 0.333f, 2.0f, 1.0f, 1, 0);
        }
        if ((*(u8 *)(moby + 0x60) & 2) && vec_distance_xy(moby + 0x10, g_hero_position) > g_yeedil_small_leave_distance) moby_set_state(moby, 3, -1);
        break;
    }
    case 7:
        *(char **)(moby + 0x68) = vars + 0x210;
        cam_moby_update(moby);
        *(char **)(moby + 0x68) = vars;
        coll_sweep_from_object(moby, moby + 0x10, 0x04000000, 0, 0.5f, 5.0f, 1.0f, 1, 0);
        qzero_nc(&v);
        v.f[2] = *(float *)(vars + 0x288) * 0.0166666675f;
        euler_rotation_basis(matrix, &v);
        matrix_mul_vec3(vars + 0x210, vars + 0x210, matrix);
        length = vec_length_xy(vars + 0x210);
        if (length < 0.0500000045f) {
            ApproachValue(&length, 0.0f, 0.0027777778f);
            if (length <= 0.0f) moby_set_state(moby, 1, 1);
            else vec_fast_normalize_helper(vars + 0x210, vars + 0x210, length);
        }
        if (*(float *)(moby + 0x18) < *(float *)(vars + 0x180)) {
            *(int *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            char *data = *(char **)(moby + 0x24);
            int flags = *(int *)(data + 0x10);
            *(int *)(moby + 0x9C) = 2;
            *(int *)(moby + 0x98) = flags;
            *(u16 *)(moby + 0x34) = *(u16 *)(data + 0x44) | 0x1000;
            matrix_mul_vec3(&v, vars + 0x230, moby + 0xC0);
            FastVecAdd(moby + 0x10, &v, moby + 0x10);
            *(float *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
            qzero(moby + 0xF0);
            *(float *)(moby + 0xF8) = mat_fast_helper_a(
                g_hero_state.pos[0] - *(float *)(moby + 0x10),
                g_hero_state.pos[1] - *(float *)(moby + 0x14));
            if (*(u8 *)(moby + 0x43) != 3) anim_start_blended(moby, 3, 0, 5);
        }
        if (*(u8 *)(moby + 0x60) & 2) moby_set_state(moby, 2, 1);
        break;
    case 5:
    case 6:
        break;
    }
    moby_advance_frame_counter(moby);
}
