#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern u8 *D_L17_001FF890;
extern u8 *func_002B9030(int);
extern int func_001163B0(void);
extern int func_00283CF0(float);
u8 *func_L17_00340DD0(u8 *object,int color,int lifetime,float size)
{
    u8 *particle=func_002B9030(0x54);
    u8 *state;
    if (particle) {
        state=particle+0x20;
        *(u8 **)state=object;
        *(s16 *)(state+6)=lifetime;
        *(int *)(state+0xc)=color>>24;
        *(s16 *)(state+4)=lifetime;
        *(Quadword *)(particle+0x10)=*(Quadword *)(object+0x10);
        particle[8]=func_001163B0();
        *(int *)(particle+4)=color;
        particle[9]=FloatToInt(4.0f)+0x70;
        particle[3]=0x48;*(float *)(particle+0xc)=size;particle[1]=0;
        particle[2]=D_L17_001FF890[0];
    }
    return particle;
}
