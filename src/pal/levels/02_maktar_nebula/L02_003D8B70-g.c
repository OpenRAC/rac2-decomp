#include "include_asm.h"

#include "common.h"
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int D_0018C2EC;
extern int D_001A7A00 MACRO_ADDR;
extern float func_002A7878(float, float);

void func_PAL_L02_003D8B70(char *self, int previous) {
    int mode = *(unsigned char *)(self + 0x95);
    char *state = *(char **)(self + 0x68);
    float elapsed;
    float fraction;
    float choice;
    if (mode == 1) {
        fraction = ((float)*(short *)(state + 0x24) - *(float *)(state + 0x20)) / (float)*(short *)(state + 0x24);
        elapsed = (float)((D_001A7A00 - D_0018C2EC) / D_001A7A00);
        choice = elapsed - fraction + func_002A7878(-0.2f, 0.2f);
        {
            if (previous != mode && (choice < 0.0f || previous == -1)) {
                if (func_002A77E0(2)) {
                    if (*(unsigned char *)(self + 0x43) != 5)
                        func_PAL_002A7E68(self, 5, 0, 8);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 6)
                        func_PAL_002A7E68(self, 6, 0, 8);
                }
            } else {
                if (func_002A77E0(2)) {
                    if (*(unsigned char *)(self + 0x43) != 7)
                        func_PAL_002A7E68(self, 7, 0, 8);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 8)
                        func_PAL_002A7E68(self, 8, 0, 8);
                }
            }
        }
    }
    if (*(unsigned char *)(self + 0x95) == 2) {
        if (func_002A77E0(2)) {
            if (*(unsigned char *)(self + 0x43) != 20)
                func_PAL_002A7E68(self, 20, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0x43) != 19)
                func_PAL_002A7E68(self, 19, 0, 8);
        }
    }
    *(short *)(state + 0x324) = *(unsigned char *)(self + 0x20);
    *(short *)(state + 0x326) = *(unsigned char *)(self + 0x95);
    func_002A7750(self, 10, *(unsigned char *)(self + 0x95));
}
