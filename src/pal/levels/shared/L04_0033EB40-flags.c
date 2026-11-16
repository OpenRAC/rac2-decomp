#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_move_toward_target_pal(char *,char *,float *,float *,float);

void coll_probe_ahead_of_moby_pal(char *a0, char *a1)
{
    float v[4];
    float w[4];
    float *src = (float *)(a0 + 0x10);

    qcopy(v, src);
    {
        float x = v[0] + math_fast_sin_or_cos_a(*(float *)(a0 + 0xF8)) * 100.0f;
        float angle = *(float *)(a0 + 0xF8);
        v[0] = x;
        v[1] += math_fast_sin_or_cos_b(angle) * 100.0f;
    }
    moby_move_toward_target_pal(a0, a1, v, w, 1.0f);
}
