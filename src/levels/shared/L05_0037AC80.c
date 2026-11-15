#include "common.h"
typedef struct { int state,next,pad08[2],limit,value,pad18[4]; } L05Slot40;
extern L05Slot40 D_L05_002A1800[];
extern int D_L05_00221D10[];
extern char *D_L05_001B9710;
extern int hero_is_state_flag_set(void);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int table_find_last_used_entry(int);
extern void ship_start_crash_recovery(void *);
extern void hero_record_play_counters(void);
/* Applies damage to the hero: first from the shield-like slot, then from health. */
void hero_apply_damage(float amount)
{
    int slot,remaining,damage;
    int *state;
    int *initial;
    if (hero_is_state_flag_set()) amount *= 0.5f;
    damage = FloatToInt(amount);
    initial = D_L05_00221D10;
    *(u16 *)((u8 *)initial+0x40) += damage;
    initial[0x80/4] = 1;
    slot = table_find_last_used_entry(6);
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
            if (*(s16 *)(D_L05_001B9710+0x86) == 25) ship_start_crash_recovery(D_L05_001B9710);
            else hero_record_play_counters();
        }
    }
finished:
    return;
}
