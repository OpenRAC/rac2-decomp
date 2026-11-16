#include "include_asm.h"
#include "common.h"
extern s8 *g_active_menu_object;
extern s8 g_menu_source_entries[];
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern int text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);

/* Shows a message in the middle of the screen. With no item chosen it shows one line, otherwise two lines for the chosen item. */
s32 menu_entry_message_draw_pal(s8 *menu) {
    s8 *focus;
    s32 message_index;

    focus = (*(s8 **)((s8 *)(g_active_menu_object) + (0xE8)));
    message_index = (*(s32 *)((s8 *)((*(s8 **)((s8 *)(focus) + (0x34))) + (*(s32 *)((s8 *)(focus) + (0x40))) * 12) + (4)));
    SetupGifPaging(0);
    if (message_index == -1) {
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 2 - 8, 0x80FFA888ULL, GetLocalizedString(0xC75), -1);
    } else {
        s32 entry_offset = message_index * 12;
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(g_menu_source_entries + entry_offset) + (0)))), -1);
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) * 2 / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(g_menu_source_entries + entry_offset) + (4)))), -1);
    }
    DoGifPaging();
    return 2;
}
