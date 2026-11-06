#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern int D_001B1668 __attribute__((nosda));
extern int D_001A89B0[8] __attribute__((sda));
extern int func_0027F128(u8 *, int, u8 *);
extern void func_US2_0027FCB0(float, float, u64, u8 *, int, float, u64, u8 *);
extern int D_001A8BB0 __attribute__((section(".sdata")));
extern int D_001B166C __attribute__((sda));
extern int D_001A7340 __attribute__((nosda));
extern int D_001A7344 __attribute__((nosda));
extern void func_002FC620(int, int, int, int);

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
void func_US2_00280550(unsigned short *win_p, u64 a1, u8 *text_p, int len, u64 a4, u8 *glyphs, float scale)
{
    struct FontWindow *win = (struct FontWindow *)win_p;
    unsigned char *text = (unsigned char *)text_p;
    short start[80];
    short endi[80];
    short colr_arr[80];
    int W, balanced, Wsave, line, i, brk, width, colr, n0, last;
    int k, y, adv;

    if (D_001A8BB0 != 1 && !(win->flags & 0x10))
        func_002FC620(win->x_min, win->x_max - 1, win->y_min, win->y_max - 1);
    D_001B166C = 1;
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
    balanced = 0;
    colr = 0;
    Wsave = W;
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
                if (D_001B1668 != 0 && (unsigned char)(text[i] - 8) < 8)
                    colr = text[i] - 8;
                if (text[i] < 2)
                    break;
                adv = ((signed char *)glyphs)[text[i] * 4 + 3];
                i++;
                if (adv != 0)
                    width += adv;
            }
            if (D_001B1668 != 0 && width >= W) {
                if (text[i] >= 8) {
                    if (text[i] < 0x10)
                        colr = text[i] - 8;
                }
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
            w = func_0027F128(text + start[k], cnt, glyphs);
            if (dw->out_w < w)
                dw->out_w = w;
            if (!(dw->flags & 4)) {
                D_001A89B0[0] = a1;
                if (dw->flags & 8) {
                    float fx;
                    if (dw->flags & 1)
                        fx = (dw->x_anchor - (w >> 1)) + dw->x_sub * 0.0625f;
                    else
                        fx = dw->x_anchor + dw->x_sub * 0.0625f;
                    func_US2_0027FCB0(fx, y + dw->y_sub * 0.0625f, (long)D_001A89B0[colr_arr[k]],
                                      text + start[k], cnt, scale, a4, glyphs);
                } else if (dw->flags & 1) {
                    func_US2_0027FCB0(dw->x_anchor - (w >> 1), y, (long)D_001A89B0[colr_arr[k]],
                                      text + start[k], cnt, scale, a4, glyphs);
                } else {
                    func_US2_0027FCB0(dw->x_anchor, y, (long)D_001A89B0[colr_arr[k]],
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
    D_001B166C = 0;
    if (D_001A8BB0 != 1 && !(win->flags & 0x10))
        func_002FC620(0, D_001A7340 - 1, 0, D_001A7344 - 1);
}
