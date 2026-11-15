#include "include_asm.h"
#include "common.h"

/* Small-data unit for func_L23_00419970: the five-slot table at $gp+0x2668
 * (20 bytes, hence the assembler's -G32) and the current slot right after it,
 * bounded by the count at 0x001B38C0, read through the absolute macro form. */

extern int D_L23_001B166C __attribute__((sda));
extern int D_L23_001B1658 __attribute__((sda));
extern int D_L23_001B38C0 MACRO_ADDR;
extern int *D_L23_001FF300[];
extern void func_0032A1C8(void *, void *, int);
extern void func_002F3D60(void *, void *, float);
extern void func_002F3AB0(void *, void *, void *);
extern void func_002F3BB0(void *, void *, void *);
extern void func_002F3AF0(void *, void *, float);
extern void func_002F3A80(void *, void *, void *);
extern int func_L23_00418BC8(void *, void *, void *);

typedef struct ScanSub_00419970 {
    char pad[0x230];
    int record_ids[0];
} ScanSub_00419970;

/* Reading the slot through an accessor matters: its inlined block stays at
 * the top of the rotated while loop, so cse1 does not merge the loop's table
 * base with the pre-test's and retail's separate loop copy is kept. */
static inline int SlotAt(int i) {
    return (&D_L23_001B1658)[i];
}

/* Advances the current slot round-robin to the next one not yet spent (-1),
 * giving up after a full turn. Two point pairs are built from the first and
 * last points of the slot's record, and the slot is marked spent once
 * func_L23_00418BC8 accepts both pairs. */
void func_L23_00419970(char *moby) {
    float startA[4], startB[4], endA[4], endB[4], sideB[4], sideA[4], span[4], startDir[4], endDir[4], scratch[4];
    char *vars;
    int startSlot = D_L23_001B166C;
    char *rec;
    vars = *(char **)(moby + 0x68);
    while (SlotAt(D_L23_001B166C = (D_L23_001B166C + 1) % D_L23_001B38C0) == -1) {
        if (startSlot == D_L23_001B166C) return;
    }
    rec = (char *)gPathLists[((ScanSub_00419970 *)vars)->record_ids[(&D_L23_001B1658)[D_L23_001B166C]]];
    qcopy_nc(startA, rec + 16);
    qcopy_nc(endA, rec + *(int *)rec * 16);
    qcopy_nc(startB, rec + 16);
    qcopy_nc(endB, rec + *(int *)rec * 16);
    func_0032A1C8(startA, startDir, 1);
    func_0032A1C8(endA, endDir, 1);
    func_002F3D60(startDir, startDir, 1.0f);
    func_002F3D60(endDir, endDir, 1.0f);
    func_002F3AB0(span, endA, startA);
    func_002F3BB0(sideB, span, startDir);
    func_002F3D60(sideB, sideB, -1.5f);
    func_002F3D60(sideA, sideB, -1.5f);
    func_002F3AF0(scratch, startDir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, sideA);
    func_002F3A80(startA, startA, scratch);
    func_002F3AF0(scratch, endDir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, sideA);
    func_002F3A80(endA, endA, scratch);
    func_002F3AF0(scratch, startDir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, sideB);
    func_002F3A80(startB, startB, scratch);
    func_002F3AF0(scratch, endDir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, sideB);
    func_002F3A80(endB, endB, scratch);
    if (CheckClearPathBetweenPoints(moby, startA, endA) && CheckClearPathBetweenPoints(moby, startB, endB))
        (&D_L23_001B1658)[D_L23_001B166C] = -1;
}
