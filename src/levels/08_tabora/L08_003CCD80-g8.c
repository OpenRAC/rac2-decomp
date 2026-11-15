#include "common.h"

#define FIELD(base, T, offset) (((struct { u8 pad[offset]; T value; } *)(base))->value)

extern char g_sound_state[], D_L08_001B9B00[];
extern s16 D_L08_001AFF24 __attribute__((sda));
extern s16 D_L08_001AFF26 __attribute__((sda));
extern s16 D_L08_001AFF28 __attribute__((sda));
extern s16 D_L08_001AFF2A __attribute__((sda));
extern u8 D_L08_001AFF2C __attribute__((sda));
extern u8 D_L08_001AFF2E __attribute__((sda));
extern u8 D_L08_001AFF30 __attribute__((sda));
extern u8 D_L08_001AFF32 __attribute__((sda));
extern int D_L08_001AFF5C __attribute__((sda));
extern int D_L08_001AFFC0 __attribute__((sda));
extern float D_L08_001AFFC8 __attribute__((sda));
extern float D_L08_001AFFCC __attribute__((sda));
extern float D_L08_001AFF34 __attribute__((sda));
extern float D_L08_001AFF38 __attribute__((sda));
extern float D_L08_001AFF3C __attribute__((sda));
extern float D_L08_001AFF40 __attribute__((sda));
extern float D_L08_001AFF44 __attribute__((sda));
extern float D_L08_001AFF48 __attribute__((sda));
extern float D_L08_001AFF4C __attribute__((sda));
extern float D_L08_001AFF50 __attribute__((sda));
extern float D_L08_001AFF54 __attribute__((sda));
extern float D_L08_001AFF58 __attribute__((sda));
extern float D_L08_001AFF60 __attribute__((sda));
extern float D_L08_001AFF64 __attribute__((sda));
extern float D_L08_001AFF68 __attribute__((sda));
extern float D_L08_001AFF6C __attribute__((sda));
extern float D_L08_001AFF70 __attribute__((sda));
extern float D_L08_001AFF74 __attribute__((sda));
extern float D_L08_001AFF78 __attribute__((sda));
extern float D_L08_001AFF90 __attribute__((sda));
extern float D_L08_001AFF94 __attribute__((sda));
extern float D_L08_001AFF98 __attribute__((sda));
extern float D_L08_001AFF9C __attribute__((sda));
extern float D_L08_001AFFA0 __attribute__((sda));
extern float D_L08_001AFFA4 __attribute__((sda));
extern float D_L08_001AFFA8 __attribute__((sda));
extern float D_L08_001AFFAC __attribute__((sda));
extern float D_L08_001AFFB0 __attribute__((sda));
extern float D_L08_001AFFB4 __attribute__((sda));
extern float D_L08_001AFFBC __attribute__((sda));
extern float D_L08_001AFFC4 __attribute__((sda));
extern int D_L08_001AFF7C __attribute__((sda));
extern int D_L08_001AFF80 __attribute__((sda));
extern int D_L08_001AFF84 __attribute__((sda));
extern int D_L08_001AFF88 __attribute__((sda));
extern int D_L08_001AFF8C __attribute__((sda));
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

/* Waterfall: opens and closes with its linked switch, spins its texture, and sprays mist and drops while flowing. */
void UpdateWaterfall(char * moby) {
    char * vars = FIELD(moby, char *, 0x68), *sound_slot_entry;
    int rotationDelta;
    int sound_slot;
    float size_min, size_max;
    float velocityX, velocityY, accelerationX, accelerationY;
    float velocity[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float inverseBasis[12] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (!FIELD(moby, u8, 0x20)) {
        if (FIELD(moby, s16, 0xAA) == MOBY_CLASS_WATERFALL_FROZEN_3) {
            FIELD(vars, s16, 4) = D_L08_001AFF24;
            FIELD(vars, u8, 0x1E) = D_L08_001AFF2C;
            FIELD(vars, float, 8) = IntToFloat(FIELD(vars, u8, 0x1C));
            FIELD(vars, void *, 0x10) = waterfall_spawn_piece(moby, MOBY_CLASS_WATERFALL_FROZEN_2, D_L08_001AFF26, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF2E, FIELD(vars, u8, 0x1D));
            FIELD(vars, void *, 0x14) = waterfall_spawn_piece(moby, MOBY_CLASS_WATERFALL_FROZEN, D_L08_001AFF28, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF30, FIELD(vars, u8, 0x1D));
            FIELD(vars, void *, 0x18) = waterfall_spawn_piece(moby, MOBY_CLASS_WATERFALL, D_L08_001AFF2A, FIELD(vars, u8, 0x1C), FIELD(vars, int, 0), D_L08_001AFF32, FIELD(vars, u8, 0x1D));
        }
        FIELD(vars, float, 0xC) = moby_get_height(FIELD(vars, int, 0));
        FIELD(moby, float, 0x18) += D_L08_001AFFC8;
        FIELD(moby, u16, 0x34) |= 0x2008;
        FIELD(vars, s8, 0x1F) = -1;
        FIELD(moby, u8, 0x20) = 1;
    }
    FIELD(moby, float, 0x18) += ((FIELD(vars, float, 0xC) + 0.2f + D_L08_001AFFC8 * (1.0f - FIELD(vars, float, 8))) - FIELD(moby, float, 0x18)) * 0.1f;
    if (moby_is_linked_switched_on(FIELD(vars, int, 0))) {
        if (!FIELD(vars, u8, 0x1C)) {
            FIELD(vars, float, 8) += D_L08_001AFF34;
            if (FIELD(vars, float, 8) > 1) {
                FIELD(vars, float, 8) = 1;
                FIELD(vars, u8, 0x1C) = 1;
            }
        }
    } else if (FIELD(vars, u8, 0x1C)) {
        FIELD(vars, float, 8) -= D_L08_001AFF34;
        if (FIELD(vars, float, 8) < 0) {
            FIELD(vars, float, 8) = 0;
            FIELD(vars, u8, 0x1C) = 0;
        }
    }
    FIELD(moby, u8, 0x23) = FIELD(vars, u8, 0x1E) + FloatToInt(IntToFloat(255 - FIELD(vars, u8, 0x1E)) * FIELD(vars, float, 8));
    if (FIELD(vars, float, 8) < 1) {
        if (FIELD(vars, u8, 0x1D)) {
            rotationDelta = -FloatToInt(IntToFloat(FIELD(vars, s16, 4)) * (1.0f - FIELD(vars, float, 8)));
            FIELD(vars, s16, 6) += rotationDelta;
            if (FIELD(vars, s16, 6) > 4096) {
                FIELD(vars, s16, 6) -= 4096;
                rotationDelta -= 4096;
            } else if (FIELD(vars, s16, 6) < 0) {
                FIELD(vars, s16, 6) += 4096;
                rotationDelta += 4096;
            }
            offset_moby_class_point_pairs(FIELD(moby, void *, 0x24), 0, rotationDelta);
        }
        if (!math_random_int_below(D_L08_001AFF5C + FloatToInt(D_L08_001AFF60 * FIELD(vars, float, 8)) - 1)) {
            vec_scale_to_length(acceleration, moby + 0xC0, math_random_float_range(-D_L08_001AFF38, D_L08_001AFF38));
            FastVecAdd(velocity, moby + 0x10, acceleration);
            vec_scale_to_length(acceleration, moby + 0xD0, math_random_float_range(-D_L08_001AFF3C, D_L08_001AFF3C));
            FastVecAdd(velocity, velocity, acceleration);
            velocity[2] = FIELD(vars, float, 0xC) + D_L08_001AFFCC;
            size_min = math_random_float_range(D_L08_001AFF40, D_L08_001AFF44);
            size_max = math_random_float_range(D_L08_001AFF48, D_L08_001AFF4C);
            water_stop_effect(velocity[0], velocity[1], size_min, size_max);
            part_spawn_drifting(velocity, 0, -1, math_random_float_range(D_L08_001AFF50, D_L08_001AFF54), D_L08_001AFF58);
        }
    }
    if (!FIELD(vars, u8, 0x1C)) {
        if (FIELD(moby, s16, 0xAA) == MOBY_CLASS_WATERFALL_FROZEN_3) {
            sound_slot = FIELD(vars, s8, 0x1F);
            sound_slot_entry = g_sound_state + sound_slot * 0x70;
            if (FIELD(sound_slot_entry, void *, 0x88) != moby || !FIELD(sound_slot_entry, u8, 0x74))
                sound_slot = PlayMobySound(0, 4, moby);
            FIELD(vars, s8, 0x1F) = sound_slot;
            if (!math_random_int_below(D_L08_001AFFC0 - 1)) {
                velocity[3] = math_random_float_range(D_L08_001AFF90, D_L08_001AFF94);
                acceleration[3] = math_random_float_range(D_L08_001AFF98, D_L08_001AFF9C);
                if (!math_random_int_below(2)) {
                    qcopy(position, moby + 0x10);
                    position[2] += D_L08_001AFFC4;
                    vec_scale_to_length(offset, moby + 0xC0, math_random_float_range(D_L08_001AFFA0, D_L08_001AFFA4));
                    FastVecAdd(position, position, offset);
                    vec_scale_to_length(offset, moby + 0xD0, math_random_float_range(D_L08_001AFFA8, D_L08_001AFFAC));
                    FastVecAdd(position, position, offset);
                } else {
                    FastVecSub(position, D_L08_001B9B00, moby + 0x10);
                    vec_scale_to_length(position, position, 1);
                    position[2] = 0;
                    mat_fast_helper_c(inverseBasis, moby + 0xC0);
                    matrix_mul_vec3(position, position, inverseBasis);
                    position[0] *= math_random_float_range(D_L08_001AFFB0, D_L08_001AFFB4);
                    position[1] *= math_random_float_range(0, D_L08_001AFFBC);
                    position[2] = math_random_float_range(0, D_L08_001AFFC4);
                    matrix_mul_vec3(position, position, moby + 0xC0);
                    add_vectors(delta, position, moby + 0x10);
                }
                velocityX = math_fast_sin_or_cos_a(math_random_angle());
                velocityX *= math_random_float_range(0, D_L08_001AFF64 * 0.016666668f);
                velocity[0] = velocityX;
                velocityY = math_fast_sin_or_cos_b(math_random_angle());
                velocityY *= math_random_float_range(0, D_L08_001AFF64 * 0.016666668f);
                velocity[1] = velocityY;
                velocity[2] = 0;
                velocity[2] = math_random_float_range(D_L08_001AFF68, D_L08_001AFF6C) * 0.016666668f;
                accelerationX = math_fast_sin_or_cos_a(math_random_angle());
                accelerationX *= math_random_float_range(0, D_L08_001AFF70 * 0.016666668f);
                acceleration[0] = accelerationX;
                accelerationY = math_fast_sin_or_cos_b(math_random_angle());
                accelerationY *= math_random_float_range(0, D_L08_001AFF70 * 0.016666668f);
                acceleration[1] = accelerationY;
                acceleration[2] = 0;
                acceleration[2] = math_random_float_range(D_L08_001AFF74, D_L08_001AFF78) * 0.016666668f;
                part_spawn_trail(position, velocity, acceleration, D_L08_001AFF7C, D_L08_001AFF80, D_L08_001AFF84, D_L08_001AFF88, D_L08_001AFF8C, -1);
            }
        }
        FIELD(moby, int, 0x98) = 0;
    } else {
        int playing_slot;
        if (FIELD(moby, s16, 0xAA) == MOBY_CLASS_WATERFALL_FROZEN_3 && FIELD(vars, s8, 0x1F) != -1) {
            playing_slot = FIELD(vars, s8, 0x1F);
            sound_slot_entry = g_sound_state + playing_slot * 0x70;
            if (FIELD(sound_slot_entry, void *, 0x88) == moby && FIELD(sound_slot_entry, u8, 0x74))
                snd_stop_voice(playing_slot);
            playing_slot = -1;
            FIELD(vars, s8, 0x1F) = playing_slot;
        }
        FIELD(moby, int, 0x98) = FIELD(FIELD(moby, char *, 0x24), int, 0x10);
    }
}
