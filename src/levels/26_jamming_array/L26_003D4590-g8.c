#include "names.h"
/* func_L26_003D4590 reaches its small globals through $gp (-G8) and clears a stack vector with
 * por (-frac2-zero-ti-por). As in the level-2 state machine (L02_003C43F0-state-g8.c), each
 * random range reads its upper bound, absolutely, before its lower bound.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int g_hero_tether_enabled;
extern Vector g_trail_ribbon_template[6];
extern Vector g_orbit_center_offset MACRO_ADDR;
extern float g_orbit_tilt_min __attribute__((sda));
/* Upper bounds, snapshotted before the lower bounds are read. */
extern volatile float g_orbit_tilt_max MACRO_ADDR;
extern float g_orbit_spin_min __attribute__((sda));
extern volatile float g_orbit_spin_max MACRO_ADDR;
extern int g_orbit_object_values[2] __attribute__((sda));
extern int g_orbit_private_values[2] __attribute__((sda));
extern int g_frame_l26_counter;
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void moby_set_state(unsigned char *, int, int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void mat_align_to_dir(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_scale_triangle_vertices(unsigned char *, int);
extern int math_fast_float_d(int *);
extern void trail_advance_samples(unsigned char *);

/* Per-frame update for the moby of class 3072: it moves around a circle centred on a fixed point,
   turning to face along its path and switching between two animation modes now and then. It is
   hidden while the level is not active. */
void orbiting_moby_update(unsigned char *object) {
    Vector position;
    union {
        float init_matrix[12];
        struct { Vector tangent; Vector rotation; Vector rotation_seed; } motion;
    } workspace;
    float matrix[12];
    char *private;
    float radius;
    float upper;
    float angle;
    unsigned int selection;
    if (!g_hero_tether_enabled && object[0x20]) {
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        return;
    }
    object[0x31] = 1;
    *(unsigned short *)(object + 0x34) &= 0xFFFE;
    private = *(char **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        if (g_trail_ribbon_template[0].f[3] == 0.0f) {
            position.q = 0;
            position.f[2] = 2.0943954f;
            euler_rotation_basis(workspace.init_matrix, &position);
            g_trail_ribbon_template[0].f[3] = 1.0f;
            g_trail_ribbon_template[1].f[3] = 1.0f;
            matrix_mul_vec3(g_trail_ribbon_template + 2, g_trail_ribbon_template, workspace.init_matrix);
            matrix_mul_vec3(g_trail_ribbon_template + 3, g_trail_ribbon_template + 1, workspace.init_matrix);
            matrix_mul_vec3(g_trail_ribbon_template + 4, g_trail_ribbon_template + 2, workspace.init_matrix);
            matrix_mul_vec3(g_trail_ribbon_template + 5, g_trail_ribbon_template + 3, workspace.init_matrix);
        }
        object[0x30] = 0xFF;
        *(unsigned short *)(object + 0x32) = 0x200;
        *(unsigned short *)(object + 0x34) |= 0x110;
        FastVecSub(private + 0x50, object + 0x10, &g_orbit_center_offset);
        radius = FastVecLength(private + 0x50);
        vec_scale_to_length(private + 0x60, object + 0xC0, radius);
        FastVecCross(private + 0x70, private + 0x60, private + 0x50);
        vec_scale_to_length(private + 0x70, private + 0x70, radius);
        FastVecCross(private + 0x60, private + 0x50, private + 0x70);
        vec_scale_to_length(private + 0x60, private + 0x60, radius);
        upper = g_orbit_tilt_max;
        *(float *)(private + 0x188) = math_random_signed_float_range(g_orbit_tilt_min, upper) * 0.00029088825f;
        upper = g_orbit_spin_max;
        *(float *)(private + 0x180) = math_random_float_range(g_orbit_spin_min, upper) * 0.00029088825f;
        *(float *)(private + 0x184) = math_random_angle();
        moby_set_state(object, 1, -1);
        break;
    case 1:
        *(float *)(private + 0x184) = FastAddRotations(*(float *)(private + 0x184), *(float *)(private + 0x180));
        position.f[0] = math_fast_sin_or_cos_a(*(float *)(private + 0x184));
        position.f[1] = math_fast_sin_or_cos_b(*(float *)(private + 0x184));
        position.f[2] = 0.0f;
        matrix_mul_vec3(object + 0x10, &position, private + 0x50);
        FastVecAdd(object + 0x10, object + 0x10, &g_orbit_center_offset);
        angle = FastAddRotations(*(float *)(private + 0x184), 1.5707965f);
        workspace.motion.tangent.f[0] = math_fast_sin_or_cos_a(angle);
        workspace.motion.tangent.f[1] = math_fast_sin_or_cos_b(angle);
        workspace.motion.tangent.f[2] = 0.0f;
        matrix_mul_vec3(&workspace.motion.tangent, &workspace.motion.tangent, private + 0x50);
        mat_align_to_dir(object + 0xC0, &workspace.motion.tangent, 0);
        workspace.motion.rotation_seed.q = 0;
        workspace.motion.rotation_seed.f[2] = *(float *)(private + 0x188);
        workspace.motion.rotation.q = workspace.motion.rotation_seed.q;
        euler_rotation_basis(matrix, &workspace.motion.rotation);
        multiply_matrix3x3(object + 0xC0, object + 0xC0, matrix);
        if ((g_frame_l26_counter & 0xFF) == 0) vec_scale_triangle_vertices(object + 0xC0, 0);
        if (math_fast_float_d((int *)(private + 0x18C))) {
            selection = (object[0xBC] + 1) & 1;
            object[0xBC] = selection;
            *(int *)(object + 0x78) = g_orbit_object_values[object[0xBC]];
            *(int *)(private + 0x18C) = g_orbit_private_values[object[0xBC]];
        }
        trail_advance_samples(object);
        break;
    }
}
