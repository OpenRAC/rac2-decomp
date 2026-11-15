#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    union { Quad q; float f[4]; } position;
    float payload[8];
} Particle;

extern Particle *func_002B9030(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern unsigned char *D_L00_001FEAB0;
extern float D_001B8DC0[];

/* func_002C2210's effect record with a per-call palette index, two more payload words and
   a pull of 0.9 towards the 0x1B8DC0 point. The floats lead the parameter list, as in
   func_002C2210: that numbering is what gives the flag a saved register. */
/* Creates a particle like the basic one, but it is also pulled a little toward a fixed point. */
Particle *func_L00_0033EC48(float life, float secondLife, Quad *position, int size, int color, int mode, int flag, float *vector,
                            int word, int index, short tag, int counter)
{
    Particle *p = AllocParticle(0x5C);
    if (p) {
        float *out = p->payload;
        float pull[4] __attribute__((aligned(16)));
        p->position.q = *position;
        p->position.f[3] = IntToFloat(counter);
        p->color = color;
        p->b3 = 0x48;
        p->alpha = FloatToInt(0.4f) + 32;
        p->b1 = 0;
        p->b2 = D_L00_001FEAB0[index];
        p->size = size;
        p->life = life * 210000.0f;
        if (mode == 0) p->seed = 0x40;
        else if (mode == 1) p->seed = 0x5A;
        else if (mode == 2) p->seed = RandomIntBelow(255);
        out[0] = p->life;
        *(short *)((char *)out + 8) = size;
        *((unsigned char *)out + 10) = flag;
        out[1] = secondLife * 210000.0f;
        *((unsigned char *)out + 11) = color >> 24;
        *(int *)(out + 6) = word;
        *(short *)((char *)out + 0x1E) = tag;
        { float *dst = out + 3; dst[0] = vector[0]; dst[1] = vector[1]; dst[2] = vector[2]; }
        FastVecSub(pull, D_001B8DC0, &p->position);
        vec_scale_to_length(pull, pull, 0.9f);
        FastVecAdd(&p->position, &p->position, pull);
    }
    return p;
}
