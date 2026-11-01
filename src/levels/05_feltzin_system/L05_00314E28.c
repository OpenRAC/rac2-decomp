#include "include_asm.h"
#include "common.h"

extern void func_00282CC0(char *, char *, char *);
extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L05_001AC790 __attribute__((sda));
extern int D_L05_001B2CB0 __attribute__((sda)), D_L05_001B2CB8 __attribute__((sda));
extern Material D_L05_00278A70[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
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
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);
typedef int RibbonWord __attribute__((mode(TI)));
typedef struct { float v[4]; } RibbonVector __attribute__((aligned(16)));
typedef struct {
    RibbonVector position[4];
    unsigned int color[4];
    float uv[8];
    unsigned long primitive, texture, mode, registers;
} RibbonPacket;


/* Quadword copies, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_3065F8(char *block);

extern void func_306630(char *dst, char *src, char *src2);

extern void func_306660(char *dst, char *src, char *src2);

extern void func_3066A0(char *dst, char *src, float value);

extern void func_306AD8(char *dst, char *src, char *object);

extern char *func_328508(int id);

extern char *func_L05_00416D68(char *a0, int a1);

extern int func_332AB8(int kind);

extern float func_332B50(float a, float b);

extern float func_332C18(void);

extern int func_334CB8(char *object, char *state, int value);

extern void func_32AF08(char *object);

extern void func_32E728(char *object, int flag, int *mode, char *out);

extern void func_33B330(char *dst, float a, float b, float c);

extern void func_3719A8(int a0, int a1, char *object, int a3);

extern char *func_379CA0(char *object);

extern void func_379FA0(char *object, int a1, int a2, int a3, float f0, float f1, float f2,
                        float f3, int a8, int a9, int a10);

extern void func_37AEC0(char *object, int flag);

extern void func_L05_00416E08(char *object);

extern int func_379860(char *object);

extern void func_379E60(char *object, int a1, int a2, int a3);

extern void func_332708(char *object, int a1, int a2, int a3);

extern void func_37C160(char *object);

extern void func_37B538(char *object, int a1, int a2, int a3);

extern void func_37B948(char *object, int a1, float a2);

extern int func_37B888(char *object);

extern void func_37B6D0(char *object);

extern void func_3062A0(char *block);

extern int func_307840(char *buf, float value);

extern void func_2FF698(void *fn, char *object);

extern void func_L00_003E4948(void);

extern char D_L05_002681E0[];

/* sda: one absolute `lw` macro load at -G0, as in retail. */
extern char *D_L05_001B251C __attribute__((sda));

extern void func_L05_0041CB68(char *object);

extern char D_00188660[];
extern int func_002E5DA0(int, int, char *, int);
extern void func_L05_00415D70(void);
extern void func_L05_00415DA8(char *obj);
extern void func_L05_00415F18(char *object);
extern void func_L05_00415FD0(char *object);
extern void func_L05_004161B0(char *obj);
extern void func_L00_003BAAD0(void);

/* The fields of the record func_379CA0 returns that func_L05_00415B38 uses; +0x120 is the
   target moby (its position is at +0x10), +0x11C says one is set. */
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;

extern void func_L05_0041CE00(char *object);
extern float func_3067D8(char *a, char *b);
extern void func_L05_004157B0(char *obj);
extern void func_L05_004158B0(char *object);
extern void func_L05_00415958(char *obj);

extern void func_L05_0041CA70(char *obj);

extern int func_2F6C50(char *a0, char *a1, int a2, char *a3, int a4);

extern void func_329960(char *object, int a1, char *out);

extern void func_37AC80(float value);

extern char D_L05_001BFB00[];

extern char D_L05_001B9580[];

extern char D_L05_002659E0[];

extern int D_L05_00221D10[];

extern char *D_L05_001B2614 __attribute__((sda));


extern void func_L00_002FC980(void);
extern void func_002E64A0(char *);
extern void func_L00_00326048(char *, char *, int, int, float);
extern void func_00283AF0(char *, char *);
extern void func_00283958(char *, char *);
extern void func_L01_0031A278(char *, char *, float, float, float);
extern void func_L05_00424990(char *, int, int, int, int, int, int, int, int, int, int, float);
extern int func_002A77E0(int kind);
extern float func_002A78D8(float, float);
extern char *func_L05_00419CC8(char *, char *, char *, int, int, int, int, int, float);

typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap[0xC];
    short count;
    char gap2[0x146];
    char *objects[3];
} Scene05;
extern Scene05 D_L05_001BD3C0;
extern char D_L05_00294A90[];
extern int D_001A79F0 __attribute__((sda));


void func_L05_00314E28(void)
{
    float pos[4] __attribute__((aligned(16)));
    union {
        float matrix[12];
        struct { float dest[4], delta[4]; } vectors;
    } scratch __attribute__((aligned(16)));
    int i;
    char *obj;
    func_L00_002FC980();
    for (i = 0; i < D_L05_001BD3C0.count; i++) {
        char *current = D_L05_001BD3C0.objects[i];
        if (current && *(short *)(current + 0xAA) == 0xE29)
            *(unsigned short *)(current + 0x34) |= 0x800;
        if (*(short *)(current + 0xAA) == 0xD54) func_002E64A0(current);
        if (current && *(short *)(current + 0xAA) == 0xFA0) {
            char *state = *(char **)(current + 0x68);
            if (state) func_L00_00326048(current, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
        }
    }
    if (D_001A79F0 != 5 || D_L05_001BD3C0.mode) return;
    obj = D_L05_001BD3C0.objects[2];
    if (D_L05_001BD3C0.timer == 0x62) {
        func_00283AF0(*(char **)(obj + 0x58) + 0x10, (char *)scratch.matrix);
        func_00283958((char *)scratch.matrix, obj + 0xC0);
        func_L01_0031A278(obj, (char *)pos, 4.0f, 3.0f, 5.0f);
        func_L05_00424990((char *)pos, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
        func_L01_0031A278(obj, (char *)pos, 9.0f, 4.0f, 4.0f);
        func_L05_00424990((char *)pos, 35, 50, 30, 30, 30, 50, 1, 1, 1, 1, 1.0f);
    }
    if ((unsigned int)(D_L05_001BD3C0.timer - 0x29) < 0x72 && !func_002A77E0(4)) {
        float sign = 1.0f;
        float *entry;
        if (func_002A77E0(2)) sign = -1.0f;
        entry = (float *)(D_L05_00294A90 + func_002A77E0(3) * 32);
        func_L01_0031A278(obj, (char *)pos, entry[0], entry[1], entry[2]);
        func_L01_0031A278(obj, (char *)scratch.vectors.dest, entry[4], entry[5], entry[6]);
        scratch.vectors.dest[0] += func_002A78D8(0.5f, 1.5f);
        scratch.vectors.dest[1] += func_002A78D8(0.5f, 1.5f);
        scratch.vectors.dest[2] += func_002A78D8(0.5f, 1.5f);
        func_00282CF0((char *)scratch.vectors.delta, (char *)scratch.vectors.dest, (char *)pos);
        func_00282F20((char *)scratch.vectors.delta, (char *)scratch.vectors.delta, 1.1666667461395264f);
        func_L05_00419CC8(obj, (char *)pos, (char *)scratch.vectors.delta, 0x46BE20, 0x327814, 1, 0, 1, sign);
    }
}


INCLUDE_ASM("asm/levels", func_L05_00367340);

void func_L05_003A3CE0(unsigned char *obj) {
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
    func_L00_0038F178(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L05_00278A70 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L05_001B2CB0, D_L05_001B2CB8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = ((Collision *)D_L05_001BFB00)->point.f[2];
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
            Collision *collision = ((Collision *)D_L05_001BFB00);
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = ((Collision *)D_L05_001BFB00);
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L05_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
        func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
    }
}

void func_L05_003A40F8(char *obj) {
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
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L05_00278A70)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = ((Collision *)D_L05_001BFB00);
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = ((Collision *)D_L05_001BFB00);
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L05_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = ((Collision *)D_L05_001BFB00);
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
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}



INCLUDE_ASM("asm/levels", func_L05_00414F90);

/* Per-frame update. On the first frame it initializes the object; afterwards it points the record
   at moby state+0x260, renews the D_00188660 slot in state+0x270 near that target at random and the
   one in state+0x26C when the object no longer owns it. */
void func_L05_004155A0(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    char *rec, *rec2;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        func_L05_004157B0(object);
        func_3065F8(buf);
        if (*(int *)(state + 0x264) != 0)
            func_379E60(object, 0, 0, 0);
        return;
    }
    r = (Target05 *)func_379CA0(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 32.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
                if (func_3067D8(r->target + 0x10, object + 0x10) < 10.0f) {
                    rec2 = D_00188660 + *(int *)(state + 0x270) * 0x70;
                    if (*(char **)(rec2 + 0x88) != object ||
                        *(unsigned char *)(rec2 + 0x74) == 0) {
                        if (func_332AB8(0x190) == 0)
                            *(int *)(state + 0x270) =
                                func_002E5DA0(0xE, 0, object, 0xFBF);
                    }
                }
            }
            if (r->x104 != 0)
                func_L05_004158B0(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            func_L05_00415958(object);
        }
    }
    rec = D_00188660 + *(int *)(state + 0x26C) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x26C) = func_002E5DA0(0, 6, object, 0xF73);
}

void func_L05_004157B0(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 0x14;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x26C) = -1;
    *(int *)(sub + 0x270) = -1;
    *(float *)(sub + 0x180) = 20.0f;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.02f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

/* Runs the object's pending effect when three guards clear, then marks the run. */
void func_L05_004158B0(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 1)
        func_379FA0(object, 0x60800000, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    *(int *)(s1 + 0x268) = 0x14;
}

/* func_L05_00415958 is defined in L05_00415958-qcopy.c. */

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set,
   clears the owners of the 128 interpolation records; afterwards it creates the two
   func_L05_00416D68 children once, points the record at moby state+0x260, and renews the
   D_00188660 slot in state+0x274 when the object no longer owns it. */
void func_L05_00415B38(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    char *rec;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        func_L05_00415DA8(object);
        func_3065F8(buf);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_379E60(object, (int)func_L05_00415D70, 0, 0);
            base = D_L05_002659E0;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)func_379CA0(object);
    if (r->mode == 0)
        return;
    if (*(int *)(state + 0x26C) == 0 && *(int *)(state + 0x270) == 0) {
        *(int *)(state + 0x26C) = (int)func_L05_00416D68(object, 0);
        *(int *)(state + 0x270) = (int)func_L05_00416D68(object, 1);
        *(float *)(*(int *)(state + 0x26C) + 0x2C) = *(float *)(object + 0x2C);
        *(float *)(*(int *)(state + 0x270) + 0x2C) = *(float *)(object + 0x2C);
    }
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 32.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                func_L05_00415F18(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            func_L05_00415FD0(object);
        }
    }
    rec = D_00188660 + *(int *)(state + 0x274) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x274) = func_002E5DA0(1, 6, object, 0xF76);
    func_L05_004161B0(object);
    func_2FF698(func_L00_003BAAD0, object);
}

/* Clears one int field of each of 128 strided records. */
void func_L05_00415D70(void)
{
    char *base = D_L05_002659E0;
    int *p = (int *)(base + 0x27F0);
    int i = 0x7F;

    do {
        *p = 0;
        p -= 0x14;
        i--;
    } while (i >= 0);
}

void func_L05_00415DA8(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *r;
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    r = func_379CA0(obj);
    *(int *)(r + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x274) = -1;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x268) = 0;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
    if (*(int *)(r + 0x110) == 1) {
        *(int *)(sub + 0x26C) = func_L05_00416D68(obj, 0);
        *(int *)(sub + 0x270) = func_L05_00416D68(obj, 1);
    } else {
        *(int *)(sub + 0x26C) = 0;
        *(int *)(sub + 0x270) = 0;
    }
    *(float *)(obj + 0x2C) = 0.02f;
}

/* Clears one of two state words on the object's sub-record, by mode. */
void func_L05_00415EE8(int object, int mode)
{
    int s = *(int *)(object + 0x68);

    switch (mode) {
    case 0:
        *(int *)(s + 0x26C) = 0;
        break;
    case 1:
        *(int *)(s + 0x270) = 0;
        break;
    }
}

/* Spawns the object's effect after three guards, then runs the follow-up by kind. */
void func_L05_00415F18(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    func_379FA0(object, 0x60408020, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    if (func_332AB8(3) != 0)
        func_3719A8(0, 0, object, 0xF76);
    *(int *)(s1 + 0x268) = 0xF;
}


/* func_L05_004161B0 lives in its own compiler-profile unit. */

/* func_L05_00416468 is defined in L05_00416468-g8.c. */


/* func_L05_00416918 is defined in L05_00416918.c. */

char *func_L05_00416D68(char *a0, int a1)
{
    char *obj = func_328508(0xF81);

    if (obj != 0) {
        char *sub = *(char **)(obj + 0x68);

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        *(unsigned char *)(obj + 0x20) = 0;
        *(char **)(sub + 0x50) = a0;
        *(int *)(sub + 0x54) = a1;
        func_3065F8(sub + 0x30);
        func_3065F8(sub + 0x40);
        func_L05_00416E08(obj);
        func_32AF08(obj);
    }
    return obj;
}

/* Builds the sub-record's three planes and blends them onto the object's transform. */

/* Blends the sub-record into the object's transform once three guards clear. */
void func_L05_00416F80(char *object, char *arg1)
{
    char *sub = *(char **)(object + 0x68);
    char buf[16];
    char buf2[16];
    char *r;
    char *base;
    int value;

    r = func_379CA0(*(char **)(sub + 0x50));
    func_329960(object, 0, buf);
    func_306660(buf2, buf, object + 0x10);
    if (func_2F6C50(arg1, buf, 0, object, 0) == 0)
        return;
    base = D_L05_001BFB00;
    value = *(int *)(base + 0x18);
    if (value == 0)
        return;
    if (value != *(int *)(r + 0x120))
        return;
    func_306630(object + 0x10, buf2, base + 0x20);
    func_37AC80(2.0f);
    {
        char *state = D_L05_001B9580;

        *(float *)(state + 0x160) = 0.05f;
        *(int *)(state + 0x168) = 0x1E;
        *(int *)(state + 0x16C) = 0;
    }
    *(unsigned char *)(object + 0x20) = 4;
}

int func_L05_00417088(char *object)
{
    int r = func_334CB8(object, (char *)0x230000, 0);

    *(unsigned char *)(object + 0xA8) = 0xFF;
    if (r != 0)
        *(unsigned char *)(object + 0x20) = 4;
}

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set, clears
   the owners of the 128 interpolation records; afterwards it points the record at moby state+0x260
   and runs func_L05_0041CE00 unless func_307840 returns -1 for the object's position. */
void func_L05_0041C860(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    Vec buf;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        func_L05_0041CA70(object);
        func_332708(object, 1, 0, 0);
        func_3065F8((char *)&buf);
        *(float *)(object + 0x48) = func_332B50(0.9f, 1.1f);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_379E60(object, 0, 0, 0);
            base = D_L05_002681E0;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)func_379CA0(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_37C160(object);
        func_37B538(object, 0, 0, 0);
        func_37B948(object, one, 64.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                func_L05_0041CB68(object);
            if (func_37B888(object) != 0)
                func_37B6D0(object);
            func_3062A0(state + 0x268);
            qcopy(&buf, object + 0x10);
            buf.f[3] = *(float *)(object + 0xC) * 0.00097656f;
            if (func_307840((char *)&buf, 100.0f) != -1)
                func_L05_0041CE00(object);
        }
    }
    func_2FF698(func_L00_003E4948, object);
}

void func_L05_0041CA70(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x268) = 0;
    *(float *)(sub + 0x180) = 5.0f;
    *(float *)(obj + 0x2C) = 0.08f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

/* func_L05_0041CB68 is defined in L05_004161B0.c (-fno-gcse profile). */

/* func_L05_0041CFE8 is defined in L05_0041CFE8-g8.c. */

/* shared native body of family 5a97ab89858c */
void func_L05_0041D1B0(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}



INCLUDE_ASM("asm/levels", func_L05_0041DF58);

INCLUDE_ASM("asm/levels", func_L05_0041EF00);

/* func_L05_0041FC60 is built with -G8: see L05_00314E28-g8.c. */

/* func_L05_0041FD48 is built with -G8: see L05_00314E28-g8.c. */




/* func_L05_0041FFF8 is built with -G8: see L05_00314E28-g8.c. */
