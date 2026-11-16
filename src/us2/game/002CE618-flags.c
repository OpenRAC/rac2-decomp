#include "include_asm.h"
#include "names.h"
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int g_menu_input_flags;
extern void weapon_menu_sync_slots(void);
extern int func_0029CBE0(int);

int menu_handle_input_with_fallback_us2(void) {
    int result = 0;
    int flags = g_menu_input_flags;
    if (flags & 0x10) {
        int value;
        weapon_menu_sync_slots();
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            result = -1;
            goto done;
        }
        result = 0;
done:
        ;
    } else if (flags & 0x900) {
        weapon_menu_sync_slots();
        result = 1;
    } else {
        func_0029CBE0(flags);
    }
    return result;
}
