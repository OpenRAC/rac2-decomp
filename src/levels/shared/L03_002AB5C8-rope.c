#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } RopeVector;
extern RopeVector D_L03_00238040[][16];

typedef struct {
    unsigned char pad_0[0x28];
    int groups[4];
    int count;
    int flags;
    unsigned char pad_40[0x44];
    float cycle;
    float cycleRate;
    unsigned char pad_8C[0x4];
    float jitterScale;
    float phaseA;
    float rate;
    unsigned char pad_9C[0x4];
    float amplitude;
    float swayScale;
    float phaseB;
    unsigned char pad_AC[0x28];
    float radius;
    unsigned char pad_D8[0x4];
    int pool;
    float center[4];
} RopeState;

extern float (*D_L03_001FE700[])[4];
extern RopeVector D_L03_00237F40[];
extern float D_00189EA0[];
extern float func_00283B98(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283248(float, float);


void func_L03_0038B5D8(u8 *object)
{
    RopeVector toward, relative, blended, tangent, radial, jitter;
    RopeState *state = *(RopeState **)(object + 0x68);
    int row, column;
    float segmentLength, vertical, phase, angle, magnitude;

    state->phaseA = func_00283B98(state->phaseA, state->rate);
    state->phaseB = func_00283B98(state->phaseB, state->rate);
    state->cycle += state->cycleRate;
    if (state->cycle > 1.0f)
        state->cycle -= 1.0f;
    for (row = 0; row < 4; row++) {
        if ((state->flags & 1) && state->groups[row] >= 0) {
            RopeVector *source = (RopeVector *)D_L03_001FE700[state->groups[row]];
            int limit = state->count;
            for (column = 0; column < limit; column++)
                qcopy_nc(&D_L03_00238040[state->pool + row][column], &source[column + 1]);
            if (state->flags & 8) {
                float distance, strength;
                func_00282CF0(&toward, D_00189EA0, state->center);
                distance = func_00282DF0(&toward);
                func_00282F20(&toward, &toward, 1.1f);
                if (!(distance > state->radius + 1.1f)) {
                    strength = 1.0f - (distance - 1.1f) / state->radius;
                    for (column = 0; column < state->count; column++) {
                        float length, amount;
                        qcopy(&relative, &D_L03_00238040[state->pool + row][column]);
                        func_00282CF0(&relative, &relative, state->center);
                        length = func_00282DF0(&relative);
                        if (length > 1.1f)
                            length = 1.1f;
                        length *= 0.9090909f;
                        amount = strength * (1.0f - length);
                        func_00282D30(&blended, &toward, amount);
                        func_00282D30(&relative, &relative, 1.0f - amount);
                        func_00282CC0(&blended, &blended, &relative);
                        func_00282CC0(&D_L03_00238040[state->pool + row][column], &blended, state->center);
                    }
                }
            }
        } else {
            tangent.quad = 0;
            tangent.f[3] = 1.0f;
            switch (row) {
            case 0:
                tangent.f[2] += 1.1f;
                break;
            case 1:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] -= 0.6395348906517029f;
                break;
            case 2:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] -= 0.6395348906517029f;
                tangent.f[0] += 0.6395348906517029f;
                break;
            default:
                tangent.f[2] -= 0.6395348906517029f;
                tangent.f[1] += 0.785714328289032f;
                break;
            }
            for (column = 0; column < state->count; column++) {
                func_00282F20(&radial, &tangent, (float)column / ((float)state->count - 0.5f));
                qcopy_nc(&D_L03_00238040[state->pool + row][column], &radial);
                func_00282CC0(&D_L03_00238040[state->pool + row][column], &D_L03_00238040[state->pool + row][column], state->center);
            }
        }
    }
    func_00282CF0(&tangent, &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((state->pool) * 256 + (1) * 16))),
                             &(*(RopeVector *)((unsigned int)D_L03_00238040 + ((state->pool) * 256 + (0) * 16))));
    segmentLength = func_00282DF0(&tangent);
    for (column = 0; column < state->count; column++) {
        vertical = 0.0f;
        phase = 0.0f;
        if (!(state->flags & 0x40))
            func_00282D30(&jitter, &D_L03_00237F40[column], state->jitterScale * segmentLength);
        if (!(state->flags & 0x80)) {
            float firstPhase = func_002ABB18(state->phaseA + (float)column * -1.780236005783081f);
            float first = state->amplitude * func_00283198(firstPhase);
            phase = func_002ABB18(state->phaseB + (float)column * -1.5184365510940552f);
            vertical = segmentLength * (first * func_00283198(phase));
        }
        if (!(state->flags & 0x100)) {
            angle = func_00283B98(func_00283248(tangent.f[0], tangent.f[1]), 1.5707964897155762f);
            magnitude = segmentLength * state->swayScale * func_00283180(phase);
            radial.f[0] = func_00283180(angle) * magnitude;
            radial.f[1] = func_00283198(angle) * magnitude;
            radial.f[2] = 0.0f;
        }
        for (row = 0; row < 4; row++) {
            qcopy_nc(&D_L03_00238040[state->pool + row + 4][column], &D_L03_00238040[state->pool + row][column]);
            if (column != 0 && column != state->count - 1) {
                if (!(state->flags & 0x40)) {
                    func_00282CC0(&D_L03_00238040[state->pool + row + 4][column], &D_L03_00238040[state->pool + row + 4][column], &jitter);
                    func_00282CC0(&D_L03_00238040[state->pool + row][column], &D_L03_00238040[state->pool + row][column], &jitter);
                }
                if (!(state->flags & 0x80))
                    D_L03_00238040[state->pool + row + 4][column].f[2] += vertical;
                if (!(state->flags & 0x100))
                    func_00282CC0(&D_L03_00238040[state->pool + row + 4][column], &D_L03_00238040[state->pool + row + 4][column], &radial);
            }
        }
    }
}
