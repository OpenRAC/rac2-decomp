#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_003198A4);


#include "common.h"
extern int D_001B2758 MACRO_ADDR;
extern int func_00283CF0(float), func_002A7820(int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A7750(void *, int, int), func_PAL_002A7E68(void *, int, int, int);
extern float D_001BAFA8;
extern u8 D_00189E20[];
extern u8 D_00188660[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
extern u8 D_00189E20[];
extern u8 *D_001B1B5C MACRO_ADDR;

/* func_00318340 is in 00318340.c. */
/* func_00319780 is in 00319780-g8.c. */

void func_PAL_0031B110(char *self)
{
    char *d = *(char **)(self + 0x68);
    *(u8 *)(d+0x68) = func_00283CF0(15.0f);
    *(u8 *)(d+0x6A) = func_00283CF0(12.0f);
    *(float *)(self+0x2C) *= 1.1f;
    *(u16 *)(self+0x34) |= 0x8100;
    *(char **)(d+0x18) = d+0x130;
    *(u8 *)(d+0x48)=3;
    *(u8 *)(d+0x90)=17;
    *(int *)(d+0xC8)=4;
    *(int *)(d+0xFC)=*(int *)(d+0x270);
    *(u8 *)(d+0x95)=13;
    *(float *)(d+220)=0.30000001192092896f;
    *(float *)(d+216)=0.05000000074505806f;
    *(float *)(d+160)=0.080000006f;
    *(float *)(d+164)=0.006f;
    *(float *)(d+168)=0.012f;
    *(float *)(d+176)=0.5f;
    *(float *)(d+180)=0.5f;
    *(float *)(d+188)=0.4000000059604645f;
    *(float *)(d+156)=0.120000005f;
    if ((float)*(int *)(d+0x2E8)>0.0f) *(float *)(d+0xC0)=(float)*(int *)(d+0x2E8);
    *(float *)(d+0x15C)=0.0f;
    *(float *)(d+320)=12.56637191772461f;
    *(float *)(d+304)=0.800000011920929f;
    *(float *)(d+308)=0.5f;
    *(float *)(d+0x138)=0.4f;
    *(float *)(d+316)=0.4000000059604645f;
    *(float *)(d+352)=0.523598849773407f;
    *(int *)(d+0x168)|=5;
    func_002B60B0(self,0.0048f,0.120000005f,0.0016755164f,0.12566373f);
    qcopy(d+0x220,self+0x10);
    *(float *)(d+0x230)=1.0f;
    *(float *)(d+0x23C)=3.0f;
    *(float *)(d+0x240)=10.0f;
    *(int *)(d+0x2D8)=func_002A7820(100,583);
    *(float *)(d+0x294)*=0.01745329424738884f;
    *(u8 *)(d+0x250)=176;
    *(u8 *)(d+0x251)=128;
    *(u8 *)(d+0x252)=64;
    *(int *)(d+0x2C4)=1;
    *(float *)(d+0x2BC)=0.0f;
    *(int *)(d+0x2C0)=0;
    qcopy(d+0x340,self+0x10);
    *(float *)(d+0x290)=0.0f;
    *(int *)(d+0x2C8)=0;
    *(int *)(d+0x2CC)=0;
    *(int *)(d+0x37C)=0;
    func_0029FCC0(self,0,d+0x2F0);
    qcopy(d+0x300,d+0x2F0);
    *(float *)(d+0x2F8)+=20.0f;
    if (func_002761F8(d+0x300,d+0x2F0,0,self,0))
        *(float *)(d+0x2F8)=D_001BAFA8;
    *(int *)(d+0x168)|=4;
    *(u16 *)(self+0x34)|=0x100;
    *(float *)(d+0x140)=12.56637191772461f;
    *(int *)(d+0x168)|=1;
    if (*(int *)(d+0x28C)==0) {
        if (*(int *)(d+0x370)!=-1) {
            func_002A7750(self,15,3);
            if (*(u8 *)(self+0x43)!=7) func_PAL_002A7E68(self,7,0,0);
        } else {
            func_002A7750(self,1,0);
            if (*(u8 *)(self+0x43)!=0) func_PAL_002A7E68(self,0,0,0);
        }
    } else {
        func_002A7750(self,3,1);
        if (*(u8 *)(self+0x43)!=11) func_PAL_002A7E68(self,11,0,0);
    }
}

