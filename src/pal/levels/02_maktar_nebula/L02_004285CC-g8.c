#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern int g_hovering_object_count __attribute__((sda));
extern float g_breakable_piece_speed_min __attribute__((sda));
extern float D_L02_001B2020_1[8] __attribute__((sda));
extern float g_breakable_piece_size_min __attribute__((sda));
extern float D_L02_001B2040_1[4] __attribute__((sda));
extern void moby_get_anim_entry_count(void *, void *, void *);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *cam_moby_create_pal(char *, int, int, int, char *, char *, float *, float, float, int);
extern void part_spawn_glow_fade_effects_pal(char *, char *, float, int, int, char *, float, int, int, float, float);
extern void part_throw_spark_burst_pal(u8 *, float, float);

/* Updates a breakable piece: when it breaks it throws pieces, bolts and a spark burst, then goes to its final state. */
void breakable_piece_update_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    float pos[4];
    float back[4];
    int anim_count, anim_unused, piece_mask, piece_unused;
    int i;
    float piece_size, piece_spin;

    switch (moby[0x20]) {
    case 0:
        moby_get_anim_entry_count(moby, &anim_count, &anim_unused);
        *(u16 *)(moby + 0x7C) = anim_count;
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x1000;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0) {
            g_hovering_object_count = g_hovering_object_count - 1;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        *(u16 *)(moby + 0x7C) = 0;
        *(int *)state = 0x64;
        *(int *)(moby + 0x98) = 0;
        part_spawn_scaled_bolts_pal(moby, 1, 1.0f);
        moby_get_anim_entry_count(moby, &piece_mask, &piece_unused);
        PlayMobySound(0, 0, moby);
        for (i = 0; i < 16; i++) {
            if ((piece_mask >> i) & 1) {
                piece_size = math_random_float_range(g_breakable_piece_size_min, D_L02_001B2040_1[1]);
                piece_spin = math_random_float_range(D_L02_001B2040_1[2], D_L02_001B2040_1[3]);
                pos[0] = math_random_float_range(g_breakable_piece_speed_min, D_L02_001B2020_1[4]) * 0.020000001f;
                pos[1] = math_random_signed_float_range(D_L02_001B2020_1[1], D_L02_001B2020_1[5]) * 0.020000001f;
                pos[2] = math_random_float_range(D_L02_001B2020_1[2], D_L02_001B2020_1[6]) * 0.020000001f;
                matrix_mul_vec3(pos, pos, moby + 0xC0);
                cam_moby_create_pal((char *)moby, 2, 0xD0D, i, (char *)(moby + 0x10), (char *)(moby + 0xF0), pos, piece_spin, piece_size, 0xFF);
            }
        }
        *(TI128 *)pos = 0;
        pos[0] = -0.8f;
        pos[2] = 1.5f;
        matrix_mul_vec3(pos, pos, moby + 0xC0);
        FastVecAdd(pos, pos, moby + 0x10);
        vec_scale_to_length(back, moby + 0xC0, -0.10000001f);
        part_spawn_glow_fade_effects_pal((char *)moby, (char *)pos, 0.25f, 4, 1, (char *)back, 5.0f, 0x50404040, 0, 0.5f, 1.0f);
        part_throw_spark_burst_pal(moby, -0.10000001f, -0.3f);
        moby_set_state(moby, 3, -1);
        break;
    }
    moby[0xA8] = 0xFF;
}
