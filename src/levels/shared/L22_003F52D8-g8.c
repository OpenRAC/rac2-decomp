#include "include_asm.h"
#include "common.h"

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

extern u8 D_L22_001B9C80[];
extern s32 D_L22_001B2040;
extern f32 D_L22_001B0A0C __attribute__((sda));
extern f32 D_L22_001B0A10 __attribute__((sda));
extern f32 func_00282E48(void *a0, void *a1);
extern f32 func_00283CE0(s32 a0);
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7940(void);
extern void func_00283098(void *a0, void *a1, void *a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_L16_003C3A10(void *a0, void *a1, void *a2);

/* Sprinkles particles along the object's height, scattered around it with random speeds. */
void func_L22_003F52D8(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    f32 distanceScale = 60.0f / fast_vec_dist(D_L22_001B9C80, moby + 0x10);
    f32 count;
    f32 stepSize;
    f32 maxCount;
    f32 height;
    s32 i;
    Quad position, scratch, randomVec;

    if (distanceScale > 2.2f)
        distanceScale = 2.7f;
    height = *(f32 *)(state + 0xA0);
    count = distanceScale * distanceScale * height * D_L22_001B0A0C;
    maxCount = (f32)D_L22_001B2040 * D_L22_001B0A10;
    stepSize = height / count;
    if (count > maxCount)
        count = maxCount;
    for (i = 0; (f32)i < count; i++) {
        f32 progress = IntToFloat(i) * stepSize;
        f32 spread = distanceScale + progress * 0.1f;

        scratch.q = 0;
        scratch.f[0] = RandomSignedFloatRange(0.0f, spread);
        scratch.f[1] = RandomSignedFloatRange(0.0f, spread);
        scratch.f[2] = progress;
        position.q = scratch.q;
        matrix_mul_vec3(&position, &position, moby + 0xC0);
        FastVecAdd(&position, &position, moby + 0x10);
        randomVec.q = 0;
        randomVec.f[0] = RandomAngle();
        randomVec.f[1] = RandomAngle();
        randomVec.f[2] = RandomAngle();
        scratch.q = randomVec.q;
        CreateBouncingDebrisMoby(moby, &position, &scratch);
    }
}
