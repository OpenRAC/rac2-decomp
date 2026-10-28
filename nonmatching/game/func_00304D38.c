/* func_00304D38 and func_00307500 - 496 bytes each, 28 places.  Both match
   byte for byte at every place in us, pal and us2 with this unit,
   src/game/00300618-g8-qcopy.c, flags
   `-O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`, with their
   markers removed from src/game/00300618.c.

   Not landed: each fills a local `t0[4] = {0, 0, 0, 1}` that is never read.
   Retail has those four stack stores, so the original source probably had the
   unused local too, but an unread local breaks the batch's no-dead-locals
   rule.  A maintainer can decide whether this is acceptable. */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { int w[3]; } Query304D38;

extern float ref_L00_00304D38_00 __attribute__((sda));
extern Query304D38 D_001AEC10;
extern Query304D38 D_001AEC70;
extern float ref_L00_00307500_00 __attribute__((sda));

extern void func_002FE8D8(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern char *func_002AF580(void *, void *, float, float, void *, int, int, int, float, float, float, int, Query304D38 *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);

void func_00304D38(char *object)
{
    char *state;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    Query304D38 query;
    float e[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float basis[4] __attribute__((aligned(16)));
    float t0[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char buf[16] __attribute__((aligned(16)));
    char *hit;
    char *src;

    state = *(char **)(object + 0x68);
    func_002FE8D8(object + 0x10, a);
    func_0029FCC0(object, 0, b);
    if (*(char **)(state + 0x68) == 0) {
        query = D_001AEC10;
        hit = func_002AF580(b, object + 0xC0, 6.2831855f, 6.2831855f, buf, 0, 0, 0,
                            ref_L00_00304D38_00, 0.0f, 0.0f, 0, &query);
        *(char **)(state + 0x68) = hit;
        if (hit != 0) {
            object[0x20] = 4;
            *(float *)(state + 0x5C) = 0.0f;
        }
    }
    if (*(short *)(state + 0x4C) == 0 && *(char **)(state + 0x68) == 0)
        return;
    src = state + 0x30;
    if (*(char **)(state + 0x68) == 0) {
        TI128 zero = 0;
        float f;
        float r;

        *(TI128 *)up = zero;
        up[2] = 1.0f;
        qcopy(dir, src);
        func_00282DD8(side, dir, up);
        func_00282F20(side, side, 1.0f);
        func_00282DD8(basis, side, dir);
        t0[0] = 0.0f;
        t0[1] = 0.0f;
        t0[2] = 0.0f;
        t0[3] = 1.0f;
        func_002AB6D8(dir, e);
        f = func_00283B98(e[2], func_002A78D8(0.78539825f, 1.5707965f));
        r = func_002A7878(-0.1f, 0.45f);
        func_002AF000(state + 0x20, 1.0f, f, r);
    }
    qcopy(state + 0x10, src);
    *(int *)(state + 0x54) = 0;
    *(short *)(state + 0x4C) = 0;
}

void func_00307500(char *object)
{
    char *state;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    Query304D38 query;
    float e[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float basis[4] __attribute__((aligned(16)));
    float t0[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char buf[16] __attribute__((aligned(16)));
    char *hit;
    char *src;

    state = *(char **)(object + 0x68);
    func_002FE8D8(object + 0x10, a);
    func_0029FCC0(object, 0, b);
    if (*(char **)(state + 0x64) == 0) {
        query = D_001AEC70;
        hit = func_002AF580(b, object + 0xC0, 6.2831855f, 6.2831855f, buf, 0, 0, 0,
                            ref_L00_00307500_00, 0.0f, 0.0f, 0, &query);
        *(char **)(state + 0x64) = hit;
        if (hit != 0) {
            object[0x20] = 4;
            *(float *)(state + 0x5C) = 0.0f;
        }
    }
    if (*(short *)(state + 0x4C) == 0 && *(char **)(state + 0x64) == 0)
        return;
    src = state + 0x30;
    if (*(char **)(state + 0x64) == 0) {
        TI128 zero = 0;
        float f;
        float r;

        *(TI128 *)up = zero;
        up[2] = 1.0f;
        qcopy(dir, src);
        func_00282DD8(side, dir, up);
        func_00282F20(side, side, 1.0f);
        func_00282DD8(basis, side, dir);
        t0[0] = 0.0f;
        t0[1] = 0.0f;
        t0[2] = 0.0f;
        t0[3] = 1.0f;
        func_002AB6D8(dir, e);
        f = func_00283B98(e[2], func_002A78D8(0.78539825f, 1.5707965f));
        r = func_002A7878(-0.1f, 0.45f);
        func_002AF000(state + 0x20, 1.0f, f, r);
    }
    qcopy(state + 0x10, src);
    *(int *)(state + 0x54) = 0;
    *(short *)(state + 0x4C) = 0;
}
