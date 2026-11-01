#include "include_asm.h"

#include "common.h"
extern s32 ref_L22_00415A48_00(s32 *a, void *b);
extern s32 ref_L22_00415A48_01(s32 a, s32 b);
extern struct { s32 w0; s32 w1; s32 w2; } D_0018B6A8;

void func_PAL_L22_0041AA10(void *arg0) {
    s32 *temp_s1;
    void *temp_s0;

    temp_s1 = (*(s32 **)((s8 *)(arg0) + (0x68)));
    if ((*(u8 *)((s8 *)(arg0) + (0x20))) == 0) {
        (*(u8 *)((s8 *)(arg0) + (0x20))) = 1U;
        (*(u8 *)((s8 *)(arg0) + (0x30))) = 0xFF;
        *temp_s1 = 0x5DC;
    }
    if ((*(u8 *)((s8 *)(arg0) + (0x20))) == 1) {
        temp_s0 = (void *) D_0018B6A8.w0;
        if ((ref_L22_00415A48_00(temp_s1, arg0) != 0) && ((*(s32 *)((s8 *)(temp_s0) + (8))) == 0)) {
            if ((*(s32 *)((s8 *)(temp_s0) + (0xC))) == 0) {
                ref_L22_00415A48_01(0x9FD, 0x54);
                *temp_s1 = 0x5DC;
            }
        }
    }
}
