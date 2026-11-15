#include "common.h"
typedef struct { float position[4]; short life,alpha; int unused; float angle,size; } Glow;
extern Glow D_001BAA40[];
extern char g_camera_eye_state[], D_001AC8B0[];
extern char D_001B91C0[];
typedef struct { char pad[0x1a8]; float depth; char gap[0x64]; float scale; } GlowView;
extern GlowView D_001B9040;
/* The packet cursor: retail rereads it after every store through it, as for an array element. */
extern int *g_dma_packet_cursor[] __attribute__((section(".sdata")));
extern void VU1_addGSregister(unsigned int,unsigned long);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *,void *,float);
extern void transform_vector(void *,void *,void *);
extern void multiply_vector_components(void *,void *,void *);
extern int is_vector_outside_clip(void *);
extern void mem_clear(void *,int,int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern unsigned long GetEffectTextureDescriptor(int);
/* Draws the 16 glow slots as rotated quads, clearing any slot that clips. */
void DrawGlowSprites(void) {
    float v[4],clip[4];
    int i;
    Glow *g,*table;
    float distance,radius;
    unsigned long center,color;
    long x,y;
    int dx,dy;
    int *base;
    unsigned long *packet;
    VU1_addGSregister(0x42,0x8000000048UL);
    for(i=0;i<16;i++) {
        table=D_001BAA40;
        g=&table[i];
        if(g->life<=0) continue;
        FastVecSub(v,g,g_camera_eye_state);
        v[3]=1.0f;
        distance=FastVecLength(v);
        FastVecScale(v,v,1024.0f);
        transform_vector(v,v,g_camera_eye_state-0x100);
        multiply_vector_components(clip,v,D_001B91C0);
        if(is_vector_outside_clip(clip)) { mem_clear(g,0,32); continue; }
        FastVecScale(v,v,D_001B9040.scale/v[3]);
        color=(g->alpha<<24)|0x808080;
        x=FloatToInt(v[0]*16.0f)+0x8000;
        y=FloatToInt(v[1]*16.0f)+0x8000;
        center=((unsigned long)FloatToInt(v[2]*0.9997f+D_001B9040.depth)<<32)|((unsigned long)y<<16)|(unsigned long)x;
        if(distance>18.0f) distance=18.0f;
        else if(distance<2.0f) distance=2.0f;
        radius=g->size*0.015625f*IntToFloat(g->alpha+16);
        radius=radius*16.0f*(24.0f-distance);
        dx=FloatToInt(radius*math_fast_sin_or_cos_b(g->angle));
        dy=FloatToInt(radius*math_fast_sin_or_cos_a(g->angle));
        g_dma_packet_cursor[0][0]=0x10000009; g_dma_packet_cursor[0][1]=0; g_dma_packet_cursor[0][2]=0; g_dma_packet_cursor[0][3]=0x50000009;
        base=g_dma_packet_cursor[0];
        g_dma_packet_cursor[0]=base+4;
        qcopy(base+4,D_001AC8B0);
        packet=(unsigned long *)(base+8);
        g_dma_packet_cursor[0]=(int *)packet;
        packet[0]=5;
        packet[1]=GetEffectTextureDescriptor(19);
        packet[2]=0x154;
        packet[3]=color;
        packet[4]=0;
        packet[5]=center+(dy<<16)+dx;
        packet[6]=color;
        packet[7]=0x200;
        packet[8]=center+((-dx)<<16)+dy;
        packet[9]=color;
        packet[10]=0x2000000;
        packet[11]=center+(dx<<16)-dy;
        packet[12]=color;
        packet[13]=0x2000200;
        packet[14]=center+((-dy)<<16)-dx;
        packet[15]=0;
        g_dma_packet_cursor[0]+=32;
    }
    VU1_addGSregister(0x42,0x8000000044UL);
}
