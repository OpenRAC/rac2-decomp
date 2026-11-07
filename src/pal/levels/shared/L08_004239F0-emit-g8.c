#include "common.h"

/* func_PAL_L08_004239F0, the PAL copy of func_L08_0041E790, written as func_PAL_L08_003CA1C8: 1/60 becomes 1/50, the
 * three func_00283CF0 arguments take the 50 Hz scale, and the acceleration address sits in a local set
 * before the rise term: its longer life keeps loop.c hoisting it past the nine extra scale insns. */

/* Built with -fno-gcse and -g: PRE would hoist object+0xC0 out of the loop, and -g gives the
 * nops before the div.s pairs. The acceleration clear is qzero_nc: cse forgets the frame
 * addresses there, so the constructor call builds them again, as retail does. */

typedef int ParticleQuad __attribute__((mode(TI)));
typedef union { ParticleQuad q; float f[4]; } ParticleVector;
extern int D_L08_001B1ADC __attribute__((sda)), D_L08_001B1AE0 __attribute__((sda));
extern int D_L08_001B1B74 __attribute__((sda)), D_L08_001B1B78 __attribute__((sda));
extern float D_L08_001B1AE4 __attribute__((sda)), D_L08_001B1AE8 __attribute__((sda));
extern float D_L08_001B1AEC __attribute__((sda)), D_L08_001B1AF0 __attribute__((sda));
extern float D_L08_001B1AF4 __attribute__((sda)), D_L08_001B1AF8 __attribute__((sda));
extern float D_L08_001B1B14 __attribute__((sda)), D_L08_001B1B18 __attribute__((sda));
extern float D_L08_001B1B68 __attribute__((sda)), D_L08_001B1B6C __attribute__((sda));
extern int func_00278E78(void), func_001163B0(void);
extern float func_002A7878(float, float), func_00283180(float), func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern unsigned char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Emit two-ended particles from a transformed disk around the object. */
void func_PAL_L08_004239F0(char *object, void *position, int count,
                      float speed, float rise, float outerRadius, float innerRadius,
                      float startScale, float endScale)
{
    struct { ParticleVector offset, velocity, acceleration, inherited; } frame;
    char *state = *(char **)(object + 0x68);
    int startColor = D_L08_001B1ADC;
    int endColor = D_L08_001B1AE0;
    int n;
    float component, length, magnitude;
    int kind, duration, size;
    unsigned char *particle;
    ParticleVector *acceleration;

    if (!func_00278E78()) {
        startColor = D_L08_001B1B74;
        endColor = D_L08_001B1B78;
    }
    if (count > 0) {
        n = count;
        do {
        frame.offset.f[0] = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f))
            * func_002A7878(innerRadius, outerRadius);
        component = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
        component *= func_002A7878(innerRadius, outerRadius);
        frame.offset.f[1] = component;
        frame.offset.f[2] = 0.0f;
        func_00283098(&frame.offset, &frame.offset, object + 0xC0);
        length = func_00282DF0(&frame.offset);
        magnitude = speed * ((outerRadius - length) * 0.020000001f) / outerRadius;
        func_00282F20(&frame.velocity, &frame.offset,
                     func_002A7878(magnitude / D_L08_001B1B14, magnitude));
        frame.inherited.q = *(ParticleQuad *)state;
        frame.inherited.f[2] *= D_L08_001B1B68;
        func_00282CC0(&frame.velocity, &frame.velocity, &frame.inherited);
        acceleration = &frame.acceleration;
        frame.velocity.f[2] += func_002A7878(rise / D_L08_001B1B18, rise) * 0.020000001f;
        qzero_nc(acceleration);
        func_00282CC0(&frame.offset, &frame.offset, position);
        frame.offset.f[2] += D_L08_001B1B6C;
        frame.velocity.f[3] = startScale;
        frame.acceleration.f[3] = endScale;
        kind = func_00283CF0((func_002A7878(D_L08_001B1AE4, D_L08_001B1AE8) * 5.0f + 2.0f) * 0.16666667f);
        duration = func_00283CF0((func_002A7878(D_L08_001B1AEC, D_L08_001B1AF0) * 5.0f + 2.0f) * 0.16666667f);
        size = func_00283CF0((func_002A7878(D_L08_001B1AF4, D_L08_001B1AF8) * 5.0f + 2.0f) * 0.16666667f);
        particle = func_002BAA28(&frame.offset, &frame.velocity, &frame.acceleration, startColor, endColor,
                               kind, duration, size, -1);
        if (particle && (func_001163B0() & 1))
            particle[3] = 0x48;
        } while (--n != 0);
    }
}
