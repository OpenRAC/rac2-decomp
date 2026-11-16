#include "include_asm.h"
#include "names.h"

extern float g_tether_glow_angle_degrees __attribute__((sda));
extern void AttachManipulator(int, int, char *);
extern void build_axis_rotation_quaternion(char *, int, float);
extern float fast_subtract_rotations(float, float);

/* Attaches the glow manipulator on the first frame and spins it a little each frame. (PAL) */
void tether_update_glow_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(unsigned char *)(vars + 0x371) == 0)
        AttachManipulator(*(int *)(vars + 0x2A0), 2, vars + 0x370);
    build_axis_rotation_quaternion(vars + 0x380, 2, *(float *)(vars + 0x3B0));
    *(float *)(vars + 0x3B0) = fast_subtract_rotations(*(float *)(vars + 0x3B0),
                                            g_tether_glow_angle_degrees * 0.0003490659f);
}
