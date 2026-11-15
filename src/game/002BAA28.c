#include "common.h"

/* Spawn a two-ended trail particle (kind 2) between two points. */
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 used;
    u8 flag1;
    u8 texture;
    u8 mode;
    s32 color;
    u8 alpha;
    u8 fade;
    s16 kind;
    f32 phase;
    Quad position;
    struct ParticleTrail {
        s32 packedA;
        s32 packedB;
        s32 startColor;
        s32 endColor;
        s16 kind;
        s16 duration;
        s16 size;
        s16 scaleA;
        s16 scaleB;
    } trail;
} Particle;
extern Particle *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern void vec_pack_direction(float *, int *);
extern void vec_decode_byte_color(void *, void *);
extern u8 *D_001F2540[];
extern u8 *D_001F259C;

Particle *part_spawn_trail(void *position, float *from, float *to, int startColor, int endColor, int kind, int duration, int size, int flags)
{
    Particle *particle = part_alloc(2);
    float packedVecA[4], packedVecB[4];
    struct ParticleTrail *trailData;
    if (particle != 0) {
        qcopy(&particle->position, position);
        particle->color = startColor;
        particle->fade = FloatToInt(4.0f) + 0x40;
        particle->phase = 0.0f;
        particle->flag1 = 0;
        particle->mode = 0x44;
        particle->alpha = FloatToInt(math_random_float_range(particle->phase, 255.0f));
        if (flags == -1) {
            particle->texture = *D_001F259C;
        } else {
            particle->texture = *D_001F2540[flags & 0xFFFF];
            if (flags & 0x10000)
                particle->mode = 0x48;
        }
        particle->kind = kind;
        trailData = &particle->trail;
        trailData->scaleA = FloatToInt(from[3] * 210.00002f);
        trailData->scaleB = FloatToInt(to[3] * 210.00002f);
        vec_pack_direction(from, &trailData->packedA);
        vec_pack_direction(to, &trailData->packedB);
        vec_decode_byte_color(packedVecA, &trailData->packedA);
        vec_decode_byte_color(packedVecB, &trailData->packedB);
        trailData->startColor = startColor;
        trailData->endColor = endColor;
        trailData->kind = kind;
        trailData->duration = duration;
        trailData->size = size;
    }
    return particle;
}
