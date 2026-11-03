/* functional: high. Unchecked: retail never returns within the gate's 40M instructions from any captured call (levels 01-03: NOTHING COMPARED; the captures ran 80 of its 87 instructions). Read against all 87 retail instructions of level 00's copy (0x2B30E8-0x2B3240): same reads, writes and calls (func_L00_002F45B8, func_0027D330(0x10) at level 00's 0x2E7258) in the same order, data at the addresses retail forms. Fixed from the draft earlier: when the hero's slot byte (0x189E20+0x22C6) is 0xFF retail does not return early; it skips the threshold block and the slot&0xF count but still counts D_001A73E0[0xFF], calls func_0027D330(0x10) and sets byte 0x22C1. */
/*
 * func_L00_002B30E8 (348 bytes): counts a death/retry: bumps D_001A73D8 and
 * the level's D_0013A148 counter, runs func_L00_002F45B8, then (slot byte
 * not 0xFF) after D_L00_001B19C8 frames (1800 for hero states 0x74/0x79,
 * else 900) counts the slot in the level's D_001A24A8 row unless the save
 * byte D_0019B2E8 has bit 7, counts D_001A73E0[slot & 0xF]; always counts
 * D_001A73E0[slot], calls func_0027D330(0x10) and sets the hero's byte 0x22C1.
 */
/* GPT-6.1 Sol (high), v0775; default game -O2 -G0.
 * Best check: 328/348 bytes, 0/27 places.
 * Slot indices are unsigned bytes, including both final global increments.
 * Preserve independent row/column scaling of the per-player counter and the
 * initial two counter values before their stores. Global base-address
 * lifetimes, repeated slot reads, and scalar scheduling still differ.
 * A multidimensional spelling reaches 320 bytes with the retail 16-byte frame,
 * but not its address allocation; -mno-split-addresses and a declared volatile
 * slot do not resolve this. This retained draft has no volatile fields.
 * Required declarations are included below.
 */
#include "common.h"
extern int D_001A79F0;
extern int D_001A73D8;
extern int D_001A73E0[];
extern int D_0013A148[];
extern unsigned char D_0019B2E8[];
extern int D_001A24A8[];
extern int D_L00_001B19C8;
extern unsigned char D_00189E20[];
extern void func_L00_002F45B8(void);
extern void func_0027D330(int);

void func_L00_002B30E8(void)
{
    char *state = (char *)D_00189E20;
    int player;
    int slot;
    int id;
    int threshold;

    {
        int *counter = &D_0013A148[D_001A79F0];
        int count = *counter;

        D_001A73D8 = D_001A73D8 + 1;
        *counter = count + 1;
    }
    func_L00_002F45B8();
    if ((unsigned char)state[0x22C6] != 0xFF) {
        id = *(int *)(state + 0x2294);
        if (id == 0x74 || id == 0x79)
            threshold = 0x708;
        else
            threshold = 0x384;
        if (!(D_L00_001B19C8 < threshold)) {
            player = D_001A79F0;
            slot = (unsigned char)state[0x22C6];
            if ((D_0019B2E8[player * 16 + slot] & 0x80) == 0)
                D_001A24A8[player * 16 + (slot & 0xF)]++;
        }
        D_001A73E0[(unsigned char)state[0x22C6] & 0xF]++;
    }
    D_001A73E0[(unsigned char)state[0x22C6]]++;
    func_0027D330(0x10);
    state[0x22C1] = 1;
}
