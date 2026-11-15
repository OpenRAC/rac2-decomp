#include "include_asm.h"

#include "common.h"
extern float D_L05_001AFC58 __attribute__((sda));
extern float D_L05_001AFC54 __attribute__((sda));
extern char D_L05_001BFB00[];
extern void vec_scale_to_length(void *, void *, float);
extern void QueueMobyImpact(void *, void *);
extern char *func_L05_003D1E60(void *, int, int);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_range(int, int);
extern char *func_PAL_002BE9A8(void *, int, float, float, float, void *, int, int, float);
extern int math_random_int_below(int);
struct HitRecord {
    float pos[4];
    void *obj;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float damage;
    int one;
    char pad[12];
};

void func_PAL_L05_003D50B0(char *obj, char *input, float *output)
{
    struct HitRecord hit __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    int i;
    char *table;
    hit.flags = 0x810000;
    hit.obj = obj;
    if (*(int *)(input + 0x24))
        hit.damage = D_L05_001AFC58;
    else
        hit.damage = D_L05_001AFC54;
    hit.one = 1;
    qcopy(hit.pos, input);
    vec_scale_to_length(&hit, &hit, 1.0f);
    table = D_L05_001BFB00;
    hit.pos[3] = 5627.9248046875f;
    hit.type = 3;
    hit.subtype = 2;
    hit.id = *(unsigned short *)(obj + 0xAA);
    if (*(char **)(table + 0x18))
        QueueMobyImpact(*(char **)(table + 0x18), &hit);
    func_L05_003D1E60(obj + 0x10, 0, 0);
    if (*(char **)(table + 0x18) && *(short *)(*(char **)(table + 0x18) + 0xAA) == 0x956) {
        float count = 20.0f, scale = 3.0f, spread = 2.0f;
        qcopy(pos, obj + 0x10);
        for (i = 0; (float)i < count; i++) {
            float a, b;
            char *p;
            output[0] = pos[0] + math_random_signed_float_range(0.0f, spread);
            output[1] = pos[1] + math_random_signed_float_range(0.0f, spread);
            output[2] = pos[2] + math_random_signed_float_range(0.0f, spread);
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(vel, 0.060000002f, a, b);
            p = func_PAL_002BE9A8(output, math_random_int_range(-3, 3), 0.0f, 1.0f, 1.0f, vel, 0x7FFFFFFF, 0, scale * 210000.0f);
            if (p) {
                char *q = p + 0x20;
                *(short *)(p + 0xA) = 100;
                *(unsigned char *)(p + 8) = math_random_int_below(255);
                p[3] = 0x44;
                *(int *)(q + 4) = 2;
                q[0xA] = 127;
                q[0xB] = *(unsigned char *)(p + 0xA);
            }
        }
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern float D_L05_001AFC60[] SDATA(D_L05_001AFC60);
extern float D_L05_001AFC70[] SDATA(D_L05_001AFC70);
extern float D_L05_001AFC80[] SDATA(D_L05_001AFC80);

/* For each of two points in the object's frame, either side of it in Y, makes three copies of the
   point and passes each to func_L00_0033C0D0 with a random speed. */
void func_PAL_L05_003D5800(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float speed[4] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    float p1[4] __attribute__((aligned(16)));
    float p2[4] __attribute__((aligned(16)));
    float p3[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float factor;
    float y;

    *(TI128 *)a = 0;
    a[0] = -0.21f;
    a[1] = 0.061f;
    *(TI128 *)speed = 0;
    a[2] = 0.045f;
    a[3] = 1.0f;
    matrix_mul_vec3(p, a, obj + 0xC0);
    factor = 0.4f;
    FastVecAdd(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    vec_add_random_offset(p, 0.1f);
    vec_add_random_offset(p1, 0.1f);
    vec_add_random_offset(p2, 0.1f);
    vec_add_random_offset(p3, 0.1f);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p3, speed, D_L05_001AFC80, 1);
    y = -0.061f;
    *(TI128 *)b = 0;
    b[0] = -0.21f;
    b[1] = y;
    b[2] = 0.045f;
    b[3] = 1.0f;
    matrix_mul_vec3(p, b, obj + 0xC0);
    FastVecAdd(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    vec_add_random_offset(p, 0.1f);
    vec_add_random_offset(p1, 0.1f);
    vec_add_random_offset(p2, 0.1f);
    vec_add_random_offset(p3, 0.1f);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(math_random_float_range(30.0f, 40.0f) * (0.020000001f)) * factor;
    part_spawn_object_relative_particle(obj, p3, speed, D_L05_001AFC80, 1);
}
