#include "common.h"
typedef struct { float x, y; } WaveUV;
typedef struct { WaveUV p[2]; } WaveRates;
extern int g_water_ripple_vertex_counts[2] __attribute__((sda));
extern float *g_water_ripple_positions[2] __attribute__((sda));
extern float *g_water_ripple_uvs[2] __attribute__((sda));
extern unsigned int *g_water_ripple_colors[2] __attribute__((sda));
extern float *g_water_ripple_base_vertices[2] __attribute__((sda));
extern float *g_water_ripple_base_uvs[2] __attribute__((sda));
extern int g_water_gs_register_value __attribute__((sda));
extern int g_water_effect_texture __attribute__((sda));
extern int g_water_alpha __attribute__((sda));
extern float g_water_wave_segment_count __attribute__((sda));
extern float g_water_ripple_segment_count __attribute__((sda));
extern float g_water_wave_height __attribute__((sda));
extern float g_water_time_scale __attribute__((sda));
extern WaveRates g_water_wave_rates __attribute__((nosda));
extern int g_game_tick_counter MACRO_ADDR;
extern float IntToFloat(int);
extern u64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int, u64);
extern float FastAddRotations(float, float);
extern void get_moby_color(void *, int *, int *, int *);
extern float square_root(float);
extern float fast_fmod(float, float);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_b(float);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
/* Draws the rippling water surface around the object, with waves that move up and down and a texture that scrolls. */
void water_draw_ripple_surface(char *moby)
{
    float *ripple = *(float **)(moby + 0x68);
    float time;
    int red, green, blue;
    int colour;
    int group, i, uv_group, uv_i, draw_group;

    time = (IntToFloat(g_game_tick_counter) * (1.0f/60.0f)) * g_water_time_scale;
    VU1_addGSregister(6,GetEffectTextureDescriptor(g_water_effect_texture));
    VU1_addGSregister(0x42, ((u64)g_water_gs_register_value<<32)|0x44);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260ULL);
    {
        float delta = 360.0f / g_water_ripple_segment_count;
        ripple[0] = ripple[1];
        ripple[1] = FastAddRotations(ripple[1], delta * 0.000290888245f);
    }
    get_moby_color(moby, &red, &green, &blue);
    {
        int high = (g_water_alpha << 24) | (blue << 16);
        int rgb = high | (green << 8);
        colour = rgb | red;
    }
    for (group = 0; group < 2; group++) {
        for (i = 0; i < g_water_ripple_vertex_counts[group]; i++) {
            float *v = &g_water_ripple_base_vertices[group][i * 3];
            float wave = math_fast_sin_or_cos_b(FastAddRotations(
                math_fast_float_g((fast_fmod(
                    square_root(v[0] * v[0] + v[1] * v[1]),
                    g_water_wave_segment_count) * 6.28318596f) / g_water_wave_segment_count),
                ripple[1]));
            float height = g_water_wave_height * wave;
            g_water_ripple_positions[group][i * 3] = v[0] + *(float *)(moby + 0x10);
            g_water_ripple_positions[group][i * 3 + 1] = v[1] + *(float *)(moby + 0x14);
            g_water_ripple_positions[group][i * 3 + 2] = (v[2] + *(float *)(moby + 0x18)) + height;
            g_water_ripple_colors[group][i] = colour;
        }
    }
    for (group = 0; group < 2; group++) {
        for (uv_group = 0; uv_group < 2; uv_group++) {
            for (uv_i = 0; uv_i < g_water_ripple_vertex_counts[uv_group]; uv_i++) {
                WaveRates rates = g_water_wave_rates;
                g_water_ripple_uvs[uv_group][uv_i*2]=g_water_ripple_base_uvs[uv_group][uv_i*2]+fast_fmod(time*rates.p[group].x,1.0f);
                g_water_ripple_uvs[uv_group][uv_i*2+1]=g_water_ripple_base_uvs[uv_group][uv_i*2+1]+fast_fmod(time*rates.p[group].y,1.0f);
            }
        }
        font_queue_vu_state();
        for (draw_group = 0; draw_group < 2; draw_group++)
            part_draw_glint_effect(g_water_ripple_vertex_counts[draw_group],g_water_ripple_positions[draw_group],g_water_ripple_colors[draw_group],g_water_ripple_uvs[draw_group],1);
    }
}
