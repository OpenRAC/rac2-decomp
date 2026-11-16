#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern int g_screen_flag_enabled __attribute__((nosda));
extern int g_text_color_table[8] __attribute__((sda));
extern int measure_text_width(u8 *, int, u8 *);
extern void text_draw_scaled_us2(float, float, u64, u8 *, int, float, u64, u8 *);
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

/* func_US2_00280550, the v2.00 scaled FontPrintWindow; adapted from RAC1 draw.c
 * FontPrintWindow (GPL-3.0). It is func_0027FC70 with a scale passed to the text
 * printer, 80 lines instead of 32, a colour code read at the wrap point, and
 * window flag 0x10 to skip both func_002FC620 calls. */
void FontPrintWindow_us2(unsigned short *window_arg, u64 color, u8 *text_arg, int len, u64 shadow, u8 *glyphs, float scale)
{
    struct FontWindow *win = (struct FontWindow *)window_arg;
    unsigned char *text = (unsigned char *)text_arg;
    short line_start[80];
    short line_end[80];
    short line_colors[80];
    int wrap_width, balanced, wrap_width_saved, line, i, break_pos, width, color_index, first_pass_lines, last_width;
    int row, y, advance;

    if (g_current_game_mode != 1 && !(win->flags & 0x10))
        gfx_set_scissor_clamped(win->x_min, win->x_max - 1, win->y_min, win->y_max - 1);
    g_text_flag_enabled = 1;
    if ((win->flags ^ 1) & 1) {
        wrap_width = win->x_max - win->x_anchor;
    } else {
        int anchor_left = win->x_anchor;
        int right_space = win->x_max - anchor_left;
        wrap_width = anchor_left - win->x_min;
        if (right_space < wrap_width)
            wrap_width = right_space;
        wrap_width = wrap_width * 2;
    }
    balanced = 0;
    color_index = 0;
    wrap_width_saved = wrap_width;
    first_pass_lines = 0;
    last_width = 0;

    for (;;) {
        line = 0;
        i = 0;
        while (i != len && text[i] != 0 && line < 79) {
            line_start[line] = i;
            line_colors[line] = color_index;
            width = 0;
            break_pos = i;
            while (width < wrap_width) {
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
            if (g_screen_flag_enabled != 0 && width >= wrap_width) {
                if (text[i] >= 8) {
                    if (text[i] < 0x10)
                        color_index = text[i] - 8;
                }
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
            if (first_pass_lines == 0)
                first_pass_lines = line;
            if (first_pass_lines < line) {
                wrap_width = wrap_width_saved;
                balanced = 1;
                continue;
            }
            if (last_width < wrap_width / 3) {
                wrap_width -= 16;
                continue;
            }
        }
        break;
    }

    {
        struct FontWindow *win_ref = win;
        int char_count, line_width;
        win_ref->out_w = 0;
        y = win_ref->y_start;
        win_ref->out_h = line * win_ref->line_h;
        if (win_ref->flags & 2)
            y -= (line * win_ref->line_h) >> 1;
        for (row = 0; row < line; row++, y += win_ref->line_h) {
            if (y + win_ref->line_h < win_ref->y_min)
                continue;
            if (win_ref->y_max < y)
                continue;
            char_count = line_end[row] - line_start[row] + 1;
            if (len > 0 && char_count > len)
                char_count = len;
            line_width = measure_text_width(text + line_start[row], char_count, glyphs);
            if (win_ref->out_w < line_width)
                win_ref->out_w = line_width;
            if (!(win_ref->flags & 4)) {
                g_text_color_table[0] = color;
                if (win_ref->flags & 8) {
                    float fx;
                    if (win_ref->flags & 1)
                        fx = (win_ref->x_anchor - (line_width >> 1)) + win_ref->x_sub * 0.0625f;
                    else
                        fx = win_ref->x_anchor + win_ref->x_sub * 0.0625f;
                    text_draw_scaled_us2(fx, y + win_ref->y_sub * 0.0625f, (long)g_text_color_table[line_colors[row]],
                                      text + line_start[row], char_count, scale, shadow, glyphs);
                } else if (win_ref->flags & 1) {
                    text_draw_scaled_us2(win_ref->x_anchor - (line_width >> 1), y, (long)g_text_color_table[line_colors[row]],
                                      text + line_start[row], char_count, scale, shadow, glyphs);
                } else {
                    text_draw_scaled_us2(win_ref->x_anchor, y, (long)g_text_color_table[line_colors[row]],
                                      text + line_start[row], char_count, scale, shadow, glyphs);
                }
            }
            if (len > 0) {
                len -= char_count;
                if (len <= 0)
                    break;
            }
        }
    }
    g_text_flag_enabled = 0;
    if (g_current_game_mode != 1 && !(win->flags & 0x10))
        gfx_set_scissor_clamped(0, g_screen_width - 1, 0, g_screen_height - 1);
}
