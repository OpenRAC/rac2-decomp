/* functional: high. SAME on 4 level-22 calls. From the near-miss draft, callees named by level 22's places (lesson 12: 0x2F3C40 func_00282E48, 0x2F3AB0 func_00282CF0, 0x321298 func_L00_0031BDC0, 0x32FEB8 func_L02_00333438, 0x32A758 func_L02_00329C48); state 3 steers at the waypoint also while still 2 or more away. Unrun blocks read against retail, every offset and compare: the no-hit start (state 0 -> 1), states 2 and 4 clearing the avoidance, the avoidance branch (f190 < 5, distance < 10, func_L22_003A1ED8 copies and the timer), all of state 1 (end-point and middle-point waypoint choice; retail's middle case uses path point direction+1, kept), state 2, state 3's arrival (path end calls func_L22_003A2E50 with the end point's w) and state 4. */
#include "common.h"

typedef struct Rec_003A2D58 {
    int count;
    unsigned char pad04[0x18];
    float angle;
} Rec_003A2D58;

extern Rec_003A2D58 *D_L22_001FE940[];

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
extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern int func_L22_003A2780(void *, void *, void *);
extern int func_L22_003A1ED8(void *);
extern void func_L22_003A2988(void *, float);
extern void func_L22_003A2A28(void *, int);
extern void func_L22_003A2E50(char *, int, int, float);
extern float func_L00_0031BDC0(void *, void *, void *, void *);
extern void func_L02_00333438(void *, void *);
extern float func_L02_00329C48(void *, void *, int);
void func_L22_003A2160(char *obj) {
    char target[16], flat[16], point[16];
    float distances[2];
    State_2160 *st = *(State_2160 **)(obj + 0x68);
    int hit, active, state, next;
    short mode;
    float distance;
    qcopy_nc(target, st->target);
    qcopy_nc(flat, st->target);
    func_L22_003A2988(flat, 0.0f);
    if (st->target == D_00189EA0) hit = st->target_hit;
    else hit = func_L22_003A2780(obj, obj + 0x10, st->target);
    if (!hit && st->state == 0) st->state = 1;
    active = 1;
    mode = st->state;
    if (mode == 2) {
        if (func_L22_003A2780(obj, (obj + 0x10), st->waypoint)) {
            st->avoiding = 0; active = 0;
        }
    } else if (mode == 4) {
        if (hit) { st->avoiding = 0; active = 0; }
    } else if ((st->target == D_00189EA0 && st->target_hit) ||
               (st->state == 0 && hit) || st->state == 3) {
        st->avoiding = 0; active = 0;
    }
    if (active) {
        if (st->avoiding && st->f190 < 5) {
            if (func_00282E48((obj + 0x10), st->avoidance) < 10.0f) st->avoiding = 0;
            qcopy(target, st->avoidance);
        } else {
            if (func_L22_003A1ED8(obj)) {
                qcopy(target, st->avoidance);
                qcopy(st->previous, (obj + 0x10));
            }
            st->timer += 1;
        }
    }
    state = st->state;
    if (state != 0) switch (state) {
    case 1: {
        Path_2160 *rec;
        func_L22_003A2A28(obj, 1);
        rec = (Path_2160 *)D_L22_001FE940[st->paths[st->path]];
        qcopy_nc(point, rec + (st->point + 1));
        st->state = 2;
        distance = func_00282E48(rec + (st->point + 1), st->target);
        if (st->point == 0) {
            if (func_00282E48(rec + 2, st->target) < distance) {
                st->direction = state;
                func_L00_0031BDC0(st->waypoint, point, rec + (st->point + 2), (obj + 0x10));
            } else {
                *(Quad_2160 *)st->waypoint = *(Quad_2160 *)point;
                st->direction = -1;
            }
        } else if (st->point == rec->count - 1) {
            if (func_00282E48(rec + (rec->count - 1), st->target) < distance) {
                st->direction = -1;
                func_L00_0031BDC0(st->waypoint, point, rec + st->point, (obj + 0x10));
            } else {
                *(Quad_2160 *)st->waypoint = *(Quad_2160 *)point;
                st->direction = state;
            }
        } else {
            distances[0] = func_00282E48(rec + st->point, st->target);
            distances[1] = func_00282E48(rec + (st->point + 2), st->target);
            if (distances[0] < distances[1]) st->direction = -1;
            else st->direction = state;
            func_L00_0031BDC0(st->waypoint, point, rec + (st->direction + 1), (obj + 0x10));
        }
        func_L22_003A2988(st->waypoint, 0.0f);
        break;
    }
    case 2:
        if (func_00282E48((obj + 0x10), st->waypoint) < 2.0f) {
            st->state = 3;
            goto finish;
        }
        qcopy(target, st->waypoint);
        break;
    case 3: {
        if (func_00282E48(st->flat, flat) < 20.0f && (st->f418 || hit)) {
            st->state = 4;
        } else if (func_00282E48((obj + 0x10), st->waypoint) < 2.0f) {
            next = st->point + st->direction;
            if (next < 0) {
                func_L22_003A2E50(obj, 1, 0, ((PathData_2160 *)D_L22_001FE940[st->paths[st->path]])->points[0].f[3]);
            } else {
                PathData_2160 *end = (PathData_2160 *)D_L22_001FE940[st->paths[st->path]];
                if (next >= end->count) func_L22_003A2E50(obj, 1, 0, end->points[end->count - 1].f[3]);
                else st->point = next;
            }
            qcopy(st->waypoint, (Path_2160 *)D_L22_001FE940[st->paths[st->path]] + (st->point + 1));
            func_L22_003A2988(st->waypoint, 0.0f);
            qcopy(target, st->waypoint);
        } else {
            qcopy(target, st->waypoint);
        }
        break;
    }
    case 4:
        st->state = 0;
        break;
    }
finish:
    func_L02_00333438(obj, target);
    func_00282CF0(point, target, (obj + 0x10));
    st->angle = func_L02_00329C48(obj, point, 0);
}
