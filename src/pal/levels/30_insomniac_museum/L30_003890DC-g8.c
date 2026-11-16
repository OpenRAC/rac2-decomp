#include "include_asm.h"

#include "common.h"
extern int g_vehicle_gauge_texture_left __attribute__((sda));
extern int g_vehicle_gauge_texture_needle __attribute__((sda));
extern int g_vehicle_gauge_texture_right __attribute__((sda));
extern int g_vehicle_gauge_color __attribute__((sda));
extern float g_vehicle_gauge_angle_scale __attribute__((sda));
extern float g_vehicle_gauge_angle_offset __attribute__((sda));
extern float g_vehicle_gauge_needle_scale __attribute__((sda));
extern float g_vehicle_gauge_needle_offset __attribute__((sda));
extern float g_vehicle_gauge_x __attribute__((sda));
extern float g_vehicle_l30_max_speed __attribute__((sda));
extern int g_screen_height;
extern u64 GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern float FastVecLength(void *),math_fabs(float),FastAddRotations(float,float);
extern void DrawTexturedQuad(int,int,int,int,int,int,int,int,s64,u64);
extern void AppendRotatedSpriteQuad(float,float,float,float,float,int,int,u64,unsigned,unsigned,int,int,float,float);

void hud_draw_vehicle_gauges_pal(char *obj) {
    char *st=*(char **)(obj+0x68);
    u64 texture=GetEffectTextureDescriptor(g_vehicle_gauge_texture_left+0x12);
    DrawTexturedQuad(FloatToInt(g_vehicle_gauge_x),g_screen_height-128,128,128,0,0,128,128,g_vehicle_gauge_color,texture);
    texture=GetEffectTextureDescriptor(g_vehicle_gauge_texture_needle+0x12);
    DrawTexturedQuad(FloatToInt(g_vehicle_gauge_x)+128,g_screen_height-128,128,128,0,0,128,128,g_vehicle_gauge_color,texture);
    texture=GetEffectTextureDescriptor(g_vehicle_gauge_texture_right+0x12);
    {
        float angle;
        angle=FastVecLength(st)*0.017453294f;
        { float numerator=g_vehicle_gauge_angle_scale*angle;
        angle=numerator/(g_vehicle_l30_max_speed*0.020000001f); }
        angle=FastAddRotations(angle,g_vehicle_gauge_angle_offset*0.017453294f);
        AppendRotatedSpriteQuad(g_vehicle_gauge_x+64,(float)(g_screen_height-64),64,64,angle,64,64,texture,0x00FFFFF3,0x60808080,0,0,0.5f,0.35f);
    }
    {
        float angle;
        angle=math_fabs(*(float *)(st+0x4C))*0.017453294f;
        { float scaled=g_vehicle_gauge_needle_scale*angle;
        angle=FastAddRotations(g_vehicle_gauge_needle_offset*0.017453294f,scaled); }
        AppendRotatedSpriteQuad(g_vehicle_gauge_x+128+64,(float)(g_screen_height-64),64,64,angle,64,64,texture,0x00FFFFF3,0x60808080,0,0,0.5f,0.35f);
    }
}
