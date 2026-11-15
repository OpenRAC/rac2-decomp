#include "include_asm.h"
#include "names.h"

/* func_L02_003DBA70 is a unit of its own: retail clears its velocity vector as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps,
   and copies the position with the grouped quadword copy and its scheduling barrier
   (-frac2-qcopy -frac2-qcopy-barrier; config/cflags.txt). */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B0518 __attribute__((sda));
extern float D_L02_001B051C __attribute__((sda));
extern float D_L02_001B0520 __attribute__((sda));
extern float D_L02_001B0524 __attribute__((sda));
extern float D_L02_001B0528 __attribute__((sda));
extern char D_L02_001B0500[4] __attribute__((sda));
extern char g_camera_l02_position[];

extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *, void *, void *, void *, int);

/* Spawns arg1 particles at the point arg0 raised by D_L02_001B0524 and pushed along the vector
   from D_L02_001BA500, each with a random upward speed (a sixtieth of the range D_L02_001B051C ..
   D_L02_001B0520) and the particle kind that func_002A77E0 picks for 2. */
void part_spawn_rising(char *point, int count) {
    float vel[4];
    float pos[4];
    float tmp[4];
    int i;

    *(TI128 *)vel = 0;
    *(TI128 *)pos = *(TI128 *)point;
    pos[2] += D_L02_001B0524;
    pos[3] = 0;
    FastVecSub(tmp, g_camera_l02_position, pos);
    tmp[2] = 0;
    vec_scale_to_length(tmp, tmp, D_L02_001B0528);
    FastVecAdd(pos, pos, tmp);
    for (i = 0; i < count; i++) {
        vec_add_random_offset(pos, D_L02_001B0518);
        vel[2] = math_random_float_range(D_L02_001B051C, D_L02_001B0520) * 0.016666668f;
        enemy_spawn_record(pos, vel, D_L02_001B0500, (void *)math_random_int_below(2), 1);
    }
}
