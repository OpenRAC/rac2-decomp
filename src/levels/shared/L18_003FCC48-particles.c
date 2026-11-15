#include "names.h"
typedef int s32;
typedef float f32;
typedef int Quad __attribute__((mode(TI)));
typedef struct ParticleSettings {
    void *colorRange;
    void *sizeRange;
    short *frameRange;
    s32 reserved;
    s32 frameCount;
    f32 speed;
} ParticleSettings;
extern f32 D_L18_001B0610[4] __attribute__((sda));
extern ParticleSettings D_L18_001B06F8 __attribute__((sda));
extern s32 func_002A77E0(s32);
extern s32 func_002A7820(s32, s32);
extern f32 func_002A7878(f32, f32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002ACB48(f32 *, f32);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);

/* Spawns a few upward-moving particles from the object's transformed effect point. */
void func_L18_003FCC48(char *self) {
    f32 point[4];
    f32 direction[4];
    s32 count, i, kind;
    *(Quad *)direction = 0;
    direction[2] = 1.0f;
    count = RandomIntBelow(2);
    for (i = 0; i < count + 1; i++) {
        matrix_mul_vec3(point, D_L18_001B0610, self + 0xC0);
        FastVecAdd(point, point, self + 0x10);
        AddRandomOffsetToVector(point, 0.5f);
        vec_scale_to_length(direction, direction, RandomFloatRange(8.0f, 12.0f) * 0.01666666753590107f);
        AddRandomOffsetToVector(direction, 0.06666667014360428f);
        kind = RandomIntBelow(2);
        SpawnEnemyRecord(point, direction, &D_L18_001B06F8, (void *)kind, RandomIntRange(-2, 2));
    }
}
