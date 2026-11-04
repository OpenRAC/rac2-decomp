/* func_L00_003A8E28: store a fresh trail sample in the source's slot (flags in config/cflags.txt). */
#include "common.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } Vec;

typedef struct {
    Vec pos;            /* 0x00 */
    Vec a;              /* 0x10 */
    Vec b;              /* 0x20 */
    Vec c;              /* 0x30 */
    Vec d;              /* 0x40 */
    short flag;         /* 0x50 */
    short count;        /* 0x52 */
    float t;            /* 0x54 */
    float u;            /* 0x58 */
    float rate;         /* 0x5C */
} Slot;

typedef struct {
    char pad0[0x18];
    short index;        /* 0x18 */
    short id;           /* 0x1A */
} Source;

typedef struct {
    char pad0[0x10];
    Vec pos;            /* 0x10 */
    char pad20[0x48];
    Source *source;     /* 0x68 */
} Actor;

extern int D_0018C0B4 __attribute__((nosda));
extern int D_L00_001A8FF0 MACRO_ADDR;
extern short D_L00_001AF770 __attribute__((sda));
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

void func_L00_003A8E28(Actor *self)
{
    Slot *slots;
    Source *source;
    Vec m, dir, tmp;
    char *base;

    source = self->source;
    if (D_0018C0B4 == 0x1D) return;
    base = func_L00_0032A088(0x5CB, source->id);
    slots = (Slot *)(base + *func_L00_0032A0B8(0x5CB, source->id));
    func_00282F20(&m, source, 1.0f);
    dir.q = 0;
    dir.f[2] = 1.0f;
    dir.f[3] = 1.0f;
    if (D_L00_001A8FF0) func_002AFFD8(&self->pos, &dir, 1);
    func_00282DD8(&tmp, &m, &dir);
    func_00282F20(&tmp, &tmp, 1.0f);
    func_00282DD8(&slots[source->index].d, &tmp, &m);
    qcopy_nc(&slots[source->index].c, &m);
    qcopy_nc(&slots[source->index].pos, &self->pos);
    func_00282CC0(&slots[source->index].a, &self->pos, source);
    qcopy_nc(&slots[source->index].b, &slots[source->index].a);
    slots[source->index].count = D_L00_001AF770;
    slots[source->index].rate = 1.0f / slots[source->index].count;
    slots[source->index].t = 0;
    slots[source->index].u = 0;
    slots[source->index].flag = 1;
}

/* func_L00_003B14D0: a burst of particles and glows where a consumed trail
 * group ends (flags in config/cflags.txt: the zeroed vectors are por/sq). */
typedef struct { float x, y, z, w; } Vec16_Fc936841d;
typedef int EffectQuad __attribute__((mode(TI)));
typedef struct { char pad[0x2290]; int owner; } EffectContext;
typedef struct { unsigned char pad[0x23]; unsigned char index; } EffectSelector;
typedef struct { unsigned int tag; unsigned char enabled; unsigned char tail[0xDB]; } EffectMaterial;
typedef struct { int v[6]; } EffectSix;

extern EffectContext D_00189E20 __attribute__((nosda));
extern EffectSelector D_00139568 __attribute__((nosda));
extern EffectMaterial D_L00_00262570[] __attribute__((nosda));
extern char D_L00_001C3280[] __attribute__((nosda));
extern char D_L00_001B8DC0[] __attribute__((nosda));
extern EffectSix D_L00_001AF858 __attribute__((nosda));
extern EffectSix D_L00_001AF870 __attribute__((nosda));

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_00277F48(void *, int, int, int, float);
extern void func_002A9850(int, void *, void *, int, int, int, int, int, float, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002AAFA0(unsigned int, int);
extern void func_002AAF40(int *, int *, int *, int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, float, int, int);
extern char *func_L00_003A0DA0(int, void *, void *, int, unsigned char, unsigned char,
                               unsigned char, unsigned char, float);

void func_L00_003B14D0(float x, float y, float z)
{
    Vec16_Fc936841d p, v;
    Vec16_Fc936841d delta;
    EffectSix a, b;
    int c0, c1, c2, r, g, blue;
    /* The initial value only changes gcse's table size, which orders the three
       RGB pointer spills as retail has them; flow deletes the store. */
    int n = 0, ca, cb, t0, t1;
    float distance, fade, speed, one;

    *(EffectQuad *)&p = 0;
    p.x = x;
    p.y = y;
    p.z = z;
    n = func_00277F48(&p, 16, D_00189E20.owner, 0, 3.0f);
    one = 1.0f;
    func_002A9850(D_00189E20.owner, &p, D_L00_001C3280, n, 0, 0x830000, 2, 1, 8.0f, one, one);
    *(EffectQuad *)&v = 0;
    v.z = 1.0f / 30.0f;
    func_00282CF0(&delta, D_L00_001B8DC0, &p);
    distance = func_00282DF0(&delta);
    n = distance < 6.0f ? func_00283CF0(distance) + 1 : 4;
    fade = 0.0f;
    if (distance < 7.0f)
        fade = 7.0f - distance;
    {
        int count;
        for (count = 0; count < n; count++) {
            speed = func_002A7878(8.0f, 10.0f) * (1.0f / 60.0f);
            speed -= fade * (1.0f / 60.0f);
            a = D_L00_001AF858;
            b = D_L00_001AF870;
            {
                int choice = func_002A77E0(6);
                EffectMaterial *entry = D_L00_00262570 + D_00139568.index;
                ca = func_002AAFA0(a.v[choice], entry->enabled != 0);
                choice = func_002A77E0(6);
                entry = D_L00_00262570 + D_00139568.index;
                cb = func_002AAFA0(b.v[choice], entry->enabled != 0);
            }
            t0 = func_002A7820(15, 20);
            t1 = func_002A7820(25, 30);
            func_002BBCB0(&p, &v, ca, cb, 400000.0f, t0, t1, speed, 0, 0);
        }
    }
    if (distance > 9.0f) {
        func_L00_003A0DA0(D_00189E20.owner, &p, &v, 15, 127, 127, 127, 32, one * 4.0f);
        r = 127;
        g = 32;
        blue = 0;
        func_002AAF40(&r, &g, &blue, D_L00_00262570[D_00139568.index].enabled != 0);
        func_L00_003A0DA0(D_00189E20.owner, &p, &v, 24, r, g, blue, 32, one * 4.0f);
    }
    c0 = 127;
    c1 = 63;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 20, c0, c1, c2, 48, one * 4.0f);
    c0 = 96;
    c1 = 16;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 27, c0, c1, c2, 64, one * 3.5f);
    c0 = 32;
    c1 = 0;
    c2 = 0;
    func_002AAF40(&c0, &c1, &c2, D_L00_00262570[D_00139568.index].enabled != 0);
    func_L00_003A0DA0(D_00189E20.owner, &p, &v, 29, c0, c1, c2, 32, one * 3.0f);
}
