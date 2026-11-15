#include "common.h"

typedef int L01_EF38Quad __attribute__((mode(TI)));
typedef struct {
    float scale;
    float second;
    int color;
    int kind;
    float rate;
} L01_EF38Payload;
typedef struct {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    int color;
    unsigned char seed;
    unsigned char alpha;
    unsigned short size;
    float life;
    union {
        L01_EF38Quad q;
        float f[4];
    } position;
    L01_EF38Payload payload;
} L01_EF38Particle;

extern L01_EF38Particle *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern unsigned char *D_L01_001FF110;

L01_EF38Particle *func_L01_0032EF38(L01_EF38Quad *position, int color, int kind, float scale, float second, int life)
{
    L01_EF38Particle *p;
    L01_EF38Payload *out;

    p = func_002B9030(0x34);
    if (p) {
        out = &p->payload;
        qcopy(&p->position, position);
        p->color = color;
        p->b3 = 0x44;
        p->position.f[2] = p->position.f[2] + 0.05f;
        p->alpha = FloatToInt(2.0f) + 32;
        p->b1 = 1;
        p->b2 = *D_L01_001FF110;
        p->size = life;
        p->life = scale * 210000.0f;
        p->seed = func_002A77E0(255);
        out->color = color;
        out->kind = kind;
        p->payload.scale = scale;
        out->second = second;
        out->rate = 1.0f / IntToFloat(life);
    }
    return p;
}
