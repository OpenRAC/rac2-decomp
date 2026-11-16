#include "names.h"
/* func_US2_L08_0041EDCC (DrawLevelStatusHud), the USA v2.00 copy of func_L08_0041D808
   (src/levels/08_tabora/L08_0041D808-g8.c): draws the status bar and its two texture labels, the
   warning and counter texts, the pickup icon and its labels. The same C, with v2.00's string ids,
   and the counter text moved 24 pixels left when the language byte D_US2_001A7BBC is 3.

   Built with -fno-gcse (as the HUD units func_0032F3D0 and func_L02_003C43F0: `half`, `one`,
   `entry` and the label floats stay in registers) and -g (the nop pair before div.s).

   `hero` is one int local that holds the hero's address and later the counter colour. With two
   sets alias analysis has no base for it, so the palette stores stay behind the hero load. */
#include "common.h"

extern unsigned char g_hero_state[];
extern int g_screen_width, g_screen_height;
extern int g_pad_pressed_flags __attribute__((section(".data")));
extern int g_current_map_index;
extern unsigned char g_display_mode_index;
extern int g_frame_l08_counter;
extern unsigned char *g_hud_l08_text_table;
extern int g_hud_l08_layout_mode;
extern float g_hud_l08_scale;
extern unsigned char g_hud_bar_alpha_flag_a __attribute__((sda));
extern unsigned char g_hud_bar_alpha_flag_b __attribute__((sda));
extern unsigned char g_hud_bar_alpha_flag_c __attribute__((sda));
extern unsigned char g_hud_bar_alpha_flag_d __attribute__((sda));
extern unsigned char g_hud_bar_alpha_high_flag __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_a __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_b __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_c __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_d __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_e __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_f __attribute__((sda));
extern unsigned char g_hud_bar_test_flag_g __attribute__((sda));
extern unsigned char g_hud_bar_test_high_flag __attribute__((sda));
extern int g_hud_l08_bar_y_offset __attribute__((sda));
extern int g_mining_vehicle_timer_max __attribute__((sda));
extern float g_hud_bar_slide_x __attribute__((sda));
extern float g_hud_bar_slide_y __attribute__((sda));
extern float g_hud_bar_top_offset __attribute__((sda));
extern float g_hud_l08_bar_right_margin __attribute__((sda));
extern int g_hud_bar_text_x_margin __attribute__((sda));
extern int g_hud_bar_label_x_margin __attribute__((sda));
extern int g_hud_bar_label_y_offset __attribute__((sda));
extern float g_hud_bar_scale_from __attribute__((sda));
extern float g_hud_bar_text_param __attribute__((sda));
extern float g_hud_bar_scale_base __attribute__((sda));
extern float g_hud_bar_scale_mult __attribute__((sda));
extern float g_hud_bar_scale_start __attribute__((sda));
extern float g_hud_bar_scale_end __attribute__((sda));
extern float g_hud_bar_rect_x __attribute__((sda));
extern float g_hud_bar_rect_y __attribute__((sda));
extern float g_hud_bar_rect_width __attribute__((sda));
extern float g_hud_bar_size_param __attribute__((sda));
extern unsigned int g_hud_bar_color_a __attribute__((sda));
extern unsigned int g_hud_bar_color_b __attribute__((sda));
extern float g_hud_bar_label_y __attribute__((sda));
extern float g_hud_l08_bar_threshold __attribute__((sda));
extern void gfx_append_vectors_to_packet(int,int,unsigned long,int,unsigned long);
extern int FastDecTimer(void *);
extern int hero_begin_saved_float_hold(void);
extern void hero_set_saved_float_and_update(void);
extern int hero_end_saved_float_hold(void);
extern void *table_find_by_id(void *,int);
extern void gfx_draw_scaled_object_two_axes(char *,int,float,float,float,float,float);
extern float math_fabs(float);
extern unsigned int FastTweenColor(unsigned int,unsigned int,float);
extern void gfx_draw_screen_rectangle(int,int,int,int,int,void *);
extern int snd_play_from_class_bank(int,int,char *,int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_ease_out_quad(float);
extern float math_square(float);
extern float IntegerPower(int,float);
extern char *GetLocalizedString(int);
extern void DrawCenteredScaledText(int,int,u64,void *,int,float);
extern void thread_call_var_args_worker(s32,s32,...);
extern int func_001157AC(void *);
extern void text_draw_medium(int,int,u64,void *,int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern int GetIconFrame(int,int);
extern void hud_draw_sprite_gradient(int,int,int,int,int,void *);
extern void radar_draw(void *);
typedef struct { unsigned char pad[0xA4]; float level; } HudState;
static __inline__ unsigned long PackGaugeFlag(unsigned long flags, unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* A screen coordinate scaled for the display, offset in display mode `active`. */
static __inline__ int hud_coord(int mode, float value, float half, int active, float offset)
{
    float scaled = value * g_hud_l08_scale + half;
    if (mode == active)
        return (int)(scaled + offset);
    return (int)scaled;
}

/* The status bar's height (a float) scaled for the display and rounded. scaled_coord's
   display-mode test, on the display mode its caller has already read (as scaled_screen_size(mode,
   ...) in src/game/002D3390.c takes it), compared with the 1 its caller's own test uses. The test
   has no effect on the result: flow deletes it after allocation. */
static __inline__ int hud_size(int mode, float value, float scale, float half)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == 1)
        scaled = 1.0f;
    return result;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c). The display-mode test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_hud_l08_layout_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A label's y coordinate (a text line or a sprite) scaled for the display and rounded to a whole
   pixel. Its display-mode and handle tests do not change the result: flow deletes them after
   allocation, as with scaled_coord in src/levels/02_maktar_nebula/L02_003FF6E8-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l08_layout_mode;
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

/* Draws one centred texture label. */
static __inline__ void sprite(char *id, int col, float x, int y, float a, float b, float c)
{
    gfx_draw_scaled_object_two_axes(id, col, x, (float)y, a, b, c);
}

/* The status bar's bottom edge. */
static __inline__ int hud_bar_bottom(void)
{
    int mode = g_hud_l08_layout_mode;
    int h = g_screen_height;
    float scaled = g_hud_bar_rect_y * g_hud_l08_scale + 0.5f;
    float scale = g_hud_l08_scale;
    int y;

    if (mode == 1)
        y = (int)(scaled + -4.0f);
    else
        y = (int)scaled;
    return h - y + hud_size(mode, g_hud_bar_size_param, scale, 0.5f);
}

int func_US2_L08_0041EDCC(void)
{
    unsigned int colors[4];
    struct Palette { unsigned int a,b; } palette;
    char text[64];
    int hero = (int)g_hero_state;
    unsigned char *obj = *(unsigned char **)(hero + 0x1830);
    unsigned char *s = *(unsigned char **)(obj + 0x68);
    int mask = -1;

    if (*(float *)(hero + 0x183C) < *(float *)(hero + 0x1840) * 0.25f)
        if ((g_frame_l08_counter / 90) & 1) mask = 0xFF0F0FFF;
    {
        unsigned long test, alpha;
        test = g_hud_bar_test_flag_a;
        test = PackGaugeFlag(test, g_hud_bar_test_flag_b, 1);
        test = PackGaugeFlag(test, g_hud_bar_test_flag_c, 4);
        test = PackGaugeFlag(test, g_hud_bar_test_flag_d, 12);
        test = PackGaugeFlag(test, g_hud_bar_test_flag_e, 14);
        test = PackGaugeFlag(test, g_hud_bar_test_flag_f, 15);
        alpha = g_hud_bar_alpha_flag_a;
        alpha = PackGaugeFlag(alpha, g_hud_bar_alpha_flag_b, 2);
        test = PackGaugeFlag(test, g_hud_bar_test_flag_g, 16);
        alpha = PackGaugeFlag(alpha, g_hud_bar_alpha_flag_c, 4);
        alpha = PackGaugeFlag(alpha, g_hud_bar_alpha_flag_d, 6);
        gfx_append_vectors_to_packet(2, 0x47, test | ((unsigned long)g_hud_bar_test_high_flag << 17),
            0x42, alpha | ((unsigned long)g_hud_bar_alpha_high_flag << 32));
    }
    FastDecTimer(s + 0x8E);
    if (g_hud_l08_text_table) {
        float delta, ratio;
        unsigned char *str;
        int y;
        float x;
        unsigned int c0, c1;
        int one, entry;
        float half, fade, z;
        entry = 0x8710;
        hero_begin_saved_float_hold();
        one = 1;
        hero_set_saved_float_and_update();
        half = 0.5f;
        str = (unsigned char *)table_find_by_id(g_hud_l08_text_table + entry,0xA8);
        x = (float)(g_screen_width / 2);
        y = label_y(str, g_hud_bar_label_y, g_hud_l08_scale, half, 1);
        fade = 1.0f;
        z = 0.0f;
        sprite((char *)str, mask & 0x60442D00, x, g_screen_height / 2 + y, fade, fade, z);
        str = (unsigned char *)table_find_by_id(g_hud_l08_text_table + entry,0xA9);
        x = (float)(g_screen_width / 2);
        y = label_y(str, g_hud_bar_label_y, g_hud_l08_scale, half, 1);
        sprite((char *)str, mask & 0x55F0C070, x, g_screen_height / 2 + y, fade, fade, z);
        delta = *(float *)(hero + 0x183C) - ((HudState *)s)->level;
        delta *= 0.2f;
        {
            float magnitude = math_fabs(delta);
            if (magnitude > fade) delta /= magnitude;
        }
        c0 = g_hud_bar_color_a;
        c1 = g_hud_bar_color_b;
        ((HudState *)s)->level += delta;
        ratio = ((HudState *)s)->level / *(float *)(hero + 0x1840);
        palette.a = c0;
        palette.b = c1;
        *(struct Palette *)colors = palette;
        colors[1] = FastTweenColor(c0,c1,ratio);
        gfx_draw_screen_rectangle((int)g_hud_bar_rect_x,
            g_screen_height - hud_coord(g_hud_l08_layout_mode, g_hud_bar_rect_y, half, one, -4.0f),
            (int)(g_hud_bar_rect_x + g_hud_bar_rect_width * ratio),
            hud_bar_bottom(),
            0xFFFFF1, colors);
        hero_end_saved_float_hold();
    }
    if (g_current_map_index == 8 || g_current_map_index == 19) {
        unsigned char *str;
        if (*(short *)(s + 0x8E)) {
            float ratio, scale, alpha;
            int color;
            if (*(short *)(s + 0x8E) == 1) snd_play_from_class_bank(3,0,obj,0x85C);
            ratio = IntToFloat(180-*(short *)(s + 0x8E)) / IntToFloat(180);
            scale = g_hud_bar_scale_start + (g_hud_bar_scale_end-g_hud_bar_scale_from)*math_ease_out_quad(ratio);
            alpha = IntegerPower(3,1.0f-ratio)*127.0f;
            color = FloatToInt(alpha*0.5f) << 24;
            str = GetLocalizedString(0x2def);
            DrawCenteredScaledText(g_screen_width-g_hud_bar_label_x_margin,g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f),
                (color|0x80)&mask,str,0x11,scale*0.96f);
            color = FloatToInt(alpha*0.75f) << 24;
            DrawCenteredScaledText(g_screen_width-g_hud_bar_label_x_margin,g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f),
                (color|0x800000)&mask,str,0x11,scale*0.98f);
            color = FloatToInt(alpha) << 24;
            DrawCenteredScaledText(g_screen_width-g_hud_bar_label_x_margin,g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f),
                (color|0x808080)&mask,str,0x11,scale);
        } else if (*(int *)(s + 0x6C)) {
            if (*(float *)(s + 0x68) > g_hud_l08_bar_threshold) {
                int x, y, pad;
                char *line;
                str = GetLocalizedString(0x3076);
                thread_call_var_args_worker((s32)text,(s32)str,FloatToInt(*(float *)(s + 0x68)));
                line = text;
                pad = 0; /* 24 pixels further left in language 3 */
                if (g_display_mode_index == 3)
                    pad = 24;
                x = g_screen_width-g_hud_bar_text_x_margin-pad;
                y = g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f);
                hero = 0x80FFDE8D; /* From here on `hero` is the counter's colour. */
                hero = mask & hero;
                text_draw_medium(x,y,(unsigned int)hero,line,func_001157AC(line));
            } else if (g_pad_pressed_flags & 0x80) {
                str = GetLocalizedString(0x2ded);
                DrawCenteredScaledText(g_screen_width-g_hud_bar_label_x_margin,g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0xD,g_hud_bar_text_param);
            } else {
                float scale;
                scale = math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter)*0.1f);
                scale = math_fast_sin_or_cos_b(scale);
                scale = g_hud_bar_scale_base + g_hud_bar_scale_mult*scale;
                str = GetLocalizedString(0x2dee);
                DrawCenteredScaledText(g_screen_width-g_hud_bar_label_x_margin,g_screen_height-hud_coord(g_hud_l08_layout_mode, (float)g_hud_bar_label_y_offset, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0x11,scale);
            }
        }
        if (s[0x8A]) {
            float ratio, width, height, dx, dy, top;
            int color, tex, x, y, a, b, alpha;
            ratio = IntToFloat(*(short *)(s + 0x88))/IntToFloat(g_mining_vehicle_timer_max);
            width = math_square(ratio)*32.0f;
            height = math_square(ratio)*24.0f;
            dx = g_hud_bar_slide_x*math_ease_out_quad(ratio);
            dy = g_hud_bar_slide_y*math_ease_out_quad(ratio);
            color = FloatToInt(ratio*128.0f)<<24;
            top = 16.0f-width*0.5f;
            if (g_hud_l08_text_table) {
                hero_begin_saved_float_hold();
                hero_set_saved_float_and_update();
                alpha = FloatToInt(IntToFloat(96)*ratio)<<24;
                str = (unsigned char *)table_find_by_id(g_hud_l08_text_table+0x8710,0xAA);
                gfx_draw_scaled_object_two_axes((char *)str,
                    (alpha|0x442D00)&mask,
                    (float)(g_screen_width/2+32)-dx,(float)(g_screen_height/2+g_hud_l08_bar_y_offset),1.0f,1.0f,0.0f);
                alpha = FloatToInt(IntToFloat(85)*ratio)<<24;
                str = (unsigned char *)table_find_by_id(g_hud_l08_text_table+0x8710,0xAB);
                gfx_draw_scaled_object_two_axes((char *)str,
                    (alpha|0xF0C070)&mask,
                    (float)(g_screen_width/2+32)-dx,(float)(g_screen_height/2+g_hud_l08_bar_y_offset),1.0f,1.0f,0.0f);
                hero_end_saved_float_hold();
            }
            if (s[0x8A] < 3) {
                int c=color|0xF0F0B0;
                colors[0]=c;
                colors[1]=c;
                colors[2]=c;
                colors[3]=c;
                tex=GetIconFrame(0xEAA2,3);
                x=FloatToInt((float)g_screen_width-g_hud_l08_bar_right_margin-dy);
                y=FloatToInt(g_hud_bar_top_offset+(float)g_hud_l08_bar_y_offset+(float)*(short *)(s + 0x8C)+top);
                y=scaled_coord(y,g_hud_l08_scale,0.5f,1);
                a=FloatToInt(height);
                b=FloatToInt(height);
                hud_draw_sprite_gradient(tex,x,y,a,b,colors);
            }
        }
        radar_draw(obj);
    }
    gfx_append_vectors_to_packet(2,0x47,0x5340B,0x42,0x8000000044ULL);
    *(float *)(s + 0x68)=1000000.0f;
    *(int *)(s + 0x6C)=0;
    return 1;
}
