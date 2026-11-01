#include "include_asm.h"


INCLUDE_ASM("asm/us2/game", func_US2_00345890);





extern void F6402b823_FUN_00336320(char *a);
extern void F6402b823_FUN_00336A78(char *a);
extern void F6402b823_FUN_00335E68(char *a, int b);
extern void F6402b823_FUN_00345268(char *a);
extern void F6402b823_FUN_00345088(char *a);
extern void F6402b823_FUN_00344F98(char *a);
extern void F6402b823_FUN_00345178(char *a);
extern void F6402b823_FUN_00344938(char *a);

void func_US2_003462C0(char *obj)
{
    if (*(int *)(obj + 1192) != 0) {
        char *s0 = obj + 456;

        F6402b823_FUN_00336320(obj);
        F6402b823_FUN_00336320(obj + 76);
        F6402b823_FUN_00336320(obj + 152);
        F6402b823_FUN_00336320(obj + 228);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00336A78(obj + 696);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00335E68(obj + 544, 0);
        F6402b823_FUN_00345268(obj);
        F6402b823_FUN_00345088(obj);
        F6402b823_FUN_00344F98(obj);
        F6402b823_FUN_00345178(obj);
        F6402b823_FUN_00344938(obj);
        F6402b823_FUN_00336320(obj + 380);
    }
}


extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_US2_00346368(char *p)
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


INCLUDE_ASM("asm/us2/game", func_US2_003463F8);
