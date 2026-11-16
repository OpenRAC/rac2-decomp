#include "include_asm.h"
#include "common.h"

extern char g_barrel_entry_groups[];
extern void level_init_pending_slot(u8 *, char *);
extern void level_append_record_to_table(char *, s32, s32, float);
extern void moby_update_transform_history_followers(char *, s32);
extern void level_release_slot_list(char *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 cam_moby_update(u8 *);
extern void moby_mark_spawned(void *);

/* Fading effect: sets up its entry group, lets it linger, then fades it out in steps of two and removes it (PAL). */
void fading_effect_update_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    char *group_table;
    s32 n;
    s32 index;
    s32 k;

    switch (moby[0x20]) {
    case 0:
        index = *(s16 *)(state + 0x36);
        n = 0x150;
        group_table = g_barrel_entry_groups;
        level_init_pending_slot(moby, &group_table[index * n]);
        level_append_record_to_table(&group_table[*(s16 *)(state + 0x36) * n], 0x28, 2, 0.0f);
        level_append_record_to_table(&group_table[*(s16 *)(state + 0x36) * n], 0x14, 4, 0.0f);
        level_append_record_to_table(&group_table[*(s16 *)(state + 0x36) * n], 0xA, 6, 0.0f);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        k = 0x150;
        group_table = &g_barrel_entry_groups[*(s16 *)(state + 0x36) * k];
        moby_update_transform_history_followers(group_table, 0);
        n = cam_moby_update(moby);
        if (n != 0) {
            moby_set_state(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x2800;
        }
        break;
    case 2:
        cam_moby_update(moby);
        group_table = &g_barrel_entry_groups[*(s16 *)(state + 0x36) * 0x150];
        level_release_slot_list(group_table);
        if (moby[0x23] < 2) {
            moby_mark_spawned(moby);
        } else {
            moby[0x23] -= 2;
        }
        break;
    }
}
