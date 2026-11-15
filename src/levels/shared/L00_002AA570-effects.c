#include "common.h"

/* Resident fields accessed by the paired particle emitter. */
typedef struct {
    char pad0[128];
    float x;
    float y;
    char pad88[16];
    float angle;
    char pad9c[660];
    float z;
    char pad334[1812];
    unsigned short counter;
} ParticleResidentFields;
extern ParticleResidentFields D_00189E20_20;
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_00338AE0(float, float, float *, float *, float *);

void func_L00_002AA570(char *self, int arg1)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float f;
    float r;
    int n;
    int i;


    n = D_00189E20_20.counter + 1;
    D_00189E20_20.counter = n;
    if (arg1 < (short)n) {
        for (i = 0; i < 2; i++) {
            if (i == 0)
                f = FastAddRotations(D_00189E20_20.angle, 0.785398006f);
            else
                f = fast_subtract_rotations(D_00189E20_20.angle, 0.785398006f);
            v[0] = func_00283180(f) * 0.0100000007f;
            v[1] = func_00283198(f) * 0.0100000007f;
            w[0] = D_00189E20_20.x + v[0] * 18.0f;
            w[1] = D_00189E20_20.y + v[1] * 18.0f;
            w[2] = D_00189E20_20.z;
            v[2] = 0.0f;
            v[0] = v[0] - func_00283180(D_00189E20_20.angle) * 0.0250000022f;
            v[1] = v[1] - func_00283198(D_00189E20_20.angle) * 0.0250000022f;
            r = func_002A7878(0.4f, 0.5f);
            func_L00_00338AE0(r, i == 0 ? 2.0f : -2.0f, w, v, &D_00189E20_20.z);
            D_00189E20_20.counter = self == 0 ? 0 : func_002A77E0((int)self);
        }
    }
}
