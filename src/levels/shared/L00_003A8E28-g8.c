#include "include_asm.h"
#include "common.h"

/* Small-data sibling of L00_003A8E28.c: the body below reaches the level's
   globals through $gp (the file gets -G8 by its name, see config/cflags.txt). */

extern char D_L00_0023BB78[];

extern unsigned char D_L00_001AF810 __attribute__((sda));

extern unsigned char D_L00_001AF811 __attribute__((sda));

extern void func_2EDE88();

typedef int TI128 __attribute__((mode(TI)));

extern float D_L00_001AF7A4 __attribute__((sda));

extern void func_00283098(void *, void *, void *);

extern void func_00282CC0(void *, void *, void *);

/* Builds the local vector {scale, 0, 0, 1}, transforms its copy, then adds the object position. */
void func_L00_003ACC88(char *a0, char *a1)
{
    float other[4];
    float local[4];
    TI128 zero = 0;

    *(TI128 *)local = zero;
    local[0] = D_L00_001AF7A4;
    local[3] = 1.0f;
    *(TI128 *)other = *(TI128 *)local;
    func_00283098(other, other, a0 + 0xC0);
    func_00282CC0(a1, other, a0 + 0x10);
}

/* Resets the two slot cursors, then releases the 256-entry slot table. */
void func_L00_003B09F8(void)
{
    D_L00_001AF811 = 0;
    D_L00_001AF810 = 0;
    func_2EDE88(D_L00_0023BB78, 0x1C00);
}

typedef int Qword __attribute__((mode(TI)));

typedef struct {
    Qword pos;
    Qword a;
    Qword b;
    Qword c;
    Qword d;
    short flag;
    short count;
    float t;
    float u;
    float rate;
} TrailSlot;

typedef struct {
    char pad0[0x18];
    short index;
    short id;
} TrailSource;

typedef struct {
    char pad0[0x10];
    Qword pos;
    char pad20[0x48];
    TrailSource *source;
} TrailActor;

extern float D_L00_001AF760 __attribute__((sda));
extern float D_L00_001AF798 __attribute__((sda));
extern float D_L00_001AF774 __attribute__((sda));
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern int ref_L00_003A9000_00(void *);
extern void func_2EE3D0(void *, void *, float);
extern void func_2EE108(void *, void *, void *);

int func_L00_003A9000(TrailActor *self)
{
    TrailSource *source = self->source;
    char *base = func_L00_0032A088(0x5CB, source->id);
    char *data = base + *func_L00_0032A0B8(0x5CB, source->id);
    TrailSlot *slots = (TrailSlot *)data;
    Qword rot[1];

    if (slots[source->index].flag == 0)
        return 0;
    if (ref_L00_003A9000_00(&slots[source->index].count)) {
        slots[source->index].flag = 0;
        return 0;
    }
    qcopy_nc(&slots[source->index].b, &self->pos);
    slots[source->index].t += D_L00_001AF760;
    if (slots[source->index].t >= 4.0f)
        slots[source->index].t -= 4.0f;
    slots[source->index].u += D_L00_001AF798;
    if (slots[source->index].u >= 4.0f)
        slots[source->index].u -= 4.0f;
    func_2EE3D0(rot, source, D_L00_001AF774 * 0.016666668f);
    func_2EE108(&slots[source->index], &slots[source->index], rot);
    func_2EE108(&slots[source->index].a, &slots[source->index].a, rot);
    return 1;
}
