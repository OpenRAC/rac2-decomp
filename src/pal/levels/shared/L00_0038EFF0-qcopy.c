#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char pad00[0x10];
    TI128 position;
    char state20;
    char pad21[0x30 - 0x21];
    unsigned char alpha;
    char visible;
    short timer;
    char pad34[0x68 - 0x34];
    char *vars;
    char pad6C[0xF0 - 0x6C];
    float spin[3];
    int spinTime;
} Moby_38D530;
extern Moby_38D530 *func_0029EFD0(int size);
extern float func_002A7878(float lo, float hi);
extern int func_002FED90(Moby_38D530 *object, int a, float b, float c, float d);
extern void func_002A0F48(Moby_38D530 *object);

/* Spawns object 0x79 at A1 with the state vector A2 (the func_L00_003E7650 spawner): a random
   spin on all three axes, a 30..300 frame timer and its effect handle. */
Moby_38D530 *func_PAL_L00_00390608(TI128 *a1, TI128 *a2)
{
    Moby_38D530 *p;
    char *s0;
    float lo;
    float hi;

    p = func_0029EFD0(0x79);
    if (p != 0) {
        p->alpha = 0xFF;
        p->timer = 0x1FF;
        p->visible = 1;
        s0 = p->vars;
        p->state20 = 0;
        qcopy(&p->position, a1);
        *(TI128 *)s0 = *a2;
        lo = -3.1415927f;
        hi = 3.1415927f;
        *(int *)(s0 + 0x14) = 0;
        *(int *)(s0 + 0x10) = 0x19;
        *(int *)(s0 + 0x18) = 0xFA;
        p->spin[0] = func_002A7878(lo, hi);
        p->spin[1] = func_002A7878(lo, hi);
        p->spin[2] = func_002A7878(lo, hi);
        p->spinTime = 0;
        func_002A0F48(p);
        *(int *)(s0 + 0x1C) = func_002FED90(p, 0, 1.0f, 1.0f, 1.0f);
    }
    return p;
}
