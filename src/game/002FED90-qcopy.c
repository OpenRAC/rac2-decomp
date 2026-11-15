/* func_002FED90 in its own unit: it takes the first free slot of the 128-entry
   effect table at 0x002212E0 for obj, filling its position, its xyz and its owner,
   and answers the slot's index (or -1 when the table is full). Retail's two
   128-bit copies of the source vector keep their addresses in registers, which
   is the opt-in grouped copy, so config/cflags.txt gives this file
   "-O2 -G0 -ffunction-sections -frac2-qcopy". The resident's quad (when its
   +0x348 halfword is set) goes into the slot through qcopy() and a pointer to the
   slot's position, the copy retail makes in $a0. */

#include "include_asm.h"
#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef struct {
    Quad pos;
    float x, y, z;
    char *owner;
} EffectSlot;

extern EffectSlot D_002212E0[];
extern char D_00189E20[];
extern void func_002AFFD8(void *, void *, int);

/* Claims a free effect slot for the object and returns its number, or -1 if all are used. */
int func_002FED90(char *obj, Quad *src, float x, float y, float z)
{
    int i = 0;
    EffectSlot *e = D_002212E0;
    Quad *pos;
    Quad v;
    char *h;
    Quad *def = (Quad *)(obj + 0x10);

    do {
        if (e->owner == 0) {
            if (src)
                v = *src;
            else
                v = *def;
            e->owner = obj;
            e->x = x;
            e->y = y;
            e->z = z;
            pos = &e->pos;
            h = gHeroState;
            if (*(short *)(h + 0x348) != 0)
                qcopy(pos, *(char **)(h + 0x2290) + 0xE0);
            else
                ComputeViewDirection(&v, e, 1);
            return i;
        }
        i++;
        e++;
    } while (i < 0x80);
    return -1;
}
