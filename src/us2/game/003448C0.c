#include "include_asm.h"

extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_US2_003448C0(char *p)
{
    F449e2f67_FUN_003361A8(p);
    F449e2f67_FUN_003361A8(p + 76);
    F449e2f67_FUN_003361A8(p + 152);
    F449e2f67_FUN_003361A8(p + 228);
    F449e2f67_FUN_003361A8(p + 304);
    F449e2f67_FUN_003361A8(p + 380);
    F449e2f67_FUN_00336968(p + 456);
    F449e2f67_FUN_00336968(p + 544);
    F449e2f67_FUN_003366D0(p + 632);
    F449e2f67_FUN_00336968(p + 696);
    F449e2f67_FUN_00336968(p + 784);
    F449e2f67_FUN_00336968(p + 872);
    F449e2f67_FUN_00336968(p + 960);
    F449e2f67_FUN_00336968(p + 1048);
    return p;
}


INCLUDE_ASM("asm/us2/game", func_US2_00344950);

INCLUDE_ASM("asm/us2/game", func_US2_00344E08);

INCLUDE_ASM("asm/us2/game", func_US2_00344F18);

INCLUDE_ASM("asm/us2/game", func_US2_00345080);

extern int func_002E5E58(int, unsigned int, void *);
extern short D_L00_001AAB76;

void func_US2_003451B8(char *object, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4B0) = 1;
        *(int *)(object + 0x4AC) = 3;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4AC) = 3;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 0;
        *(int *)(object + 0x4AC) = 1;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B0) = 0;
        *(int *)(object + 0x4B8) = 3;
        *(int *)(object + 0x4AC) = 0;
    }
    *(int *)(object + 0x4B4) = D_L00_001AAB76;
}


INCLUDE_ASM("asm/us2/game", func_US2_00345298);
