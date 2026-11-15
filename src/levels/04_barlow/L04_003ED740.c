#include "common.h"

typedef struct {
    char pad[0x284];
    char *target;
    int timer;
} HeroD740;

extern char *D_L04_001B24DC __attribute__((sda));
extern char *D_L04_001B25CC[] __attribute__((sda));
extern char D_00189EA0[], D_00188660[];
extern HeroD740 D_L04_001B9540;
extern u8 D_0019B2E8[];
extern char *D_0018C0B0;
extern int D_001A79F0 __attribute__((sda));
extern int func_002A8508(int, int);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002ACBC8(void *, int);
extern void func_L00_00429020(int);
extern int func_L00_00429048(int);
extern void func_002A0430(unsigned int);
extern void func_002DF3F8(void *, void *);
extern int func_L00_0035F5A0(int, int, void *);
extern void func_L00_003294F0(void *, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_002E59F8(int);

/* Controls a sequence of linked objects: waits for them to finish, plays a camera move, then puts the player at a saved spot. */
void func_L04_003ED740(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0x20) = 1;
        break;
    case 1: {
        int i, busy;

        busy = 0;
        for (i = 0; i < 4; i++)
            if (CountMobysInGroupNotInState(*(int *)(vars + 4 * i), -1))
                busy = 1;
        if (!busy) {
            if (*(int *)(vars + 0x18) == 0) {
                char *partA, *partB;

                partA = gMobyPool_L04 + (*(int *)(vars + 0x74) << 8);
                partB = gMobyPool_L04 + (*(int *)(vars + 0x78) << 8);
                if (*(u8 *)(partA + 0x20) == 1)
                    PlaySoundFromClassBank(0, 0, partA, 0xCE6);
                *(u8 *)(partA + 0x20) = 2;
                *(u8 *)(partB + 0x20) = 2;
                if (IsPointInCuboid(gHeroPosition, *(int *)(vars + 0x70)) &&
                    !(D_0019B2E8[*(u8 *)(moby + 0xB0) + gCurrentMapIndex * 16] & 128)) {
                    LockCameraEntry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 2;
                    *(u8 *)(partA + 0x20) = 3;
                    *(u8 *)(partB + 0x20) = 3;
                }
            } else if (*(int *)(vars + 0x18) == 1) {
                char *partA, *partB;

                if (!(D_0019B2E8[*(u8 *)(moby + 0xB0) + gCurrentMapIndex * 16] & 128)) {
                    LockCameraEntry(*(int *)(vars + 0x10));
                    *(u8 *)(moby + 0x20) = 4;
                    partA = gMobyPool_L04 + (*(int *)(vars + 0x74) << 8);
                    partB = gMobyPool_L04 + (*(int *)(vars + 0x78) << 8);
                    PlaySoundFromClassBank(0, 0, partA, 0xCE6);
                    *(u8 *)(partA + 0x20) = 2;
                    *(u8 *)(partB + 0x20) = 2;
                    if (!(D_0019B2E8[*(u8 *)(moby + 0xB0) + gCurrentMapIndex * 16] & 128)) {
                        MarkTableEntryFlagged(*(u8 *)(moby + 0xB0));
                        CaptureCheckpointState(moby + 0x10, moby + 0xF0);
                    }
                }
            }
        } else if (*(int *)(vars + 0x18) == 0 &&
                   IsPointInCuboid(gHeroPosition, *(int *)(vars + 0x70)) &&
                   !(D_0019B2E8[*(u8 *)(moby + 0xB0) + gCurrentMapIndex * 16] & 128)) {
            LockCameraEntry(*(int *)(vars + 0x10));
            *(u8 *)(moby + 0x20) = 2;
        }
        break;
    }
    case 2: {
        if (IsCameraTriggerReady(*(int *)(vars + 0x10))) {
            *(signed char *)(moby + 0x95) = StartEffectInSlot(23, 4, gHeroMoby_0018C0B0);
            {
                char *mobyTable = gMobyPool_L04;
                int i;

                for (i = 0; i < 14; i++) {
                    char *partA, *partVars;
                    int partId = *(int *)(vars + 0x20 + i * 4);

                    if (partId != -1) {
                        partA = mobyTable + (partId << 8);
                        if (partA) {
                            partVars = *(char **)(partA + 0x68);
                            *(int *)(partVars + 0x260) = *(int *)(partVars + 0x264);
                            *(int *)(partVars + 0x250) = *(int *)(partVars + 0x254);
                            *(int *)(partA + 0x98) = *(int *)(*(char **)(partA + 0x24) + 0x10);
                            *(u16 *)(partA + 0x34) &= 0xFFBE;
                        }
                    }
                }
            }
            {
                char *partA = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(gHeroPosition, partA + 0x30);
                qcopy(gHeroPosition + 0x10, partA + 0x70);
                SetObjectFlagBit(moby, 1);
                *(u16 *)(moby + 0x96) = 0;
                *(u8 *)(moby + 0x20) = 5;
            }
        }
        break;
    }
    case 3: {
        char *partA, *partB;

        if (IsCameraTriggerReady(*(int *)(vars + 0x10))) {
            {
                char *spot = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);

                qcopy(gHeroPosition, spot + 0x30);
                spot += 0x70;
                qcopy(gHeroPosition + 0x10, spot);
            }
            partA = gMobyPool_L04 + (*(int *)(vars + 0x20) << 8);
            partB = gMobyPool_L04 + (*(int *)(vars + 0x24) << 8);
            *(u8 *)(partA + 0x95) = 4;
            *(u8 *)(partA + 0x20) = 17;
            if (!D_L04_001B9540.target) {
                D_L04_001B9540.target = partB;
                D_L04_001B9540.timer = 0;
            }
            *(int *)(partA + 0x98) = *(int *)(*(char **)(partA + 0x24) + 0x10);
            {
                char *partBVars = *(char **)(partB + 0x68);
                *(int *)(partBVars + 0x270) = *(int *)(partBVars + 0x274);
            }
            {
                char *partAVars = *(char **)(partA + 0x68);
                *(int *)(partAVars + 0x270) = *(int *)(partAVars + 0x274);
            }
            *(u8 *)(moby + 0x20) = 5;
        }
        break;
    }
    case 4: {
        char *partA;

        if (IsCameraTriggerReady(*(int *)(vars + 0x10))) {
            partA = D_L04_001B25CC[0] + (*(int *)(vars + 0x14) << 7);
            ResetHeroPositionAndDirection(partA + 0x30, partA + 0x70, 111, 1);
            *(u8 *)(moby + 0x20) = 5;
            SetObjectFlagBit(moby, 1);
        }
        break;
    }
    case 5: {
        if (*(u16 *)(moby + 0x96) < 60)
            ++*(u16 *)(moby + 0x96);
        else if (IsCameraTriggerReady(*(int *)(vars + 0x10))) {
            int i = *(signed char *)(moby + 0x95);

            if (i != -1) {
                char *partA = (char *)gSoundState + i * 0x70;
                if (*(char **)(partA + 0x88) == gHeroMoby_0018C0B0 && *(u8 *)(partA + 0x74))
                    StopSoundVoice(i);
            }
            i = -1;
            *(signed char *)(moby + 0x95) = i;
        }
        break;
    }
    }
}
