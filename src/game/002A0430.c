#include "include_asm.h"
#include "common.h"

extern int ref_L00_00312060_01;

extern unsigned char ref_L00_00312060_00[];

/* Sets the high flag bit on one entry of a small table, unless the index is 255. */
void moby_mark_table_entry_flagged(unsigned int index)
{
    if (index != 255u)
        ref_L00_00312060_00[index + (unsigned int)ref_L00_00312060_01 * 16u] |= 0x80u;
}

void gfx_pack_render_command_fields(unsigned long long *command_words, unsigned long long upper_field, unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field);

/* rac1-decomp src/game/mobyfunc.c: func_0020E340 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/rendering/commands/pack_render_command_fields.c, gfx_pack_render_command_fields. */
/* Combines four values into one packed 64-bit word and stores it in slot 7 of a command list. */
void gfx_pack_render_command_fields(unsigned long long *command_words, unsigned long long upper_field,
                             unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field) {
    int command_word_index;
    if (middle_field) {
        upper_field <<= 32;
        low_field <<= 8;
        tail_field <<= 16;
    } else {
        upper_field <<= 32;
        low_field <<= 8;
        tail_field <<= 16;
    }
    {
        register unsigned long long packed_command;
        packed_command = upper_field | middle_field;
        packed_command |= low_field;
        packed_command |= tail_field;
        command_word_index = 7;
        command_words[command_word_index] = packed_command;
    }
}

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251328. */
ASM_FUNC("asm/game", func_002A0488);

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251358. */
ASM_FUNC("asm/game", func_002A04B8);

ASM_FUNC("asm/game", func_002A04E8);

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251468. */
ASM_FUNC("asm/game", func_002A0558);

/* Original assembly: 29 trapping add/addi/sub/dsub, $at as a working register, and two cvt.w.s
   words in an encoding the compiler never emits. */
ASM_FUNC("asm/game", func_002A05A8);

/* Original assembly: VU0 lqc2 ops, scratchpad base in $t7 and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002A08A0);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002A0A28);

ASM_FUNC("asm/game", func_002A0B88);

ASM_FUNC("asm/game", func_002A0BE8);

ASM_FUNC("asm/game", func_002A0C68);

/* Original assembly: VU0 macro instructions (lqc2/sqc2, vmula/vmadd, vcallms, qmtc2/qmfc2),
   trapping addi/add and $at as a working register. */
ASM_FUNC("asm/game", func_002A0F48);

/* Original assembly: lqc2/vmove VU0 ops and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002A10E8);

/* Original assembly: trapping add with $at as a working register, and it leaves by jumps into
   its neighbours; the compiler cannot emit it (marked by owner decision, 8 November 2026). */
ASM_FUNC("asm/game", func_002A1130);

/* Original assembly: VU0 lqc2/sqc2 ops and trapping addi/add with $at as a working register; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002A1378);

/* Original assembly: 32 trapping add/addi/sub, $at as a working register, and no return:
   it leaves by jumps, like func_002A1130. */
ASM_FUNC("asm/game", func_002A1490);

ASM_FUNC("asm/game", func_002A1738);

ASM_FUNC("asm/game", func_002A2450);

ASM_FUNC("asm/game", func_002A3110);

ASM_FUNC("asm/game", func_002A3DB8);

ASM_FUNC("asm/game", func_002A3F10);

ASM_FUNC("asm/game", func_002A4078);

ASM_FUNC("asm/game", func_002A4AD8);

ASM_FUNC("asm/game", func_002A4D88);

ASM_FUNC("asm/game", func_002A4E68);

ASM_FUNC("asm/game", func_002A6640);

/* Original assembly: $ra kept in $t9 and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002A677C);



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
extern void moby_count_kill_or_event(RewardMoby *, int);
extern void STUB_printf(char *, int, int, int);
extern int stat_scale_by_nibble_lookup(char *, int, int);
extern char *moby_get_private_value_0(RewardMoby *);
extern void level_forward_value_b(int);
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern void moby_spawn_bolt_pickups(RewardMoby *, int, int, int, int, int, float);

/* Gives out the reward when an enemy or crate is destroyed: counts the kill, works out the bolts and scatters them. */
void SetDeathBits(RewardMoby *moby, int flags, int arg)
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
        moby_count_kill_or_event(moby, 0);
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
        level_forward_value_b(720);
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
            moby_spawn_bolt_pickups(moby, n, hi, dropflags, -1, arg, 0.0f);
        }
    }
}


typedef int TI128_002A7470 __attribute__((mode(TI)));

typedef struct {
    char pad[0x48];
    unsigned char *anims[1];
} Model_002A7470;

extern void anim_start_immediate(unsigned char *, int, int);
extern int moby_alloc_object_slot(void *);
extern void func_002A2450(void *, int);
extern void update_moby_animation_state(void *);
extern float IntToFloat(int);
extern TI128_002A7470 ref_L00_002A7470_00[];

/* Starts an animation on an object, blending into it over some frames, or switching at once if there are none. */
void anim_start_blended(unsigned char *object, int animation, int frame, int rate)
{
    int count;
    int slot;
    float reciprocal;

    count = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x10];
    if (frame >= count)
        frame = count - 1;

    if (rate <= 0) {
        anim_start_immediate(object, animation, frame);
        return;
    }

    if (0.025f < *(float *)(object + 0x44) ||
        *(unsigned int *)(object + 0x50) != 0 ||
        *(unsigned int *)(object + 0x54) != 0) {
        slot = moby_alloc_object_slot(object);
        if (slot >= 0) {
            func_002A2450(object, slot | 0x300);
            qcopy(&ref_L00_002A7470_00[slot], object + 0x80);
            if (object[0x42] != 0xFF)
                object[0xA9] = object[0x42];
            object[0x42] = 0xFF;
            object[0x40] = slot;
        }
    }

    object[0x41] = frame;
    object[0x43] = animation;
    update_moby_animation_state(object);
    *(float *)(object + 0x48) = 1.0f;
    reciprocal = 1.0f / IntToFloat(rate);
    *(unsigned int *)(object + 0x44) = 0;
    object[0x60] &= 0xFD;
    *(float *)(object + 0x4C) = reciprocal;
    object[0x6C] = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x11];
}

typedef struct {
    unsigned char pad0[0x8E];
    unsigned short count;
    unsigned char pad90[0x50];
} Class_2A68A8;

extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern Class_2A68A8 g_weapon_table[];
extern int math_random_int_below(int);

/* Picks a random item to drop, preferring kinds the player has fewer of than the limit. */
int PickAmmoDropItem(int unused, int *out)
{
    int i;
    int j;
    int k;
    int sum = 0;
    int total = 0;
    int pick;
    Class_2A68A8 *cls;

    for (i = 0; i < 0x38; i++) {
        if (g_item_owned_flags[i] != 0) {
            cls = &g_weapon_table[g_item_slot_to_record[i]];
            if (cls->count != 0 && i != 0x1F && i != 0x3D && i != 0x2D && i != 0x4D) {
                total++;
                if (g_item_ammo_counts[i] < cls->count)
                    sum++;
            }
        }
    }
    if (sum != 0) {
        pick = math_random_int_below(sum);
        for (j = 0; j < 0x38; j++) {
            if (g_item_owned_flags[j] != 0) {
                cls = &g_weapon_table[g_item_slot_to_record[j]];
                if (cls->count != 0 && g_item_ammo_counts[j] < cls->count && j != 0x1F && j != 0x3D) {
                    if (pick == 0) {
                        *out = j;
                        break;
                    }
                    pick--;
                }
            }
        }
    } else {
        pick = math_random_int_below(total);
        for (k = 0; k < 0x38; k++) {
            if (g_item_owned_flags[k] != 0) {
                cls = &g_weapon_table[g_item_slot_to_record[k]];
                if (cls->count != 0 && k != 0x1F && k != 0x3D && k != 0x2D && k != 0x4D) {
                    if (pick == 0) {
                        *out = k;
                        break;
                    }
                    pick--;
                }
            }
        }
    }
    {
        int roll = math_random_int_below(5);
        int one;
        int result = 2;
        one = 1;
        if (roll != 0) result = one;
        return result;
    }
}
