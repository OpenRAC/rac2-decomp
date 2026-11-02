/* func_L00_003ABEC0: near miss, 2588/2588 bytes, 0 of 27 places (USA v1.01, 1 November 2026).
   Retail begins at 0x003ABEC8 in level 00 (the catalogue keeps the old name).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -g` (-g for the nop pair before each
   div.s); D_L00_001B1FB0 in the `.sdata` macro form, so its `la` stays out of the bounds
   checks' delay slots.

   The homing shot: control flow, calls, constants and the frame agree with retail. Things that
   mattered: `kind == 0xFE || (kind == 0xFD || ...)` (otherwise the two compares fold into one
   range test), `distance / speed` before the sine call, the three zero stores as one chained
   assignment (CC = DC = EC), the 0x45/0x1B choice as an if/else on an unsigned byte, and the
   hit block laid out with `goto far` so that the explode sequence follows it and the hero
   distance check comes last, as in retail.
   What differs: allocation of the callee-saved registers. Retail keeps delta (sp + 0x40) in $s4,
   object + 0x10 in $s2 then a copy in $s6 (later $s2 holds the offset vector), and %hi(D_00139568)
   in $fp; here delta takes $s2, the position $s4 and the offset $s6, which also moves a few
   moves and the material lookup's scheduling. Tried: object + 0x10 directly in the offset
   subtraction, inline helpers (not at retail size). */

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
    char *position;
    char *heading;
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
        position = object + 0x10;
        heading = object + 0xC0;
        func_00282CF0(delta, aim, step);
        distance = func_00282DF0(delta);
        func_00282CC0(lead, aim, state + 0x40);
        func_00282CF0(offset, position, lead);
        length = func_00282DF0(offset);
        if (length != 0.0f && distance != 0.0f) {
            angle = 1.5707964f - func_002831B0(func_00282DB0(offset, delta) / (length * distance));
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
                func_002ACDE8(heading, offset, u.t.turn);
                func_00282DD8(object + 0xD0, heading, forward);
                func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
                func_00282DD8(object + 0xE0, object + 0xD0, heading);
                qcopy(state + 0x30, heading);
            }
            if (func_00282E48(aim, position) <= *(float *)(state + 0x18)
                && func_002761F8(position, aim, 0x12, D_0018C0B0, 0) == 0) {
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
        heading = object + 0xC0;
        func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
        position = object + 0x10;
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
    }

    if (target != 0) {
        *(float *)(state + 0x0) = aim[0];
        *(float *)(state + 0x4) = aim[1];
        *(float *)(state + 0x8) = aim[2];
    }
    *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
    func_00282D30(step, heading, *(float *)(state + 0x18));
    func_00282CC0(position, position, step);
    func_00300190(position, position);
    if (target != 0 && *(short *)(target + 0xAA) == 0xCEA) {
        func_00282CF0(delta, aim, position);
        if (func_00282DB0(delta, heading) < 0.0f) {
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
    qcopy(lead, position);
    func_00282D30(offset, forward, -0.25f);
    func_00282CC0(offset, position, offset);
    if (func_002761F8(lead, offset, 2, 0, 0) != 0) {
        func_00282D30(lead, forward, 0.25f);
        func_00282CC0(position, D_L00_001BF200.point, lead);
    }
    u.shot.owner = object;
    u.shot.count = 1;
    u.shot.flags = 0x830000;
    u.shot.damage = D_L00_00262570[D_00139568[0x1B]].damage;
    qcopy(u.shot.direction, step);
    func_00282F20(u.shot.direction, u.shot.direction, 1.5f);
    u.shot.direction[3] = 5627.9248f;
    u.shot.kind = 3;
    u.shot.one = 1;
    u.shot.id = *(unsigned short *)(object + 0xAA);
    if (locked == 0) {
        if (func_002761F8(start, position, 0, D_0018C0B0, &u.shot) == 0) {
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
                qcopy(position, hit->point);
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
        qcopy(position, hit->point);
    }
checked:
    if (*(unsigned char *)(object + 0xBC) == 0) {
        goto far;
    }
    {
        float spin;

        func_002E5CF8(0, 0, object);
        bounce = 1;
        func_002AFFD8(position, up, 1);
        if (D_L00_001BF200.hit != 0 && D_L00_001BF200.count <= 0) {
            func_00282CF0(normal, D_L00_001B8DC0, position);
            func_00282F20(normal, normal, 1.0f);
        } else {
            func_00282F20(normal, D_L00_001BF200.normal, 1.0f);
            if (func_00282C48(func_00282DB0(normal, up)) >= 0.1f) {
                bounce = 0;
            }
        }
        spin = 0.0f;
        if (bounce) {
            spin = func_002A89A8(position, 0, 0.5f);
        }
        func_0032DA58(object, position, normal, spin);
        func_L00_003AC8E8(object, up, owner);
    }
explode:
    func_002ACAD0(object, D_L00_001B1FB0);
    func_002FEE50(*(int *)(state + 0x50));
    func_0029F338(object);
    return;
far:
    if (func_00282978(state + 0x24) != 0 || func_00282E80(position, D_00189EA0) > 75.0f) {
        func_002ACAD0(object, D_L00_001B1FB0);
        func_002FEE50(*(int *)(state + 0x50));
        func_0029F338(object);
    }
}
