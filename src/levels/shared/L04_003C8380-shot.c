#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *CreateMoby(int);
extern float math_random_float_range(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(char *, char *, float);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[] __attribute__((sda));
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecLength(void *);
extern int math_random_int_range(int, int);
extern void part_spawn_velocity_particle(void *, void *, unsigned int, int, float);
extern void SpawnJointFollowParticle(void *, unsigned int, int, int, float);
extern unsigned char *part_spawn_random_effect_record(void *, void *, int, float);
extern void moby_destroy_effects_with_burst(void *, int);
extern void moby_mark_spawned(void *);
extern float cubic_hermite_scalar(float, float, float, float, float);

/* Spawns a shot moby at pos heading along velocity. If the sweep from the owner to pos is
 * blocked, it bursts into sparks and is deleted at once; otherwise it gets 17 trail particles.
 * The owner is kept as an int: a pointer parameter would let the start-vector load
 * be scheduled above the probe stores. */
/* Creates a homing shot at a position with a velocity, and builds its trail of followers. If the shot would start inside a wall it bursts into sparks at once and returns 0. */
unsigned char *SpawnHomingShot(int owner, float *pos, float *velocity, int life)
{
    float originBuf[4], directionBuf[4];
    float *origin = originBuf, *direction = directionBuf;
    SweepProbe probe;
    float start[4], scratch[4], random[4];
    unsigned char *shot, *vars, *particle;
    int i, trailIndex;
    unsigned short kind;
    float fade, alpha, numerator, denominator;
    *(QuadWord *)origin = *(QuadWord *)pos;
    *(QuadWord *)direction = *(QuadWord *)velocity;
    shot = CreateMoby(0xABC /* moby class 2748 */);
    if (shot) {
        vars = *(unsigned char **)(shot + 0x68);
        *(void **)(vars + 0x18) = (void *)owner;
        shot[0x30] = 0x7F;
        *(short *)(shot + 0x32) = 0x7F;
        shot[0x31] = 1;
        *(long *)(shot + 0x38) = *(long *)(owner + 0x38);
        *(float *)(shot + 0xF0) = 0;
        *(float *)(shot + 0xF4) = -mat_fast_helper_a(vec_length_xy(direction), direction[2]);
        *(float *)(shot + 0xF8) = mat_fast_helper_a(direction[0], direction[1]);
        qcopy((shot + 0x10), origin);
        qcopy(vars, direction);
        *(int *)(vars + 0x10) = life;
        *(int *)(vars + 0x14) = life;
        probe.owner = *(void **)(vars + 0x18);
        probe.flags = 0x30000;
        probe.radius = 13.0f;
        probe.active = 1;
        *(QuadWord *)probe.v = *(QuadWord *)vars;
        vec_fast_normalize_helper(&probe, &probe, 1.0f);
        probe.v[2] = 1;
        probe.v[3] = 5627.9248046875f;
        probe.mode = 1;
        probe.enabled = 1;
        kind = *(unsigned short *)(shot + 0xAA);
        *(QuadWord *)start = *(QuadWord *)(owner + 0x10);
        probe.kind = kind;
        start[2] = origin[2];
        if (CollLine(start, origin, 0, (void *)owner, &probe)) {
            qcopy((shot + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = math_random_float_range(-1, 1);
                random[1] = math_random_float_range(-1, 1);
                random[2] = math_random_float_range(-1, 1);
                *(QuadWord *)scratch = *(QuadWord *)random;
                vec_fast_normalize(random, vars, D_L04_001BFB00);
                vec_scale_to_length((char *)scratch, (char *)scratch, FastVecLength(random) * 0.5f);
                FastVecAdd(random, random, scratch);
                vec_scale_to_length((char *)random, (char *)random, math_random_float_range(0.050000004f, 0.10000001f));
                part_spawn_velocity_particle(shot + 0x10, random, 0x7F2F4F6F, math_random_int_range(10, 15), 15000);
            }
            moby_destroy_effects_with_burst(shot, 0);
            moby_mark_spawned(shot);
            return 0;
        }
        SpawnJointFollowParticle(shot, 0x2F4F7F7F, *(int *)(vars + 0x10), -1, 100000);
        for (trailIndex = 0; trailIndex < 17; trailIndex++) {
            particle = part_spawn_random_effect_record(shot + 0x10, D_L04_001A8F20, 1, 0);
            if (particle) {
                *(float *)(particle + 0xC) = math_random_float_range(15000, 25000);
                numerator = IntToFloat(trailIndex);
                denominator = IntToFloat(16);
                fade = cubic_hermite_scalar(-1.5f, 0, 1, 0, numerator / denominator);
                *(float *)(particle + 0xC) += (8000.0f - *(float *)(particle + 0xC)) * fade;
                alpha = fade * -64.0f + 128.0f;
                *(unsigned int *)(particle + 4) = (FloatToInt(alpha) << 24) | 0xFFFFFF;
                *(void **)(vars + 0x1C + trailIndex * 4) = particle;
            } else *(void **)(vars + 0x1C + trailIndex * 4) = 0;
        }
    }
    return shot;
}
