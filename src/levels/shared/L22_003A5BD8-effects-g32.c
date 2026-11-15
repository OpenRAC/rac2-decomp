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
extern void func_0029FCC0(void *, int, void *);
extern float func_00282DF0(void *, void *), func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_00282F20(void *, void *, float), func_002ACB48(void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *), func_002830C0(void *, void *, void *);
extern void * func_L02_003449D8(void *, void *, void *, void *, int);

/* Emit sprays from two transformed offsets, optionally mirrored about Y. */
void func_L22_003A5BD8(u8 * obj, int index, int flip) {
    float p[4], x[4], y[4], z[4], origin[4], dir[4], vel[4], pos[4], a[4], b[4], tmp[4];
    u8 * ctl = *(u8 **)(obj + 0x68);
    float f;
    int i;

    func_0029FCC0(obj, index, p);
    qcopy(x, obj + 0xC0);
    qcopy(y, obj + 0xD0);
    qcopy(z, obj + 0xE0);
    qcopy(origin, p);
    qcopy(dir, obj + 0xE0);
    f = FastVecLength(ctl + 0x1B0, x);
    {
        float r = func_002A7878(0.0f, 0.1f);
        f *= 60.0f;
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
        float r = func_002A7878(0.0f, f * ref_L22_003A5BD8_04);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_05 + r) * (1.0f / 60.0f)));
        func_002ACB48(pos, ref_L22_003A5BD8_06);
        func_L02_003449D8(pos, vel, &ref_L22_003A5BD8_11, (void *)func_002A77E0(2), 1);
    }
    transform_vector(pos, b, x);
    FastVecAdd(pos, pos, p);
    for (i = 0; (float)i < f * (float)ref_L22_003A5BD8_10 + 2.0f; i++) {
        float r = func_002A7878(0.0f, f * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + r) * (1.0f / 60.0f)));
        func_002ACB48(pos, ref_L22_003A5BD8_09);
        func_L02_003449D8(pos, vel, &ref_L22_003A5BD8_12, (void *)func_002A77E0(2), 1);
        r = func_002A7878(0.0f, f * ref_L22_003A5BD8_07);
        vec_scale_to_length(vel, dir, -((ref_L22_003A5BD8_08 + r) * (1.0f / 60.0f)));
        func_002ACB48(pos, ref_L22_003A5BD8_09);
        func_L02_003449D8(pos, vel, &ref_L22_003A5BD8_13, (void *)func_002A77E0(2), 1);
    }
}
