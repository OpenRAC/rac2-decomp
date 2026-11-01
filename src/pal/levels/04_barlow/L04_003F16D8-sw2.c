#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;
extern char *D_L04_001B24DC __attribute__((sda));
extern char *D_L04_001B25CC[] __attribute__((sda));
extern char D_00189EA0[], D_00188660[];
extern HeroD740 D_L04_001B9540;
extern u8 D_0019B2E8[];
extern char *D_0018C0B0;
extern int D_001A79F0 __attribute__((sda));
extern int func_002A8508(int, int);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002ACBC8(void *, int);
extern void func_L00_00429020(int);
extern int func_L00_00429048(int);
extern void func_002A0430(unsigned int);
extern void func_002DF3F8(void *, void *);
extern int func_L00_0035F5A0(int, int, void *);
extern void func_L00_003294F0(void *, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_002E59F8(int);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_003F16D8);

