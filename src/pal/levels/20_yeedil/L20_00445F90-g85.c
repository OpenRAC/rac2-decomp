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

/* Turns the fight camera a little each frame so it keeps the enemy in view relative to the hero. (PAL) */
void yeedil_boss_update_camera_pal(char *moby)
{
    char *work = moby;
    char *hero_extra = g_hero_l20_extra_state;
    char *vars;
    float *dir_vec;
    float hero_angle, dir_angle, angle_diff, dir_x;

    if (*(short *)(*(char **)(hero_extra + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, g_yeedil_camera_distance, 0.003f);
    follow_camera_set_height(g_yeedil_camera_height, 0.003f);
    cam_set_aim_offset_target(0, g_yeedil_camera_aim_offset, 0.005f);
    if (*(unsigned char *)(work + 0x95) == 4 ||
        *(unsigned char *)(work + 0x95) == 2) {
        return;
    }
    vars = *(char **)(work + 0x68);
    {
        char *cam_vars = *(char **)(*(char **)(hero_extra + 0x190) + 0x70);
        work = cam_vars;
        dir_vec = (float *)(cam_vars + 0x160);
    }
    hero_angle = mat_fast_helper_a(*(float *)(moby + 0x10) - g_hero_state.pos[0],
                      *(float *)(moby + 0x14) - g_hero_state.pos[1]);
    dir_x = dir_vec[0];
    work += 0x1C0;
    dir_angle = mat_fast_helper_a(dir_x, dir_vec[1]);
    dir_angle = FastAddRotations(dir_angle, 3.1415927f);
    angle_diff = fast_subtract_rotations(hero_angle, dir_angle);
    math_approach_target_with_direction_mode((char *)&angle_diff, 0.0f,
                   g_yeedil_camera_small_angle * 6.981318e-06f,
                   g_yeedil_camera_small_angle * 6.981318e-06f,
                   g_yeedil_camera_angle * 0.0003490659f, vars + 0x17F0, 0);
    *(float *)(work + 0x1C) = 1.0f;
    *(float *)(work + 0x14) = -*(float *)(vars + 0x17F0);
}
