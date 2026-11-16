#include "names.h"
/* func_PAL_L08_003D0B88, the PAL copy of func_L08_003CCD80: the same C, where wrap D_L08_001AFF58 (({e}) * 1.2f); wrap D_L08_001AFF34 (({e}) * 1.2f); wrap D_L08_001AFF34 (({e}) * 1.2f). */
#include "common.h"

#define FIELD(base, T, offset) (((struct { u8 pad[offset]; T value; } *)(base))->value)

extern char g_sound_state[], g_hero_position_vec[];
extern s16 g_waterfall_vars_short __attribute__((sda));
extern s16 g_waterfall_frozen2_piece_param __attribute__((sda));
extern s16 g_waterfall_frozen_piece_param __attribute__((sda));
extern s16 g_waterfall_piece_param __attribute__((sda));
extern u8 g_waterfall_vars_byte __attribute__((sda));
extern u8 g_waterfall_frozen2_piece_flag __attribute__((sda));
extern u8 g_waterfall_frozen_piece_flag __attribute__((sda));
extern u8 g_waterfall_piece_flag __attribute__((sda));
extern int g_waterfall_spawn_chance_base __attribute__((sda));
extern int g_waterfall_spawn_chance __attribute__((sda));
extern float g_waterfall_height_offset __attribute__((sda));
extern float g_waterfall_velocity_z_offset __attribute__((sda));
extern float g_waterfall_level_step __attribute__((sda));
extern float g_waterfall_accel_range_a __attribute__((sda));
extern float g_waterfall_accel_range_b __attribute__((sda));
extern float g_waterfall_size_min_low __attribute__((sda));
extern float g_waterfall_size_min_high __attribute__((sda));
extern float g_waterfall_size_max_low __attribute__((sda));
extern float g_waterfall_size_max_high __attribute__((sda));
extern float g_waterfall_drift_time_low __attribute__((sda));
extern float g_waterfall_drift_time_high __attribute__((sda));
extern float g_waterfall_drift_param __attribute__((sda));
extern float g_waterfall_spawn_chance_scale __attribute__((sda));
extern float g_waterfall_velocity_xy_range __attribute__((sda));
extern float g_waterfall_velocity_z_low __attribute__((sda));
extern float g_waterfall_velocity_z_high __attribute__((sda));
extern float g_waterfall_accel_xy_range __attribute__((sda));
extern float g_waterfall_accel_z_low __attribute__((sda));
extern float g_waterfall_accel_z_high __attribute__((sda));
extern float g_waterfall_velocity_w_low __attribute__((sda));
extern float g_waterfall_velocity_w_high __attribute__((sda));
extern float g_waterfall_accel_w_low __attribute__((sda));
extern float g_waterfall_accel_w_high __attribute__((sda));
extern float g_waterfall_offset_c0_low __attribute__((sda));
extern float g_waterfall_offset_c0_high __attribute__((sda));
extern float g_waterfall_offset_d0_low __attribute__((sda));
extern float g_waterfall_offset_d0_high __attribute__((sda));
extern float g_waterfall_position_x_scale_low __attribute__((sda));
extern float g_waterfall_position_x_scale_high __attribute__((sda));
extern float g_waterfall_position_y_range __attribute__((sda));
extern float g_waterfall_position_z_range __attribute__((sda));
extern int g_waterfall_trail_param_a __attribute__((sda));
extern int g_waterfall_trail_param_b __attribute__((sda));
extern int g_waterfall_trail_param_c __attribute__((sda));
extern int g_waterfall_trail_param_d __attribute__((sda));
extern int g_waterfall_trail_param_e __attribute__((sda));
extern float IntToFloat(int);
extern float moby_get_height(int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern int moby_is_linked_switched_on(int);
extern int math_random_int_below(int);
extern int PlayMobySound(int, int, void *);
extern void *waterfall_spawn_piece(void *, int, short, int, int, unsigned char, unsigned char);
extern void offset_moby_class_point_pairs(void *, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void mat_fast_helper_c(void *, void *);
extern void add_vectors(void *, void *, void *);
extern void snd_stop_voice(int);
extern void water_stop_effect(float, float, float, float);
extern void *part_spawn_drifting(void *, int, int, float, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L08_003D0B88(char * object) {
    char * state = FIELD(object, char *, 0x68), *sound;
    int rotationDelta;
    int slot;
    float first, second;
    float velocityX, velocityY, accelerationX, accelerationY;
    float velocity[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float inverseBasis[12] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (!FIELD(object, u8, 0x20)) {
        if (FIELD(object, s16, 0xAA) == 0x8F9) {
            FIELD(state, s16, 4) = g_waterfall_vars_short;
            FIELD(state, u8, 0x1E) = g_waterfall_vars_byte;
            FIELD(state, float, 8) = IntToFloat(FIELD(state, u8, 0x1C));
            FIELD(state, void *, 0x10) = waterfall_spawn_piece(object, 0x8F8, g_waterfall_frozen2_piece_param, FIELD(state, u8, 0x1C), FIELD(state, int, 0), g_waterfall_frozen2_piece_flag, FIELD(state, u8, 0x1D));
            FIELD(state, void *, 0x14) = waterfall_spawn_piece(object, 0x8F7, g_waterfall_frozen_piece_param, FIELD(state, u8, 0x1C), FIELD(state, int, 0), g_waterfall_frozen_piece_flag, FIELD(state, u8, 0x1D));
            FIELD(state, void *, 0x18) = waterfall_spawn_piece(object, 0x8F6, g_waterfall_piece_param, FIELD(state, u8, 0x1C), FIELD(state, int, 0), g_waterfall_piece_flag, FIELD(state, u8, 0x1D));
        }
        FIELD(state, float, 0xC) = moby_get_height(FIELD(state, int, 0));
        FIELD(object, float, 0x18) += g_waterfall_height_offset;
        FIELD(object, u16, 0x34) |= 0x2008;
        FIELD(state, s8, 0x1F) = -1;
        FIELD(object, u8, 0x20) = 1;
    }
    FIELD(object, float, 0x18) += ((FIELD(state, float, 0xC) + 0.2f + g_waterfall_height_offset * (1.0f - FIELD(state, float, 8))) - FIELD(object, float, 0x18)) * 0.1f;
    if (moby_is_linked_switched_on(FIELD(state, int, 0))) {
        if (!FIELD(state, u8, 0x1C)) {
            FIELD(state, float, 8) += ((g_waterfall_level_step) * 1.2f);
            if (FIELD(state, float, 8) > 1) {
                FIELD(state, float, 8) = 1;
                FIELD(state, u8, 0x1C) = 1;
            }
        }
    } else if (FIELD(state, u8, 0x1C)) {
        FIELD(state, float, 8) -= ((g_waterfall_level_step) * 1.2f);
        if (FIELD(state, float, 8) < 0) {
            FIELD(state, float, 8) = 0;
            FIELD(state, u8, 0x1C) = 0;
        }
    }
    FIELD(object, u8, 0x23) = FIELD(state, u8, 0x1E) + FloatToInt(IntToFloat(255 - FIELD(state, u8, 0x1E)) * FIELD(state, float, 8));
    if (FIELD(state, float, 8) < 1) {
        if (FIELD(state, u8, 0x1D)) {
            rotationDelta = -FloatToInt(IntToFloat(FIELD(state, s16, 4)) * (1.0f - FIELD(state, float, 8)));
            FIELD(state, s16, 6) += rotationDelta;
            if (FIELD(state, s16, 6) > 4096) {
                FIELD(state, s16, 6) -= 4096;
                rotationDelta -= 4096;
            } else if (FIELD(state, s16, 6) < 0) {
                FIELD(state, s16, 6) += 4096;
                rotationDelta += 4096;
            }
            offset_moby_class_point_pairs(FIELD(object, void *, 0x24), 0, rotationDelta);
        }
        if (!math_random_int_below(g_waterfall_spawn_chance_base + FloatToInt(g_waterfall_spawn_chance_scale * FIELD(state, float, 8)) - 1)) {
            vec_scale_to_length(acceleration, object + 0xC0, math_random_float_range(-g_waterfall_accel_range_a, g_waterfall_accel_range_a));
            FastVecAdd(velocity, object + 0x10, acceleration);
            vec_scale_to_length(acceleration, object + 0xD0, math_random_float_range(-g_waterfall_accel_range_b, g_waterfall_accel_range_b));
            FastVecAdd(velocity, velocity, acceleration);
            velocity[2] = FIELD(state, float, 0xC) + g_waterfall_velocity_z_offset;
            first = math_random_float_range(g_waterfall_size_min_low, g_waterfall_size_min_high);
            second = math_random_float_range(g_waterfall_size_max_low, g_waterfall_size_max_high);
            water_stop_effect(velocity[0], velocity[1], first, second);
            part_spawn_drifting(velocity, 0, -1, math_random_float_range(g_waterfall_drift_time_low, g_waterfall_drift_time_high), ((g_waterfall_drift_param) * 1.2f));
        }
    }
    if (!FIELD(state, u8, 0x1C)) {
        if (FIELD(object, s16, 0xAA) == 0x8F9) {
            slot = FIELD(state, s8, 0x1F);
            sound = g_sound_state + slot * 0x70;
            if (FIELD(sound, void *, 0x88) != object || !FIELD(sound, u8, 0x74))
                slot = PlayMobySound(0, 4, object);
            FIELD(state, s8, 0x1F) = slot;
            if (!math_random_int_below(g_waterfall_spawn_chance - 1)) {
                velocity[3] = math_random_float_range(g_waterfall_velocity_w_low, g_waterfall_velocity_w_high);
                acceleration[3] = math_random_float_range(g_waterfall_accel_w_low, g_waterfall_accel_w_high);
                if (!math_random_int_below(2)) {
                    qcopy(position, object + 0x10);
                    position[2] += g_waterfall_position_z_range;
                    vec_scale_to_length(offset, object + 0xC0, math_random_float_range(g_waterfall_offset_c0_low, g_waterfall_offset_c0_high));
                    FastVecAdd(position, position, offset);
                    vec_scale_to_length(offset, object + 0xD0, math_random_float_range(g_waterfall_offset_d0_low, g_waterfall_offset_d0_high));
                    FastVecAdd(position, position, offset);
                } else {
                    FastVecSub(position, g_hero_position_vec, object + 0x10);
                    vec_scale_to_length(position, position, 1);
                    position[2] = 0;
                    mat_fast_helper_c(inverseBasis, object + 0xC0);
                    matrix_mul_vec3(position, position, inverseBasis);
                    position[0] *= math_random_float_range(g_waterfall_position_x_scale_low, g_waterfall_position_x_scale_high);
                    position[1] *= math_random_float_range(0, g_waterfall_position_y_range);
                    position[2] = math_random_float_range(0, g_waterfall_position_z_range);
                    matrix_mul_vec3(position, position, object + 0xC0);
                    add_vectors(delta, position, object + 0x10);
                }
                velocityX = math_fast_sin_or_cos_a(math_random_angle());
                velocityX *= math_random_float_range(0, g_waterfall_velocity_xy_range * 0.020000001f);
                velocity[0] = velocityX;
                velocityY = math_fast_sin_or_cos_b(math_random_angle());
                velocityY *= math_random_float_range(0, g_waterfall_velocity_xy_range * 0.020000001f);
                velocity[1] = velocityY;
                velocity[2] = 0;
                velocity[2] = math_random_float_range(g_waterfall_velocity_z_low, g_waterfall_velocity_z_high) * 0.020000001f;
                accelerationX = math_fast_sin_or_cos_a(math_random_angle());
                accelerationX *= math_random_float_range(0, g_waterfall_accel_xy_range * 0.020000001f);
                acceleration[0] = accelerationX;
                accelerationY = math_fast_sin_or_cos_b(math_random_angle());
                accelerationY *= math_random_float_range(0, g_waterfall_accel_xy_range * 0.020000001f);
                acceleration[1] = accelerationY;
                acceleration[2] = 0;
                acceleration[2] = math_random_float_range(g_waterfall_accel_z_low, g_waterfall_accel_z_high) * 0.020000001f;
                part_spawn_trail(position, velocity, acceleration, g_waterfall_trail_param_a, g_waterfall_trail_param_b, g_waterfall_trail_param_c, g_waterfall_trail_param_d, g_waterfall_trail_param_e, -1);
            }
        }
        FIELD(object, int, 0x98) = 0;
    } else {
        int stopSlot;
        if (FIELD(object, s16, 0xAA) == 0x8F9 && FIELD(state, s8, 0x1F) != -1) {
            stopSlot = FIELD(state, s8, 0x1F);
            sound = g_sound_state + stopSlot * 0x70;
            if (FIELD(sound, void *, 0x88) == object && FIELD(sound, u8, 0x74))
                snd_stop_voice(stopSlot);
            stopSlot = -1;
            FIELD(state, s8, 0x1F) = stopSlot;
        }
        FIELD(object, int, 0x98) = FIELD(FIELD(object, char *, 0x24), int, 0x10);
    }
}
