#include "include_asm.h"

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
void func_PAL_L01_0039AE48(char *m) {
    char *d = *(char **)(m + 0x68);
    float a[4], b[4], c[4];
    float scale = 1.0f;
    int i;
    float *phase, *speed, *size;
    int *timer;
    if (*(unsigned char *)(m + 0x20) == 1)
        func_00282D30(b, m, 0.0009765625f);
    else {
        func_0029FCC0(m, 0, b);
        scale = (160.0f - func_0029F530(m)) * 0.1f;
        if (scale > 1.0f) scale = 1.0f;
    }
    func_00282CF0(a, D_L01_001B94C0, b);
    func_00282F20(a, a, -0.3f);
    func_00282F20(c, a, 0.1f);
    func_00282CC0(a, a, b);
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
        if (func_00282948((int *)(d + 0x40) + i)) timer[i] = 212;
        t = func_00283CE0(212 - timer[i]) * 0.004716981f;
        color = func_00283D38(ref_L01_00397A28_00, ref_L01_00397A28_01,
            func_00282C48(0.5f - t));
        func_002C2FD8(a, color, (unsigned char)func_00283CF0(phase[i]), ref_L01_00397A28_03,
            ref_L01_00397A28_02, 2, 0, size[i] * scale);
        func_00282CC0(a, a, c);
    }
}
