#include "include_asm.h"
#include "names.h"

extern float g_tether_glow_angle_degrees __attribute__((sda));
extern void AttachManipulator(int, int, char *);
extern void build_axis_rotation_quaternion(char *, int, float);
extern float fast_subtract_rotations(float, float);

void tether_update_glow_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(state + 0x371) == 0)
        AttachManipulator(*(int *)(state + 0x2A0), 2, state + 0x370);
    build_axis_rotation_quaternion(state + 0x380, 2, *(float *)(state + 0x3B0));
    *(float *)(state + 0x3B0) = fast_subtract_rotations(*(float *)(state + 0x3B0),
                                            g_tether_glow_angle_degrees * 0.0003490659f);
}
