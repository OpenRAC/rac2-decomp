#include "common.h"

typedef struct { char pad[0x228]; float f228, f22C; } WaterFog;
typedef struct { char pad0[0x348]; short f348; char pad34A[0x1F4A]; int currentState; } WaterHero;
typedef struct { char pad[0x140]; float x, y, z; } WaterCamera;
typedef struct {
    int color0, color1, color2, color3, color4;
    float f14, range;
    int texture;
    int f20;
    float f24, reach, f2C;
} WaterState;

extern WaterFog g_water_fog;
extern WaterHero g_hero_state;
extern WaterCamera g_camera_state;
extern int g_hero_l06_override_flag MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern float g_water_axes_matrix[3][4] __attribute__((sda));
extern float g_water_basis_matrix[][4];
extern float g_water_surface_height MACRO_ADDR;
extern float g_ocean_layer_scales[] SDATA(D_L06_001B0060);
extern float g_water_layer_offsets[][2] MACRO_ADDR;
extern float g_glint_edge_positions[][3], g_glint_cell_positions[][3];
extern int g_glint_edge_colors[], g_glint_cell_colors[];
extern float g_glint_edge_uvs[][2], g_glint_cell_uvs[][2];

extern void VU1_addGSregister(int, unsigned long);
extern unsigned long GetEffectTextureDescriptor(int);
extern void font_queue_vu_state(void);
extern void FastVecCross(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern int FastTweenColor(int, int, float);
extern void FastVecScale(void *, void *, float);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
extern float vec_length_xy(void *);
extern void math_trap_always(void);

/* Draws the level's water sheet: a fading edge strip and two scrolling layers of grid cells
 * around the camera. RAC1's draw_pokitaru_ocean is its counterpart. */
void DrawOceanWaterSheet(unsigned char *owner)
{
    float edge_start[4], edge_offset[4], axis_x[4], axis_y[4], corner[4][4], top_edge[4], bottom_edge[4];
    WaterState *state;
    int layer;
    float saved22C;
    float saved228;
    int i, count, color;
    int near_color, far_color;
    float range, height_above_water, wave_lift, cell_x, cell_y, blend;

    saved228 = g_water_fog.f228;
    state = *(WaterState **)(owner + 0x68);
    saved22C = g_water_fog.f22C;
    if (g_hero_state.currentState != 28 && !g_hero_l06_override_flag) {
        g_water_fog.f228 = 255.0f;
        g_water_fog.f22C = 249.9f;
    }
    VU1_addGSregister(0x42, 0x3200000044UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    if (state->color0 < 0)
        VU1_addGSregister(0x47, 0x5310B);
    else
        VU1_addGSregister(0x47, 0x513F1);
    VU1_addGSregister(6, GetEffectTextureDescriptor(22));
    font_queue_vu_state();
    if (g_current_map_index == 13 || (g_current_map_index == 16 && g_hero_state.f348 == 1)) {
        qcopy(g_water_axes_matrix[1], g_water_basis_matrix[1]);
        g_water_axes_matrix[2][0] = 0;
        g_water_axes_matrix[2][1] = 0;
        g_water_axes_matrix[2][2] = 1;
        g_water_axes_matrix[2][3] = 0;
        FastVecCross(g_water_axes_matrix[0], g_water_axes_matrix[2], g_water_axes_matrix[1]);
        axis_x[0] = 1;
        axis_x[1] = 0;
        axis_x[2] = 0;
        axis_x[3] = 1;
        matrix_mul_vec3(axis_x, axis_x, g_water_axes_matrix);
        axis_y[0] = 0;
        axis_y[1] = 1;
        axis_y[2] = 0;
        axis_y[3] = 1;
        matrix_mul_vec3(axis_y, axis_y, g_water_axes_matrix);
    } else {
        axis_x[0] = 1;
        axis_x[1] = 0;
        axis_x[2] = 0;
        axis_x[3] = 1;
        matrix_mul_vec3(axis_x, axis_x, g_water_basis_matrix);
        axis_y[0] = 0;
        axis_y[1] = 1;
        axis_y[2] = 0;
        axis_y[3] = 1;
        matrix_mul_vec3(axis_y, axis_y, g_water_basis_matrix);
    }
    if (g_current_map_index != 16) {
        axis_x[2] = 0;
        vec_scale_to_length(axis_x, axis_x, 1);
        axis_y[2] = 0;
        vec_scale_to_length(axis_y, axis_y, 1);
    } else if (g_hero_state.f348 == 1) {
        axis_x[0] = 0;
        axis_x[1] = 1;
        axis_x[2] = 0;
        axis_x[3] = 1;
        axis_y[0] = -0.79706f;
        axis_y[1] = 0;
        axis_y[2] = -0.60389f;
        axis_y[3] = 1.00405f;
    }
    if (g_current_map_index != 16) {
        vec_scale_to_length(edge_start, axis_x, -75);
        vec_scale_to_length(edge_offset, axis_y, -87);
        FastVecAdd(corner[0], edge_start, edge_offset);
        vec_scale_to_length(edge_offset, axis_y, 87);
        FastVecAdd(corner[2], edge_start, edge_offset);
        vec_scale_to_length(edge_start, axis_x, state->reach);
        vec_scale_to_length(edge_offset, axis_y, -750);
        FastVecAdd(corner[1], edge_start, edge_offset);
        vec_scale_to_length(edge_offset, axis_y, 750);
        FastVecAdd(corner[3], edge_start, edge_offset);
    } else {
        vec_scale_to_length(edge_start, axis_x, -150);
        vec_scale_to_length(edge_offset, axis_y, -175);
        FastVecAdd(corner[0], edge_start, edge_offset);
        vec_scale_to_length(edge_offset, axis_y, 175);
        FastVecAdd(corner[2], edge_start, edge_offset);
        vec_scale_to_length(edge_start, axis_x, state->reach);
        vec_scale_to_length(edge_offset, axis_y, -1500);
        FastVecAdd(corner[1], edge_start, edge_offset);
        vec_scale_to_length(edge_offset, axis_y, 1500);
        FastVecAdd(corner[3], edge_start, edge_offset);
    }
    for (i = 0; i < 4; i++) {
        float *corner_point = corner[i];
        FastVecAdd(corner_point, corner_point, &g_camera_state.x);
        corner_point[2] = g_water_surface_height;
    }
    FastVecSub(top_edge, corner[1], corner[0]);
    FastVecSub(bottom_edge, corner[3], corner[2]);
    blend = 10;
    for (i = 0; i < 12; i += 2) {
        float fraction = IntToFloat(i) * 0.1f;
        color = FastTweenColor(state->color0, state->color1, IntToFloat(i) / blend);
        FastVecScale(edge_start, top_edge, fraction);
        g_glint_edge_colors[i] = color;
        g_glint_edge_uvs[i][0] = 0;
        g_glint_edge_uvs[i][1] = 0;
        FastVecAdd(edge_start, edge_start, corner[0]);
        g_glint_edge_positions[i][0] = edge_start[0];
        g_glint_edge_positions[i][1] = edge_start[1];
        g_glint_edge_positions[i][2] = edge_start[2];
        FastVecScale(edge_start, bottom_edge, fraction);
        g_glint_edge_colors[i + 1] = color;
        g_glint_edge_uvs[i + 1][0] = 0;
        g_glint_edge_uvs[i + 1][1] = 0;
        FastVecAdd(edge_start, edge_start, corner[2]);
        g_glint_edge_positions[i + 1][0] = edge_start[0];
        g_glint_edge_positions[i + 1][1] = edge_start[1];
        g_glint_edge_positions[i + 1][2] = edge_start[2];
    }
    part_draw_glint_effect(12, g_glint_edge_positions, g_glint_edge_colors, g_glint_edge_uvs, 1);
    VU1_addGSregister(0x42, 0x8000000048UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x47, 0x513F1);
    near_color = state->color3;
    far_color = state->color4;
    range = state->range;
    if (g_hero_state.currentState == 28 || g_hero_l06_override_flag) {
        if (range > 32)
            range = 32;
    }

    for (layer = 0; layer < 2; layer++) {
        int texture_offset = layer + 63;
        VU1_addGSregister(6, GetEffectTextureDescriptor(state->texture + texture_offset));
        for (cell_y = range * -2; cell_y < range * 2; cell_y += range) {
            count = 0;
            height_above_water = g_camera_state.z - g_water_surface_height;
            if (height_above_water < 10)
                height_above_water = 10;
            wave_lift = height_above_water * range * 0.00002f;
            if (wave_lift < 0.125f)
                wave_lift = 0.125f;
            for (cell_x = range * -2; cell_x < range * 2; cell_x += range) {
                g_glint_cell_uvs[count][0] = cell_x / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][0];
                g_glint_cell_uvs[count][1] = cell_y / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][1];
                g_glint_cell_positions[count][0] = cell_x + g_camera_state.x + 1;
                g_glint_cell_positions[count][1] = cell_y + g_camera_state.y + 1;
                g_glint_cell_positions[count][2] = g_water_surface_height + wave_lift;
                i = count + 1;
                g_glint_cell_uvs[i][0] = cell_x / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][0];
                g_glint_cell_uvs[i][1] = (cell_y + range) / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][1];
                g_glint_cell_positions[i][0] = cell_x + g_camera_state.x + 1;
                g_glint_cell_positions[i][1] = (cell_y + range) + g_camera_state.y + 1;
                g_glint_cell_positions[i][2] = g_water_surface_height + wave_lift;
                i = count + 2;
                g_glint_cell_uvs[i][0] = (cell_x + range) / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][0];
                g_glint_cell_uvs[i][1] = cell_y / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][1];
                g_glint_cell_positions[i][0] = (cell_x + range) + g_camera_state.x + 1;
                g_glint_cell_positions[i][1] = cell_y + g_camera_state.y + 1;
                g_glint_cell_positions[i][2] = g_water_surface_height + wave_lift;
                i = count + 3;
                g_glint_cell_uvs[i][0] = (cell_x + range) / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][0];
                g_glint_cell_uvs[i][1] = (cell_y + range) / (range * 2) * g_ocean_layer_scales[layer] + g_water_layer_offsets[layer][1];
                g_glint_cell_positions[i][0] = (cell_x + range) + g_camera_state.x + 1;
                g_glint_cell_positions[i][1] = (cell_y + range) + g_camera_state.y + 1;
                g_glint_cell_positions[i][2] = g_water_surface_height + wave_lift;
                for (i = count; i < count + 4; i++) {
                    edge_start[0] = g_glint_cell_positions[i][0] - g_camera_state.x;
                    edge_start[1] = g_glint_cell_positions[i][1] - g_camera_state.y;
                    edge_start[2] = g_glint_cell_positions[i][2] - g_camera_state.z;
                    edge_start[3] = 1;
                    blend = vec_length_xy(edge_start) / (range * 2);
                    if (blend > 1)
                        blend = 1;
                    g_glint_cell_colors[i] = FastTweenColor(near_color, far_color, blend);
                }
                count += 4;
                if (count >= 64)
                    math_trap_always();
            }
            part_draw_glint_effect(count, g_glint_cell_positions, g_glint_cell_colors, g_glint_cell_uvs, 1);
        }
    }
    g_water_fog.f228 = saved228;
    g_water_fog.f22C = saved22C;
    VU1_addGSregister(0x47, 0x5360B);
}
