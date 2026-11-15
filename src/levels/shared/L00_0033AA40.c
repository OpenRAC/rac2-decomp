#include "include_asm.h"
#include "common.h"

typedef int Quad __attribute__((mode(TI)));

/* A spawned particle: header, position, then the payload its update reads. */
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    union { Quad q; float f[4]; } position;
    float payload[8];
} L00_0033AA40_Particle;

extern L00_0033AA40_Particle *part_alloc(int);
extern int FloatToInt(float);
extern float vec_distance_xy(void *, void *);
extern float math_random_float_range(float, float);
extern unsigned char *ref_L00_0033AA40_00[];
extern char g_hero_position[];

/* Creates a moving particle that is brighter when it is close to the camera. */
L00_0033AA40_Particle *SpawnDistanceFadedParticle(Quad *position, Quad *velocity, unsigned int size,
                                         float life, float a, int color, float b, int value, int flag)
{
    L00_0033AA40_Particle *p = part_alloc(0x40);

    if (p) {
        float *out = p->payload;

        qcopy(&p->position, position);
        if (vec_distance_xy(g_hero_position, position) < 80.0f)
            p->alpha = FloatToInt(1.0f) + 48;
        else
            p->alpha = FloatToInt(1.0f) + 32;
        p->b3 = flag ? 0x48 : 0x44;
        p->b1 = 0;
        p->b2 = ref_L00_0033AA40_00[0][1];
        p->color = color;
        p->life = life * 210000.0f;
        {
            float random = math_random_float_range(0.0f, 255.0f);

            p->size = size;
            p->seed = (int)random;
        }
        qcopy(out, velocity);
        out[4] = a;
        out[5] = b;
        *(int *)(out + 6) = value;
    }
    return p;
}
