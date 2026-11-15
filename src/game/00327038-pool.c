/* func_00329488: draw every particle in the pool that belongs to an object, then release them.
   Its own unit for -fno-gcse: each loop loads the pool's address in its own preheader. The pool
   address is an int in the first loop so that the counter survives and the loop test stays on i. */
#include "common.h"

typedef struct {
    float v[4];
    float f10;
    float f14;
    float f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int pad2C;
    int f30;
    int f34;
    void *owner;
    int pad3C;
} F328Tail;

typedef struct {
    float m[4];
    F328Tail t;
} F328Particle;

extern F328Particle D_0022C9A0[300];
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283180(float);
extern void func_002820A0(void);
extern void func_002820C8(void);
extern void func_002820D0(float, float, float, void *, int, float **);
extern void func_00282CC0(void *, void *, void *);
extern void func_00329630(char *);

/* Draws every particle that belongs to an object, first as soft glows and then as flat quads. */
void func_00329488(void *obj) {
    float v[4] __attribute__((aligned(16)));
    float full, scale, s, a, b;
    int i, n;

    SetGsRegisterConstant();
    full = 128.0f;
    for (i = 0; i < 300; i++) {
        int base = (int)gObjectParticles;
        F328Particle *p = (F328Particle *)(base + i * 80);
        float *pos = p->m;
        if (p->t.owner != obj)
            continue;
        if (p->t.f30 < (p->t.f34 >> 1))
            scale = IntToFloat(p->t.f30) / IntToFloat((p->t.f34 >> 1));
        else
            scale = 1.0f;
        n = FloatToInt(scale * full);
        s = FastSinOrCosA(p->t.f14);
        a = (s + 1.0f) * 0.5f;
        b = a * (scale * -0.025f);
        v[2] = v[1] = v[0] = s * 0.05f;
        FastVecAdd(v, v, pos);
        DrawBillboardQuadWithUv((p->t.f18 + p->t.f18) * a, b, 0.08f, v, n, 0);
    }
    NoOpFunction();
    for (i = 0; i < 300; i++) {
        F328Particle *base = gObjectParticles;
        F328Particle *p = &base[i];
        if (p->t.owner == obj)
            DrawObjectParticle((char *)p);
    }
}
