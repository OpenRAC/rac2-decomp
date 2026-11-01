#include "include_asm.h"

#include "common.h"
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
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

extern float D_PAL_001B09B8 __attribute__((sda));
extern float D_PAL_001B09F0 __attribute__((sda));
extern float D_PAL_001B09CC __attribute__((sda));

int func_PAL_L00_003FA5C8(TrailActor *self)
{
    TrailSource *source = self->source;
    char *base = func_L00_0032A088(0xC04, source->id);
    char *data = base + *func_L00_0032A0B8(0xC04, source->id);
    TrailSlot *slots = (TrailSlot *)data;
    Qword rot[1];

    if (slots[source->index].flag == 0)
        return 0;
    if (ref_L00_003A9000_00(&slots[source->index].count)) {
        slots[source->index].flag = 0;
        return 0;
    }
    qcopy_nc(&slots[source->index].b, &self->pos);
    slots[source->index].t += D_PAL_001B09B8;
    if (slots[source->index].t >= 4.0f)
        slots[source->index].t -= 4.0f;
    slots[source->index].u += D_PAL_001B09F0;
    if (slots[source->index].u >= 4.0f)
        slots[source->index].u -= 4.0f;
    func_00282F20(rot, source, D_PAL_001B09CC * 0.020000001f);
    func_00282CC0(&slots[source->index], &slots[source->index], rot);
    func_00282CC0(&slots[source->index].a, &slots[source->index].a, rot);
    return 1;
}


