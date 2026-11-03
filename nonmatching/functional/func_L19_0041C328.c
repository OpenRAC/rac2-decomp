/* functional: high. unchecked (w19v1 never called it: its only caller, func_L19_0041BFD0 at 0x0041C228, calls it when func_002B0ED8 (level 19 copy at 0x00323FA8) returns nonzero for (obj, state+0x140, 0)). Read in full against retail. The near-miss draft's body (all 42 instructions equal retail's) with the `sda`
   matching attribute dropped. Retail's catalogue row also holds the empty method at 0x0041C3D0
   (`jr $ra; nop`, entered from the level's vtbl); this C covers only 0x0041C328..0x0041C3CC. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C;
extern s32 D_L19_001B2A38;

/* Sets the +0x240 word of every entity listed in the object's group (arg0[0x21]) to 1. */
void func_L19_0041C328(u8 *arg0)
{
    u16 *p;
    u8 *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L19_001FB5A0[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L19_001B2A38 && p != 0 &&
           ((s16)p[-1] >= 0 || p == D_L19_001FB5A0[arg0[0x21]])) {
        e = D_L19_001B2A1C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        *(s32 *)(*(u8 **)(e + 0x68) + 0x240) = 1;
        p++;
    }
}
