#include "include_asm.h"
#include "common.h"

extern float D_L19_001B1D28 __attribute__((sda));

extern void func_2EB590();

extern void func_3238E0(void *, void *, int, int, float);

/* Ticks two timers in the object's data, counts up its age, and refreshes its attached effect. */
void func_L19_0041C2B8(char *moby)
{
    char *mobyPtr = moby;
    int varsAddr = *(int *)(mobyPtr + 0x68);

    func_2EB590(varsAddr + 0x230);
    func_2EB590(varsAddr + 0x234);
    if (*(unsigned short *)(mobyPtr + 0x96) < 0xFFFF) {
        *(unsigned short *)(mobyPtr + 0x96) += 1;
    }
    func_3238E0(mobyPtr, varsAddr + 0x2A0, 1, 1, D_L19_001B1D28);
}

extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern char D_L19_001BFC40[];

extern void func_4239B8(char *a0);
extern void func_30DFE8(char *a0);
extern void func_318240(char *a0, s32 a1, s32 a2);
extern void func_31A620(char *a0);
extern s32 func_31E128(char *a0, s32 a1);
extern s32 func_2F1940(char *a0, s32 a1);
extern void func_32C2E8(char *a0);
extern void func_2F1A88(char *a0);
extern s32 func_36E868(void);
extern void func_31F110(s32 a0);
extern void func_321BB0(s32 a0);
extern void func_2BBFD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_30FC48(s32 a0);
extern void func_356928(char *a0, char *a1);
extern void func_309FB8(s32 a0, s32 a1);

/* Per-frame update for a warp trigger (class 4711). When triggered it fades the screen and moves the hero to a linked spot. */
void func_L19_00423A98(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    u8 id;

    func_4239B8(moby);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            func_30DFE8(moby);
        } else {
            func_318240(moby, 1, -1);
            func_31A620(moby);
        }
        break;
    case 1:
        if (func_31E128(gHeroPosition, *(s32 *)(vars + 0x120)) != 0) {
            if (func_2F1940(D_L19_001BFC40, 0x96) != 0) {
                func_2F1940(D_L19_001BFC40, 0x14);
                func_2F1940(D_L19_001BFC40, 0x97);
                func_32C2E8(moby);
                func_2F1A88(D_L19_001BFC40);
                func_318240(moby, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(moby + 0x31) = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (func_36E868() == 0) {
            D_L19_001B2724[1] = 0;
            func_31F110(0x14);
            func_321BB0(0x14);
            func_2BBFD8(D_L19_001B2B0C[0] + (*(s32 *)(vars + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(vars + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            *(u8 *)(moby + 0x31) = 1;
            if (*(u8 *)(moby + 0xB0) != 0xFF) {
                id = *(u8 *)(moby + 0xB0);
                if ((D_0019B2E8[id + (gCurrentMapIndex[0] << 4)] & 0x80) == 0)
                    func_30FC48(id);
                func_356928(gHeroPosition, gHeroPosition + 0x10);
                func_309FB8(0, -1);
            } else {
                func_309FB8(0, -1);
            }
            func_30DFE8(moby);
        }
        break;
    }
}

extern float D_L19_001B1EB0 __attribute__((sda)), D_L19_001B1EB4 __attribute__((sda));
extern float D_L19_001B1EB8 __attribute__((sda)), D_L19_001B1EBC __attribute__((sda));
extern float D_L19_001B1EC0 __attribute__((sda)), D_L19_001B1EC4 __attribute__((sda));
extern float D_L19_001B1EC8 __attribute__((sda));
/* The hero: its state word and another mode word. */
typedef struct {
    char pad0[0x2294];
    int state;
    int pad2298;
    int mode;
} HeroModes;
extern HeroModes D_00189E20;
extern u8 D_0019B4A8[];
/* Player stats: the pending bolt credit at +0x1C. */
typedef struct { u8 pad0[0x1C]; int pendingBolts; } PlayerStats;
extern PlayerStats D_001A7A00 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L19_001A903C[] MACRO_ADDR;
extern void func_002A7470(void *, int, int, int);
extern void func_L19_00423270(void *);
extern float func_00282E80(void *, void *);
extern float func_00282C48(float);
extern float func_00282E20(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern void func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002E5E58(int, int, void *);
extern int func_L19_0042A860(void);
extern void func_002B0A18(int, int);

/* A pickup that floats until the hero is close, then flies to the hero, shrinks, and adds a bolt when it arrives. */
void func_L19_00423548(u8 *object)
{
    float direction[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    float distance, movement, threshold;
    switch (object[0x20]) {
    case 0:
        object[0x23] = 0x80;
        *(u32 *)(object + 0x78) = 0xFFAAAAAA;
        *(u16 *)(object + 0x34) |= 0x800;
        object[0x20] = 1;
        if (object[0x43]) StartAnimationBlended(object, 0, 0, 0);
        break;
    case 1:
        if (vec_distance_xy(object + 0x10, gHeroPosition) < D_L19_001B1EB0 &&
            FloatAbs(*(float *)(object + 0x18) - *(float *)(gHeroPosition + 8)) < D_L19_001B1EC0) {
            *(float *)vars = D_L19_001B1EC4;
            if (object[0x43] != 1) StartAnimationBlended(object, 1, 0, 20);
            *(float *)(object + 0x48) = *(float *)vars + *(float *)vars;
            object[0x20] = 2;
        }
        if (object[0x31]) EmitGrelbinGlowSprites(object);
        break;
    case 2:
        if (object[0x43] != 1) StartAnimationBlended(object, 1, 0, 20);
        *(float *)vars += (1.0f - *(float *)vars) * D_L19_001B1EBC;
        *(float *)(object + 0x48) = *(float *)vars + *(float *)vars;
        FastVecSub(direction, gHeroPosition, object + 0x10);
        direction[2] += 0.6f;
        distance = vec_length_xy(direction);
        threshold = 0.12f;
        if (*(int *)(gHeroPosition + 0x2214) != 0x31)
            movement = D_L19_001B1EB4 * (*(float *)vars * 0.016666668f);
        else {
            movement = D_L19_001B1EB8 * (*(float *)vars * 0.016666668f);
            threshold = 0.8f;
        }
        FastVectorDivideHelper(direction, direction, movement);
        FastVecAdd(object + 0x10, object + 0x10, direction);
        if (*(float *)(object + 0x2C) > 0.1f || distance < threshold || distance < movement)
            *(float *)(object + 0x2C) -= D_L19_001B1EC8 * *(float *)(*(u8 **)(object + 0x24) + 0x24);
        if ((distance < movement &&
             *(float *)(object + 0x2C) < *(float *)(*(u8 **)(object + 0x24) + 0x24) * 0.01f) ||
            gHeroState.mode == 0x14 || gHeroState.mode == 0x19 ||
            gHeroState.state == 0x39 || gHeroState.state == 0x6F) {
            if (*(u8 **)(vars + 4)) {
                u8 *linked = *(u8 **)(vars + 4);
                int flagIndex = *(unsigned short *)(linked + 0xB2);
                if (flagIndex & 1) {
                    unsigned char *flagByte = &D_0019B4A8[((short)flagIndex >> 1) + (gCurrentMapIndex[0] << 10)];
                    if (((*flagByte >> 4) & 7) != 7) {
                        *flagByte += 0x10;
                    }
                } else {
                    unsigned char *flagByte = &D_0019B4A8[((short)flagIndex >> 1) + (gCurrentMapIndex[0] << 10)];
                    if ((*flagByte & 7) != 7) {
                        *flagByte += 1;
                    }
                }
                MarkMobySpawned(*(u8 **)(vars + 4));
            }
            D_001A7A00.pendingBolts++;
            PlaySoundFromClassBank(3, 0, object, 0x11C7);
            MarkMobySpawned(object);
            if (!SumThreeCounts() && !D_001A7A60[6]) {
                D_001A7A60[6] = 1;
                PlaySoundFromGlobalBank(1, 0, 0);
                SetEntryValueByIndex(0x1233, -1);
                D_L19_001A903C[0] = 1;
            }
            MarkMobySpawned(object);
        } else EmitGrelbinGlowSprites(object);
        break;
    }
}
