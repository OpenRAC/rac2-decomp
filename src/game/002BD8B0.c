/* func_002BD8B0: both 16-byte copies are qcopy(), so the 4.0f argument stays at its call
 * as in retail; the spawn returns p itself when the allocation fails, and the flag byte at
 * +2 is stored before the two halfword copies of a4. */
#include "common.h"

extern void *func_002B9030(int kind);
extern int func_00283CF0(float f);
extern int func_001163B0(void);
extern unsigned char *D_001F2594;


/* Creates a spark particle that leaves a short trail of copies behind it. It returns the new particle, or 0 when there is no life to give it. */
void *func_002BD8B0(void *position, void *velocity, int color, int colorEnd, int life, int trailFlag, float size)
{
    void *particle;
    char *motion;
    int variation;

    if (life == 0)
        return 0;
    particle = AllocParticle(0x15);
    if (particle != 0) {
        qcopy((char *)particle + 0x10, position);
        *(int *)((char *)particle + 4) = color;
        variation = FloatToInt(4.0f);
        *(unsigned char *)((char *)particle + 1) = 0;
        *(float *)((char *)particle + 0xC) = size;
        *(unsigned char *)((char *)particle + 3) = 0x48;
        *(unsigned char *)((char *)particle + 9) = (unsigned char)(variation - 0x60);
        *(unsigned char *)((char *)particle + 8) = (unsigned char)Rand();
        motion = (char *)particle + 0x20;
        *(unsigned char *)((char *)particle + 2) = *D_001F2594;
        *(short *)((char *)particle + 0xA) = life;
        *(short *)(motion + 0x18) = life;
        *(float *)(motion + 0x1C) = size;
        *(int *)(motion + 0x10) = color;
        *(int *)(motion + 0x14) = colorEnd;
        *(short *)(motion + 0x1A) = trailFlag;
        qcopy(motion, velocity);
    }
    return particle;
}
