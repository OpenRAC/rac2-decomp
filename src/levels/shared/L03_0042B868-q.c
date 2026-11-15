/* func_L03_0042B868 (156 bytes; levels 03, 06, 09): copies the two input vectors into the
   object's controller block, interpolates them halfway (lerp_vector), keeps the result at
   the object and stores their distance. The two entry copies are qcopy: across them the
   argument registers are reloaded from their saved copies, as in retail. */
#include "common.h"

typedef int Q128 __attribute__((mode(TI)));

extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);

void func_L03_0042B868(char *a0, Q128 *a1, Q128 *a2)
{
    char *p;

    if (a0 == 0)
        return;
    {
        p = *(char **)(a0 + 0x68);
        qcopy(p, a1);
        qcopy(p + 0x10, a2);
        lerp_vector(p + 0x30, a1, a2, 0.5f);
        *(Q128 *)(a0 + 0x10) = *(Q128 *)(p + 0x30);
        *(float *)(p + 0x3C) = fast_vec_dist(a1, a2);
    }
}
