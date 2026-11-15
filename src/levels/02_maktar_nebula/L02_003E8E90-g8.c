#include "include_asm.h"
#include "names.h"

/* func_L02_003E8E90 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy), which gives retail's `lq`/`sq` with a register address. It reads $gp data,
   hence -G8. */

typedef int TI128 __attribute__((mode(TI)));

extern unsigned char *g_moby_l02_pool[3] __attribute__((sda));

extern char g_hero_state[];

/* Two plain words, tilts in degrees. Read as one array with `[1]` in the first arm, they keep the
   two arms apart (as two scalars the else load is hoisted above the test, 8 bytes shorter). */
extern float D_L02_001B0C10[2];

extern float D_L02_001B0C18 __attribute__((sda));

extern float mat_fast_helper_a(float, float);

extern float FastDiffRots(float, float);

extern float FastAddRotations(float, float);

extern void vec_build_spherical_offset(void *, float, float, float);

extern void FastVecSub(void *, void *, void *);

extern void vec_clamp_length(float *, float);

extern void FastVecAdd(void *, void *, void *);

extern float FastVecDot(void *, void *);

/* Steers the point at +0x10 of the actor's private data. The velocity comes from the actor's
   heading (turned by pi when the hero is within a quarter turn of it, as seen from the actor) and
   a tilt chosen by the class of the entity the actor follows (0x9C8 or not). The point moves by
   the velocity's difference to it, limited in length, and the entity's own point moves by the
   new one. When the new point and the flat vector from the actor to the entity make a positive
   product, the point is replaced by the velocity and the result is 1. */
int tether_swing_entity(char *actor) {
    char *state = *(char **)(actor + 0x68);
    unsigned char *entity = g_moby_l02_pool[0] + (*(int *)state << 8);
    float tilt;
    float heading;
    float wantedVel[4];
    float velDelta[4];
    float flatOffset[4];
    char *point;
    unsigned char *entityPos;
    char *hero;

    if (*(short *)(entity + 0xAA) == 0x9C8 /* moby class 2504 */)
        tilt = D_L02_001B0C10[1];
    else
        tilt = D_L02_001B0C10[0];
    heading = *(float *)(actor + 0xF8);
    hero = g_hero_state;
    if (FastDiffRots(*(float *)(actor + 0xF8),
                      mat_fast_helper_a(*(float *)(hero + 0x80) - *(float *)(actor + 0x10),
                                    *(float *)(hero + 0x84) - *(float *)(actor + 0x14))) < 1.5707964f)
        heading = FastAddRotations(heading, 3.1415927f);
    point = state + 0x10;
    vec_build_spherical_offset(wantedVel, *(float *)(state + 0x44), heading, tilt * 0.01745329424738884f);
    entityPos = entity + 0x10;
    FastVecSub(velDelta, wantedVel, point);
    vec_clamp_length(velDelta, D_L02_001B0C18 * 0.00027777778450399637f);
    FastVecAdd(point, point, velDelta);
    FastVecAdd(entityPos, entityPos, point);
    FastVecSub(flatOffset, entityPos, actor + 0x10);
    flatOffset[2] = 0;
    if (0.0f < FastVecDot(point, flatOffset)) {
        *(TI128 *)point = *(TI128 *)wantedVel;
        return 1;
    }
    return 0;
}
