#include "include_asm.h"

#include "common.h"
extern char g_hero_l20_extra_state[];
typedef struct { char pad[0x80]; float pos[4]; } HeroView;
extern HeroView g_hero_state;
extern float g_yeedil_camera_small_angle __attribute__((sda));
extern float g_yeedil_camera_angle __attribute__((sda));
extern float g_yeedil_camera_distance __attribute__((sda));
extern float g_yeedil_camera_height __attribute__((sda));
extern float g_yeedil_camera_aim_offset __attribute__((sda));
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
    char *base = g_hero_l20_extra_state;
    char *s1;
    float *p;
    float r, q, w, x;

    if (*(short *)(*(char **)(base + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, g_yeedil_camera_distance, 0.003f);
    follow_camera_set_height(g_yeedil_camera_height, 0.003f);
    cam_set_aim_offset_target(0, g_yeedil_camera_aim_offset, 0.005f);
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
                   g_yeedil_camera_small_angle * 6.981318e-06f,
                   g_yeedil_camera_small_angle * 6.981318e-06f,
                   g_yeedil_camera_angle * 0.0003490659f, s1 + 0x17F0, 0);
    *(float *)(s0 + 0x1C) = 1.0f;
    *(float *)(s0 + 0x14) = -*(float *)(s1 + 0x17F0);
}
