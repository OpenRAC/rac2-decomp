#include "include_asm.h"
#include "common.h"

/* Small-data unit for func_L23_00419970: the five-slot table at $gp+0x2668
 * (20 bytes, hence the assembler's -G32) and the current slot right after it,
 * bounded by the count at 0x001B38C0, read through the absolute macro form. */

extern int D_L23_001B166C __attribute__((sda));
extern int D_L23_001B1658 __attribute__((sda));
extern int D_L23_001B38C0 MACRO_ADDR;
extern int *g_path_lists[];
extern void func_0032A1C8(void *, void *, int);
extern void func_002F3D60(void *, void *, float);
extern void func_002F3AB0(void *, void *, void *);
extern void func_002F3BB0(void *, void *, void *);
extern void func_002F3AF0(void *, void *, float);
extern void func_002F3A80(void *, void *, void *);
extern int mothership_check_clear_path(void *, void *, void *);

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
void mothership_advance_scan_slot(char *moby) {
    float start_a[4], start_b[4], end_a[4], end_b[4], side_b[4], side_a[4], span[4], start_dir[4], end_dir[4], scratch[4];
    char *vars;
    int start_slot = D_L23_001B166C;
    char *rec;
    vars = *(char **)(moby + 0x68);
    while (SlotAt(D_L23_001B166C = (D_L23_001B166C + 1) % D_L23_001B38C0) == -1) {
        if (start_slot == D_L23_001B166C) return;
    }
    rec = (char *)g_path_lists[((ScanSub_00419970 *)vars)->record_ids[(&D_L23_001B1658)[D_L23_001B166C]]];
    qcopy_nc(start_a, rec + 16);
    qcopy_nc(end_a, rec + *(int *)rec * 16);
    qcopy_nc(start_b, rec + 16);
    qcopy_nc(end_b, rec + *(int *)rec * 16);
    func_0032A1C8(start_a, start_dir, 1);
    func_0032A1C8(end_a, end_dir, 1);
    func_002F3D60(start_dir, start_dir, 1.0f);
    func_002F3D60(end_dir, end_dir, 1.0f);
    func_002F3AB0(span, end_a, start_a);
    func_002F3BB0(side_b, span, start_dir);
    func_002F3D60(side_b, side_b, -1.5f);
    func_002F3D60(side_a, side_b, -1.5f);
    func_002F3AF0(scratch, start_dir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, side_a);
    func_002F3A80(start_a, start_a, scratch);
    func_002F3AF0(scratch, end_dir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, side_a);
    func_002F3A80(end_a, end_a, scratch);
    func_002F3AF0(scratch, start_dir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, side_b);
    func_002F3A80(start_b, start_b, scratch);
    func_002F3AF0(scratch, end_dir, *(float *)(vars + 0x54) + *(float *)(vars + 0x50));
    func_002F3A80(scratch, scratch, side_b);
    func_002F3A80(end_b, end_b, scratch);
    if (mothership_check_clear_path(moby, start_a, end_a) && mothership_check_clear_path(moby, start_b, end_b))
        (&D_L23_001B1658)[D_L23_001B166C] = -1;
}
