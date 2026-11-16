#include "common.h"
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
extern void water_init_object(void *), water_update_controller(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);
/* Updates a ring of linked effects (moby class 3929) by calling the shared effect code for the current state. It does nothing while the hero is in a special mode. */
void effect_ring_update(u8 *moby) {
    u8 *vars;
    u8 *hero = g_hero_state.hero;
    int effect_args[13], count;
    if (hero && *(short *)(hero + 0xAA) == 0x45 /* moby class 69 */ && hero[0x20] != 0xFE && hero[0x20] != 0xFD && g_hero_state.mode == 0x31) return;
    vars = *(u8 **)(moby + 0x68);
    if (!vars) return;
    if (*(int *)(vars + 0x10) && moby[0x20] && *(int *)(vars + 0x28) != -1 && !coll_point_inside_region(g_camera_l18_position, *(int *)(vars + 0x28))) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = (&g_ring_effect_count_table)[*(int *)(vars + 0x18)];
    count += *(int *)(vars+0x10);
    effect_args[0]=0x12;
    effect_args[1]=count;
    effect_args[8]=(int)&g_ring_effect_arg_b;
    effect_args[9]=(int)&g_ring_effect_arg_c;
    effect_args[2]=(int)g_water_l18_grid_data;
    effect_args[3]=(int)g_effect_ring_data_a;
    effect_args[4]=(int)&g_ring_effect_arg_a;
    effect_args[5]=(int)&g_ring_effect_count_table;
    effect_args[6]=(int)g_effect_ring_data_b;
    effect_args[7]=(int)g_effect_ring_data_c;
    effect_args[10]=(int)moby;
    effect_args[11]=(int)part_effect_callback;
    effect_args[12]=(int)gfx_add_draw_callback_third;
    switch(moby[0x20]) {
    case 0: water_init_object(effect_args); water_add_splash_entry(moby, *(float *)(vars+0x2C));
    case 1: water_update_controller(effect_args); break;
    case 2: water_advance_controller_state(effect_args); break;
    }
    water_update_ripple_patches(effect_args);
}
