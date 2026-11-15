#include "common.h"
extern void vec_fast_helper_e(void *, unsigned long long);
extern void scale_vector(void *, void *, float);
extern void vec_copy_helper_b(void *, void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void vec_clear_128(void *);
extern void part_draw_sprite_trail(void *, void *, int, float, float, float, unsigned int);
extern void part_update_effect_records(void *);
extern void part_add_effect_record(void *, void *);
extern float D_001AC090 __attribute__((sda));
extern float D_001B2150[4];
extern char g_scene_playback_state[];

typedef struct {
 float pos[4], velocity[4];
 float angle, rotation, size; unsigned int color;
 int unknown, life, unknown2, flags, first, last, unknown3, type;
} Effect76;

/* Draws one engine flame of the ship and adds a smoky puff behind it. */
void ship_spawn_engine_flame(void *object, int index, int alternate)
{
 float pos[4], step[4], matrix[12], first[4], second[4], combined[4];
 Effect76 effect;
 char *o = object;
 unsigned long long next;
 float strength, count, radius, small, start, end, inner, outer, width;
 float *entry;
 int count1, count2, low, high;
 unsigned int color1, color2;
#ifdef OPENRAC_HOSTGEN
 /* OpenRAC: the new record's colour and alpha now (+0x30, +0x38) are never set here: it is drawn once
    with what the stack held, before func_002ED368 sets them. Retail's stack held 0x001A0000 and 0x001C0000
    there at every spawn of a New Game flight, an alpha byte of 0, so that draw changes no pixel; the host's
    held float bits, a puff of alpha up to 0xFD at the engine every tick. */
 effect.unknown = 0x001A0000;
 effect.unknown2 = 0x001C0000;
#endif
 next = *(unsigned long long *)(*(char **)(o + 0x5c) + 0x10);
 vec_fast_helper_e(first, *(unsigned long long *)(*(char **)(o + 0x58) + 0x10));
 vec_fast_helper_e(second, next);
 scale_vector(first, first, (1.0f - *(float *)(o + 0x44)) * (1.0f / 32768.0f));
 scale_vector(second, second, *(float *)(o + 0x44) * (1.0f / 32768.0f));
 vec_copy_helper_b(combined, first, second);
 quaternion_to_rotation_basis(combined, matrix);
 multiply_matrix3x3(matrix, o + 0xc0, matrix);
 entry = &D_001AC090 + index * 4;
 matrix_mul_vec3(pos, entry, matrix);
 FastVecAdd(pos, pos, o + 0x10);
 strength = (float)*(unsigned char *)(o + 0x95) * (entry[3] * (1.0f / 128.0f));
 count = strength * 5.0f;
 radius = strength * 0.06f + 0.06f;
 small = strength * 0.04f + 0.04f;
 count1 = FloatToInt(count + 25.0f);
 count2 = FloatToInt(count + 15.0f);
 start = strength * 0.375f + 0.375f;
 end = strength * 0.09999999403953552f + 0.09999999403953552f;
 inner = strength * 0.02499999850988388f + 0.02499999850988388f;
 outer = strength * 0.024999991059303284f + 0.175f;
 width = strength * 0.07499999552965164f + 0.07499999552965164f;
 color1 = FastTweenColor(0x40204080, 0x40205080, strength);
 color2 = FastTweenColor(-1, -1, strength);
 FastVecScale(step, matrix, -radius);
 part_draw_sprite_trail(pos, step, count1, start, end, width, color1);
 if (index == 0) {
  FastVecScale(step, matrix, -small);
  part_draw_sprite_trail(pos, step, count2, outer, inner, 0.07499999552965164f, color2);
 }
 part_update_effect_records(object);
 effect.color = FastTweenColor(0x2f7f, 0x7f7f, math_random_float_range(0.0f, 1.0f));
 if (alternate) { low = 24; high = 40; }
 else { low = 31; high = 63; }
 effect.life = math_random_int_range(low, high);
 effect.size = math_random_float_range(1.0f, 2.0f);
 qcopy(effect.pos, pos);
 effect.pos[0] += math_random_float_range(-0.025f, 0.025f);
 effect.pos[1] += math_random_float_range(-0.025f, 0.025f);
 effect.pos[2] += math_random_float_range(-0.025f, 0.025f);
 vec_clear_128(effect.velocity);
 qcopy(effect.velocity, D_001B2150);
 effect.rotation = math_random_angle();
 effect.angle = math_random_float_range(90.0f, 180.0f) * 0.0002908882452175021f;
 effect.first = effect.last = math_random_int_range(70, 90);
 effect.type = 5;
 effect.flags = 1;
 if (!alternate) effect.flags = ((*(int *)(g_scene_playback_state + 0x34) % 2 + 1) << 1) | 1;
 part_add_effect_record(object, &effect);
}
