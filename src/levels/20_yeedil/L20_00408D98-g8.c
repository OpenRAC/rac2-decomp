#include "common.h"

extern char *D_L20_001B2F9C;
extern char *D_L20_001B308C;
extern float D_L20_001B29E0 MACRO_ADDR;
extern void func_L20_004095D0(char *);
extern u32 D_L20_001CA540 __attribute__((nosda));
extern float D_L20_001B2BE8;
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0019B2E8[];
extern float D_00189EA0[];
extern int D_L20_001A8F08;
extern int D_L20_001A8F00;
extern int func_0029B3E0(int, int);
extern void func_L01_00323310(int, int);
extern void func_L00_00303530(int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002A0430(unsigned int);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_L20_00409480(s32);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002B3868(u8 *);
extern int func_00282948(int *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L20_002DC390(int);

/* The platform controller records switch edges and raises its linked platform. */
void func_L20_00408D98(u8 *moby) {
    s32 *state = *(s32 **)(moby + 0x68);
    int saveOffset;

    if (D_L20_001CA540 < 2) D_L20_001B2BE8 = 85.0f;
    switch (moby[0x20]) {
    case 0: {
        char *otherMoby;
        saveOffset = gCurrentMapIndex * 16;
        state[8] = D_L20_001CA540;
        state[5] = 0;
        state[4] = 0;
        state[0x23] = D_0019B2E8[state[2] + saveOffset] >> 7;
        if ((D_0019B2E8[state[1] + saveOffset] & 0x80) == 0) {
            state[0x1F] = 0;
            otherMoby = (char *)((state[0x1C] << 8) + (u32)D_L20_001B2F9C);
            *(float *)(state + 0x1D) = *(float *)(otherMoby + 0x18);
            *(float *)(otherMoby + 0x18) += 20.0f;
        } else state[0x1F] = 1;
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1: {
        char *otherMoby;
        if (state[0x23] == 0 &&
            (D_0019B2E8[state[2] + gCurrentMapIndex * 16] & 0x80) != 0 &&
            IsPointInCuboid(gHeroPosition, state[10]) != 0) {
            state[0x23] = 1;
            MemcardSave(0, -1);
        }
        if (D_L20_001CA540 == 2) {
            if (state[4] == 0) {
                if (IsPointInCuboid(gHeroPosition, state[0x18])) {
                    state[4] = 1;
                    QueueKeyedRequest(state[0x20], -1);
                }
            }
        }
        if (IsPointInCuboid(gHeroPosition, state[11]) != 0) {
            if (D_0019B2E8[state[1] + gCurrentMapIndex * 16] & 0x80) return;
            MarkTableEntryFlagged(state[1]);
            if (state[0x13] >= 0)
                SetObjectFlagBit((u8 *)D_L20_001B2F9C + state[0x13] * 0x100, 1);
            DestroyGroupTrooperLegs(state[0x14]);
            DestroyGroupTrooperLegs(state[0x15]);
            state[8] = 2;
            state[15] = 3;
            SetMobyState(moby, 5, -1);
        }
        if (D_0019B2E8[state[1] + gCurrentMapIndex * 16] & 0x80) return;
        if (*(u8 *)(D_L20_001B2F9C + state[0x1B] * 0x100 + 0xBC) == 1) return;
        if (state[0x1F] != 0) return;
        otherMoby = D_L20_001B2F9C + state[0x19] * 0x100;
        if (otherMoby != 0 && *(s16 *)(otherMoby + 0xAA) == 0xCBC /* Megacorp Hover Tank */ &&
            *(u8 *)(otherMoby + 0x20) != 0xFE && *(u8 *)(otherMoby + 0x20) != 0xFD) return;
        otherMoby = D_L20_001B2F9C + state[0x1A] * 0x100;
        if (otherMoby != 0 && *(s16 *)(otherMoby + 0xAA) == 0xCBC /* Megacorp Hover Tank */) {
            int status = *(u8 *)(otherMoby + 0x20);
            if (status != 0xFE && *(u8 *)(otherMoby + 0x20) != 0xFD) return;
        }
        SetMobyState(moby, 7, -1);
        break;
    }
    case 2:
    case 3:
        if (SetFirstPendingFlag(moby)) state[5] = 125;
        if (FastFloatHelperD(state + 5)) goto movement_done;
        if (moby[0x20] == 2) *(float *)(state + 3) = 1.0f - (float)state[5] * 0.008f;
        else *(float *)(state + 3) = (float)state[5] * 0.008f;
        goto movement_callback;
movement_done:
        SetMobyState(moby, state[7], -1);
movement_callback:
        AddDrawCallbackToList3((void (*)(void *))SetScaledSpeedCapped, moby);
        break;
    case 4: {
        char *otherMoby;
        s32 *entry = (s32 *)((u32)state + (state[15] * 4));
        otherMoby = D_L20_001B308C + entry[9] * 0x80;
        LoadSceneChunk(state[8], state[0x21]);
        MarkTableEntryFlagged(state[0]);
        ResetHeroPositionAndDirection(otherMoby + 0x30, otherMoby + 0x70, 0x6F, 1);
        LoadYeedilHeroStateByGameMode(0);
        state[7] = 1;
        D_L20_001B29E0 = 1.0f;
        *(float *)(state + 3) = 1.0f;
        AddDrawCallbackToList3((void (*)(void *))SetScaledSpeedCapped, moby);
        SetMobyState(moby, 6, -1);
        break;
    }
    case 5:
        if (D_L20_001A8F08 == -2 && D_L20_001A8F00 != 2) {
            *(float *)(state + 3) = 1.0f;
            AddDrawCallbackToList3((void (*)(void *))SetScaledSpeedCapped, moby);
            if (*(u8 *)(D_L20_001B2F9C + state[0x13] * 0x100 + 0x20) > 0x80)
                SetMobyState(moby, 4, -1);
        }
        state[6]++;
        break;
    case 6: {
        if (D_L20_001A8F00 != 2) {
            D_L20_001B29E0 = 1.0f;
            *(float *)(state + 3) = 1.0f;
            AddDrawCallbackToList3((void (*)(void *))SetScaledSpeedCapped, moby);
        } else D_L20_001B29E0 = 0.0f;
        if (D_L20_001A8F00 != 2) {
            char *mobys = D_L20_001B2F9C;
            if (*(u8 *)(mobys + state[0x12] * 0x100 + 0x20) > 0x80) {
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) &= 0xFFFD;
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) &= 0xFFFD;
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) &= 0xFFBE;
                *(u16 *)(mobys + state[0x17] * 0x100 + 0x34) |= 0x1000;
                {
                    char *first = (char *)((state[0x17] << 8) + (u32)mobys);
                    *(int *)(first + 0x98) = *(int *)(*(char **)(first + 0x24) + 0x10);
                }
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) &= 0xFFBE;
                *(u16 *)(mobys + state[0x16] * 0x100 + 0x34) |= 0x1000;
                {
                    char *second = (char *)((state[0x16] << 8) + (u32)mobys);
                    *(int *)(second + 0x98) = *(int *)(*(char **)(second + 0x24) + 0x10);
                }
                D_L20_001B29E0 = 0.0f;
                SetMobyState(moby, 3, -1);
            }
        }
        state[6]++;
        break;
    }
    case 7: {
        char *otherMoby;
        if (SetFirstPendingFlag(moby)) {
            otherMoby = D_L20_001B2F9C + state[0x1B] * 0x100;
            otherMoby[0xBC] = 1;
            {
                int duration = *(int *)(*(char **)(otherMoby + 0x68) + 0x2C);
                state[0x1F] = 1;
                state[6] = duration;
                state[0x1E] = duration;
            }
        }
        *(float *)(D_L20_001B2F9C + state[0x1C] * 0x100 + 0x18) =
            *(float *)(state + 0x1D) + ((float)state[6] * 20.0f) / (float)state[0x1E];
        if (FastFloatHelperD(state + 6)) SetMobyState(moby, 1, -1);
        break;
    }
    }
}
