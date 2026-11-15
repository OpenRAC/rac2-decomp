#include "include_asm.h"
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rotation[3], inverse[4], axes[3], point, angles; } AimWorkspace;
extern char *D_L16_001B2B1C[] __attribute__((sda));
extern char D_L16_001B9B00[];
extern Vector128 D_L16_001B3490[] __attribute__((sda));
extern Vector128 D_L16_001B34A0[] __attribute__((sda));
extern Vector128 D_L16_001B34B0[] __attribute__((sda));
extern Vector128 D_L16_001B34C0[] __attribute__((sda));
extern Vector128 D_L16_001AF440 __attribute__((sda));
extern void func_00335438(void *,void *,int,int,int);
extern void func_002833F0(void *,void *);
extern void func_00283698(void *,void *);
extern void func_002A91F0(void *,float *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_002AB6D8(float *,float *);
void func_L16_00395D30(char *object)
{
    AimWorkspace local;
    char *state=*(char **)(object+0x68);
    char *camera;
    char *cameraPosition;
    char *target;
    if (*(int *)(state+4)==-1) return;
    camera=D_L16_001B9B00;
    cameraPosition=camera+0x10;
    target=D_L16_001B2B1C[0]+*(int *)(state+4)*0x100;
    SetCamera5Pose(camera,cameraPosition,1,0,0);
    *(int *)(state+0x4c)=0; *(int *)(state+0x50)=0;
    euler_rotation_basis(local.rotation,state+0x20);
    matrix_from_basis_rows(local.inverse,local.rotation);
    func_002A91F0(D_L16_001B3490,(float *)cameraPosition);
    FastVecSub(D_L16_001B34B0,camera,state+0x10);
    matrix_mul_vec3(D_L16_001B34B0,D_L16_001B34B0,local.inverse);
    vec_scale_to_length(&local.point,target+0xe0,3.0f);
    FastVecAdd(&local.point,&local.point,target+0x10);
    FastVecSub(&local.axes[0],&local.point,object+0x10);
    vec_scale_to_length(&local.axes[0],&local.axes[0],1.0f);
    qcopy(&local.axes[2],&local.rotation[2]);
    FastVecCross(&local.axes[1],&local.axes[0],&local.axes[2]);
    matrix_mul_vec3(D_L16_001B34C0,&D_L16_001AF440,local.axes);
    matrix_mul_vec3(D_L16_001B34C0,D_L16_001B34C0,local.inverse);
    func_002AB6D8((float *)local.axes,(float *)&local.angles);
    func_002A91F0(D_L16_001B34A0,(float *)&local.angles);
}
