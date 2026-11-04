/* 4 November 2026, real source-group review; retained, not linked.
 * Default G0 profile in L01_002A7248.c: a group containing the actual height read restores the
 * full retail register map. It is 276/272 bytes, 0/5 USA places: only the alignment nop at +0x74
 * remains (then shifts the following instructions). Including normal preparation or the whole
 * response with its real return keeps 276 bytes and loses that register map. The retained best
 * group is below with complete declarations and the existing four-word pointer interface; no
 * dummy owner reference was used. Reopen with a real height-lifetime/label-alignment witness, not
 * padding removal or invented volatility. Older measurements follow as history.
 */
#include "common.h"
typedef struct { char pad[0x18]; void *moby; int count; char gap[0x20]; float normal[4]; } ProbeResult;
extern ProbeResult D_L01_001BF900;
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
/*
 func_L01_0031B300 (272 bytes, 5 places) - default flags (-O2 -G0), in L01_002A7248.c; right size.
 opus-1 (v2139, 2026-11-03), recompiled on v2/c04: 272/272 bytes, 0/5 places, 12 instruction rows differ
 (20 counting relocation-only rows): only the saved-register roles of a0 and the global base g are exchanged
 (retail a0 -> s2, g -> s3; ours g -> s2, a0 -> s3). Needs the file's ProbeResult/D_L01_001BF900,
 func_002761F8, func_00282F20, func_00282CF0, func_00282DB0, func_00282CC0 declarations plus the two below.
 Why (measured with tools/regalloc.py and the cc1 source): a0 is pseudo 84, 5 refs over 44 insns after sched1
 (priority 2*5/44 = 0.227); g is pseudo 90, 4 refs over 16 insns after sched1, but its constant-address
 REG_EQUIV makes update_equiv_regs double that to 32 (local-alloc.c `REG_LIVE_LENGTH (regno) *= 2`), giving
 2*4/32 = 0.25, so g is allocated first and takes s2. Retail needs a0 > g: a sixth a0 reference, or g live over
 at least 18 post-sched1 insns (sched1 puts `a2 = g + 0x20` before the a0/a1 moves of the VecSub call; after
 them would be 18), or a0 under 40.
 Tied or worse here: g initialised before CollLine (65 rows), struct-field access without g (260 bytes, base
 split into %hi/%lo loads), typed `ProbeResult *hit` with direct `return 0` (same priorities), one combined
 `p != 0 && (...)` test (same priorities), `w = *(Vector *)(g + 0x40)` instead of qcopy (g gets 6 refs).
 Earlier: the permuter reaches 5/5 only with an identical-arm `if (a0)` around the 0xAA load (not allowed);
 that is exactly the missing sixth a0 reference.
 Reopen with a real construct that references a0 once more (and vanishes) or lengthens g's range.
 */
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern float func_00282C48(float f12);

int func_L01_0031B300(void *a0, void *a1, void *a2, void *a3) {
    Vector v, w;
    float f20;
    float f2;
    char *g;
    char *h;
    char *p;
    int v1;

    if (func_002761F8(a2, a3, 0x10, a0, 0) == 0)
        goto fail;
    g = (char *)&D_L01_001BF900;
    p = *(char **)(g + 0x18);
    if (p != 0) {
        v1 = *(short *)(p + 0xAA);
        if (v1 == 0x881 || v1 == 0)
            return 0;
    }
    do {
        f20 = *(float *)(a0 + 0x18);
    } while (0);
    qcopy(&w, g + 0x40);
    h = g + 0x40;
    func_00282F20(w.f, w.f, 1.0f);
    func_00282CF0(&v, a3, g + 0x20);
    f2 = func_00282C48(func_00282DB0(v.f, w.f));
    func_00282F20(w.f, (float *)h, f2);
    func_00282CC0(a0 + 0x10, a0 + 0x10, &w);
    *(float *)(a0 + 0x18) = f20;
    return 1;
fail:
    return 0;
}
