#include "include_asm.h"

extern int func_00283D38(int a, int b, float c);
extern int D_L14_001B259C __attribute__((sda));
extern int func_L00_00324120(char *self);
extern void func_L00_003294F0(int table, int mode);
extern void func_002A7750(char *self, int state, int mode);
extern int func_002B3868(char *self);
extern void func_002E5CF8(int a, int b, char *self);
extern float func_00283B98(float a, float b);
extern float func_00283198(float a);
extern int func_00283D38(int a, int b, float c);

/* Steps the owner's state block, then blends the two colours its state asks for. */
void func_PAL_L14_0040E8C8(char *self)
{
    char *v = *(char **)(self + 0x68);
    int c1 = 0x808C8C8C;
    int c2 = 0x80282828;
    int idx;
    float f;
    int r;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (func_L00_00324120(self) != 0) {
            idx = *(int *)(v + 0);
            if (idx != -1) {
                func_L00_003294F0(D_L14_001B259C + (idx << 8), 1);
            }
            func_002A7750(self, 1, -1);
        }
        break;
    case 1:
        if (func_002B3868(self) != 0) {
            func_002E5CF8(0, 0, self);
        }
        c1 = 0x80468CDC;
        c2 = 0x801E78AA;
        break;
    }
    f = func_00283B98(*(float *)(v + 4), 0.12915438f);
    *(float *)(v + 4) = f;
    r = func_00283D38(c1, c2, func_00283198(f) * 0.5f + 0.5f);
    *(int *)(self + 0x78) = func_00283D38(*(int *)(self + 0x78), r, 0.18f);
}
