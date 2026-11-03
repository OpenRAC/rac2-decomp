/* functional: high. From the near-miss draft (608/584 bytes; loop-invariant hoisting differs, see the draft in nonmatching/levels); same reads, writes and calls in retail's order. Placed in levels 06 and 15; names are level 06's (gated SAME in level 15 with that level's D_L15_ names substituted in a test copy). */
#include "common.h"

extern void func_0026FEB8(const char *, ...);
extern const char D_L06_001AA660[];
extern char *D_L06_001FE500[];
extern float D_L06_001B9A90[];
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern u8 *func_L03_00339128(void *, void *, int, int, u8, s16, u8, float);

void func_L06_00382608(void *data, int path, int owner, int flags, int stride, float scale)
{
    float previous[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float advance[4] __attribute__((aligned(16)));
    char *polygon;
    int timer;
    int index;

    if (path == -1) {
        func_0026FEB8(D_L06_001AA660);
        return;
    }
    polygon = D_L06_001FE500[path];
    timer = (flags & 0x40) ? -1 : 2;
    qcopy(previous, polygon + 0x10);
    for (index = 0; index < *(int *)polygon; index += stride) {
        func_00282F20(advance, D_L06_001B9A90, scale * 1.2f);
        qcopy(point, polygon + (index * 16 + 0x10));
        switch (flags & 7) {
        case 1:
            func_L03_00339128(point, data, 0, owner, 0x7F, timer, 0xFF, scale);
            break;
        case 2:
            func_L03_00339128(point, data, 1, owner, 0x7F, timer, 0xFF, scale);
            break;
        case 4:
            point[2] += scale * 0.5f;
            {
                int n = index;
                do {
                    func_L03_00339128(point, data, n % 10 + 2, owner, 0x7F, timer, 0xFF, scale);
                    n /= 10;
                    func_00282CC0(point, point, advance);
                } while (n != 0);
            }
            break;
        }
        qcopy(previous, polygon + (index * 16 + 0x10));
    }
}
