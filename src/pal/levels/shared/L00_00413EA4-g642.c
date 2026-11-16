#include "include_asm.h"

#include "common.h"
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int func_PAL_L00_00415648(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);
extern float g_charge_glow_size_start __attribute__((sda));
extern float g_charge_glow_size_end __attribute__((sda));
extern unsigned int g_charge_glow_color __attribute__((sda));
extern float g_charge_glow_offset_table[4][4] __attribute__((sda));
extern int g_weapon_slot __attribute__((nosda));
extern int g_item_ammo_counts[];

/* Draws the object's glow: the level at +0x1A of its state (out of 90) blends the size
   between two tuning values, four times it (at most 96) plus a pulse from the phase at
   +0x20 gives the alpha, and the phase advances by 8 degrees. As many of the four
   offset vectors as the ammo of the item selected by D_0018B068 (capped by the grade from
   func_PAL_L00_00415648) are transformed by the object, and each draws two sprites.
   The global loads pass the float phase store only under -fstrict-aliasing, and
   D_0018B068, far from $gp, is split into %hi/%lo by nosda as retail does. */
void func_PAL_L00_00415498(char *object)
{
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    float fraction, size;
    int alpha, count, n, i;
    unsigned int color;
    fraction = IntToFloat(*(short *)(state + 0x1a));
    fraction /= IntToFloat(75);
    if (fraction > 1.0f) fraction = 1.0f;
    size = g_charge_glow_size_start + (g_charge_glow_size_end - g_charge_glow_size_start) * fraction;
    alpha = *(short *)(state + 0x1a) << 2;
    if (alpha >= 97) alpha = 96;
    alpha = (unsigned int)(FloatToInt(math_fast_sin_or_cos_b(*(float *)(state + 0x20)) * 32.0f) + alpha) << 24;
    *(float *)(state + 0x20) = FastAddRotations(*(float *)(state + 0x20), 0.139626354f);
    color = alpha | g_charge_glow_color;
    count = g_item_ammo_counts[g_weapon_slot];
    n = func_PAL_L00_00415648(object);
    if (n < count) count = n;
    for (i = 0; i < count; i++) {
        matrix_mul_vec3(position, g_charge_glow_offset_table[i], object + 0xc0);
        FastVecAdd(position, object + 0x10, position);
        gfx_draw_billboard_quad(position, 11, color, 1, size, 0.0f, 0.0f);
        gfx_draw_billboard_quad(position, 11, 0x80808080, 1, size * 0.3f, 0.0f, 0.0f);
    }
}
