#include "common.h"
extern float FastAddRotations(float,float),math_random_angle(void);
extern int math_random_int_range(int,int);
extern void gfx_draw_billboard_quad(void *,int,unsigned int,int,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern int D_L00_001B0E00 __attribute__((sda));
extern int D_L00_001B0E04 __attribute__((sda));
extern int D_L00_001B0E08 __attribute__((sda));
extern int D_L00_001B0E0C __attribute__((sda));
extern int D_L00_001B0E10 __attribute__((sda));
extern int D_L00_001B0E14 __attribute__((sda));
extern float D_L00_001B0E18 __attribute__((sda));
extern float D_L00_001B0E1C __attribute__((sda));
extern float D_L00_001B0E20 __attribute__((sda));

/* Draws the sparkling glow and sparks around a flying shot. */
void shot_draw_glow_sparks(char *obj)
{
    float tmp[4];
    char *ctx=*(char **)(obj+104);
    char *pos=obj+16;
    unsigned int color;
    *(float *)(ctx+28)=FastAddRotations(*(float *)(ctx+28),D_L00_001B0E18*0.017453294f);
    color=math_random_int_range(D_L00_001B0E0C,D_L00_001B0E10);
    color=(color<<24)|D_L00_001B0E08;
    gfx_draw_billboard_quad(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,-*(float *)(ctx+28));
    gfx_draw_billboard_quad(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,*(float *)(ctx+28));
    gfx_draw_billboard_quad(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,FastAddRotations(*(float *)(ctx+28)*2.0f,0.0f));
    gfx_draw_billboard_quad(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,FastAddRotations(-*(float *)(ctx+28)*1.5f,0.0f));
    gfx_draw_billboard_quad(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,*(float *)(ctx+28)*0.5f);
    gfx_draw_billboard_quad(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,FastAddRotations(*(float *)(ctx+28)*2.5f,0.0f));
    gfx_draw_billboard_quad(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*0.5f);
    gfx_draw_billboard_quad(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*-0.5f);
    gfx_draw_billboard_quad(pos,47,0x507f7f7f,1,0.1f,0.08f,math_random_angle());
    FastVecAdd(tmp,pos,ctx+32);
    gfx_draw_billboard_quad(tmp,47,0x507f7f7f,1,0.09f,0.08f,math_random_angle());
}
