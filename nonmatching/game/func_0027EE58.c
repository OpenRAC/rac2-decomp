/* func_0027EE58 - 696 bytes, 28 places (the boot and every level).
   Screened in wave 13 (worker g4): 17 call(s), 0 $gp-relative small-data access(es), 0 MMI lq/sq word(s), 13 64-bit daddu copy(ies), 0 float constant(s).
   17 calls and 13 pointers copied with daddu $d,$s,$zero, where this cc1 sign-extends with dsll/dsra.
   Not matched in wave 13 (worker g4): screening only; no C candidate was tested in this wave. */
/* Retained bounded near miss, 2026-10-28: 680/696 bytes with-g.
 * Four forms. Default672 bytes lacks retail division hazard padding; -g
 * supplies it. A guarded do/while count lifetime, -fno-regmove and then
 * -fno-gcse all tie680. Broader controls are not retained. Compiler holds
 * fourFPRs where retail keeps five, coalescing current/next angle lifetimes.
 * Reopen on a measured genuine angular lifetime witness.
 * Actual caller windows (boot273234/2732bc, plus carrying level copies)
 * confirm color/UV pointer inputs and a16 segment divisor. The function
 * still draws exactly16 strips for any divisor, as the real loop specifies.
 * Centers participate in full64-bit packed arithmetic; callers supply their
 * sign-extended32-bit screen values. Renderer gets complete32-byte vertices,
 *16-byte UV and16-byte color inputs, full64-bit texture and integer mode.
 * Two16-byte angular locals define/useXYZ only; no W load or helper transfer.
 * All coordinate packing uses unsigned64-bit shifts/additions before storing
 * the signed renderer words. Canonical callee signatures retained.
 */
#include "common.h"

extern unsigned long func_0027C878(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_0027E920(const long *, const int *, const int *, unsigned long long, int);

/* Draw sixteen arc strips. Retail callers supply sign-extended screen
 * centers and two complete four-word color/UV tables. Coordinate additions
 * and shifts deliberately operate in unsigned64-bit packed arithmetic.
 * The two16-byte angular vectors useXYZ only; no fourth lane is consumed. */
void func_0027EE58(long center_x, long center_y, int inner_radius, int outer_radius,
                   const int *colors, const int *uv, int texture_index, int segments,
                   float start, float end)
{
    long vertices[4];
    float first[4], second[4];
    unsigned long texture = func_0027C878(texture_index);
    float step = (end - start) / (float)segments;
    float angle = func_00283B98(start, 1.57079649f);
    float next = func_00283B98(angle, step);
    float inner = (float)inner_radius, outer = (float)outer_radius;
    int i;
    i = 15;
    do {
        first[0] = func_00283180(angle);
        first[1] = func_00283198(angle);
        first[2] = 0.0f;
        angle = next;
        --i;
        second[0] = func_00283180(next);
        second[1] = func_00283198(next);
        second[2] = 0.0f;
        vertices[3] = 0;
        vertices[2] = 0;
        vertices[1] = 0;
        vertices[0] = 0;
        vertices[0] += (unsigned long)func_00283CF0(first[0] * inner) + (unsigned long)center_x;
        vertices[0] += ((unsigned long)func_00283CF0(first[1] * inner) + (unsigned long)center_y) << 16;
        vertices[1] += (unsigned long)func_00283CF0(first[0] * outer) + (unsigned long)center_x;
        vertices[1] += ((unsigned long)func_00283CF0(first[1] * outer) + (unsigned long)center_y) << 16;
        vertices[2] += (unsigned long)func_00283CF0(second[0] * inner) + (unsigned long)center_x;
        vertices[2] += ((unsigned long)func_00283CF0(second[1] * inner) + (unsigned long)center_y) << 16;
        vertices[3] += (unsigned long)func_00283CF0(second[0] * outer) + (unsigned long)center_x;
        vertices[3] += ((unsigned long)func_00283CF0(second[1] * outer) + (unsigned long)center_y) << 16;
        vertices[1] += 0xFFFFF000000000UL;
        vertices[0] += 0xFFFFF000000000UL;
        vertices[3] += 0xFFFFF000000000UL;
        vertices[2] += 0xFFFFF000000000UL;
        func_0027E920(vertices, uv, colors, texture, 1);
        next = func_00283B98(angle, step);
    } while (i >= 0);
}
