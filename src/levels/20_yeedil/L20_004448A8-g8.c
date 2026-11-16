#include "common.h"

extern char *g_group_l20_id_lists[];
extern int g_group_count;
extern char *g_group_l20_member_table;
extern float vec_distance_xy(void *, void *);

/* Walks the id lists that arg0's state names for arg1's class (0xD0F: two lists,
   0x119E/0x12EF: one) and returns the last moby, not flagged at +0x34 bit 0, for which
   func_00282E80(moby + 0x10, arg0 + 0x10) < 1025.0f; 0 if none.  Built with -G8 and
   split addresses: the list limit and the moby bank are single absolute loads, the
   list table is reached through a %hi/%lo pair. */
/* Looks through the groups linked to the given object and returns the last enabled member that is close to this enemy, or 0 if none is. */
char *FindLastGroupMemberInRange(char *moby, char *owner) {
    char *state = *(char **)(moby + 0x68);
    /* Retail's frame has 0x20 bytes of locals for this list; only two slots are used. */
    int group_ids[8];
    int list_count = 0;
    char *best;
    float range;
    int i;

    switch (*(s16 *)(owner + 0xAA)) {
    case MOBY_CLASS_MEGACORP_TROOPER_LEGS:
        list_count = 2;
        group_ids[0] = *(int *)(state + 0x21C);
        group_ids[1] = *(int *)(state + 0x240);
        break;
    case 0x119E /* moby class 4510 */:
    case 0x12EF /* moby class 4847 */:
        list_count = 1;
        group_ids[0] = *(int *)(state + 0x23C);
        break;
    }
    range = 1025.0f;
    best = 0;
    for (i = 0; i < list_count; i++) {
        u16 *record;

        for (record = (u16 *)g_group_l20_id_lists[group_ids[i]];
             (group_ids[i] & 0xFF) != 0xFF && g_group_count >= group_ids[i] && record != 0 &&
             (*(s16 *)(record - 1) >= 0 || record == (u16 *)g_group_l20_id_lists[group_ids[i]]);
             record++) {
            char *member = g_group_l20_member_table + ((*record & 0x7FFF) << 8);

            if (member == 0) {
                break;
            }
            if (!(*(u16 *)(member + 0x34) & 1)) {
                if (vec_distance_xy(member + 0x10, moby + 0x10) < range) {
                    best = member;
                }
            }
        }
    }
    return best;
}
