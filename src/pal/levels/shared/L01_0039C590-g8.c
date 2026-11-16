#include "include_asm.h"

#include "common.h"
extern float g_vendor_logo_spin_speed __attribute__((sda));
extern float FastAddRotations(float, float);
extern void build_axis_rotation_quaternion(char *, int, float);
extern void AttachManipulator(char *, int, char *);
extern float math_random_angle(void);
extern float FastAddRotations(float, float);

/* grows a moby out of the ground the first time, then spins it down */
void megacorp_vendor_logo_update_pal(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned char *)(a0 + 0x63) = 0x20;
        *(float *)(s1 + 0x40) = math_random_angle();
        AttachManipulator(a0, 1, s1);
        break;
    case 1: {
        float f = g_vendor_logo_spin_speed * 0.0003490659f;

        *(float *)(a0 + 0xF8) = FastAddRotations(*(float *)(a0 + 0xF8), f);
        *(float *)(s1 + 0x40) = FastAddRotations(*(float *)(s1 + 0x40), f * -2.0f);
        build_axis_rotation_quaternion(s1 + 0x10, 2, *(float *)(s1 + 0x40));
        break;
    }
    }
}
