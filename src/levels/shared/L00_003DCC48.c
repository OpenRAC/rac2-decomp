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
    char core_packet[144] __attribute__((aligned(16)));
    char outer_packet[144] __attribute__((aligned(16)));
    float matrix[16];
    TrailVector offsets[2];
    int i;
    int core_color, outer_color;
    char *basis = origin;
    float tex_end, tex_start, last_start, last_end;
    *(TrailQuad *)origin = *(TrailQuad *)start;
    func_00281DE8_7(core_packet,43,1,128);
    func_00281DE8_7(outer_packet,43,1,128);
    offsets[0].quad=0; offsets[1].quad=0;
    width *= .25f;
    *(int *)(core_packet+64)=*(int *)(core_packet+68)=color;
    *(int *)(outer_packet+64)=*(int *)(outer_packet+68)=color;
    *(int *)(core_packet+72)=*(int *)(core_packet+76)=color;
    *(int *)(outer_packet+72)=*(int *)(outer_packet+76)=color;
    offsets[0].f[3]=1;
    offsets[1].f[3]=1;
    offsets[0].f[2]=width;
    offsets[1].f[2]=width+width;
    if (!(func_001163B0()&1)) {
        *(float *)(core_packet+80)=tex; *(float *)(core_packet+84)=0; *(float *)(core_packet+88)=tex; *(float *)(core_packet+92)=1;
        *(float *)(core_packet+96)=step+tex; *(float *)(core_packet+100)=0; *(float *)(core_packet+104)=step+tex; *(float *)(core_packet+108)=1;
        *(float *)(outer_packet+80)=tex; *(float *)(outer_packet+84)=0; *(float *)(outer_packet+88)=tex; *(float *)(outer_packet+92)=1;
        *(float *)(outer_packet+96)=step+tex; *(float *)(outer_packet+100)=0; *(float *)(outer_packet+104)=step+tex; *(float *)(outer_packet+108)=1;
    } else {
        *(float *)(core_packet+80)=tex; *(float *)(core_packet+84)=1; *(float *)(core_packet+88)=tex; *(float *)(core_packet+92)=0;
        *(float *)(core_packet+96)=step+tex; *(float *)(core_packet+100)=1; *(float *)(core_packet+104)=step+tex; *(float *)(core_packet+108)=0;
        *(float *)(outer_packet+80)=tex; *(float *)(outer_packet+84)=1; *(float *)(outer_packet+88)=tex; *(float *)(outer_packet+92)=0;
        *(float *)(outer_packet+96)=step+tex; *(float *)(outer_packet+100)=1; *(float *)(outer_packet+104)=step+tex; *(float *)(outer_packet+108)=0;
    }
    func_00282CF0_7(matrix,points,basis); func_00282F20_7(matrix,matrix,1);
    func_00282CF0_7(matrix+4,g_camera_l00_position,basis);
    func_00282DD8_7(matrix+8,matrix+4,matrix); func_00282F20_7(matrix+8,matrix+8,1); func_00282DD8_7(matrix+4,matrix,matrix+8);
    qcopy(matrix+12,basis);
    qcopy(core_packet,offsets); qcopy(outer_packet,offsets+1);
    func_00282D30_7(core_packet+16,core_packet,-1); func_00282D30_7(outer_packet+16,outer_packet,-1);
    func_002830C0_7(core_packet,core_packet,matrix); func_002830C0_7(core_packet+16,core_packet+16,matrix); func_002830C0_7(outer_packet,outer_packet,matrix); func_002830C0_7(outer_packet+16,outer_packet+16,matrix);
    for(i=0;i<count-1;i++) {
        core_color=color|0x7f000000; outer_color=color|0x3f000000;
basis = (char *)matrix;
        func_00282CF0_7(basis,points+(i*16+16),points+i*16); func_00282F20_7(basis,basis,1);
        func_00282CF0_7(basis+16,g_camera_l00_position,points+i*16);
        func_00282DD8_7(basis+32,basis+16,basis); func_00282F20_7(basis+32,basis+32,1); func_00282DD8_7(basis+16,basis,basis+32);
        qcopy(basis+48,points+i*16);
        offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
        qcopy(core_packet+32,offsets); qcopy(outer_packet+32,offsets+1);
        func_00282D30_7(core_packet+48,core_packet+32,-1); func_00282D30_7(outer_packet+48,outer_packet+32,-1);
        func_002830C0_7(core_packet+32,core_packet+32,basis); func_002830C0_7(core_packet+48,core_packet+48,basis); func_002830C0_7(outer_packet+32,outer_packet+32,basis); func_002830C0_7(outer_packet+48,outer_packet+48,basis);
        tex_start=step*func_00283CE0_7(i+1); tex_end=tex_start+step; if(tex_start>=1) {tex_start-=1;tex_end-=1;}
*(float *)(core_packet+80)=tex_start+tex; *(float *)(core_packet+88)=tex_start+tex; *(float *)(core_packet+96)=tex_end+tex; *(float *)(core_packet+104)=tex_end+tex;
*(float *)(outer_packet+80)=tex_start+tex; *(float *)(outer_packet+88)=tex_start+tex; *(float *)(outer_packet+96)=tex_end+tex; *(float *)(outer_packet+104)=tex_end+tex;
        func_00280B90_7(core_packet,0,0); func_00280B90_7(outer_packet,0,0);
         if(i) { *(int *)(core_packet+68)=core_color; *(int *)(core_packet+64)=core_color; *(int *)(outer_packet+68)=outer_color; *(int *)(outer_packet+64)=outer_color; }
        *(int *)(core_packet+76)=core_color; *(int *)(core_packet+72)=core_color; *(int *)(outer_packet+76)=outer_color; *(int *)(outer_packet+72)=outer_color;
        qcopy(core_packet,core_packet+32);qcopy(core_packet+16,core_packet+48);qcopy(outer_packet,outer_packet+32);qcopy(outer_packet+16,outer_packet+48);
    }
    qcopy(matrix+12,points+(count-1)*16);
    offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
    qcopy(core_packet+32,offsets);qcopy(outer_packet+32,offsets+1);
    func_00282D30_7(core_packet+48,core_packet+32,-1);func_00282D30_7(outer_packet+48,outer_packet+32,-1);
    func_002830C0_7(core_packet+32,core_packet+32,matrix);func_002830C0_7(core_packet+48,core_packet+48,matrix);func_002830C0_7(outer_packet+32,outer_packet+32,matrix);func_002830C0_7(outer_packet+48,outer_packet+48,matrix);
    *(int *)(core_packet+76)=color; *(int *)(core_packet+72)=color; *(int *)(outer_packet+76)=color; *(int *)(outer_packet+72)=color;
    last_start=step*func_00283CE0_7(i+1); last_end=last_start+step; if(last_start>=1) {last_start-=1;last_end-=1;}
*(float *)(core_packet+80)=last_start+tex; *(float *)(core_packet+88)=last_start+tex; *(float *)(core_packet+96)=last_end+tex; *(float *)(core_packet+104)=last_end+tex;
*(float *)(outer_packet+80)=last_start+tex; *(float *)(outer_packet+88)=last_start+tex; *(float *)(outer_packet+96)=last_end+tex; *(float *)(outer_packet+104)=last_end+tex;
    func_00280B90_7(core_packet,0,0);func_00280B90_7(outer_packet,0,0);
}
