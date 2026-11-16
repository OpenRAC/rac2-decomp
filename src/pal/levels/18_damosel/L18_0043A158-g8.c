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

/* Throws out a random burst of orbiting effects from a fixed spot, each with a random direction, size and lifetime. (PAL version) */
void part_l18_spawn_random_burst_pal(Moby4359A8 *self) {
    Vars4359A8 *vars = self->vars;
    s32 i;
    s32 k;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    for (i = 0; i < g_random_burst_count; i++) {
        k = math_random_int_below(2);
        x = g_random_burst_x_base + math_random_float_range(-g_random_burst_x_spread, g_random_burst_x_spread);
        y = g_random_burst_y_base + math_random_float_range(-g_random_burst_y_spread, g_random_burst_y_spread);
        z = -((g_random_burst_pitch_deg + math_random_float_range(-g_random_burst_pitch_spread, g_random_burst_pitch_spread)) * 0.0003490659f);
        w = g_random_burst_size_table[k] + math_random_float_range(-g_random_burst_size_spread_table[k], g_random_burst_size_spread_table[k]);
        part_create_orbiting_effect(g_burst_origin_position, x, y, z, w, g_orbit_effect_radius_table[k], g_orbit_effect_life_min + math_random_int_below(g_orbit_effect_life_max - g_orbit_effect_life_min), vars->kinds[k], k, g_orbit_effect_name_table[k]);
    }
}

extern struct { char pad[0x1830]; u8 *hero; char pad2[0xA60]; int mode; } g_hero_state;
extern float g_camera_l18_position[];
extern int g_ring_effect_count_table __attribute__((sda));
extern int g_ring_effect_arg_a __attribute__((sda));
extern int g_ring_effect_arg_b __attribute__((sda));
extern int g_ring_effect_arg_c __attribute__((sda));
extern char g_water_l18_grid_data[], g_effect_ring_data_a[], g_effect_ring_data_b[], g_effect_ring_data_c[];
extern void part_effect_callback(void);
extern void gfx_add_draw_callback_third(void);
extern int coll_point_inside_region(void *, int);
extern void water_init_object_pal(void *), water_update_controller_pal(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);

/* Updates a ring of linked effects (moby class 3929) by calling the shared effect code for the current state. It does nothing while the hero is in a special mode. (PAL version) */
void effect_ring_update_pal(u8 *moby) {
    u8 *vars;
    u8 *hero = g_hero_state.hero;
    int args[13], count;
    if (hero && *(short *)(hero + 0xAA) == 0x45 && hero[0x20] != 0xFE && hero[0x20] != 0xFD && g_hero_state.mode == 0x31) return;
    vars = *(u8 **)(moby + 0x68);
    if (!vars) return;
    if (*(int *)(vars + 0x10) && moby[0x20] && *(int *)(vars + 0x28) != -1 && !coll_point_inside_region(g_camera_l18_position, *(int *)(vars + 0x28))) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = (&g_ring_effect_count_table)[*(int *)(vars + 0x18)];
    count += *(int *)(vars+0x10);
    args[0]=0x12;
    args[1]=count;
    args[8]=(int)&g_ring_effect_arg_b;
    args[9]=(int)&g_ring_effect_arg_c;
    args[2]=(int)g_water_l18_grid_data;
    args[3]=(int)g_effect_ring_data_a;
    args[4]=(int)&g_ring_effect_arg_a;
    args[5]=(int)&g_ring_effect_count_table;
    args[6]=(int)g_effect_ring_data_b;
    args[7]=(int)g_effect_ring_data_c;
    args[10]=(int)moby;
    args[11]=(int)part_effect_callback;
    args[12]=(int)gfx_add_draw_callback_third;
    switch(moby[0x20]) {
    case 0: water_init_object_pal(args); water_add_splash_entry(moby, *(float *)(vars+0x2C));
    case 1: water_update_controller_pal(args); break;
    case 2: water_advance_controller_state(args); break;
    }
    water_update_ripple_patches(args);
}
