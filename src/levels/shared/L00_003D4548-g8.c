#include "common.h"

typedef struct { char pad[0x80]; float x, y; } PositionBase;
extern PositionBase g_hero_state __attribute__((nosda));
extern char g_hero_position[] __attribute__((nosda));
extern float g_keep_near_yaw_rate __attribute__((sda));
extern float g_keep_near_pitch_rate __attribute__((sda));
extern float g_keep_near_turn_rate __attribute__((sda));
extern float g_keep_near_param_a __attribute__((sda));
extern float g_keep_near_param_b __attribute__((sda));
extern float g_keep_near_param_c __attribute__((sda));
extern float g_keep_near_limit __attribute__((sda));
extern float g_keep_near_scale __attribute__((sda));
extern void ref_L00_003D4548_00(void *, void *, void *);
extern float ref_L00_003D4548_01(void *, void *);
extern void ref_L00_003D4548_02(void *, void *, void *, float, float, float);
extern void ref_L00_003D4548_03(void *, void *, float);
extern void ref_L00_003D4548_04(void *, void *, void *);
extern void ref_L00_003D4548_05(void *, void *, float);
extern int ref_L00_003D4548_06(void *, void *, int, float, float, float);
extern float ref_L00_003D4548_07(void *);
extern float ref_L00_003D4548_08(float, float);
extern float ref_L00_003D4548_09(float);
extern float ref_L00_003D4548_10(float);
extern float ref_L00_003D4548_11(float, float);
extern void ref_L00_003D4548_12(void *, void *, void *, float, float, float);

/* Keeps the moby close to its target or the hero. It eases along, backs off when too near the hero, and jumps back to its start spot when stuck for a while. */
void moby_keep_near_target_or_hero(char *object, char *state)
{
    float difference[4], offset[4];
    float distance, angle, correction, speed;
    int hit;
    char *target;
    ref_L00_003D4548_00(difference, state, object + 0x10);
    distance = ref_L00_003D4548_01(object + 0x10, g_hero_position);
    ref_L00_003D4548_01(object + 0x10, state);
    switch (*(unsigned char *)(object + 0xbc)) {
    case 0:
        ref_L00_003D4548_02(object, state, state + 0x30,
                           0.00174532947f, 0.000872664736f, 0.191986248f);
        *(unsigned char *)(object + 0xbc) = 2;
        break;
    case 2:
        target = *(char **)(state + 0x28);
        if (!target)
            ref_L00_003D4548_02(object, state, state + 0x30,
                               0.00174532947f, 0.000872664736f, 0.191986248f);
        else
            ref_L00_003D4548_02(object, target + 0x10, state + 0x30,
                               g_keep_near_yaw_rate * 4.84813745e-6f,
                               g_keep_near_pitch_rate * 4.84813745e-6f,
                               g_keep_near_turn_rate * 0.000290888245f);
        ref_L00_003D4548_03(difference, difference, 0.04f);
        ref_L00_003D4548_00(difference, difference, state + 0x10);
        if (distance > 1.3f)
            ref_L00_003D4548_03(difference, difference, 0.13f);
        else
            ref_L00_003D4548_03(difference, difference, 0.25f);
        difference[2] *= 0.9f;
        ref_L00_003D4548_04(state + 0x10, state + 0x10, difference);
        if (*(unsigned char *)(object + 0x20) == 2)
            ref_L00_003D4548_05(state + 0x10, state + 0x10, 0.045f);
        hit = ref_L00_003D4548_06(object, state + 0x10, 0, 1.0f, 0.5f, 0.0f);
        speed = ref_L00_003D4548_07(state + 0x10);
        if (hit) {
            if (speed < 0.005f) {
                if (++*(unsigned char *)(state + 0x26) > 20 && !*(unsigned char *)(object + 0x31)) {
                    qcopy(object + 0x10, state);
                    *(unsigned char *)(state + 0x26) = 0;
                }
            }
        } else {
            *(unsigned char *)(state + 0x26) = 0;
        }
        if (distance < 1.1f) {
            correction = 1.1f - distance;
            angle = ref_L00_003D4548_08(g_hero_state.x - *(float *)(object + 0x10),
                                      g_hero_state.y - *(float *)(object + 0x14));
            *(float *)(state + 0x10) -= correction * ref_L00_003D4548_09(angle) * 0.1f;
            *(float *)(state + 0x14) -= correction * ref_L00_003D4548_10(angle) * 0.1f;
        }
        break;
    default:
        *(unsigned char *)(object + 0xbc) = 0;
        if (distance > 1.3f) *(unsigned char *)(object + 0xbc) = 2;
        break;
    }
    *(float *)(state + 0x54) = ref_L00_003D4548_11(*(float *)(state + 0x54), g_keep_near_limit);
    ref_L00_003D4548_03(offset, object + 0xe0, *(float *)(state + 0x50));
    ref_L00_003D4548_00(object + 0x10, object + 0x10, offset);
    *(float *)(state + 0x50) = ref_L00_003D4548_10(*(float *)(state + 0x54)) * g_keep_near_scale;
    ref_L00_003D4548_03(offset, object + 0xe0, *(float *)(state + 0x50));
    ref_L00_003D4548_04(object + 0x10, object + 0x10, offset);
    ref_L00_003D4548_12(object, state + 0x48, state + 0x4c, g_keep_near_param_a, g_keep_near_param_b, g_keep_near_param_c);
}
