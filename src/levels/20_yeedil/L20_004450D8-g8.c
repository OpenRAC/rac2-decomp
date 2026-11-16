#include "common.h"

/* -G8: the group-index bound D_L20_001B2FB8 is read through $gp. */

extern int g_group_count __attribute__((sda));
extern char *g_group_l20_member_table;
extern unsigned short *g_group_l20_id_lists[];

/* For each entity of the object's group that has class 0xD0F and whose state has bit 0 set and
   word 0x420 equal to 1, sets the state byte to 2 and clears bit 1 of the entity's flags. */
/* Wakes up the troopers of this group that were waiting, switching them to their next state. */
void yeedil_wake_group_troopers(unsigned char *moby) {
    unsigned short *q;
    char *member;

    if (moby[0x21] == 0xFF)
        return;
    q = g_group_l20_id_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= g_group_count && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == g_group_l20_id_lists[moby[0x21]])) {
        char *trooper_vars;

        member = g_group_l20_member_table + ((*q & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (*(short *)(member + 0xAA) == MOBY_CLASS_MEGACORP_TROOPER_LEGS) {
            trooper_vars = *(char **)(member + 0x68);
            if (trooper_vars != 0 && (trooper_vars[0x302] & 1) && *(int *)(trooper_vars + 0x420) == 1) {
                trooper_vars[0x302] = 2;
                *(unsigned short *)(member + 0x34) &= 0xFFFD;
            }
        }
        q++;
    }
}
