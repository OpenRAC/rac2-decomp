#include "common.h"

typedef int Vector __attribute__((mode(TI)));
extern float D_L02_001B03E0[4] __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_0029EFD0(int);
extern void func_0029FCC0(char *, int, char *);
extern void func_00283098(void *, void *, void *);
extern void func_002A0F48(char *);
extern void func_002AB028(void *);
extern void func_002A10E8(char *);
extern int func_002B3868(char *);
extern int func_00282978(void *);
extern float func_00283CE0(int);
extern void func_L02_003D7900(char *);

/* Per-frame update for moby class 2581. Updates a lift-like moby that slides along its direction while its animation plays, and keeps a child moby stuck to its joint. */
void func_L02_003D7330(char *moby) {
    float startPos[4] __attribute__((aligned(16)));
    /* Separate initial and final query events use four measured local vectors. */
    float moveDelta[4] __attribute__((aligned(16)));
    float jointPos[4] __attribute__((aligned(16)));
    float rotatedOffset[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    Vector *sourceRow;
    Vector *destRow;
    int i;
    qcopy(startPos, moby + 0x10);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(vars + 0x10) = 0;
        *(int *)(vars + 0x14) = 0;
        *(int *)(vars + 0x18) = 0;
        SetMobyState(moby, 2, -1);
        if (*(unsigned char *)(moby + 0x43) != 0) StartAnimationBlended(moby, 0, 0, 0);
        *(float *)(moby + 0x48) = 0.0f;
        vec_scale_to_length(moveDelta, moby + 0xD0, 2.0f);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        qcopy(vars, moby + 0x10);
        *(char **)(vars + 0x1C) = CreateMoby(0x1172 /* moby class 4466 */);
        if (*(char **)(vars + 0x1C) == 0) return;
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 0x41;
        *(unsigned char *)(*(char **)(vars + 0x1C) + 0x30) = *(unsigned char *)(moby + 0x30);
        *(short *)(*(char **)(vars + 0x1C) + 0x32) = 0;
        TransformMobyJointToWorld(moby, 0, (char *)jointPos);
        matrix_mul_vec3(rotatedOffset, D_L02_001B03E0, moby + 0xC0);
        FastVecAdd(jointPos, rotatedOffset, jointPos);
        {
            char *child = *(char **)(vars + 0x1C);
            qcopy(child + 0x10, jointPos);
            func_002A0F48(child);
        }
        {
            Vector *row = (Vector *)(moby + 0xC0);
            Vector *out = (Vector *)(*(char **)(vars + 0x1C) + 0xC0);
            int count = 0;
            do {
                qcopy(out, row);
                count++;
                row++;
                out++;
            } while (count < 3);
        }
        NormalizeMatrixColumns(*(char **)(vars + 0x1C) + 0xC0);
        func_002A10E8(*(char **)(vars + 0x1C));
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 6;
        break;
    case 1:
        if (SetFirstPendingFlag(moby)) *(short *)(vars + 0x22) = 19;
        if (!FastDecTimer(vars + 0x22)) {
            vec_scale_to_length(moveDelta, moby + 0xD0, 2.0f / IntToFloat(19));
            FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            qcopy(moby + 0x10, vars);
            *(float *)(moby + 0x48) = 0.0f;
            SetMobyState(moby, 2, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) *(short *)(vars + 0x22) = 19;
        if (!FastDecTimer(vars + 0x22)) {
            vec_scale_to_length(moveDelta, moby + 0xD0, -2.0f / IntToFloat(19));
            FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            *(float *)(moby + 0x48) = 0.0f;
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        SetMobyState(moby, 5, -1);
        *(float *)(moby + 0x48) = 1.0f;
        if (*(unsigned char *)(moby + 0x43) != 1) StartAnimationBlended(moby, 1, 0, 0);
        ReleaseHeldActors(moby);
        break;
    case 5:
        if (*(unsigned char *)(moby + 0x60) & 2) {
            *(short *)(vars + 0x20) = 90;
            *(float *)(moby + 0x48) = 0.0f;
            SetMobyState(moby, 6, -1);
        }
        break;
    case 6:
        if (!*(short *)(vars + 0x20)) {
        *(float *)(moby + 0x48) = 1.0f;
        if (*(unsigned char *)(moby + 0x43) != 2) StartAnimationBlended(moby, 2, 0, 0);
        SetMobyState(moby, 7, -1);
        } else {
            FastDecTimer(vars + 0x20);
        }
        break;
    case 7:
        if (*(unsigned char *)(moby + 0x60) & 2) {
            if (*(unsigned char *)(moby + 0x43) != 3) StartAnimationBlended(moby, 3, 0, 0);
            SetMobyState(moby, 1, -1);
        }
        break;
    }
    if (*(char **)(vars + 0x1C) && *(float *)(moby + 0x48) != 0.0f) {
        TransformMobyJointToWorld(moby, 0, (char *)moveDelta);
        matrix_mul_vec3(jointPos, D_L02_001B03E0, moby + 0xC0);
        FastVecAdd(moveDelta, jointPos, moveDelta);
        {
            char *child = *(char **)(vars + 0x1C);
            qcopy(child + 0x10, moveDelta);
            func_002A0F48(child);
        }
        {
        char *childMatrix = *(char **)(vars + 0x1C);
        sourceRow = (Vector *)(moby + 0xC0);
        destRow = (Vector *)(childMatrix + 0xC0);
        for (i = 0; i < 3; i++) {
            *destRow = *sourceRow;
            sourceRow++;
            destRow++;
        }
        NormalizeMatrixColumns(childMatrix + 0xC0);
        }
        func_002A10E8(*(char **)(vars + 0x1C));
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 6;
    }
}
