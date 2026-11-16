#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern int g_screen_flag_enabled __attribute__((nosda));
extern int g_text_color_table[8] __attribute__((sda));
extern int measure_text_width(u8 *, int, u8 *);
extern void func_PAL_0027FB48(float, float, u64, u8 *, int, float, u64, u8 *);
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
void func_PAL_002804A8(unsigned short *win_p, u64 a1, u8 *text_p, int len, u64 a4, u8 *glyphs, float scale)
{
    struct FontWindow *win = (struct FontWindow *)win_p;
    unsigned char *text = (unsigned char *)text_p;
    short start[80];
    short endi[80];
    short colr_arr[80];
    int W, Wsave, line, i, brk, width, colr, n0, last, balanced;
    int k, y, adv;

    if (g_current_game_mode != 1 && !(win->flags & 0x10))
        gfx_set_scissor_clamped(win->x_min, win->x_max - 1, win->y_min, win->y_max - 1);
    g_text_flag_enabled = 1;
    if ((win->flags ^ 1) & 1) {
        W = win->x_max - win->x_anchor;
    } else {
        int l = win->x_anchor;
        int a = win->x_max - l;
        W = l - win->x_min;
        if (a < W)
            W = a;
        W = W * 2;
    }
    Wsave = W;
    colr = 0;
    balanced = 0;
    n0 = 0;
    last = 0;

    for (;;) {
        line = 0;
        i = 0;
        while (i != len && text[i] != 0 && line < 79) {
            start[line] = i;
            colr_arr[line] = colr;
            width = 0;
            brk = i;
            while (width < W) {
                if (text[i] == 0x20 || text[i] < 0x10)
                    brk = i;
                if (g_screen_flag_enabled != 0 && (unsigned char)(text[i] - 8) < 8)
                    colr = text[i] - 8;
                if (text[i] < 2)
                    break;
                adv = ((signed char *)glyphs)[text[i] * 4 + 3];
                i++;
                if (adv != 0)
                    width += adv;
            }
            endi[line] = brk;
            if ((short)brk == start[line])
                endi[line] = i;
            i = endi[line];
            if (text[i] == 0x20 || text[i] < 0x10)
                endi[line] = endi[line] - 1;
            line++;
            if (text[i] == 0) {
                last = width;
                break;
            }
            i++;
        }
        if (!balanced && line >= 2) {
            if (n0 == 0)
                n0 = line;
            if (n0 < line) {
                W = Wsave;
                balanced = 1;
                continue;
            }
            if (last < W / 3) {
                W -= 16;
                continue;
            }
        }
        break;
    }

    {
        struct FontWindow *dw = win;
        int cnt, w;
        dw->out_w = 0;
        y = dw->y_start;
        dw->out_h = line * dw->line_h;
        if (dw->flags & 2)
            y -= (line * dw->line_h) >> 1;
        for (k = 0; k < line; k++, y += dw->line_h) {
            if (y + dw->line_h < dw->y_min)
                continue;
            if (dw->y_max < y)
                continue;
            cnt = endi[k] - start[k] + 1;
            if (len > 0 && cnt > len)
                cnt = len;
            w = measure_text_width(text + start[k], cnt, glyphs);
            if (dw->out_w < w)
                dw->out_w = w;
            if (!(dw->flags & 4)) {
                g_text_color_table[0] = a1;
                if (dw->flags & 8) {
                    float fx;
                    if (dw->flags & 1)
                        fx = (dw->x_anchor - (w >> 1)) + dw->x_sub * 0.0625f;
                    else
                        fx = dw->x_anchor + dw->x_sub * 0.0625f;
                    func_PAL_0027FB48(fx, y + dw->y_sub * 0.0625f, (long)g_text_color_table[colr_arr[k]],
                                      text + start[k], cnt, scale, a4, glyphs);
                } else if (dw->flags & 1) {
                    func_PAL_0027FB48(dw->x_anchor - (w >> 1), y, (long)g_text_color_table[colr_arr[k]],
                                      text + start[k], cnt, scale, a4, glyphs);
                } else {
                    func_PAL_0027FB48(dw->x_anchor, y, (long)g_text_color_table[colr_arr[k]],
                                      text + start[k], cnt, scale, a4, glyphs);
                }
            }
            if (len > 0) {
                len -= cnt;
                if (len <= 0)
                    break;
            }
        }
    }
    g_text_flag_enabled = 0;
    if (g_current_game_mode != 1 && !(win->flags & 0x10))
        gfx_set_scissor_clamped(0, g_screen_width - 1, 0, g_screen_height - 1);
}
