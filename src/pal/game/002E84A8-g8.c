#include "include_asm.h"

#include "common.h"
extern void func_00283130(void *, unsigned long long);
extern void func_00282D60(void *, void *, float);
extern void func_00282CA8(void *, void *, void *);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_00282C88(void *);
extern void func_002E7570(void *, void *, int, float, float, float, unsigned int);
extern void func_002ED368(void *);
extern void func_002ED2B8(void *, void *);
extern float D_001AC090 __attribute__((sda));
extern float D_001B2150[4];
extern char D_001B8840[];
typedef struct {
 float pos[4], velocity[4];
 float angle, rotation, size; unsigned int color;
 int unknown, life, unknown2, flags, first, last, unknown3, type;
} Effect76;

void func_PAL_002E84A8(void *object, int index, int alternate)
{
 float pos[4], step[4], matrix[12], first[4], second[4], combined[4];
 Effect76 effect;
 char *o = object;
 unsigned long long next;
 float strength, count, radius, small, start, end, inner, outer, width;
 float *entry;
 int count1, count2, low, high;
 unsigned int color1, color2;
 next = *(unsigned long long *)(*(char **)(o + 0x5c) + 0x10);
 func_00283130(first, *(unsigned long long *)(*(char **)(o + 0x58) + 0x10));
 func_00283130(second, next);
 func_00282D60(first, first, (1.0f - *(float *)(o + 0x44)) * (1.0f / 32768.0f));
 func_00282D60(second, second, *(float *)(o + 0x44) * (1.0f / 32768.0f));
 func_00282CA8(combined, first, second);
 func_00283958(combined, matrix);
 func_00283738(matrix, o + 0xc0, matrix);
 entry = &D_001AC090 + index * 4;
 func_00283098(pos, entry, matrix);
 func_00282CC0(pos, pos, o + 0x10);
 strength = (float)*(unsigned char *)(o + 0x95) * (entry[3] * (1.0f / 128.0f));
 count = strength * 5.0f;
 radius = strength * 0.06f + 0.06f;
 small = strength * 0.04f + 0.04f;
 count1 = func_00283CF0(count + 25.0f);
 count2 = func_00283CF0(count + 15.0f);
 start = strength * 0.375f + 0.375f;
 end = strength * 0.09999999403953552f + 0.09999999403953552f;
 inner = strength * 0.02499999850988388f + 0.02499999850988388f;
 outer = strength * 0.024999991059303284f + 0.175f;
 width = strength * 0.07499999552965164f + 0.07499999552965164f;
 color1 = func_00283D38(0x40204080, 0x40205080, strength);
 color2 = func_00283D38(-1, -1, strength);
 func_00282D30(step, matrix, -radius);
 func_002E7570(pos, step, count1, start, end, width, color1);
 if (index == 0) {
  func_00282D30(step, matrix, -small);
  func_002E7570(pos, step, count2, outer, inner, 0.07499999552965164f, color2);
 }
 func_002ED368(object);
 effect.color = func_00283D38(0x2f7f, 0x7f7f, func_002A7878(0.0f, 1.0f));
 if (alternate) { low = 24; high = 40; }
 else { low = 31; high = 63; }
 effect.life = func_002A7820(low, high);
 effect.size = func_002A7878(1.0f, 2.0f);
 qcopy(effect.pos, pos);
 effect.pos[0] += func_002A7878(-0.025f, 0.025f);
 effect.pos[1] += func_002A7878(-0.025f, 0.025f);
 effect.pos[2] += func_002A7878(-0.025f, 0.025f);
 func_00282C88(effect.velocity);
 qcopy(effect.velocity, D_001B2150);
 effect.rotation = func_002A7940();
 effect.angle = func_002A7878(90.0f, 180.0f) * 0.0003490659f;
 effect.first = effect.last = ((s32)(func_002A7820(70, 90)) * 5 + 2) / 6;
 effect.type = 5;
 effect.flags = 1;
 if (!alternate) effect.flags = ((*(int *)(D_001B8840 + 0x34) % 2 + 1) << 1) | 1;
 func_002ED2B8(object, &effect);
}
