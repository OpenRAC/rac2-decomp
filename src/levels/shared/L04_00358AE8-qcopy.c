#include "include_asm.h"
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
extern u8 *D_L04_001FF26C;
extern u8 *func_002B9030(int);
extern int func_001163B0(void);
extern int func_00283CF0(float);

/* The func_L17_00340DD0 particle with a velocity: copies the position, then the velocity and
   the start/end time into the state block. */
u8 *func_L04_00358AE8(u8 *position, u8 *velocity, int color, int time, float size)
{
    u8 *particle=func_002B9030(0x1B);
    u8 *state;
    if (particle) {
        state=particle+0x20;
        qcopy(particle+0x10, position);
        particle[8]=func_001163B0();
        *(int *)(particle+4)=color;
        particle[9]=FloatToInt(4.0f)+0x40;
        particle[3]=0x48;*(float *)(particle+0xc)=size;particle[1]=0;
        particle[2]=D_L04_001FF26C[0];
        *(int *)(state+0x18)=(s8)particle[7];
        qcopy(state, velocity);
        *(int *)(state+0x10)=time;
        *(int *)(state+0x14)=time;
    }
    return particle;
}
