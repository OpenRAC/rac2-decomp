#include "include_asm.h"
#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern int D_L16_001B10E0 __attribute__((sda));
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00282C48(float);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L16_003C3A10(void *, void *, void *);

/* Spawns a bounded set of random vectors outside the central rectangle. */
/* Spawns random bursts around the object, skipping a box in the middle. */
void func_L16_003F55A0(char *object)
{
    float position[4];
    float random[4];
    float direction[4];
    int i;
    float scale;
    for (i = 0; i < D_L16_001B10E0; ++i) {
        *(Quadword *)random = 0;
        random[0] = RandomSignedFloatRange(0.0f, 26.0f);
        random[1] = RandomSignedFloatRange(0.0f, 8.0f);
        random[2] = RandomFloatRange(0.0f, 30.0f);
        *(Quadword *)position = *(Quadword *)random;
        if (FloatAbs(position[0]) < 9.0f && FloatAbs(position[2]) < 25.0f)
            continue;
        scale = *(float *)(object + 44) / *(float *)(*(char **)(object + 36) + 36);
        FastVecScale(position, position, scale);
        matrix_mul_vec3(position, position, object + 192);
        FastVecAdd(position, position, object + 16);
        *(Quadword *)direction = 0;
        direction[0] = RandomAngle();
        direction[1] = RandomAngle();
        direction[2] = RandomAngle();
        *(Quadword *)random = *(Quadword *)direction;
        CreateBouncingDebrisMoby(object, position, random);
    }
}

