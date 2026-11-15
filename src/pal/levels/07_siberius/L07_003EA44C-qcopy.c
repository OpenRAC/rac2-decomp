#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void math_fast_float_d(char *);
extern void func_PAL_002B14F8(char *, char *, int, int, float);
extern int D_L07_001C9780;
extern void RideMobyBelow(char *);
extern void group_sync_counter(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void func_PAL_003273B8(char *, char *, int, void *, float);

/* Clear the two resource slots, step the state counter, refresh the object's
   transform and hand the entity to the shared launcher. */
void func_PAL_L07_003EB0C8(char *arg)
{
    char *o;
    char *src;
    char *dst;
    TI128 v;
    unsigned short c;
    float f;

    o = *(char **)(arg + 0x68);
    math_fast_float_d(o + 0x344);
    math_fast_float_d(o + 0x348);
    c = *(unsigned short *)(arg + 0x96);
    if (c <= 0xFFFE)
        *(unsigned short *)(arg + 0x96) = c + 1;
    group_sync_counter(arg, o + 0x340);
    src = arg + 0x10;
    dst = o + 0x2E0;
    FastVecSub(&v, src, dst);
    *(TI128 *)dst = *(TI128 *)src;
    if (D_L07_001C9780 != 0)
        RideMobyBelow(arg);
    if (*(unsigned char *)(arg + 0x95) == 2) {
        f = FastAddRotations(*(float *)(o + 0x2DC), 0.25132746f);
        *(float *)(o + 0x2DC) = f;
        func_PAL_003273B8(arg, o + 0x330, 1, &v, f);
    } else {
        f = FastAddRotations(*(float *)(o + 0x2DC), 0.013962637f);
        *(float *)(o + 0x2DC) = f;
        func_PAL_003273B8(arg, o + 0x330, 0, &v, f);
    }
    func_PAL_002B14F8(arg, o + 0x230, 7, 1, 2.5f);
}
