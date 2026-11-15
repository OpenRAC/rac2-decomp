#include "include_asm.h"

#include "common.h"
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_animation_and_speed(void *, int, int, int);
extern int func_PAL_L01_00323068(void *, void *);
extern int func_PAL_002B5E30(void *, float);
typedef struct {
    u8 prefix[0x30];
    float centre[4];
    u8 rest[0x40];
} L01ArenaRow;
extern L01ArenaRow *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001AFED0 __attribute__((sda));
typedef struct {
    u8 prefix[0x80];
    float position[4];
} L01HeroPositionView;
extern u8 g_hero_state[];

float func_PAL_L01_003C4250(u8 *obj)
{
    u8 *s = *(u8 **)(obj + 0x68);
    float distance, angle, delta, magnitude;

    if (*(int *)(s + 0x124) == 1) {
        distance = vec_distance_xy(obj + 0x10, *(u8 **)(s + 0x120) + 0x10);
        angle = mat_fast_helper_a(
            *(float *)(obj + 0x10) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[0],
            *(float *)(obj + 0x14) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[1]);
        delta = fast_subtract_rotations(
            mat_fast_helper_a(
                *(float *)(*(u8 **)(s + 0x120) + 0x10) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[0],
                *(float *)(*(u8 **)(s + 0x120) + 0x14) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[1]),
            angle);
        magnitude = math_fabs(delta);
        if (distance > *(float *)(s + 0x2EC)) {
            if (obj[0x43] != s[0x2E1])
                moby_set_animation_and_speed(obj, s[0x2E1], 0, 20);
            if (magnitude < D_L01_001AFED0 * 0.017453294f) {
                qcopy(s + 0x2A0, *(u8 **)(s + 0x120) + 0x10);
            } else {
                delta = delta / magnitude;
                delta = delta * 0.087266474f;
                qcopy(s + 0x2A0, D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre);
                *(float *)(s + 0x2A0) += math_fast_sin_or_cos_a(FastAddRotations(angle, delta)) * 38.0f;
                *(float *)(s + 0x2A4) += math_fast_sin_or_cos_b(FastAddRotations(angle, delta)) * 38.0f;
            }
            func_PAL_L01_00323068(obj, s + 0x2A0);
            *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
        } else {
            if (obj[0x43] != s[0x2E2] && obj[0x95] != 3)
                moby_set_animation_and_speed(obj, s[0x2E2], 0, 20);
            func_PAL_002B5E30(obj, mat_fast_helper_a(*(float *)(*(u8 **)(s + 0x120) + 0x10) - *(float *)(obj + 0x10),
                                             *(float *)(*(u8 **)(s + 0x120) + 0x14) - *(float *)(obj + 0x14)));
            *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
        }
        return distance;
    }
    if (obj[0x43] != s[0x2E2] && obj[0x95] != 3)
        moby_set_animation_and_speed(obj, s[0x2E2], 0, 20);
    func_PAL_002B5E30(obj, mat_fast_helper_a(((L01HeroPositionView *)g_hero_state)->position[0] - *(float *)(obj + 0x10),
                                     ((L01HeroPositionView *)g_hero_state)->position[1] - *(float *)(obj + 0x14)));
    *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
    return -1000.0f;
}
