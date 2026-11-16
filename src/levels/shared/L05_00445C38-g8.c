#include "common.h"

extern float g_unit_dir_vec[];
extern int g_ship_trail_texture SDATA(D_L05_001B1C24);
extern int g_ship_trail_blend SDATA(D_L05_001B1C28);
extern float g_ship_trail_start_size SDATA(D_L05_001B1C2C);
extern float g_ship_trail_end_size SDATA(D_L05_001B1C30);
extern float g_ship_trail_random_offset SDATA(D_L05_001B1C34);
extern float g_ship_trail_step_scale SDATA(D_L05_001B1C38);
extern int g_ship_trail_step_count SDATA(D_L05_001B1C3C);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);
extern float math_random_angle(void);
extern void vec_add_random_offset(void *, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);
extern void FastVecAdd(void *, void *, void *);

/* Spawns a trail of small particles along the spot where the ship just hit something. */
void part_spawn_impact_trail(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float step[4], position[4], particle[4];
    float fraction, size, heading, inverse;
    int i;
    FastVecScale(step, g_unit_dir_vec, -g_ship_trail_step_scale);
    qcopy(position, state + 0x90);
    inverse = 1.0f / IntToFloat(g_ship_trail_step_count);
    for (i = 0; i < g_ship_trail_step_count; i++) {
        fraction = IntToFloat(i) * inverse;
        size = g_ship_trail_start_size;
        size += (g_ship_trail_end_size - size) * fraction;
        heading = math_random_angle();
        qcopy(particle, position);
        vec_add_random_offset(particle, g_ship_trail_random_offset);
        gfx_draw_billboard_quad(particle, g_ship_trail_texture, g_ship_trail_blend, 1, size, 0.0f, heading);
        FastVecAdd(position, position, step);
    }
}
