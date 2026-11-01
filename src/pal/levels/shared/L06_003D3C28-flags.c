#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 D_001A7BC8[] __attribute__((sda));
extern u8 D_001A7BE0 __attribute__((sda));
extern char D_00189EA0[];
extern int D_L06_001B2348 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern void func_002AD7B8(int);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L06_003E1040(void);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282C48(float);
extern u8 D_00189E20[];

void func_PAL_L06_003E4348(u8 *moby)
{
    char *st = *(char **)(moby + 0x68);
    float scale, inverse;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!D_001A7BC8[*(int *)st]) func_002A7750(moby, 1, -1);
        else func_0029F338(moby);
        break;
    case 1:
        if (func_00282E80(moby + 0x10, D_00189EA0) < 2.0f &&
            func_00282C48(*(float *)(moby + 0x18) - *(float *)(D_00189EA0 + 8)) < 2.0f) {
            func_002AD7B8(*(int *)st);
            func_002A7750(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 150;
        }
        if (*(int *)st == 24 && D_001A7BE0) {
            func_002AD7B8(24);
            func_002A7750(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 150;
        }
        break;
    case 2:
        if ((*(u16 *)(moby + 0x34) ^ 1) & 1) {
            scale = func_00282DF0(moby + 0xC0);
            func_002AA2E8(&scale, 0, 0.080000006f);
            inverse = 2.0f - scale;
            func_00282F20(moby + 0xC0, moby + 0xC0, scale);
            func_00282F20(moby + 0xD0, moby + 0xD0, scale);
            func_00282F20(moby + 0xE0, moby + 0xE0, inverse);
            if (scale <= 0) {
                moby[0x31] = 0;
                *(u16 *)(moby + 0x34) |= 1;
            }
        }
        func_L00_002E6CF0(func_L06_003E1040, moby);
        if ((D_L06_001B2348 ^ 1) & 1) (*(int *)(st + 4))++;
        if (func_00282948((int *)(st + 8))) {
            func_002AA2E8((float *)(st + 12), 0, 0.060000002f);
            if (*(float *)(st + 12) <= 0) func_0029F338(moby);
        } else {
            func_002AA2E8((float *)(st + 12), 1, 0.060000002f);
        }
        break;
    }
}
