#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern int D_L02_001AEC78 __attribute__((sda));
extern float D_L02_001B2020 __attribute__((sda));
extern float D_L02_001B2020_1[8] __attribute__((sda));
extern float D_L02_001B2040 __attribute__((sda));
extern float D_L02_001B2040_1[4] __attribute__((sda));
extern void func_0029F648(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_PAL_L00_003281C0(void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, float, float, int);
extern void func_PAL_L00_00328480(char *, char *, float, int, int, char *, float, int, int, float, float);
extern void func_PAL_L02_004288E8(u8 *, float, float);

void func_PAL_L02_004285CC(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    float v[4];
    float w[4];
    int p20, p24, p28, p2c;
    int i;
    float r1, r2;

    switch (a0[0x20]) {
    case 0:
        func_0029F648(a0, &p20, &p24);
        *(u16 *)(a0 + 0x7C) = p20;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) | 0x1000;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0) {
            D_L02_001AEC78 = D_L02_001AEC78 - 1;
            func_002A7750(a0, 2, -1);
        }
        break;
    case 2:
        *(u16 *)(a0 + 0x7C) = 0;
        *(int *)state = 0x64;
        *(int *)(a0 + 0x98) = 0;
        func_PAL_L00_003281C0(a0, 1, 1.0f);
        func_0029F648(a0, &p28, &p2c);
        func_002E5CF8(0, 0, a0);
        for (i = 0; i < 16; i++) {
            if ((p28 >> i) & 1) {
                r1 = func_002A7878(D_L02_001B2040, D_L02_001B2040_1[1]);
                r2 = func_002A7878(D_L02_001B2040_1[2], D_L02_001B2040_1[3]);
                v[0] = func_002A7878(D_L02_001B2020, D_L02_001B2020_1[4]) * 0.020000001f;
                v[1] = func_002A78D8(D_L02_001B2020_1[1], D_L02_001B2020_1[5]) * 0.020000001f;
                v[2] = func_002A7878(D_L02_001B2020_1[2], D_L02_001B2020_1[6]) * 0.020000001f;
                func_00283098(v, v, a0 + 0xC0);
                func_PAL_002735D0((char *)a0, 2, 0xD0D, i, (char *)(a0 + 0x10), (char *)(a0 + 0xF0), v, r2, r1, 0xFF);
            }
        }
        *(TI128 *)v = 0;
        v[0] = -0.8f;
        v[2] = 1.5f;
        func_00283098(v, v, a0 + 0xC0);
        func_00282CC0(v, v, a0 + 0x10);
        func_00282F20(w, a0 + 0xC0, -0.10000001f);
        func_PAL_L00_00328480((char *)a0, (char *)v, 0.25f, 4, 1, (char *)w, 5.0f, 0x50404040, 0, 0.5f, 1.0f);
        func_PAL_L02_004288E8(a0, -0.10000001f, -0.3f);
        func_002A7750(a0, 3, -1);
        break;
    }
    a0[0xA8] = 0xFF;
}
