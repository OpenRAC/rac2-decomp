#include "include_asm.h"

#include "common.h"
extern float ref_L22_003A5BD8_00[4] __attribute__((sda));
extern float ref_L22_003A5BD8_01[4] __attribute__((sda));
extern float ref_L22_003A5BD8_02 __attribute__((sda));
extern int ref_L22_003A5BD8_03 __attribute__((sda));
extern float ref_L22_003A5BD8_04 __attribute__((sda)), ref_L22_003A5BD8_05 __attribute__((sda)), ref_L22_003A5BD8_06 __attribute__((sda));
extern float ref_L22_003A5BD8_07 __attribute__((sda)), ref_L22_003A5BD8_08 __attribute__((sda)), ref_L22_003A5BD8_09 __attribute__((sda));
extern int ref_L22_003A5BD8_10 __attribute__((sda));
typedef struct {
    void * colours;
    void * sizes;
    void * frames;
    int kind;
    int count;
    float acceleration;
} ParticleSettings;
extern ParticleSettings ref_L22_003A5BD8_11 __attribute__((sda)), ref_L22_003A5BD8_12 __attribute__((sda)), ref_L22_003A5BD8_13 __attribute__((sda));
extern u8 g_tether_origin[];
extern void moby_transform_joint_to_world(void *, int, void *);
extern float FastVecLength(void *, void *), math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float), vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *), transform_vector(void *, void *, void *);
extern void * enemy_spawn_record(void *, void *, void *, void *, int);

/* Sprays thruster particles (PAL copy of part_spray_thruster). Emit sprays from two transformed offsets, optionally mirrored about Y. */
void part_spray_thruster_pal(u8 * obj, int index, int flip) {
    float joint_pos[4], basis_x[4], basis_y[4], basis_z[4], origin[4], dir[4], vel[4], pos[4], offset_a[4], offset_b[4], to_origin[4];
    u8 * vars = *(u8 **)(obj + 0x68);
    float intensity;
    int i;

    moby_transform_joint_to_world(obj, index, joint_pos);
    qcopy(basis_x, obj + 0xC0);
    qcopy(basis_y, obj + 0xD0);
    qcopy(basis_z, obj + 0xE0);
    qcopy(origin, joint_pos);
    qcopy(dir, obj + 0xE0);
    intensity = FastVecLength(vars + 0x1B0, basis_x);
    {
        float jitter = math_random_float_range(0.0f, 0.1f);
        intensity *= 49.999996f;
        intensity += jitter;
    }
    if (intensity > 1.0f)
        intensity = 1.0f;
    else if (intensity < 0.0f)
        intensity = 0.0f;
    qcopy(offset_a, ref_L22_003A5BD8_00);
    qcopy(offset_b, ref_L22_003A5BD8_01);
    if (flip) {
        offset_a[1] = -offset_a[1];
        offset_b[1] = -offset_b[1];
    }
    transform_vector(pos, offset_a, basis_x);
    FastVecAdd(pos, pos, joint_pos);
    FastVecSub(to_origin, g_tether_origin, pos);
    to_origin[2] = 0.0f;
    vec_scale_to_length(to_origin, to_origin, ref_L22_003A5BD8_02);
    FastVecAdd(pos, pos, to_origin);
    for (i = 0; i < ref_L22_003A5BD8_03; i++) {
        float jitter = math_random_float_range(0.0f, intensity * ref_L22_003A5BD8_04);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_05 + jitter) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_06);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_11, (void *)math_random_int_below(2), 1);
    }
    transform_vector(pos, offset_b, basis_x);
    FastVecAdd(pos, pos, joint_pos);
    for (i = 0; (float)i < intensity * (float)ref_L22_003A5BD8_10 + 2.0f; i++) {
        float jitter = math_random_float_range(0.0f, intensity * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + jitter) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_12, (void *)math_random_int_below(2), 1);
        jitter = math_random_float_range(0.0f, intensity * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + jitter) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_13, (void *)math_random_int_below(2), 1);
    }
}
