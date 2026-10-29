/* Complete C near miss; not linked and no matching credit.
 * Game -O2 -G0 -ffunction-sections -fno-rerun-loop-opt: 588/584 bytes.
 * USA v1.01: 0/2 places. Default profile is 600 bytes with an extra saved FPR;
 * disabling the second loop pass retains the retail in-loop scale constant,
 * but the cached mode and vector pointer still extend the frame by 16 bytes.
 * Eight trials include three identical source/edge-control forms; strength
 * reduction control ties and broad GCSE suppression only reaches 596 bytes.
 * All vector locals hold four floats. 82F20 reads/writes 16 bytes; the real
 * marker constructor returns u8* and copies the complete position quadword.
 * Reopen with grounded loop/flag lifetime evidence, never a fake dependency.
 */
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
    int next;
    int offset;
    int base;

    if (path == -1) {
        func_0026FEB8(D_L06_001AA660);
        return;
    }
    polygon = D_L06_001FE500[path];
    timer = (flags & 0x40) ? -1 : 2;
    /* Retain the previous-vertex snapshot present in the retail helper calls. */
    qcopy(previous, polygon + 0x10);
    for (index = 0; index < *(int *)polygon; index = next) {
        func_00282F20(advance, D_L06_001B9A90, scale * 1.2f);
        offset = index << 4;
        qcopy(point, polygon + (offset + 0x10));
        next = index + stride;
        switch (flags & 7) {
        case 1:
            func_L03_00339128(point, data, 0, owner, 0x7F, timer, 0xFF, scale);
            break;
        case 2:
            func_L03_00339128(point, data, 1, owner, 0x7F, timer, 0xFF, scale);
            break;
        case 4:
            point[2] += scale * 0.5f;
            base = 10;
            do {
                int digit = index % base;
                index /= base;
                func_L03_00339128(point, data, digit + 2, owner, 0x7F, timer, 0xFF, scale);
                func_00282CC0(point, point, advance);
            } while (index != 0);
            break;
        }
        qcopy(previous, polygon + (offset + 0x10));
    }
}
