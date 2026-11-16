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
extern char g_spark_origin_quad[];
extern char g_scratch_direction_quad[];
extern char g_effect_default_params[] __attribute__((sda));
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecLength(void *);
extern int math_random_int_range(int, int);
extern u8 *part_spawn_velocity_particle(void *, void *, unsigned int, int, float);
extern void *SpawnJointFollowParticle(void *, unsigned int, int, int, float);
extern unsigned char *part_spawn_random_effect_record(void *, void *, int, float);
extern void func_PAL_L04_003FDE38(void *, int);
extern void moby_mark_spawned(void *);
extern float cubic_hermite_scalar(float, float, float, float, float);

/* func_PAL_L04_003FD4F8, the PAL copy of func_L04_003F9320: the same C, where the spark speed
 * range 0.05-0.1 becomes 0.06-0.12, the spark life 10-15 becomes 8-12, and the callee
 * func_L04_003F9C60 becomes func_PAL_L04_003FDE38. */

/* Spawns a shot moby at pos heading along velocity. If the sweep from the owner to pos is
 * blocked, it bursts into sparks and is deleted at once; otherwise it gets 17 trail particles.
 * The owner is kept as an int: a pointer parameter would let the start-vector load
 * be scheduled above the probe stores. */
unsigned char *func_PAL_L04_003FD4F8(int owner, float *pos, float *velocity, int life)
{
    float origin_buf[4], direction_buf[4];
    float *origin = origin_buf, *direction = direction_buf;
    SweepProbe probe;
    float start[4], temp[4], random[4];
    unsigned char *m, *v, *particle;
    int i, j;
    unsigned short kind;
    float t, alpha, numerator, denominator;
    *(QuadWord *)origin = *(QuadWord *)pos;
    *(QuadWord *)direction = *(QuadWord *)velocity;
    m = CreateMoby(0xABC);
    if (m) {
        v = *(unsigned char **)(m + 0x68);
        *(void **)(v + 0x18) = (void *)owner;
        m[0x30] = 0x7F;
        *(short *)(m + 0x32) = 0x7F;
        m[0x31] = 1;
        *(long *)(m + 0x38) = *(long *)(owner + 0x38);
        *(float *)(m + 0xF0) = 0;
        *(float *)(m + 0xF4) = -mat_fast_helper_a(vec_length_xy(direction), direction[2]);
        *(float *)(m + 0xF8) = mat_fast_helper_a(direction[0], direction[1]);
        qcopy((m + 0x10), origin);
        qcopy(v, direction);
        *(int *)(v + 0x10) = life;
        *(int *)(v + 0x14) = life;
        probe.owner = *(void **)(v + 0x18);
        probe.flags = 0x30000;
        probe.radius = 13.0f;
        probe.active = 1;
        *(QuadWord *)probe.v = *(QuadWord *)v;
        vec_fast_normalize_helper(&probe, &probe, 1.0f);
        probe.v[2] = 1;
        probe.v[3] = 5627.9248046875f;
        probe.mode = 1;
        probe.enabled = 1;
        kind = *(unsigned short *)(m + 0xAA);
        *(QuadWord *)start = *(QuadWord *)(owner + 0x10);
        probe.kind = kind;
        start[2] = origin[2];
        if (CollLine(start, origin, 0, (void *)owner, &probe)) {
            qcopy((m + 0x10), g_spark_origin_quad);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = math_random_float_range(-1, 1);
                random[1] = math_random_float_range(-1, 1);
                random[2] = math_random_float_range(-1, 1);
                *(QuadWord *)temp = *(QuadWord *)random;
                vec_fast_normalize(random, v, g_scratch_direction_quad);
                vec_scale_to_length((char *)temp, (char *)temp, FastVecLength(random) * 0.5f);
                FastVecAdd(random, random, temp);
                vec_scale_to_length((char *)random, (char *)random, math_random_float_range(0.060000002f, 0.120000005f));
                part_spawn_velocity_particle(m + 0x10, random, 0x7F2F4F6F, math_random_int_range(8, 12), 15000);
            }
            func_PAL_L04_003FDE38(m, 0);
            moby_mark_spawned(m);
            return 0;
        }
        SpawnJointFollowParticle(m, 0x2F4F7F7F, *(int *)(v + 0x10), -1, 100000);
        for (j = 0; j < 17; j++) {
            particle = part_spawn_random_effect_record(m + 0x10, g_effect_default_params, 1, 0);
            if (particle) {
                *(float *)(particle + 0xC) = math_random_float_range(15000, 25000);
                numerator = IntToFloat(j);
                denominator = IntToFloat(16);
                t = cubic_hermite_scalar(-1.5f, 0, 1, 0, numerator / denominator);
                *(float *)(particle + 0xC) += (8000.0f - *(float *)(particle + 0xC)) * t;
                alpha = t * -64.0f + 128.0f;
                *(unsigned int *)(particle + 4) = (FloatToInt(alpha) << 24) | 0xFFFFFF;
                *(void **)(v + 0x1C + j * 4) = particle;
            } else *(void **)(v + 0x1C + j * 4) = 0;
        }
    }
    return m;
}
