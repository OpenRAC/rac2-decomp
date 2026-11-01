#include "include_asm.h"
#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

extern int func_419CA0(int);

extern char D_00189EA0[];

extern const int D_L23_001B1684 __attribute__((sda));

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *D_L23_001FF300[];

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282E48(void *, void *);

extern void func_L23_003C0F48(char *arg0, int arg1);

extern void func_3242D0(int, int, int);

extern void func_L23_003C1988(char *arg0);

extern int D_L23_001B36B0 __attribute__((sda));

INCLUDE_ASM("asm/levels", func_L23_0035CE90);

/* func_L23_00394218 is defined in L23_00394218.c. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;

extern unsigned char D_00139574;

extern char *D_0018C0B0;

extern int D_L23_001AC790 __attribute__((sda));

extern Collision D_L23_001C0A80;

extern Material D_L23_00266A70[];

extern int func_002761F8(void *, void *, int, void *, void *);

extern int func_00282948(char *);

extern void func_00282CC0(char *, char *, char *);

extern void func_00282D30(void *, void *, float);

extern void func_00282F20(void *, void *, float);

extern void func_00282F70(void *, void *, float);

extern void func_00283028(void *, void *, void *);

extern void func_002AFFD8(void *, void *, int);

extern void func_002FEE50(int);

extern void func_L00_0038DE70(void *, void *, void *);

extern void func_L00_0038E880(void *, void *, void *);

extern void func_L00_0038F3D8(void *);


void func_L23_00394630(char *obj) {
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
    frame.packet.material = (D_00139574 + D_L23_00266A70)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L23_001C0A80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L23_001C0A80;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L23_001AC790 && *(short *)(model + 0xAA) != 0x336)
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
            collision = &D_L23_001C0A80;
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




/* func_L23_003BDA20 is defined in L23_003BDA20-g8.c ($gp, -ffast-math). */

/* func_L23_003BEA00 is defined in L23_003BEA00-g8.c ($gp). */

/* func_L23_003BF9B0 is defined in L23_003BF9B0-g8.c ($gp, and -g for its division padding). */

extern void func_2F7DD0(char *);

extern void func_2F7E00(char *);

void func_L23_003BFE38(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    func_2F7DD0(state + 0x250);
    func_2F7E00(state + 0x254);
    if (*(unsigned short *)(arg0 + 0x96) <= 0xFFFE)
        *(unsigned short *)(arg0 + 0x96) += 1;
}

/* func_L23_003BFE90 is matched in L23_003BFE90.c (built with -frac2-zero-ti-barrier). */

extern void func_323FF0(char *, int, int, int);

void func_L23_003BFFC0(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5) {
    char *state = *(char **)(arg0 + 0x68);

    if (arg4 & 1)
        func_323FF0(arg0, arg1, 0, 4);
    if (arg4 & 2)
        func_323FF0(*(char **)(state + 0x2A0), arg1, 0, 4);
}

extern void func_367150(int);

void func_L23_003C0028(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int none = -1;

    func_L23_003C1988(arg0);
    *(short *)(state + 0x178) = 0;
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x41;
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) &= 0xEFFF;
    *(int *)(*(char **)(state + 0x2A0) + 0x98) = 0;
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    func_3242D0(arg0, 0xD, 4);
    *(int *)(state + 0x25C) = 0;
    if (*(int *)(state + 0x3B4) != none) {
        func_367150(*(int *)(state + 0x3B4));
        *(int *)(state + 0x3B4) = none;
    }
}

/* func_L23_003C00D0 is matched in L23_003C00D0.c (built with -g). */

/* func_L23_003C01F8 is matched in L23_003C01F8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_003C02C8 is defined in L23_003C02C8-g8.c ($gp). */

/* func_L23_003C0A60 is defined in L23_003C0A60-g8.c ($gp). */

/* picks the nearest entry of the objects the index table names, and stores its index */
void func_L23_003C0C78(char *arg0, int arg1) {
    struct {
        TI16 a;
        float b[4];
    } loc;
    char *src = arg0 + 0x10;
    char *state;
    float best;
    int i;

    state = *(char **)(arg0 + 0x68);
    qcopy(&loc.a, src);
    func_00282CF0(loc.b, src, D_00189EA0);
    best = 30000.0f;
    func_00282F20(loc.b, loc.b, 4.0f);
    func_00282CC0((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < D_L23_001B1684; i++) {
        int *obj;
        int k;

        if (arg1 != 0 && func_419CA0(i) == 0)
            continue;
        obj = D_L23_001FF300[D_L23_001B36A8[i]];
        for (k = 0; k < *obj; k++) {
            float d = func_00282E48((char *)obj + 0x10 + k * 0x10, &loc.a);

            if (d < best) {
                best = d;
                func_L23_003C0F48(arg0, i);
                *(short *)(state + 0x2B6) = k;
            }
        }
    }
}

extern int func_419CA0(int);

int func_L23_003C0DF8(int arg0, unsigned long long v, int *arg2, int arg3) {
    int *out = arg2;
    int i = 0;
    int n = 0;

    while (i < 0x40) {
        if (v & 1) {
            if (arg3 == 0 || func_419CA0(i) != 0) {
                *out = i;
                n++;
                out++;
            }
        }
        i++;
        v >>= 1;
    }
    return n;
}

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *D_L23_001FF300[];

extern char D_L23_002595C8[];

extern int func_419070(long long v, char *arg);

int func_L23_003C0E98(int arg0, int index, char *arg) {
    int v;
    int w;
    int n;

    v = D_L23_001B36A8[index];
    if (func_419070(*(long long *)(D_L23_002595C8 + (v << 4)), arg) != 0)
        return 0;
    w = D_L23_001B36A8[index];
    n = *D_L23_001FF300[w] - 1;
    func_419070(*(long long *)(D_L23_002595C8 + (w << 4) + 8), arg);
    return n;
}

void func_L23_003C0F48(char *arg0, int arg1) {
    char *p = *(char **)(arg0 + 0x68);
    short n = *(short *)(p + 0x2BE);
    unsigned short old = *(unsigned short *)(p + 0x2B4);
    int off;
    int r;

    r = (n + 1) % 3;
    off = r * 2;
    *(short *)(p + 0x2BE) = r;
    *(short *)(p + off + 0x2B8) = old;
    *(short *)(p + 0x2B4) = arg1;
}

extern const int D_L23_001B1688 __attribute__((sda));

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *D_L23_001FF300[];

extern char D_L23_002595C8[];

extern char D_00189EA0[];

extern int func_L23_003C0DF8(int arg0, unsigned long long v, int *arg2, int arg3);

extern int func_L23_003C0E98(int arg0, int index, char *arg);

extern void func_L23_003C0F48(char *arg0, int arg1);

extern int func_002A77E0(int);

extern int func_L23_00419CE0(long long);

extern float func_00282E48(void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern float func_00282DB0(void *, void *);

void func_L23_003C0F88(char *arg0, unsigned long long mask, int mode, int check)
{
    char *state = *(char **)(arg0 + 0x68);
    int count = D_L23_001B1688;
    int ids[count];
    int n;
    int id;
    float va[4];
    float vb[4];

    n = func_L23_003C0DF8((int)arg0, mask, ids, check);
    if (n == 0) {
        int d = *(short *)(state + 0x2B2);

        *(short *)(state + 0x2B2) = -d;
        return;
    }
    if (mode == 0) {
        int res;

        id = ids[func_002A77E0(n)];
        res = func_L23_003C0E98((int)arg0, id, (char *)(int)*(short *)(state + 0x2B4));
        *(short *)(state + 0x2B2) = res == 0 ? 1 : -1;
        *(short *)(state + 0x2B6) = res;
        func_L23_003C0F48(arg0, id);
        return;
    } else {
        char *pos[count];
        int res[count];
        long long *bits[count];
        int i;
        int best;

        for (i = 0; i < n; i++) {
            int *q;

            id = ids[i];
            res[i] = func_L23_003C0E98((int)arg0, id, (char *)(int)*(short *)(state + 0x2B4));
            q = D_L23_001FF300[D_L23_001B36A8[id]];
            if (res[i] == 0) {
                pos[i] = (char *)(q + *q * 4);
                bits[i] = (long long *)(D_L23_002595C8 + 8 + (D_L23_001B36A8[id] << 4));
            } else {
                pos[i] = (char *)(q + 4);
                bits[i] = (long long *)(D_L23_002595C8 + (D_L23_001B36A8[id] << 4));
            }
        }
        best = 0;
        switch (mode) {
        case 1: {
            float bestDist = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = func_L23_00419CE0(*bits[j]);
                d = func_00282E48(pos[j], *(void **)(state + 0x320));
                if ((d < bestDist && !blocked) || n == 1) {
                    best = j;
                    bestDist = d;
                }
            }
            break;
        }
        case 3: {
            float bestDot = -30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = func_L23_00419CE0(*bits[j]);
                func_00282CF0(va, D_00189EA0, arg0 + 0x10);
                func_00282CF0(vb, pos[j], arg0 + 0x10);
                d = func_00282DB0(va, vb);
                if ((bestDot < d && !blocked) || n == 1) {
                    best = j;
                    bestDot = d;
                }
            }
            break;
        }
        case 2:
        default: {
            float bestDot = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = func_L23_00419CE0(*bits[j]);
                func_00282CF0(va, D_00189EA0, arg0 + 0x10);
                func_00282CF0(vb, pos[j], arg0 + 0x10);
                d = func_00282DB0(va, vb);
                if ((d < bestDot && !blocked) || n == 1) {
                    best = j;
                    bestDot = d;
                }
            }
            break;
        }
        }
        if (res[best] == 0) {
            id = ids[best];
            *(short *)(state + 0x2B2) = 1;
        } else {
            id = ids[best];
            *(short *)(state + 0x2B2) = -1;
        }
        *(short *)(state + 0x2B6) = res[best];
        func_L23_003C0F48(arg0, id);
    }
}



void func_L23_003C1960(char *arg0) {
    D_L23_001B36B0 = 0;
    func_L23_003C1988(arg0);
}

extern void func_31A108(int);

void func_L23_003C1988(char *arg0) {
    int *p = (int *)(*(int *)(arg0 + 0x68) + 0x328);
    int i;

    for (i = 1; i >= 0; i--) {
        int v = *p;

        if (v != 0) {
            func_31A108(v);
            *p = 0;
        }
        p++;
    }
}

/* func_L23_003C19E0 is defined in L23_0035CE90-g8.c (this unit has no $gp access for it). */

void func_L23_003C1AB0(int arg0) {
    func_3242D0(arg0, 9, 2);
    D_L23_001B36B0 = arg0;
}


/* func_L23_003C1B58 is matched in L23_003C1B58.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_003C1E88 is defined in L23_003C1E88-g8.c. */



INCLUDE_ASM("asm/levels", func_L23_00415988);


void func_L23_00416090(char *arg0) {
    if (*(unsigned short *)(arg0 + 0x96) <= 0xFFFE)
        *(unsigned short *)(arg0 + 0x96) += 1;
}

/* func_L23_004160B0 is matched in L23_004160B0-g8.c (built with -g). */
