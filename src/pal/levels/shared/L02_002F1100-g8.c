/* func_PAL_L02_002F1100, the PAL copy of func_L02_002EFB60: the same C, where the gravity factor 0.00027777778f
   becomes 0.00040000002f and the three colour arguments are scaled for 50 Hz. Needs -frac2-sticky-volatile-refs
   (reorg stops at the copy's volatile asm); see docs/COMPILER-NOTES.md. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern int D_L02_001A8D68 __attribute__((sda));
extern float D_L02_001A8D78[] SDATA(D_L02_001A8D78) __attribute__((nosda));
extern int D_L02_001A8D58 __attribute__((sda));
extern int D_L02_001A8D50 __attribute__((sda));
extern float D_L02_001A8D7C __attribute__((nosda));
extern int D_L02_001A8D5C __attribute__((nosda));
extern int D_L02_001A8D60 __attribute__((nosda));
extern int D_L02_001A8D64 __attribute__((nosda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L02_002F1100(void *owner, void *from, void *to, int count, int *colour, float speed) {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    float gravity = speed * 0.00040000002f;
    float brightness, t;
    int r, g, b, first, second, i;
    int *rgb = &D_L02_001A8D68;
    if (colour) rgb = colour;
    for (i = 0; i < count; i++) {
        brightness = func_002A7878(0.7f, 1.3f);
        r = func_00283CF0(((float)rgb[0] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        g = func_00283CF0(((float)rgb[1] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        b = func_00283CF0(((float)rgb[2] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        func_00282D08(&direction, from, to, func_002A7878(0.0f, 1.0f));
        qcopy(&position, &direction);
        position.f[3] = func_002A7878(D_L02_001A8D78[0], D_L02_001A8D7C);
        func_00282C88(&velocity);
        velocity.f[2] = -gravity * (float)(r + g + b);
        func_00282CC0(&velocity, &velocity, &direction);
        velocity.f[3] = position.f[3];
        t = func_002A7878(0.0f, 1.0f);
        first = func_00283D38(D_L02_001A8D58, D_L02_001A8D5C, t);
        t = func_002A7878(0.0f, 1.0f);
        second = func_00283D38(D_L02_001A8D60, D_L02_001A8D64, t);
        func_002BAA28(owner, &position, &velocity, first, second, r, g, b, D_L02_001A8D50);
    }
}
