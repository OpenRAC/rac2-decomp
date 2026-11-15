#include "common.h"

/* Two level tables read both ways: the first word of each through $gp (the _gp views), the rest
   through the assembler's absolute macro form (incomplete sda arrays). The source vector of the
   first call is its own object at 0x1B0A80, just past the 4-float table at 0x1B0A70: SN builds
   `la table+16` as lui/addiu, but retail has one $gp addiu (owner ruling 8 November 2026). */
extern unsigned int D_L00_001B0A50[] __attribute__((sda));
extern unsigned int D_L00_001B0A50_gp[] SDATA(D_L00_001B0A50);
extern float D_L00_001B0A70[] __attribute__((sda));
extern float D_L00_001B0A70_gp[] SDATA(D_L00_001B0A70);
extern float D_L00_001B0A80[] __attribute__((sda));
extern float D_L00_001B0A80_gp[] SDATA(D_L00_001B0A80);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);

/* Four particle emissions around the object, each with a colour picked between two table entries. */
void part_emit_colored_burst(char *object)
{
    float position[4];
    float *data = *(float **)(object + 0x68);

    matrix_mul_vec3(position, D_L00_001B0A80_gp, object + 0xC0);
    FastVecAdd(position, position, object + 0x10);
    {
        unsigned int color = FastTweenColor(D_L00_001B0A50_gp[0], D_L00_001B0A50[1], math_random_float_range(0.0f, 1.0f));
        float size = D_L00_001B0A70_gp[0] * data[0];
        gfx_draw_billboard_quad(position, 0x31, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(D_L00_001B0A50[2], D_L00_001B0A50[3], math_random_float_range(0.0f, 1.0f));
        float size = D_L00_001B0A70[1] * data[0];
        gfx_draw_billboard_quad(position, 0x31, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(D_L00_001B0A50[4], D_L00_001B0A50[5], math_random_float_range(0.0f, 1.0f));
        float size = D_L00_001B0A70[2] * data[0];
        gfx_draw_billboard_quad(position, 0xB, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(D_L00_001B0A50[5], D_L00_001B0A50[6], math_random_float_range(0.0f, 1.0f));
        float size = D_L00_001B0A70[3] * data[0];
        gfx_draw_billboard_quad(position, 0xB, color, 1, size, 0.0f, math_random_angle());
    }
}
