#include "include_asm.h"

#include "common.h"
extern s32 g_path_l17_table[];
extern s32 func_31B160(s32);
extern f32 func_2EF0B0(s32, s32);
extern s32 g_flash_frame_counter __attribute__((sda));
extern s32 func_2F0108(u32, u32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 g_moby_l17_pool __attribute__((sda));
extern s32 g_aim_hit_result;
extern s32 func_2DF570(s32, s32, s32, s32, s32);
extern f32 math_fabs(f32);
extern f32 g_fan_var_value SDATA(D_L17_001B04BC);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 ApproachValue(void *, f32, f32);
extern u16 *g_group_l17_member_table[];
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
extern s32 g_max_l17_group_id[] __attribute__((sda));
typedef struct {
    u8 pad[0x43C];
    s32 group;
    s32 mode;
} L17GroupState;

/* Walks the id list of the state's group and sets the state's mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
void grulch_activate_group_members_pal(u8 *obj)
{
    L17GroupState *state = *(L17GroupState **)(obj + 0x68);
    u16 *group_ids;
    u8 *entity;

    for (group_ids = g_group_l17_member_table[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= g_max_l17_group_id[0] && group_ids != 0 &&
         ((group_ids != 0 && (s16)group_ids[-1] >= 0) || group_ids == g_group_l17_member_table[state->group]);
         group_ids++) {
        entity = D_L17_001B2C1C_base[0] + ((*group_ids & 0x7FFF) << 8);
        if (entity == 0)
            break;
        state->mode = 0x3E;
    }
}




