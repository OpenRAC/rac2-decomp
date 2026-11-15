#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 angles, matrix[3], position, target; } CameraFollowWorkspace;
extern float func_00283B98(float,float);
extern void func_002833F0(void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern Vector128 D_L16_001B1AA0 __attribute__((sda));
extern Vector128 D_L16_001B1AB0 __attribute__((sda));
extern float D_L16_001B1AC0 __attribute__((sda));
extern float D_L16_001B1AC4 __attribute__((sda));
/* Moves the camera to sit behind the turret, following the way the turret faces. */
void func_L16_00416EC8(char *object)
{
    CameraFollowWorkspace local;
    char *state=*(char **)(object+0x68);
    float height;
    *(Vector128 *)&local.angles=*(Vector128 *)(object+0xf0);
    ((float *)&local.angles)[1]=FastAddRotations(((float *)&local.angles)[1],D_L16_001B1AC0);
    ((float *)&local.angles)[1]=FastAddRotations(((float *)&local.angles)[1],*(float *)(state+0x90));
    euler_rotation_basis(local.matrix,&local.angles);
    matrix_mul_vec3(&local.position,&D_L16_001B1AA0,local.matrix);
    matrix_mul_vec3(&local.target,&D_L16_001B1AB0,object+0xc0);
    FastVecAdd(&local.target,&local.target,object+0x10);
    FastVecAdd(&local.position,&local.position,&local.target);
    height=*(float *)(object+0x18)+D_L16_001B1AC4;
    if (((float *)&local.position)[2]<height) ((float *)&local.position)[2]=height;
    CopyVectorToSelectedObject(&local.position);
    SetCameraStateRotation(&local.angles);
}
