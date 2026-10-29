/* Nonmatching museum trail emitter, 2026-10-28. No C coverage credit.
 * Four US checks, 0/1: all792/804B, frame0xF0 versus0x100. Retained
 * -O2 -G0 -ffunction-sections. Current compiler rematerializes the two PI
 * argument constants rather than preserving the retail's extra saved FP
 * values; GPR parameter/pointer roles and scheduling differ. Existing
 * -fmove-all-movables, narrow CSE path controls and disabling the post-loop
 * CSE rerun do not restore those lifetimes. Their full forms are not claimed
 * byte-identical merely because their sizes coincide. No option retained.
 * Reopen with independent original FP-constant or parameter-scope evidence.
 *
 * Three integer and six incoming FP slots are observed and preserved. Actual
 * constructor definition (worker03 src/game/002BAA28.c:36) returns Particle*
 * with three pointer and six integer slots; caller uses opaque pointer result.
 * Complete constructor/raw and worker03 renderer audit07e9c6c7 establish:
 * radial XYZ are initialized; radial W is opaque and copied by the family2
 * constructor, not semantically consumed. Constructor clears flag1; BABE8
 * leaves it clear; B9420 normal path reads XYZ and zeroes output W at+0x750
 * before use. This caller changes only blend byte3, preserving that path.
 * Both endpoint W values are explicitly initialized from incoming f16/f17
 * before constructor reads them as sizes. Acceleration is whole-cleared;
 * velocity and inherited vector are full transfers before XYZ arithmetic.
 * Matrix helper's W contribution reaches only output W; no extra zero is
 * invented. Origin/context require actual16B storage, orientation48B; all
 * unknown external table extents remain incomplete. Raw-only mutation return
 * hypotheses remain provisional unless backed by actual definitions.
 */

#include "common.h"
extern int D_001A79F0 __attribute__((sda));
extern int D_L30_001B1820[] SDATA(D_L30_001B1820);
extern int D_L30_001B1824[] SDATA(D_L30_001B1824);
extern int D_L30_001B18B8[] SDATA(D_L30_001B18B8);
extern int D_L30_001B18BC[] SDATA(D_L30_001B18BC);
extern float D_L30_001B1858[] SDATA(D_L30_001B1858);
extern float D_L30_001B185C[] SDATA(D_L30_001B185C);
extern float D_L30_001B18AC[] SDATA(D_L30_001B18AC);
extern float D_L30_001B18B0[] SDATA(D_L30_001B18B0);
extern float D_L30_001B1828[] SDATA(D_L30_001B1828);
extern float D_L30_001B182C[] SDATA(D_L30_001B182C);
extern float D_L30_001B1830[] SDATA(D_L30_001B1830);
extern float D_L30_001B1834[] SDATA(D_L30_001B1834);
extern float D_L30_001B1838[] SDATA(D_L30_001B1838);
extern float D_L30_001B183C[] SDATA(D_L30_001B183C);
extern int func_00278E78(void), func_00283CF0(float), func_001163B0(void);
extern float func_002A7878(float, float), func_00283180(float), func_00283198(float), func_00282DF0(const void *);
extern void func_00283098(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void *func_002BAA28(void *, float *, float *, int, int, int, int, int, int);

/* Radial position W is an opaque lane, not a float value used here. Family2
 * ctor clears flag1; BABE8 preserves that normal-render path. Renderer B9420
 * uses XYZ and overwrites output W before consumption (review07e9c6c7).
 * This caller changes only blend byte3; both endpoint size W are initialized. */
void func_L30_0040B6B0(unsigned char *object, const void *origin, int count,
                      float speed, float lift, float maxRadius, float minRadius,
                      float velocitySize, float accelerationSize)
{
    float radial[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float inherited[4] __attribute__((aligned(16)));
    void *state = *(void **)(object + 0x68);
    unsigned char *particle;
    int startColor, endColor, remaining, kind, duration, size;
    float value, maximum, pi, negativePi, frameScale;
    if (D_001A79F0 == 21 || D_001A79F0 == 30) {
        startColor = 0x30301010;
        endColor = D_L30_001B1824[0];
    } else {
        startColor = D_L30_001B1820[0];
        endColor = D_L30_001B1824[0];
    }
    if (!func_00278E78()) {
        startColor = D_L30_001B18B8[0];
        endColor = D_L30_001B18BC[0];
    }
    if (count > 0) {
        negativePi = -3.1415927410125732f;
        pi = 3.1415927410125732f;
        frameScale = 0.01666666753590107f;
        remaining = count;
        do {
            value = func_00283180(func_002A7878(negativePi, pi));
            value *= func_002A7878(minRadius, maxRadius);
            radial[0] = value;
            value = func_00283198(func_002A7878(negativePi, pi));
            value *= func_002A7878(minRadius, maxRadius);
            radial[1] = value;
            radial[2] = 0.0f;
            func_00283098(radial, radial, object + 0xC0);
            maximum = (maxRadius - func_00282DF0(radial)) * frameScale;
            maximum *= speed;
            maximum /= maxRadius;
            func_00282F20(velocity, radial, func_002A7878(maximum / D_L30_001B1858[0], maximum));
            qcopy(inherited, state);
            inherited[2] *= D_L30_001B18AC[0];
            func_00282CC0(velocity, velocity, inherited);
            velocity[2] += func_002A7878(lift / D_L30_001B185C[0], lift) * frameScale;
            qzero(acceleration);
            func_00282CC0(radial, radial, origin);
            radial[2] += D_L30_001B18B0[0];
            velocity[3] = velocitySize;
            acceleration[3] = accelerationSize;
            kind = func_00283CF0(func_002A7878(D_L30_001B1828[0], D_L30_001B182C[0]));
            duration = func_00283CF0(func_002A7878(D_L30_001B1830[0], D_L30_001B1834[0]));
            size = func_00283CF0(func_002A7878(D_L30_001B1838[0], D_L30_001B183C[0]));
            particle = func_002BAA28(radial, velocity, acceleration, startColor, endColor, kind, duration, size, -1);
            if (particle && (func_001163B0() & 1)) particle[3] = 0x48;
            remaining--;
        } while (remaining != 0);
    }
}
