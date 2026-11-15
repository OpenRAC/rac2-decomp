#include "include_asm.h"
#include "common.h"
extern s8 *D_001F2854;
extern s8 D_00262BE0[];
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern s32 GetLocalizedString(s32);

s32 func_PAL_002DCF20(s8 *a0) {
    s8 *v1;
    s32 s4;

    v1 = (*(s8 **)((s8 *)(D_001F2854) + (0xE8)));
    s4 = (*(s32 *)((s8 *)((*(s8 **)((s8 *)(v1) + (0x34))) + (*(s32 *)((s8 *)(v1) + (0x40))) * 12) + (4)));
    SetupGifPaging(0);
    if (s4 == -1) {
        text_draw_centered_small((*(s32 *)((s8 *)(a0) + (0x20))) / 2, (*(s32 *)((s8 *)(a0) + (0x24))) / 2 - 8, 0x80FFA888ULL, GetLocalizedString(0xC75), -1);
    } else {
        s32 t = s4 * 12;
        text_draw_centered_small((*(s32 *)((s8 *)(a0) + (0x20))) / 2, (*(s32 *)((s8 *)(a0) + (0x24))) / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(D_00262BE0 + t) + (0)))), -1);
        text_draw_centered_small((*(s32 *)((s8 *)(a0) + (0x20))) / 2, (*(s32 *)((s8 *)(a0) + (0x24))) * 2 / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(D_00262BE0 + t) + (4)))), -1);
    }
    DoGifPaging();
    return 2;
}
