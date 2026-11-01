#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
typedef struct { u8 pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef struct { Quad128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long header[4]; } StripPayload;
typedef union { QuadPacket raw; StripPayload view; } StripPacket;
typedef unsigned int Rac2Native_9da4b6b15b3cf4a0_RecordWord180;
typedef unsigned long long Rac2Native_9da4b6b15b3cf4a0_RecordValue180;
extern int func_L00_0032A088(int id, int index);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void func_002FC560(Rac2Native_9da4b6b15b3cf4a0_RecordWord180,Rac2Native_9da4b6b15b3cf4a0_RecordValue180);
extern void func_00281DE8(QuadPacket *,int,int,int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00280B90(void *,void *,int);

/* Draws the trail strip along the owner table path, fading the alpha near the end of its life. */
void func_PAL_L00_00423918(void *self,int color,int alpha)
{
    StripPacket packet;
    Quad128 direction,side;
    char *object=self,*state=*(char **)(object+0x68);
    Quad128 **table;
    int index;
    float fraction,uvStep,width;
    table=(Quad128 **)func_L00_0032A088(*(int *)(state+0x50),*(int *)(state+0x3c));
    if(!table) { func_002FEE50(*(int *)(state+0x6c)); func_0029F338(object); return; }
    if(*(int *)(state+0x54)<3) return;
    func_002FC560(0x47,0x5360bULL);
    func_00281DE8(&packet.raw,11,1,128);
    packet.view.uv[0][0]=0; packet.view.uv[0][1]=0;
    packet.view.uv[1][0]=0; packet.view.uv[1][1]=1;
    packet.view.uv[2][0]=0.5f; packet.view.uv[2][1]=0;
    packet.view.uv[3][0]=0.5f; packet.view.uv[3][1]=1;
    if(*(short *)(state+0x10)>233) {
        fraction=func_00283CE0(250-*(short *)(state+0x10)); fraction/=func_00283CE0(17);
        alpha=func_00283CF0(func_00283CE0(alpha)*fraction);
    }
    packet.view.colors[3]=color|alpha<<24; packet.view.colors[2]=color|alpha<<24; packet.view.colors[1]=color|alpha<<24; packet.view.colors[0]=color|alpha<<24;
    width=0.5f; if(!*(int *)(state+0x68)) width=0.25f;
    func_00282CF0(&direction,object+0x10,table[*(int *)(state+0x30)]);
    func_00282DD8(&side,&direction,object+0xe0); func_00282F20(&side,&side,width);
    func_00282CC0(&packet.view.vertices[0],object+0x10,&side); func_00282CF0(&packet.view.vertices[1],object+0x10,&side);
    uvStep=0.5f/func_00283CE0(*(int *)(state+0x54)-2);
    for(index=0;index<*(int *)(state+0x54);index++) {
        if(index>0) func_00282CF0(&direction,&table[*(int *)(state+0x30)][index-1],table[*(int *)(state+0x30)]+index);
        func_00282DD8(&side,&direction,object+0xe0); func_00282F20(&side,&side,width);
        func_00282CC0(&packet.view.vertices[2],table[*(int *)(state+0x30)]+index,&side);
        func_00282CF0(&packet.view.vertices[3],table[*(int *)(state+0x30)]+index,&side);
        func_00280B90(&packet,0,0);
        packet.view.vertices[0]=packet.view.vertices[2]; packet.view.vertices[1]=packet.view.vertices[3];
        packet.view.uv[0][0]=packet.view.uv[2][0]; packet.view.uv[1][0]=packet.view.uv[3][0];
        packet.view.uv[2][0]+=uvStep; packet.view.uv[3][0]+=uvStep;
    }
}
