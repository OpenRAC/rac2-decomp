#include "include_asm.h"

#include "common.h"
extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char g_hero_position[];
extern char D_L19_001BFC40[];
extern void moby_reset_matching_effects(char *a0);
extern void moby_mark_spawned(char *a0);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_reset_vars_defaults(char *a0);
extern s32 IsPointInCuboid(char *a0, s32 a1);
extern s32 req_push_queue(char *a0, s32 a1);
extern void level_apply_index_for_key(char *a0);
extern void req_launch_queued(char *a0);
extern s32 game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(s32 a0);
extern void func_US2_002AFF10(s32 a0);
extern void hero_reset_position_and_direction(char *a0, char *a1, s32 a2, s32 a3);
extern void moby_mark_table_entry_flagged(s32 a0);
extern void level_capture_checkpoint_state(char *a0, char *a1);
extern void MemcardSave(s32 a0, s32 a1);

void func_US2_L19_00424DC8(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    u8 id;

    moby_reset_matching_effects(a0);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            moby_mark_spawned(a0);
        } else {
            moby_set_state(a0, 1, -1);
            moby_reset_vars_defaults(a0);
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(s1 + 0x120)) != 0) {
            if (req_push_queue(D_L19_001BFC40, 0x96) != 0) {
                req_push_queue(D_L19_001BFC40, 0x14);
                req_push_queue(D_L19_001BFC40, 0x97);
                level_apply_index_for_key(a0);
                req_launch_queued(D_L19_001BFC40);
                moby_set_state(a0, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (game_is_either_mode_two() == 0) {
            D_L19_001B2724[1] = 0;
            moby_mark_flag_and_append_to_list(0x14);
            func_US2_002AFF10(0x14);
            hero_reset_position_and_direction(D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(u8 *)(a0 + 0x31) = 1;
            if (*(u8 *)(a0 + 0xB0) != 0xFF) {
                id = *(u8 *)(a0 + 0xB0);
                if ((D_0019B2E8[id + (g_current_map_index[0] << 4)] & 0x80) == 0)
                    moby_mark_table_entry_flagged(id);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                MemcardSave(0, -1);
            } else {
                MemcardSave(0, -1);
            }
            moby_mark_spawned(a0);
        }
        break;
    }
}
