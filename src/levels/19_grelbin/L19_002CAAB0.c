#include "include_asm.h"
#include "common.h"

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern void *D_L19_001AC790 __attribute__((sda));
extern int D_L19_001B31B0 __attribute__((sda)), D_L19_001B31B8 __attribute__((sda));
extern Collision D_L19_001BFE80;
extern Material D_L19_00265870[];
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
extern void *func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CC0(char *, char *, char *);


extern int D_L19_001A8F00 __attribute__((sda));

/* The cutscene record: the group of L19_0042A860.c (entity count at 0x44,
 * entity list at 0x18C) with its state and frame counter at 0x30. */
typedef struct {
    u8 pad0[0x30];
    s32 state;
    s32 frame;
    u8 pad38[0x44 - 0x38];
    s16 count;
    u8 pad46[0x18C - 0x46];
    char *items[1]; /* bounded by count */
} L19Cutscene;
extern L19Cutscene D_L19_001BD740;
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks, mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
/* Separate scalars: only a plain symbol operand is one instruction to cc1, so
 * only these reach the delay slots where retail has their $gp forms. */
extern int D_001A79F0 MACRO_ADDR;
extern char *D_L19_001B2814 MACRO_ADDR;
extern Vec D_L19_001B2820 MACRO_ADDR;
extern float D_L19_001B2830 MACRO_ADDR;
extern float D_L19_001B2834 MACRO_ADDR;
extern float D_L19_001B2838 MACRO_ADDR;
extern float D_L19_001B283C MACRO_ADDR;
extern float D_L19_001B2840 MACRO_ADDR;
extern int D_L19_001B2844 MACRO_ADDR;
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern int func_00283D38(float, int, int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002AF000(float *, float, float, float);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *func_002C7BB8(void *, void *, int, int, int, int, int, float, float, float, int);
extern u8 *func_002BDBC0(void *, void *, int, int, float, int);

void func_L19_002FA1A8(void)
{
    Vec position, direction, axis;
    char *actor;
    int i;
    func_L00_002FC980();
    for (i = 0; i < D_L19_001BD740.count; i++) {
        actor = D_L19_001BD740.items[i];
        if (actor && *(short *)(actor + 0xaa) == 0xe29)
            *(unsigned short *)(actor + 0x34) |= 0x800;
        /* Retail makes this test without a null check: it also reads an
         * empty slot. */
        if (*(short *)(actor + 0xaa) == 0xd54)
            func_002E64A0(actor);
        if (actor && *(short *)(actor + 0xaa) == 4000 && *(char **)(actor + 0x68))
            func_L00_00326048(actor, (float *)(*(char **)(actor + 0x68) + 0xc), 0x80aaaad2, 0x80396464, 0.061086535f);
    }
    if (D_001A79F0 == 19) {
        if (D_L19_001BD740.state == 4) {
            int frame = D_L19_001BD740.frame;
            if (frame == 1) {
                D_L19_001B2814 = D_L19_001BD740.items[3];
                D_L19_001B2830 = 3.5f;
                D_L19_001B2834 = 11.0f;
                D_L19_001B2838 = 10.7f;
                D_L19_001B283C = 0.0f;
                D_L19_001B2840 = 0.0f;
                D_L19_001B2844 = frame;
            }
            D_L19_001B2820.q = *(Quad *)(D_L19_001B2814 + 0x10);
            if (frame == 750) {
                D_L19_001B9900.strength = 1.0f;
                D_L19_001B9900.ticks = 15;
                D_L19_001B9900.mode = 0;
            }
            if (D_L19_001BD740.frame >= 750 && D_L19_001BD740.frame <= 770) {
                D_L19_001B2840 += D_L19_001B2838;
                if (D_L19_001B2840 >= 1.0f) {
                    do {
                        int color;
                        float angle;
                        direction.q = 0;
                        direction.f[0] = 0.72f;
                        direction.f[1] = -0.72f;
                        direction.f[3] = 1.0f;
                        color = ((u32)func_002A7820(96, 128) << 16) | 0x1e00;
                        position.f[0] = 0.0f;
                        position.f[1] = D_L19_001B2830 * func_002A7878(0.9f, 1.1f);
                        position.f[2] = 0.0f;
                        position.f[3] = 1.0f;
                        angle = func_002A7878(0.0f, 6.2831855f);
                        func_002ACEC0(&position, &position, &direction, angle);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        func_00282F20(&direction, &direction, func_002A7878(1.5f, 2.5f));
                        func_00282CC0((char *)&position, (char *)&position, (char *)&direction);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&direction);
                        D_L19_001B2840 -= 1.0f;
                        {
                            int life = func_002A7820(4, 8);
                            float speed = func_002A7878(0.6f, 0.8f) * 210000.0f;
                            func_002C7970(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, 0);
                        }
                        {
                            int life = func_002A7820(4, 8);
                            float speed = func_002A7878(0.6f, 0.8f) * 210000.0f;
                            int style = func_002A7820(1, 7);
                            func_002C7970(&position, D_L19_001A8F20, 24, color, life, 128, 32, speed, 21000.0f, 0.0f, style);
                        }
                    } while (D_L19_001B2840 >= 1.0f);
                }
            }
            if (D_L19_001BD740.frame >= 761 && D_L19_001BD740.frame <= 839) {
                D_L19_001B283C += D_L19_001B2834;
                if (D_L19_001B283C >= 1.0f) {
                    do {
                        int color, life, style;
                        float speed, other, angle;
                        color = func_00283D38(func_002A7878(0.0f, 1.0f), 0x803c14, 0x400000);
                        position.f[0] = 0.0f;
                        position.f[1] = 0.0f;
                        position.f[2] = D_L19_001B2830 * -0.8f;
                        position.f[3] = 1.0f;
                        direction.f[0] = 1.0f;
                        direction.f[1] = 0.0f;
                        direction.f[2] = 0.0f;
                        direction.f[3] = 1.0f;
                        /* Retail never writes axis.f[0] before this rotation. */
                        axis.f[1] = 0.0f;
                        axis.f[2] = 1.0f;
                        axis.f[3] = 1.0f;
                        func_002ACEC0(&direction, &direction, &axis, func_002A7878(0.0f, 6.2831855f));
                        angle = func_002A7878(0.0f, 1.5707964f);
                        func_002ACEC0(&position, &position, &direction, angle);
                        func_00282CC0((char *)&position, (char *)&position, (char *)&D_L19_001B2820);
                        life = func_002A7820(22, 55);
                        style = func_002A7820(0, 10);
                        speed = func_002A7878(0.5f, 1.0f) * 21000.0f;
                        other = func_002A7878(0.7f, 1.0f) * 21000.0f;
                        func_002C7BB8(&position, D_L19_001A8F20, life, color, style, 128, 0, speed, other, 0.0033333334f, 3);
                        D_L19_001B283C -= 1.0f;
                    } while (D_L19_001B283C >= 1.0f);
                }
            }
        }
        if (D_001A79F0 == 19 && D_L19_001BD740.state == 5 && D_L19_001BD740.frame == 1375) {
            char *burstActor = D_L19_001BD740.items[4];
            int n;
            for (n = 0; n < 47; n++) {
                int color, style, life, red, gray, high;
                float speed, angle, pitch, radius;
                radius = func_002A7878(0.0f, 0.37f);
                angle = func_002A7940();
                pitch = func_002A7940();
                func_002AF000(direction.f, radius, angle, pitch);
                func_00282CC0((char *)&direction, (char *)&direction, burstActor + 0x10);
                radius = func_002A7878(0.006166667f, 0.023333333f);
                angle = func_002A7940();
                pitch = func_002A7940();
                func_002AF000(position.f, radius, angle, pitch);
                red = func_002A7820(47, 87);
                gray = func_002A7820(100, 220);
                speed = func_002A7878(70000.0f, 150000.0f);
                /* Built in two steps: as one expression cc1 regroups the four
                 * terms and shares an OR with style, unlike retail. */
                high = (red << 24) | (gray << 16) | (gray << 8);
                color = high | gray;
                style = (gray << 16) | (gray << 8) | gray;
                life = func_002A7820(13, 42);
                func_002BDBC0(&direction, &position, color, style, speed, life);
            }
        }
    }
}

INCLUDE_ASM("asm/levels", func_L19_00380918);

void func_L19_00380A98(char *a0)
{
    if (D_L19_001A8F00 == 2) {
        *(int *)(a0 + 0x98) = 0;
        *(unsigned short *)(a0 + 0x34) = (*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF;
    } else {
        *(unsigned short *)(a0 + 0x34) = (*(unsigned short *)(a0 + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(a0 + 0x98) = *(int *)(*(char **)(a0 + 0x24) + 0x10);
    }
}

void func_L19_0038B580(unsigned char *obj) {
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
        ((Material *)((u32)D_L19_00265870 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L19_001B31B0, D_L19_001B31B8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L19_001BFE80.point.f[2];
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
            Collision *collision = &D_L19_001BFE80;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L19_001BFE80;
                model = reread->hit;
                if (*(void **)(model + 0x64) == D_L19_001AC790 && *(short *)(model + 0xAA) != 0x336)
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


void func_L19_0038B998(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L19_00265870)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L19_001BFE80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L19_001BFE80;
            model = reread->hit;
            if (*(void **)(model + 0x64) == D_L19_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L19_001BFE80;
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


