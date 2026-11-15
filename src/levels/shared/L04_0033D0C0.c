#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_move_toward_target(char *,char *,float *,float *,float);
/* Looks at a point 100 units in front of an object and passes it on. */
void coll_probe_ahead_of_moby(char *srcMoby, char *otherMoby)
{
    float ahead[4];
    float result[4];
    float *src = (float *)(srcMoby + 0x10);

    qcopy(ahead, src);
    {
        float x = ahead[0] + math_fast_sin_or_cos_a(*(float *)(srcMoby + 0xF8)) * 100.0f;
        float angle = *(float *)(srcMoby + 0xF8);
        ahead[0] = x;
        ahead[1] += math_fast_sin_or_cos_b(angle) * 100.0f;
    }
    moby_move_toward_target(srcMoby, otherMoby, ahead, result, 1.0f);
}
