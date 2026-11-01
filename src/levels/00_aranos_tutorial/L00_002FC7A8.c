#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;

typedef struct {
    char pad00[0x24];
    float f24;
} AranosModel;

/* Context of the child objects spawned by func_L00_003CFB00. */
typedef struct {
    char pad00[4];
    float f04;
    char pad08[0x48];
    int f50;
} AranosChildCtx;

/* The generic object these functions work on: position at 0x10, state at 0x20, context at 0x68. */
typedef struct AranosMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[2];
    unsigned char f23;
    AranosModel *model;
    char pad28[4];
    float f2C;
    char pad30;
    unsigned char f31;
    char pad32[2];
    unsigned short flags;
    char pad36[0x2E];
    void (*hook)(void *);
    void *ctx;
    char pad6C[0x10];
    unsigned short f7C;
    char pad7E[0x1A];
    int f98;
    char pad9C[0xC];
    unsigned char fA8;
    char padA9;
    short classId;
    char padAC[0x14];
    char matrix[0x30];
    Vec rotation;
} AranosMoby;

extern float D_L00_001B19CC __attribute__((sda));
extern float D_L00_001B19D0 __attribute__((sda));
extern void *func_002A9640(void *, unsigned int, int);
extern int func_002B3868(void *);
extern void func_002A7750(void *, int, int);
extern void func_002833F0(void *, void *);
extern void func_002A7A00(void *, float, float);
extern int func_002A99A0(void *, int, void *, int, float);
extern int func_002E5DA0(int, int, void *, int);
extern char *func_L00_00326620(void *, int, int);
extern AranosMoby *func_00273730(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_L00_0039B288(void *);
extern void func_002A0488(void *, unsigned char, unsigned char, unsigned char);

extern char D_00189EA0[];
extern int func_002ACBC8(char *, unsigned int);
extern void func_0029F338(void *);
extern void func_002E5CF8(int, int, void *);

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);

typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision D_L00_001BF200;
extern Material D_L00_00262570[];
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
extern int func_00282948(void *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern unsigned char *D_L00_001FEA00[];
typedef int TI128 __attribute__((mode(TI)));

/* Per-spark data after the common header: velocity, fade rate and colour. */
typedef struct {
    Vec velocity;
    float duration;
    int rgb;
    int color;
    unsigned short step;
} AranosSparkTail;

/* A spark particle object. */
typedef struct {
    char pad00;
    unsigned char f01;
    unsigned char f02;
    unsigned char f03;
    int rgb;
    unsigned char f08;
    unsigned char f09;
    unsigned short frames;
    float f0C;
    Vec position;
    AranosSparkTail tail;
} AranosSpark;

/* Allocates a spark at the given position and velocity; the last arguments set its life, step and colour. */
void *func_L00_00338E90(TI128 *position, TI128 *velocity, int frames, int step, int color, float scale) {
    AranosSpark *obj;
    AranosSparkTail *cursor;

    obj = func_002B9030(0x30);
    if (obj != 0) {
        qcopy_nc(&obj->position, position);
        cursor = &obj->tail;
        obj->rgb = color & 0x00FFFFFF;
        obj->f09 = func_00283CF0(2.0f) + 0x10;
        obj->f03 = 0x44;
        obj->f01 = 0;
        obj->f02 = D_L00_001FEA00[0][0];
        obj->f0C = scale * 210000.0f;
        obj->f08 = func_002A77E0(0x100);
        qcopy_nc(cursor, velocity);
        cursor->duration = 2.0f / func_00283CE0(frames);
        obj->frames = frames;
        cursor->step = step;
        cursor->rgb = color & 0x00FFFFFF;
        cursor->color = color;
    }
    return obj;
}


extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_00283CE0(int);
extern int func_00283D38(char *, char *, float);
extern int func_00282978(char *);
extern void func_002B9180(void *);

void func_L00_00338FB8(char *obj) {
    char *tail = obj + 0x20;
    obj[8] += tail[0x1C];
    func_00282CC0(obj + 0x10, obj + 0x10, tail);
    *(int *)(obj + 4) = func_00283D38(*(char **)(tail + 0x18), *(char **)(tail + 0x14),
        func_00282C48(func_00283CE0(*(short *)(obj + 0x0A)) * *(float *)(tail + 0x10) - 1.0f));
    if (func_00282978(obj + 0x0A) != 0) {
        func_002B9180(obj);
    }
}


extern unsigned int D_001A7AF0 __attribute__((sda));
extern void func_002E76C0(void *, int, int);
extern void func_002ED4B8(void);

void func_L00_003618D8(void *obj) {
    int count;
    int i;
    count = 1;
    if (((D_001A7AF0 >> 4) & 1) != 0) count = 3;
    i = 0;
    while (i < count) {
        func_002E76C0(obj, i, 1);
        i++;
    }
    func_002ED4B8();
}



/* AranosMoby.matrix as the three rows it holds. */
typedef struct { char pad[0xC0]; float matrix[3][4]; } AranosMatrixView;

extern AranosMoby *D_L00_00220DA0[];
extern int D_L00_001A8F00 __attribute__((sda));
extern void func_0029FC20(void *, int, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002A10E8(void *);

/* Moves every attached object of the null-terminated list onto obj, taking its orientation. */
void func_L00_00383958(AranosMoby *obj) {
    Vec position, rotation;
    float matrix[4][4];
    Vec transformed, offset;
    int i = 0, j;
    Vec *source;

    if (D_L00_00220DA0[0]) {
        do {
            D_L00_00220DA0[i]->flags &= 0xFFBE;
            D_L00_00220DA0[i]->flags |= 0x1000;
            D_L00_00220DA0[i]->f98 = *(int *)((char *)D_L00_00220DA0[i]->model + 0x10);
            /* Retail stores these two saves and never reads them back. */
            qcopy_nc(&position, &D_L00_00220DA0[i]->position);
            qcopy_nc(&rotation, &D_L00_00220DA0[i]->rotation);
            /* A statement of its own: the longer life lets loop hoist it on its first pass. */
            source = &obj->position;
            qcopy(&D_L00_00220DA0[i]->position, source);
            func_0029FC20(obj, 0, matrix);
            for (j = 0; j < 3; j++) {
                float *row = matrix[j];
                ((AranosMatrixView *)D_L00_00220DA0[i])->matrix[j][0] = row[0];
                ((AranosMatrixView *)D_L00_00220DA0[i])->matrix[j][1] = row[1];
                ((AranosMatrixView *)D_L00_00220DA0[i])->matrix[j][2] = row[2];
            }
            if (D_L00_001A8F00 == 2) {
                offset.q = 0;
                offset.f[0] = -4.1919f;
                offset.f[2] = -1.355f;
                func_0029FCC0(obj, 1, &transformed);
                func_00283098(&offset, &offset, D_L00_00220DA0[i]->matrix);
                func_00282CC0(&transformed, &transformed, &offset);
                qcopy(&D_L00_00220DA0[i]->position, &transformed);
            }
            func_002AB6D8(D_L00_00220DA0[i]->matrix, &D_L00_00220DA0[i]->rotation);
            func_002A10E8(D_L00_00220DA0[i]);
            if (D_L00_001A8F00 != 0) {
                D_L00_00220DA0[i]->f98 = 0;
            } else if (obj->f98) {
                D_L00_00220DA0[i]->f98 = *(int *)((char *)D_L00_00220DA0[i]->model + 0x10);
            }
            i++;
        } while (D_L00_00220DA0[i]);
    }
}

void func_L00_0038D750(unsigned char *obj) {
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
            *(float *)(ctx + 8) = -0.025000002f;
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
            Collision *collision = &D_L00_001BF200;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L00_001BF200;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336)
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

void func_L00_0038DB68(char *obj) {
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
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
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
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L00_001BF200;
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


/* The level's copy of func_003173B0 (src/game/003173B0.c): same instructions, its own path table. */
extern float func_00283B98(float angle, float step);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern int func_00317D78(char *);
extern int func_002B3890(char *);
extern int func_002B1C20(char *, char *);
extern void func_002E59F8(int);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_002A677C(void *);
extern int func_002B4FF0(void *, void *, float);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_00318200(char *);
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *D_L00_001FDA80[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");
void func_L00_003B9CD8(char *self)
{
    char *d = FP(self,0x68);
    int flags, n, i;
    char *sound, *path;
    float target[4], delta[4];
    float f, height, savedHeight;
    /* Written out here and at the end of state 3, not shared through a label: cross-jumping
       merges the two after sched1, which has to see func_0029F338 in the same block as the
       explosion's calls for it to set a3..t3 up before a0..a2. */
    if (func_00317D78(self)) {
        func_0029F338(self);
        return;
    }
    switch (FB(self,0x95)) {
    case 0:
        if (func_002B3890(self))
            func_002B60B0(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(d,0x258)==1 && func_00282948(d+0x2A4) && FI(d,0x2AC)) {
            if (FI(d,0x294)==-1) {
                func_002A7750(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_002A7470(self,2,0,5);
            } else func_002A7750(self,4,2);
        } else if (FH(d,0x276)) {
            func_002A7750(self,3,1);
            FH(d,0x276)=0;
            if (FH(d,0x270)<300) FH(d,0x270)=func_002A7820(480,600);
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 1:
        if (func_002B3890(self))
            func_002B60B0(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if ((FI(d,0x258)==1 || FI(d,0x25C)==1) && FI(d,0x2AC)) {
            if (FI(d,0x294)!=-1) func_002A7750(self,4,2);
            else {
                func_002A7750(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_002A7470(self,2,0,5);
            }
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 2:
        if (func_002B3890(self))
            func_002B60B0(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(d,0x258)!=1 && FI(d,0x25C)!=1 && FB(self,0x20)!=4) {
            func_002A7750(self,1,1);
            if (FB(self,0x43)) func_002A7470(self,0,0,20);
            FH(d,0x270)=func_002A7820(580,600);
        }
        break;
    case 3:
        flags=func_002B1C20(self,d+0x60);
        if (flags&1) {
            n=FI(d,0x2A8);
            if (n!=-1) {
                sound=(char *)D_00188660+n*0x70;
                if (FP(sound,0x88)==self && FB(sound,0x74)) func_002E59F8(n);
            }
            FI(d,0x2A8)=-1;
            func_0032C700(self+0x10,0,0,0,0,20,45,1,0.3f,20.0f,1,0,0,0);
            func_002E5CF8(0,0,self);
            func_002A6C58(self,0,3);
            func_0029F338(self);
            return;
        }
        if (flags&2) {
            if (FI(d,0x258)==1 || FI(d,0x25C)==1) {
                func_002A7750(self,5,2);
                if (FB(self,0x43)) func_002A7470(self,0,0,5);
                if (FI(d,0x294)!=-1) func_002A7750(self,4,2);
            } else {
                func_002A7750(self,3,1);
                FH(d,0x270)=func_002A7820(580,600);
            }
        }
        break;
    }
    switch (FB(self,0x20)) {
    case 1:
        if (FU(self,0x96)>=26) {
            if (FB(self,0x43)) func_002A7470(self,0,0,5);
            func_002A7750(self,2,-1);
            FF(self,0x18)=FF(d,0x28C);
        } else {
            f=func_00283198((float)FU(self,0x96)*0.12566361f)*0.02f;
            if (FF(self,0x18)>FF(d,0x28C)) FF(self,0x18)-=f;
            else FF(self,0x18)+=f;
        }
        break;
    case 4:
        path=D_L00_001FDA80[FI(d,0x294)];
        if (FI(d,0x298)>=FI(path,0)) {
            FI(d,0x294)=-1;
            FF(d,0x28C)=func_002A89A8(self+0x10,0,0.5f)+0.5f;
            func_002A7750(self,5,-1);
        } else {
            qcopy(target,path+0x10+FI(d,0x298)*16);
            func_00282CF0(delta,target,self+0x10);
            func_00282F20(delta,delta,FF(d,0x1C0));
            func_00282CC0(self+0x10,self+0x10,delta);
            if (func_00282E80(self+0x10,target)<0.5f) FI(d,0x298)++;
            if (FI(d,0x298)>=FI(path,0)-6 && FF(d,0x1C0)>=0.10000001f)
                FF(d,0x1C0)-=0.0022222223f;
            height=func_002A89A8(self+0x10,0,0.5f)+0.5f;
            if (FF(self,0x18)<height) FF(self,0x18)=height;
            FF(d,0x28C)=FF(self,0x18);
            func_002A677C(self);
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 5:
        savedHeight=FF(self,0x18);
        func_002B4FF0(self,d+0x230,FF(d,0x290));
        FF(self,0x18)=savedHeight;
        if (func_00282E80(self+0x10,FP(d,0x240)+0x10)<1.3f) func_002A7750(self,7,-1);
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 6:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)!=3) func_002A7470(self,3,0,5);
            changeMode3173Six(self,8,-1);
        }
        break;
    case 8:
        height=1.75f;
        FF(self,0x48)=height;
        for (i=0;i<4;i++) func_002A8D70(self,i,0.17f,FF(d,0x2B0),1,1.0f,0,1,0);
        if (((Hero3173 *)D_00189E20)->target==self) func_002A7750(self,9,-1);
        if (func_00282E80(self+0x10,FP(d,0x240)+0x10)>1.3f && (float)FU(self,0x96)>120.0f) {
            if (FB(self,0x43)) func_002A7470(self,0,0,15);
            func_002A7750(self,5,-1);
            FF(self,0x48)=1.0f;
        }
        break;
    case 9:
        if ((float)FU(self,0x96)>20.0f) {
            func_002A7750(self,10,-1);
            if (FB(self,0x43)!=4) func_002A7470(self,4,0,5);
            FF(self,0x48)=1.0f;
        }
        break;
    case 10:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)) func_002A7470(self,0,0,15);
            func_002A7750(self,5,-1);
        }
        break;
    case 7:
        if (FU(self,0x96)>=30) {
            func_002A7750(self,6,-1);
            if (FB(self,0x43)!=1) func_002A7470(self,1,0,2);
            FF(self,0x48)=1.0f;
        }
        break;
    }
    if (FB(self,0x20)!=4 && FB(self,0x95)==2 && FF(self,0x18)<FF(d,0x28C)) FF(self,0x18)=FF(d,0x28C);
    func_00318200(self);
}
#undef FI
#undef FF
#undef FH
#undef FU
#undef FB
#undef FP


/* func_L00_003CD160 is defined in L00_003CD160.c. */

/* func_L00_003CD8E0 is defined in L00_003CD8E0-lift-g8.c. */

/* func_L00_003CE278 is defined in L00_003CE278-update.c. */


/* Context of func_L00_003CF530's object: the flag that starts it and a frame counter. */
typedef struct {
    unsigned int flag;
    int frames;
} AranosDriftCtx;

/* Once its flag is set, drifts the object along its heading for 100 frames, then removes it. */
void func_L00_003CF530(AranosMoby *obj) {
    AranosDriftCtx *ctx;
    int result;
    float angle;
    float point[3];

    ctx = obj->ctx;
    if (obj->state == 0) {
        result = func_002ACBC8(D_00189EA0, ctx->flag);
        if (result != 0) {
            obj->state = 1;
            ctx->frames = 0;
            func_002E5CF8(0, 0, obj);
        }
    }
    if (obj->state != 1)
        return;
    angle = obj->rotation.f[2];
    point[0] = func_00283180(angle) * 0.4166667f;
    angle = obj->rotation.f[2];
    point[1] = func_00283198(angle) * 0.4166667f;
    point[2] = 0.0f;
    func_00282CC0(&obj->position, &obj->position, point);
    ctx->frames += 1;
    if (ctx->frames < 0x65)
        return;
    func_0029F338(obj);
}


/* func_L00_003CF610 is defined in L00_003CF610-update.c. */

extern float func_002A78D8(float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);

void func_L00_003CF9B0(char *obj) {
    char *ctx;
    float limit;
    ctx = *(char **)(obj + 0x68);
    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(ctx + 8) = func_002A78D8(5.0f, 15.0f);
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(ctx + 0x0C) = func_002A7820(0x3C, 0x78);
        limit = *(float *)(ctx + 8) * 0.017453294f;
        if (*(float *)(obj + 0xF0) < limit) {
            func_002E5CF8(0, 0, obj);
        } else {
            func_002E5CF8(1, 0, obj);
        }
    }
    if (*(unsigned char *)(obj + 0x20) != 1) return;
    limit = *(float *)(ctx + 8) * 0.017453294f;
    func_002AA3A8((float *)(obj + 0xF0), (float *)ctx, limit,
        0.0008726647356525064f, 0.0008726647356525064f, 0.004363324f);
    func_002833F0(obj + 0xC0, obj + 0xF0);
    if (func_00282948(ctx + 0x0C) != 0) {
        *(unsigned char *)(obj + 0x20) = 0;
    } else if (*(float *)(obj + 0xF0) == *(float *)(ctx + 8) * 0.017453294f) {
        *(unsigned char *)(obj + 0x20) = 0;
    }
}

/* Context of func_L00_003CFB00's object: the sparks it spawned and their decay rates. */
typedef struct {
    AranosMoby *sparks[16];
    float decay[16];
    int hold;
    int timer;
} AranosSparkerCtx;

/* Spawns a burst of sparks around the object, then fades them until the timer runs out. */
void func_L00_003CFB00(AranosMoby *obj) {
    struct {
        Vec velocity, offset, position;
    } frame;
    AranosSparkerCtx *ctx = obj->ctx;
    AranosMoby *child;
    AranosChildCtx *childctx;
    int type, i;
    float life;

    switch (obj->state) {
    case 0:
        for (i = 15; i >= 0; i--)
            ctx->sparks[i] = 0;
        if (obj->classId == 0xAC9) {
            obj->rotation.f[1] += 0.78539824f;
            func_002833F0(obj->matrix, &obj->rotation);
        }
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002A9640(obj, 0x10000, 0) && ctx->hold == 0)
            func_002A7750(obj, 2, -1);
        obj->fA8 = 0xFF;
        return;
    case 2: {
        unsigned char alpha;
        int count = 5, n;

        if (D_L00_001B19CC < 0.85f && D_L00_001B19D0 < 0.85f)
            count = 14;
        for (n = 0; n < count; n++) {
            func_002A7A00(&frame.offset, 0.85f, 1.95f);
            func_002A99A0(obj, 1, &frame.position, 0xFFFF, 1000.0f);
            func_00282CC0(&frame.offset, &frame.offset, &frame.position);
            frame.velocity.f[2] = func_002A7878(0.0f, 5.0f) * 0.016666668f;
            frame.velocity.f[1] = func_002A7878(-6.0f, 6.0f) * 0.016666668f;
            if (func_002A77E0(4)) {
                type = 1;
                ctx->decay[n] = func_002A7878(20.0f, 40.0f) * 0.00027777778f;
                frame.velocity.f[0] = func_002A7878(-8.0f, -4.0f) * 0.016666668f;
                life = func_002A7878(5.0f, 10.0f);
            } else {
                type = 2;
                ctx->decay[n] = 0.0f;
                frame.velocity.f[0] = func_002A7878(2.0f, 4.0f) * 0.016666668f;
                life = func_002A7878(15.0f, 20.0f);
            }
            child = func_00273730(obj, type, 0x43E, func_002A77E0(4), &frame.offset, &obj->rotation, &frame.velocity,
                                  0xFF, 180.0f, life);
            ctx->sparks[n] = child;
            if (child) {
                child->hook = func_L00_0039B288;
                life = func_002A7878(0.75f, 5.0f);
                ctx->sparks[n]->f2C = ctx->sparks[n]->model->f24 * life;
                childctx = ctx->sparks[n]->ctx;
                alpha = 0x80;
                func_002A0488(ctx->sparks[n], 0x20, 0x60, alpha);
                ctx->sparks[n]->f23 = alpha;
                childctx->f50 = 0x1806020;
            }
        }
        func_002E5DA0(func_002A7820(0, 1), 0, obj, 0xC0A);
        switch (obj->classId) {
        case 0xC0A:
            func_L00_00326620(obj, 0xC10, 0);
            break;
        case 0xC0B:
            func_L00_00326620(obj, 0xC11, 0);
            break;
        case 0xC0C:
            func_L00_00326620(obj, 0xC12, 0);
            break;
        case 0xC0D:
            func_L00_00326620(obj, 0xC13, 0);
            break;
        case 0xE01:
            obj->f7C = 0x8001;
            break;
        case 0xE02:
            obj->f7C = 0x8001;
            break;
        case 0xAC9:
            obj->f7C = 0x8001;
            break;
        }
        func_002A7750(obj, 3, -1);
        break;
    }
    case 3:
        if (func_002B3868(obj)) {
            if (!(obj->f7C & 0x8000)) {
                obj->f31 = 0;
                obj->flags |= 1;
            }
            obj->f98 = 0;
            ctx->timer = 300;
        }
        if (!func_00282948(&ctx->timer)) {
            for (i = 0; i < 16; i++) {
                if (ctx->sparks[i])
                    ((AranosChildCtx *)ctx->sparks[i]->ctx)->f04 -= ctx->decay[i];
            }
        } else if (!(obj->f7C & 0x8000)) {
            func_0029F338(obj);
        }
        return;
    default:
        return;
    }
}


/* func_L00_003D0008 is in L00_002FC7A8-lift.c. */

/* func_L00_003D0910 is in L00_002FC7A8-exhaust-g8.c. */
