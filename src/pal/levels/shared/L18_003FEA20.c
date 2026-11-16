#include "include_asm.h"

#include "common.h"
extern void *memset(void *, int, unsigned int);
extern float g_hero_position[4];
extern float vec_distance_squared_xy(void *, void *);
extern int moby_is_state_two(unsigned char *);
extern int moby_enter_hit_state_pal(unsigned char *, int);
extern unsigned short *g_condition_target_lists[];
extern char *g_moby_l18_table[] __attribute__((sda));
extern int g_max_l18_group_index[] __attribute__((sda));
/* Each scan reads the current slot id again when advancing its group iterator. */
static __inline__ int L18_SelectionGroupId(char *p, int i, int base) {
    int off = i << 2;
    int *groups = (int *)(p + base);
    return *(int *)((char *)groups + off);
}

/* Selects the source, secondary member and target from the owner's three group
   lists. The first target scan prefers entries passing the flag and distance tests. */
int SelectGroupMembersAndTarget_pal(char *owner, int slot) {
    char *secondary[2];
    char *state = *(char **)(owner + 0x68);
    char *source = 0;
    char *selected = 0;
    char *entity;
    int i;

    memset(secondary, 0, 8);
    {
        unsigned short *entry;
        for (entry = g_condition_target_lists[L18_SelectionGroupId(state, slot, 0)];
             (L18_SelectionGroupId(state, slot, 0) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0) <= g_max_l18_group_index[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == g_condition_target_lists[L18_SelectionGroupId(state, slot, 0)]); entry++) {
            entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (entity != 0 && *(unsigned char *)(entity + 0x20) != 0xfe &&
                *(unsigned char *)(entity + 0x20) != 0xfd &&
                (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                source = entity;
                break;
            }
        }
    }
    if (source == 0) return 0;
    for (i = 0; i < 1; i++) {
        {
            unsigned short *entry;
            for (entry = g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x20)];
                 (L18_SelectionGroupId(state, slot, 0x20) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x20) <= g_max_l18_group_index[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x20)]); entry++) {
                entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (entity != secondary[0] && entity != 0 &&
                    *(unsigned char *)(entity + 0x20) != 0xfe &&
                    *(unsigned char *)(entity + 0x20) != 0xfd &&
                    (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                    secondary[i] = entity;
                    break;
                }
            }
        }
    }
    if (secondary[0] == 0) return 0;
    {
        unsigned short *entry;
        for (entity = 0, entry = g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x10)];
             (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0x10) <= g_max_l18_group_index[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
            entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (*(unsigned char *)(entity + 0x31) != 0 &&
                vec_distance_squared_xy(g_hero_position, entity + 0x10) > 16.0f &&
                moby_is_state_two((unsigned char *)entity) == 0) {
                selected = entity;
                break;
            }
        }
    }
    if (selected == 0) {
        {
            unsigned short *entry;
            for (entity = 0, entry = g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x10)];
                 (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x10) <= g_max_l18_group_index[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == g_condition_target_lists[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
                entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (moby_is_state_two((unsigned char *)entity) == 0) {
                    selected = entity;
                    break;
                }
            }
        }
        if (selected == 0) goto fail;
    }
    protopet_setup_target_transforms(source, entity, (void *)L18_SelectionGroupId(state, slot, 0x10));
    protopet_attach_to_target((unsigned char *)secondary[0], (unsigned char *)source, 0);
    moby_enter_hit_state_pal((unsigned char *)selected, 1);
    return 1;
fail:
    return 0;
}

