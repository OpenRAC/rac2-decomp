#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int,int,u64,char *,int);
extern int text_draw_centered_medium(int,int,u64,char *,int);
extern int func_001157AC(char *);
extern int text_measure_width_medium(char *,int);
extern void menu_draw_text_highlight_frame(int,int);
extern void menu_draw_scroll_arrows_and_frame(void);
extern char *g_resident_data_base;
extern int g_screen_width;
extern float g_menu_alpha_scale;
extern int g_eight_entry_cursor __attribute__((sda));
extern int g_entry_list_title_y __attribute__((sda));
extern unsigned char g_special_item_collected_flags[8] __attribute__((sda));
extern short g_entry_list_text_ids[] MACRO_ADDR;

/* Draws a list of eight entries, five rows around the cursor; entries not collected show a placeholder. */
int menu_entry_list_draw_pal(void) {
    int i, y, index, color;
    int sprite;
    char *text;
    float depth;
    SetupGifPaging(0);
    depth = 0.0f;
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xD7);
    gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (float)(g_screen_width / 2), (float)g_entry_list_title_y, 1.0f, g_menu_alpha_scale, depth);
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xD8);
    gfx_draw_scaled_object_two_axes(sprite, 0x60241700, (float)(g_screen_width / 2), (float)g_entry_list_title_y, 1.0f, g_menu_alpha_scale, depth);
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xD9);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (float)(g_screen_width / 2), (float)g_entry_list_title_y, 1.0f, g_menu_alpha_scale, depth);
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xDD);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (float)(g_screen_width / 2), (float)g_entry_list_title_y, 1.0f, g_menu_alpha_scale, depth);
    text_draw_centered_small(0xB3, 0x1B, 0x80F0F0F0ULL, GetLocalizedString(0x1114), -1);
    text_draw_centered_small(0x161, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    text_draw_centered_small(0xB5, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0xB86), -1);
    menu_draw_scroll_arrows_and_frame();
    for (i = 0, y = 0x112; i < 5; i++, y += 20) {
        index = i + g_eight_entry_cursor - 2;
        if (index < 0) index += 8;
        if (index >= 8) index -= 8;
        text = GetLocalizedString(g_special_item_collected_flags[index] ? g_entry_list_text_ids[index] : 0xBD1);
        if (i == 0 || i == 4) color = 0x10F0F0F0;
        else if (i == 1 || i == 3) color = 0x50F0F0F0;
        else {
            color = 0x70F0F0F0;
            menu_draw_text_highlight_frame(text_measure_width_medium(text, func_001157AC(text)), 0x70F0F0F0);
        }
        text_draw_centered_medium(g_screen_width / 2, y, color, text, -1);
    }
    DoGifPaging();
    return 0;
}
