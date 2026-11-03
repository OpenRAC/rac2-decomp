#include "include_asm.h"
#include "common.h"

extern float func_00283CE0(int);
/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xA0];
    float fA0, fA4;
    char gap[8];
    float fB0;
    char gapB4[0x14C];
    float f200, f204, f208, f20C;
    char gap210[8];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
    int color[3];
} ScreenState;
extern ScreenState D_001B9040;
extern void func_0027AB40(void);

extern void F4778f810_FUN_002B00D8(char *a, char *b, char *c, f32 d);

extern void F4778f810_FUN_00282CC0(char *a, char *b, char *c);

extern void F4778f810_FUN_00283098(char *a, char *b, char *c);

extern void F4778f810_FUN_00283958(char *a, char *b);

extern void F4778f810_FUN_00283738(char *a, char *b, char *c);

extern void F4778f810_FUN_00282CF0(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif

#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif

#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif

/* Append an observed point index and update the original geometric descriptor. */
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;

typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;

extern void func_00274810(OozlaAppendObject164 *, int, const float *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00283098(float *, const float *, const float *);

extern void func_00274B58(OozlaAppendObject164 *, float *, const float *);

extern void func_00283028(void *a, void *b, void *c);

extern float func_00282DF0_5(void *a);

extern float func_00282DB0_3(void *a, void *b);

extern void func_002AA2E8_2(float *p, float a, float b);

extern void func_00282F20_16(void *a, void *b, float f);

/* Measured partial layouts; original type and game roles are unknown. */
struct Rac2Native_00169805055547ed_Rec31cd0302 {
    int v[10];
};

extern struct Rac2Native_00169805055547ed_Rec31cd0302 D_L04_001BCE48[];

extern char Fd8e166aa_D_001B7F80[];

extern int Fcdb4d905_FUN_0027A0F8(int a, int b, int c);

extern void func_00282D08(float *out, float *a, float *b, float t);
extern void func_00282F20(float *out, float *in, float s);
extern void func_00282DD8(float *out, float *a, float *b);
extern void func_002AFFD8(float *a, float *b, int c);
extern void func_00283958(float *a, float *b);
extern void func_00283738(float *a, float *b, float *c);
extern void func_00274A88(char *o, float *p, float *v);

/* Hit-index descriptor: a vector at 0x20 (its w is the scale), the point array at 0x30,
   the collision data at 0x54, the point count at 0x58, three used indices at 0x59 and
   the used count at 0x5C. */
typedef struct {
    u8 pad000[0x20];
    f32 vec020[4];
    f32 (*points030)[4];
    u8 pad034[0x20];
    char *p054;
    u8 count058;
    u8 indices059[3];
    u8 count05C;
} HitIndex_00274500;

extern int func_00278CE0(float *a, float *b, int c, int d);

extern int func_00277258(float *out, int mode, float scale, char *data);

extern float D_001BAFA0[];

/* Collision-hit nudge subject: geometry plane at 0x20, scale 0x2C, data pointer 0x54. */
typedef struct {
    u8 pad000[0x20];
    u8 at020[0xC];
    f32 f02C;
    u8 pad030[0x24];
    char *p054;
} HitNudge_002746C8;

extern float D_001BAFB0[];

extern void func_002ACE78(float *, float *, float);

extern void func_00282D30(void *, void *, float);

extern void func_002FC3C0(int);
extern void func_002FC138(void);
extern void func_002FC1D8(void);
extern void func_0027D330(int);
extern int D_001B7F98;
extern int D_001A72D4 __attribute__((sda));

extern int func_00282948(void *);
extern char D_001B7FA8[];

/* Index holder at 0x1B7F80: the current item index and the key that goes with it. */
typedef struct {
    char pad000[0x20];
    unsigned short idx;
    unsigned short idx2;
} OozlaIndex_001B7F80;

/* Item table at 0x1B8308: 32 entries of 40 bytes; the group key first, the item pointer at 0x1C. */
typedef struct {
    int key;
    char pad004[0x18];
    int ptr;
    char pad020[8];
} OozlaEntry_001B8308;

typedef struct {
    OozlaEntry_001B8308 e[32];
    int count;
} OozlaTable_001B8308;

extern OozlaTable_001B8308 D_001B8308;
extern int func_002798A0(int, int *, int *);

/* The index holder itself, named through the symbol the file already uses for it. */
#define OozlaHolder ((OozlaIndex_001B7F80 *)Fd8e166aa_D_001B7F80)

/* The level's state word.  It sits at a different address in every program that has
   this function (0x1B1580 in the boot, 0x1B18C0 in level 00, and so on), so it is a
   per-level external.  The sda attribute makes the compiler emit a bare symbol
   reference; the assembler then expands it - in reorder mode, and with the symbol's
   size still unknown - into the retail's "lui $reg,0x1B" plus offset, with the
   address in $at for the stores.  This unit therefore has to stay at -G0: a -G8
   sibling would emit the .extern directive, and the reference would become
   gp-relative instead. */
extern int ref_L00_002E38F0_00 __attribute__((sda));

extern int D_001B1710 __attribute__((sda));
extern char D_001BADC0[];
extern void func_00282A60(void *, int, int);
extern void func_0027A288(void);

/* Occlusion state read by func_0027A288: the camera position, the current and
   merged visibility bitmaps, and the two fallback tables (octant and
   directional, both a 16-byte origin followed by 128-byte bitmaps). */
typedef struct { float origin[4]; char visibility[0][128]; } OcclDirectional;
typedef struct { char pad[0x140]; float position[3]; } OcclCamera;
extern OcclCamera D_001B5200;
extern char D_001BAE40[128];
extern float *D_001B1704 __attribute__((sda));
extern float *D_001B1708 __attribute__((sda));
extern int D_001B170C __attribute__((sda));
extern int D_001B1714 __attribute__((sda));
extern unsigned char *D_001B1718 __attribute__((sda));
extern int func_00283CF0(float);
extern void func_00282B50(void *, const void *, int);
extern void func_00282A88(void *, int);
extern void func_00282B78(void *, const void *, const void *, int);
extern float func_00283248(float, float);
extern float func_00282E80(const void *, const void *);

/* The screen extent record: size, half size and the four <<4 edges around 0x800. Its
   fields are stored as symbol+offset, which this cc1 counts as two-instruction macro
   stores, so none of them takes a call's delay slot (retail's order). */
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent D_001A7340 __attribute__((sda));
typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions D_001A6480;

void func_00274128(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    F4778f810_FUN_002B00D8((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    F4778f810_FUN_00283098((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00283958((char *)p + 0x10, (char *)&tmp[3]);
    F4778f810_FUN_00283738((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    F4778f810_FUN_00283098((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00282CF0((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    F4778f810_FUN_00282CF0((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

void func_00274208(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    F4778f810_FUN_002B00D8((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    F4778f810_FUN_00283098((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00283958((char *)p + 0x10, (char *)&tmp[3]);
    F4778f810_FUN_00283738((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    F4778f810_FUN_00283098((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00282CF0((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    F4778f810_FUN_00282CF0((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

void func_002742E8(char *o)
{
    float a[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float h[4] __attribute__((aligned(16)));
    float i[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float g[3][4] __attribute__((aligned(16)));
    unsigned char *m = *(unsigned char **)(o + 0x68);
    float *w;

    if (m[0x5C] >= 2) {
        func_00282D08(a, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16), 0.5f);
        func_00282CF0(b, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16));
        func_00283098(b, b, (float *)(o + 0xC0));
        w = (float *)(o + 0xC0);
    } else {
        qcopy(a, *(char **)(m + 0x30) + m[0x59] * 16);
        w = (float *)(o + 0xC0);
    }
    func_00283098(c, a, w);
    func_002AFFD8((float *)(o + 0x10), d, 1);
    func_00282CF0(e, a, (float *)(m + 0x20));
    func_00283098(e, e, w);
    func_00282F20(e, e, 1.0f);
    func_00282DD8(f, e, d);
    func_00282F20(f, f, *(float *)(m + 0x4C));
    func_00274A88(o, (float *)(m + 0x10), f);
    if (m[0x5C] >= 2)
        func_00274B58(o, (float *)(m + 0x10), b);
    func_00283958((float *)(m + 0x10), g[0]);
    func_00283738(w, g[0], w);
    func_00283098(h, a, w);
    func_00282CF0(i, h, c);
    func_00282CF0((float *)(o + 0x10), (float *)(o + 0x10), i);
}

int func_00274500(Obj_F4778f810 *obj)
{
    float tmp0[4];
    float tmp1[4];
    float tmp2[4];
    float tmp3[4];
    float *v;
    HitIndex_00274500 *p = (HitIndex_00274500 *)obj->p068;
    int i;
    int j;
    int used;
    int hit;
    float scale;

    func_00283098(tmp0, p->vec020, (float *)((char *)obj + 0xC0));
    F4778f810_FUN_00282CC0((char *)tmp0, (char *)tmp0, (char *)obj + 0x10);
    hit = func_00277258(tmp0, 0x62, p->vec020[3], p->p054);
    if (hit != 0) {
        for (i = 0; i < p->count058; i++) {
            used = 0;
            for (j = 0; j < p->count05C; j++) {
                if (p->indices059[j] == i) {
                    used = 1;
                    break;
                }
            }
            if (used)
                continue;
            func_00283098(tmp1, p->points030[i], (float *)((char *)obj + 0xC0));
            F4778f810_FUN_00282CC0((char *)tmp1, (char *)tmp1, (char *)obj + 0x10);
            if (func_00278CE0(tmp0, tmp1, hit, 0) != 0) {
                v = D_001BAFA0;
                F4778f810_FUN_00282CF0((char *)tmp2, (char *)tmp1, (char *)v);
                func_00282F20_16(v + 8, v + 8, 1.0f);
                scale = func_00282DB0_3(tmp2, v + 8);
                func_00282F20_16(tmp3, v + 8, -scale);
                F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)tmp3);
                return i;
            }
        }
        return -1;
    }
    p->count05C = 0;
    return -1;
}

int func_002746C8(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[2];
    HitNudge_002746C8 *p = (HitNudge_002746C8 *)obj->p068;

    func_00283098((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    func_00282CC0((char *)&tmp[0], (char *)&tmp[0], (char *)obj + 0x10);
    if (func_00277258((float *)&tmp[0], 2, p->f02C, p->p054) != 0) {
        func_00282CF0((char *)&tmp[1], (char *)D_001BAFB0, (char *)&tmp[0]);
        func_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[1]);
        return 1;
    }
    return 0;
}

/* appendindexbyte59/count5C descriptor68, originalthreeGPR geometricupdate inclincomingdirectionA2, ifcount!=1 originalpointdifference24/transform40/bound80 andterminalcountbyte return */
unsigned int func_00274768(OozlaAppendObject164 *object, unsigned int index, const float *direction)
{
    float difference[4];
    OozlaAppendDescriptor164 *descriptor = object->descriptor;
    descriptor->indices[descriptor->count] = index;
    ++descriptor->count;
    func_00274810(object, (int)descriptor->count - 1, direction);
    if (descriptor->count != 1) {
        func_00282CF0(difference, descriptor->points[descriptor->indices[0]], descriptor->points[descriptor->indices[1]]);
        func_00283098(difference, difference, &object->transform[0][0]);
        func_00274B58(object, descriptor->plane, difference);
    }
    return descriptor->count;
}

void func_00274B58(OozlaAppendObject164 *a0, float *a1, const float *a2) {
    float tmp[4];
    float value;
    func_00282F20_16(tmp, (void *)a2, 1.0f);
    value = func_00282DB0_3(tmp, a1);
    func_002ACE78(a1, tmp, value);
}

/* Keeps the float one helper returns, and when a later helper reports a ratio above 0.7 scales it by a factor with a floor, hands it to a setter through a local, then reports whether the kept value is non-zero. */
int func_00274BA8(void *p, void *q, void *r, float f12, float f13)
{
    float saved;
    float t;
    float v;

    func_00283028(p, p, q);
    saved = func_00282DF0_5(p);
    v = func_00282DB0_3(r, q);
    if (v > 0.7f) {
        t = saved * f12;
        if (t < f13) t = f13;
        func_002AA2E8_2(&saved, 0.0f, t);
        func_00282F20_16(p, p, saved);
    }
    if (saved != 0.0f) return 1;
    return 0;
}

int func_00274C90(char *object, float *output, int limit)
{
    char *data = *(char **)(*(char **)(object + 0x24) + 0x10);
    char *entry, *base;
    float scale;
    int count, remaining;
    float *cursor;
    if (!data)
        return 0;
    count = *(int *)(data + 0xC) / 8;
    base = data + *(int *)(data + 4);
    scale = *(float *)(object + 0x2C) * (1.0f / 1024.0f);
    if (limit < count)
        count = limit;
    entry = base + 16;
    if (count > 0) {
    cursor = output;
    remaining = count;
    do {
        remaining--;
        cursor[0] = func_00283CE0(*(short *)entry);
        cursor[1] = func_00283CE0(*(short *)(entry + 2));
        cursor[2] = func_00283CE0(*(short *)(entry + 4));
        entry += 8;
        func_00282D30(cursor, cursor, scale);
        cursor[3] = 1.0f;
        cursor += 4;
    } while (remaining);
    }
    return count;
}

ASM_FUNC("asm/game", func_00274D90);

ASM_FUNC("asm/game", func_00276158);

ASM_FUNC("asm/game", func_002761F8);

ASM_FUNC("asm/game", func_00277258);

ASM_FUNC("asm/game", func_00277F48);

ASM_FUNC("asm/game", func_00278870);

INCLUDE_ASM("asm/game", func_00278CE0);

ASM_FUNC("asm/game", func_00278E78);

void func_00278F80(void) {
    func_002FC3C0(1);
    func_002FC138();
    func_002FC1D8();
    D_001A72D4 = D_001B7F98;
    func_0027D330(30);
}

/* Store ten integer arguments in the indexed record when the unsigned index is below 32; otherwise leave the table unchanged. */
void func_00279790(int p0, int p1, int p2, int p3, int p4, int p5,
                                      int p6, int p7, int p8, int p9, unsigned idx)
{
    if (idx >= 32u)
        return;
    D_L04_001BCE48[idx].v[0] = p0;
    D_L04_001BCE48[idx].v[1] = p1;
    D_L04_001BCE48[idx].v[2] = p2;
    D_L04_001BCE48[idx].v[3] = p3;
    D_L04_001BCE48[idx].v[4] = p4;
    D_L04_001BCE48[idx].v[5] = p5;
    D_L04_001BCE48[idx].v[6] = p6;
    D_L04_001BCE48[idx].v[7] = p7;
    D_L04_001BCE48[idx].v[8] = p8;
    D_L04_001BCE48[idx].v[9] = p9;
}

/* Walk the item table from the current index, carrying the offset across entries of one group; return 1 when it lands inside an entry. */
int func_002798A0(int value, int *out_index, int *out_offset)
{
    OozlaTable_001B8308 *table;
    char *start_field;
    char *end_field;

    *out_index = (short)OozlaHolder->idx;
    *out_offset = (short)OozlaHolder->idx2 + value;

    while (*out_index >= 0 && *out_index < D_001B8308.count) {
        int row, start, end, offset, next_offset;

        table = &D_001B8308;
        start_field = (char *)table + 4;
        end_field = (char *)table + 8;
        row = *out_index * sizeof(OozlaEntry_001B8308);
        start = *(int *)(row + start_field);
        end = *(int *)(row + end_field);
        offset = *out_offset;

        if (end >= start + offset)
            return 1;
        if (*out_index + 1 >= table->count)
            return 0;
        if (*(int *)(row + (char *)table) != table->e[*out_index + 1].key)
            return 0;

        next_offset = offset - 1;
        next_offset -= end - start;
        *out_offset = next_offset;
        *out_index = *out_index + 1;
    }
    return 0;
}

int func_00279988(void) {
    return func_00282948(D_001B7FA8);
}

int func_002799A8(void)
{
    int t1, t2;
    OozlaIndex_001B7F80 *g = OozlaHolder;
    int key, found, count;

    if ((short)g->idx == -1) {
        g->idx = 0;
        g->idx2 = 0;
        if (ref_L00_002E38F0_00 == 1) {
            ref_L00_002E38F0_00 = 2;
            g->idx = 4;
            g->idx2 = 0;
        }
        return 1;
    }
    if (func_002798A0(D_001B8308.e[(short)g->idx].ptr, &t1, &t2)) {
        if (D_001B8308.e[(short)g->idx].ptr != 0) {
            g->idx = (unsigned short)t1;
            g->idx2 = (unsigned short)t2;
            return 1;
        }
    }
    {
        OozlaEntry_001B8308 *e = &D_001B8308.e[(short)OozlaHolder->idx];

        found = 1;
        count = D_001B8308.count;
        key = e->key;
        OozlaHolder->idx2 = 0;
        OozlaHolder->idx = OozlaHolder->idx + 1;
        if ((short)OozlaHolder->idx < count) {
            do {
                if (D_001B8308.e[(short)OozlaHolder->idx].key != key) {
                    found = 0;
                } else {
                    OozlaHolder->idx = OozlaHolder->idx + 1;
                }
            } while ((short)OozlaHolder->idx < count && found);
        }
        if ((short)OozlaHolder->idx == 4 && ref_L00_002E38F0_00 == 0) {
            OozlaHolder->idx = 3;
            ref_L00_002E38F0_00 = 1;
            return 0;
        }
    }
    return !found;
}

int func_0027A1D0(float x, int a, int b, int c, int d, int e, int g)
{
    int r, p, q, s;
    if (x < 0.5f) {
        r = Fcdb4d905_FUN_0027A0F8(a, b, c);
        if (r) return r;
        p = d;
        q = e;
        s = g;
    } else {
        r = Fcdb4d905_FUN_0027A0F8(d, e, g);
        if (r) return r;
        p = a;
        q = b;
        s = c;
    }
    return Fcdb4d905_FUN_0027A0F8(p, q, s);
}

/* Fills the visibility bitmap D_001BADC0 for the camera's grid cell (position / 4).
   Without an entry for the cell, mode 0 merges the nearer neighbor along each axis;
   otherwise the mode in D_001B170C picks a fallback: the previous bitmap, all visible,
   an octant table around an origin, or a directional table indexed by azimuth and
   elevation. The last bit is always set. */
void func_0027A288(void)
{
    float origin[4], delta[4];
    float scale = 0.25f;
    int x, y, z, bx, by, bz, index;
    int xm, xp, ym, yp, zm, zp;
    float fraction;
    unsigned char *vis, *gx, *gy, *gz, *previous;
    float *p;

    x = func_00283CF0(D_001B5200.position[0] * scale);
    y = func_00283CF0(D_001B5200.position[1] * scale);
    z = func_00283CF0(D_001B5200.position[2] * scale);
    vis = (unsigned char *)Fcdb4d905_FUN_0027A0F8(x, y, z);
    if (vis) {
        D_001B1714 = 0;
        func_00282B50(D_001BADC0, vis, 128);
        D_001B1718 = vis;
    } else {
        D_001B1714 = 1;
        if (D_001B170C == 0) {
            xm = x - 1;
            xp = x + 1;
            fraction = func_00283CE0(x);
            yp = y + 1;
            zp = z + 1;
            ym = y - 1;
            zm = z - 1;
            gx = (unsigned char *)func_0027A1D0(D_001B5200.position[0] * scale - fraction, xm, y, z, xp, y, z);
            fraction = func_00283CE0(y);
            gy = (unsigned char *)func_0027A1D0(D_001B5200.position[1] * scale - fraction, x, ym, z, x, yp, z);
            fraction = func_00283CE0(z);
            gz = (unsigned char *)func_0027A1D0(D_001B5200.position[2] * scale - fraction, x, y, zm, x, y, zp);
            if (gx || gy || gz) {
                func_00282A88(D_001BAE40, 128);
                if (gx) func_00282B78(D_001BAE40, D_001BAE40, gx, 128);
                if (gy) func_00282B78(D_001BAE40, D_001BAE40, gy, 128);
                if (gz) func_00282B78(D_001BAE40, D_001BAE40, gz, 128);
                vis = D_001BAE40;
                D_001B1718 = vis;
                func_00282B50(D_001BADC0, vis, 128);
            }
        }
        if (!vis) {
            switch (D_001B170C) {
            case 0:
                previous = D_001B1718;
                if (previous) func_00282B50(D_001BADC0, previous, 128);
                else func_00282A60(D_001BADC0, -1, 128);
                break;
            case 2:
                p = D_001B1704;
                if (p) {
                    bx = 0.0f < D_001B5200.position[0] - p[0];
                    by = 0.0f < D_001B5200.position[1] - p[1];
                    bz = 0.0f < D_001B5200.position[2] - p[2];
                    func_00282B50(D_001BADC0, (char *)p + ((bz + by * 2 + bx * 4) * 128 + 16), 128);
                    break;
                }
                if (D_001B1718) {
                    func_00282B50(D_001BADC0, D_001B1718, 128);
                    break;
                }
                /* fall through */
            case 1:
                func_00282A60(D_001BADC0, -1, 128);
                break;
            case 3: {
                float *directional = D_001B1708;
                if (directional) {
                    origin[0] = directional[0];
                    origin[1] = directional[1];
                    origin[2] = directional[2];
                    origin[3] = 0;
                    delta[0] = D_001B5200.position[0] - origin[0];
                    delta[1] = D_001B5200.position[1] - origin[1];
                    delta[2] = D_001B5200.position[2] - origin[2];
                    delta[3] = 0;
                    index = 0;
                    if (delta[0] > 0 && delta[1] > 0) {
                        index = func_00283CF0(func_00283248(delta[0], delta[1]) * 10.185916f) << 6;
                        delta[0] = func_00282E80(D_001B5200.position, origin);
                    } else if (delta[0] <= 0 && delta[1] > 0) {
                        index = 1024;
                        if (delta[0] == 0) {
                            delta[0] = delta[1];
                        } else {
                            index += func_00283CF0(func_00283248(delta[1], -delta[0]) * 10.185916f) << 6;
                            delta[0] = func_00282E80(D_001B5200.position, origin);
                        }
                    } else if (delta[0] < 0 && delta[1] < 0) {
                        index = func_00283CF0(func_00283248(-delta[0], -delta[1]) * 10.185916f) << 6;
                        delta[0] = -func_00282E80(D_001B5200.position, origin);
                    } else if (delta[0] >= 0 && delta[1] < 0) {
                        index = 1024;
                        if (delta[0] == 0) {
                            delta[0] = delta[1];
                        } else {
                            index += func_00283CF0(func_00283248(-delta[1], delta[0]) * 10.185916f) << 6;
                            delta[0] = -func_00282E80(D_001B5200.position, origin);
                        }
                    }
                    if (delta[2] > 0 && delta[0] > 0) {
                        index += func_00283CF0(func_00283248(delta[2], delta[0]) * 10.185916f);
                    } else if (delta[2] <= 0 && delta[0] > 0) {
                        index += 16;
                        if (delta[2] != 0) index += func_00283CF0(func_00283248(delta[0], -delta[2]) * 10.185916f);
                    } else if (delta[2] < 0 && delta[0] <= 0) {
                        index += 32;
                        if (delta[0] != 0) index += func_00283CF0(func_00283248(-delta[2], -delta[0]) * 10.185916f);
                    } else if (delta[2] >= 0 && delta[0] < 0) {
                        index += 48;
                        if (delta[2] != 0) index += func_00283CF0(func_00283248(-delta[0], delta[2]) * 10.185916f);
                    }
                    func_00282B50(D_001BADC0, ((OcclDirectional *)D_001B1708)->visibility[index], 128);
                } else {
                    previous = D_001B1718;
                    if (previous) {
                        func_00282B50(D_001BADC0, previous, 128);
                    } else {
                        func_00282A60(D_001BADC0, -1, 128);
                    }
                }
                break;
            }
            }
        }
    }
    D_001BADC0[127] |= 128;
}


void func_0027A9A0(void)
{
    if (D_001B1710 == 0)
        func_00282A60(D_001BADC0, -1, 0x80);
    else if (D_001B1710 == 2)
        func_0027A288();
}

/* InitViewContext: set the screen extent from the display size and the view's fixed scales. */
void func_0027A9F0(void)
{
    ScreenDimensions *dimensions = &D_001A6480;
    ScreenState *view = &D_001B9040;
    short width = dimensions->width;
    short height = dimensions->height;
    int half_width = width >> 1;
    int half_height = height >> 1;
    float half_height_f;

    D_001A7340.width = width;
    D_001A7340.height = height;
    D_001A7340.half_width = half_width;
    D_001A7340.half_height = half_height;
    D_001A7340.left = (2048 - half_width) << 4;
    D_001A7340.top = (2048 - half_height) << 4;
    D_001A7340.right = (half_width + 2048) << 4;
    D_001A7340.bottom = (half_height + 2048) << 4;

    view->fA0 = 32.0f;
    view->fA4 = 1048576.0f;
    view->fB0 = 0.62f;
    view->f200 = func_00283CE0(width) * 0.5f;
    half_height_f = func_00283CE0(dimensions->height) * 0.5f;
    view->f204 = half_height_f;
    view->f208 = view->f200 * 4.0f;
    view->f20C = half_height_f * 4.0f;
    view->f218 = 0.0f;
    view->f21C = 524288.0f;
    view->f228 = 255.0f;
    view->f22C = 0.0f;
}

/* ConfigureGraphicsProjection: InitViewContext for a given size and scale, with the four
   context values from the arguments, then func_0027AB40. */
void func_0027B2F8(int width, int height, float scale, float a, float b, float c, float d)
{
    ScreenState *context = &D_001B9040;
    int halfW = width >> 1;
    int halfH = height >> 1;
    float halfHeight;
    D_001A7340.width = width;
    D_001A7340.height = height;
    D_001A7340.half_width = halfW;
    D_001A7340.half_height = halfH;
    D_001A7340.left = (2048 - halfW) << 4;
    D_001A7340.top = (2048 - halfH) << 4;
    D_001A7340.right = (halfW + 2048) << 4;
    D_001A7340.bottom = (halfH + 2048) << 4;
    context->fB0 = scale;
    context->fA0 = 32.0f;
    context->fA4 = 1048576.0f;
    context->f200 = func_00283CE0(width) * 0.5f;
    halfHeight = func_00283CE0(height) * 0.5f;
    context->f204 = halfHeight;
    context->f208 = context->f200 * 4.0f;
    context->f20C = halfHeight * 4.0f;
    context->f218 = a;
    context->f21C = b;
    context->f228 = c;
    context->f22C = d;
    func_0027AB40();
}

/* The full-screen anti-aliasing buffer record behind the screen dimensions above: the
   display size at 0x150 and the storage size at 0x158. */
typedef struct {
    char disp_and_contexts[0x150];
    s16 display_width;
    s16 display_height;
    s16 psm;
    s16 fbp0;
    s16 storage_width;
    s16 storage_height;
} FsAaBuf;
#define FsAaBuffer (*(FsAaBuf *)&D_001A6480)

/* The drawing environment's GS register values, each followed by its register address. */
typedef struct {
    u64 pad0[2];
    u64 frame1;
    u64 pad18;
    u64 frame2;
    u64 pad28;
    u64 zbuf1;
    u64 pad38;
    u64 zbuf2;
    u64 pad48;
    u64 xyoffset1;
    u64 pad58;
    u64 xyoffset2;
    u64 pad68;
    u64 scissor1;
    u64 pad78;
    u64 scissor2;
} GsDrawEnvRegs;

typedef struct {
    char b[0x60];
} GsLoadImage;

extern GsDrawEnvRegs D_00139120;
extern u64 D_00139310;
extern u64 D_00139380;
extern unsigned char D_001BB000[];
extern int D_001A7B90 __attribute__((sda));
extern int D_001A7BB8 __attribute__((sda));
extern int D_001A72D0 __attribute__((sda));
extern int D_001A72D8 __attribute__((sda));
extern int D_001A72DC __attribute__((sda));
extern int D_001A72E0 __attribute__((sda));
extern int D_001A72E4 __attribute__((sda));
extern int D_001A72E8 __attribute__((sda));
extern int D_001A72EC __attribute__((sda));
extern int D_001A72F0 __attribute__((sda));
extern int D_001A72F4 __attribute__((sda));
extern void func_0011AEA0(int);
extern int func_001244B8(int, int);
extern void func_00284268(int, int, int, int, int, int);
extern void func_00284EA8(void);
extern void func_00284F40(int);
extern void func_00284E80(void);
extern int func_00126288(GsLoadImage *, s16, s16, s16, s16, s16, s16, s16);
extern int func_001265B0(GsLoadImage *, unsigned char *);

/* Adapted from RAC1 SetPalMode (GPL-3.0), with RAC2's mode selection, texture cursors
   and optional image clearing.
   Adapted from Lombyte's project (GPL-3.0): src/video/display/set_pal_mode.c, set_pal_mode. */
void func_0027B440(int clear) {
    GsLoadImage image;
    int n;
    int i;
    u64 zbuf;
    u64 frame;
    u64 scissor;
    s16 w;

    func_0011AEA0(0);
    if (D_001A7B90 != 0) {
        D_001A72E0 = 0x100000;
        D_001A72DC = 0x1E0000;
        D_001A72D8 = 0;
        D_001A72E4 = 0x2C0000;
        func_00284268(0x200, 0x1C0, 0x200, 0x200, 4, 0);
    } else if (D_001A7BB8 != 0) {
        D_001A72E0 = 0x118000;
        D_001A72DC = 0x1E8000;
        D_001A72D8 = 0;
        D_001A72E4 = 0x2C0000;
        func_00284268(0x200, 0x1A0, 0x280, 0x1C0, 0, 0);
    } else {
        D_001A72E0 = 0x118000;
        D_001A72DC = 0x1E8000;
        D_001A72D8 = 0;
        D_001A72E4 = 0x2C0000;
        func_00284268(0x200, 0x1A0, 0x200, 0x1C0, 0, 0);
    }
    D_001A72E8 = D_001A72E4;
    D_001A72EC = D_001A72E4 + 0x1000;
    D_001A72F0 = D_001A72E4 + 0x1400;
    D_001A72F4 = D_001A72E4 + 0x1800;
    w = FsAaBuffer.display_width;
    D_001A7340.width = w;
    D_001A7340.height = FsAaBuffer.display_height;
    D_001A7340.half_width = w >> 1;
    D_001A7340.half_height = D_001A7340.height >> 1;
    D_001A7340.left = (0x800 - D_001A7340.half_width) << 4;
    D_001A7340.top = (0x800 - D_001A7340.half_height) << 4;
    D_001A7340.right = (D_001A7340.half_width + 0x800) << 4;
    D_001A7340.bottom = (D_001A7340.half_height + 0x800) << 4;
    frame = (D_001A72DC >> 13) | ((u64)(D_001A7340.width >> 6) << 16);
    D_00139120.frame1 = frame;
    zbuf = (D_001A72E0 >> 13) | 0x1000000;
    D_00139120.frame2 = frame;
    D_00139120.xyoffset1 = D_001A7340.left | ((u64)D_001A7340.top << 32);
    D_00139120.zbuf1 = zbuf;
    D_00139120.zbuf2 = zbuf;
    D_00139120.xyoffset2 = D_001A7340.left | ((u64)D_001A7340.top << 32);
    scissor = ((u64)(D_001A7340.width - 1) << 16) | ((u64)(D_001A7340.height - 1) << 48);
    D_00139310 = zbuf;
    D_00139120.scissor1 = scissor;
    D_00139120.scissor2 = scissor;
    D_00139380 = zbuf | ((u64)0x8000 << 17);
    if (clear) {
        D_001A72D0 = D_001A72E4;
        D_001A72D4 = D_001A72E4;
        func_0011AEA0(0);
        func_001244B8(0, 0);
        func_0011AEA0(0);
        func_00284EA8();
        func_00284F40(0);
        func_0011AEA0(0);
        func_001244B8(0, 0);
        func_00284E80();
        func_00282A60(D_001BB000, 0, 0x1000);
        n = (FsAaBuffer.storage_width * FsAaBuffer.storage_height) >> 10;
        for (i = 0; i < n; i++) {
            func_00126288(&image, i << 4, 1, 0, 0, 0, 32, 32);
            func_0011AEA0(0);
            func_001265B0(&image, D_001BB000);
            func_001244B8(0, 0);
        }
    }
}
