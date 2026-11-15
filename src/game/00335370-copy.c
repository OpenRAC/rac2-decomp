#include "common.h"

/* Copy the input vector to the selected object's output area. The real shared
 * transfer helper keeps the return-address restore after the memory operation.
 */

typedef struct {
    unsigned char pad_35370[0x70];
    void *f70_35370;
    unsigned char pad2_35370[0x12];
    short f86_35370;
} Obj_35370;

extern Obj_35370 *ref_L00_00335370_00;
extern char *func_00270280(s32 a0);

/* Copies a vector into the data of the selected object. */
void func_00335370(void *vec)
{
    Obj_35370 *current;
    Obj_35370 *selected;
    void *dst;
    char *dstPtr;

    current = ref_L00_00335370_00;
    if (current->f86_35370 != 5) {
        selected = (Obj_35370 *)FindRecordByHandleId(5);
    } else {
        selected = current;
    }
    dst = selected->f70_35370;
    dstPtr = (char *)dst + 0x80;
    qcopy(dstPtr, vec);
}
