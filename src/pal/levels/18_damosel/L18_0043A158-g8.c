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

void func_PAL_L18_0043AAE8(Moby4359A8 *self) {
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

void effect_ring_update_pal(u8 *o) {
    u8 *s;
    u8 *hero = g_hero_state.hero;
    int f[13], n;
    if (hero && *(short *)(hero + 0xAA) == 0x45 && hero[0x20] != 0xFE && hero[0x20] != 0xFD && g_hero_state.mode == 0x31) return;
    s = *(u8 **)(o + 0x68);
    if (!s) return;
    if (*(int *)(s + 0x10) && o[0x20] && *(int *)(s + 0x28) != -1 && !coll_point_inside_region(g_camera_l18_position, *(int *)(s + 0x28))) return;
    n = 1;
    if (*(int *)(s + 0x18) != -1) n = (&g_ring_effect_count_table)[*(int *)(s + 0x18)];
    n += *(int *)(s+0x10);
    f[0]=0x12;
    f[1]=n;
    f[8]=(int)&g_ring_effect_arg_b;
    f[9]=(int)&g_ring_effect_arg_c;
    f[2]=(int)g_water_l18_grid_data;
    f[3]=(int)g_effect_ring_data_a;
    f[4]=(int)&g_ring_effect_arg_a;
    f[5]=(int)&g_ring_effect_count_table;
    f[6]=(int)g_effect_ring_data_b;
    f[7]=(int)g_effect_ring_data_c;
    f[10]=(int)o;
    f[11]=(int)part_effect_callback;
    f[12]=(int)gfx_add_draw_callback_third;
    switch(o[0x20]) {
    case 0: water_init_object_pal(f); water_add_splash_entry(o, *(float *)(s+0x2C));
    case 1: water_update_controller_pal(f); break;
    case 2: water_advance_controller_state(f); break;
    }
    water_update_ripple_patches(f);
}
