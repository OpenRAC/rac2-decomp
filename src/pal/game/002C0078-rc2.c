#include "names.h"
/* func_PAL_002C0078, the PAL copy of func_002BF390: the same C, where each D_001AA36x - 1.0f is scaled by 1.2f. */
#include "common.h"

typedef int TI __attribute__((mode(TI)));
extern s32 FastDecTimer();
extern void FastVecAdd();
extern void FastVecSub();
extern void FastVecScale(void *, void *, f32);
extern f32 fast_vec_dist();
extern void part_kill();
extern f32 D_001AA364 __attribute__((sda));
extern f32 D_001AA368 __attribute__((sda));

void func_PAL_002C0078(s32 arg0) {
    s32 sp[4];
    TI sp10;
    s32 temp_v0;
    u8 temp_v1;
    s32 temp_s1;
    s32 temp_s3;

    temp_v0 = (*(s32 *)((s8 *)(arg0) + (0x30)));
    if (temp_v0 == 0 || (temp_v1 = (*(u8 *)((s8 *)(temp_v0) + (0x20))), temp_v1 == 0xFE) || temp_v1 == 0xFD || FastDecTimer(arg0 + 0xA) != 0) {
        part_kill(arg0);
        return;
    }
    temp_s3 = arg0 + 0x10;
    FastVecSub(&sp10, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10, temp_s3);
    temp_s1 = arg0 + 0x20;
    *(TI *)sp = sp10;
    FastVecScale(sp, sp, (D_001AA364 - 1.0f) * 1.2f + 1.0f);
    FastVecAdd(&sp10, sp, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(arg0) + (0x10))) = sp10;
    FastVecSub(&sp10, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10, temp_s1);
    *(TI *)sp = sp10;
    FastVecScale(sp, sp, (D_001AA368 - 1.0f) * 1.2f + 1.0f);
    FastVecAdd(&sp10, sp, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(arg0) + (0x20))) = sp10;
    if (fast_vec_dist(temp_s3, temp_s1) < 0.1f || fast_vec_dist(temp_s3, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10) < 1.0f) {
        part_kill(arg0);
    }
}
