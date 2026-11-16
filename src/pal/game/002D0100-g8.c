#include "include_asm.h"
#include "names.h"
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *g_resident_data_base;
extern SelectionCallback g_pause_menu_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern CallbackMenuState g_pad_state;
extern int func_0029C560(int);
extern char *tab_menu_get_selected_entry(void *);
extern void menu_start_action(int);

/* Handles input on the pause menu list: starts the selected entry's action on confirm, closes or refuses on cancel, and plays the refuse sound for an entry with no value. (PAL copy) */
int menu_handle_input_send_selection_or_refuse_pal(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        int status;
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
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && g_resident_data_base != 0) {
            char *data = tab_menu_get_selected_entry(g_resident_data_base + 0x3C210);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            if (message.value == 0)
                snd_play_from_global_bank(5, 0, 0);
            menu_start_action((int)&message);
        }
    }
    return result;
}
