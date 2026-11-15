#include "common.h"

extern void func_00282D30(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern float func_0029F530(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern unsigned char *func_002C2FD8(void *, int, unsigned char, int, int, int, int, float);
extern char D_L01_001B94C0[];
extern int ref_L01_00397A28_00 __attribute__((sda));
extern int ref_L01_00397A28_01 __attribute__((sda));
extern int ref_L01_00397A28_02 __attribute__((sda));
extern int ref_L01_00397A28_03 __attribute__((sda));
/* Draws four pulsing glow rings between the moby and camera, fading with distance.
 * Adapted from RAC1 update_gold_bolt_glow_rings (GPL-3.0). */
void func_L01_00397A28(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float ringPos[4], mobyPos[4], ringStep[4];
    float scale = 1.0f;
    int i;
    float *phase, *speed, *size;
    int *timer;
    if (*(unsigned char *)(moby + 0x20) == 1)
        FastVecScale(mobyPos, moby, 0.0009765625f);
    else {
        TransformMobyJointToWorld(moby, 0, mobyPos);
        scale = (160.0f - GetMobyAnimationValue(moby)) * 0.1f;
        if (scale > 1.0f) scale = 1.0f;
    }
    FastVecSub(ringPos, D_L01_001B94C0, mobyPos);
    vec_scale_to_length(ringPos, ringPos, -0.3f);
    vec_scale_to_length(ringStep, ringPos, 0.1f);
    FastVecAdd(ringPos, ringPos, mobyPos);
    phase = (float *)(vars + 0x20);
    speed = (float *)(vars + 0x30);
    timer = (int *)(vars + 0x40);
    size = (float *)(vars + 0x50);
    for (i = 0; i < 4; i++) {
        float value = phase[i] + speed[i];
        float t;
        int color;
        phase[i] = value;
        if (255.0f <= value) phase[i] = value - 255.0f;
        else if (value <= 0.0f) phase[i] = value + 255.0f;
        if (FastFloatHelperD((int *)(vars + 0x40) + i)) timer[i] = 255;
        t = IntToFloat(255 - timer[i]) * 0.003921568859368563f;
        color = FastTweenColor(ref_L01_00397A28_00, ref_L01_00397A28_01,
            FloatAbs(0.5f - t));
        SpawnFadingParticle_002C2FD8(ringPos, color, (unsigned char)FloatToInt(phase[i]), ref_L01_00397A28_03,
            ref_L01_00397A28_02, 2, 0, size[i] * scale);
        FastVecAdd(ringPos, ringPos, ringStep);
    }
}
