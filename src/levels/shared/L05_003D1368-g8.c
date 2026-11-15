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
extern char *SpawnSpinningSparkParticle(void *, int, float, float, float, void *, int, int, float);
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
/* Applies damage to the thing a shot hit and makes a small spray of sparks when the target is
   a special one. */
void func_L05_003D1368(char *obj, char *input, float *output)
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
            vec_build_spherical_offset(vel, 0.05000000447034836f, a, b);
            p = SpawnSpinningSparkParticle(output, math_random_int_range(-3, 3), 0.0f, 1.0f, 1.0f, vel, 0x7FFFFFFF, 0, scale * 210000.0f);
            if (p) {
                char *q = p + 0x20;
                *(short *)(p + 0xA) = 120;
                *(unsigned char *)(p + 8) = math_random_int_below(255);
                p[3] = 0x44;
                *(int *)(q + 4) = 2;
                q[0xA] = 127;
                q[0xB] = *(unsigned char *)(p + 0xA);
            }
        }
    }
}
