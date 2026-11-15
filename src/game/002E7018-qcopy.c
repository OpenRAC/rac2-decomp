#include "include_asm.h"
#include "common.h"

/* The ring's quads are copied with the grouped `lq`/`sq` profile, so this
 * function needs its own unit. */

typedef int TI128 __attribute__((mode(TI)));

extern int g_hero_moby_default[];
extern float IntToFloat(int);
extern float math_random_angle(void);
extern void vec_add_random_offset(float *, float);
extern void gfx_draw_billboard_quad(void *, unsigned int, unsigned int, int, float, float, float);
extern void FastVecAdd(void *, void *, void *);

/* Draws `count` copies of one quad along the segment from `from` to `to`,
 * each jittered by `radius` and turned by the engine's matrix. The mode flag
 * is the short at D_00152C20, 0x20 into the table at D_00152C00. */
/* Draws a trail of small glowing sprites along a line between two points. */
void part_draw_sprite_trail(void *src, void *matrix, int count, unsigned int colour,
                   float from, float to, float radius)
{
    TI128 quad[2];
    float step;
    int i;

    quad[0] = *(TI128 *)src;
    step = 1.0f / IntToFloat(count);
    for (i = 0; i < count; i++) {
        short *table = (short *)g_hero_moby_default;
        float f = IntToFloat(i) * step;
        float t = from + (to - from) * f;
        float angle = math_random_angle();

        quad[1] = quad[0];
        vec_add_random_offset((float *)&quad[1], radius);
        gfx_draw_billboard_quad((char *)&quad[1], table[0x10] == 2 ? 5 : 0x2E, colour, 1,
                      t, 0.0f, angle);
        FastVecAdd((char *)&quad[0], (char *)&quad[0], matrix);
    }
}

extern float ref_L00_002E8F80_00[][4];
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Six sparks from the table, each placed by the object's matrices and given a
   small random drift; `height` lifts the drift's z. */
/* Throws out six small sparks around an object, each with a bit of random drift. */
void part_spawn_object_sparks(char *object, float height)
{
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int i;

    for (i = 0; i < 6; i++) {
        from[0] = math_random_float_range(-0.016666668f, 0.016666668f);
        from[1] = math_random_float_range(-0.016666668f, 0.016666668f);
        from[2] = height + math_random_float_range(-0.004166667f, 0.004166667f);
        from[3] = 0.4f;
        qcopy(to, from);
        to[3] = 0.6f;
        qcopy(position, ref_L00_002E8F80_00[i]);
        matrix_mul_vec3(position, position, object + 0xC0);
        FastVecAdd(position, position, object + 0x10);
        part_spawn_trail(position, from, to, 0x30F0F0F0, 0x14F0F0F0, 4, 4, math_random_int_below(4) + 4, 0x17);
    }
}
