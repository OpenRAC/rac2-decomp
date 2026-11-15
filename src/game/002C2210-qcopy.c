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
extern unsigned char *D_001F2614;

/* func_002C2210: initializes an allocated effect record and its payload, as func_L00_0033C638
   does, with a lifted position and a scaled counter in place of the owner lookup. */
/* Creates a ground effect particle with its life, colour and starting speed. */
Particle *func_002C2210(float life, float secondLife, float third, Quad *position, int size, int color, int mode, int flag, float *vector, int counter)
{
    Particle *p = AllocParticle(0x35);
    if (p) {
        float *out = p->payload;
        p->position.q = *position;
        p->position.f[2] = p->position.f[2] + 0.05f;
        p->position.f[3] = IntToFloat(counter);
        p->color = color;
        p->b3 = 0x48;
        p->alpha = FloatToInt(0.4f) + 32;
        p->b1 = 0;
        p->b2 = *D_001F2614;
        p->size = size;
        p->life = life * 210000.0f;
        if (mode == 0) p->seed = 0;
        else if (mode == 1) p->seed = 32;
        else p->seed = RandomIntBelow(255);
        out[0] = p->life;
        *(short *)((char *)out + 8) = size;
        *((unsigned char *)out + 10) = flag;
        out[1] = secondLife * 210000.0f;
        *((unsigned char *)out + 11) = color >> 24;
        out[6] = third;
        { float *dst = out + 3; dst[0] = vector[0]; dst[1] = vector[1]; dst[2] = vector[2]; }
    }
    return p;
}
