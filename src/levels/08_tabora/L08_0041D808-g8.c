#include "names.h"
/* func_L08_0041D808 (DrawLevelStatusHud): draws the status bar and its two texture labels, the
   warning and counter texts, the pickup icon and its labels. The same C as func_PAL_L19_00417318
   (src/pal/levels/19_grelbin/L19_00417318-g8.c), with this level's data and string ids.

   Built with -fno-gcse (as the HUD units func_0032F3D0 and func_L02_003C43F0: `half`, `one`,
   `entry` and the label floats stay in registers) and -g (the nop pair before div.s).

   `hero` is one int local that holds the hero's address and later the counter colour. With two
   sets alias analysis has no base for it, so the palette stores stay behind the hero load. */
#include "common.h"

extern unsigned char g_hero_state[];
extern int g_screen_width, g_screen_height;
extern int D_00138320 __attribute__((section(".data")));
extern int g_current_map_index;
extern int D_L08_001B2508;
extern unsigned char *D_L08_001A904C;
extern int D_L08_001B3240;
extern float D_L08_001B3244;
extern unsigned char D_L08_001B1A34 __attribute__((sda));
extern unsigned char D_L08_001B1A35 __attribute__((sda));
extern unsigned char D_L08_001B1A36 __attribute__((sda));
extern unsigned char D_L08_001B1A37 __attribute__((sda));
extern unsigned char D_L08_001B1A38 __attribute__((sda));
extern unsigned char D_L08_001B1A39 __attribute__((sda));
extern unsigned char D_L08_001B1A3A __attribute__((sda));
extern unsigned char D_L08_001B1A3B __attribute__((sda));
extern unsigned char D_L08_001B1A3C __attribute__((sda));
extern unsigned char D_L08_001B1A3D __attribute__((sda));
extern unsigned char D_L08_001B1A3E __attribute__((sda));
extern unsigned char D_L08_001B1A3F __attribute__((sda));
extern unsigned char D_L08_001B1A40 __attribute__((sda));
extern int D_L08_001B1A74 __attribute__((sda));
extern int D_L08_001B1A78 __attribute__((sda));
extern float D_L08_001B1A80 __attribute__((sda));
extern float D_L08_001B1A84 __attribute__((sda));
extern float D_L08_001B1A88 __attribute__((sda));
extern float D_L08_001B1A8C __attribute__((sda));
extern int D_L08_001B1A90 __attribute__((sda));
extern int D_L08_001B1A94 __attribute__((sda));
extern int D_L08_001B1A98 __attribute__((sda));
extern float D_L08_001B1AAC __attribute__((sda));
extern float D_L08_001B1AB0 __attribute__((sda));
extern float D_L08_001B1AB4 __attribute__((sda));
extern float D_L08_001B1AB8 __attribute__((sda));
extern float D_L08_001B1ABC __attribute__((sda));
extern float D_L08_001B1AC0 __attribute__((sda));
extern float D_L08_001B1AC4 __attribute__((sda));
extern float D_L08_001B1AC8 __attribute__((sda));
extern float D_L08_001B1ACC __attribute__((sda));
extern float D_L08_001B1AD0 __attribute__((sda));
extern unsigned int D_L08_001B1AD4 __attribute__((sda));
extern unsigned int D_L08_001B1AD8 __attribute__((sda));
extern float D_L08_001B199C __attribute__((sda));
extern float D_L08_001B031C __attribute__((sda));
extern void gfx_append_vectors_to_packet(int,int,unsigned long,int,unsigned long);
extern int FastDecTimer(void *);
extern int hero_begin_saved_float_hold(void);
extern void hero_set_saved_float_and_update(void);
extern int hero_end_saved_float_hold(void);
extern char *table_find_by_id(void *,int);
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
extern unsigned char *GetLocalizedString(int);
extern void DrawCenteredScaledText(int,int,u64,void *,int,float);
extern void thread_call_var_args_worker(s32,s32,...);
extern int func_001157AC(void *);
extern void text_draw_medium(int,int,u64,void *,int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern int GetIconFrame(int,int);
extern int hud_draw_sprite_gradient(int,int,int,int,int,void *);
extern void radar_draw(void *);
typedef struct { unsigned char pad[0xA4]; float level; } HudState;
static __inline__ unsigned long PackGaugeFlag(unsigned long flags, unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* A screen coordinate scaled for the display, offset in display mode `active`. */
static __inline__ int hud_coord(int mode, float value, float half, int active, float offset)
{
    float scaled = value * D_L08_001B3244 + half;
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
    int mode = D_L08_001B3240;
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
    int mode = D_L08_001B3240;
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
    int mode = D_L08_001B3240;
    int h = g_screen_height;
    float scaled = D_L08_001B1AC8 * D_L08_001B3244 + 0.5f;
    float scale = D_L08_001B3244;
    int y;

    if (mode == 1)
        y = (int)(scaled + -4.0f);
    else
        y = (int)scaled;
    return h - y + hud_size(mode, D_L08_001B1AD0, scale, 0.5f);
}

/* Draws the level's heads-up display: the health bar with its labels, the warning and counter text, and the pickup icon. */
int DrawLevelStatusHud(void)
{
    unsigned int colors[4];
    struct Palette { unsigned int a,b; } palette;
    char text[64];
    int hero = (int)g_hero_state;
    unsigned char *hero_moby = *(unsigned char **)(hero + 0x1830);
    unsigned char *vars = *(unsigned char **)(hero_moby + 0x68);
    int mask = -1;

    if (*(float *)(hero + 0x183C) < *(float *)(hero + 0x1840) * 0.25f)
        if ((D_L08_001B2508 / 90) & 1) mask = 0xFF0F0FFF;
    {
        unsigned long test, alpha;
        test = D_L08_001B1A39;
        test = PackGaugeFlag(test, D_L08_001B1A3A, 1);
        test = PackGaugeFlag(test, D_L08_001B1A3B, 4);
        test = PackGaugeFlag(test, D_L08_001B1A3C, 12);
        test = PackGaugeFlag(test, D_L08_001B1A3D, 14);
        test = PackGaugeFlag(test, D_L08_001B1A3E, 15);
        alpha = D_L08_001B1A34;
        alpha = PackGaugeFlag(alpha, D_L08_001B1A35, 2);
        test = PackGaugeFlag(test, D_L08_001B1A3F, 16);
        alpha = PackGaugeFlag(alpha, D_L08_001B1A36, 4);
        alpha = PackGaugeFlag(alpha, D_L08_001B1A37, 6);
        gfx_append_vectors_to_packet(2, 0x47, test | ((unsigned long)D_L08_001B1A40 << 17),
            0x42, alpha | ((unsigned long)D_L08_001B1A38 << 32));
    }
    FastDecTimer(vars + 0x8E);
    if (D_L08_001A904C) {
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
        str = (unsigned char *)table_find_by_id(D_L08_001A904C + entry,0xA8);
        x = (float)(g_screen_width / 2);
        y = label_y(str, D_L08_001B199C, D_L08_001B3244, half, 1);
        fade = 1.0f;
        z = 0.0f;
        sprite((char *)str, mask & 0x60442D00, x, g_screen_height / 2 + y, fade, fade, z);
        str = (unsigned char *)table_find_by_id(D_L08_001A904C + entry,0xA9);
        x = (float)(g_screen_width / 2);
        y = label_y(str, D_L08_001B199C, D_L08_001B3244, half, 1);
        sprite((char *)str, mask & 0x55F0C070, x, g_screen_height / 2 + y, fade, fade, z);
        delta = *(float *)(hero + 0x183C) - ((HudState *)vars)->level;
        delta *= 0.2f;
        {
            float magnitude = math_fabs(delta);
            if (magnitude > fade) delta /= magnitude;
        }
        c0 = D_L08_001B1AD4;
        c1 = D_L08_001B1AD8;
        ((HudState *)vars)->level += delta;
        ratio = ((HudState *)vars)->level / *(float *)(hero + 0x1840);
        palette.a = c0;
        palette.b = c1;
        *(struct Palette *)colors = palette;
        colors[1] = FastTweenColor(c0,c1,ratio);
        gfx_draw_screen_rectangle((int)D_L08_001B1AC4,
            g_screen_height - hud_coord(D_L08_001B3240, D_L08_001B1AC8, half, one, -4.0f),
            (int)(D_L08_001B1AC4 + D_L08_001B1ACC * ratio),
            hud_bar_bottom(),
            0xFFFFF1, colors);
        hero_end_saved_float_hold();
    }
    if (g_current_map_index == 8 || g_current_map_index == 19) {
        unsigned char *str;
        if (*(short *)(vars + 0x8E)) {
            float ratio, scale, alpha;
            int color;
            if (*(short *)(vars + 0x8E) == 1) snd_play_from_class_bank(3,0,hero_moby,0x85C);
            ratio = IntToFloat(180-*(short *)(vars + 0x8E)) / IntToFloat(180);
            scale = D_L08_001B1ABC + (D_L08_001B1AC0-D_L08_001B1AAC)*math_ease_out_quad(ratio);
            alpha = IntegerPower(3,1.0f-ratio)*127.0f;
            color = FloatToInt(alpha*0.5f) << 24;
            str = GetLocalizedString(0x2F59);
            DrawCenteredScaledText(g_screen_width-D_L08_001B1A94,g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x80)&mask,str,0x11,scale*0.96f);
            color = FloatToInt(alpha*0.75f) << 24;
            DrawCenteredScaledText(g_screen_width-D_L08_001B1A94,g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x800000)&mask,str,0x11,scale*0.98f);
            color = FloatToInt(alpha) << 24;
            DrawCenteredScaledText(g_screen_width-D_L08_001B1A94,g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x808080)&mask,str,0x11,scale);
        } else if (*(int *)(vars + 0x6C)) {
            if (*(float *)(vars + 0x68) > D_L08_001B031C) {
                int x, y;
                char *line;
                str = GetLocalizedString(0x31E0);
                thread_call_var_args_worker((s32)text,(s32)str,FloatToInt(*(float *)(vars + 0x68)));
                line = text;
                x = g_screen_width-D_L08_001B1A90;
                y = g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f);
                hero = 0x80FFDE8D; /* From here on `hero` is the counter'vars colour. */
                hero = mask & hero;
                text_draw_medium(x,y,(unsigned int)hero,line,func_001157AC(line));
            } else if (D_00138320 & 0x80) {
                str = GetLocalizedString(0x2F57);
                DrawCenteredScaledText(g_screen_width-D_L08_001B1A94,g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0xD,D_L08_001B1AB0);
            } else {
                float scale;
                scale = math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508)*0.1f);
                scale = math_fast_sin_or_cos_b(scale);
                scale = D_L08_001B1AB4 + D_L08_001B1AB8*scale;
                str = GetLocalizedString(0x2F58);
                DrawCenteredScaledText(g_screen_width-D_L08_001B1A94,g_screen_height-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0x11,scale);
            }
        }
        if (vars[0x8A]) {
            float ratio, width, height, dx, dy, top;
            int color, tex, x, y, a, b, alpha;
            ratio = IntToFloat(*(short *)(vars + 0x88))/IntToFloat(D_L08_001B1A78);
            width = math_square(ratio)*32.0f;
            height = math_square(ratio)*24.0f;
            dx = D_L08_001B1A80*math_ease_out_quad(ratio);
            dy = D_L08_001B1A84*math_ease_out_quad(ratio);
            color = FloatToInt(ratio*128.0f)<<24;
            top = 16.0f-width*0.5f;
            if (D_L08_001A904C) {
                hero_begin_saved_float_hold();
                hero_set_saved_float_and_update();
                alpha = FloatToInt(IntToFloat(96)*ratio)<<24;
                str = (unsigned char *)table_find_by_id(D_L08_001A904C+0x8710,0xAA);
                gfx_draw_scaled_object_two_axes((char *)str,
                    (alpha|0x442D00)&mask,
                    (float)(g_screen_width/2+32)-dx,(float)(g_screen_height/2+D_L08_001B1A74),1.0f,1.0f,0.0f);
                alpha = FloatToInt(IntToFloat(85)*ratio)<<24;
                str = (unsigned char *)table_find_by_id(D_L08_001A904C+0x8710,0xAB);
                gfx_draw_scaled_object_two_axes((char *)str,
                    (alpha|0xF0C070)&mask,
                    (float)(g_screen_width/2+32)-dx,(float)(g_screen_height/2+D_L08_001B1A74),1.0f,1.0f,0.0f);
                hero_end_saved_float_hold();
            }
            if (vars[0x8A] < 3) {
                int c=color|0xF0F0B0;
                colors[0]=c;
                colors[1]=c;
                colors[2]=c;
                colors[3]=c;
                tex=GetIconFrame(0xEAA2,3);
                x=FloatToInt((float)g_screen_width-D_L08_001B1A8C-dy);
                y=FloatToInt(D_L08_001B1A88+(float)D_L08_001B1A74+(float)*(short *)(vars + 0x8C)+top);
                y=scaled_coord(y,D_L08_001B3244,0.5f,1);
                a=FloatToInt(height);
                b=FloatToInt(height);
                hud_draw_sprite_gradient(tex,x,y,a,b,colors);
            }
        }
        radar_draw(hero_moby);
    }
    gfx_append_vectors_to_packet(2,0x47,0x5340B,0x42,0x8000000044ULL);
    *(float *)(vars + 0x68)=1000000.0f;
    *(int *)(vars + 0x6C)=0;
    return 1;
}
