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
extern char D_L01_001B94C0[];
extern int ref_L01_00397A28_00 __attribute__((sda));
extern int ref_L01_00397A28_01 __attribute__((sda));
extern int ref_L01_00397A28_02 __attribute__((sda));
extern int ref_L01_00397A28_03 __attribute__((sda));
/* Draws four pulsing glow rings between the moby and camera, fading with distance.
 * Adapted from RAC1 update_gold_bolt_glow_rings (GPL-3.0). */
void part_draw_bolt_glow_rings(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float ring_pos[4], moby_pos[4], ring_step[4];
    float scale = 1.0f;
    int i;
    float *phase, *speed, *size;
    int *timer;
    if (*(unsigned char *)(moby + 0x20) == 1)
        FastVecScale(moby_pos, moby, 0.0009765625f);
    else {
        moby_transform_joint_to_world(moby, 0, moby_pos);
        scale = (160.0f - moby_get_anim_value(moby)) * 0.1f;
        if (scale > 1.0f) scale = 1.0f;
    }
    FastVecSub(ring_pos, D_L01_001B94C0, moby_pos);
    vec_scale_to_length(ring_pos, ring_pos, -0.3f);
    vec_scale_to_length(ring_step, ring_pos, 0.1f);
    FastVecAdd(ring_pos, ring_pos, moby_pos);
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
        if (math_fast_float_d((int *)(vars + 0x40) + i)) timer[i] = 255;
        t = IntToFloat(255 - timer[i]) * 0.003921568859368563f;
        color = FastTweenColor(ref_L01_00397A28_00, ref_L01_00397A28_01,
            math_fabs(0.5f - t));
        part_spawn_fading(ring_pos, color, (unsigned char)FloatToInt(phase[i]), ref_L01_00397A28_03,
            ref_L01_00397A28_02, 2, 0, size[i] * scale);
        FastVecAdd(ring_pos, ring_pos, ring_step);
    }
}
