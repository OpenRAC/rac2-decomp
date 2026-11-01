#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F415958;
extern s32 D_L05_001B0EE8 __attribute__((sda));
extern s32 D_L05_001B0EF8 __attribute__((sda));
extern s32 D_L05_001B0F08 __attribute__((sda));
extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, char *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(char *, void *, void *, void *, s32);

INCLUDE_ASM("asm/pal/levels", func_PAL_L05_0041A628);

