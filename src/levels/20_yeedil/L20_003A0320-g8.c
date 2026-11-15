#include "common.h"
extern char *D_L20_001B2F9C_1 __attribute__((sda));

extern float D_L20_001B2ACC __attribute__((sda));

/* Retail materializes this vector address independently for the two effect
 * constructors. The two symbol views preserve those separate lifetimes. */
extern char D_L20_001A8F20[];
extern char D_L20_001A8F20_1[];

extern int func_002A9640(char *, int, int);

extern void func_0032F5B0(char *, int, int);

extern void func_L00_00324F18(char *, char *, f32, f32, f32);

extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);

extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);

extern void func_L00_00326110(char *, int, f32);

extern void func_002E5CF8(int, int, char *);

extern int func_002B3868(char *);

extern int func_00282948(char *);

extern void func_0029F338(char *);

/* Updates moby class 4890: waits for its trigger, puts out a burst of effects and a sound, then removes itself after a short timer. */
void func_L20_003A0320(char *mobyArg) {
    char *moby = mobyArg;
    char *vars;
    f32 effectPos[4];
    f32 zero;
    f32 size;
    int value;

    vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        func_0032F5B0(moby, 1, -1);
        break;
    case 1:
        value = FindOwnedEffectSlot(moby, 0x04010000, 0);
        if (value == 0) {
            value = 0xFF;
        } else if (*(int *)vars != 0) {
            value = 0xFF;
        } else {
            func_0032F5B0(moby, 2, -1);
            break;
        }
        *(u8 *)(moby + 0xA8) = value;
        value = *(int *)(vars + 4);
        if (value <= 0) {
            break;
        }
        value = (int)((char *)D_L20_001B2F9C_1 + (value << 8));
        if (value == 0) {
            break;
        }
        {
            s32 mode = *(u8 *)(value + 0x20);
            if (mode == 0xFE) goto changeState;
            if (mode == 0xFD) goto changeState;
            if (mode != 3) break;
        changeState:
            func_0032F5B0(moby, 2, -1);
        }
        break;
    case 2:
        zero = 0.0f;
        size = 3.0f;
        LocalOffsetToWorld(moby, (char *)effectPos, zero, zero, size);
        if (*(u8 *)(moby + 0x31) != 0 && D_L20_001B2ACC < 0.9f) {
            SpawnExplosionEffects(moby, D_L20_001A8F20, effectPos, zero, zero, 10, 3, 16,
                          1.0f, 0.5f, 9.0f, *(f32 *)(moby + 0x2C) * 1.3f, -1, 15.0f,
                          0, 1, -1, 0, 0);
            SpawnDebrisForMaskedParts(moby, 1, (float *)D_L20_001A8F20_1, size, 6.0f, size, 6.0f, 0xFF);
        } else {
            SpawnDebrisForMaskedParts(moby, 1, (float *)D_L20_001A8F20_1, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        SpawnScaledBolts(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        func_0032F5B0(moby, 3, -1);
        break;
    case 3:
        if (SetFirstPendingFlag(moby) != 0) {
            *(u16 *)(moby + 0x34) |= 1;
            *(u32 *)(moby + 0x98) = 0;
            *(u8 *)(moby + 0x31) = 0;
            *(u32 *)(vars + 8) = 0x78;
        }
        if (FastFloatHelperD(vars + 8) != 0) {
            MarkMobySpawned(moby);
        }
        break;
    }
}
