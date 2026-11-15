#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern int g_hovering_object_count __attribute__((sda));
extern float D_L02_001B2020 __attribute__((sda));
extern float D_L02_001B2020_1[8] __attribute__((sda));
extern float D_L02_001B2040 __attribute__((sda));
extern float D_L02_001B2040_1[4] __attribute__((sda));
extern void moby_get_anim_entry_count(void *, void *, void *);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void func_PAL_L00_003281C0(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, float, float, int);
extern void func_PAL_L00_00328480(char *, char *, float, int, int, char *, float, int, int, float, float);
extern void func_PAL_L02_004288E8(u8 *, float, float);

void func_PAL_L02_004285CC(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    float v[4];
    float w[4];
    int p20, p24, p28, p2c;
    int i;
    float r1, r2;

    switch (a0[0x20]) {
    case 0:
        moby_get_anim_entry_count(a0, &p20, &p24);
        *(u16 *)(a0 + 0x7C) = p20;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) | 0x1000;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) != 0) {
            g_hovering_object_count = g_hovering_object_count - 1;
            moby_set_state(a0, 2, -1);
        }
        break;
    case 2:
        *(u16 *)(a0 + 0x7C) = 0;
        *(int *)state = 0x64;
        *(int *)(a0 + 0x98) = 0;
        func_PAL_L00_003281C0(a0, 1, 1.0f);
        moby_get_anim_entry_count(a0, &p28, &p2c);
        PlayMobySound(0, 0, a0);
        for (i = 0; i < 16; i++) {
            if ((p28 >> i) & 1) {
                r1 = math_random_float_range(D_L02_001B2040, D_L02_001B2040_1[1]);
                r2 = math_random_float_range(D_L02_001B2040_1[2], D_L02_001B2040_1[3]);
                v[0] = math_random_float_range(D_L02_001B2020, D_L02_001B2020_1[4]) * 0.020000001f;
                v[1] = math_random_signed_float_range(D_L02_001B2020_1[1], D_L02_001B2020_1[5]) * 0.020000001f;
                v[2] = math_random_float_range(D_L02_001B2020_1[2], D_L02_001B2020_1[6]) * 0.020000001f;
                matrix_mul_vec3(v, v, a0 + 0xC0);
                func_PAL_002735D0((char *)a0, 2, 0xD0D, i, (char *)(a0 + 0x10), (char *)(a0 + 0xF0), v, r2, r1, 0xFF);
            }
        }
        *(TI128 *)v = 0;
        v[0] = -0.8f;
        v[2] = 1.5f;
        matrix_mul_vec3(v, v, a0 + 0xC0);
        FastVecAdd(v, v, a0 + 0x10);
        vec_scale_to_length(w, a0 + 0xC0, -0.10000001f);
        func_PAL_L00_00328480((char *)a0, (char *)v, 0.25f, 4, 1, (char *)w, 5.0f, 0x50404040, 0, 0.5f, 1.0f);
        func_PAL_L02_004288E8(a0, -0.10000001f, -0.3f);
        moby_set_state(a0, 3, -1);
        break;
    }
    a0[0xA8] = 0xFF;
}
