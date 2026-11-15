#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern f32 func_00282E48(void *, void *);

/* Count followed by aligned, variable-length 16-byte points. */
struct PointListPrefix { int count; };

int func_L02_00348420(TI128 *position, struct PointListPrefix *list) {
    TI128 point;
    int i, nearest = -1;
    f32 distance, minimum = 9999999.0f;
    point = *position;
    position = &point;
    if (!list)
        return -1;
    for (i = 0; i < list->count; i++) {
        distance = fast_vec_dist(position, (TI128 *)((u8 *)list + 0x10) + i);
        if (distance < minimum) {
            minimum = distance;
            nearest = i;
        }
    }
    return nearest;
}
