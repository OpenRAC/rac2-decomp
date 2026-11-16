#include "include_asm.h"
#include "names.h"

typedef struct { char pad0[0x80]; char position[0x2BC]; char *active; int enabled; char pad1[0x244]; char *other; char pad2[0x1D10]; int mode; } Globals;
extern Globals g_hero_state;
extern char *g_moby_array;
extern float g_tilt_weight_factor __attribute__((sda)), g_tilt_over_limit_degrees __attribute__((sda)), g_tilt_range_degrees __attribute__((sda));
extern float g_tilt_restore_factor __attribute__((sda)), g_tilt_distance_divisor __attribute__((sda)), g_tilt_hero_trigger_degrees __attribute__((sda)), g_tilt_damp_factor __attribute__((sda));
extern int seesaw_is_linked_switched_on(int);
extern float math_fast_sin_or_cos_a(float);
extern float vec_distance_xy(void *, void *);
extern float FastAddRotations(float, float);
extern float math_fabs(float);
extern int PlayMobySound(int, int, void *);
extern void moby_attach_parts(void *);

/* Seesaw beam: tilts when the hero stands on either end and rocks back toward level, playing a creak sound as it moves (PAL: 50 Hz timings). */
void UpdateLinkedObjectTilt_pal(char *object) {
    char *state = *(char **)(object + 0x68);
    float delta, previous, magnitude;
    float damping;
    int result;
    switch ((unsigned char)object[0x20]) {
    case 0:
        *(float *)(state + 8) = 0;
        if (*(int *)(state + 0x14) != -1) {
            char *part = (char *)((*(unsigned int *)(state + 0x14) << 8) + (unsigned int)g_moby_array);
            int status = (unsigned char)part[0x20];
            if (status == 0xFE) goto first_done;
            if (status == 0xFD) goto first_done;
            *(char **)state = part;
        }
    first_done:
        if (*(int *)(state + 0x18) != -1) {
            char *part = (char *)((*(unsigned int *)(state + 0x18) << 8) + (unsigned int)g_moby_array);
            int status = (unsigned char)part[0x20];
            if (status == 0xFE) goto second_done;
            if (status == 0xFD) goto second_done;
            *(char **)(state + 4) = part;
        }
    second_done:
        *(int *)(state + 0x10) = seesaw_is_linked_switched_on(*(int *)(state + 0xC));
        object[0x20] = 1;
        break;
    case 1:
        delta = 0;
        if (g_hero_state.enabled) {
            if (g_hero_state.active == *(char **)state) {
                float angular = math_fast_sin_or_cos_a(*(float *)(object + 0xF4));
                float distance = vec_distance_xy(g_hero_state.position, object + 0x10);
                float coefficient = g_tilt_weight_factor;
                angular *= 6.981318e-06f;
                delta = coefficient * angular * distance / g_tilt_distance_divisor;
            }
            if (g_hero_state.active == *(char **)(state + 4)) {
                magnitude = math_fast_sin_or_cos_a(*(float *)(object + 0xF4));
                delta = -(g_tilt_weight_factor * 6.981318e-06f) * magnitude * vec_distance_xy(g_hero_state.position, object + 0x10) / g_tilt_distance_divisor;
            }
        }
        if (g_hero_state.mode == 3) {
            if (g_hero_state.other == *(char **)state) {
                float angular = math_fast_sin_or_cos_a(*(float *)(object + 0xF4));
                float distance = vec_distance_xy(g_hero_state.position, object + 0x10);
                float coefficient = g_tilt_weight_factor;
                angular *= 6.981318e-06f;
                delta = coefficient * angular * distance / g_tilt_distance_divisor;
            }
            if (g_hero_state.other == *(char **)(state + 4)) {
                magnitude = math_fast_sin_or_cos_a(*(float *)(object + 0xF4));
                delta = -(g_tilt_weight_factor * 6.981318e-06f) * magnitude * vec_distance_xy(g_hero_state.position, object + 0x10) / g_tilt_distance_divisor;
            }
        }
        if (*(float *)(object + 0xF4) > g_tilt_over_limit_degrees * 0.01745329424738884f)
            {
            float offset = *(float *)(object + 0xF4) - g_tilt_over_limit_degrees * 0.01745329424738884f;
            float range = g_tilt_range_degrees * 0.01745329424738884f;
            offset /= range;
            delta -= g_tilt_restore_factor * (offset * 6.981318e-06f);
        }
        else if (*(float *)(object + 0xF4) < -g_tilt_over_limit_degrees * 0.01745329424738884f)
            {
            float offset = g_tilt_over_limit_degrees * 0.01745329424738884f + *(float *)(object + 0xF4);
            float range = g_tilt_range_degrees * 0.01745329424738884f;
            offset /= range;
            delta -= g_tilt_restore_factor * (offset * 6.981318e-06f);
        }
        previous = *(float *)(state + 8);
        *(float *)(state + 8) += delta;
        *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 8));
        if ((math_fabs(previous) < 0.0003490659f && math_fabs(*(float *)(state + 8)) > 0.0003490659f) ||
            (math_fabs(previous) < 0.0017453296f && math_fabs(*(float *)(state + 8)) > 0.0017453296f) ||
            (math_fabs(previous) < 0.0034906592f && math_fabs(*(float *)(state + 8)) > 0.0034906592f))
            PlayMobySound(0, 0, object);
        result = seesaw_is_linked_switched_on(*(int *)(state + 0xC));
        if (math_fabs(*(float *)(object + 0xF4)) > g_tilt_hero_trigger_degrees * 0.01745329424738884f && result) {
            *(float *)(state + 8) = 0;
            object[0x20] = 2;
        }
        damping = g_tilt_damp_factor;
        *(int *)(state + 0x10) = result;
        *(float *)(state + 8) *= damping;
        moby_attach_parts(object);
        break;
    case 2:
        if (!seesaw_is_linked_switched_on(*(int *)(state + 0xC))) object[0x20] = 1;
        break;
    }
}
