#include "include_asm.h"
#include "names.h"

/* func_L02_00423520 is a unit of its own: retail clears its vector as plain C, with the zero
   materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

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
extern void part_spawn_scaled_bolts(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *cam_moby_create(char *, int, int, int, char *, char *, float *, float, float, int);
extern void SpawnTintedEffects(char *, char *, float, int, int, char *, float, int, int, float, float);
extern void part_throw_spark_burst(u8 *, float, float);

/* A breakable object (moby class 3341). It waits to be hit, then flies apart into pieces with a puff of sparks, and goes away. */
void breakable_piece_update(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    float velocity[4];
    float backDir[4];
    int firstValue, secondValue, partMask, unusedValue;
    int i;
    float sizeA, sizeB;

    switch (moby[0x20]) {
    case 0:
        moby_get_anim_entry_count(moby, &firstValue, &secondValue);
        *(u16 *)(moby + 0x7C) = firstValue;
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
        *(int *)state = 0x78;
        *(int *)(moby + 0x98) = 0;
        part_spawn_scaled_bolts(moby, 1, 1.0f);
        moby_get_anim_entry_count(moby, &partMask, &unusedValue);
        PlayMobySound(0, 0, moby);
        for (i = 0; i < 16; i++) {
            if ((partMask >> i) & 1) {
                sizeA = math_random_float_range(g_breakable_piece_size_min, D_L02_001B2040_1[1]);
                sizeB = math_random_float_range(D_L02_001B2040_1[2], D_L02_001B2040_1[3]);
                velocity[0] = math_random_float_range(g_breakable_piece_speed_min, D_L02_001B2020_1[4]) * 0.016666668f;
                velocity[1] = math_random_signed_float_range(D_L02_001B2020_1[1], D_L02_001B2020_1[5]) * 0.016666668f;
                velocity[2] = math_random_float_range(D_L02_001B2020_1[2], D_L02_001B2020_1[6]) * 0.016666668f;
                matrix_mul_vec3(velocity, velocity, moby + 0xC0);
                cam_moby_create((char *)moby, 2, 0xD0D /* moby class 3341 */, i, (char *)(moby + 0x10), (char *)(moby + 0xF0), velocity, sizeB, sizeA, 0xFF);
            }
        }
        *(TI128 *)velocity = 0;
        velocity[0] = -0.8f;
        velocity[2] = 1.5f;
        matrix_mul_vec3(velocity, velocity, moby + 0xC0);
        FastVecAdd(velocity, velocity, moby + 0x10);
        vec_scale_to_length(backDir, moby + 0xC0, -0.083333336f);
        SpawnTintedEffects((char *)moby, (char *)velocity, 0.25f, 4, 1, (char *)backDir, 5.0f, 0x50404040, 0, 0.5f, 1.0f);
        part_throw_spark_burst(moby, -0.083333336f, -0.25f);
        moby_set_state(moby, 3, -1);
        break;
    }
    moby[0xA8] = 0xFF;
}
