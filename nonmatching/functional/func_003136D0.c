/* functional: high. Draft that compiled to retail bytes alone but has not landed in a linked build; the differences left are placement only. */
/*
 * func_003136D0: exact bytes in USA v1.01 with 15 dead initial values at declarations, whose only effect is gcse's insn count (the PRE spill-slot order). Over the limit of five per function ruled on 31 October 2026, so not linked; a maintainer can rule on it. Everything below is the whole unit `src/game/0030F7B0-ball-g8.c` as it matched, with flags `-O2 -G8 -ffunction-sections -g` (batch v1895).
 */
/* func_003136D0: nanotech ball update (RAC1 nanotech_ball_update, 4080 bytes, 28 places).
 * -g gives retail's two NOPs before div.s. Three wordings below carry the match:
 * - D_001A7A44[2] is read at an offset from its array name, so the macro load is two words and
 *   never fills a branch slot; D_001AF180 is reached through its $gp view.
 * - The interpolation arm keeps &v40 in a local and copies in a scoped block: the extra block note
 *   gives the pseudo the lifetime loop needs to hoist it, so the later &v40 is rebuilt after the call.
 * - The initial stores on locals are dead (flow deletes them, no word remains). gcse sizes its
 *   expression table from the insn count and numbers its reaching registers in hash order, which
 *   decides the four spill slots at 0x7C-0x88: retail's order needs the 513-bucket table.
 */
#include "common.h"
/* Adapted from RAC1 nanotech_ball_update (OpenRAC/rac1-decomp, GPL-3.0). */
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) Vec;
typedef struct Moby { char pad0[16]; Vec pos; unsigned char state; char pad21[15]; unsigned char update_dist; char pad31[3]; unsigned short flags; char pad36[0x32]; void *pvars; char pad6c[0x2c]; int collision; char pad9c[0x1c]; struct Moby *owner; unsigned char command; char padbd[3]; Vec rot_row0,rot_row1,rot_row2,rot; } Moby;
typedef struct { char pad0[0x80]; struct { Vec pos; } motion; char pad90[0x14c]; short invulnerable_frames; char pad1de[0xe2]; Vec gravity_dir; char pad2d0[0x1fe4]; unsigned char vehicle_mode; char pad22b5[0x217]; struct { int hp; } health; } Hero;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V_2D9EA0;
typedef struct { float x, y, z; } V3_2D9EA0;
typedef struct Part_2D9EA0 {
    int f0;
    int f4;
    unsigned char b8;
    char p9[3];
    float fC;
    V_2D9EA0 pos;
} Part_2D9EA0;
typedef struct Ext_2D9EA0 {
    int f0;
    union {
        struct { struct Moby *owner; float scale; float ang; } s;
        V3_2D9EA0 a;
    } u;
    V3_2D9EA0 b;
    short h1C;
    short h1E;
} Ext_2D9EA0;
typedef struct D_2D9EA0 {
    float f0;
    float f4;
    short h8;
    unsigned char hA;
    unsigned char pending;
    struct Moby *owner;
    V_2D9EA0 pos;
    V_2D9EA0 v20;
    Part_2D9EA0 *slots[8];
    int f50;
    short h54;
    unsigned char h56;
    unsigned char special;
    short h58[4];
    float f60[4];
    char p70[0xC];
    int f7C;
} D_2D9EA0;
extern char D_00189E20[], D_00189EA0[];
extern Vec D_L00_0023A670[], D_L00_0023A6F0[];
extern float D_001AF180_gp[] SDATA(D_001AF180);
extern char D_L00_001B8DC0[];
extern Moby *D_L00_001B1AEC;
extern int D_001A7A00;
extern unsigned char D_001A7A44[] MACRO_ADDR;
extern unsigned char D_001A7A0A;
extern int D_001AD7EC, D_001B1688;
extern int D_001AF11C __attribute__((sda)), D_001AF1A0 __attribute__((sda));
extern void func_002B00D8(void *,void *,void *,float);
extern void func_002AD330(void *,void *,void *,void *);
extern int func_00312B58(void *), func_002ACD38(void *);
extern void func_002A7750(void *,int,int), func_0029B720(int);
extern float D_001AF130 __attribute__((sda));
extern float D_001AF178 __attribute__((sda));
extern unsigned short D_001AF174 __attribute__((sda));
extern float D_001AF170 __attribute__((sda));
extern float D_001AF16C __attribute__((sda));
extern int D_001AF164 __attribute__((sda));
extern int D_001AF160 __attribute__((sda));
extern int D_001AF15C __attribute__((sda));
extern unsigned short D_001AF158 __attribute__((sda));
extern float D_001AF12C __attribute__((sda));
extern float D_001AF128 __attribute__((sda));
extern int D_001AF118 __attribute__((sda));
extern float D_001AF114 __attribute__((sda));
extern float D_001AF110 __attribute__((sda));
extern unsigned char D_001AF10C __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_002A77E0(int);

extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AF000(void *, float, float, float);
extern float func_002A78D8(float, float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_00282E48(void *, void *);
extern int func_00313678(void *);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, float, void *);
extern int func_002A7820(int, int);
extern void func_00313600(void);
extern int func_00283DB8(void *, float);
extern void func_0027CDC8(void (*)(void), Moby *);
extern void func_003146C0(void);
extern float func_00282E80(void *, void *);
extern void func_00313548(void *, void *, int);
extern Part_2D9EA0 *func_002C36D0(void *, int, int, int);
extern void func_003130F0(void *);
extern int func_00313210(void *);
extern void func_00312EB0(void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern void func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int);
extern float func_00283CE0(int);
extern float func_002A7AA8(float, float, float, float, float);

void func_003136D0(Moby *m) {
    V_2D9EA0 v0, v10, v20, v30, v40, v50, v60;
    D_2D9EA0 *d = (D_2D9EA0 *)m->pvars;

    switch (m->state) {
    case 0: {
        Moby *c = 0;
        int i = 0;
        m->state = 1;
        m->flags |= 0x41;
        m->collision = 0;
        m->command = 0;
        c = m->owner;
        qcopy_nc(&m->pos, &c->pos);
        qcopy_nc(&m->rot, &c->rot);
        func_00282F20(&d->pos, &m->rot_row2, 0.5f);
        func_00282CC0(&d->pos, &d->pos, &m->pos);
        *(int *)&d->f0 = 0;
        d->h8 = 0;
        d->f4 = func_002A7878(d->f0, 3.1415927f);
        d->h56 = 0;
        d->owner = 0;
        for (i = 0; i < 4; i++) d->f60[i] = (float)func_002A77E0(0xFF);
        for (i = 3; i >= 0; i--) d->h58[i] = D_001AF174;
        for (i = 7; i >= 0; i--) d->slots[i] = 0;
        if (D_L00_001B1AEC == 0) {
            func_002833F0(&m->rot_row0, &m->rot);
            D_L00_001B1AEC = m;
            m->update_dist = 0xFF;
            d->pending = 0;
            func_00282F20(&D_L00_0023A670[0], &m->rot_row0, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[0], &m->rot_row2);
            func_00282F20(&D_L00_0023A670[1], &m->rot_row1, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[1], &m->rot_row0);
            func_00282F20(&D_L00_0023A670[2], &m->rot_row2, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[2], &m->rot_row1);
            func_00282CC0(&D_L00_0023A670[3], &m->rot_row0, &m->rot_row2);
            func_00282F20(&D_L00_0023A670[3], &D_L00_0023A670[3], D_001AF130);
            func_00282DD8(&D_L00_0023A6F0[3], &D_L00_0023A670[3], &m->rot_row1);
            func_00282CC0(&D_L00_0023A670[4], &m->rot_row0, &m->rot_row1);
            func_00282F20(&D_L00_0023A670[4], &D_L00_0023A670[4], D_001AF130);
            func_00282DD8(&D_L00_0023A6F0[4], &D_L00_0023A670[4], &m->rot_row2);
            func_00282CF0(&D_L00_0023A670[5], &m->rot_row1, &m->rot_row2);
            func_00282F20(&D_L00_0023A670[5], &D_L00_0023A670[5], D_001AF130);
            func_00282DD8(&D_L00_0023A6F0[5], &D_L00_0023A670[5], &m->rot_row0);
            func_00282CF0(&D_L00_0023A670[6], &m->rot_row0, &m->rot_row2);
            func_00282F20(&D_L00_0023A670[6], &D_L00_0023A670[6], D_001AF130);
            func_00282DD8(&D_L00_0023A6F0[6], &D_L00_0023A670[6], &m->rot_row1);
            func_00282CF0(&D_L00_0023A670[7], &m->rot_row0, &m->rot_row1);
            func_00282F20(&D_L00_0023A670[7], &D_L00_0023A670[7], D_001AF130);
            func_00282DD8(&D_L00_0023A6F0[7], &D_L00_0023A670[7], &m->rot_row2);
        }
        {
            float a = 0.0f;
            a = func_002A7878(0.0f, 6.2831855f);
            func_002AF000(&d->v20, 1.0f, a, func_002A7878(-1.5707964f, 1.5707964f));
        }
        d->v20.w = func_002A78D8(0.785398006f, 1.5707964f);
    }
    case 1: {
        Moby *c = 0;
        qcopy_nc(&m->pos, &m->owner->pos);
        qcopy_nc(&d->pos, &m->owner->pos);
        func_002B00D8(&m->pos, &d->pos, &d->pos, -0.5f);
        c = m->owner;
        if ((signed char)c->state < 0 || func_00312B58(c) || c == m) {
            m->state = 2;
            d->f50 = 0;
        }
    }
    case 2:
        if (m->state == 2) {
            int i = 0;
            qcopy_nc(&d->pos, &m->pos);
            func_002B00D8(&m->pos, &d->pos, &d->pos, -0.5f);
            func_00312EB0(m);
            for (i = 0; i < 8; i++) {
                if (d->slots[i] != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
                    x->u.s.scale = D_001AF178 * func_00283198(x->u.s.ang) + D_001AF130;
                    x->u.s.ang = func_00283B98(x->u.s.ang, D_001AF180_gp[i]);
                }
            }
        }
        {
            Hero *g = (Hero *)(D_00189E20);
            int lim = D_001A7A00;
            if (g->vehicle_mode == 1) lim = 4;
            if (m->state != 1 && D_L00_001B1AEC != 0 && ((D_2D9EA0 *)D_L00_001B1AEC->pvars) != 0 && g->health.hp != 0
                && (g->health.hp + ((D_2D9EA0 *)D_L00_001B1AEC->pvars)->pending < lim || (D_001A7A44[2] != 0 && g->invulnerable_frames == 0))
                && (d->slots[0] || d->slots[1] || d->slots[2] || d->slots[3] || d->slots[4] || d->slots[5] || d->slots[6] || d->slots[7])
                && func_00282E48(&m->pos, D_00189EA0) < 10.0f
                && func_00313678(m)) {
                int i;
                m->state = 3;
                ((D_2D9EA0 *)D_L00_001B1AEC->pvars)->pending++;
                if (D_001A7A44[2] != 0) *(short *)(D_00189EA0 + 0x15C) = 0x258;
                d->h54 = (D_001AF158);
                func_00282D30(&v30, D_00189EA0 + 0x240, -D_001AF170);
                func_00282CC0(&v30, D_00189EA0, &v30);
                func_00282D30(&v0, D_00189EA0 + 0x240, -D_001AF16C);
                func_00282CF0(&v20, &v30, &m->pos);
                func_002B00D8(&m->pos, &v20, &v20, 0.5f);
                func_00282DD8(&v40, &v20, &v0);
                func_00282DD8(&v0, &v40, &v20);
                func_002ACEC0(&v0, &v0, -1.5707964f, &v20);
                func_00282F20(&v0, &v0, D_001AF16C);
                func_00282D30(&v50, &v20, 0.5f);
                for (i = 0; i < 8; i++) {
                    if (d->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
                        func_002ACEC0(&v10, &v0, (float)i * 0.44854968786239624f, &v20);
                        func_00282CC0(&v60, &v50, &v10);
                        {
                            V3_2D9EA0 *dst = &x->u.a;
                            dst->x = v60.x;
                            dst->y = v60.y;
                            dst->z = v60.z;
                        }
                        {
                            V3_2D9EA0 *dst = &x->b;
                            V3_2D9EA0 *src = (V3_2D9EA0 *)&d->slots[i]->pos;
                            dst->x = src->x;
                            dst->y = src->y;
                            dst->z = src->z;
                        }
                        x->h1E = x->h1C = (func_002A7820(D_001AF160, D_001AF164));
                    }
                }
            }
        }
        d->f0 = D_001AF12C * func_00283198(d->f4);
        d->f4 = func_00283B98(d->f4, D_001AF128);
        if (D_L00_001B1AEC == m) func_00313600();
        qcopy(&v0, &m->pos);
        func_002B00D8(&m->pos, &v0, &v0, -0.5f);
        v0.w = 1.0f;
        if (func_00283DB8(&v0, 64.0f) >= 0) {
            int i;
            int n = 0;
            func_0027CDC8(func_003146C0, m);
            if (10.0f < func_00282E80(&m->pos, D_L00_001B8DC0)) n = (5);
            else n = (40);
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = 0;
                Part_2D9EA0 *p = 0;
                func_00313548(m, &v10, i);
                e = func_002C36D0(&v10, n, 2, 0);
                if (e != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(e + 1);
                    qcopy(&v20, &m->pos);
                    qzero_nc(&v30);
                    if (m->state == 1) func_002AD330(m, m->owner, &m->pos, &v30);
                    else if (d->owner) {
                        func_002AD330(m, d->owner, &m->pos, &v30);
                        func_00282CF0(&v20, &v20, &v30);
                    }
                    func_00282CC0(&v10, &v10, &v30);
                    x->b.x = e->pos.x - v20.x;
                    x->b.y = e->pos.y - v20.y;
                    x->b.z = e->pos.z - v20.z;
                    if (m->state == 2) x->u.s.owner = m;
                    else x->u.s.owner = m->owner;
                    if (d->special) e->f4 = D_001AF11C;
                    else e->f4 = D_001AF118;
                    e->fC = D_001AF110;
                }
                p = d->slots[i];
                if (p == 0) {
                    d->slots[i] = func_002C36D0(&v10, 0, 1, 0);
                    if (d->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
                        x->u.s.scale = D_001AF130;
                        x->u.s.ang = 0.0f;
                        d->slots[i]->fC = D_001AF114;
                        if (d->special) d->slots[i]->f4 = D_001AF11C;
                        else d->slots[i]->f4 = D_001AF118;
                    }
                } else {
                    qcopy_nc(&p->pos, &v10);
                    p->b8 += D_001AF10C;
                }
            }
        } else if (D_001AD7EC || d->owner) {
            int i = 0;
            for (i = 0; i < 8; i++) if (d->slots[i]) qcopy_nc(&d->slots[i]->pos, &m->pos);
        }
        break;
    case 3:
        if (D_L00_001B1AEC == m) func_00313600();
        if (d->h56 != 0) {
            func_00282D30(&m->pos, D_00189E20 + 0x2C0, -D_001AF170);
            func_00282CC0(&m->pos, D_00189E20 + 0x80, &m->pos);
            m->rot.w = 0.523598849773407f;
            if (func_00313210(m) != 0 && func_002A77E0(5) == 0) func_003130F0(m);
        }
        {
            Hero *g = (Hero *)(D_00189E20);
            int lim = D_001A7A00;
            if (g->vehicle_mode == 1) lim = 4;
            if (g->health.hp == lim && g->invulnerable_frames != 0 && D_001A7A44[2] != 0) {
                int r = 0;
                r = (D_001AF15C);
                if (d->h54 < r) {
                    int i = 0;
                    d->h54 = r;
                    for (i = 0; i < 4; i++) d->h58[i]++;
                }
            }
        }
        if (func_00282978(&d->h54)) {
            int i = 0;
            for (i = 0; i < 8; i++) {
                if (d->slots[i] != 0) {
                    func_002B9180(d->slots[i]);
                    d->slots[i] = 0;
                }
            }
            if (D_L00_001B1AEC == m) m->state = 4;
            else func_0029F338(m);
        } else {
            int i;
            func_00282D30(&v20, D_00189E20 + 0x2C0, -D_001AF170);
            func_00282CC0(&v20, D_00189E20 + 0x80, &v20);
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = d->slots[i];
                Ext_2D9EA0 *x = 0;
                if (e == 0) continue;
                x = (Ext_2D9EA0 *)(e + 1);
                if (func_00282978(&x->h1E)) {
                    if (d->h56 == 0) {
                        Hero *g = (Hero *)(D_00189E20);
                        int lim = D_001A7A00;
                        int old_health = g->health.hp;
                        if (g->vehicle_mode == 1) lim = 4;
                        if (g->health.hp != 0) {
                            int amount = 1;
                            if (D_001A7A0A) amount = D_001AF1A0;
                            if (d->special) {
                                int t = g->health.hp + amount * 4;
                                g->health.hp = (lim < t) ? lim : t;
                            } else {
                                int t = g->health.hp + amount;
                                g->health.hp = (lim < t) ? lim : t;
                            }
                            if (old_health != ((Hero *)D_00189E20)->health.hp) func_0029B720(0x168);
                        }
                        {
                            D_2D9EA0 *o = (D_2D9EA0 *)D_L00_001B1AEC->pvars;
                            o->pending--;
                            if ((signed char)o->pending < 0) o->pending = 0;
                        }
                        if (d->special) func_002E5DA0(1, 0x20, m, 0x200);
                        else func_002E5DA0(1, 0x20, m, 0x1F5);
                        d->h56 = 1;
                    }
                    func_002B9180(e);
                    d->slots[i] = 0;
                } else {
                    float t;
                    float k = 0.0f;
                    Part_2D9EA0 *n = 0;
                    V_2D9EA0 *mid = &v40;
                    {
                        qcopy(mid, &e->pos);
                    }
                    k = func_00283CE0(x->h1C);
                    k = (float)x->h1E / k;
                    {
                        V3_2D9EA0 *src = &x->b;
                        v10.x = src->x;
                        v10.y = src->y;
                        v10.z = src->z;
                    }
                    v10.w = 0.0f;
                    t = 1.0f - k;
                    v0.x = v10.x - x->u.a.x;
                    v0.y = v10.y - x->u.a.y;
                    v0.z = v10.z - x->u.a.z;
                    v30.x = v20.x - x->u.a.x;
                    v30.y = v20.y - x->u.a.y;
                    v30.z = v20.z - x->u.a.z;
                    e->pos.x = func_002A7AA8(v0.x, v10.x, v20.x, v30.x, t);
                    e->pos.y = func_002A7AA8(v0.y, v10.y, v20.y, v30.y, t);
                    e->pos.z = func_002A7AA8(v0.z, v10.z, v20.z, v30.z, t);
                    v50.x = func_002A78D8(0.0f, 0.00999999978f) + e->pos.x;
                    v50.y = func_002A78D8(0.0f, 0.00999999978f) + e->pos.y;
                    v50.z = func_002A78D8(0.0f, 0.00999999978f) + e->pos.z;
                    n = func_002C36D0(&v50, (0x14), 0, 0);
                    if (n != 0) {
                        if (d->special) n->f4 = D_001AF11C;
                        else n->f4 = D_001AF118;
                        n->fC = D_001AF110;
                    }
                    func_00282CC0(&v40, &e->pos, &v40);
                    func_00282D30(&v40, &v40, 0.5f);
                    v50.x = func_002A78D8(0.0f, 0.00999999978f) + v40.x;
                    v50.y = func_002A78D8(0.0f, 0.00999999978f) + v40.y;
                    v50.z = func_002A78D8(0.0f, 0.00999999978f) + v40.z;
                    n = func_002C36D0(&v50, (0x14), 0, 0);
                    if (n != 0) {
                        if (d->special) n->f4 = D_001AF11C;
                        else n->f4 = D_001AF118;
                        n->fC = D_001AF110;
                    }
                }
            }
        }
        break;
    case 4:
        if (D_L00_001B1AEC == m) func_00313600();
        break;
    case 5:
        if ((D_001B1688 & 1) && func_002ACD38(&m->pos)) func_002A7750(m, 2, -1);
        break;
    }
}
