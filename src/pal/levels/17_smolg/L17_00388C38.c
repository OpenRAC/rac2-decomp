#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision D_L00_001BF200;
extern Material D_L00_00262570[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_PAL_L00_00392250(void *);
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
extern void func_PAL_002C0838(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(void *);
extern void func_002FEE50(int);
extern void func_PAL_L00_00390F48(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* func_PAL_L17_00388C38, the PAL copy of func_L17_00385DE8: the same C, where the sparks' life of
   16 frames becomes 13 and the second spark's spin stays a literal 16. */
/* Read once as a GP macro load in a delay slot and otherwise as lui/lw, as at -G0 in retail. */
extern int D_L17_001A8F00 __attribute__((sda));
typedef struct { char pad[0x30]; int phase, frame; char gap[0x15C]; char *actor; } CutsceneState;
extern CutsceneState D_L17_001BD8C0;
typedef struct EffectMoby {
    char pad0[0x28]; struct EffectMoby *next; char pad1[8]; unsigned short flags;
    char pad2[0x62]; int unknown; char pad3[0xE]; short classId;
} EffectMoby;
extern EffectMoby *D_L17_001B2C28 __attribute__((sda));
extern void func_0029FCC0(void *, int, void *);
typedef struct { char pad0[4]; int state; char pad1[2]; unsigned char opacity, age; } EffectTail;
typedef struct { char pad0[8]; unsigned char color, size; short life; char pad1[0x14]; EffectTail tail; } CutsceneParticle;
/* Each register bank keeps the callee's order (a0-t0: position, spin, axis, colour, count;
   f12-f15: jitter, lo, hi, size); the interleaving gives retail's argument setup order. */
extern CutsceneParticle *func_PAL_002BE9A8(void *, int, float, float, void *, float, unsigned int, float, int);
extern int func_00283CF0(float);

/* Activates the scene's effect mobys during phase 6 and emits paired sparks from the
   scene actor during two frame windows of phases 4 and 5. */
void func_PAL_L17_00388C38(unsigned char *self) {
    Vec velocity, point;
    char *obj;
    CutsceneParticle *first, *second;
    EffectTail *detail;
    int amount, state;

    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L17_001A8F00 != 2)
            break;
        if (D_L17_001BD8C0.phase == 6) {
            EffectMoby *m;
            for (m = D_L17_001B2C28; m; m = m->next) {
                if (m->classId == 0xB88 || m->classId == 0x1249) {
                    m->unknown = 0;
                    m->flags = (m->flags | 0x43) & 0xEFFF;
                }
            }
        }
        state = D_L17_001A8F00;
        if (state != 2)
            break;
        if (D_L17_001BD8C0.phase == 4 && (unsigned)(D_L17_001BD8C0.frame - 301) < 59) {
            obj = D_L17_001BD8C0.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                func_0029FCC0(obj, 0, &point);
                func_00282F20(&velocity, obj + 0xE0, -0.05f);
                amount = func_002A77E0(16);
                if (func_002A77E0(2))
                    amount = -amount;
                first = func_PAL_002BE9A8(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 13;
                    first->size = func_00283CF0(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                second = func_PAL_002BE9A8(&point, 16, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                /* Retail tests the first spark again before writing the second. */
                if (first) {
                    detail = &second->tail;
                    second->size = func_00283CF0(4.0f) + 64;
                    second->life = 13;
                    second->color = func_002A77E0(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
                state = D_L17_001A8F00;
            }
        }
        if (state != 2)
            break;
        if (D_L17_001BD8C0.phase == 5 && D_L17_001BD8C0.frame >= 531) {
            obj = D_L17_001BD8C0.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                func_0029FCC0(obj, 0, &point);
                func_00282F20(&velocity, obj + 0xE0, -0.05f);
                amount = func_002A77E0(16);
                if (func_002A77E0(2))
                    amount = -amount;
                first = func_PAL_002BE9A8(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 13;
                    first->size = func_00283CF0(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                second = func_PAL_002BE9A8(&point, 16, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                if (first) {
                    detail = &second->tail;
                    second->size = func_00283CF0(4.0f) + 64;
                    second->life = 13;
                    second->color = func_002A77E0(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
            }
        }
        break;
    }
}

void func_PAL_L17_00393E08(unsigned char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0044f);
    func_PAL_L00_00392250(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L00_00262570 + D_00139568[12] * sizeof(Material)))->material;
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
            func_002FD1B8(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.030000001f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L00_001BF200.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.060000002f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.060000002f, 0.13000001f);
                lifetime = func_002A7820(90, 120);
                func_PAL_002C0838(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L00_001BF200;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0xF1)
                    goto finish;
                reread = &D_L00_001BF200;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
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
        func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
    }
}


extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_PAL_L00_00391958(void *, void *, void *);
extern void func_PAL_L00_00392500(void *);

void func_PAL_L17_00394220(char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.00044f);
    func_PAL_L00_00392500(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L00_00262570)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L00_001BF200;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0xF2)
                goto finish;
            reread = &D_L00_001BF200;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L00_001BF200;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.040000003f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 17)
            func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
        else
            func_PAL_L00_00391958(obj, &frame.velocity, &frame.normal);
    }
}




INCLUDE_ASM("asm/pal/levels", func_PAL_L17_003A7DB0);



