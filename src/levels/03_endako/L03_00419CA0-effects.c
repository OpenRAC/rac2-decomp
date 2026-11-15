#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern void vec_scale_to_length(void *, void *, float);
extern void *part_spawn_object_following_effect(void *, void *, u32, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, u32, int);
extern void part_explode_object_into_pieces(void *, float *, float *, float *, int, int, int, int, int, u8, void *);
extern void part_spawn_scaled_bolts(void *, int, float);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void *SpawnExplosion(void *, float, int, int, int, int, int, int, int, int, int, int, int, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, int, int, int, int, int, int, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void SpawnTintedEffects(float, void *, void *, int, int, void *, u32, int, float, float, float);
extern void moby_mark_spawned(void *);

/* At -G0, the assembler emits GP accesses in delay slots and absolute
 * accesses elsewhere for this counter. The settings below use explicit GP views. */
extern int D_L03_001AEBF8 __attribute__((sda));

extern int D_L03_001B1AD0 SDATA(D_L03_001B1AD0) __attribute__((sda));
extern float D_L03_001B1AB0[2] SDATA(D_L03_001B1AB0) __attribute__((sda));
extern float D_L03_001B1AA8[2] SDATA(D_L03_001B1AA8) __attribute__((sda));
extern float D_L03_001B1AA0[2] SDATA(D_L03_001B1AA0) __attribute__((sda));

/* Waits for a hit, then blows up with sparks and flying bits. */
void endako_breakable_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float a[4] __attribute__((aligned(16)));
    Quad zero = 0;
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    int i;
    switch (moby[0x20]) {
    case 0:
        vec_scale_to_length(a, moby+0xE0, *(float *)(moby+0x2C)*20.0f);
        part_spawn_object_following_effect(a, moby, 0x28208080, -1, 0, -1, 0, 0x60, 367500.0f, 0.0f);
        part_spawn_object_following_effect(a, moby, 0x20208080, -1, 1, -1, 0, 0x60, 325500.0f, 0.75f);
        if (*(int *)vars)
            --D_L03_001AEBF8;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !*(int *)vars) {
            --D_L03_001AEBF8;
            moby_set_state(moby, 2, -1);
        }
        moby[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces(moby, D_L03_001B1AB0, D_L03_001B1AA8, D_L03_001B1AA0, 127, 0, D_L03_001B1AD0, 1, 65535, 255, 0);
        part_spawn_scaled_bolts(moby, 1, 3.0f);
        *(Quad *)b = zero;
        moby_compute_local_point(moby, a, 0, 0, *(float *)(moby+0x2C)*20.0f);
        SpawnExplosion(a, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 20.0f);
        SpawnExplosionEffects(moby, b, a, 0.0f, 0.0f, 15, 0, 0, 0.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, 9.0f, 1.0f, 0.0f);
        moby_compute_local_point(moby, c, 0, 0, *(float *)(moby+0x2C)*20.0f);
        for (i = 0; i < 4; i++) {
            float d[4] __attribute__((aligned(16)));
            d[0] = (i / 2 * 2 - 1) * 0.033333335f;
            d[1] = (i % 2 * 2 - 1) * 0.033333335f;
            d[2] = 0.06666667f;
            matrix_mul_vec3(d, d, moby+0xC0);
            SpawnTintedEffects(0.25f, moby, c, 6, 1, d, 0x50404040, 0, 5, 0.75f, 1.25f);
        }
        if (D_L03_001B1AD0 >= 0) {
            *(u16 *)(moby+0x7C)=(1<<D_L03_001B1AD0)|0x8000;
            moby_set_state(moby, 3, -1);
        } else {
            moby_mark_spawned(moby);
        }
        break;
    }
}
