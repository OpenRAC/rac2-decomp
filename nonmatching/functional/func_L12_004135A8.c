/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: opus-1 (Claude Opus 5.5, xhigh), 1 November 2026. USA v1.01, Todano only.
 * Best check.py: 1848/1848 bytes, 0 of 1 places match; first difference at +0x14,
 * 99 of 462 rows differ. The object is in s5 and the frame is right.
 * Compile as a separate -O2 -G8 -ffunction-sections unit, for example
 * src/levels/12_todano/L12_00398E50-init-g8.c, in place of the INCLUDE_ASM marker.
 * The declarations it needs are at the top of this file. func_002B60B0 is used as
 * returning a pointer and its result is ignored.
 *
 * Still differs:
 * - Head registers. Retail has 14,18,20,255,10 in v0,v1,a0,a1,a2 and 7,5,17,9 in
 *   a3,t0,t1,t2. Here `value` (14, then 8) goes to global-alloc, because it has two
 *   deaths, and takes t2 behind the local pseudos, so the rest shift. Retail keeps
 *   14 and 8 in v0. FP: .3667, .45, slow and [0x310] are not in f4,f3,f5,f6.
 * - Head order: stores 0x28 and 0xBE are swapped, and 4,3,2,1 load in another order.
 * - Reload rotation: retail's 4,3,2,1 (v1,a0,a1,a2), the later 1 (v1), the copy
 *   temps (a0,a1,a2,v0) and 0xD66/0xFE (a0,a1) look one spill reg ahead of this form.
 * - Stores 0x1E8/0x1E9: retail loads 11 then 12 but stores 0x1E8 first. Either source
 *   order keeps the load and store orders tied.
 *
 * Measured:
 * - No vanished test is needed: REG_DEAD stores go first, non-death stores of shared
 *   values sink, and sched1's flush is store 0x30, which gives retail's store order.
 * - BE between BD and BF, as in the matching table in func_L12_00412E50, fixes 5 and 7.
 * - Moving 0x302's test outside if (p) fixes the beqz target.
 * - The reused local puts `li 8` in retail's row. Reusing all five pairs (14,8),
 *   (18,4), (20,3), (255,2), (10,1) also spaces the stores and fixes most FP
 *   registers, but 4,3,2,1 stop being rematerialized: 1840 bytes, object in s6.
 * - The body of this form still reads the group-2 values as shared constants.
 */
#include "common.h"
typedef struct { u8 bytes[16]; } InitBytes;
typedef struct { float data[12]; } InitBlock;
extern InitBytes D_L12_001B1848;
extern u8 D_L12_001A8F20[] MACRO_ADDR;
extern void *D_L12_001FEAC0[];
extern float D_L12_001B17F0 __attribute__((sda));
extern float D_L12_001B17F4 __attribute__((sda)),D_L12_001B17F8 __attribute__((sda)),D_L12_001B1804 __attribute__((sda)),D_L12_001B1808 __attribute__((sda)),D_L12_001B180C __attribute__((sda));
extern int func_00283CF0(float),func_001163B0(void),func_002A7820(int,int);
extern u8 *func_0029EFD0(int),*func_L02_0032B468(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void *func_002B60B0(u8 *,float,float,float,float);
extern float func_L01_003377C8(u8 *);
extern int func_002B3380(void *,void *,void *),func_L09_003F7C50(void *,int,int);
extern void func_0029FCC0(void *,int,void *),func_00282CF0(void *,void *,void *),func_L09_003F73E8(void *),func_002A7750(void *,int,int),func_L12_00412E50(void *,int,int,int);
void func_L12_004135A8(u8 *o) {
    u8 *d=*(u8 **)(o+0x68), *p,*pd; InitBytes bytes=D_L12_001B1848; float pos[4]; int i,j; u8 *parameters; float acceleration; int animation=9; float slow=0.004166666883975267f; int value;
    *(float *)(o+0x2C)*=D_L12_001B17F0;
    *(int *)(d+0x98)=animation;
    d[0x62]=17;
    *(float *)(d+0x74)=slow;
    *(float *)(d+0x6C)=0.36666667461395264f;
    *(float *)(d+0x70)=0.11666667461395264f;
    *(float *)(d+0x78)=0.008333333767950535f;
    *(float *)(d+0x7C)=slow;
    *(float *)(d+0x8C)=0.4f;
    d[0xBC]=5;
    d[0xBD]=animation;
    d[0xBE]=4;
    d[0xBF]=7;
    d[0xC3]=17;
    *(float *)(d+0x90)=*(float *)(d+0x310);
    d[0x28]=3;
    value=14;d[0x60]=value;value=8;
    d[0x61]=18;
    d[0x66]=20;
    d[0x67]=255;
    d[0xC2]=10;
    *(float *)(d+0xF8)=0.45f;
    *(u8 **)(d+0x2F8)=0;
    *(u8 **)(d+0x2F0)=0;
    *(u8 **)(d+0x2F4)=0;
    *(float *)(d+0x80)=0.7f;
    *(float *)(d+0x84)=0.7f;
    *(float *)(d+0x30)=1.7f;
    d[0x2A]=2;
    d[0x2E]=1;
    d[0x4D]=0;
    d[0x2F]=value;
    d[0x48]=func_00283CF0(25.0f);d[0x4A]=func_00283CF0(16.0f);
    { float first,second,third,fourth;
    acceleration=D_L12_001B180C*0.00027777778450399637f;
    d[0x1E8]=12;d[0x1E9]=11;
    second=D_L12_001B17F8*0.01666666753590107f;third=D_L12_001B1804*0.000004848137454391923f;
    fourth=D_L12_001B1808*0.0002908882452175021f;first=D_L12_001B17F4*0.00027777778450399637f;
    *(float *)(d+0x100)=0.7f;*(float *)(d+0x104)=0.5f;*(float *)(d+0x108)=0.5f;*(float *)(d+0x10C)=0.5f;
    *(float *)(d+0x110)=0.7853982448577881f;*(float *)(d+0x130)=0.349065899848938f;
    *(float *)(d+0x12C)=acceleration;
    func_002B60B0(o,first,second,third,fourth); }
    *(int *)(d+0x138)|=0x80;*(int *)(d+0x1DC)=0;*(float *)(d+0x1D4)=3.0f;
    *(u16 *)(d+0x1E4)=0;*(u16 *)(d+0x1E2)=0;*(int *)(d+0x1D0)=0;
    if(*(int *)(d+0x2BC)!=-1)func_L01_003377C8(D_L12_001FEAC0[*(int *)(d+0x2BC)]);
    if(*(int *)(d+0x2B4)!=-1)func_L01_003377C8(D_L12_001FEAC0[*(int *)(d+0x2B4)]);
    if(*(int *)(d+0x2B8)!=-1)func_L01_003377C8(D_L12_001FEAC0[*(int *)(d+0x2B8)]);
    p=func_0029EFD0(0x114B);
    if(p) {
        *(u8 **)(d+0x2F8)=p;*(u16 *)(p+0x32)=*(u16 *)(o+0x32);p[0x30]=o[0x30];
        *(u64 *)(p+0x38)=*(u64 *)(o+0x38);p[0x31]=1;*(int *)(p+0x78)=*(int *)(o+0x78);
        *(float *)(p+0x2C)*=D_L12_001B17F0;
        func_0029FCC0(o,0,p+0x10);qcopy(p+0xF0,o+0xF0);
        pd=*(u8 **)(p+0x68);*(InitBlock *)(pd+0x20)=*(InitBlock *)(d+0x20);
        *(float *)(pd+0x20)=*(float *)(d+0x20);*(u16 *)(pd+0x24)=*(u16 *)(d+0x24);pd[0x28]=d[0x28];
        *(float *)(pd+0x30)=0.7f;pd[0x2A]=2;pd[0x2F]=4;pd[0x4A]=3;pd[0x4D]=1;*(u8 **)(pd+0x70)=o;
        for(i=0;i<2;i++) {
            u8 *child;
            func_0029FCC0(*(u8 **)(d+0x2F8),i,pos);func_00282CF0(pos,pos,*(u8 **)(d+0x2F8)+0x10);
            child=func_L02_0032B468(*(u8 **)(d+0x2F8),0xD66,pos,D_L12_001A8F20,0,0,D_L12_001A8F20,D_L12_001A8F20,D_L12_001A8F20,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(o+0x32);*(u8 **)(d+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=pd+0x50;
        for(j=0;j<10;j++)parameters[j]=bytes.bytes[j];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[8]=func_00283CF0((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 1:parameters[5]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[9]=func_00283CF0((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 2:parameters[7]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);break;
        }
        func_002B3380(*(u8 **)(d+0x2F8),pd+0x50,pd+0x20);{ u8 *partner=*(u8 **)(d+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(d[0x302] && !(d[0x302]&2))d[0x302]=1;
    func_L09_003F7C50(o,*(int *)(d+0x2B4),-1);func_L09_003F73E8(o);**(int **)(d+0x304)=0;
    if(*(int *)(d+0x2B0)!=-1) {
        *(int *)(d+0x2DC)=*(int *)(d+0x2B0);*(int *)(d+0x138)|=4;func_002A7750(o,1,1);
        func_L12_00412E50(o,13,0,func_002A7820(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    } else {
        int state;func_002A7750(o,5,1);state=func_001163B0()&1;
        func_L12_00412E50(o,state,0,func_002A7820(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    }
}
