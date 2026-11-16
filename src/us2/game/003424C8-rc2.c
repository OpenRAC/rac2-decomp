#include "include_asm.h"
#include "common.h"

/* Returns the address of the selected entry of the current tab (USA v2.00). */
s32 tab_menu_get_selected_entry_us2(s32 menu) {
    s32 tab;
    s32 table;
    s32 index;
    s32 tab_base;

    tab = (*(s32 *)((s8 *)(menu) + (0x31C)));
    if (tab == 0) {
        goto block_2;
    }
    goto block_5;
block_2:
    index = (*(s32 *)((s8 *)(menu) + (0x1B8)));
    table = (*(s32 *)((s8 *)(menu) + (0x310)));
block_4:
    return table + (index * 0x14);
block_5:
    if (tab != 1) {
        tab_base = menu + (tab * 4);
        return (*(s32 *)((s8 *)(menu) + (0x318))) + ((*(s32 *)((s8 *)(tab_base) + (0x1B8))) * 0x14);
    }
    table = (*(s32 *)((s8 *)(menu) + (0x314)));
    return table + (((*(s32 *)((s8 *)(menu) + (0x1BC)))) * 0x14);
block_7:
    return (*(s32 *)((s8 *)(menu) + (0x318))) + ((*(s32 *)((s8 *)((menu + (tab * 4))) + (0x1B8))) * 0x14);
}
