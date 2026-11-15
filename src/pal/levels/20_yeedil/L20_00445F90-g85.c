#include "include_asm.h"

#include "common.h"
extern char D_L20_001B9E80[];
typedef struct { char pad[0x80]; float pos[4]; } HeroView;
extern HeroView g_hero_state;
extern float D_L20_001B2150 __attribute__((sda));
extern float D_L20_001B2154 __attribute__((sda));
extern float D_L20_001B2158 __attribute__((sda));
extern float D_L20_001B215C __attribute__((sda));
extern float D_L20_001B2160 __attribute__((sda));
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern void cam_set_aim_offset_target(int, float, float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);

void func_PAL_L20_004482C8(char *arg0)
{
    char *s0 = arg0;
    char *base = D_L20_001B9E80;
    char *s1;
    float *p;
    float r, q, w, x;

    if (*(short *)(*(char **)(base + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, D_L20_001B2158, 0.003f);
    follow_camera_set_height(D_L20_001B215C, 0.003f);
    cam_set_aim_offset_target(0, D_L20_001B2160, 0.005f);
    if (*(unsigned char *)(s0 + 0x95) == 4 ||
        *(unsigned char *)(s0 + 0x95) == 2) {
        return;
    }
    s1 = *(char **)(s0 + 0x68);
    {
        char *st = *(char **)(*(char **)(base + 0x190) + 0x70);
        s0 = st;
        p = (float *)(st + 0x160);
    }
    r = mat_fast_helper_a(*(float *)(arg0 + 0x10) - g_hero_state.pos[0],
                      *(float *)(arg0 + 0x14) - g_hero_state.pos[1]);
    x = p[0];
    s0 += 0x1C0;
    q = mat_fast_helper_a(x, p[1]);
    q = FastAddRotations(q, 3.1415927f);
    w = fast_subtract_rotations(r, q);
    math_approach_target_with_direction_mode((char *)&w, 0.0f,
                   D_L20_001B2150 * 6.981318e-06f,
                   D_L20_001B2150 * 6.981318e-06f,
                   D_L20_001B2154 * 0.0003490659f, s1 + 0x17F0, 0);
    *(float *)(s0 + 0x1C) = 1.0f;
    *(float *)(s0 + 0x14) = -*(float *)(s1 + 0x17F0);
}
