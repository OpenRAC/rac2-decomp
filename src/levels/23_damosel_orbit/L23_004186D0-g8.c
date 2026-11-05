#include "include_asm.h"
#include "common.h"

/* func_L23_004186D0 is a unit of its own: it stores the $gp datum D_L23_001B1410 (-G8 by the
   file name) and calls func_L23_0041BFF0, which L23_00416388-g8.c defines.
   Retail recomputes object+16 at each use: gcse's PRE gives those uses one reaching register,
   and the middle endpoint arm's own computation survives with an end-of-arm copy into it. */

typedef int Quad __attribute__((mode(TI)));
typedef unsigned long long Mask;
extern int *D_L23_001FF300[];
extern Mask D_L23_002595C8[][2];
extern float D_L23_001B1410 __attribute__((sda));
extern void func_L23_00418650(char *, float);
extern int func_L23_00418BC8(char *, char *, char *);
extern void func_L23_00418DC0(char *, int);
extern float func_00282E48(char *, char *);
extern float func_L00_0031BDC0(float *, const float *, const float *, const float *);
extern void func_L23_004190C8(char *, Mask, int, int);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_L23_0041BFF0(char *);
extern int func_L22_003300E8(char *, Quad *);
extern void func_L23_0041C040(char *);
/* Path follower state: phase at 0x390, direction (+1/-1) at 0x392, path slot index at 0x394,
   point index at 0x396, per-slot path numbers at 0x230. */
typedef struct { char pad[0x392]; short direction; } PathState;
typedef struct { int id[16]; } PathSlots;
typedef struct { char pad[0x230]; int slot[16]; } SlotState;
#define DIR (((PathState *)state)->direction)
#define H(off) (*(short *)(state + (off)))

/* Advance the selected path segment and send its displacement to the object. */
void func_L23_004186D0(char *object, float height) {
    struct { Quad target, raised, secondary, point; float before, after; } local;
    char *state = *(char **)(object + 0x68);
    char *point;
    int *list;
    int index, next;
    float distance;
    short mode;
    char *source = *(char **)(state + 0x400);
    qcopy(&local.target, source);
    qcopy(&local.raised, source);
    func_L23_00418650((char *)&local.raised, 0.0f);
    qcopy(&local.secondary, *(char **)(state + 0x400));
    func_L23_00418650((char *)&local.secondary, height);
    func_L23_00418BC8(object, object+16, *(char **)(state + 0x400));
    if (H(0x390) != 0)
        func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
    if (H(0x390) == 0) H(0x390) = 1;
    mode = H(0x390);
    H(0x406) = 0;
    if (mode) {
        switch (mode) {
        case 1:
            func_L23_00418DC0(object, 1);
            index = H(0x396);
            list = D_L23_001FF300[((SlotState *)state)->slot[H(0x394)]];
            point = (char *)(index * 16 + (int)list + 16);
            qcopy(&local.point, point);
            H(0x390) = 2;
            distance = func_00282E48((char *)list + (index * 16 + 16), (char *)&local.raised);
            if (H(0x396) == 0) {
                if (func_00282E48((char *)list + 32, (char *)&local.raised) < distance) {
                    DIR = 1;
                    func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16 + 32)), (float *)(object + 16));
                } else {
                    *(Quad *)(state + 0x3A0) = local.point;
                    DIR = -1;
                }
            } else if (H(0x396) == *list - 1) {
                if (func_00282E48((char *)list + (*list * 16 - 16), (char *)&local.raised) < distance) {
                    DIR = -1;
                    func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16)), (float *)(object + 16));
                } else {
                    *(Quad *)(state + 0x3A0) = local.point;
                    DIR = 1;
                }
            } else {
                local.before = func_00282E48((char *)list + (H(0x396) * 16), (char *)&local.raised);
                local.after = func_00282E48((char *)list + (H(0x396) * 16 + 32), (char *)&local.raised);
                if (local.before < local.after) DIR = -1;
                else DIR = 1;
                func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                    (float *)((char *)list + (DIR * 16 + 16)), (float *)(object + 16));
            }
            func_L23_00418650(state + 0x3A0, height);
            break;
        case 2:
            if (func_00282E48(object + 16, state + 0x3A0) < 2.0f) H(0x390) = 3;
            else qcopy(&local.target, state + 0x3A0);
            break;
        case 3:
            if (func_00282E48(object + 16, state + 0x3A0) < 2.0f) {
                next = H(0x396) + DIR;
                if (next < 0) {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    func_L23_004190C8(object, D_L23_002595C8[slot][0], 1, 1);
                } else {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    if (next >= *D_L23_001FF300[slot])
                        func_L23_004190C8(object, D_L23_002595C8[slot][1], 1, 1);
                    else H(0x396) = next;
                }
                {
                    PathSlots *slots = (PathSlots *)(state + 0x230);
                    int slot = slots->id[H(0x394)];
                    char *target = (char *)(H(0x396) * 16 + (int)D_L23_001FF300[slot] + 16);
                    qcopy(state + 0x3A0, target);
                }
                func_L23_00418650(state + 0x3A0, height);
            }
            qcopy(&local.target, state + 0x3A0);
            break;
        case 4:
            H(0x390) = 0;
            break;
        }
    }
    func_00282CF0((char *)&local.point, (char *)&local.target, object + 16);
    func_00282F20((char *)&local.point, (char *)&local.point, *(float *)(state + 0x5C8) * 0.016666668f);
    func_L23_0041BFF0(object);
    func_L22_003300E8(object, &local.point);
    func_L23_0041C040(object);
    D_L23_001B1410 = 1.0f;
}
