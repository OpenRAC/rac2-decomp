#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern char D_00189E20[] __attribute__((nosda));
extern char *D_L00_001B043C __attribute__((sda));
extern int D_L00_001B2B4C;
extern char *func_0029EFD0(int type);
extern void func_002833F0(void *out, void *vector);
extern int func_002A0F48(void *object);
extern int func_002FED90(void *object, int mode, float x, float y, float z);

/* Spawns the object of type 0xB58 at position with velocity in its state, quarter size, and registers it as the shared one. */
char *func_L00_003DE088(Quad *position, Quad *velocity)
{
    char *object = CreateMoby(0xb58);
    char *state;
    char *base;

    if (object != 0) {
        state = *(char **)(object + 0x68);
        *(short *)(object + 0x32) = 255;
        *(unsigned char *)(object + 0x30) = 255;
        *(Quad *)(object + 0x10) = *position;
        *(Quad *)state = *velocity;
        *(unsigned char *)(object + 0x20) = 0;
        *(unsigned short *)(object + 0x34) |= 0x100;
        *(float *)(object + 0x2c) *= 0.25f;
        base = D_00189E20;
        *(float *)(object + 0xf0) = *(float *)(base + 0x90);
        *(float *)(object + 0xf4) = *(float *)(base + 0x94);
        *(float *)(object + 0xf8) = *(float *)(base + 0x98);
        euler_rotation_basis(object + 0xc0, object + 0xf0);
        *(int *)(state + 0x1c) = 0x7f000000;
        D_L00_001B043C = object;
        func_002A0F48(object);
        D_L00_001B2B4C = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
    }
    return object;
}
