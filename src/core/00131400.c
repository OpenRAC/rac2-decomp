#include "include_asm.h"
#include "names.h"

/* Qwen draft (branch qwen/autonomy, 3d350393), checked by tools/check.py */
extern int __cmpdf2(long long, long long);

/* Handles a square root error by calling a helper with the stored value, then reports no error handled. */
int math_handle_sqrt_error(void *exception)
{
    long long val = *(long long *)(exception + 8);
    __cmpdf2(val, val);
    return 0;
}

/* func_00131424 is defined in 00131424-sqrt.c. */

