#include "include_asm.h"
#include "common.h"

typedef u64 TI128 __attribute__((mode(TI)));

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern u8 *D_0018C0B0;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int ref_L08_0039DBE8_00 __attribute__((sda));
extern int ref_L08_0039DBE8_01 __attribute__((sda)), ref_L08_0039DBE8_02 __attribute__((sda));
extern Collision ref_L08_0039DBE8_03;
extern Material ref_L08_0039DBE8_04[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void ref_L08_0039DBE8_06(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void ref_L08_0039DBE8_05(void *, void *, void *);
extern void func_00282CC0(char *, char *, char *);

typedef int Quad_L08_003B2DB0 __attribute__((mode(TI)));

typedef struct {
    float dir[4];                 /* 0x00 */
    float f10;                    /* 0x10 */
    int f14;                      /* 0x14 */
    int owner;                    /* 0x18 */
    short h1C, h1E;               /* 0x1C */
    float f20;                    /* 0x20 */
    int f24, f28;                 /* 0x24 */
} Bolt_L08_003B2DB0;
typedef struct {
    char pad0[0x10];
    float pos[4];                 /* 0x10 */
    char pad20[0x23 - 0x20];
    u8 b23;                       /* 0x23 */
    char pad24[0x2C - 0x24];
    float scale;                  /* 0x2C */
    u8 b30, b31;                  /* 0x30 */
    short h32;                    /* 0x32 */
    u16 h34;                      /* 0x34 */
    char pad36[0x68 - 0x36];
    Bolt_L08_003B2DB0 *state;     /* 0x68 */
    char pad6C[0xF0 - 0x6C];
    int fF0;                      /* 0xF0 */
    float fF4, fF8;               /* 0xF4 */
} Moby_L08_003B2DB0;

extern char D_00189EA0[];
extern Moby_L08_003B2DB0 *func_0029EFD0(int);
extern float func_00282E48(void *, void *);
extern void *func_L04_00358868(void *, float, int, int, int);
extern void func_002A0F48(void *);


extern f32 D_L08_001BE0B0;
extern void func_0027AB40();

extern int r1_D_0015F564_002F2D10 MACRO_ADDR;

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002F2D10)(void *);

extern DrawCallback_r002F2D10 r1_D_0018DC40_002F2D10[];

extern void *r1_D_0018DD40_002F2D10[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
void func_L08_002F2D10(DrawCallback_r002F2D10 fn, void *arg) {
    int count = r1_D_0015F564_002F2D10;
    if (count < 0x40) {
        r1_D_0018DC40_002F2D10[count] = fn;
        r1_D_0018DD40_002F2D10[count] = arg;
        r1_D_0015F564_002F2D10 = count + 1;
    }
}

extern int func_L00_002E9210(u8 *, int, float);
extern u64 func_0027C878(int);
extern void func_0027F640(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L08_00296CD0[];

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_0027F640 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void func_L08_002F5CB8(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_L00_002E9210(text, length, scale) >> 1);
    fy = y;
    texture = func_0027C878(1);
    func_0027F640(fx, fy, color, text, length, scale, texture, D_L08_00296CD0);
}

void func_L08_00300100(void) {
    D_L08_001BE0B0 = 0.62f;
    func_0027AB40();
}

extern void func_00292408();
extern void func_L00_002FE268();
extern void func_002934B8();
extern u8 D_L08_001DB5E7;
extern s32 D_L08_001DAC40[];
extern s32 D_L08_001BFEF4;

void func_L08_0030A8F8(s32 x) {
    func_00292408(x);
    func_L00_002FE268(x);
    func_002934B8(D_L08_001DAC40[D_L08_001DB5E7], D_L08_001BFEF4);
}

f32 func_L08_003277C0(s32 n, f32 x) {
    f32 r;
    if (n < 2)
        return x;
    r = x;
    while (n >= 2) {
        n--;
        r = r * x;
    }
    return r;
}

extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));

/* Counts the 0x100-byte records between the two pointers whose halfword at +0xAA equals A0
   and whose byte at +0x20 is neither 0xFE nor 0xFD. */
s32 func_L08_003289D0(s32 a0) {
    u8 *p = D_L08_001B29DC;
    s32 n = 0;

    for (; p < D_L08_001B29E0; p += 0x100) {
        if (p != 0 && *(s16 *)(p + 0xAA) == a0) {
            if (*(u8 *)(p + 0x20) != 0xFE) {
                if (*(u8 *)(p + 0x20) != 0xFD)
                    n++;
            }
        }
    }
    return n;
}

/* Switches three flags of one record; -1 leaves a group alone, 0 clears it and anything
   else sets it. */
void func_L08_00328AE0(void *a0v, s32 a1, s32 a2, s32 a3) {
    u8 *a0 = a0v;
    u8 kind;

    if (a0 == 0)
        return;
    kind = *(u8 *)(a0 + 0x20);
    if (kind == 0xFE)
        return;
    if (kind == 0xFD)
        return;
    if (a1 != -1) {
        if (a1 != 0)
            *(u16 *)(a0 + 0x34) &= 0xFFFD;
        else
            *(u16 *)(a0 + 0x34) |= 2;
    }
    if (a2 != -1) {
        if (a2 != 0) {
            *(u8 *)(a0 + 0x31) = 1;
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
        } else {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
    }
    if (a3 != -1) {
        if (a3 != 0)
            *(s32 *)(a0 + 0x98) = *(s32 *)(*(s32 *)(a0 + 0x24) + 0x10);
        else
            *(s32 *)(a0 + 0x98) = 0;
    }
}

extern u8 *D_L08_001B29DC __attribute__((sda));
extern void func_L08_00328AE0(void *, s32, s32, s32);

void func_L08_00328B80(s32 a0, s32 a1, s32 a2, s32 a3) {
    if (a0 == -1)
        return;
    func_L08_00328AE0(D_L08_001B29DC + (a0 << 8), a1, a2, a3);
}

/* Runs func_L08_00328B80 on every object named by entry a0 of the 0x1FB660 table: a u16
   list whose low 15 bits select the object and whose high bit ends the walk. The list
   pointer is read under two names (the guard keeps the fresh load, the walk needs a
   callee-saved register across the call). */
extern u32 D_L08_001FB660[];

void func_L08_00328BB0(s32 a0, s32 a1, s32 a2, s32 a3) {
    u16 *q = (u16 *)D_L08_001FB660[a0];

    if (q != 0) {
        u16 *p = q;
        do {
            func_L08_00328B80(p[0] & 0x7FFF, a1, a2, a3);
        } while (*(s16 *)p++ >= 0);
    }
}

extern f32 func_00283248(f32, f32);
extern f32 func_00282E20(void *);

/* Splits a four-float vector: two components give an angle, 0x45AFDF66 marks an
   already-resolved vector. */
void func_L08_0032A4D0(u8 *a0, f32 *a1, f32 *a2, f32 *a3) {
    f32 v[4];

    *(TI128 *)v = *(TI128 *)a0;
    if (v[3] != 5627.9248046875f) {
        *a1 = func_00283248(v[0], v[1]);
        return;
    }
    *a1 = func_00283248(v[0], v[1]);
    *a2 = *a2 * func_00282E20(v);
    v[3] = 0;
    *a3 = *a3 * v[2];
}

extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002AB1F0(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002A7470(void *, int, int, int);
struct LaunchState {
    float direction[4];
    char gap10[8];
    float radius, height;
    char gap20[4];
    unsigned int flags;
    char gap28[4];
    short lifetime;
    char gap2e[14];
    unsigned char active;
    char gap3d;
    short delay;
    float heading;
    int age;
};

void func_L08_0032C0D8(unsigned char *m, struct LaunchState *p, int animation, int flags, int frames, float angle)
{
    int effect;
    int active;
    p->direction[0] = func_00283180(angle) * p->radius;
    p->direction[1] = func_00283198(angle) * p->radius;
    p->direction[2] = p->height;
    p->direction[3] = 1.0f;
    {
        float heading = func_00283B98(angle, 3.141593f);
        short lifetime = 300;
        active = 1;
        p->age = 0;
        p->delay = 0;
        p->heading = heading;
        p->lifetime = lifetime;
        p->active = active;
    }
    effect = func_002AB1F0(m);
    if (effect && *(float *)effect == 0.0f) {
        p->flags |= 0x20;
        *(int *)(m + 0x98) = 0;
    }
    if (p->flags & 2)
        func_002A75E0(m, animation, frames, flags, active);
    else
        func_002A7470(m, animation, frames, flags);
}

s32 func_L08_003391C0(u8 *p, s32 a1, s32 a2, u8 *out, f32 f1, f32 f2) {
    u8 *q;
    if (p == 0)
        return -1;
    q = *(u8 **)(p + 0x24);
    if (q == 0)
        return -1;
    if (*(s32 *)(q + 0x28) == 0)
        return -1;
    *(u32 *)(out + 0x1C) = (u32)p;
    *(f32 *)(out + 0x14) = f2 * 0.016666668f;
    *(f32 *)(out + 0x10) = f1 * 0.016666668f;
    *(TI128 *)out = *(TI128 *)(p + 0x10);
    *(s32 *)(out + 0x18) = a2;
    *(s32 *)(out + 0x20) = a1;
    return 1;
}

INCLUDE_ASM("asm/levels", func_L08_00339220);

extern void func_L01_00324410(s32, s32, void *);

/* The float varargs entry: 2.95.3 spills $a2-$a3, $t0-$t3 (eight bytes each)
   and $f12-$f18; the work is done by the shared worker on that save area. */
void func_L08_0033CD18(s32 a0, s32 a1, ...) {
    func_L01_00324410(a0, a1, (char *)__builtin_next_arg(a1) - 0x30);
}



INCLUDE_ASM("asm/levels", func_L08_00363320);



INCLUDE_ASM("asm/levels", func_L08_00389B68);

void func_L08_0039DBE8(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0030555557f);
    ref_L08_0039DBE8_06(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)ref_L08_0039DBE8_04 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!func_00278E78() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            func_002FD1B8(ref_L08_0039DBE8_01, ref_L08_0039DBE8_02, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = ref_L08_0039DBE8_03.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.050000004f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.050000004f, 0.10833334f);
                lifetime = func_002A7820(90, 120);
                func_002BFB38(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &ref_L08_0039DBE8_03;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &ref_L08_0039DBE8_03;
                model = reread->hit;
                if (*(int *)(model + 0x64) == ref_L08_0039DBE8_00 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        ref_L08_0039DBE8_05(obj, &frame.velocity, &frame.normal);
    }
}


extern unsigned char D_00139574;
extern Material ref_L08_0039E000_00[];
extern Collision ref_L08_0039E000_01;
extern int ref_L08_0039E000_02 __attribute__((sda));
extern void ref_L08_0039E000_03(void *);
extern void ref_L08_0039E000_04(void *, void *, void *);
extern void ref_L08_0039E000_05(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);

void func_L08_0039E000(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    ref_L08_0039E000_03(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + ref_L08_0039E000_00)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &ref_L08_0039E000_01;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &ref_L08_0039E000_01;
            model = reread->hit;
            if (*(int *)(model + 0x64) == ref_L08_0039E000_02 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &ref_L08_0039E000_01;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            ref_L08_0039E000_04(obj, &frame.velocity, &frame.normal);
        else
            ref_L08_0039E000_05(obj, &frame.velocity, &frame.normal);
    }
}



Moby_L08_003B2DB0 *func_L08_003B2DB0(int owner, float *pos, float *dir, int life)
{
    float p[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    Moby_L08_003B2DB0 *moby;
    Bolt_L08_003B2DB0 *state;
    int n;
    float *pp = p;
    float *dd = d;

    *(Quad_L08_003B2DB0 *)p = *(Quad_L08_003B2DB0 *)pos;
    *(Quad_L08_003B2DB0 *)d = *(Quad_L08_003B2DB0 *)dir;
    moby = func_0029EFD0(0x4EA);
    if (moby) {
        state = moby->state;
        state->owner = owner;
        moby->fF0 = 0;
        moby->scale *= 4.0f;
        moby->b30 = 0xFF;
        moby->h32 = 0xFF;
        moby->b31 = 1;
        moby->fF4 = -func_00283248(func_00282E20(dd), dd[2]);
        moby->fF8 = func_00283248(d[0], dd[1]);
        qcopy(moby->pos, pp);
        qcopy(state->dir, dd);
        state->f10 = func_002A7878(-0.02617994323372841f, 0.02617994323372841f);
        state->f14 = 0;
        state->h1C = life;
        state->h1E = life;
        state->f20 = func_00282E48(moby->pos, D_00189EA0);
        state->f24 = 0;
        state->f28 = 0;
        n = life * 5 / 4;
        moby->h34 |= 0x200;
        moby->b23 = 0x40;
        func_L04_00358868(moby, 400000.0f, 0x2F7F4F4F, n, -1);
        func_L04_00358868(moby, 160000.0f, 0x4F7F7F7F, n, -1);
        func_002A0F48(moby);
    }
    return moby;
}

INCLUDE_ASM("asm/levels", func_L08_003B2F70);

INCLUDE_ASM("asm/levels", func_L08_003C5940);

/* Defined in L08_003C63F0-g8.c. */


extern void func_0029FCC0(void *, int, void *);
extern void *func_L08_003D4600(void *, void *);
extern float func_00283CE0(int);

/* Keeps a child object at points 7 and 8 of obj: spawns a missing one,
 * otherwise moves it there and copies the parent's orientation. */
void func_L08_003C66F0(char *obj) {
    float p[4] __attribute__((aligned(16)));
    char **slot = (char **)(*(char **)(obj + 0x68) + 0x80);
    char *child = 0;
    int i;
    for (i = 0; i < 2; ++i, ++slot) {
        func_0029FCC0(obj, i + 7, p);
        if (*slot == 0) {
            *slot = func_L08_003D4600(obj, p);
        } else {
            child = *slot;
            qcopy(child + 0x10, p);
            *(float *)(child + 0xF8) = *(float *)(obj + 0xF8);
            *(float *)(child + 0xF4) = *(float *)(obj + 0xF4);
            *(float *)(child + 0xF0) = func_00283CE0(i) * 3.1415927410125732f;
        }
    }
}

INCLUDE_ASM("asm/levels", func_L08_003C67B8);

INCLUDE_ASM("asm/levels", func_L08_003C6AB0);


/* func_L08_003CD488 lives in the -g8 sibling file (it reads the level's scalars
   through $gp). */

extern u8 *D_0018C0B0;
extern void func_002A0F48();

/* func_L08_003CD600 and func_L08_003CD6C8 are matched in L08_003CD600-qcopy.c. */

/* Defined in L08_003CD648.c. */


INCLUDE_ASM("asm/levels", func_L08_003CD708);

INCLUDE_ASM("asm/levels", func_L08_003CDB78);

INCLUDE_ASM("asm/levels", func_L08_003CDF98);
