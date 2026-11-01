#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern char *func_L00_0033E220(void *, void *, unsigned int, int, int, int, int, float, float, int);
extern void func_002A7750(char *, int, int);
extern int func_002A9640(char *, int, int);
extern void func_0029F338(char *);
extern void func_PAL_L00_0032C328(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_L01_0031A278(char *, void *, float, float, float);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_L00_00328480(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
extern float D_L06_001B1CB8 __attribute__((sda));
extern float D_L06_001B1CB0 __attribute__((sda));
extern float D_L06_001B1CC0 __attribute__((sda));
extern float D_L06_001B1CE0 __attribute__((sda));
extern float D_L06_001B1CE4, D_L06_001B1CE8;

void func_PAL_L06_00468998(char *a0) {
    float pos[4], vel[4];
    char *state = *(char **)(a0 + 0x68);
    int i;
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0: {
        float scale;
        *(u128 *)pos = 0;
        pos[2] = 3.75f;
        scale = *(float *)(a0 + 0x2C) / *(float *)(*(char **)(a0 + 0x24) + 0x24);
        pos[2] *= scale;
        func_L00_0033E220(pos, a0, 0x300033FF, -1, 1, -1, 0, scale * 525000.0f, 0.75f, -1);
        func_L00_0033E220(pos, a0, 0x280033FF, -1, 0, -1, 0, scale * 525000.0f, 0.75f, -1);
        *(int *)(a0 + 0x78) = -16192;
        func_002A7750(a0, 1, -1);
        /* fall through */
    }
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) && *(int *)state == 0) func_002A7750(a0, 2, -1);
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, &D_L06_001B1CC0, &D_L06_001B1CB8, &D_L06_001B1CB0, 0xFFFF, 0, -1, 6, 0xFF, 0xFF, 0);
        func_L01_0031A278(a0, pos, D_L06_001B1CE0, D_L06_001B1CE4, D_L06_001B1CE8);
        func_PAL_L00_003FB330(pos, 0, 5, 5, 5, 20, 5, 0, 1, 1, 1, 0, 1.0f, 20.0f);
        for (i = 0; i < 4; i++) {
            vel[0] = (i / 2 * 2 - 1) * 0.060000002f;
            vel[1] = (i % 2 * 2 - 1) * 0.060000002f;
            vel[2] = 0.14000002f;
            func_00283098(vel, vel, a0 + 0xC0);
            func_PAL_L00_00328480(a0, pos, 3, 0.2f, 1, vel, 5.0f, 0x7F40FFFF, 1.45f, 2.2f, 0);
        }
        func_0029F338(a0);
        break;
    }
}
