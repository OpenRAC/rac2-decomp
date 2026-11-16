#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *g_resident_data_base;
extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int level_l00_call_module_handler_with_arg_5_pal(int);
extern char *list_menu_get_selected_record_pal(void *);
extern void menu_start_action_pal(int);
extern int ref_PAL_L00_00350F30_00(int);

/* Menu selection callback: handles the pad flags and sends the selected record's key and value
   as a message when the confirm bit is set. */
int list_menu_selection_callback_pal(void)
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
    if (flags & 0x900) {
        result = 1;
    } else {
        ref_PAL_L00_00350F30_00(flags);
        if ((state->flags & 0x40) && g_resident_data_base != 0) {
            char *data = list_menu_get_selected_record_pal(g_resident_data_base + 0x3E810);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            menu_start_action_pal((int)&message);
        }
    }
    return result;
}
