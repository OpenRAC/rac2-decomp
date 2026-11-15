#include "include_asm.h"
#include "common.h"

extern char g_hero_state[];
extern float vec_length_xy(char *);
extern float mat_fast_helper_a(float, float);
extern void transform_vector(void *, void *, char *);

/* Returns the angle of a vector in the current view mode space, turning it first when needed. */
float cam_get_view_space_angle(char *vec)
{
    char *heroBase = g_hero_state;
    int viewMode = *(unsigned char *)(heroBase + 8899);
    float rotated[4] __attribute__((aligned(16)));

    if (viewMode == 0)
        return mat_fast_helper_a(*(float *)(vec + 8), vec_length_xy(vec));
    if (viewMode < 0)
        return 0.0f;
    if (viewMode >= 3)
        return 0.0f;
    qcopy(rotated, vec);
    transform_vector(rotated, rotated, heroBase + 64);
    return mat_fast_helper_a(rotated[2], vec_length_xy((char *)rotated));
}
