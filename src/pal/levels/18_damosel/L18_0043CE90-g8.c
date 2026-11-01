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
extern void func_0029F338(void *);
extern int D_L18_001B1BB0 __attribute__((sda));
extern int D_L18_001B1B88 __attribute__((sda));
extern int D_L18_001B1B80 __attribute__((sda));
extern int D_L18_001B1B90 __attribute__((sda));
extern int func_002A77E0(int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00283098(void *,void *,void *);
extern void *func_PAL_L06_00469110(void *,void *,void *,int,float,float);

void func_PAL_L18_00441F00(u8 *o) {
    u8 *s=*(u8 **)(o+0x68), *hit;
    int n, i;
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
            *(float *)(hit+0x18)=0.75f;
            func_00282D30(a,hit+0x10,func_002A7878(6.0f,8.0f));
            qcopy(b,a);
            func_00282CF0(a,a,spread);
            func_00282CC0(b,b,spread);
            func_PAL_L00_0032C328(o,a,&D_L18_001B1B88,&D_L18_001B1B80,65535,-1,D_L18_001B1BB0,9,2,255,0);
            func_002A7750(o,2,-1);
        }
        o[0xA8]=255;
        break;
    case 2:
        func_PAL_L00_0032C328(o,&D_L18_001B1B90,&D_L18_001B1B88,&D_L18_001B1B80,65535,0,D_L18_001B1BB0,6,61,255,0);
        n=func_002A77E0(5);
        func_L01_0031A278(o,a,0.35f,0.0f,1.8f);
        for(i=0;i<n;i++) {
            float x,y;
            b[0]=func_002A7878(8.0f,12.0f)*(0.020000001f);
            b[1]=(2*i-n+1)*(0.080000006f);
            b[2]=func_002A7878(0.0f,2.0f)*(0.020000001f);
            func_00283098(b,b,o+0xC0);
            x=func_002A7878(0.75f,1.25f);
            y=func_002A7878(0.75f,1.25f);
            func_PAL_L06_00469110(o,a,b,1,x,y);
        }
        func_0029F338(o);
        break;
    }
}
