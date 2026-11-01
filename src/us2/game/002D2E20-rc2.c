#include "include_asm.h"

#include "common.h"
extern void func_0027C540(s32);
extern void func_0027C660(void);
extern void func_0027FAA8(s32, s32, u64, s32, s32);
extern s32 func_00288FB8(s32);
extern void func_002CE5D0(s32, s32);
extern void func_00300A00(s32, s32, f32, f32, f32, f32, f32);
extern s32 func_00336D50(s32, s32);
extern s32 D_001A8CFC;
extern s32 D_001A7340;
extern f32 D_001B23A8;
extern s32 g_001ABA5C __attribute__((sda));
extern s32 g_001ABA58 __attribute__((sda));

s32 func_US2_002D2E20(void) {
    f32 z;
    s32 r;

    func_0027C540(0);
    z = 0.0f;
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDE);
    func_00300A00(r, 0x60442D00, (f32)(D_001A7340 / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDF);
    func_00300A00(r, 0x60241700, (f32)(D_001A7340 / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xE0);
    func_00300A00(r, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    func_002CE5D0(g_001ABA58 != 0, g_001ABA58 != 0x11);
    func_0027FAA8(0x1B0, 0x177, (u64)0x80F0F0F0, func_00288FB8(0x2BE5), -1);
    func_0027C660();
    return 0;
}
