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
extern s32 D_001A7340[] NOT_SDA;
extern Style D_L08_001B0490;
extern char D_L08_001B04A0[];
extern void func_L00_0037B750(void), func_L08_00300090(void), func_L08_00300100(void), func_L08_003000C0(void);
extern char *func_00336D50(void *, s32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern s32 func_L08_003DB4E8(void), func_0028E588(s32, s32), func_00283CF0(f32);
extern void func_0028EA58(s32, s32, s32, s32, s32, void *);
extern s32 func_00115DA8(char *, char *, ...);
extern u32 func_001157AC(char *);
extern s32 func_0027FAA8(s32, s32, u64, void *, s32);

s32 func_L08_003DB518(void)
{
    Style style;
    char text[16];
    u8 *state = *(u8 **)(D_L08_001B0488 + 0x68);
    f32 fade, bottom, scaled;
    s32 texture, x, y, width, height;
    char *label;
    func_L00_0037B750();
    *(f32 *)(state + 4) += D_L08_001B046C;
    if (*(f32 *)(state + 4) > 1.0f) *(f32 *)(state + 4) = 1.0f;
    if (D_L08_001A904C) {
        func_L08_00300090();
        func_L08_00300100();
        label = func_00336D50(D_L08_001A904C + 0x8710, 0xAC);
        func_00300A00(label, 0x60442D00, (f32)(D_001A7340[0] / 2), (f32)(D_001A7340[1] / 2), 1.0f, 1.0f, 0.0f);
        label = func_00336D50(D_L08_001A904C + 0x8710, 0xAD);
        func_00300A00(label, 0x55F0C070, (f32)(D_001A7340[0] / 2), (f32)(D_001A7340[1] / 2), 1.0f, 1.0f, 0.0f);
        func_L08_003000C0();
    }
    fade = (1.0f - *(f32 *)(state + 4)) * 32.0f * 0.5f;
    bottom = (f32)(D_001A7340[1] - (s32)(D_L08_001B0468 * D_L08_001B3244 + 0.5f));
    style = D_L08_001B0490;
    texture = func_0028E588(0xEAA2, func_L08_003DB4E8());
    x = func_00283CF0(D_L08_001B0460 + fade);
    scaled = (fade - (f32)D_L08_001B0484) * D_L08_001B3244 + 0.5f;
    y = func_00283CF0(bottom + (f32)(s32)(D_L08_001B3240 == 1 ? scaled + 4.0f : scaled));
    width = func_00283CF0(32.0f * *(f32 *)(state + 4));
    height = (s32)((f32)func_00283CF0(32.0f * *(f32 *)(state + 4)) * D_L08_001B3244 + 0.5f);
    func_0028EA58(texture, x, y, width, height, &style);
    func_00115DA8(text, D_L08_001B04A0, *(s32 *)state);
    x = func_00283CF0(D_L08_001B0460 + (f32)D_L08_001B047C);
    y = func_00283CF0(bottom);
    scaled = (f32)D_L08_001B0480 * D_L08_001B3244 + 0.5f;
    y += (s32)(D_L08_001B3240 == 1 ? scaled + 4.0f : scaled);
    func_0027FAA8(x, y, 0x80F0F0F0UL, text, func_001157AC(text));
    return 0;
}
