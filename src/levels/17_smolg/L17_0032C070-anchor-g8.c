#include "common.h"

/* Built with -G8 and -frac2-gcse-unsplit-edges: gcse inserts the zero vector's shared %hi at
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
extern void func_L17_003C3AF0(void *, void *, void *);
extern int func_L17_003C3A00(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Moves the object between two anchors when their source mobys are cleared, waiting at
   the far anchor, and stops while a forward or backward probe is blocked. */
void func_L17_003C3C50(unsigned char *obj)
{
    struct { MotionVec old, delta, probe1, probe2; } frame;
    MotionState *vars = *(MotionState **)(obj + 0x68);
    char *target;
    MotionAnchor *anchor;

    frame.old.q = *(MotionQuad *)(obj + 0x10);
    FastFloatHelperD(&vars->cooldown);
    switch (obj[0x20]) {
    case 0:
        vars->speed = 0;
        vars->blocked = 0;
        vars->cooldown = 0;
        obj[0x20] = 1;
        vars->flags |= 9;
        if (vars->destination0 != -1)
            *(MotionQuad *)(obj + 0x10) = gPathTable_L17[vars->destination0]->position.q;
        else if (vars->destination1 != -1)
            *(MotionQuad *)(obj + 0x10) = gPathTable_L17[vars->destination1]->position.q;
        break;
    case 1:
        if (vars->source0 != -1 && vars->destination0 != -1) {
            target = gMobyPool_L17 + (vars->source0 << 8);
            if (!target || (unsigned char)target[0x20] == 254 || (unsigned char)target[0x20] == 253
                || (unsigned char)target[0x20] == vars->activeState) {
                vars->timer = 0;
                vars->direction = 0;
                obj[0x20] = 2;
                break;
            }
        }
        if (vars->destination0 == -1 && vars->source1 != -1 && vars->destination1 != -1) {
            target = gMobyPool_L17 + (vars->source1 << 8);
            if (!target || (unsigned char)target[0x20] == 254 || (unsigned char)target[0x20] == 253
                || (unsigned char)target[0x20] == vars->activeState) {
                vars->timer = 0;
                vars->direction = 1;
                obj[0x20] = 2;
            }
        }
        break;
    case 2:
        if (!vars->blocked)
            vars->timer += 1.0f;
        if (vars->timer >= D_L17_001B0240 * 60.0f)
            vars->timer = D_L17_001B0240 * 60.0f;
        if (vars->direction == 0)
            anchor = gPathTable_L17[vars->destination0];
        else
            anchor = gPathTable_L17[vars->destination1];
        PlaceObjectOnPathByTimer(obj, anchor, &frame.old);
        if (vars->timer >= D_L17_001B0240 * 60.0f) {
            if (vars->once0 && !vars->direction) {
                vars->destination0 = -1;
                obj[0x20] = 1;
            } else if (vars->once1 && vars->direction == 1) {
                vars->destination1 = -1;
                obj[0x20] = 1;
            } else {
                obj[0x20] = 4;
                vars->delay = 0;
            }
        }
        break;
    case 3:
        if (!vars->blocked)
            vars->timer -= 1.0f;
        if (vars->timer <= 0.0f)
            vars->timer = 0.0f;
        if (vars->direction == 0)
            anchor = gPathTable_L17[vars->destination0];
        else
            anchor = gPathTable_L17[vars->destination1];
        PlaceObjectOnPathByTimer(obj, anchor, &frame.old);
        if (vars->timer <= 0.0f)
            obj[0x20] = 1;
        break;
    case 4:
        vars->delay += 1.0f;
        if (vars->delay >= D_L17_001B0244 * 60.0f) {
            MotionMoby *sourceMoby;
            obj[0x20] = 3;
            if (vars->direction == 0)
                sourceMoby = (MotionMoby *)((vars->source0 << 8) + (unsigned int)gMobyPool_L17);
            else if (vars->direction == 1)
                sourceMoby = (MotionMoby *)((vars->source1 << 8) + (unsigned int)gMobyPool_L17);
            else
                break;
            sourceMoby->marked = 0;
        }
        break;
    }
    if (vars->cooldown) {
        vars->blocked = 1;
    } else if (vars->speed < 0.0f) {
        frame.probe1.q = gHeroPosition[0];
        if (IsPointJustBelowObject(obj, &frame.probe1)) {
            if (!vars->cooldown)
                vars->cooldown = 30;
            vars->blocked = 1;
        } else
            goto check_clear;
    } else {
check_clear:
        frame.probe2.q = gHeroPosition[0];
        if (!IsPointJustBelowObject(obj, &frame.probe2))
            vars->blocked = 0;
    }
    FastVecSub(&frame.delta, obj + 0x10, &frame.old);
    CombineTransformsAndStore((char *)vars + 0x50, &frame.delta, obj + 0xF0, obj + 0xF0);
}
