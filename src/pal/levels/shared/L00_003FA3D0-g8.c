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
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern int ref_L00_003A9000_00(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

extern float D_PAL_001B09B8 __attribute__((sda));
extern float D_PAL_001B09F0 __attribute__((sda));
extern float D_PAL_001B09CC __attribute__((sda));

int func_PAL_L00_003FA5C8(TrailActor *self)
{
    TrailSource *source = self->source;
    char *base = level_get_slot_body(0xC04, source->id);
    char *data = base + *level_get_slot_header(0xC04, source->id);
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
    vec_scale_to_length(rot, source, D_PAL_001B09CC * 0.020000001f);
    FastVecAdd(&slots[source->index], &slots[source->index], rot);
    FastVecAdd(&slots[source->index].a, &slots[source->index].a, rot);
    return 1;
}


