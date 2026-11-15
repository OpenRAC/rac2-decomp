/* Casts the ray ahead of the object and, on a hit, places the follow point against the surface. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B36A4 MACRO_ADDR;
extern int D_L23_001AFA54 __attribute__((sda));

extern TI128 D_L23_001C0AA0[];
extern char D_00189ED0[];

extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void func_L22_002F3B38(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);

#define F(i, k) (((float *)&loc[i])[k])

/* Fires a ray ahead of the enemy; on a hit it picks a new point to move toward next to the wall and returns 1. */
int enemy_probe_ahead_point(char *moby) {
    TI128 loc[8];
    char *vars = *(char **)(moby + 0x68);
    int value;
    TI128 *hitInfo;
    TI128 *hitNormal;
    TI128 *followPoint;
    TI128 *clampedPoint;

    loc[1] = 0;
    F(1, 2) = *(float *)(vars + 0x54) + *(float *)(vars + 0x50);
    loc[2] = 0;
    F(2, 0) = 4.0f;
    loc[0] = loc[1];
    value = math_random_int_below(8);
    F(2, 1) = (float)value * 0.4285714626f + -1.5f;
    F(2, 2) = *(float *)(vars + 0x54) + *(float *)(vars + 0x50);
    loc[1] = loc[2];
    FastVecScale(&loc[0], moby + 0xE0, F(0, 2));
    FastVecAdd(&loc[0], &loc[0], moby + 0x10);
    matrix_mul_vec3(&loc[1], &loc[1], moby + 0xC0);
    FastVecAdd(&loc[1], &loc[1], moby + 0x10);
    if (CollLine(&loc[0], &loc[1], 0x12, 0, 0) != 0) {
    hitInfo = &D_L23_001C0AA0[2];
    hitNormal = &loc[2];
    qcopy(hitNormal, hitInfo);
    loc[5] = 0;
    F(5, 0) = 0.0009765625f;
    F(5, 1) = 0.0009765625f;
    F(5, 2) = 0.0009765625f;
    func_L22_002F3B38(hitNormal, hitNormal, &loc[5]);
    hitInfo -= 2;
    vec_scale_to_length(hitNormal, hitNormal, 1.0f);
    FastVecSub(&loc[3], &loc[0], hitInfo);
    { float distance = FastVecDot(&loc[3], hitNormal);
    FastVecScale(&loc[4], hitNormal, distance); }
    FastVecSub(&loc[6], &loc[3], &loc[4]);
    vec_scale_to_length(&loc[6], &loc[6], -30.0f);
    followPoint = (TI128 *)(vars + 0x2D0);
    FastVecAdd(followPoint, moby + 0x10, &loc[6]);
    clampedPoint = &loc[7];
    FastVecSub(clampedPoint, followPoint, D_00189ED0);
    vec_scale_to_length(clampedPoint, clampedPoint, D_L23_001B36A4);
    FastVecAdd(clampedPoint, clampedPoint, D_00189ED0);
    qcopy(followPoint, clampedPoint);
    value = D_L23_001AFA54;
    *(short *)(vars + 0x26C) = 1;
    *(unsigned short *)(vars + 0x26E) = (unsigned short)D_L23_001AFA54 + math_random_int_range(-value / 2, value / 2);
    vec_scale_to_length(hitNormal, hitNormal, 10.0f);
    FastVecAdd(hitNormal, hitNormal, hitInfo);
    return 1;
    }
    return 0;
}
