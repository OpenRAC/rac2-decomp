#include "common.h"
extern struct { char pad[0x1830]; u8 *hero; char pad2[0xA60]; int mode; } g_hero_state;
extern float g_camera_l18_position[];
extern int D_L18_001B1698 __attribute__((sda));
extern int D_L18_001B16B0 __attribute__((sda));
extern int D_L18_001B16D4 __attribute__((sda));
extern int D_L18_001B16D8 __attribute__((sda));
extern char D_L18_002A9C40[], D_L18_00257C80[], D_L18_00257DA0[], D_L18_002BD860[];
extern void part_effect_callback(void);
extern void gfx_add_draw_callback_third(void);
extern int coll_point_inside_region(void *, int);
extern void water_init_object(void *), water_update_controller(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);
/* Updates a ring of linked effects (moby class 3929) by calling the shared effect code for the current state. It does nothing while the hero is in a special mode. */
void effect_ring_update(u8 *moby) {
    u8 *vars;
    u8 *hero = g_hero_state.hero;
    int effectArgs[13], count;
    if (hero && *(short *)(hero + 0xAA) == 0x45 /* moby class 69 */ && hero[0x20] != 0xFE && hero[0x20] != 0xFD && g_hero_state.mode == 0x31) return;
    vars = *(u8 **)(moby + 0x68);
    if (!vars) return;
    if (*(int *)(vars + 0x10) && moby[0x20] && *(int *)(vars + 0x28) != -1 && !coll_point_inside_region(g_camera_l18_position, *(int *)(vars + 0x28))) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = (&D_L18_001B1698)[*(int *)(vars + 0x18)];
    count += *(int *)(vars+0x10);
    effectArgs[0]=0x12;
    effectArgs[1]=count;
    effectArgs[8]=(int)&D_L18_001B16D4;
    effectArgs[9]=(int)&D_L18_001B16D8;
    effectArgs[2]=(int)D_L18_002A9C40;
    effectArgs[3]=(int)D_L18_00257C80;
    effectArgs[4]=(int)&D_L18_001B16B0;
    effectArgs[5]=(int)&D_L18_001B1698;
    effectArgs[6]=(int)D_L18_00257DA0;
    effectArgs[7]=(int)D_L18_002BD860;
    effectArgs[10]=(int)moby;
    effectArgs[11]=(int)part_effect_callback;
    effectArgs[12]=(int)gfx_add_draw_callback_third;
    switch(moby[0x20]) {
    case 0: water_init_object(effectArgs); water_add_splash_entry(moby, *(float *)(vars+0x2C));
    case 1: water_update_controller(effectArgs); break;
    case 2: water_advance_controller_state(effectArgs); break;
    }
    water_update_ripple_patches(effectArgs);
}
