#include "ps2_hw.h"
#include "include_asm.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

extern s32 func_00342228(u8 *a0, s32 a1);
extern void func_0030C948(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_0030ED98(u8 *a0, u8 *a1, u8 *a2);
extern void func_0030F8B8(u8 *a0, u8 *a1);
extern void func_0030F298(u8 *a0, u8 *a1, u8 *a2);
extern f32 func_0030FE40(f32 x, f32 y);
extern f32 func_0030F3A0(f32 x);
extern f32 func_0030F3B8(f32 x);

typedef struct {
    s32 count;
    s32 pad04[3];
    f32 points[1][4];
} L04_Route;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0xAA - 0x20];
    s16 modelId;
} L04_RouteObject;

typedef struct {
    u8 pad000[0x1A8];
    s32 route;
    s32 links[4];
    s32 nextLinks[4];
    s32 prevLinks[4];
} L04_RouteState;

extern L04_Route *D_L04_001FE340[];
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_L04_0040F8F0(void *, void *, int, int, int, int);

extern u8 D_L04_00254E10[];

/* Finds the nearest point on the current route or one of its four links. */
void func_L04_00410518(L04_RouteObject *object, L04_RouteState *state, int *link, int *point,
                       float *result, int mode)
{
    float delta[4] __attribute__((aligned(16)));
    L04_Route *route;
    int oldPoint = *point, oldLink = *link;
    int i, j;
    float best = 9999.0f, distance;

    *link = -1;
    *point = 0;
    *result = 0;

    route = D_L04_001FE340[state->route];
    for (i = 0; i < route->count - 1; i++) {
        func_00282CF0(delta, object->pos, route->points[i]);
        distance = func_L00_002EE290(delta);
        if (distance < best) {
            *point = i;
            best = distance;
        }
    }

    for (i = 0; i < 4; i++) {
        if (state->links[i] != -1) {
            route = D_L04_001FE340[state->links[i]];
            for (j = 0; j < route->count - 1; j++) {
                func_00282CF0(delta, object->pos, route->points[j]);
                distance = func_L00_002EE290(delta);
                if (distance < best) {
                    *point = j;
                    best = distance;
                    *link = i;
                }
            }
        }
    }

    route = D_L04_001FE340[state->route];
    i = (int)((float)route->count * 0.5f);
    if (oldLink == -1 && oldPoint == 0 && *link == oldLink && *point > i)
        *point = 0;

    *result = func_L04_0040F8F0(object, state, *link, *point, mode, object->modelId == 0xBBC);
}

extern s32 func_00283CF0(f32);

/* Finds the nearest point around the last known position: on the current link and its
   neighbours, or on the base route and the links that leave it near that position. */
float func_L04_00410788(L04_RouteObject *object, L04_RouteState *state, s32 *link, s32 *point,
                        s32 wrap, s32 mode)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 best = 9999.0f, dist;
    s32 oldLink = *link;
    L04_Route *path;
    L04_Route *base = D_L04_001FE340[state->route];
    L04_Route *other;
    s32 start, boundary;
    s32 i, j, k, index, n;
    s32 end;

    if (oldLink == -1) {
        start = *point - 5;
        if (start < 0)
            start += base->count - 1;

        for (i = 0; i < 4; i++) {
            s32 *links = state->links, *nextLinks, *entry, *nextEntry;

            entry = links + i;
            if (*entry == -1)
                continue;
            path = D_L04_001FE340[*entry];

            end = start + 10;
            boundary = func_00283CF0(path->points[1][3]);
            {
                s32 count = base->count;

                if (end >= count)
                    end -= count;
            }
            if ((state->prevLinks[i] == -1 && start < end && boundary >= start && boundary < end) ||
                (end < start && (boundary >= start || boundary < end))) {
                for (j = 0; j < 5; j++) {
                    func_00282CF0(delta, object->pos, path->points[j]);
                    dist = func_L00_002EE290(delta);
                    if (dist < best) {
                        best = dist;
                        *link = i;
                        *point = j;
                    }
                }
            }

            boundary = func_00283CF0(path->points[2][3]);
            nextLinks = state->nextLinks;
            nextEntry = nextLinks + i;
            if ((*nextEntry == -1 && start < end && boundary >= start && boundary < end) ||
                (end < start && (boundary >= start || boundary < end))) {
                for (j = 0; j < 5; j++) {
                    s32 last = path->count - 1;

                    index = last - j;
                    func_00282CF0(delta, object->pos, path->points[index]);
                    dist = func_L00_002EE290(delta);
                    if (dist < best) {
                        best = dist;
                        *link = i;
                        *point = index;
                    }
                }
            }
        }

        for (n = 0; n < 10; n++) {
            index = start + n;
            {
                s32 count = base->count;

                if (index >= count)
                    index -= count;
            }
            func_00282CF0(delta, object->pos, base->points[index]);
            dist = func_L00_002EE290(delta);
            if (dist < best) {
                best = dist;
                *link = -1;
                *point = index;
            }
        }
    } else {
        s32 offset = oldLink * 4;
        s32 *links = state->links, *entry, *oldEntry = (s32 *)((u8 *)links + offset);

        path = D_L04_001FE340[*oldEntry];
        start = *point - 5;
        if (start < 0) {
            start = 0;
            n = func_00283CF0(path->points[1][3]);
            n -= 5;
            if (n < 0) {
                if (!wrap)
                    n = 0;
                else
                    n += base->count - 1;
            }
            for (i = 0; i < 10; i++) {
                s32 l;

                j = n + i;
                {
                    s32 count = base->count;

                    if (j >= count)
                        j -= count;
                }
                func_00282CF0(delta, object->pos, base->points[j]);
                dist = func_L00_002EE290(delta);
                if (dist < best) {
                    best = dist;
                    *link = -1;
                    *point = j;
                }
                for (l = 0; l < 4; l++) {
                    s32 *branches = state->links;

                    entry = branches + l;
                    if (*entry == -1 || l == oldLink)
                        continue;
                    other = D_L04_001FE340[*entry];
                    if (func_00283CF0(other->points[1][3]) != j)
                        continue;
                    for (k = 0; k < 5; k++) {
                        func_00282CF0(delta, object->pos, other->points[k]);
                        dist = func_L00_002EE290(delta);
                        if (dist < best) {
                            best = dist;
                            *link = l;
                            *point = k;
                        }
                    }
                }
            }
        } else if (*point > path->count - 4) {
            s32 l;
            s32 *nextLinks;

            n = func_00283CF0(path->points[2][3]) - 5;
            nextLinks = state->nextLinks;
            entry = nextLinks + oldLink;
            l = *entry;
            if (l != -1) {
                s32 *nextEntry = links + l;

                other = D_L04_001FE340[*nextEntry];
            } else {
                other = base;
            }
            if (n < 0) {
                if (!wrap)
                    n = 0;
                else
                    n += other->count - 1;
            }
            for (i = 0; i < 10; i++) {
                j = n + i;
                {
                    s32 count = other->count;

                    if (j >= count)
                        j -= count;
                }
                func_00282CF0(delta, object->pos, other->points[j]);
                dist = func_L00_002EE290(delta);
                if (dist < best) {
                    best = dist;
                    {
                        s32 *nextTable = state->nextLinks, *oldNext = nextTable + oldLink;

                        *link = *oldNext;
                    }
                    *point = j;
                }
            }
        }

        for (n = 0; n < 10; n++) {
            index = start + n;
            if (index >= base->count)
                break;
            func_00282CF0(delta, object->pos, path->points[index]);
            dist = func_L00_002EE290(delta);
            if (dist < best) {
                best = dist;
                *point = index;
                *link = oldLink;
            }
        }
    }

    return func_L04_0040F8F0(object, state, *link, *point, wrap, object->modelId == 0xBBC);
}

/* Scans the 0x20 slots at +0x110 of the state block for the first whose stored id the
   matcher accepts, and records its index in +0x270. */
void func_L04_00410F10(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    s32 *p = (s32 *)(s2 + 0x110);
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (func_00342228(arg0 + 0x10, *p) != 0) {
            *(s32 *)(s2 + 0x270) = i;
            return;
        }
        p++;
    }
}


INCLUDE_ASM("asm/levels", func_L04_00411298);

typedef struct RankState {
    u8 pad0[0xA2];
    u8 rank;
    u8 count;
    u8 padA4[0x11C - 0xA4];
    f32 progress;
    s32 f120;
    s32 f124;
    u8 pad128[0x160 - 0x128];
    s32 lap;
    u8 pad164[0x1E4 - 0x164];
    s32 slots[21];
    u8 pad238[0x244 - 0x238];
    s32 f244;
} RankState;
typedef struct RankObject {
    u8 pad0[0x20];
    u8 active;
    u8 pad21[0x68 - 0x21];
    RankState *state;
    u8 pad6c[0x100 - 0x6c];
} RankObject;
extern RankObject *D_L04_001B24DC __attribute__((sda));

/* Restarts EE timer 0 (T0_MODE = 0x81, T0_COUNT = 0), recomputes the route progress of every
   racer listed in the 21 slots at +0x1E4 of the object's state, bubble-sorts the active ones
   (byte +0x20 == 2) by progress unless that would put a racer ahead of one on a later lap, and
   stores each racer's 1-based rank and the racer count. The table base is reread after the call
   ($gp form in the branch delay slot, absolute in ordinary flow), and the progress store is a
   struct field, which lets the scheduler issue that reload ahead of the slot reload. */
void func_L04_00412130(RankObject *object) {
    RankObject *list[21], **out = list;
    RankState *state, *p;
    RankObject *obj;
    s32 *slot;
    s32 count = 0;
    s32 i, j, k, l;

    T0_MODE = 0x81;
    T0_COUNT = 0;
    state = object->state;
    slot = state->slots;
    for (k = 0; k < 21; k++, slot++) {
        if (*slot != -1) {
            obj = &D_L04_001B24DC[*slot];
            p = obj->state;
            p->progress = func_L04_00410788(obj, state, &p->f120, &p->f124, p->lap, p->f244);
            if (D_L04_001B24DC[*slot].active == 2) {
                *out++ = obj;
                count++;
            }
        }
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (list[j]->state->progress < list[j + 1]->state->progress
                && list[j]->state->lap <= list[j + 1]->state->lap) {
                RankObject *temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    for (l = 0; l < count; l++) {
        RankState *data = list[l]->state;
        data->rank = l + 1;
        data->count = count;
    }
}




float func_00283180(float);
float func_00283198(float);
float func_00283B98(float, float);

void func_L04_00412E38(void *arg0, void *arg1, float fparg0, float fparg1) {
    float temp_f0;
    float temp_f1;
    float temp_f20;

    temp_f0 = func_00283B98((*(float *)((unsigned char *)arg1 + 0x38C)), fparg0);
    *(float *)((unsigned char *)arg1 + 0x38C) = temp_f0;
    temp_f20 = func_00283180(temp_f0) * fparg1;
    temp_f1 = (*(float *)((unsigned char *)arg0 + 0xF4)) + (func_00283198((*(float *)((unsigned char *)arg1 + 0x38C))) * fparg1);
    *(float *)((unsigned char *)arg0 + 0xF0) = (float) ((*(float *)((unsigned char *)arg0 + 0xF0)) + temp_f20);
    *(float *)((unsigned char *)arg0 + 0xF4) = temp_f1;
}

/* func_L04_004135B8 is defined in L04_004135B8-g8.c. */


/* func_L04_00414698 is defined in L04_00414698-g8.c. */

/* func_L04_00415E28 is a near miss: nonmatching/levels/func_L04_00415E28.c */

/* func_L04_00415EA8 is a near miss: nonmatching/levels/func_L04_00415EA8.c */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

typedef struct {
    f32 start[4];
    u8 pad10[0x80 - 0x10];
    f32 origin[4];
    u8 pad90[0x100 - 0x90];
    f32 dir[4];
    f32 *from;
    f32 *to;
    s16 h118;
    u8 pad11A[0x128 - 0x11A];
    s16 h128;
    u8 pad12A[0x138 - 0x12A];
    s32 i138;
    s32 i13C;
    u32 color;
    s32 active;
    u8 *owner;
    u8 pad14C[0x150 - 0x14C];
} L04_5EE8Bolt;

extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283698(void *, void *);

void func_L04_00415EE8(u8 *owner, f32 *pos, f32 *to, f32 *from)
{
    f32 d[4] __attribute__((aligned(16)));
    f32 m[16] __attribute__((aligned(16)));
    L04_5EE8Bolt *b;
    s32 i;

    for (i = 0; i < 140; i++) {
        b = &((L04_5EE8Bolt *)D_L04_00254E10)[i];
        if (b->active == 0) {
            b->active = 1;
            func_00282CC0(d, from, pos);
            func_00282CC0(b->start, d, to);
            func_00283698(m, owner + 0xC0);
            func_002830C0(b->dir, pos, m);
            qcopy(b->origin, pos);
            b->to = to;
            b->i138 = 1;
            b->from = from;
            b->i13C = 0x1E;
            b->owner = owner;
            b->color = 0x80858585;
            b->h128 = 0;
            b->h118 = 0;
            return;
        }
    }
}

/* func_L04_00416018 is defined in L04_0040F8F0-g8.c. */

/* func_L04_004167B0 is defined in L04_0040F8F0-anim-g8.c. */

/* func_L04_00416E38 is defined in L04_00416E38.c. */

/* func_L04_00417028 is defined in L04_00417028.c. */
