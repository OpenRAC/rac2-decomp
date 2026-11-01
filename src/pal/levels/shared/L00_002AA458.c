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
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_00338AE0(float, float, float *, float *, float *);

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
                f = func_00283B98(D_00189E20_20.angle, 0.785398006f);
            else
                f = func_00283BE0(D_00189E20_20.angle, 0.785398006f);
            v[0] = func_00283180(f) * 0.012000001f;
            v[1] = func_00283198(f) * 0.012000001f;
            w[0] = D_00189E20_20.x + v[0] * 18.0f;
            w[1] = D_00189E20_20.y + v[1] * 18.0f;
            w[2] = D_00189E20_20.z;
            v[2] = 0.0f;
            v[0] = v[0] - func_00283180(D_00189E20_20.angle) * 0.030000001f;
            v[1] = v[1] - func_00283198(D_00189E20_20.angle) * 0.030000001f;
            r = func_002A7878(0.4f, 0.5f);
            func_L00_00338AE0(r, i == 0 ? 2.0f : -2.0f, w, v, &D_00189E20_20.z);
            D_00189E20_20.counter = self == 0 ? 0 : func_002A77E0((int)self);
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
extern char D_00189E20[];
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern Effect2BFB38 *func_PAL_002C0838(void *, void *, int, int);

void func_PAL_L00_002AA638(int period, int threshold)
{
    EmissionStateView *state = (EmissionStateView *)D_00189E20;
    float position[4];
    float velocity[4];
    float angle;
    float radius;
    int lifetime;
    state->counter++;
    if (threshold < state->counter) {
        position[0] = state->x + func_002A7878(-0.15f, 0.15f) + state->vx * 8.0f;
        position[1] = state->y + func_002A7878(-0.15f, 0.15f) + state->vy * 8.0f;
        position[2] = state->z + 0.1f;
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.060000002f);
        velocity[0] = func_00283180(angle) * radius + state->vx * 0.75f;
        velocity[1] = func_00283198(angle) * radius + state->vy * 0.75f;
        velocity[2] = func_002A7878(0.060000002f, 0.13000001f);
        lifetime = func_002A7820(90, 120);
        if (state->amount < 0.25f)
            func_PAL_002C0838(position, velocity, 3, lifetime);
        else
            func_PAL_002C0838(position, velocity, 1, lifetime);
        ((EmissionStateView *)D_00189E20)->counter = func_002A77E0(period);
    }
}




