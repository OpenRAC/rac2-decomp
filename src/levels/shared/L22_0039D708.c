#include "include_asm.h"
#include "common.h"

extern void ref_L22_003A4FF8_00(void);
extern int func_L22_003A2DF8(int, float);

typedef struct Rec_003A2D58 {
    int count;
    unsigned char pad04[0x18];
    float angle;
} Rec_003A2D58;

typedef union F32Bits {
    float f;
    unsigned int u;
} F32Bits;

extern Rec_003A2D58 *D_L22_001FE940[];

/* func_L22_0039D708 is defined in L22_0039D708-main-g8.c. */

/* func_L22_003A15D0 is defined in L22_003A15D0-g8.c. */


/* func_L22_003A1ED8 is defined in L22_003A1ED8.c. */

extern char D_00189EA0[];

typedef int Quad_2160 __attribute__((mode(TI)));
typedef union Path_2160 { Quad_2160 q; float f[4]; int count; } Path_2160;
typedef struct PathData_2160 { int count; char pad04[12]; Path_2160 points[1]; } PathData_2160;
typedef struct State_2160 {
    char pad000[0x190]; int f190;
    char pad194[0x10C]; int paths[44];
    short state, direction, path, point;
    char pad358[8]; char waypoint[16];
    char pad370[8]; short avoiding;
    char pad37A[10]; unsigned short timer;
    char pad386[10]; char avoidance[16];
    char pad3A0[12]; char *target;
    char pad3B0[16]; char previous[16];
    char pad3D0[8]; int target_hit;
    char pad3DC[36]; char flat[16];
    char pad410[8]; int f418;
    char pad41C[32]; float angle;
} State_2160;
extern void func_002F3AB0(void *, void *, void *);
extern float func_002F3C40(void *, void *);
extern int func_L22_003A2780(char *, Quad_2160 *, Quad_2160 *);
extern int func_L22_003A1ED8(void *);
extern void func_L22_003A2988(void *, float);
extern void func_L22_003A2A28(void *, int);
extern void func_L22_003A2E50(char *, int, int, float);
extern void func_00321298(void *, void *, void *, void *);
extern void func_0032FEB8(void *, void *);
extern float func_0032A758(void *, void *, int);
/* Steers the ship along its flight lanes toward a target point. It picks a lane, moves from point to point and goes around anything in the way. */
void func_L22_003A2160(char *obj) {
    char target[16], flat[16], point[16];
    float distances[2];
    State_2160 *st = *(State_2160 **)(obj + 0x68);
    int hit, active, state, next;
    float distance;
    qcopy_nc(target, st->target);
    qcopy_nc(flat, st->target);
    PushPointOutOfArena(flat, 0.0f);
    if (st->target == gHeroPosition) hit = st->target_hit;
    else hit = WalkPathIsClear(obj, (Quad_2160 *)(obj + 0x10), (Quad_2160 *)st->target);
    if (!hit && st->state == 0) st->state = 1;
    active = 1;
    if (st->state == 2) {
        if (WalkPathIsClear(obj, (Quad_2160 *)(obj + 0x10), (Quad_2160 *)st->waypoint)) {
            st->avoiding = 0; active = 0;
        }
    } else if (st->state == 4) {
        if (hit) { st->avoiding = 0; active = 0; }
    } else if (st->target == gHeroPosition && st->target_hit) {
        st->avoiding = 0; active = 0;
    } else if (!st->state && hit) {
        st->avoiding = 0; active = 0;
    } else if (st->state == 3) {
        st->avoiding = 0; active = 0;
    }
    if (active) {
        if (st->avoiding && st->f190 < 5) {
            if (func_002F3C40((obj + 0x10), st->avoidance) < 10.0f) st->avoiding = 0;
            qcopy(target, st->avoidance);
        } else {
            if (TraceSafePointAheadOfShip(obj)) {
                qcopy(target, st->avoidance);
                qcopy(st->previous, (obj + 0x10));
            }
            st->timer += 1;
        }
    }
    state = st->state;
    if (state != 0) {
    switch (state) {
    case 1: {
        Path_2160 *rec;
        StoreNearestLanePointAsCurrent(obj, 1);
        rec = (Path_2160 *)D_L22_001FE940[st->paths[st->path]];
        qcopy_nc(point, rec + (st->point + 1));
        st->state = 2;
        distance = func_002F3C40(rec + (st->point + 1), st->target);
        if (st->point == 0) {
            if (func_002F3C40(rec + 2, st->target) < distance) {
                st->direction = 1;
                func_00321298(st->waypoint, point, rec + (st->point + 2), (obj + 0x10));
            } else {
                *(Quad_2160 *)st->waypoint = *(Quad_2160 *)point;
                st->direction = -1;
            }
        } else if (st->point == rec->count - 1) {
            if (func_002F3C40(rec + (rec->count - 1), st->target) < distance) {
                st->direction = -1;
                func_00321298(st->waypoint, point, rec + st->point, (obj + 0x10));
            } else {
                *(Quad_2160 *)st->waypoint = *(Quad_2160 *)point;
                st->direction = 1;
            }
        } else {
            distances[0] = func_002F3C40(rec + st->point, st->target);
            distances[1] = func_002F3C40(rec + (st->point + 2), st->target);
            if (distances[0] < distances[1]) st->direction = -1;
            else st->direction = 1;
            func_00321298(st->waypoint, point, rec + (st->direction + 1), (obj + 0x10));
        }
        PushPointOutOfArena(st->waypoint, 0.0f);
        break;
    }
    case 2:
        if (func_002F3C40((obj + 0x10), st->waypoint) < 2.0f) {
            st->state = 3;
            goto finish;
        }
        qcopy(target, st->waypoint);
        break;
    case 3: {
        if (func_002F3C40(st->flat, flat) < 20.0f && (st->f418 || hit)) {
            st->state = 4;
        } else {
            if (func_002F3C40((obj + 0x10), st->waypoint) < 2.0f) {
                next = st->point + st->direction;
                if (next < 0) {
                    WalkPathPickNext(obj, 1, 0, ((PathData_2160 *)D_L22_001FE940[st->paths[st->path]])->points[0].f[3]);
                } else {
                    PathData_2160 *end = (PathData_2160 *)D_L22_001FE940[st->paths[st->path]];
                    if (next >= end->count) WalkPathPickNext(obj, 1, 0, end->points[end->count - 1].f[3]);
                    else st->point = next;
                }
                qcopy(st->waypoint, (Path_2160 *)D_L22_001FE940[st->paths[st->path]] + (st->point + 1));
                PushPointOutOfArena(st->waypoint, 0.0f);
            }
            qcopy(target, st->waypoint);
        }
        break;
    }
    case 4:
        st->state = 0;
        break;
    }
    }
finish:
    func_0032FEB8(obj, target);
    func_002F3AB0(point, target, (obj + 0x10));
    st->angle = func_0032A758(obj, point, 0);
}

typedef int Quad_003A2780 __attribute__((mode(TI)));
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_L22_003A2988(void *, float);

/* Walks from FROM to TO in steps of 8 units, each point dropped by the placement helper, and
 * returns 1 when no segment of the walk hits anything. Points over 50 units apart fail. */
/* Checks that nothing blocks the straight way between two points. */
int func_L22_003A2780(char *obj, Quad_003A2780 *from, Quad_003A2780 *to) {
    struct { Quad_003A2780 end, step, previous, next, cursor, scaled; } v;
    char *state = *(char **)(obj + 0x68);
    int last;
    float dist;

    if (fast_vec_dist(from, to) > 50.0f) return 0;
    qcopy(&v.end, to);
    PushPointOutOfArena(&v.end, *(float *)(state + 0x114) + *(float *)(state + 0x110));
    FastVecSub(&v.step, &v.end, from);
    vec_scale_to_length(&v.step, &v.step, 8.0f);
    qcopy(&v.cursor, from);
    qcopy(&v.previous, from);
    PushPointOutOfArena(&v.previous, *(float *)(state + 0x114) + *(float *)(state + 0x110));
    last = 0;
    do {
        dist = fast_vec_dist(&v.cursor, &v.end);
        if (dist < 8.0f) {
            if (dist < 0.0f) return 1;
            vec_scale_to_length(&v.scaled, &v.step, dist);
            last = 1;
            FastVecAdd(&v.next, &v.cursor, &v.scaled);
            PushPointOutOfArena(&v.next, *(float *)(state + 0x114) + *(float *)(state + 0x110));
        } else {
            FastVecAdd(&v.next, &v.cursor, &v.step);
            PushPointOutOfArena(&v.next, *(float *)(state + 0x114) + *(float *)(state + 0x110));
        }
        if (CollLine(&v.previous, &v.next, 0x12, 0, 0)) return 0;
        qcopy(&v.previous, &v.next);
        FastVecAdd(&v.cursor, &v.cursor, &v.step);
    } while (!last);
    return 1;
}

/* func_L22_003A2988 is defined in L22_003A2988-qcopy-barrier.c. */

/* func_L22_003A2A28 is defined in L22_003A2A28-qcopy-barrier.c. */

extern int func_L22_003A48F8(int);

/* Collects the set bit positions of VALUE, keeping those a null FLAG lets
 * through and, otherwise, those the shared table scan accepts. */
/* Lists which lanes are switched on in a bit mask. */
int func_L22_003A2CB8(float value, int unused, int *out, int flag) {
    int pos = 0;
    int count = 0;
    unsigned int mask;
    int *o;
    F32Bits bits;
    bits.f = value;
    mask = bits.u;
    o = out;
    while (pos < 32) {
        if (mask & 1) {
            if (flag == 0 || IsKeyMissingFromList(pos) != 0) {
                *o = pos;
                o++;
                count++;
            }
        }
        pos++;
        mask >>= 1;
    }
    return count;
}

/* Tells which end of a lane is the entry end for the given mask bit. Returns 0 for the start or the last point number. */
int func_L22_003A2D58(char *obj, int laneSlot, int bit) {
    char *laneIds = *(char **)(obj + 0x68) + 0x2A0;
    int *slot = (int *)(laneIds + laneSlot * 4);
    Rec_003A2D58 *rec;
    int lastPoint;
    rec = D_L22_001FE940[*slot];
    if (GetFloatBit(bit, rec->angle) != 0) return 0;
    rec = D_L22_001FE940[*slot];
    lastPoint = rec->count - 1;
    rec = (Rec_003A2D58 *)((char *)rec + lastPoint * 16);
    GetFloatBit(bit, rec->angle);
    return lastPoint;
}

/* Returns bit BIT of VALUE's raw pattern. */
/* Reads one bit of a number stored in a float. */
int func_L22_003A2DF8(int bit, float value) {
    F32Bits bits;
    bits.f = value;
    return (bits.u >> bit) & 1;
}

/* Remembers the lane the ship just chose and keeps a short history of the last three lanes. */
void func_L22_003A2E10(char *obj, int laneId) {
    char *vars = *(char **)(obj + 0x68);
    unsigned short previousLane = *(unsigned short *)(vars + 0x354);
    int i = (short)*(short *)(vars + 0x35E);
    char *historySlot;
    i = (i + 1) % 3;
    *(short *)(vars + 0x35E) = (short)i;
    historySlot = vars + i * 2;
    *(unsigned short *)(historySlot + 0x358) = previousLane;
    *(unsigned short *)(vars + 0x354) = laneId;
}

extern char D_00189EA0[];
extern void func_002F3AB0(void *, void *, void *);
extern float func_002F3C40(void *, void *);
extern int func_0031FC88(int);
extern int func_L22_003A6128(float);
extern float func_002F3B88(void *, void *);
extern float func_002F39F0(float);
extern void func_002F3BB0(void *, void *, void *);
extern void func_0032A5F8(void *, void *, int);
extern void func_002F3D60(void *, void *, float);
struct PathIds {
    char pad[0x2A0];
    int ids[32];
};
/* Chooses the next lane for the ship at a junction. Depending on the mode it picks randomly, the nearest lane or the one that fits the ship's heading best. */
void func_L22_003A2E50(char *obj, int mode, int filter, float bits) {
    int ids[4];
    char *points[4];
    union Endpoint { int value; unsigned short half[2]; } ends[4];
    char a[16], b[16], c[16], d[16], e[48], f[48];
    char *p = *(char **)(obj + 0x68);
    int count, i, selected, blocked, end, id;
    char *rec;
    float best, score;
    count = ListEnabledLanesFromMask(bits, (int)obj, ids, filter);
    if (!count) {
        int direction = *(short *)(p + 0x352);
        *(short *)(p + 0x352) = -direction;
        return;
    }
    if (!mode) {
        id = ids[func_0031FC88(count)];
        end = GetLaneEntryEnd(obj, id, *(short *)(p + 0x354));
        *(short *)(p + 0x352) = end == 0 ? 1 : -1;
        *(short *)(p + 0x356) = end;
        RememberChosenLane(obj, id);
        return;
    }
    for (i = 0; i < count; i++) {
        id = ids[i];
        ends[i].value = GetLaneEntryEnd(obj, id, *(short *)(p + 0x354));
        rec = (char *)D_L22_001FE940[((struct PathIds *)p)->ids[id]];
        if (!ends[i].value) points[i] = rec + *(int *)rec * 16;
        else points[i] = rec + 16;
    }
    selected = 0;
    switch (mode) {
    case 1: {
        int j, rejected;
        best = 30000.0f;
        for (j = 0; j < count; j++) {
            rejected = 0;
            if (filter) rejected = IsSingleBitSetAndValid(*(float *)(points[j] + 12));
            score = func_002F3C40(points[j], *(void **)(p + 0x3AC));
            if ((score < best && !rejected) || count == 1) {
                selected = j;
                best = score;
            }
        }
        break;
    }
    case 3: {
        int k, rejected;
        best = -30000.0f;
        for (k = 0; k < count; k++) {
            rejected = 0;
            if (filter) rejected = IsSingleBitSetAndValid(*(float *)(points[k] + 12));
            func_002F3AB0(a, gHeroPosition, obj + 0x10);
            func_002F3AB0(b, points[k], obj + 0x10);
            score = func_002F3B88(a, b);
            if ((best < score && !rejected) || count == 1) {
                selected = k;
                best = score;
            }
        }
        break;
    }
    case 2:
    default: {
        float bias = -0.35f;
        float closest = 30000.0f;
        int n;
        for (n = 0; n < count; n++) {
            blocked = 0;
            if (filter) blocked = IsSingleBitSetAndValid(*(float *)(points[n] + 12));
            func_002F3AB0(a, p + 0x3F0, p + 0x400);
            func_002F3AB0(b, points[n], p + 0x400);
            func_002F3D60(c, a, 1.0f);
            func_002F3D60(d, b, 1.0f);
            qcopy(e, c);
            qcopy(f, d);
            qcopy_nc(e + 32, obj + 0xE0);
            qcopy_nc(f + 32, obj + 0xE0);
            func_002F3BB0(e + 16, e + 32, e);
            func_002F3BB0(f + 16, f + 32, f);
            func_0032A5F8(e, p + 0x200, 0);
            func_0032A5F8(f, p + 0x200, 0);
            score = func_002F39F0(func_002F3B88(e, f) - bias);
            if ((score < closest && !blocked) || count == 1) {
                selected = n;
                closest = score;
            }
        }
        break;
    }
    }
    if (ends[selected].value == 0) {
        id = ids[selected];
        *(short *)(p + 0x352) = 1;
    } else {
        id = ids[selected];
        *(short *)(p + 0x352) = -1;
    }
    *(short *)(p + 0x356) = ends[selected].half[0];
    RememberChosenLane(obj, id);
}



typedef struct PathState_003A36A0 {
    char pad[0x2A0];
    int ids[32];
    char pad320[0x20];
    int other_id;
} PathState_003A36A0;
typedef struct PathRec_003A36A0 {
    int count;
    int pad[3];
    Quad_003A2780 pts[1];
} PathRec_003A36A0;
extern Quad_003A2780 D_L22_001C00E0;
extern void func_L22_003A3CA0(char *);
extern int func_002A77E0(int);
extern void *func_00115484(void *, int, unsigned int);
extern void func_L22_003A3B50(void *, int);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);

/* Picks seven different points at random from the 32 paths in ST->ids and spawns an object at
 * each one, skipping five of the paths, then probes the points of the other_id path, spawning
 * once per hit, up to 27 times. CUMULATIVE[i] is the number of segments before path i. The two
 * `% 3` results are unused: retail keeps only their zero-divisor guards (divisor 3, `beql`,
 * `break 0,7`), so the dividend is a reconstruction. */
/* Spawns the first pickups around the arena. Seven are placed at random spots on the lanes and some more along one special lane. */
void func_L22_003A36A0(char *obj) {
    struct {
        int cumulative[32];
        int selected[7];
        Quad_003A2780 point, low, normal;
    } v;
    PathState_003A36A0 *st = *(PathState_003A36A0 **)(obj + 0x68);
    PathRec_003A36A0 *rec;
    int total = 0, i, j, next, unused, chosen, duplicate, n, spawned;
    Quad_003A2780 *pt;

    ResetPickupTables(obj);
    RandomIntBelow(3);
    memset(v.selected, -1, 28);
    for (i = 0; i < 32; i++) {
        v.cumulative[i] = total;
        total += D_L22_001FE940[st->ids[i]]->count - 1;
    }
    for (i = 0; i < 7; i++) {
        duplicate = 1;
        do {
            chosen = RandomIntBelow(total);
            for (j = 0; j < 7; j++) {
                if (chosen == v.selected[j]) {
                    duplicate = 1;
                    break;
                }
                if (j == 6) duplicate = 0;
            }
        } while (duplicate == 1);
        v.selected[i] = chosen;
        for (j = 0; j < 32; j = next) {
            if (j == 31) {
                qcopy_nc(&v.point, (char *)((chosen - v.cumulative[31]) * 16 + (int)D_L22_001FE940[st->ids[31]]) + 16);
                break;
            }
            next = j + 1;
            if (chosen >= v.cumulative[j] && chosen < v.cumulative[next]) {
                qcopy_nc(&v.point, (char *)((chosen - v.cumulative[j]) * 16 + (int)D_L22_001FE940[st->ids[j]]) + 16);
                break;
            }
        }
        if (j != 10 && j != 27 && j != 28 && j != 31 && j != 15) {
            unused = i % 3;
            SpawnRandomKindAt(&v.point, 0);
        }
    }
    rec = (PathRec_003A36A0 *)D_L22_001FE940[st->other_id];
    n = rec->count;
    for (i = 0, spawned = 0; i < n && spawned < 27; i++) {
        unused = i % 3;
        pt = &rec->pts[i];
        ComputeViewDirection(pt, &v.normal, 0);
        FastVecScale(&v.point, &v.normal, 6.0f);
        FastVecScale(&v.low, &v.normal, -3.0f);
        FastVecAdd(&v.point, &v.point, pt);
        FastVecAdd(&v.low, &v.low, pt);
        if (CollLine(&v.low, &v.point, 0x12, 0, 0)) {
            SpawnRandomKindAt(&D_L22_001C00E0, 1);
            spawned++;
        }
    }
}

/* func_L22_003A3B50 is defined in L22_0039D708-g8.c. */

/* func_L22_003A3D50 is defined in L22_003A3D50-g8.c. */

/* func_L22_003A4128 is defined in L22_003A4128.c. */

/* func_L22_003A42E8 uses the profile in L22_003A42E8-g8.c. */


typedef struct Ctl_003A47E8 {
    int f0;
    int f4;
    int f8;
} Ctl_003A47E8;

extern Ctl_003A47E8 *D_L22_001B2AB4[1] __attribute__((sda));
extern void func_00316B30(void *, int, void *);
extern void func_0039CDC0(void *, void *, int, int, int);

/* Runs the two optional child passes while the controller's counter lasts. */
/* Runs the effect for the ship's attached part once for each side, then counts one use down. */
void func_L22_003A47E8(char *obj, int flags, int a2, int a3, int a4) {
    char *vars = *(char **)(obj + 0x68);
    char point[16];
    if (D_L22_001B2AB4[0]->f8 == 0) return;
    if (flags & 1) {
        func_00316B30(*(void **)(vars + 0x440), 3, point);
        func_0039CDC0(*(void **)(vars + 0x440), point, a2, a3,
                      a4 != 0 || D_L22_001B2AB4[0]->f0 != 0);
    }
    if (flags & 2) {
        func_00316B30(*(void **)(vars + 0x440), 4, point);
        func_0039CDC0(*(void **)(vars + 0x440), point, a2, a3,
                      a4 != 0 || D_L22_001B2AB4[0]->f0 != 0);
    }
    D_L22_001B2AB4[0]->f8 = D_L22_001B2AB4[0]->f8 - 1;
}

/* func_L22_003A4938 is defined in L22_0039D708-scan.c. */

extern float D_L22_001B2AA4 __attribute__((sda));
extern char *D_0018C0B0;
extern void func_002F3AB0(void *, void *, void *);
extern void func_002F3D60(void *, void *, float);
extern void func_002F3AF0(void *, void *, float);
extern void func_002F3A80(void *, void *, void *);
extern void func_L22_003A2B90(void *, void *, void *, int);
extern void func_L22_003A2988(void *, float);

/* Builds the sub-object's three local matrices around its fixed offset and
 * hands the result to the placement helper. */
/* Works out a point just ahead of the ship and finds the nearest lane point to it, to aim at. */
void func_L22_003A4EE8(char *obj) {
    char ahead[16];
    char back[16];
    char aim[16];
    char *vars = *(char **)(obj + 0x68);
    func_002F3AB0(ahead, obj + 0x10, vars + 0x3F0);
    func_002F3D60(ahead, ahead, D_L22_001B2AA4 * 4.0f);
    func_002F3AF0(back, gHeroMoby_0018C0B0 + 0xE0, -D_L22_001B2AA4 * 4.0f);
    func_002F3A80(aim, ahead, back);
    func_002F3AF0(aim, aim, 0.5f);
    func_002F3A80(aim, aim, vars + 0x3F0);
    FindNearestLanePoint(obj, vars + 0x3B0, aim, 1);
    PushPointOutOfArena(vars + 0x3B0, 0.0f);
    *(char **)(vars + 0x3AC) = vars + 0x3B0;
}

/* Calls a level helper and always says it worked. */
int func_L22_003A4FF8(void) {
    ref_L22_003A4FF8_00();
    return 1;
}
