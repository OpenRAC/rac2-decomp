#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L12_003E3BD0);


#include "common.h"
extern u8 D_L12_001B9E00[];
extern u8 D_L12_00188660[];
extern s32 func_315148();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern void func_PAL_002AC3C0(void *arg0, void *arg1);
extern void func_002AEC48(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern f32 func_2F2950(f32 x, f32 y);
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *D_L12_001FB960[];
extern s32 D_001A79F0 __attribute__((sda));
extern s32 func_002A8600(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern u8 D_L12_001C0000[];
extern u8 *func_0029EFD0(int);
extern u8 *func_00288FB8(int);
extern s32 *D_L12_001FEAC0[];
extern s32 func_002A8AF0(void *, void *, s32);

/* Re-arms the measured two-slot primitive after the counter step. */
void func_PAL_L12_003E4A20(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_PAL_002AC3C0(object, state + 0x50);
    func_002AEC48(object, state + 0x6C0, 1, 0.0432f, 0.43200004f);
    func_002AEC48(object, state + 0x640, 0, 0.0432f, 0.43200004f);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
}


