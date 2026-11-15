#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F428000;

extern float D_L00_001B1630[];
typedef struct { u8 pad[0x80]; V4_F428000 pos; u8 pad90[0x1220 - 0x90]; char *partner; } HeroView_F428000;
typedef struct { u8 pad[0x140]; V4_F428000 pos; u8 pad150[8]; float yaw; } CamView_F428000;
extern HeroView_F428000 D_00189E20;
extern CamView_F428000 D_L00_001B8C80;

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002D7958(void *, void *, float);
extern void func_L00_00427BE8(char *, void *, float, void *);
extern float func_00283B98(float, float);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E80(void *, void *);
extern void func_00300190(void *, void *);

/* Camera follow step for a target object: aims at a point offset from the target and
   adjusts the orbit by the hero's distance; returns 0 on the easing path, else 1. */
int func_L00_00428000(char *self, char *target)
{
    V4_F428000 offset, pos;
    char *cam = *(char **)(self + 0x70);
    float *orbit = (float *)(cam + 0x64);
    char *info;
    float angle;
    float d;

    *(char **)(cam + 0xF4) = target;
    if (target != 0) {
        offset.q = 0;
        offset.f[0] = D_L00_001B1630[0];
        offset.f[2] = 0.12f;
        info = *(char **)(target + 0x68);
        matrix_mul_vec3(&offset, &offset, target + 0xC0);
        FastVecAdd(&pos, target + 0x10, &offset);
        if (*(int *)(info + 0x10) == -1) {
            CopyVec5WithFirstBlended(orbit, self + 0x50, 0.0f);
            orbit[2] = 6.0f;
            orbit[1] = orbit[3];
            orbit[3] = 0.0f;
            SetCameraTargetAndWeight(self, orbit, 0.0f, &pos);
        }
        if (*(int *)(info + 0x10) <= 0) {
            *(float *)(cam + 0xAC) = FastAddRotations(*(float *)(cam + 0xAC), *(float *)(info + 0x18));
            *(float *)(info + 0x18) *= 0.97f;
            angle = FastDiffRots(FastMatrixHelperA(D_L00_001B8C80.pos.f[0] - gHeroState.pos.f[0],
                                                D_L00_001B8C80.pos.f[1] - gHeroState.pos.f[1]),
                                  D_L00_001B8C80.yaw);
            d = vec_distance_xy(&gHeroState.pos, &D_L00_001B8C80.pos) <
                        vec_distance_xy(gHeroState.partner + 0x10, &D_L00_001B8C80.pos)
                    ? vec_distance_xy(&gHeroState.pos, &D_L00_001B8C80.pos)
                    : vec_distance_xy(gHeroState.partner + 0x10, &D_L00_001B8C80.pos);
            if (d < 0.77f) {
                if (angle < 1.5707965f) {
                    *(float *)(cam + 0x1C) -= 0.7f - d;
                    *(int *)(info + 4) = 0;
                } else {
                    *(float *)(cam + 0x1C) += 0.7f - d;
                }
            } else {
                *(float *)(cam + 0x1C) += *(float *)(info + 4);
                *(float *)(info + 4) *= 0.97f;
            }
            qcopy(cam + 0x80, &pos);
            TransformVectorOrCopy(cam + 0x80, cam + 0x80);
            return 0;
        }
        *(float *)(cam + 0xAC) = *(float *)(target + 0xF0) * 0.5f;
        *(float *)(cam + 0x20) += (*(float *)(target + 0xF4) - *(float *)(cam + 0x20)) * 0.05f;
        qcopy(cam + 0x80, &pos);
        qcopy(cam + 0xC0, target + 0xF0);
    }
    return 1;
}
