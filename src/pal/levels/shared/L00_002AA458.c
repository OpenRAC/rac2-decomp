#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[128];
    float x;
    float y;
    char pad88[16];
    float angle;
    char pad9c[660];
    float z;
    char pad334[1812];
    unsigned short counter;
} ParticleResidentFields;
extern ParticleResidentFields D_00189E20_20;
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void *part_spawn_random_tinted_effect(float, float, float *, float *, float *);

void func_PAL_L00_002AA458(char *self, int arg1)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float f;
    float r;
    int n;
    int i;


    n = D_00189E20_20.counter + 1;
    D_00189E20_20.counter = n;
    if (arg1 < (short)n) {
        for (i = 0; i < 2; i++) {
            if (i == 0)
                f = FastAddRotations(D_00189E20_20.angle, 0.785398006f);
            else
                f = fast_subtract_rotations(D_00189E20_20.angle, 0.785398006f);
            v[0] = math_fast_sin_or_cos_a(f) * 0.012000001f;
            v[1] = math_fast_sin_or_cos_b(f) * 0.012000001f;
            w[0] = D_00189E20_20.x + v[0] * 18.0f;
            w[1] = D_00189E20_20.y + v[1] * 18.0f;
            w[2] = D_00189E20_20.z;
            v[2] = 0.0f;
            v[0] = v[0] - math_fast_sin_or_cos_a(D_00189E20_20.angle) * 0.030000001f;
            v[1] = v[1] - math_fast_sin_or_cos_b(D_00189E20_20.angle) * 0.030000001f;
            r = math_random_float_range(0.4f, 0.5f);
            part_spawn_random_tinted_effect(r, i == 0 ? 2.0f : -2.0f, w, v, &D_00189E20_20.z);
            D_00189E20_20.counter = self == 0 ? 0 : math_random_int_below((int)self);
        }
    }
}


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
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern Effect2BFB38 *func_PAL_002C0838(void *, void *, int, int);

void func_PAL_L00_002AA638(int period, int threshold)
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
        radius = math_random_float_range(0.0f, 0.060000002f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * radius + state->vx * 0.75f;
        velocity[1] = math_fast_sin_or_cos_b(angle) * radius + state->vy * 0.75f;
        velocity[2] = math_random_float_range(0.060000002f, 0.13000001f);
        lifetime = math_random_int_range(90, 120);
        if (state->amount < 0.25f)
            func_PAL_002C0838(position, velocity, 3, lifetime);
        else
            func_PAL_002C0838(position, velocity, 1, lifetime);
        ((EmissionStateView *)g_hero_state)->counter = math_random_int_below(period);
    }
}




