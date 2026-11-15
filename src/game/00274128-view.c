#include "common.h"
/* Adapted from RAC1 gfx_build_view_matrices (GPL-3.0). */
typedef struct { float f[0x50]; } SceneG;
extern char D_001B5570[],D_001B9100[],D_001B92C0[];
extern void multiply_matrix(void *,void *,void *);
extern void scale_vector(void *,void *,float);
extern void FastVecScale(void *,void *,float);
/* Builds the camera view matrices and the clip data from the current camera. */
void gfx_build_view_matrices(void) {
    float m[4][4];
    SceneG *viewMatrix;
    char *viewState;
    float *viewFloats;
    float offX;
    float offY;
    float offZ;

    qcopy(m[0], D_001B5570);
    qcopy(m[1], D_001B5570 + 0x10);
    qcopy(m[2], D_001B5570 + 0x20);
    viewMatrix = (SceneG *)(D_001B5570 - 0x370);
    viewState = D_001B9100;
    viewFloats = (float *)(viewState - 0xC0);
    viewMatrix->f[0] = -m[1][0];
    *(int *)&viewMatrix->f[0x30 / 4] = 0;
    viewMatrix->f[0x10 / 4] = -m[1][1];
    viewMatrix->f[0x20 / 4] = -m[1][2];
    viewMatrix->f[4 / 4] = -m[2][0];
    viewMatrix->f[0x14 / 4] = -m[2][1];
    viewMatrix->f[0x24 / 4] = -m[2][2];
    viewMatrix->f[8 / 4] = m[0][0];
    viewMatrix->f[0x18 / 4] = m[0][1];
    viewMatrix->f[0x28 / 4] = m[0][2];
    viewMatrix->f[0x3C / 4] = 1.0f;
    *(int *)&viewMatrix->f[0x34 / 4] = 0;
    *(int *)&viewMatrix->f[0x38 / 4] = 0;
    *(int *)&viewMatrix->f[0xC / 4] = 0;
    *(int *)&viewMatrix->f[0x1C / 4] = 0;
    *(int *)&viewMatrix->f[0x2C / 4] = 0;
    multiply_matrix(&viewMatrix->f[0x40 / 4], viewState, viewMatrix);
    multiply_matrix(&viewMatrix->f[0x80 / 4], viewState + 0x40, viewMatrix);
    offX = viewFloats[0x1A0 / 4];
    offY = viewFloats[0x1A4 / 4];
    offZ = viewFloats[0x1A8 / 4];
    viewMatrix->f[0x80 / 4] += viewMatrix->f[0x8C / 4] * offX;
    viewMatrix->f[0x84 / 4] += viewMatrix->f[0x8C / 4] * offY;
    viewMatrix->f[0x88 / 4] += viewMatrix->f[0x8C / 4] * offZ;
    viewMatrix->f[0x90 / 4] += viewMatrix->f[0x9C / 4] * offX;
    viewMatrix->f[0x94 / 4] += viewMatrix->f[0x9C / 4] * offY;
    viewMatrix->f[0x98 / 4] += viewMatrix->f[0x9C / 4] * offZ;
    viewMatrix->f[0xA0 / 4] += viewMatrix->f[0xAC / 4] * offX;
    viewMatrix->f[0xA4 / 4] += viewMatrix->f[0xAC / 4] * offY;
    viewMatrix->f[0xA8 / 4] += viewMatrix->f[0xAC / 4] * offZ;
    viewMatrix->f[0xB0 / 4] += viewMatrix->f[0xBC / 4] * offX;
    viewMatrix->f[0xB4 / 4] += viewMatrix->f[0xBC / 4] * offY;
    viewMatrix->f[0xB8 / 4] += viewMatrix->f[0xBC / 4] * offZ;
    multiply_matrix(&viewMatrix->f[0xC0 / 4], viewState + 0x80, viewMatrix);
    scale_vector(&viewMatrix->f[0x100 / 4], viewState + 0x80, viewFloats[0x1C0 / 4]);
    scale_vector(&viewMatrix->f[0x110 / 4], viewState + 0x90, viewFloats[0x1C0 / 4]);
    qcopy(&viewMatrix->f[0x120 / 4], viewState + 0xA0);
    qcopy(&viewMatrix->f[0x130 / 4], viewState + 0xB0);
    multiply_matrix(&viewMatrix->f[0x100 / 4], &viewMatrix->f[0x100 / 4], viewMatrix);
    qcopy(D_001B92C0, viewMatrix);
    qcopy(D_001B92C0 + 0x10, &viewMatrix->f[0x10 / 4]);
    qcopy(D_001B92C0 + 0x20, &viewMatrix->f[0x20 / 4]);
    FastVecScale(D_001B92C0 + 0x30, &viewMatrix->f[0x140 / 4], 1024.0f);
    *(float *)(D_001B92C0 + 0x3C) = 1024.0f;
}
