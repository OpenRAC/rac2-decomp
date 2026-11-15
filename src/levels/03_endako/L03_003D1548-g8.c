#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L03_001B064C __attribute__((sda));
extern char D_L03_001A8F20[] __attribute__((sda));
typedef struct {
    char pad[0x1C];
    int count;
    float pos[4];
    char pad2[0x10];
    float normal[4];
} HitResult;
extern HitResult D_L03_001BFDC0;
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_002A7A00(void *, float, float);
extern void func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_003E3258(void *, int, int);
extern void func_002A7750(void *, int, int);
extern int func_00282948(void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_002AA800(void *, int, float, float);
extern float func_002AA2E8(void *, float, float);
extern float func_00283B98(float, float);
extern void func_0029F338(void *);

/* Advances the trail, resolves a collision, then settles and fades the object. */
void func_L03_003D1548(char *moby)
{
    float nextPosition[4], traceEnd[4], matrix[12], particlePosition[4], trailPosition[4], trailStep[4];
    int i, color;

    char *vars = *(char **)(moby + 0x68);
    switch (*(u8 *)(moby + 0x20)) {
    case 0: {
        float value;
        FastVecAdd(nextPosition, moby + 0x10, vars);
        vec_scale_to_length(traceEnd, moby + 0xc0, D_L03_001B064C);
        FastVecAdd(traceEnd, traceEnd, nextPosition);
        make_hit_descriptor(matrix, moby, 1, D_L03_001A8F20, (float)*(int *)(vars + 0x38));
        *(TI128 *)(trailPosition) = *(TI128 *)(moby + 0x10);
        FastVecScale(trailStep, vars, -0.2f);
        i = 4;
        do {
            i--;
            value = RandomFloatRange(0.1f, 0.3f);
            color = RandomIntBelow(255);
            RandomDirectionVector(particlePosition, 0.0f, 0.1f);
            FastVecAdd(particlePosition, particlePosition, trailPosition);
            SpawnGravityFadeParticle(particlePosition, D_L03_001A8F20, 15, 0x808080, color, 32, 0, value*210000.0f, value*42000.0f, 0.0f, 0);
            FastVecAdd(trailPosition, trailPosition, trailStep);
        } while (i >= 0);
        if (CollLine(nextPosition, traceEnd, 0, moby, matrix) && D_L03_001BFDC0.count > 0) {
            *(TI128 *)(vars + 0x20) = *(TI128 *)(D_L03_001BFDC0.pos);
            *(TI128 *)(vars + 0x10) = *(TI128 *)(D_L03_001BFDC0.normal);
            *(float *)(vars + 0x34) = D_L03_001B064C;
            SpawnSparkBurstAtPosition(D_L03_001BFDC0.pos, 10, 1);
            SetMobyState(moby, 1, -1);
        }
        *(TI128 *)(moby + 0x10) = *(TI128 *)(nextPosition);
        if (FastFloatHelperD(vars + 0x30)) MarkMobySpawned(moby);
        break;
    }
    case 1: {
        void *rotation = moby + 0xf4;
        float value;
        value = FastMatrixHelperA(vec_length_xy(vars + 0x10), *(float *)(vars + 0x18));
        StepAngleTowardTarget(rotation, 0, value, 0.104719773f);
        *(TI128 *)(moby + 0x10) = *(TI128 *)(vars + 0x20);
        vec_scale_to_length(nextPosition, moby + 0xc0, -*(float *)(vars + 0x34));
        FastVecAdd(moby + 0x10, moby + 0x10, nextPosition);
        ApproachValue(vars + 0x34, 0.0f, 0.00500000035f);
        { float amount = *(float *)(vars + 0x34);
          value = amount*1.0471977f;
          *(float *)(moby + 0xf0) = FastAddRotations(*(float *)(moby + 0xf0), value); }
        if (*(float *)(vars + 0x34) <= 0.0f) {
            SetMobyState(moby, 2, -1);
            *(int *)(vars + 0x30) = 60;
        }
        break;
    }
    case 2:
        if (FastFloatHelperD(vars + 0x30)) goto finish;
        break;
    }
    return;
finish:
    if (*(u8 *)(moby + 0x23) < 4) MarkMobySpawned(moby);
    else *(u8 *)(moby + 0x23)-=4;
}
