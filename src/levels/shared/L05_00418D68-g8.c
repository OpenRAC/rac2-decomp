#include "common.h"

extern float IntToFloat(int);
extern float math_random_angle(void);
extern void vec_add_random_offset(void *, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);
extern int D_L05_001B0FBC __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);

typedef int TI128 __attribute__((mode(TI)));

/* Places a row of sprites along a direction, changing size from the first one to the last. */
void part_spawn_sprite_line(void *position, void *direction, int count, int color, float sizeStart, float sizeEnd, float pushOut)
{
    TI128 points[2];
    float step;
    float progress;
    float spin;
    float scale;
    float lastSize;
    float firstSize;
    float pushDistance;
    int i;

    firstSize = sizeStart;
    lastSize = sizeEnd;
    pushDistance = pushOut;
    qcopy(&points[0], position);
    step = 1.0f / IntToFloat(count);
    for (i = 0; i < count; i++) {
        progress = IntToFloat(i) * step;
        scale = firstSize + (lastSize - firstSize) * progress;
        spin = math_random_angle();
        qcopy(&points[1], &points[0]);
        vec_add_random_offset(&points[1], pushDistance);
        gfx_draw_billboard_quad(&points[1], D_L05_001B0FBC, color, 1, scale, 0.0f, spin);
        FastVecAdd(&points[0], &points[0], direction);
    }
}
