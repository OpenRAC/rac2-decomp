#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
/* Measured fields in the resident hero block. */
typedef struct {
    char pad0[0x110];
    Vector motion;
    char pad120[0x220];
    int motionActive;
    char pad344[0x3EC];
    Vector axis, side;
} ContactHero;
extern ContactHero g_hero_state;
typedef struct {
    unsigned char pad0[3];
    unsigned char flags;
    unsigned char pad4[5];
    unsigned char tile;
    union { short frames; unsigned char bytes[2]; } life;
} ContactParticle;
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern float FastAddRotations(float, float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, unsigned int, int);
extern void FastVecSub(void *, void *, void *);
extern char *part_spawn_burst(void *, void *, unsigned int, int, int, int, float, float, float, float, float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, int, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern int math_random_int_range(int, int);
extern char *part_spawn_spark(void *, void *, int, int, int, int, int, int, int, float);

/* Spawn layered particles and two falling streaks at the supplied position. */
void SpawnLayeredParticleBurst(void *owner, void *position)
{
    Vector rotation, direction, base, origin, velocity, jitter, drift, offset, scatter;
    float angle = 0.0f;
    int count;

    *(VectorBits *)base = 0;
    base[0] = 0.3f;
    base[1] = -1.0f;
    base[3] = 1.0f;
    qcopy(origin, position);
    math_apply_axis_rotation_to_quat(base, g_hero_state.axis, g_hero_state.side, 0.349065899848938f);
    qcopy(direction, base);
    /* This clear precedes every read of drift; surrounding objects do not alias it. */
    qzero_nc(drift);
    if (g_hero_state.motionActive)
        FastVecScale(drift, g_hero_state.motion, 1.7f);
    FastVecScale(offset, g_hero_state.axis, 0.4f);
    FastVecAdd(origin, origin, offset);
    for (count = 19; count >= 0; count--) {
        char *particle;
        float size;
        int spin;
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186078f));
        FastVecScale(velocity, direction, math_random_float_range(0.2000000179f, 0.2666666806f));
        FastVecAdd(velocity, velocity, drift);
        jitter[0] = origin[0] + math_random_signed_float_range(0.0f, 0.3f);
        jitter[1] = origin[1] + math_random_signed_float_range(0.0f, 0.3f);
        jitter[2] = origin[2] + math_random_signed_float_range(0.0f, 0.3f);
        spin = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        size = math_random_float_range(0.2f, 0.75f) * 210000.0f;
        particle = SpawnSpinningSparkParticle(jitter, 0.0f, 1.0f, 1.00999999f, spin,
                                 g_hero_state.motion, size, 0x7F202020, 0);
        if (particle) {
            char *tail = particle + 0x20;
            ((ContactParticle *)particle)->flags = 0x44;
            ((ContactParticle *)particle)->life.frames = 60;
            ((ContactParticle *)particle)->tile = FloatToInt(4.0f) + 0x40;
            *(float *)(tail + 0x1C) = IntToFloat(5);
            *(int *)(tail + 4) = 3;
            *(unsigned char *)(tail + 0xA) = 0x30;
            *(unsigned char *)(tail + 0xB) = ((ContactParticle *)particle)->life.bytes[0];
        }
        jitter[0] = origin[0] + math_random_signed_float_range(0.0f, 0.6f);
        jitter[1] = origin[1] + math_random_signed_float_range(0.0f, 0.6f);
        jitter[2] = origin[2] + math_random_signed_float_range(0.0f, 0.6f);
        size = math_random_float_range(0.2f, 1.75f) * 210000.0f;
        FastVecSub(jitter, jitter, velocity);
        part_spawn_burst(jitter, velocity, 6, 0x7F, 0x404040, spin,
                      size, 500.0f, 0.95f, 0.0f, 0.0f);
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, (int)g_hero_state.axis, angle);
            vec_rotate_by_quaternion(direction, base, rotation);
        }
    }
    {
        int streakCount;
        float speed = math_random_float_range(8.0f, 12.0f);
        float scale = 0.5f;
        FastVecScale(base, g_hero_state.axis, speed * (1.0f / 60.0f));
        for (streakCount = 1; streakCount >= 0; streakCount--) {
            float cone = math_random_float_range(0.2617994249f, 1.396263599395752f);
            float heading = math_random_angle();
            float length = math_random_float_range(7.0f, 10.5f);
            int firstColor, secondColor, life;
            vec_build_spherical_offset(scatter, scale * (1.0f / 60.0f) * length, heading, cone);
            FastVecAdd(scatter, scatter, base);
            scatter[2] += 0.05000000447f;
            firstColor = gfx_swap_packed_color_channels(0x4F007FFF, 0);
            secondColor = gfx_swap_packed_color_channels(0x1F00007F, 0);
            life = math_random_int_range(60, 120);
            part_spawn_spark(position, scatter, firstColor, secondColor, life, 1, -1, -1, 0, scale * 40000.0f);
        }
    }
}
