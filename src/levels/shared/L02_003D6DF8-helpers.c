#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(u8 *, s32, s32);

extern void func_002833F0(void *, void *);

extern void func_L02_003D6EE0(char *);

extern void func_L00_00323958(void *, void *);

/* The level's own rate, read $gp-relative. */
extern float D_L02_001B0380 __attribute__((sda));

/* Integer duration counter: readers use integer loads; this store is absolute. */
extern int D_L02_001B3FD8 NOT_SDA;

/* Sets up a moving platform when it first appears: sets its turn speed, its timer and its starting state. */
void func_L02_003D6DF8(char *mobyArg) {
    char *moby = mobyArg;
    char *vars = *(char **)(moby + 0x68);
    TI128 rotation[2];
    float seconds;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    *(unsigned char *)(vars + 0x9) = 0;
    *(unsigned char *)(vars + 0x8) = 3;
    *(int *)(vars + 0x10) = 0;
    *(unsigned short *)(moby + 0x34) &= 0xEFFF;
    SetMobyState((u8 *)moby, 2, -1);
    rotation[1] = 0;
    *(float *)&rotation[1] = D_L02_001B0380 * 0.0002908882452175021f;
    rotation[0] = rotation[1];
    euler_rotation_basis((char *)(vars + 0x80), (char *)&rotation[0]);
    seconds = 180.0f / D_L02_001B0380;
    *(unsigned short *)(moby + 0x34) |= 0x100;
    D_L02_001B3FD8 = (int)(seconds * 60.0f);
    FindNearbyRecordForMoby(moby);
    UpdateAttachedObjectTransforms(moby, vars + 0x30);
    *(int *)(vars + 0xBC) = 0;
    *(short *)(vars + 0xC0) = -1;
}
