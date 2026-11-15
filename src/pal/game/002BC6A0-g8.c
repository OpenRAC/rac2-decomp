#include "include_asm.h"
#include "names.h"

extern void part_kill(char *);
extern int FloatToInt(float);
extern int math_fast_float_d(char *);
extern float FastAddRotations(float, float);
extern int D_001AA304 __attribute__((sda));

/* func_PAL_002BC6A0, the PAL copy of func_002BBA38: the same C, with the frame count scaled to 50 Hz. */
void func_PAL_002BC6A0(char *particle)
{
    char *state = particle + 32;
    int alpha;
    unsigned int shifted;
    int color;
    if (math_fast_float_d(state)) {
        part_kill(particle);
    } else {
        *(float *)(state + 12) = FastAddRotations(*(float *)(state + 12), *(float *)(state + 8));
        particle[8] = FloatToInt(*(float *)(state + 12) * 40.7436637878418f) - 128;
        if (*(int *)(particle + 32) > ((D_001AA304 * 5 + 2) / 6) * 3 / 4)
            alpha = *(int *)(state + 16) * (((D_001AA304 * 5 + 2) / 6) - *(int *)(particle + 32)) / (((D_001AA304 * 5 + 2) / 6) / 4);
        else if (*(int *)(particle + 32) < ((D_001AA304 * 5 + 2) / 6) / 4)
            alpha = *(int *)(state + 16) * *(int *)(particle + 32) / (((D_001AA304 * 5 + 2) / 6) / 4);
        else
            alpha = *(int *)(state + 16);
        shifted = (unsigned int)alpha << 24;
        switch ((unsigned char)particle[3]) {
        case 72:
            color = shifted + 0x004f4f4f;
            break;
        default:
            color = shifted + 0x007f7f7f;
            break;
        }
        *(int *)(particle + 4) = color;
    }
}
