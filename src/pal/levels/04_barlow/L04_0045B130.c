#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u8 g_barlow_trigger_started;
extern u8 g_barlow_start_trigger_data;
extern void moby_mark_spawned(void *a0);
extern int flag_is_third_pending_set(u8 *a0);
extern void moby_mark_table_entry_flagged(u32 a0);
extern s32 req_push_queue(u8 *a0, s32 a1);
extern s32 req_launch_queued(void *a0);
extern void game_set_slowdown_factor(void);
extern u8 g_moby_group_flags[];
extern int g_current_map_index __attribute__((sda));
extern int g_moby_l04_pool __attribute__((sda));
extern u8 g_request_l04_queue[];
extern u8 g_barlow_l04_path_points_a[] __attribute__((sda));
extern u8 g_barlow_l04_path_points_b[] __attribute__((sda));
extern u8 g_barlow_path_points_c[] __attribute__((sda));
extern u8 g_barlow_path_points_d[] __attribute__((sda));
extern u8 g_barlow_path_points_e[] __attribute__((sda));
extern u8 g_barlow_l04_path_vectors_b[] __attribute__((sda));
extern u8 g_barlow_l04_path_vectors_d[] __attribute__((sda));
extern u8 g_barlow_path_vectors_e[] __attribute__((sda));
extern u8 g_barlow_path_lengths_a[] __attribute__((sda));
extern u8 g_barlow_path_lengths_b[] __attribute__((sda));
extern u8 g_barlow_path_lengths_c[] __attribute__((sda));
extern u8 g_barlow_path_lengths_d[] __attribute__((sda));
extern u8 g_barlow_path_lengths_e[] __attribute__((sda));
extern u8 g_barlow_path_lengths_f[] __attribute__((sda));
extern u8 g_barlow_path_lengths_g[] __attribute__((sda));
extern u8 g_barlow_path_starts_a[] __attribute__((sda));
extern u8 g_barlow_path_starts_b[] __attribute__((sda));
extern u8 g_barlow_path_starts_c[] __attribute__((sda));
extern u8 g_barlow_path_starts_d[] __attribute__((sda));
extern u8 g_barlow_path_starts_e[] __attribute__((sda));
extern u8 g_barlow_path_starts_f[] __attribute__((sda));
extern u8 g_barlow_path_starts_g[] __attribute__((sda));
extern u8 g_barlow_path_total_a[] __attribute__((sda));
extern u8 g_barlow_path_total_b[] __attribute__((sda));
extern u8 g_barlow_path_total_c[] __attribute__((sda));
extern u8 g_barlow_path_total_d[] __attribute__((sda));
extern u8 g_barlow_path_total_e[] __attribute__((sda));
extern u8 g_barlow_path_total_f[] __attribute__((sda));
extern u8 g_barlow_path_total_g[] __attribute__((sda));
extern u8 g_barlow_path_vectors_a[];
extern u8 g_barlow_l04_path_vectors_b_2[];
extern u8 g_barlow_path_vectors_c[];
extern u8 g_barlow_l04_path_vectors_d_2[];
extern u8 g_barlow_l04_path_points_a_2[];
extern u8 g_barlow_l04_path_points_b_2[];

/* Starts the object's encounter state and, once it is running, hands the level's
   camera table the object's slot and asks the frame helpers to update it. */
void barlow_encounter_trigger_update_pal(u8 *a0) {
    u32 *a1 = *(u32 **)(a0 + 0x68);

    if (a0[0x20] == 0) {
        if (g_moby_group_flags[a0[0xB0] + g_current_map_index * 16] & 0x80) {
            moby_mark_spawned(a0);
            return;
        }
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        if (flag_is_third_pending_set((u8 *)(g_moby_l04_pool + (*a1 << 8)))) {
            moby_mark_table_entry_flagged(a0[0xB0]);
            req_push_queue(g_request_l04_queue, 0x38);
            req_launch_queued(g_request_l04_queue);
            game_set_slowdown_factor();
            moby_mark_spawned(a0);
        }
    }
}

extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_game_flag_table[];
extern s32 g_game_tick_counter[] __attribute__((sda));
extern u8 *g_linked_record_table[] __attribute__((sda));
extern u8 g_hero_position[];
extern void hero_reset_position_and_direction_pal(void *a0, void *a1, s32 a2, s32 a3);
extern s32 IsPointInCuboid(void *a0, void *a1);
extern u8 g_tether_zero_vec[];
extern u8 g_hero_position[];
extern u8 g_str_linked_groups_debug_a[];
extern u8 g_str_linked_groups_debug_b[];

/* On the first update: with inventory item 0x1F owned, the byte at D_001395B8+0x12
   clear and the level counter D_L04_001B2008 below 5, passes the +0x30/+0x70 vectors
   of the level record the object names to func_PAL_L00_002B9CD8 (RAC1's Hero_ResetToPosition
   call shape); with the item owned and that byte set, hands the object to
   func_0029F338. Later, once func_002ACBC8 accepts the hero position (D_00189EA0) for
   the object's volume and the item is still owned, sets the byte and does the same. */
void barlow_item_pickup_trigger_update_pal(u8 *a0) {
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 *p;
    if (a0[0x20] == 0) {
        if (g_inventory_have_flags[0x1F] != 0 && g_game_flag_table[0x12] == 0 && g_game_tick_counter[0] < 5) {
            p = g_linked_record_table[0] + (*(s32 *)(s2 + 4) << 7);
            hero_reset_position_and_direction_pal(p + 0x30, p + 0x70, 0, 1);
        } else if (g_inventory_have_flags[0x1F] != 0 && g_game_flag_table[0x12] != 0) {
            moby_mark_spawned(a0);
            return;
        } else {
            a0[0x20] = 1;
        }
        a0[0x30] = 0xFF;
    }
    if (a0[0x20] == 1) {
        if (IsPointInCuboid(g_hero_position, *(void **)s2) != 0) {
            if (g_inventory_have_flags[0x1F] != 0) {
                g_game_flag_table[0x12] = 1;
                moby_mark_spawned(a0);
            }
        }
    }
}

