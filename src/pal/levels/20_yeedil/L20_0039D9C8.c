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
extern YeedilEffectState D_L20_001BDCC0;
extern int D_L20_001A8F00[] __attribute__((sda));
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_below(int);
extern void func_PAL_002BEF58(void *, void *, int, float);

void func_PAL_L20_0039D9C8(unsigned char *object)
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
        if (D_L20_001A8F00[0] != 2)
            break;
        state = &D_L20_001BDCC0;
        if (state->mode != 7)
            break;
        if (state->frame == 131)
            func_PAL_L00_003FB330(state->second + 0x10, 1, 40, 20, 30, 40, 50, 1,
                          1, 1, 0, 0, 1.5f, 20.0f);
        if ((unsigned int)(state->frame - 143) < 124) {
            moby_transform_joint_to_world(state->first, 0, position);
            position[2] += 0.03f;
            speed = math_random_float_range(0.034f, 0.060000002f);
            heading = math_random_angle();
            tilt = math_random_float_range(0.523598849773407f, 2.6179940700531006f);
            vec_build_spherical_offset(velocity, speed, heading, tilt);
            if (math_random_int_below(2))
                func_PAL_002BEF58(position, velocity, 0, math_random_float_range(1470.0f, 7350.0f));
        }
        break;
    }
}


