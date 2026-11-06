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
void func_PAL_L22_003A54A0(char *obj) {
    char target[16], flat[16], point[16];
    float distances[2];
    State_2160 *st = *(State_2160 **)(obj + 0x68);
    int hit, active, state, next;
    float distance;
    qcopy_nc(target, st->target);
    qcopy_nc(flat, st->target);
    func_L22_003A2988(flat, 0.0f);
    if (st->target == D_00189EA0) hit = st->target_hit;
    else hit = func_L22_003A2780(obj, (Quad_2160 *)(obj + 0x10), (Quad_2160 *)st->target);
    if (!hit && st->state == 0) st->state = 1;
    active = 1;
    if (st->state == 2) {
        if (func_L22_003A2780(obj, (Quad_2160 *)(obj + 0x10), (Quad_2160 *)st->waypoint)) {
            st->avoiding = 0; active = 0;
        }
    } else if (st->state == 4) {
        if (hit) { st->avoiding = 0; active = 0; }
    } else if (st->target == D_00189EA0 && st->target_hit) {
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
            if (func_L22_003A1ED8(obj)) {
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
        func_L22_003A2A28(obj, 1);
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
        func_L22_003A2988(st->waypoint, 0.0f);
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
                    func_L22_003A2E50(obj, 1, 0, ((PathData_2160 *)D_L22_001FE940[st->paths[st->path]])->points[0].f[3]);
                } else {
                    PathData_2160 *end = (PathData_2160 *)D_L22_001FE940[st->paths[st->path]];
                    if (next >= end->count) func_L22_003A2E50(obj, 1, 0, end->points[end->count - 1].f[3]);
                    else st->point = next;
                }
                qcopy(st->waypoint, (Path_2160 *)D_L22_001FE940[st->paths[st->path]] + (st->point + 1));
                func_L22_003A2988(st->waypoint, 0.0f);
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

/* func_L22_003A2988 is defined in L22_003A2988-qcopy-barrier.c. */

/* func_L22_003A2A28 is defined in L22_003A2A28-qcopy-barrier.c. */

extern int func_L22_003A48F8(int);

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

/* func_L22_003A4938 is defined in L22_0039D708-scan.c. */

extern float D_L22_001B2AA4 __attribute__((sda));
extern char *D_0018C0B0;
extern void func_002F3AB0(void *, void *, void *);
extern void func_002F3D60(void *, void *, float);
extern void func_002F3AF0(void *, void *, float);
extern void func_002F3A80(void *, void *, void *);
extern void func_L22_003A2B90(void *, void *, void *, int);
extern void func_L22_003A2988(void *, float);