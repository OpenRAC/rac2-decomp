/* func_L04_00412C58 - 480 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Leaf function, args (int, char *a1, f12..f16). Control flow and all float
   ops right (draft.c, 464 vs 480 B).
   Open: (1) D_001A79F0 and D_L04_001A8FE4 must be tied absolute macro loads
   (`lui v1,0x1A; lw v1,0x79F0(v1)`); `[] sda` gives $gp here, plain gives
   split lui/addiu hoist.
   (2) retail copies e=d+a with `add.s f0; ...; mov.s f4,f0` in the bc1f delay
   slot; mine adds straight into f4. */

extern int D_001A79F0[] __attribute__((sda));
extern int D_L04_001A8FE4[] __attribute__((sda));

void func_L04_00412C58(int unused, char *a1, float t, float a, float b, float c, float d)
{
    float e;
    float r;
    float bonus;

    if (*(int *)(a1 + 0x34C) >= 8) {
        *(float *)(a1 + 0x298) = *(float *)(a1 + 0x2A8) + c * 0.00027777778f;
        return;
    }
    if (d + a < t) {
        e = d + a;
        if (D_001A79F0[0] == 4 && *(s16 *)(a1 + 0x274) != 0 && *(int *)(a1 + 0x314) == -1
            && *(int *)(a1 + 0x318) >= 0x1DC) {
            r = *(float *)(a1 + 0x27C) * 9.999999f;
            if (r > 1.0f)
                r = 1.0f;
            else if (r < 0.0f)
                r = 0.0f;
            if (D_L04_001A8FE4[0] >= 2)
                bonus = r * 7.0f + 3.5f;
            else
                bonus = r * 3.0f + 1.5f;
        } else {
            bonus = 0.0f;
        }
        r = (t - a + d) / e;
        if (r > 1.0f)
            r = 1.0f;
        if (r < 0.0f)
            r = 0.0f;
        *(float *)(a1 + 0x298) = *(float *)(a1 + 0x2A8) - (c + bonus) * r * 0.00027777778f;
    } else {
        r = (a - t + d) / a;
        if (r > 1.0f)
            r = 1.0f;
        if (r < 0.0f)
            r = 0.0f;
        r *= b;
        *(float *)(a1 + 0x298) = *(float *)(a1 + 0x2A8) + c * r * 0.00027777778f;
    }
}
