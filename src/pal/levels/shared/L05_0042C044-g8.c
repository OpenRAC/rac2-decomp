#include "include_asm.h"
#include "names.h"

extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern int D_L05_001B1500 __attribute__((sda));
extern void func_PAL_L05_0042C2E8(char *);


