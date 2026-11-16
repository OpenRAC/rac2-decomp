#include "include_asm.h"

#include "common.h"
typedef struct { int v[5]; } B1202Five;
extern B1202Five g_race_banner_keys_x, g_race_banner_keys_y, g_race_banner_keys_start, g_race_banner_keys_end;
extern int g_race_time_ticks __attribute__((sda));
extern unsigned char *g_popup_resource_table;
typedef struct { unsigned char pad[0xb0]; float tan_half; } ProjectionState;
extern ProjectionState g_water_camera;
extern float g_race_hud_layout_scale;
extern int g_is_pal_video;
extern int g_race_hud_mode;

/* Upstream's hud_coord (src/game/00326A10-g8.c), unchanged, with this level's display-mode global.
   The display-mode test has no effect on the result, but it is real: its load and compare go at
   flow2, after allocation, which leaves the saved but unused register ($s5, as in retail). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && g_race_hud_mode == active)
        scaled = 1.0f;
    return result;
}
extern int FastTweenColor(int,int,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void UpdateViewContext(void);
extern void *table_find_by_id(char *,int);
/* Typed interleaving (docs/build/compiler-notes.md, "Source methods shared with RAC1"): the same two
   integer and five float arguments, in the same order within each register bank. */
extern void gfx_draw_scaled_object_two_axes(int,float,int,float,float,float,float);
extern void VU1_addGSregister(int,unsigned long long);
/* Draws the race banner: five fading coloured markers and the icons at the left and right sides of the screen. */
void hud_draw_race_banner(unsigned char *controller)
{
    B1202Five x = g_race_banner_keys_x;
    B1202Five y = g_race_banner_keys_y;
    B1202Five start = g_race_banner_keys_start;
    B1202Five end = g_race_banner_keys_end;
    int colors[5];
    unsigned char *vars = *(unsigned char **)(controller+0x68);
    int frame,i,j,right,fade_in_start,fade_in_end,fade_out_start,fade_out_end;
    int sprite,banner_sprite;
    float angle, sine, sign, left_x, inner_x;
    int one, top, off;
    if (controller[0xbc]==3 || controller[0xbc]==4 || controller[0xbc]==1 || controller[0xbc]==2) frame=150-*(int *)(vars+0x394);
    else frame=g_race_time_ticks+150;
    if (!g_popup_resource_table) return;
    for(i=0;i<5;i++) {
        if(i==4) { fade_in_start=120;fade_in_end=149;do{fade_out_start=156;}while(0);fade_out_end=171; }
        else { j=i*30; fade_in_start=j;fade_in_end=fade_in_start+30;fade_out_end=fade_in_start+45;fade_out_start=fade_in_end; }
        colors[i]=0;
        if(frame>=fade_in_start && frame<fade_in_end) colors[i]=FastTweenColor(0,start.v[i],(float)(frame-fade_in_start)*0.033333335f);
        else if(frame>=fade_in_end && frame<fade_out_start && fade_in_end!=fade_out_start) colors[i]=start.v[i];
        else if(frame>=fade_out_start && frame<fade_out_end) colors[i]=FastTweenColor(start.v[i],end.v[i],(float)(frame-fade_out_start)*0.06666667f);
        else if(frame>=fade_out_end) colors[i]=end.v[i];
    }
    i=0;
    off=0x8710;
    angle=0.56217057f;
    sine=math_fast_sin_or_cos_b(angle);
    sine=sine/math_fast_sin_or_cos_a(angle);
    g_water_camera.tan_half=sine;
    UpdateViewContext();

    one=1;
    for(;i<2;i++) {
        if(i==0) {j=10;right=31;sign=1.0f;} else {j=498;right=478;sign=-1.0f;}
        left_x=(float)j;
        banner_sprite=table_find_by_id((char *)g_popup_resource_table+off,58);
        top=hud_coord(120.0f,g_race_hud_layout_scale,0.5f,one);
        gfx_draw_scaled_object_two_axes(banner_sprite,(float)j,0x60442d00,(float)top,sign,1.0f,0.0f);
        sprite=table_find_by_id((char *)g_popup_resource_table+off,59);
        top=hud_coord(120.0f,g_race_hud_layout_scale,0.5f,one);
        gfx_draw_scaled_object_two_axes(sprite,(float)j,0x55f0c070,(float)top,sign,1.0f,0.0f);
        sprite=table_find_by_id((char *)g_popup_resource_table+off,60);
        gfx_draw_scaled_object_two_axes(sprite,left_x,0x55f0c070,(float)hud_coord(120.0f,g_race_hud_layout_scale,0.5f,one),sign,1.0f,0.0f);
        inner_x=(float)right;
        for(j=0;j<5;j++) {
            gfx_draw_scaled_object_two_axes(table_find_by_id((char *)g_popup_resource_table+0x8710,61),inner_x,colors[j],(float)(g_is_pal_video?y.v[j]:x.v[j]),0.8f,0.8f,0.0f);
        }
        VU1_addGSregister(71,0x5360b);
    }
    if(controller[0x20]!=3) {
        float turn, ratio;
        turn=*(float *)(vars+0x28c);
        turn*=0.008726647f;
        ratio=math_fast_sin_or_cos_b(turn);
        ratio=ratio/math_fast_sin_or_cos_a(turn);
        g_water_camera.tan_half=ratio;
        UpdateViewContext();
    }
}
