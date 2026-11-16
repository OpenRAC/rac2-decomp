#include "names.h"
/* func_PAL_L02_004030B4: the PAL copy of v2.00's func_US2_L02_003FFEDC
 * (src/us2/levels/02_maktar_nebula/L02_003FFEDC-g8.c), itself the v2.00 copy of func_L02_003FE8B8, the
 * level's six-box HUD. The same C, flags and helpers, with PAL's text ids, and its countdowns read
 * the 50 Hz frame counter: seconds are frames / 50 (v2.00: / 60). As in v2.00, the r70 title's
 * routine is picked by func_PAL_L02_00402928, and the r70 and rB0 boxes come from two-row tables
 * indexed by it. */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

extern s32 g_arena_menu_base[] __attribute__((sda));
extern f32 g_hud_label_scale;
typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;
extern u8 g_hud_l02_render_state[];
extern char g_str_hud_number_format[];
extern char g_str_hud_round_name_format[];
extern s16 *g_arena_challenge_table_2[] SDATA(D_L02_001B1190);
extern s32 g_hud_text_color __attribute__((sda));

extern s32 g_hud_panel_d_window_height __attribute__((sda));
extern s32 g_hud_panel_d_height __attribute__((sda));
extern s32 g_hud_panel_d_pos_x __attribute__((sda));
extern s32 g_hud_panel_d_pos_y[] __attribute__((sda));
extern s32 g_hud_panel_d_window_left[] __attribute__((sda));
extern s32 g_hud_panel_d_window_right[] __attribute__((sda));
extern s32 g_hud_panel_c_window_height __attribute__((sda));
extern s32 g_hud_panel_c_height __attribute__((sda));
extern s32 g_hud_panel_c_pos_x[][4] SDATA(D_L02_001B13C8);
extern s32 g_hud_panel_c_pos_y[][4] __attribute__((sda));
extern s32 g_hud_panel_c_window_left[][4] __attribute__((sda));
extern s32 g_hud_panel_c_window_right[][4] __attribute__((sda));
extern s32 g_hud_window_b_height __attribute__((sda));
extern s32 g_hud_window_b_box_height __attribute__((sda));
extern s32 g_hud_window_b_x __attribute__((sda));
extern s32 g_hud_window_b_y[] __attribute__((sda));
extern s32 g_hud_window_b_left[] __attribute__((sda));
extern s32 g_hud_window_b_top[] __attribute__((sda));
extern s32 g_hud_window_a_height __attribute__((sda));
extern s32 g_hud_window_a_box_height __attribute__((sda));
extern s32 g_hud_window_a_x[][4] SDATA(D_L02_001B1368);
extern s32 g_hud_window_a_y[][4] __attribute__((sda));
extern s32 g_hud_window_a_left[][4] __attribute__((sda));
extern s32 g_hud_window_a_top[][4] __attribute__((sda));
extern s32 g_hud_panel_b_window_height __attribute__((sda));
extern s32 g_hud_panel_b_text_y __attribute__((sda));
extern s32 g_hud_panel_b_pos_x __attribute__((sda));
extern s32 g_hud_panel_b_pos_y[] __attribute__((sda));
extern s32 g_hud_panel_b_window_left[] __attribute__((sda));
extern s32 g_hud_panel_b_window_right[] __attribute__((sda));
extern s32 g_hud_window_c_height __attribute__((sda));
extern s32 g_hud_window_c_box_height __attribute__((sda));
extern s32 g_hud_window_c_x __attribute__((sda));
extern s32 g_hud_window_c_y[] __attribute__((sda));
extern s32 g_hud_panel_a_window_left[] __attribute__((sda));
extern s32 g_hud_panel_a_window_right[] __attribute__((sda));

extern s32 g_hud_label_a_word0 __attribute__((sda));
extern s32 g_hud_label_a_word1 __attribute__((sda));
extern s32 g_hud_label_a_word2 __attribute__((sda));
extern s32 g_hud_label_b_word0 __attribute__((sda));
extern s32 g_hud_label_b_word1 __attribute__((sda));
extern f32 g_hud_label_unit_float __attribute__((sda));
extern f32 g_hud_label_c_float0 __attribute__((sda));
extern f32 g_hud_label_c_float1 __attribute__((sda));
extern f32 g_hud_label_d_float0 __attribute__((sda));
extern f32 g_hud_label_d_float1 __attribute__((sda));
extern f32 g_hud_label_e_float0 __attribute__((sda));
extern f32 g_hud_label_e_float1 __attribute__((sda));
extern s32 g_hud_label_color_a __attribute__((sda));
extern s32 g_hud_label_color_b __attribute__((sda));

extern void UpdateViewContext(void);
extern void text_draw_window_small(Rect *, u64, char *, s32);
extern void text_draw_window_large(Rect *, u64, char *, s32);
extern void text_draw_window_medium(Rect *, u64, char *, s32);
extern int pal_language_at_least_two(void);
extern void FontSetWindow(Rect *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 IntToFloat(s32);
extern char *GetLocalizedString(s32);
extern void VU1_addGSregister(u32, u64);
extern void gfx_append_draw_list_packet_c(void);
extern void gfx_draw_scaled_object_two_axes(char *, f32, s32, f32, f32, f32, f32);
extern void hud_draw_boss_health_bar(f32);
extern void *table_find_by_id(s32, s32);
extern s32 func_001157AC(char *);
extern s32 sprintf(char *, char *, ...);

#define LBL0(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define LBL4(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y4(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define TITLE(B, A) \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, B); \
        LBL0(0x4D, D_L02_001B1420, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, A)
#define LABEL(B, A) \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, B); \
        LBL0(0x4D, D_L02_001B1420, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, A)
#define LABEL50(A) \
        LBL4(0x50, D_L02_001B1420, D_L02_001B13FC, D_L02_001B1400, D_L02_001B1404, 1.0f, 0.0f, half, A)
#define SUM() \
            sum = 0; \
            for (obj = data + 0x90, i = 5; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L02_001B1358, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L02_001B1358; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8

extern int g_hud_l02_mode;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* label_y4: label_y with the mode test before the rounding and dead stores to value. */
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = value * scale + half;
    int result;
    void *copy;
    if (mode == active) value = scale;
    result = (int)scaled;
    if (handle != 0) value = scale;
    copy = handle;
    if (copy != 0) value = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the Maktar Nebula challenge HUD: the timer, round and title boxes, the score and the boss
   health bar, depending on the challenge state (PAL: countdowns use 50 frames per second). */
void arena_draw_hud_pal(u8 *moby)
{
    char buf[0x40];
    Rect r50;
    Rect r70;
    Rect r90;
    Rect rB0;
    Rect rD0;
    Rect rF0;
    u8 *data;
    u8 *obj;
    u8 *pv;
    f32 saved_text_scale;
    s32 sum;
    s32 i;
    s32 n;
    f32 t;
    f32 half;
    s32 one;
    s32 k2;
    s32 k3;
    s32 x, y, h;
    char *str;
    s32 three;
    s32 three2;
    s32 three3;

    if (g_arena_menu_base[0] == 0) {
        return;
    }
    gfx_append_draw_list_packet_c();
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    x = hud_coord((f32)g_hud_panel_d_pos_x, g_hud_label_scale, half, 1);
    y = hud_coord((f32)g_hud_panel_d_pos_y[0], g_hud_label_scale, half, 1);
    h = hud_coord((f32)g_hud_panel_d_height, g_hud_label_scale, half, 1);
    three = 3;
    FontSetWindow(&r50, x, y, g_hud_panel_d_window_left[0], g_hud_panel_d_window_right[0], g_hud_panel_d_window_height, h, 0, three);
    {
    s32 x, y;
    x = (f32)g_hud_panel_c_pos_x[pal_language_at_least_two()][0] * g_hud_label_scale + half;
    y = label_y(moby, (f32)g_hud_panel_c_pos_y[pal_language_at_least_two()][0], g_hud_label_scale, half, 1);
    FontSetWindow(&r70, x, y, g_hud_panel_c_window_left[pal_language_at_least_two()][0], g_hud_panel_c_window_right[pal_language_at_least_two()][0], g_hud_panel_c_window_height, hud_coord((f32)g_hud_panel_c_height, g_hud_label_scale, half, 1), 0, three);
    three2 = 3;
    }
    k2 = 1;
    x = hud_coord((f32)g_hud_window_b_x, g_hud_label_scale, half, k2);
    do { t = (f32)g_hud_window_b_y[0] * g_hud_label_scale + half; y = t; } while (0);
    h = hud_coord((f32)g_hud_window_b_box_height, g_hud_label_scale, half, k2);
    FontSetWindow(&r90, x, y, g_hud_window_b_left[0], g_hud_window_b_top[0], g_hud_window_b_height, h, 0, three);
    {
    s32 x, y;
    x = label_y(&rB0, (f32)g_hud_window_a_x[pal_language_at_least_two()][0], g_hud_label_scale, half, 1);
    do { k3 = 1; } while (0);
    y = (f32)g_hud_window_a_y[pal_language_at_least_two()][0] * g_hud_label_scale + half;
    FontSetWindow(&rB0, x, y, g_hud_window_a_left[pal_language_at_least_two()][0], g_hud_window_a_top[pal_language_at_least_two()][0], g_hud_window_a_height, hud_coord((f32)g_hud_window_a_box_height, g_hud_label_scale, half, k3), 0, three);
    }
    one = 1;
    x = hud_coord((f32)g_hud_panel_b_pos_x, g_hud_label_scale, half, k2);
    do { t = (f32)g_hud_panel_b_pos_y[0] * g_hud_label_scale + half; y = t; } while (0);
    three3 = 3;
    FontSetWindow(&rF0, x, y, g_hud_panel_b_window_left[0], g_hud_panel_b_window_right[0], g_hud_panel_b_window_height, hud_coord((f32)g_hud_panel_b_text_y, g_hud_label_scale, half, one), 0, three3);
    x = hud_coord((f32)g_hud_window_c_x, g_hud_label_scale, half, one);
    do { t = (f32)g_hud_window_c_y[0] * g_hud_label_scale + half; y = t; } while (0);
    FontSetWindow(&rD0, x, y, g_hud_panel_a_window_left[0], g_hud_panel_a_window_right[0], g_hud_window_c_height, hud_coord((f32)g_hud_window_c_box_height, g_hud_label_scale, half, 1), 0, three2);
    saved_text_scale = ((HudRenderState *)g_hud_l02_render_state)->text_scale;
    ((HudRenderState *)g_hud_l02_render_state)->text_scale = 0.62f;
    UpdateViewContext();
    if (*(s16 *)(data + 0x120) == three2) {
        s32 ofs = 0x8710;
        TITLE( k2, 1);
        sprintf_n(buf, g_str_hud_number_format, 0x1E - *(s32 *)(data + 0xD4) / 50);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_medium, &rB0, GetLocalizedString(0xE88));
        LABEL( k2, 1);
        SUM();
        sprintf(buf, g_str_hud_number_format, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(text_draw_window_large, &r50);
        str = GetLocalizedString(0xE86);
        if (pal_language_at_least_two()) {
            text_draw_window_medium(&r70, g_hud_text_color, str, func_001157AC(str));
        } else {
            text_draw_window_small(&r70, g_hud_text_color, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x120) == 5) {
        s32 ofs = 0x8710;
        TITLE( 1, 1);
        sprintf_n(buf, g_str_hud_number_format, 60 - *(s32 *)(data + 0xD4) / 50);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_medium, &rB0, GetLocalizedString(0xE88));
        LABEL( one, one);
        SUM();
        sprintf(buf, g_str_hud_number_format, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(text_draw_window_large, &r50);
        str = GetLocalizedString(0xE86);
        if (pal_language_at_least_two()) {
            text_draw_window_medium(&r70, g_hud_text_color, str, func_001157AC(str));
        } else {
            text_draw_window_small(&r70, g_hud_text_color, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x120) == 0xC) {
        s32 ofs = 0x8710;
        TITLE( one, one);
        n = 120 - *(s32 *)(data + 0xD4) / 50;
        sprintf(buf, g_str_hud_number_format, n);
        if (n >= 100) {
            DRAWBUF(text_draw_window_small, &r90);
        } else {
            do { DRAWBUF(text_draw_window_large, &r90); } while (0);
        }
        DRAW(text_draw_window_medium, &rB0, GetLocalizedString(0xE88));
    } else {
        if (*(u8 **)(data + 0xD0) != 0) {
            s32 ofs = 0x8710;
            LABEL( k2, 1);
            LABEL50( 1);
            obj = *(u8 **)(data + 0xD0);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0x9F8:
                pv = *(u8 **)(obj + 0x68);
                hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                LBL4(0x51, g_hud_label_a_word0, g_hud_label_a_word1, g_hud_label_a_word2, g_hud_label_unit_float, 1.0f, 2.0f, half, k2);
                break;
            case 0xA44:
                pv = *(u8 **)(obj + 0x68);
                hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                LBL4(0x51, g_hud_label_a_word0, g_hud_label_a_word1, g_hud_label_a_word2, g_hud_label_unit_float, 1.0f, 1.0f, half, 1);
                break;
            }
        }
        {
        s32 ofs = 0x8710;
        LBL0(0x4E, g_hud_label_color_b, g_hud_label_e_float0, g_hud_label_e_float1, -1.0f, g_hud_label_unit_float, 0.0f, 0.5f, k2);
        LBL0(0x4F, g_hud_label_color_a, g_hud_label_e_float0, g_hud_label_e_float1, -1.0f, g_hud_label_unit_float, 0.0f, 0.5f, one);
        }
        sprintf(buf, g_str_hud_round_name_format, *(s16 *)(data + 0x122) + 1, *g_arena_challenge_table_2[*(s16 *)(data + 0x120)]);
        DRAWBUF(text_draw_window_large, &rF0);
        DRAW(text_draw_window_small, &rD0, GetLocalizedString(0xE85));
    }
    VU1_addGSregister(0x47, 0x5360B);
    ((HudRenderState *)g_hud_l02_render_state)->text_scale = saved_text_scale;
    UpdateViewContext();
}
