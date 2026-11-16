#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
typedef struct { u8 pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef struct { Quad128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long header[4]; } StripPayload;
typedef union { QuadPacket raw; StripPayload view; } StripPacket;
typedef unsigned int Rac2Native_9da4b6b15b3cf4a0_RecordWord180;
typedef unsigned long long Rac2Native_9da4b6b15b3cf4a0_RecordValue180;
extern u8 *level_get_slot_body(int id, int index);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern void VU1_addGSregister(Rac2Native_9da4b6b15b3cf4a0_RecordWord180,Rac2Native_9da4b6b15b3cf4a0_RecordValue180);
extern void gfx_init_quad_packet_state(QuadPacket *,int,int,int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void draw_world_quad(void *,void *,int);

/* Draws the trail strip along the owner table path, fading the alpha near the end of its life. */
void rocket_draw_ribbon_strip_pal(void *self,int color,int alpha)
{
    StripPacket packet;
    Quad128 direction,side;
    char *object=self,*state=*(char **)(object+0x68);
    Quad128 **table;
    int index;
    float fraction,uvStep,width;
    table=(Quad128 **)level_get_slot_body(*(int *)(state+0x50),*(int *)(state+0x3c));
    if(!table) { table_clear_entry_flag(*(int *)(state+0x6c)); moby_mark_spawned(object); return; }
    if(*(int *)(state+0x54)<3) return;
    VU1_addGSregister(0x47,0x5360bULL);
    gfx_init_quad_packet_state(&packet.raw,11,1,128);
    packet.view.uv[0][0]=0; packet.view.uv[0][1]=0;
    packet.view.uv[1][0]=0; packet.view.uv[1][1]=1;
    packet.view.uv[2][0]=0.5f; packet.view.uv[2][1]=0;
    packet.view.uv[3][0]=0.5f; packet.view.uv[3][1]=1;
    if(*(short *)(state+0x10)>233) {
        fraction=IntToFloat(250-*(short *)(state+0x10)); fraction/=IntToFloat(17);
        alpha=FloatToInt(IntToFloat(alpha)*fraction);
    }
    packet.view.colors[3]=color|alpha<<24; packet.view.colors[2]=color|alpha<<24; packet.view.colors[1]=color|alpha<<24; packet.view.colors[0]=color|alpha<<24;
    width=0.5f; if(!*(int *)(state+0x68)) width=0.25f;
    FastVecSub(&direction,object+0x10,table[*(int *)(state+0x30)]);
    FastVecCross(&side,&direction,object+0xe0); vec_scale_to_length(&side,&side,width);
    FastVecAdd(&packet.view.vertices[0],object+0x10,&side); FastVecSub(&packet.view.vertices[1],object+0x10,&side);
    uvStep=0.5f/IntToFloat(*(int *)(state+0x54)-2);
    for(index=0;index<*(int *)(state+0x54);index++) {
        if(index>0) FastVecSub(&direction,&table[*(int *)(state+0x30)][index-1],table[*(int *)(state+0x30)]+index);
        FastVecCross(&side,&direction,object+0xe0); vec_scale_to_length(&side,&side,width);
        FastVecAdd(&packet.view.vertices[2],table[*(int *)(state+0x30)]+index,&side);
        FastVecSub(&packet.view.vertices[3],table[*(int *)(state+0x30)]+index,&side);
        draw_world_quad(&packet,0,0);
        packet.view.vertices[0]=packet.view.vertices[2]; packet.view.vertices[1]=packet.view.vertices[3];
        packet.view.uv[0][0]=packet.view.uv[2][0]; packet.view.uv[1][0]=packet.view.uv[3][0];
        packet.view.uv[2][0]+=uvStep; packet.view.uv[3][0]+=uvStep;
    }
}
