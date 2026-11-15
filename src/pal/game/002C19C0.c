#include "include_asm.h"



#include "common.h"
typedef struct {
    f32 velocity[3];
    u8 pad0C[8];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    s16 life;
} SmokeMotion;
typedef struct {
    u8 used;
    u8 flag1;
    u8 texture;
    u8 mode;
    u32 color;
    u8 frame;
    u8 fade;
    s16 age;
    f32 phase;
    f32 position[4];
    SmokeMotion motion;
} SmokeParticle;
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecAdd(void *, void *, void *);

/* Age a smoke particle: fade its colour towards grey and its alpha in and out. */
void func_PAL_002C21D8(SmokeParticle *p)
{
    SmokeMotion *m = &p->motion;
    float t;
    int r, g, b, a;
    u32 color;
    if (m->life < ++p->age) {
        part_kill(p);
        return;
    }
    t = IntToFloat(p->age) / IntToFloat(m->life);
    t = 1.0f - t;
    r = FloatToInt(IntToFloat(m->red) + t * -0.001f) & 0xFF;
    g = FloatToInt(IntToFloat(m->green) + t * -0.0011f) & 0xFF;
    b = FloatToInt(IntToFloat(m->blue) + t * -0.00111f) & 0xFF;
    if (p->age < 25) {
        t = IntToFloat(p->age) / IntToFloat(25);
        a = FloatToInt(IntToFloat(m->alpha) * t) & 0xFF;
    } else {
        t = IntToFloat(p->age - 25) / IntToFloat(m->life - 25);
        t = 1.0f - t;
        a = FloatToInt(IntToFloat(m->alpha) * t) & 0xFF;
    }
    color = a << 24;
    color |= b << 16;
    color |= g << 8;
    color |= r;
    p->color = color;
    p->frame++;
    FastVecAdd(p->position, p->position, m);
    m->velocity[2] += 0.00072000007f;
}


