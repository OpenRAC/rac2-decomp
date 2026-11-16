/* func_002CFBE8 in its own unit, a sibling of func_002D0930: the cursor goes through $gp, so the
   file is compiled at -G32 (config/cflags.txt). The unlock table's address is built by one
   lui/addiu pair in one register, the assembler's la macro, so it is declared MACRO_ADDR. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
typedef struct { short f0; short text; short f4; } TextEntry;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int g_skill_points_cursor __attribute__((sda));
extern short g_sequence_active_flag[];
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
extern MenuFields g_skill_menu_fields;
extern FlagTarget *g_skill_menu_flag_targets[];
extern int g_skill_menu_text_slot[];
extern TextEntry g_skill_text_entries[];

/* Handles input on the skill points list: moves the cursor through the 30 entries and shows the earned entry text. */
int menu_handle_skill_points_list_input(void)
{
    int result = 0;
    int flags = g_pad_state.flags;
    int old_cursor = g_skill_points_cursor;

    if (flags & 0x10) {
        int value;
        int return_code;
        g_skill_points_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            return_code = -1;
            goto finish;
        }
        return_code = 0;
finish:
        return return_code;
    }
    if (flags & 0x900) {
        g_skill_points_cursor = 0;
        result = 1;
    } else if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        if (--g_skill_points_cursor < 0)
            g_skill_points_cursor = 29;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        if (++g_skill_points_cursor >= 30)
            g_skill_points_cursor = 0;
    }
    {
        MenuFields *menu = &g_skill_menu_fields;
        menu->f58 = g_skill_points_cursor;
        if (g_item_enabled_flags[g_skill_points_cursor] != 0) {
            if (old_cursor == g_skill_points_cursor) {
                if (g_sequence_active_flag[0] == 0) {
                    if (menu->f50 == old_cursor && menu->f44 == 2) {
                        g_skill_menu_flag_targets[0]->flags &= -5;
                    } else if (menu->f54 == old_cursor && menu->f44 == 4) {
                        g_skill_menu_flag_targets[0]->flags &= -5;
                    }
                }
            }
            g_skill_menu_text_slot[0] = g_skill_text_entries[g_skill_points_cursor].text;
        } else {
            g_skill_menu_flag_targets[0]->flags |= 4;
            g_skill_menu_text_slot[0] = 0;
        }
    }
    return result;
}
