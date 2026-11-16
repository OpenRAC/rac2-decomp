#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct L01_003C2680_OWNED {
    char pad0[0x68];
    float f68;
    char pad1[0x120 - 0x6C];
    float f120;
    float f124;
    float f128;
    char pad2[0x130 - 0x12C];
    Quad f130;
    Quad f140;
} L01_003C2680_OWNED;
typedef struct L01_003C2680_OBJ {
    char pad0[0x18];
    float f18;
    char pad1[0x20 - 0x1C];
    unsigned char f20;
    char pad2[0x31 - 0x21];
    unsigned char f31;
    char pad3[0x68 - 0x32];
    L01_003C2680_OWNED *f68;
    char pad4[0xAA - 0x6C];
    short fAA;
    char pad5[0xB2 - 0xAC];
    short fB2;
} L01_003C2680_OBJ;
extern void STUB_printf(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float func_PAL_L01_003BEB40();
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void moby_init_controller_params_pal(void *, void *, int, int, void *, int, int, int, void *, void *, int);
extern void moby_update_sway_pal(void *, void *, int);
extern char g_level_origin_vec[];
extern float g_water_surface_height_offset __attribute__((sda));
extern long long g_water_surface_param_b __attribute__((sda));
extern long long g_water_surface_param_c __attribute__((sda));
extern long long g_water_surface_param_a __attribute__((sda));
extern char g_str_water_surface_debug[];

void water_surface_update_pal(L01_003C2680_OBJ *a0)
{
    char *p = (char *)a0;
    L01_003C2680_OWNED *s1 = a0->f68;
    Quad frame[2];

    if (s1 == 0) {
        STUB_printf(g_str_water_surface_debug, a0->fAA, a0->fB2);
        return;
    }
    qcopy(&frame[0], p + 0x10);
    qcopy(&frame[1], p + 0xF0);
    switch (a0->f20) {
    case 0:
        if (func_PAL_L01_003BEB40(p + 0x10) > 0.0f) {
            s1->f120 = math_random_angle();
            s1->f124 = math_random_angle();
            s1->f128 = 0.02f;
            qcopy(&s1->f130, p + 0xF0);
            qzero(&s1->f140);
            moby_set_state(a0, 1, -1);
        }
        a0->f18 = a0->f18 + g_water_surface_height_offset;
        moby_init_controller_params_pal(a0, (char *)s1 + 0x60, 0, 0, &g_water_surface_param_a, 0, 0, 0, &g_water_surface_param_b, &g_water_surface_param_c, 0);
        return;
    case 1:
        if (a0->f31 != 0 && vec_distance_xy(p + 0x10, g_level_origin_vec) < 32.0f) {
            s1->f68 = func_PAL_L01_003BEB40() + g_water_surface_height_offset;
            moby_update_sway_pal(a0, (char *)s1 + 0x60, 0);
        }
        return;
    }
}
