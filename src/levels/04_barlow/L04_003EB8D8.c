#include "common.h"
extern void func_003317E8(void *);
extern int func_00342228(void *, int);
extern char g_hero_position[];
extern unsigned char g_sound_state[];
extern float func_0030EFA8(void *, void *);
extern void FastVecAdd(void *, void *, void *);
typedef struct EntityEntry { char bytes[256]; } EntityEntry;
extern EntityEntry *g_moby_l04_pool MACRO_ADDR;
extern char *g_route_path_table[];
extern float mat_fast_helper_a(float, float);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern int flag_is_third_pending_set(void *);
extern int PlayMobySound(int, int, void *);
extern void moby_step_controller(void *, void *, float);
extern void MobySpringTurn(void *, float, float, float, float, void *);
extern void moby_l01_turn_toward_target(void *, void *);
extern void path_set_follower_nodes(void *, void *, int, int);
extern void moby_set_flag_bit(void *, int);
extern void hovering_object_update_motion(void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, unsigned int, int);
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
/* Moves a flying vehicle back and forth between two stops, turning to face each one, with sparks trailing behind and a linked rider carried along. */
void flying_vehicle_update(char *moby)
{
 char *vars = *(char **)(moby + 0x68);
 float oldpos[4], delta[4], oldrot[4], temp[4], temp2[4], velocity[4], pos[4];
 char *entry;
 char *particle;
 char *middle;
 char *second;
 int angle;
 qcopy(oldpos, moby + 0x10);
 qcopy(oldrot, moby + 0xF0);
 entry = (char *)&g_moby_l04_pool[*(int *)(vars + 0x180)];
 switch (*(unsigned char *)(moby + 0x20)) {
 case 0: {
  *(char **)(vars + 0x18) = vars + 0x50;
  if (*(int *)(vars + 0x190) == -1) {func_003317E8(moby); return;}
  ((State *)vars)->motion.f50 = 0.05f;
  ((State *)vars)->motion.f54 = 0.5f;
  ((State *)vars)->motion.f58 = 100.0f;
  ((State *)vars)->motion.f5c = 100.0f;
  ((State *)vars)->motion.f60 = 1.6580629348754883f;
  ((State *)vars)->motion.f80 = 6.283185958862305f;
  ((State *)vars)->motion.f70 = (*(float *)(vars + 0x188) + *(float *)(vars + 0x188)) * 0.00027777778450399637f;
  ((State *)vars)->motion.f78 = *(float *)(vars + 0x188) * (1.0f / 60.0f);
  ((State *)vars)->motion.f68 = 0.0001939255016623065f;
  *(int *)(vars + 0x1DC) = -1;
  ((State *)vars)->motion.i7c = 0;
  ((State *)vars)->motion.i64 = 0;
  ((State *)vars)->motion.i6c = 0;
  *(float *)(moby + 0xF8) = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x20) - *(float *)(moby + 0x10), *(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x24) - *(float *)(moby + 0x14));
  *(float *)(vars + 0x1A8) = math_random_angle();
  *(float *)(vars + 0x1AC) = math_random_angle();
  *(float *)(vars + 0x1C0) = math_random_angle();
  qcopy(vars + 0x1B0, moby + 0x10);
  if (*(int *)(vars + 0x180) != -1) moby_set_state(moby, 3, -1);
  else moby_set_state(moby, 1, -1);
  break;
 }
 case 2:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, moby); moby_set_state(moby, 6, -1);}
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x20) - *(float *)(moby + 0x10), *(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x24) - *(float *)(moby + 0x14)); moby_step_controller(moby, moby + 0x10, heading);}
  break;
 case 4:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, moby); moby_set_state(moby, 5, -1);}
  else if (func_00342228(g_hero_position, *(int *)(vars + 0x194))) moby_set_state(moby, 5, -1);
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x10) - *(float *)(moby + 0x10), *(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x14) - *(float *)(moby + 0x14)); MobySpringTurn(moby, heading, 0.0011635529808700085f, 0.0011635529808700085f, 0.10471977293491364f, vars + 0x18C);}
  break;
 case 3:
  if (flag_is_third_pending_set(entry)) {PlayMobySound(1, 0, moby); moby_set_state(moby, 6, -1);}
  else if (func_00342228(g_hero_position, *(int *)(vars + 0x190))) moby_set_state(moby, 6, -1);
  else {float heading = mat_fast_helper_a(*(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x20) - *(float *)(moby + 0x10), *(float *)(g_route_path_table[*(int *)(vars + 0x184)] + 0x24) - *(float *)(moby + 0x14)); MobySpringTurn(moby, heading, 0.0011635529808700085f, 0.0011635529808700085f, 0.10471977293491364f, vars + 0x18C);}
  break;
 case 6:
  qcopy(temp, entry + 0x10);
  if (func_0030EFA8(entry + 0x10, g_hero_position) < 2.0f && *(char **)(g_hero_position + 0x2BC) != moby) break;
  qcopy(moby + 0x10, vars + 0x1B0);
  moby_l01_turn_toward_target(moby, g_route_path_table[*(int *)(vars + 0x184)] + 0x20);
  qcopy(vars + 0x1B0, moby + 0x10);
  if (func_0030EFA8(moby + 0x10, g_route_path_table[*(int *)(vars + 0x184)] + 0x20) <= 0.5f) {
   moby_set_state(moby, 4, -1);
   path_set_follower_nodes(moby, g_route_path_table[*(int *)(vars + 0x184)], 0, 1);
  }
  break;
 case 5:
  qcopy(temp, entry + 0x10);
  if (func_0030EFA8(entry + 0x10, g_hero_position) < 2.0f && *(char **)(g_hero_position + 0x2BC) != moby) break;
  qcopy(moby + 0x10, vars + 0x1B0);
  moby_l01_turn_toward_target(moby, g_route_path_table[*(int *)(vars + 0x184)] + 0x10);
  qcopy(vars + 0x1B0, moby + 0x10);
  if (func_0030EFA8(moby + 0x10, g_route_path_table[*(int *)(vars + 0x184)] + 0x10) <= 0.5f) {
   moby_set_state(moby, 3, -1);
   PlayMobySound(1, 0, moby);
   moby_set_flag_bit(entry, 0);
   path_set_follower_nodes(moby, g_route_path_table[*(int *)(vars + 0x184)], 1, 0);
  }
  break;
 }
 hovering_object_update_motion(moby);
 {
  char *sound = (char *)g_sound_state + *(int *)(vars + 0x1DC) * 112;
  if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74)) *(int *)(vars + 0x1DC) = PlayMobySound(0, 4, moby);
 }
 FastVecSub(delta, moby + 0x10, oldpos);
 mat_combine_and_store(vars + 0x140, delta, oldrot, moby + 0xF0);
 qcopy(entry + 0x10, moby + 0x10);
 vec_scale_to_length(temp, moby + 0xC0, 2.2f);
 FastVecAdd(entry + 0x10, moby + 0x10, temp);
 vec_scale_to_length(temp2, moby + 0xE0, 0.5f);
 FastVecAdd(entry + 0x10, entry + 0x10, temp2);
 velocity[0] = 0; velocity[3] = 1.0f; velocity[2] = -0.2f; velocity[1] = 0;
 angle = math_random_int_below(16);
 if (math_random_int_below(2)) angle = -angle;
 qcopy(pos, moby + 0x10);
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
  *(unsigned char *)(second + 8) = math_random_int_below(255);
  *(int *)(p + 4) = 2;
  *(unsigned char *)(p + 0xA) = 0xDF;
  *(unsigned char *)(p + 0xB) = *(unsigned char *)(particle + 0xA);
 }
}
