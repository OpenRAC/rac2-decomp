#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern void func_00283098(Quad128 *, Quad128 *, char *);
typedef int TI128 __attribute__((mode(TI)));
extern void func_PAL_002A7650(char *, int, int);
extern void func_00283098(TI128 *, TI128 *, char *);
extern void func_00282CC0(TI128 *, TI128 *, char *);
extern void func_PAL_L00_003FB330(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);
extern void func_002E5CF8(int, int, char *);
extern void func_00282F20(TI128 *, TI128 *, float);
extern void func_PAL_002B15D8(char *, int, TI128 *, float, float, float, float, int);

/* func_L07_003EB838 is in L07_003EB838.c. */

void func_PAL_L07_003EFEA0(char *actor)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    *(int *)(actor + 0x98) = 0;
    *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) | 0x41) & 0xefff;
    func_PAL_002A7650(actor, 0, 3);
    *(TI128 *)position = 0;
    position[2] = 0.75f;
    func_00283098((TI128 *)position, (TI128 *)position, actor + 0xc0);
    func_00282CC0((TI128 *)position, (TI128 *)position, actor + 0x10);
    func_PAL_L00_003FB330((TI128 *)position, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f,
                 1, 0, 0, *(int *)(state + 0x314));
    func_002E5CF8(9, 0, actor);
    func_00282F20((TI128 *)direction, (TI128 *)(state + 0x1c0), 0.060000002f);
    func_PAL_002B15D8(actor, 0x7f8, (TI128 *)direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xff);
}


extern void func_002A7750(int, int, int);
extern int func_002A7820(int, int);
extern void func_L07_002E2090(char *, int, int, char *, int, int, int);
extern void func_002A7750(int, int, int);

/* Arm the object's mode ten and hand it to the shared launcher. */
void func_PAL_L07_003EFFD0(char *arg, int a1, int a2, int a3, int a4)
{
    int r;

    func_002A7750(arg, 8, -1);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(arg + 0x98) = *(int *)(*(char **)(arg + 0x24) + 0x10);
    r = ((s32)(func_002A7820(0x2D, 0x4B)) * 5 + 2) / 6;
    func_L07_002E2090(arg, a1, a2, arg + 0xF0, r, a3, a4);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L07_003F0090);

