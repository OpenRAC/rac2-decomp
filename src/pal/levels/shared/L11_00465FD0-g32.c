#include "include_asm.h"

typedef unsigned int u32;
struct ParticleSettings {
    int *colors;
    short *sizes;
    short *range;
    int unknown0C;
    int lifetime;
    float jitter;
};
extern float D_L11_001B22D0 __attribute__((sda));
extern float D_L11_001B22D4 __attribute__((sda));
extern float D_L11_001B22D8 __attribute__((sda));
extern float D_L11_001B22DC __attribute__((sda));
extern u32 D_L11_001B22C0 __attribute__((sda));
extern struct ParticleSettings D_L11_001B2300 __attribute__((sda));
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, float, float, float, int);
extern float func_00283B98(float, float);

void func_PAL_L11_00465FD0(void *position, int count) {
    float velocity[4];
    float step = 6.2831854820251465f / func_00283CE0(count);
    float angle = func_002A7878(-3.1415927410125732f, 3.1415927410125732f);
    float speed;
    int remaining, kind, variation;
    if (count > 0) {
        remaining = count;
        do {
            remaining--;
            speed = func_002A7878(D_L11_001B22D0, D_L11_001B22D4) * 0.020000001f;
            velocity[0] = speed * func_00283180(angle);
            velocity[1] = speed * func_00283198(angle);
            velocity[2] = func_002A7878(D_L11_001B22D8, D_L11_001B22DC) * 0.020000001f;
            kind = func_002A77E0(2);
            variation = func_002A7820(-2, 2);
            func_L02_003449D8(position, velocity, &D_L11_001B2300, (void *)kind, variation);
            velocity[2] = 0.0f;
            func_002C65A0(position, velocity, 60, D_L11_001B22C0, 3, 48, 0, func_002A7878(5.0f, 6.0f) * 210000.0f, 0.0f, 0.0f, 0);
            angle = func_00283B98(angle, step);
        } while (remaining);
    }
}
