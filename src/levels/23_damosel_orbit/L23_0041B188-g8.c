/* func_L23_0041B188 is a unit of its own: it reads $gp data (-G8).  Each branch keeps its own
   block-local pointer to the slot ids, which lets gcse's copy at the join stay out of the call in
   the step < 0 branch.  The kind-2 mask is read through `second`, a pointer to the table's second
   mask: `masks + 8` stays a sum of its own until combine moves the +8 into the ld displacement,
   which leaves the table base as the first operand of the addu, as in func_L23_00418FD0. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B14E4 __attribute__((sda));
extern float D_L23_001B14E8 __attribute__((sda));
extern float D_L23_001B1680 __attribute__((sda));
extern float D_L23_001B14DC __attribute__((sda));
extern float D_L23_001B1410 __attribute__((sda));
extern TI128 D_L23_001B38D0;
extern char D_L23_002595C8[];
extern int *D_L23_001FF300[];

extern void func_L23_00418650(char *, float);
extern float func_00282C48(float);
extern float func_00282E48(char *, char *);
extern void func_L23_004190C8(char *, u64, int, int);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);

void func_L23_0041B188(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *slots;
    int *list;
    TI128 vec;
    float x, mid, dev;
    int side, flip, step, slot;

    func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
    mid = D_L23_001B14E4;
    x = *(float *)(state + 0x5B8);
    if (mid + D_L23_001B14E8 <= x || x <= mid - D_L23_001B14E8) {
        flip = 0;
        if (mid - D_L23_001B14E8 < x) {
            side = 3;
            dev = func_00282C48(x - mid);
            if (*(u32 *)(state + 0x5F0) >= 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 1;
        } else {
            side = 2;
            dev = func_00282C48(x - mid);
            if (*(int *)(state + 0x5F0) != 0 && *(int *)(state + 0x5F0) != 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 2;
        }
        if (flip != 0 || func_00282E48(obj + 0x10, state + 0x3A0) < D_L23_001B1680) {
            step = *(short *)(state + 0x396) + *(short *)(state + 0x392);
            if (step < 0) {
                char *ids = state + 0x230;

                func_L23_004190C8(obj, *(u64 *)(D_L23_002595C8 + (*(int *)(ids + (*(short *)(state + 0x394) << 2)) << 4)), side, 1);
            } else {
                char *ids = state + 0x230;

                slot = *(int *)(ids + (*(short *)(state + 0x394) << 2));
                list = D_L23_001FF300[slot];
                if (step >= *list) {
                    char *masks = D_L23_002595C8;
                    char *second = masks + 8;

                    func_L23_004190C8(obj, *(u64 *)(second + (slot << 4)), side, 1);
                } else
                    *(short *)(state + 0x396) = step;
            }
            slots = state + 0x230;
            qcopy(state + 0x3A0, (char *)D_L23_001FF300[*(int *)(slots + (*(short *)(state + 0x394) << 2))] + *(short *)(state + 0x396) * 16 + 0x10);
            func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
        }
        func_00282CF0((char *)&vec, state + 0x3A0, obj + 0x10);
        dev = dev * 0.0625f;
        if (D_L23_001B14DC < dev)
            dev = D_L23_001B14DC;
        else if (dev < D_L23_001B14DC * 0.05f)
            dev = D_L23_001B14DC * 0.05f;
        func_00282F20((char *)&vec, (char *)&vec, dev);
        qcopy(&D_L23_001B38D0, &vec);
        func_00282CC0(obj + 0x10, obj + 0x10, (char *)&vec);
        func_L23_00418650(obj + 0x10, *(float *)(state + 0x588));
    }
    D_L23_001B1410 = 1.0f;
}
