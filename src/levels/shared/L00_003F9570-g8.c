#include "common.h"

/* Two level tables read both ways: the first word of each through $gp (the _gp views), the rest
   through the assembler's absolute macro form (incomplete sda arrays). The source vector of the
   first call is its own object at 0x1B0A80, just past the 4-float table at 0x1B0A70: SN builds
   `la table+16` as lui/addiu, but retail has one $gp addiu (owner ruling 8 November 2026). */
extern unsigned int g_burst_color_pair_table[] __attribute__((sda));
extern unsigned int D_L00_001B0A50_gp[] SDATA(D_L00_001B0A50);
extern float g_burst_size_scale_table[] __attribute__((sda));
extern float D_L00_001B0A70_gp[] SDATA(D_L00_001B0A70);
extern float g_burst_float_table[] __attribute__((sda));
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
        unsigned int color = FastTweenColor(D_L00_001B0A50_gp[0], g_burst_color_pair_table[1], math_random_float_range(0.0f, 1.0f));
        float size = D_L00_001B0A70_gp[0] * data[0];
        gfx_draw_billboard_quad(position, 0x31, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(g_burst_color_pair_table[2], g_burst_color_pair_table[3], math_random_float_range(0.0f, 1.0f));
        float size = g_burst_size_scale_table[1] * data[0];
        gfx_draw_billboard_quad(position, 0x31, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(g_burst_color_pair_table[4], g_burst_color_pair_table[5], math_random_float_range(0.0f, 1.0f));
        float size = g_burst_size_scale_table[2] * data[0];
        gfx_draw_billboard_quad(position, 0xB, color, 1, size, 0.0f, math_random_angle());
    }
    {
        unsigned int color = FastTweenColor(g_burst_color_pair_table[5], g_burst_color_pair_table[6], math_random_float_range(0.0f, 1.0f));
        float size = g_burst_size_scale_table[3] * data[0];
        gfx_draw_billboard_quad(position, 0xB, color, 1, size, 0.0f, math_random_angle());
    }
}
