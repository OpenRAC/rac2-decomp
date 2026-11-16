#include "common.h"

extern float g_impact_spark_scale_b __attribute__((sda));
extern float g_impact_spark_scale_a __attribute__((sda));
extern float g_projectile_hit_radius_alt __attribute__((sda));
extern float g_projectile_hit_radius_normal __attribute__((sda));
extern char *g_hit_l05_result __attribute__((nosda));
extern void vec_scale_to_length(void *, void *, float);
extern int coll_process_hit(void *, float, int, char *, void *);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_range(int, int);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, float, int, void *, u32, int);
extern int math_random_int_below(int);

typedef int ImpactTI __attribute__((mode(TI)));
typedef union { ImpactTI q; float f[4]; } ImpactVector;
typedef struct {
    ImpactVector pos;
    void *owner;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float scale;
    int one;
} ImpactParams;

/* Queues an impact request (func_00277F48) from the object at pos, then, when the
   object in D_L05_001BFB18 has class 0x956, spawns twenty spark particles there. */
void projectile_apply_impact_sparks(char *object, char *state, float *pos)
{
    ImpactParams p;
    ImpactVector origin, direction;
    int i;
    int spin;
    float a, b;
    float count, speed, spread;
    char *particle, *data;

    p.flags = 0x810000;
    p.owner = object;
    if (*(int *)(state + 0x24))
        p.scale = g_impact_spark_scale_b;
    else
        p.scale = g_impact_spark_scale_a;
    p.one = 1;
    qcopy(&p.pos, state);
    vec_scale_to_length(&p, &p, 1.0f);
    p.pos.f[3] = 5627.925f;
    p.type = 3;
    p.subtype = 2;
    p.id = *(unsigned short *)(object + 0xAA);
    coll_process_hit(pos, *(int *)(state + 0x24) ? g_projectile_hit_radius_alt : g_projectile_hit_radius_normal,
                  1, *(char **)(state + 0x20), &p);
    if (g_hit_l05_result && *(short *)(g_hit_l05_result + 0xAA) == 0x956) {
        count = 20.0f;
        speed = 3.0f;
        spread = 2.0f;
        qcopy(&origin, object + 0x10);
        for (i = 0; (float)i < count; i++) {
            pos[0] = origin.f[0] + math_random_signed_float_range(0.0f, spread);
            pos[1] = origin.f[1] + math_random_signed_float_range(0.0f, spread);
            pos[2] = origin.f[2] + math_random_signed_float_range(0.0f, spread);
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(&direction, 0.050000004f, a, b);
            spin = math_random_int_range(-3, 3);
            particle = SpawnSpinningSparkParticle(pos, 0.0f, 1.0f, 1.0f, speed * 210000.0f, spin,
                                     &direction, 0x7fffffff, 0);
            if (particle) {
                *(short *)(particle + 0xA) = 120;
                data = particle + 0x20;
                particle[8] = math_random_int_below(255);
                particle[3] = 0x44;
                *(int *)(data + 4) = 2;
                data[0xA] = 127;
                data[0xB] = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}
