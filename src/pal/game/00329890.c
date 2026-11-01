#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 rot[4];
    void *parent;
    f32 scale;
    f32 f18;
    f32 f1C;
    f32 f20;
    s32 f24;
} Pvar_3280C8;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 f20;
    u8 pad21[2];
    u8 f23;
    u8 pad24[8];
    f32 f2C;
    u8 f30;
    u8 f31;
    s16 f32;
    u16 f34;
    u8 pad36[2];
    s64 f38;
    u8 pad40[0x28];
    Pvar_3280C8 *pvar;
} Moby_3280C8;
extern Moby_3280C8 *func_0029EFD0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);

/* Spawn class 0xB7F at a position, owned by a parent, with a random spin. */
Moby_3280C8 *func_PAL_00329890(Moby_3280C8 *parent, f32 *rot, f32 *pos, s32 unused, s32 arg, f32 scale)
{
    Moby_3280C8 *m = func_0029EFD0(0xB7F);
    if (m != 0) {
        Pvar_3280C8 *pv;
        m->f30 = 0xFF;
        m->f32 = 0xFF;
        m->f31 = 1;
        m->f20 = 0;
        m->f38 = parent->f38;
        qcopy(m->pos, pos);
        pv = m->pvar;
        qcopy(pv->rot, rot);
        pv->parent = parent;
        pv->scale = scale;
        pv->f18 = func_002A7940();
        pv->f1C = func_002A7878(0.25132746f, 0.75398237f);
        pv->f20 = 1.0f;
        pv->f24 = arg;
        m->f23 = 0x5D;
        m->f34 |= 0x100;
        m->f2C = func_002A7878(0.01f, 0.0125f) * pv->f20;
    }
    return m;
}



