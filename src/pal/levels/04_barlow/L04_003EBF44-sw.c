#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern int IsPointInCuboid(void *, int);
extern char g_hero_position[];
extern unsigned char g_sound_state[];
extern float vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
typedef struct EntityEntry { char bytes[256]; } EntityEntry;
extern EntityEntry *g_moby_l04_pool MACRO_ADDR;
extern char *g_route_path_table[];
extern float mat_fast_helper_a(float, float);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern int flag_is_third_pending_set(void *);
extern int PlayMobySound(int, int, void *);
extern void func_PAL_002B5C98(void *, void *, float);
extern void MobySpringTurn(void *, float, float, float, float, void *);
extern void func_PAL_L01_00323068(void *, void *);
extern void path_set_follower_nodes(void *, void *, int, int);
extern void moby_set_flag_bit(void *, int);
extern void func_PAL_L04_003F00D8(void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern char *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, unsigned int, int);
extern int FloatToInt(float);
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

void func_PAL_L04_003EF870(char *obj)
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
 entry = (char *)&g_moby_l04_pool[*(int *)(state + 0x180)];
 switch (*(unsigned char *)(obj + 0x20)) {
 case 0: {
  *(char **)(state + 0x18) = state + 0x50;
  if (*(int *)(state + 0x190) == -1) {moby_mark_spawned(obj); return;}
  ((State *)state)->motion.f50 = 0.05f;
  ((State *)state)->motion.f54 = 0.5f;
  ((State *)state)->motion.f58 = 100.0f;
  ((State *)state)->motion.f5c = 100.0f;
  ((State *)state)->motion.f60 = 1.6580629348754883f;
  ((State *)state)->motion.f80 = 6.283185958862305f;
  ((State *)state)->motion.f70 = (*(float *)(state + 0x188) + *(float *)(state + 0x188)) * 0.00040000002f;
  ((State *)state)->motion.f78 = *(float *)(state + 0x188) * (0.020000001f);
  ((State *)state)->motion.f68 = 0.00027925274f;
  *(int *)(state + 0x1DC) = -1;
  ((State *)state)->motion.i7c = 0;
  ((State *)state)->motion.i64 = 0;
  ((State *)state)->motion.i6c = 0;
  *(float *)(obj + 0xF8) = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14));
  *(float *)(state + 0x1A8) = math_random_angle();
  *(float *)(state + 0x1AC) = math_random_angle();
  *(float *)(state + 0x1C0) = math_random_angle();
  qcopy(state + 0x1B0, obj + 0x10);
  if (*(int *)(state + 0x180) != -1) moby_set_state(obj, 3, -1);
  else moby_set_state(obj, 1, -1);
  break;
 }
 case 2:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, obj); moby_set_state(obj, 6, -1);}
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14)); func_PAL_002B5C98(obj, obj + 0x10, heading);}
  break;
 case 4:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, obj); moby_set_state(obj, 5, -1);}
  else if (IsPointInCuboid(g_hero_position, *(int *)(state + 0x194))) moby_set_state(obj, 5, -1);
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x10) - *(float *)(obj + 0x10), *(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x14) - *(float *)(obj + 0x14)); MobySpringTurn(obj, heading, 0.0016755164f, 0.0016755164f, 0.12566373f, state + 0x18C);}
  break;
 case 3:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, obj); moby_set_state(obj, 6, -1);}
  else if (IsPointInCuboid(g_hero_position, *(int *)(state + 0x190))) moby_set_state(obj, 6, -1);
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x20) - *(float *)(obj + 0x10), *(float *)(g_route_path_table[*(int *)(state + 0x184)] + 0x24) - *(float *)(obj + 0x14)); MobySpringTurn(obj, heading, 0.0016755164f, 0.0016755164f, 0.12566373f, state + 0x18C);}
  break;
 case 6:
  qcopy(temp, entry + 0x10);
  if (vec_distance_xy(entry + 0x10, g_hero_position) < 2.0f && *(char **)(g_hero_position + 0x2BC) != obj) break;
  qcopy(obj + 0x10, state + 0x1B0);
  func_PAL_L01_00323068(obj, g_route_path_table[*(int *)(state + 0x184)] + 0x20);
  qcopy(state + 0x1B0, obj + 0x10);
  if (vec_distance_xy(obj + 0x10, g_route_path_table[*(int *)(state + 0x184)] + 0x20) <= 0.5f) {
   moby_set_state(obj, 4, -1);
   path_set_follower_nodes(obj, g_route_path_table[*(int *)(state + 0x184)], 0, 1);
  }
  break;
 case 5:
  qcopy(temp, entry + 0x10);
  if (vec_distance_xy(entry + 0x10, g_hero_position) < 2.0f && *(char **)(g_hero_position + 0x2BC) != obj) break;
  qcopy(obj + 0x10, state + 0x1B0);
  func_PAL_L01_00323068(obj, g_route_path_table[*(int *)(state + 0x184)] + 0x10);
  qcopy(state + 0x1B0, obj + 0x10);
  if (vec_distance_xy(obj + 0x10, g_route_path_table[*(int *)(state + 0x184)] + 0x10) <= 0.5f) {
   moby_set_state(obj, 3, -1);
   PlayMobySound(1, 0, obj);
   moby_set_flag_bit(entry, 0);
   path_set_follower_nodes(obj, g_route_path_table[*(int *)(state + 0x184)], 1, 0);
  }
  break;
 }
 func_PAL_L04_003F00D8(obj);
 {
  char *sound = (char *)g_sound_state + *(int *)(state + 0x1DC) * 112;
  if (*(char **)(sound + 0x88) != obj || !*(unsigned char *)(sound + 0x74)) *(int *)(state + 0x1DC) = PlayMobySound(0, 4, obj);
 }
 FastVecSub(delta, obj + 0x10, oldpos);
 mat_combine_and_store(state + 0x140, delta, oldrot, obj + 0xF0);
 qcopy(entry + 0x10, obj + 0x10);
 vec_scale_to_length(temp, obj + 0xC0, 2.2f);
 FastVecAdd(entry + 0x10, obj + 0x10, temp);
 vec_scale_to_length(temp2, obj + 0xE0, 0.5f);
 FastVecAdd(entry + 0x10, entry + 0x10, temp2);
 velocity[0] = 0; velocity[3] = 1.0f; velocity[2] = -0.2f; velocity[1] = 0;
 angle = math_random_int_below(16);
 if (math_random_int_below(2)) angle = -angle;
 qcopy(pos, obj + 0x10);
 pos[2] -= 0.2f;
 particle = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, angle, velocity, 630000.0f, 0xDF204080, 0);
 if (particle) {
  char *p = particle + 0x20;
  *(short *)(particle + 0xA) = 12;
  *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 112;
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
 /* Retail really does write the first particle's header here: only the
  * subrecord belongs to the new particle. */
 middle = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, angle, velocity, 630000.0f, 0xDF204080, 0);
 if (middle) {
  char *p = middle + 0x20;
  *(short *)(particle + 0xA) = 12;
  *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 112;
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
 second = func_PAL_002BE9A8(pos, 0.05f, 1.0f, 0.97f, 16, velocity, 315000.0f, 0xDFFFFFFF, 0);
 if (second) {
  char *p = second + 0x20;
  int size = FloatToInt(4.0f) + 112;
  *(short *)(second + 0xA) = 21;
  *(unsigned char *)(second + 9) = size;
  *(unsigned char *)(second + 8) = math_random_int_below(255);
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
}
