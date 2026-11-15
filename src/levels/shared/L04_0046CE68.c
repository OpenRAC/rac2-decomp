#include "common.h"
typedef unsigned int CameraQuad __attribute__((mode(TI)));
typedef union { CameraQuad q; float f[4]; } CameraVector;
extern unsigned char D_00189E20[];
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
void func_L04_0046CE68(unsigned char *camera)
{
    CameraVector matrix[4];
    CameraVector position;
    CameraVector up;
    unsigned char *direction;
    unsigned char *state;
    FastVecScale(matrix, D_00189E20, -1.0f);
    FastVecScale(matrix + 1, D_00189E20 + 0x10, -1.0f);
    qcopy(matrix + 2, D_00189E20 + 0x20);
    qcopy(matrix + 3, D_00189E20 + 0x80);
    direction = *(unsigned char **)(camera + 0x70) + 0x70;
    transform_vector(camera + 0x30, direction, matrix);
    FastVecSub(direction, camera + 0x30, D_00189E20 + 0x80);
    *(float *)(direction + 0x10) = vec_length_xy(direction);
    state = *(unsigned char **)(camera + 0x70);
    qcopy(&position, D_00189E20 + 0x80);
    position.f[2] += *(float *)(state + 0x90);
    up.q = 0;
    up.f[2] = 1.0f;
    up.f[3] = 1.0f;
    FastVecSub(camera, &position, camera + 0x30);
    vec_scale_to_length(camera, camera, 1.0f);
    FastVecCross(camera + 0x10, camera, &up);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
