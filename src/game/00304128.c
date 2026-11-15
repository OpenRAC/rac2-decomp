#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef union { int q __attribute__((mode(TI))); float f[4]; } TI128;

extern int func_00282948(void *);
extern void func_00303568(void *, void *);
extern float func_00303DA8(void *, float);
extern void func_002C7BB8(void *, void *, int, int, float, int, int, float, float, int, int);

/* The address the buffer is copied from; its value differs from program to program. */
extern char ref_00304128_00[];

/* Emit an effect at a sampled surface point while its timer is active. */
/* Spawns an effect at a random surface point each time the timer runs out. */
void func_00304128(void *obj)
{
    void *state = *(void **)((char *)obj + 0x68);
    TI128 position;
    TI128 parameters;
    float distance;

    if (!(*(int *)((char *)state + 0x4C) & 8)) {
        if (FastFloatHelperD((char *)state + 0x8C) != 0) {
            GetRandomSurfacePoint(obj, &position);
            qcopy(&parameters, ref_00304128_00);
            parameters.f[2] = *(float *)((char *)state + 8);
            distance = GetDistanceIfInsideField(&position, 4.0f);
            if (1.0f < distance)
                SpawnSizeChangingParticle(&position, &parameters, *(int *)((char *)state + 0x80), 0x00808080,
                        *(float *)((char *)state + 0x78) * 210000.0f,
                        *(int *)((char *)state + 0x74), *(int *)((char *)state + 0x7C), 0.0f,
                        *(float *)((char *)state + 0x88), 0, 3);
            *(int *)((char *)state + 0x8C) = *(int *)((char *)state + 0x84);
        }
    }
}
