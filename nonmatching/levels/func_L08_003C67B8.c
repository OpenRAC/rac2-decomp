/* 2 November 2026: retained nonmatching C; no linked matching credit.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * USA v1.01 check: 756/756 bytes, 0/3 placements.
 * Full particle-emitter C replaces the old incorrect MMI exclusion. Four complete 16-byte
 * vectors, all three integer inputs and six float inputs, all random samples and the nine-
 * argument particle constructor are retained. The positive-count guarded do-loop improves the
 * helper draft from 744 to 752 bytes; ordinary TI transfers reach 756 bytes. Aggregate storage
 * ties. The 0x100 frame agrees, but saved GPR allocation and division/address scheduling remain
 * different. Debug hazard padding gives 760 bytes. Reopen on genuine object/vector pointer
 * lifetimes. No linked or native-runtime validation.
 */
#include "common.h"

typedef int ParticleQuad __attribute__((mode(TI)));
typedef union { ParticleQuad q; float f[4]; } ParticleVector;
extern int D_L08_001AFB30 __attribute__((sda)), D_L08_001AFB34 __attribute__((sda));
extern int D_L08_001AFBC8 __attribute__((sda)), D_L08_001AFBCC __attribute__((sda));
extern float D_L08_001AFB38 __attribute__((sda)), D_L08_001AFB3C __attribute__((sda));
extern float D_L08_001AFB40 __attribute__((sda)), D_L08_001AFB44 __attribute__((sda));
extern float D_L08_001AFB48 __attribute__((sda)), D_L08_001AFB4C __attribute__((sda));
extern float D_L08_001AFB68 __attribute__((sda)), D_L08_001AFB6C __attribute__((sda));
extern float D_L08_001AFBBC __attribute__((sda)), D_L08_001AFBC0 __attribute__((sda));
extern int func_00278E78(void), func_001163B0(void);
extern float func_002A7878(float, float), func_00283180(float), func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern unsigned char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Emit two-ended particles from a transformed disk around the object. */
void func_L08_003C67B8(char *object, void *position, int count,
                      float speed, float rise, float outerRadius, float innerRadius,
                      float startScale, float endScale)
{
    struct { ParticleVector offset, velocity, acceleration, inherited; } frame;
    char *state = *(char **)(object + 0x68);
    int startColor = D_L08_001AFB30;
    int endColor = D_L08_001AFB34;
    int n;
    float component, length, magnitude;
    int kind, duration, size;
    unsigned char *particle;

    if (!func_00278E78()) {
        startColor = D_L08_001AFBC8;
        endColor = D_L08_001AFBCC;
    }
    if (count > 0) {
        n = count;
        do {
        component = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
        component *= func_002A7878(innerRadius, outerRadius);
        frame.offset.f[0] = component;
        component = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
        component *= func_002A7878(innerRadius, outerRadius);
        frame.offset.f[1] = component;
        frame.offset.f[2] = 0.0f;
        func_00283098(&frame.offset, &frame.offset, object + 0xC0);
        length = func_00282DF0(&frame.offset);
        magnitude = speed * ((outerRadius - length) * 0.01666666753590107f) / outerRadius;
        func_00282F20(&frame.velocity, &frame.offset,
                     func_002A7878(magnitude / D_L08_001AFB68, magnitude));
        frame.inherited.q = *(ParticleQuad *)state;
        frame.inherited.f[2] *= D_L08_001AFBBC;
        func_00282CC0(&frame.velocity, &frame.velocity, &frame.inherited);
        frame.velocity.f[2] += func_002A7878(rise / D_L08_001AFB6C, rise) * 0.01666666753590107f;
        frame.acceleration.q = 0;
        func_00282CC0(&frame.offset, &frame.offset, position);
        frame.offset.f[2] += D_L08_001AFBC0;
        frame.velocity.f[3] = startScale;
        frame.acceleration.f[3] = endScale;
        kind = func_00283CF0(func_002A7878(D_L08_001AFB38, D_L08_001AFB3C));
        duration = func_00283CF0(func_002A7878(D_L08_001AFB40, D_L08_001AFB44));
        size = func_00283CF0(func_002A7878(D_L08_001AFB48, D_L08_001AFB4C));
        particle = func_002BAA28(&frame.offset, &frame.velocity, &frame.acceleration, startColor, endColor,
                               kind, duration, size, -1);
        if (particle && (func_001163B0() & 1))
            particle[3] = 0x48;
        } while (--n != 0);
    }
}
