#include "names.h"
/* func_L20_00442890: own unit (-O2 -G8). The parent state block is read into its own block
 * local (st) and p is formed from it before the hero distance call: that extra pseudo copy
 * gives sched1 the retail order (the parent load before the hero-pos loads, base still live). */
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

/* Turns the fight camera a little each frame so it keeps the enemy in view relative to the hero. */
void yeedil_boss_update_camera(char *moby)
{
    char *cursor = moby;
    char *base = g_hero_l20_extra_state;
    char *vars;
    float *p;
    float angle_to_hero, hero_heading, angle_diff, heading_x;

    if (*(short *)(*(char **)(base + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, g_yeedil_camera_distance, 0.003f);
    follow_camera_set_height(g_yeedil_camera_height, 0.003f);
    cam_set_aim_offset_target(0, g_yeedil_camera_aim_offset, 0.005f);
    if (*(unsigned char *)(cursor + 0x95) == 4 ||
        *(unsigned char *)(cursor + 0x95) == 2) {
        return;
    }
    vars = *(char **)(cursor + 0x68);
    {
        char *st = *(char **)(*(char **)(base + 0x190) + 0x70);
        cursor = st;
        p = (float *)(st + 0x160);
    }
    angle_to_hero = mat_fast_helper_a(*(float *)(moby + 0x10) - g_hero_state.pos[0],
                      *(float *)(moby + 0x14) - g_hero_state.pos[1]);
    heading_x = p[0];
    cursor += 0x1C0;
    hero_heading = mat_fast_helper_a(heading_x, p[1]);
    hero_heading = FastAddRotations(hero_heading, 3.1415927f);
    angle_diff = fast_subtract_rotations(angle_to_hero, hero_heading);
    math_approach_target_with_direction_mode((char *)&angle_diff, 0.0f,
                   g_yeedil_camera_small_angle * 4.84813745e-06f,
                   g_yeedil_camera_small_angle * 4.84813745e-06f,
                   g_yeedil_camera_angle * 0.000290888245f, vars + 0x17F0, 0);
    *(float *)(cursor + 0x1C) = 1.0f;
    *(float *)(cursor + 0x14) = -*(float *)(vars + 0x17F0);
}
