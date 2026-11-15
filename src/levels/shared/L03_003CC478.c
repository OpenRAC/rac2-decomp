#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits;float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern u8 *func_0029EFD0(s32);
extern void func_002B37E8(void *,void *),func_002A7750(u8 *,s32,s32);
void func_L03_003CC478(u8 *owner,void *unused,Vector4 *velocity,s32 index)
{
    u8 *object=CreateMoby(FIELD(s16,owner,0xAA));
    char *work;
    if(!object)return;
    func_002B37E8(object,owner);
    object[0x31]=0;FIELD(u16,object,0x34)|=1;
    FIELD(u32,object,0x98)=FIELD(u32,FIELD(char *,object,0x24),0x10);
    work=FIELD(char *,object,0x68);FIELD(Quadword,work,0)=velocity->bits;FIELD(s32,work,0x10)=index;
    func_002A7750(object,5,-1);
}
