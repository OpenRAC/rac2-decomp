#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *g_moby_l02_pool[3] __attribute__((sda));
extern char g_hero_state[];
extern float g_tether_swing_tilts[2];
extern float g_tether_swing_velocity_limit __attribute__((sda));
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
int tether_swing_entity_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    unsigned char *entity = g_moby_l02_pool[0] + (*(int *)state << 8);
    float tilt;
    float heading;
    float v0[4];
    float v1[4];
    float v2[4];
    char *point;
    unsigned char *entity_pos;
    char *hero;

    if (*(short *)(entity + 0xAA) == 0x9C8)
        tilt = g_tether_swing_tilts[1];
    else
        tilt = g_tether_swing_tilts[0];
    heading = *(float *)(moby + 0xF8);
    hero = g_hero_state;
    if (FastDiffRots(*(float *)(moby + 0xF8),
                      mat_fast_helper_a(*(float *)(hero + 0x80) - *(float *)(moby + 0x10),
                                    *(float *)(hero + 0x84) - *(float *)(moby + 0x14))) < 1.5707964f)
        heading = FastAddRotations(heading, 3.1415927f);
    point = state + 0x10;
    vec_build_spherical_offset(v0, *(float *)(state + 0x44), heading, tilt * 0.01745329424738884f);
    entity_pos = entity + 0x10;
    FastVecSub(v1, v0, point);
    vec_clamp_length(v1, g_tether_swing_velocity_limit * 0.00040000002f);
    FastVecAdd(point, point, v1);
    FastVecAdd(entity_pos, entity_pos, point);
    FastVecSub(v2, entity_pos, moby + 0x10);
    v2[2] = 0;
    if (0.0f < FastVecDot(point, v2)) {
        *(TI128 *)point = *(TI128 *)v0;
        return 1;
    }
    return 0;
}
