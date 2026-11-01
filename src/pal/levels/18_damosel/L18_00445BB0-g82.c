#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void *func_PAL_L00_003FB330(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_0029F338(void *);
extern int D_L18_001B1D20 __attribute__((sda));
extern int D_L18_001B1D18 __attribute__((sda));
extern int D_L18_001B1D10 __attribute__((sda));
extern int D_L18_001B1CF0 __attribute__((sda));
extern unsigned char D_00139658 NOT_SDA;
extern struct { char pad[0xA0]; unsigned char bits; } D_001395B8;

void func_PAL_L18_00446558(u8 *o) {
    u8 *s=*(u8 **)(o+0x68), *hit;
    float a[4] __attribute__((aligned(16))), b[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(o[0x20]) {
    case 0: func_002A7750(o,1,-1); break;
    case 1:
        hit=func_002A9640(o,0x4010000,0);
        if(hit && !*(int *)s) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=1.0f;
            func_00282D30(a,hit+0x10,func_002A7878(6.0f,8.0f));
            qcopy(b,a);
            func_00282CF0(a,a,spread);
            func_00282CC0(b,b,spread);
            func_PAL_L00_0032C328(o,a,&D_L18_001B1D18,&D_L18_001B1D10,65535,-1,D_L18_001B1D20,9,1,255,0);
            func_002A7750(o,2,-1);
        }
        o[0xA8]=255;
        break;
    case 2:
        if((unsigned)*(int *)(s+4)>=8 || (((D_00139658>>*(int *)(s+4))^1)&1)) {
            func_PAL_L00_0032C328(o,&D_L18_001B1CF0,&D_L18_001B1D18,&D_L18_001B1D10,65535,0,D_L18_001B1D20,16,254,255,0);
            if((unsigned)*(int *)(s+4)<8) D_001395B8.bits |= 1<<*(int *)(s+4);
        } else func_PAL_L00_0032C328(o,&D_L18_001B1CF0,&D_L18_001B1D18,&D_L18_001B1D10,65535,0,D_L18_001B1D20,0,254,255,0);
        func_PAL_L00_003FB330(o+0x10,0,5,5,5,5,5,0,*(float *)(o+0x2C)*10.0f,20.0f,1,0,1,0);
        func_0029F338(o);
        break;
    }
}
