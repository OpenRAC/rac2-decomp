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
extern ParticleSettings D_L11_001AECB8 __attribute__((sda));
extern s32 func_002A77E0(s32);
extern s32 func_002A7820(s32, s32);
extern void func_002ACB48(f32 *, f32);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);

/* Throws out a small burst of random particles from the object's position. */
void func_L11_00397A30(char *self) {
    f32 point[4];
    f32 direction[4];
    s32 count, i;
    *(Quad *)direction = 0;
    count = RandomIntBelow(5);
    for (i = 0; i < count + 1; i++) {
        *(Quad *)point = *(Quad *)(self + 0x10);
        AddRandomOffsetToVector(point, 0.1f);
        AddRandomOffsetToVector(direction, 0.0016666668f);
        SpawnEnemyRecord(point, direction, &D_L11_001AECB8, (void *)1, RandomIntRange(-5, 5));
    }
}
