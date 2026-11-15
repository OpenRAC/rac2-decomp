#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern u16 D_L18_001B18FC __attribute__((sda));

extern float D_L18_001B191C __attribute__((sda));

extern void *func_0029EFD0(short a);

extern float func_00283248(float a, float b);

extern void func_002A0F48(void *a);

extern int func_002A7750(void *, int, int);

extern void *func_002A9640(void *, s32, s32);

extern void func_0029F338(void *);

extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32,
                              s32, s32, s32);

extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, s32);

extern float D_L18_001B1D30 __attribute__((sda));

extern float D_L18_001B1D38 __attribute__((sda));

extern float D_L18_001B1D40 __attribute__((sda));

/* A breakable object: it waits to be hit, then releases a burst of items and an explosion and disappears. */
void func_L18_004412F0(u8 *moby) {
    s32 state = moby[0x20];
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 one = 1;
    switch (state) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x04010000, 0) != 0 && *(s32 *)vars == 0) {
            SetMobyState(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        s32 mask = 0xFFFF;
        ExplodeObjectIntoPieces(moby, &D_L18_001B1D40, &D_L18_001B1D38,
                          &D_L18_001B1D30, 0xFFFF, 0, -1, 0, mask, 0xFF, 0);
        SpawnExplosion(moby + 0x10, 0, 5, 5, 5, 5, 5, 0,
                      *(float *)(moby + 0x2C) * 10.0f, 20.0f, one, 0, one, 0);
        MarkMobySpawned(moby);
        break;
    }
    }
}
