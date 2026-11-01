#include "include_asm.h"

#include "common.h"
extern void ref_L16_00424B48_00(s32, s32, s8 *, s32);

void func_PAL_L16_0042A338(s8 *arg0) {
    s32 temp_v0;
    s32 m;
    s32 lt;
    f32 fv;

    if ((*(u8 *)((char *)(arg0) + (0x20))) == 0) {
        if ((*(u8 *)((char *)(arg0) + (0xBC))) != 0) {
            (*(u8 *)((char *)(arg0) + (0x20))) = 1;
            ref_L16_00424B48_00(0, 0, arg0, 0xE71);
        }
        (*(s16 *)((char *)(arg0) + (0x32))) = 0x80;
    }
    if ((*(u8 *)((char *)(arg0) + (0x20))) == 1) {
        fv = (*(f32 *)((char *)(arg0) + (0x18))) - 0.16000001f;
        temp_v0 = (*(u16 *)((char *)(arg0) + (0x96))) + 1;
        m = temp_v0 & 0xFFFF;
        (*(u16 *)((char *)(arg0) + (0x96))) = temp_v0;
        lt = (u32) m < 0x3CU;
        (*(f32 *)((char *)(arg0) + (0x18))) = fv;
        if (lt == 0) {
            (*(u8 *)((char *)(arg0) + (0x20))) = 2;
        }
    }
}
