#include "common.h"
typedef int TrailQuad __attribute__((mode(TI)));
typedef union { TrailQuad quad; float f[4]; } TrailVector;
extern void func_00281DE8_7(void *, int, int, int);
extern int func_001163B0(void);
extern void func_00282CF0_7(void *, void *, void *);
extern void func_00282DD8_7(void *, void *, void *);
extern void func_00282F20_7(void *, void *, float);
extern void func_00282D30_7(void *, void *, float);
extern void func_002830C0_7(void *, void *, void *);
extern float func_00283CE0_7(int);
extern void func_00280B90_7(void *, void *, int);

extern float g_camera_l00_position[];
/* Draws a tapering two-layer ribbon along a list of points, with a fading end. */
void gfx_draw_tapered_ribbon(float tex, float width, float step, void *start, char *points, int color, int count)
{
    char origin[16] __attribute__((aligned(16)));
    char corePacket[144] __attribute__((aligned(16)));
    char outerPacket[144] __attribute__((aligned(16)));
    float matrix[16];
    TrailVector offsets[2];
    int i;
    int coreColor, outerColor;
    char *basis = origin;
    float texEnd, texStart, lastStart, lastEnd;
    *(TrailQuad *)origin = *(TrailQuad *)start;
    func_00281DE8_7(corePacket,43,1,128);
    func_00281DE8_7(outerPacket,43,1,128);
    offsets[0].quad=0; offsets[1].quad=0;
    width *= .25f;
    *(int *)(corePacket+64)=*(int *)(corePacket+68)=color;
    *(int *)(outerPacket+64)=*(int *)(outerPacket+68)=color;
    *(int *)(corePacket+72)=*(int *)(corePacket+76)=color;
    *(int *)(outerPacket+72)=*(int *)(outerPacket+76)=color;
    offsets[0].f[3]=1;
    offsets[1].f[3]=1;
    offsets[0].f[2]=width;
    offsets[1].f[2]=width+width;
    if (!(func_001163B0()&1)) {
        *(float *)(corePacket+80)=tex; *(float *)(corePacket+84)=0; *(float *)(corePacket+88)=tex; *(float *)(corePacket+92)=1;
        *(float *)(corePacket+96)=step+tex; *(float *)(corePacket+100)=0; *(float *)(corePacket+104)=step+tex; *(float *)(corePacket+108)=1;
        *(float *)(outerPacket+80)=tex; *(float *)(outerPacket+84)=0; *(float *)(outerPacket+88)=tex; *(float *)(outerPacket+92)=1;
        *(float *)(outerPacket+96)=step+tex; *(float *)(outerPacket+100)=0; *(float *)(outerPacket+104)=step+tex; *(float *)(outerPacket+108)=1;
    } else {
        *(float *)(corePacket+80)=tex; *(float *)(corePacket+84)=1; *(float *)(corePacket+88)=tex; *(float *)(corePacket+92)=0;
        *(float *)(corePacket+96)=step+tex; *(float *)(corePacket+100)=1; *(float *)(corePacket+104)=step+tex; *(float *)(corePacket+108)=0;
        *(float *)(outerPacket+80)=tex; *(float *)(outerPacket+84)=1; *(float *)(outerPacket+88)=tex; *(float *)(outerPacket+92)=0;
        *(float *)(outerPacket+96)=step+tex; *(float *)(outerPacket+100)=1; *(float *)(outerPacket+104)=step+tex; *(float *)(outerPacket+108)=0;
    }
    func_00282CF0_7(matrix,points,basis); func_00282F20_7(matrix,matrix,1);
    func_00282CF0_7(matrix+4,g_camera_l00_position,basis);
    func_00282DD8_7(matrix+8,matrix+4,matrix); func_00282F20_7(matrix+8,matrix+8,1); func_00282DD8_7(matrix+4,matrix,matrix+8);
    qcopy(matrix+12,basis);
    qcopy(corePacket,offsets); qcopy(outerPacket,offsets+1);
    func_00282D30_7(corePacket+16,corePacket,-1); func_00282D30_7(outerPacket+16,outerPacket,-1);
    func_002830C0_7(corePacket,corePacket,matrix); func_002830C0_7(corePacket+16,corePacket+16,matrix); func_002830C0_7(outerPacket,outerPacket,matrix); func_002830C0_7(outerPacket+16,outerPacket+16,matrix);
    for(i=0;i<count-1;i++) {
        coreColor=color|0x7f000000; outerColor=color|0x3f000000;
basis = (char *)matrix;
        func_00282CF0_7(basis,points+(i*16+16),points+i*16); func_00282F20_7(basis,basis,1);
        func_00282CF0_7(basis+16,g_camera_l00_position,points+i*16);
        func_00282DD8_7(basis+32,basis+16,basis); func_00282F20_7(basis+32,basis+32,1); func_00282DD8_7(basis+16,basis,basis+32);
        qcopy(basis+48,points+i*16);
        offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
        qcopy(corePacket+32,offsets); qcopy(outerPacket+32,offsets+1);
        func_00282D30_7(corePacket+48,corePacket+32,-1); func_00282D30_7(outerPacket+48,outerPacket+32,-1);
        func_002830C0_7(corePacket+32,corePacket+32,basis); func_002830C0_7(corePacket+48,corePacket+48,basis); func_002830C0_7(outerPacket+32,outerPacket+32,basis); func_002830C0_7(outerPacket+48,outerPacket+48,basis);
        texStart=step*func_00283CE0_7(i+1); texEnd=texStart+step; if(texStart>=1) {texStart-=1;texEnd-=1;}
*(float *)(corePacket+80)=texStart+tex; *(float *)(corePacket+88)=texStart+tex; *(float *)(corePacket+96)=texEnd+tex; *(float *)(corePacket+104)=texEnd+tex;
*(float *)(outerPacket+80)=texStart+tex; *(float *)(outerPacket+88)=texStart+tex; *(float *)(outerPacket+96)=texEnd+tex; *(float *)(outerPacket+104)=texEnd+tex;
        func_00280B90_7(corePacket,0,0); func_00280B90_7(outerPacket,0,0);
         if(i) { *(int *)(corePacket+68)=coreColor; *(int *)(corePacket+64)=coreColor; *(int *)(outerPacket+68)=outerColor; *(int *)(outerPacket+64)=outerColor; }
        *(int *)(corePacket+76)=coreColor; *(int *)(corePacket+72)=coreColor; *(int *)(outerPacket+76)=outerColor; *(int *)(outerPacket+72)=outerColor;
        qcopy(corePacket,corePacket+32);qcopy(corePacket+16,corePacket+48);qcopy(outerPacket,outerPacket+32);qcopy(outerPacket+16,outerPacket+48);
    }
    qcopy(matrix+12,points+(count-1)*16);
    offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
    qcopy(corePacket+32,offsets);qcopy(outerPacket+32,offsets+1);
    func_00282D30_7(corePacket+48,corePacket+32,-1);func_00282D30_7(outerPacket+48,outerPacket+32,-1);
    func_002830C0_7(corePacket+32,corePacket+32,matrix);func_002830C0_7(corePacket+48,corePacket+48,matrix);func_002830C0_7(outerPacket+32,outerPacket+32,matrix);func_002830C0_7(outerPacket+48,outerPacket+48,matrix);
    *(int *)(corePacket+76)=color; *(int *)(corePacket+72)=color; *(int *)(outerPacket+76)=color; *(int *)(outerPacket+72)=color;
    lastStart=step*func_00283CE0_7(i+1); lastEnd=lastStart+step; if(lastStart>=1) {lastStart-=1;lastEnd-=1;}
*(float *)(corePacket+80)=lastStart+tex; *(float *)(corePacket+88)=lastStart+tex; *(float *)(corePacket+96)=lastEnd+tex; *(float *)(corePacket+104)=lastEnd+tex;
*(float *)(outerPacket+80)=lastStart+tex; *(float *)(outerPacket+88)=lastStart+tex; *(float *)(outerPacket+96)=lastEnd+tex; *(float *)(outerPacket+104)=lastEnd+tex;
    func_00280B90_7(corePacket,0,0);func_00280B90_7(outerPacket,0,0);
}
