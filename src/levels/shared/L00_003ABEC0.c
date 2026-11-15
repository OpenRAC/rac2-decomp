/* func_L00_003ABEC0 (retail begins at 0x003ABEC8 in level 00; the catalogue keeps the old name).
   Own unit, `-O2 -G0 -ffunction-sections -g`: -g gives the nop pair before each div.s, and
   D_L00_001B1FB0 uses the `.sdata` macro form so its `la` stays out of the bounds checks' slots.
   The out-of-arena test carries its own copy of the explosion code; jump2's cross-jumping
   later points those branches at the copy after the bounce block, so at sched2 the bounce
   join and the explosion are one block (retail's mov.s-first join and beqz slot). */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { char pad[0x18]; char *hit; int count; Vector point; char gap[0x10]; Vector normal; } Collision;
/* What the shot hands the collision test and its target: direction, owner and damage. */
typedef struct {
    Vector direction;
    char *owner;
    int flags;
    unsigned char kind;
    unsigned char one;
    unsigned short id;
    float damage;
    int count;
    int pad[3];
} ShotInfo;
typedef struct { char pad[4]; unsigned char piercing; char pad5[0x6B]; float damage; char tail[0x6C]; } Material;

extern Collision D_L00_001BF200;
extern Vector D_L00_0023B710[][4];
extern Material D_L00_00262570[];
extern unsigned short D_L00_001B1FB0[] MACRO_ADDR;
extern char D_L00_001B8DC0[];
extern unsigned char D_00139568[];
extern char *D_0018C0B0;
extern char D_00189EA0[];
extern int func_002761F8(void *, void *, int, void *, void *);
/* func_L00_002E6EF8 in most levels; the callee differs in levels 08, 09, 19 and 30. */
extern void ref_L00_003ABEC0_00(void *, void *);
extern int func_00282978(void *);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_002831B0(float);
extern void func_0029F338(void *);
extern float func_002A89A8(void *, int, float);
extern void func_002A8E20(void *, void *);
extern char *func_002AB1F0(char *);
extern void func_002AB668(void *, void *, float);
extern void func_002ACAD0(void *, unsigned short *);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002FEE50(int);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_L00_003AC8E8(char *, void *, char *);
extern void func_L00_003ACA60(char *, void *);
extern void func_L00_003ACC88(char *, void *);
extern void func_L00_003ACCF8(void);
extern void func_0032D758(void *, int, int);
extern void func_0032DA58(char *, char *, void *, float);

/* A homing shot: follows its target (turning at most as far as its speed allows), records
   its path, tests the step for a hit and explodes on contact, out of the arena or too far
   from the hero. */
void func_L00_003ABEC0(char *object)
{
    Vector start;
    Vector forward;
    Vector aim;
    Vector step;
    Vector delta;
    Vector lead;
    Vector offset;
    union {
        struct { Vector axis; Vector side; Vector turn; } t;
        ShotInfo shot;
    } u;
    Vector up;
    Vector normal;
    char *state;
    char *target;
    char *info;
    char *owner;
    int locked;
    float distance, length, angle;
    unsigned char kind;
    Collision *hit;
    int bounce;

    owner = 0;
    state = *(char **)(object + 0x68);
    target = *(char **)(state + 0x10);
    qcopy(start, object + 0x10);
    func_002AFFD8(object + 0x10, forward, 1);
    if (target != 0) {
        info = func_002AB1F0(target);
        kind = *(unsigned char *)(target + 0x20);
        if (kind == 0xFE || (kind == 0xFD || (info != 0 && *(float *)info <= 0.0f))) {
            *(char **)(state + 0x10) = 0;
            target = 0;
        } else {
            qcopy(aim, target + 0x10);
            if (info != 0) {
                FastVecScale(step, target + 0xE0, *(float *)(info + 0x10));
                FastVecAdd(aim, aim, step);
            }
        }
    }
    locked = 0;
    if (target != 0 && *(short *)(state + 0x24) < 0x127 && *(signed char *)(target + 0x20) >= 0
        && *(unsigned char *)(state + 0x26) != 0) {
        step[0] = *(float *)(state + 0x0);
        step[1] = *(float *)(state + 0x4);
        step[2] = *(float *)(state + 0x8);
        step[3] = 0.0f;
        FastVecSub(delta, aim, step);
        distance = FastVecLength(delta);
        FastVecAdd(lead, aim, state + 0x40);
        FastVecSub(offset, object + 0x10, lead);
        length = FastVecLength(offset);
        if (length != 0.0f && distance != 0.0f) {
            angle = FastVecDot(offset, delta);
            angle = 1.5707964f - func_002831B0(angle / (length * distance));
            FastVecCross(u.t.axis, delta, offset);
            FastVecCross(u.t.side, delta, u.t.axis);
            if (FastVecDot(offset, u.t.side) < 0.0f) {
                angle = -angle;
            }
            length = distance / *(float *)(state + 0x18);
            angle = length * func_00283198(angle);
            if (func_00282C48(angle) > 100.0f) {
                angle = 0.0f;
            }
            while (angle > 1.0f) {
                angle -= 1.0f;
            }
            while (angle < -1.0f) {
                angle += 1.0f;
            }
            angle = func_002831B0(angle);
            FastVecScale(offset, offset, -1.0f);
            vec_scale_to_length(offset, offset, 1.0f);
            if (func_00282C48(angle) > 1e-05f) {
                vec_scale_to_length(u.t.turn, u.t.axis, 1.0f);
                func_002AB668(u.t.turn, u.t.turn, angle);
                func_002ACDE8(object + 0xC0, offset, u.t.turn);
                FastVecCross(object + 0xD0, object + 0xC0, forward);
                vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
                FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
                qcopy(state + 0x30, object + 0xC0);
            }
            if (fast_vec_dist(aim, object + 0x10) <= *(float *)(state + 0x18)
                && CollLine(object + 0x10, aim, 0x12, D_0018C0B0, 0) == 0) {
                locked = 1;
                qcopy(D_L00_001BF200.point, aim);
                D_L00_001BF200.count = -1;
                D_L00_001BF200.hit = target;
            }
        }
    } else {
        func_002FEE70(*(int *)(state + 0x50), state + 0x30, 0);
        qcopy(object + 0xC0, state + 0x30);
        FastVecCross(object + 0xD0, object + 0xC0, forward);
        vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
        FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
    }

    if (target != 0) {
        *(float *)(state + 0x0) = aim[0];
        *(float *)(state + 0x4) = aim[1];
        *(float *)(state + 0x8) = aim[2];
    }
    *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
    FastVecScale(step, object + 0xC0, *(float *)(state + 0x18));
    FastVecAdd(object + 0x10, object + 0x10, step);
    func_00300190(object + 0x10, object + 0x10);
    if (target != 0 && *(short *)(target + 0xAA) == 0xCEA) {
        FastVecSub(delta, aim, object + 0x10);
        if (FastVecDot(delta, object + 0xC0) < 0.0f) {
            *(char **)(state + 0x10) = 0;
            target = 0;
            locked = 0;
        }
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f
        || *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f
        || *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        RemoveMobyFromIndexList(object, D_L00_001B1FB0);
        func_002FEE50(*(int *)(state + 0x50));
        func_0029F338(object);
        return;
    }
    func_L00_003ACC88(object, delta);
    {
        Vector *trail = D_L00_0023B710[*(int *)(state + 0x2C)];
        int k;

        for (k = 3; k > 0; k--) {
            qcopy(trail[k], trail[k - 1]);
        }
        qcopy(trail[0], delta);
    }
    if (++*(unsigned char *)(state + 0x27) >= 4) {
        ref_L00_003ABEC0_00(func_L00_003ACCF8, object);
    }
    func_L00_003ACA60(object, start);
    qcopy(lead, object + 0x10);
    FastVecScale(offset, forward, -0.25f);
    FastVecAdd(offset, object + 0x10, offset);
    if (CollLine(lead, offset, 2, 0, 0) != 0) {
        FastVecScale(lead, forward, 0.25f);
        FastVecAdd(object + 0x10, D_L00_001BF200.point, lead);
    }
    u.shot.owner = object;
    u.shot.count = 1;
    u.shot.flags = 0x830000;
    {
        Material *material = &D_L00_00262570[D_00139568[0x1B]];

        u.shot.damage = material->damage;
    }
    qcopy_nc(u.shot.direction, step);
    vec_scale_to_length(u.shot.direction, u.shot.direction, 1.5f);
    u.shot.direction[3] = 5627.9248f;
    u.shot.kind = 3;
    u.shot.one = 1;
    u.shot.id = *(unsigned short *)(object + 0xAA);
    if (locked == 0) {
        if (CollLine(start, object + 0x10, 0, D_0018C0B0, &u.shot) == 0) {
            goto checked;
        }
    } else if (target != 0) {
        QueueMobyImpact(target, &u.shot);
    }
    hit = &D_L00_001BF200;
    if (hit->hit != 0) {
        if (hit->hit != D_0018C0B0) {
            if (hit->hit != *(char **)(state + 0xC)) {
                *(unsigned char *)(object + 0xBC) = 2;
                qcopy(object + 0x10, hit->point);
                owner = object;
                if (D_L00_00262570[D_00139568[0x1B]].piercing != 0) {
                    StartAttachedEffect(hit->hit, 0x45, *(int *)(object + 0xB8));
                } else {
                    StartAttachedEffect(hit->hit, 0x1B, *(int *)(object + 0xB8));
                }
            }
        }
    } else if (hit->count > 0) {
        *(unsigned char *)(object + 0xBC) = 1;
        qcopy(object + 0x10, hit->point);
    }
checked:
    if (*(unsigned char *)(object + 0xBC) == 0) {
        goto far;
    }
    {
        float spin;

        PlayMobySound(0, 0, object);
        bounce = 1;
        func_002AFFD8(object + 0x10, up, 1);
        if (D_L00_001BF200.hit != 0 && D_L00_001BF200.count <= 0) {
            FastVecSub(normal, D_L00_001B8DC0, object + 0x10);
            vec_scale_to_length(normal, normal, 1.0f);
        } else {
            vec_scale_to_length(normal, D_L00_001BF200.normal, 1.0f);
            if (func_00282C48(FastVecDot(normal, up)) >= 0.1f) {
                bounce = 0;
            }
        }
        spin = 0.0f;
        if (bounce) {
            spin = func_002A89A8(object + 0x10, 0, 0.5f);
        }
        func_0032DA58(object, object + 0x10, normal, spin);
        func_L00_003AC8E8(object, up, owner);
    }
    RemoveMobyFromIndexList(object, D_L00_001B1FB0);
    func_002FEE50(*(int *)(state + 0x50));
    func_0029F338(object);
    return;
far:
    if (FastDecTimer(state + 0x24) != 0 || vec_distance_xy(object + 0x10, D_00189EA0) > 75.0f) {
        RemoveMobyFromIndexList(object, D_L00_001B1FB0);
        func_002FEE50(*(int *)(state + 0x50));
        func_0029F338(object);
    }
}
