#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

typedef struct { unsigned char pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long header[4]; } QuadPayload;
typedef union { QuadPacket raw; QuadPayload view; } BeamPacket;
typedef struct { Vector128 start,next,ray,firstSide,secondSide,step; BeamPacket packet; Vector128 scratch; } BeamWorkspace;
extern Vector128 D_L18_002A08C0[11],D_L18_002A0970[11];
extern char D_L18_001B97C0[];
extern float D_L18_001B0534[] MACRO_ADDR;
extern float D_L18_001B0530[4][2] __attribute__((sda));
extern unsigned int D_L18_001B0550 __attribute__((sda)),D_L18_001B0554 __attribute__((sda));
extern float D_L18_001B0558 __attribute__((sda));
extern float D_L18_001B0560[] __attribute__((sda));
extern float D_L18_001B0568 __attribute__((sda)),D_L18_001B056C __attribute__((sda)),D_L18_001B0570 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00281DE8(QuadPacket *,int,int,int);
extern void func_00280B90(void *,void *,int);
/* Gives the two outer vertices of the beam's first or last segment the
 * alpha-free colour, which fades both ends of the beam out. */
static __inline__ void BeamFadeEnds(BeamPacket *packet,unsigned int rgb,const int *segment)
{
    if(*segment==0) {
        packet->view.colors[0]=rgb;
        packet->view.colors[1]=rgb;
    } else if((float)*segment==D_L18_001B0570-1.0f) {
        packet->view.colors[2]=rgb;
        packet->view.colors[3]=rgb;
    }
}
/* Draws a set of jagged glowing beams that slide along their length and fade at both ends. */
void func_L18_003FAE50(char *object)
{
    BeamWorkspace local;
    char *state=*(char **)(object+0x68);
    unsigned int faded,rgb,endColor;
    float alpha;
    unsigned int alphaByte,sourceColor;
    int beam,i;
    for(beam=0;beam<11;beam++) {
        qcopy(&local.start,&D_L18_002A08C0[beam]);
        FastVecSub(&local.step,&D_L18_002A0970[beam],&local.start);
        FastVecScale(&local.step,&local.step,1.0f/D_L18_001B0570);
        FastVecAdd(&local.next,&local.start,&local.step);
        alpha=RandomFloatRange(D_L18_001B0560[0],D_L18_001B0560[1]);
        sourceColor=D_L18_001B0550;
        alphaByte=sourceColor>>24;
        faded=sourceColor&0xffffffu;
        faded|=(unsigned int)(int)(alpha*(float)(int)alphaByte)<<24;
        {
        int segment;
        for(segment=0;(float)segment<D_L18_001B0570;) {
            rgb=faded&0xffffffu;
            FastVecSub(&local.ray,&local.start,&local.next);
            FastVecSub(&local.firstSide,&local.start,gCameraPosition_L18);
            FastVecSub(&local.secondSide,&local.next,gCameraPosition_L18);
            FastVecCross(&local.firstSide,&local.firstSide,&local.ray);
            FastVecCross(&local.secondSide,&local.secondSide,&local.ray);
            vec_scale_to_length(&local.firstSide,&local.firstSide,D_L18_001B0568);
            vec_scale_to_length(&local.secondSide,&local.secondSide,D_L18_001B0568);
            InitQuadPacketState(&local.packet.raw,0x17,1,0x80);
            local.packet.view.colors[3]=faded;
            local.packet.view.colors[2]=faded;
            local.packet.view.colors[1]=faded;
            local.packet.view.colors[0]=faded;
            {
            int index=segment;
            BeamFadeEnds(&local.packet,rgb,&segment);
            for(i=0;i<4;i++) {
                local.packet.view.uv[i][0]=D_L18_001B0530[i][0]+*(float *)(state+0x8c);
                local.packet.view.uv[i][1]=D_L18_001B0534[i*2];
            }
            FastVecSub(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            FastVecAdd(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            FastVecSub(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            FastVecAdd(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            draw_world_quad(&local.packet.raw,0,0);
            vec_scale_to_length(&local.firstSide,&local.firstSide,D_L18_001B056C);
            vec_scale_to_length(&local.secondSide,&local.secondSide,D_L18_001B056C);
            FastVecSub(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            FastVecAdd(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            FastVecSub(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            FastVecAdd(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            InitQuadPacketState(&local.packet.raw,0x2b,1,0x80);
            endColor=D_L18_001B0554;
            local.packet.view.colors[3]=endColor;
            local.packet.view.colors[2]=endColor;
            local.packet.view.colors[1]=endColor;
            local.packet.view.colors[0]=endColor;
            if(segment==0) {
                local.packet.view.colors[0]=endColor&0xffffffu;
                local.packet.view.colors[1]=endColor&0xffffffu;
            } else if((float)segment==D_L18_001B0570-1.0f) {
                local.packet.view.colors[2]=endColor&0xffffffu;
                local.packet.view.colors[3]=endColor&0xffffffu;
            }
            segment=index+1;
            }
            draw_world_quad(&local.packet.raw,0,0);
            qcopy(&local.start,&local.next);
            FastVecAdd(&local.next,&local.next,&local.step);
        }
        }
    }
    *(float *)(state+0x8c)+=D_L18_001B0558;
    if(*(float *)(state+0x8c)>1.0f) *(float *)(state+0x8c)-=2.0f;
    if(*(float *)(state+0x8c)<-1.0f) *(float *)(state+0x8c)+=2.0f;
}
