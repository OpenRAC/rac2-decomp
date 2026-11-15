#include "common.h"

typedef struct {
    s32 frames;
    f32 step;
    s32 f08;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    f32 vec[3];
    s32 f3C;
} Pvar_32E588;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 f20;
    u8 pad21[0x30 - 0x21];
    u8 f30;
    u8 f31;
    s16 f32;
    u16 f34;
    u8 pad36[0x68 - 0x36];
    Pvar_32E588 *pvar;
} Moby_32E588;

extern Moby_32E588 *func_0029EFD0(int);
extern float func_00283CE0(int);
extern void func_0027CFD0(void (*)(Moby_32E588 *), Moby_32E588 *);
extern void func_0032E708(Moby_32E588 *);

/* Spawn class 0xDC1 at a position with its timed parameters and start its update. */
Moby_32E588 *func_0032E588(f32 *pos, f32 *vec, s32 frames, f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, s32 e)
{
    Moby_32E588 *m = CreateMoby(0xDC1);
    if (m != 0) {
        Pvar_32E588 *pv;
        m->f30 = 0xFF;
        m->f32 = 0xFF;
        m->f31 = 1;
        m->f34 |= 0x41;
        m->f20 = 0;
        pv = m->pvar;
        qcopy(m->pos, pos);
        {
            f32 *dst = pv->vec;
            dst[0] = vec[0];
            dst[1] = vec[1];
            dst[2] = vec[2];
        }
        pv->frames = frames;
        pv->step = 1.0f / IntToFloat(frames);
        pv->f1C = w;
        pv->f20 = a;
        pv->f24 = b;
        pv->f28 = c;
        pv->f2C = d;
        pv->f3C = e;
        pv->f10 = x;
        pv->f14 = y;
        pv->f18 = z;
        pv->f08 = 0;
        func_0027CFD0(func_0032E708, m);
    }
    return m;
}
