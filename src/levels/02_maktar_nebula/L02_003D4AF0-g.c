#include "common.h"

/* Timed state step; the -g line labels give the pre-division nop. */

extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int D_0018C2EC;
extern int D_001A7A00 MACRO_ADDR;
extern float func_002A7878(float, float);

/* Picks a random idle animation for the current phase, avoiding the one already playing, and records the state. */
void func_L02_003D4AF0(char *self, int previous) {
    int phase = *(unsigned char *)(self + 0x95);
    char *state = *(char **)(self + 0x68);
    float elapsed;
    float fraction;
    float choice;
    if (phase == 1) {
        fraction = ((float)*(short *)(state + 0x24) - *(float *)(state + 0x20)) / (float)*(short *)(state + 0x24);
        elapsed = (float)((D_001A7A00 - D_0018C2EC) / D_001A7A00);
        choice = elapsed - fraction + RandomFloatRange(-0.2f, 0.2f);
        {
            if (previous != phase && (choice < 0.0f || previous == -1)) {
                if (RandomIntBelow(2)) {
                    if (*(unsigned char *)(self + 0x43) != 5)
                        StartAnimationBlended(self, 5, 0, 10);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 6)
                        StartAnimationBlended(self, 6, 0, 10);
                }
            } else {
                if (RandomIntBelow(2)) {
                    if (*(unsigned char *)(self + 0x43) != 7)
                        StartAnimationBlended(self, 7, 0, 10);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 8)
                        StartAnimationBlended(self, 8, 0, 10);
                }
            }
        }
    }
    if (*(unsigned char *)(self + 0x95) == 2) {
        if (RandomIntBelow(2)) {
            if (*(unsigned char *)(self + 0x43) != 20)
                StartAnimationBlended(self, 20, 0, 10);
        } else {
            if (*(unsigned char *)(self + 0x43) != 19)
                StartAnimationBlended(self, 19, 0, 10);
        }
    }
    *(short *)(state + 0x324) = *(unsigned char *)(self + 0x20);
    *(short *)(state + 0x326) = *(unsigned char *)(self + 0x95);
    SetMobyState(self, 10, *(unsigned char *)(self + 0x95));
}
