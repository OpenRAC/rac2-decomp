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

/* Seesaw beam: tilts when the hero stands on either end and rocks back toward level, playing a creak sound as it moves. */
void UpdateLinkedObjectTilt(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float tiltAccel, previousTilt, tiltScale;
    float dampFactor;
    int linkedOn;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(float *)(vars + 8) = 0;
        if (*(int *)(vars + 0x14) != -1) {
            char *beamEnd = (char *)((*(unsigned int *)(vars + 0x14) << 8) + (unsigned int)g_moby_array);
            int partState = (unsigned char)beamEnd[0x20];
            if (partState == 0xFE) goto first_done;
            if (partState == 0xFD) goto first_done;
            *(char **)vars = beamEnd;
        }
    first_done:
        if (*(int *)(vars + 0x18) != -1) {
            char *beamEnd = (char *)((*(unsigned int *)(vars + 0x18) << 8) + (unsigned int)g_moby_array);
            int partState = (unsigned char)beamEnd[0x20];
            if (partState == 0xFE) goto second_done;
            if (partState == 0xFD) goto second_done;
            *(char **)(vars + 4) = beamEnd;
        }
    second_done:
        *(int *)(vars + 0x10) = seesaw_is_linked_switched_on(*(int *)(vars + 0xC));
        moby[0x20] = 1;
        break;
    case 1:
        tiltAccel = 0;
        if (g_hero_state.enabled) {
            if (g_hero_state.active == *(char **)vars) {
                float tiltRate = math_fast_sin_or_cos_a(*(float *)(moby + 0xF4));
                float heroDistance = vec_distance_xy(g_hero_state.position, moby + 0x10);
                float weightFactor = g_tilt_weight_factor;
                tiltRate *= 0.000004848137450608192f;
                tiltAccel = weightFactor * tiltRate * heroDistance / g_tilt_distance_divisor;
            }
            if (g_hero_state.active == *(char **)(vars + 4)) {
                tiltScale = math_fast_sin_or_cos_a(*(float *)(moby + 0xF4));
                tiltAccel = -(g_tilt_weight_factor * 0.000004848137450608192f) * tiltScale * vec_distance_xy(g_hero_state.position, moby + 0x10) / g_tilt_distance_divisor;
            }
        }
        if (g_hero_state.mode == 3) {
            if (g_hero_state.other == *(char **)vars) {
                float tiltRate = math_fast_sin_or_cos_a(*(float *)(moby + 0xF4));
                float heroDistance = vec_distance_xy(g_hero_state.position, moby + 0x10);
                float weightFactor = g_tilt_weight_factor;
                tiltRate *= 0.000004848137450608192f;
                tiltAccel = weightFactor * tiltRate * heroDistance / g_tilt_distance_divisor;
            }
            if (g_hero_state.other == *(char **)(vars + 4)) {
                tiltScale = math_fast_sin_or_cos_a(*(float *)(moby + 0xF4));
                tiltAccel = -(g_tilt_weight_factor * 0.000004848137450608192f) * tiltScale * vec_distance_xy(g_hero_state.position, moby + 0x10) / g_tilt_distance_divisor;
            }
        }
        if (*(float *)(moby + 0xF4) > g_tilt_over_limit_degrees * 0.01745329424738884f)
            {
            float overTilt = *(float *)(moby + 0xF4) - g_tilt_over_limit_degrees * 0.01745329424738884f;
            float tiltRange = g_tilt_range_degrees * 0.01745329424738884f;
            overTilt /= tiltRange;
            tiltAccel -= g_tilt_restore_factor * (overTilt * 0.000004848137450608192f);
        }
        else if (*(float *)(moby + 0xF4) < -g_tilt_over_limit_degrees * 0.01745329424738884f)
            {
            float overTilt = g_tilt_over_limit_degrees * 0.01745329424738884f + *(float *)(moby + 0xF4);
            float tiltRange = g_tilt_range_degrees * 0.01745329424738884f;
            overTilt /= tiltRange;
            tiltAccel -= g_tilt_restore_factor * (overTilt * 0.000004848137450608192f);
        }
        previousTilt = *(float *)(vars + 8);
        *(float *)(vars + 8) += tiltAccel;
        *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(vars + 8));
        if ((math_fabs(previousTilt) < 0.0002908882452175021f && math_fabs(*(float *)(vars + 8)) > 0.0002908882452175021f) ||
            (math_fabs(previousTilt) < 0.0014544413425028324f && math_fabs(*(float *)(vars + 8)) > 0.0014544413425028324f) ||
            (math_fabs(previousTilt) < 0.002908882685005665f && math_fabs(*(float *)(vars + 8)) > 0.002908882685005665f))
            PlayMobySound(0, 0, moby);
        linkedOn = seesaw_is_linked_switched_on(*(int *)(vars + 0xC));
        if (math_fabs(*(float *)(moby + 0xF4)) > g_tilt_hero_trigger_degrees * 0.01745329424738884f && linkedOn) {
            *(float *)(vars + 8) = 0;
            moby[0x20] = 2;
        }
        dampFactor = g_tilt_damp_factor;
        *(int *)(vars + 0x10) = linkedOn;
        *(float *)(vars + 8) *= dampFactor;
        moby_attach_parts(moby);
        break;
    case 2:
        if (!seesaw_is_linked_switched_on(*(int *)(vars + 0xC))) moby[0x20] = 1;
        break;
    }
}
