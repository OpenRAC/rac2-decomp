/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, 29 October 2026. Upstream pinned GNU game compiler.
 * Best US check: 1768/1768 bytes, 0/2 placements, -O2 -G0 -ffunction-sections.
 * Byte-offset indexing for quadword copies, typed indexing for vector callees,
 * and qcopy_nc in the initial independent pool copy recover the 0x100 frame and
 * both the column index and running pool-base lifetimes. Keeping the source's
 * +1 vector offset inside the loop recovers retail's complete initial copy loop.
 * Remaining: tangent pointer spills at sp+0x60 rather than +0x64; flags are masked
 * early rather than copied whole; output-pool bases/next-column allocation differ.
 * Attraction FP allocation and division-label padding also remain different.
 * An earlier form with -g gives 1776 bytes and recovers the division nops; qcopy /
 * barrier with TI assignments gives 1784. Separate output-pool views, byte-offset
 * regrouping and a captured normalized attraction length did not close the gap.
 * Reopen with evidence for output base/column lifetimes across the final loop.
 * Declarations below are complete. No linked build: not an exact match.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } RopeVector;
extern RopeVector D_L03_00238040[][16];

extern float (*D_L03_001FE700[])[4];
extern RopeVector D_L03_00237F40[];
extern float D_00189EA0[];
extern float func_00283B98(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283248(float, float);


void func_L03_0038B5D8(u8 *object)
{
    RopeVector toward, relative, blended, tangent, radial, jitter;
    u8 *state = *(u8 **)(object + 0x68);
    int row, column;
    int flags;
    float segmentLength, vertical, phase, angle, magnitude;
    *(float *)(state + 0x94) = func_00283B98(*(float *)(state + 0x94), *(float *)(state + 0x98));
    *(float *)(state + 0xA8) = func_00283B98(*(float *)(state + 0xA8), *(float *)(state + 0x98));
    *(float *)(state + 0x84) += *(float *)(state + 0x88);
    if (*(float *)(state + 0x84) > 1.0f)
        *(float *)(state + 0x84) -= 1.0f;
    for (row = 0; row < 4; row++) {
        flags = *(int *)(state + 0x3C);
        if ((flags & 1) && *(int *)(state + 0x28 + row * 4) >= 0) {
            int group = *(int *)(state + 0x28 + row * 4);
            RopeVector *source = (RopeVector *)D_L03_001FE700[group];
            int limit = *(int *)(state + 0x38);
            for (column = 0; column < limit; column++)
                qcopy_nc(&D_L03_00238040[*(int *)(state + 0xDC) + row][column], &source[column + 1]);
            if (flags & 8) {
                float distance, strength;
                func_00282CF0(&toward, D_00189EA0, state + 0xE0);
                distance = func_00282DF0(&toward);
                func_00282F20(&toward, &toward, 1.1f);
                if (!(distance > *(float *)(state + 0xD4) + 1.1f)) {
                    strength = 1.0f - (distance - 1.1f) / *(float *)(state + 0xD4);
                    for (column = 0; column < *(int *)(state + 0x38); column++) {
                        RopeVector *vertex = &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC) + row) * 256 + (column) * 16)));
                        float length, amount;
                        qcopy(&relative, vertex);
                        func_00282CF0(&relative, &relative, state + 0xE0);
                        length = func_00282DF0(&relative);
                        if (length > 1.1f)
                            length = 1.1f;
                        amount = strength * (1.0f - length * 0.9090909f);
                        func_00282D30(&blended, &toward, amount);
                        func_00282D30(&relative, &relative, 1.0f - amount);
                        func_00282CC0(&blended, &blended, &relative);
                        func_00282CC0(&D_L03_00238040[*(int *)(state + 0xDC) + row][column], &blended, state + 0xE0);
                    }
                }
            }
        } else {
            tangent.quad = 0;
            tangent.f[3] = 1.0f;
            switch (row) {
            case 0:
                tangent.f[2] += 1.1f;
                break;
            case 1:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] -= 0.6395348906517029f;
                break;
            case 2:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] += 0.6395348906517029f;
                break;
            default:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] += 0.785714328289032f;
                break;
            }
            for (column = 0; column < *(int *)(state + 0x38); column++) {
                RopeVector *vertex;
                func_00282F20(&radial, &tangent, (float)column / ((float)*(int *)(state + 0x38) - 0.5f));
                vertex = &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC) + row) * 256 + (column) * 16)));
                qcopy(vertex, &radial);
                func_00282CC0(&D_L03_00238040[*(int *)(state + 0xDC) + row][column], &D_L03_00238040[*(int *)(state + 0xDC) + row][column], state + 0xE0);
            }
        }
    }
    func_00282CF0(&tangent, &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC)) * 256 + (1) * 16))),
                             &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC)) * 256 + (0) * 16))));
    segmentLength = func_00282DF0(&tangent);
    for (column = 0; column < *(int *)(state + 0x38); column++) {
        vertical = 0.0f;
        phase = 0.0f;
        if (!(*(int *)(state + 0x3C) & 0x40))
            func_00282D30(&jitter, &D_L03_00237F40[column], *(float *)(state + 0x90) * segmentLength);
        if (!(*(int *)(state + 0x3C) & 0x80)) {
            float firstPhase = func_002ABB18(*(float *)(state + 0x94) + (float)column * -1.780236005783081f);
            float first = *(float *)(state + 0xA0) * func_00283198(firstPhase);
            phase = func_002ABB18(*(float *)(state + 0xA8) + (float)column * -1.5184365510940552f);
            vertical = segmentLength * (first * func_00283198(phase));
        }
        if (!(*(int *)(state + 0x3C) & 0x100)) {
            angle = func_00283B98(func_00283248(tangent.f[0], tangent.f[1]), 1.5707964897155762f);
            magnitude = segmentLength * *(float *)(state + 0xA4) * func_00283180(phase);
            radial.f[0] = func_00283180(angle) * magnitude;
            radial.f[1] = func_00283198(angle) * magnitude;
            radial.f[2] = 0.0f;
        }
        for (row = 0; row < 4; row++) {
            int base = *(int *)(state + 0xDC) + row;
            RopeVector *original = &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((base) * 256 + (column) * 16)));
            RopeVector *output = &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((base + 4) * 256 + (column) * 16)));
            qcopy(output, original);
            if (column != 0 && column != *(int *)(state + 0x38) - 1) {
                if (!(*(int *)(state + 0x3C) & 0x40)) {
                    func_00282CC0(output, output, &jitter);
                    func_00282CC0(&D_L03_00238040[*(int *)(state + 0xDC) + row][column], &D_L03_00238040[*(int *)(state + 0xDC) + row][column], &jitter);
                }
                if (!(*(int *)(state + 0x3C) & 0x80))
                    (*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC) + row + 4) * 256 + (column) * 16))).f[2] += vertical;
                if (!(*(int *)(state + 0x3C) & 0x100))
                    func_00282CC0(&(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC) + row + 4) * 256 + (column) * 16))),
                                 &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((*(int *)(state + 0xDC) + row + 4) * 256 + (column) * 16))), &radial);
            }
        }
    }
}
