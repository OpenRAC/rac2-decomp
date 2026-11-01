#include "include_asm.h"

typedef signed int s32;
typedef unsigned long long u64;
extern s32 func_L23_00419CA0(s32 arg0);
extern s32 func_L23_00419070(u64, s32);
extern void func_L00_0030C930(void);
extern s32 D_L23_001B3744 __attribute__((sda));
extern s32 D_L23_001B3738[3] __attribute__((sda));
extern s32 D_L23_00259050[3][60];
extern s32 D_L23_001B3744 __attribute__((sda));
extern s32 D_L23_001B3738[3] __attribute__((sda));
extern s32 D_L23_001B1FA0[4];
extern s32 D_L23_00259050[3][60];

/* Calls the measured shared helper and reports success. */
s32 func_PAL_L23_00420558(void) {
    func_L00_0030C930();
    return 1;
}

