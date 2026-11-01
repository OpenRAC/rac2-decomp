#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 a;
    TI128 b;
    float f20;
    void *owner;
    int pad28, pad2C;
} Slot00305438;
extern void func_0029FCC0(void *a, int b, void *c);
extern Slot00305438 ref_00305438_00[];

/* Takes the first free entry of the table for the object and counts it. */
void func_PAL_003066B8(void *obj, void *other)
{
    char *s0 = *(char **)((char *)obj + 0x68);
    TI128 local;
    int i;

    func_0029FCC0(obj, 1, &local);
    for (i = 0; i < 100; i++) {
        if (ref_00305438_00[i].owner == 0) {
            Slot00305438 *e = &ref_00305438_00[i];

            *(int *)(s0 + 0x64) += 1;
            e->owner = obj;
            e->f20 = 1e+02f;
            qcopy(&e->b, other);
            qcopy(e, &local);
            break;
        }
    }
}
