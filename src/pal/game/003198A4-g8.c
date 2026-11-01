#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void func_PAL_0031B110(void *),func_002A93B0(void *),func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *),func_00282C88(void *),func_002830C0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_002AB6D8(void *,void *),func_002B4090(void *,void *,float,float,float),func_PAL_002A7650(void *,int,int),func_0029F338(void *),func_00319F38(void *),func_002B3BA8(void *,int,int,int,float,float),func_0031A718(void *);
extern float func_00282E48(void *,void *),func_002A89A8(void *,int,float);
extern int func_PAL_002B1A50(void *,void *,int),func_002761F8(void *,void *,int,void *,int),func_002A8508(int,int);
extern int func_00278E78(void);
extern int func_0031A628(void *);
extern char D_001B5340[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
extern char *D_0018C0B0 NOT_SDA;

void func_PAL_0031AD58(char *self)
{
    float matrix[16];
    float a[4],b[4];
    char *d=P(self,0x68);
    float height;
    int result,kind,mode;
    short *list;
    char *moby;
    if(B(self,0x20)==0) func_PAL_0031B110(self);
    if(B(self,0x31) && func_00282E48(self+0x10,D_001B5340)<24.0f) {
        func_002A93B0(self);
        B(self,0x6F)=22;
    }
    func_0029FCC0(self,0,d+0x300);
    func_0029FCC0(self,1,d+0x310);
    func_0029FCC0(self,2,d+0x320);
    func_0029FC20(self,3,matrix);
    func_00282C88(d+0x330);
    F(d,0x338)=0.0f;
    F(d,0x330)=0.25f;
    func_002830C0(d+0x330,d+0x330,matrix);
    func_00282CC0(d+0x330,d+0x330,matrix+12);
    result=func_PAL_002B1A50(self,d+0x80,0);
    height=func_002A89A8(self+0x10,0,0.5f);
    if(height==0.0f || F(self,0x18)-height>20.0f) {
        if(B(d,0x9A)==1) {
            if(H(self,0x34)&0x100) {
                func_002AB6D8(self+0xC0,self+0xF0);
                H(self,0x34)&=~0x100;
            }
            qcopy(a,D_001A8BD0);
            a[2]+=0.5f;
            func_002B4090(self,a,0.05f,0.05f,0.0f);
        }
    } else {
        qcopy(a,self+0x10);
        qcopy(b,self+0x10);
        b[2]-=1.0f;
        if(func_002761F8(a,b,0,self,0)) {
            kind=func_00278E78();
            if(kind==1 || kind==11) {
                func_PAL_002A7650(self,0,3);
                func_0029F338(self);
                return;
            }
        }
    }
    if(result) {
        if(result==5) {
            I(d,0x110)=0;
            F(d,0x114)=1.0053098f;
        }
        func_00319F38(self);
        func_0031A628(self);
        if((result==4 || result==5) && D_001B1B78>=B(self,0x21) && func_002A8508(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            do {
                moby=D_001B1B5C+((*list&0x7FFF)<<8);
                if(*(short *)(moby+0xAA)==0x9B4 && I(P(moby,0x68),0x2A4)==0) {
                    I(P(moby,0x68),0x2A4)=1;
                    goto done_list;
                }
            } while(*list++>=0);
        }
    }
done_list:
    func_002B3BA8(self,I(d,0x400),0,0,0.0f,0.0f);
    mode=B(self,0x20);
    if(mode!=3 && mode!=12 && mode!=13 && mode!=14 && mode!=16 && I(d,0x350) && P(d,0x30)==D_0018C0B0)
        func_0031A718(self);
}
