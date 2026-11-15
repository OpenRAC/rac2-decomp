#include "common.h"
extern float D_L07_001B0FD8 SDATA(D_L07_001B0FD8);
extern float D_L07_001B0FDC[] NOT_SDA;
extern float func_002A78D8(float, float);
extern void func_002A7750(void *, int, int);

/* Sets up a newly spawned homing bomb: places it, remembers who made it, picks a random turn, and switches it to state 2. */
void func_L07_003F6C40(char *object, int owner, void *position, float restYaw)
{
    char *state = *(char **)(object + 0x68);
    *(int *)(object + 0xb8) = owner;
    qcopy(object + 0x10, position);
    qzero(state + 0x50);
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(float *)(state + 0x60) = restYaw;
    *(float *)(state + 0x64) = RandomSignedFloatRange(D_L07_001B0FD8, D_L07_001B0FDC[0]) * 0.01745329424738884f;
    *(unsigned short *)(object + 0x34) = (*(unsigned short *)(object + 0x34) & 0xffbe) | 0x1000;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    SetMobyState(object, 2, -1);
}
