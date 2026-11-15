#include "include_asm.h"
#include "common.h"

extern void func_00282CC0_17(char *dst, char *src, char *vec);
extern float vec_length_xy(void *);
extern int FastDecTimer(short *);
extern int moby_decrement_top_byte(void *, int);
extern void part_kill(void *);

/* func_PAL_002C5C18, the PAL copy of func_002C4F08: the same C, where the 0.003f
   fall becomes 0.0043200003f (scaled by 36/25) and the decay above 1.0f is scaled by 1.2f. */
void func_PAL_002C5C18(char *self)
{
    char *motion = self + 0x20;
    float len;
    float f;

    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 0x12);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(motion + 8) = *(float *)(motion + 8) - 0.0043200003f;
    len = vec_length_xy(motion);
    f = (len * 9.7000002861022949218750e-01f - 1.0f) * 1.2f + 1.0f;
    f = f / len;
    *(float *)(self + 0x20) = *(float *)(self + 0x20) * f;
    *(float *)(motion + 4) = *(float *)(motion + 4) * f;
    if (FastDecTimer((short *)(self + 0xA)) == 0) {
        f = *(float *)(self + 0xC) + *(float *)(motion + 0x14) * 2.0f;
        *(float *)(self + 0xC) = f;
        if (f < 15000.0f)
            *(float *)(self + 0xC) = 15000.0f;
    } else {
        if (moby_decrement_top_byte(self + 4, *(int *)(motion + 0x1C)) != 0) {
            *(int *)(self + 0xC) = 0;
            part_kill(self);
        }
    }
}
