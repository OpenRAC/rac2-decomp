/* func_L26_003D4590 reaches its small globals through $gp (-G8) and clears a stack vector with
 * por (-frac2-zero-ti-por). As in the level-2 state machine (L02_003C43F0-state-g8.c), each
 * random range reads its upper bound, absolutely, before its lower bound.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L26_001A8FF0;
extern Vector D_L26_002967A0[6];
extern Vector D_L26_001B1890 MACRO_ADDR;
extern float D_L26_001B0460 __attribute__((sda));
/* Upper bounds, snapshotted before the lower bounds are read. */
extern volatile float D_L26_001B0464 MACRO_ADDR;
extern float D_L26_001B0458 __attribute__((sda));
extern volatile float D_L26_001B045C MACRO_ADDR;
extern int D_L26_001B0468[2] __attribute__((sda));
extern int D_L26_001B0470[2] __attribute__((sda));
extern int D_L26_001B1748;
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002A7750(unsigned char *, int, int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0408(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_L26_00324DE8(unsigned char *, int);
extern int func_00282948(int *);
extern void func_L26_003D4930(unsigned char *);

/* Per-frame update for the moby of class 3072: it moves around a circle centred on a fixed point,
   turning to face along its path and switching between two animation modes now and then. It is
   hidden while the level is not active. */
void func_L26_003D4590(unsigned char *object) {
    Vector position;
    union {
        float init_matrix[12];
        struct { Vector tangent; Vector rotation; Vector rotation_seed; } motion;
    } workspace;
    float matrix[12];
    char *private;
    float radius;
    float upper;
    float angle;
    unsigned int selection;
    if (!D_L26_001A8FF0 && object[0x20]) {
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        return;
    }
    object[0x31] = 1;
    *(unsigned short *)(object + 0x34) &= 0xFFFE;
    private = *(char **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        if (D_L26_002967A0[0].f[3] == 0.0f) {
            position.q = 0;
            position.f[2] = 2.0943954f;
            euler_rotation_basis(workspace.init_matrix, &position);
            D_L26_002967A0[0].f[3] = 1.0f;
            D_L26_002967A0[1].f[3] = 1.0f;
            matrix_mul_vec3(D_L26_002967A0 + 2, D_L26_002967A0, workspace.init_matrix);
            matrix_mul_vec3(D_L26_002967A0 + 3, D_L26_002967A0 + 1, workspace.init_matrix);
            matrix_mul_vec3(D_L26_002967A0 + 4, D_L26_002967A0 + 2, workspace.init_matrix);
            matrix_mul_vec3(D_L26_002967A0 + 5, D_L26_002967A0 + 3, workspace.init_matrix);
        }
        object[0x30] = 0xFF;
        *(unsigned short *)(object + 0x32) = 0x200;
        *(unsigned short *)(object + 0x34) |= 0x110;
        FastVecSub(private + 0x50, object + 0x10, &D_L26_001B1890);
        radius = FastVecLength(private + 0x50);
        vec_scale_to_length(private + 0x60, object + 0xC0, radius);
        FastVecCross(private + 0x70, private + 0x60, private + 0x50);
        vec_scale_to_length(private + 0x70, private + 0x70, radius);
        FastVecCross(private + 0x60, private + 0x50, private + 0x70);
        vec_scale_to_length(private + 0x60, private + 0x60, radius);
        upper = D_L26_001B0464;
        *(float *)(private + 0x188) = RandomSignedFloatRange(D_L26_001B0460, upper) * 0.00029088825f;
        upper = D_L26_001B045C;
        *(float *)(private + 0x180) = RandomFloatRange(D_L26_001B0458, upper) * 0.00029088825f;
        *(float *)(private + 0x184) = RandomAngle();
        SetMobyState(object, 1, -1);
        break;
    case 1:
        *(float *)(private + 0x184) = FastAddRotations(*(float *)(private + 0x184), *(float *)(private + 0x180));
        position.f[0] = FastSinOrCosA(*(float *)(private + 0x184));
        position.f[1] = FastSinOrCosB(*(float *)(private + 0x184));
        position.f[2] = 0.0f;
        matrix_mul_vec3(object + 0x10, &position, private + 0x50);
        FastVecAdd(object + 0x10, object + 0x10, &D_L26_001B1890);
        angle = FastAddRotations(*(float *)(private + 0x184), 1.5707965f);
        workspace.motion.tangent.f[0] = FastSinOrCosA(angle);
        workspace.motion.tangent.f[1] = FastSinOrCosB(angle);
        workspace.motion.tangent.f[2] = 0.0f;
        matrix_mul_vec3(&workspace.motion.tangent, &workspace.motion.tangent, private + 0x50);
        AlignRotationToDirection(object + 0xC0, &workspace.motion.tangent, 0);
        workspace.motion.rotation_seed.q = 0;
        workspace.motion.rotation_seed.f[2] = *(float *)(private + 0x188);
        workspace.motion.rotation.q = workspace.motion.rotation_seed.q;
        euler_rotation_basis(matrix, &workspace.motion.rotation);
        multiply_matrix3x3(object + 0xC0, object + 0xC0, matrix);
        if ((D_L26_001B1748 & 0xFF) == 0) ScaleTriangleVertices(object + 0xC0, 0);
        if (FastFloatHelperD((int *)(private + 0x18C))) {
            selection = (object[0xBC] + 1) & 1;
            object[0xBC] = selection;
            *(int *)(object + 0x78) = D_L26_001B0468[object[0xBC]];
            *(int *)(private + 0x18C) = D_L26_001B0470[object[0xBC]];
        }
        AdvanceTrailSamples(object);
        break;
    }
}
