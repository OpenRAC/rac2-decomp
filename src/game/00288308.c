#include "names.h"
/* func_00288308: the two per-class flag tables are sda arrays, which -G0 addresses with
 * the la macro (lui/addiu together) as retail does; func_00287FF8 returns a value (it
 * ends with daddu $v0,$s2), which keeps the final store's high half out of $v0. */
/* func_00288308 (near miss, boot 0x00288308, 220 bytes, 28 places).
 *
 * The activate arm of the class-record updaters in game/002880E0.c.  Retail:
 *   - if the byte at 0x1A7AF8[a0] is already set, return (void function);
 *   - set 0x1A7B30[a0] and 0x1A7AF8[a0] to 1, in that order;
 *   - when the record's halfword at +0x88 is non-zero and the count word at
 *     0x139688[a0] is zero, copy the halfword at +0x92 into the count (note the
 *     direction: the non-zero halfword gates the store, it is not tested as a
 *     cleared flag);
 *   - call func_002883E8 and then func_00288208 with the same id;
 *   - for id 0x10 only: when func_00288D58() is non-zero call
 *     func_00287FF8(0x10, 2) and then clear 0x1398A8, which is inside that
 *     inner if.
 *
 * Measured: -O2 -G0 -ffunction-sections, 220 bytes, exact size, 0 of 28
 * places.  Instruction at +0x8 is the first difference: retail keeps the
 * `lui`/`addiu` pair of D_001A7AF8 together before the two `sd` prologue
 * stores, this cc1 puts `sd $s0` between them, and the same hoisting
 * difference moves the two address additions (`$s0 + D_00139568` and
 * `$s0 + 0x1A7B30`) four instructions earlier in retail.  Every instruction
 * and operand otherwise agrees (including the shared `$v0 = 1` for both
 * byte stores).  `-fno-schedule-insns` reproduced the same difference.
 * Reopen only with evidence for the original statement order, e.g. a sibling
 * whose prologue has the same hoist.
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

extern unsigned char g_item_owned_flags[] __attribute__((sda));

extern unsigned char g_help_unlocked_flags[] __attribute__((sda));

extern int g_item_ammo_counts[];

extern int g_help_unlock_word;

extern int menu_seek_chain_entry(int, int);

extern int flag_is_byte_set(void);

extern int help_store_id_in_slot_list(int);

extern void help_queue_pending_id(int);

/* Marks a help id as unlocked and makes its record ready to be shown. */
void help_unlock_entry(int helpId)
{
    ClassRecord *record;

    if (g_item_owned_flags[helpId] != 0)
        return;
    g_item_owned_flags[helpId] = 1;
    g_help_unlocked_flags[helpId] = 1;
    record = &g_weapon_table[g_item_slot_to_record[helpId]];
    if (record->half88 != 0 && g_item_ammo_counts[helpId] == 0)
        g_item_ammo_counts[helpId] = record->half92;
    help_store_id_in_slot_list(helpId);
    help_queue_pending_id(helpId);
    if (helpId == 0x10) {
        if (flag_is_byte_set() != 0) {
            menu_seek_chain_entry(0x10, 2);
            g_help_unlock_word = 0;
        }
    }
}
