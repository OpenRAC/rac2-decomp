#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
extern u8 *func_002C65A0(void *, void *, int, unsigned, int, int, int,
                          float, float, float, int);
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern u8 *D_L18_001FF414[];
extern u8 *func_L18_00437AA0(void *, void *, void *, int, float, float);
extern void func_PAL_002AC3C0(u8 *arg0, u8 *arg1);
extern void func_002AEC48(u8 *arg0, u8 *arg1, s32 arg2, float arg3, float arg4);
extern void func_PAL_002B14F8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, float arg4);
extern void func_002A93B0(u8 *arg0);
extern float func_00282E48();
extern u8 D_001C97C0[];
extern u16 *D_L18_001FB320[];
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern s32 func_002ACBC8(u8 *, s32);
extern s32 func_002761F8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern u16 *D_L18_001FB320[];
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern u8 D_00190000[];

void func_PAL_L18_003FCCE8(u8 *a0) {
    u8 *s0 = a0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    func_PAL_002AC3C0(a0, s1 + 0x50);
    func_002AEC48(s0, s1 + 0x680, 1, 0.0432f,
                  0.43200004f);
    func_002AEC48(s0, s1 + 0x600, 0, 0.0432f,
                  0.43200004f);
    func_PAL_002B14F8(s0, s1 + 0x770, 2, 1, 2.5f);
    if (*(u16 *)(s0 + 0x96) <= 0xFFFEu) {
        *(u16 *)(s0 + 0x96) = *(u16 *)(s0 + 0x96) + 1;
    }
    *(u16 *)(s1 + 0x766) = 0;
    *(u16 *)(s1 + 0x768) = 0;
    *(u16 *)(s1 + 0x76A) = 0;
    if (*(u8 *)(s0 + 0x31) != 0) {
        if (func_00282E48(s0 + 0x10, D_001C97C0) < 24.0f) {
            func_002A93B0(s0);
            *(u8 *)(s0 + 0x6F) = 0x16;
        }
    }
}
