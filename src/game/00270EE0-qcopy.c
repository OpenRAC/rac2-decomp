#include "common.h"
extern char D_001B5200[], D_001B5490[], D_00189E20[];
extern void func_00282F20(float *, float *, float);
extern void func_00270B58(float *, float *, float *, float *, float *, float *);
extern void func_002AB600(void *, void *);
extern void func_00270D50(void);
extern void func_00270E30(void);
extern void func_00270EA8(void);
extern float func_00283CE0(int);
/* Starts a camera mode change: stores the new camera data, picks the transition setup and resets its timers. */
void func_00270EE0(char *from)
{
    unsigned char *cam = (unsigned char *)gActiveCamera + 0x290;
    float rowA[4] __attribute__((aligned(16)));
    float rowB[4] __attribute__((aligned(16)));
    float rowC[4] __attribute__((aligned(16)));
    unsigned char subMode;

    if (*(short *)cam == 1) {
        subMode = cam[3];
        if (subMode == 0) {
            qcopy(cam + 0x50, from + 0x30);
            TransformMatrixViaCopy(cam + 0x60, from);
        } else if (subMode == 2) {
            qcopy(cam + 0xC0, from + 0x30);
            TransformMatrixViaCopy(cam + 0xD0, from);
            RebuildCameraLookAtFromHero();
        } else {
            char *hero = gHeroState;

            vec_scale_to_length(rowA, (float *)(*(char **)(hero + 0x2290) + 0xC0), 1.0f);
            vec_scale_to_length(rowB, (float *)(*(char **)(hero + 0x2290) + 0xD0), 1.0f);
            vec_scale_to_length(rowC, (float *)(*(char **)(hero + 0x2290) + 0xE0), 1.0f);
            ComputeAimAngles((float *)(cam + 0x70), (float *)(from + 0x30),
                          (float *)(*(char **)(cam - 0x100) + 0x30), rowA, rowB, rowC);
            TransformMatrixViaCopy(cam + 0xB0, from);
            qcopy(cam + 0xD0, cam + 0xB0);
        }
    } else {
        subMode = cam[3];
        if (subMode == 2) {
            SaveObjectVectors();
            RebuildCameraLookAtFromHero();
        } else if (subMode == 1) {
            SaveObjectVectors();
            qcopy(cam + 0xB0, cam + 0xD0);
        } else if (subMode == 0) {
            RestoreObjectVectors();
        }
    }
    *(short *)D_001B5490 = 3;
    cam[2] = cam[3];
    if (cam[2] == 0) {
        unsigned char *fade = cam + 0x10;

        *(float *)(fade + 0x10) = *(float *)(fade + 0x14);
        *(int *)(fade + 0xC) = 0;
        qcopy(cam + 0x40, cam + 0x50);
        *(int *)(cam + 0x10) = 0;
        *(float *)(fade + 0x4) = *(float *)(fade + 0x8);
        qcopy(cam + 0x30, cam + 0x60);
    } else {
        unsigned char *blend = cam + 0x70;
        int count = ++*(int *)(blend + 0x14);

        *(int *)(blend + 0xC) = count;
        *(float *)(blend + 0x10) = 1.0f / IntToFloat(count);
    }
}
