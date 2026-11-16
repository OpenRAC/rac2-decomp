#include "names.h"
/* func_002BD8B0: both 16-byte copies are qcopy(), so the 4.0f argument stays at its call
 * as in retail; the spawn returns p itself when the allocation fails, and the flag byte at
 * +2 is stored before the two halfword copies of a4. */
#include "common.h"

extern void *part_alloc(int kind);
extern int FloatToInt(float f);
extern int func_001163B0(void);
extern unsigned char *g_part_tex_trailing_spark;


/* Creates a spark particle that leaves a short trail of copies behind it. It returns the new particle, or 0 when there is no life to give it. */
void *part_spawn_trailing_spark(void *position, void *velocity, int color, int color_end, int life, int trail_flag, float size)
{
    void *particle;
    char *motion;
    int variation;

    if (life == 0)
        return 0;
    particle = part_alloc(0x15);
    if (particle != 0) {
        qcopy((char *)particle + 0x10, position);
        *(int *)((char *)particle + 4) = color;
        variation = FloatToInt(4.0f);
        *(unsigned char *)((char *)particle + 1) = 0;
        *(float *)((char *)particle + 0xC) = size;
        *(unsigned char *)((char *)particle + 3) = 0x48;
        *(unsigned char *)((char *)particle + 9) = (unsigned char)(variation - 0x60);
        *(unsigned char *)((char *)particle + 8) = (unsigned char)func_001163B0();
        motion = (char *)particle + 0x20;
        *(unsigned char *)((char *)particle + 2) = *g_part_tex_trailing_spark;
        *(short *)((char *)particle + 0xA) = life;
        *(short *)(motion + 0x18) = life;
        *(float *)(motion + 0x1C) = size;
        *(int *)(motion + 0x10) = color;
        *(int *)(motion + 0x14) = color_end;
        *(short *)(motion + 0x1A) = trail_flag;
        qcopy(motion, velocity);
    }
    return particle;
}
