#include "common.h"


extern unsigned char D_00139574;
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
extern int D_L03_001AC7D0 __attribute__((sda));
extern int D_L03_001B31B0 __attribute__((sda)), D_L03_001B31B8 __attribute__((sda));
extern Collision D_L03_001BFDC0;
extern Material D_L03_00266DA0[];
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
extern int func_002A77E0(int);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);


/* func_L03_002CCB70 is in the sibling file L03_002CCB70-decider.c (its own profile). */


extern char D_00189E20_8[];
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_L00_0031EC88(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_L00_002D3EA8(void *);
extern float func_L00_002D3B00(void *);
extern int func_002A88A0(float *, float *, float, float, float);
extern char D_L03_001BFE00[];

extern char D_L03_001BFDE0[];
typedef int MotionQuad __attribute__((mode(TI)));

/* The level's runtime block: its mode word and timer, and a counted list of objects. */
typedef struct {
    u8 pad00[0x30];
    u32 mode;
    s32 timer;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} EndakoState;

extern EndakoState D_L03_001BD680;
extern s32 D_001A79F0 __attribute__((sda));
extern f32 D_L03_001A9420 SDATA(D_L03_001A9420);
extern s32 D_L03_001A9424 SDATA(D_L03_001A9424);
/* Four rows of three quadwords, filled from twelve joints of one object. */
extern Quad D_L03_001C64A0[][3];
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, u32, u32, f32);
extern void func_L03_00326458(void *);
extern void func_0029FCC0(void *, s32, void *);

/* Solve the forward collision time for each of the resident movement modes. */
float func_L03_002D3498(float time, float acceleration, float height)
{
    float end[4], direction[4], curve[4], start[4];
    float root0a, root0b, root1a, root1b, root2a, root2b;
    float speed, position;
    char *state = D_00189E20_8;
    switch (*(unsigned char *)(state + 0x22C3)) {
    case 0: {
        float half;
        if (height < 0.0f) {
            char *pos = state + 0x80;
            FastVecScale(end, state + 0xF0, time);
            end[2] -= (time * time + time) * (acceleration * 0.5f);
            FastVecAdd(end, end, pos);
            *(MotionQuad *)direction = *(MotionQuad *)(state + 0x80);
            func_L00_0031EC88(direction, end);
            qcopy(direction, pos);
            if (CollLine(direction, end, 0xD22, 0, 0)) {
                if (func_L00_002D3EA8(D_L03_001BFE00) <= 0.8726647f)
                    height = *(float *)(D_L03_001BFE00 - 0x18);
            }
        }
        if (height > 0.0f) {
            char *root = D_00189E20_8;
            half = acceleration * -0.5f;
            if (func_002A88A0(&root0a, &root0b, half,
                    *(float *)(root + 0xF8) - half,
                    *(float *)(root + 0x88) - height) > 0
                    && root0a > 0.0f)
                return root0a;
        }
        break;
    } case 1: {
        float half;
        char *velocity;
        char *pos;
        qcopy(direction, state + 0x2A0);
        velocity = state + 0xF0;
        vec_scale_to_length(direction, direction, acceleration);
        pos = state + 0x80;
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        func_L00_0031EC88(start, end);
        if (CollLine(pos, end, 0xD22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = func_L00_002D3B00(velocity) - half;
            position = func_L00_002D3B00(pos);
            position -= func_L00_002D3B00(D_L03_001BFDE0);
            if (func_002A88A0(&root1a, &root1b, half, speed, position) > 0
                    && root1a > 0.0f)
                return root1a;
        }
        break;
    } case 2: {
        float half;
        char *velocity = state + 0xF0;
        char *pos = state + 0x80;
        curve[2] = 100.0f;
        curve[1] = 100.0f;
        curve[0] = 100.0f;
        FastVecSub(direction, pos, curve);
        vec_scale_to_length(direction, direction, acceleration);
        FastVecScale(direction, direction, -1.0f);
        FastVecScale(end, velocity, time);
        FastVecScale(curve, direction, (time * time + time) * (acceleration * 0.5f));
        FastVecAdd(end, curve, end);
        FastVecAdd(end, pos, end);
        *(MotionQuad *)start = *(MotionQuad *)(pos);
        func_L00_0031EC88(start, end);
        if (CollLine(pos, end, 0xD22, 0, 0)) {
            half = acceleration * -0.5f;
            speed = func_L00_002D3B00(velocity) - half;
            position = func_L00_002D3B00(pos);
            position -= func_L00_002D3B00(D_L03_001BFDE0);
            if (func_002A88A0(&root2a, &root2b, half, speed, position) > 0
                    && root2a > 0.0f)
                return root2a;
        }
        break;
    } }
    return time;
}


void func_L03_002FDE30(void)
{
    EndakoState *state;
    u8 *object;
    s32 i;
    Quad a, b;

    func_L00_002FC980();
    for (i = 0; i < D_L03_001BD680.count; i++) {
        object = D_L03_001BD680.objects[i];
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xE29)
            *(u16 *)(object + 0x34) |= 0x800;
        if (*(s16 *)(object + 0xAA) == 0xD54)
            UpdateEquipmentPieces(object);
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xFA0) {
            u8 *vars = *(u8 **)(object + 0x68);
            if (vars != 0)
                func_L00_00326048(object, vars + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
        }
    }
    if (D_001A79F0 != 3)
        return;
    state = &D_L03_001BD680;
    if (state->mode < 3) {
        u8 *p = state->objects[1];
        *(f32 *)(p + 0x2C) = *(f32 *)(*(u8 **)(p + 0x24) + 0x24) * D_L03_001A9420;
    }
    if (state->mode == 6)
        EmitScaledObjectParticles(state->objects[1]);
    if (state->mode == 8)
        EmitScaledObjectParticles(state->objects[3]);
    if (state->mode == 7 && state->timer == 0x424) {
        u8 *target;
        s32 row, col, k;

        D_L03_001A9424 = state->timer;
        target = state->objects[2];
        for (row = 0; row < 4; row++)
            for (col = 0; col < 3; col++)
                func_0029FCC0(target, row * 3 + col, &D_L03_001C64A0[row][col]);
        for (k = 0; k < 4; k++) {
            Quad (*rows)[3] = D_L03_001C64A0;
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][1]);
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][2]);
        }
    }
}

extern u8 *D_L03_001B2918;

s32 func_L03_003112F8(void)
{
    u8 *p = D_L03_001B2918;
    u8 *q;
    s32 n = 0;

    if (p == 0)
        return 1;
    q = p;
    while (*(s16 *)q != 0) {
        if (*(s16 *)(q + 0x24) == 1) {
            if ((*(u16 *)(q + 0x10) & 2) == 0)
                n++;
        }
        q += 0x28;
    }
    return n;
}


extern void *func_L00_0032C638(char *a0);
extern float func_00283248(float a, float b);
extern float func_00283B98(float a, float b);
extern int func_00282978(short *p);
extern int func_002A7820(int a0, int a1);
/* The callee's parameters are listed in the order the retail code sets the
   registers up in: int, int, float, int, float, float. */
extern int func_L02_00331440(char *a0, char *a1, float f12, char *a2, float f13, float f14);

/* Aim the record at the shape the caller found. */
int func_L03_0032CFD8(char *self, float *target, char *third, float amount, float f13, float f14)
{
    char *data = (char *)func_L00_0032C638(self);
    float angle;

    if (data == 0)
        return 8;
    angle = func_00283248(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = func_002A7820(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return func_L02_00331440(self, target, angle, third, f13, f14);
}

/* func_L03_00383FE8 is in its -G8 sibling unit. */


/* func_L03_003844D8 is in its -G8 sibling unit. */


void func_L03_00393838(unsigned char *obj) {
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
    FastVecAdd(position, ctx, position);
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
        ((Material *)((u32)D_L03_00266DA0 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, (int)&frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L03_001B31B0, D_L03_001B31B8, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L03_001BFDC0.point.f[2];
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
            Collision *collision = &D_L03_001BFDC0;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L03_001BFDC0;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L03_001AC7D0 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
    }
}


void func_L03_00393C50(char *obj) {
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
    FastVecAdd(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L03_00266DA0)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L03_001BFDC0;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L03_001BFDC0;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L03_001AC7D0 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L03_001BFDC0;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
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
