#include "names.h"

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4]; } Vector;
extern float func_0029F530(char *);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern float func_00283180(float), func_00283198(float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00335370(void *), func_003353C8(void *);
extern char *D_L01_001B264C __attribute__((sda));
extern struct { unsigned char prefix[0x80]; Vector position; unsigned char unused90[8]; float heading; } D_00189E20;

/* Blend the configured cameras, or orbit the player when either endpoint is absent. */
/* Same body as func_L01_00416E78, with this function's own callees. */
void func_L01_00397C98(char *object)
{
    int *state = *(int **)(object + 0x68);
    Vector position, rotation, first, second;
    float weight, heading, value;
    if (*(unsigned char *)(object + 0x42) == 1)
        value = GetMobyAnimationValue(object);
    else
        value = 170.0f;
    weight = value * 0.0058823530562222003937f;
    if (state[1] == -1 || state[2] == -1) {
        heading = FastAddRotations(weight * 0.69813179969787597656f - 0.34906589984893798828f, gHeroState.heading);
        position.f[0] = FastSinOrCosA(heading) * 5.0f;
        position.f[1] = FastSinOrCosB(heading) * 5.0f;
        position.f[2] = 0;
        FastVecAdd(&position, &position, &gHeroState.position);
        position.f[2] += 1.0f;
        ClearVector128(&rotation);
        rotation.f[2] = FastAddRotations(heading, 3.141590118408203125f);
        rotation.f[1] = weight * -0.17000000178813934326f;
    } else {
        lerp_vector(&position, D_L01_001B264C + state[1] * 0x80 + 0x30, D_L01_001B264C + state[2] * 0x80 + 0x30, weight);
        first.whole = ((Vector *)(D_L01_001B264C + state[1] * 0x80 + 0x70))->whole;
        second.whole = ((Vector *)(D_L01_001B264C + state[2] * 0x80 + 0x70))->whole;
        rotation.f[2] = FastAddRotations(fast_subtract_rotations(second.f[2], first.f[2]) * weight, first.f[2]);
        rotation.f[1] = FastAddRotations(fast_subtract_rotations(second.f[1], first.f[1]) * weight, first.f[1]);
        rotation.f[0] = FastAddRotations(fast_subtract_rotations(second.f[0], first.f[0]) * weight, first.f[0]);
    }
    CopyVectorToSelectedObject(&position);
    SetCameraStateRotation(&rotation);
}
