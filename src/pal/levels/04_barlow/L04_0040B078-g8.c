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
void func_PAL_L04_0040B078(char *object)
{
    float *state = *(float **)(object + 0x68);
    float time;
    int red, green, blue;
    int colour;
    int group, i, uv_group, uv_i, draw_group;

    time = (func_00283CE0(D_L04_001B2008) * 0.020000001f) * D_L04_001B06F8;
    func_002FC560(6,func_0027C878(D_L04_001B06E4));
    func_002FC560(0x42, ((u64)D_L04_001B06E0<<32)|0x44);
    func_002FC560(8,0);
    func_002FC560(0x14,0xFF9000000260ULL);
    {
        float delta = 360.0f / ((D_L04_001B06F0 * 5.0f + 2.0f) * 0.16666667f);
        state[0] = state[1];
        state[1] = func_00283B98(state[1], delta * 0.0003490659f);
    }
    func_002A04B8(object, &red, &green, &blue);
    {
        int high = (D_L04_001B06E8 << 24) | (blue << 16);
        int rgb = high | (green << 8);
        colour = rgb | red;
    }
    for (group = 0; group < 2; group++) {
        for (i = 0; i < D_L04_001B0680[group]; i++) {
            float *v = &D_L04_001B06C8[group][i * 3];
            float wave = func_00283198(func_00283B98(
                func_00283C28((func_00283D00(
                    func_00282C10(v[0] * v[0] + v[1] * v[1]),
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
                D_L04_001B06B8[uv_group][uv_i*2]=D_L04_001B06D0[uv_group][uv_i*2]+func_00283D00(time*rates.p[group].x,1.0f);
                D_L04_001B06B8[uv_group][uv_i*2+1]=D_L04_001B06D0[uv_group][uv_i*2+1]+func_00283D00(time*rates.p[group].y,1.0f);
            }
        }
        func_00280328();
        for (draw_group = 0; draw_group < 2; draw_group++)
            func_00281810(D_L04_001B0680[draw_group],D_L04_001B06B0[draw_group],D_L04_001B06C0[draw_group],D_L04_001B06B8[draw_group],1);
    }
}
