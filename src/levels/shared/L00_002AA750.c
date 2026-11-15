#include "common.h"
typedef struct { u8 pos[16]; s32 kind, life; f32 z, rate; } Spark2BFB38;
typedef struct {
    u8 f0, f1, f2, f3;
    u32 color;
    u8 f8, f9, padA[2];
    f32 fC, pos[4];
    Spark2BFB38 s;
} Effect2BFB38;
typedef struct {
    char prefix[0x80];
    float x, y;
    char gap088[0x110 - 0x88];
    float vx, vy;
    char gap118[0x330 - 0x118];
    float z;
    char gap334[0xA46 - 0x334];
    short counter;
    char gapA48[0x24C4 - 0xA48];
    float amount;
} EmissionStateView;
extern char g_hero_state[];
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern Effect2BFB38 *part_spawn_spark_2(void *, void *, int, int);
extern int math_random_int_below(int);

/* Every so often, sprinkles a small spark particle near the hero that drifts the way the hero moves. */
void part_emit_hero_trail_spark(int period, int threshold)
{
    EmissionStateView *state = (EmissionStateView *)g_hero_state;
    float position[4];
    float velocity[4];
    float angle;
    float radius;
    int lifetime;
    state->counter++;
    if (threshold < state->counter) {
        position[0] = state->x + math_random_float_range(-0.15f, 0.15f) + state->vx * 8.0f;
        position[1] = state->y + math_random_float_range(-0.15f, 0.15f) + state->vy * 8.0f;
        position[2] = state->z + 0.1f;
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.05000000447034836f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * radius + state->vx * 0.75f;
        velocity[1] = math_fast_sin_or_cos_b(angle) * radius + state->vy * 0.75f;
        velocity[2] = math_random_float_range(0.05000000447034836f, 0.10833334177732468f);
        lifetime = math_random_int_range(90, 120);
        if (state->amount < 0.25f)
            part_spawn_spark_2(position, velocity, 3, lifetime);
        else
            part_spawn_spark_2(position, velocity, 1, lifetime);
        ((EmissionStateView *)g_hero_state)->counter = math_random_int_below(period);
    }
}
