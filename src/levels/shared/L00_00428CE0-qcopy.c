#include "include_asm.h"
#include "common.h"

extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float func_002703B0(char *, float, float, float, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern char ref_L00_00428CE0_00[];

/* Turns the camera smoothly to look at the hero's position, then rebuilds the camera's other two direction vectors. */
void func_L00_00428CE0(char *camera) {
    char *vars = *(char **)(camera + 0x70);
    char *a30 = vars + 0x30;
    char *a40 = vars + 0x40;
    float aimPoint[4] __attribute__((aligned(16)));
    float aimDir[4] __attribute__((aligned(16)));
    float turnAxis[4] __attribute__((aligned(16)));
    float scale, aimAngle;

    qcopy(aimPoint, gHeroPosition);
    aimPoint[2] += *(float *)(a40 + 0x4C);
    FastVecSub(aimDir, aimPoint, camera + 0x30);
    vec_scale_to_length(aimDir, aimDir, 1.0f);
    aimAngle = 1.5707964f - FastAngleHelper(FastVecDot(aimDir, camera));
    if (*(int *)(gHeroPosition + 0x2214) == 0x24) {
        *(float *)a30 = *(float *)a30 + 0.017f;
        if (1.0f < *(float *)a30)
            *(float *)a30 = 1.0f;
        scale = aimAngle * *(float *)a30;
    } else {
        scale = StepSpringDamperStored(a30, 0.0f, aimAngle, 0.02f, 0.175f, 0.0f);
    }
    FastVecCross(turnAxis, aimDir, camera + 0x40);
    ApplyAxisRotationToQuaternion(camera, camera + 0x40, turnAxis, scale);
    vec_scale_to_length(camera + 0x40, camera, 1.0f);
    qcopy(camera, camera + 0x40);
    FastVecCross(camera + 0x10, camera, ref_L00_00428CE0_00);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
