#include "common.h"

typedef struct { char reserved00[0x30]; float point[4]; char reserved40[0x40]; } HeadingReference;
extern HeadingReference *D_L20_001B308C;
extern struct { char reserved00[0x80]; float position[4]; } g_hero_state;
extern float D_L20_001B2098 __attribute__((sda));
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);

/* Works out a spot beside a path point, to the side of the direction toward the hero, for the enemy to walk to. */
void yeedil_boss_compute_side_step(char *object, float *output)
{
    char *state = *(char **)(object + 0x68);
    float towardHero, heading;
    unsigned int index;
    float y;
    HeadingReference *reference;
    towardHero = mat_fast_helper_a(g_hero_state.position[0] - *(float *)(object + 0x10),
        g_hero_state.position[1] - *(float *)(object + 0x14));
    index = *(unsigned int *)(state + 0x230);
    heading = mat_fast_helper_a(D_L20_001B308C[index].point[0] - *(float *)(object + 0x10),
        D_L20_001B308C[index].point[1] - *(float *)(object + 0x14));
    if (0.0f < fast_subtract_rotations(towardHero, heading))
        heading = fast_subtract_rotations(heading, 1.5707964f);
    else
        heading = FastAddRotations(heading, 1.5707964f);
    output[0] = math_fast_sin_or_cos_a(heading) * D_L20_001B2098;
    y = math_fast_sin_or_cos_b(heading) * D_L20_001B2098;
    reference = D_L20_001B308C;
    *(int *)&output[2] = 0;
    output[1] = y;
    FastVecAdd(output, output, reference[*(unsigned int *)(state + 0x230)].point);
}
