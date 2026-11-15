#include "common.h"

typedef struct { char pad[16]; int limit,value; char tail[16]; } RewardSlot;
extern RewardSlot D_L05_002A1800[];
extern int D_L05_00221D10[];
extern int func_002ED8A0(int);
extern char *func_L05_0041C118(char *);
extern char *func_L05_0041D498(char *);

/* Drops a reward, choosing a different kind if the first kind is already full, and counts it. */
void func_L05_003CFC48(char *object)
{
    int slot=FindLastUsedChainEntry(1);
    if(slot<0 || D_L05_002A1800[slot].value==D_L05_002A1800[slot].limit) {
        SpawnHomingPickup(object);
        D_L05_00221D10[23]++;
        D_L05_00221D10[28]++;
    } else {
        SpawnHomingPickupVariant(object);
        D_L05_00221D10[25]++;
        D_L05_00221D10[28]++;
    }
}
