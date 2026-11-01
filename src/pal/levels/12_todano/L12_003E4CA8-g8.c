#include "include_asm.h"

#include "common.h"
extern u8 *D_L12_001B2E9C __attribute__((sda));
extern u16 *D_L12_001FB960[];
extern s32 D_L12_001B09F4 __attribute__((sda));
extern s32 func_PAL_002A7E68(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_002A7750(void *arg0, s32 arg1, s32 arg2);
extern void func_00282CF0(f32 *buf, u8 *arg1, u8 *arg2);
extern void func_002AC9F8(f32 *buf, f32 x);
extern void func_00282CC0(u8 *arg0, u8 *arg1, f32 *buf);
extern void func_002AA800(u8 *arg0, s32 arg1, f32 x, f32 y);
extern void func_PAL_002AD288(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);
extern s32 D_L12_001B1838 __attribute__((sda));
extern s32 D_L12_001B183C __attribute__((sda));
extern s32 D_L12_001B1840 __attribute__((sda));
extern u16 D_L12_001B1834 __attribute__((sda));
extern f32 D_L12_001B1858 __attribute__((sda));
extern s32 func_2F15C8(void *arg0);
extern s32 func_31E2E0(s32 arg0, s32 arg1);
extern u8 *D_L12_001B090C __attribute__((sda));
extern u8 *D_L12_001B1360 __attribute__((sda));
extern u8 D_L12_001B9E00[];
extern u8 *D_0018C0B0 NOT_SDA;
extern u8 *D_L12_001FEAC0[];
extern u8 D_00189EA0[];
extern u8 D_001A7AF8[] __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;

/* Arms the measured sub-object on the first entry. */
void func_PAL_L12_003E4CA8(u8 *object, u8 *arg1, u8 *arg2, s32 arg3) {
    f32 buffer[4];
    u16 flags;

    if (*(u8 *)(object + 0x43) != 0xA)
        func_PAL_002A7E68(object, 0xA, 0, 5);
    if (*(u8 *)(object + 0xBC) != 8)
        func_002A7750(object, 8, 1);
    func_00282CF0(buffer, arg1, object + 0x10);
    func_002AC9F8(buffer, 0.20000002f);
    func_00282CC0(object + 0x10, object + 0x10, buffer);
    func_002AA800(object + 0xF8, 0, *(f32 *)(arg2 + 8), 0.25132746f);
    if (arg3 != 0) {
        flags = *(u16 *)(object + 0x34);
        D_L12_001B09F4 = D_L12_001B09F4 + 1;
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (flags | 0x41) & 0xEFFF;
        func_PAL_002AD288(object, object + 0x10, -1, 1.0f, 0.0f);
        func_002A7750(object, 1, 0);
    }
}
