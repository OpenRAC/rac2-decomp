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
extern int func_0029C6B0(int);

/* Menu input handler: confirm keeps the selection, back or cancel closes the menu, anything else goes to the page helper. */
int menu_handle_page_input_us2(void) {
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
        func_0029C6B0(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void func_0029C680(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);

/* Draws a menu page through the paging helper. */
int menu_page_draw_us2(void)
{
    SetupGifPaging(0);
    func_0029C680();
    DoGifPaging();
    return 0;
}

