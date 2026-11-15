/* Updates the path-constrained position only inside the measured distance gate.
 * The two-dimensional limiter consumes the threshold in the floating argument bank. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L20_001B2AC8 __attribute__((sda));
extern float D_L20_001B23F0 __attribute__((sda));
extern char *D_L20_001C4480[] __attribute__((nosda));

extern int func_00277F48(float f, char *a, int b, char *c, int d);
extern void func_L20_00449AE8(char *);
extern void func_L20_00444C18(char *, char *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *vec);
extern void func_00282F70(void *out, void *in, float magnitude);
extern void func_00282CC0(void *, void *, void *);
extern int func_002C9218(int index, void *point, void *out, float radius);

void func_L20_00449BB0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int count;
    int i;

    if (*(int *)(state + 0xAC) != 0) {
        if ((D_L20_001B2AC8 & 7) == (((int)arg0 >> 8) & 7)) {
            count = func_00277F48(1.5f, arg0 + 0x10, 0, arg0, 0);
            for (i = 0; i < count; i++) {
                if (*(short *)(D_L20_001C4480[i] + 0xAA) == 0x11E0) {
                    func_L20_00449AE8(arg0);
                    return;
                }
            }
        }
    }
    {
        TI128 a;
        TI128 b;
        char *p = arg0 + 0x10;

        func_L20_00444C18(*(char **)(state + 0xA4), (char *)&a);
        FastVecSub(&b, p, (char *)&a);
        if (vec_length_xy(&b) < D_L20_001B23F0) {
            func_00282F70(&b, &b, D_L20_001B23F0);
            FastVecAdd(p, &b, &a);
            qcopy(state + 0x60, p);
            func_002C9218(*(int *)(state + 0xA0), p, p, 0.5f);
        }
    }
}
