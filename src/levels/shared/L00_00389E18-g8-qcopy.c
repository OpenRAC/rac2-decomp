#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern float ref_L00_00389E18_00 __attribute__((sda));
extern void func_00282CC0(void *a, void *b, void *c);
extern void func_002FE880(void *a, void *b, float c);
extern int func_002761F8(void *a, void *b, int c, void *d, int e);

/* The level's copy of func_00304AD0: same body, the $gp word is the level's. */
void func_L00_00389E18(void *obj)
{
    void *s2 = obj;
    void *s0 = (char *)s2 + 0x10;
    void *s1 = *(void **)((char *)s2 + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)s0;
    FastVecAdd(s0, s0, s1);
    func_002FE880(s0, s1, ref_L00_00389E18_00 * 2.7777778e-05f);
    if (CollLine(&local, s0, 0x10, s2, 0) != 0)
        *(unsigned char *)((char *)s2 + 0x20) = 8;
}
