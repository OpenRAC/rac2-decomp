#include "common.h"
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern int func_002A77E0(int);
extern u8 D_L12_001B9E00[];
extern void func_00282CF0(void *,void *,void *),func_00283098(void *,void *,void *);
extern float D_L12_001B12C4 __attribute__((sda)),D_L12_001B12C8 __attribute__((sda)),D_L12_001B12CC __attribute__((sda)),D_L12_001B12D0 __attribute__((sda));
extern u8 D_L12_001B12D4 __attribute__((sda));
extern int D_L12_001B12D8 __attribute__((sda)),D_L12_001B12DC __attribute__((sda));
extern float D_L12_001B12E0 __attribute__((sda)),D_L12_001B12E4 __attribute__((sda));
extern int D_L12_001B12E8 __attribute__((sda)),D_L12_001B12EC __attribute__((sda));
extern float D_L12_001B12F0 __attribute__((sda)),D_L12_001B12F4 __attribute__((sda));
extern int D_L12_001B12F8 __attribute__((sda)),D_L12_001B12FC __attribute__((sda));
extern float D_L12_001B1300[4] __attribute__((sda));
extern int D_L12_001B29C8 MACRO_ADDR;
extern void func_002A7A00(void *,float,float);
extern void func_002C3150(void *,void *,int,int,int,int,float);
extern float func_00283CE0(int),func_00282C48(float);
extern int func_00283D38(int,int,float);
extern void func_002C2FD8(void *,int,int,int,int,int,int,float);
extern void func_00282E70(void *,void *,void *);

void func_L12_00402B48(u8 *o) {
    float pos[4], v[4], delta[4], toward[4], step[4];
    int i, j;

    func_00282E70(pos, D_L12_001B1300, o + 0xC0);
    FastVecAdd(pos, pos, o + 0x10);
    if (!func_002A77E0(4)) {
        func_002A7A00(v, D_L12_001B12C4 * 0.0166666675f,
                     D_L12_001B12C8 * 0.0166666675f);
        func_002C3150(pos, v, D_L12_001B12D8, D_L12_001B12D4,
                     (u8)func_002A77E0(255), 0, D_L12_001B12E0);
        for (j = 2; j >= 0; j--) {
            func_002A7A00(delta, D_L12_001B12CC * 0.0166666675f,
                         D_L12_001B12D0 * 0.0166666675f);
            FastVecAdd(v, v, delta);
            func_002C3150(pos, v, D_L12_001B12DC, D_L12_001B12D4,
                         (u8)func_002A77E0(255), 0, D_L12_001B12E4);
        }
    }
    FastVecSub(toward, D_L12_001B9E00, pos);
    vec_scale_to_length(toward, toward, -0.3f);
    vec_scale_to_length(step, toward, 0.1f);
    FastVecAdd(toward, toward, pos);
    for (i = 0; i < 4; i++) {
        int color, alpha;

        color = FastTweenColor(D_L12_001B12E8, D_L12_001B12EC,
            func_00282C48(0.5f - IntToFloat(
                255 - ((D_L12_001B29C8 + i * 20) & 255)) * 0.00392156886f));
        alpha = *(u8 *)&D_L12_001B29C8;
        if (i & 2) alpha *= 2;
        if (i & 1) alpha = 255 - alpha;
        func_002C2FD8(toward, color, (u8)alpha, D_L12_001B12FC,
                     D_L12_001B12F8, 2, 0,
                     (D_L12_001B12F0 + IntToFloat(i) * D_L12_001B12F4) *
                     (*(float *)(o + 0x2C) /
                      *(float *)(*(u8 **)(o + 0x24) + 0x24)));
        FastVecAdd(toward, toward, step);
    }
}
