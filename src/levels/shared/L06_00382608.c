#include "common.h"

extern void STUB_printf(const char *, ...);
extern const char g_str_l06_debug_message[];
extern char *g_path_list[];
extern float g_aim_direction[];
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern unsigned char *effect_create_timed(void *, void *, int, int, float, unsigned char, short, unsigned char);

/* Walks along a stored path and puts a marker at each point, or the point number as digits. */
void DrawPath(void *data, int path, int owner, int flags, int stride, float scale)
{
    float previous[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float advance[4] __attribute__((aligned(16)));
    char *polygon;
    int timer;
    int index;
    int one;

    if (path == -1) {
        STUB_printf(g_str_l06_debug_message);
        return;
    }
    polygon = g_path_list[path];
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
            vec_scale_to_length(advance, g_aim_direction, scale * 1.2f);
            qcopy(point, polygon + (index * 16 + 0x10));
            switch (flags & 7) {
            case 1:
                effect_create_timed(point, data, 0, owner, scale, 0x7F, timer, 0xFF);
                break;
            case 2:
                effect_create_timed(point, data, one, owner, scale, 0x7F, timer, 0xFF);
                break;
            case 4:
                point[2] += scale * 0.5f;
                {
                    int n = index;
                    do {
                        effect_create_timed(point, data, n % 10 + 2, owner, scale, 0x7F, timer, 0xFF);
                        FastVecAdd(point, point, advance);
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
