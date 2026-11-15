#include "common.h"
#include "structs.h"

extern u8 r1_D_00154B80[];

struct TtyInitState {
    s32 unk0;
    volatile s32 unk4;
    volatile s32 unk8;
    volatile s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

struct TtyMmio {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u32 unk8;
};

extern struct TtyInitState r1_D_00154B50;

extern u8 r1_D_00154CC0[];

extern s32 r1_func_00118D80();

extern s32 r1_func_00119868_tty(int) __asm__("func_0011BAC8");

extern s32 r1_func_00119718();

extern void tty_handle_deci2_event();

/* rac1-decomp src/core/00119868.c: func_00119CC8 */
/* Opens the TTY DECI2 endpoint and initializes its uncached packet headers. */
s32 tty_open_channel(void) {
    struct TtyInitState *state = &r1_D_00154B50;
    struct TtyMmio *txBlock;
    struct TtyMmio *rxBlock;
    u32 mask;
    s32 baud;
    s32 cmd;

    r1_func_00118D80(0);
    *(volatile s32 *)&state->unk0 = r1_func_00119718(0x210, state, &tty_handle_deci2_event);
    if (state->unk0 < 0) {
        return 0;
    }
    state->unkC = 0;
    mask = 0x20000000;
    rxBlock = (struct TtyMmio *)((u32)r1_D_00154CC0 | mask);
    state->unk4 = 0;
    txBlock = (struct TtyMmio *)((u32)r1_D_00154B80 | mask);
    state->unk8 = 0;
    state->unk14 = (s32)rxBlock;
    state->unk10 = (s32)txBlock;
    baud = 0x210;
    cmd = 0x45;
    txBlock->unk2 = 0;
    txBlock->unk4 = baud;
    txBlock->unk6 = cmd;
    txBlock->unk7 = 0x48;
    txBlock->unk8 = 0;
    state->unk18 = r1_func_00119868_tty(0x100);
    return 1;
}

