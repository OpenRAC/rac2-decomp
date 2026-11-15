#include "include_asm.h"

#include "common.h"
typedef struct { int v[5]; } B1202Five;
extern B1202Five D_L04_001B09B0, D_L04_001B09C8, D_L04_001B09E0, D_L04_001B09F8;
extern int g_race_time_ticks __attribute__((sda));
extern unsigned char *D_L04_001A904C;
typedef struct { unsigned char pad[0xb0]; float tan_half; } ProjectionState;
extern ProjectionState D_L04_001BDB80;
extern float D_L04_001B2D44;
extern int g_is_pal_video;
extern int D_L04_001B2D40;

/* Upstream's hud_coord (src/game/00326A10-g8.c), unchanged, with this level's display-mode global.
   The display-mode test has no effect on the result, but it is real: its load and compare go at
   flow2, after allocation, which leaves the saved but unused register ($s5, as in retail). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L04_001B2D40 == active)
        scaled = 1.0f;
    return result;
}
extern int FastTweenColor(int,int,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void UpdateViewContext(void);
extern int table_find_by_id(char *,int);
/* Typed interleaving (docs/build/compiler-notes.md, "Source methods shared with RAC1"): the same two
   integer and five float arguments, in the same order within each register bank. */
extern void gfx_draw_scaled_object_two_axes(int,float,int,float,float,float,float);
extern void VU1_addGSregister(int,unsigned long long);
/* Draws the race banner: five fading coloured markers and the icons at the left and right sides of the screen. */
void hud_draw_race_banner(unsigned char *controller)
{
    B1202Five x = D_L04_001B09B0;
    B1202Five y = D_L04_001B09C8;
    B1202Five start = D_L04_001B09E0;
    B1202Five end = D_L04_001B09F8;
    int colors[5];
    unsigned char *vars = *(unsigned char **)(controller+0x68);
    int frame,i,j,right,fadeInStart,fadeInEnd,fadeOutStart,fadeOutEnd;
    int sprite,bannerSprite;
    float angle, sine, sign, leftX, innerX;
    int one, top, off;
    if (controller[0xbc]==3 || controller[0xbc]==4 || controller[0xbc]==1 || controller[0xbc]==2) frame=150-*(int *)(vars+0x394);
    else frame=g_race_time_ticks+150;
    if (!D_L04_001A904C) return;
    for(i=0;i<5;i++) {
        if(i==4) { fadeInStart=120;fadeInEnd=149;do{fadeOutStart=156;}while(0);fadeOutEnd=171; }
        else { j=i*30; fadeInStart=j;fadeInEnd=fadeInStart+30;fadeOutEnd=fadeInStart+45;fadeOutStart=fadeInEnd; }
        colors[i]=0;
        if(frame>=fadeInStart && frame<fadeInEnd) colors[i]=FastTweenColor(0,start.v[i],(float)(frame-fadeInStart)*0.033333335f);
        else if(frame>=fadeInEnd && frame<fadeOutStart && fadeInEnd!=fadeOutStart) colors[i]=start.v[i];
        else if(frame>=fadeOutStart && frame<fadeOutEnd) colors[i]=FastTweenColor(start.v[i],end.v[i],(float)(frame-fadeOutStart)*0.06666667f);
        else if(frame>=fadeOutEnd) colors[i]=end.v[i];
    }
    i=0;
    off=0x8710;
    angle=0.56217057f;
    sine=math_fast_sin_or_cos_b(angle);
    sine=sine/math_fast_sin_or_cos_a(angle);
    D_L04_001BDB80.tan_half=sine;
    UpdateViewContext();

    one=1;
    for(;i<2;i++) {
        if(i==0) {j=10;right=31;sign=1.0f;} else {j=498;right=478;sign=-1.0f;}
        leftX=(float)j;
        bannerSprite=table_find_by_id((char *)D_L04_001A904C+off,58);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        gfx_draw_scaled_object_two_axes(bannerSprite,(float)j,0x60442d00,(float)top,sign,1.0f,0.0f);
        sprite=table_find_by_id((char *)D_L04_001A904C+off,59);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        gfx_draw_scaled_object_two_axes(sprite,(float)j,0x55f0c070,(float)top,sign,1.0f,0.0f);
        sprite=table_find_by_id((char *)D_L04_001A904C+off,60);
        gfx_draw_scaled_object_two_axes(sprite,leftX,0x55f0c070,(float)hud_coord(120.0f,D_L04_001B2D44,0.5f,one),sign,1.0f,0.0f);
        innerX=(float)right;
        for(j=0;j<5;j++) {
            gfx_draw_scaled_object_two_axes(table_find_by_id((char *)D_L04_001A904C+0x8710,61),innerX,colors[j],(float)(g_is_pal_video?y.v[j]:x.v[j]),0.8f,0.8f,0.0f);
        }
        VU1_addGSregister(71,0x5360b);
    }
    if(controller[0x20]!=3) {
        float turn, ratio;
        turn=*(float *)(vars+0x28c);
        turn*=0.008726647f;
        ratio=math_fast_sin_or_cos_b(turn);
        ratio=ratio/math_fast_sin_or_cos_a(turn);
        D_L04_001BDB80.tan_half=ratio;
        UpdateViewContext();
    }
}
