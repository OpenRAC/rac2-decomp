#include "include_asm.h"

#include "common.h"
extern u16 *g_group_l20_id_lists[];
extern u8 *g_group_l20_member_table[] __attribute__((sda));
extern int g_group_count __attribute__((sda));
extern void SetDeathBits_pal(void *, int, int);
extern void protopet_end_action(u8 *, int);

/* For every entity of the object's group (the id list D_L20_001FBB20[self[0x21]], ids masked
   with 0x7FFF, 0x100-byte records at D_L20_001B2F9C) of class 0xB69 whose state byte is neither
   0xFE nor 0xFD, calls func_PAL_002A7650(e, 0, 1) and func_L18_003F74B8(e, 0).
   Own -G8 unit: D_L20_001B2FB8 is read through $gp.  The list walk is the usual group macro;
   its doubled p test leaves the exit test at the bottom, so retail's `b test` entry and the
   %hi copy in its delay slot come out (see func_L02_003EB138).  The entity bank is an `sda`
   array of unknown size, which gives retail's absolute lui/lw load in this -G8 unit. */
void yeedil_destroy_group_protopets_pal(u8 *self) {
    u16 *entry;
    u8 *member;

    if (self[0x21] == 0xFF)
        return;
    for (entry = g_group_l20_id_lists[self[0x21]];
         self[0x21] != 0xFF && self[0x21] <= g_group_count && entry != 0 &&
         ((entry != 0 && (s16)entry[-1] >= 0) || entry == g_group_l20_id_lists[self[0x21]]);
         entry++) {
        member = g_group_l20_member_table[0] + ((*entry & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (*(s16 *)(member + 0xAA) == MOBY_CLASS_PROTOPET && member[0x20] != 0xFE && member[0x20] != 0xFD) {
            SetDeathBits_pal(member, 0, 1);
            protopet_end_action(member, 0);
        }
    }
}
