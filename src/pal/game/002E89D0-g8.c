#include "include_asm.h"

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

void func_PAL_002E89D0(void *object)
{
 float pos[4], other[4], matrix[12], first[4], second[4], combined[4];
 Effect7B effect, spark;
 char *o = object;
 unsigned long long next;
 unsigned int color;
 next = *(unsigned long long *)(*(char **)(o + 0x5c) + 0x10);
 func_00283130(first, *(unsigned long long *)(*(char **)(o + 0x58) + 0x10));
 func_00283130(second, next);
 func_00282D60(first, first, (1.0f - *(float *)(o + 0x44)) * (1.0f / 32768.0f));
 func_00282D60(second, second, *(float *)(o + 0x44) * (1.0f / 32768.0f));
 func_00282CA8(combined, first, second);
 func_00283958(combined, matrix);
 func_00283738(matrix, o + 0xc0, matrix);
 func_00283098(pos, &D_001AC130, matrix);
 func_00283098(other, &D_001AC140, matrix);
 func_00282CC0(pos, pos, o + 0x10);
 func_00282CC0(other, other, o + 0x10);
 func_002ED368(object);
 effect.life = func_002A7820(95, 127);
 if (*(short *)(o + 0xaa) == 0x128c)
  effect.color = func_00283D38(0xff0f0f, 0xff3f3f, func_002A7878(0.0f, 1.0f));
 else if (*(short *)(o + 0xaa) == 0x128d)
  effect.color = func_00283D38(0xf6fcf, 0x3fcfef, func_002A7878(0.0f, 1.0f));
 else
  effect.color = func_00283D38(0xf4fdf, 0x1f8fff, func_002A7878(0.0f, 1.0f));
 effect.size = func_002A7878(1.0f, 2.0f);
 if (*(short *)(o + 0xaa) == 0x128c) qcopy(effect.pos, pos);
 else qcopy(effect.pos, o + 0x10);
 if (*(short *)(o + 0xaa) != 0x128c) {
  effect.pos[0] += func_002A7878(-0.25f, 0.25f);
  effect.pos[1] += func_002A7878(-0.25f, 0.25f);
  effect.pos[2] += func_002A7878(-0.25f, 0.25f);
 }
 func_00282C88(effect.velocity);
 effect.rotation = func_002A7940();
 effect.angle = func_002A7878(90.0f, 180.0f) * 0.0003490659f;
 effect.first = effect.last = ((s32)(func_002A7820(70, 90)) * 5 + 2) / 6;
 effect.type = 5;
 effect.flags = ((D_001B8840.frame % 2 + 1) << 1) | 1;
 func_002ED2B8(object, &effect);
 if (*(short *)(o + 0xaa) == 0x128c) {
  qcopy(effect.pos, other);
  func_002ED2B8(object, &effect);
  if (*(short *)(o + 0xaa) == 0x128c) {
   if (!(D_001B8840.frame & 1)) {
   spark.life = func_002A7820(127, 255);
   spark.color = 0x3fff;
   spark.size = func_002A7878(0.0625f, 0.125f);
   qcopy(spark.pos, o + 0x10);
   spark.pos[0] += func_002A7878(-1.5f, 1.5f);
   spark.pos[1] += func_002A7878(-1.5f, 1.5f);
   spark.pos[2] += func_002A7878(-1.5f, 1.5f);
   func_00282C88(spark.velocity);
   spark.rotation = func_002A7940();
   spark.angle = func_002A7878(90.0f, 180.0f) * 0.0003490659f;
   spark.first = spark.last = ((s32)(func_002A7820(135, 160)) * 5 + 2) / 6;
   spark.type = 0;
   spark.flags = 0;
   func_002ED2B8(object, &spark);
   spark.color = 0xffffff;
   spark.size *= 0.8f;
   func_002ED2B8(object, &spark);
   }
   color = (func_002A7820(32, 80) << 24) | 0xff1f1f;
   func_00281EB8(o + 0x10, 5, color, 1, 5.0f, 1.0f, func_002A7940());
  }
 }
}
