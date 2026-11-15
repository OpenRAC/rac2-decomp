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
extern ParticleSettings D_L18_001B0730 __attribute__((sda));
extern s32 func_002A77E0(s32);
extern s32 func_002A7820(s32, s32);
extern void func_002ACB48(f32 *, f32);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);

/* Emits a small randomized spray from the object's saved effect origin. */
void func_L18_003FCD70(char *self) {
    f32 point[4];
    f32 direction[4];
    char *state = *(char **)(self + 0x68);
    s32 count, i;
    *(Quad *)direction = 0;
    count = RandomIntBelow(5);
    for (i = 0; i < count + 1; i++) {
        *(Quad *)point = *(Quad *)(state + 0x90);
        AddRandomOffsetToVector(point, 0.5f);
        AddRandomOffsetToVector(direction, 0.008333333767950535f);
        SpawnEnemyRecord(point, direction, &D_L18_001B0730, (void *)1, RandomIntRange(-5, 5));
    }
}
