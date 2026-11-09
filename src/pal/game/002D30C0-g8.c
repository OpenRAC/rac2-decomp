/* func_PAL_002D30C0, the PAL copy of func_002D2188 (src/game/002D2188-g8.c): HUD coordinates 306/308
   (USA 330/332), text 0xB60 (USA 0x2D4F), and the three bar draws in an inline helper, so each
   call reloads its 1.0f instead of sharing one register as USA does. */
#include "common.h"

extern void func_0027C540(s32);
extern void func_0027C660(void);
extern s32 func_0027FAA8(s32, s32, u64, s32, s32);
extern s32 func_00288FB8(s32);
extern void func_0028FC48(s32, s32, s32, s32, u64, s32);
extern void func_002CE5D0(s32, s32);
extern void func_00300A00(s32, s32, f32, f32, f32, f32, f32);
extern s32 func_00336D50(s32, s32);
extern s32 D_001A8CFC;
extern s32 D_001A7340;
extern f32 D_001B23A8;
extern f32 D_001B23A4;
extern s32 ref_PAL_002D30C0_01 __attribute__((sda));
extern s32 ref_PAL_002D30C0_02 __attribute__((sda));
extern struct { s16 text; s16 reserved; } D_001ABD68[] MACRO_ADDR;

/* The display mode word beside the HUD scale. */
extern s32 D_001B23A0;

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused $s1 (as func_00326A10). */
static __inline__ s32 hud_coord(f32 value, f32 scale, f32 half, s32 active)
{
    f32 scaled = scale * value + half;
    s32 result = (s32)scaled;

    if (result != 0 && D_001B23A0 == active)
        scaled = 1.0f;
    return result;
}

/* One bar of the HUD: the sprite for `id`, centred, in `color`. */
static __inline__ void draw_bar(s32 id, s32 color, f32 z)
{
    s32 r = func_00336D50(D_001A8CFC + 0x8710, id);

    func_00300A00(r, color, (f32)(D_001A7340 / 2), (f32)ref_PAL_002D30C0_01, 1.0f, D_001B23A8, z);
}

s32 func_PAL_002D30C0(void) {
    f32 z, s, half;
    s32 r;
    s32 center, one;

    func_0027C540(0);
    z = 0.0f;
    one = 1;
    draw_bar(0xDE, 0x60442D00, z);
    draw_bar(0xDF, 0x60241700, z);
    draw_bar(0xE0, 0x55F0C070, z);
    func_002CE5D0(ref_PAL_002D30C0_02 != 0, ref_PAL_002D30C0_02 != 5);
    s = D_001B23A4;
    half = 0.5f;
    func_0028FC48(66, hud_coord(306.0f, s, half, one), 463, hud_coord(308.0f, s, half, one), 0x55F0C070, 0);
    center = D_001A7340 / 2;
    func_0027FAA8(center, 311, (u64)0x80F0F0F0, func_00288FB8(D_001ABD68[ref_PAL_002D30C0_02].text), -1);
    func_0027FAA8(0x1B0, 0x177, (u64)0x80F0F0F0, func_00288FB8(0xB60), -1);
    func_0027C660();
    return 0;
}
