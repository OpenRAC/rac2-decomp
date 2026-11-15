#include "common.h"

/* Resolve up to eight movement/collision steps, preserving the input position.
 * Shared quadword helpers express the real position snapshot and controller clear;
 * the four-float views include the complete sixteen-byte vector writes.
 */

typedef int Quad_002B5678 __attribute__((mode(TI)));
typedef union { Quad_002B5678 q; float f[4]; } Vec4Q_002B5678;

typedef struct {
    char pad0[0x10];
    float pos[4];                       /* 0x10 */
} Self_002B5678;

typedef struct {
    char pad0[0x28];
    float f28;                          /* 0x28 */
    char pad1[0x60 - 0x2C];
    Quad_002B5678 q60;                  /* 0x60: cleared */
    char out70[0x10];                   /* 0x70: movement of this step (FastVecSub output) */
    int w80;                            /* 0x80 */
    int w84;                            /* 0x84: cleared */
    char pad2[0x90 - 0x88];
    float f90;                          /* 0x90 */
    char pad3[0xA0 - 0x94];
    float vel[4];                       /* 0xA0 */

    float speed;                        /* 0xB0 */
} Ctl_002B5678;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_00282F70(void *, void *, float);
extern int func_00282948(void *);
extern int func_002B5D38(void *, void *);
extern int func_002B5E48(void *, void *);

/* Retail callers also pass a fourth scratch pointer. This body does not read it;
 * keep the slot explicit so its C interface agrees with those callers.
 */
void func_002B5678(Self_002B5678 *self, Ctl_002B5678 *ctl, float *target, void *unused_output)
{
    Vec4Q_002B5678 saved;
    Quad_002B5678 *position = (Quad_002B5678 *)self->pos;
    int changed, i, r;
    float len;

    FastVecAdd(position, position, ctl->vel);
    qcopy(&saved, position);
    ctl->w84 = 0;
    qzero(&ctl->q60);
    changed = 0;
    for (i = 0; i < 8; i++) {
        r = func_002B5D38(self, ctl);
        r |= func_002B5E48(self, ctl);
        changed |= r;
        if (r == 0)
            break;
    }
    if (changed) {
        FastVecSub(ctl->vel, self->pos, target);
        len = vec_length_xy(ctl->vel);
        if (ctl->speed < len)
            func_00282F70(ctl->vel, ctl->vel, ctl->speed);
        else
            ctl->speed = len;
        if (self->pos[2] <= ctl->f90) {
            if (self->pos[2] < target[2])
                self->pos[2] = target[2];
            if (ctl->vel[2] < 0.0f)
                ctl->vel[2] = 0.0f;
        }
        if (ctl->speed < ctl->f28 * 0.5f)
            ctl->w80 += 1;
        else
            func_00282948(&ctl->w80);
    } else {
        func_00282948(&ctl->w80);
    }
    FastVecSub(ctl->out70, self->pos, &saved);
}
