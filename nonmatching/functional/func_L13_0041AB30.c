/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Nonmatching C reconstruction.
 * Profile: game -O2 -G8 -ffunction-sections -frac2-qcopy -g.
 * Measured size: 464 emitted bytes versus 460 retail bytes.
 * US: 0/2 local places; PAL: 0/2; US2: 0/2. All rows are present.
 * These unchanged-body checks remain failures; no strict build was run.
 * Hoisting the destination base at +0x420 across prior loops creates an
 * extra saved register. Copy controls tie. Reopen with independently
 * measured pointer lifetimes and allocator evidence.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern unsigned int func_00283D38(int, int, float);
extern int D_L13_001B1624 __attribute__((sda));
extern int D_L13_001B1628 __attribute__((sda));
extern int D_L13_001B1650 __attribute__((sda));
extern int D_L13_001B1654 __attribute__((sda));
extern int D_L13_001B1658 __attribute__((sda));
void func_L13_0041AB30(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    unsigned char *indices;
    char *dst, *src;
    int i, j, k;
    float numerator, denominator;
    if (*(short *)(state + 0x12) != 0) {
        *(short *)(state + 0x12) -= 1;
        indices = (unsigned char *)state + 0x18;
        src = state + 0x260;
        dst = state + 0x60;
        for (j = 22; j >= 0; --j) {
            func_00282CC0(dst, dst, src);
            dst += 16;
            src += 16;
        }
        for (i = 0; (float)i < 4.0f;) {
            int next = i + 1;
            char *row = state + i * 16;
            dst = row + 0x460;
            src = row + 0x560;
            for (j = 2; j >= 0; --j) {
                func_00282CC0(dst, dst, src);
                dst += 64;
                src += 64;
            }
            i = next;
        }
        dst = state + 0x420;
        for (k = 0; k < 4; ++k) {
            *(Quad *)dst = *(Quad *)(state + 0x20 + indices[k] * 16);
            dst += 16;
        }
    }
    if (*(short *)(state + 0x12) > D_L13_001B1624) {
        numerator = func_00283CE0(*(short *)(state + 0x12) - D_L13_001B1624);
        {
            int bound = D_L13_001B1624;
            denominator = func_00283CE0(*(int *)(state + 0x620) - bound);
        }
        *(int *)(state + 0x14) = func_00283D38(D_L13_001B1654, D_L13_001B1650, numerator / denominator);
    } else if (*(short *)(state + 0x12) > D_L13_001B1628) {
        numerator = func_00283CE0(*(short *)(state + 0x12) - D_L13_001B1628);
        denominator = func_00283CE0(D_L13_001B1624 - D_L13_001B1628);
        *(int *)(state + 0x14) = func_00283D38(D_L13_001B1658, D_L13_001B1654, numerator / denominator);
    } else {
        *(int *)(state + 0x14) = 0;
    }
}
