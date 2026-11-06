#include "common.h"

/* -G8 for the HUD layout words. Incomplete sda arrays keep the resource pointer and the screen
   width as plain absolute loads. The early return sets v0 in the first branch's delay slot, and
   `result` shares v0 with it: with a single `return 0` block after the print code, reorg moves
   `li v0,1` into a jump over that block, and its USE keeps v0 live at the print block, which
   stops the blink test taking `andi v0` in the range branch's delay slot. */
extern u8 *D_L18_001A904C[] __attribute__((sda));
extern u8 D_00189E20[];
extern s32 D_001A7340[] __attribute__((sda));
extern u32 D_L18_001B12C4 __attribute__((sda)), D_L18_001B12C8 __attribute__((sda));
extern u32 D_L18_001B12CC __attribute__((sda)), D_L18_001B12D0 __attribute__((sda));
extern s32 D_L18_001B12D4 __attribute__((sda)), D_L18_001B12D8 __attribute__((sda));
extern s32 D_L18_001B12DC __attribute__((sda)), D_L18_001B12E0 __attribute__((sda));
extern s32 D_L18_001B12E4 __attribute__((sda)), D_L18_001B12E8 __attribute__((sda));
extern char D_L18_001B1300[];
extern s32 func_00336D50(u8 *, s32);
extern void func_00300A00(char *, s32, float, float, float, float, float);
extern float func_00283CE0(s32);
extern s32 func_00283D38(s32, s32, float);
extern void func_0027EAE8(s32, s32, s32, s32, s32, void *);
extern s32 func_00115DA8(char *, char *, ...);
extern void func_L18_003044B8(s32, s32, s64, char *, s32, float);
s32 func_L18_00426AB0(void)
{
    s32 colors[2];
    char text[16];
    u8 *state;
    u8 *hero = D_00189E20;
    s32 middle;
    float ratio;
    float amount;
    s32 handle;
    u16 remaining;
    s32 result;

    if (hero[0x22B4] != 4) {
        return 0;
    }
    result = 0;
    if (D_L18_001A904C[0]) {
        handle = func_00336D50(D_L18_001A904C[0] + 0x8710, 0xDB);
        func_00300A00((char *)handle, 0x60442D00, (float)(D_001A7340[0] / 2),
                      (float)(D_L18_001B12D8 + D_L18_001B12E8), 1.0f, 1.0f, 0.0f);
        handle = func_00336D50(D_L18_001A904C[0] + 0x8710, 0xDC);
        func_00300A00((char *)handle, 0x55F0C070, (float)(D_001A7340[0] / 2),
                      (float)(D_L18_001B12D8 + D_L18_001B12E8), 1.0f, 1.0f, 0.0f);
        state = *(u8 **)(*(u8 **)(hero + 0x2290) + 0x68);
        amount = func_00283CE0(*(s16 *)(state + 0x3BC));
        ratio = amount / func_00283CE0(*(s16 *)(state + 0x3BE));
        colors[0] = func_00283D38(D_L18_001B12C4, D_L18_001B12CC, ratio);
        colors[1] = func_00283D38(D_L18_001B12C8, D_L18_001B12D0, ratio);
        middle = D_001A7340[0] / 2;
        func_0027EAE8(middle + D_L18_001B12D4, D_L18_001B12D8,
                      (s32)((float)(middle + D_L18_001B12D4) + (float)D_L18_001B12DC * ratio),
                      D_L18_001B12D8 + D_L18_001B12E0, 0xFFFFF1, colors);
        func_0027EAE8(middle - D_L18_001B12D4, D_L18_001B12D8,
                      (s32)((float)(middle - D_L18_001B12D4) - (float)D_L18_001B12DC * ratio),
                      D_L18_001B12D8 + D_L18_001B12E0, 0xFFFFF1, colors);
        remaining = *(u16 *)(state + 0x3BC);
        if (remaining < 32 || remaining > 300 || (remaining & 24)) {
            func_00115DA8(text, D_L18_001B1300, (s16)remaining / 60);
            func_L18_003044B8(middle, D_L18_001B12E4 + 1, 0xFF000000, text, 3, 0.96f);
            func_L18_003044B8(middle, D_L18_001B12E4 - 1, 0xFF000000, text, 3, 1.04f);
            func_L18_003044B8(middle, D_L18_001B12E4, colors[0], text, 3, 1.0f);
        }
        result = 1;
    }
    return result;
}
