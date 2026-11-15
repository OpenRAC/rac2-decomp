/* func_L03_0042B868 (156 bytes; levels 03, 06, 09): copies the two input vectors into the
   object's controller block, interpolates them halfway (func_00282D08), keeps the result at
   the object and stores their distance. The two entry copies are qcopy: across them the
   argument registers are reloaded from their saved copies, as in retail. */
#include "common.h"

typedef int Q128 __attribute__((mode(TI)));

extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);

/* Sets up an object between two points: it sits at the midpoint and remembers the distance between them. */
void func_L03_0042B868(char *moby, Q128 *start, Q128 *end)
{
    char *vars;

    if (moby == 0)
        return;
    {
        vars = *(char **)(moby + 0x68);
        qcopy(vars, start);
        qcopy(vars + 0x10, end);
        lerp_vector(vars + 0x30, start, end, 0.5f);
        *(Q128 *)(moby + 0x10) = *(Q128 *)(vars + 0x30);
        *(float *)(vars + 0x3C) = fast_vec_dist(start, end);
    }
}
