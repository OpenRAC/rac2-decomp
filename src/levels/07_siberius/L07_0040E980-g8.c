#include "common.h"

/* Quadword copies, the spelling -frac2-qcopy lowers to lq/sq through address registers. */
typedef int TI128 __attribute__((mode(TI)));

extern f32 fast_vec_dist(void *a, void *b);
extern void ship_build_joint_pointers(u8 *a);
extern void group_walk_entities(u8 *a);
extern void boss_place_attached_parts(u8 *a);
extern u8 *g_path_l07_table[];
extern u16 *g_moby_l07_group_lists[];
extern f32 g_ship_chain_fast_scale __attribute__((sda));
extern f32 g_ship_chain_slow_scale __attribute__((sda));
extern f32 g_ship_chain_time_offsets[5] SDATA(D_L07_001B1770);
extern s32 g_entity_group_count;
/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it. */
extern u8 *g_moby_l07_array[] __attribute__((sda));

/* The chain of the state record: five times at +0xE0 and the five members at +0xF4. Indexing
   the member arrays (not pointer arithmetic) keeps `times[i - 1]`'s own scaled index and the
   base-first address additions retail has. */
typedef struct {
    u8 pad[0xE0];
    f32 times[5];
    u8 *ents[5];
} SiberiusChain;

/* Starts the chain of the object's group: the rates at +0x1A0/+0x1A4 from 1 / the length of
   record D_L07_001FDEC0[state + 0x90] (its points at +0x10 and +0x20), then for i = 1 to 4 every
   entity of the group whose class is 0x11D9 + i: shown, scaled like the object, its time
   accumulated from D_L07_001B1770, stored as member i and set up. */
void ship_start_chain(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *base;
    f32 inv, slow, fast;
    f32 scale;
    s32 i;
    u16 *entry;
    u8 *member;
    u8 *member_vars;

    base = g_path_l07_table[*(s32 *)(state + 0x90)];
    inv = 1.0f / fast_vec_dist(base + 0x10, base + 0x20);
    fast = inv * 0.016666668f * g_ship_chain_fast_scale;
    slow = inv * 0.00027777778f * g_ship_chain_slow_scale;
    *(s32 *)(state + 0x11C) = 0;
    *(u8 **)(state + 0xF4) = moby;
    *(s32 *)(state + 0x5C) |= 2;
    *(s32 *)(state + 0xE0) = 0;
    *(f32 *)(state + 0x1A4) = slow;
    *(f32 *)(state + 0x1A0) = fast;
    *(TI128 *)(state + 0x40) = *(TI128 *)(moby + 0xF0);
    ship_build_joint_pointers(moby);
    *(u16 *)(moby + 0x34) |= 1;
    moby[0x31] = 0;
    scale = *(f32 *)(moby + 0x2C) / *(f32 *)(*(u8 **)(moby + 0x24) + 0x24);
    if (moby[0x21] != 0xFF) {
        for (i = 1; i < 5; i++) {
            for (entry = g_moby_l07_group_lists[moby[0x21]];
                 moby[0x21] != 0xFF && moby[0x21] <= g_entity_group_count && entry != 0 &&
                 ((entry != 0 && (s16)entry[-1] >= 0) || entry == g_moby_l07_group_lists[moby[0x21]]);
                 entry++) {
                member = g_moby_l07_array[0] + ((*entry & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(s16 *)(member + 0xAA) == i + 0x11D9 /* moby class 4569 + i */) {
                    *(u16 *)(member + 0x34) |= 1;
                    member[0x31] = 0;
                    *(f32 *)(member + 0x2C) = *(f32 *)(*(u8 **)(member + 0x24) + 0x24) * scale;
                    member_vars = *(u8 **)(member + 0x68);
                    *(u16 *)(member + 0x34) |= 0x22;
                    *(u8 **)(member_vars + 8) = member_vars + 0x20;
                    *(s32 *)(member_vars + 0x5C) = 2;
                    *(TI128 *)(member_vars + 0x40) = *(TI128 *)(member + 0xF0);
                    ((SiberiusChain *)state)->times[i] =
                        ((SiberiusChain *)state)->times[i - 1] + g_ship_chain_time_offsets[i];
                    ((SiberiusChain *)state)->ents[i] = member;
                    group_walk_entities(member);
                    boss_place_attached_parts(member);
                    ship_build_joint_pointers(member);
                }
            }
        }
    }
}
