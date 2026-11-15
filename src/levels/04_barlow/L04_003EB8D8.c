#include "common.h"
extern void func_003317E8(void *);
extern int func_00342228(void *, int);
extern char D_00189EA0[];
extern unsigned char D_00188660[];
extern float func_0030EFA8(void *, void *);
extern void func_00282CC0(void *, void *, void *);
typedef struct EntityEntry { char bytes[256]; } EntityEntry;
extern EntityEntry *D_L04_001B24DC MACRO_ADDR;
extern char *D_L04_001FE340[];
extern float func_00283248(float, float);
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern int func_002B38B8(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002B50E0(void *, void *, float);
extern void func_002A7CA0(void *, float, float, float, float, void *);
extern void func_L01_00321178(void *, void *);
extern void func_002B6228(void *, void *, int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L04_003EC140(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002A77E0(int);
extern char *func_002BDCE8(void *, float, float, float, int, void *, float, unsigned int, int);
extern int func_00283CF0(float);
typedef struct Motion {
 float f50, f54, f58, f5c, f60;
 int i64;
 float f68;
 int i6c;
 float f70, f74, f78;
 int i7c;
 float f80;
} Motion;
typedef struct State { char pad[0x50]; Motion motion; } State;
void func_L04_003EB8D8(char *obj)
{
 char *state = *(char **)(obj + 0x68);
 float oldpos[4], delta[4], oldrot[4], temp[4], temp2[4], velocity[4], pos[4];
 char *entry;
 char *particle;
 char *middle;
 char *second;
 int angle;
 qcopy(oldpos, obj + 0x10);
 qcopy(oldrot, obj + 0xF0);
 entry = (char *)&D_L04_001B24DC[*(int *)(state + 0x180)];
 switch (*(unsigned char *)(obj + 0x20)) {
 case 0: {
  *(char **)(state + 0x18) = state + 0x50;
  if (*(int *)(state + 0x190) == -1) {func_003317E8(obj); return;}
  ((State *)state)->motion.f50 = 0.05f;
  ((State *)state)->motion.f54 = 0.5f;
  ((State *)state)->motion.f58 = 100.0f;
  ((State *)state)->motion.f5c = 100.0f;
  ((State *)state)->motion.f60 = 1.6580629348754883f;
  ((State *)state)->motion.f80 = 6.283185958862305f;
  ((State *)state)->motion.f70 = (*(float *)(state + 0x188) + *(float *)(state + 0x188)) * 0.00027777778450399637f;
  ((State *)state)->motion.f78 = *(float *)(state + 0x188) * (1.0f / 60.0f);
  ((State *)state)->motion.f68 = 0.0001939255016623065f;
  *(int *)(state + 0x1DC) = -1;
  ((State *)state)->motion.i7c = 0;
  ((State *)state)->motion.i64 = 0;
  ((State *)state)->motion.i6c = 0;
  *(float *)(obj + 0xF8) = func_00283248(*(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14));
  *(float *)(state + 0x1A8) = func_002A7940();
  *(float *)(state + 0x1AC) = func_002A7940();
  *(float *)(state + 0x1C0) = func_002A7940();
  qcopy(state + 0x1B0, obj + 0x10);
  if (*(int *)(state + 0x180) != -1) func_002A7750(obj, 3, -1);
  else func_002A7750(obj, 1, -1);
  break;
 }
 case 2:
  if (func_002B38B8(entry)) {PlayMobySound(1, 0, obj); func_002A7750(obj, 6, -1);}
  else {float heading = func_00283248(*(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14)); func_002B50E0(obj, obj + 0x10, heading);}
  break;
 case 4:
  if (func_002B38B8(entry)) {PlayMobySound(1, 0, obj); func_002A7750(obj, 5, -1);}
  else if (func_00342228(D_00189EA0, *(int *)(state + 0x194))) func_002A7750(obj, 5, -1);
  else {float heading = func_00283248(*(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x10) - *(float *)(obj + 0x10), *(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x14) - *(float *)(obj + 0x14)); MobySpringTurn(obj, heading, 0.0011635529808700085f, 0.0011635529808700085f, 0.10471977293491364f, state + 0x18C);}
  break;
 case 3:
  if (func_002B38B8(entry)) {PlayMobySound(1, 0, obj); func_002A7750(obj, 6, -1);}
  else if (func_00342228(D_00189EA0, *(int *)(state + 0x190))) func_002A7750(obj, 6, -1);
  else {float heading = func_00283248(*(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(D_L04_001FE340[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14)); MobySpringTurn(obj, heading, 0.0011635529808700085f, 0.0011635529808700085f, 0.10471977293491364f, state + 0x18C);}
  break;
 case 6:
  qcopy(temp, entry + 0x10);
  if (func_0030EFA8(entry + 0x10, D_00189EA0) < 2.0f && *(char **)(D_00189EA0 + 0x2BC) != obj) break;
  qcopy(obj + 0x10, state + 0x1B0);
  func_L01_00321178(obj, D_L04_001FE340[*(int *)(state + 0x184)] + 0x20);
  qcopy(state + 0x1B0, obj + 0x10);
  if (func_0030EFA8(obj + 0x10, D_L04_001FE340[*(int *)(state + 0x184)] + 0x20) <= 0.5f) {
   func_002A7750(obj, 4, -1);
   func_002B6228(obj, D_L04_001FE340[*(int *)(state + 0x184)], 0, 1);
  }
  break;
 case 5:
  qcopy(temp, entry + 0x10);
  if (func_0030EFA8(entry + 0x10, D_00189EA0) < 2.0f && *(char **)(D_00189EA0 + 0x2BC) != obj) break;
  qcopy(obj + 0x10, state + 0x1B0);
  func_L01_00321178(obj, D_L04_001FE340[*(int *)(state + 0x184)] + 0x10);
  qcopy(state + 0x1B0, obj + 0x10);
  if (func_0030EFA8(obj + 0x10, D_L04_001FE340[*(int *)(state + 0x184)] + 0x10) <= 0.5f) {
   func_002A7750(obj, 3, -1);
   PlayMobySound(1, 0, obj);
   func_L00_003294F0(entry, 0);
   func_002B6228(obj, D_L04_001FE340[*(int *)(state + 0x184)], 1, 0);
  }
  break;
 }
 func_L04_003EC140(obj);
 {
  char *sound = (char *)D_00188660 + *(int *)(state + 0x1DC) * 112;
  if (*(char **)(sound + 0x88) != obj || !*(unsigned char *)(sound + 0x74)) *(int *)(state + 0x1DC) = PlayMobySound(0, 4, obj);
 }
 FastVecSub(delta, obj + 0x10, oldpos);
 func_002AD6F0(state + 0x140, delta, oldrot, obj + 0xF0);
 qcopy(entry + 0x10, obj + 0x10);
 vec_scale_to_length(temp, obj + 0xC0, 2.2f);
 FastVecAdd(entry + 0x10, obj + 0x10, temp);
 vec_scale_to_length(temp2, obj + 0xE0, 0.5f);
 FastVecAdd(entry + 0x10, entry + 0x10, temp2);
 velocity[0] = 0; velocity[3] = 1.0f; velocity[2] = -0.2f; velocity[1] = 0;
 angle = func_002A77E0(16);
 if (func_002A77E0(2)) angle = -angle;
 qcopy(pos, obj + 0x10);
 pos[2] -= 0.2f;
 particle = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, angle, velocity, 630000.0f, 0xDF204080, 0);
 if (particle) {
  char *p = particle + 0x20;
  *(short *)(particle + 0xA) = 15;
  *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 112;
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
 /* Retail really does write the first particle's header here: only the
  * subrecord belongs to the new particle. */
 middle = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, angle, velocity, 630000.0f, 0xDF204080, 0);
 if (middle) {
  char *p = middle + 0x20;
  *(short *)(particle + 0xA) = 15;
  *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 112;
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
 second = SpawnSpinningSparkParticle(pos, 0.05f, 1.0f, 0.97f, 16, velocity, 315000.0f, 0xDFFFFFFF, 0);
 if (second) {
  char *p = second + 0x20;
  int size = FloatToInt(4.0f) + 112;
  *(short *)(second + 0xA) = 25;
  *(unsigned char *)(second + 9) = size;
  *(unsigned char *)(second + 8) = func_002A77E0(255);
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
}
