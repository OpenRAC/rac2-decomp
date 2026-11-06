/* func_PAL_L04_0040C050, the PAL copy of func_L04_00407B80: the same C, where the 1/60 time step becomes
   0.020000001f, the wave rate is scaled to 50 Hz as (x * 5 + 2) / 6, and the phase factor grows by 6/5. */
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
extern float func_00283CE0(int);
extern u64 func_0027C878(int);
extern void func_002FC560(int, u64);
extern float func_00283B98(float, float);
extern void func_002A04B8(void *, int *, int *, int *);
extern float func_00282C10(float);
extern float func_00283D00(float, float);
extern float func_00283C28(float);
extern float func_00283198(float);
extern void func_00280328(void);
extern void func_00281810(int, void *, void *, void *, int);
void func_PAL_L04_0040C050(char *object)
{
    float *state = *(float **)(object + 0x68);
    float time;
    int red, green, blue;
    int colour;
    int group, i, uv_group, uv_i, draw_group;

    time = (func_00283CE0(D_L04_001B2008) * 0.020000001f) * D_L04_001B0798;
    func_002FC560(6,func_0027C878(D_L04_001B0784));
    func_002FC560(0x42, ((u64)D_L04_001B0780<<32)|0x44);
    func_002FC560(8,0);
    func_002FC560(0x14,0xFF9000000260ULL);
    {
        float delta = 360.0f / ((D_L04_001B0790 * 5.0f + 2.0f) * 0.16666667f);
        state[0] = state[1];
        state[1] = func_00283B98(state[1], delta * 0.0003490659f);
    }
    func_002A04B8(object, &red, &green, &blue);
    {
        int high = (D_L04_001B0788 << 24) | (blue << 16);
        int rgb = high | (green << 8);
        colour = rgb | red;
    }
    for (group = 0; group < 2; group++) {
        for (i = 0; i < D_L04_001B0720[group]; i++) {
            float *v = &D_L04_001B0768[group][i * 3];
            float wave = func_00283198(func_00283B98(
                func_00283C28((func_00283D00(
                    func_00282C10(v[0] * v[0] + v[1] * v[1]),
                    D_L04_001B078C) * 6.28318596f) / D_L04_001B078C),
                state[1]));
            float height = D_L04_001B0794 * wave;
            D_L04_001B0750[group][i * 3] = v[0] + *(float *)(object + 0x10);
            D_L04_001B0750[group][i * 3 + 1] = v[1] + *(float *)(object + 0x14);
            D_L04_001B0750[group][i * 3 + 2] = (v[2] + *(float *)(object + 0x18)) + height;
            D_L04_001B0760[group][i] = colour;
        }
    }
    for (group = 0; group < 2; group++) {
        for (uv_group = 0; uv_group < 2; uv_group++) {
            for (uv_i = 0; uv_i < D_L04_001B0720[uv_group]; uv_i++) {
                WaveRates rates = D_L04_001B07A0;
                D_L04_001B0758[uv_group][uv_i*2]=D_L04_001B0770[uv_group][uv_i*2]+func_00283D00(time*rates.p[group].x,1.0f);
                D_L04_001B0758[uv_group][uv_i*2+1]=D_L04_001B0770[uv_group][uv_i*2+1]+func_00283D00(time*rates.p[group].y,1.0f);
            }
        }
        func_00280328();
        for (draw_group = 0; draw_group < 2; draw_group++)
            func_00281810(D_L04_001B0720[draw_group],D_L04_001B0750[draw_group],D_L04_001B0760[draw_group],D_L04_001B0758[draw_group],1);
    }
}
