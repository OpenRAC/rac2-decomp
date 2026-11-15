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
extern void func_00282CC0(void *a, void *b, void *c);
extern void func_002FE880(void *a, void *b, float c);
extern int func_002761F8(void *a, void *b, int c, void *d, int e);

/* Copies the owner's position, asks the vector unit whether it is inside the
   field, and marks the object when it is. */
void func_00304AD0(void *obj)
{
    void *s2 = obj;
    void *s0 = (char *)s2 + 0x10;
    void *s1 = *(void **)((char *)s2 + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)s0;
    FastVecAdd(s0, s0, s1);
    func_002FE880(s0, s1, D_001AEBF0 * 2.7777778e-05f);
    if (CollLine(&local, s0, 0x10, s2, 0) != 0)
        *(unsigned char *)((char *)s2 + 0x20) = 8;
}
