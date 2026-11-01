#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_001AEBF0 __attribute__((sda));
extern void func_00282CC0(void *a, void *b, void *c);
extern void func_002FE880(void *a, void *b, float c);
extern int func_002761F8(void *a, void *b, int c, void *d, int e);

extern float D_PAL_001AECC0 __attribute__((sda));

/* Copies the owner's position, asks the vector unit whether it is inside the
   field, and marks the object when it is. */
void func_PAL_00308540(void *obj)
{
    void *s2 = obj;
    void *s0 = (char *)s2 + 0x10;
    void *s1 = *(void **)((char *)s2 + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)s0;
    func_00282CC0(s0, s0, s1);
    func_002FE880(s0, s1, D_PAL_001AECC0 * 4.0000003e-05f);
    if (func_002761F8(&local, s0, 0x10, s2, 0) != 0)
        *(unsigned char *)((char *)s2 + 0x20) = 8;
}


