/* func_L04_003FBEF8: near miss, 1912/1920 bytes, 0 of 2 places (USA v1.01, 1 November 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -g`.

   The shield dome draw: ten rings of sixteen quads, then three rings of a jagged band of
   twenty-eight. Calls, constants and stores agree with retail. Things that mattered: the two
   16-byte copies (+0xF0, +0x10) as TI-mode assignments (retail's lq/sq from the object, not
   qcopy); the base colour 0xA06060 as a variable (retail keeps it in $s2); `x++` loops with a
   separate `next = x + 1` (retail computes x + 1 and copies it, `addiu $s0; daddu $s6,$s0`);
   the fade as if/else with its own variable.
   What differs: which callee-saved registers hold the counters, the path record and the float
   constants (1.0, the band angles), and the inner first loop's copy of j + 1. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));

extern int D_L04_001B2008 MACRO_ADDR;
extern unsigned long long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283410(void *, void *);
extern float func_00283C28(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283D00(float, float);
extern int func_00283D38(int, int, float);
extern float func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);

/* Draws the shield dome: ten rings of sixteen quads over the upper sphere, fading in at the
   seam, then three rings of a jagged band of twenty-eight quads around its base. */
void func_L04_003FBEF8(u8 *m)
{
    Vector quad[4];
    int colors[4];
    float uv[4][2];
    unsigned long long registers[4];
    Vector matrix[4];
    Vector angles;
    u8 *q = *(u8 **)(m + 0x68);
    int i, j, k, next, alpha0, alpha1, inext, jnext;
    int base = 0xA06060;
    float full;
    float radius, scroll, lo, hi, left, right, fade, t, tilt;

    radius = *(float *)(q + 0x70) * *(float *)(q + 0x7C);
    scroll = func_00283D00(func_00283CE0(D_L04_001B2008), 30.0f) * 0.033333335f;
    *(Quad *)angles = *(Quad *)(m + 0xF0);
    angles[0] = 0.0f;
    func_00283410(matrix, angles);
    *(Quad *)matrix[3] = *(Quad *)(m + 0x10);
    registers[1] = func_0027C878(0x15);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = 0x8000000048ULL;
    registers[0] = 0;
    for (i = 0; i < 10; i++) {
        inext = i + 1;
        lo = func_00283CE0(i) * 0.17453295f / func_00283CE0(10) - 0.087266475f;
        hi = func_00283CE0(inext) * 0.17453295f / func_00283CE0(10) - 0.087266475f;
        for (j = 0; j < 16; j++) {
            jnext = j + 1;
            left = func_00283C28(func_00283CE0(j) * 1.3962636f / func_00283CE0(16)) - 0.6981318f;
            right = func_00283C28(func_00283CE0(jnext) * 1.3962636f / func_00283CE0(16)) - 0.6981318f;
            uv[0][0] = scroll + (func_00283180(left) + 1.0f) * 0.5f;
            uv[1][0] = scroll + (func_00283180(right) + 1.0f) * 0.5f;
            uv[2][0] = scroll + (func_00283180(left) + 1.0f) * 0.5f;
            uv[3][0] = scroll + (func_00283180(right) + 1.0f) * 0.5f;
            uv[0][1] = (func_00283198(lo) + 1.0f) * 0.5f;
            uv[1][1] = (func_00283198(lo) + 1.0f) * 0.5f;
            uv[2][1] = (func_00283198(hi) + 1.0f) * 0.5f;
            uv[3][1] = (func_00283198(hi) + 1.0f) * 0.5f;
            full = func_00283CE0(0x40);
            if (*(int *)(q + 0x78) != 0) {
                fade = func_00283CE0(*(int *)(q + 0x78)) * (full * 0.06666667f);
            } else {
                fade = full;
            }
            alpha0 = func_00283CF0(fade * func_00283198(func_00283CE0(i) * 3.141593f / func_00283CE0(10)));
            alpha1 = func_00283CF0(fade * func_00283198(func_00283CE0(inext) * 3.141593f / func_00283CE0(10)));
            colors[0] = j != 0 ? (alpha0 << 24) | base : 0xA06060;
            colors[1] = j != 15 ? (alpha0 << 24) | base : 0xA06060;
            colors[2] = j != 0 ? (alpha1 << 24) | base : 0xA06060;
            colors[3] = j != 15 ? (alpha1 << 24) | base : 0xA06060;
            func_002AF000(quad[0], radius, left, lo);
            func_002AF000(quad[1], radius, right, lo);
            func_002AF000(quad[2], radius, left, hi);
            func_002AF000(quad[3], radius, right, hi);
            quad[0][3] = 1.0f;
            quad[1][3] = 1.0f;
            quad[2][3] = 1.0f;
            quad[3][3] = 1.0f;
            func_00280B90(quad, matrix, 0);
        }
    }

    registers[1] = func_0027C878(0xE);
    for (k = 0; k < 3; k++) {
        float start = 0.0f, last = 0.0f, end;

        for (j = 0; j < 28; j++) {
            next = j + 1;
            left = func_00283C28(func_00283CE0(j) * 0.04986656f) - 0.6981318f;
            right = func_00283C28(func_00283CE0(next) * 0.04986656f) - 0.6981318f;
            end = func_002A7878(left, right);
            if (j == 0) {
                start = left;
            } else if (j == 27) {
                end = right;
            }
            uv[0][0] = func_00283CE0(j) * 0.035714287f;
            uv[1][0] = func_00283CE0(next) * 0.035714287f;
            uv[2][0] = func_00283CE0(j) * 0.035714287f;
            uv[3][0] = func_00283CE0(next) * 0.035714287f;
            uv[0][1] = 0.0f;
            uv[1][1] = 0.0f;
            uv[2][1] = 1.0f;
            uv[3][1] = 1.0f;
            t = uv[0][1];
            if (*(int *)(q + 0x78) != 0) {
                t = 1.0f - func_00283CE0(*(int *)(q + 0x78)) * 0.06666667f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            }
            colors[0] = colors[3] = colors[2] = colors[1] = func_00283D38(0x7FC04070, 0xFF0000, t);
            tilt = ((float *)q)[j] * (func_002A7878(-1.0f, 1.0f) * 0.017453294f) * *(float *)(q + 0x7C);
            if (tilt > 0.069813184f) {
                tilt = 0.069813184f;
            }
            if (tilt < -0.069813184f) {
                tilt = -0.069813184f;
            }
            if (j == 0) {
                last = 0.0f;
            }
            func_002AF000(quad[0], radius, start, last);
            func_002AF000(quad[1], radius, end, tilt);
            func_002AF000(quad[2], radius, start, last);
            last = tilt;
            func_002AF000(quad[3], radius, end, tilt);
            start = end;
            quad[2][2] -= 0.15f;
            quad[3][2] -= 0.15f;
            quad[3][3] = 1.0f;
            quad[0][3] = 1.0f;
            quad[1][3] = 1.0f;
            quad[2][3] = 1.0f;
            func_00280B90(quad, matrix, 0);
        }
    }
}
