#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00283CE0(int);

extern void func_L01_002F14E8(int, int, float);

extern void func_L20_00442890(char *);

extern void func_L20_004429F0(char *);

extern void func_002AEC48(void *, void *, int, float, float);

extern int func_00282948(void *);

extern void *func_L20_00442F80(char *);

extern void func_00283098(void *, const void *, const void *);

extern void func_002833F0(char *, char *);

extern void func_00282CF0(void *, void *, void *);

extern void func_002A93B0(void *);

extern void func_002B0990(void *, float *, float, int, int);


extern float D_L20_001B20B0[] SDATA(D_L20_001B20B0);


extern float D_L20_001B2164 __attribute__((sda));

/* Does the upkeep shared by every state of the big enemy. It updates the health display, camera and spawning, applies its tilt, ages it and moves it. */
void func_L20_004435A0(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *linkedMoby;
    char *dst;
    char *src;
    TI128 before, after, delta;
    float tilt;
    unsigned short frames;

    if (*(unsigned char *)(moby + 0x95) != 6) {
        StartHudOverlay(0xA, 0,
                         *(float *)(vars + 0x20)
                         / IntToFloat(*(short *)(vars + 0x24)));
        UpdateFightCamera(moby);
        SpawnMinionsAtArenaEdge(moby);
    }
    UpdateEasedNode(moby, vars + 0x250, 0, 0.015f, 0.3f);
    if (*(int *)(vars + 0x1810) > 0) {
        if (FastFloatHelperD(vars + 0x1810) != 0) {
            SpawnMinionAtArenaPoint(moby);
            *(int *)(vars + 0x1810) = -1;
        }
    }
    linkedMoby = *(char **)(vars + 0x1850);
    if (linkedMoby != 0) {
        if (*(short *)(linkedMoby + 0xAA) != 0x1316) {
            *(int *)(vars + 0x1850) = 0;
        } else {
            if (*(unsigned char *)(linkedMoby + 0x20) != 0xFE) {
                if (*(unsigned char *)(linkedMoby + 0x20) != 0xFD) {
                    goto copy;
                }
            }
            *(int *)(vars + 0x1850) = 0;
        }
    }
copy:
    dst = vars + 0x17E0;
    src = moby + 0x10;
    qcopy(dst, src);
    tilt = *(float *)(vars + 0x1800);
    if (tilt == 0.0f && *(float *)(vars + 0x1804) == 0.0f) {
        goto done;
    }
    *(float *)(moby + 0xF0) = tilt;
    *(float *)(moby + 0xF4) = *(float *)(vars + 0x1804);
    matrix_mul_vec3(&before, D_L20_001B20B0, moby + 0xC0);
    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    matrix_mul_vec3(&after, D_L20_001B20B0, moby + 0xC0);
    FastVecSub(&delta, &after, &before);
    FastVecSub(src, src, &delta);
done:
    UpdateMobyGroundCheck(moby);
    frames = *(unsigned short *)(moby + 0x96);
    moby[0xBD] = 2;
    if (frames <= 0xFFFE) {
        *(unsigned short *)(moby + 0x96) = frames + 1;
    }
    SetValueAndStartSmoothChange(moby, (float *)(vars + 0x250), D_L20_001B2164, 0, 1);
}
