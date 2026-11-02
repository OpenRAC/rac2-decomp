/* functional: high. From the near-miss draft (nonmatching/game/func_003166C8.c, register allocation and frame size only), with retail's lq/sq vector copies (qcopy) written as four-word copies. Same reads, writes and calls with the same arguments, in retail's order; -(x) * a is retail's neg.s then mul.s, bit for bit. */

#include "common.h"

/* One of the three 0xA0-byte effect slots of D_0022AA10 (func_00316400 fills them). */
typedef struct {
    float offset[4], rotation[4], origin[4], position[4];
    float angle[3], speed[3], amplitude[3];
    float angle2[3], speed2[3], amplitude2[3];
    int fade;      /* 0x88 */
    void *owner;   /* 0x8C */
    char *object;  /* 0x90 */
    int timer;     /* 0x94 */
    int duration;  /* 0x98 */
    int expired;   /* 0x9C */
} PoolEffect;

extern PoolEffect D_0022AA10[3];
extern float D_001B2520[4];
extern char *func_002AB1F0(void *);
extern void func_002B00B0(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00283CE0(int);
extern int func_00282948(int *);

/* Updates owner's lock-on effect slots: each slot's origin is set to D_001B2520, its wobble angles advance (twice as
   fast while its timer runs), the offset and rotation are the angles' sines/cosines times the amplitudes, and with
   an object attached the position moves from the object (or its scaled attachment point) toward the origin as the
   timer runs out. When the timer ends the slot is marked expired; when the fade timer then ends, it is freed. */
void func_003166C8(void *owner)
{
    int i, k;
    PoolEffect *p;
    char *info;
    float *position;
    float local[4] __attribute__((aligned(16)));
    float ratio;

    for (i = 0; i < 3; i++) {
        p = &D_0022AA10[i];
        if (p->owner != owner) {
            continue;
        }
        for (k = 0; k < 4; k++) {
            p->origin[k] = D_001B2520[k];
        }
        if (p->timer != 0) {
            p->angle[0] = func_00283B98(p->angle[0], p->speed[0] * 100.0f);
            p->angle[1] = func_00283B98(p->angle[1], p->speed[1] * 100.0f);
            p->angle[2] = func_00283B98(p->angle[2], p->speed[2] * 100.0f);
            p->angle2[0] = func_00283B98(p->angle2[0], p->speed2[0] * 100.0f);
            p->angle2[1] = func_00283B98(p->angle2[1], p->speed2[1] * 100.0f);
            p->angle2[2] = func_00283B98(p->angle2[2], p->speed2[2] * 100.0f);
        } else {
            p->angle[0] = func_00283B98(p->angle[0], p->speed[0] * 50.0f);
            p->angle[1] = func_00283B98(p->angle[1], p->speed[1] * 50.0f);
            p->angle[2] = func_00283B98(p->angle[2], p->speed[2] * 50.0f);
            p->angle2[0] = func_00283B98(p->angle2[0], p->speed2[0] * 50.0f);
            p->angle2[1] = func_00283B98(p->angle2[1], p->speed2[1] * 50.0f);
            p->angle2[2] = func_00283B98(p->angle2[2], p->speed2[2] * 50.0f);
        }
        p->offset[0] = func_00283180(p->angle[0]) * p->amplitude[0];
        p->offset[1] = func_00283198(p->angle[1]) * p->amplitude[1];
        p->offset[2] = -func_00283198(p->angle[2]) * p->amplitude[2];
        p->rotation[0] = func_00283180(p->angle2[0]) * p->amplitude2[0];
        p->rotation[1] = func_00283198(p->angle2[1]) * p->amplitude2[1];
        p->rotation[2] = -func_00283198(p->angle2[2]) * p->amplitude2[2];
        if (p->object != 0) {
            info = func_002AB1F0(p->object);
            if (info != 0) {
                func_002B00B0(p->object, local, 1);
                func_00282D30(local, local, *(float *)(info + 16));
                func_00282CC0(p->position, local, p->object + 16);
            } else {
                for (k = 0; k < 4; k++) {
                    p->position[k] = ((float *)(p->object + 16))[k];
                }
            }
            position = p->position;
            ratio = func_00283CE0(p->timer);
            ratio /= func_00283CE0(p->duration);
            func_00282D08(position, p->origin, position, 1.0f - ratio);
        }
        if (func_00282948(&p->timer) != 0) {
            if (p->expired == 0) {
                p->expired = 1;
            }
            if (func_00282948(&p->fade) != 0) {
                p->owner = 0;
            }
        }
    }
}
