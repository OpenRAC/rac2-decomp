/* func_PAL_L20_00449750, the PAL copy of func_L20_00443CF0: the same C with the callees are PAL's
   func_PAL_L20_004495C0 and func_PAL_L20_00445B90. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_PAL_L20_004495C0(char *, char *, char *, float *);
extern u8 *func_PAL_L20_00445B90(int, const float *, const float *, float);

u8 *func_PAL_L20_00449750(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 v0;
    TI128 v1;
    float f;

    f = 1.0471977f;
    func_PAL_L20_004495C0(arg0, (char *)&v0, (char *)&v1, &f);
    return func_PAL_L20_00445B90(*(int *)(state + 0x21C), (float *)&v0, (float *)&v1, f);
}
