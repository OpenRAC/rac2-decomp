/* func_002A89A8: both copies of the object position are qcopy(), so the destinations
 * are held in registers and the 0.01f store sits between them, as in retail. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern float D_001BAFA8;
extern int func_002761F8(void *, void *, int, void *, int);

/* Checks for ground just below the object and returns the ground height offset, or 0 if none is found. */
float func_002A89A8(char *object, int mode, float amount)
{
    Vector local;
    Vector query;

    qcopy(&local, object);
    local.f[2] = 0.01f;
    qcopy(&query, object);
    query.f[2] += amount;
    if (CollLine(query.f, local.f, mode | 2, 0, 0))
        return D_001BAFA8;
    return 0.0f;
}
