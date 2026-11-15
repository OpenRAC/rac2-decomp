#include "common.h"
typedef struct { int state,next,pad08[2],limit,value,pad18[4]; } L05Slot40;
extern L05Slot40 D_L05_002A1800[];
extern int D_L05_00221D10[];
extern char *D_L05_001B9710;
extern int func_L05_00445980(void);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002ED8A0(int);
extern void func_L05_00442398(void *);
extern void func_L00_002B30E8(void);
/* Applies damage to the hero: first from the shield-like slot, then from health. */
void func_L05_0037AC80(float amount)
{
    int slot,remaining,damage;
    int *state;
    int *initial;
    if (IsHeroStateFlagSet()) amount *= 0.5f;
    damage = FloatToInt(amount);
    initial = D_L05_00221D10;
    *(u16 *)((u8 *)initial+0x40) += damage;
    initial[0x80/4] = 1;
    slot = FindLastUsedChainEntry(6);
    if (slot >= 0) {
        remaining = D_L05_002A1800[slot].value;
        remaining -= FloatToInt(amount);
        if (remaining <= 0) D_L05_002A1800[slot].value = 0;
        else { D_L05_002A1800[slot].value = remaining; goto finished; }
        amount = IntToFloat(-remaining);
        if (amount == 0.0f) goto finished;
    }
    state = D_L05_00221D10;
    {
        *(u16 *)((u8 *)state+0x42) += FloatToInt(amount);
        state[0x28/4] -= FloatToInt(amount);
        if (state[0x28/4] <= 0) {
            state[0x88/4]++;
            state[0x28/4] = 0;
            if (*(s16 *)(D_L05_001B9710+0x86) == 25) StartShipCrashRecovery(D_L05_001B9710);
            else RecordHeroPlayCounters();
        }
    }
finished:
    return;
}
