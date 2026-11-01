/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Retained complete C reconstruction; v1003 sol-high recheck, 2026-10-29.
 * Profile: -O2 -G8 -ffunction-sections; no additional compiler options.
 * Compiled 1272/1272 bytes, 0/1 placements in USA v1.01 and USA v2.00.
 * PAL has no canonical row. No linked build or matching credit.
 *
 * Improvements over the 1232-byte draft: capture the initial source once for the
 * first two complete copies, recompute the first distance argument from the path
 * index, keep COPY on the unordered first guard, use ordinary stack-vector
 * assignments for the two endpoint copies, and form/reuse the slot array pointer
 * within each endpoint branch. The direction field is declared volatile: retail
 * performs each of its six alternative writes and its two explicit reads,
 * including the read after selecting direction in the middle-point branch.
 * Every other field retains ordinary access semantics. All declarations follow.
 *
 * Remaining: register allocation differs from +0x4. The first endpoint's stack
 * copy shares a store with the later endpoint instead of retail's separate
 * lq/sq pair. Position/PRE copies, saved pointer registers, and slot-array
 * scheduling also differ in the correct 0xB0 frame. The two-argument nearest-path
 * helper and the float-returning projection helper retain their real interfaces.
 *
 * Measured controls: -fno-gcse produced 1204 bytes; -fno-thread-jumps produced
 * 1248 bytes on the preceding nonvolatile draft. Critical-edge/block-order
 * controls did not improve it. A scoped raised-vector pointer and the unsplit
 * critical-edge option each produced the same final 1272-byte object. Stop this
 * tied approach; reopen with independent PRE/address-lifetime or tail-merge
 * evidence. Do not fabricate another input to func_L23_00418DC0.
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
typedef struct { char pad[0x392]; volatile short direction; } PathState;
#define DIR (((PathState *)state)->direction)
#define H(off) (*(short *)(state + (off)))

/* Advance the selected path segment and send its displacement to the object. */
void func_L23_004186D0(char *object, float height) {
    struct { Quad target, raised, secondary, point; float before, after; } local;
    char *state = *(char **)(object + 0x68);
    char *position;
    char *point;
    int *list;
    int index, next, slot;
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
                    DIR = -1;
                    *(Quad *)(state+0x3A0) = local.point;
                }
            } else if (H(0x396) == *list - 1) {
                if (func_00282E48((char *)list + (*list * 16 - 16), (char *)&local.raised) < distance) {
                    DIR = -1;
                    func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                        (float *)((char *)list + (H(0x396) * 16)), (float *)position);
                } else {
                    DIR = 1;
                    *(Quad *)(state+0x3A0) = local.point;
                }
            } else {
                local.before = func_00282E48((char *)list + (H(0x396) * 16), (char *)&local.raised);
                local.after = func_00282E48((char *)list + (H(0x396) * 16 + 32), (char *)&local.raised);
                if (local.before < local.after) DIR = -1;
                else DIR = 1;
                func_L00_0031BDC0((float *)(state + 0x3A0), (float *)&local.point,
                    (float *)((char *)list + (DIR * 16 + 16)), (float *)position);
            }
            func_L23_00418650(state + 0x3A0, height);
            break;
        case 2:
            if (func_00282E48(position, state + 0x3A0) < 2.0f) H(0x390) = 3;
            else qcopy(&local.target,state+0x3A0);
            break;
        case 3: {
            int *slots;
            if (func_00282E48(position, state + 0x3A0) < 2.0f) {
                next = H(0x396) + DIR;
                if (next < 0) {
                    slots = (int *)(state + 0x230);
                    slot = slots[H(0x394)];
                    func_L23_004190C8(object, D_L23_002595C8[slot][0], 1, 1);
                } else {
                    slots = (int *)(state + 0x230);
                    slot = slots[H(0x394)];
                    if (next >= *D_L23_001FF300[slot])
                        func_L23_004190C8(object, D_L23_002595C8[slot][1], 1, 1);
                    else H(0x396) = next;
                }
                slot = slots[H(0x394)];
                point = (char *)D_L23_001FF300[slot] + H(0x396) * 16 + 16;
                qcopy((state + 0x3A0) ,point);
                func_L23_00418650(state + 0x3A0, height);
            }
            qcopy(&local.target,state+0x3A0);
            break;
        }
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
