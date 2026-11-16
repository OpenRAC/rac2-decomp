#include "include_asm.h"

#include "common.h"
extern s8 g_tab_menu_values[];

/* Returns the value of the selected entry of the current tab, or 0 for the third tab when its option is locked (PAL). */
s32 tab_menu_get_selected_value_pal(s32 self) {
    s32 tab;
    s32 value;
    s32 tab_ptr;

    tab = (*(s32 *)((s8 *)(self) + (0x31C)));
    tab_ptr = self + (tab * 4);
    value = *(s32 *)(((s32)g_tab_menu_values) + (s32) (((*(s32 *)((s8 *)(tab_ptr) + (0x1B8))) * 4) + (tab << 5)));
    if ((tab == 2) && (*(u8 *)0x1A7A92 == 0)) {
        value = ((*(s32 *)((s8 *)(self) + (0x1C0))) >= 3) ? 0 : value;
    }
    return value;
}
