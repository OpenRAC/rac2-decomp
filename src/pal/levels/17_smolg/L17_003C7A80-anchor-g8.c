#include "common.h"

/* func_PAL_L17_003C7A80, the PAL copy of func_L17_003C3C50: the same C, where the periods
   D * 60 become the 50 Hz (D * 300 + 2) / 6 and the cooldown 30 becomes 25.
   Built with -G8 and -frac2-gcse-unsplit-edges: gcse inserts the zero vector's shared %hi at
   the end of the speed test's block, as GCC 2.95 does, instead of splitting the edge to
   check_clear (config/cflags.txt). */

typedef unsigned int MotionQuad __attribute__((mode(TI)));
typedef union { MotionQuad q; float f[4]; } MotionVec;
typedef struct { MotionVec header, position; } MotionAnchor;
typedef struct { unsigned char pad[0xBC], marked, tail[0x43]; } MotionMoby;
typedef struct {
    char pad[0x3E];
    unsigned short flags;
    char gap[0x50];
    int source0, source1, activeState, unused;
    int destination0, destination1;
    float timer, delay;
    int once0, once1, blocked, cooldown;
    float speed;
    int direction;
} MotionState;

extern MotionAnchor *D_L17_001FE880[];
/* One macro pointer: a GP load in case 1's delay slots, absolute in case 4. */
extern char *D_L17_001B2C1C MACRO_ADDR;
extern float D_L17_001B0240 __attribute__((sda)), D_L17_001B0244 __attribute__((sda));
extern MotionQuad D_00189EA0[];
extern int func_00282948(void *);
extern void func_PAL_L17_003C7908(void *, void *, void *);
extern int func_L17_003C3A00(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Moves the object between two anchors when their source mobys are cleared, waiting at
   the far anchor, and stops while a forward or backward probe is blocked. */
void func_PAL_L17_003C7A80(unsigned char *obj)
{
    struct { MotionVec old, delta, probe1, probe2; } frame;
    MotionState *s = *(MotionState **)(obj + 0x68);
    char *target;
    MotionAnchor *anchor;

    frame.old.q = *(MotionQuad *)(obj + 0x10);
    func_00282948(&s->cooldown);
    switch (obj[0x20]) {
    case 0:
        s->speed = 0;
        s->blocked = 0;
        s->cooldown = 0;
        obj[0x20] = 1;
        s->flags |= 9;
        if (s->destination0 != -1)
            *(MotionQuad *)(obj + 0x10) = D_L17_001FE880[s->destination0]->position.q;
        else if (s->destination1 != -1)
            *(MotionQuad *)(obj + 0x10) = D_L17_001FE880[s->destination1]->position.q;
        break;
    case 1:
        if (s->source0 != -1 && s->destination0 != -1) {
            target = D_L17_001B2C1C + (s->source0 << 8);
            if (!target || (unsigned char)target[0x20] == 254 || (unsigned char)target[0x20] == 253
                || (unsigned char)target[0x20] == s->activeState) {
                s->timer = 0;
                s->direction = 0;
                obj[0x20] = 2;
                break;
            }
        }
        if (s->destination0 == -1 && s->source1 != -1 && s->destination1 != -1) {
            target = D_L17_001B2C1C + (s->source1 << 8);
            if (!target || (unsigned char)target[0x20] == 254 || (unsigned char)target[0x20] == 253
                || (unsigned char)target[0x20] == s->activeState) {
                s->timer = 0;
                s->direction = 1;
                obj[0x20] = 2;
            }
        }
        break;
    case 2:
        if (!s->blocked)
            s->timer += 1.0f;
        if (s->timer >= (D_L17_001B0240 * 300.0f + 2.0f) * 0.16666667f)
            s->timer = (D_L17_001B0240 * 300.0f + 2.0f) * 0.16666667f;
        if (s->direction == 0)
            anchor = D_L17_001FE880[s->destination0];
        else
            anchor = D_L17_001FE880[s->destination1];
        func_PAL_L17_003C7908(obj, anchor, &frame.old);
        if (s->timer >= (D_L17_001B0240 * 300.0f + 2.0f) * 0.16666667f) {
            if (s->once0 && !s->direction) {
                s->destination0 = -1;
                obj[0x20] = 1;
            } else if (s->once1 && s->direction == 1) {
                s->destination1 = -1;
                obj[0x20] = 1;
            } else {
                obj[0x20] = 4;
                s->delay = 0;
            }
        }
        break;
    case 3:
        if (!s->blocked)
            s->timer -= 1.0f;
        if (s->timer <= 0.0f)
            s->timer = 0.0f;
        if (s->direction == 0)
            anchor = D_L17_001FE880[s->destination0];
        else
            anchor = D_L17_001FE880[s->destination1];
        func_PAL_L17_003C7908(obj, anchor, &frame.old);
        if (s->timer <= 0.0f)
            obj[0x20] = 1;
        break;
    case 4:
        s->delay += 1.0f;
        if (s->delay >= (D_L17_001B0244 * 300.0f + 2.0f) * 0.16666667f) {
            MotionMoby *m;
            obj[0x20] = 3;
            if (s->direction == 0)
                m = (MotionMoby *)((s->source0 << 8) + (unsigned int)D_L17_001B2C1C);
            else if (s->direction == 1)
                m = (MotionMoby *)((s->source1 << 8) + (unsigned int)D_L17_001B2C1C);
            else
                break;
            m->marked = 0;
        }
        break;
    }
    if (s->cooldown) {
        s->blocked = 1;
    } else if (s->speed < 0.0f) {
        frame.probe1.q = D_00189EA0[0];
        if (func_L17_003C3A00(obj, &frame.probe1)) {
            if (!s->cooldown)
                s->cooldown = 25;
            s->blocked = 1;
        } else
            goto check_clear;
    } else {
check_clear:
        frame.probe2.q = D_00189EA0[0];
        if (!func_L17_003C3A00(obj, &frame.probe2))
            s->blocked = 0;
    }
    func_00282CF0(&frame.delta, obj + 0x10, &frame.old);
    func_002AD6F0((char *)s + 0x50, &frame.delta, obj + 0xF0, obj + 0xF0);
}
