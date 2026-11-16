#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float moby_get_anim_value(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);
extern char g_level_origin_vec[];
extern int ref_L01_00397A28_00 __attribute__((sda));
extern int ref_L01_00397A28_01 __attribute__((sda));
extern int ref_L01_00397A28_02 __attribute__((sda));
extern int ref_L01_00397A28_03 __attribute__((sda));

/* Draws four pulsing glow rings between the moby and camera, fading with distance.
 * Adapted from RAC1 update_gold_bolt_glow_rings (GPL-3.0). */
void func_PAL_L01_0039AE48(char *m) {
    char *d = *(char **)(m + 0x68);
    float a[4], b[4], c[4];
    float scale = 1.0f;
    int i;
    float *phase, *speed, *size;
    int *timer;
    if (*(unsigned char *)(m + 0x20) == 1)
        FastVecScale(b, m, 0.0009765625f);
    else {
        moby_transform_joint_to_world(m, 0, b);
        scale = (160.0f - moby_get_anim_value(m)) * 0.1f;
        if (scale > 1.0f) scale = 1.0f;
    }
    FastVecSub(a, g_level_origin_vec, b);
    vec_scale_to_length(a, a, -0.3f);
    vec_scale_to_length(c, a, 0.1f);
    FastVecAdd(a, a, b);
    phase = (float *)(d + 0x20);
    speed = (float *)(d + 0x30);
    timer = (int *)(d + 0x40);
    size = (float *)(d + 0x50);
    for (i = 0; i < 4; i++) {
        float value = phase[i] + speed[i];
        float t;
        int color;
        phase[i] = value;
        if (255.0f <= value) phase[i] = value - 255.0f;
        else if (value <= 0.0f) phase[i] = value + 255.0f;
        if (math_fast_float_d((int *)(d + 0x40) + i)) timer[i] = 212;
        t = IntToFloat(212 - timer[i]) * 0.004716981f;
        color = FastTweenColor(ref_L01_00397A28_00, ref_L01_00397A28_01,
            math_fabs(0.5f - t));
        part_spawn_fading(a, color, (unsigned char)FloatToInt(phase[i]), ref_L01_00397A28_03,
            ref_L01_00397A28_02, 2, 0, size[i] * scale);
        FastVecAdd(a, a, c);
    }
}
