#include "common.h"

extern unsigned char D_00139574;
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L17_001AC790 __attribute__((sda));
extern int D_L17_001B33B0 __attribute__((sda)), D_L17_001B33B8 __attribute__((sda));
extern Collision D_L17_001C0000;
extern Material D_L17_00263470[];
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

extern void func_00282CC0(char *, char *, char *);


extern char D_00189E20[];

extern char D_L17_001FE880[];

extern char D_L17_00296F80[];

extern char D_L17_00296FF0[];

extern void func_00283098(void *, void *, void *);

extern void func_2EEEB8(void *, void *, void *);

extern int func_2EEB28(char *);

extern int func_2F00C0(float);

extern float func_2EF4E0(float);

extern float func_00282C48(float);

extern float func_2F00B0(int);

extern void func_332E48(char *);

extern void func_002A7398();

extern void func_L17_003C71B0();

extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00282E80(void *, void *);
extern void func_L02_0032EF10(void *, void *, void *, void *, float);
int func_L17_0032C070(float *origin, float *target, void *out, void *object, float radius, float height)
{
    Vec left, right, farLeft, farRight, start;
    float heading, angle, dleft, dright, finalDistance;
    heading = func_00283248(target[0] - origin[0], target[1] - origin[1]);
    angle = func_00283B98(heading, 1.5707965f);
    left.f[0] = func_00283180(angle) * radius;
    left.f[1] = func_00283198(angle) * radius;
    left.f[2] = 0;
    func_00282CC0((char *)&left, (char *)&left, (char *)origin);
    angle = func_00283BE0(heading, 1.5707965f);
    right.f[0] = func_00283180(angle) * radius;
    right.f[1] = func_00283198(angle) * radius;
    right.f[2] = 0;
    func_00282CC0((char *)&right, (char *)&right, (char *)origin);
    start.q = *(Quad *)origin;
    func_L02_0032EF10(&start, &left, &left, object, height);
    start.q = *(Quad *)origin;
    func_L02_0032EF10(&start, &right, &right, object, height);
    dleft = func_00282E80(origin, &left);
    dright = func_00282E80(origin, &right);
    if (radius < dleft + dright) {
        if (func_002A7878(0, dleft + dright) < dleft) qcopy(out, &left);
        else qcopy(out, &right);
        return 1;
    }
    angle = func_00283B98(heading, 0.78539824f);
    farLeft.f[0] = func_00283180(angle) * 12.0f;
    farLeft.f[1] = func_00283198(angle) * 12.0f;
    farLeft.f[2] = 0;
    func_00282CC0((char *)&farLeft, (char *)&farLeft, (char *)origin);
    angle = func_00283BE0(heading, 0.78539824f);
    farRight.f[0] = func_00283180(angle) * 12.0f;
    farRight.f[1] = func_00283198(angle) * 12.0f;
    farRight.f[2] = 0;
    func_00282CC0((char *)&farRight, (char *)&farRight, (char *)origin);
    start.q = *(Quad *)origin;
    func_L02_0032EF10(&start, &farLeft, &farLeft, object, height);
    start.q = *(Quad *)origin;
    func_L02_0032EF10(&start, &farRight, &farRight, object, height);
    finalDistance = func_00282E80(origin, &farLeft);
    dright = func_00282E80(origin, &farRight);
    if (func_002A7878(0, finalDistance + dright) < finalDistance) qcopy(out, &farLeft);
    else qcopy(out, &farRight);
    return 0;
}




/* divides two sub-object measurements taken through the float accessor, scales the ratio by a fixed
   2*pi-scale constant, folds the result through two helpers and packs a colour byte into the object's
   high word */
void func_L17_00340EA0(char *s1)
{
    float f20;
    float t;
    char *s0;

    if (s1 == 0)
        return;
    s0 = s1 + 0x20;
    if (func_2EEB28(s1 + 0x24) != 0) {
        func_332E48(s1);
        return;
    }
    f20 = func_2F00B0(*(short *)(s0 + 4)) / func_2F00B0(*(short *)(s0 + 6));
    t = func_2EF4E0(f20 * 6.283186f);
    *(int *)(s1 + 4) = (*(int *)(s1 + 4) & 0x00FFFFFF)
                       + (func_2F00C0(func_00282C48(func_2F00B0(*(int *)(s0 + 0xC)) * t)) << 24);
}

INCLUDE_ASM("asm/levels", func_L17_003583F8);

INCLUDE_ASM("asm/levels", func_L17_00385DE8);

void func_L17_00390CE0(unsigned char *obj) {
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
        ((Material *)((u32)D_L17_00263470 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L17_001B33B0, D_L17_001B33B8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L17_001C0000.point.f[2];
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
            Collision *collision = &D_L17_001C0000;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L17_001C0000;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L17_001AC790 && *(short *)(model + 0xAA) != 0x336)
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



void func_L17_003910F8(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L17_00263470)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L17_001C0000;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L17_001C0000;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L17_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L17_001C0000;
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



/* func_L17_003A14A0 is defined in L17_0032C070-burst-g8.c. */

/* func_L17_003A4740 is defined in L17_0032C070-grid.c. */

/* func_L17_003BCBC8 is defined in L17_0032C070-g8.c: the -G8 profile of that
   unit is what makes its register allocation come out right. */

/* func_L17_003BCC30 is defined in L17_0032C070-path.c. */

/* func_L17_003BCEC0 is defined in L17_0032C070-path.c. */

/* func_L17_003BD310 is defined in L17_0032C070-hazard-g8.c. */

/* runs seven two-stage transforms over a record reached from an id in the sub-object; the id -1
   aborts, and the last id is echoed into the shared resident word */
void func_L17_003C3250(char *a2)
{
    char *s5;
    char *s0;
    char *s2;
    char *s4;
    char *s3;
    char *base;
    int v1;
    int i;

    s5 = *(char **)(a2 + 0x68);
    v1 = *(int *)(s5 + 0xD0);
    if (v1 == -1)
        return;
    v1 = *(int *)(D_L17_001FE880 + v1 * 4);
    if (*(int *)v1 != 7)
        return;
    s3 = a2 + 0xC0;
    s4 = a2 + 0x10;
    s2 = D_L17_00296F80;
    s0 = v1 + 0x10;
    for (i = 6; i >= 0; i--) {
        func_00283098(s0, s2, s3);
        s2 += 0x10;
        func_2EEEB8(s0, s0, s4);
        s0 += 0x10;
    }
    base = D_00189E20;
    *(unsigned short *)(base + 0x24FE) = *(unsigned short *)(s5 + 0xD0);
}

/* func_L17_003C3330 is defined in L17_0032C070-lift-g8.c. */





INCLUDE_ASM("asm/levels", func_L17_003C3C50);

/* func_L17_003C4090 is defined in L17_0032C070-motion-g8.c. */

/* func_L17_003C45A0 is defined in L17_0032C070-carrier-g8.c. */



/* raises the state word to 0x920 and runs a three-argument setup, or, when it is already 0x929,
   re-runs the 0x71B0 activation if the object is still unmarked */
void func_L17_003C5AF8(int a0)
{
    if (*(short *)(a0 + 0xAA) == 0x920) {
        if (*(unsigned char *)(a0 + 0x20) == 0) {
            *(unsigned char *)(a0 + 0x20) = 1;
            func_002A7398(a0, 1, 0);
            return;
        }
    }
    if (*(short *)(a0 + 0xAA) == 0x929) {
        if (*(unsigned char *)(a0 + 0x20) == 0)
            func_L17_003C71B0(a0);
    }
}



/* true for the sub-state 0x922 when the object's stage byte sits in the 2..6 window */
int func_L17_003C5DF0(int a0)
{
    if (*(short *)(a0 + 0xAA) != 0x922)
        return 0;
    return *(unsigned char *)(a0 + 0x20) - 2U < 5;
}

/* true when the level's shared record names the given sub-state; the shared word at
   0x34E closes the answer when the record is not the level's own */
int func_L17_003C5E20(int a0)
{
    char *base = D_00189E20;

    if (*(int *)(base + 0x229C) == 3 || *(int *)(base + 0x2294) == 0x1B) {
        if (*(int *)(base + 0x588) != a0)
            goto zero;
        return 1;
    }
    if (*(short *)(base + 0x34E) != 0)
        goto zero;
    if (*(int *)(base + 0x33C) == a0)
        return 1;
zero:
    return 0;
}

/* twin of func_L17_003C3250 on the 0x128 sub-object id and its own table */
void func_L17_003C5E78(char *a2)
{
    char *s5;
    char *s0;
    char *s2;
    char *s4;
    char *s3;
    char *base;
    int v1;
    int i;

    s5 = *(char **)(a2 + 0x68);
    v1 = *(int *)(s5 + 0x128);
    if (v1 == -1)
        return;
    v1 = *(int *)(D_L17_001FE880 + v1 * 4);
    if (*(int *)v1 != 7)
        return;
    s3 = a2 + 0xC0;
    s4 = a2 + 0x10;
    s2 = D_L17_00296FF0;
    s0 = v1 + 0x10;
    for (i = 6; i >= 0; i--) {
        func_00283098(s0, s2, s3);
        s2 += 0x10;
        func_2EEEB8(s0, s0, s4);
        s0 += 0x10;
    }
    base = D_00189E20;
    *(unsigned short *)(base + 0x24FE) = *(unsigned short *)(s5 + 0x128);
}


/* func_L17_003C69A8 is defined in its dedicated-g8.c source. */

/* func_L17_003C6CE8 is defined in its dedicated-g8.c source. */

/* func_L17_003C7018 is defined in L17_0032C070-g8.c (this unit has no $gp access for it). */

/* func_L17_003C71B0 is matched in L17_003C71B0.c (built with -mno-split-addresses). */

/* Stores the second argument in the object's sub-record at 0xA4. */
void func_L17_003C7250(char *a0, int a1)
{
    *(int *)(*(char **)(a0 + 0x68) + 0xA4) = a1;
}



/* func_L17_003C7680 is matched in L17_0032C070-platform-g8.c. */

/* true when the sub-object word at 0xBC holds the value two */
int func_L17_003C7C58(int a0)
{
    return *(int *)(*(int *)(a0 + 0x68) + 0xBC) == 2;
}
