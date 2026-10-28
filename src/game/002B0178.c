#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int D_001A8CA0[] __attribute__((sda));
extern int D_001A8CA4[] __attribute__((sda));
extern Vector D_001B17D0;
extern Vector D_001BAFA0;
extern float D_001BAFA8;
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002B00D8(void *, float *, float *, float);
extern float func_00282E48(void *, void *);

float func_002B0178(Vector *position, void *owner, Vector *output)
{
    Vector low, high;
    float distance, result;
    if (D_001A8CA0[0] == 0) {
        qcopy(&low, position);
        low.f[2] = 0.01f;
        qcopy(&high, position);
        high.f[2] += 0.5f;
        if (func_002761F8(&high, &low, 2, owner, 0)) {
            if (output != 0)
                qcopy(output, &D_001BAFA0);
            return position->f[2] - D_001BAFA8;
        }
        if (output != 0)
            qcopy(output, position);
        return position->f[2];
    }
    qcopy(&low, &D_001B17D0);
    if (D_001A8CA4[0] != 0) {
        qcopy(&low, position);
        func_002B00D8(&low, low.f, low.f, -10.0f);
    }
    func_002B00D8(position, high.f, position->f, -0.5f);
    distance = func_00282E48(position, &low);
    if (func_002761F8(&high, &low, 2, owner, 0)) {
        if (output != 0)
            qcopy(output, &D_001BAFA0);
        result = func_00282E48(position, &D_001BAFA0);
        if (distance < func_00282E48(&D_001BAFA0, &low))
            result = -result;
        return result;
    }
    if (output != 0)
        qcopy(output, position);
    return distance;
}
