#include "include_asm.h"



#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int moby_move_over_ground(char *, char *, char *, int, float, float, float, float);
extern float ApproachValue(float *, float, float);
extern void math_step_value_toward_target(float *, char *, float, float, float, float);
extern void math_approach_target_with_direction_mode(char *, float, float, float, float, char *, int);
extern float FastDiffRots(float, float);
extern int ComputeRegionRouteHeading(char *, int, float *, char *, int, char *, char *, float,
                             float);
extern void FastVecAdd(void *, void *, void *);

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int func_PAL_L06_004235E8(char *a0, char *a1, float f1, float f2, float f3, float f4)
{
    char *st = *(char **)(a0 + 0x68);
    float v[4];
    float w[4];
    float x[4];
    float d = 0.0f;
    float out;
    float f24;
    float t;
    int ret = 0;

    FastVecSub(v, (float *)a1, (float *)(a0 + 0x10));
    v[2] = 0.0f;
    f24 = FastVecLength(v);
    t = f2 * 0.0012f;
    if (f3 < f24) {
        int c = *(int *)(st + 0x480);

        out = 0.0f;
        ComputeRegionRouteHeading(a0 + 0x10, (int)a1, &out, st + 0x260, c, st + 0x488,
                          st + 0x48C, f4, 0.5f);
        math_approach_target_with_direction_mode(a0 + 0xF8, out, 0.005445428f,
                      0.005445428f, 0.35604724f, st + 0x474, 0);
        if (FastDiffRots(*(float *)(a0 + 0xF8), out) < 1.3089970350265503f) {
            math_step_value_toward_target(&d, st + 0x470, f24, t, t, f2 * 0.020000001f);
        } else {
            *(float *)(st + 0x470) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(a0 + 0xF8, f1, 0.005445428f,
                      0.005445428f, 0.35604724f, st + 0x474, 0);
        ApproachValue((float *)(st + 0x470), 0.0f, t);
        if (*(float *)(st + 0x470) == 0.0f) {
            if (FastDiffRots(*(float *)(a0 + 0xF8), f1) < 0.0872664749622345f) {
                *(float *)(st + 0x474) = 0.0f;
                ret = 1;
            }
        }
    }
    vec_scale_to_length(w, (float *)(a0 + 0xC0), *(float *)(st + 0x470));
    FastVecAdd(x, w, (float *)(a0 + 0x10));
    if (moby_move_over_ground(a0, a0 + 0x10, (char *)x, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(st + 0x5A8) = *(int *)(st + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(st + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(st + 0x5A8) = 0;
    ret = 1;
done:
    return ret;
}

