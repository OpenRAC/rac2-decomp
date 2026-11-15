#include "names.h"
/* Rests on the redundant-insn rule of docs/build/compiler-notes.md (volatile asm): the last jump of the
   mode == 0 arm lands on the restore of $s0, across a qcopy. */

#include "common.h"

extern char g_hero_state[];
extern char ref_0030E8A8_00[];

extern void moby_get_facing_direction(char *, float *);
extern void FastVecSub(float *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(float *, float *, float);
extern float FastVecDot(float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int CollLine(float *, float *, int, int, int);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern void moby_move_and_collide(char *, float *, float, float, float, int);

/* Pushes a springy object down when the player stands on it and lets it bounce back up. Keeps it above the floor. */
void moby_spring_away_from_player(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *hero = g_hero_state;
    short flag = *(short *)(hero + 0x202);
    float up[4] __attribute__((aligned(16)));
    float toObject[4] __attribute__((aligned(16)));
    float sideOffset[4] __attribute__((aligned(16)));
    float alongUp[4] __attribute__((aligned(16)));
    float probeBelow[4] __attribute__((aligned(16)));
    float probeAbove[4] __attribute__((aligned(16)));
    float groundPoint[4] __attribute__((aligned(16)));
    float groundAlong[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float groundToObject[4] __attribute__((aligned(16)));
    float pushAmount;
    float projection;
    int mode;
    float heightAlong, sideDistance, step, groundGap, newSpeed;

    if (*(int *)(vars + 0x44) == 0 && flag == 0)
        return;
    moby_get_facing_direction(obj + 0x10, up);
    groundGap = 0.0f;
    FastVecSub(toObject, obj + 0x10, hero + 0x80);
    projection = FastVecDot(toObject, up);
    FastVecScale(alongUp, up, projection);
    FastVecSub(sideOffset, toObject, alongUp);
    heightAlong = FastVecLength(alongUp);
    sideDistance = FastVecLength(sideOffset);
    FastVecScale(probeBelow, up, -2.5f);
    FastVecAdd(probeBelow, obj + 0x10, probeBelow);
    FastVecScale(probeAbove, up, 0.5f);
    FastVecAdd(probeAbove, obj + 0x10, probeAbove);
    if (CollLine(probeAbove, probeBelow, 2, 0, 0)) {
        qcopy(groundPoint, ref_0030E8A8_00);
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        FastVecSub(push, groundPoint, obj + 0x10);
        projection = FastVecDot(push, up);
        FastVecScale(groundAlong, up, projection);
        groundGap = FastVecLength(groundAlong);
    }
    if (*(int *)(vars + 0x44) == 0) {
        if (!(sideDistance < 1.0f))
            return;
        if (!(heightAlong < 1.3f))
            return;
        *(int *)(vars + 0x44) = 1;
    }
    qcopy(push, sideOffset);
    pushAmount = sideDistance - 1.4f;
    if (pushAmount > 0.0f)
        pushAmount = 0.0f;
    if (flag == 0)
        pushAmount = 0.0f;
    step = 0.02f;
    math_spring_float_to_goal(&pushAmount, 0.0f, (float *)(vars + 0x48), step, 0.3f, 0.06666667f);
    if (pushAmount == 0.0f && *(float *)(vars + 0x48) == 0.0f && groundGap < step)
        *(int *)(vars + 0x44) = 0;
    if (sideDistance < *(float *)(vars + 0x48))
        *(float *)(vars + 0x48) = sideDistance;
    if (*(float *)(vars + 0x48) < sideDistance)
        vec_scale_to_length(push, push, *(float *)(vars + 0x48));
    moby_move_and_collide(obj, push, 0.5f, 0.4f, 0.0f, 0);
    if (mode == 0) {
        if (FastVecDot(groundAlong, up) > 0.0f) {
            qcopy(obj + 0x10, groundPoint);
            *(float *)(vars + 0x4C) = 0.0f;
        } else {
            newSpeed = *(float *)(vars + 0x4C) - 0.0066666668f;
            *(float *)(vars + 0x4C) = newSpeed;
            FastVecScale(push, up, newSpeed);
            FastVecAdd(obj + 0x10, push, obj + 0x10);
            FastVecSub(groundToObject, groundPoint, obj + 0x10);
            if (FastVecDot(groundToObject, up) > 0.0f) {
                qcopy(obj + 0x10, groundPoint);
                *(float *)(vars + 0x4C) = 0.0f;
            }
        }
    } else {
        *(float *)(vars + 0x4C) -= 0.0066666668f;
        FastVecScale(push, up, *(float *)(vars + 0x4C));
        FastVecAdd(obj + 0x10, push, obj + 0x10);
    }
}
