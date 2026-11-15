#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern void func_002A7750(u8 *, u8, int);

/* Sets up the object the first time it runs: places it at a fixed spot and starts its first state. */
void func_L23_0042AD10(u8 *object) {
    float position[4];
    int *state = *(int **)(object + 0x68);
    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x32) = 0x50;
        object[0x30] = 0xFF;
        state[0] = 0;
        state[1] = 0;
        *(Quadword *)position = 0;
        position[0] = 500.0f;
        position[1] = 500.0f;
        position[2] = 585.0f;
        *(Quadword *)(object + 0x10) = *(Quadword *)position;
        SetMobyState(object, 1, 0);
    }
}
