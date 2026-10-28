/* func_L22_003A4128 - 448 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file src/levels/shared/L22_003A4128.c (default flags), marker
   removal in L22_0039D708.c needed. 444 vs 448 bytes (2 places: L22, L23).
   Logic decoded: mask = (g[2]<=2 ? 2:0) | (g[3]<=0 ? 2:0) | (st[0x20] <
   (float)(x - x/6) ? 1:0); 3 rows x 50 pointer entries (D_L22_0023B530,
   stride 0xF0), nearest within 30.0 with z test < 3.0.
   Diff: ifcvt form: retail s2=0 early then `movz s2,2,v1` (v1 = 2<g[8]); mine
   s2=2 then `movn s2,zero,v1`. Loads: retail loads x (D_001B2AA8) before the
   pointer; mine loads pointer first and the div uses different regs. Tried
   gt/else, ternaries. */

#include "common.h"

extern float func_00282E48(void *, void *);
extern float func_002B0360(void *);
extern s32 D_L22_001B2AA8;
extern s32 *D_L22_001B2AB4;
extern float D_L22_001B2AA4;

typedef struct {
    u8 *entry[60];
} Row;

extern Row D_L22_0023B530[];

s32 func_L22_003A4128(u8 *obj, void *out) {
    s32 found = 0;
    s32 mask = 0;
    s32 j;
    s32 i;
    f32 best;
    f32 dist;
    u8 **p;

    if (D_L22_001B2AB4[2] <= 2) {
        mask = 2;
    }
    if (D_L22_001B2AB4[3] <= 0) {
        mask |= 2;
    }
    if (*(f32 *)(*(u8 **)(obj + 0x68) + 0x20) < (f32)(D_L22_001B2AA8 - D_L22_001B2AA8 / 6)) {
        mask |= 1;
    }
    best = 30.0f;
    for (j = 0; j < 3; j++) {
        if (mask & (1 << j)) {
            p = D_L22_0023B530[j].entry;
            for (i = 49; i >= 0; i--, p++) {
                if (*p != 0) {
                    dist = func_00282E48(*p + 0x10, obj + 0x10);
                    if (dist < best) {
                        if (func_002B0360(*p + 0x10) - D_L22_001B2AA4 < 3.0f) {
                            qcopy(out, *p + 0x10);
                            best = dist;
                            found = 1;
                        }
                    }
                }
            }
        }
    }
    return found;
}
