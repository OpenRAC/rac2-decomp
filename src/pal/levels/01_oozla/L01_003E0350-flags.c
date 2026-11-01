#include "include_asm.h"

#include "common.h"
typedef int OozlaQuad __attribute__((mode(TI)));
extern int D_L01_001B2088;
extern float func_PAL_L01_003BEB40(void);
extern void *func_00312D58(float *, float);
extern void func_002A0488(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern void func_PAL_002C0838(void *, void *, int, int);
extern float D_L01_001AFE18[];

void func_PAL_L01_003E0350(char *object, int bubbles, int drops, int splash)
{
    float velocity[4], position[4];
    float height, angle, radius, size;
    char *state = *(char **)(object + 0x68);
    void *effect;
    int i, j, type, lifetime;
    if (D_L01_001B2088 - *(int *)(state + 0x40C) < 11)
        return;
    height = func_PAL_L01_003BEB40();
    if (splash) {
        *(OozlaQuad *)velocity = *(OozlaQuad *)(object + 0x10);
        velocity[2] = height;
        effect = func_00312D58(velocity, 2.25f);
        if (effect)
            func_002A0488(effect, 0x60, 0x50, 0);
    }
    if (bubbles > 0) {
      i = bubbles;
      do {
        --i;
        velocity[0] = *(float *)(object + 0x10) + func_002A7878(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + func_002A7878(-0.3f, 0.3f);
        velocity[2] = height;
        size = func_002A7878(0.3f, 0.6f);
        type = ((func_002A77E0(6) + 20) << 24) | 0x5060;
        func_002C19D8(velocity, D_L01_001AFE18, type, size, 5250.0f);
      } while (i != 0);
    }
    if (drops > 0) {
      j = drops;
      do {
        --j;
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.060000002f);
        velocity[0] = func_00283180(angle) * radius;
        velocity[1] = func_00283198(angle) * radius;
        velocity[2] = func_002A7878(0.060000002f, 0.16000001f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = height - func_002A7878(0.0f, 0.2f);
        type = func_002A77E0(2);
        lifetime = func_002A7820(90, 120);
        func_PAL_002C0838(position, velocity, type, lifetime);
      } while (j != 0);
    }
    *(int *)(state + 0x40C) = D_L01_001B2088;
}
