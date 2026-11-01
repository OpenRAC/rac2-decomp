#include "include_asm.h"

#include "common.h"
extern f32 D_L01_001B082C __attribute__((sda));
extern f32 D_L01_001B0830 __attribute__((sda));
extern f32 D_L01_001B0834 __attribute__((sda));
extern f32 D_L01_001B0838 __attribute__((sda));
extern u8 *D_L01_001BF918 __attribute__((nosda));
typedef struct { u8 pad[0x2290]; s32 collision; } CameraAB;
extern CameraAB D_00189E20;
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L01_003DED38(void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern f32 func_PAL_L01_003BEB40(void);
extern s32 func_00277258(void *, s32, f32, s32);
extern void func_PAL_L01_003DE970(void *, void *);
extern void func_L01_003120A8(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void func_00282F20(void *, void *, f32);
extern void func_0029F338(void *);
extern void func_002A9288(void *, f32);

void func_PAL_L01_003DF218(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 height;
    *(f32 *)(obj + 0x2C) += (*(f32 *)(*(u8 **)(obj + 0x24) + 0x24) * D_L01_001B082C - *(f32 *)(obj + 0x2C)) * D_L01_001B0830;
    qcopy(pos, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, state);
    func_PAL_L01_003DED38(obj);
    if ((obj[0x60] & 2) && obj[0x43] != 1) func_PAL_002A7E68(obj, 1, 0, 10);
    height = func_PAL_L01_003BEB40();
    if ((func_00277258(obj + 0x10, 0, D_L01_001B0838, *(s32 *)(state + 0x10)) &&
          (!D_L01_001BF918 || *(s16 *)(D_L01_001BF918 + 0xAA) != 0x660)) || *(f32 *)(obj + 0x18) < height) {
        func_PAL_L01_003DE970(obj, state);
        qcopy(bottom, obj + 0x10);
        bottom[2] -= 6.0f;
        func_L01_003120A8(D_00189E20.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        func_00282F20(state, state, D_L01_001B0838);
        *(s32 *)(state + 8) = 0;
        func_00282CC0(obj + 0x10, obj + 0x10, state);
        func_00282CC0(bottom, bottom, state);
        func_L01_003120A8(D_00189E20.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        func_0029F338(obj);
    } else {
        *(f32 *)(state + 8) -= D_L01_001B0834 * 0.00040000002f;
        if (*(f32 *)(obj + 0x10) < 2.0f || *(f32 *)(obj + 0x10) > 1021.0f ||
            *(f32 *)(obj + 0x14) < 2.0f || *(f32 *)(obj + 0x14) > 1021.0f ||
            *(f32 *)(obj + 0x18) < 2.0f || *(f32 *)(obj + 0x18) > 1021.0f) { func_0029F338(obj); return; }
        func_002A9288(obj, *(f32 *)(obj + 0x2C) / *(f32 *)(*(u8 **)(obj + 0x24) + 0x24));
    }
}
