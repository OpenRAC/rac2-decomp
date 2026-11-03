/* Tier opus-1 (Claude Opus 5.5), task v2200, 2026-11-03.
 * Profile: -O2 -G8 -ffunction-sections (file name needs -g8.c for the sda
 * D_L23_001B1410); no other compiler options.
 * Best check.py: 1272/1272 bytes, 0/1 places in USA v1.01; 149/318 rows differ
 * (the 2026-10-29 draft this replaces had 202/318).
 *
 * Changes from the previous draft: direction is no longer volatile (retail
 * rereads it with lh, not lhu/sll/sra); each endpoint else arm stores the stack
 * copy before writing direction, which gives retail's separate lq/sq; case 3
 * forms a block-local PathSlots pointer and slot in each branch and at the join,
 * which gives retail's address order and its PRE temp+copy; the middle arm ends
 * with its own func_L23_00418650 call and break, so its state+0x3A0 temporary
 * crosses the call into a saved register.
 *
 * Remaining: retail's middle arm also recomputes object+16 into $s0 and copies
 * it to position ($s6) at the end of the block. Its state+0x3A0 temporary shares
 * $s1 with the case-1 tail's PRE register, so the tail falls through instead of
 * branching. Those two call-crossing locals take $s0/$s1, which explains retail's
 * globals: mode s0, state s2, &local.point s3, list s4, object s5, position s6,
 * constant 2 s7. Ours has state s1 and the rest shifted. In ours, object+16 in
 * the middle arm is fully redundant with the top `position = object + 16`
 * (reaching register $fp), and a later `position = object + 16` also folds into
 * $fp, so retail must stop that expression from being available there.
 * All declarations needed are below.
 */

#include "common.h"
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
/* Retail reads direction again after the branch writes it. Keep that property on
 * the real state field, including all six writes and both reads. */
typedef struct { char pad[0x392]; short direction; } PathState;
typedef struct { int id[16]; } PathSlots;
#define DIR (((PathState *)state)->direction)
#define H(off) (*(short *)(state + (off)))

/* Advance the selected path segment and send its displacement to the object. */
void func_L23_004186D0(char *object, float height) {
    struct { Quad target, raised, secondary, point; float before, after; } local;
    char *state = *(char **)(object + 0x68);
    char *position;
    char *point;
    int *list;
    int index, next;
    float distance;
    short mode;
    char *source = *(char **)(state + 0x400);
    qcopy(&local.target, source);
    qcopy(&local.raised, source);
    func_L23_00418650((char *)&local.raised, 0.0f);
    qcopy(&local.secondary,*(void **)(state+0x400));
    func_L23_00418650((char *)&local.secondary, height);
    func_L23_00418BC8(object, object+16, *(char **)(state + 0x400));
    if (H(0x390) != 0)
        func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
    if (H(0x390) == 0) H(0x390) = 1;
    mode = H(0x390);
    position = object+16;
    H(0x406) = 0;
    if (mode) {
        switch (mode) {
        case 1:
            func_L23_00418DC0(object, 1);
            index = H(0x396);
            list = D_L23_001FF300[*(int *)(state + H(0x394) * 4 + 0x230)];
            point = (char *)list + index * 16 + 16;
            qcopy(&local.point,point);
            H(0x390) = 2;
            distance = func_00282E48((char *)list + (index * 16 + 16), (char *)&local.raised);
            if (H(0x396) == 0) {
                if (func_00282E48((char *)list + 32, (char *)&local.raised) < distance) {
                    DIR = 1;
                    func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16 + 32)), (float *)position);
                } else {
                    *(Quad *)(state+0x3A0) = local.point;
                    DIR = -1;
                }
            } else if (H(0x396) == *list - 1) {
                if (func_00282E48((char *)list + (*list * 16 - 16), (char *)&local.raised) < distance) {
                    DIR = -1;
                    func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16)), (float *)position);
                } else {
                    *(Quad *)(state+0x3A0) = local.point;
                    DIR = 1;
                }
            } else {
                local.before = func_00282E48((char *)list + (H(0x396) * 16), (char *)&local.raised);
                local.after = func_00282E48((char *)list + (H(0x396) * 16 + 32), (char *)&local.raised);
                if (local.before < local.after) DIR = -1;
                else DIR = 1;
                func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                    (float *)((char *)list + (DIR * 16 + 16)), (float *)position);
                func_L23_00418650(state + 0x3A0, height);
                break;
            }
            func_L23_00418650(state + 0x3A0, height);
            break;
        case 2:
            if (func_00282E48(position, state + 0x3A0) < 2.0f) H(0x390) = 3;
            else qcopy(&local.target,state+0x3A0);
            break;
        case 3:
            if (func_00282E48(position, state + 0x3A0) < 2.0f) {
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
                    point = (char *)D_L23_001FF300[slot] + H(0x396) * 16 + 16;
                }
                qcopy((state + 0x3A0) ,point);
                func_L23_00418650(state + 0x3A0, height);
            }
            qcopy(&local.target,state+0x3A0);
            break;
        case 4:
            H(0x390) = 0;
            break;
        }
    }
    func_00282CF0((char *)&local.point, (char *)&local.target, position);
    func_00282F20((char *)&local.point, (char *)&local.point, *(float *)(state + 0x5C8) * 0.016666668f);
    func_L23_0041BFF0(object);
    func_L22_003300E8(object, &local.point);
    func_L23_0041C040(object);
    D_L23_001B1410 = 1.0f;
}
