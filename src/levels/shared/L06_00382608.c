#include "common.h"

extern void func_0026FEB8(const char *, ...);
extern const char D_L06_001AA660[];
extern char *D_L06_001FE500[];
extern float D_L06_001B9A90[];
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern unsigned char *func_L03_00339128(void *, void *, int, int, float, unsigned char, short, unsigned char);

void func_L06_00382608(void *data, int path, int owner, int flags, int stride, float scale)
{
    float previous[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float advance[4] __attribute__((aligned(16)));
    char *polygon;
    int timer;
    int index;
    int one;

    if (path == -1) {
        func_0026FEB8(D_L06_001AA660);
        return;
    }
    polygon = D_L06_001FE500[path];
    timer = (flags & 0x40) ? -1 : 2;
    qcopy(previous, polygon + 0x10);
    index = 0;
    if (index < *(int *)polygon) {
        /* The dead null test (polygon was already read above) keeps the outer
         * loop unrotated at jump1; delete_null_pointer_checks removes it before
         * loop.c, which then hoists only timer << 16, as retail's loop shows.
         * Allowed by owner ruling (2026-11-09). */
        while (index < (polygon ? *(int *)polygon : 0)) {
            /* cse reuses this 1 for the case-1 compare, kept in $s1 across the call. */
            one = 1;
            func_00282F20(advance, D_L06_001B9A90, scale * 1.2f);
            qcopy(point, polygon + (index * 16 + 0x10));
            switch (flags & 7) {
            case 1:
                func_L03_00339128(point, data, 0, owner, scale, 0x7F, timer, 0xFF);
                break;
            case 2:
                func_L03_00339128(point, data, one, owner, scale, 0x7F, timer, 0xFF);
                break;
            case 4:
                point[2] += scale * 0.5f;
                {
                    int n = index;
                    do {
                        func_L03_00339128(point, data, n % 10 + 2, owner, scale, 0x7F, timer, 0xFF);
                        func_00282CC0(point, point, advance);
                        n /= 10;
                    } while (n != 0);
                }
                break;
            }
            qcopy(previous, polygon + (index * 16 + 0x10));
            index += stride;
        }
    }
}
