#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits;float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern s32 func_00277258(void *,s32,void *,float);
extern void func_00282F20(void *,void *,float);
extern char *D_L10_001BFAD8 NOT_SDA;
extern char *D_L10_001B1780 __attribute__((sda));
extern Vector4 D_L10_001BFB00;

void func_PAL_L10_004342B0(char *object)
{
    Vector4 direction;
    char *work=FIELD(char *,object,0x68),*hit;
    if(!func_00277258(object+0x10,16,object,0.8f))return;
    hit=D_L10_001BFAD8;
    if(hit && FIELD(s16,hit,0xAA)==0xFBF) {
        if(!D_L10_001B1780)return;
        direction.bits=FIELD(Quadword,D_L10_001B1780,0xC0);
        func_00282F20(&direction,&direction,0.32000002f);
        FIELD(Quadword,work,0)=direction.bits;
    }else {
        FIELD(Quadword,work,0)=D_L10_001BFB00.bits;
        func_00282F20(work,work,0.040000003f);
    }
}
