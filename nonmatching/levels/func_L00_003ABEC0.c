/* func_L00_003ABEC0: near miss, 2592/2588 bytes, 0 of 27 places (USA v1.01, 8 November 2026).
   Retail begins at 0x003ABEC8 in level 00 (the catalogue keeps the old name).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -g` (-g for the nop pair before each
   div.s); D_L00_001B1FB0 in the `.sdata` macro form, so its `la` stays out of the bounds
   checks' delay slots.

   The homing shot. 8 November 2026 (master compiler): everything up to +0x920 matches except
   relocations, and the rest is the same code shifted by one word. What fixed the old
   $s2/$s4/$s6/$fp allocation: no `position`/`heading` locals. Writing `object + 0x10` and
   `object + 0xC0` at every use lets gcse PRE build retail's reaching registers (addiu $s2 /
   daddu $s6,$s2 in the locked arm, addiu $s6 in the else arm, $fp for the heading; the same
   for offset: addiu $s0 / daddu $s2,$s0). Also: the arccos argument in its own statement
   (`angle = func_00282DB0(...); angle = ... / (length * distance)`) gives the line label that
   puts retail's one nop between mul.s and div.s; the damage read through a `Material *`
   local gives retail's v1/a0/a1 temporaries; qcopy_nc for the shot direction lets
   post-reload cse keep &u in $a0 (qcopy's memory clobber forced a second lw from 0xCC(sp)).
   What differs: the bounce block. Retail fills `beqz $s1` with `daddu $a0,$s6` from the
   fall-through and its join block issues `mov.s $f12,$f0` first (then a0 in the jal slot);
   here sched2 ranks the 0.5 constant before a0 and a1/a2 before the mov.s, so reorg takes
   `daddu $a1,$s6` from the target (one extra word) and the mov.s goes in the jal slot.
   Tried 8 November: if/else and ternary forms of spin (worse), one-line if, an interleaved
   (void *, float, int) prototype, a one-pass group around func_0032DA58 or around
   func_L00_003AC8E8 (adds an alignment nop; the second gives a1, a2, mov.s, a0).
   Round 2 (8 November): reorg tries the fall-through first (beqz predicted not taken) but
   the fall-through is not its own thread, so it stops at the first insn it cannot take, the
   two-word 0.5 constant; retail's sched2 must have put `daddu $a0,$s6` first. Tried without
   change: a block-local `pos` for the argument, a (float, ...) interleaved prototype for
   func_0032DA58, -fno-sched-interblock, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
   -frac2-sticky-volatile-refs, -frac2-hazard-labels. Worse: spin = 0.0f before the normal
   test (moves spin into $f20), `if (!bounce) ... else ...` (bnel form), -fno-schedule-insns.
   Twin search (8 November): matched twin func_L00_0040A4A8 discards func_002A89A8's result
   (`if (explode) func_002A89A8(...)`), so it has no spelling of the spin argument; its flags
   (-frac2-gcse-unsplit-edges) and one-line if/call forms leave 2592 bytes. Diagnostic:
   -fno-schedule-insns2 gives retail's bounce block exactly (daddu $a0,$s6 in the beqz slot) but
   the join becomes a1, a2, mov.s, a0 (retail mov.s, a1, a2) and the rest breaks; so retail's
   order there is the RTL order and sched2 ties decide it.
   Dead ends from the earlier rounds (all with position/heading locals): a pointer variable
   reused for the offset, -fno-gcse, groups around the copies. */

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
extern void func_L00_002E6EF8(void *, void *);
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
                func_00282D30(step, target + 0xE0, *(float *)(info + 0x10));
                func_00282CC0(aim, aim, step);
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
        func_00282CF0(delta, aim, step);
        distance = func_00282DF0(delta);
        func_00282CC0(lead, aim, state + 0x40);
        func_00282CF0(offset, object + 0x10, lead);
        length = func_00282DF0(offset);
        if (length != 0.0f && distance != 0.0f) {
            angle = func_00282DB0(offset, delta);
            angle = 1.5707964f - func_002831B0(angle / (length * distance));
            func_00282DD8(u.t.axis, delta, offset);
            func_00282DD8(u.t.side, delta, u.t.axis);
            if (func_00282DB0(offset, u.t.side) < 0.0f) {
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
            func_00282D30(offset, offset, -1.0f);
            func_00282F20(offset, offset, 1.0f);
            if (func_00282C48(angle) > 1e-05f) {
                func_00282F20(u.t.turn, u.t.axis, 1.0f);
                func_002AB668(u.t.turn, u.t.turn, angle);
                func_002ACDE8(object + 0xC0, offset, u.t.turn);
                func_00282DD8(object + 0xD0, object + 0xC0, forward);
                func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
                func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
                qcopy(state + 0x30, object + 0xC0);
            }
            if (func_00282E48(aim, object + 0x10) <= *(float *)(state + 0x18)
                && func_002761F8(object + 0x10, aim, 0x12, D_0018C0B0, 0) == 0) {
                locked = 1;
                qcopy(D_L00_001BF200.point, aim);
                D_L00_001BF200.count = -1;
                D_L00_001BF200.hit = target;
            }
        }
    } else {
        func_002FEE70(*(int *)(state + 0x50), state + 0x30, 0);
        qcopy(object + 0xC0, state + 0x30);
        func_00282DD8(object + 0xD0, object + 0xC0, forward);
        func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
    }

    if (target != 0) {
        *(float *)(state + 0x0) = aim[0];
        *(float *)(state + 0x4) = aim[1];
        *(float *)(state + 0x8) = aim[2];
    }
    *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
    func_00282D30(step, object + 0xC0, *(float *)(state + 0x18));
    func_00282CC0(object + 0x10, object + 0x10, step);
    func_00300190(object + 0x10, object + 0x10);
    if (target != 0 && *(short *)(target + 0xAA) == 0xCEA) {
        func_00282CF0(delta, aim, object + 0x10);
        if (func_00282DB0(delta, object + 0xC0) < 0.0f) {
            *(char **)(state + 0x10) = 0;
            target = 0;
            locked = 0;
        }
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f
        || *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f
        || *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        goto explode;
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
        func_L00_002E6EF8(func_L00_003ACCF8, object);
    }
    func_L00_003ACA60(object, start);
    qcopy(lead, object + 0x10);
    func_00282D30(offset, forward, -0.25f);
    func_00282CC0(offset, object + 0x10, offset);
    if (func_002761F8(lead, offset, 2, 0, 0) != 0) {
        func_00282D30(lead, forward, 0.25f);
        func_00282CC0(object + 0x10, D_L00_001BF200.point, lead);
    }
    u.shot.owner = object;
    u.shot.count = 1;
    u.shot.flags = 0x830000;
    {
        Material *material = &D_L00_00262570[D_00139568[0x1B]];

        u.shot.damage = material->damage;
    }
    qcopy_nc(u.shot.direction, step);
    func_00282F20(u.shot.direction, u.shot.direction, 1.5f);
    u.shot.direction[3] = 5627.9248f;
    u.shot.kind = 3;
    u.shot.one = 1;
    u.shot.id = *(unsigned short *)(object + 0xAA);
    if (locked == 0) {
        if (func_002761F8(start, object + 0x10, 0, D_0018C0B0, &u.shot) == 0) {
            goto checked;
        }
    } else if (target != 0) {
        func_002A8E20(target, &u.shot);
    }
    hit = &D_L00_001BF200;
    if (hit->hit != 0) {
        if (hit->hit != D_0018C0B0) {
            if (hit->hit != *(char **)(state + 0xC)) {
                *(unsigned char *)(object + 0xBC) = 2;
                qcopy(object + 0x10, hit->point);
                owner = object;
                if (D_L00_00262570[D_00139568[0x1B]].piercing != 0) {
                    func_0032D758(hit->hit, 0x45, *(int *)(object + 0xB8));
                } else {
                    func_0032D758(hit->hit, 0x1B, *(int *)(object + 0xB8));
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

        func_002E5CF8(0, 0, object);
        bounce = 1;
        func_002AFFD8(object + 0x10, up, 1);
        if (D_L00_001BF200.hit != 0 && D_L00_001BF200.count <= 0) {
            func_00282CF0(normal, D_L00_001B8DC0, object + 0x10);
            func_00282F20(normal, normal, 1.0f);
        } else {
            func_00282F20(normal, D_L00_001BF200.normal, 1.0f);
            if (func_00282C48(func_00282DB0(normal, up)) >= 0.1f) {
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
explode:
    func_002ACAD0(object, D_L00_001B1FB0);
    func_002FEE50(*(int *)(state + 0x50));
    func_0029F338(object);
    return;
far:
    if (func_00282978(state + 0x24) != 0 || func_00282E80(object + 0x10, D_00189EA0) > 75.0f) {
        func_002ACAD0(object, D_L00_001B1FB0);
        func_002FEE50(*(int *)(state + 0x50));
        func_0029F338(object);
    }
}
