#include "include_asm.h"

#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vec4;
extern void func_PAL_002ABCB8(void *, void *, void *);
extern float vec_length_xy(void *);
extern void ApproachValue(float *, float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int GetCollHitMaterial(void);
extern void *moby_spawn_scaled_effect(void *, float);
extern float coll_get_ground_height_under_object(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern void MobySpringTurn(void *, void *, float, float, float, float);
extern int coll_process_hit(float, void *, int, void *, void *);
extern float IntToFloat(int);
extern int moby_is_in_special_class_range(void *);
extern void part_queue_impact_effect(void *, float, int, int, void *, void *);
extern float FastVecLength(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, float, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int *D_L06_001C3D00[];
extern Vec4 D_L06_001BFCA0, D_L06_001BFCB0;

/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/moby_ground_collision.c, mine_fall. */
int func_PAL_L06_00360A78(char *moby, char *st) {
    float v0[4];
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float f60, f64, f68, f6c;

    Vec4 *g;
    char *q;
    int flags = 0;

    float sc, f21, f20, t, rr, one;
    int n, i;

    *(float *)(st + 0x8) = *(float *)(st + 0x8) - *(float *)(st + 0x10);
    if (*(unsigned char *)(st + 0x2E) == 1) {
        if (*(unsigned char *)(st + 0x2F) != 0) {
            func_PAL_002ABCB8(moby, st, (void *)(int)*(unsigned char *)(st + 0x2F));
        }
    }

    f60 = vec_length_xy(st);
    t = (*(short *)(st + 0x3E) == 2) ? 0.0f : *(float *)(st + 0x4C);
    ApproachValue(&f60, t, *(float *)(st + 0x14));
    vec_fast_normalize_helper((float *)st, (float *)st, f60);
    if (*(float *)(st + 0x1C) < *(float *)(st + 0x8)) {
        *(float *)(st + 0x8) = *(float *)(st + 0x1C);
    }

    qcopy(v10, moby + 0x10);
    v10[2] = v10[2] + *(float *)(st + 0x28);
    f21 = coll_probe_ground_height_below(v10, 0, 0.5f);
    if (GetCollHitMaterial() == 0) {
        if (*(float *)(st + 0x5C) == 0.0f && f21 <= v10[2] && v10[2] + *(float *)(st + 0x8) < f21) {
            *(float *)(st + 0x5C) = 1.0f;
            v10[2] = f21;
            moby_spawn_scaled_effect(v10, 3.0f);
        }
        f21 = coll_get_ground_height_under_object((moby + 0x10));
    } else {
        if ((*(int *)(st + 0x24) & 0x10) || *(short *)(st + 0x3E) == 2) {
            FastVecAdd(v20, (moby + 0x10), st);
            if (coll_get_ground_height_under_object(v20) < f21 - 0.25f) {
                vec_fast_normalize_helper((float *)st, (float *)st, 0.0f);
            }
        }
    }

    if (*(float *)(st + 0x5C) != 0.0f) {
        if (*(float *)(st + 0x5C) < 4.0f) {
            FastVecScale(st, st, 0.7f);
        }
        if (*(float *)(st + 0x5C) < 7.0f) {
            *(float *)(st + 0x5C) = *(float *)(st + 0x5C) + 1.0f;
            *(float *)(st + 0x10) = *(float *)(st + 0x10) * 0.75f;
        }
    }
    if (*(float *)(moby + 0x10) < 2.0f || 1021.0f < *(float *)(moby + 0x10)
        || *(float *)(moby + 0x14) < 2.0f || 1021.0f < *(float *)(moby + 0x14)
        || *(float *)(moby + 0x18) < 2.0f || 1021.0f < *(float *)(moby + 0x18)) {
        flags = 0x100;
    }

    if (*(float *)(st + 0x54) != -1.0f && *(float *)(st + 0x50) != -1.0f) {
        switch (*(short *)(st + 0x3E)) {
        case 0: {
            float s0;
            float numerator0;
            s0 = math_fabs(*(float *)(st + 0x8) / *(float *)(st + 0x10));
            if (2.0f < s0) {
                t = moby_get_anim_value(moby);
                numerator0 = *(float *)(st + 0x50) - t;
                rr = numerator0 / s0;
                if (0.0f < rr) {
                    ApproachValue((float *)(moby + 0x48), rr, 0.120000005f);
                }
            }
            break;
        }
        case 1:
            t = moby_get_anim_value(moby);
            if (*(float *)(st + 0x54) <= t) {
                *(int *)(moby + 0x48) = 0;
            } else {
                float numerator1;
                float h = *(float *)(st + 0x10) * -0.5f;
                f20 = 60.0f;
                n = math_solve_quadratic(&f64, &f68, h, *(float *)(st + 0x8) - h, *(float *)(moby + 0x18) - f21);
                if (n > 0 && 0.0f < f64 && f64 < f20) {
                    f20 = f64;
                }
                if (f20 < 0.0001f) {
                    f20 = 0.0001f;
                }
                t = moby_get_anim_value(moby);
                numerator1 = *(float *)(st + 0x54) - t;
                rr = numerator1 / f20;
                if (2.0f < rr) {
                    rr = 2.0f;
                } else if (rr < 0.0f) {
                    rr = 0.0f;
                }
                ApproachValue((float *)(moby + 0x48), rr, 0.120000005f);
            }
            break;
        case 2:
            *(float *)(moby + 0x48) = 1.0f;
            break;
        }
    }

    if (*(unsigned char *)(moby + 0x60) & 2) {
        flags |= 0x40;
    }
    if (!(*(int *)(st + 0x24) & 4)) {
        MobySpringTurn(moby, (float *)(st + 0x44), *(float *)(st + 0x40), 0.02f, 0.3f, *(float *)(st + 0x48));
    }

    i = 0;
    qcopy(v0, (moby + 0x10));
    v0[2] = v0[2] + *(float *)(st + 0x28);
    FastVecAdd((moby + 0x10), (moby + 0x10), st);
    qcopy(v20, (moby + 0x10));
    v20[2] = v20[2] + *(float *)(st + 0x28);
    FastVecAdd(v30, v20, st);
    n = coll_process_hit(IntToFloat(*(int *)(st + 0x20)) * 0.0010742187732830644f, v30, 16, moby, 0);
    if (i < n) {
        int **pp = D_L06_001C3D00;
        int k = n;
        do {
            if (moby_is_in_special_class_range(*pp) != 0) {
                part_queue_impact_effect((char *)*pp, 1.0f, (int)moby, 0x10000, (moby + 0x10), st);
            }
            pp++;
        } while (--k != 0);
    }

    sc = 0.0009765625f;
    t = FastVecLength(st);
    if ((float)*(int *)(st + 0x20) * sc < t) {
        CollLine(v0, v20, 36, moby, 0);
        qcopy(v20, &D_L06_001BFCA0);
    }
    if (coll_test_point(v20, IntToFloat(*(int *)(st + 0x20)) * sc, 36, moby) != 0) {
        flags |= 2;
        g = &D_L06_001BFCB0;
        qcopy((moby + 0x10), g);
        one = 1.0f;
        *(float *)(moby + 0x18) = *(float *)(moby + 0x18) - *(float *)(st + 0x28);
        vec_scale_to_length(v40, (char *)g + 0x10, one);
        if (0.7070000171661377f <= v40[2]) {
            float e = FastVecDot(st, v40);
            if (e < 0.0f) {
                q = (char *)g - 0x30;
                if (*(int *)(q + 0x18) == 0 || *(int *)(q + 0x1C) > 0) {
                    flags |= 1;
                    *(short *)(st + 0x3E) = 2;
                }
                vec_scale_to_length(v50, v40, e);
                FastVecSub(st, st, v50);
                if (*(short *)(st + 0x3E) == 2) {
                    f6c = FastVecLength(st);
                    ApproachValue(&f6c, 0.0f, *(float *)(st + 0x10));
                    vec_scale_to_length(st, st, f6c);
                }
            }
        } else {
            float d = FastVecDot(st, v40);
            if (d < 0.0f) {
                d = d * -(*(float *)(st + 0x30) + one);
                vec_scale_to_length(v50, v40, d);
                FastVecAdd(st, st, v50);
            }
        }
    }
    if (*(short *)(st + 0x3E) == 0) {
        if (*(float *)(st + 0x8) < 0.0f) {
            *(short *)(st + 0x3E) = 1;
        }
    }
    return flags;
}
