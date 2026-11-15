#include "include_asm.h"
#include "names.h"

extern char *g_route_polygons[];
extern void vec_clear_128(void *);
extern float vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);

/* Prepares the actor's path (built with -g: the line labels pad the two divisions with nops).
   The table entry the state names holds a count and 16-byte points from +0x10: the fourth float
   of each point but the last becomes the distance to the next one, the points are summed and
   scaled by 1/(count - 1) into the centre at +0x20, the largest func_00282E48 distance from the
   centre plus the margin at +4 becomes the radius at +0x2C, and two ratios of the entry's float
   at +0x1C become the words at +0x3C and +0x40. The guarded do-while with a second pointer walked beside
   the point index is the loop shape retail has. */
/* Works out the middle and size of a path of points, plus two timing counts, when the actor is set up. */
void path_init_bounds(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *entry = g_route_polygons[*(int *)state];
    float pointSum[4];
    int i;
    int j;

    vec_clear_128(pointSum);
    i = 0;
    if (*(int *)entry - 1 > 0) {
        char *nextPoint = entry + 0x20;

        do {
            char *point = entry + i * 16 + 0x10;

            *(float *)(point + 0xC) = vec_distance_xy(point, nextPoint);
            FastVecAdd(pointSum, pointSum, point);
            nextPoint += 0x10;
            i++;
        } while (i < *(int *)entry - 1);
    }
    FastVecScale(state + 0x20, pointSum, 1.0f / (float)(*(int *)entry - 1));
    *(float *)(state + 0x2C) = 0.0f;
    for (j = 0; j < *(int *)entry; j++) {
        float distance = fast_vec_dist(entry + j * 16 + 0x10, state + 0x20);

        if (*(float *)(state + 0x2C) < distance)
            *(float *)(state + 0x2C) = distance;
    }
    *(float *)(state + 0x2C) += *(float *)(state + 4);
    *(int *)(state + 0x3C) = FloatToInt(*(float *)(state + 8) / *(float *)(entry + 0x1C));
    *(int *)(state + 0x40) = FloatToInt(*(float *)(state + 4) / *(float *)(entry + 0x1C));
}
