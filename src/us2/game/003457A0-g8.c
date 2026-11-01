#include "include_asm.h"

extern void func_00337210(int *);
extern char D_0025E328[];
extern int D_001AE304 __attribute__((sda));
extern int D_001AE308 __attribute__((sda));
extern int D_001AE310 __attribute__((sda));
extern int D_001AE318 __attribute__((sda));
extern int D_001AE320 __attribute__((sda));
extern int D_001AE328 __attribute__((sda));
extern int D_001AE330 __attribute__((sda));

void func_US2_00345F00(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 2;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&D_001AE330;
    f[1] = D_001AE304;
    f[2] = D_001AE308;
    f[0] = (int)D_0025E328;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&D_001AE328;
    f[7] = (int)&D_001AE320;
    f[6] = (int)&D_001AE318;
    f[5] = (int)&D_001AE310;
    f[22] = 1;
    func_00337210(f);
}

extern char D_001AA810[];
extern int D_001AE398 __attribute__((sda));
extern int D_001AE39C __attribute__((sda));
extern int D_001AE3A0 __attribute__((sda));
extern int D_001AE3A8 __attribute__((sda));
extern int D_001AE3B0 __attribute__((sda));
extern int D_001AE3B8 __attribute__((sda));
extern int D_001AE3C0 __attribute__((sda));

void func_US2_003461D0(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 0;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&D_001AE3C0;
    f[1] = D_001AE398;
    f[2] = D_001AE39C;
    f[0] = (int)D_001AA810;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&D_001AE3B8;
    f[7] = (int)&D_001AE3B0;
    f[6] = (int)&D_001AE3A8;
    f[5] = (int)&D_001AE3A0;
    f[22] = 1;
    func_00337210(f);
}

extern void func_00335E38(char *p, float x, float y, float zero, float zero2);
extern float D_L04_001AE1E0 __attribute__((sda));
extern float D_L04_001AE1E8 __attribute__((sda));
extern float D_L04_001AE1F0 __attribute__((sda));
extern float D_L04_001AE1F8 __attribute__((sda));
extern float D_L04_001AE1E4;
extern float D_L04_001AE1EC;
extern float D_L04_001AE1F4;
extern float D_L04_001AE1FC;
struct pos {
    float x;
    float y;
};

INCLUDE_ASM("asm/us2/game", func_US2_003457A0);

