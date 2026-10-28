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
extern char D_00189E20[];
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern Effect2BFB38 *func_002BFB38(void *, void *, int, int);
extern int func_002A77E0(int);

void func_L00_002AA750(int period, int threshold)
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
        radius = func_002A7878(0.0f, 0.05000000447034836f);
        velocity[0] = func_00283180(angle) * radius + state->vx * 0.75f;
        velocity[1] = func_00283198(angle) * radius + state->vy * 0.75f;
        velocity[2] = func_002A7878(0.05000000447034836f, 0.10833334177732468f);
        lifetime = func_002A7820(90, 120);
        if (state->amount < 0.25f)
            func_002BFB38(position, velocity, 3, lifetime);
        else
            func_002BFB38(position, velocity, 1, lifetime);
        ((EmissionStateView *)D_00189E20)->counter = func_002A77E0(period);
    }
}
