#include "names.h"
/* func_002CC6B0 (2,076 bytes, boot): the HUD scroll window. A FAKEMATCH unit (owner ruling,
 * 13 November 2026; config/fakematch.tsv): RAC1's win_shift/win_unshift pairs on stand-in globals
 * and reused locals, each site marked below. It builds with the switches of
 * tools/compiler/transformers/cc6b0_rules.py (config/cflags.txt; docs/build/compiler-notes.md). */
#include "common.h"
typedef struct { short s[12]; } Win;
typedef struct { char pad[0x3C]; int so; } LabelSO;
extern char g_str_label_text_a[], g_str_label_text_b[], g_str_two_string_fmt[], g_str_label_text_c[];
extern unsigned char g_font_glyphs_small[], g_font_glyphs_large[], g_font_glyphs_medium[], g_item_slot_to_record[];
extern unsigned char g_item_owned_flags[] MACRO_ADDR, g_game_flag_table[] MACRO_ADDR, g_item_enabled_flags[] MACRO_ADDR;
extern int g_selected_map_index NOT_SDA;
extern int g_is_pal_video[] MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern int g_label_default_color __attribute__((sda));
extern int g_label_line_height __attribute__((sda));
extern int g_label_centered_flag __attribute__((sda));
extern int g_label_origin_y __attribute__((sda));
extern int g_label_outline_flag __attribute__((sda));
extern int g_pad_pressed_flags[];
extern char *g_active_menu_object NOT_SDA;
extern char g_pause_page_c[];
extern void VU1_addGSregister(int, long);
extern int menu_list_active_entries(int *, unsigned int *, int *, int);
extern int text_find_pair_in_table(short, int, unsigned short *);
typedef struct { unsigned char pad[4]; unsigned char available; unsigned char tail[0xDB]; } ItemConfig;
extern ItemConfig g_weapon_table[];
extern int sprintf(char *, const char *, ...);
extern void *memset(void *, int, int);
extern void SetupGifPaging(int);
extern long GetEffectTextureDescriptor(int);
extern void DoGifPaging(void), gfx_disable_screen_flag(void), gfx_enable_screen_flag(void);
extern char *GetLocalizedString(int);
extern void FontPrintWindow(void *, long, char *, long, long, unsigned char *);
extern void gfx_draw_box_outline(int, int, int, int, int);
#define ST (*(char **)(D_001F2854 + 0xE8))
#define TEXT(id) func_00288FB8(id)
#define DRAW(c,t) func_0027FC70(&win,c,t,-1,tex,glyphs)
static inline int translated_edge(int extent, int origin) { return extent + origin; }
static inline void set_anchor(Win *p, unsigned short anchor) { p->s[5] = anchor; }
static inline void set_top(Win *p, unsigned short top) { p->s[0] = top; }
static inline void set_window_vertical(Win *p, unsigned short top, unsigned short anchor) { p->s[5] = anchor; p->s[0] = top; }
/* Draws one line of help or item text inside a menu label box, and scrolls it when it is too long to fit. */
int render_configured_text_label(unsigned char *label) {
    char buf[0x40];
    int id;
    int helpResult;
    int originY, originX;
    Win win;
    Win tmp;
    char *text = g_str_label_text_a;
    unsigned char *glyphs = g_font_glyphs_small;
    int font;
    int font_flags, content_flags, g, f, content, variant = 0, center_y, center_x, colour, t, wflags;
    /* func_0027C878's TEX0 is 64 bits, and FontPrintWindow reads all of them: on the console the
       register keeps them whatever the C says, on a PC an int keeps only the low half. */
    long tex;
    int y, x, m; /* FAKEMATCH: y/x/m only serve the second scroll block below */
    int k;       /* FAKEMATCH: shift stand-in, then the 0x20000 mask (s0) */

    font = 1;
    font_flags = *(int *)(label + 0x30);
    if (font_flags & 8) {
        font = 3;
        glyphs = g_font_glyphs_large;
    }
    if (font_flags & 0x10) {
        font = 2;
        glyphs = g_font_glyphs_medium;
    }
    VU1_addGSregister(0x42, 0x44);
    ((void (*)(int, long))VU1_addGSregister)(0x47, 0x2004B);

    content_flags = *(int *)(label + 0x30);
    if (content_flags & 0x20) {
        content = g_current_map_index - 1;
        if ((unsigned int)content >= 0x12) {
            content = -1;
        }
    } else if (content_flags & 0x40) {
        content = g_selected_map_index - 1;
    } else if (content_flags & 4) {
        t = g_label_default_color;
        if (*(int *)(label + 0x44) < t) {
            *(int *)(label + 0x44) = g_label_default_color;
        }
        content = 0;
        *(int *)(label + 0x48) = 0;
        *(int *)(label + 0x4C) = 0;
    } else if (content_flags & 0x80) {
        content = *(int *)(ST + 0x40);
        if (content_flags & 0x8000) {
            variant = g_is_pal_video[0] != 0;
        }
    } else if (content_flags & 0x100) {
        char *cell;
        content = *(int *)(ST + 0x3C);
        cell = *(char **)(ST + 0x48) + content * 10;
        if (*(short *)(cell + 4) == 0) {
            id = g_item_owned_flags[*(short *)(cell + 6)];
        } else {
            id = g_game_flag_table[*(short *)(cell + 6)];
        }
        if (id == 0) {
            content = -1;
            t = 0;
        }
    } else if (content_flags & 0x1000) {
        char *st = ST;
        content = *(int *)(st + 0x40);
        id = *(short *)(*(char **)(st + 0x34) + content * 12);
        *(int *)(label + 0x34) = 0xFFFF;
        text_find_pair_in_table(id, 0, (unsigned short *)(label + 0x34));
    } else {
        char *cell;
        int k;
        cell = (char *)(*(int *)(ST + 0x3C) * 10 + *(int *)(ST + 0x48));
        k = *(short *)(cell + 6);
        variant = 0;
        if (*(short *)(cell + 4) == 0)
            variant = ((ItemConfig *)(g_item_slot_to_record[k] * 0xE0 + (int)g_weapon_table))->available != 0;
        content = k;
    }

    if (*(int *)(label + 0x44) == -1) {
        *(int *)(label + 0x44) = g_label_default_color;
        *(int *)(label + 0x48) = content;
        *(int *)(label + 0x4C) = variant;
    }
    if (content != *(int *)(label + 0x48)) {
        int fade;
        t = g_label_default_color;
        if (t < *(int *)(label + 0x44)) {
            *(int *)(label + 0x44) = g_label_default_color;
        }
        fade = *(int *)(label + 0x44);
        { int was = fade < 1; fade--; if (was) fade = 0; }
        { int was = fade < 1; fade--; if (was) fade = 0; }
        { int was = fade < 1; fade--; if (was) fade = 0; }
        *(int *)(label + 0x44) = fade;
        if (fade != 0) {
            content = *(int *)(label + 0x48);
            variant = *(int *)(label + 0x4C);
        } else {
            *(int *)(label + 0x48) = content;
            *(int *)(label + 0x4C) = variant;
            *(int *)(label + 0x30) &= ~0x400;
            *(int *)(label + 0x3C) = 0;
        }
    } else {
        *(int *)(label + 0x44) += 3;
    }

    g = *(int *)(label + 0x30);
    if (g & 4) {
        if (*(int *)(label + 0x34) == 0) {
            return 1;
        }
        text = TEXT(*(int *)(label + 0x34));
    } else if (g & 0x1000) {
        if (*(int *)(label + 0x34) == 0xFFFF) {
            return 1;
        }
        if (*(int *)(label + 0x34) == 0) return 1;
        text = TEXT(*(int *)(label + 0x34));
    } else if ((g & 0x100) && content == -1) {
        text = g_str_label_text_b;
    } else if (*(int *)(label + 0x34) != 0) {
        unsigned int at = (unsigned int)(content * *(int *)(label + 0x38)) >> 2 << 2;
        char *table = *(char **)(label + 0x34);
        text = TEXT(*(int *)(at + (unsigned int)(table + variant * 4)));
    }
    if ((*(int *)(label + 0x30) & 0x11E4) == 0 && ((unsigned char *)&g_item_owned_flags)[content] == 0) {
        text = g_str_label_text_b;
    }
    if (*(int *)(label + 0x30) & 0x200) {
        unsigned int at = (unsigned int)(content * *(int *)(label + 0x38)) >> 2 << 2;
        char *table = *(char **)(label + 0x34);
        int id = *(int *)(at + (unsigned int)table);
        if (id != 0xB4B && id != 0xB52 && id != 0xB56) {
            sprintf(buf, g_str_two_string_fmt, TEXT(0xB44), text);
            text = buf;
        }
    }
    f = *(int *)(label + 0x30);
    center_x = *(int *)(label + 0x18) + *(int *)(label + 0x20) / 2;
    center_y = *(int *)(label + 0x1C) + *(int *)(label + 0x24) / 2;
    if ((f & 0x4004) == 0x4004 && *(int *)(label + 0x34) == 0x112D) {
        menu_list_active_entries((int *)0x70000000, (unsigned int *)&helpResult, 0, 0);
        if (helpResult < 0) text = TEXT(0x112C);
        center_y += 8;
    }
    if (*(int *)(label + 0x30) & 0x800) if (g_item_enabled_flags[content] == 0) {
        text = TEXT(0x2DC0);
        f |= 3;
    }
    if (text == 0) {
        text = g_str_label_text_c;
    }
    wflags = 8;
    if (f & 1) {
        wflags = 9;
        center_x = *(int *)(label + 0x20) / 2;
    }
    if (f & 2) {
        wflags |= 2;
        center_y = *(int *)(label + 0x24) / 2;
    }

    SetupGifPaging(0);
    tex = GetEffectTextureDescriptor(font);
    if (g_active_menu_object == g_pause_page_c || g_label_centered_flag != 0) { originY = center_y; originX = center_x + 1; } else { originX = 1; originY = g_label_origin_y; }
    memset(&tmp, 0, 0x18);
    tmp.s[0] = originY;
    tmp.s[1] = *(unsigned short *)(label + 0x24) + originY;
    tmp.s[2] = originX;
    tmp.s[3] = translated_edge(*(unsigned short *)(label + 0x20), originX - 4);
    tmp.s[4] = center_x;
    tmp.s[5] = center_y - (*(int *)(label + 0x3C) >> 4);
    tmp.s[8] = *(int *)&g_label_line_height;
    tmp.s[9] = wflags;
    tmp.s[11] = -(*(unsigned short *)(label + 0x3C) & 0xF);
    win = tmp;
    if (g_label_outline_flag) gfx_draw_box_outline(win.s[0], win.s[1], win.s[2], win.s[3], 0x40303030);
    if (*(int *)(label + 0x30) & 0x10000) {
        win.s[1] = *(unsigned short *)(label + 0x24) - 1;
    }
    colour = 0x80F0F0F0;
    win.s[9] |= 4;
    DRAW(colour, text);
    win.s[9] ^= 4;
    if (!(*(int *)(label + 0x30) & 0x2000) && !(win.s[7] + 4 < win.s[1] - win.s[0])) {
        if (!(*(int *)(label + 0x30) & 0x400)) {
            *(int *)(label + 0x30) |= 0x400;

        }
    } else {
        if (*(int *)(label + 0x30) & 0x400)
            *(int *)(label + 0x30) ^= 0x400;
        *(int *)(label + 0x3C) = 0;
    }

    id = *(int *)(label + 0x3C);
    id >>= 4;
    id = center_y - id;
    set_anchor(&win, id);
    /* FAKEMATCH: dead shift/unshift on stand-in globals (RAC1 win_shift/win_unshift without the
       shadow DRAW); combine cancels it and leaves USE(g)/USE(k) at the block head, and g/k are
       set again below (lw 0x30 / lui), so the USEs fill retail's two empty issue slots. */
    g = g_label_origin_y; k = g_label_centered_flag;
    win.s[5] += g; win.s[5] += k; win.s[5] -= g;
    g = *(int *)(label + 0x30);
    set_top(&win, win.s[0]);
    win.s[5] -= k; /* FAKEMATCH: unshift after the s[0] copy, so the s[5] store comes last */
    k = 0x20000; /* FAKEMATCH: mask kept in the reused stand-in (shares s0 with its USE) */
    g &= k;
    /* FAKEMATCH: RAC1's win_shift/win_unshift pair with the shadow DRAW removed, on stand-in
       globals. combine cancels (a + x) - x, deletes the loads and leaves USE insns of k and g at the
       block head (no code, one issue slot each); k and g are set again below, so the USEs
       anti-depend on `lui s0` / `lw v1,0x30` and fill retail's two empty slots. */
    if (g) {
        gfx_disable_screen_flag();
    }
    DRAW(colour, text);
    if (*(int *)(label + 0x30) & 0x20000) {
        gfx_enable_screen_flag();
    }
    if (*(int *)(label + 0x30) & 0x400) {
        /* FAKEMATCH: y holds gap*3 and then the s[0] copy, so the lhu waits for the add that
           reads gap*3 (anti dependence) as in retail. */
        y = *(int *)&g_label_line_height << 1; y += *(int *)&g_label_line_height;
        x = (unsigned short)win.s[7] + y;
        y = (unsigned short)win.s[0];
        win.s[5] = win.s[5] + x;
        win.s[0] = y;
        /* FAKEMATCH: second dead shift/unshift pair (USE slots at the block head) */
        m = g_label_centered_flag; g = g_label_origin_y;
        win.s[5] += m; win.s[0] += g; win.s[5] -= m; win.s[0] -= g;
        DRAW(colour, text);
        if (*(int *)(label + 0x30) & 0x400) {
            ((LabelSO *)label)->so += (g_pad_pressed_flags[0] & 0xF) == 0xF ? 10 : 3;
            ((LabelSO *)label)->so %= (win.s[7] + *(int *)&g_label_line_height * 3) << 4;
        }
    }
    DoGifPaging();
    return 2;
}
