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
extern int g_menu_input_flags;
extern int menu_update_screen_adjust_pal(int);

/* Handles input for a menu page: confirms the selection, closes on a button press, otherwise passes the buttons on (PAL). */
int menu_page_update_send_request_pal(void) {
    int result = 0;
    int flags = g_menu_input_flags;
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
    else
        menu_update_screen_adjust_pal(flags);
    return result;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void menu_draw_screen_adjust_pal(void);
extern void DoGifPaging(void);

/* Draws a menu page between the start and end of screen drawing (PAL). */
int menu_page_draw_7_pal(void)
{
  SetupGifPaging(0);
  menu_draw_screen_adjust_pal();
  DoGifPaging();
  return 0;
}

