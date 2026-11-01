#include "include_asm.h"

#include "common.h"
extern void func_00282948();
extern int func_002A7820(int, int);
extern void func_PAL_002B14F8(u8 *, u8 *, s32, s32, f32);
extern u8 *D_L01_001B264C __attribute__((sda));

/* Clears the measured 0x350 word when it is set, then draws the new duration
   if the old one is still short. */
void func_PAL_L01_003B8E50(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x68);
    u16 flags;

    if (*(u32 *)(p + 0x350) != 0) {
        *(u32 *)(p + 0x350) = 0;
        if (*(s32 *)(p + 0x330) < 167) {
            *(u32 *)(p + 0x330) = ((s32)(func_002A7820(300, 360)) * 5 + 2) / 6;
        }
    }
    if (*(u32 *)(p + 0x244) != 1)
        func_00282948(p + 0x330);
    flags = *(u16 *)(a0 + 0x96);
    if (flags < 65534)
        *(u16 *)(a0 + 0x96) = flags + 1;
    func_00282948(p + 0x32C);
    func_00282948(p + 0x334);
    func_PAL_002B14F8(a0, p + 0x250, 6, 1, 4.0f);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L01_003B8F28);
