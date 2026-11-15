#include "names.h"
/* func_PAL_002D1488, the PAL copy of func_002D0568: the same C, with four slots in place
   of five, three rows from y 290 spaced 24 apart and the other text ids. */
#include "common.h"

extern char *D_001A8CFC;
extern int g_screen_width;
extern int D_001ABA1C __attribute__((sda));
extern int D_001ABA04 __attribute__((sda));
extern int D_001ABA08[] SDATA(D_001ABA08);
extern short D_001ABD00[] MACRO_ADDR;
extern float D_001B23A8;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern char *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern int func_001157AC(char *);
extern int text_measure_width_medium(char *, int);
extern void menu_draw_scroll_arrows_and_frame(void);
extern void menu_draw_text_highlight_frame(int, unsigned int);

int func_PAL_002D1488(void)
{
    int i, y = 290;
    float z;

    SetupGifPaging(0);
    z = 0.0f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xD7), 0x60442D00, (float)(g_screen_width / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xD8), 0x60241700, (float)(g_screen_width / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xD9), 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xDD), 0x55F0C070, (float)(g_screen_width / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    text_draw_centered_small(179, 27, 0x80F0F0F0UL, GetLocalizedString(0x1111), -1);
    text_draw_centered_small(353, 375, 0x80F0F0F0UL, GetLocalizedString(0xB60), -1);
    text_draw_centered_small(181, 375, 0x80F0F0F0UL, GetLocalizedString(0xB86), -1);
    menu_draw_scroll_arrows_and_frame();
    for (i = 0; i < 3; i++, y += 24) {
        int index = i + D_001ABA04 - 1, key;
        unsigned int color;
        char *text;

        if (index < 0)
            index += 4;
        if (index >= 4)
            index -= 4;
        key = D_001ABA08[index] ? D_001ABD00[index * 2] : 0xBD1;
        text = GetLocalizedString(key);
        if (i == 0 || i == 2)
            color = 0x30F0F0F0;
        else {
            color = 0x70F0F0F0;
            menu_draw_text_highlight_frame(text_measure_width_medium(text, func_001157AC(text)), 0x70F0F0F0);
        }
        text_draw_centered_medium(g_screen_width / 2, y, color, text, -1);
    }
    DoGifPaging();
    return 0;
}
