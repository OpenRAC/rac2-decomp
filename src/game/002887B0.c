#include "names.h"
/* func_002887B0: the switch only sets a flag (retail's jump table lands on one shared
 * a1 = 1), one call per arm is cross-jumped into retail's single call, and the per-class
 * word is cleared when the call succeeds. The table it clears is D_00139868 (lui 0x14 /
 * -0x6798), not the one at 0x139688. */
/* func_002887B0 (near miss, boot 0x002887B0, 188 bytes, 28 places).
 *
 * The dispatch arm of the class-record updaters in game/002880E0.c.  Retail:
 * if the record's word at +0 is zero, return 0; otherwise call
 * func_00287FF8(id, kind) with kind 1 for ids 0xC, 0xE, 0x11, 0x12 and 0x35
 * and kind 2 for everything else (including out-of-range ids), then clear the
 * count word at 0x139688[id] when the call returned 0 and return that value.
 *
 * The switch is real: retail builds a 42-entry table at 0x26C6F0 covering
 * 0xC..0x35, and the five ids above are its only entries that are not the
 * default target.  Two measured spellings, both 0 of 28 places:
 *
 *   1. one call site per arm (below): 184 bytes, exact table span and
 *      default, but this cc1 hoists the shared `$a0 = $s0` above the split
 *      (retail has it only on the kind-1 edge);
 *   2. `int flag = 0; switch (...) { case <5 ids>: flag = 1; break; default:
 *      break; } result = func_00287FF8(a0, flag ? 1 : 2);` - also 184 bytes,
 *      and it reproduces the single call but this cc1 lowers the ternary with
 *      `movz` and puts the flag in `$a3`, where retail tests the flag in
 *      `$a1` (`addiu $a1,$zero,1` in the case block, then `beqz $a1`) because
 *      its flag and its argument were coalesced into the same register.
 *
 * What was learned and is worth keeping: the table span comes from the
 * extreme *case labels* (0xC and 0x35), not from the default, and the two
 * arms share one call - so the source had a single call with a conditional
 * second argument, and the remaining difference is that register coalescing.
 */

typedef int s32;

typedef unsigned char u8;

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x70];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} ClassRecord;

extern ClassRecord g_weapon_table[];

extern unsigned char g_item_slot_to_record[];

extern int D_00139868[];

extern int menu_seek_chain_entry(int, int);

/* Starts a help entry with the short or long variant depending on its id. Returns whether it started. */
int help_start_entry(int helpId)
{
    ClassRecord *record = &g_weapon_table[g_item_slot_to_record[helpId]];
    int result = 0;

    if (record->word00 != 0) {
        int isSmall = 0;

        switch (helpId) {
        case 0xC: case 0xE: case 0x11: case 0x12: case 0x35:
            isSmall = 1;
            break;
        }
        if (isSmall)
            result = menu_seek_chain_entry(helpId, 1);
        else
            result = menu_seek_chain_entry(helpId, 2);
        if (result != 0)
            D_00139868[helpId] = 0;
    }
    return result;
}
