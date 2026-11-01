#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 stage;
    u8 pad21[0x10];
    u8 active;
    u8 pad32[0x68 - 0x32];
    void *state;
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0xAA - 0x70];
    s16 id;
} JobaObject;
typedef struct {
    float points[8][4];
    s32 count;
    float minRadius;
    float maxRadius;
    float maxElevation;
    float minElevation;
    float f94;
    float f98;
    float f9C;
    float fA0;
    float fA4;
} JobaRingState;
extern JobaObject *D_L11_001C4D80[];
extern float func_00282E48(void *, void *);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283BE0(float, float);
extern float func_002A78D8(float, float);
extern void func_L00_002E6EF8(void *, char *);
extern float func_00283248(float a, float b);
extern float func_002A7878(float a, float b);
extern float func_002A7940(void);
extern float func_00282E80(void *p, float *v);
extern void func_00282CF0(float *out, float *a, float *b);
extern void func_L11_00456EA0(void);

/* Keeps the ring's points inside the configured radial and angular limits. */
void func_PAL_L11_0045C810(JobaObject *obj)
{
    JobaRingState *state = obj->state;
    float *point;
    int i, j;
    float scratch[4];
    float radius, azimuth, elevation, step;

    if (obj->stage == 0) {
        if (state->count > 8)
            state->count = 8;
        obj->stage = 1;
        for (i = 0; i < state->count; i++) {
            float newRadius, newAzimuth;

            newRadius = func_002A7878(state->minRadius, state->maxRadius);
            newAzimuth = func_002A7940();
            func_002AF000(state->points[i], newRadius, newAzimuth, func_002A7940());
            func_00282CC0(state->points[i], obj->position, state->points[i]);
        }
    }

    if (obj->stage == 1) {
        func_L00_002E6EF8(func_L11_00456EA0, (char *)obj);
        for (j = 0; j < state->count; j++) {
            point = state->points[j];
            func_00282CF0(scratch, obj->position, point);
            azimuth = func_00283248(point[0] - obj->position[0], point[1] - obj->position[1]);
            elevation = func_00283248(func_00282E80(obj->position, point),
                                      point[2] - obj->position[2]);
            azimuth = func_00283BE0(azimuth, state->f9C * 0.017453294f);
            elevation = func_00283BE0(elevation,
                                      func_002A78D8(state->fA4, state->fA0) * 0.017453294f);
            if (state->maxElevation < elevation)
                elevation = state->maxElevation;
            if (elevation < state->minElevation)
                elevation = state->minElevation;

            radius = func_00282E48(obj->position, point);
            step = func_002A78D8(state->f98 * 0.020000001f, state->f94 * 0.020000001f);
            radius += step;
            if (state->maxRadius < radius)
                radius = state->maxRadius;
            if (radius < state->minRadius)
                radius = state->minRadius;

            func_002AF000(point, radius, azimuth, elevation);
            func_00282CC0(point, obj->position, point);
        }
    }
}

