#include "include_asm.h"

struct RouteNode {
    int path;
    unsigned char neighbors[4];
    unsigned char portals[4];
    unsigned short flags;
    unsigned char unused[18];
};
extern char *D_L02_001FF1C0[];
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern int func_L02_0032EDD8(void *, struct RouteNode *, int, int *);
extern float func_L02_0032EC98(void *, void *, void *, float, float);


/* func_L02_002DCEA0 is matched in its own unit, src/levels/shared/L02_002DCEA0.c (-g). */


/* func_L02_002EF968 is defined in L02_002EF968-helpers.c. */

INCLUDE_ASM("asm/levels", func_L02_002EFB60);


ASM_FUNC("asm/levels", func_L02_002F1FB8);

ASM_FUNC("asm/levels", func_L02_002F21C0);

float func_L02_0031E918(float scale)
{
  float r = ((float) (0xFFF & (func_001163B0() >> 16))) * (1.0f / 4096.0f);
  float new_var;
  new_var = r * r;
  new_var = 1.0f - new_var;
  return new_var * scale;
}


extern float func_L02_0031E918(float scale);
extern float func_002A7940(void);
extern float func_00283180(float x);
extern float func_00283198(float x);
extern void func_00282C88(void *target);

void func_L02_0031E9E8(float *arg0, float arg1) {
    float a = func_002A7940();
    float b = func_L02_0031E918(arg1);

    func_00282C88(arg0);
    arg0[0] = func_00283180(a) * b;
    arg0[1] = func_00283198(a) * b;
}

extern unsigned int D_L02_001FC060[];
extern char *D_L02_001B359C __attribute__((section(".sdata")));
extern void func_L00_003294F0(unsigned char *entity, int enabled);

/* Walk the 16-bit stream the table entry points at; a negative word ends it. */
void func_L02_0031F858(int arg0, int arg1) {
    short *p;

    if (D_L02_001FC060[arg0] != 0) {
        p = (short *)D_L02_001FC060[arg0];
        do {
            func_L00_003294F0((unsigned char *)(D_L02_001B359C + ((*(unsigned short *)p & 0x7FFF) << 8)), arg1);
        } while (*p++ >= 0);
    }
}


extern void func_002A04B8(char *object, int *out0, int *out4, int *out8);

/* Pack the three words the callee fills in behind a marker bit. */
int func_L02_003272D8(char *arg0) {
    int w0;
    int w4;
    int w8;
    int v;

    func_002A04B8(arg0, &w0, &w4, &w8);
    v = (w4 << 8) | 0x80000000;
    return (w8 << 16) | v | w0;
}

extern char *D_L02_001B368C __attribute__((section(".sdata")));
extern void func_L02_00327390(char *arg0, char *arg1, int arg2);

/* Index -1 means "no record". */
void func_L02_00327350(int arg0, int arg1) {
    char *base;

    if (arg0 != -1) {
        base = D_L02_001B368C + (arg0 << 7);
        func_L02_00327390(base + 0x30, base + 0x70, arg1);
    }
}

extern unsigned char D_0018C0D4;
extern void func_L00_002B9D60(int a0, int a1, int a2, int a3);
extern void func_L00_0042A500(int arg0);

void func_L02_00327390(char *arg0, char *arg1, int arg2) {
    int kind = 0;

    switch (D_0018C0D4) {
    case 1:
        kind = 0x3F;
        break;
    case 2:
        kind = 0x56;
        break;
    }
    func_L00_002B9D60((int)arg0, (int)arg1, kind, 1);
    if (arg2 != -1)
        func_L00_0042A500(arg2);
}

/* func_L02_00329410 is matched in its own unit, L02_00329410.c. */

extern void func_00282C88(void *target);
extern void func_00283098(float *out, const float *a, const float *b);

void func_L02_003294D8(char *arg0, float *arg1, float arg2) {
    float *p = arg1;
    char *q = arg0;

    func_00282C88(p);
    *p = arg2;
    func_00283098(p, p, (const float *)(q + 0xC0));
}

typedef int TI128 __attribute__((mode(TI)));

extern float func_002B04E0(char *arg0, float *arg1, char *transform);
extern float func_00282C48(float t);

/* Copy the incoming 16-byte record to a local, hand both to the two calls. */
float func_L02_00329C48(char *arg0, TI128 *arg1, char *transform) {
    TI128 buf = *arg1;

    return func_00282C48(func_002B04E0(arg0, (float *)&buf, transform));
}

/* func_L02_0032B468 is defined in L02_0032B468.c. */

extern int func_L02_0032E3B0(void *a0, float *a1, int a2);

/* The shared lookup takes the record index as a third argument; the retail wrapper hands it
   only two, so the call goes through a two-parameter prototype. */
void func_L02_0032E390(void *a0, void *a1) {
    ((int (*)(void *, void *))func_L02_0032E3B0)(a0, (char *)a1 + 0x10);
}

extern void func_00283410(float *matrix, float *quat);
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(float *out, const float *a, const float *b);
extern float func_00283248(float a, float b);

int func_L02_0032E3B0(void *object, float *target, int index) {
    float quat[4];
    float vec[4];
    float mat[16];
    float best;
    int count;
    short *p;
    char *entity;

    if (index == -1) {
        index = (int)(unsigned char)*(char *)((char *)object + 0x21);
        if (index == -1)
            return 0;
    }
    best = 0.0f;
    count = 0;
    func_00282C88(quat);
    quat[2] = func_00283248(target[0] - *(float *)((char *)object + 0x10),
                                   target[1] - *(float *)((char *)object + 0x14));
    func_00283410(mat, quat);
    func_00283698(mat, mat);
    p = (short *)D_L02_001FC060[index];
    do {
        entity = D_L02_001B359C + ((*(unsigned short *)p & 0x7FFF) << 8);
        if (entity[0x20] >= 0 && entity != (char *)object) {
            func_00282CF0(vec, (float *)(entity + 0x10), (float *)((char *)object + 0x10));
            func_00283098(vec, vec, mat);
            if (best < vec[1])
                count--;
            else
                count++;
        }
    } while (*p++ >= 0);
    return count;
}

INCLUDE_ASM("asm/levels", func_L02_0032E508);

int func_L02_0032E998(float *position, float *target, float *heading, struct RouteNode *nodes, int count, int *sourceNode, int *targetNode, float override, float margin) {
    unsigned char visited[256];
    int i, j, found, portal, step, routeDepth;
    int layer;
    char *path;
    float angle;
    *heading = func_00283248(target[0] - position[0], target[1] - position[1]);
    if (override != 0.0f)
        *heading = func_00283B98(override, *heading);
    if (!func_L02_0032EDD8(position, nodes, count, sourceNode))
        return 0;
    if (!func_L02_0032EDD8(target, nodes, count, targetNode))
        return 0;
    if (nodes[*targetNode].flags & 1)
        return 0;
    if (*sourceNode == *targetNode)
        return 1;
    {
        int clear;
        for (clear = 0; clear < count; clear++)
            visited[clear] = 0;
    }
    found = -1;
    portal = -1;
    visited[*targetNode] = 1;
    for (layer = 1; layer < 50; layer++) {
        for (i = 0; i < count; i++) {
            if (visited[i] == layer) {
                for (j = 0; j < 4; j++) {
                    unsigned int neighbor = nodes[i].neighbors[j];
                    if (!(neighbor & 0x80) && !visited[neighbor] && ((nodes[neighbor].flags ^ 1) & 1)) {
                        visited[neighbor] = layer + 1;
                        if (neighbor == *sourceNode) {
                            portal = nodes[i].portals[j];
                            found = i;
                        }
                    }
                }
            }
            if (found != -1)
                break;
        }
        if (found != -1)
            break;
    }
    if (found == -1)
        return 0;
    path = D_L02_001FF1C0[nodes[found].path];
    angle = *heading;
    routeDepth = visited[found];
    if (routeDepth >= 3) {
        int edge;
        step = routeDepth - 1;
        for (edge = 0; edge < 4; edge++) {
            if (visited[nodes[found].neighbors[edge]] == step) {
                int offset = nodes[found].portals[edge] * 16;
                angle = func_L02_0032EC98(path + (offset + 0x10), path + (offset + 0x20), position, angle, margin);
                break;
            }
        }
    }
    *heading = func_L02_0032EC98(path + (portal * 16 + 0x10), path + (portal * 16 + 0x20), position, angle, margin);
    return 1;
}

INCLUDE_ASM("asm/levels", func_L02_0032EC98);

INCLUDE_ASM("asm/levels", func_L02_0032EDD8);

/* func_L02_0032EF10 is defined in L02_0032EF10-helpers.c. */


extern void *func_L00_0032C638(char *a0);
extern int func_002B50E0(void *a0, void *a1, float f12);

/* Set the record's fields for the call, then put the old ones back. */
int func_L02_00331440(void *a0, void *a1, int a2, float f12, float f13, float f14) {
    char *rec;
    int old38;
    float old28;
    float old20;
    int ret;

    rec = (char *)func_L00_0032C638((char *)a0);
    if (rec == 0)
        return 8;
    old38 = *(int *)(rec + 0x38);
    old28 = *(float *)(rec + 0x28);
    *(int *)(rec + 0x38) = a2;
    if (0.0f < f13)
        *(float *)(rec + 0x28) = f13;
    old20 = *(float *)(rec + 0x20);
    if (0.0f < f14)
        *(float *)(rec + 0x20) = f14;
    ret = func_002B50E0(a0, a1, f12);
    *(int *)(rec + 0x38) = old38;
    *(float *)(rec + 0x28) = old28;
    *(float *)(rec + 0x20) = old20;
    return ret;
}

extern void func_00282CF0(float *out, const float *a, const float *b);
extern int func_L02_00332668(char *arg0, char *arg1);

int func_L02_00332630(char *arg0, void *arg1) {
    int tmp[4];

    func_00282CF0((float *)tmp, (const float *)arg1, (const float *)(arg0 + 0x10));
    return func_L02_00332668(arg0, (char *)tmp);
}

extern int D_L02_001A8FF0 __attribute__((sda));
extern float func_00283248(float a, float b);
extern int func_L01_00322288(char *a0, float f12);
extern void *func_L00_0032C638(char *a0);
extern float func_L00_003BFF68(char *a0, void *a1, char *a2, int a3);

/* Pick a target from the shape, or answer whether its height still fits. */
int func_L02_00332668(char *arg0, char *arg1) {
    void *rec;
    float h;

    if (D_L02_001A8FF0 == 0)
        return func_L01_00322288(arg0, func_00283248(*(float *)(arg1), *(float *)(arg1 + 4)));

    rec = func_L00_0032C638(arg0);
    if (rec == 0)
        return 0;
    h = func_L00_003BFF68(arg0, rec, arg1, 0);
    if (*(float *)((char *)rec + 0x30) < h)
        return 0;
    return 1;
}



extern void func_00282F20(float *out, const float *in, float s);
extern void *func_L00_0032C638(char *a0);
extern float func_L00_0031CDD0(char *a0, char *a1, int a2, float f12, float f13);

/* Aim the record at the shape the caller found. */
int func_L02_003329C8(char *a0, char *a1, float f12, float f13) {
    char *rec = func_L00_0032C638(a0);

    if (rec == 0)
        return 0;
    *(float *)(rec + 0x2C) = f13;
    func_00282CF0((float *)(rec + 0xA0), (const float *)a1, (const float *)(a0 + 0x10));
    *(int *)(rec + 0xA8) = 0;
    func_00282F20((float *)(rec + 0xA0), (const float *)(rec + 0xA0), f12);
    *(float *)(rec + 0xA8) = func_L00_0031CDD0(a0 + 0x10, a1, 0, f12, -f13);
    return 1;
}


#include "common.h"

typedef union { TI128 q; float f[4]; } MotionVector;
extern float func_L02_00329C48(char *, TI128 *, char *);

extern float func_00282E48(void *, void *);
extern float func_00282C10(float);
extern void func_L02_003294D8(char *, float *, float);
extern void func_002AFEB8(char *, char *, char *, float, char *);
extern float func_00282DB0(void *, void *);
extern void func_002AC9F8(float *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AFF08(char *, char *, char *);
extern float func_002B0360(char *);
/* This wrapper forwards its live a1/a2/f12 into func_002B00D8. */
extern void func_L00_003253A0(u8 *, float *, float *, float);
extern float func_002AFF38(char *, char *, char *);
extern void func_002AAC80(float *, float, float, float, float);

void func_L02_00332A80(char *object, char *data, void *target, TI128 *input, void *unused0, void *unused1, char *transform) {
    MotionVector desired, change;
    float vertical;
    float heading, distance, speed, height, drop;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        func_L00_003BFF68(object, data, (char *)input, (int)transform);
    heading = 0.0f;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        heading = func_L02_00329C48(object, input, transform);
    if (*(float *)(data + 0x30) < heading) {
        func_00282C88(&desired.q);
    } else {
        float gap;
        distance = func_00282E48(object + 0x10, target);
        *(float *)(data + 0xCC) = distance;
        gap = *(float *)(data + 0x34);
        if (distance <= gap) {
            qzero(&desired);
        } else {
            gap = distance - gap;
            speed = func_00282C10((gap + gap) * *(float *)(data + 0x24));
            if (*(float *)(data + 0x28) < speed)
                speed = *(float *)(data + 0x28);
            func_L02_003294D8(object, desired.f, speed);
        }
    }
    func_00282CF0(change.f, desired.f, (float *)(data + 0xA0));
    func_002AFEB8(object, (char *)&change, (char *)&change, 0.0f, transform);
    if (func_00282DB0(&desired, data + 0xA0) > 0.0f)
        func_002AC9F8(change.f, *(float *)(data + 0x20));
    else
        func_002AC9F8(change.f, *(float *)(data + 0x24));
    func_00282CC0(data + 0xA0, data + 0xA0, &change);
    *(float *)(data + 0xB0) = func_002AFF08(object, data + 0xA0, transform);
    if (!(*(unsigned int *)(data + 0x38) & 4)) {
        height = func_002B0360(object + 0x10);
        if (*(float *)(data + 0x90) < height) {
            func_L00_003253A0((u8 *)object, (float *)(data + 0xA0), (float *)(data + 0xA0), *(float *)(data + 0x2C));
            if (*(short *)(data + 0xC0) == 0)
                *(unsigned int *)(data + 0x94) |= 0x20;
        } else {
            vertical = func_002AFF38(object, data + 0xA0, transform);
            drop = vertical;
            if (*(float *)(data + 0x90) - height < drop)
                vertical = *(float *)(data + 0x90) - height;
            else if (vertical < 0.0f)
                vertical = 0.0f;
            func_002AAC80(&vertical, *(float *)(data + 0x90) - height, 0.011111111380159855f, 0.011111111380159855f, 1.0f);
            func_002AFEB8(object, data + 0xA0, data + 0xA0, vertical, transform);
        }
    }
}



/* func_L02_00333218 is defined in L02_00333218.c. */

extern void func_002AFFD8(char *a0, char *a1, int a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern int func_002761F8(char *a0, char *a1, int mode, char *self, int flag);
extern float func_002B0360(char *p);
extern char D_L02_001C0960;

/* Scale the shape's two axes, compare them with the record and copy the
   result into the second argument. */
void func_L02_00333300(char *a0, char *a1) {
    float buf0[4];
    float buf1[4];
    float buf2[4];
    char *obj;
    char *sub;

    func_002AFFD8(a0 + 0x10, (char *)buf0, 1);
    func_00282F20(buf1, buf0, *(float *)(a1 + 8) + 0.1f);
    func_00282F20(buf2, buf0, -*(float *)(a1 + 0xC) - 0.1f);
    func_00282CC0((char *)buf1, (char *)buf1, a0 + 0x10);
    func_00282CC0((char *)buf2, (char *)buf2, a0 + 0x10);
    if (func_002761F8((char *)buf1, (char *)buf2, 0, a0, 0)) {
        obj = &D_L02_001C0960;
        *(float *)(a1 + 0x90) = func_002B0360(obj);
        sub = obj - 0x20;
        *(int *)(a1 + 0x88) = *(int *)(sub + 0x18);
        *(int *)(a1 + 0x8C) = *(int *)(sub + 0x1C);
        func_00282F20((float *)(a1 + 0x50), (float *)(obj + 0x20), 1.0f);
    } else {
        *(int *)(a1 + 0x90) = 0;
        *(int *)(a1 + 0x88) = 0;
        *(int *)(a1 + 0x8C) = 0;
        func_00282C88(a1 + 0x50);
    }
}

extern void func_L02_00333480(char *arg0, char *arg1, void *arg2);

void func_L02_00333438(char *arg0, char *arg1) {
    int tmp[4];

    func_00282CF0((float *)tmp, (const float *)arg1, (const float *)(arg0 + 0x10));
    func_L02_00333480(arg0, arg1, tmp);
}

INCLUDE_ASM("asm/levels", func_L02_00333480);

extern void *func_002B9030(int kind);
extern int func_00283CF0(float f);
extern float func_002A7878(float a, float b);
extern float func_00283CE0(int n);
extern int func_L00_0031C998(int a0, int a1, float f12);
extern void func_00282D30(void *a0, void *a1, float f12);
extern unsigned char *D_L02_002001D8;
extern int func_001163B0(void);

/* Build one enemy record: pick its kind, place it, and aim it. */
void *func_L02_003449D8(void *a0, void *a1, void *a2, void *a3, int a4) {
    float buf[4];
    unsigned char *rec;
    unsigned char *rec2;
    short *p;
    short *q;
    int *r;
    float f21;
    float f20;

    rec = (unsigned char *)func_002B9030(0x56);
    if (rec != 0) {
        rec[9] = (unsigned char)(func_00283CF0(0.04f) - 0x60);
        rec[3] = (a3 != 0) ? 0x48 : 0x44;
        rec[1] = 0;
        rec[2] = *D_L02_002001D8;
        rec[8] = (unsigned char)func_001163B0();
        f21 = func_002A7878(0.0f, 1.0f);

        p = *(short **)((char *)a2 + 8);
        f20 = f21 / func_00283CE0(p[1] - p[0]);

        r = *(int **)((char *)a2 + 0);
        *(int *)(rec + 4) = func_L00_0031C998(r[0], r[1], f20);

        q = *(short **)((char *)a2 + 4);
        *(float *)(rec + 0xC) = ((float)q[0] + f20 * (float)(q[1] - q[0])) * 1000.0f;

        func_00282D30(buf, a1, f21);
        func_00282CC0(rec + 0x10, a0, buf);

        *(short *)(rec + 0xA) = (short)(*(int *)((char *)a2 + 0x10) - (f21 > 0.5f));

        rec2 = rec + 0x20;
        func_00282D30(rec2, a1, f21 * *(float *)((char *)a2 + 0x14));
        *(int *)(rec2 + 0x18) = a4;
        *(void **)(rec2 + 0x10) = a2;
        *(short *)(rec2 + 0x14) = 0;
    }

    return rec;
}

/* func_L02_00348420 is defined in L02_00348420-helpers.c. */

/* func_L02_00349BD8 is matched in its own unit, L02_00349BD8.c. */

INCLUDE_ASM("asm/levels", func_L02_00389F70);

/* func_L02_0038A008 is matched in its own unit, L02_0038A008.c. */

/* Two fields of the resident record at 0x189E20; retail shares its base between them. */
typedef struct {
    unsigned char pad00[0x88];
    float f88;
    unsigned char pad8C[0x2294 - 0x8C];
    int f2294;
} View_00189E20;

extern View_00189E20 D_00189E20;
/* sda: the bare load `lui $v1 ; lw $v1,%lo($v1)` retail has twice; a plain extern keeps the %hi
   in a saved register across the calls. */
extern int D_001A79F0 __attribute__((sda));
extern int D_L02_001CAA80;
extern char D_L02_001BA500[];
extern int D_L02_001B35B8 __attribute__((sda));
extern int func_L00_00329520(void *a0, int a1);
extern void func_002A7750(void *a0, int a1, int a2);
extern void func_L02_0038BD00(unsigned char *a0, int a1);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L02_0038C998(unsigned char *a0);
extern void func_L02_0038DA00(void *arg0);

/* State machine of the controller object that owns a group id list. On level 13 it retires
   itself (+0x30 = 0xFF, bits 0 and 6 of +0x34 set, bit 12 cleared) once the resident float is
   past 89 or the resident word is 0x74. State 0 runs func_L02_0038BD00; state 1 switches the
   whole group off (+0x31 cleared, bit 0 of +0x34 set) when the record test passes, then runs
   func_L02_0038C998 and queues func_L02_0038DA00; state 2 switches the group back on. */
void func_L02_0038BA28(unsigned char *arg0) {
    unsigned char *o = *(unsigned char **)(arg0 + 0x68);

    if (D_001A79F0 == 13) {
        if (89.0f < D_00189E20.f88 || D_00189E20.f2294 == 0x74) {
            arg0[0x30] = 0xFF;
            *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
            *(int *)(arg0 + 0x98) = 0;
            return;
        }
        *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    }
    if (*(unsigned short *)(arg0 + 0x34) & 2)
        return;
    if (D_L02_001CAA80 != 0)
        return;
    switch (arg0[0x20]) {
    case 0:
        func_L02_0038BD00(arg0, arg0[0x21]);
        break;
    case 1:
        /* each walk has its own q and e: retail gives the two walks different registers */
        if (*(int *)(o + 0xC) != -1 && func_L00_00329520(D_L02_001BA500, *(int *)(o + 0xC)) != 0) {
            unsigned short *q;
            unsigned char *e;

            q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
            while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
                   ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
                e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
                if (e == 0)
                    break;
                e[0x31] = 0;
                *(unsigned short *)(e + 0x34) |= 1;
                q++;
            }
            func_002A7750(arg0, 2, -1);
        }
        func_L02_0038C998(arg0);
        if (D_001A79F0 != 13 || !(89.0f < D_00189E20.f88))
            func_L00_002E6CF0(func_L02_0038DA00, arg0);
        break;
    case 2:
        if (func_L00_00329520(D_L02_001BA500, *(int *)(o + 0xC)) == 0) {
            unsigned short *q;
            unsigned char *e;

            q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
            while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
                   ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
                e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
                if (e == 0)
                    break;
                e[0x31] = 1;
                *(unsigned short *)(e + 0x34) &= 0xFFFE;
                q++;
            }
            func_002A7750(arg0, 1, -1);
        }
        break;
    }
}

/* func_L02_0038BD00 is defined in L02_0038BD00-g8.c. */

/* func_L02_0038C998 is defined in L02_002B5F50-g8.c (it reads $gp data). */

/* func_L02_0038CDE8 is defined in L02_002B5F50-lamps.c. */

extern int func_00282978(void *p);
extern int func_00283D38(int a0, int a1, float f12);

/* Toggle the lamp and hand the new state to the colour routine. */
void func_L02_0038D978(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    if (*(short *)(arg0 + 0xAA) != 0x9B0)
        return;
    if (func_00282978(s0 + 0x74) != 0) {
        *(unsigned short *)(s0 + 0x74) = 0x32;
        *(unsigned int *)(s0 + 0x8C) = (*(unsigned int *)(s0 + 0x8C) == 0);
    }
    *(int *)(arg0 + 0x78) = func_00283D38(*(int *)(arg0 + 0x78),
        *(unsigned int *)(s0 + 0x8C) != 0 ? 0x50787878 : 0x50141414, 0.15f);
}


extern void func_L02_0038DA60(unsigned char *arg0);
extern void func_L02_0038DC68(unsigned char *arg0);
extern void func_L02_0038DE58(unsigned char *arg0);
extern void func_L02_0038E048(unsigned char *arg0);
extern void func_L02_0038E250(unsigned char *arg0);
extern void func_L02_0038E430(unsigned char *arg0);
extern void func_L02_0038E610(unsigned char *arg0);
extern void func_L02_0038E838(unsigned char *arg0);

void func_L02_0038DA00(void *arg0) {
    func_L02_0038DA60(arg0);
    func_L02_0038DC68(arg0);
    func_L02_0038DE58(arg0);
    func_L02_0038E048(arg0);
    func_L02_0038E250(arg0);
    func_L02_0038E430(arg0);
    func_L02_0038E610(arg0);
    func_L02_0038E838(arg0);
}

extern void func_00282D60(void *buf, void *value, float scale);
extern int func_00283DB8(void *buf, float value);
extern void func_L00_002ECFE8(void *a0, void *a1, int a2, unsigned int a3,
                              float f12, float f13, float f14, int t0, int t1);
extern char *D_L02_001FBFC0[];
extern int func_L02_002F1658(void);

/* Walks the object's group id list: every entity of kind 0x9B0 in state 1 that passes the
   visibility test gets its phase at +0x1C advanced (while the flag word is clear) and one effect
   call. */
void func_L02_0038DA60(unsigned char *arg0) {
    unsigned short *q;
    unsigned char *e;
    char *o;
    float buf[4];
    int flag;

    if (arg0[0x21] == 0xFF)
        return;
    flag = func_L02_002F1658();
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                (*(unsigned short *)(e + 0x34) & 1) == 0 && *(short *)(e + 0xAA) == 0x9B0 &&
                e[0x20] == 1) {
                if (flag != 0) {
                    *(float *)(o + 0x1C) -= 0.1f;
                    if (*(float *)(o + 0x1C) <= -8.0f)
                        *(float *)(o + 0x1C) += 8.0f;
                }
                func_L00_002ECFE8(e, o + 0xA0, 3, 0x60804040, *(float *)(o + 0x78) * 0.8f,
                                  *(float *)(o + 0x78) * 5.0f, *(float *)(o + 0x1C), 0x204090, 0x17);
            }
        }
        q++;
    }
}

/* Walk the object's group list: every entity of kind 0x9B7 in state 1 that is in view gets one
   effect call. While the resident flag word is clear, its object's phase (+0x1C) first steps
   down by 0.1, and up by 8 once it reaches -8. */
void func_L02_0038DC68(unsigned char *arg0) {
    float buf[4];
    unsigned short *q;
    unsigned char *e;
    char *o;
    int flag;

    if (arg0[0x21] == 0xFF)
        return;
    flag = func_L02_002F1658();
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                !(*(unsigned short *)(e + 0x34) & 1) && *(short *)(e + 0xAA) == 0x9B7 &&
                e[0x20] == 1) {
                if (flag != 0) {
                    *(float *)(o + 0x1C) -= 0.1f;
                    if (*(float *)(o + 0x1C) <= -8.0f)
                        *(float *)(o + 0x1C) += 8.0f;
                }
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x605696FF, *(float *)(o + 0x78),
                                  *(float *)(o + 0x78) * 7.0f, *(float *)(o + 0x1C), 0xC0, 0x17);
            }
        }
        q++;
    }
}

/* The same walk as func_L02_0038DC68, for the entities of kind 0xB15. */
void func_L02_0038DE58(unsigned char *arg0) {
    float buf[4];
    unsigned short *q;
    unsigned char *e;
    char *o;
    int flag;

    if (arg0[0x21] == 0xFF)
        return;
    flag = func_L02_002F1658();
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                !(*(unsigned short *)(e + 0x34) & 1) && *(short *)(e + 0xAA) == 0xB15 &&
                e[0x20] == 1) {
                if (flag != 0) {
                    *(float *)(o + 0x1C) -= 0.1f;
                    if (*(float *)(o + 0x1C) <= -8.0f)
                        *(float *)(o + 0x1C) += 8.0f;
                }
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x605696FF, *(float *)(o + 0x78),
                                  *(float *)(o + 0x78) * 7.0f, *(float *)(o + 0x1C), 0xC0, 0x17);
            }
        }
        q++;
    }
}

/* Like func_L02_0038DA60 for kind 0x134B: one effect call, with the scale 2.1000001f
   (0x40066667, one above 2.1f). */
void func_L02_0038E048(unsigned char *arg0) {
    unsigned short *q;
    unsigned char *e;
    char *o;
    float buf[4];
    int flag;

    if (arg0[0x21] == 0xFF)
        return;
    flag = func_L02_002F1658();
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                (*(unsigned short *)(e + 0x34) & 1) == 0 && *(short *)(e + 0xAA) == 0x134B &&
                e[0x20] == 1) {
                if (flag != 0) {
                    *(float *)(o + 0x1C) -= 0.1f;
                    if (*(float *)(o + 0x1C) <= -8.0f)
                        *(float *)(o + 0x1C) += 8.0f;
                }
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x60804040, *(float *)(o + 0x78) * 0.3f,
                                  *(float *)(o + 0x78) * 2.1000001f, *(float *)(o + 0x1C), 0x204090, 0x17);
            }
        }
        q++;
    }
}

/* Walk the object's group list: every entity of kind 0x127D in state 1 that is in view has its
   object's phase (+0x1C) stepped down by 0.1 (and up by 8 once it reaches -8), and gets one
   effect call. */
void func_L02_0038E250(unsigned char *arg0) {
    float buf[4];
    unsigned short *q;
    unsigned char *e;
    char *o;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                !(*(unsigned short *)(e + 0x34) & 1) && *(short *)(e + 0xAA) == 0x127D &&
                e[0x20] == 1) {
                *(float *)(o + 0x1C) -= 0.1f;
                if (*(float *)(o + 0x1C) <= -8.0f)
                    *(float *)(o + 0x1C) += 8.0f;
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x605696FF, *(float *)(o + 0x78) * 0.4f,
                                  *(float *)(o + 0x78) * 4.0f, *(float *)(o + 0x1C), 0xC0, 0x17);
            }
        }
        q++;
    }
}

/* The same walk as func_L02_0038E250, for the entities of kind 0x128B (the effect's second
   scale is 3 times the object's +0x78 instead of 4 times). */
void func_L02_0038E430(unsigned char *arg0) {
    float buf[4];
    unsigned short *q;
    unsigned char *e;
    char *o;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                !(*(unsigned short *)(e + 0x34) & 1) && *(short *)(e + 0xAA) == 0x128B &&
                e[0x20] == 1) {
                *(float *)(o + 0x1C) -= 0.1f;
                if (*(float *)(o + 0x1C) <= -8.0f)
                    *(float *)(o + 0x1C) += 8.0f;
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x605696FF, *(float *)(o + 0x78) * 0.4f,
                                  *(float *)(o + 0x78) * 3.0f, *(float *)(o + 0x1C), 0xC0, 0x17);
            }
        }
        q++;
    }
}

/* Like func_L02_0038DA60 for kind 0x1290, without the flag word: the phase always advances
   and two effect calls follow, the second one at +0xC0 with both scales times 1.5. */
void func_L02_0038E610(unsigned char *arg0) {
    unsigned short *q;
    unsigned char *e;
    char *o;
    float buf[4];
    float a;
    float b;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                (*(unsigned short *)(e + 0x34) & 1) == 0 && *(short *)(e + 0xAA) == 0x1290 &&
                e[0x20] == 1) {
                *(float *)(o + 0x1C) -= 0.1f;
                if (*(float *)(o + 0x1C) <= -8.0f)
                    *(float *)(o + 0x1C) += 8.0f;
                a = *(float *)(o + 0x78) * 0.4f;
                b = *(float *)(o + 0x78) * 3.0f;
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x60804020, a, b, *(float *)(o + 0x1C), 0xC00000, 0x17);
                func_L00_002ECFE8(e, o + 0xC0, 1, 0x60804020, a * 1.5f, b * 1.5f, *(float *)(o + 0x1C), 0xC00000,
                                  0x17);
            }
        }
        q++;
    }
}

/* Like func_L02_0038DA60 for kind 0x1340: one effect call whose first scale is the +0x78
   field itself and the second is seven times it. */
void func_L02_0038E838(unsigned char *arg0) {
    unsigned short *q;
    unsigned char *e;
    char *o;
    float buf[4];
    int flag;

    if (arg0[0x21] == 0xFF)
        return;
    flag = func_L02_002F1658();
    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        if (e[0x31] != 0) {
            func_00282D60(buf, e, 0.0009765625f);
            buf[3] *= 1.1f;
            if (func_00283DB8(buf, (float)*(int *)(o + 0x98)) != -1 &&
                (*(unsigned short *)(e + 0x34) & 1) == 0 && *(short *)(e + 0xAA) == 0x1340 &&
                e[0x20] == 1) {
                if (flag != 0) {
                    *(float *)(o + 0x1C) -= 0.1f;
                    if (*(float *)(o + 0x1C) <= -8.0f)
                        *(float *)(o + 0x1C) += 8.0f;
                }
                func_L00_002ECFE8(e, o + 0xA0, 2, 0x605696FF, *(float *)(o + 0x78), *(float *)(o + 0x78) * 7.0f,
                                  *(float *)(o + 0x1C), 0xC0, 0x17);
            }
        }
        q++;
    }
}

/* Raise the byte field to eight when it is below. */
void func_L02_00392C70(unsigned char *a0) {
    if (a0[0x20] < 8) {
        a0[0x20] = 8;
    }
}

/* Raise the byte field to eight when it is below. */
void func_L02_003948D0(unsigned char *a0) {
    if (a0[0x20] < 8) {
        a0[0x20] = 8;
    }
}

extern void func_L02_003AA650(char *arg0);

void func_L02_003A6F78(char *arg0) {
    unsigned char *p;
    unsigned char *q;

    arg0[0x20] = 6;
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    *(int *)(arg0 + 0x98) = 0;
    p = *(unsigned char **)(arg0 + 0x68);
    p[0xC8] = 1;
    p[0xC9] = 0xFF;
    q = *(unsigned char **)(p + 0xFC);
    if (q != 0) {
        if (*(short *)(q + 0xAA) == 0x326) {
            func_L02_003AA650(q);
            *(unsigned char **)(p + 0xFC) = 0;
        } else {
            *(unsigned char **)(p + 0xFC) = 0;
        }
    }
}

/* Raises the object's flag word, copies a context field in and dispatches on the
   two-byte kind code. */
extern int func_00312E20(void *, int);

void func_L02_003A6FE8(char *self) {
    char *s1;
    short t;

    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) & 0xFFBE) | 0x1000;
    s1 = *(char **)(self + 0x68);
    *(unsigned int *)(self + 0x98) = *(unsigned int *)(*(unsigned int *)(self + 0x24) + 0x10);
    self[0x20] = 1;
    *(unsigned int *)(s1 + 0x100) = 0;
    t = *(short *)(self + 0xAA);
    if (t == 0x1F5) {
        *(unsigned int *)(s1 + 0xFC) = func_00312E20(self, 0);
    } else if (t == 0x200) {
        *(unsigned int *)(s1 + 0xFC) = func_00312E20(self, 1);
    }
    self[0x7F] = 0;
}

/* func_L02_003A8770 is defined in L02_002B5F50-quad.c. */

extern void func_002B9180(void *p);
extern void func_0029F338(void *e);
extern void *D_L02_001B31EC __attribute__((sda));

/* Release the eight slots behind the entity, then retire it. */
void func_L02_003AA650(char *arg0) {
    void **p;
    int i;

    p = (void **)(*(char **)(arg0 + 0x68) + 0x30);
    for (i = 7; i >= 0; i--) {
        if (p[0] != 0) {
            func_002B9180(p[0]);
            p[0] = 0;
        }
        p++;
    }
    if (D_L02_001B31EC == arg0)
        arg0[0x20] = 4;
    else
        func_0029F338(arg0);
}



/* func_L02_003C0890 is defined in L02_003C0890-helpers.c. */


/* func_L02_003C4068 is defined in L02_003C4068.c. */

/* func_L02_003C4280 is defined in L02_003C4280.c. */
