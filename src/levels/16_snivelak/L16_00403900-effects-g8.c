#include "include_asm.h"
#include "names.h"

extern int math_random_int_range(int, int);
extern float math_random_angle(void);

extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows_alt(void *, int, float, int, float, float, int, int, void *);
extern float g_glow_sprite_scale __attribute__((sda));
extern float g_glow_second_scale_mult __attribute__((sda));
extern int g_glow_beam_param_a __attribute__((sda));
extern int g_glow_beam_param_b __attribute__((sda));
extern int g_snivelak_spark_part_id_a __attribute__((sda));
extern int g_snivelak_spark_part_id_b __attribute__((sda));
/* Draws two glowing sprites at the object, one bigger than the other. */
void gfx_draw_two_glow_sprites(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = g_glow_sprite_scale;
    scale *= *(float *)(object + 0x2C);
    value = math_random_int_range(95, 111);
    random = math_random_angle();
    gfx_draw_beam_quads_glows_alt(object + 0x10, g_snivelak_spark_part_id_a, scale, value, random, 1.0f, g_glow_beam_param_a, 2, object);
    scale2 = g_glow_sprite_scale;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= g_glow_second_scale_mult;
    value2 = math_random_int_range(111, 127);
    random = math_random_angle();
    gfx_draw_beam_quads_glows_alt(object + 0x10, g_snivelak_spark_part_id_b, scale2, value2, random, 1.0f, g_glow_beam_param_b, 2, object);
}
