#include "include_asm.h"

#include "common.h"
typedef struct { int state,next,pad08[2],limit,value,pad18[4]; } L05Slot40;
extern L05Slot40 g_spawn_entry_table[];
extern int g_feltzin_challenge_state[];
extern char *g_hero_l05_moby;
extern int hero_is_state_flag_set(void);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int table_find_last_used_entry(int);
extern void ship_start_record_playback_pal(void *);
extern void hero_record_play_counters_pal(void);

/* Applies damage to the hero: absorbed by the armor slot first, the rest taken from health (PAL). */
void hero_apply_damage_pal(float amount)
{
    int slot,remaining,damage;
    int *state;
    int *initial;
    if (hero_is_state_flag_set()) amount *= 0.5f;
    damage = FloatToInt(amount);
    initial = g_feltzin_challenge_state;
    *(u16 *)((u8 *)initial+0x40) += damage;
    initial[0x80/4] = 1;
    slot = table_find_last_used_entry(6);
    if (slot >= 0) {
        remaining = g_spawn_entry_table[slot].value;
        remaining -= FloatToInt(amount);
        if (remaining <= 0) g_spawn_entry_table[slot].value = 0;
        else { g_spawn_entry_table[slot].value = remaining; goto finished; }
        amount = IntToFloat(-remaining);
        if (amount == 0.0f) goto finished;
    }
    state = g_feltzin_challenge_state;
    {
        *(u16 *)((u8 *)state+0x42) += FloatToInt(amount);
        state[0x28/4] -= FloatToInt(amount);
        if (state[0x28/4] <= 0) {
            state[0x88/4]++;
            state[0x28/4] = 0;
            if (*(s16 *)(g_hero_l05_moby+0x86) == 25) ship_start_record_playback_pal(g_hero_l05_moby);
            else hero_record_play_counters_pal();
        }
    }
finished:
    return;
}

