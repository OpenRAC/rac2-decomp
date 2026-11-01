#include "include_asm.h"

#include "common.h"
typedef int L06_7270TI __attribute__((mode(TI)));
extern void func_002A7750(unsigned char *, int, int);
extern void func_L00_00322A18(void *, float, float, float);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_00283098(void *, const void *, const void *);
extern void func_PAL_002B15D8(char *, int, float *, unsigned char, float, float, float, float);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(void *);

void func_PAL_L06_0045C390(unsigned char *m)
{
    int *v = *(int **)(m + 0x68);
    int state = m[0x20];
    float t[4] __attribute__((aligned(16)));
    unsigned char *r;
    unsigned char *o;

    switch (state) {
    case 0:
        *v = 0;
        func_002A7750(m, 1, -1);
        break;
    case 1:
        func_L00_00322A18(m, 0.0f, 0.0f, 0.020943955f);
        r = func_002A9640(m, 0x4010000, 0);
        if (r != 0) {
            o = *(unsigned char **)(r + 0x20);
            if (o != 0 && *(short *)(o + 0xAA) == 0x12C4) {
                *v = state;
            }
            func_002A7750(m, 2, -1);
        }
        m[0xA8] = 0xFF;
        break;
    case 2:
        *(L06_7270TI *)t = 0;
        if (*v != 0) {
            t[0] = -0.20000002f;
        } else {
            t[0] = 0.20000002f;
        }
        func_00283098(t, t, m + 0xC0);
        func_PAL_002B15D8((char *)m, 7, t, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(0, 0, (char *)m);
        func_0029F338(m);
        break;
    }
}
