#include "common.h"

/* func_L23_0041AFE8 is a unit of its own: it reads $gp data and needs -fno-sched-interblock
   (config/cflags.txt), which keeps the effect call's argument setup behind the handle test.
   Every transfer is the qcopy helper: the inline parameters keep the loop's two names for the
   next point apart, which is what spills obj to the 0xD0 frame. The effect call is typed with
   its FP arguments ahead of the last integer register, as retail sets them up; the EE assigns
   the two banks independently, so this is the same call as func_L23_004256F0's definition. */

typedef int TI128 __attribute__((mode(TI)));

extern float g_barrier_surface_radius __attribute__((sda));
extern float g_energy_barrier_level;
extern char g_energy_barrier_origin[] __attribute__((sda));
extern int g_barrier_trail_life_b __attribute__((sda));
extern unsigned char g_barrier_trail_red __attribute__((sda));
extern unsigned char g_barrier_trail_green __attribute__((sda));
extern float g_barrier_trail_width_a __attribute__((sda));
extern float g_barrier_trail_width_b __attribute__((sda));
extern float g_barrier_trail_length_a __attribute__((sda));
extern float g_barrier_trail_length_b __attribute__((sda));
extern short g_barrier_trail_alpha_a __attribute__((sda));
extern short g_barrier_trail_alpha_b __attribute__((sda));
extern int g_barrier_trail_life_a __attribute__((sda));

extern void mothership_project_point_onto_surface(char *, float);
extern void FastVecAdd(float *, float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void *ribbon_trail_create(u8 *, u8 *, u8 *, u8, u8, short, short, float, float, float, float, int, int, int, int, int);

/* Lays three beam segments between two points around the planet, creating each beam effect only once. */
void mothership_spawn_field_beam_segments(char *obj, TI128 *p1, TI128 *p2, TI128 *out, int *handles) {
    TI128 loc[5];
    char *prev = g_energy_barrier_origin;
    int k;

    qcopy(&loc[0], p2);
    mothership_project_point_onto_surface((char *)&loc[0], g_barrier_surface_radius);
    FastVecSub((float *)&loc[1], (float *)&loc[0], (float *)p1);
    vec_scale_to_length((float *)&loc[1], (float *)&loc[1], g_energy_barrier_level);
    qcopy(&loc[4], p1);
    qcopy(&loc[2], p1);
    mothership_project_point_onto_surface((char *)&loc[2], g_barrier_surface_radius);
    for (k = 0; k < 3; k++) {
        FastVecAdd((float *)&loc[3], (float *)&loc[4], (float *)&loc[1]);
        mothership_project_point_onto_surface((char *)&loc[3], g_barrier_surface_radius);
        qcopy(out, &loc[3]);
        if (*handles == 0) {
            *handles = (int)ribbon_trail_create(prev, obj, (char *)out, g_barrier_trail_red, g_barrier_trail_green, g_barrier_trail_alpha_a, g_barrier_trail_alpha_b, g_barrier_trail_width_a, g_barrier_trail_width_b, g_barrier_trail_length_a, g_barrier_trail_length_b, g_barrier_trail_life_a, g_barrier_trail_life_b, 1, -1, 1);
        }
        handles++;
        qcopy(&loc[2], &loc[3]);
        prev = (char *)out;
        FastVecAdd((float *)&loc[4], (float *)&loc[4], (float *)&loc[1]);
        out++;
    }
}
