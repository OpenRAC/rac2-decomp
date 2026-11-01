#include "include_asm.h"

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

void func_PAL_L11_0039A880(char *self) {
    f32 point[4];
    f32 direction[4];
    s32 count, i;
    *(Quad *)direction = 0;
    count = func_002A77E0(5);
    for (i = 0; i < count + 1; i++) {
        *(Quad *)point = *(Quad *)(self + 0x10);
        func_002ACB48(point, 0.1f);
        func_002ACB48(direction, 0.002f);
        func_L02_003449D8(point, direction, &D_L18_001B0730, (void *)1, func_002A7820(-5, 5));
    }
}
