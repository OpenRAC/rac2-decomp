#include "common.h"

extern void FastVecSub(void *,void *,void *),FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *),transform_vector(void *,void *,void *);
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,int,int);
extern float D_L11_001AEC88 __attribute__((sda)),D_L11_001AEC70 __attribute__((sda));
extern float D_L11_001AEC8C MACRO_ADDR,D_L11_001AEC90 MACRO_ADDR;
extern char D_L11_001BA8C0[],D_L11_001AA2D0[] __attribute__((sda));
typedef struct { float v[4][4]; u32 color[4]; float uv[7]; float param; u64 prim,texture,reg,tag; } QuadDrawPacket11;
/* Builds an oriented quad and submits it with texture IDs 11 and 6. */
/* Draws a flat glowing square that faces the player, using two textures. */
void gfx_draw_facing_quad(u8 *moby) {
 struct { float forward[4],side[4],up[4],position[4],direction[4],offset[4]; QuadDrawPacket11 draw; } frame;
 u8 *vars=*(u8 **)(moby+0x68); int i; float *out,*corners; QuadDrawPacket11 *draw;
 qcopy(frame.direction,moby+0xe0);qcopy(frame.position,moby+0x10);
 corners=(float *)D_L11_001AA2D0;
 FastVecSub(frame.forward,D_L11_001BA8C0,frame.position);
 i=3;
 vec_scale_to_length(frame.forward,frame.forward,1.0f);
 FastVecCross(frame.side,frame.forward,frame.direction);
 vec_scale_to_length(frame.side,frame.side,1.0f);
 FastVecCross(frame.up,frame.side,frame.forward);
 vec_scale_to_length(frame.forward,frame.forward,D_L11_001AEC88);
 vec_scale_to_length(frame.side,frame.side,D_L11_001AEC8C);
 vec_scale_to_length(frame.up,frame.up,D_L11_001AEC90);
 FastVecScale(frame.offset,frame.forward,D_L11_001AEC70);
 FastVecAdd(frame.position,frame.position,frame.offset);
 draw=&frame.draw;
 frame.draw.tag=0x8000000048ULL;
 frame.draw.reg=0xff9000000260ULL;
 frame.draw.prim=5;
 frame.draw.uv[0]=0;frame.draw.uv[1]=0;frame.draw.uv[2]=0;frame.draw.uv[3]=1;
 frame.draw.uv[4]=1;frame.draw.uv[5]=0;frame.draw.uv[6]=1.0f;
 frame.draw.param=1.0f;
 frame.draw.color[0]=frame.draw.color[1]=frame.draw.color[2]=frame.draw.color[3]=*(u32 *)(vars+0x30);
 out=draw->v[0];
 do {FastVecScale(out,corners,*(float *)(vars+0x2c));--i;corners+=4;transform_vector(out,out,frame.forward);out+=4;}while(i>=0);
 frame.draw.texture=GetEffectTextureDescriptor(11);draw_world_quad(draw,0,0);
 frame.draw.texture=GetEffectTextureDescriptor(6);draw_world_quad(draw,0,0);
}

