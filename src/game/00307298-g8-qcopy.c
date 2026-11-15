#include "include_asm.h"
#include "names.h"

/* func_00307298 - 148 bytes, 1 place (the boot); the G8 twin of func_00304AD0.
 * The qcopy barrier reproduces retail's first-call argument setup. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_001AEC50 __attribute__((sda));
extern void FastVecAdd(void *a, void *b, void *c);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern int CollLine(void *a, void *b, int c, void *d, int e);

/* Lets the Megaturret fall after it hits something. It moves along its speed and goes to the burst state when it lands. */
void megaturret_update_fall(void *obj)
{
    void *moby = obj;
    void *posPtr = (char *)moby + 0x10;
    void *vars = *(void **)((char *)moby + 0x68);
    TI128 oldPosition;

    *(TI128 *)&oldPosition = *(TI128 *)posPtr;
    FastVecAdd(posPtr, posPtr, vars);
    vec_add_object_direction_scaled(posPtr, vars, D_001AEC50 * 2.7777778e-05f);
    if (CollLine(&oldPosition, posPtr, 0x10, moby, 0) != 0)
        *(unsigned char *)((char *)moby + 0x20) = 8;
}
