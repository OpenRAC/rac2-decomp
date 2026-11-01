#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00283098(float *, float *, float *);
extern void func_00282CC0(float *, float *, float *);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, int, float, float);
extern int func_PAL_00303578(char *, float *, float *, int, int, int);
extern int D_L02_001B096C __attribute__((sda));

/* Spawns five particles at the actor (the ids 0xCA5 to 0xCA9, each with a random velocity in a
   0.0167-scaled box rotated by the matrix at +0xC0), then, while D_L02_001B096C stays above 0, up
   to five more (-5 each) through func_PAL_00303578 around a point near the actor. */
void func_PAL_L02_003EB760(char *arg0) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    char *pos = arg0 + 0x10;
    char *mat = arg0 + 0xC0;
    int i;

    for (i = 0xCA5; i < 0xCAA; i++) {
        qzero(a);
        a[0] = func_002A7878(1.0f, 4.0f) * 0.020000001f;
        a[1] = func_002A78D8(1.0f, 3.0f) * 0.020000001f;
        a[2] = func_002A7878(4.0f, 9.0f) * 0.020000001f;
        func_00283098(a, a, (float *)(arg0 + 0xC0));
        func_PAL_002735D0(arg0, 0, i, -1, arg0 + 0x10, arg0 + 0xF0, a, 0xFF,
                      func_002A7878(90.0f, 180.0f), func_002A7878(15.0f, 25.0f));
    }
    *(TI128 *)b = 0;
    b[2] = 1.5f;
    func_00283098(b, b, (float *)mat);
    func_00282CC0(b, b, (float *)pos);
    for (i = 0; i < 5 && D_L02_001B096C > 0; i++) {
        qzero(a);
        a[0] = func_002A7878(1.0f, 4.0f) * 0.020000001f;
        a[1] = func_002A78D8(1.0f, 3.0f) * 0.020000001f;
        a[2] = func_002A7878(4.0f, 9.0f) * 0.020000001f;
        func_00283098(a, a, (float *)mat);
        func_PAL_00303578(arg0, b, a, 0, 5, 0);
        D_L02_001B096C -= 5;
    }
}
