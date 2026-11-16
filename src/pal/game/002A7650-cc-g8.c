#include "names.h"
/* func_PAL_002A7650, the PAL copy of func_002A6C58: the same C, where rename func_002A6AE0 becomes func_PAL_002A74D8; rename func_0029B720 becomes func_PAL_0029C0B8; rename func_002ADB78 becomes func_PAL_002AE6D8. */
#include "common.h"

void gfx_pack_render_command_fields(unsigned long long *command_words, unsigned long long upper_field, unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field);

/* rac1-decomp src/game/mobyfunc.c: func_0020E340 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/rendering/commands/pack_render_command_fields.c, gfx_pack_render_command_fields. */
void gfx_pack_render_command_fields(unsigned long long *command_words, unsigned long long upper_field, unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field);


/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251328. */

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251358. */

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251468. */

typedef struct {
    unsigned char pad00[0x46];
    short kind;
} RewardClass;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];
    unsigned char pad20[4];
    RewardClass *mclass;
    unsigned char pad28[0x57];
    unsigned char kills;
    unsigned char pad80[0x30];
    unsigned char owner, flags;
    short id, bolts;
    unsigned short count;
} RewardMoby;
extern int g_reward_slot_index __attribute__((sda));
extern int g_current_map_index;
extern short g_default_base_reward __attribute__((sda));
extern RewardMoby *g_reward_moby_slots[2];
typedef struct { unsigned char pad[0x80]; float position[4]; unsigned char pad90[0x2204]; int state; unsigned char pad2298[0x1C]; unsigned char mode; unsigned char pad22B5[13]; unsigned char option; } PlayerReward;
extern PlayerReward g_hero_state;
typedef struct { unsigned char pad[12]; int earned, reserve, extra; unsigned char pad18[26]; unsigned char multiplier; } RewardState;
extern RewardState g_player_stats MACRO_ADDR;
extern int g_reward_counts[];
extern short g_base_reward_table[] MACRO_ADDR, g_reward_cap_table[] MACRO_ADDR;
extern unsigned char g_moby_nibble_table[];
extern char g_str_reward_debug_format[];
extern char g_reward_scale_table_b[] MACRO_ADDR, g_reward_scale_table_a[] MACRO_ADDR, g_bolt_scale_table_b[] MACRO_ADDR, g_bolt_scale_table_a[] MACRO_ADDR;
extern int g_reward_weight_table[][56], g_help_entry_state[];
extern short g_map_two_base_reward;
typedef struct { u8 prefix[0x464]; u8 collected[0]; } BoltCollectionTable;
extern BoltCollectionTable g_bolt_collection_table, g_bolt_collection_checkpoint;
extern unsigned char g_render_command_flags[] MACRO_ADDR, g_moby_group_flags[] MACRO_ADDR;
extern int g_hero_health_percent;
extern void moby_count_kill_or_event_pal(RewardMoby *, int);
extern void STUB_printf(char *, int, int, int);
extern int stat_scale_by_nibble_lookup(char *, int, int);
extern char *moby_get_private_value_0(RewardMoby *);
extern void level_forward_value_b_pal(int);
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern void moby_spawn_bolt_pickups_pal(RewardMoby *, int, int, int, int, int, float);

/* Gives out the reward when an enemy or crate is destroyed: counts the kill, works out the bolts and scatters them (PAL). */
void SetDeathBits_pal(RewardMoby *moby, int flags, int arg)
{
    int multiplier;
    int slot, bonus, reward, extra, i, j, total;
    unsigned short count;
    char *info;
    float bolts;
    int dropflags;
    if (moby->id < 0 || (moby->flags & 0x80)) return;
    moby->kills++;
    multiplier = 1;
    if (moby->mclass && moby->mclass->kind == 5) {
        if (g_player_stats.multiplier) multiplier = g_player_stats.multiplier;
        moby_count_kill_or_event_pal(moby, 0);
    }
    count = moby->count;
    for (slot = 1; slot >= 0; slot--) if (moby == g_reward_moby_slots[slot]) break;
    if ((count || g_reward_slot_index != -1) && (unsigned)(g_hero_state.mode - 1) >= 2) {
        bonus = (g_player_stats.reserve + 49) / 50;
        if (g_reward_slot_index != -1 && slot < 0) {
            unsigned short base = g_base_reward_table[g_reward_slot_index];
            reward = (short)base;
            if (g_reward_counts[g_reward_slot_index] * 2 > g_reward_cap_table[g_reward_slot_index])
                reward = (short)base * g_reward_cap_table[g_reward_slot_index] / (g_reward_counts[g_reward_slot_index] * 2);
            if (!reward) reward = 1;
            STUB_printf(g_str_reward_debug_format, g_reward_slot_index, (short)base, reward);
        } else {
            int n = g_moby_nibble_table[(moby->id >> 1) + (g_current_map_index << 10)];
            if (((unsigned short)moby->id & 1) ? (n >> 4) & 8 : n & 8) reward = stat_scale_by_nibble_lookup(g_reward_scale_table_b, (short)count, moby->id);
            else reward = stat_scale_by_nibble_lookup(g_reward_scale_table_a, (short)count, moby->id);
        }
        info = moby_get_private_value_0(moby);
        if (info && (unsigned char)info[0x17] != 255) {
            if (slot >= 0) {
                total = 0;
                for (i = 0; i < 56; i++) total += g_reward_weight_table[slot][i];
                if (total) {
                    for (j = 0; j < 56; j++) g_help_entry_state[j] += g_reward_weight_table[slot][j] * (reward + bonus) / total;
                }
                g_reward_moby_slots[slot] = 0;
            } else g_help_entry_state[(unsigned char)info[0x17]] += reward + bonus;
        }
        g_player_stats.reserve -= bonus;
        g_player_stats.earned += reward + bonus;
        level_forward_value_b_pal(600);
    }
    extra = (g_player_stats.extra + 49) / 50;
    g_player_stats.extra -= extra;
    if (g_reward_slot_index != -1) {
        int base;
        if (g_current_map_index == 2) base = g_map_two_base_reward;
        else base = g_default_base_reward;
        bolts = base;
        if (slot >= 0) bolts *= 10.0f;
    } else {
        int n = g_moby_nibble_table[(moby->id >> 1) + (g_current_map_index << 10)];
        if (((unsigned short)moby->id & 1) ? (n >> 4) & 8 : n & 8) bolts = stat_scale_by_nibble_lookup(g_bolt_scale_table_b, moby->bolts, moby->id);
        else bolts = stat_scale_by_nibble_lookup(g_bolt_scale_table_a, moby->bolts, moby->id);
    }
    if (moby->id >= 0 && !(moby->flags & 0x80)) {
        unsigned short id;
        if (g_reward_slot_index != -1) g_reward_counts[g_reward_slot_index]++;
        id = (unsigned short)moby->id;
        if (id & 1) {
            unsigned char *bits = g_moby_nibble_table + (((short)id >> 1) + (g_current_map_index << 10));
            if (((*bits >> 4) & 7) != 7) *bits += 16;
        } else {
            unsigned char *bits = g_moby_nibble_table + (((short)id >> 1) + (g_current_map_index << 10));
            if ((*bits & 7) != 7) *bits += 1;
        }
        g_bolt_collection_table.collected[moby->id] = moby->owner + 2;
        {
            int k = moby->owner;
            if (k == 255 || (!(g_render_command_flags[k & 0xFF] & 0x80) && (g_moby_group_flags[(k & 0xFF) + (g_current_map_index << 4)] & 0x80)))
                g_bolt_collection_checkpoint.collected[moby->id] = k + 2;
        }
    }
    if (g_reward_slot_index == -1) bolts *= multiplier;
    bolts += extra;
    dropflags = flags & 0x100 ? 5 : 1;
    if (g_hero_state.option || (flags & 0x200)) dropflags |= 2;
    if (g_hero_state.state == 16 && fast_vec_dist(g_hero_state.position, moby->position) < 4.0f) dropflags |= 2;
    if (flags & 0x400) dropflags |= 0x10;
    dropflags |= 8;
    if (g_hero_health_percent <= 99) dropflags |= 2;
    if (bolts < 0.0f) bolts = 0.0f;
    if (bolts > 0.0f) {
        int spread = 0;
        if (bolts >= 8.0f) spread = FloatToInt(bolts * 0.25f);
        else if (bolts >= 2.0f) spread = 1;
        {
            int n = FloatToInt(bolts);
            int hi = n + spread;
            n -= spread;
            moby_spawn_bolt_pickups_pal(moby, n, hi, dropflags, -1, arg, 0.0f);
        }
    }
}

typedef int TI128_002A7470 __attribute__((mode(TI)));

extern TI128_002A7470 ref_L00_002A7470_00[];

typedef struct {
    unsigned char pad0[0x8E];
    unsigned short count;
    unsigned char pad90[0x50];
} Class_2A68A8;

extern Class_2A68A8 g_weapon_table[];
