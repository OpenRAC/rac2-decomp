#include "include_asm.h"
#include "common.h"

/* Reward slots: a spawn kind is available while value has not reached limit. */
typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot D_L05_002A1800[];
/* Spawn counters: [22..27] per kind, [28] the total. */
extern int D_L05_00221D10[];
extern int D_001A79F0 __attribute__((sda));
extern int D_0013A148[];
extern int func_002A77E0(int);
extern int func_002ED8A0(int);
/* The spawners return the new object, or 0. */
extern char *func_L05_003CD1A8(char *);
extern char *func_L05_00425FE0(char *);
extern char *func_L05_00426568(char *);
extern char *func_L05_00426B08(char *);
extern void func_L05_003CFC48(char *);
extern int D_L05_001AFBF0 __attribute__((sda));
extern char *func_L05_0041C118(char *);

/* Drops a reward after the four-way roll, or while the manager latch is clear.
   Unavailable kinds fall back to another drop. A nonzero bonus independently
   adds a second roll, with its per-level chance in 100 capped at 11.
   Known callers also pass a third argument, unused by this body. */
/* Randomly picks and drops a reward when something is destroyed, with an extra chance of a
   bonus drop. */
void func_L05_003CFCF0(char *object, int bonus, int unused)
{
    int slot;
    int chance;

    if (RandomIntBelow(4) == 0 || D_L05_001AFBF0 == 0) {
        int choice = RandomIntBelow(48);
        D_L05_001AFBF0 = 1;
        switch (choice) {
        case 0: case 1: case 2: case 3:
            slot = FindLastUsedChainEntry(6);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            D_L05_00221D10[24]++;
            D_L05_00221D10[28]++;
            break;
        case 5:
            slot = FindLastUsedChainEntry(2);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto fallback;
            SpawnMobyClass117C(object);
            D_L05_00221D10[26]++;
            D_L05_00221D10[28]++;
            break;
        case 6:
            slot = FindLastUsedChainEntry(3);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto fallback;
            SpawnMobyClass117D(object);
            D_L05_00221D10[22]++;
            D_L05_00221D10[28]++;
            break;
        case 7:
            slot = FindLastUsedChainEntry(4);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit) {
        case 4:
        fallback:
                func_L05_003CFC48(object);
                break;
            }
            SpawnMobyClass117F(object);
            D_L05_00221D10[27]++;
            D_L05_00221D10[28]++;
            break;
        default:
        ordinary:
            SpawnHomingPickup(object);
            D_L05_00221D10[23]++;
            D_L05_00221D10[28]++;
            break;
        }
    }
    if (bonus) {
        chance = D_0013A148[gCurrentMapIndex] * 2;
        if (chance > 11)
            chance = 11;
        if (chance >= RandomIntBelow(100)) {
            func_L05_003CD1A8(object);
            D_L05_00221D10[24]++;
            D_L05_00221D10[28]++;
        }
    }
}
