#include "common.h"

extern unsigned int D_L04_001B24DC;

extern int func_00282948(void *a0);

extern void func_L04_003F8FA0(unsigned char *a0);

extern void func_L04_003F9078(unsigned char *a0);

void func_L04_003F9270(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    int idx = *(int *)(obj + 8);
    unsigned char *entry;

    if (idx != -1) {
        entry = (unsigned char *)((idx << 8) + D_L04_001B24DC);
        if ((unsigned int)(entry[0x20] - 2) >= 2) {
            return;
        }
    }
    if (a0[0x20] == 0) {
        *(int *)obj = 0;
        a0[0x30] = 0xFF;
        *(unsigned short *)(a0 + 0x32) = 0x7F;
        a0[0x20] = 1;
        func_L04_003F8FA0(a0);
    }
    if (func_00282948(obj) != 0) {
        func_L04_003F9078(a0);
        *(unsigned short *)(a0 + 0x34) &= 0xFFBE;
    } else {
        *(unsigned short *)(a0 + 0x34) |= 0x41;
    }
}

typedef int L04_FBD80Quad __attribute__((mode(TI)));

/* The spawned object's state: a jitter table, a scale and a link back to the entity. */
typedef struct {
    float jitter[28];
    float scale;
    unsigned char *owner;
    int timer;
    float age;
} L04_FBD80Vars;

extern unsigned char *ref_L04_003FBD80_00(int kind);
extern int ref_L04_003FBD80_01(int a0, int a1, void *owner);
extern float ref_L04_003FBD80_02(float low, float high);
extern void func_L04_003FB990(unsigned char *object, L04_FBD80Vars *vars);
extern int D_L04_001B0488 __attribute__((sda));

/* Spawns a kind-0xABE object for an entity of kind 0xBBC: it takes the entity's 8-byte
   word at +0x38, the given position raised by 0.2 and the entity's quadword at +0xF0 (with
   +0xF4 replaced by the entity state's +0x284 when its +0x274 is set), and its state
   points back at the entity with a 0.5 scale and a jitter table of 28 random floats in
   [-10, 10] / 75, the first and last zero. Returns the object, or 0. */
unsigned char *func_L04_003FBD80(unsigned char *entity, L04_FBD80Quad *position)
{
    float pos[4] __attribute__((aligned(16)));
    unsigned char *object;
    unsigned char *state;
    L04_FBD80Vars *vars;
    int result;
    long word;
    int i;

    *(L04_FBD80Quad *)pos = *position;
    if (entity == 0 || *(short *)(entity + 0xAA) != 0xBBC)
        return 0;
    object = ref_L04_003FBD80_00(0xABE);
    if (object != 0) {
        state = *(unsigned char **)(entity + 0x68);
        object[0x30] = 0x7F;
        *(short *)(object + 0x32) = 0x7F;
        object[0x31] = 1;
        vars = *(L04_FBD80Vars **)(object + 0x68);
        result = ref_L04_003FBD80_01(9, 0, entity);
        word = *(long *)(entity + 0x38);
        D_L04_001B0488 = result;
        *(long *)(object + 0x38) = word;
        *(L04_FBD80Quad *)(object + 0x10) = *(L04_FBD80Quad *)pos;
        *(float *)(object + 0x18) += 0.2f;
        *(L04_FBD80Quad *)(object + 0xF0) = *(L04_FBD80Quad *)(entity + 0xF0);
        if (*(short *)(state + 0x274) != 0)
            *(float *)(object + 0xF4) = *(float *)(state + 0x284);
        vars->owner = entity;
        vars->scale = 0.5f;
        vars->timer = 0;
        vars->age = 0;
        for (i = 0; i < 28; i++) {
            vars->jitter[i] = ref_L04_003FBD80_02(-10.0f, 10.0f) * 0.013333335f;
            if (i == 0 || i == 27)
                vars->jitter[i] = 0;
        }
        func_L04_003FB990(object, vars);
    }
    return object;
}

typedef int UpdateQuad __attribute__((mode(TI)));
typedef float L04_EE090Vec[4] __attribute__((aligned(16)));
extern int D_L04_001B2008 MACRO_ADDR;
extern L04_EE090Vec D_L04_001B9680, D_00189EA0;
extern unsigned char D_L04_001A8F20[] MACRO_ADDR;
/* Table of 0x80-byte target records; targets[] below holds indices into it. */
extern unsigned char *D_L04_001B25CC __attribute__((sda));
extern unsigned char *D_L04_001FE340[];
extern void func_L04_003EDF80(unsigned char *, unsigned char *);
extern int func_L04_003EDFF0(unsigned char *, unsigned char *);
extern void func_0029F338(void *);
extern int func_002A8600(unsigned char **, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_002A7470(void *, int, int, int);
extern int func_00282978(short *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *, void *, void *, int, void *, int, float);
extern int func_002A7820(int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L02_0031E9E8(void *, float);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002ACB48(void *, float);
extern float func_L00_0031CDD0(void *, void *, int, float, float);
extern unsigned char *func_L04_003EDD40(void *, void *);
extern void func_002A7A00(void *, float, float);
extern void *func_L04_0030C4C0(void *, void *, void *, void *, void *, void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern char *func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_002A6C58(void *, int, int);

typedef struct {
    char pad0[0x20];
    float speed;
    char pad24[5];
    unsigned char active;
    char pad2a[0x46];
    float range;
    int idList;
    int pathIndex;
    short delay;
    short timer;
    unsigned char limit;
    unsigned char fired;
    unsigned char nearest;
    char pad83;
    int group;
    char pad88[8];
    int targets[4]; /* indices into D_L04_001B25CC, -1 for an empty slot */
    char padA0[0x50];
    UpdateQuad goal;
    char pad100[0x30];
    unsigned char *link;
    int linkState;
    char pad138[8];
    int shots;
} L04_EE090Vars;

/* Launcher: pick a target point near a record (nearest to the player, or a
 * random one), fire a child towards it, and retire after enough shots. */
void func_L04_003EE090(unsigned char *m)
{
    float target[4], delta[4], rotation[4], axis[4], position[4], velocity[4];
    L04_EE090Vars *p = *(L04_EE090Vars **)(m + 0x68);
    unsigned char *cursor, *chosen, *child;
    int count, index;
    float scale, z;

    func_L04_003EDF80(m, (unsigned char *)p);
    if (m[0x31] && func_00282E48(m + 0x10, D_L04_001B9680) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 22;
    }
    switch (m[0x20]) {
    case 0:
        p->active = 1;
        p->speed = 1.0f;
        p->shots = 0;
        if (D_L04_001B2008) {
            cursor = 0;
            count = 0;
            while (!func_002A8600(&cursor, p->group, 0, 0)) {
                func_0029F338(cursor);
                count++;
            }
            if (count < p->limit)
                p->limit = count;
            m[0x20] = 1;
        }
        break;
    case 1: {
        float best, distance;

        func_L04_003EDF80(m, (unsigned char *)p);
        if (m[0x43] == 1 && (m[0x60] & 2))
            func_002A7470(m, 0, 0, 5);
        if (!func_00282978(&p->timer))
            break;
        if (!func_002A77E0(7)) {
            void *ids, *path;
            int n, pathCount;
            ids = 0;
            n = 0;
            path = 0;
            pathCount = 0;
            if (p->idList != -1) {
                ids = &p->idList;
                n = 1;
            }
            if (p->pathIndex != -1) {
                unsigned char *d = D_L04_001FE340[p->pathIndex];
                path = d + 0x10;
                pathCount = *(int *)d;
            }
            func_L04_003429F8(m, &p->goal, ids, n, path, pathCount, p->range);
        } else {
            unsigned char *q = p->link;
            if (q && q[0x20] != 0xFE && q[0x20] != 0xFD) {
                qcopy_nc(&p->goal, q + 0x10);
            } else {
                p->link = 0;
                p->linkState = 2;
            }
        }
        if (p->linkState == 2)
            break;
        index = func_L04_003EDFF0(m, (unsigned char *)p);
        if (p->fired >= p->limit || index == -1)
            break;
        chosen = 0;
        if (p->nearest) {
            int i;
            best = 100000.0f;
            /* Read through an int-pointer view, as in func_L06_003F3800;
             * p->targets[i] here gives different registers and stack slots. */
            for (i = 0; i < 4; i++) {
                int id = ((int *)((unsigned char *)p + 0x90))[i];
                if (id != -1) {
                    unsigned char *q = D_L04_001B25CC + id * 128;
                    distance = func_00282E48(D_00189EA0, q + 0x30);
                    if (distance < best) {
                        chosen = q;
                        best = distance;
                    }
                }
            }
            if (!chosen) {
                func_00282CF0(target, &p->goal, m + 0x10);
                func_00282D30(target, target, 0.5f);
                if (p->range > 1.0f)
                    func_00282FB8(target, target, 1.0f);
                if (func_00282DF0(target) < 1.0f)
                    func_00282F20(target, target, 1.0f);
                func_00282CC0(target, target, m + 0x10);
            } else {
                qcopy_nc(target, chosen + 0x30);
            }
        } else {
            int i;
            int start = func_002A7820(0, 3);
            /* targets[k] is read twice (cse merges the loads), keeping the
             * exit test short enough that jump1 does not peel an iteration. */
            for (i = 0; i < 4; i++) {
                int k = (i + start) % 4;
                if (p->targets[k] != -1) {
                    chosen = D_L04_001B25CC + p->targets[k] * 128;
                    break;
                }
            }
            if (!chosen) {
                float radius = p->range;
                if (radius < 1.0f)
                    radius = 1.0f;
                func_L02_0031E9E8(target, radius);
                func_00282CC0(target, target, m + 0x10);
            } else {
                qcopy_nc(target, chosen + 0x30);
            }
        }
        if (chosen) {
            func_00282D30(delta, chosen, func_002A7878(-0.5f, 0.5f));
            func_00282CC0(target, target, delta);
            func_00282D30(delta, chosen + 0x10, func_002A7878(-0.5f, 0.5f));
            func_00282CC0(target, target, delta);
        }
        z = func_002A89A8(target, 0, 3.0f);
        if (z != 0)
            target[2] = z;
        func_00282CF0(delta, target, m + 0x10);
        scale = func_00282DF0(delta) * 0.0100000007f;
        func_00282F20(delta, delta, scale);
        func_0029FCC0(m, 0, rotation);
        func_00282F20(axis, delta, 0.05f);
        func_002ACB48(axis, 0.025f);
        delta[2] = func_L00_0031CDD0(rotation, target, 0, scale, -0.00272222236f);
        *(UpdateQuad *)position = *(UpdateQuad *)(m + 0x10);
        child = func_L04_003EDD40(m, position);
        *(float *)(child + 0x2C) = *(float *)(*(unsigned char **)(child + 0x24) + 0x24);
        func_002A7A00(position, 2.0f, 3.0f);
        position[2] = 0;
        func_00282CC0(position, position, target);
        rotation[2] += 1.0f;
        *(UpdateQuad *)velocity = 0;
        velocity[2] = 3.0f;
        func_L04_0030C4C0(child, rotation, velocity, position, velocity, D_L04_001A8F20, 60, 0, 0);
        p->fired++;
        p->timer = p->delay;
        if (++p->shots >= 19)
            func_002A7750(m, 2, -1);
        func_002E5CF8(0, 0, m);
        if (m[0x43] != 1)
            func_002A7470(m, 1, 0, 5);
        break;
    }
    case 2:
        func_0032C700(m + 0x10, 0, 25, 20, 20, 20, 20, 0, 1, 0, 0, 0, 0.75f, 20.0f);
        p->speed = 0;
        func_002E5CF8(1, 0, m);
        func_002A6C58(m, 0, 3);
        func_0029F338(m);
        break;
    }
}
