#include "include_asm.h"
#include "common.h"
extern void *func_002A9640(void *a0, s32 a1, s32 a2);
extern s32 func_002A77E0(s32 a0);
extern s32 func_002E5DA0(s32 a0, s32 a1, char *a2, s32 a3);
extern void func_002AC728(u8 *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern void func_002B0A68(char *a0, s32 a1, f32 *a2, u8 a3, f32 f12, f32 f13, f32 f14,
                        f32 f15);
extern void func_0029F338(char *a0);

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L22_001AC790 __attribute__((sda));
extern int D_L22_001B28B0 __attribute__((sda)), D_L22_001B28B8 __attribute__((sda));
extern char D_L22_002645F0[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
extern void func_00282F70(void *, void *, float);
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
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern struct { char pad[0x18]; char *target; } D_L22_001C00C0;
extern u8 *D_0018C0B0;
extern void func_002A8E20(void *, void *);

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));

extern void func_31FBB8();
extern void func_3300E8();
extern s32 D_L22_0018B6A8 __attribute__((sda));

extern s32 func_2F36F0(s32);
extern void func_2F3720();
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3D60(void *, void *, f32);
extern void func_2F3A80(void *, void *, void *);
extern void func_2F9E20(s32, s32);
extern void func_32F330(s32, s32);
extern void func_3A2988(void *, f32);
extern void func_2F4788(s32, s32, f32);
extern f32 func_2F4AD0(f32, f32);
extern void func_3167E8(s32, s32, s32);
extern void func_362E98(s32, s32, s32);
extern void func_32AE80(s32, s32);

extern void func_L22_003E87B8(s32, s32, s32);
extern void func_L22_003FA1D0(s32, s32, s32);

INCLUDE_ASM("asm/levels", func_L22_00358778);

/* func_L22_00385F40 is in L22_00385F40.c. */

void func_L22_0038FBE0(unsigned char *obj) {
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
        ((Material *)((u32)D_L22_002645F0 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (func_002761F8(&frame.old, position, 0x10, obj, (int)&frame.packet)) {
        if (!func_00278E78() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            func_002FD1B8(D_L22_001B28B0, D_L22_001B28B8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = ((Collision *)&D_L22_001C00C0)->point.f[2];
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
            Collision *collision = ((Collision *)&D_L22_001C00C0);
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = ((Collision *)&D_L22_001C00C0);
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L22_001AC790 && *(short *)(model + 0xAA) != 0x336)
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


void func_L22_0038FFF8(char *obj) {
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
    frame.packet.material = ((Material *)D_L22_002645F0 + D_00139574)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, (int)&frame.packet)) {
        collision = ((Collision *)&D_L22_001C00C0);
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = ((Collision *)&D_L22_001C00C0);
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L22_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = ((Collision *)&D_L22_001C00C0);
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



/* func_L22_003A6620 lives in the -g8 sibling file (it reaches a global through $gp). */



INCLUDE_ASM("asm/levels", func_L22_003D0840);

/* func_L22_003E87B8 is in L22_003E87B8.c. */

void func_L22_003E8830(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    func_L22_003E87B8(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

void func_L22_003FA1D0(s32 arg, s32 unused1, s32 unused2)
{
    char *a0 = (char *)arg;
    char *s1 = func_002A9640(a0, -1, 0);
    char buf[0x10];

    if (s1 == 0)
        return;
    func_002E5DA0(func_002A77E0(3) + 0xC, 0, a0, 0xE0B);
    func_002AC728((u8 *)a0, a0 + 0x10, -1, 2.0f, 13.0f);
    func_002E5CF8(0, 0, a0);
    func_2F3D60(buf, s1 + 0x10, 0.25f);
    func_002B0A68(a0, 3, (f32 *)buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(a0);
}


void func_L22_003FA2A8(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    func_L22_003FA1D0(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}


/* func_L22_0040C888 is in L22_0040C888-g8.c. */

/* func_L22_0040D638 lives in L22_00358778-state-g8.c. */

void func_L22_0040DA80(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    func_2F36F0(s0 + 0x258);
    func_2F3720(s0 + 0x25C);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    if (*(u8 *)(s0 + 0x211) == 0)
        func_3167E8(s1, 7, s0 + 0x210);
    func_2F4788(s0 + 0x220, 2, *(f32 *)(s0 + 0x26C));
    *(f32 *)(s0 + 0x26C) = func_2F4AD0(*(f32 *)(s0 + 0x26C), 0.41597018f);
}


void func_L22_0040DC40(s32 a0, s32 a1, s32 a2, f32 f12) {
    u8 buf[0x10];
    u8 buf2[0x10];
    f32 v = f12;

    func_2F3AB0(buf, (void *)a1, (void *)(a0 + 0x10));
    v = v * 0.016666668f;
    func_2F3D60(buf, buf, v);
    if (a2 != 0) {
        func_2F3A80(buf2, (void *)(a0 + 0x10), buf);
        func_3A2988(buf2, 7.2f);
        func_2F3AB0(buf, buf2, (void *)(a0 + 0x10));
        func_2F3D60(buf, buf, v);
    }
    func_32F330(a0, a1);
    func_3300E8(a0, buf);
}

/* The existing implementation is in L22_0040DD20-rc2.c. */

/* Spawns moby 0xF5D at pos moving along vel: copies both in, sets its colour and life
   from *scale, and builds its three-point trail (vel, vel + offset from the pos's
   reference point, and that again) with zeroed fourth components. */
typedef struct {
    float vel[4];
    int life;
    int f14;
    int f18;
    float scale;
} TrailVars0040DE00;
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 flag20;
    u8 pad21[0xF];
    u8 alpha;
    u8 pad31;
    short colour;
    u8 pad34[0x34];
    TrailVars0040DE00 *vars;
    u8 pad6C[0x54];
    float p0[4];
    float p1[4];
    float p2[4];
} TrailMoby0040DE00;
extern void func_002AFFD8(void *, void *, int);
extern TrailMoby0040DE00 *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

TrailMoby0040DE00 *func_L22_0040DE00(float *pos, float *vel, float *scale)
{
    float ref[4];
    float scaled[4];
    TrailMoby0040DE00 *moby;
    TrailVars0040DE00 *vars;

    func_002AFFD8(pos, ref, 1);
    moby = func_0029EFD0(0xF5D);
    if (moby != 0) {
        vars = moby->vars;
        vars->scale = *scale;
        vars->life = 0x50;
        moby->alpha = 0xFF;
        moby->colour = 0xFF;
        moby->flag20 = 0;
        qcopy(moby->pos, pos);
        qcopy(vars->vel, vel);
        vars->f18 = 0;
        vars->f14 = 0;
        func_00282F20(scaled, vel, 1.0f);
        qcopy(moby->p0, scaled);
        func_00282DD8(moby->p1, moby->p0, ref);
        func_00282F20(moby->p1, moby->p1, 1.0f);
        func_00282DD8(moby->p2, moby->p1, moby->p0);
        moby->p0[3] = moby->p1[3] = moby->p2[3] = 0.0f;
    }
    return moby;
}

extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern void func_0029FCC0(void *, s32, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);

void func_L22_0040DB20(u8 *a0, f32 *a1, f32 f12) {
    f32 vec1[4] __attribute__((aligned(16)));
    f32 vec2[4] __attribute__((aligned(16)));
    f32 scale = f12;

    if (D_L22_001AF314[0] != 0 && *(f32 *)(*(u8 **)(D_L22_001AF314[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    func_0029FCC0(a0, 2, vec1);
    if (scale == 0.0f) {
        scale = D_L22_001B2A98;
    }
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.6666667f);
    func_L22_0040DE00(vec1, vec2, &scale);
    func_0029FCC0(a0, 3, vec1);
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.6666667f);
    func_L22_0040DE00(vec1, vec2, &scale);
}

typedef struct { u8 pad[0x18]; u8 *target; } G1C00C0;
extern G1C00C0 D_001C00C0;
extern u8 *D_0018C0B0;
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282F20(void *, void *, f32);
extern void func_002A8C00(void *, void *, int, void *, f32);
extern void func_002A8E20(void *, void *);
extern void func_L22_0040E2B0(void *, s32, s32);

void func_L22_0040DF28(u8 *a0, u8 *a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    u8 vec[16] __attribute__((aligned(16)));
    u8 ev[0x30] __attribute__((aligned(16)));
    u8 buf[16] __attribute__((aligned(16)));
    u8 *target;

    if (func_002761F8(a1, a0 + 0x10, 0, a0, 0) == 0) {
        return;
    }
    target = D_001C00C0.target;
    if (target == 0) {
        return;
    }
    if (*(s16 *)(target + 0xAA) == 0xEDD || *(s16 *)(target + 0xAA) == 0xE0B) {
        return;
    }
    if (target == D_0018C0B0 && !(*(f32 *)(s0 + 0x1C) < 50.0f)) {
        return;
    }
    if (*(f32 *)(s0 + 0x1C) >= 50.0f) {
        *(f32 *)(s0 + 0x1C) = 50.1f;
    }
    func_00282F20(vec, s0, 1.0f);
    func_002A8C00(ev, a0, 0x8B0003, vec, *(f32 *)(s0 + 0x1C));
    ev[0x18] = 5;
    ev[0x19] = 3;
    *(u16 *)(ev + 0x1A) = *(u16 *)(a0 + 0xAA);
    func_002A8E20(D_001C00C0.target, ev);
    func_L22_0040E2B0(a0 + 0x10, 10, 1);
    if (D_001C00C0.target == 0) {
        qcopy(buf, a0 + 0x10);
        func_L22_0040E2B0(buf, 15, 0);
    }
    a0[0x20] = 2;
}

/* func_L22_0040E098 uses the profile in L22_0040E098-g8.c. */

INCLUDE_ASM("asm/levels", func_L22_0040F1C0);

/* func_L22_004135F8 is in L22_004135F8-g8.c. */

/* func_L22_00413B70 is in L22_00413B70-g8.c. */


