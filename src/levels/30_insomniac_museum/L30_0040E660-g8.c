#include "names.h"
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_L16_00414038(void *, float, int, int, int, float, float, int, void *);
extern float D_001B197C __attribute__((sda));
extern float D_001B1980 __attribute__((sda));
extern int D_001B193C __attribute__((sda));
extern int D_001B1940 __attribute__((sda));
extern int D_001B1974 __attribute__((sda));
extern int D_001B1978 __attribute__((sda));

/* Spawns two puffs of dust at the object's position, each with a random size. */
void func_L30_0040E660(char *obj) {
    DrawBeamQuadsAndGlowsB(obj + 0x10, D_001B197C * *(float *)(obj + 0x2C), D_001B193C, RandomIntRange(0x5F, 0x6F), D_001B1974, RandomAngle(), 1.0f, 2, obj);
    DrawBeamQuadsAndGlowsB(obj + 0x10, D_001B197C * *(float *)(obj + 0x2C) * D_001B1980, D_001B1940, RandomIntRange(0x6F, 0x7F), D_001B1978, RandomAngle(), 1.0f, 2, obj);
}
