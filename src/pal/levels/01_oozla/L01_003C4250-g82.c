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
extern float level_get_water_height_pal();
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

/* Updates an object that sits on the water: it waits until water is present, then bobs along and reacts when the camera gets close (PAL version). */
void water_surface_update_pal(L01_003C2680_OBJ *moby)
{
    char *moby_bytes = (char *)moby;
    L01_003C2680_OWNED *state = moby->f68;
    Quad frame[2];

    if (state == 0) {
        STUB_printf(g_str_water_surface_debug, moby->fAA, moby->fB2);
        return;
    }
    qcopy(&frame[0], moby_bytes + 0x10);
    qcopy(&frame[1], moby_bytes + 0xF0);
    switch (moby->f20) {
    case 0:
        if (level_get_water_height_pal(moby_bytes + 0x10) > 0.0f) {
            state->f120 = math_random_angle();
            state->f124 = math_random_angle();
            state->f128 = 0.02f;
            qcopy(&state->f130, moby_bytes + 0xF0);
            qzero(&state->f140);
            moby_set_state(moby, 1, -1);
        }
        moby->f18 = moby->f18 + g_water_surface_height_offset;
        moby_init_controller_params_pal(moby, (char *)state + 0x60, 0, 0, &g_water_surface_param_a, 0, 0, 0, &g_water_surface_param_b, &g_water_surface_param_c, 0);
        return;
    case 1:
        if (moby->f31 != 0 && vec_distance_xy(moby_bytes + 0x10, g_level_origin_vec) < 32.0f) {
            state->f68 = level_get_water_height_pal() + g_water_surface_height_offset;
            moby_update_sway_pal(moby, (char *)state + 0x60, 0);
        }
        return;
    }
}
