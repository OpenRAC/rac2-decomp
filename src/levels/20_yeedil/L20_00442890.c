#include "names.h"
/* func_L20_00442890: own unit (-O2 -G8). The parent state block is read into its own block
 * local (st) and p is formed from it before the hero distance call: that extra pseudo copy
 * gives sched1 the retail order (the parent load before the hero-pos loads, base still live). */
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

/* Turns the fight camera a little each frame so it keeps the enemy in view relative to the hero. */
void yeedil_boss_update_camera(char *moby)
{
    char *cursor = moby;
    char *base = D_L20_001B9E80;
    char *vars;
    float *p;
    float angleToHero, heroHeading, angleDiff, headingX;

    if (*(short *)(*(char **)(base + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, D_L20_001B2158, 0.003f);
    follow_camera_set_height(D_L20_001B215C, 0.003f);
    cam_set_aim_offset_target(0, D_L20_001B2160, 0.005f);
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
    angleToHero = mat_fast_helper_a(*(float *)(moby + 0x10) - g_hero_state.pos[0],
                      *(float *)(moby + 0x14) - g_hero_state.pos[1]);
    headingX = p[0];
    cursor += 0x1C0;
    heroHeading = mat_fast_helper_a(headingX, p[1]);
    heroHeading = FastAddRotations(heroHeading, 3.1415927f);
    angleDiff = fast_subtract_rotations(angleToHero, heroHeading);
    math_approach_target_with_direction_mode((char *)&angleDiff, 0.0f,
                   D_L20_001B2150 * 4.84813745e-06f,
                   D_L20_001B2150 * 4.84813745e-06f,
                   D_L20_001B2154 * 0.000290888245f, vars + 0x17F0, 0);
    *(float *)(cursor + 0x1C) = 1.0f;
    *(float *)(cursor + 0x14) = -*(float *)(vars + 0x17F0);
}
