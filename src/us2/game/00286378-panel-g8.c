/* func_US2_00286378 (3,472 bytes): the USA v2.00 copy of func_002859C8 (src/game/002859C8-panel-g8.c), the
 * HUD panel with eleven cases, with the release's text ids. Its first
 * accept test also passes while D_001A7424 & 0x600 and func_US2_00299960() hold, as in the
 * release's func_00287018 copy. Same unit flags as the v1.01 copy (config/cflags.txt).
 */
#include "include_asm.h"
#include "names.h"

/* Near miss: func_002859C8 (boot 0x2859C8, 3436 bytes, in every level too).

   What still differs: cases 9, 10 and 11, the func_002802E0 setup only.
     retail 9, 10: f1=100 v0=3 f0=D_001B23A4 f2=0.5 | mul.s sw &box a1 a0=&box a2 add.s a3 t0 t1 cvt jal
     retail 11:    f1=100 f0=D_001B23A4 f2=0.5 &box | mul.s s1=3 sw a0=&box a1 a2 add.s a3 ...
     this C:       &box and a0 are issued in the free ALU slots of the first cycles.

   What the sched2 dump (x.i.sched2 from tools/regalloc.py) shows. The r5900 issues 2 insns per cycle;
   a1..t1 are ready from cycle 1 and fill any free ALU slot, so retail's idle slots cannot come from
   priorities or operand order. Something holds the ALU work back: either a scheduling barrier in the
   block, or two insns that take issue slots and later vanish. add.s still has to follow mul.s by its
   latency in the same block, so a real block boundary between them is ruled out. A helper whose return
   value ends a block does not fit either: it moves cvt ahead of the arguments.

   Measured, all with this C otherwise unchanged. Rows are the same masked count as above:
   - Empty volatile asm (FORBIDDEN, diagnostic only): k = 100.0f; n = 3; sc = D_001B23A4; h = 0.5f;
     then the asm, then f = sc * k + h; and (int)f as the argument. Cases 9 and 10 become exact. Case 11,
     with k, sc, h, the asm, then enabled = 1 and (int)(sc * k + h), leaves 9 rows, first difference
     +0xBB0, so the model holds but no exact-bytes form was reached. Moving case 11's asm between sc and
     h gives 14 rows. Retail's order there fits a barrier between f0 and f2, which this source does not
     reproduce.
   - do { } while (0) around the same loads, or around the call (FORBIDDEN): 3444 bytes. The loop notes
     add a padding nop at a later label that retail lacks, and around the call they also change
     allocation across the function. A loop in these two positions does not fit retail.
   - No change, 36 rows before the case 11 fix or 32 after: const or volatile on D_001B23A4; an inline
     helper returning float; -fno-sched-interblock, -fno-sched-spec, -fno-rerun-loop-opt, -fno-force-mem,
     -frac2-qcopy, -frac2-keep-block-order; a dead-arm test before the call (it folds or dies before
     sched1).
   - Worse: the whole call as an inline helper (frame 0x4C0, &box no longer kept in a register, as
     FIXED_BASE_PLUS_P arguments are substituted); the (int) in a helper with a vanishing test (61 rows);
     separate statements for the sprintf text calls (53 rows).
   - Not found: a USE, CLOBBER or no-op move that survives to sched2 here. The dump has no no-op moves,
     and its only USE insns are the scheduler's own, after calls that end a block. The compiler's USE and
     CLOBBER emission sites were read; none was found to apply.

   Next: find the original construct that gives a barrier without an instruction or a loop note. The
   same rounding of D_001B23A4 needs a barrier in func_0033A520 too, so a shared macro is possible.

   What made the difference while matching, for the next attempt:
   - every case keeps its own block-scoped variables (one shared `id` or `text`
     becomes one pseudo and drags every case into callee-saved registers), except
     case 11's `a`, which retail does share between its inner cases 1 and 3;
   - case 11's `enabled` gives the saved 1 in $s0 and the state-base ordering;
   - memset (func_00115484) must return void *, strncpy (func_00115AC0) char *
     and sprintf (func_00115DA8) int: the call setting $v0 steers the next value
     to $v1 (local-alloc's anti-false-dependency rule), which fixed the box
     builders, case 2's first byte test and several argument orders at once;
   - the SPR base is a register variable (`spr`), not a folded constant;
   - `show = 1` precedes the f5C test in case 1 (it lands in the blez delay slot);
   - inner cases 2 and 21 assign id1 after the text call, 17/18/20 before it,
     which is what decides retail's cross-jumped tails;
   - the plain small extern D_001A8C8C under -G8 gives retail's $gp load in a
     delay slot and lui/lw elsewhere; D_001F29A0 must be non-small (cc1 splits
     it, so its lui can sit in a delay slot on its own);
   - case 11's {0, 1, 2, 3} switch (0 and 2 just break) reproduces retail's
     decision tree; case 3's tail is func_00280190's body inlined.
*/

typedef struct {
    short x;
    unsigned short f02;
    short f04;
    short f06;
    short f08;
    short f0A;
    short f0C;
    short h;
    short f10;
    unsigned short flags;
    short f14;
    short f16;
} MenuBox;

typedef struct {
    char pad0[0x40];
    int mode;
    int f44;
    char pad48[0x10];
    int f58;
    int f5C;
    int f60;
    char pad64[0x18];
    short f7C;
    short f7E;
    int f80;
} MenuState;

extern MenuState g_modal_state;
extern MenuBox g_message_box_primary;
extern MenuBox g_message_box_secondary;
extern char g_str_message_text[];
extern char g_str_message_format[];
extern char g_str_message_format_two[];
extern char g_font_glyphs_small[];
extern char *g_message_panel_icon_a __attribute__((sda));
extern char *g_message_panel_icon_b __attribute__((sda));
extern char *g_message_panel_text __attribute__((sda));
extern char *g_message_panel_extra __attribute__((sda));
extern int g_message_text_color_a __attribute__((sda));
extern int g_message_text_color_b __attribute__((sda));
extern int g_menu_panel_active;
extern int g_menu_panel_flag;
extern int g_message_panel_flags[];
extern int g_save_menu_screen;
extern unsigned short g_screen_height;
extern int g_frame_counter_3;
extern float g_hud_scale;

extern void gfx_set_clear_color_packet(int, int, int, int);
extern void SetupGifPaging(int);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern char *GetLocalizedString(int);
extern char *strncpy(unsigned char *, char *, int);
extern void text_draw_window_small(MenuBox *, unsigned long, unsigned char *, int);
extern int func_001157AC(unsigned char *);
extern void level_forward_draw_args(MenuBox *, int, void *, int, int, int, int, char *, char *, char *);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern unsigned long long GetFrameTexture(int);
extern void DrawRotatedSprite(float, float, float, float, float, int, int, long long);
extern void *memset(void *, int, int);
extern int flag_get_word(void);
extern int func_US2_00299960(void);
extern int g_save_menu_flags;
extern int menu_is_confirm_pending(void);
extern int sprintf(char *, const char *, ...);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);
extern int FastTweenColor(int, int, float);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern int GetEffectTextureDescriptor(int);
extern void FontPrintWindow(MenuBox *, unsigned long, char *, int, int, void *);
extern void FontSetWindow(MenuBox *, int, int, int, int, int, int, int, int);
extern void DoGifPaging(void);

#define SPR ((unsigned char *)0x70000000)

void func_US2_00286378(void)
{
    char buf[0x300];
    MenuBox box;
    MenuBox tmp;
    MenuBox tmp2;
    char buf2[0x100];

    if (g_modal_state.f7E == 0)
        gfx_set_clear_color_packet(0, 0, 0, 0x30);
    if (g_modal_state.f7C != 0)
        return;
    SetupGifPaging(0);
    VU1_addGSregister(0x42, 0x8000000044UL);
    VU1_addGSregister(0x47, 0x5360B);
    switch (g_modal_state.mode) {
    case 2: {
        unsigned char *spr;
        unsigned char *p;
        int h, len, i, x, y;

        box = g_message_box_primary;
        spr = SPR;
        strncpy(spr, GetLocalizedString(0x9B4), 0x400);
        p = spr;
        while (*p >= 2)
            p++;
        while (*p == 1) {
            *p = 0;
            p++;
        }
        box.flags |= 4;
        text_draw_window_small(&box, 0x80000000UL, spr, -1);
        box.flags ^= 4;
        h = box.h;
        len = func_001157AC(spr);
        for (i = 4; i >= 0; i--)
            spr[len + i] = 1;
        spr[len + 5] = 0;
        level_forward_draw_args(&box, 0x80F0F0F0, spr, 1, 1, -1, 1, GetLocalizedString(0x31C3), 0, 0);
        x = box.x + h;
        VU1_addGSregister(0x47, 0x3004B);
        y = x + 8;
        hud_draw_sprite(GetIconFrame(0x755D, 0), 0xE0, y, 0x40, 0x40, 0x80);
        DrawRotatedSprite(4096.0f, (x + 40) * 16, 272.0f, 272.0f,
                      (g_frame_counter_3 % 55) * -0.11423973f, 0x40, 0x40,
                      GetFrameTexture(GetIconFrame(0x755D, 1)));
        break;
    }
    case 4:
        if (g_modal_state.f5C > 0) {
            unsigned char *p;
            int id;

            strncpy(SPR, GetLocalizedString(0x2C7B), 0x400);
            p = SPR;
            while (*p >= 2)
                p++;
            while (*p == 1) {
                *p = 0;
                p++;
            }
            id = g_modal_state.f44 ? 0 : 0x31C3;
            memset(&tmp, 0, sizeof(tmp));
            tmp.f02 = g_screen_height;
            tmp.f04 = 0x60;
            tmp.f06 = 0x1A0;
            tmp.f08 = 0x100;
            tmp.f0A = 0x68;
            tmp.f10 = 0x10;
            tmp.flags = 1;
            box = tmp;
            level_forward_draw_args(&box, 0x80F0F0F0, p, 1, 1, -1, 0, id ? GetLocalizedString(id) : 0, 0, 0);
        }
        break;
    case 5:
        if (g_modal_state.f5C > 0) {
            char *text;
            int id;

            text = GetLocalizedString(g_modal_state.f80 ? 0x2C9A : 0x2C99);
            id = g_modal_state.f44 ? 0 : 0x31C3;
            memset(&tmp2, 0, sizeof(tmp2));
            tmp2.f02 = g_screen_height;
            tmp2.f04 = 0x60;
            tmp2.f06 = 0x1A0;
            tmp2.f08 = 0x100;
            tmp2.f0A = 0x68;
            tmp2.f10 = 0x10;
            tmp2.flags = 1;
            box = tmp2;
            level_forward_draw_args(&box, 0x80F0F0F0, text, 1, 1, -1, 0, id ? GetLocalizedString(id) : 0, 0, 0);
        }
        break;
    case 1: {
        int show, id1, id2;
        char *text;

        show = 1;
        if (g_modal_state.f5C > 0) {
            text = g_str_message_text;
            id1 = 0;
            id2 = 0;
            if (flag_get_word() || ((g_save_menu_flags & 0x600) && func_US2_00299960())) {
                id1 = 0x31C3;
                text = GetLocalizedString(0x2C9A);
            } else {
                switch (g_save_menu_screen) {
                case 6:
                    id1 = 0x31C8;
                    id2 = 0x31C4;
                    text = GetLocalizedString(0x2C8A);
                    break;
                case 12:
                    if (g_message_panel_flags[0]) {
                        id1 = 0x2C7E;
                        text = GetLocalizedString(0x2C7C);
                        break;
                    }
                case 13:
                    id1 = 0x31C8;
                    id2 = 0x31C4;
                    text = GetLocalizedString(0x2C86);
                    break;
                case 10:
                case 11:
                    text = GetLocalizedString(0x2C96);
                    break;
                case 7:
                case 8:
                    text = GetLocalizedString(0x2C94);
                    break;
                case 14:
                case 15:
                    text = GetLocalizedString(0x2C95);
                    break;
                case 17:
                    id1 = 0x31C3;
                    text = GetLocalizedString(0x2C97);
                    break;
                case 18:
                    id1 = 0x31C3;
                    text = GetLocalizedString(0x2C99);
                    break;
                case 2:
                    text = GetLocalizedString(0x2C7B);
                    id1 = g_modal_state.f44 ? 0 : 0x31C3;
                    break;
                case 19:
                    if (g_message_panel_flags[0]) {
                        id1 = 0x2C7E;
                        text = GetLocalizedString(0x2C7C);
                    } else if (g_menu_panel_active) {
                        id1 = 0x31C7;
                        id2 = 0x31C4;
                        sprintf(buf, g_str_message_format, GetLocalizedString(0x2C7F), 1, 1,
                                      GetLocalizedString(0x2C81));
                        text = buf;
                    } else {
                        id1 = 0x31C7;
                        sprintf(buf, g_str_message_format, GetLocalizedString(0x2C7F), 1, 1,
                                      GetLocalizedString(0x2C81));
                        text = buf;
                        if (g_menu_panel_flag)
                            id1 = 0x31C8;
                    }
                    break;
                case 21:
                    text = GetLocalizedString((!g_menu_panel_active && menu_is_confirm_pending()) ? 0x2C9A : 0x2C99);
                    id1 = 0x31C3;
                    break;
                case 20:
                    id1 = 0x31C3;
                    text = GetLocalizedString(0x2C98);
                    break;
                case 24:
                    id1 = 0x31C7;
                    id2 = 0x31C4;
                    sprintf(buf, g_str_message_format, GetLocalizedString(0x2C88), 1, 1,
                                  GetLocalizedString(0x2C81));
                    text = buf;
                    break;
                case 23:
                    id1 = 0x31C7;
                    id2 = 0x31C4;
                    text = GetLocalizedString(0x2C8C);
                    break;
                case 3:
                case 4:
                    if (g_menu_panel_active && !g_message_panel_flags[0]) {
                        id1 = 0x31C7;
                        id2 = 0x31C4;
                        text = GetLocalizedString(0x2C82);
                    } else if (g_menu_panel_flag) {
                        id1 = 0x31C7;
                        text = GetLocalizedString(0x2C82);
                    } else if (g_message_panel_flags[0]) {
                        id1 = 0x2C7E;
                        text = GetLocalizedString(0x2C7C);
                    } else {
                        id1 = 0x2C7E;
                        text = GetLocalizedString(0x2C84);
                    }
                    break;
                case 5:
                    id1 = 0x2C7E;
                    text = GetLocalizedString(0x2C7C);
                    break;
                default:
                    show = 0;
                    break;
                }
            }
            if (show) {
                memset(&tmp, 0, sizeof(tmp));
                tmp.f02 = g_screen_height;
                tmp.f04 = 0x60;
                tmp.f06 = 0x1A0;
                tmp.f08 = 0x100;
                tmp.f0A = 0x68;
                tmp.f10 = 0x10;
                tmp.flags = 1;
                box = tmp;
                level_forward_draw_args(&box, 0x80F0F0F0, text, 1, 1, -1, 0,
                              id1 ? GetLocalizedString(id1) : 0, id2 ? GetLocalizedString(id2) : 0, 0);
            }
        }
        break;
    }
    case 3: {
        float t;
        int c1, c2, id;

        t = 1.0f - g_modal_state.f44 * 0.033333335f;
        box = g_message_box_secondary;
        gfx_draw_rounded_box(0x64, 0x12C, 0x60, 0x1A0, (int)(t * 80.0f), 0x40404);
        c1 = FastTweenColor(g_message_text_color_a, g_message_text_color_b, t);
        c2 = FastTweenColor(0x20FFFF, 0x8020FFFF, t);
        switch (g_modal_state.f58) {
        case 0:
        case 1:
            text_draw_centered_small(0xCA, 0x118, c2, GetLocalizedString(0x31C7), -1);
            text_draw_centered_small(0x135, 0x118, c2, GetLocalizedString(0x31C4), -1);
            id = 0x2DBE;
            break;
        case 2:
            text_draw_centered_small(0xCA, 0x118, c2, GetLocalizedString(0x31C7), -1);
            text_draw_centered_small(0x135, 0x118, c2, GetLocalizedString(0x31C4), -1);
            id = 0x2DBF;
            break;
        case 3:
            text_draw_centered_small(0x100, 0x118, c2, GetLocalizedString(0x31C3), -1);
            id = 0x2DC0;
            break;
        default:
            id = 0;
            break;
        }
        if (id)
            FontPrintWindow(&box, c1, GetLocalizedString(id), -1, GetEffectTextureDescriptor(1), g_font_glyphs_small);
        break;
    }
    case 9: {
        char *a, *b, *c;

        FontSetWindow(&box, 0xF0, 0x1E0, 0x60, 0x1A0, 0x100,
                      (int)(g_hud_scale * 100.0f + 0.5f), 0x10, 3);
        a = g_message_panel_icon_a;
        if (!a)
            a = GetLocalizedString(0x31C7);
        b = g_message_panel_icon_b;
        if (!b)
            b = GetLocalizedString(0x31C4);
        c = g_message_panel_text;
        if (!c)
            c = GetLocalizedString(0x2C63);
        level_forward_draw_args(&box, 0x80F0F0F0, c, 1, 1, -1, 0, a, b, g_message_panel_extra);
        break;
    }
    case 10: {
        char *a, *c;

        FontSetWindow(&box, 0xF0, 0x1E0, 0x60, 0x1A0, 0x100,
                      (int)(g_hud_scale * 100.0f + 0.5f), 0x10, 3);
        a = g_message_panel_icon_a;
        if (!a)
            a = GetLocalizedString(0x31C7);
        c = g_message_panel_text;
        if (!c)
            c = GetLocalizedString(0x2C63);
        level_forward_draw_args(&box, 0x80F0F0F0, c, 1, 1, -1, 0, a, 0, g_message_panel_extra);
        break;
    }
    case 11: {
        int enabled;
        char *a;
        float k, sc, h;
        int n;
        MenuBox *pb;

        do { k = 100.0f; sc = g_hud_scale; h = 0.5f; } while (0);
        pb = &box;
        n = 3;
        enabled = 1;
        FontSetWindow(pb, 0xF0, 0x1E0, 0x60, 0x1A0, 0x100,
                      (int)(sc * k + h), 0x10, n);
        switch (g_modal_state.f58) {
        case 0:
            break;
        case 1: {
            char *b;

            a = GetLocalizedString(0x31C3);
            b = GetLocalizedString(0x1BCA);
            sprintf(buf2, GetLocalizedString(0x307C), 15);
            level_forward_draw_args(&box, 0x80F0F0F0, buf2, enabled, enabled, -1, 0, a, b, 0);
            break;
        }
        case 2:
            break;
        case 3:
            g_modal_state.f60 = g_modal_state.f5C / 60 + 1;
            sprintf(buf2, g_str_message_format_two, GetLocalizedString(0x3083), GetLocalizedString(0x3084),
                          g_modal_state.f60, GetLocalizedString(0x3085));
            a = GetLocalizedString(0x31C7);
            level_forward_draw_args(&box, 0x80F0F0F0, buf2, enabled, enabled, -1, 0, a,
                          GetLocalizedString(0x31C4), 0);
            break;
        }
        break;
    }
    }
    DoGifPaging();
}
