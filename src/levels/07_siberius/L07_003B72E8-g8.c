#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct BeamPacket72E8 {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    u64 state[4];
} BeamPacket72E8;
extern float math_random_float_range(float,float);
extern int FastTweenColor(int,int,float);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *,int,int,int,float,float,float);
extern void vec_copy_helper_a(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void gfx_init_quad_packet_state(void *,int,int,int);
extern float IntToFloat(int);
extern void draw_world_quad(void *,void *,int);
extern char D_L07_001B9200[];
extern float D_L07_001AFF00[][2] SDATA(D_L07_001AFF00);
extern float D_L07_001AFF04[][2] __attribute__((sda));
extern int D_L07_001AFF20 __attribute__((sda));
extern float D_L07_001AFF24 __attribute__((sda));
extern float D_L07_001AFF28 __attribute__((sda));
extern int D_L07_001AFF30[] __attribute__((sda));
extern int D_L07_001AFF30_gp[] SDATA(D_L07_001AFF30);
/* Emits four particles at the actor, then builds two quads and draws them once per D_L07_001AFF20
   step, fading between the state's two phase colours. `alpha` also supplies the w of both end vectors. */
/* Draws a glowing beam effect that fades its colours over time, with a few sparks at the
   object. */
void gfx_draw_fading_beam_pair(char *moby)
{
    float matrix[4][4] __attribute__((aligned(16)));
    BeamPacket72E8 beam[2] __attribute__((aligned(16)));
    float phase[2];
    float ends[2][4] __attribute__((aligned(16)));
    float temp[2][4] __attribute__((aligned(16)));
    char *vars=*(char **)(moby+0x68);
    char *pos=moby+0x10;
    int color;
    float rotation,step,alpha;
    color=FastTweenColor(0x50103080,0x60103080,math_random_float_range(0,1));
    rotation=math_random_angle();
    gfx_draw_billboard_quad(pos,0x31,color,1,1,0,rotation);
    color=FastTweenColor(0x50FFFFFF,0x60FFFFFF,math_random_float_range(0,1));
    rotation=math_random_angle();
    gfx_draw_billboard_quad(pos,0x31,color,1,0.6f,0,rotation);
    color=FastTweenColor(0x08803010,0x18803010,math_random_float_range(0,1));
    rotation=math_random_angle();
    gfx_draw_billboard_quad(pos,0xB,color,1,1.4f,0,rotation);
    color=FastTweenColor(0x20803010,0x40803010,math_random_float_range(0,1));
    rotation=math_random_angle();
    gfx_draw_billboard_quad(pos,0xB,color,1,0.9f,0,rotation);
    qcopy(matrix[3],pos);
    matrix[3][3]=1;
    vec_copy_helper_a(matrix[2]);
    FastVecSub(matrix[1],D_L07_001B9200,pos);
    matrix[1][2]=0;
    vec_scale_to_length(matrix[1],matrix[1],1);
    FastVecCross(matrix[0],matrix[1],matrix[2]);
    gfx_init_quad_packet_state(&beam[0],0x2F,1,0x80);
    gfx_init_quad_packet_state(&beam[1],0x2F,1,0x80);
    phase[0]=*(float *)(vars+0x30);
    phase[1]=*(float *)(vars+0x30)+0.5f;
    if(phase[1]>1) phase[1]-=1;
    *(u128 *)temp[0]=0;
    *(u128 *)temp[1]=0;
    alpha=1;
    temp[0][3]=alpha;
    temp[1][3]=alpha;
    temp[0][0]=D_L07_001AFF28*phase[0];
    temp[1][0]=D_L07_001AFF28*phase[1];
    *(u128 *)ends[0]=*(u128 *)temp[0];
    *(u128 *)ends[1]=*(u128 *)temp[1];
    { int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<2;j++) {
            qcopy(beam[j].pos[i],ends[j]);
            if(i&1) beam[j].pos[i][0]=-beam[j].pos[i][0];
            beam[j].uv[i][0]=D_L07_001AFF00[i][0]+(*(float *)(vars+0x2C)+j*0.5f);
            beam[j].uv[i][1]=D_L07_001AFF04[i][0];
        }
    }
    }
    alpha=1;
    step=alpha/IntToFloat(D_L07_001AFF20);
    ((int *)temp)[0]=FastTweenColor(D_L07_001AFF30_gp[0],D_L07_001AFF30[1],phase[0]);
    ((int *)temp)[1]=FastTweenColor(D_L07_001AFF30_gp[0],D_L07_001AFF30[1],phase[1]);
    if(*(float *)(vars+0x34)<alpha) {
        ((int *)temp)[0]=FastTweenColor(((int *)temp)[0]&0xFFFFFF,((int *)temp)[0],*(float *)(vars+0x34));
        ((int *)temp)[1]=FastTweenColor(((int *)temp)[1]&0xFFFFFF,((int *)temp)[1],*(float *)(vars+0x34));
    }
    { int i,j;
    for(i=0;i<D_L07_001AFF20;i++) {
        float next=alpha-step;
        int *colors=(int *)temp;
        for(j=0;j<2;j++) {
            int col;
            beam[j].pos[2][2]-=D_L07_001AFF24;
            beam[j].pos[3][2]-=D_L07_001AFF24;
            col=FastTweenColor(colors[j]&0xFFFFFF,colors[j],alpha);
            beam[j].color[1]=col;
            beam[j].color[0]=col;
            col=FastTweenColor(colors[j]&0xFFFFFF,colors[j],next);
            beam[j].color[3]=col;
            beam[j].color[2]=col;
            draw_world_quad(&beam[j],matrix,0);
            beam[j].pos[0][2]-=D_L07_001AFF24;
            beam[j].pos[1][2]-=D_L07_001AFF24;
        }
        alpha=next;
    }
    }
}
