#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern void moby_set_state(u8 *, u8, int);

/* Sets up the object the first time it runs: places it at a fixed spot and starts its first state. */
void counter_effect_init_position(u8 *object) {
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
        moby_set_state(object, 1, 0);
    }
}
