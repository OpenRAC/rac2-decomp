#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern void func_002A7750(void *,int,int);
extern float func_00283B98(float,float);
extern char *func_002A9640(void *,int,int);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002AC290(void *,void *);
extern void func_PAL_002AC3C0(void *,void *);
extern void func_002E5CF8(int,int,void *);
extern void func_002A0488(void *,int,int,int);
extern int func_002A8508(int,int);
extern int func_002A7820(int,int);
extern void func_PAL_L00_00323918(void *,int,int,int,int,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_PAL_002B15D8(void *,int,void *,float,float,float,float,int);
extern void func_0029F338(void *);
extern int D_L08_001B3AA0 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern int D_L08_002B35C0[];

void func_PAL_L08_00435540(char *a) {
    char *q=*(char **)(a+0x68);
    float hit;
    float v[4] __attribute__((aligned(16)));
    int id;
    switch(*(u8 *)(a+0x20)) {
    case 0:
        *(s16 *)(q+0x24)=5;
        *(float *)(q+0x20)=5.0f;
        func_002A7750(a,1,-1);
        break;
    case 1:
        *(float *)(a+0xF8)=func_00283B98(*(float *)(a+0xF8),*(float *)(q+0x64)*0.0003490659f);
        hit=func_PAL_002AA108(a,func_002A9640(a,0x230000,0));
        if(hit>0.0f) {
            *(u8 *)(q+0x57)=255;
            *(u8 *)(q+0x58)=128;
            *(u8 *)(q+0x59)=128;
            func_PAL_002AC290(a,q+0x50);
            if(D_L08_001B3AA0<4) *(float *)(q+0x20)-=hit;
        }
        if(*(float *)(q+0x20)<0.0f) {
            func_002E5CF8(0,0,a);
            func_002A7750(a,2,-1);
        }
        func_PAL_002AC3C0(a,q+0x50);
        *(u8 *)(a+0xA8)=255;
        break;
    case 2:
        func_002A0488(a,*(u8 *)(q+0x54),*(u8 *)(q+0x55),*(u8 *)(q+0x56));
        if(func_002A8508(*(u8 *)(a+0x21),-1)==1) {
            id=*(int *)((D_001A79F0 << 2)+(char *)D_L08_002B35C0)*35-1;
            func_PAL_L00_00323918(a,id,id,3,-1,func_002A7820(1,3),0.0f);
        }
        *(u128 *)v=0;
        v[0]=0.14000002f; v[1]=0.080000006f;
        func_00283098(v,v,a+0xC0);
        if(*(u8 *)(a+0x31)) func_PAL_002B15D8(a,255,v,3.0f,6.0f,3.0f,6.0f,255);
        else func_PAL_002B15D8(a,170,v,3.0f,6.0f,3.0f,6.0f,255);
        func_0029F338(a);
        break;
    }
}
