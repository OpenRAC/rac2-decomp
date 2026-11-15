#include "include_asm.h"
#include "names.h"

/* func_L02_00423520 is a unit of its own: retail clears its vector as plain C, with the zero
   materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));

extern int D_L02_001AEC78 __attribute__((sda));
extern float D_L02_001B2020 __attribute__((sda));
extern float D_L02_001B2020_1[8] __attribute__((sda));
extern float D_L02_001B2040 __attribute__((sda));
extern float D_L02_001B2040_1[4] __attribute__((sda));

extern void func_0029F648(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L00_00326110(void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_00273730(char *, int, int, int, char *, char *, float *, float, float, int);
extern void func_L00_003263D0(char *, char *, float, int, int, char *, float, int, int, float, float);
extern void func_L02_00423838(u8 *, float, float);

/* A breakable object (moby class 3341). It waits to be hit, then flies apart into pieces with a puff of sparks, and goes away. */
void func_L02_00423520(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    float velocity[4];
    float backDir[4];
    int firstValue, secondValue, partMask, unusedValue;
    int i;
    float sizeA, sizeB;

    switch (moby[0x20]) {
    case 0:
        GetMobyAnimationEntryCount(moby, &firstValue, &secondValue);
        *(u16 *)(moby + 0x7C) = firstValue;
        *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x1000;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) != 0) {
            gHoveringObjectCount = gHoveringObjectCount - 1;
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        *(u16 *)(moby + 0x7C) = 0;
        *(int *)state = 0x78;
        *(int *)(moby + 0x98) = 0;
        SpawnScaledBolts(moby, 1, 1.0f);
        GetMobyAnimationEntryCount(moby, &partMask, &unusedValue);
        PlayMobySound(0, 0, moby);
        for (i = 0; i < 16; i++) {
            if ((partMask >> i) & 1) {
                sizeA = RandomFloatRange(D_L02_001B2040, D_L02_001B2040_1[1]);
                sizeB = RandomFloatRange(D_L02_001B2040_1[2], D_L02_001B2040_1[3]);
                velocity[0] = RandomFloatRange(D_L02_001B2020, D_L02_001B2020_1[4]) * 0.016666668f;
                velocity[1] = RandomSignedFloatRange(D_L02_001B2020_1[1], D_L02_001B2020_1[5]) * 0.016666668f;
                velocity[2] = RandomFloatRange(D_L02_001B2020_1[2], D_L02_001B2020_1[6]) * 0.016666668f;
                matrix_mul_vec3(velocity, velocity, moby + 0xC0);
                CreateCameraMoby((char *)moby, 2, 0xD0D /* moby class 3341 */, i, (char *)(moby + 0x10), (char *)(moby + 0xF0), velocity, sizeB, sizeA, 0xFF);
            }
        }
        *(TI128 *)velocity = 0;
        velocity[0] = -0.8f;
        velocity[2] = 1.5f;
        matrix_mul_vec3(velocity, velocity, moby + 0xC0);
        FastVecAdd(velocity, velocity, moby + 0x10);
        vec_scale_to_length(backDir, moby + 0xC0, -0.083333336f);
        SpawnTintedEffects((char *)moby, (char *)velocity, 0.25f, 4, 1, (char *)backDir, 5.0f, 0x50404040, 0, 0.5f, 1.0f);
        ThrowSparkBurst(moby, -0.083333336f, -0.25f);
        SetMobyState(moby, 3, -1);
        break;
    }
    moby[0xA8] = 0xFF;
}
