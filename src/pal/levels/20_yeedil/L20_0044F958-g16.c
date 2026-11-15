#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuadword __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x18];
    u8 *object;
    int polygon;
    float correction[4], point[4], normal[4];
} CollisionView;
extern int D_L20_001A8F00;
extern CollisionView D_L20_001C0400;
extern u8 *g_hero_moby __attribute__((nosda));
extern float D_L20_001B23F8 __attribute__((sda));
extern float D_L20_001B23FC __attribute__((sda));
extern float D_L20_001B2400 __attribute__((sda));
extern float D_L20_001B2400_4[] MACRO_ADDR;
extern float D_L20_001B2408 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *), vec_length_xy(void *);
extern int CollLine(void *, void *, int, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_normalize_helper(float, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void func_PAL_L20_0044FD80(char *, char *);
extern float math_random_float_range(float, float);
extern float ApproachValue(float *, float, float);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_queue_ground_shadow(char *, float);
extern void vec_copy_helper_a(void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(float *, float *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern int math_fast_float_d(int *);

void func_PAL_L20_0044F958(u8 *moby)
{
    float rate;
    float previous[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float quaternion[4] __attribute__((aligned(16)));
    float spin[12] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    int collided;
    if (D_L20_001A8F00 == 2) { moby_mark_spawned(moby); return; }
    if (moby[0x20] != 1) return;
    qcopy(previous, (float *)(moby + 0x10));
    collided = 0;
    FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), state);
    if (FastVecLength(state) > D_L20_001B23F8 * 0.1f && CollLine(previous, (float *)(moby + 0x10), 2, moby, 0)) {
        collided = 1;
        vec_scale_to_length((float *)(moby + 0x10), D_L20_001C0400.normal, 0.01f);
        FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), D_L20_001C0400.correction);
    }
    if (coll_test_point((float *)(moby + 0x10), 0, moby, D_L20_001B23F8 * 0.1f)) {
        collided = 1;
        if (D_L20_001C0400.polygon < 0 &&
            (D_L20_001C0400.object != *(u8 **)(moby + 0xb8) || !*(int *)(state + 0x20)) &&
            *(short *)(D_L20_001C0400.object + 0xaa) != *(short *)(moby + 0xaa)) {
            func_PAL_L20_0044FD80((char *)moby, (char *)(D_L20_001C0400.object == g_hero_moby ? 0x10001 : 0x10000));
            return;
        }
        qcopy((float *)(moby + 0x10), D_L20_001C0400.point);
    }
    if (collided) *(float *)(state + 8) = math_random_float_range(D_L20_001B2400, D_L20_001B2400_4[1]) * 0.020000001f;
    else *(float *)(state + 8) -= *(float *)(state + 0x10);
    rate = vec_length_xy(state);
    ApproachValue(&rate, D_L20_001B23FC * 0.020000001f, 0.002f);
    vec_fast_normalize_helper(rate, state, state);
    *(ProjectileQuadword *)rotation = 0;
    rotation[2] = *(float *)(state + 0x14);
    *(ProjectileQuadword *)angles = *(ProjectileQuadword *)rotation;
    euler_rotation_basis(basis, angles);
    matrix_mul_vec3(state, state, basis);
    if (moby[0x31]) {
        part_queue_ground_shadow((char *)moby, D_L20_001B2408);
        vec_copy_helper_a(rotation);
        FastVecCross(quaternion, rotation, state);
        vec_set_direction_with_complement(quaternion, quaternion, 0.031415932f);
        quaternion_to_rotation_basis(quaternion, spin);
        multiply_matrix3x3(moby + 0xc0, spin, moby + 0xc0);
    }
    math_fast_float_d((int *)(state + 0x20));
    if (math_fast_float_d((int *)(state + 0x18))) func_PAL_L20_0044FD80((char *)moby, 0);
}
