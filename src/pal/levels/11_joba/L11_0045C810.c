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
extern float fast_vec_dist(void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float fast_subtract_rotations(float, float);
extern float math_random_signed_float_range(float, float);
extern void gfx_add_draw_callback_third(void *, char *);
extern float mat_fast_helper_a(float a, float b);
extern float math_random_float_range(float a, float b);
extern float math_random_angle(void);
extern float vec_distance_xy(void *p, float *v);
extern void FastVecSub(float *out, float *a, float *b);
extern void joba_ring_effect_draw_sprites(void);

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

            newRadius = math_random_float_range(state->minRadius, state->maxRadius);
            newAzimuth = math_random_angle();
            vec_build_spherical_offset(state->points[i], newRadius, newAzimuth, math_random_angle());
            FastVecAdd(state->points[i], obj->position, state->points[i]);
        }
    }

    if (obj->stage == 1) {
        gfx_add_draw_callback_third(joba_ring_effect_draw_sprites, (char *)obj);
        for (j = 0; j < state->count; j++) {
            point = state->points[j];
            FastVecSub(scratch, obj->position, point);
            azimuth = mat_fast_helper_a(point[0] - obj->position[0], point[1] - obj->position[1]);
            elevation = mat_fast_helper_a(vec_distance_xy(obj->position, point),
                                      point[2] - obj->position[2]);
            azimuth = fast_subtract_rotations(azimuth, state->f9C * 0.017453294f);
            elevation = fast_subtract_rotations(elevation,
                                      math_random_signed_float_range(state->fA4, state->fA0) * 0.017453294f);
            if (state->maxElevation < elevation)
                elevation = state->maxElevation;
            if (elevation < state->minElevation)
                elevation = state->minElevation;

            radius = fast_vec_dist(obj->position, point);
            step = math_random_signed_float_range(state->f98 * 0.020000001f, state->f94 * 0.020000001f);
            radius += step;
            if (state->maxRadius < radius)
                radius = state->maxRadius;
            if (radius < state->minRadius)
                radius = state->minRadius;

            vec_build_spherical_offset(point, radius, azimuth, elevation);
            FastVecAdd(point, obj->position, point);
        }
    }
}

