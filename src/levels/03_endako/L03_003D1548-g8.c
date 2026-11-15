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
void func_L03_003D1548(char *obj)
{
    float nextPosition[4], traceEnd[4], matrix[12], particlePosition[4], trailPosition[4], trailStep[4];
    int i, color;

    char *state = *(char **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0: {
        float f;
        FastVecAdd(nextPosition, obj + 0x10, state);
        vec_scale_to_length(traceEnd, obj + 0xc0, D_L03_001B064C);
        FastVecAdd(traceEnd, traceEnd, nextPosition);
        make_hit_descriptor(matrix, obj, 1, D_L03_001A8F20, (float)*(int *)(state + 0x38));
        *(TI128 *)(trailPosition) = *(TI128 *)(obj + 0x10);
        FastVecScale(trailStep, state, -0.2f);
        i = 4;
        do {
            i--;
            f = func_002A7878(0.1f, 0.3f);
            color = func_002A77E0(255);
            func_002A7A00(particlePosition, 0.0f, 0.1f);
            FastVecAdd(particlePosition, particlePosition, trailPosition);
            func_002C65A0(particlePosition, D_L03_001A8F20, 15, 0x808080, color, 32, 0, f*210000.0f, f*42000.0f, 0.0f, 0);
            FastVecAdd(trailPosition, trailPosition, trailStep);
        } while (i >= 0);
        if (CollLine(nextPosition, traceEnd, 0, obj, matrix) && D_L03_001BFDC0.count > 0) {
            *(TI128 *)(state + 0x20) = *(TI128 *)(D_L03_001BFDC0.pos);
            *(TI128 *)(state + 0x10) = *(TI128 *)(D_L03_001BFDC0.normal);
            *(float *)(state + 0x34) = D_L03_001B064C;
            func_L00_003E3258(D_L03_001BFDC0.pos, 10, 1);
            func_002A7750(obj, 1, -1);
        }
        *(TI128 *)(obj + 0x10) = *(TI128 *)(nextPosition);
        if (func_00282948(state + 0x30)) func_0029F338(obj);
        break;
    }
    case 1: {
        void *rotation = obj + 0xf4;
        float f;
        f = func_00283248(vec_length_xy(state + 0x10), *(float *)(state + 0x18));
        StepAngleTowardTarget(rotation, 0, f, 0.104719773f);
        *(TI128 *)(obj + 0x10) = *(TI128 *)(state + 0x20);
        vec_scale_to_length(nextPosition, obj + 0xc0, -*(float *)(state + 0x34));
        FastVecAdd(obj + 0x10, obj + 0x10, nextPosition);
        ApproachValue(state + 0x34, 0.0f, 0.00500000035f);
        { float amount = *(float *)(state + 0x34);
          f = amount*1.0471977f;
          *(float *)(obj + 0xf0) = FastAddRotations(*(float *)(obj + 0xf0), f); }
        if (*(float *)(state + 0x34) <= 0.0f) {
            func_002A7750(obj, 2, -1);
            *(int *)(state + 0x30) = 60;
        }
        break;
    }
    case 2:
        if (func_00282948(state + 0x30)) goto finish;
        break;
    }
    return;
finish:
    if (*(u8 *)(obj + 0x23) < 4) func_0029F338(obj);
    else *(u8 *)(obj + 0x23)-=4;
}
