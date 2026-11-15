#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rotation[3], source[3], quaternion, angles; float position[4] __attribute__((aligned(16))); } BlendWorkspace;
/* Integer and FP arguments retain their order within the EE ABI register banks. */
extern float func_002AA548(float *,float,float *,float,float,float);
extern void func_002833F0(void *,void *);
extern float func_00283248(float,float);
extern float func_00282E20(void *);
extern float func_002AA150(float,float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283810(void *,void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_002AB6D8(float *,float *);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern float D_L16_001B3490[4] MACRO_ADDR;
extern float D_L16_001B34A0[4] MACRO_ADDR;
extern float D_L16_001B34B0[4] MACRO_ADDR;
extern float D_L16_001B34C0[4] MACRO_ADDR;
/* Blends the camera smoothly from its start view to the target view over time and applies the result. */
void func_L16_00395ED0(char *object)
{
    BlendWorkspace local;
    char *state=*(char **)(object+0x68);
    float startAngle,endAngle,startLength,endLength,startHeight,endHeight,angle,length;
    float *position;
    if (*(int *)(state+4)==-1) return;
    if (*(float *)(state+0x4c)<1.0f) StepValueTowardTarget((float *)(state+0x4c),1.0f,(float *)(state+0x50),0.0001850000117f,0.0001850000117f,0.01110000070f);
    euler_rotation_basis(local.source,state+0x20);
    if (*(float *)(state+0x4c)<1.0f) {
        startAngle=FastMatrixHelperA(D_L16_001B34B0[0],D_L16_001B34B0[1]);
        endAngle=FastMatrixHelperA(D_L16_001B34C0[0],D_L16_001B34C0[1]);
        startLength=vec_length_xy(D_L16_001B34B0);
        endLength=vec_length_xy(D_L16_001B34C0);
        startHeight=D_L16_001B34B0[2]; endHeight=D_L16_001B34C0[2];
        angle=MoveAngleTowardTarget(startAngle,endAngle,*(float *)(state+0x4c));
        length=(endLength-startLength)*(*(float *)(state+0x4c))+startLength;
        local.position[0]=FastSinOrCosA(angle)*length;
        local.position[1]=FastSinOrCosB(angle)*length;
        local.position[2]=0.0f;
        local.position[2]=(endHeight-startHeight)*(*(float *)(state+0x4c))+startHeight;
    } else { qcopy(local.position,D_L16_001B34C0); }
    position=local.position;
    matrix_mul_vec3(position,position,local.source);
    FastVecAdd(position,position,state+0x10);
    FastVectorNormalize3(&local.quaternion,D_L16_001B3490,D_L16_001B34A0,*(float *)(state+0x4c));
    quaternion_to_rotation_basis(&local.quaternion,local.rotation);
    GetEulerAnglesFromMatrix((float *)local.rotation,(float *)&local.angles);
    CopyVectorToSelectedObject(position);
    SetCameraStateRotation(&local.angles);
}
