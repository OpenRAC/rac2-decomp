/* Nonmatching paired-particle emitter, 2026-10-28. No C coverage credit.
 * Three bounded US checks, 0/4 placements; retained 768/772B, frame0xC0,
 * with -O2 -G0 -ffunction-sections. Explicit positive-count scope restores
 * the parameter/count roles; three-vector pointer lifetimes, color register,
 * saved FP jitter versus repeated literal loads, and call scheduling differ.
 * -fmove-all-movables is worse, 792B/frame0xD0, and is not retained.
 * Initial diagnostic lacked the second color's top7F byte; retained code
 * uses the actual0x7F7F7F7F. Reopen with independent original constant/pointer
 * lifetimes rather than synthetic accesses, volatility, or register pins.
 *
 * Actual002ACEC0 definition confirms void rotation/blend and full vector
 * inputs. Full002C2210 raw body and consuming callers establish a particle
 * address result. Banks are a0 position,a1 lifetime,a2 color,a3 mode,t0 sign,
 * t1 XYZ velocity,t2 integer converted by00283CE0, and f12..f14 three floats.
 * Current RAC1 ref8bbc6b38 src/overlays/shared/alpha_fade_particle_updates.c,
 * PartType53Spawn, independently corroborates the common interface; RAC2
 * additionally consumes that T2 integer and writes particle+0x1C. No donor
 * implementation copied. Other raw-only math return hypotheses are provisional.
 * All16B axis bytes are cleared before Z/W writes; difference and offset are
 * fully written by helpers. The unsigned/float union describes the real Z
 * word clear and read. Rotation initializes all16B velocity bytes; constructor
 * reads only XYZ12B. The deliberately unused point receives a full vector
 * write. External texture/camera extents remain incomplete. Position is a
 * caller-supplied16B vector and its XYZ jitter accumulates as retail does.
 */

#include "common.h"
typedef int EmitterQuad __attribute__((mode(TI)));
typedef union { EmitterQuad q; unsigned int u[4]; float f[4]; } EmitterVector;
extern unsigned char D_L05_001B96C0[], D_L05_001FF240[];
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_002ACEC0(void *, void *, float *, float);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern int func_002A77E0(int), func_00283CF0(float);
/* Actual7 integer slots: position,life,color,mode,sign,XYZ velocity,int value;
 * three FP slots: start/end size and decay. T2 is converted to float, not a
 * pointer. Current RAC1 PartType53Spawn corroborates the common9 arguments;
 * this RAC2 body adds the T2 integer and a float field at particle+0x1C. */
extern unsigned char *func_002C2210(void *, int, unsigned int, int, int, const float *, int, float, float, float);

void func_L05_0037DA58(float *position, int count, unsigned int color, int lifetime)
{
    EmitterVector velocity, unusedPoint, difference, axis, offset;
    unsigned char *particle;
    int remaining, sign;
    float size, zero, jitter, frameScale;
    axis.q = 0;
    axis.f[2] = axis.f[3] = 1.0f;
    func_00282CF0(difference.f, D_L05_001B96C0, position);
    func_00282F20(offset.f, difference.f, 0.5f);
    difference.u[2] = 0;
    if (count > 0) {
    zero = difference.f[2];
    frameScale = 0.01666666753590107f;
    jitter = 0.15f;
    remaining = count;
    do {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        func_002ACEC0(velocity.f, difference.f, axis.f, func_002A7878(-1.047197699546814f, 1.047197699546814f));
        func_00282F20(velocity.f, velocity.f, func_002A7878(0.05f, 3.0f) * frameScale);
        velocity.f[2] = func_002A7878(1.0f, 5.0f) * frameScale;
        func_00282CC0(unusedPoint.f, position, offset.f);
        position[0] += func_002A78D8(zero, jitter);
        position[1] += func_002A78D8(zero, jitter);
        position[2] += func_002A78D8(zero, jitter);
        particle = func_002C2210(position, lifetime, color, 0, sign, velocity.f, 0, size * 0.1f, size, 0.002f);
        if (particle) {
            particle[2] = (*(unsigned char **)(D_L05_001FF240 + 0x184))[6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
        particle = func_002C2210(position, lifetime, 0x7F7F7F7F, 1, -sign, velocity.f, 0, size * 0.07f, size * 0.7f, 0.002f);
        if (particle) {
            particle[2] = (*(unsigned char **)(D_L05_001FF240 + 0x184))[6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
        remaining--;
    } while (remaining != 0);
    }
}
