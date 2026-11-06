/* func_PAL_L00_00415690, the PAL copy of func_L00_00410888: the same C, where 0.016666668f
   becomes 0.020000001f, 0.0022222223f becomes 0.0032000002f, both lives take the 50 Hz scale
   and the second loop is written counting up (check_dbra_loop reverses it, which sets its
   counter after the hoisted divisor, as retail does).
   -fno-sched-interblock: retail's first loop has no interblock motion. The second loop gets
   none anyway, being over the scheduler's 100-LUID region limit; this source's first loop is
   only 82. */
#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_00282D30(void *, void *, float);
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern void func_002C6DD8(void *, void *, int, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern char D_0018A550[];

typedef struct {
    char pad[0x110];
    float velocity[4];
    char pad2[0x220];
    int flag;
} EffectHero;

extern EffectHero D_00189E20;
extern float D_L00_001B1300 __attribute__((sda));
extern float D_L00_001B1304 __attribute__((sda));
extern int D_L00_001B1308 __attribute__((sda));
extern int D_L00_001B130C __attribute__((sda));
extern int D_L00_001B1310 __attribute__((sda));
extern float D_L00_001B1314 __attribute__((sda));
extern float D_L00_001B1318 __attribute__((sda));
extern float D_L00_001B131C __attribute__((sda));
extern float D_L00_001B1320 __attribute__((sda));
extern float D_L00_001B1324 __attribute__((sda));
extern float D_L00_001B1328 __attribute__((sda));

/* Emit two groups of particles around the object, rotating each emission direction. */
void func_PAL_L00_00415690(char *object, int mode)
{
    float rotation[4], direction[4], basis[4], position[4], point[4], velocity[4], offset[4];
    float angle, jitter, scale, speed, spread;
    int i, j, life, kind, life2;

    *(EffectVector *)basis = 0;
    basis[0] = 0.3f;
    basis[1] = -1.0f;
    basis[3] = 1.0f;
    func_00283098(basis, basis, object + 0xc0);
    angle = 0.0f;
    func_00282CC0(position, object + 0x10, basis);
    func_002ACEC0(basis, D_0018A550, D_0018A550 + 0x10, 0.349065899848938f);
    qcopy(direction, basis);
    for (i = 0; i < mode * 20 + 20; i++) {
        angle = func_00283B98(angle, func_002A7878(0.0f, 0.6283186f));
        func_00282D30(offset, direction, func_002A7878(7.0f, 60.0f) * 0.020000001f);
        life = (func_002A7820(10, 30) * 5 + 2) / 6;
        point[0] = position[0] + func_002A78D8(0.0f, 0.2f);
        point[1] = position[1] + func_002A78D8(0.0f, 0.2f);
        point[2] = position[2] + func_002A78D8(0.0f, 0.2f);
        func_002C6DD8(point, offset, life, 0.0032000002f);
        if (func_00282C48(angle) > 0.00001f) {
            func_002AB668(rotation, D_0018A550, angle);
            func_002ACDE8(direction, basis, rotation);
        }
    }

    func_002ACEC0(basis, D_0018A550, D_0018A550 + 0x10, D_L00_001B1300 * 0.017453294f);
    angle = 0.0f;
    qcopy(direction, basis);
    /* Only external calls read this local vector after its clear. */
    qzero_nc(offset);
    if (D_00189E20.flag)
        func_00282D30(offset, D_00189E20.velocity, 1.7f);
    scale = D_L00_001B1324;
    speed = D_L00_001B1328;
    spread = D_L00_001B1304;
    if (mode) {
        scale = 2.0f;
        speed = 10000.0f;
        spread = 0.8f;
    }
    for (j = 0; j < 20; j++) {
        angle = func_00283B98(angle, func_002A7878(0.0f, 0.6283186f));
        func_00282D30(velocity, direction,
                      func_002A7878(D_L00_001B1318 * 0.020000001f,
                                    D_L00_001B131C * 0.020000001f));
        func_00282CC0(velocity, velocity, offset);
        kind = (D_L00_001B1310 * 5 + 2) / 6;
        life2 = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        point[0] = position[0] + func_002A78D8(0.0f, spread);
        point[1] = position[1] + func_002A78D8(0.0f, spread);
        point[2] = position[2] + func_002A78D8(0.0f, spread);
        jitter = func_002A7878(D_L00_001B1320, scale) * 210000.0f;
        func_00282CF0(point, point, velocity);
        func_002C16C0(point, velocity, kind, D_L00_001B1308, D_L00_001B130C,
                      life2, jitter, speed, D_L00_001B1314, 0.0f, 0.0f);
        if (func_00282C48(angle) > 0.00001f) {
            func_002AB668(rotation, D_0018A550, angle);
            func_002ACDE8(direction, basis, rotation);
        }
    }
}
