#include "include_asm.h"

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float lane[4]; } Vector;
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_PAL_L00_00328480(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);
extern void func_PAL_L00_003281C0(void *, int, float);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(void *);

/* Idle, active, and terminal states of an effect emitter. */
void func_PAL_L06_003C8D60(unsigned char *object)
{
    int *state = *(int **)(object + 0x68);
    Vector velocity;
    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002A9640(object, 0x4010000, 0) != 0 && state[0] == 0)
            func_002A7750(object, 2, -1);
        object[0xa8] = 0xff;
        break;
    case 2:
        velocity.whole = 0;
        velocity.lane[2] = -0.060000002f;
        func_PAL_L00_00328480(object, object + 0x10, 0x12, 1, &velocity, 0x80404040, 0,
                          1.5f, 3.0f, 0.75f, 1.5f);
        func_PAL_L00_003281C0(object, 1, 0.0f);
        func_002E5CF8(0, 0, (char *)object);
        func_0029F338(object);
        break;
    }
}
