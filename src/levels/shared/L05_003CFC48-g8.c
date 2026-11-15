#include "common.h"

typedef struct { char pad[16]; int limit,value; char tail[16]; } RewardSlot;
extern RewardSlot D_L05_002A1800[];
extern int D_L05_00221D10[];
extern int table_find_last_used_entry(int);
extern char *pickup_spawn_homing(char *);
extern char *pickup_spawn_homing_variant(char *);

/* Drops a reward, choosing a different kind if the first kind is already full, and counts it. */
void func_L05_003CFC48(char *object)
{
    int slot=table_find_last_used_entry(1);
    if(slot<0 || D_L05_002A1800[slot].value==D_L05_002A1800[slot].limit) {
        pickup_spawn_homing(object);
        D_L05_00221D10[23]++;
        D_L05_00221D10[28]++;
    } else {
        pickup_spawn_homing_variant(object);
        D_L05_00221D10[25]++;
        D_L05_00221D10[28]++;
    }
}
