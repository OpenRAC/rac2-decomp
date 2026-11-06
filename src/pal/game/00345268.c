#include "include_asm.h"

typedef unsigned char u8;
extern void func_003361A8(u8 *);
extern void func_00336968(u8 *);
extern void func_00336968(u8 *);
extern void func_003427B0(u8 *);
extern void func_003366D0(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_PAL_00345268(u8 *a0) {
    func_003361A8(a0);
    func_003361A8(a0 + 76);
    func_003361A8(a0 + 152);
    func_003366D0(a0 + 228);
    func_00336968(a0 + 432);
    func_00336968(a0 + 520);
    func_00336968(a0 + 608);
    func_003427B0(a0 + 712);
    return a0;
}

INCLUDE_ASM("asm/pal/game", func_PAL_003456B0);

INCLUDE_ASM("asm/pal/game", func_PAL_003452C8);


extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern char D_001ADC10[], D_001ADC18[], D_001ADC20[], D_001ADC30[], D_001ADC88[], D_001AE0C0[];
/* sda in this -G0 unit gives the one-instruction (macro) load of D_001A8CFC that retail has */
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_003361E0(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
extern void func_00336710(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00336A38(void *, void *);
extern void func_00336A30(void *, int);
extern const char *func_00288FB8(int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_003428E0(void *, void *);
extern void func_00343028(void *, float, float);
extern void func_00343038(void *, float);
extern void func_PAL_003457F0(void *, int);
extern void func_PAL_00345628(u8 *, unsigned int);

/* func_PAL_003452C8, the PAL copy of func_00343260: the same C, where the sub-objects past +0x1F8 move,
   the text id becomes 0xB60 and func_00336A30 is called after the third func_00336A38. */
typedef int s32;
typedef unsigned int u32;
extern void func_003435B0(u8 *, u32);

void func_PAL_00345628(u8 *a0, u32 a1) {
    if (a1 < 4) *(u32 *)(a0 + 0x2C4) = a1;
    *(s32 *)(a0 + 0x1a0) = 0;
}






INCLUDE_ASM("asm/pal/game", func_PAL_00345618);

INCLUDE_ASM("asm/pal/game", func_PAL_00345620);
