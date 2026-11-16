#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_move_toward_target_pal(char *,char *,float *,float *,float);

/* Looks at a point 100 units in front of an object and passes it on (PAL). */
void coll_probe_ahead_of_moby_pal(char *moby, char *other_moby)
{
    float target[4];
    float result[4];
    float *src = (float *)(moby + 0x10);

    qcopy(target, src);
    {
        float x = target[0] + math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 100.0f;
        float angle = *(float *)(moby + 0xF8);
        target[0] = x;
        target[1] += math_fast_sin_or_cos_b(angle) * 100.0f;
    }
    moby_move_toward_target_pal(moby, other_moby, target, result, 1.0f);
}
