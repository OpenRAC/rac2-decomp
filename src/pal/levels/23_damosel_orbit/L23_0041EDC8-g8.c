#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L23_001B1438 __attribute__((sda));
extern int D_L23_001B1440 __attribute__((sda));
extern float D_L23_001B1448 __attribute__((sda));
extern float D_L23_001B144C __attribute__((sda));
extern float D_L23_001B1580 __attribute__((sda));
extern float D_L23_001B1584 __attribute__((sda));
extern float D_L23_001B1588 __attribute__((sda));
extern float D_L23_001B158C __attribute__((sda));
extern int D_L23_001B1648 __attribute__((sda));
extern int D_L23_001B140C __attribute__((sda));
extern int D_L23_001B36AC;
extern Quad D_L23_001B3850 MACRO_ADDR;
extern Quad D_L23_001B3870 MACRO_ADDR;
extern float D_L23_001B3728;
extern int D_L23_001B3784;
extern char D_L23_001B3860[] MACRO_ADDR;
extern char D_L23_001B36C0[] MACRO_ADDR;
extern char *g_hero_moby __attribute__((nosda));
extern void vec_clear_128(Quad *);
extern void moby_transform_joint_point(char *, int, char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern float FastVecDot(char *, char *);
extern int CollLine(void *, void *, int, void *, int);
extern void FastVecCross(char *, char *, char *);
extern float math_fast_angle_helper(float);
extern float math_fast_float_g(float);
extern float FastAddRotations(float, float);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);
extern void build_axis_rotation_quaternion(void *, int, float);
extern float fast_subtract_rotations(float, float);
extern void func_PAL_L23_00420FF8(char *, float, float);

/* Update the aiming direction and its signed turn rate. */
int func_PAL_L23_0041F0D8(char *object, char *target) {
    struct { Quad zero, matrix[4], axis, direction, cross; } local;
    char *state = *(char **)(object + 0x68);
    char *direction;
    float speed, dot, angle;
    unsigned int mode;
    vec_clear_128(&local.zero);
    ((float *)&local.zero)[3] = 1.0f;
    ((unsigned char *)state)[0x473] = 1;
    *(Quad *)(state + 0x480) = local.zero;
    moby_transform_joint_point(object, 39, (char *)local.matrix);
    qcopy(&D_L23_001B3850, &local.matrix[3]);
    qcopy(&D_L23_001B3870, &local.matrix[0]);
    if (D_L23_001B1438) return 0;
    local.axis = 0;
    ((float *)&local.axis)[2] = 1.0f;
    ((float *)&local.axis)[3] = 1.0f;
    FastVecScale(state + 0x4A0, (char *)&local.axis,
        (float)D_L23_001B1440 * D_L23_001B1448 * D_L23_001B144C);
    moby_transform_joint_to_world(object, 42, (char *)&local.axis);
    FastVecSub((char *)&local.direction, target, (char *)&local.axis);
    vec_scale_to_length((char *)&local.direction, (char *)&local.direction, 1.0f);
    D_L23_001B3728 = FastVecDot((char *)&local.direction, (char *)&D_L23_001B3870);
    D_L23_001B3784 = CollLine(D_L23_001B3860, D_L23_001B36C0, 16, g_hero_moby, 0) == 0;
    direction = (char *)&local.direction;
    speed = D_L23_001B1580 * 0.0003490659f;
    if (((unsigned char *)state)[0x404] && ((unsigned char *)state)[0x405]) {
        mode = ((unsigned char *)object)[0x20];
        if ((unsigned char)mode != 7 || D_L23_001B1648 / 2 < D_L23_001B36AC) {
            if ((unsigned char)mode == 16) speed = D_L23_001B1584 * 0.0003490659f;
            else if ((unsigned)(mode - 13) < 3) speed = D_L23_001B1588 * 0.0003490659f;
        }
        FastVecCross((char *)&local.cross, direction, (char *)&D_L23_001B3870);
        dot = FastVecDot((char *)&local.cross, object + 0xD0);
        angle = math_fast_angle_helper(dot);
        math_fast_float_g(angle + 1.5707964f);
        if (dot < 0.0f) *(float *)(state + 0x57C) = -speed;
        else *(float *)(state + 0x57C) = speed;
        *(float *)(state + 0x578) = FastAddRotations(*(float *)(state + 0x578), *(float *)(state + 0x57C));
        if (((unsigned char *)state)[0x4B1] == 0) AttachManipulator((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
        build_axis_rotation_quaternion(state + 0x4C0, 1, *(float *)(state + 0x578));
        *(float *)(state + 0x578) = fast_subtract_rotations(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
        func_PAL_L23_00420FF8(object, 1.0f, 1.0f);
        return 1;
    }
    if ((unsigned)((unsigned char)object[0x20] - 13) < 2) D_L23_001B140C = 1;
    if (!((unsigned char *)state)[0x404]) {
        *(float *)(state + 0x57C) = -(D_L23_001B158C * 0.0003490659f);
        if (*(float *)(state + 0x578) > 0.0f) {
            *(float *)(state + 0x578) += *(float *)(state + 0x57C);
            if (((unsigned char *)state)[0x4B1] == 0) AttachManipulator((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
            build_axis_rotation_quaternion(state + 0x4C0, 1, *(float *)(state + 0x578));
            *(float *)(state + 0x578) = fast_subtract_rotations(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
            func_PAL_L23_00420FF8(object, -1.0f, -1.0f);
        }
    }
    return 0;
}
