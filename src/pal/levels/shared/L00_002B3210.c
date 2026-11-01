#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002B3210);

#include "common.h"
extern u8 D_00189E20_1[];
extern void func_00282978(char *);
typedef int AnimQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0x158]; float value; u8 gap[0x370-0x15c]; AnimQuad vector; } AnimBase;
extern AnimBase D_L00_001B8C80;
extern void func_L00_002B3EF8(int, float, float, float);

void func_PAL_L00_002B34C0(void)
{
    u8 *p=D_00189E20_1;
    float f;
    *(float *)(p+0x1458)=*(float *)(p+0x1a0);
    qcopy_nc(p+0x1440,p+0x190);
    func_00282978(p+0x146c);
    func_00282978(p+0x146e);
    f=1.0f;
    if(p[0x22b4]==0) {
        if(p[0x1457]==0) {
            *(short *)(p+0x146e)=5;
            if(*(short *)(p+0x146c)!=0) f=-0.25f;
        } else if(p[0x1457]==1) {
            *(short *)(p+0x146c)=5;
            if(*(short *)(p+0x146e)!=0)
                f=(4.0f-(float)*(short *)(p+0x146e))*0.25f;
        }
    }
    {
        u8 *q=D_00189E20_1;
        AnimBase *anim=&D_L00_001B8C80;
        *(float *)(q+0x1a0)=anim->value;
        *(float *)(q+0x1b4)*=f;
        qcopy_nc(q+0x190,&anim->vector);
        *(float *)(q+0x1a4)=*(float *)(q+0x145c);
        func_L00_002B3EF8(0,0.053280003f,0.36f,0.24434614f);
        {
            float saved=*(float *)(q+0x1a4);
            *(float *)(q+0x1a8)=0.0f;
            *(float *)(q+0x145c)=saved;
        }
        *(float *)(q+0x1a4)=0.0f;
    }
}


