#include "common.h"
extern float FastAddRotations(float,float),math_random_angle(void);
extern int math_random_int_range(int,int);
extern void gfx_draw_billboard_quad(void *,int,unsigned int,int,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern int g_glow_spark_texture_main __attribute__((sda));
extern int g_glow_spark_texture_alt __attribute__((sda));
extern int g_glow_spark_color_low __attribute__((sda));
extern int g_glow_spark_color_min __attribute__((sda));
extern int g_glow_spark_color_max __attribute__((sda));
extern int g_glow_spark_alt_color __attribute__((sda));
extern float g_glow_spark_spin_rate __attribute__((sda));
extern float g_glow_spark_main_size __attribute__((sda));
extern float g_glow_spark_alt_size __attribute__((sda));

/* Draws the sparkling glow and sparks around a flying shot. */
void shot_draw_glow_sparks(char *obj)
{
    float tmp[4];
    char *ctx=*(char **)(obj+104);
    char *pos=obj+16;
    unsigned int color;
    *(float *)(ctx+28)=FastAddRotations(*(float *)(ctx+28),g_glow_spark_spin_rate*0.017453294f);
    color=math_random_int_range(g_glow_spark_color_min,g_glow_spark_color_max);
    color=(color<<24)|g_glow_spark_color_low;
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_main,color,1,g_glow_spark_main_size,0.08f,-*(float *)(ctx+28));
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_main,color,1,g_glow_spark_main_size,0.08f,*(float *)(ctx+28));
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_main,color,1,g_glow_spark_main_size,0.08f,FastAddRotations(*(float *)(ctx+28)*2.0f,0.0f));
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_alt,g_glow_spark_alt_color,1,g_glow_spark_alt_size,0.08f,FastAddRotations(-*(float *)(ctx+28)*1.5f,0.0f));
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_alt,g_glow_spark_alt_color,1,g_glow_spark_alt_size,0.08f,*(float *)(ctx+28)*0.5f);
    gfx_draw_billboard_quad(pos,g_glow_spark_texture_alt,g_glow_spark_alt_color,1,g_glow_spark_alt_size,0.08f,FastAddRotations(*(float *)(ctx+28)*2.5f,0.0f));
    gfx_draw_billboard_quad(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*0.5f);
    gfx_draw_billboard_quad(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*-0.5f);
    gfx_draw_billboard_quad(pos,47,0x507f7f7f,1,0.1f,0.08f,math_random_angle());
    FastVecAdd(tmp,pos,ctx+32);
    gfx_draw_billboard_quad(tmp,47,0x507f7f7f,1,0.09f,0.08f,math_random_angle());
}
