#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void vec_scale_to_length(void *, void *, float);
extern void *part_spawn_object_following_effect(void *, void *, u32, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, u32, int);
extern void part_explode_object_into_pieces_pal(void *, float *, float *, float *, int, int, int, int, int, u8, void *);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void *SpawnExplosion_pal(void *, float, int, int, int, int, int, int, int, int, int, int, int, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, int, int, int, int, int, int, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_L00_00328480(float, void *, void *, int, int, void *, u32, int, float, float, float);
extern void moby_mark_spawned(void *);
extern int g_arc_effect_count __attribute__((sda));
extern int g_breakable_flag_bit SDATA(D_L03_001B1AD0) __attribute__((sda));
extern float g_breakable_piece_lifetimes[2] SDATA(D_L03_001B1AB0) __attribute__((sda));
extern float g_breakable_piece_spin[2] SDATA(D_L03_001B1AA8) __attribute__((sda));
extern float g_breakable_piece_speeds[2] SDATA(D_L03_001B1AA0) __attribute__((sda));

void endako_breakable_update_pal(u8 *e) {
    u8 *s = *(u8 **)(e + 0x68);
    float a[4] __attribute__((aligned(16)));
    Quad zero = 0;
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    int i;
    switch (e[0x20]) {
    case 0:
        vec_scale_to_length(a, e+0xE0, *(float *)(e+0x2C)*20.0f);
        part_spawn_object_following_effect(a, e, 0x28208080, -1, 0, -1, 0, 0x60, 367500.0f, 0.0f);
        part_spawn_object_following_effect(a, e, 0x20208080, -1, 1, -1, 0, 0x60, 325500.0f, 0.75f);
        if (*(int *)s)
            --g_arc_effect_count;
        moby_set_state(e, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(e, 0x4010000, 0) && !*(int *)s) {
            --g_arc_effect_count;
            moby_set_state(e, 2, -1);
        }
        e[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(e, g_breakable_piece_lifetimes, g_breakable_piece_spin, g_breakable_piece_speeds, 127, 0, g_breakable_flag_bit, 1, 65535, 255, 0);
        part_spawn_scaled_bolts_pal(e, 1, 3.0f);
        *(Quad *)b = zero;
        moby_compute_local_point(e, a, 0, 0, *(float *)(e+0x2C)*20.0f);
        SpawnExplosion_pal(a, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 20.0f);
        SpawnExplosionEffects_pal(e, b, a, 0.0f, 0.0f, 15, 0, 0, 0.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, 9.0f, 1.0f, 0.0f);
        moby_compute_local_point(e, c, 0, 0, *(float *)(e+0x2C)*20.0f);
        for (i = 0; i < 4; i++) {
            float d[4] __attribute__((aligned(16)));
            d[0] = (i / 2 * 2 - 1) * 0.040000003f;
            d[1] = (i % 2 * 2 - 1) * 0.040000003f;
            d[2] = 0.080000006f;
            matrix_mul_vec3(d, d, e+0xC0);
            func_PAL_L00_00328480(0.25f, e, c, 6, 1, d, 0x50404040, 0, 5, 0.75f, 1.25f);
        }
        if (g_breakable_flag_bit >= 0) {
            *(u16 *)(e+0x7C)=(1<<g_breakable_flag_bit)|0x8000;
            moby_set_state(e, 3, -1);
        } else {
            moby_mark_spawned(e);
        }
        break;
    }
}



