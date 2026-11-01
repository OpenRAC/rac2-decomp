#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern void func_00283098(Quad128 *, Quad128 *, char *);
typedef int TI128 __attribute__((mode(TI)));
extern void func_00325D30(char *, char *);
extern void func_PAL_002A7650(char *, int, int);
extern void func_00283098(TI128 *, TI128 *, char *);
extern void func_00282CC0(TI128 *, TI128 *, char *);
extern void func_PAL_L00_003FB330(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);
extern void func_002E5CF8(int, int, char *);
extern void func_00282F20(TI128 *, TI128 *, float);
extern void func_PAL_002B15D8(char *, int, TI128 *, float, float, float, float, int);

/* Arm the object's mode, then set up its position and hand it to the launcher.
   func_PAL_002B15D8's integer mask is its last parameter, and this compiler sets the
   arguments up in parameter order: the mask's store then comes after the four
   float copies, in the call's delay slot, as the retail has it. */
void func_PAL_L07_003EB508(char *arg)
{
    char *o;
    TI128 v[1];
    TI128 w;

    o = *(char **)(arg + 0x68);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) | 0x41) & 0xEFFF;
    *(int *)(arg + 0x98) = 0;
    func_00325D30(arg, o + 0x330);
    func_PAL_002A7650(arg, 0, 3);
    v[0] = 0;
    ((float *)v)[2] = 0.75f;
    func_00283098(v, v, arg + 0xC0);
    func_00282CC0(v, v, arg + 0x10);
    func_PAL_L00_003FB330(v, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, *(int *)(o + 0x338));
    func_002E5CF8(6, 0, arg);
    func_00282F20(&w, o + 0x1C0, 0.060000002f);
    func_PAL_002B15D8(arg, 1016, &w, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L07_003EB648);

INCLUDE_ASM("asm/pal/levels", func_PAL_L07_003EEC8C);

INCLUDE_ASM("asm/pal/levels", func_PAL_L07_003EF670);
