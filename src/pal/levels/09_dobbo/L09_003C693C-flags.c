#include "include_asm.h"

#include "common.h"
extern s32 g_current_map_index __attribute__((sda));
extern void math_store_angle_update_result(void *, s32, s32, s32, float);
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern u8 g_unlocked_item_flags[] __attribute__((sda));
extern u8 g_mystic_manipulator_data[] __attribute__((sda));
extern s32 level_get_saved_count(void);
extern u8 g_player_stats[] __attribute__((sda));
extern u8 g_mystic_state[] __attribute__((sda));
extern u8 g_game_flag_table[];
extern u8 g_request_l08_queue[];

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
void mob_store_angle_update_pal(u8 *moby)
{
    s32 link = *(s32 *)(moby + 0x68);

    if (link == 0)
        return;
    math_store_angle_update_result(moby, link, 0x80AAAAD2, 0x80396464, 0.07330384f);
}
