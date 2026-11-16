#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[8];
    char *kinds[2];
} Vars4359A8;

typedef struct {
    u8 pad00[0x68];
    Vars4359A8 *vars;
} Moby4359A8;

extern f32 g_random_burst_pitch_deg __attribute__((sda));
extern f32 g_random_burst_pitch_spread __attribute__((sda));
extern f32 g_random_burst_x_base __attribute__((sda));
extern f32 g_random_burst_x_spread __attribute__((sda));
extern f32 g_random_burst_y_base __attribute__((sda));
extern f32 g_random_burst_y_spread __attribute__((sda));
extern s32 g_random_burst_count __attribute__((sda));
extern s32 g_orbit_effect_life_min __attribute__((sda));
extern s32 g_orbit_effect_life_max __attribute__((sda));
extern f32 g_random_burst_size_table[2] __attribute__((sda));
extern f32 g_orbit_effect_radius_table[2] __attribute__((sda));
extern f32 g_random_burst_size_spread_table[2] __attribute__((sda));
extern char *g_orbit_effect_name_table[2] __attribute__((sda));
extern char g_burst_origin_position[] __attribute__((sda));

extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern char *part_create_orbiting_effect(char *p0, float f0, float f1, float f2, float f3, float f4, s16 p1, char *p2, s32 p3, char *p4);

/* Spawns a burst of small effect objects with random positions, sizes and kinds, picking one of two looks for each. */
void part_l18_spawn_random_burst(Moby4359A8 *self) {
    Vars4359A8 *vars = self->vars;
    s32 i;
    s32 variant;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    for (i = 0; i < g_random_burst_count; i++) {
        variant = math_random_int_below(2);
        x = g_random_burst_x_base + math_random_float_range(-g_random_burst_x_spread, g_random_burst_x_spread);
        y = g_random_burst_y_base + math_random_float_range(-g_random_burst_y_spread, g_random_burst_y_spread);
        z = -((g_random_burst_pitch_deg + math_random_float_range(-g_random_burst_pitch_spread, g_random_burst_pitch_spread)) * 0.00029088825f);
        w = g_random_burst_size_table[variant] + math_random_float_range(-g_random_burst_size_spread_table[variant], g_random_burst_size_spread_table[variant]);
        part_create_orbiting_effect(g_burst_origin_position, x, y, z, w, g_orbit_effect_radius_table[variant], g_orbit_effect_life_min + math_random_int_below(g_orbit_effect_life_max - g_orbit_effect_life_min), vars->kinds[variant], variant, g_orbit_effect_name_table[variant]);
    }
}
