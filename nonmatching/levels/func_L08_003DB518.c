/* 6 November 2026, USA v1.01, check.py only: retained 972/972 bytes,
 * 0/2 placements, frame 0x70 versus retail 0x80. Profile: -O2 -G8
 * -ffunction-sections. Equal size does not establish a match.
 * New hypotheses: declare the two real screen-dimension words separately
 * as macro-addressed scalars, and spell vertical scaling in an inline helper
 * with two int returns. The scalar declarations remove the incorrect shared
 * address hoist and preserve x/y order in both text draws. The helper joins
 * its integer result before converting it back to float, as retail does.
 * The real clamp and raster operations are grouped in separate one-pass
 * groups. An explicit size constant is retained as source, with no added
 * memory access. Removing the clamp group gives 964 bytes; one outer group
 * gives 968. -fno-gcse and a non-const size local do not fix the frame.
 * Remaining: retail keeps 32.0f in f23 across the conditional UI draws and
 * saves s5 for a second rounding-mode constant; this body rematerializes
 * 32.0f later and uses only three saved FPRs. FP allocation, style-copy
 * scheduling and rounding setup still differ. Reopen with constant-lifetime
 * evidence, not an equal-size claim. No donor found in RAC1/RAC4 searches.
 * Historical reconstruction note follows; it describes the earlier body.
 */
/* func_L08_003DB518: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Complete UI reconstruction with 16-byte packed style and 64-bit text-style argument. The 16-byte text slot is sufficient: the current retail format is %d and the input is s32 (at most 12 bytes including termination). Frame, rounding/allocation and scheduling remain.
   No linked match is claimed.
*/

#include "common.h"
typedef struct __attribute__((packed)) { s64 word[2]; } Style;
extern u8 *D_L08_001B0488 __attribute__((sda));
extern u8 *D_L08_001A904C MACRO_ADDR;
extern f32 D_L08_001B046C __attribute__((sda));
extern f32 D_L08_001B0468 __attribute__((sda));
extern f32 D_L08_001B0460 __attribute__((sda));
extern s32 D_L08_001B0484 __attribute__((sda));
extern s32 D_L08_001B047C __attribute__((sda));
extern s32 D_L08_001B0480 __attribute__((sda));
extern f32 D_L08_001B3244 MACRO_ADDR;
extern s32 D_L08_001B3240 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_001A7344 MACRO_ADDR;
extern Style D_L08_001B0490;
extern char D_L08_001B04A0[];
extern void func_L00_0037B750(void), func_L08_00300090(void), func_L08_00300100(void), func_L08_003000C0(void);
extern s32 func_00336D50(void *, s32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern s32 func_L08_003DB4E8(void), func_0028E588(s32, s32), func_00283CF0(f32);
extern int func_0028EA58(s32, s32, s32, s32, s32, void *);
extern s32 func_00115DA8(char *, char *, ...);
extern u32 func_001157AC(char *);
extern s32 func_0027FAA8(s32, s32, u64, void *, s32);

static __inline__ s32 screen_y(f32 y)
{
    f32 scaled = y * D_L08_001B3244 + 0.5f;
    if (D_L08_001B3240 == 1) return (s32)(scaled + 4.0f);
    return (s32)scaled;
}

s32 func_L08_003DB518(void)
{
    Style style;
    char text[16];
    u8 *state = *(u8 **)(D_L08_001B0488 + 0x68);
    f32 fade, bottom;
    const f32 size = 32.0f;
    s32 texture, x, y, width, height;
    char *label;
    func_L00_0037B750();
    do {
    *(f32 *)(state + 4) += D_L08_001B046C;
    if (*(f32 *)(state + 4) > 1.0f) *(f32 *)(state + 4) = 1.0f;
    } while (0);
    if (D_L08_001A904C) {
        func_L08_00300090();
        func_L08_00300100();
        label = (char *)func_00336D50(D_L08_001A904C + 0x8710, 0xAC);
        func_00300A00(label, 0x60442D00, (f32)(D_001A7340 / 2), (f32)(D_001A7344 / 2), 1.0f, 1.0f, 0.0f);
        label = (char *)func_00336D50(D_L08_001A904C + 0x8710, 0xAD);
        func_00300A00(label, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)(D_001A7344 / 2), 1.0f, 1.0f, 0.0f);
        func_L08_003000C0();
    }
    do {
    fade = (1.0f - *(f32 *)(state + 4)) * size * 0.5f;
    bottom = (f32)(D_001A7344 - (s32)(D_L08_001B0468 * D_L08_001B3244 + 0.5f));
    style = D_L08_001B0490;
    texture = func_0028E588(0xEAA2, func_L08_003DB4E8());
    x = func_00283CF0(D_L08_001B0460 + fade);
    y = func_00283CF0(bottom + (f32)screen_y(fade - (f32)D_L08_001B0484));
    width = func_00283CF0(size * *(f32 *)(state + 4));
    height = (s32)((f32)func_00283CF0(size * *(f32 *)(state + 4)) * D_L08_001B3244 + 0.5f);
    func_0028EA58(texture, x, y, width, height, &style);
    func_00115DA8(text, D_L08_001B04A0, *(s32 *)state);
    x = func_00283CF0(D_L08_001B0460 + (f32)D_L08_001B047C);
    y = func_00283CF0(bottom);
    y += screen_y((f32)D_L08_001B0480);
    func_0027FAA8(x, y, 0x80F0F0F0UL, text, func_001157AC(text));
    } while (0);
    return 0;
}
