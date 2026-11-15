#include "include_asm.h"
#include "names.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

/* The object the copy's destination comes from: a pointer at +0x70 and a state
   short at +0x86.  The layout is measured; the original type is unknown. */
typedef struct {
    unsigned char pad_353C8[0x70];
    int f70_353C8;
    unsigned char pad2_353C8[0x12];
    short f86_353C8;
} Obj_3353C8;

extern Obj_3353C8 *D_001B5390;

extern Obj_3353C8 *func_00270280(int id);

/* Copies the caller's position into the current object's position slot. */
void func_003353C8(TI128 *position)
{
    Obj_3353C8 *obj = D_001B5390;
    Obj_3353C8 *target = (obj->f86_353C8 == 5) ? obj : FindRecordByHandleId(5);
    TI128 *dst = (TI128 *)(target->f70_353C8 + 0x90);

    *dst = *position;
}
