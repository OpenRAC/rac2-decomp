#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuadword __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x18];
    u8 *object;
    int polygon;
    float correction[4], point[4], normal[4];
} CollisionView;
extern int g_hero_vehicle_mode;
extern CollisionView g_collision_contact;
extern u8 *g_hero_moby __attribute__((nosda));
extern float g_yeedil_projectile_radius __attribute__((sda));
extern float g_yeedil_projectile_spin_rate __attribute__((sda));
extern float g_yeedil_projectile_bounce_min __attribute__((sda));
extern float D_L20_001B2400_4[] MACRO_ADDR;
extern float g_yeedil_projectile_shadow_size __attribute__((sda));
extern void moby_mark_spawned(void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *), vec_length_xy(void *);
extern int CollLine(void *, void *, int, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_normalize_helper(float, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void projectile_explode_pal(char *, char *);
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

void yeedil_projectile_update_pal(u8 *moby)
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
    if (g_hero_vehicle_mode == 2) { moby_mark_spawned(moby); return; }
    if (moby[0x20] != 1) return;
    qcopy(previous, (float *)(moby + 0x10));
    collided = 0;
    FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), state);
    if (FastVecLength(state) > g_yeedil_projectile_radius * 0.1f && CollLine(previous, (float *)(moby + 0x10), 2, moby, 0)) {
        collided = 1;
        vec_scale_to_length((float *)(moby + 0x10), g_collision_contact.normal, 0.01f);
        FastVecAdd((float *)(moby + 0x10), (float *)(moby + 0x10), g_collision_contact.correction);
    }
    if (coll_test_point((float *)(moby + 0x10), 0, moby, g_yeedil_projectile_radius * 0.1f)) {
        collided = 1;
        if (g_collision_contact.polygon < 0 &&
            (g_collision_contact.object != *(u8 **)(moby + 0xb8) || !*(int *)(state + 0x20)) &&
            *(short *)(g_collision_contact.object + 0xaa) != *(short *)(moby + 0xaa)) {
            projectile_explode_pal((char *)moby, (char *)(g_collision_contact.object == g_hero_moby ? 0x10001 : 0x10000));
            return;
        }
        qcopy((float *)(moby + 0x10), g_collision_contact.point);
    }
    if (collided) *(float *)(state + 8) = math_random_float_range(g_yeedil_projectile_bounce_min, D_L20_001B2400_4[1]) * 0.020000001f;
    else *(float *)(state + 8) -= *(float *)(state + 0x10);
    rate = vec_length_xy(state);
    ApproachValue(&rate, g_yeedil_projectile_spin_rate * 0.020000001f, 0.002f);
    vec_fast_normalize_helper(rate, state, state);
    *(ProjectileQuadword *)rotation = 0;
    rotation[2] = *(float *)(state + 0x14);
    *(ProjectileQuadword *)angles = *(ProjectileQuadword *)rotation;
    euler_rotation_basis(basis, angles);
    matrix_mul_vec3(state, state, basis);
    if (moby[0x31]) {
        part_queue_ground_shadow((char *)moby, g_yeedil_projectile_shadow_size);
        vec_copy_helper_a(rotation);
        FastVecCross(quaternion, rotation, state);
        vec_set_direction_with_complement(quaternion, quaternion, 0.031415932f);
        quaternion_to_rotation_basis(quaternion, spin);
        multiply_matrix3x3(moby + 0xc0, spin, moby + 0xc0);
    }
    math_fast_float_d((int *)(state + 0x20));
    if (math_fast_float_d((int *)(state + 0x18))) projectile_explode_pal((char *)moby, 0);
}
