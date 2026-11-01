#include "include_asm.h"

#include "common.h"
extern s32 *ref_L06_0047AC68_00[] __attribute__((sda));
extern void ref_L06_0047AC68_01(s32);
extern u8 D_0018C0D4 __attribute__((nosda));
extern s32 D_0018C0BC __attribute__((nosda));
typedef struct {
    char pad0[0x34C];
    s16 field34C;
    char pad1[0x24A0 - 0x34E];
    s32 field24A0;
} L06State;
extern L06State D_00189E20 __attribute__((nosda));
extern int D_001A79F0;

s32 func_PAL_L06_00480660(s32 a0)
{
    s32 *row;
    s32 *entry;
    char *state;
    u16 tag;

    row = (s32 *)((*(s16 *)(a0 + 0x84) << 5) + (s32)ref_L06_0047AC68_00[0]);
    entry = row + 7;
    state = (char *)*entry;

    if (*(s16 *)(state + 0x48) == 1 && *(s16 *)(state + 0x4A) != 0)
        return 0;
    tag = *(u16 *)(state + 0x2C);
    if (*(s16 *)(state + 0x2C) == 11 && D_0018C0D4 != 2)
        return 0;

    switch ((s16)tag) {
    case 1:
    case 10:
        if (*(s16 *)(state + 0x2E) != 0)
            goto clear;
        if (D_00189E20.field34C != 0) {
            if (D_001A79F0 != 14)
                return 0;
            if (D_00189E20.field24A0 != 13)
                return 0;
        }
    }
clear:
    if ((s16)tag != 2)
        goto call;
    if (D_0018C0BC == 26)
        goto call;
    *(u16 *)(state + 0x2E) = 0;
    return 0;
call:
    ref_L06_0047AC68_01(a0);
    return 0;
}
