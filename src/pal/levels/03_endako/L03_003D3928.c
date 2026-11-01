#include "include_asm.h"


#include "common.h"
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_32C010();
extern void func_32C328(char *a0, char *a1, s32 a2);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern u8   D_001395BF;
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;

void func_PAL_L03_003D3C90(char *a0)
{
    char *moby = *(char **)(a0 + 0x68);

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x5C) |= 1;
        func_32C010(a0, moby + 0x60, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        func_32C328(a0, moby + 0x60, 0);
        break;
    }
}

