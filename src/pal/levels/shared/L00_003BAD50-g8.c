#include "include_asm.h"

#include "common.h"
extern float g_pair_game_centre_pull __attribute__((sda));

void func_PAL_L00_003BAD50(float x, float y, float unused_step, float *p, float *q)
{
    float s = -(g_pair_game_centre_pull * 0.00040000002f) / (x * x + y * y);

    *p = *p + x * s;
    *q = *q + y * s;
}
