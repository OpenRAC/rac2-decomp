#include "names.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_002B9180(void *);

typedef struct {
    int opaque;
    char *source;
    int frame;
} ParticleContext_C01F8;

typedef struct {
    unsigned short opaque0;
    unsigned char shade, opaque3;
    int packed;
    unsigned char phase, opaque9;
    short timer;
    float value;
    float position[4];
    ParticleContext_C01F8 context;
} Particle_C01F8;

extern float ref_L00_00337058_00 __attribute__((sda));
extern int ref_L00_00337058_01 __attribute__((sda));
extern float ref_L00_00337058_02 __attribute__((sda));
extern unsigned char ref_L00_00337058_03 __attribute__((sda));
extern float ref_L00_00337058_04[];
extern unsigned char *ref_L00_00337058_05[];

/* Keeps a shimmering particle next to its source object and cycles its brightness. It disappears when its timer ends. */
void func_002C01F8(Particle_C01F8 *self) {
    float offset[4];
    ParticleContext_C01F8 *context = &self->context;
    int shadeIndex;

    self->value = ref_L00_00337058_00;
    self->packed = ref_L00_00337058_01;
    self->phase += ref_L00_00337058_03;
    FastVecSub(offset, context->source + 0x10, ref_L00_00337058_04);
    vec_scale_to_length(offset, offset, ref_L00_00337058_02);
    FastVecAdd((char *)self->position, context->source + 0x10, (char *)offset);
    shadeIndex = FloatToInt((float)(context->frame / 2));
    self->shade = ref_L00_00337058_05[0][shadeIndex];
    context->frame++;
    if (context->frame >= 31) context->frame = 0;
    if (self->timer == 0) KillParticle(self);
}
