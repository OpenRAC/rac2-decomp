#include "include_asm.h"

#include "common.h"
extern s8 g_tab_menu_values[];

/* Returns the value of the selected entry of the current tab (USA v2.00). */
s32 tab_menu_get_selected_value_us2(s32 menu) {
    s32 tab;
    s32 value;
    s32 tab_base;

    tab = (*(s32 *)((s8 *)(menu) + (0x31C)));
    tab_base = menu + (tab * 4);
    value = *(s32 *)(((s32)g_tab_menu_values) + (s32) (((*(s32 *)((s8 *)(tab_base) + (0x1B8))) * 4) + (tab << 5)));
    if ((tab == 2) && (*(u8 *)0x1A7A12 == 0)) {
        value = ((*(s32 *)((s8 *)(menu) + (0x1C0))) >= 3) ? 0 : value;
    }
    return value;
}
