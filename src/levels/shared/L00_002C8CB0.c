/* func_L00_002C8CB0 (348 bytes, 22 places), in its own unit for the approved qcopy helper.
 * The two final transitions are an if/else that joins at one `return 1`: flow puts a
 * `(use (const_int 0))` after the else arm's call, which ends its block, so jump2 cross-jumps
 * only the 0x34 arm into the first transition's call and the 0x32 arm keeps its own call, as
 * retail does. Separate `return 1` statements, or a shared mode variable, merge all three. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern char D_00189E20[];
extern int D_00138320;
extern int D_L00_001B9080;
extern void func_L00_002C42E0(int mode, int flag);
extern int func_002761F8(void *start, void *end, int flags, void *object, int mode);
int func_L00_002C8CB0(void)
{
    char *pre = D_00189E20;
    char *base;
    char *object;
    Vector start, end;
    if (*(int *)(pre + 0x229c) == 0x11) {
        if (*(float *)(pre + 0x330) + 0.4f < *(float *)(pre + 0x88)) {
            D_L00_001B9080 = 0;
            func_L00_002C42E0(6, 1);
            return 1;
        }
    } else if (*(int *)(pre + 0x2294) != 0x67 && *(int *)(pre + 0x2294) != 0x73) {
        *(int *)(pre + 0x24c0) = 10000;
    }
    base = D_00189E20;
    if (*(short *)(base + 0x1fe) != 0)
        goto fail;
    object = *(char **)(base + 0x2290);
    if (*(int *)(*(char **)(object + 0x24) + 0x134) == 0)
        goto fail;
    if (*(int *)(base + 0x229c) != 0x12)
        goto fail;
    qcopy(&start, base + 0x80);
    start.v[2] = *(float *)(base + 0x330) + 0.01f;
    qcopy(&end, &start);
    end.v[2] += 0.3f;
    if (CollLine(&start, &end, 2, object, 0) == 0)
        goto fail;
    if (*(short *)(base + 0x24fc) == 0 && (D_00138320 & 10) != 0)
        func_L00_002C42E0(0x34, 1);
    else
        func_L00_002C42E0(0x32, 1);
    return 1;
fail:
    return 0;
}
