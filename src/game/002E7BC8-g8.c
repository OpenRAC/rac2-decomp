#include "common.h"
extern void func_00283130(void *, unsigned long long);
extern void func_00282D60(void *, void *, float);
extern void func_00282CA8(void *, void *, void *);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_00282C88(void *);
extern void func_002ED368(void *);
extern void func_002ED2B8(void *, void *);
extern void func_00281EB8(void *, unsigned int, unsigned int, int, float, float, float);
extern float D_001AC130 __attribute__((sda));
extern float D_001AC140 __attribute__((sda));
typedef struct { char pad[0x34]; int frame; } Frame7B;
extern Frame7B D_001B8840;
typedef struct {
 float pos[4], velocity[4];
 float angle, rotation, size; unsigned int color;
 int unknown, life, unknown2, flags, first, last, unknown3, type;
} Effect7B;
/* Spawns fire, glow and spark particles on the ship for its current scene. */
void func_002E7BC8(void *object)
{
 float pos[4], other[4], matrix[12], first[4], second[4], combined[4];
 Effect7B effect, spark;
 char *o = object;
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
 next = *(unsigned long long *)(*(char **)(o + 0x5c) + 0x10);
 FastVectorHelperE(first, *(unsigned long long *)(*(char **)(o + 0x58) + 0x10));
 FastVectorHelperE(second, next);
 scale_vector(first, first, (1.0f - *(float *)(o + 0x44)) * (1.0f / 32768.0f));
 scale_vector(second, second, *(float *)(o + 0x44) * (1.0f / 32768.0f));
 VectorCopyHelperB(combined, first, second);
 quaternion_to_rotation_basis(combined, matrix);
 multiply_matrix3x3(matrix, o + 0xc0, matrix);
 matrix_mul_vec3(pos, &D_001AC130, matrix);
 matrix_mul_vec3(other, &D_001AC140, matrix);
 FastVecAdd(pos, pos, o + 0x10);
 FastVecAdd(other, other, o + 0x10);
 UpdateEffectRecords(object);
 effect.life = RandomIntRange(95, 127);
 if (*(short *)(o + 0xaa) == 0x128c /* moby class 4748 */)
  effect.color = FastTweenColor(0xff0f0f, 0xff3f3f, RandomFloatRange(0.0f, 1.0f));
 else if (*(short *)(o + 0xaa) == 0x128d /* moby class 4749 */)
  effect.color = FastTweenColor(0xf6fcf, 0x3fcfef, RandomFloatRange(0.0f, 1.0f));
 else
  effect.color = FastTweenColor(0xf4fdf, 0x1f8fff, RandomFloatRange(0.0f, 1.0f));
 effect.size = RandomFloatRange(1.0f, 2.0f);
 if (*(short *)(o + 0xaa) == 0x128c /* moby class 4748 */) qcopy(effect.pos, pos);
 else qcopy(effect.pos, o + 0x10);
 if (*(short *)(o + 0xaa) != 0x128c /* moby class 4748 */) {
  effect.pos[0] += RandomFloatRange(-0.25f, 0.25f);
  effect.pos[1] += RandomFloatRange(-0.25f, 0.25f);
  effect.pos[2] += RandomFloatRange(-0.25f, 0.25f);
 }
 ClearVector128(effect.velocity);
 effect.rotation = RandomAngle();
 effect.angle = RandomFloatRange(90.0f, 180.0f) * 0.0002908882452175021f;
 effect.first = effect.last = RandomIntRange(70, 90);
 effect.type = 5;
 effect.flags = ((gScenePlaybackState.frame % 2 + 1) << 1) | 1;
 AddEffectRecord(object, &effect);
 if (*(short *)(o + 0xaa) == 0x128c /* moby class 4748 */) {
  qcopy(effect.pos, other);
  AddEffectRecord(object, &effect);
  if (*(short *)(o + 0xaa) == 0x128c /* moby class 4748 */) {
   if (!(gScenePlaybackState.frame & 1)) {
   spark.life = RandomIntRange(127, 255);
   spark.color = 0x3fff;
   spark.size = RandomFloatRange(0.0625f, 0.125f);
   qcopy(spark.pos, o + 0x10);
   spark.pos[0] += RandomFloatRange(-1.5f, 1.5f);
   spark.pos[1] += RandomFloatRange(-1.5f, 1.5f);
   spark.pos[2] += RandomFloatRange(-1.5f, 1.5f);
   ClearVector128(spark.velocity);
   spark.rotation = RandomAngle();
   spark.angle = RandomFloatRange(90.0f, 180.0f) * 0.0002908882452175021f;
   spark.first = spark.last = RandomIntRange(135, 160);
   spark.type = 0;
   spark.flags = 0;
   AddEffectRecord(object, &spark);
   spark.color = 0xffffff;
   spark.size *= 0.8f;
   AddEffectRecord(object, &spark);
   }
   color = (RandomIntRange(32, 80) << 24) | 0xff1f1f;
   DrawBillboardQuad_00281EB8(o + 0x10, 5, color, 1, 5.0f, 1.0f, RandomAngle());
  }
 }
}
