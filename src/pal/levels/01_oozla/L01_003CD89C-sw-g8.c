#include "include_asm.h"

#include "common.h"
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern int math_fast_float_d(void *);
extern void moby_set_byte_on_group(int, int);
extern void gfx_free_point_light(int);
typedef struct { char pad[0x30]; float position[4]; char rest[0x40]; } L01_003C9D00_PATH;
extern L01_003C9D00_PATH *D_L01_001B264C;
extern char g_dynamic_light_table[];
extern float fast_vec_dist(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_helper_a(void *, float);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void DrawFiveLayerScrollingRibbons(void *);

void func_PAL_L01_003CDDC8(char *obj)
{
    float vec[4];
    char *s = *(char **)(obj + 0x68);
    float blend = 0.0f;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(s + 0x90) = -1;
        *(int *)(s + 0x5C) |= 4;
        *(float *)(s + 0x70) = 0.0f;
        *(int *)(s + 0x6C) = 0;
        *(float *)(s + 0x74) = 0.0f;
        *(int *)(obj + 0x98) = 0;
        qcopy(s + 0x80, obj + 0x10);
        *(float *)(s + 0x98) = fast_vec_dist(D_L01_001B264C[*(int *)(s + 0x94)].position);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(unsigned char *)(obj + 0xBC)) {
            *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
            moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        *(float *)(s + 0x70) += 1.0f / *(float *)(s + 0x60);
        if (*(float *)(s + 0x70) > 1.0f) *(float *)(s + 0x70) = 1.0f;
        else if (*(float *)(s + 0x70) < 0.0f) *(float *)(s + 0x70) = 0.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(*(float *)(s + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(s + 0x94) == -1) {
            vec_scale_to_length(vec, obj + 0xC0, blend * 10.0f);
            FastVecSub(obj + 0x10, s + 0x80, vec);
        } else {
            FastVecSub(vec, D_L01_001B264C[*(int *)(s + 0x94)].position, s + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(s + 0x98) * blend);
            FastVecAdd(obj + 0x10, s + 0x80, vec);
        }
        if (*(float *)(s + 0x70) >= 1.0f) {
            *(int *)(s + 0x6C) = *(int *)(s + 0x64);
            moby_set_state(obj, 3, -1);
        }
        break;
    case 3:
        blend = 1.0f;
        if (math_fast_float_d(s + 0x6C)) moby_set_state(obj, 4, -1);
        break;
    case 4:
        *(float *)(s + 0x70) -= 1.0f / *(float *)(s + 0x60);
        if (*(float *)(s + 0x70) > 1.0f) *(float *)(s + 0x70) = 1.0f;
        else if (*(float *)(s + 0x70) < 0.0f) *(float *)(s + 0x70) = 0.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(*(float *)(s + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(s + 0x94) == -1) {
            vec_scale_to_length(vec, obj + 0xC0, blend * 10.0f);
            FastVecSub(obj + 0x10, s + 0x80, vec);
        } else {
            FastVecSub(vec, D_L01_001B264C[*(int *)(s + 0x94)].position, s + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(s + 0x98) * blend);
            FastVecAdd(obj + 0x10, s + 0x80, vec);
        }
        if (*(float *)(s + 0x70) <= 0.0f) {
            *(int *)(obj + 0x98) = 0;
            moby_set_byte_on_group(*(unsigned char *)(obj + 0x21), 0);
            moby_set_state(obj, 1, -1);
        }
        break;
    }
    *(unsigned char *)(obj + 0xBC) = 0;
    if ((unsigned int)(*(unsigned char *)(obj + 0x20) - 2) < 3) {
        gfx_add_draw_callback_first(DrawFiveLayerScrollingRibbons, obj);
        vec_scale_to_length(vec, obj + 0xC0, *(float *)(s + 0x68) * ((float)*(int *)(s + 0x7C) * 0.020000001f));
        mat_combine_and_store(s + 0x20, vec, obj + 0xF0, obj + 0xF0);
    }
    qcopy(vec, obj + 0x10);
    vec[3] = 10.0f;
    if (*(unsigned char *)(obj + 0x20) >= 2 && (*(unsigned char *)(obj + 0x31) || math_fast_helper_a(vec, 255.0f) != -1)) {
        if (*(int *)(s + 0x90) == -1) {
            *(int *)(s + 0x90) = part_l00_alloc_effect_slot_2(s + 0x80, 10.0f, 0.0f, blend * 0.8f, blend * 0.9f, blend * 1.1f);
        } else {
            char *light = g_dynamic_light_table + *(int *)(s + 0x90) * 32;
            *(float *)(light + 0) = blend * 0.8f;
            *(float *)(light + 4) = blend * 0.9f;
            *(float *)(light + 8) = blend * 1.1f;
        }
    } else if (*(int *)(s + 0x90) != -1) {
        gfx_free_point_light(*(int *)(s + 0x90));
        *(int *)(s + 0x90) = -1;
    }
}
