/* func_L11_00437FD0: four alternating constraint passes over the object's state
 * (field 0x68): live points at 0x100..0x1CF (16-byte records), previous points at
 * 0x1D0..0x29F, twelve rest lengths at 0x2F0..0x31F. A forward pass walks links
 * 0..11 and a backward pass links 11..0. For each link, when object byte 0x20 >= 3
 * the point's Z is raised to the Z returned by func_L11_004417E8 (also written to
 * the previous point); then delta = next - current is scaled by
 * length / (|delta| + length) - 0.5, subtracted from current and added to next.
 * After each pass object + 0x10 is copied over the first point again.
 *
 * Why the shape matches:
 * - The direction flag and pass count are carried as next-state values set in each
 *   arm and copied back at the end of the iteration. The arm-local values are live
 *   across calls and get stack slots (0x10/0x14); the loop-top values are short
 *   pseudos in $a1/$v1, so each arm stores after its definition and the reloads
 *   sit before the shared copy and the pass test, as retail.
 * - Indexing the lengths by the loop counter makes the length pointer a loop.c
 *   giv set after the hoisted copy addresses ($s7/$fp); the backward pass counts
 *   down from 11, the forward one is reversed by loop.c.
 * - `length` is block-local so local-alloc keeps it and the quotient in $f12;
 *   `next` is computed after the clamp so the scheduler puts it before the
 *   counter decrement. -g (config/cflags.txt) gives the line-label nop before div.s.
 */
#include "common.h"
extern float *func_L11_004417E8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);

void func_L11_00437FD0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float *current, *next, *previous;
    float distance;
    int pass, forward = 1, i;
    int npass, nforward;
    qcopy(state + 0x100, object + 0x10);
    pass = 0;
    do {
        if (forward) {
            nforward = forward ^ 1;
            npass = pass + 1;
            current = (float *)(state + 0x100);
            previous = (float *)(state + 0x1D0);
            for (i = 0; i < 12; i++) {
                float length;
                if (object[0x20] >= 3 && current[2] < func_L11_004417E8(*(void **)(object + 0xB8))[2]) {
                    current[2] = func_L11_004417E8(*(void **)(object + 0xB8))[2];
                    previous[2] = current[2];
                }
                next = current + 4;
                func_00282CF0(delta, next, current);
                previous += 4;
                distance = func_00282DF0(delta);
                length = ((float *)(state + 0x2F0))[i];
                func_00282D30(delta, delta, length / (distance + length) - 0.5f);
                func_00282CF0(current, current, delta);
                func_00282CC0(next, next, delta);
                current = next;
            }
        } else {
            npass = pass + 1;
            nforward = 1;
            current = (float *)(state + 0x1C0);
            previous = (float *)(state + 0x290);
            for (i = 11; i >= 0; i--) {
                float length;
                if (object[0x20] >= 3 && current[2] < func_L11_004417E8(*(void **)(object + 0xB8))[2]) {
                    current[2] = func_L11_004417E8(*(void **)(object + 0xB8))[2];
                    previous[2] = current[2];
                }
                next = current - 4;
                func_00282CF0(delta, next, current);
                previous -= 4;
                distance = func_00282DF0(delta);
                length = ((float *)(state + 0x2F0))[i];
                func_00282D30(delta, delta, length / (distance + length) - 0.5f);
                func_00282CF0(current, current, delta);
                func_00282CC0(next, next, delta);
                current = next;
            }
        }
        forward = nforward;
        qcopy(state + 0x100, object + 0x10);
        pass = npass;
    } while (pass < 4);
}
