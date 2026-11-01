/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Tier: GPT-6.1 Sol high, v0826. USA v1.01, game compiler.
 * Corrected draft: 1068/1076 bytes, 0 of 1 places match (level 03).
 * Baseline was 1076/1076 but had inaccurate return declarations and a one-bit
 * FP constant error. Required profile: -O2 -G8 -ffunction-sections
 * -frac2-qcopy -frac2-qcopy-barrier (separate unit).
 * Initialization stores and f3/f4 allocation differ. Explicit block-local mode
 * shares the byte/int 3 and restores retail's copy-address registers. Named
 * product locals restore most post-initialization FP allocation, but the paired
 * 0x70/0x74 and 0x64/0x68 stores are reversed. The 0xFFFFFFFFULL sentinel is
 * materialized with lui FFFF; dsrl32, retail uses addiu -1; dsrl32.
 * The angular constant must be 0x36A2AD2F, not the older draft's 0x36A2AD2E.
 * qcopy helper vs ordinary TI with qcopy profiles tied; measured field wrappers
 * and -fno-gcse did not repair the initialization. No linked check of this C.
 * All declarations are below. func_002E5CF8 / func_002E5E58 and func_002B3BA8
 * return int in the existing game source; do not restore their void declarations.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_002A7750(void *,int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_0029F338(void *);
extern void func_00283098(void *,void *,void *);
extern float D_L03_001B1BA4 __attribute__((sda));
extern float D_L03_001B1BA0 __attribute__((sda));
extern float D_L03_001B1B80 __attribute__((sda));
extern float D_L03_001B1B84 __attribute__((sda));
extern float D_L03_001B1B88 __attribute__((sda));
extern float D_L03_001B1B8C __attribute__((sda));
extern float D_L03_001B1BB0[4] SDATA(D_L03_001B1BB0) __attribute__((sda));
extern u8 D_00189EA0[], D_L03_001A8F20[], D_L03_001B9980[];
extern int D_L03_001A9044, D_L03_001A9040, D_L03_001A903C;
extern u8 D_001A7A7C;
extern int func_00283CF0(float);
extern void func_002A7470(void *,int,int,int);
extern int func_002B0ED8(void *,void *,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002B0A68(void *,int,void *,u8,float,float,float,float);
extern int func_002E5E58(int,unsigned int,void *);
extern void func_002B0A18(int,int);
extern void func_L03_0041D0A8(void *);
extern void func_002A6C58(void *,int,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int func_002B3BA8(void *,int,void *,int,float,float);

void func_L03_0041CA78(u8 *e) {
    u8 *s=*(u8 **)(e+0x68);
    float scale;
    Vec a,b;
    if(e[0x20]==0) {
        if(*(int *)(s+0x29c)) {
            scale=D_L03_001B1BA4;
            *(float *)(s+0x20)=1;
            *(short *)(s+0x24)=1;
        } else scale=D_L03_001B1BA0;
        *(float *)(e+0x2c)=*(float *)(*(u8 **)(e+0x24)+0x24)*scale;
        s[0x48]=func_00283CF0(20);
        s[0x4a]=func_00283CF0(6);
        if(*(int *)(s+0x290)==-1) goto die;
        { s32 initialMode = 3;
        s[0x150]=7; s[0x28]=initialMode;
        *(float *)(s+0x68)=0.20943955f;
        *(float *)(s+0x84)=scale*0.05f;
        *(float *)(s+0x54)=scale*0.25f;
        *(float *)(s+0x50)=scale*0.5f;
        *(float *)(s+0x5c)=0.4f;
        *(float *)(s+0x60)=0.78539824f;
        *(float *)(s+0x80)=0.52359885f;
        *(int *)(s+0x8c)=*(int *)(s+0x290);
        *(int *)(s+0x2ac)=0; *(int *)(s+0x188)=initialMode;
        *(float *)(s+0x174)=*(float *)(s+0x170)=0.5f;
        *(float *)(s+0x17c)=0.4f; *(float *)(s+0x64)=0.20943955f; *(float *)(s+0x58)=0.4f;
        *(Quad *)(s+0x2b0)=*(Quad *)(e+0x10); }
        if(*(u64 *)(s+0x2a0)!=0xffffffffULL) {
            func_002A7750(e,8,4);
            *(int *)(e+0x98)=0;
            *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
        } else {
            func_002A7750(e,1,0);
            if(e[0x43]) func_002A7470(e,0,0,0);
        }
        {
            float v0 = scale*0.00027777778f;
            float v1 = scale*0.016666668f;
            float v2 = D_L03_001B1B80*v0;
            float v3 = D_L03_001B1B84*v1;
            float v4 = D_L03_001B1B88*0.000004848137343f;
            float v5 = D_L03_001B1B8C*0.00029088825f;
            *(float *)(s+0x74)=v2;
            *(float *)(s+0x70)=v2;
            *(float *)(s+0x78)=v3;
            *(float *)(s+0x68)=v4;
            *(float *)(s+0x6c)=v5;
            *(float *)(s+0x64)=v4;
        }
    }
    if(func_002B0ED8(e,s+0x140,0) && *(float *)(s+0x20)<=0) {
        func_00283098(&a,D_L03_001B1BB0,e+0xc0);
        func_00282CC0(&a,&a,e+0x10);
        func_002E5CF8(2,0,e);
        func_002AC728(e,&a,-1,0.333f,0);
        func_00282CF0(&b,e+0x10,D_00189EA0);
        b.f[2]=0;
        func_00282F20(&b,&b,0.10000001f);
        func_002B0A68(e,31,D_L03_001A8F20,255,3,6,3,6);
        if(*(int *)(D_00189EA0+0x2214)==49) {
            D_L03_001A9044++;
            if(D_L03_001A9044>=10 && !D_001A7A7C) {
                D_001A7A7C=1;
                func_002E5E58(1,0,0);
                func_002B0A18(0x1233,-1);
                D_L03_001A903C=1;
            }
        }
        func_002E5CF8(2,0,e);
        func_L03_0041D0A8(e);
    die:
        func_002A6C58(e,0,3);
        func_0029F338(e);
        return;
    }
    if(e[0x31] && func_00282E48(e+0x10,D_L03_001B9980)<24) {
        func_002A93B0(e);
        e[0x6f]=22;
    }
    if(e[0x95]<3) func_002B3BA8(e,*(int *)(s+0x294),0,0,16,0);
}
