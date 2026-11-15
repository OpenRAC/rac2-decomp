#include "common.h"
typedef struct { float x, y; } WaveUV;
typedef struct { WaveUV p[2]; } WaveRates;
extern int D_L04_001B0720[2] __attribute__((sda));
extern float *D_L04_001B0750[2] __attribute__((sda));
extern float *D_L04_001B0758[2] __attribute__((sda));
extern unsigned int *D_L04_001B0760[2] __attribute__((sda));
extern float *D_L04_001B0768[2] __attribute__((sda));
extern float *D_L04_001B0770[2] __attribute__((sda));
extern int D_L04_001B0780 __attribute__((sda));
extern int D_L04_001B0784 __attribute__((sda));
extern int D_L04_001B0788 __attribute__((sda));
extern float D_L04_001B078C __attribute__((sda));
extern float D_L04_001B0790 __attribute__((sda));
extern float D_L04_001B0794 __attribute__((sda));
extern float D_L04_001B0798 __attribute__((sda));
extern WaveRates D_L04_001B07A0 __attribute__((nosda));
extern int D_L04_001B2008 MACRO_ADDR;
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
/* Draws a second rippling water surface around the object, with waves that move up and down and a texture that scrolls. */
void water_draw_ripple_surface_second(char *moby)
{
    float *ripple = *(float **)(moby + 0x68);
    float time;
    int red, green, blue;
    int colour;
    int group, i, uv_group, uv_i, draw_group;

    time = (IntToFloat(D_L04_001B2008) * (1.0f/60.0f)) * D_L04_001B0798;
    VU1_addGSregister(6,GetEffectTextureDescriptor(D_L04_001B0784));
    VU1_addGSregister(0x42, ((u64)D_L04_001B0780<<32)|0x44);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260ULL);
    {
        float delta = 360.0f / D_L04_001B0790;
        ripple[0] = ripple[1];
        ripple[1] = FastAddRotations(ripple[1], delta * 0.000290888245f);
    }
    get_moby_color(moby, &red, &green, &blue);
    {
        int high = (D_L04_001B0788 << 24) | (blue << 16);
        int rgb = high | (green << 8);
        colour = rgb | red;
    }
    for (group = 0; group < 2; group++) {
        for (i = 0; i < D_L04_001B0720[group]; i++) {
            float *v = &D_L04_001B0768[group][i * 3];
            float wave = math_fast_sin_or_cos_b(FastAddRotations(
                math_fast_float_g((fast_fmod(
                    square_root(v[0] * v[0] + v[1] * v[1]),
                    D_L04_001B078C) * 6.28318596f) / D_L04_001B078C),
                ripple[1]));
            float height = D_L04_001B0794 * wave;
            D_L04_001B0750[group][i * 3] = v[0] + *(float *)(moby + 0x10);
            D_L04_001B0750[group][i * 3 + 1] = v[1] + *(float *)(moby + 0x14);
            D_L04_001B0750[group][i * 3 + 2] = (v[2] + *(float *)(moby + 0x18)) + height;
            D_L04_001B0760[group][i] = colour;
        }
    }
    for (group = 0; group < 2; group++) {
        for (uv_group = 0; uv_group < 2; uv_group++) {
            for (uv_i = 0; uv_i < D_L04_001B0720[uv_group]; uv_i++) {
                WaveRates rates = D_L04_001B07A0;
                D_L04_001B0758[uv_group][uv_i*2]=D_L04_001B0770[uv_group][uv_i*2]+fast_fmod(time*rates.p[group].x,1.0f);
                D_L04_001B0758[uv_group][uv_i*2+1]=D_L04_001B0770[uv_group][uv_i*2+1]+fast_fmod(time*rates.p[group].y,1.0f);
            }
        }
        font_queue_vu_state();
        for (draw_group = 0; draw_group < 2; draw_group++)
            part_draw_glint_effect(D_L04_001B0720[draw_group],D_L04_001B0750[draw_group],D_L04_001B0760[draw_group],D_L04_001B0758[draw_group],1);
    }
}
