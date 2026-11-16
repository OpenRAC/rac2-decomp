#include "names.h"
/* func_PAL_L11_00449CBC: the PAL copy of v2.00's func_US2_L11_00445CB4
 * (src/us2/levels/11_joba/L11_00445CB4-g8.c), itself the v2.00 copy of func_L11_00444400, the Joba
 * six-box HUD. The same C, flags and helpers, with PAL's text ids, and its countdowns and clock read
 * the 50 Hz frame counter: seconds are frames / 50 and minutes frames / 3000 (v2.00: / 60, / 3600).
 * Built with -frac2-frame-pointer-liveness, as in v2.00: the flag lets flow2 drop a dead set-once
 * store left in $fp. */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;

extern s32 g_help_prompt_table[] __attribute__((sda));
extern f32 g_hud_label_y_param;
extern u8 g_hud_l11_render_state[];
extern char g_str_number_format[];
extern char g_str_time_format[];
extern char g_str_wave_number_format[];
extern char g_str_wave_name_format[];
extern s32 g_arena_wave_kill_targets_a[] SDATA(D_L11_001B14B8);
extern s32 g_arena_wave_kill_targets_b[] SDATA(D_L11_001B14D0);
extern s32 g_arena_wave_kill_targets_c[] SDATA(D_L11_001B14D8);
extern s16 *g_arena_challenge_table[] SDATA(D_L11_001B14F8);
extern s32 g_challenge_hud_text_color __attribute__((sda));

extern s32 g_challenge_hud_f_window_flags __attribute__((sda));
extern s32 g_challenge_hud_f_height __attribute__((sda));
extern s32 g_challenge_hud_f_x __attribute__((sda));
extern s32 g_challenge_hud_f_y[] __attribute__((sda));
extern s32 g_challenge_hud_f_window_left[] __attribute__((sda));
extern s32 g_challenge_hud_f_window_right[] __attribute__((sda));
extern s32 g_challenge_hud_e_window_flags __attribute__((sda));
extern s32 g_challenge_hud_e_height __attribute__((sda));
extern s32 g_challenge_hud_e_x[][4] SDATA(D_L11_001B1788);
extern s32 g_challenge_hud_e_y[][4] __attribute__((sda));
extern s32 g_challenge_hud_e_window_left[][4] __attribute__((sda));
extern s32 g_challenge_hud_e_window_right[][4] __attribute__((sda));
extern s32 g_challenge_hud_b_window_flags __attribute__((sda));
extern s32 g_challenge_hud_b_height __attribute__((sda));
extern s32 g_challenge_hud_b_x __attribute__((sda));
extern s32 g_challenge_hud_b_y[] __attribute__((sda));
extern s32 g_challenge_hud_b_window_left[] __attribute__((sda));
extern s32 g_challenge_hud_b_window_right[] __attribute__((sda));
extern s32 g_challenge_hud_a_window_flags __attribute__((sda));
extern s32 g_challenge_hud_a_height __attribute__((sda));
extern s32 g_challenge_hud_a_x[][4] SDATA(D_L11_001B1728);
extern s32 g_challenge_hud_a_y[][4] __attribute__((sda));
extern s32 g_challenge_hud_a_window_left[][4] __attribute__((sda));
extern s32 g_challenge_hud_a_window_right[][4] __attribute__((sda));
extern s32 g_challenge_hud_d_window_flags __attribute__((sda));
extern s32 g_challenge_hud_d_height __attribute__((sda));
extern s32 g_challenge_hud_d_x __attribute__((sda));
extern s32 g_challenge_hud_d_y[] __attribute__((sda));
extern s32 g_challenge_hud_d_window_left[] __attribute__((sda));
extern s32 g_challenge_hud_d_window_right[] __attribute__((sda));
extern s32 g_challenge_hud_c_window_flags __attribute__((sda));
extern s32 g_challenge_hud_c_height __attribute__((sda));
extern s32 g_challenge_hud_c_x __attribute__((sda));
extern s32 g_challenge_hud_c_y[] __attribute__((sda));
extern s32 g_challenge_hud_c_window_left[] __attribute__((sda));
extern s32 g_challenge_hud_c_window_right[] __attribute__((sda));

extern s32 g_challenge_icon_color __attribute__((sda));
extern s32 g_challenge_icon_x __attribute__((sda));
extern s32 g_challenge_icon_y __attribute__((sda));
extern s32 g_challenge_label_a_x __attribute__((sda));
extern s32 g_challenge_label_a_y __attribute__((sda));
extern f32 g_challenge_label_scale __attribute__((sda));
extern f32 g_challenge_label_b_x __attribute__((sda));
extern f32 g_challenge_label_b_y __attribute__((sda));
extern f32 g_challenge_label_c_x __attribute__((sda));
extern f32 g_challenge_label_c_y __attribute__((sda));
extern f32 g_challenge_label_d_x __attribute__((sda));
extern f32 g_challenge_label_d_y __attribute__((sda));
extern s32 g_challenge_label_color_a __attribute__((sda));
extern s32 g_challenge_label_color_b __attribute__((sda));

extern void UpdateViewContext(void);
extern void text_draw_window_small(Rect *, u64, char *, s32);
extern void text_draw_window_medium(Rect *, u64, char *, s32);
extern void text_draw_window_large(Rect *, u64, char *, s32);
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

extern s32 g_hud_coord_mode;
#define LBL(id, c, xv, yv, a1, a2, a3, A) { char *ls = (char *)func_00336D50(D_L11_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y(ls, (yv), D_L11_001B3E04, half, A), a1, a2, a3); }
#define LBL4(id, c, xv, yv, a1, a2, a3, A) { char *ls = (char *)func_00336D50(D_L11_001A904C[0] + ofs, id); func_00300A00(ls, xv, c, (f32)label_y4(ls, (yv), D_L11_001B3E04, half, A), a1, a2, a3); }
#define TITLE(A2, A) \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f, A2); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f, A)
#define LABEL(A2, A) \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f, A2); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f, A)
#define LABEL50(A) \
        LBL4(0x50, D_L11_001B17E0, D_L11_001B17BC, D_L11_001B17C0, D_L11_001B17C4, 1.0f, 0.0f, A)
#define SUM() \
            sum = 0; \
            for (obj = data + 0x100, i = 7; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L11_001B1718, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L11_001B1718; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_coord_mode;
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
    int mode = g_hud_coord_mode;
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
    int mode = g_hud_coord_mode;
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

/* Draws the Joba arena challenge HUD for the running challenge: timers or kill counters, the
   wave label and the boss health bar (PAL: 50 Hz frame counter; PAL copy of joba_hud_draw_challenge). */
void joba_hud_draw_challenge_pal(u8 *moby)
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
    f32 save;
    s32 sum;
    s32 i;
    s32 n;
    s32 tm;
    s32 x, y, h;
    char *str;
    f32 half;
    f32 t;
    s32 one;
    s32 k2;
    s32 k3;
    s32 three;
    s32 three2;
    s32 three3;

    if (g_help_prompt_table[0] == 0) {
        return;
    }
    gfx_append_draw_list_packet_c();
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    x = hud_coord((f32)g_challenge_hud_f_x, g_hud_label_y_param, half, 1);
    y = hud_coord((f32)g_challenge_hud_f_y[0], g_hud_label_y_param, half, 1);
    h = hud_coord((f32)g_challenge_hud_f_height, g_hud_label_y_param, half, 1);
    three = 3;
    FontSetWindow(&r50, x, y, g_challenge_hud_f_window_left[0], g_challenge_hud_f_window_right[0], g_challenge_hud_f_window_flags, h, 0, three);
    {
    s32 x, y;
    x = label_y(&r70, (f32)g_challenge_hud_e_x[pal_language_at_least_two()][0], g_hud_label_y_param, half, 1);
    y = label_y(data, (f32)g_challenge_hud_e_y[pal_language_at_least_two()][0], g_hud_label_y_param, half, 1);
    FontSetWindow(&r70, x, y, g_challenge_hud_e_window_left[pal_language_at_least_two()][0], g_challenge_hud_e_window_right[pal_language_at_least_two()][0], g_challenge_hud_e_window_flags, hud_coord((f32)g_challenge_hud_e_height, g_hud_label_y_param, half, 1), 0, three);
    }
    x = hud_coord((f32)g_challenge_hud_b_x, g_hud_label_y_param, half, 1);
    do { t = (f32)g_challenge_hud_b_y[0] * g_hud_label_y_param + half; y = t; } while (0);
    h = hud_coord((f32)g_challenge_hud_b_height, g_hud_label_y_param, half, 1);
    FontSetWindow(&r90, x, y, g_challenge_hud_b_window_left[0], g_challenge_hud_b_window_right[0], g_challenge_hud_b_window_flags, h, 0, three);
    three2 = 3;
    {
    s32 x, y;
    x = label_y(moby, (f32)g_challenge_hud_a_x[pal_language_at_least_two()][0], g_hud_label_y_param, half, 1);
    do { k3 = 1; } while (0);
    y = label_y(&rB0, (f32)g_challenge_hud_a_y[pal_language_at_least_two()][0], g_hud_label_y_param, half, k3);
    FontSetWindow(&rB0, x, y, g_challenge_hud_a_window_left[pal_language_at_least_two()][0], g_challenge_hud_a_window_right[pal_language_at_least_two()][0], g_challenge_hud_a_window_flags, hud_coord((f32)g_challenge_hud_a_height, g_hud_label_y_param, half, k3), 0, three);
    }
    x = hud_coord((f32)g_challenge_hud_d_x, g_hud_label_y_param, half, 1);
    y = hud_coord((f32)g_challenge_hud_d_y[0], g_hud_label_y_param, half, 1);
    FontSetWindow(&rF0, x, y, g_challenge_hud_d_window_left[0], g_challenge_hud_d_window_right[0], g_challenge_hud_d_window_flags, hud_coord((f32)g_challenge_hud_d_height, g_hud_label_y_param, half, 1), 0, three2);
    x = hud_coord((f32)g_challenge_hud_c_x, g_hud_label_y_param, half, k3);
    do { t = (f32)g_challenge_hud_c_y[0] * g_hud_label_y_param + half; y = t; } while (0);
    three3 = 3;
    FontSetWindow(&rD0, x, y, g_challenge_hud_c_window_left[0], g_challenge_hud_c_window_right[0], g_challenge_hud_c_window_flags, hud_coord((f32)g_challenge_hud_c_height, g_hud_label_y_param, half, k3), 0, three3);
    one = 1;
    k2 = 1;
    save = ((HudRenderState *)g_hud_l11_render_state)->text_scale;
    ((HudRenderState *)g_hud_l11_render_state)->text_scale = 0.62f;
    UpdateViewContext();
    if (*(s16 *)(data + 0x1F0) == 5) {
        s32 ofs = 0x8710;
        TITLE( k3, 1);
        sprintf_n(buf, g_str_number_format, 0x5A - *(s32 *)(data + 0x188) / 50);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_medium, &rB0, ((char *)GetLocalizedString(0xE88)));
        LABEL( k3, k2);
        SUM();
        sprintf_n(buf, g_str_number_format, g_arena_wave_kill_targets_a[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(text_draw_window_large, &r50);
        str = (char *)GetLocalizedString(0xE86);
        if (pal_language_at_least_two()) {
            text_draw_window_medium(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        } else {
            text_draw_window_small(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x1F0) == 9) {
        s32 ofs = 0x8710;
        TITLE( k3, one);
        tm = *(s32 *)(data + 0x188);
        { s32 hh = 2 - tm / 3000; s32 m = 0x3B - tm / 50 % 60; sprintf_n(buf, g_str_time_format, hh, m); }
        DRAWBUF(text_draw_window_medium, &r90);
        DRAW(text_draw_window_medium, &rB0, ((char *)GetLocalizedString(0xE88)));
        LABEL( k3, one);
        LABEL50( one);
        pv = *(u8 **)(*(u8 **)(data + 0x180) + 0x68);
        hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
        LBL4(0xE3, g_challenge_icon_color, g_challenge_icon_x, g_challenge_icon_y, g_challenge_label_scale, 1.0f, 1.0f, k2);
    } else if (*(s16 *)(data + 0x1F0) == 8) {
        s32 ofs = 0x8710;
        TITLE( k3, 1);
        sprintf_n(buf, g_str_number_format, 60 - *(s32 *)(data + 0x188) / 50);
        DRAWBUF(text_draw_window_large, &r90);
        DRAW(text_draw_window_medium, &rB0, ((char *)GetLocalizedString(0xE88)));
        LABEL( k2, 1);
        SUM();
        sprintf_n(buf, g_str_number_format, g_arena_wave_kill_targets_b[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(text_draw_window_large, &r50);
        str = (char *)GetLocalizedString(0xE86);
        if (pal_language_at_least_two()) {
            text_draw_window_medium(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        } else {
            text_draw_window_small(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        }
    } else if (*(s16 *)(data + 0x1F0) == 0xC) {
        s32 ofs = 0x8710;
        TITLE( 1, k2);
        n = 100 - *(s32 *)(data + 0x188) / 50;
        sprintf_n(buf, g_str_number_format, n);
        if (n >= 100) {
            DRAWBUF(text_draw_window_small, &r90);
        } else {
            do { DRAWBUF(text_draw_window_large, &r90); } while (0);
        }
        DRAW(text_draw_window_medium, &rB0, ((char *)GetLocalizedString(0xE88)));
        if (moby[0xBC] != 0) {
            s32 ofs = 0x8710; f32 half = 0.5f;
            LABEL( one, one);
            SUM();
            if (moby[0xBC] < 2) {
                sprintf_n(buf, g_str_number_format, g_arena_wave_kill_targets_c[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
                DRAWBUF(text_draw_window_large, &r50);
            } else {
                sprintf_n(buf, g_str_number_format, 100);
                DRAWBUF(text_draw_window_small, &r50);
            }
            str = (char *)GetLocalizedString(0xE86);
        if (pal_language_at_least_two()) {
            text_draw_window_medium(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        } else {
            text_draw_window_small(&r70, g_challenge_hud_text_color, str, func_001157AC(str));
        }
        }
    } else {
        if (*(u8 **)(data + 0x180) != 0) {
            s32 ofs = 0x8710;
            LABEL( one, k3);
            LABEL50( 1);
            obj = *(u8 **)(data + 0x180);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0xD4A:
                pv = *(u8 **)(obj + 0x68);
                if (*(f32 *)(pv + 0x20) > 0.0f) {
                    hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                }
                LBL4(0xE3, g_challenge_icon_color, g_challenge_icon_x, g_challenge_icon_y, g_challenge_label_scale, 1.0f, 1.0f, 1);
                break;
            case MOBY_CLASS_ARACHNOID:
                pv = *(u8 **)(obj + 0x68);
                hud_draw_boss_health_bar(*(f32 *)(pv + 0x20) / IntToFloat(*(s16 *)(pv + 0x24)));
                LBL4(0xE3, g_challenge_icon_color, g_challenge_icon_x, g_challenge_icon_y, g_challenge_label_scale, 1.0f, 2.0f, one);
                break;
            }
        }
        {
            s32 ofs = 0x8710; f32 half = 0.5f;
            LBL(0x4E, g_challenge_label_color_b, g_challenge_label_d_x, g_challenge_label_d_y, -1.0f, g_challenge_label_scale, 0.0f, k2);
            LBL(0x4F, g_challenge_label_color_a, g_challenge_label_d_x, g_challenge_label_d_y, -1.0f, g_challenge_label_scale, 0.0f, k3);
        }
        if (*(s16 *)(data + 0x1F0) == 0xA) {
            sprintf_n(buf, g_str_wave_number_format, *(s16 *)(data + 0x1F2) + 1);
        } else {
            sprintf_n(buf, g_str_wave_name_format, *(s16 *)(data + 0x1F2) + 1, *g_arena_challenge_table[*(s16 *)(data + 0x1F0)]);
        }
        DRAWBUF(text_draw_window_large, &rF0);
        DRAW(text_draw_window_small, &rD0, ((char *)GetLocalizedString(0xE85)));
    }
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x47, 0x5360B);
    ((HudRenderState *)g_hud_l11_render_state)->text_scale = save;
    UpdateViewContext();
}
