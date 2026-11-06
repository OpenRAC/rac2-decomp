/* func_PAL_L00_003FA3D0, the PAL copy of func_L00_003F5F90: the same C, where the sample count is an int scaled to 50 Hz (flags in config/cflags.txt). */
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
extern int D_L00_001B0998 __attribute__((sda));
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

void func_PAL_L00_003FA3D0(Actor *self)
{
    Slot *slots;
    Source *source;
    Vec m, dir, tmp;
    char *base;

    source = self->source;
    if (D_0018C0B4 == 0x1D) return;
    base = func_L00_0032A088(0xC04, source->id);
    slots = (Slot *)(base + *func_L00_0032A0B8(0xC04, source->id));
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
    slots[source->index].count = (D_L00_001B0998 * 5 + 2) / 6;
    slots[source->index].rate = 1.0f / slots[source->index].count;
    slots[source->index].t = 0;
    slots[source->index].u = 0;
    slots[source->index].flag = 1;
}
