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
extern char *D_001A8CFC;
extern int g_screen_width;
extern float D_001B23A8;
extern int D_001ABA28 __attribute__((sda));
extern int D_001ABA38 __attribute__((sda));
extern unsigned char D_001ABA30[8] __attribute__((sda));
extern short D_001ABD18[] MACRO_ADDR;

/* Draws the list of eight entries with five rows around the cursor; locked ones show a placeholder. */
int menu_entry_list_draw(void) {
    int i, y, entry_index, color;
    int r;
    char *row_text;
    float z;
    SetupGifPaging(0);
    z = 0.0f;
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD7);
    gfx_draw_scaled_object_two_axes(r, 0x60442D00, (float)(g_screen_width / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD8);
    gfx_draw_scaled_object_two_axes(r, 0x60241700, (float)(g_screen_width / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xD9);
    gfx_draw_scaled_object_two_axes(r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xDD);
    gfx_draw_scaled_object_two_axes(r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA38, 1.0f, D_001B23A8, z);
    text_draw_centered_small(0xB3, 0x1B, 0x80F0F0F0ULL, GetLocalizedString(0x3202), -1);
    text_draw_centered_small(0x161, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0x2D4F), -1);
    text_draw_centered_small(0xB5, 0x177, 0x80F0F0F0ULL, GetLocalizedString(0x2D75), -1);
    menu_draw_scroll_arrows_and_frame();
    for (i = 0, y = 0x112; i < 5; i++, y += 20) {
        entry_index = i + D_001ABA28 - 2;
        if (entry_index < 0) entry_index += 8;
        if (entry_index >= 8) entry_index -= 8;
        row_text = GetLocalizedString(D_001ABA30[entry_index] ? D_001ABD18[entry_index] : 0x2DC0);
        if (i == 0 || i == 4) color = 0x10F0F0F0;
        else if (i == 1 || i == 3) color = 0x50F0F0F0;
        else {
            color = 0x70F0F0F0;
            menu_draw_text_highlight_frame(text_measure_width_medium(row_text, func_001157AC(row_text)), 0x70F0F0F0);
        }
        text_draw_centered_medium(g_screen_width / 2, y, color, row_text, -1);
    }
    DoGifPaging();
    return 0;
}
