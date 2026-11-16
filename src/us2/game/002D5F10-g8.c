#include "include_asm.h"
#include "names.h"
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
typedef struct { char reserved00[0x1C4]; int flags; } MenuGameState;
typedef struct { short reserved00, key; int value; } MenuMessage;
extern MenuGameState g_pad_state;
extern CallbackState g_pause_menu_state;
extern char *g_resident_data_base[] __attribute__((sda));
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern void menu_clear_counter(void);
extern void data_set_small_value_and_refresh(int, int);
extern int func_0029C560(int);
extern char *tab_menu_get_selected_entry(void *);
extern void menu_start_action(int);

int menu_popup_update_us2(void)
{
    MenuMessage message;
    int result = 0;
    MenuGameState *state;
    int flags;
    if (menu_get_counter() == 2 && menu_get_mode() == 9) {
        menu_clear_counter();
        data_set_small_value_and_refresh(-1, 0);
        return 1;
    }
    menu_clear_counter();
    state = &g_pad_state;
    flags = state->flags;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && g_resident_data_base[0] != 0) {
            char *data = tab_menu_get_selected_entry(g_resident_data_base[0] + 0x3C160);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            menu_start_action((int)&message);
        }
    }
    return result;
}
