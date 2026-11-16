#include "include_asm.h"

#include "common.h"
extern float g_vendor_logo_spin_speed __attribute__((sda));
extern float FastAddRotations(float, float);
extern void build_axis_rotation_quaternion(char *, int, float);
extern void AttachManipulator(char *, int, char *);
extern float math_random_angle(void);
extern float FastAddRotations(float, float);

/* grows a moby out of the ground the first time, then spins it down */
void megacorp_vendor_logo_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned char *)(moby + 0x63) = 0x20;
        *(float *)(vars + 0x40) = math_random_angle();
        AttachManipulator(moby, 1, vars);
        break;
    case 1: {
        float spin = g_vendor_logo_spin_speed * 0.0003490659f;

        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), spin);
        *(float *)(vars + 0x40) = FastAddRotations(*(float *)(vars + 0x40), spin * -2.0f);
        build_axis_rotation_quaternion(vars + 0x10, 2, *(float *)(vars + 0x40));
        break;
    }
    }
}
