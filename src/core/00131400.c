#include "include_asm.h"

/* Qwen draft (branch qwen/autonomy, 3d350393), checked by tools/check.py */
extern void func_00123028(long long, long long);

/* Math exception hook: compares the 64-bit value at arg+8 with itself through func_00123028
   and returns 0. */
int func_00131400(void *arg)
{
    long long val = *(long long *)(arg + 8);
    func_00123028(val, val);
    return 0;
}

/* func_00131424 is defined in 00131424-sqrt.c. */

