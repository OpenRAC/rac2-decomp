#include "include_asm.h"

#include "common.h"
typedef int TrailVector128 __attribute__((mode(TI)));
typedef struct { int values[5]; } TrailParticleTypes;
typedef struct { float values[10]; } TrailParticleSizes;
extern TrailParticleTypes D_L04_001B0AD8;
extern TrailParticleSizes D_L04_001B0AF0;
extern int D_L04_001B0B18 __attribute__((sda));
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L04_00365B68(void *, void *, void *, int, int, float, float, float);
extern void func_PAL_L04_0041A660(void *, void *, void *, void *);

void func_PAL_L04_0041AB08(char *owner, void *pos, void *dir, float length)
{
    struct {
        struct { float v[4]; } __attribute__((aligned(16))) origin;
        TrailParticleTypes types;
        TrailParticleSizes sizes __attribute__((aligned(16)));
        float step[4] __attribute__((aligned(16)));
        float point[4] __attribute__((aligned(16)));
        float offset[4] __attribute__((aligned(16)));
        float bias[4] __attribute__((aligned(16)));
    } frame;
    void *origin = &frame.origin;
    float chance, angle, inc, magnitude;
    int count, type, i;

    *(TrailVector128 *)origin = *(TrailVector128 *)pos;
    frame.types = D_L04_001B0AD8;
    frame.sizes = D_L04_001B0AF0;
    chance = func_002A7878(0.0f, 1.0f);
    func_00282D30(frame.bias, owner + 0xC0, 0.05f);
    func_00282D30(frame.step, dir, 1.0f / length);
    func_00282DB0(frame.step, owner + 0xC0);
    if (*(short *)(owner + 0xAA) == 0xB2D)
        count = (int)(length + length) + 1;
    else
        count = (int)(length * 5.0f) + 2;
    type = -1;
    inc = func_002A7878(0.0f, 1.5707964f) + 0.1f;
    angle = func_002A7878(0.0f, 3.926991f);
    if (chance < 0.05f)
        type = 0;
    else if (chance < 0.1f)
        type = 1;
    else if (chance < 0.15f)
        type = 2;
    for (i = 0; i < count; i++) {
        angle = func_00283B98(angle, inc);
        frame.offset[0] = func_00283180(angle);
        frame.offset[1] = func_00283198(angle);
        frame.offset[2] = 0.3f;
        magnitude = func_00282DB0(frame.offset, frame.step);
        func_00282D30(frame.point, frame.offset,
            (length * 0.1f + frame.sizes.values[D_L04_001B0B18] * 1.05f) * 0.020000001f);
        func_00282D30(frame.offset, frame.offset, 0.15f);
        func_00282CC0(frame.offset, frame.offset, origin);
        func_00282CC0(frame.offset, frame.offset, frame.bias);
        frame.offset[2] -= 0.2f;
        if (i == 1 && type >= 0) {
            func_00282CC0(frame.point, frame.point, dir);
            func_PAL_L04_00365B68(frame.offset, frame.point, dir, frame.types.values[type], type,
                magnitude * 0.01f + 0.05f, frame.offset[2] - 0.25f, 0.004f);
        } else {
            func_PAL_L04_0041A660(owner, frame.point, dir, owner + 0x10);
        }
        if (++D_L04_001B0B18 >= 10)
            D_L04_001B0B18 = 0;
    }
}
