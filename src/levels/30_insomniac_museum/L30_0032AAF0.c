#include "common.h"
#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0x138]; float f138, f13C; } InputExtra;

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038E880(void *, void *, void *);
extern void func_L00_0038F3D8(void *);
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
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CC0(char *, char *, char *);


extern char D_00189EA0[];
extern char D_00233A60[];
extern char D_L30_00235560[];

extern void func_00115484(char *, int, int);
extern int func_002ACBC8(char *, int);
extern void func_002A7470(char *, int, int, int);
extern void func_L00_0042A500(int);
extern char D_001A63A8[];
extern char D_001AEC98[];
extern char D_001B9DC0[];
extern char D_0018C0DC[];
extern char D_00295BF0[];
extern int func_2FB3C8(int);
extern void func_3132D8(void *, unsigned int, int, int, int, int, int, int, int, int);
extern void func_316DB8(char *);
extern int func_32C0D0(char *, int);
extern void func_320FD0(char *, int, int);

typedef struct {
    float x;
    float y;
    float z;
    float u;
    float v;
    float w;
} Vec6;

typedef struct {
    unsigned char pad[0x1E0];
    unsigned short mode;
    unsigned char pad2[0x1FB0 - 0x1E2];
    float f1FB0;
    float f1FB4;
    unsigned char pad3[0x22BC - 0x1FB8];
    unsigned char flag;
} D00189E20_View;

extern D00189E20_View D_00189E20;

typedef struct {
    unsigned char pad[0x124];
    float f124;
    float f128;
    float f12C;
    unsigned char pad2[8];
    float f138;
    float f13C;
} D00138180_View;

extern D00138180_View D_00138180;

extern float func_321018(float);

INCLUDE_ASM("asm/levels", func_L30_0032AAF0);


INCLUDE_ASM("asm/levels", func_L30_003557F0);

float func_L30_00382EF0(float a0, float a1, float a2) {
    return a0 * (1.0f - a2) + a1 * a2;
}

typedef struct {
    float x;
    float y;
} L30Pair2f;

/* Clears the 0x1B00-byte block and lays a 24-by-24 grid of two-float cells over the table at
   0x235560: every cell's first float comes from its row index and its second from its column,
   both on a one-sixth step starting at -2. */
void func_L30_00382F10(void) {
    int i;
    int j;

    func_00115484(D_00233A60, 0, 0x1B00);
    for (i = 0; i < 24; i++) {
        L30Pair2f *row = (L30Pair2f *)(D_L30_00235560 + i * 0xC0);

        for (j = 0; j < 24; j++) {
            row[j].x = i * (1.0f / 6.0f) + -2.0f;
            row[j].y = j * (1.0f / 6.0f) + -2.0f;
        }
    }
}

/* func_L30_00382FB8 is defined in L30_00382FB8-g8.c. */

/* func_L30_003830D8 needs the -g8 sibling: it reaches its globals through $gp.
   Its C is in nonmatching/levels/ for now. */


/* func_L30_003831E8 is defined in L30_003831E8-g8.c. */

/* func_L30_00383398 is in L30_00383398-g8.c. */

/* func_L30_00383928 is in L30_00383928-g8.c. */

/* func_L30_003840E0 uses small data in L30_0032AAF0-g8.c. */

void func_L30_003842E0(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        if (*(int *)st == -1) {
            func_316DB8(a0);
        } else {
            func_320FD0(a0, 1, -1);
        }
        break;
    case 1:
        if (func_32C0D0(D_001B9DC0, *(int *)st) != 0) {
            *(unsigned char *)D_0018C0DC = 1;
            func_320FD0(a0, 2, -1);
        }
        break;
    case 2:
        if (func_32C0D0(D_001B9DC0, *(int *)st) != 0) {
            *(unsigned char *)D_0018C0DC = 1;
        } else {
            *(unsigned char *)D_0018C0DC = 0;
            func_320FD0(a0, 1, -1);
        }
        break;
    }
}

/* func_L30_003844C8 is in L30_003844C8-g8.c. */

/* Walks the context's 27-word handle table and adopts the first live one the shared probe
   accepts, stamping its index at +0x144 and the handle at +0x140; -1 when none is live. */
int func_L30_00384768(char *a0) {
    char *q = *(char **)(a0 + 0x68);
    int i;

    for (i = 0; i < 27; i++) {
        int h = *(int *)(q + i * 4);

        if (h != -1 && func_002ACBC8(D_00189EA0, h) != 0) {
            *(int *)(q + 0x140) = *(int *)(q + i * 4);
            *(int *)(q + 0x144) = i;
            return *(int *)(q + i * 4);
        }
    }
    return -1;
}

void func_L30_003847F8(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    Vec6 buf;
    int v;

    D_00189E20.mode = 5;
    D_00189E20.flag = 1;
    buf = *(Vec6 *)D_001AEC98;
    v = func_2FB3C8(*(int *)(D_00295BF0 + *(int *)(st + 0x144) * 4));
    func_3132D8(&buf, 0x80F0F0F0, v, 1, 0, -1, 0, 0, 0, 0);
}


int func_L30_00384980(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    char *g = (char *)D_001A63A8;
    int idx;

    if (*(int *)(g + 0x68) == 0 && *(int *)(g + 0x24) == -1) {
        char *q;

        idx = *(int *)(st + 0x144);
        if (idx != -1) {
            q = st + idx * 4;
            *(int *)(g + 0x24) = (*(int *)(q + 0x70) & 0x3FFF) + 0xBB8;
            *(int *)(g + 0x28) = 0;
            return 1;
        }
    }
    return 0;
}

/* func_L30_00386300 lives in the -g8 sibling: it reaches its globals through $gp. */

void func_L30_0038E7E0(unsigned char *obj) {
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


void func_L30_0038EBF8(char *obj) {
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




void func_L30_003B3E60(float *a0, float *a1, float *a2, float *a3) {
    *a0 = -D_00189E20.f1FB0;
    *a2 = -D_00189E20.f1FB4;
    *a1 = func_321018(D_00138180.f128) - func_321018(D_00138180.f124);
    *a3 = D_00138180.f12C;
    if (*a0 > 1.0f) {
        *a0 = 1.0f;
    } else if (*a0 < -1.0f) {
        *a0 = -1.0f;
    }
    if (*a1 > 1.0f) {
        *a1 = 1.0f;
    } else if (*a1 < -1.0f) {
        *a1 = -1.0f;
    }
}

/* func_L30_003B3F70 uses small data in L30_003B3F70-g8.c. */

/* func_L30_003BE478 uses small data in L30_0032AAF0-g8.c. */

void func_L30_003BE678(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        if (*(unsigned char *)(a0 + 0x43) != 1) {
            func_002A7470(a0, 1, 0, 5);
        }
        *(unsigned char *)(a0 + 0x20) = 2;
    } else {
        if (*(unsigned char *)(a0 + 0x43) != 2) {
            func_002A7470(a0, 2, 0, 5);
        }
        *(unsigned char *)(a0 + 0x20) = 5;
        if (*(int *)(st + 0xC) != -1) {
            func_L00_0042A500(*(int *)(st + 0xC));
        }
    }
}



/* func_L30_003D9E60 is defined in L30_003D9E60-g8.c. */

/* func_L30_003DA040 is matched in its own unit, src/levels/shared/L30_003DA040-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* func_L30_003E1BA0 is defined in L30_003E1BA0-g8.c. */

/* func_L30_003E1E78 uses small data in L30_003E1E78-g8.c. */

/* func_L30_00404608 needs the -g8 sibling too; its C is in nonmatching/levels/. */


/* func_L30_0040AE38 is defined in L30_0040AE38-g8.c. */

extern int D_001A79F0 MACRO_ADDR;

void func_L30_0040B4E0(float *a0, float *a1, float *a2, float *a3, float *a4, float *a5) {
    int mode;

    *a0 = -D_00189E20.f1FB0;
    *a2 = -D_00189E20.f1FB4;
    *a1 = func_321018(D_00138180.f128) - func_321018(D_00138180.f124);
    mode = D_001A79F0;
    if (mode == 8 || mode == 0x10 || mode == 0x15 || mode == 0x1E) {
        *a3 = D_00138180.f12C;
        *a5 = 0.0f;
    } else {
        *a5 = D_00138180.f12C;
        *a3 = 0.0f;
    }
    *a4 = func_321018(D_00138180.f138) - func_321018(D_00138180.f13C);
    if (*a0 > 1.0f) {
        *a0 = 1.0f;
    } else if (*a0 < -1.0f) {
        *a0 = -1.0f;
    }
    if (*a1 > 1.0f) {
        *a1 = 1.0f;
    } else if (*a1 < -1.0f) {
        *a1 = -1.0f;
    }
    if (*a4 > 1.0f) {
        *a4 = 1.0f;
    } else if (*a4 < -1.0f) {
        *a4 = -1.0f;
    }
}

INCLUDE_ASM("asm/levels", func_L30_0040B6B0);

INCLUDE_ASM("asm/levels", func_L30_0040B9D8);

/* func_L30_0040C270 is defined in L30_0040C270-g8.c. */
