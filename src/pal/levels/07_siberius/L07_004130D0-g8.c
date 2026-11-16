#include "include_asm.h"

#include "common.h"
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
extern u8 *g_moby_l07_array[] __attribute__((sda));
typedef struct {
    u8 pad[0xE0];
    f32 times[5];
    u8 *ents[5];
} SiberiusChain;

/* Starts the chain of the object's group: the rates at +0x1A0/+0x1A4 from 1 / the length of
   record D_L07_001FDEC0[state + 0x90] (its points at +0x10 and +0x20), then for i = 1 to 4 every
   entity of the group whose class is 0x11D9 + i: shown, scaled like the object, its time
   accumulated from D_L07_001B1770, stored as member i and set up. */
void ship_start_chain_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *path;
    f32 inv_length, slow, fast;
    f32 scale;
    s32 i;
    u16 *group_ptr;
    u8 *member;
    u8 *member_vars;

    path = g_path_l07_table[*(s32 *)(vars + 0x90)];
    inv_length = 1.0f / fast_vec_dist(path + 0x10, path + 0x20);
    fast = inv_length * 0.020000001f * g_ship_chain_fast_scale;
    slow = inv_length * 0.00040000002f * g_ship_chain_slow_scale;
    *(s32 *)(vars + 0x11C) = 0;
    *(u8 **)(vars + 0xF4) = moby;
    *(s32 *)(vars + 0x5C) |= 2;
    *(s32 *)(vars + 0xE0) = 0;
    *(f32 *)(vars + 0x1A4) = slow;
    *(f32 *)(vars + 0x1A0) = fast;
    *(TI128 *)(vars + 0x40) = *(TI128 *)(moby + 0xF0);
    ship_build_joint_pointers(moby);
    *(u16 *)(moby + 0x34) |= 1;
    moby[0x31] = 0;
    scale = *(f32 *)(moby + 0x2C) / *(f32 *)(*(u8 **)(moby + 0x24) + 0x24);
    if (moby[0x21] != 0xFF) {
        for (i = 1; i < 5; i++) {
            for (group_ptr = g_moby_l07_group_lists[moby[0x21]];
                 moby[0x21] != 0xFF && moby[0x21] <= g_entity_group_count && group_ptr != 0 &&
                 ((group_ptr != 0 && (s16)group_ptr[-1] >= 0) || group_ptr == g_moby_l07_group_lists[moby[0x21]]);
                 group_ptr++) {
                member = g_moby_l07_array[0] + ((*group_ptr & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(s16 *)(member + 0xAA) == i + 0x11D9) {
                    *(u16 *)(member + 0x34) |= 1;
                    member[0x31] = 0;
                    *(f32 *)(member + 0x2C) = *(f32 *)(*(u8 **)(member + 0x24) + 0x24) * scale;
                    member_vars = *(u8 **)(member + 0x68);
                    *(u16 *)(member + 0x34) |= 0x22;
                    *(u8 **)(member_vars + 8) = member_vars + 0x20;
                    *(s32 *)(member_vars + 0x5C) = 2;
                    *(TI128 *)(member_vars + 0x40) = *(TI128 *)(member + 0xF0);
                    ((SiberiusChain *)vars)->times[i] =
                        ((SiberiusChain *)vars)->times[i - 1] + g_ship_chain_time_offsets[i];
                    ((SiberiusChain *)vars)->ents[i] = member;
                    group_walk_entities(member);
                    boss_place_attached_parts(member);
                    ship_build_joint_pointers(member);
                }
            }
        }
    }
}
