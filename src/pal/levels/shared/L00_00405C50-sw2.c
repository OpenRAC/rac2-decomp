#include "include_asm.h"

#include "common.h"
extern float D_0022AFA0[8][4];
extern float D_0022B020[8][4];
extern float D_001B27B0[4] __attribute__((sda));
extern float D_001BAFA0[4];
extern float D_001BAFC0[4] __attribute__((sda));
extern int D_001B27C4;
extern float D_001B0108 __attribute__((sda));
extern float D_001B0134 __attribute__((sda));
extern float D_001B0130 __attribute__((sda));
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern int weapon_get_group(int);
extern int subtract_integer_with_clamp(int);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);


