#include "include_asm.h"

#include "common.h"
typedef struct YeedilEffectState {
    char pad00[0x30];
    int mode;
    int frame;
    char pad38[0x154];
    char *first;
    int unused190;
    char *second;
} YeedilEffectState;
extern YeedilEffectState g_yeedil_state_prefix;
extern int g_hero_vehicle_mode[] __attribute__((sda));
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_below(int);
extern void part_spawn_white_flash_pal(void *, void *, int, float);

/* Updates a spark-spraying effect (moby class 3882) during a Yeedil scene. At a set moment it fires a burst, then it keeps shooting sparks from a scene object while the scene runs. (PAL version) */
void spark_l20_burst_update_pal(unsigned char *object)
{
    float position[4], velocity[4];
    float speed, heading, tilt;
    YeedilEffectState *state;

    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        object[0x20] = 1;
        break;
    case 1:
        if (g_hero_vehicle_mode[0] != 2)
            break;
        state = &g_yeedil_state_prefix;
        if (state->mode != 7)
            break;
        if (state->frame == 131)
            SpawnExplosion_pal(state->second + 0x10, 1, 40, 20, 30, 40, 50, 1,
                          1, 1, 0, 0, 1.5f, 20.0f);
        if ((unsigned int)(state->frame - 143) < 124) {
            moby_transform_joint_to_world(state->first, 0, position);
            position[2] += 0.03f;
            speed = math_random_float_range(0.034f, 0.060000002f);
            heading = math_random_angle();
            tilt = math_random_float_range(0.523598849773407f, 2.6179940700531006f);
            vec_build_spherical_offset(velocity, speed, heading, tilt);
            if (math_random_int_below(2))
                part_spawn_white_flash_pal(position, velocity, 0, math_random_float_range(1470.0f, 7350.0f));
        }
        break;
    }
}


