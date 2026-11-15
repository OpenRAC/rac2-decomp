#include "include_asm.h"
#include "common.h"

/* One of the 300 0x50-byte particles at D_0022C9A0 (see func_00329328). */
typedef struct {
    float pos[4];
    float velocity[4];
    float spin;
    float angle;
    float size;
    int color;
    int color2;
    int timer;
    int timer2;
    int kind;
    int life;
    int duration;
    char *owner;
    int tail;
} Particle290;

extern Particle290 g_object_particles[300];
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float), math_random_angle(void), math_random_float_range(float, float);
extern void vec_clear_128(void *), matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);

/* Claims a free particle for self: random life, grey colour, spin and size, at pos or, when
   pos[3] is -1, at a point on self's basis; counts it in self's state (+0x4C, +0x50).
   The EE ABI passes size in $f12 and pos in $a1 in either declaration order (callers
   declare (void *, void *, float)); this order copies pos last, as retail's $s3 shows. */
void SpawnObjectParticle(char *self, float size, float *pos)
{
    float offset[4];
    Particle290 *base = g_object_particles;
    char *state = *(char **)(self + 0x68);
    Particle290 *p;
    Particle290 *record;
    int i, grey;

    for (i = 0; i < 300; i++) {
        p = &base[i];
        if (p->owner)
            continue;
        p->timer2 = p->timer = math_random_int_range(80, 200);
        record = p;
        grey = math_random_int_range(96, 128);
        p->color2 = p->color = grey + ((grey << 7) & 0xFF00) + ((grey << 14) & 0xFF0000);
        p->kind = *(int *)(state + 0x50) % 2 + 1;
        p->life = p->duration = math_random_int_range(50, 60);
        p->size = size;
        p->spin = math_random_signed_float_range(180.0f, 720.0f) * 0.0002908882452175021f;
        p->angle = math_random_angle();
        p->owner = self;
        ++*(int *)(state + 0x4C);
        if (pos[3] == -1.0f) {
            vec_clear_128(offset);
            offset[3] = 1.0f;
            offset[0] = -0.3f;
            matrix_mul_vec3(offset, offset, self + 0xC0);
            FastVecAdd(p, offset, self + 0x10);
        } else {
            qcopy(record->pos, pos);
        }
        p->pos[0] += math_random_float_range(-0.015f, 0.015f);
        p->pos[1] += math_random_float_range(-0.015f, 0.015f);
        p->pos[2] += math_random_float_range(-0.015f, 0.015f);
        vec_clear_128(p->velocity);
        p->velocity[2] = math_random_float_range(0.01f, 0.015f);
        ++*(int *)(state + 0x50);
        break;
    }
}
