#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern unsigned char *CreateMoby(int);
extern int set_moby_color(void *, int, int, int);
extern float math_random_float_range(float, float);
extern void func_002A0F48(void *);

/* Creates a small spinning debris effect at a position, moving in the given direction for a given time. */
unsigned char *part_spawn_spinning_debris(char *position, char *vector, int count, int mode, int flag)
{
    unsigned char *moby = CreateMoby(0x7A /* moby class 122 */);
    char *state;
    float lo;
    float hi;

    if (moby != 0) {
        moby[0x30] = 0xFF;
        *(short *)(moby + 0x32) = 0xFF;
        moby[0x31] = 1;
        moby[0x23] = 0x80;
        state = *(char **)(moby + 0x68);
        set_moby_color(moby, 0x7F, 0x7F, 0x7F);
        *(TI128 *)(moby + 0x10) = *(TI128 *)position;
        *(TI128 *)state = *(TI128 *)vector;
        lo = 0.1047197729f;
        hi = 0.2094395458f;
        *(float *)(state + 0x10) = math_random_float_range(lo, hi);
        *(float *)(state + 0x14) = math_random_float_range(lo, hi);
        *(short *)(state + 0x18) = (short)count;
        *(short *)(state + 0x1A) = (short)count;
        if (mode == 2) {
            mode = 1;
            *(int *)(state + 0x20) = mode;
        }
        if (mode == 0)
            *(float *)(moby + 0x2C) *= math_random_float_range(0.5f, 0.75f);
        *(float *)(state + 0x1C) = *(float *)(moby + 0x2C);
        moby[0xBC] = (unsigned char)(mode | (flag << 1));
        func_002A0F48(moby);
    }
    return moby;
}
