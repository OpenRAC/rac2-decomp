/* func_PAL_L20_00449B08, the PAL copy of func_L20_00444088: the same C, where the 1/60 step
 * becomes 0.02, the integer argument takes the 50 Hz scale and the created child is returned. */
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2090 __attribute__((sda));

extern int D_L20_001B2094 __attribute__((sda));

extern void func_PAL_L20_004495C0(char *, char *, char *, float *);

extern char *func_PAL_L20_00450D78(char *, char *, char *, char *, int, float, int);

extern void func_00282F20(char *, char *, float);

char *func_PAL_L20_00449B08(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 a;
    TI128 b;
    float f;

    f = 0.78539824f;
    func_PAL_L20_004495C0(arg0, (char *)&a, (char *)&b, (float *)&f);
    func_00282F20((char *)&b, (char *)&b, D_L20_001B2090 * 0.020000001f);
    return func_PAL_L20_00450D78(arg0, (char *)&a, (char *)&b, state + 0x1F0, (D_L20_001B2094 * 5 + 2) / 6,
                                 (float)*(unsigned char *)(state + 0x35), *(int *)(state + 0x210));
}
