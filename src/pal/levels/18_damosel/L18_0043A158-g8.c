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
extern f32 D_L18_001B1640 __attribute__((sda));
extern f32 D_L18_001B1644 __attribute__((sda));
extern f32 D_L18_001B1648 __attribute__((sda));
extern f32 D_L18_001B164C __attribute__((sda));
extern f32 D_L18_001B1650 __attribute__((sda));
extern f32 D_L18_001B1654 __attribute__((sda));
extern s32 D_L18_001B165C __attribute__((sda));
extern s32 D_L18_001B1660 __attribute__((sda));
extern s32 D_L18_001B1664 __attribute__((sda));
extern f32 D_L18_001B1678[2] __attribute__((sda));
extern f32 D_L18_001B1680[2] __attribute__((sda));
extern f32 D_L18_001B1688[2] __attribute__((sda));
extern char *D_L18_001B1690[2] __attribute__((sda));
extern char D_L18_001B3720[] __attribute__((sda));
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

    for (i = 0; i < D_L18_001B165C; i++) {
        k = math_random_int_below(2);
        x = D_L18_001B1648 + math_random_float_range(-D_L18_001B164C, D_L18_001B164C);
        y = D_L18_001B1650 + math_random_float_range(-D_L18_001B1654, D_L18_001B1654);
        z = -((D_L18_001B1640 + math_random_float_range(-D_L18_001B1644, D_L18_001B1644)) * 0.0003490659f);
        w = D_L18_001B1678[k] + math_random_float_range(-D_L18_001B1688[k], D_L18_001B1688[k]);
        part_create_orbiting_effect(D_L18_001B3720, x, y, z, w, D_L18_001B1680[k], D_L18_001B1660 + math_random_int_below(D_L18_001B1664 - D_L18_001B1660), vars->kinds[k], k, D_L18_001B1690[k]);
    }
}

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
extern void func_PAL_L04_003A47C0(void *), func_PAL_L04_003A49E0(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(void *, float);

void func_PAL_L18_0043AC50(u8 *o) {
    u8 *s;
    u8 *hero = g_hero_state.hero;
    int f[13], n;
    if (hero && *(short *)(hero + 0xAA) == 0x45 && hero[0x20] != 0xFE && hero[0x20] != 0xFD && g_hero_state.mode == 0x31) return;
    s = *(u8 **)(o + 0x68);
    if (!s) return;
    if (*(int *)(s + 0x10) && o[0x20] && *(int *)(s + 0x28) != -1 && !coll_point_inside_region(g_camera_l18_position, *(int *)(s + 0x28))) return;
    n = 1;
    if (*(int *)(s + 0x18) != -1) n = (&D_L18_001B1698)[*(int *)(s + 0x18)];
    n += *(int *)(s+0x10);
    f[0]=0x12;
    f[1]=n;
    f[8]=(int)&D_L18_001B16D4;
    f[9]=(int)&D_L18_001B16D8;
    f[2]=(int)D_L18_002A9C40;
    f[3]=(int)D_L18_00257C80;
    f[4]=(int)&D_L18_001B16B0;
    f[5]=(int)&D_L18_001B1698;
    f[6]=(int)D_L18_00257DA0;
    f[7]=(int)D_L18_002BD860;
    f[10]=(int)o;
    f[11]=(int)part_effect_callback;
    f[12]=(int)gfx_add_draw_callback_third;
    switch(o[0x20]) {
    case 0: func_PAL_L04_003A47C0(f); water_add_splash_entry(o, *(float *)(s+0x2C));
    case 1: func_PAL_L04_003A49E0(f); break;
    case 2: water_advance_controller_state(f); break;
    }
    water_update_ripple_patches(f);
}
