#include "include_asm.h"
#include "names.h"

/* func_US2_002D1F28, the v2.00 copy of func_002D0FA0: the same C, where entry 7 also sets D_001A7904 and
 * saves D_001A79F0 in a word v2.00 added, unless it is already 21. */

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);

extern int g_eight_entry_cursor __attribute__((sda));
extern unsigned char g_special_item_collected_flags[8] __attribute__((sda));
extern int g_arena_state_flag __attribute__((sda));
extern int g_saved_map_index;
extern int g_current_map_index;
extern short g_sequence_active_flag[];
extern void data_set_small_value_and_refresh(int, int);

typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern FlagTarget *g_eight_entry_flag_targets[];
extern MenuFields g_eight_entry_menu_fields;
extern int D_0026CD20[];

int menu_handle_eight_entry_input_us2(void)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old = g_eight_entry_cursor;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int status;
        g_eight_entry_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        g_eight_entry_cursor = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--g_eight_entry_cursor < 0)
                g_eight_entry_cursor = 7;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++g_eight_entry_cursor >= 8)
                g_eight_entry_cursor = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (g_special_item_collected_flags[g_eight_entry_cursor] != 0) {
                snd_play_from_global_bank(4, 0, 0);
                if ((unsigned)g_eight_entry_cursor < 8)
                    goto *D_0026CD20[g_eight_entry_cursor];
                goto cont;
c0:            g_arena_state_flag = 2; data_set_small_value_and_refresh(2, 1); goto cont;
c1:            g_arena_state_flag = 3; data_set_small_value_and_refresh(4, 1); goto cont;
c2:            g_arena_state_flag = 3; data_set_small_value_and_refresh(11, 1); goto cont;
c3:            g_arena_state_flag = 2; data_set_small_value_and_refresh(11, 1); goto cont;
c4:            g_arena_state_flag = 1; data_set_small_value_and_refresh(26, 1); goto cont;
c5:            g_arena_state_flag = 1; data_set_small_value_and_refresh(22, 1); goto cont;
c6:            g_arena_state_flag = 1; data_set_small_value_and_refresh(23, 1); goto cont;
c7:            g_arena_state_flag = 1; if (g_current_map_index != 21) g_saved_map_index = g_current_map_index; data_set_small_value_and_refresh(21, 1); goto cont;
            } else {
                snd_play_from_global_bank(5, 0, 0);
            }
        }
cont:
        {
            MenuFields *menu = &g_eight_entry_menu_fields;
            menu->f58 = g_eight_entry_cursor;
            if (g_special_item_collected_flags[g_eight_entry_cursor] != 0) {
                if (old == g_eight_entry_cursor) {
                    if (g_sequence_active_flag[0] == 0) {
                        if (menu->f50 == old && menu->f44 == 2) {
                            g_eight_entry_flag_targets[0]->flags &= -5;
                        } else if (menu->f54 == old && menu->f44 == 4) {
                            g_eight_entry_flag_targets[0]->flags &= -5;
                        }
                    }
                }
            } else {
                g_eight_entry_flag_targets[0]->flags |= 4;
            }
        }
    }
    return result;
}
