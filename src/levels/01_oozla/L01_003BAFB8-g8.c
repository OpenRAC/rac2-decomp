#include "common.h"

/*
 * Counterpart of RAC1's draw_pokitaru_ocean (homing_missile_and_water_sheet.c): a fading edge
 * strip, a far quad, and two scrolling layers of grid cells around the camera. As in RAC1, the
 * scroll table is declared in .sdata, so its address is one `la` macro instruction rather than a
 * split %hi/%lo pair; that makes the loop optimizer hoist both per-layer scroll pointers. This
 * unit needs -g for the measured division padding (docs/build/compiler-notes.md).
 */

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { float v[4]; Quadword q; } Vector;
typedef struct {
    int color0, color1, color2, color3, color4;
    float threshold, spacing;
    int texture;
    u32 unused;
    float altitude, depth;
} GridSettings;
typedef struct {
    Vector points[4];
    u32 colors[4];
    u32 zero[8];
    u64 state[4];
} SurfacePacket;
typedef struct { char prefix[0x2294]; int state; } WaterHero;
extern WaterHero g_hero_state;
extern int g_hero_l01_lock_flag __attribute__((section(".sdata")));
typedef struct { unsigned char prefix[0x228]; float scale0, scale1; } RenderScales;
extern RenderScales g_render_scales;
extern float g_water_view_matrix[16], g_level_origin_vec[4];
typedef struct { char prefix[0x140]; float pos[3]; } WaterCamera;
extern WaterCamera g_drive_settings;
extern float g_water_l01_height __attribute__((sda));
extern float g_wave_layer_uv_scales[2] __attribute__((sda));
typedef struct { float u, v; } WaterUV;
extern WaterUV g_water_uv_offsets[] __attribute__((section(".sdata")));
typedef struct { float x, y, z; } WaterPos;
extern WaterPos g_water_glint_positions_a[], g_water_glint_positions_b[];
extern u32 g_water_glint_colors_a[], g_water_glint_colors_b[];
extern WaterUV g_water_glint_uvs_a[], g_water_glint_uvs_b[];
extern void VU1_addGSregister(u32, u64);
extern unsigned long GetEffectTextureDescriptor(int);
extern void font_queue_vu_state(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);
extern int FastTweenColor(int, int, float);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
extern void draw_world_quad(void *, int, int);
extern float vec_length_xy(void *);
extern void math_trap_always(void);
/* Draws the ocean: a fading strip at the shore, a far-away sheet of water, and two moving layers of water tiles around the camera. */
void DrawWaterSheet(char *object)
{
    Vector point, scratch, right, up;
    Vector corners[4], along_left, along_right;
    SurfacePacket packet;
    GridSettings *settings = *(GridSettings **)(object + 0x68);
    float saved1, saved0;
    float x, y, t, factor;
    float grid_start;
    int i, layer, count, start;
    int color, lower_color, upper_color;
    saved0 = g_render_scales.scale0;
    saved1 = g_render_scales.scale1;
    if (g_hero_state.state != 28 && g_hero_l01_lock_flag == 0) {
        g_render_scales.scale0 = 255.0f;
        g_render_scales.scale1 = 249.9f;
    }
    VU1_addGSregister(0x42, 0x3200000044ULL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260ULL);
    VU1_addGSregister(0x47, 0x513F1);
    VU1_addGSregister(6, GetEffectTextureDescriptor(0x16));
    font_queue_vu_state();
    right.v[0] = 1.0f; right.v[1] = 0.0f;
    right.v[2] = 0.0f; right.v[3] = 1.0f;
    matrix_mul_vec3(&right, &right, g_water_view_matrix);
    up.v[0] = 0.0f; up.v[1] = 1.0f;
    up.v[2] = 0.0f; up.v[3] = 1.0f;
    matrix_mul_vec3(&up, &up, g_water_view_matrix);
    right.v[2] = 0.0f;
    vec_scale_to_length(&right, &right, 1.0f);
    up.v[2] = 0.0f;
    vec_scale_to_length(&up, &up, 1.0f);
    vec_scale_to_length(&point, &right, -75.0f);
    vec_scale_to_length(&scratch, &up, -87.0f);
    FastVecAdd(&corners[0], &point, &scratch);
    vec_scale_to_length(&scratch, &up, 87.0f);
    FastVecAdd(&corners[2], &point, &scratch);
    vec_scale_to_length(&point, &right, settings->depth);
    vec_scale_to_length(&scratch, &up, -750.0f);
    FastVecAdd(&corners[1], &point, &scratch);
    vec_scale_to_length(&scratch, &up, 750.0f);
    FastVecAdd(&corners[3], &point, &scratch);
    for (i = 0; i < 4; ++i) {
        FastVecAdd(&corners[i], &corners[i], g_level_origin_vec);
        corners[i].v[2] = g_water_l01_height;
    }
    FastVecSub(&along_left, &corners[1], &corners[0]);
    FastVecSub(&along_right, &corners[3], &corners[2]);
    t = 10.0f;
    for (i = 0; i < 12; i += 2) {
        factor = IntToFloat(i) * 0.1f;
        color = FastTweenColor(settings->color0, settings->color1, IntToFloat(i) / t);
        FastVecScale(&point, &along_left, factor);
        g_water_glint_colors_a[i] = color;
        g_water_glint_uvs_a[i].u = 0.0f;
        g_water_glint_uvs_a[i].v = 0.0f;
        FastVecAdd(&point, &point, &corners[0]);
        g_water_glint_positions_a[i].x = point.v[0];
        g_water_glint_positions_a[i].y = point.v[1];
        g_water_glint_positions_a[i].z = point.v[2];
        FastVecScale(&point, &along_right, factor);
        g_water_glint_colors_a[i+1] = color;
        g_water_glint_uvs_a[i+1].u = 0.0f;
        g_water_glint_uvs_a[i+1].v = 0.0f;
        FastVecAdd(&point, &point, &corners[2]);
        g_water_glint_positions_a[i+1].x = point.v[0];
        g_water_glint_positions_a[i+1].y = point.v[1];
        g_water_glint_positions_a[i+1].z = point.v[2];
    }
    part_draw_glint_effect(12, g_water_glint_positions_a, g_water_glint_colors_a, g_water_glint_uvs_a, 1);
    packet.state[1] = GetEffectTextureDescriptor(0x16);
    packet.state[2] = 0xFF9000000260ULL;
    packet.state[3] = 0x8000000044ULL;
    packet.state[0] = 0;
    if (settings->threshold < g_drive_settings.pos[2] - settings->altitude &&
        g_hero_state.state != 28 && g_hero_l01_lock_flag == 0) {
        packet.zero[0] = 0;
        packet.zero[1] = 0;
        packet.zero[2] = 0;
        packet.zero[3] = 0;
        packet.zero[4] = 0;
        packet.zero[5] = 0;
        packet.zero[6] = 0;
        packet.zero[7] = 0;
        packet.colors[0] = settings->color1;
        packet.colors[1] = settings->color2;
        packet.colors[2] = packet.colors[0];
        packet.colors[3] = packet.colors[1];
        packet.points[0].q = corners[1].q;
        packet.points[1].q = corners[1].q;
        packet.points[1].v[2] = g_drive_settings.pos[2] - settings->altitude;
        packet.points[2].q = corners[3].q;
        packet.points[3].q = corners[3].q;
        packet.points[3].v[2] = g_drive_settings.pos[2] - settings->altitude;
        draw_world_quad(&packet, 0, 0);
    }
    VU1_addGSregister(0x42, 0x8000000048ULL);
    VU1_addGSregister(8, 0);
    grid_start = -2.0f;
    VU1_addGSregister(0x14, 0xFF9000000260ULL);
    VU1_addGSregister(0x47, 0x513F0);
    lower_color = settings->color3;
    upper_color = settings->color4;
    t = 1.0f;
    lower_color = FastTweenColor(0, lower_color, t);
    upper_color = FastTweenColor(0, upper_color, t);
    for (layer = 0; layer < 2; ++layer) {
        int texture_id = layer + 0x3F;
        VU1_addGSregister(6, GetEffectTextureDescriptor(settings->texture + texture_id));
        for (y = settings->spacing * grid_start; y < settings->spacing * 2.0f;
             y += settings->spacing) {
            count = 0;
            for (x = settings->spacing * grid_start; x < settings->spacing * 2.0f;
                 x += settings->spacing) {
                start = count;
                g_water_glint_uvs_b[count].u = x / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].u;
                g_water_glint_uvs_b[count].v = y / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].v;
                g_water_glint_positions_b[count].x = x + g_drive_settings.pos[0] + 1.0f;
                g_water_glint_positions_b[count].y = y + g_drive_settings.pos[1] + 1.0f;
                g_water_glint_positions_b[count].z = g_water_l01_height;
                i = count + 1;
                g_water_glint_uvs_b[i].u = x / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].u;
                g_water_glint_uvs_b[i].v = (y + settings->spacing) / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].v;
                g_water_glint_positions_b[i].x = x + g_drive_settings.pos[0] + 1.0f;
                g_water_glint_positions_b[i].y = y + settings->spacing + g_drive_settings.pos[1] + 1.0f;
                g_water_glint_positions_b[i].z = g_water_l01_height;
                i = count + 2;
                g_water_glint_uvs_b[i].u = (x + settings->spacing) / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].u;
                g_water_glint_uvs_b[i].v = y / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].v;
                g_water_glint_positions_b[i].x = x + settings->spacing + g_drive_settings.pos[0] + 1.0f;
                g_water_glint_positions_b[i].y = y + g_drive_settings.pos[1] + 1.0f;
                g_water_glint_positions_b[i].z = g_water_l01_height;
                i = count + 3;
                g_water_glint_uvs_b[i].u = (x + settings->spacing) / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].u;
                g_water_glint_uvs_b[i].v = (y + settings->spacing) / (settings->spacing * 2.0f) * g_wave_layer_uv_scales[layer] + g_water_uv_offsets[layer].v;
                g_water_glint_positions_b[i].x = x + settings->spacing + g_drive_settings.pos[0] + 1.0f;
                g_water_glint_positions_b[i].y = y + settings->spacing + g_drive_settings.pos[1] + 1.0f;
                g_water_glint_positions_b[i].z = g_water_l01_height;
                for (i = start; i < start + 4; ++i) {
                    point.v[0] = g_water_glint_positions_b[i].x - g_drive_settings.pos[0];
                    point.v[1] = g_water_glint_positions_b[i].y - g_drive_settings.pos[1];
                    point.v[2] = g_water_glint_positions_b[i].z - g_drive_settings.pos[2];
                    point.v[3] = 1.0f;
                    t = vec_length_xy(&point) / (settings->spacing * 2.0f);
                    if (t > 1.0f) t = 1.0f;
                    g_water_glint_colors_b[i] = FastTweenColor(lower_color, upper_color, t);
                }
                count += 4;
                if (count >= 64) math_trap_always();
            }
            part_draw_glint_effect(count, g_water_glint_positions_b, g_water_glint_colors_b, g_water_glint_uvs_b, 1);
        }
    }
    g_render_scales.scale0 = saved0; g_render_scales.scale1 = saved1;
    VU1_addGSregister(0x47, 0x5360A);
}
