#include "include_asm.h"

/* func_PAL_002C23B8, the PAL copy of func_002C16C0: the same C, where count, second and third - 1
   are scaled by 1.2f (60/50 Hz). */

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
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern unsigned char *D_001F25F0;

/* Another func_002C2210-style effect record (kind 0x2C): the colour split into its bytes in
   the payload, a byte count from `count` and the remaining sizes as given. */
Particle *func_PAL_002C23B8(Quad *position, float *vector, int size, int alpha, int rgb, int count,
                        float life, float second, float third, float fourth, float phase)
{
    Particle *p = func_002B9030(0x2C);
    if (p) {
        unsigned char *out;
        p->position.q = *position;
        out = (unsigned char *)p->payload;
        p->color = (alpha << 24) | rgb;
        p->position.f[3] = phase;
        p->alpha = func_00283CF0(4.0f) + 0x40;
        p->life = life;
        p->b1 = 0;
        p->b3 = 0x48;
        p->seed = func_002A77E0(255);
        p->b2 = *D_001F25F0;
        p->size = size;
        ((float *)out)[0] = vector[0];
        ((float *)out)[1] = vector[1];
        ((float *)out)[2] = vector[2];
        out[0x10] = func_00283CF0((float)count * 1.2f);
        ((float *)out)[5] = second * 1.2f;
        out[0x12] = rgb >> 8;
        ((float *)out)[6] = (third - 1.0f) * 1.2f + 1.0f;
        out[0x11] = rgb;
        out[0x13] = rgb >> 16;
        *(short *)(out + 0x1C) = size;
        *(short *)(out + 0x1E) = alpha;
        ((float *)out)[3] = fourth;
    }
    return p;
}
