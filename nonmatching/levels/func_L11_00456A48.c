/* func_L11_00456A48 - 472 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L11_00456A48 (472 B, 1 place), goes in L11_00453358.c (uses its
   existing float* prototypes of func_00282CF0/func_00282F20; draft.c declares
   D_00189E20, D_L11_001C4D80, func_00277F48, func_002A8F70).
   Draft is the right size and shape, 15 masked diff lines left:
    - retail: $s6 = &D_00189E20 (lui/addiu kept), $s7 = 0xDF9; mine has them
   swapped ($s7 / $s6)
    - one scheduling swap (`mov.s $f12,$f22` vs `daddu $a3,$s0`) before
   func_002A8F70
   Warning: the qcopy into `dead[4]` (sp+0) is a local written and never read;
   retail has that lq/sq (src/game/00325430-q.c has the same `dead` pattern)
   but a reviewer may reject it.
   Tried: hero base in a local (changes shape, worse), swapping the if/else
   (worse), copy order for `src` in the else branch (fixed the v1/s0 copy),
   v[2]=0 before the scale call (fixed). */

extern u8 D_00189E20[];
extern u8 *D_L11_001C4D80[];
extern int func_00277F48(float, void *, int, void *, int);
extern void func_002A8F70(void *, void *, int, void *, float, void *);

void func_L11_00456A48(u8 *obj, void *pos, float f12, float f13, float f14, float f15, float f16, float f17, float f18) {
    float dead[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    int n = func_00277F48(f12, pos, 0, obj, 0);
    int i;
    u8 *o;
    u8 *src;
    float a, b, c;

    if (n == 0) {
        return;
    }
    for (i = 0; i < n; i++) {
        o = D_L11_001C4D80[i];
        if (o == *(u8 **)(D_00189E20 + 0x2290)) {
            if (f13 <= 0.0f) {
                continue;
            }
            qcopy(dead, D_00189E20 + 0x80);
            a = f15;
            b = f17;
            c = f13;
            src = o + 0x10;
        } else {
            if (*(short *)(o + 0xAA) == 0xDF9) {
                continue;
            }
            qcopy(dead, o + 0x10);
            src = o + 0x10;
            a = f16;
            b = f18;
            c = f14;
        }
        func_00282CF0(v, (float *)src, (float *)(obj + 0x10));
        v[2] = 0;
        func_00282F20(v, v, a);
        v[2] = b;
        v[3] = 5600.0f;
        func_002A8F70(o, obj, 0x10001, src, c, v);
    }
}
