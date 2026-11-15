#include "common.h"

typedef struct Moby_L02_003CD758 {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x34 - 0x20];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    struct Vars_L02_003CD758 *vars;
    u8 pad6C[0x98 - 0x6C];
    s32 f98;
    u8 pad9C[0xAA - 0x9C];
    u16 type;
    u8 padAC[0xF0 - 0xAC];
    f32 fF0;
    f32 fF4;
} Moby_L02_003CD758;

typedef struct Vars_L02_003CD758 {
    u8 pad000[0x20];
    f32 f20;
    s16 h24;
    u8 pad026[0x2E - 0x26];
    u8 b2E;
    u8 pad02F[0x88 - 0x2F];
    s16 h88;
    u8 pad08A[0x310 - 0x8A];
    s16 h310;
    u8 pad312[0x338 - 0x312];
    s32 timer;
    u8 pad33C[0x340 - 0x33C];
    f32 home[4];
    u8 pad350[0x370 - 0x350];
    Moby_L02_003CD758 *link;
} Vars_L02_003CD758;

extern int func_00282948(void *);
extern Moby_L02_003CD758 *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern void func_002B37E8(void *, void *);

/* Keep the linked effect moby alive while the timer runs; delete both when it ends. */
void func_L02_003CD758(Moby_L02_003CD758 *m)
{
    Vars_L02_003CD758 *v = m->vars;

    if (v->timer == 0) {
        if (v->link != 0 && (v->link->type == 0xA20 || v->link->type == 0xA21)) func_0029F338(v->link);
        func_0029F338(m);
        return;
    }
    func_00282948(&v->timer);
    if (v->link != 0 && !(v->link->type == 0xA20 || v->link->type == 0xA21)) {
        if (v->h310 == 0) v->link = CreateMoby(0xA20);
        else v->link = CreateMoby(0xA21);
        if (v->link == 0) {
            func_0029F338(m);
            return;
        }
        func_002B37E8(v->link, m);
        v->link->flags |= 0x100;
    }
    v->link->flags |= 0x41;
    v->link->flags &= 0xEFFF;
    v->link->f98 = 0;
    qcopy(m->pos, v->home);
    m->fF0 = m->fF4 = 0.0f;
    v->f20 = v->h24;
    m->f98 = 0;
    m->flags = (m->flags | 0x41) & 0xEFFF;
    v->h88 = 0;
    v->b2E = 1;
    func_002A7750(m, 0x17, 4);
}
