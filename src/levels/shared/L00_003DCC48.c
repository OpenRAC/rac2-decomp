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

extern float D_L00_001B8DC0[];
void func_L00_003DCC48(float tex, float width, float step, void *start, char *points, int color, int count)
{
    char origin[16] __attribute__((aligned(16)));
    char p[144] __attribute__((aligned(16)));
    char q[144] __attribute__((aligned(16)));
    float m[16];
    TrailVector offsets[2];
    int i;
    int c1, c2;
    char *basis = origin;
    float v, u, a, b;
    *(TrailQuad *)origin = *(TrailQuad *)start;
    func_00281DE8_7(p,43,1,128);
    func_00281DE8_7(q,43,1,128);
    offsets[0].quad=0; offsets[1].quad=0;
    width *= .25f;
    *(int *)(p+64)=*(int *)(p+68)=color;
    *(int *)(q+64)=*(int *)(q+68)=color;
    *(int *)(p+72)=*(int *)(p+76)=color;
    *(int *)(q+72)=*(int *)(q+76)=color;
    offsets[0].f[3]=1;
    offsets[1].f[3]=1;
    offsets[0].f[2]=width;
    offsets[1].f[2]=width+width;
    if (!(func_001163B0()&1)) {
        *(float *)(p+80)=tex; *(float *)(p+84)=0; *(float *)(p+88)=tex; *(float *)(p+92)=1;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=0; *(float *)(p+104)=step+tex; *(float *)(p+108)=1;
        *(float *)(q+80)=tex; *(float *)(q+84)=0; *(float *)(q+88)=tex; *(float *)(q+92)=1;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=0; *(float *)(q+104)=step+tex; *(float *)(q+108)=1;
    } else {
        *(float *)(p+80)=tex; *(float *)(p+84)=1; *(float *)(p+88)=tex; *(float *)(p+92)=0;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=1; *(float *)(p+104)=step+tex; *(float *)(p+108)=0;
        *(float *)(q+80)=tex; *(float *)(q+84)=1; *(float *)(q+88)=tex; *(float *)(q+92)=0;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=1; *(float *)(q+104)=step+tex; *(float *)(q+108)=0;
    }
    func_00282CF0_7(m,points,basis); func_00282F20_7(m,m,1);
    func_00282CF0_7(m+4,D_L00_001B8DC0,basis);
    func_00282DD8_7(m+8,m+4,m); func_00282F20_7(m+8,m+8,1); func_00282DD8_7(m+4,m,m+8);
    qcopy(m+12,basis);
    qcopy(p,offsets); qcopy(q,offsets+1);
    func_00282D30_7(p+16,p,-1); func_00282D30_7(q+16,q,-1);
    func_002830C0_7(p,p,m); func_002830C0_7(p+16,p+16,m); func_002830C0_7(q,q,m); func_002830C0_7(q+16,q+16,m);
    for(i=0;i<count-1;i++) {
        c1=color|0x7f000000; c2=color|0x3f000000;
basis = (char *)m;
        func_00282CF0_7(basis,points+(i*16+16),points+i*16); func_00282F20_7(basis,basis,1);
        func_00282CF0_7(basis+16,D_L00_001B8DC0,points+i*16);
        func_00282DD8_7(basis+32,basis+16,basis); func_00282F20_7(basis+32,basis+32,1); func_00282DD8_7(basis+16,basis,basis+32);
        qcopy(basis+48,points+i*16);
        offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
        qcopy(p+32,offsets); qcopy(q+32,offsets+1);
        func_00282D30_7(p+48,p+32,-1); func_00282D30_7(q+48,q+32,-1);
        func_002830C0_7(p+32,p+32,basis); func_002830C0_7(p+48,p+48,basis); func_002830C0_7(q+32,q+32,basis); func_002830C0_7(q+48,q+48,basis);
        u=step*func_00283CE0_7(i+1); v=u+step; if(u>=1) {u-=1;v-=1;}
*(float *)(p+80)=u+tex; *(float *)(p+88)=u+tex; *(float *)(p+96)=v+tex; *(float *)(p+104)=v+tex;
*(float *)(q+80)=u+tex; *(float *)(q+88)=u+tex; *(float *)(q+96)=v+tex; *(float *)(q+104)=v+tex;
        func_00280B90_7(p,0,0); func_00280B90_7(q,0,0);
         if(i) { *(int *)(p+68)=c1; *(int *)(p+64)=c1; *(int *)(q+68)=c2; *(int *)(q+64)=c2; }
        *(int *)(p+76)=c1; *(int *)(p+72)=c1; *(int *)(q+76)=c2; *(int *)(q+72)=c2;
        qcopy(p,p+32);qcopy(p+16,p+48);qcopy(q,q+32);qcopy(q+16,q+48);
    }
    qcopy(m+12,points+(count-1)*16);
    offsets[0].f[2]*=.7f; offsets[1].f[2]=offsets[0].f[2]+offsets[0].f[2];
    qcopy(p+32,offsets);qcopy(q+32,offsets+1);
    func_00282D30_7(p+48,p+32,-1);func_00282D30_7(q+48,q+32,-1);
    func_002830C0_7(p+32,p+32,m);func_002830C0_7(p+48,p+48,m);func_002830C0_7(q+32,q+32,m);func_002830C0_7(q+48,q+48,m);
    *(int *)(p+76)=color; *(int *)(p+72)=color; *(int *)(q+76)=color; *(int *)(q+72)=color;
    a=step*func_00283CE0_7(i+1); b=a+step; if(a>=1) {a-=1;b-=1;}
*(float *)(p+80)=a+tex; *(float *)(p+88)=a+tex; *(float *)(p+96)=b+tex; *(float *)(p+104)=b+tex;
*(float *)(q+80)=a+tex; *(float *)(q+88)=a+tex; *(float *)(q+96)=b+tex; *(float *)(q+104)=b+tex;
    func_00280B90_7(p,0,0);func_00280B90_7(q,0,0);
}
