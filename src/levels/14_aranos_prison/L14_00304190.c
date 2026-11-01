#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern unsigned char D_00139574;
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L14_001AC790 __attribute__((sda));
extern int D_L14_001B2D30 __attribute__((sda)), D_L14_001B2D38 __attribute__((sda));
extern Collision D_L14_001BF940;
extern Material D_L14_002686F0[];
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



extern void func_321F58();
extern char *func_328768();
extern void func_328DA8();
extern void func_3322F0();
extern void func_3DECE0();
extern void func_3DF6A0();
extern float func_3E22A8();
extern void func_2F5C38();
extern void func_2F5C68();
extern void func_2F6498();
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_31A618();
extern void func_4209A0();
extern int func_420C68();
extern float func_2F6C80(float a, float b);
extern float func_2F6240(float a);
extern void func_2F5F18(void *dst, void *src, float s);
extern void func_2F5D68(void *dst, void *src, void *mtx);
extern void func_3910E0(char *a0, char *a1, int a2, int a3, int t0, int t1, int t2,
                        float f12, float f13, float f14, float f15, float f16);

extern char D_0018A0E0[];
extern char D_L14_00237B00[];

/* func_L14_00304190 is defined in L14_00304190-zp.c (it clears a stack vector with por, which needs -frac2-zero-ti-por). */

/* func_L14_00304280 lives in the -g8 sibling file (it reaches a global through $gp). */

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L14_00304588;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L14_00304588 *mobs[1];
} MobList_L14_00304588;

extern MobList_L14_00304588 ref_L14_00304588_00;
extern int D_001A79F0 __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_L08_0037E6D8(void);
extern void func_L03_00326458(int);

/* Walks the level's list of mobs like func_L02_00300CE8; when the game state is 0xE and the
   list's word at +0x30 is zero it then runs two more calls, the second with the list's word at +0x194. */
void func_L14_00304588(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < ref_L14_00304588_00.count; i++) {
        Mob_L14_00304588 *mob = ref_L14_00304588_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_002E64A0(mob);
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0)
            func_L00_00326048(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (D_001A79F0 == 0xE && ref_L14_00304588_00.mode == 0) {
        func_L08_0037E6D8();
        func_L03_00326458(*(int *)((char *)&ref_L14_00304588_00 + 0x194));
    }
}

/* func_L14_00328E70 is matched in its own unit, src/levels/14_aranos_prison/L14_00328E70-qcopy.c (-frac2-qcopy). */

void func_L14_00328E90(char *arg0, char *arg1, char *arg2) {
    char buf[16];
    char *s1 = func_328768(arg0);

    if (s1 != 0) {
        func_2F5C68(buf, arg0 + 0x10, arg1);
        func_328DA8(s1, buf, arg2, arg0 + 0xF0);
    }
}

INCLUDE_ASM("asm/levels", func_L14_0035F510);

/* func_L14_00390DF8 is defined in L14_00390DF8-helpers.c. */

INCLUDE_ASM("asm/levels", func_L14_00390EC0);

void func_L14_00390FE8(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);
    char *base = D_L14_00237B00;
    char *base2 = base + 0x400;
    int i;

    for (i = 0; i < 4; i++) {
        func_3910E0(arg0, (char *)(((*(int *)(s0 + 0xDC) + i) << 8) + (unsigned int)base),
                    *(int *)(s0 + 0x38), *(int *)(s0 + 0x40),
                    *(int *)(s0 + 0x60), *(int *)(s0 + 0x44), *(int *)(s0 + 0x64),
                    *(float *)(s0 + 0x50), *(float *)(s0 + 0x70), *(float *)(s0 + 0x54),
                    *(float *)(s0 + 0x74), 0.9f);
        func_3910E0(arg0, (char *)(((*(int *)(s0 + 0xDC) + i) << 8) + (unsigned int)base2),
                    *(int *)(s0 + 0x38), *(int *)(s0 + 0x48),
                    *(int *)(s0 + 0x68), *(int *)(s0 + 0x4C), *(int *)(s0 + 0x6C),
                    *(float *)(s0 + 0x58), *(float *)(s0 + 0x78), *(float *)(s0 + 0x5C),
                    *(float *)(s0 + 0x7C), 0.1f);
    }
}

void func_L14_00391B58(char *arg0, float scale) {
    char buf[16];

    func_00282D30(buf, arg0, scale);
    func_00282CC0(arg0 + 0x30, arg0 + 0x30, buf);
}

void func_L14_00399E28(unsigned char *obj) {
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
        ((Material *)((u32)D_L14_002686F0 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L14_001B2D30, D_L14_001B2D38, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L14_001BF940.point.f[2];
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
            Collision *collision = &D_L14_001BF940;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L14_001BF940;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L14_001AC790 && *(short *)(model + 0xAA) != 0x336)
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


void func_L14_0039A240(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L14_002686F0)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L14_001BF940;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L14_001BF940;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L14_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L14_001BF940;
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



int func_L14_003C9548(char *arg0) {
    return (arg0[0x95] ^ 1) == 0;
}

/* func_L14_003CB258 is defined in L14_003CB258-g8.c (it reads its tuning through $gp). */

/* func_L14_003CB4D8 is defined in L14_003CB4D8-g8.c. */

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern float func_00282C48(float a);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* The twin of func_L14_003DF200 for the group word at +0x64: the same pass over the entities
   of the owner's group (not the states 0xFE and 0xFD, not the class 0xA59, accepted by
   func_L14_003C9548), with the box centred at -2.0 on the first axis: beyond 0.8 of it the
   offset is pulled back to -1.5 or -2.5, beyond 0.8 on the second axis to +-0.5, and the entity
   is handed the corrected world position (func_L14_003C9658). */
void func_L14_003CB608(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int clamped;

    func_00283698(mtx, self + 0xC0);
    for (p = D_L14_001FB060[*(int *)(state + 0x64)];
         (*(int *)(state + 0x64) & 0xFF) != 0xFF && *(int *)(state + 0x64) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[*(int *)(state + 0x64)]);
         p++) {
        e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (*(short *)(e + 0xAA) != 0xA59) {
                    if (func_L14_003C9548((char *)e) != 0) {
                        func_00282CF0(off, e + 0x10, self + 0x10);
                        clamped = 0;
                        func_002AFDD8(self, off, off, mtx);
                        if (func_00282C48(off[0] + 2.0f) > 0.8f) {
                            clamped = 1;
                            if (off[0] > -1.5f)
                                off[0] = -1.5f;
                            else if (off[0] < -2.5f)
                                off[0] = -2.5f;
                        }
                        if (func_00282C48(off[1]) > 0.8f) {
                            clamped = 1;
                            if (off[1] > 0.5f)
                                off[1] = 0.5f;
                            else if (off[1] < -0.5f)
                                off[1] = -0.5f;
                        }
                        if (clamped) {
                            func_00283098(off, off, self + 0xC0);
                            func_00282CC0(off, off, self + 0x10);
                            func_L14_003C9658((char *)e, off);
                        }
                    }
                }
            }
        }
    }
}

/* func_L14_003CB868 is defined in L14_003CB868.c. */

/* func_L14_003D18C8 is defined in L14_003D18C8.c. */


/* func_L14_003DDD38 is defined in L14_00304190-g8.c (it reaches D_L14_001B259C through $gp). */

int func_L14_003DE2D8(char *arg0) {
    int *p = (int *)(*(int *)(arg0 + 0x68) + 0xE0);
    int count = 0;
    int i;

    for (i = 3; i >= 0; i--) {
        if (*p != 0) {
            count++;
        }
        p++;
    }
    return count;
}

extern void func_328340(void *dst, void *src, void *mtx, float f);
extern float func_324F78(float a, float b, float c);

/* The object is placed in the world: the group's two matrices are copied and turned by the
   angle, the object's own matrix is rebuilt from them, and the three floats it keeps are
   cleared. The first call takes the object's own matrix as its second argument, but the
   compiler overwrites it with the local buffer before the call, so the callee sees the
   buffer (as retail does). */
void func_L14_003DE360(char *self, float f) {
    char buf[16];
    char *s0 = *(char **)(self + 0x68);
    char *mB0 = s0 + 0xB0;
    char *mC0 = s0 + 0xC0;
    char *m10 = self + 0x10;
    char *mD0 = self + 0xD0;
    char *mE0 = self + 0xE0;
    float f0;
    float zero;

    func_2F5C68(buf, m10, mB0);
    func_328340(buf, buf, mC0, f);
    f0 = *(float *)(s0 + 0x80) + f;
    *(float *)(s0 + 0x80) = f0;
    func_2F5F18(buf, buf,
                func_324F78(*(float *)(s0 + 0x84), *(float *)(s0 + 0x88), f0 * 0.63661977f));
    func_2F5C38(m10, mB0, buf);
    func_2F5F18(mD0, mC0, 1.0f);
    func_2F5F18(mE0, buf, -1.0f);
    func_2F5D68(self + 0xC0, mE0, mD0);
    zero = 0.0f;
    *(float *)(self + 0xEC) = zero;
    *(float *)(self + 0xDC) = zero;
    *(float *)(self + 0xCC) = zero;
}

void func_L14_003DE488(char *arg0) {
    char **p = (char **)(*(int *)(arg0 + 0x68) + 0xE0);
    int i;

    for (i = 3; i >= 0; i--) {
        char *v = *p;

        if (v != 0 && *(int *)(*(int *)(v + 0x68) + 0x2E0) != 0) {
            func_3322F0(v, 1);
        }
        p++;
    }
}

typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } PrisonLiftVoice;
typedef struct {
    char pad0000[0x80];
    Vec position;               /* 0x80 */
    char pad0090[0x22B4 - 0x90];
    unsigned char mode;         /* 0x22B4 */
} PrisonLiftHero;
extern PrisonLiftHero D_00189E20;
extern char D_00188660[];
extern int func_002B3868(char *self);
extern int func_L00_00324120(char *);
extern int func_002ACBC8(void *, int);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002A7750(void *, int, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);

/* A lift that travels between its start height (0x68) and its target (0x64): state 0 sets it
   up, state 1 waits for the hero (or a trigger) and starts it with its travel sound, states 2
   and 3 ease it up and down and stop the sound on arrival. Riders follow its movement. */
void func_L14_003DE4E8(char *arg0)
{
    Vec pos, rot, delta;
    char *state = *(char **)(arg0 + 0x68);
    int sound;

    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(int *)(state + 0x5C) |= 1;
        {
            float target = *(float *)(state + 0x64);
            float start = *(float *)(arg0 + 0x18);
            *(int *)(state + 0x74) = -1;
            *(float *)(state + 0x7C) = 0.0011666667f;
            *(float *)(state + 0x68) = start;
            *(int *)(state + 0x70) = 0;
            *(float *)(state + 0x80) = (start + target) * 0.5f;
        }
        if (*(int *)(state + 0x60) == 0) *(int *)(state + 0x6C) = 0;
        else *(int *)(state + 0x6C) = 1;
        *(unsigned char *)(arg0 + 0x20) = 1;
        break;
    case 1:
        if (D_00189E20.mode == 1 && *(int *)(state + 0x84)) {
            if (*(int *)(state + 0x6C) == 1) {
                func_002A7750(arg0, 2, -1);
                *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            }
        } else if (func_L00_00324120(arg0)
                   || ((*(float *)(arg0 + 0x18) - *(float *)(state + 0x80)) * (D_00189E20.position.f[2] - *(float *)(state + 0x80)) < 0.0f
                       && *(int *)(state + 0x70))) {
            if (*(int *)(state + 0x6C) == 0) {
                func_002A7750(arg0, 3, -1);
                if (!func_002E59B0(arg0, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            } else {
                func_002A7750(arg0, 2, -1);
                if (!func_002E59B0(arg0, *(int *)(state + 0x74)))
                    *(int *)(state + 0x74) = func_002E5CF8(0, 4, arg0);
            }
        }
        break;
    case 2:
        if (func_002B3868(arg0)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(state + 0x64) - *(float *)(arg0 + 0x18) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(D_00188660 + sound * 0x70);
                if (voice->owner == arg0 && voice->active) func_002E59F8(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state + 0x6C) = 0;
                *(float *)(arg0 + 0x18) = *(float *)(state + 0x64);
                func_002A7750(arg0, 1, -1);
            }
        } else func_002AA548(arg0 + 0x18, state + 0x78, *(float *)(state + 0x64), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.10000001f);
        break;
    case 3:
        if (func_002B3868(arg0)) {
            *(float *)(state + 0x78) = 0.0f;
            (*(int *)(state + 0x70))++;
        }
        if (*(float *)(arg0 + 0x18) - *(float *)(state + 0x68) < 0.03f) {
            sound = *(int *)(state + 0x74);
            if (sound != -1) {
                PrisonLiftVoice *voice = (PrisonLiftVoice *)(D_00188660 + sound * 0x70);
                if (voice->owner == arg0 && voice->active) func_002E59F8(sound);
            }
            *(int *)(state + 0x74) = -1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state + 0x6C) = 1;
                *(float *)(arg0 + 0x18) = *(float *)(state + 0x68);
                func_002A7750(arg0, 1, -1);
            }
        } else {
            int ridden = func_L00_00324120(arg0) != 0;
            int away = func_002ACBC8(&D_00189E20.position, *(int *)(state + 0x88)) == 0;
            if (ridden || away)
                func_002AA548(arg0 + 0x18, state + 0x78, *(float *)(state + 0x68), *(float *)(state + 0x7C), *(float *)(state + 0x7C), 0.10000001f);
        }
        break;
    }
    func_00282CF0(&delta, arg0 + 0x10, &pos);
    func_002AD6F0(state + 0x20, &delta, &rot, arg0 + 0xF0);
}

int func_L14_003DE8E8(unsigned char *arg0) {
    return (unsigned int)(arg0[0x20] - 2) < 2;
}

void func_L14_003DE8F8(char *arg0) {
    *(int *)(*(int *)(arg0 + 0x68) + 0x84) = 1;
}

void func_L14_003DE990(char *arg0) {
    func_321F58(arg0, 2, -1);
}

/* func_L14_003DE9B0 is in its -g8 unit. */

/* func_L14_003DECE0 is defined in L14_003DECE0.c. */

/* func_L14_003DF100 lives in the -g8 sibling file (its calls pass floats, so it needs real prototypes). */

extern float func_00282C48(float a);

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* For every entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, that func_L14_003C9548 accepts: takes its offset from the owner in the owner's frame;
   when that is beyond 1.0 on the first axis or 1.5 on the second it is pulled back to +-0.5 or
   +-1.25, and the entity is handed the corrected world position (func_L14_003C9658). */
void func_L14_003DF200(char *self) {
    float mtx[16];
    float off[4];
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int clamped;

    func_00283698(mtx, self + 0xC0);
    for (p = D_L14_001FB060[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[*(int *)(state + 0x68)]);
         p++) {
        e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (func_L14_003C9548((char *)e) != 0) {
                    func_00282CF0(off, e + 0x10, self + 0x10);
                    clamped = 0;
                    func_002AFDD8(self, off, off, mtx);
                    if (func_00282C48(off[0]) > 1.0f) {
                        clamped = 1;
                        if (off[0] > 0.5f)
                            off[0] = 0.5f;
                        else if (off[0] < -0.5f)
                            off[0] = -0.5f;
                    }
                    if (func_00282C48(off[1]) > 1.5f) {
                        clamped = 1;
                        if (off[1] > 1.25f)
                            off[1] = 1.25f;
                        else if (off[1] < -1.25f)
                            off[1] = -1.25f;
                    }
                    if (clamped) {
                        func_00283098(off, off, self + 0xC0);
                        func_00282CC0(off, off, self + 0x10);
                        func_L14_003C9658((char *)e, off);
                    }
                }
            }
        }
    }
}

/* func_L14_003DF440 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_003DF540 lives in the -g8 sibling file (it reads a count through $gp). */

void func_L14_003DF650(unsigned char *arg0) {
    if (arg0[0x20] == 0) {
        func_3DECE0();
    }
    *(int *)(arg0 + 0x64) = (int)func_3DF6A0;
}

void func_L14_003DF690(char *arg0, int arg1) {
    *(int *)(*(int *)(arg0 + 0x68) + 0x7C) = arg1;
}

/* func_L14_003DF6A0 is defined in L14_003DF6A0-g8.c. */

/* func_L14_003DF7F8 is defined in L14_00304190-g8.c (this unit has no $gp access for it). */

void func_L14_003DFA10(char *arg0, char *arg1) {
    char buf[16];
    char *v = *(char **)(arg0 + 0x68);

    func_2F5C38(buf, arg0 + 0xC0, arg0 + 0x10);
    func_4209A0(*(int *)(v + 0x0), buf, arg1);
}

INCLUDE_ASM("asm/levels", func_L14_003DFA60);

void func_L14_003E1DD0(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);
    unsigned char st = *(unsigned char *)(arg0 + 0x20);

    switch (st) {
    case 0:
        *(float *)(s0 + 0x4) = *(float *)(arg0 + 0x18);
        *(int *)(s0 + 0x8) = 0;
        func_321F58(arg0, 1, -1);
        break;
    case 1:
        *(float *)(arg0 + 0xF8) = func_2F6C80(*(float *)(arg0 + 0xF8), *(float *)(s0 + 0x0));
        *(float *)(s0 + 0x8) = func_2F6C80(*(float *)(s0 + 0x8), *(float *)(s0 + 0xC));
        *(float *)(arg0 + 0x18) = *(float *)(s0 + 0x4)
                                  + *(float *)(s0 + 0x10) * func_2F6240(*(float *)(s0 + 0x8));
        break;
    }
}


/* func_L14_003E1E78 is in its -g8 unit. */

void func_L14_003E2238(char *arg0) {
    float f = func_3E22A8(arg0);

    func_2F6498(arg0 + 0xC0, arg0 + 0xF0);
    func_00282D30(arg0 + 0xC0, arg0 + 0xC0, f);
    func_00282D30(arg0 + 0xD0, arg0 + 0xD0, f);
    func_31A618(arg0);
}

float func_L14_003E22A8(char *arg0) {
    char *v = *(char **)(arg0 + 0x68);
    unsigned int s = *(unsigned char *)(arg0 + 0x20);

    if (s == 4) {
        return (float)*(int *)(v + 0x7C) / (float)*(int *)(v + 0x78);
    }
    if (s == 2) {
        return 1.0f - (float)*(int *)(v + 0x7C) / (float)*(int *)(v + 0x70);
    }
    if (s == 1) {
        return 0.0f;
    }
    return 1.0f;
}

/* func_L14_003E2328 is defined in L14_003E2328-g8.c. */

/* func_L14_003E2688 is defined in L14_00304190-g8.c. */

float func_L14_003E28E8(float arg0) {
    float f = arg0;

    while (6.2831855f < f) {
        f = f - 6.2831855f;
    }
    while (f < 0.0f) {
        f = f + 6.2831855f;
    }
    return f;
}

/* func_L14_003E2980 is defined in L14_00304190-g8.c (it reads its tuning through $gp). */

/* func_L14_003E4208 is defined in L14_003E4208-g.c (it needs -g for retail's line-note nops). */

extern char D_00188660[];
extern int func_332310(char *self);
extern int func_369AD0(int a0, int a1, char *a2);
extern int func_3697D0(int a0);
extern float func_2F6CC8(float a0, float a1);

/* The object steers a group of entities: by its state byte it either leaves the group
   (state 0), asks whether the group is free and hands itself over if it is (state 1) or
   turns (state 2).  In the turning state it takes an entry from the ring of the group's own
   entries (D_00188660, 0x70 bytes each) - a new one when the entry it holds is not its
   own or is free - and turns half a degree; at the end it releases the entry it holds
   when the entry is its own and in use, and forgets it either way. */
void func_L14_003E4A40(char *self) {
    char *state = *(char **)(self + 0x68);
    char *e1;
    char *e2;
    int idx;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        func_321F58(self, 1, -1);
        *(int *)state = -1;
        break;
    case 1:
        if (func_332310(self) != 0) {
            func_321F58(self, 2, -1);
        }
        break;
    case 2:
        if (*(float *)(self + 0xF0) > -1.5707964f) {
            e1 = D_00188660 + *(int *)state * 0x70;
            if (*(int *)(e1 + 0x88) != (int)self || *(unsigned char *)(e1 + 0x74) == 0) {
                *(int *)state = func_369AD0(0, 4, self);
            }
            *(float *)(self + 0xF0) = func_2F6CC8(*(float *)(self + 0xF0), 0.0087266471f);
        }
        idx = *(int *)state;
        if (idx != -1) {
            e2 = D_00188660 + idx * 0x70;
            if (*(int *)(e2 + 0x88) == (int)self && *(unsigned char *)(e2 + 0x74) != 0) {
                func_3697D0(idx);
            }
        }
        *(int *)state = -1;
        break;
    }
}

extern int func_002B3868(char *self);
extern int func_00282978(char *p);
extern void func_L14_003E4EA0(char *self);
extern void func_L14_003E5030(char *self);
extern void func_L14_003E50B8(char *self);
extern void func_L14_003E5190(char *self);
extern void func_L14_003E51B0(char *self);
extern void func_L14_003E5218(char *self);

/* The key state of an object that steers a group (+0x14 the current key, +0x16 the key index,
   +0x34 the key word). The last walk stores through this struct: cc1 then knows the store does
   not touch the two level globals (a store through a cast pointer might), so loop.c moves their
   loads and the constants out of the loop. That walk is spelled like the other two, with the
   second `p != 0`: its test is too long for the first jump pass to copy in front of the loop,
   and after loop.c has hoisted the invariants it is short enough for the second pass, which
   copies it (retail's entry test ahead of the loop, the hoisted values before it). A cast store
   instead leaves nothing to hoist and the walk stays in the `b test` form. */
typedef struct {
    unsigned char pad[0x14];
    unsigned short cur;
    unsigned short index;
} L14Key;

/* Steps the object by its state byte: 0 copies the six halfwords at +0x40 of its state into the
   state of every class-0xB19 entity of its group and calls func_L14_003E5030; 1 and 2 test
   func_002B3868 and call their handlers (the cases are in retail's block order, 0, 2, 1). Then,
   while the key word (+0x34) is set: when func_00282978 has run down the key counter (+0x14)
   the current key is reloaded from the key word and the key index of every class-0xB19 entity
   of the group is cleared; finally the current key is copied into each of them. Two pointers:
   the third walk has its own (one shared variable gives the other loops different registers). */
void func_L14_003E4BA0(unsigned char *self)
{
    unsigned char *state = *(unsigned char **)(self + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *e;

    switch (self[0x20]) {
    case 0:
        for (p = D_L14_001FB060[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self[0x21]]);
             p++) {
            e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xB19) {
                unsigned char *d = *(unsigned char **)(e + 0x68);

                *(unsigned short *)(d + 0x40) = *(unsigned short *)(state + 0x40);
                *(unsigned short *)(d + 0x42) = *(unsigned short *)(state + 0x42);
                *(unsigned short *)(d + 0x44) = *(unsigned short *)(state + 0x44);
                *(unsigned short *)(d + 0x46) = *(unsigned short *)(state + 0x46);
                *(unsigned short *)(d + 0x48) = *(unsigned short *)(state + 0x48);
                *(unsigned short *)(d + 0x4A) = *(unsigned short *)(state + 0x4A);
            }
        }
        func_L14_003E5030((char *)self);
        break;
    case 2:
        if (func_002B3868((char *)self) != 0) {
            func_L14_003E5218((char *)self);
            func_L14_003E5190((char *)self);
        }
        break;
    case 1:
        if (func_002B3868((char *)self) != 0)
            func_L14_003E51B0((char *)self);
        func_L14_003E4EA0((char *)self);
        break;
    }
    if (*(int *)(state + 0x34) != 0) {
        if (func_00282978((char *)(state + 0x14)) != 0) {
            *(unsigned short *)(state + 0x14) = *(unsigned short *)(state + 0x34);
            for (p = D_L14_001FB060[self[0x21]];
                 self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && p != 0 &&
                 ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self[0x21]]);
                 p++) {
                e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(short *)(e + 0xAA) == 0xB19)
                    *(unsigned short *)(*(unsigned char **)(e + 0x68) + 0x16) = 0;
            }
        }
        for (q = D_L14_001FB060[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == D_L14_001FB060[self[0x21]]);
             q++) {
            e = D_L14_001B259C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xB19)
                ((L14Key *)*(unsigned char **)(e + 0x68))->cur = ((L14Key *)state)->cur;
        }
    }
    func_L14_003E50B8((char *)self);
}

/* func_L14_003E4EA0 is matched in L14_003E4EA0-g8.c (built with -g). */

/* func_L14_003E5030 lives in the -g8 sibling file (it reaches a global through $gp). */

void func_L14_003E50B8(char *object)
{
    s16 *ring = *(s16 **)(object + 0x68);
    while (ring[10] < ring[ring[11]]) {
        ring[11] = (ring[11] + 1) % 8;
    }
    if (((u16)ring[11] & 1) == 0) {
        if (*(u8 *)(object + 0x20) != 1)
            func_321F58(object, 1, -1);
    } else {
        if (*(u8 *)(object + 0x20) != 2)
            func_321F58(object, 2, -1);
    }
}

void func_L14_003E5190(char *arg0) {
    char *v0 = *(char **)(arg0 + 0x68);
    v0 = *(char **)(v0 + 0x30);
    if (v0 != 0) {
        v0 = *(char **)(v0 + 0x68);
        *(int *)(v0 + 0x3C) = 0;
    }
}

void func_L14_003E51B0(char *arg0) {
    char *v0 = *(char **)(arg0 + 0x68);
    char *v1 = *(char **)(v0 + 0x30);

    if (v1 != 0) {
        char *v2 = *(char **)(v1 + 0x68);

        *(int *)(v2 + 0x48) = ((unsigned int)*(s16 *)(v0 + 0x44) << 16)
                              | ((unsigned int)*(s16 *)(v0 + 0x42) << 8)
                              | (unsigned int)*(s16 *)(v0 + 0x40);
        *(int *)(v2 + 0x4C) = ((unsigned int)*(s16 *)(v0 + 0x4A) << 16)
                              | ((unsigned int)*(s16 *)(v0 + 0x48) << 8)
                              | (unsigned int)*(s16 *)(v0 + 0x46);
        *(int *)(v2 + 0x3C) = 1;
        *(int *)(v2 + 0x34) = *(int *)(v0 + 0x18);
    }
}

void func_L14_003E5218(char *self) {
    char *p = *(char **)(self + 0x68);
    short index = *(short *)(p + 0x16);
    if ((short)(index % 2) == 1) {
        int a = ((short *)p)[index];
        int b = ((short *)p)[(index + 1) % 8];
        char *obj;
        char *d;
        int green;
        obj = *(char **)(p + 0x28);
        if (obj) {
            d = *(char **)(obj + 0x68);
            *(int *)(d + 0x14) = *(short *)(p + 0x14) - a;
            *(int *)(d + 0x18) = a - b;
            green = (*(short *)(p + 0x42) << 8) | 0x80000000;
            *(int *)(d + 0x30) = *(int *)(d + 0x38) = (*(short *)(p + 0x44) << 16) | green | *(short *)(p + 0x40);
            green = (*(short *)(p + 0x48) << 8) | 0x80000000;
            *(int *)(d + 0x34) = *(int *)(d + 0x3C) = (*(short *)(p + 0x4A) << 16) | green | *(short *)(p + 0x46);
            *(float *)(d + 0xC) = 1.0f;
        }
        obj = *(char **)(p + 0x2C);
        if (obj) {
            d = *(char **)(obj + 0x68);
            *(int *)(d + 0x14) = *(short *)(p + 0x14) - a;
            *(int *)(d + 0x18) = a - b;
            green = (*(short *)(p + 0x42) << 8) | 0x80000000;
            *(int *)(d + 0x30) = *(int *)(d + 0x38) = (*(short *)(p + 0x44) << 16) | green | *(short *)(p + 0x40);
            green = (*(short *)(p + 0x48) << 8) | 0x80000000;
            *(int *)(d + 0x34) = *(int *)(d + 0x3C) = (*(short *)(p + 0x4A) << 16) | green | *(short *)(p + 0x46);
            *(float *)(d + 0xC) = 1.0f;
        }
    }
}

extern void func_L00_002E54E0(float);
extern int func_002B38B8(char *);
extern void func_L00_002E6EF8(void (*f)(char *), char *arg);
extern float func_002A7878(float, float);
extern void func_L14_003F0E68(char *);

void func_L14_003F0D50(char *arg0) {
    char *s2 = arg0;
    char *s1 = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) == 0) {
        *(int *)(s1 + 0x10) = 1;
        func_L00_002E54E0(2048.0f);
        *(unsigned char *)(arg0 + 0x20) = 1;
    }
    *(float *)(s1 + 0x0) = *(float *)(s1 + 0x0) + *(float *)(s1 + 0x4);
    *(float *)(s1 + 0x8) = *(float *)(s1 + 0x8) + *(float *)(s1 + 0xC);
    if (*(float *)(s1 + 0x0) >= 8.0f) {
        *(float *)(s1 + 0x0) = *(float *)(s1 + 0x0) - 8.0f;
    }
    if (*(float *)(s1 + 0x8) >= 8.0f) {
        *(float *)(s1 + 0x8) = *(float *)(s1 + 0x8) - 8.0f;
    }
    if (func_002B38B8(s2) != 0) {
        *(int *)(s1 + 0x10) = 0;
    }
    if (*(int *)(s1 + 0x10) != 0) {
        func_L00_002E6EF8(func_L14_003F0E68, s2);
    }
    *(float *)(s1 + 0x4) = func_002A7878(0.003f, 0.005f);
    *(float *)(s1 + 0xC) = func_002A7878(0.001f, 0.0025f);
}

/* Resets the record: the four axis pairs, the flags and the packed word. */
void func_L14_003F0E98(char *a0)
{
    *(long long *)(a0 + 0x70) = 0LL;
    *(int *)(a0 + 0x50) = 0;
    *(int *)(a0 + 0x54) = 0;
    *(float *)(a0 + 0x58) = 1.0f;
    *(int *)(a0 + 0x5C) = 0;
    *(int *)(a0 + 0x60) = 0;
    *(float *)(a0 + 0x64) = 1.0f;
    *(float *)(a0 + 0x68) = 1.0f;
    *(float *)(a0 + 0x6C) = 1.0f;
    *(float *)(a0 + 0x8) = -4.0f;
    *(float *)(a0 + 0x18) = 4.0f;
    *(float *)(a0 + 0x4) = -2.0f;
    *(float *)(a0 + 0x24) = 2.0f;
    *(int *)(a0 + 0x0) = 0;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x20) = 0;
    *(int *)(a0 + 0x30) = 0;
    *(float *)(a0 + 0xC) = 1.0f;
    *(float *)(a0 + 0x1C) = 1.0f;
    *(float *)(a0 + 0x2C) = 1.0f;
    *(long long *)(a0 + 0x80) = 280993940374112LL;
    *(float *)(a0 + 0x28) = -4.0f;
    *(float *)(a0 + 0x38) = 4.0f;
    *(float *)(a0 + 0x14) = -2.0f;
    *(float *)(a0 + 0x34) = 2.0f;
    *(float *)(a0 + 0x3C) = 1.0f;
}

/* func_L14_003F0F38 lives in the -g8 sibling file (it reaches a global through $gp). */
