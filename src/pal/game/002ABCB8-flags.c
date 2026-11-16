#include "names.h"
/* func_PAL_002ABCB8, the PAL copy of func_002AB250: 0.03f and 0.015f become 0.036f and 0.018f (x6/5), the
   first delay is scaled to 50 Hz, and the loop is the plain count-up index loop, whose array base is set
   after the hoisted constants. */
#include "include_asm.h"

typedef int s32;

extern void FastVecAdd(float *, float *, void *);
extern int coll_scatter_points_in_shapes(void *, int, void *, void *, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern char *part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);

/* Scatters sparks at random points inside the given shapes (PAL: 50 Hz timings). */
void part_spawn_sparks_around_moby_pal(void *owner, char *offset, void *filter)
{
    float vectors[20][4];
    float position[4];
    int i;
    int result;
    int first;
    float angle;
    result = coll_scatter_points_in_shapes(owner, 20, vectors, filter, 14.0f);
    if (result == 0)
        return;
    for (i = 0; i < result; i++) {
        angle = math_random_angle();
        vec_build_spherical_offset(position, 0.036000002f, angle, math_random_angle());
        FastVecAdd(position, position, offset);
        position[2] += 0.018000001f;
        first = ((s32)math_random_int_range(20, 35) * 5 + 2) / 6;
        part_spawn_scaling(vectors[i], position, 0x7000A0FFu, 255, first, 30, math_random_int_range(40, 60), 1);
    }
}
