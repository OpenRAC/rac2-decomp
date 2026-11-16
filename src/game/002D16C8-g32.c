#include "include_asm.h"
#include "names.h"

/* func_002D16C8 needs 20-byte menu table in small data (-G32) and quadword copy (-frac2-qcopy). */

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef int TI128 __attribute__((mode(TI)));

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void select_moby_context(int);
extern char *CreateMoby(int);
extern int g_extras_menu_cursor __attribute__((sda));
extern int g_extras_menu_enabled_flags[5] __attribute__((sda));
extern short g_sequence_active_flag[];
extern char g_hero_position[];
extern int g_extras_list_value_a[], g_extras_list_value_b[], g_extras_list_value_c[];
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern MenuFields g_extras_list_fields;
extern FlagTarget *g_extras_list_flag_targets[];

/* Handles input on the five-entry Extras page: opens a sub-page or spawns a special object for the chosen entry. */
int extras_menu_handle_input(void)
{
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int oldCursor = g_extras_menu_cursor;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int returnCode;
        g_extras_menu_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            returnCode = -1;
            goto finish;
        }
        returnCode = 0;
finish:
        return returnCode;
    }
    if (flags & 0x900) {
        g_extras_menu_cursor = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--g_extras_menu_cursor < 0)
                g_extras_menu_cursor = 4;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++g_extras_menu_cursor >= 5)
                g_extras_menu_cursor = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (g_extras_menu_enabled_flags[g_extras_menu_cursor] != 0) {
                snd_play_from_global_bank(4, 0, 0);
                switch (g_extras_menu_cursor) {
                case 1:
                case 2: {
                    char *obj;
                    select_moby_context(0);
                    obj = CreateMoby(g_extras_menu_cursor == 2 ? 0x88D /* moby class 2189 */ : 0x1335 /* moby class 4917 */);
                    select_moby_context(1);
                    if (obj != 0) {
                        *(unsigned char *)(obj + 0x30) = 0xFF;
                        {
                            TI128 *dst = (TI128 *)(obj + 0x10);
                            TI128 *src = (TI128 *)g_hero_position;
                            *dst = *src;
                        }
                        result = 1;
                    }
                    break;
                }
                case 0:
                    g_pause_menu_state.value = (int)g_extras_list_value_a;
                    break;
                case 3:
                    g_pause_menu_state.value = (int)g_extras_list_value_b;
                    break;
                case 4:
                    g_pause_menu_state.value = (int)g_extras_list_value_c;
                    break;
                default:
                    break;
                }
            } else {
                snd_play_from_global_bank(5, 0, 0);
            }
        }
        {
            MenuFields *menu = &g_extras_list_fields;
            menu->f58 = g_extras_menu_cursor;
            if (g_extras_menu_enabled_flags[g_extras_menu_cursor] != 0) {
                if (oldCursor == g_extras_menu_cursor) {
                    if (g_sequence_active_flag[0] == 0) {
                        if (menu->f50 == oldCursor && menu->f44 == 2) {
                            g_extras_list_flag_targets[0]->flags &= -5;
                        } else if (menu->f54 == oldCursor && menu->f44 == 4) {
                            g_extras_list_flag_targets[0]->flags &= -5;
                        }
                    }
                }
            } else {
                g_extras_list_flag_targets[0]->flags |= 4;
            }
        }
    }
    return result;
}
