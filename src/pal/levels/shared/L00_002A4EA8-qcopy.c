#include "names.h"
/* func_PAL_L00_002A4EA8, the PAL copy of func_L00_002A5048 in its own unit (flags in config/cflags.txt): the same C, where the speed and acceleration arguments of func_002AA898 are scaled by 1.44f (1.2f squared, 60/50 Hz). */
#include "include_asm.h"

typedef unsigned char u8;
typedef int Quad __attribute__((mode(TI)));
extern u8 g_screen_mode_flag;
extern void *attachment_get_owner_by_kind(int);
extern float math_fabs(float);
extern float math_approach_with_velocity(float *, float, float *, float, float, float, int);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern void AttachManipulator(u8 *, unsigned int, u8 *);
extern void moby_detach_manipulator(char *, char *);
extern void mat_build_rotation_from_angles(void *, float *);
extern void vec_clear_128(Quad *);

/* Update an active attachment's orientation/position and link or retire its record. */
void func_PAL_L00_002A4EA8(u8 *node)
{
    u8 *owner = attachment_get_owner_by_kind(*(short *)(node + 0xA2));
    float *angles;
    Quad *position;

    if (owner == 0)
        return;
    if (g_screen_mode_flag == 0) {
        int kind = *(short *)(node + 0xA2);
        if (kind == 4 || kind == 2 || kind == 5 || kind == 3)
            return;
    } else if (*(short *)(node + 0xA2) == 0) {
        return;
    }
    if (*(float *)(node + 0x60) == 0.0f &&
        *(float *)(node + 0x64) == 0.0f &&
        *(float *)(node + 0x68) == 0.0f &&
        *(float *)(node + 0x90) == 0.0f &&
        *(float *)(node + 0x94) == 0.0f &&
        *(float *)(node + 0x98) == 0.0f &&
        math_fabs(*(float *)(node + 0x70)) < 0.003f &&
        math_fabs(*(float *)(node + 0x74)) < 0.003f &&
        math_fabs(*(float *)(node + 0x78)) < 0.003f &&
        *(float *)(node + 0xAC) == 1.0f &&
        math_fabs(*(float *)(node + 0x40)) < 0.005f &&
        math_fabs(*(float *)(node + 0x44)) < 0.005f &&
        math_fabs(*(float *)(node + 0x48)) < 0.005f) {
        if (node[1] != 0)
            moby_detach_manipulator((char *)owner, (char *)node);
    } else {
        angles = (float *)(node + 0x40);
        position = (Quad *)(node + 0x70);
        math_approach_with_velocity(angles, *(float *)(node + 0x60), (float *)(node + 0x50),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        math_approach_with_velocity((float *)(node + 0x44), *(float *)(node + 0x64), (float *)(node + 0x54),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        math_approach_with_velocity((float *)(node + 0x48), *(float *)(node + 0x68), (float *)(node + 0x58),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        math_spring_float_to_goal((float *)position, (float *)(node + 0x80),
                     *(float *)(node + 0x90), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        math_spring_float_to_goal((float *)(node + 0x74), (float *)(node + 0x84),
                     *(float *)(node + 0x94), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        math_spring_float_to_goal((float *)(node + 0x78), (float *)(node + 0x88),
                     *(float *)(node + 0x98), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        if (node[1] == 0)
            AttachManipulator(owner, *(short *)(node + 0xA0), node);
        mat_build_rotation_from_angles(node + 0x10, angles);
        *(Quad *)(node + 0x30) = *position;
        *(float *)(node + 0x20) = *(float *)(node + 0xAC);
        *(float *)(node + 0x24) = *(float *)(node + 0xAC);
        *(float *)(node + 0x28) = *(float *)(node + 0xAC);
    }
    vec_clear_128((Quad *)(node + 0x90));
    vec_clear_128((Quad *)(node + 0x60));
    *(float *)(node + 0xAC) = 1.0f;
}
