/* Homing projectile update, in all 27 levels. A unit of its own for -ffast-math (min.s) and
 * -frac2-hazard-labels (the fast/slow arms' cross-jump lands on the mtc1 hazard nop). */

#include "common.h"

typedef struct Vec4_003C9978 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec4_003C9978;

typedef int TI_003C9978 __attribute__((mode(TI)));

typedef union Quad_003C9978 {
    TI_003C9978 q;
    Vec4_003C9978 v;
} Quad_003C9978;

typedef struct Class_003C9978 {
    u8 pad0[0x46];
    s16 kind;                       /* 0x46 */
} Class_003C9978;

typedef struct Moby_003C9978 {
    u8 pad0[0x10];
    Vec4_003C9978 pos;              /* 0x10 */
    u8 state;                       /* 0x20 */
    u8 pad21[3];
    Class_003C9978 *cls;            /* 0x24 */
    u8 pad28[8];
    union {
        u64 all;
        struct {
            u32 lo;
            u16 mode;
            u16 hi;
        } h;
    } flags;                        /* 0x30 */
    u8 pad38[0x30];
    struct Vars_003C9978 *vars;     /* 0x68 */
    u8 pad6C[0x2C];
    s32 alive;                      /* 0x98 */
    u8 pad9C[0xE];
    s16 oclass;                     /* 0xAA */
    u8 padAC[0xC];
    s32 b8;                         /* 0xB8 */
    u8 padBC[4];
    Vec4_003C9978 m[3];             /* 0xC0 */
} Moby_003C9978;

typedef struct Vars_003C9978 {
    Vec4_003C9978 vel;              /* 0x00 */
    Vec4_003C9978 trail[4];         /* 0x10 */
    Moby_003C9978 *target;          /* 0x50 */
    f32 f54;                        /* 0x54 */
    f32 wobble_z;                   /* 0x58 */
    f32 wobble;                     /* 0x5C */
    f32 speed;                      /* 0x60 */
    f32 spin;                       /* 0x64 */
    f32 max_speed;                  /* 0x68 */
    s16 flip;                       /* 0x6C */
    s16 effect;                     /* 0x6E */
    f32 accel;                      /* 0x70 */
    f32 damage;                     /* 0x74 */
    u8 b78;                         /* 0x78 */
    u8 b79;                         /* 0x79 */
    u8 spark;                       /* 0x7A */
    u8 fast;                        /* 0x7B */
    u8 locked;                      /* 0x7C */
    u8 trail_timer;                 /* 0x7D */
    u16 life;                       /* 0x7E */
} Vars_003C9978;

typedef union Info_003C9978 {
    struct {
        Vec4_003C9978 a;
        Vec4_003C9978 b;
        /* Reused as the collision request tail before the direction is needed. */
        Vec4_003C9978 direction;
    } v;
    struct {
        Vec4_003C9978 direction;
        void *source;
        u32 flags;
        u8 kind;
        u8 count;
        u16 oclass;
        float damage;
        int repeats;
        float extra;
    } hit;
    struct {
        u8 pad0[0x10];
        struct Pair_003C9978 {
            void *p[2];
        } pair;
    } t;
} Info_003C9978;

typedef struct Collide_003C9978 {
    u8 pad0[0xAA];
    u16 oclass;
} Collide_003C9978;

extern Moby_003C9978 *D_L00_001C3280[];
extern void *D_0018C0B0;
extern s16 D_0018A168;
extern s32 D_L00_001A8FF0 __attribute__((sda));
extern s32 D_L00_001A8FF4;
extern s32 D_L00_001ADB2C MACRO_ADDR;
extern Collide_003C9978 *D_L00_001BF218;
extern u8 D_L00_001BF230[];
extern struct Pair_003C9978 D_L00_001B0128;

extern int func_001163B0(void);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_00277F48(float, void *, int, void *, int);
extern int func_00282948(int *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern int func_002AB1F0(void *);
extern void func_002AC728(void *, void *, float, float, int);
extern void func_002FEE50(int);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_00334160(void *, int, int);
extern void ref_L00_003C9978_00(void (*)(Moby_003C9978 *), void *);
extern void func_L00_003CA650(Moby_003C9978 *);
extern void func_L00_00320B70(void *, void *, void *, void *, void *, int, float, float, float, float);
extern void func_L00_003252A8(void *, void *, int);
extern void func_L00_00325300(void *, void *);
extern void * func_L00_00341410(void *, void *, void *, int, int, float);

void func_L00_003C9978(Moby_003C9978 *self)
{
    Vec4_003C9978 saved;
    Quad_003C9978 up;
    Quad_003C9978 off;
    Vec4_003C9978 step;
    Info_003C9978 info;
    int life;
    int spark;
    int trail_timer;
    int fast_trail;
    Vars_003C9978 *vars;
    int i;

    off.q = 0;
    vars = self->vars;
    up.q = 0;
    off.v.x = -0.3f;
    up.v.z = 1.0f;
    off.v.w = 1.0f;

    switch (self->state) {
    case 0:
        self->state = 1;
        vars->flip = func_001163B0() % 2;
        vars->spin = 0.0f;
        func_00282F20(&self->m[0], &vars->vel, 1.0f);
        func_00282DD8(&self->m[1], &self->m[0], &up);
        func_00282F20(&self->m[1], &self->m[1], 1.0f);
        func_00282DD8(&self->m[2], &self->m[1], &self->m[0]);
        func_00283098(&off, &off, &self->m[0]);
        func_00300190(&self->pos, &self->pos);
        func_00300248(vars, vars);
        func_00282CC0(&off, &off, &self->pos);
        func_00282F20(&step, &off, 0.01f);
        qcopy(&vars->trail[0], &off);
        for (i = 0; i < 3; i++)
            func_00282CC0(&vars->trail[i + 1], &vars->trail[i], &step);
        vars->trail_timer = 2;
    case 1: {
        float dist;
        float travelled;
        int hit;

        vars->spin = vars->spin - 0.1f;
        if (vars->spin <= -8.0f)
            vars->spin = vars->spin + 8.0f;

        if (vars->target != 0 && vars->locked == 0) {
            if ((s8)vars->target->state < 0 || vars->target->alive == 0)
                vars->target = 0;
            if (vars->target == 0) {
                int n = func_00277F48(15.0f, &self->pos, 0, self, 0);
                int i;

                /* The end test leaves by goto, so the break is the first exit expand_end_loop sees
                 * and the whole body rotates. It is then too long for jump.c to duplicate, which
                 * keeps retail's entry branch to the test. */
                for (i = 0;; i++) {
                    Moby_003C9978 *m;
                    Class_003C9978 *cls;
                    u16 *mode;
                    s16 *kind;
                    Moby_003C9978 **found;

                    if (i >= n)
                        goto searched;
                    m = D_L00_001C3280[i];
                    mode = &m->flags.h.mode;
                    if ((*mode & 0x1000) && m->oclass != 0xA7E && m != D_0018C0B0) {
                        cls = m->cls;
                        kind = &cls->kind;
                        if (*kind == 5) {
                            found = &vars->target;
                            *found = m;
                            break;
                        }
                    }
                }
            searched:;
            }
        }

        qcopy(&saved, &self->pos);
        func_00282F20(&self->m[0], &vars->vel, 1.0f);
        func_00282DD8(&self->m[1], &self->m[0], &up);
        func_00282F20(&self->m[1], &self->m[1], 1.0f);
        func_00282DD8(&self->m[2], &self->m[1], &self->m[0]);
        func_00282CC0(&self->pos, &self->pos, &vars->vel);
        life = vars->life;
        if (func_00282948(&life) != 0) {
            self->state = 2;
            self->flags.h.mode |= 0x41;
        }
        vars->life = life;

        if (self->pos.x < 2.0f || self->pos.x > 1021.0f || self->pos.y < 2.0f || self->pos.y > 1021.0f
            || self->pos.z < 2.0f || self->pos.z > 1021.0f) {
            qcopy(&self->pos, &saved);
            self->state = 2;
            self->flags.h.mode |= 0x41;
        }

        off.v.x = -0.3f;
        off.v.w = 1.0f;
        off.v.y = 0.0f;
        off.v.z = 0.0f;
        func_00283098(&off, &off, &self->m[0]);
        func_00282CC0(&off, &off, &self->pos);
        func_00300190(&off, &off);
        self->m[1].y = self->m[1].y * 0.5f;
        self->m[2].z = self->m[2].z * 0.5f;

        if (func_00277258(&self->pos, 0x10, self, 0.25f) != 0)
            hit = 1;
        else
            hit = func_002761F8(&saved, &self->pos, 0x10, self, 0) != 0;
        if (hit) {
            if (D_L00_001BF218 != 0 && (D_L00_001BF218->oclass == 0x1366 || D_L00_001BF218->oclass == 0x1367))
                hit = 0;
            if (hit) {
                int n = func_00277F48(1.0f, &self->pos, 0, self, 0);
                int i;

                for (i = 0; i < n; i++) {
                    if (D_L00_001C3280[i]->flags.all & 0x500000000000ULL) {
                        func_002A8C00(&info, self, 0x210000, vars->damage, vars);
                        info.hit.oclass = self->oclass;
                        info.hit.kind = 5;
                        info.hit.count = 3;
                        func_002A8E20(D_L00_001C3280[i], &info);
                        func_00334160(D_L00_001C3280[i], 0x40, self->b8);
                    }
                }
                func_002AC728(self, D_L00_001BF230, 1.0f, 13.0f, 0);
                self->state = 2;
                self->flags.h.mode |= 0x41;
            }
        }

        func_00282F20(&vars->vel, &vars->vel,
                      (vars->max_speed < vars->speed ? vars->max_speed : vars->speed) * 0.016666668f);
        vars->speed = vars->speed + vars->accel;

        if (vars->target != 0) {
            float *health = ((float *)func_002AB1F0(vars->target));
            int n;


            func_L00_003252A8(vars->target, &info, 1);
            if (health != 0 && D_L00_001A8FF0 == 0) {
                func_00282D30(&info.v.b, &vars->target->m[2], health[4]);
                func_00282CC0(&info.v.b, &info.v.b, &vars->target->pos);
            } else if (D_L00_001A8FF0 != 0) {
                func_L00_00325300(self, &info.v.direction);
                func_00282F20(&info.v.direction, &info.v.direction, 1.0f);
                func_00282CC0(&info.v.b, &info.v.direction, &vars->target->pos);
            } else {
                qcopy(&info.v.b, &vars->target->pos);
            }
            dist = func_00282E48(&self->pos, &info.v.b);
            if (vars->fast != 0) {
                if (dist < 1.5f)
                    dist = 0.0f;
            } else {
                if (dist < 0.25f)
                    dist = 0.0f;
            }
            n = D_L00_001A8FF0;
            if (n == 0)
                n = D_L00_001A8FF4;
            if (n == 0 && D_0018A168 == 0) {
                info.v.b.y += func_00283198(vars->wobble) * (dist * 0.749f < 0.749f ? dist * 0.749f : 0.749f);
                info.v.b.x -= func_00283180(vars->wobble) * (dist * 0.751f < 0.751f ? dist * 0.751f : 0.751f);
                info.v.b.z += (func_00283198(vars->wobble_z) + 1.0f) * (dist * 0.5f < 0.5f ? dist * 0.5f : 0.5f);
            }
            if (vars->fast != 0)
                func_L00_00320B70(&self->pos, vars, &info.v.b, &vars->f54, &info, 0, 0.03f, 0.2f, 0.0f, 1.0f);
            else
                func_L00_00320B70(&self->pos, vars, &info.v.b, &vars->f54, &info, 0, 0.03f, 0.2f, 0.0f, 0.25f);
        }

        travelled = func_00282E48(&self->pos, &saved);
        info.v.a.w = -1.0f;
        spark = vars->spark;
        if (func_00282948(&spark) != 0 || vars->spark == 0) {
            info.t.pair = D_L00_001B0128;
            func_L00_00341410(self, &info, info.t.pair.p[vars->flip % 2], vars->b78, vars->b79, travelled * 0.5f);
            vars->flip++;
        }
        vars->spark = spark;
        vars->wobble = func_00283B98(vars->wobble, func_002A7878(0.01f, 0.1f));
        vars->wobble_z = func_00283BE0(vars->wobble_z, func_002A7878(0.025f, 0.25f));
        fast_trail = D_L00_001ADB2C;
        trail_timer = vars->trail_timer;
        if (fast_trail != 0) {
            for (i = 3; i > 0; i--) {
                qcopy(&vars->trail[i], &vars->trail[i - 1]);
                func_00300190(&vars->trail[i], &vars->trail[i]);
            }
            qcopy(&vars->trail[0], &off);
        } else if (func_00282948(&trail_timer) != 0) {
            for (i = 3; i > 0; i--)
                qcopy(&vars->trail[i], &vars->trail[i - 1]);
            qcopy(&vars->trail[0], &off);
            trail_timer = 2;
        }
        vars->trail_timer = trail_timer;
        for (i = 2; i >= 0; i--)
            ;
        break;
    }
    case 2:
        func_002FEE50(vars->effect);
        func_0029F338(self);
        return;
    }

    if (self != 0) {
        if (self->state != 0xFE) {
            if (self->state != 0xFD) {
                func_00300190(&self->pos, &self->pos);
                func_00300248(vars, vars);
                func_002FEE70(vars->effect, vars, 0);
            }
        }
    }
    ref_L00_003C9978_00(func_L00_003CA650, self);
}
