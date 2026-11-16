#include "include_asm.h"

#include "common.h"
extern void vec_fast_helper_e(void *, unsigned long long);
extern void scale_vector(void *, void *, float);
extern void vec_copy_helper_b(void *, void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void vec_clear_128(void *);
extern void part_update_effect_records(void *);
extern void part_add_effect_record(void *, void *);
extern void gfx_draw_billboard_quad(void *, unsigned int, unsigned int, int, float, float, float);
extern float g_thruster_offset_a __attribute__((sda));
extern float g_thruster_offset_b __attribute__((sda));
typedef struct { char pad[0x34]; int frame; } Frame7B;
extern Frame7B g_scene_playback_state;
typedef struct {
 float pos[4], velocity[4];
 float angle, rotation, size; unsigned int color;
 int unknown, life, unknown2, flags, first, last, unknown3, type;
} Effect7B;

/* Spawns fire, glow and spark particles on the ship for its current scene. */
void ship_spawn_thruster_particles_pal(void *object)
{
 float pos[4], other[4], matrix[12], first[4], second[4], combined[4];
 Effect7B effect, spark;
 char *ship = object;
 unsigned long long next;
 unsigned int color;
#ifdef OPENRAC_HOSTGEN
 /* OpenRAC: as in func_002E76C0, the new records' colour and alpha now (+0x30, +0x38) are drawn once as
    the stack left them; retail's alpha byte 0 there, so that first draw changes no pixel. */
 effect.unknown = 0x001A0000;
 effect.unknown2 = 0x001C0000;
 spark.unknown = 0x001A0000;
 spark.unknown2 = 0x001C0000;
#endif
 next = *(unsigned long long *)(*(char **)(ship + 0x5c) + 0x10);
 vec_fast_helper_e(first, *(unsigned long long *)(*(char **)(ship + 0x58) + 0x10));
 vec_fast_helper_e(second, next);
 scale_vector(first, first, (1.0f - *(float *)(ship + 0x44)) * (1.0f / 32768.0f));
 scale_vector(second, second, *(float *)(ship + 0x44) * (1.0f / 32768.0f));
 vec_copy_helper_b(combined, first, second);
 quaternion_to_rotation_basis(combined, matrix);
 multiply_matrix3x3(matrix, ship + 0xc0, matrix);
 matrix_mul_vec3(pos, &g_thruster_offset_a, matrix);
 matrix_mul_vec3(other, &g_thruster_offset_b, matrix);
 FastVecAdd(pos, pos, ship + 0x10);
 FastVecAdd(other, other, ship + 0x10);
 part_update_effect_records(object);
 effect.life = math_random_int_range(95, 127);
 if (*(short *)(ship + 0xaa) == 0x128c)
  effect.color = FastTweenColor(0xff0f0f, 0xff3f3f, math_random_float_range(0.0f, 1.0f));
 else if (*(short *)(ship + 0xaa) == 0x128d)
  effect.color = FastTweenColor(0xf6fcf, 0x3fcfef, math_random_float_range(0.0f, 1.0f));
 else
  effect.color = FastTweenColor(0xf4fdf, 0x1f8fff, math_random_float_range(0.0f, 1.0f));
 effect.size = math_random_float_range(1.0f, 2.0f);
 if (*(short *)(ship + 0xaa) == 0x128c) qcopy(effect.pos, pos);
 else qcopy(effect.pos, ship + 0x10);
 if (*(short *)(ship + 0xaa) != 0x128c) {
  effect.pos[0] += math_random_float_range(-0.25f, 0.25f);
  effect.pos[1] += math_random_float_range(-0.25f, 0.25f);
  effect.pos[2] += math_random_float_range(-0.25f, 0.25f);
 }
 vec_clear_128(effect.velocity);
 effect.rotation = math_random_angle();
 effect.angle = math_random_float_range(90.0f, 180.0f) * 0.0003490659f;
 effect.first = effect.last = ((s32)(math_random_int_range(70, 90)) * 5 + 2) / 6;
 effect.type = 5;
 effect.flags = ((g_scene_playback_state.frame % 2 + 1) << 1) | 1;
 part_add_effect_record(object, &effect);
 if (*(short *)(ship + 0xaa) == 0x128c) {
  qcopy(effect.pos, other);
  part_add_effect_record(object, &effect);
  if (*(short *)(ship + 0xaa) == 0x128c) {
   if (!(g_scene_playback_state.frame & 1)) {
   spark.life = math_random_int_range(127, 255);
   spark.color = 0x3fff;
   spark.size = math_random_float_range(0.0625f, 0.125f);
   qcopy(spark.pos, ship + 0x10);
   spark.pos[0] += math_random_float_range(-1.5f, 1.5f);
   spark.pos[1] += math_random_float_range(-1.5f, 1.5f);
   spark.pos[2] += math_random_float_range(-1.5f, 1.5f);
   vec_clear_128(spark.velocity);
   spark.rotation = math_random_angle();
   spark.angle = math_random_float_range(90.0f, 180.0f) * 0.0003490659f;
   spark.first = spark.last = ((s32)(math_random_int_range(135, 160)) * 5 + 2) / 6;
   spark.type = 0;
   spark.flags = 0;
   part_add_effect_record(object, &spark);
   spark.color = 0xffffff;
   spark.size *= 0.8f;
   part_add_effect_record(object, &spark);
   }
   color = (math_random_int_range(32, 80) << 24) | 0xff1f1f;
   gfx_draw_billboard_quad(ship + 0x10, 5, color, 1, 5.0f, 1.0f, math_random_angle());
  }
 }
}
