#include "common.h"
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int id);
extern void func_002A0F48(char *object);

/* Finds the object with the fixed id, marks it and gives it the caller's position. */
int func_00302A20(void *object)
{
    void *found = CreateMoby(0x3EF);

    if (found != 0) {
        *(unsigned short *)((char *)found + 0x34) |= 0x41;
        *(unsigned char *)((char *)found + 0x30) = 0xFF;
        *(TI128 *)((char *)found + 0x10) = *(TI128 *)object;
        func_002A0F48(found);
    }
    return (int)found;
}

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
void func_00305438(void *obj, void *other)
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
            e->f20 = 120.0f;
            qcopy(&e->b, other);
            qcopy(e, &local);
            break;
        }
    }
}
