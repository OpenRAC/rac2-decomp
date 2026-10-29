/* Retained rope solver, 2026-10-28: best624/628B, 0/1 US.
 * Five bounded trials: normal/exact pass-counter placement both624; toggling
 * before the branch616; grouped TI copies preserve616/624, no improvement.
 * Retail keeps the alternating-direction flag in A1 until the two loop arms
 * spill it. Ordinary C spills earlier and allocates state/length/backup words
 * differently. No artificial barriers, register bindings or ordinary volatile.
 * Floor-position getter004417E8 is32B: returns recordbase + (index<<7) +30,
 * so its pointer return and the +8 float consumed here are directly witnessed.
 * All copied point records16B, live13 points100..1CF; backup13 at1D0..29F;
 * twelve rest lengths2F0..31F. State minimum320 bytes, anchor object minBC.
 */
#include "common.h"
extern float *func_L11_004417E8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);

/* Four alternating constraint passes over twelve links and thirteen points.
 * Live points100..1CF, previous points1D0..29F, lengths2F0..31F.
 * Complete16-byte copies preserve the anchor's fourth lane without inventing
 * a scalar initialization; geometry operations affect XYZ only. */
void func_L11_00437FD0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float *current, *next, *previous, *rest;
    float distance, length;
    int pass, forward = 1, remaining;
    qcopy(state + 0x100, object + 0x10);
    for (pass = 0; pass < 4;) {
        if (forward) {
            forward ^= 1;
            pass++;
            current = (float *)(state + 0x100);
            previous = (float *)(state + 0x1D0);
            rest = (float *)(state + 0x2F0);
            remaining = 11;
            do {
                next = current + 4;
                if (object[0x20] >= 3 && current[2] < func_L11_004417E8(*(void **)(object + 0xB8))[2]) {
                    current[2] = func_L11_004417E8(*(void **)(object + 0xB8))[2];
                    previous[2] = current[2];
                }
                func_00282CF0(delta, next, current);
                previous += 4;
                distance = func_00282DF0(delta);
                length = *rest++;
                func_00282D30(delta, delta, length / (distance + length) - 0.5f);
                func_00282CF0(current, current, delta);
                current = next;
                func_00282CC0(next, next, delta);
            } while (--remaining >= 0);
        } else {
            pass++;
            forward = 1;
            current = (float *)(state + 0x1C0);
            previous = (float *)(state + 0x290);
            rest = (float *)(state + 0x31C);
            remaining = 11;
            do {
                next = current - 4;
                if (object[0x20] >= 3 && current[2] < func_L11_004417E8(*(void **)(object + 0xB8))[2]) {
                    current[2] = func_L11_004417E8(*(void **)(object + 0xB8))[2];
                    previous[2] = current[2];
                }
                func_00282CF0(delta, next, current);
                previous -= 4;
                distance = func_00282DF0(delta);
                length = *rest--;
                func_00282D30(delta, delta, length / (distance + length) - 0.5f);
                func_00282CF0(current, current, delta);
                current = next;
                func_00282CC0(next, next, delta);
            } while (--remaining >= 0);
        }
        qcopy(state + 0x100, object + 0x10);
    }
}
