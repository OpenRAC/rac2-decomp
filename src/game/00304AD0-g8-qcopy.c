#include "names.h"
/* func_00304AD0 - 148 bytes, 1 place (the boot).
 *
 * Boot-only twin of func_00307298: the bodies are the same instruction for
 * instruction; only the `$gp` word differs (D_001AEBF0 here, D_001AEC50 in
 * the twin).  The old draft was 124 of 148 bytes with -frac2-qcopy alone:
 * the barrier puts the copy before the first call's argument setup, in
 * retail's order.  Matches 1/1 in USA v1.01 and USA v2.00; PAL has no
 * catalogue row.
 */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern float D_001AEBF0 __attribute__((sda));
extern void FastVecAdd(void *a, void *b, void *c);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern int CollLine(void *a, void *b, int c, void *d, int e);

/* Copies the owner's position, asks the vector unit whether it is inside the
   field, and marks the object when it is. */
void projectile_move_check_hit(void *obj)
{
    void *moby = obj;
    void *position = (char *)moby + 0x10;
    void *vars = *(void **)((char *)moby + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)position;
    FastVecAdd(position, position, vars);
    vec_add_object_direction_scaled(position, vars, D_001AEBF0 * 2.7777778e-05f);
    if (CollLine(&local, position, 0x10, moby, 0) != 0)
        *(unsigned char *)((char *)moby + 0x20) = 8;
}
