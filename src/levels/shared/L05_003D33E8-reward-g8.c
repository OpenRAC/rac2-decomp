#include "include_asm.h"
#include "common.h"

/* Reward slots: a spawn kind is available while value has not reached limit. */
typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot D_L05_002A1800[];
/* Spawn counters: [22..27] per kind, [28] the total. */
extern int D_L05_00221D10[];
extern int D_001A79F0 __attribute__((sda));
extern int D_0013A148[];
extern int func_332AB8(int);
extern int func_L05_0037AAC8(int);
/* The spawners return the new object, or 0. */
extern char *func_L05_003CD1A8(char *);
extern char *func_L05_00425FE0(char *);
extern char *func_L05_00426568(char *);
extern char *func_L05_00426B08(char *);
extern void func_L05_00421860(char *);
extern char *func_L05_0041C118(char *);

/* Drops a reward at the object: one roll in four picks a kind (an unavailable
   kind falls back to another drop). A nonzero bonus adds a second roll whose
   chance in 100 comes from a per-level table, capped at 22. */
/* Drops a random reward where the object was, with a possible bonus drop. */
void func_L05_00421908(char *object, int bonus)
{
    int slot;
    int chance;

    if (func_332AB8(4) == 0) {
        switch (func_332AB8(48)) {
        case 0: case 1: case 2: case 3:
            slot = func_L05_0037AAC8(6);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            D_L05_00221D10[24]++;
            D_L05_00221D10[28]++;
            break;
        case 5:
            slot = func_L05_0037AAC8(2);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto fallback;
            SpawnMobyClass117C(object);
            D_L05_00221D10[26]++;
            D_L05_00221D10[28]++;
            break;
        case 6:
            slot = func_L05_0037AAC8(3);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit)
                goto fallback;
            SpawnMobyClass117D(object);
            D_L05_00221D10[22]++;
            D_L05_00221D10[28]++;
            break;
        case 7:
            slot = func_L05_0037AAC8(4);
            if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit) {
        case 4:
        fallback:
                SpawnObjectAndCountIt(object);
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
        if (chance > 22)
            chance = 22;
        if (chance >= func_332AB8(100)) {
            func_L05_003CD1A8(object);
            D_L05_00221D10[24]++;
            D_L05_00221D10[28]++;
        }
    }
}
