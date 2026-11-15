#include "common.h"

/* -mno-split-addresses unit: an absolute access that cc1 does not treat as small data stays one
   macro instruction (length 2, never in a delay slot), which the assembler expands with the
   destination as the address temporary (`lui $v0 ; lbu $v0,%lo($v0)`, stores through $at). */

/* The level timer, through $gp. */
extern int D_L01_001AEC38 __attribute__((sda));

/* The level's mode word: one read, which reorg copies into a branch delay slot ($gp form there)
   and the fall-through keeps as the absolute macro (docs/build/compiler-notes.md, MACRO_ADDR). */
extern int D_L01_001B2088 MACRO_ADDR;

/* The one-shot flag byte, absolute: retail leaves the preceding bgtz slot empty, so cc1 must not
   take it for small data. */
extern unsigned char D_001A7A6F __attribute__((nosda));
extern int D_L01_001A907C MACRO_ADDR;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void value_set_entry_by_index(int, int);

/* Once the level's mode word reaches 6 and the timer at D_L01_001AEC38 has run out, raises the
   one-shot flag and starts the sequence (mode 2 first rearms the timer to 0x42). A fresh
   object (state 0) clears its byte at +0x30. */
void oozla_intro_sequence_trigger(char *effectObject) {
    if (*(unsigned char *)(effectObject + 0x20) == 0)
        *(unsigned char *)(effectObject + 0x30) = 0xFF;
    if (D_L01_001B2088 == 2)
        D_L01_001AEC38 = 0x42;
    if (D_L01_001B2088 < 6)
        return;
    if (D_L01_001AEC38 > 0)
        return;
    if (D_001A7A6F != 0)
        return;
    D_001A7A6F = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index(0x1233, -1);
    D_L01_001A907C = 1;
}
