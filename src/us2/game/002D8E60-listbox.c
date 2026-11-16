#include "common.h"

typedef struct { short fields[12]; } MenuTextRectangle;
extern char *g_active_menu_object;
extern char g_font_glyphs_small[], g_font_glyphs_large[], g_font_glyphs_medium[];
extern unsigned char g_item_enabled_flags[] MACRO_ADDR, g_language MACRO_ADDR;
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern void *memset(void *, int, int);
extern unsigned long GetEffectTextureDescriptor(int);
extern char *GetLocalizedString(int);
extern void gfx_disable_screen_flag(void), gfx_enable_screen_flag(void), DoGifPaging(void);
extern void FontPrintWindow(short *, unsigned long, int, int, unsigned long, char *);
extern void DrawMenuCheckBox(int, int, int);
extern void gfx_draw_screen_line(int, int, int, int, int, int);


/* Draws a list of menu rows with the highlighted row in a different color. */
int menu_text_list_draw_highlight_us2(char *menu)
{
    MenuTextRectangle rectangle, initial;
    short *row;
    int height, texture = 1, line_height, spacing, top;
    int count, index, selected, enabled, text;
    int active = *(char **)(g_active_menu_object + 0xE8) == menu;
    char *font = g_font_glyphs_small;
    unsigned long texture_word;
    int colour;
    height = (*(int *)(menu + 0x30) & 0x40000) ? 16 : 12;
    if (*(int *)(menu + 0x30) & 4) {
        height = (*(int *)(menu + 0x30) & 0x40000) ? 18 : 14;
        font = g_font_glyphs_large; texture = 3;
    }
    if (*(int *)(menu + 0x30) & 8) {
        height = (*(int *)(menu + 0x30) & 0x40000) ? 14 : 10;
        font = g_font_glyphs_medium; texture = 2;
    }
    VU1_addGSregister(66, 68);
    line_height = height + 2;
    VU1_addGSregister(71, 0x2004B);
    SetupGifPaging(0);
    row = *(short **)(menu + 0x34);
    count = 0;
    while (row[0]) { row += 6; count++; }
    if (*(int *)(menu + 0x30) & 16) spacing = height + 3;
    else spacing = *(int *)(menu + 0x24) / (count + 1);
    top = spacing - height / 2 + *(int *)(menu + 0x1C);
    memset(&initial, 0, 24);
    initial.fields[0] = *(int *)(menu + 0x1C) + 4;
    initial.fields[2] = *(int *)(menu + 0x18);
    initial.fields[1] = (long)(*(int *)(menu + 0x1C) - 4) + *(int *)(menu + 0x24);
    initial.fields[3] = *(int *)(menu + 0x18) + *(int *)(menu + 0x20) - 2;
    initial.fields[5] = top - *(int *)(menu + 0x44);
    initial.fields[8] = line_height;
    rectangle = initial;
    texture_word = GetEffectTextureDescriptor(texture);
    for (index = 0; (*(short **)(menu + 0x34))[index * 6]; index++) {
        selected = active && *(int *)(menu + 0x40) == index;
        enabled = (*(short **)(menu + 0x34))[index * 6 + 1] != 0;
        if (*(int *)(menu + 0x30) & 2) colour = (int)0x80F0F0F0u;
        else if (selected) colour = enabled ? (int)0x8020FFFFu : (int)0x80006060u;
        else colour = enabled ? (int)0x80F0F0F0u : (int)0x80303030u;
        if (!(*(int *)(menu + 0x30) & 0x10000) && selected && rectangle.fields[5] < rectangle.fields[0])
            *(int *)(menu + 0x44) -= 4;
        text = GetLocalizedString((*(short **)(menu + 0x34))[index * 6]);
        rectangle.fields[4] = (*(int *)(menu + 0x30) & 0xA00) ? 32 : 4;
        if (*(int *)(menu + 0x30) & 0x400) {
            rectangle.fields[9] = 1;
            rectangle.fields[4] = *(int *)(menu + 0x20) >> 1;
        }
        if (selected) gfx_disable_screen_flag();
        FontPrintWindow(rectangle.fields, colour, text, -1, texture_word, font);
        if (selected) gfx_enable_screen_flag();
        if (*(int *)(menu + 0x30) & 0x200)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, g_item_enabled_flags[index] != 0);
        if (*(int *)(menu + 0x30) & 0x800)
            DrawMenuCheckBox(15, rectangle.fields[5] + 9, g_language == *(int *)(*(short **)(menu + 0x34) + index * 6 + 2));
        rectangle.fields[5] += rectangle.fields[7];
        if ((*(short **)(menu + 0x34))[index * 6 + 4]) {
            text = GetLocalizedString((*(short **)(menu + 0x34))[index * 6 + 4]);
            rectangle.fields[4] = 20;
            FontPrintWindow(rectangle.fields, colour, text, -1, texture_word, font);
            rectangle.fields[5] += spacing;
        }
        if (!(*(int *)(menu + 0x30) & 0x80000))
            rectangle.fields[5] += 8;
        if (!(*(int *)(menu + 0x30) & 0x10000) && selected) {
            int bottom = rectangle.fields[5] + rectangle.fields[7];
            if (bottom > rectangle.fields[1]) {
                if (*(int *)(menu + 0x30) & 0x8000)
                    *(int *)(menu + 0x44) += bottom - rectangle.fields[1];
                else *(int *)(menu + 0x44) += 4;
            }
        }
    }
    DoGifPaging();
    if (*(int *)(menu + 0x30) & 0x8000) {
        *(int *)(menu + 0x30) ^= 0x8000;
        return 1;
    }
    return 2;
}
