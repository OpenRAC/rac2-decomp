#include "include_asm.h"

extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern int func_002B0CE0(int, int, int);
extern long D_00138320 __attribute__((nosda));
extern char D_00189EA0[];
extern int func_002B3868(void *);
extern char *func_L30_00413490(void *);
extern void func_L30_00413528(void *, void *, char *, int, int, int);
extern unsigned int D_L30_001B1F28;
extern float D_L30_001B1F04;
extern int func_PAL_002AF6C0(void *, float);
extern void func_0029FC20(void *, int, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_L30_0041C218(void *, void *, void *, int, float);
extern void func_0029F338(void *);
extern char D_L30_001B1C38[];
extern char D_L30_001B1C48[];
extern char D_L30_001B1C58[];
extern char D_L30_001B1C68[];
extern char D_L30_001B1C78[];
extern char D_L30_001B1C88[];
extern char D_L30_001B1C98[];
extern char D_L30_001B1CA8[];
extern char D_L30_001B1CB8[];
extern char D_L30_001B1CC8[];
extern char D_L30_001B1CD8[];
extern char D_L30_001B1CE8[];
extern char D_L30_001B1CF0[];
extern char D_L30_001B1D00[];
extern char D_L30_001B1D10[];
extern char D_L30_001B1D20[];
extern char D_L30_001B1D30[];
extern char D_L30_001B1D40[];
extern char D_L30_001B1D50[];
extern char D_L30_001B1D60[];
extern char D_L30_001B1D70[];
extern char D_L30_001B1D80[];
extern char D_L30_001B1D90[];
extern char D_L30_001B1DA0[];
extern char D_L30_001B1DB0[];
extern char D_L30_001B1DC0[];
extern char D_L30_001B1DD0[];
extern char D_L30_001B1DE0[];
extern char D_L30_001B1DF0[];
extern char D_L30_001B1E00[];
extern char D_L30_001B1E10[];
extern char D_L30_001B1E18[];
extern char D_L30_001B1E20[];
extern int D_L30_001B1F10[] __attribute__((sda));
extern int D_L30_001B1F14[] __attribute__((sda));
extern int D_L30_001B1F18[] __attribute__((sda));
extern int D_L30_001B1F1C[] __attribute__((sda));
extern int D_L30_001B1F20[] __attribute__((sda));
extern int D_L30_001B1F24[] __attribute__((sda));
extern int D_L30_001B1F2C[] __attribute__((sda));
extern int D_L30_001B1F30[] __attribute__((sda));
extern int D_L30_001B1F34[] __attribute__((sda));
extern int D_L30_001B1F38[] __attribute__((sda));
extern int D_L30_001B1F3C[] __attribute__((sda));
extern int D_L30_001B1F40[] __attribute__((sda));
extern int D_L30_001B1F44[] __attribute__((sda));
extern int D_L30_001B1F48[] __attribute__((sda));
extern int D_L30_001B1F54[] __attribute__((sda));
extern int D_L30_001B1F58[] __attribute__((sda));
extern int D_L30_001B1F5C[] __attribute__((sda));
extern int D_L30_001B1F64[] __attribute__((sda));
extern int D_L30_001B1F68[] __attribute__((sda));
extern int D_L30_001B1F6C[] __attribute__((sda));
extern int D_L30_001B1F74[] __attribute__((sda));
extern int D_L30_001B1F78[] __attribute__((sda));
extern int D_L30_001B1F7C[] __attribute__((sda));
extern int D_L30_001B1F84[] __attribute__((sda));
extern int D_L30_001B1F88[] __attribute__((sda));
extern int D_L30_001B1F8C[] __attribute__((sda));
extern int D_L30_001B1F94[] __attribute__((sda));
extern int D_L30_001B1F98[] __attribute__((sda));
extern int D_L30_001B1F9C[] __attribute__((sda));

void func_PAL_L30_00419C60(char *obj) {
    float matrix[16];
    float velocity[4];
    char *st = *(char **)(obj+0x68);
    unsigned int color;
    switch ((unsigned char)obj[0x20]) {
    case 0:
        color = D_L30_001B1F28;
        *(int *)(st+0x10) = color & 0xff;
        *(int *)(st+0x14) = (int)(color & 0xff00) >> 8;
        *(int *)(st+0x18) = (color >> 16) & 0xff;
        *(int *)(st+0x1c) = (unsigned int)color >> 24;
        D_L30_001B1F04 = 5.0f;
        func_002A7750(obj,1,-1);
        break;
    case 1:
        if (*(int *)(st+4) != -1 && func_002ACBC8(D_00189EA0,*(int *)(st+4))) {
            func_002B0CE0(1,0x1338,1);
            { long buttons = D_00138320;
              if ((buttons & 3) == 3) func_002A7750(obj,2,-1); }
        }
        if (*(int *)(st+8) != -1 && func_002ACBC8(D_00189EA0,*(int *)(st+8))) {
            func_002B0CE0(1,0x1343,1);
            { long buttons = D_00138320;
              if ((buttons & 3) == 3) func_002A7750(obj,3,-1); }
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(char **)(st+0xc) = func_L30_00413490(obj);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F10, D_L30_001B1C38, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F14, D_L30_001B1C48, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F18, D_L30_001B1C58, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F1C, D_L30_001B1C68, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F24, D_L30_001B1C78, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F38, D_L30_001B1C88, 1, -1000, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F3C, D_L30_001B1C98, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F40, D_L30_001B1CA8, 1, 0, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F20, D_L30_001B1CB8, 0, 0, 60);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F44, D_L30_001B1CC8, 0, 0, 60);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F48, D_L30_001B1CD8, 0, 0, 60);
        }
        func_002B0CE0(1,0,1);
        if (!*(char **)(st+0xc) || *(short *)(*(char **)(st+0xc)+0xaa) != 0x118a || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfd)
            func_002A7750(obj,1,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            *(char **)(st+0xc) = func_L30_00413490(obj);
            func_L30_00413528(*(char **)(st+0xc), st+0x10, D_L30_001B1CE8, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), st+0x14, D_L30_001B1CF0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), st+0x18, D_L30_001B1D00, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), st+0x1c, D_L30_001B1D10, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F30, D_L30_001B1D20, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F2C, D_L30_001B1D30, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F34, D_L30_001B1D40, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F54, D_L30_001B1D50, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F64, D_L30_001B1D60, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F58, D_L30_001B1D70, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F68, D_L30_001B1D80, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F5C, D_L30_001B1D90, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F6C, D_L30_001B1DA0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F74, D_L30_001B1DB0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F84, D_L30_001B1DC0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F78, D_L30_001B1DD0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F88, D_L30_001B1DE0, 0, -1000, 1000);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F7C, D_L30_001B1DF0, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F8C, D_L30_001B1E00, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F94, D_L30_001B1E10, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F98, D_L30_001B1E18, 0, 0, 255);
            func_L30_00413528(*(char **)(st+0xc), D_L30_001B1F9C, D_L30_001B1E20, 0, 0, 255);
        }
        func_002B0CE0(1,0,1);
        if (!*(char **)(st+0xc) || *(short *)(*(char **)(st+0xc)+0xaa) != 0x118a || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(st+0xc))[0x20] == 0xfd)
            func_002A7750(obj,1,-1);
        break;
    }
    {
        unsigned int packed;
        packed = *(int *)(st+0x1c) << 24;
        packed |= *(int *)(st+0x18) << 16;
        packed |= *(int *)(st+0x14) << 8;
        packed |= *(int *)(st+0x1c);
        D_L30_001B1F28 = packed;
    }
    if (func_PAL_002AF6C0(obj,1.0f)) {
        func_0029FC20(obj,0,matrix);
        velocity[0] = func_00283180(*(float *)(obj+0xf8));
        velocity[1] = func_00283198(*(float *)(obj+0xf8));
        velocity[2] = 0;
        func_00282F20(velocity,velocity,0.70000005f);
        if (*(int *)st) {
            func_PAL_L30_0041C218(obj,velocity,matrix+12,1,0.0f);
            func_0029F338(obj);
        } else func_PAL_L30_0041C218(obj,velocity,matrix+12,0,0.0f);
    }
}
