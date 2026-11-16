#include "include_asm.h"
#include "common.h"
extern s8 *g_active_menu_object;
extern s8 g_menu_source_entries[];
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern int text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);

/* Shows a message in the middle of the screen. With no item chosen it shows one line, otherwise two lines for the chosen item. */
s32 menu_entry_message_draw_us2(s8 *menu) {
    s8 *page;
    s32 item_index;

    page = (*(s8 **)((s8 *)(g_active_menu_object) + (0xE8)));
    item_index = (*(s32 *)((s8 *)((*(s8 **)((s8 *)(page) + (0x34))) + (*(s32 *)((s8 *)(page) + (0x40))) * 12) + (4)));
    SetupGifPaging(0);
    if (item_index == -1) {
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 2 - 8, 0x80FFA888ULL, GetLocalizedString(0x2CFB), -1);
    } else {
        s32 entry_offset = item_index * 12;
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(g_menu_source_entries + entry_offset) + (0)))), -1);
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) * 2 / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(g_menu_source_entries + entry_offset) + (4)))), -1);
    }
    DoGifPaging();
    return 2;
}
