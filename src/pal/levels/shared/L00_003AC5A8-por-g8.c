/* func_PAL_L00_003AC5A8, the PAL copy of func_L00_003A8E28: the same C, where the sample count is an int scaled to 50 Hz (flags in config/cflags.txt). */
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

extern int g_game_mode __attribute__((nosda));
extern int g_hero_locked_flag MACRO_ADDR;
extern int g_trail_sample_count __attribute__((sda));
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

/* Starts a new trail slot for a moby: builds its axes from the source direction and the camera (PAL: sample count at 50 Hz). */
void trail_store_sample_pal(Actor *self)
{
    Slot *slots;
    Source *source;
    Vec m, dir, tmp;
    char *base;

    source = self->source;
    if (g_game_mode == 0x1D) return;
    base = level_get_slot_body(0x5CB, source->id);
    slots = (Slot *)(base + *level_get_slot_header(0x5CB, source->id));
    vec_scale_to_length(&m, source, 1.0f);
    dir.q = 0;
    dir.f[2] = 1.0f;
    dir.f[3] = 1.0f;
    if (g_hero_locked_flag) cam_compute_view_direction(&self->pos, &dir, 1);
    FastVecCross(&tmp, &m, &dir);
    vec_scale_to_length(&tmp, &tmp, 1.0f);
    FastVecCross(&slots[source->index].d, &tmp, &m);
    qcopy_nc(&slots[source->index].c, &m);
    qcopy_nc(&slots[source->index].pos, &self->pos);
    FastVecAdd(&slots[source->index].a, &self->pos, source);
    qcopy_nc(&slots[source->index].b, &slots[source->index].a);
    slots[source->index].count = (g_trail_sample_count * 5 + 2) / 6;
    slots[source->index].rate = 1.0f / slots[source->index].count;
    slots[source->index].t = 0;
    slots[source->index].u = 0;
    slots[source->index].flag = 1;
}
