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
extern u8 D_L22_001B9C80[];
extern void moby_transform_joint_to_world(void *, int, void *);
extern float FastVecLength(void *, void *), math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float), vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *), transform_vector(void *, void *, void *);
extern void * enemy_spawn_record(void *, void *, void *, void *, int);

/* Emit sprays from two transformed offsets, optionally mirrored about Y. */
void func_PAL_L22_003A8F68(u8 * obj, int index, int flip) {
    float p[4], x[4], y[4], z[4], origin[4], dir[4], vel[4], pos[4], a[4], b[4], tmp[4];
    u8 * ctl = *(u8 **)(obj + 0x68);
    float f;
    int i;

    moby_transform_joint_to_world(obj, index, p);
    qcopy(x, obj + 0xC0);
    qcopy(y, obj + 0xD0);
    qcopy(z, obj + 0xE0);
    qcopy(origin, p);
    qcopy(dir, obj + 0xE0);
    f = FastVecLength(ctl + 0x1B0, x);
    {
        float r = math_random_float_range(0.0f, 0.1f);
        f *= 49.999996f;
        f += r;
    }
    if (f > 1.0f)
        f = 1.0f;
    else if (f < 0.0f)
        f = 0.0f;
    qcopy(a, ref_L22_003A5BD8_00);
    qcopy(b, ref_L22_003A5BD8_01);
    if (flip) {
        a[1] = -a[1];
        b[1] = -b[1];
    }
    transform_vector(pos, a, x);
    FastVecAdd(pos, pos, p);
    FastVecSub(tmp, D_L22_001B9C80, pos);
    tmp[2] = 0.0f;
    vec_scale_to_length(tmp, tmp, ref_L22_003A5BD8_02);
    FastVecAdd(pos, pos, tmp);
    for (i = 0; i < ref_L22_003A5BD8_03; i++) {
        float r = math_random_float_range(0.0f, f * ref_L22_003A5BD8_04);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_05 + r) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_06);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_11, (void *)math_random_int_below(2), 1);
    }
    transform_vector(pos, b, x);
    FastVecAdd(pos, pos, p);
    for (i = 0; (float)i < f * (float)ref_L22_003A5BD8_10 + 2.0f; i++) {
        float r = math_random_float_range(0.0f, f * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + r) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_12, (void *)math_random_int_below(2), 1);
        r = math_random_float_range(0.0f, f * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + r) * (1.0f / 49.999996f)));
        vec_add_random_offset(pos, ref_L22_003A5BD8_09);
        enemy_spawn_record(pos, vel, &ref_L22_003A5BD8_13, (void *)math_random_int_below(2), 1);
    }
}
