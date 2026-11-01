#include "include_asm.h"



typedef int s32;
typedef unsigned char u8;

void func_PAL_0034A2A0(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0xB8) = a1; *(s32 *)(a0 + 0xBC) = a2; }

void func_PAL_0034A2B0(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0xC8) = param_2;
  return;
}

typedef float f32;

void func_PAL_0034A2B8(u8 *a0,f32 f0,f32 f1) {
 (*(f32 **)(a0+0x5C))[0]=f0;
 (*(f32 **)(a0+0x5C))[1]=f1;
 (*(s32 **)(a0+0x5C))[2]=0;
 (*(s32 **)(a0+0x5C))[3]=0;
}

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0034A2E0(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x60) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0034A2E8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0xCC) = a1; }

extern int func_00348128(unsigned char *);

/* Measured target: byte-identical across all 27 levels. */
s32 func_PAL_0034A2F0(u8 *a0) { return *(s32 *)(a0 + 0x60); }

/* Measured target: byte-identical across all 27 levels. */
s32 func_PAL_0034A2F8(u8 *a0) { return *(s32 *)(a0 + 0xC0); }


extern void Faac80289_FUN_003361A8(char *p);
extern void Faac80289_FUN_00336968(char *p);

char *func_PAL_0034A690(char *a0)
{
    char *p = a0 + 536;
    int i;

    Faac80289_FUN_003361A8(a0);
    Faac80289_FUN_003361A8(a0 + 76);
    Faac80289_FUN_003361A8(a0 + 152);
    Faac80289_FUN_003361A8(a0 + 228);
    Faac80289_FUN_003361A8(a0 + 304);
    Faac80289_FUN_003361A8(a0 + 380);
    Faac80289_FUN_003361A8(a0 + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(p);
        p += 88;
    }
    return a0;
}

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0034A738(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4B8) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0034A740(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4BC) = a1; }

