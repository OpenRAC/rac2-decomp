#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char pad[0x30];
    TI128 position;
    char tail[0x40];
} PositionRecord;

extern float func_002A89A8(void *, int, float);
extern int func_00283CF0(float);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern char *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern void func_00291450(int);
extern int func_002B3BA8(void *, int, float, float, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L04_003E22B0(unsigned char *, int, int, int, int);
extern void func_L04_00412AF8(void *, void *);
extern void func_L04_003E5250(unsigned char *);
extern void func_L04_003E5298(void *);
extern char *D_L04_001B25CC __attribute__((sda));
extern char D_L04_001B9680[];

int func_L04_003E4C00(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    char *hit;
    int result;
    float scale;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        float ground = func_002A89A8(moby + 0x10, 0, 0.5f);

        *(unsigned char **)(vars + 0x18) = vars + 0x140;
        *(float *)(moby + 0x18) = ground;
        *(int *)(vars + 0x2D0) = 0;
        *(unsigned char *)(vars + 0x48) = func_00283CF0(20.0f);
        result = func_00283CF0(11.2f);
        *(int *)(vars + 0xA8) = 3;
        *(float *)(vars + 0x90) = 0.5f;
        *(float *)(vars + 0x94) = 0.5f;
        *(float *)(vars + 0x9C) = 0.4f;
        vars[0xD7] = 1;
        *(float *)(vars + 0x148) = 0.5f;
        *(float *)(vars + 0x14C) = 0.5f;
        *(s8 *)(vars + 0xCC) = -1;
        *(s8 *)(vars + 0xCD) = -1;
        *(s8 *)(vars + 0xCE) = -1;
        *(s8 *)(vars + 0xCF) = -1;
        *(s8 *)(vars + 0xD2) = -1;
        vars[0x4A] = result;
        vars[0x70] = 22;
        vars[0x71] = 11;
        vars[0x72] = 11;
        vars[0x76] = 13;
        vars[0x77] = 14;
        *(float *)(vars + 0x7C) = 0.10000001f;
        *(float *)(vars + 0x80) = 0.06666667f;
        *(float *)(vars + 0x84) = 0.004166667f;
        *(float *)(vars + 0x88) = 0.008333334f;
        *(s8 *)(vars + 0xD3) = -1;
        *(float *)(vars + 0x8C) = 0.004166667f;
        *(float *)(vars + 0x140) = 1.0f;
        *(float *)(vars + 0x144) = 0.25f;
        *(float *)(vars + 0x150) = 1.483530f;
        *(float *)(vars + 0x170) = 0.52359885f;
        *(float *)(vars + 0x16C) = 0.00555555569008f;
        func_002B60B0(moby, 0.0022222223f, 0.06666667f, 0.00116355298087f, 0.10471977f);
        qcopy(vars + 0x110, moby + 0x10);
        scale = 1.25f;
        *(float *)(vars + 0x120) = scale;
        *(float *)(vars + 0x12C) = *(float *)(vars + 0x2C0);
        *(float *)(vars + 0x130) = 10.0f;
        result = func_002A7820(120, 700);
        vars[0x28] = 3;
        vars[0x29] = 1;
        vars[0x2E] = 1;
        *(int *)(vars + 0x2BC) = result;
        *(float *)(vars + 0x2E4) = vars[0x34];
        *(float *)(vars + 0x2E8) = vars[0x34];
        *(float *)(vars + 0x30) = 0.75f;
        func_002A7750(moby, 1, 0);
        if (*(int *)(vars + 0x2F0) != -1) {
            *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * 0.4f;
            vars[0x306] = 0;
            *(TI128 *)(vars + 0x280) = *(TI128 *)(moby + 0x10) =
                ((PositionRecord *)D_L04_001B25CC)[*(int *)(vars + 0x2F0)].position;
            func_L04_003E22B0(moby, 1, 1,
                func_002A77E0(*(unsigned char *)(*(char **)(*(char **)(moby + 0x24) + 0x4C) + 0x10)), 10);
            *(short *)(vars + 0x300) = func_002A7820(1200, 3000);
            func_002A7750(moby, 5, 0);
            *(float *)(vars + 0x140) *= 0.4f;
            vars[0x307] = 0;
            *(float *)(vars + 0x144) = *(float *)(vars + 0x140) + 0.01f;
        } else {
            func_L04_003E22B0(moby, 4, 1,
                func_002A77E0(*(unsigned char *)(*(char **)(*(char **)(moby + 0x24) + 0x58) + 0x10)), 0);
            *(float *)(moby + 0x48) = func_002A7878(0.5f, scale);
        }
    }
    if (*(unsigned char *)(moby + 0x31) && func_00282E48(moby + 0x10, D_L04_001B9680) < 24.0f) {
        func_002A93B0(moby);
        moby[0x6F] = 22;
    }
    if (vars[0x2E] == 2) {
        func_L04_003E5250(moby);
        return 1;
    }
    if (*(int *)(vars + 0x2F0) != -1) {
        hit = func_002A9640(moby, 0x10000, 1);
        if (moby[0x20] == 22 || vars[0x307]) {
            moby[0xA8] = 255;
        } else if (hit) {
            func_L04_00412AF8(moby, vars + 0x280);
            *(float *)(hit + 0x2C) = *(short *)(vars + 0x24) * 0.3f;
        }
        if (vars[0x307]) {
            vars[0x307]--;
        }
    }
    result = func_002B0ED8(moby, vars + 0x60, 0);
    if (result) {
        *(int *)(vars + 0x2D0) = 0;
        if (*(int *)(vars + 0x2E0) >= 0) {
            func_00291450(*(int *)(vars + 0x2E0));
            *(int *)(vars + 0x2E0) = -1;
        }
        if (result == 5) {
            *(int *)(vars + 0xF0) = 0;
            *(float *)(vars + 0xF4) = 0.8377582f;
        }
        if (*(char **)(vars + 0x2AC)) {
            switch (result) {
            case 2:
            case 3:
                func_002A7470(*(char **)(vars + 0x2AC), 8, 0, 3);
                break;
            case 4:
            case 5:
                func_002A7470(*(char **)(vars + 0x2AC), 9, 0, 3);
                *(int *)(*(char **)(*(char **)(vars + 0x2AC) + 0x68) + 0x27C) = 0;
                break;
            case 1:
            default:
                break;
            }
        }
        func_L04_003E5298(moby);
        if (!moby[0x95]) {
            if (*(int *)(vars + 0x2CC) != -1) {
                func_002A7750(moby, 9, 1);
                func_L04_003E22B0(moby, 4, 3, 0, 12);
            } else {
                func_002A7750(moby, 8, 1);
                *(short *)(vars + 0x2A0) = func_002A7820(580, 600);
                func_L04_003E22B0(moby, 6, 5, 0, 10);
            }
        }
    }
    if (*(int *)(vars + 0x2F0) != -1) {
        *(float *)(vars + 0x20) = *(short *)(vars + 0x24);
    }
    *(int *)(vars + 0x258) = func_002B3BA8(moby, *(int *)(vars + 0x250), *(float *)(vars + 0x298), 10.0f, 0, 0);
    *(int *)(vars + 0x25C) = func_002B3BA8(moby, *(int *)(vars + 0x254), *(float *)(vars + 0x29C), 10.0f, 0, 0);
    return 0;
}
