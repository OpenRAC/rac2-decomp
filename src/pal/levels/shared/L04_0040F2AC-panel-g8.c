#include "names.h"
/* func_PAL_L04_0040F2AC (placed in levels 04 and 11): the PAL race-challenge panel, the copy of
   v1.01's func_L04_0040AD28. Plain C, built with -O2 -G8 -ffunction-sections -g in a unit of its
   own and no compiler switches. label_y and hud_coord are the owner-allowed dead-test helpers that
   keep retail's block boundaries after each conversion. Each title arm looks up its own string
   (jump2 cross-jumps the identical tails), one `label` carries every looked-up string the panel
   draws, and `count` carries the pulsing tint from func_00283D38, then the clear count, then the
   time (reused locals).

   Against v1.01: the text ids are PAL's; the 181 and 279 rows are drawn scaled to 0.85 by
   func_PAL_L04_0030B2C8; the clear count is clamped right after func_L04_0040A1D0 returns; the time
   is in 50 Hz frames (/50, /3000, /5); and both time-row texts use func_0027FB40, the first at
   center + 50. */
#include "common.h"
extern int g_screen_width, g_is_pal_video;
extern int g_current_map_index;
extern int D_001A79F0_1 __attribute__((sda));
extern unsigned char g_pad_state[];
extern unsigned char g_extras_unlocked_flag;
extern int g_selected_race_index __attribute__((sda));
extern unsigned char *g_race_controller __attribute__((sda));
extern unsigned char *g_popup_resource_table;
extern float g_race_hud_layout_scale;
extern int g_game_tick_counter;
extern float g_water_camera[];
extern int g_race_best_times_primary[] MACRO_ADDR;
extern int g_race_best_times_other[];
typedef struct { int name, flags, rewards[3]; unsigned char reserved[44]; } RaceChallenge;
extern RaceChallenge g_race_challenge_table[];
extern char g_str_race_time_format_a[], g_str_race_time_format_b[], g_str_race_time_format_padded[], g_str_race_time_format_plain[];
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void UpdateViewContext(void);
extern void *table_find_by_id(void *, int);
extern void gfx_draw_scaled_object_two_axes(void *, float, unsigned int, float, float, float, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int func_001157AC(const char *);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern int text_draw_centered_large(int, int, unsigned long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern void text_draw_scaled_medium_pal(float, float, unsigned long, char *, int, float);
extern void text_draw_medium(int, int, unsigned long, char *, int);
extern int race_get_course_win_count(int);
extern void VU1_addGSregister(int, unsigned long);
extern int g_race_hud_mode;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
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

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord1(float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active) scaled = scale;
    if (result != 0) scaled = scale;
    copy = result;
    if (copy != 0) scaled = half;
    return result;
}
#define Y(v) hud_coord((float)(v), D_L04_001B2D44, 0.5f)
#define TEXT(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define TEXTY(x,y,s) { char *str_ = (s); int row_ = hud_coord((float)(y), D_L04_001B2D44, 0.5f); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define TEXTR(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FB40(x,row_,0x80f0f0f0UL,str_,len_); }
#define CENTER(y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FBD8(center,row_,0x80f0f0f0UL,str_,len_); }
#define ROWF(x,id) { float row_ = (float)Y(286); char *str_ = func_00288FB8(id); func_PAL_L04_0030B2C8(x,row_,0x80f0f0f0UL,str_,-1,0.85f); }
#define ROW(x,id) { int row_ = Y(286); char *str_ = func_00288FB8(id); func_0027F5B8(x,row_,0x80f0f0f0UL,str_,-1); }
/* Draws the race challenge panel: course name, rules, reward, best time and win count (PAL). */
int race_draw_results_panel_pal(void)
{
    char buffer[128];
    unsigned char *moby = g_race_controller;
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int center = (int)((float)g_screen_width * 0.5f);
    float angle = 0.56217057f, tangent;
    unsigned int tint;
    unsigned char *input;
    int count, shift, reward, x;
    void *icon;
    float scale, centerf, py;
    int one;
    char *label;
    float w, v;
    tangent = math_fast_sin_or_cos_b(angle);
    tangent /= math_fast_sin_or_cos_a(angle);
    centerf = (float)center;
    g_water_camera[44] = tangent;
    UpdateViewContext();
    icon = table_find_by_id(g_popup_resource_table + 0x8710,0x45);
    py = (float)label_y(icon, 200.0f, g_race_hud_layout_scale, 0.5f, 1);
    scale = 0.92f;
    if (g_is_pal_video) scale = 0.9f;
    w = 1.0f;
    gfx_draw_scaled_object_two_axes(icon,centerf,0x60442d00,py,w,scale,(float)0);
    icon = table_find_by_id(g_popup_resource_table + 0x8710,0x44);
    w = (float)label_y(icon, 200.0f, g_race_hud_layout_scale, 0.5f, 1);
    v = 1.0f;
    scale = 0.92f;
    if (g_is_pal_video) scale = 0.9f;
    gfx_draw_scaled_object_two_axes(icon,centerf,0x55f0c070,w,v,scale,0.0f);
    x = g_game_tick_counter % 50;
    count = FastTweenColor(0x80ffde8d,0x60442d00, x >= 25 ? 1.0f-(float)(x-25)*0.04f : (float)x*0.04f);
    one = 1;
    input = g_pad_state;
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x2000)) tint = count;
    icon = table_find_by_id(g_popup_resource_table+0x8710,0x4a);
    gfx_draw_scaled_object_two_axes(icon,259.0f,tint,(float)label_y(icon, 283.0f, g_race_hud_layout_scale, 0.5f, one),1.0f,1.0f,0.0f);
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x8000)) tint = count;
    icon = table_find_by_id(g_popup_resource_table+0x8710,0x4b);
    gfx_draw_scaled_object_two_axes(icon,251.0f,tint,(float)label_y(icon, 283.0f, g_race_hud_layout_scale, 0.5f, one),1.0f,1.0f,0.0f);
    if (moby[0x20] != 3) {
        float projection_angle = *(float *)(vars+0x28c)*0.008726647f;
        float sine = math_fast_sin_or_cos_b(projection_angle);
        g_water_camera[44] = sine / math_fast_sin_or_cos_a(projection_angle);
        UpdateViewContext();
    }
    { int n_ = sprintf(buffer,GetLocalizedString(0xe97),g_selected_race_index+1); int row_ = label_y3((void *)n_, 60.0f, g_race_hud_layout_scale, 0.5f, 1); int len_ = func_001157AC(buffer); text_draw_centered_large(center,row_,0x80f0f0f0UL,buffer,len_); }
    { int row_ = hud_coord1(286.0f, g_race_hud_layout_scale, 0.5f, one); char *str_ = GetLocalizedString(0xe65); text_draw_medium(119,row_,0x80f0f0f0UL,str_,-1); }
    ROW(356,0xe66);
    ROWF(181.0f,0xe64);
    ROWF(279.0f,0xe67);
    { label = GetLocalizedString(g_race_challenge_table[g_selected_race_index].name); { int row_ = Y(110); int len_ = func_001157AC(label); text_draw_centered_small(center,row_,0x80f0f0f0UL,label,len_); } }
    shift = g_current_map_index == 11 ? 10 : 5;
    count = race_get_course_win_count(g_selected_race_index);
    if(count>=3) count=2;
    if ((g_race_challenge_table[g_selected_race_index].flags & 0x10000000) ||
        (g_selected_race_index > 0 && race_get_course_win_count(g_selected_race_index-1)>0)) {
        if (g_race_challenge_table[g_selected_race_index].flags & 4) label = GetLocalizedString(D_001A79F0_1 == 11 ? 0xebf : 0xe9f);
        else label = GetLocalizedString(D_001A79F0_1 == 11 ? 0xebe : 0xe9e);
        TEXTY(center,150-shift,label);
        { if (g_race_challenge_table[g_selected_race_index].flags&1) label=GetLocalizedString(0xea1);
        else label=GetLocalizedString(0xea0);
        TEXT(center,170-shift,label);
        if (g_current_map_index==11) {
            if (g_race_challenge_table[g_selected_race_index].flags&16) label=GetLocalizedString(0xec0);
            else label=GetLocalizedString(0xec1);
            TEXT(center,190-shift,label);
            if(g_race_challenge_table[g_selected_race_index].flags&2) { label=GetLocalizedString(0xeea); TEXT(center,210-shift,label) }
        } else if(g_race_challenge_table[g_selected_race_index].flags&2) { label=GetLocalizedString(0xeea); { int row_ = label_y(label, (float)(190-shift), g_race_hud_layout_scale, 0.5f, 1); int len_ = func_001157AC(label); text_draw_centered_small(center,row_,0x80f0f0f0UL,label,len_); } } }
        if(g_race_challenge_table[g_selected_race_index].rewards[count]) {
            char *fmt = g_str_race_time_format_a;
            char *str = GetLocalizedString(0xea2);
            { unsigned char boost = g_extras_unlocked_flag;
            reward = g_race_challenge_table[g_selected_race_index].rewards[count];
            if(boost) reward*=10; }
            sprintf(buffer,fmt,str,reward,GetLocalizedString(0xe83));
        } else { char *fmt = g_str_race_time_format_b; sprintf(buffer,fmt,GetLocalizedString(0xea2)); }
        TEXT(center,shift+210,buffer);
        { int *times; if (g_current_map_index==4) { times = g_race_best_times_primary; count = times[g_selected_race_index]; } else { times = g_race_best_times_other; count = times[g_selected_race_index]; } }
        x = 0;
        if(count) {
            x = 110;
            if (count / 50 % 60 < 10) sprintf(buffer,g_str_race_time_format_padded,GetLocalizedString(0x10e0),count/3000%60,count/50%60,count/5%10);
            else sprintf(buffer,g_str_race_time_format_plain,GetLocalizedString(0x10e0),count/3000%60,count/50%60,count/5%10);
            { int col = center+50; TEXTR(col,shift+230,buffer); }
        }
            { int col = center-x;
            char *fmt = GetLocalizedString(0xea3);
            sprintf(buffer,fmt,race_get_course_win_count(g_selected_race_index));
            TEXTR(col,shift+230,buffer); }
    } else {
            char *fmt;
            label = GetLocalizedString(0xe98); CENTER(150,label);
            fmt = g_str_race_time_format_a;
            { char *str = GetLocalizedString(0xea2);
            reward = g_race_challenge_table[g_selected_race_index].rewards[count];
            if(g_extras_unlocked_flag) reward*=10;
            sprintf(buffer,fmt,str,reward,GetLocalizedString(0xe83)); }
            { int row_ = label_y((void *)center, (float)(shift+210), g_race_hud_layout_scale, 0.5f, 1); int len_ = func_001157AC(buffer); text_draw_centered_small(center,row_,0x80f0f0f0UL,buffer,len_); }
    }
    VU1_addGSregister(71,0x5360b);
    return 1;
}
