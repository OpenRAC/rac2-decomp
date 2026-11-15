/* func_PAL_L04_0040B078, the PAL copy of func_L04_00406C00: the same C, where the time step 1/60 becomes 0.02 and the D_L04_001B06F0 period is scaled to 50 Hz. */
#include "common.h"
typedef struct { float x, y; } WaveUV;
typedef struct { WaveUV p[2]; } WaveRates;
extern int D_L04_001B0680[2] __attribute__((sda));
extern float *D_L04_001B06B0[2] __attribute__((sda));
extern float *D_L04_001B06B8[2] __attribute__((sda));
extern unsigned int *D_L04_001B06C0[2] __attribute__((sda));
extern float *D_L04_001B06C8[2] __attribute__((sda));
extern float *D_L04_001B06D0[2] __attribute__((sda));
extern int D_L04_001B06E0 __attribute__((sda));
extern int D_L04_001B06E4 __attribute__((sda));
extern int D_L04_001B06E8 __attribute__((sda));
extern float D_L04_001B06EC __attribute__((sda));
extern float D_L04_001B06F0 __attribute__((sda));
extern float D_L04_001B06F4 __attribute__((sda));
extern float D_L04_001B06F8 __attribute__((sda));
extern WaveRates D_L04_001B0700 __attribute__((nosda));
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
void func_PAL_L04_0040B078(char *object)
{
    float *state = *(float **)(object + 0x68);
    float time;
    int red, green, blue;
    int colour;
    int group, i, uv_group, uv_i, draw_group;

    time = (IntToFloat(D_L04_001B2008) * 0.020000001f) * D_L04_001B06F8;
    VU1_addGSregister(6,GetEffectTextureDescriptor(D_L04_001B06E4));
    VU1_addGSregister(0x42, ((u64)D_L04_001B06E0<<32)|0x44);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260ULL);
    {
        float delta = 360.0f / ((D_L04_001B06F0 * 5.0f + 2.0f) * 0.16666667f);
        state[0] = state[1];
        state[1] = FastAddRotations(state[1], delta * 0.0003490659f);
    }
    get_moby_color(object, &red, &green, &blue);
    {
        int high = (D_L04_001B06E8 << 24) | (blue << 16);
        int rgb = high | (green << 8);
        colour = rgb | red;
    }
    for (group = 0; group < 2; group++) {
        for (i = 0; i < D_L04_001B0680[group]; i++) {
            float *v = &D_L04_001B06C8[group][i * 3];
            float wave = math_fast_sin_or_cos_b(FastAddRotations(
                math_fast_float_g((fast_fmod(
                    square_root(v[0] * v[0] + v[1] * v[1]),
                    D_L04_001B06EC) * 6.28318596f) / D_L04_001B06EC),
                state[1]));
            float height = D_L04_001B06F4 * wave;
            D_L04_001B06B0[group][i * 3] = v[0] + *(float *)(object + 0x10);
            D_L04_001B06B0[group][i * 3 + 1] = v[1] + *(float *)(object + 0x14);
            D_L04_001B06B0[group][i * 3 + 2] = (v[2] + *(float *)(object + 0x18)) + height;
            D_L04_001B06C0[group][i] = colour;
        }
    }
    for (group = 0; group < 2; group++) {
        for (uv_group = 0; uv_group < 2; uv_group++) {
            for (uv_i = 0; uv_i < D_L04_001B0680[uv_group]; uv_i++) {
                WaveRates rates = D_L04_001B0700;
                D_L04_001B06B8[uv_group][uv_i*2]=D_L04_001B06D0[uv_group][uv_i*2]+fast_fmod(time*rates.p[group].x,1.0f);
                D_L04_001B06B8[uv_group][uv_i*2+1]=D_L04_001B06D0[uv_group][uv_i*2+1]+fast_fmod(time*rates.p[group].y,1.0f);
            }
        }
        font_queue_vu_state();
        for (draw_group = 0; draw_group < 2; draw_group++)
            part_draw_glint_effect(D_L04_001B0680[draw_group],D_L04_001B06B0[draw_group],D_L04_001B06C0[draw_group],D_L04_001B06B8[draw_group],1);
    }
}
