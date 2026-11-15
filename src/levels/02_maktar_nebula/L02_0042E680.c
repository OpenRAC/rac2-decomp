#include "include_asm.h"
#include "names.h"

/* func_L02_0042E680 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern void func_002ACB48(void *, float);
extern int D_L02_001B2410[2] __attribute__((sda));
extern int D_L02_001B2418[2] __attribute__((sda));

/* Throws a fan of thirty sparks out in front of the object, each with its own speed, size and colour. */
void func_L02_0042E680(u8 *moby, float lo, float hi) {
    float offset[4];
    float origin[4];
    float upSpread[4];
    float sideSpread[4];
    float velocity[4];
    float pull[4];
    float sparkPos[4];
    int i;
    float scale;
    int partA, partB, partC;
    int colorA, colorB;
    float k = 0.0025f;

    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = 4.0f;
    offset[3] = 1.0f;
    FastVecAdd(origin, offset, moby + 0x10);
    i = 29;
    do {
        vec_scale_to_length(sideSpread, moby + 0xC0, RandomFloatRange(-0.8f, 0.8f));
        vec_scale_to_length(upSpread, moby + 0xE0, RandomFloatRange(0.25f, 1.0f));
        FastVecAdd(velocity, moby + 0xD0, sideSpread);
        FastVecAdd(velocity, velocity, upSpread);
        vec_scale_to_length(velocity, velocity, RandomFloatRange(lo, hi));
        scale = RandomFloatRange(0.5f, 1.5f);
        partA = FloatToInt(scale * 10.0f);
        partB = FloatToInt(scale * 30.0f);
        partC = FloatToInt(scale * 7.0f);
        velocity[3] = RandomFloatRange(0.2f, 0.6f);
        ClearVector128(pull);
        pull[2] = -k * (float)(partA + partB + partC);
        FastVecAdd(pull, pull, velocity);
        pull[3] = 0.01f;
        colorA = FastTweenColor(D_L02_001B2410[0], D_L02_001B2410[1], RandomFloatRange(0.0f, 1.0f));
        colorB = FastTweenColor(D_L02_001B2418[0], D_L02_001B2418[1], RandomFloatRange(0.0f, 1.0f));
        *(TI128 *)sparkPos = *(TI128 *)origin;
        AddRandomOffsetToVector(sparkPos, 0.25f);
        SpawnTrailParticle_002BAA28(sparkPos, velocity, pull, colorA, colorB, partA, partB, partC, 0x1003C);
    } while (--i >= 0);
}
