#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L00_00322A18(void *, float, float, float);
extern void func_PAL_002B15D8(char *, int, char *, float, float, float, float, int);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);

void func_PAL_L06_0045C220(char *a0)
{
    int state = *(unsigned char *)(a0 + 0x20);
    char *o = *(char **)(a0 + 0x68);
    float vec[4];
    char *p;
    char *m;

    switch (state) {
    case 0:
        *(int *)(o + 4) = 0;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        func_L00_00322A18(a0, 0.0f, 0.0f, -(*(float *)o * 0.0003490659f));
        p = func_002A9640(a0, 0x4010000, 0);
        if (p != 0) {
            m = *(char **)(p + 0x20);
            if (m != 0 && *(short *)(m + 0xAA) == 0x12C4) {
                *(int *)(o + 4) = state;
            }
            func_002A7750(a0, 2, -1);
        }
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        if (*(int *)(o + 4) != 0) {
            vec[0] = -0.20000002f;
        } else {
            vec[0] = 0.20000002f;
        }
        func_PAL_002B15D8(a0, 0x1FE, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        func_002E5CF8(0, 0, a0);
        func_0029F338(a0);
        break;
    }
}
