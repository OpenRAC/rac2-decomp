/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), task v1028, 29 October 2026. Nonmatching.
 * Pinned upstream profile: -O2 -G32 -Wa,-G32 -ffunction-sections.
 * USA v1.01: 1208/1208 bytes, 0 of 3 places match; first mismatch +0x50.
 * Replaces the previous 1216-byte draft. All declarations are retained below.
 * Compute RGB from the faded color inside the segment loop: this prevents the
 * outer mask hoist and recovers the inner loop's saved-register assignments.
 * Snapshot the original color separately, then update the named faded value.
 * V coordinates use the actual overlapping D_L18_001B0534 view with nosda;
 * U coordinates retain the gp-relative D_L18_001B0530 view.
 * Incrementing segment before the second draw recovers its earlier reload.
 * Remaining: next-vector/segment spill slots are exchanged (0x110/0x114),
 * absolute f13 load setup, UV cursor allocation, and the first end-cap bc1fl.
 * Ordinary initial vector copy, explicit vector pointers and UV cursors worsen
 * the instruction match; no-gcse/strength-reduce/loop-pass changes do not fix it.
 * The previous -mno-split-addresses profile improves UV allocation but worsens
 * endpoint address scheduling. Reopen with lifetime evidence for those cursors.
 * No linked build or runtime validation; US2/PAL not checked in this task.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));

typedef struct { unsigned char pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long header[4]; } QuadPayload;
typedef union { QuadPacket raw; QuadPayload view; } BeamPacket;
typedef struct { Vector128 start,next,ray,firstSide,secondSide,step; BeamPacket packet; Vector128 scratch; } BeamWorkspace;
extern Vector128 D_L18_002A08C0[11],D_L18_002A0970[11];
extern char D_L18_001B97C0[];
extern float D_L18_001B0534[7] __attribute__((nosda));
extern float D_L18_001B0530[4][2] __attribute__((sda));
extern unsigned int D_L18_001B0550 __attribute__((sda)),D_L18_001B0554 __attribute__((sda));
extern float D_L18_001B0558 __attribute__((sda)),D_L18_001B0560 __attribute__((sda)),D_L18_001B0564 __attribute__((nosda));
extern float D_L18_001B0568 __attribute__((sda)),D_L18_001B056C __attribute__((sda)),D_L18_001B0570 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00281DE8(QuadPacket *,int,int,int);
extern void func_00280B90(void *,void *,int);
void func_L18_003FAE50(char *object)
{
    BeamWorkspace local;
    char *state=*(char **)(object+0x68);
    unsigned int faded,rgb,endColor;
    float alpha;
    unsigned int alphaByte,sourceColor;
    int beam,segment,i;
    for(beam=0;beam<11;beam++) {
        qcopy(&local.start,&D_L18_002A08C0[beam]);
        func_00282CF0(&local.step,&D_L18_002A0970[beam],&local.start);
        func_00282D30(&local.step,&local.step,1.0f/D_L18_001B0570);
        func_00282CC0(&local.next,&local.start,&local.step);
        alpha=func_002A7878(D_L18_001B0560,D_L18_001B0564);
        sourceColor=D_L18_001B0550;
        alphaByte=sourceColor>>24;
        faded=sourceColor&0xffffffu;
        faded|=(unsigned int)(int)(alpha*(float)(int)alphaByte)<<24;
        for(segment=0;(float)segment<D_L18_001B0570;) {
            rgb=faded&0xffffffu;
            func_00282CF0(&local.ray,&local.start,&local.next);
            func_00282CF0(&local.firstSide,&local.start,D_L18_001B97C0);
            func_00282CF0(&local.secondSide,&local.next,D_L18_001B97C0);
            func_00282DD8(&local.firstSide,&local.firstSide,&local.ray);
            func_00282DD8(&local.secondSide,&local.secondSide,&local.ray);
            func_00282F20(&local.firstSide,&local.firstSide,D_L18_001B0568);
            func_00282F20(&local.secondSide,&local.secondSide,D_L18_001B0568);
            func_00281DE8(&local.packet.raw,0x17,1,0x80);
            local.packet.view.colors[3]=faded;
            local.packet.view.colors[2]=faded;
            local.packet.view.colors[1]=faded;
            local.packet.view.colors[0]=faded;
            if(segment==0) {
                local.packet.view.colors[0]=rgb;
                local.packet.view.colors[1]=rgb;
            } else if((float)segment==D_L18_001B0570-1.0f) {
                local.packet.view.colors[2]=rgb;
                local.packet.view.colors[3]=rgb;
            }
            for(i=0;i<4;i++) {
                local.packet.view.uv[i][0]=D_L18_001B0530[i][0]+*(float *)(state+0x8c);
                local.packet.view.uv[i][1]=D_L18_001B0534[i*2];
            }
            func_00282CF0(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            func_00282CC0(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            func_00282CF0(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            func_00282CC0(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            func_00280B90(&local.packet.raw,0,0);
            func_00282F20(&local.firstSide,&local.firstSide,D_L18_001B056C);
            func_00282F20(&local.secondSide,&local.secondSide,D_L18_001B056C);
            func_00282CF0(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            func_00282CC0(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            func_00282CF0(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            func_00282CC0(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            func_00281DE8(&local.packet.raw,0x2b,1,0x80);
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
            segment++;
            func_00280B90(&local.packet.raw,0,0);
            qcopy(&local.start,&local.next);
            func_00282CC0(&local.next,&local.next,&local.step);
        }
    }
    *(float *)(state+0x8c)+=D_L18_001B0558;
    if(*(float *)(state+0x8c)>1.0f) *(float *)(state+0x8c)-=2.0f;
    if(*(float *)(state+0x8c)<-1.0f) *(float *)(state+0x8c)+=2.0f;
}
