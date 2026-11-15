#include "common.h"

typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot D_L10_002A3C70[];
extern int D_L10_00221CD0[];
extern int D_001A79F0 __attribute__((sda));
extern int D_0013A148[];
extern int func_002A77E0(int);
extern int func_002ED8A0(int);
extern char *func_L05_003CD1A8(char *);
extern char *func_L05_00425FE0(char *);
extern char *func_L05_00426568(char *);
extern char *func_L05_00426B08(char *);
extern void func_L10_0042E5B8(char *);
extern char *func_L05_0041C118(char *);
extern int D_L10_001B17A0 __attribute__((sda));

/* Select an available reward kind, update the per-kind and total spawn counts,
 * and optionally roll an additional reward using the current level chance. */
void func_L10_0042E660(char *object, int bonus)
{
    int slot;
    int chance;

    if (RandomIntBelow(*(int *)(*(char **)(object + 0x68) + 0x14)) == 0 || !D_L10_001B17A0) {
        slot = RandomIntBelow(48);
        D_L10_001B17A0 = 1;
        switch (slot) {
        case 0: case 1: case 2: case 3:
            slot = FindLastUsedChainEntry(6);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            D_L10_00221CD0[24]++;
            D_L10_00221CD0[28]++;
            break;
        case 5:
            slot = FindLastUsedChainEntry(2);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto fallback;
            SpawnMobyClass117C(object);
            D_L10_00221CD0[26]++;
            D_L10_00221CD0[28]++;
            break;
        case 6:
            slot = FindLastUsedChainEntry(3);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit)
                goto fallback;
            SpawnMobyClass117D(object);
            D_L10_00221CD0[22]++;
            D_L10_00221CD0[28]++;
            break;
        case 7:
            slot = FindLastUsedChainEntry(4);
            if (slot < 0 || D_L10_002A3C70[slot].value == D_L10_002A3C70[slot].limit) {
        case 4:
        fallback:
                func_L10_0042E5B8(object);
                break;
            }
            SpawnMobyClass117F(object);
            D_L10_00221CD0[27]++;
            D_L10_00221CD0[28]++;
            break;
        default:
        ordinary:
            SpawnHomingPickup(object);
            D_L10_00221CD0[23]++;
            D_L10_00221CD0[28]++;
            break;
        }
    }
    if (bonus) {
        chance = D_0013A148[gCurrentMapIndex] * 2;
        if (chance > 11)
            chance = 11;
        if (chance >= RandomIntBelow(100)) {
            func_L05_003CD1A8(object);
            D_L10_00221CD0[24]++;
            D_L10_00221CD0[28]++;
        }
    }
}
