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
extern float g_trail_time_step __attribute__((sda));
extern float g_trail_u_scroll_step __attribute__((sda));
extern float g_trail_rotation_rate __attribute__((sda));
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern int ref_L00_003A9000_00(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

extern float g_slot_t_increment __attribute__((sda));
extern float g_slot_u_increment __attribute__((sda));
extern float g_vaporizer_trail_step_speed __attribute__((sda));

/* Advances one vaporizer trail sample each frame: scrolls its texture coordinates and moves it along its direction, and frees it when it has expired (PAL: 50 Hz steps). */
int vaporizer_bolt_update_trail_sample_pal(TrailActor *self)
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
    slots[source->index].t += g_slot_t_increment;
    if (slots[source->index].t >= 4.0f)
        slots[source->index].t -= 4.0f;
    slots[source->index].u += g_slot_u_increment;
    if (slots[source->index].u >= 4.0f)
        slots[source->index].u -= 4.0f;
    vec_scale_to_length(rot, source, g_vaporizer_trail_step_speed * 0.020000001f);
    FastVecAdd(&slots[source->index], &slots[source->index], rot);
    FastVecAdd(&slots[source->index].a, &slots[source->index].a, rot);
    return 1;
}


