#include "common.h"
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern int math_fast_float_d(void *);
extern void moby_set_byte_on_group(int, int);
extern void gfx_free_point_light(int);
typedef struct { char pad[0x30]; float position[4]; char rest[0x40]; } L01_003C9D00_PATH;
extern L01_003C9D00_PATH *g_swamp_patrol_positions;
extern char g_dynamic_light_table[];
extern float fast_vec_dist(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_helper_a(void *, float);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void DrawFiveLayerScrollingRibbons(void *);

/* Updates the scrolling ribbon moby. It fades in, stays for a while, fades out, and lights up its surroundings while it is visible. */
void scrolling_ribbon_update(char *moby)
{
    float vec[4];
    char *vars = *(char **)(moby + 0x68);
    float blend = 0.0f;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(vars + 0x90) = -1;
        *(int *)(vars + 0x5C) |= 4;
        *(float *)(vars + 0x70) = 0.0f;
        *(int *)(vars + 0x6C) = 0;
        *(float *)(vars + 0x74) = 0.0f;
        *(int *)(moby + 0x98) = 0;
        qcopy(vars + 0x80, moby + 0x10);
        *(float *)(vars + 0x98) = fast_vec_dist(g_swamp_patrol_positions[*(int *)(vars + 0x94)].position);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(unsigned char *)(moby + 0xBC)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        *(float *)(vars + 0x70) += 1.0f / *(float *)(vars + 0x60);
        if (*(float *)(vars + 0x70) > 1.0f) *(float *)(vars + 0x70) = 1.0f;
        else if (*(float *)(vars + 0x70) < 0.0f) *(float *)(vars + 0x70) = 0.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(*(float *)(vars + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(vars + 0x94) == -1) {
            vec_scale_to_length(vec, moby + 0xC0, blend * 10.0f);
            FastVecSub(moby + 0x10, vars + 0x80, vec);
        } else {
            FastVecSub(vec, g_swamp_patrol_positions[*(int *)(vars + 0x94)].position, vars + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(vars + 0x98) * blend);
            FastVecAdd(moby + 0x10, vars + 0x80, vec);
        }
        if (*(float *)(vars + 0x70) >= 1.0f) {
            *(int *)(vars + 0x6C) = *(int *)(vars + 0x64);
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        blend = 1.0f;
        if (math_fast_float_d(vars + 0x6C)) moby_set_state(moby, 4, -1);
        break;
    case 4:
        *(float *)(vars + 0x70) -= 1.0f / *(float *)(vars + 0x60);
        if (*(float *)(vars + 0x70) > 1.0f) *(float *)(vars + 0x70) = 1.0f;
        else if (*(float *)(vars + 0x70) < 0.0f) *(float *)(vars + 0x70) = 0.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(*(float *)(vars + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(vars + 0x94) == -1) {
            vec_scale_to_length(vec, moby + 0xC0, blend * 10.0f);
            FastVecSub(moby + 0x10, vars + 0x80, vec);
        } else {
            FastVecSub(vec, g_swamp_patrol_positions[*(int *)(vars + 0x94)].position, vars + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(vars + 0x98) * blend);
            FastVecAdd(moby + 0x10, vars + 0x80, vec);
        }
        if (*(float *)(vars + 0x70) <= 0.0f) {
            *(int *)(moby + 0x98) = 0;
            moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 0);
            moby_set_state(moby, 1, -1);
        }
        break;
    }
    *(unsigned char *)(moby + 0xBC) = 0;
    if ((unsigned int)(*(unsigned char *)(moby + 0x20) - 2) < 3) {
        gfx_add_draw_callback_first(DrawFiveLayerScrollingRibbons, moby);
        vec_scale_to_length(vec, moby + 0xC0, *(float *)(vars + 0x68) * ((float)*(int *)(vars + 0x7C) * 0.016666668f));
        mat_combine_and_store(vars + 0x20, vec, moby + 0xF0, moby + 0xF0);
    }
    qcopy(vec, moby + 0x10);
    vec[3] = 10.0f;
    if (*(unsigned char *)(moby + 0x20) >= 2 && (*(unsigned char *)(moby + 0x31) || math_fast_helper_a(vec, 255.0f) != -1)) {
        if (*(int *)(vars + 0x90) == -1) {
            *(int *)(vars + 0x90) = part_l00_alloc_effect_slot_2(vars + 0x80, 10.0f, 0.0f, blend * 0.8f, blend * 0.9f, blend * 1.1f);
        } else {
            char *light = g_dynamic_light_table + *(int *)(vars + 0x90) * 32;
            *(float *)(light + 0) = blend * 0.8f;
            *(float *)(light + 4) = blend * 0.9f;
            *(float *)(light + 8) = blend * 1.1f;
        }
    } else if (*(int *)(vars + 0x90) != -1) {
        gfx_free_point_light(*(int *)(vars + 0x90));
        *(int *)(vars + 0x90) = -1;
    }
}
