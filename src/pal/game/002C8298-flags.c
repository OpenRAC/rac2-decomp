#include "include_asm.h"

#include "common.h"
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern void Fc3cb9262_FUN_00282CC0(char *a, char *b, char *c);
extern int Fc3cb9262_FUN_00283CF0(float f);
extern int Fc3cb9262_FUN_00282978(char *a);
extern void Fc3cb9262_FUN_002B9180(char *a);

/* Particle that grows and falls faster each frame while its alpha follows the remaining life.
   (PAL: 50 Hz timings) */
void part_update_growing_falling_pal(char *self)
{
    V4_Fc3cb9262 velocity;
    char *state = self + 32;
    float size;
    float growth;
    float fall_speed;

    growth = *(float *)(state + 16) + 1.0000000474974513053894e-03f;
    fall_speed = *(float *)(state + 8) - 0.0043200003f;
    *(float *)(state + 16) = growth;
    *(float *)(state + 8) = fall_speed;
    size = *(float *)(state + 20) * growth * 2.1000000000000000000000e+05f;
    velocity = *(V4_Fc3cb9262 *)state;
    *(float *)(self + 12) = size;
    Fc3cb9262_FUN_00282CC0(self + 16, self + 16, (char *)&velocity);
    *(int *)(self + 4) = (Fc3cb9262_FUN_00283CF0((float)*(short *)(self + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(state + 24);
    if (Fc3cb9262_FUN_00282978(self + 10) != 0)
        Fc3cb9262_FUN_002B9180(self);
}
