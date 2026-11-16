#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern int g_screen_flag_enabled __attribute__((nosda));
extern int g_text_color_table[8] __attribute__((sda));
extern int measure_text_width(u8 *, int, u8 *);
extern void FontPrintScaled_pal(float, float, u64, u8 *, int, float, u64, u8 *);
extern int g_current_game_mode __attribute__((section(".sdata")));
extern int g_text_flag_enabled __attribute__((sda));
extern int g_screen_width __attribute__((nosda));
extern int g_screen_height __attribute__((nosda));
extern void gfx_set_scissor_clamped(int, int, int, int);

struct FontWindow {
    short y_min, y_max, x_min, x_max, x_anchor, y_start;
    short out_w, out_h, line_h;
    unsigned short flags;
    short x_sub, y_sub;
};

/* func_PAL_002804A8, the PAL copy of func_0027FC70 (FontPrintWindow, adapted from RAC1 draw.c,
 * GPL-3.0) with a scale, longer line tables and a flag that keeps the clip window. */
void FontPrintWindow_pal(unsigned short *window_ptr, u64 color, u8 *text_ptr, int length, u64 texture, u8 *glyphs, float scale)
{
    struct FontWindow *window = (struct FontWindow *)window_ptr;
    unsigned char *text = (unsigned char *)text_ptr;
    short line_start[80];
    short line_end[80];
    short line_color[80];
    int line_width, saved_width, line, i, break_pos, width, color_index, first_line_count, last_width, balanced;
    int line_index, y, advance;

    if (g_current_game_mode != 1 && !(window->flags & 0x10))
        gfx_set_scissor_clamped(window->x_min, window->x_max - 1, window->y_min, window->y_max - 1);
    g_text_flag_enabled = 1;
    if ((window->flags ^ 1) & 1) {
        line_width = window->x_max - window->x_anchor;
    } else {
        int anchor = window->x_anchor;
        int half_right = window->x_max - anchor;
        line_width = anchor - window->x_min;
        if (half_right < line_width)
            line_width = half_right;
        line_width = line_width * 2;
    }
    saved_width = line_width;
    color_index = 0;
    balanced = 0;
    first_line_count = 0;
    last_width = 0;

    for (;;) {
        line = 0;
        i = 0;
        while (i != length && text[i] != 0 && line < 79) {
            line_start[line] = i;
            line_color[line] = color_index;
            width = 0;
            break_pos = i;
            while (width < line_width) {
                if (text[i] == 0x20 || text[i] < 0x10)
                    break_pos = i;
                if (g_screen_flag_enabled != 0 && (unsigned char)(text[i] - 8) < 8)
                    color_index = text[i] - 8;
                if (text[i] < 2)
                    break;
                advance = ((signed char *)glyphs)[text[i] * 4 + 3];
                i++;
                if (advance != 0)
                    width += advance;
            }
            line_end[line] = break_pos;
            if ((short)break_pos == line_start[line])
                line_end[line] = i;
            i = line_end[line];
            if (text[i] == 0x20 || text[i] < 0x10)
                line_end[line] = line_end[line] - 1;
            line++;
            if (text[i] == 0) {
                last_width = width;
                break;
            }
            i++;
        }
        if (!balanced && line >= 2) {
            if (first_line_count == 0)
                first_line_count = line;
            if (first_line_count < line) {
                line_width = saved_width;
                balanced = 1;
                continue;
            }
            if (last_width < line_width / 3) {
                line_width -= 16;
                continue;
            }
        }
        break;
    }

    {
        struct FontWindow *block = window;
        int char_count, text_width;
        block->out_w = 0;
        y = block->y_start;
        block->out_h = line * block->line_h;
        if (block->flags & 2)
            y -= (line * block->line_h) >> 1;
        for (line_index = 0; line_index < line; line_index++, y += block->line_h) {
            if (y + block->line_h < block->y_min)
                continue;
            if (block->y_max < y)
                continue;
            char_count = line_end[line_index] - line_start[line_index] + 1;
            if (length > 0 && char_count > length)
                char_count = length;
            text_width = measure_text_width(text + line_start[line_index], char_count, glyphs);
            if (block->out_w < text_width)
                block->out_w = text_width;
            if (!(block->flags & 4)) {
                g_text_color_table[0] = color;
                if (block->flags & 8) {
                    float fx;
                    if (block->flags & 1)
                        fx = (block->x_anchor - (text_width >> 1)) + block->x_sub * 0.0625f;
                    else
                        fx = block->x_anchor + block->x_sub * 0.0625f;
                    FontPrintScaled_pal(fx, y + block->y_sub * 0.0625f, (long)g_text_color_table[line_color[line_index]],
                                      text + line_start[line_index], char_count, scale, texture, glyphs);
                } else if (block->flags & 1) {
                    FontPrintScaled_pal(block->x_anchor - (text_width >> 1), y, (long)g_text_color_table[line_color[line_index]],
                                      text + line_start[line_index], char_count, scale, texture, glyphs);
                } else {
                    FontPrintScaled_pal(block->x_anchor, y, (long)g_text_color_table[line_color[line_index]],
                                      text + line_start[line_index], char_count, scale, texture, glyphs);
                }
            }
            if (length > 0) {
                length -= char_count;
                if (length <= 0)
                    break;
            }
        }
    }
    g_text_flag_enabled = 0;
    if (g_current_game_mode != 1 && !(window->flags & 0x10))
        gfx_set_scissor_clamped(0, g_screen_width - 1, 0, g_screen_height - 1);
}
