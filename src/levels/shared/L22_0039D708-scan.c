#include "include_asm.h"
#include "common.h"

/* Small-data unit for func_L22_003A4938: the five-slot table at $gp+0x3C0
 * (20 bytes, hence the assembler's -G32) and the current slot right after it,
 * bounded by the count at 0x001B2AD4, read through the absolute macro form. */

extern int D_L22_001AF3C4 __attribute__((sda));
extern int D_L22_001AF3B0[5] __attribute__((sda));
extern int D_L22_001B2AD4[] MACRO_ADDR;
extern char *D_L22_001FE940[];
extern void func_0032A1C8(void *, void *, int);
extern void func_002F3D60(void *, void *, float);
extern void func_002F3AB0(void *, void *, void *);
extern void func_002F3BB0(void *, void *, void *);
extern void func_002F3AF0(void *, void *, float);
extern void func_002F3A80(void *, void *, void *);
extern int WalkPathIsClear(void *, void *, void *);

typedef struct ScanSub_003A4938 {
    char pad[0x2A0];
    int record_ids[0];
} ScanSub_003A4938;

/* Reading the slot through an accessor matters: its inlined block stays at
 * the top of the rotated while loop, so cse1 does not merge the loop's table
 * base with the pre-test's and retail's separate loop copy is kept. */
static inline int SlotAt(int i) {
    return D_L22_001AF3B0[i];
}

/* Advances the current slot round-robin to the next one not yet spent (-1),
 * giving up after a full turn. Two point pairs are built from the first and
 * last points of the slot's record, and the slot is marked spent once
 * func_L22_003A2780 accepts both pairs. */
/* Picks the next flight lane that has not been checked yet and tests whether it is clear to fly along. */
void space_ship_pick_next_lane_to_check(char *obj) {
    float a[4], b[4], c[4], d[4], e[4], f[4], g[4], h[4], i[4], j[4];
    char *vars;
    int old = D_L22_001AF3C4;
    char *rec;
    vars = *(char **)(obj + 0x68);
    while (SlotAt(D_L22_001AF3C4 = (D_L22_001AF3C4 + 1) % D_L22_001B2AD4[0]) == -1) {
        if (old == D_L22_001AF3C4) return;
    }
    rec = D_L22_001FE940[((ScanSub_003A4938 *)vars)->record_ids[D_L22_001AF3B0[D_L22_001AF3C4]]];
    qcopy_nc(a, rec + 16);
    qcopy_nc(c, rec + *(int *)rec * 16);
    qcopy_nc(b, rec + 16);
    qcopy_nc(d, rec + *(int *)rec * 16);
    func_0032A1C8(a, h, 1);
    func_0032A1C8(c, i, 1);
    func_002F3D60(h, h, 1.0f);
    func_002F3D60(i, i, 1.0f);
    func_002F3AB0(g, c, a);
    func_002F3BB0(e, g, h);
    func_002F3D60(e, e, -1.5f);
    func_002F3D60(f, e, -1.5f);
    func_002F3AF0(j, h, *(float *)(vars + 0x114) + *(float *)(vars + 0x110));
    func_002F3A80(j, j, f);
    func_002F3A80(a, a, j);
    func_002F3AF0(j, i, *(float *)(vars + 0x114) + *(float *)(vars + 0x110));
    func_002F3A80(j, j, f);
    func_002F3A80(c, c, j);
    func_002F3AF0(j, h, *(float *)(vars + 0x114) + *(float *)(vars + 0x110));
    func_002F3A80(j, j, e);
    func_002F3A80(b, b, j);
    func_002F3AF0(j, i, *(float *)(vars + 0x114) + *(float *)(vars + 0x110));
    func_002F3A80(j, j, e);
    func_002F3A80(d, d, j);
    if (WalkPathIsClear(obj, a, c) && WalkPathIsClear(obj, b, d))
        D_L22_001AF3B0[D_L22_001AF3C4] = -1;
}
