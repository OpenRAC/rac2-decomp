#include "common.h"

extern float ref_L22_003A5BD8_00[4] __attribute__((sda));
extern float ref_L22_003A5BD8_01[4] __attribute__((sda));
extern float ref_L22_003A5BD8_02 __attribute__((sda));
extern int ref_L22_003A5BD8_03 __attribute__((sda));
extern float ref_L22_003A5BD8_04 __attribute__((sda)), ref_L22_003A5BD8_05 __attribute__((sda)), ref_L22_003A5BD8_06 __attribute__((sda));
extern float ref_L22_003A5BD8_07 __attribute__((sda)), ref_L22_003A5BD8_08 __attribute__((sda)), ref_L22_003A5BD8_09 __attribute__((sda));
extern int ref_L22_003A5BD8_10 __attribute__((sda));
/* Particle settings are six words; the emitter reads through +0x14. */
typedef struct {
    void * colours;
    void * sizes;
    void * frames;
    int kind;
    int count;
    float acceleration;
} ParticleSettings;
extern ParticleSettings ref_L22_003A5BD8_11 __attribute__((sda)), ref_L22_003A5BD8_12 __attribute__((sda)), ref_L22_003A5BD8_13 __attribute__((sda));
extern u8 D_L22_001B9C80[];
extern void moby_transform_joint_to_world(void *, int, void *);
extern float FastVecLength(void *, void *), math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float), vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *), transform_vector(void *, void *, void *);
extern void * enemy_spawn_record(void *, void *, void *, void *, int);

/* Emit sprays from two transformed offsets, optionally mirrored about Y. */
void part_spray_thruster(u8 * obj, int index, int flip) {
    float socket_pos[4], x[4], y[4], z[4], origin[4], dir[4], vel[4], pos[4], offset_a[4], offset_b[4], tmp[4];
    u8 * ctl = *(u8 **)(obj + 0x68);
    float strength;
    int i;

    moby_transform_joint_to_world(obj, index, socket_pos);
    qcopy(x, obj + 0xC0);
    qcopy(y, obj + 0xD0);
    qcopy(z, obj + 0xE0);
    qcopy(origin, socket_pos);
    qcopy(dir, obj + 0xE0);
    strength = FastVecLength(ctl + 0x1B0, x);
    {
        float jitter = math_random_float_range(0.0f, 0.1f);
        strength *= 60.0f;
        strength += jitter;
    }
    if (strength > 1.0f)
        strength = 1.0f;
    else if (strength < 0.0f)
        strength = 0.0f;
    qcopy(offset_a, ref_L22_003A5BD8_00);
    qcopy(offset_b, ref_L22_003A5BD8_01);
    if (flip) {
        offset_a[1] = -offset_a[1];
        offset_b[1] = -offset_b[1];
    }
    transform_vector(pos, offset_a, x);
    FastVecAdd(pos, pos, socket_pos);
    FastVecSub(tmp, D_L22_001B9C80, pos);
    tmp[2] = 0.0f;
    vec_scale_to_length(tmp, tmp, ref_L22_003A5BD8_02);
    FastVecAdd(pos, pos, tmp);
    for (i = 0; i < ref_L22_003A5BD8_03; i++) {
        float jitter = math_random_float_range(0.0f, strength * ref_L22_003A5BD8_04);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_05 + jitter) * (1.0f / 60.0f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_06);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_11, (void *)math_random_int_below(2), 1);
    }
    transform_vector(pos, offset_b, x);
    FastVecAdd(pos, pos, socket_pos);
    for (i = 0; (float)i < strength * (float)ref_L22_003A5BD8_10 + 2.0f; i++) {
        float jitter = math_random_float_range(0.0f, strength * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + jitter) * (1.0f / 60.0f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_12, (void *)math_random_int_below(2), 1);
        jitter = math_random_float_range(0.0f, strength * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + jitter) * (1.0f / 60.0f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_13, (void *)math_random_int_below(2), 1);
    }
}
