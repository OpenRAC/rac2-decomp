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

extern int math_fast_float_d(void *);
extern Moby_L02_003CD758 *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void moby_init_child_from_parent(void *, void *);

/* Keep the linked effect moby alive while the timer runs; delete both when it ends. */
void linked_effect_update(Moby_L02_003CD758 *m)
{
    Vars_L02_003CD758 *v = m->vars;

    if (v->timer == 0) {
        if (v->link != 0 && (v->link->type == 0xA20 /* moby class 2592 */ || v->link->type == 0xA21 /* moby class 2593 */)) moby_mark_spawned(v->link);
        moby_mark_spawned(m);
        return;
    }
    math_fast_float_d(&v->timer);
    if (v->link != 0 && !(v->link->type == 0xA20 /* moby class 2592 */ || v->link->type == 0xA21 /* moby class 2593 */)) {
        if (v->h310 == 0) v->link = CreateMoby(0xA20 /* moby class 2592 */);
        else v->link = CreateMoby(0xA21 /* moby class 2593 */);
        if (v->link == 0) {
            moby_mark_spawned(m);
            return;
        }
        moby_init_child_from_parent(v->link, m);
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
    moby_set_state(m, 0x17, 4);
}
