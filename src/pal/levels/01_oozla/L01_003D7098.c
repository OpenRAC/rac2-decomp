/* func_PAL_L01_003D7098, the PAL copy of func_L01_003D2E50: the same C, where the frame counts,
   sound ids and random timers take PAL's values and both turn rates are scaled by 1.44f at the
   calls, which keeps the 0.3f limit in a local beside turnRate. */

#include "common.h"

typedef struct {
    u8 pad[0x80];
    s32 cost;
    u8 tail[0x5C];
} VendorItem;

typedef struct {
    u8 pad[0xE0];
    f32 position[4];
} HeroView;

typedef struct PurchaseMoby {
    u8 pad00[0x10];
    f32 position[4];
    u8 state, group;
    u8 pad22[0xE];
    u8 field30, enabled;
    u16 field32, flags;
    u8 pad36[0xD];
    u8 animation;
    u8 pad44[0x1C];
    u8 animFlags;
    u8 pad61[7];
    u8 *data;
    u8 pad6C[0x8C];
    f32 yaw;
} PurchaseMoby;

extern u8 g_removal_trigger_flag[] MACRO_ADDR;
extern u8 g_unlocked_item_flags[] MACRO_ADDR;
extern s32 g_player_bolts[] MACRO_ADDR;
extern u8 g_level_flag_byte;
extern u8 g_item_slot_to_record[];
extern s32 g_pad_held_flags;
extern u8 g_hero_position[], g_hero_target_point[];
extern u8 g_action_table[];
extern u8 g_cutscene_vars[];
extern u8 *g_swamp_patrol_positions[] MACRO_ADDR;
extern s32 g_hero_l01_control_mode MACRO_ADDR;

/* The word at 0x001B22A8 follows the halfwords this level reads at 0x001B22A0/2/4. Retail keeps
   its store out of every delay slot: only a symbol-plus-offset operand does that, because the
   backend counts it as two instructions, so the word is written as a member of the block. */
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;

extern void part_spawn_effect_on_matching_things(void *, s32, s32, f32);
extern void moby_set_state(void *, s32, s32);
extern void moby_reset_vars_defaults(void *);
extern u8 *CreateMoby(s32);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(void *);
extern s32 IsPointInCuboid(void *, s32);
extern s32 req_push_queue(void *, s32);
extern void level_apply_index_for_key(void *);
extern s32 req_launch_queued(void *);
extern s32 game_is_either_mode_two(void);
extern void hero_reset_position_and_direction_pal(void *, void *, s32, s32);
extern s32 hero_is_reachable_for_count(void *, s32, f32);
extern void func_L00_0030C710(s32);
extern void text_print_localized_formatted(s32, s32, s32);
extern void moby_set_byte_on_group(s32, s32);
extern void help_unlock_entry(s32);
extern int moby_handle_request_slot_state(s32);
extern void value_set_entry_by_index_pal(s32, s32);
extern int func_PAL_00289730(s32, s32);
extern void cam_lock_entry(s32);
extern int MemcardSave(s32, s32);
extern void moby_mark_spawned(void *);
extern s32 FastDecTimer(void *);
extern f32 math_random_float_range(f32, f32);
extern s32 FloatToInt(f32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern f32 FastVecLength(void *);
extern s32 math_fast_float_d(void *);
extern f32 FastAddRotations(f32, f32);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 vec_length_xy(void *);
extern void moby_update_eased_node(void *, void *, s32, f32, f32);
extern void moby_copy_joint_transform_to_object(void *, void *, s32, s32);

#define STATE_CHILD (*(u8 **)(state + 0x128))

/* An item vendor: offers the current item table entry, compares its cost with D_001A79F8, takes
   the cost on purchase and removes itself. */
void func_PAL_L01_003D7098(PurchaseMoby *moby)
{
    u8 target[16] __attribute__((aligned(16)));
    u8 origin[16] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    u8 *state = moby->data;
    u8 *child, *record;
    f32 turnRate, turnLimit, angle, yaw, pitch;
    s32 active;
    u64 flag;

    part_spawn_effect_on_matching_things(moby, 0, 0xB1A, 2.5f);
    switch (moby->state) {
    case 0:
        if (g_removal_trigger_flag[0])
            goto remove_self;
        flag = g_level_flag_byte;
        if (flag >> 7) {
            if (g_player_bolts[0] < ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost)
                moby_set_state(moby, 3, -1);
            else
                moby_set_state(moby, 4, -1);
        } else {
            moby_set_state(moby, 1, -1);
        }
        moby_reset_vars_defaults(moby);
        child = CreateMoby(0xD7E);
        STATE_CHILD = child;
        if (child) {
            child[0x30] = moby->field30;
            *(u16 *)(STATE_CHILD + 0x32) = moby->field32;
            STATE_CHILD[0x31] = 1;
            func_002A0F48(STATE_CHILD);
            hero_copy_field_to_moby(STATE_CHILD);
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 0x120)) && req_push_queue(g_cutscene_vars, 0x27)) {
            level_apply_index_for_key(moby);
            req_launch_queued(g_cutscene_vars);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        g_cutscene_trigger_state.busy = 1;
        if (g_hero_l01_control_mode == 2) {
            moby->enabled = 0;
            moby->flags |= 1;
            if (g_hero_l01_control_mode == 2) {
                *(u16 *)(STATE_CHILD + 0x34) |= 1;
                STATE_CHILD[0x31] = 0;
            }
        }
        if (!game_is_either_mode_two()) {
            g_cutscene_trigger_state.busy = 0;
            record = g_swamp_patrol_positions[0] + (*(s32 *)(state + 0x120) << 7);
            hero_reset_position_and_direction_pal(record + 0x30, record + 0x70, 0, 1);
            moby->enabled = 1;
            moby->flags &= 0xFFFE;
            *(u16 *)(STATE_CHILD + 0x34) &= 0xFFFE;
            STATE_CHILD[0x31] = 1;
            if (g_player_bolts[0] < ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost)
                moby_set_state(moby, 3, -1);
            else
                moby_set_state(moby, 4, -1);
        }
        break;
    case 3:
        if (((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost < g_player_bolts[0]) {
            moby_set_state(moby, 4, -1);
        } else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x1300, ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 4:
        if (g_player_bolts[0] < ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost) {
            func_L00_0030C710(150);
            moby_set_state(moby, 3, -1);
        } else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x12FE, ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost, -1);
            level_apply_index_for_key(moby);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_cutscene_vars, 40)) {
                req_launch_queued(g_cutscene_vars);
                moby_set_state(moby, 5, -1);
            }
        }
        break;
    case 5:
        g_cutscene_trigger_state.busy = 1;
        if (g_hero_l01_control_mode == 2) {
            moby->enabled = 0;
            moby->flags |= 1;
            if (g_hero_l01_control_mode == 2) {
                *(u16 *)(STATE_CHILD + 0x34) |= 1;
                STATE_CHILD[0x31] = 0;
            }
        }
        if (!game_is_either_mode_two()) {
            g_cutscene_trigger_state.busy = 0;
            moby->enabled = 1;
            moby->flags &= 0xFFFE;
            *(u16 *)(STATE_CHILD + 0x34) &= 0xFFFE;
            STATE_CHILD[0x31] = 1;
            moby_set_byte_on_group(moby->group, 1);
            if (!g_removal_trigger_flag[0]) {
                g_player_bolts[0] = g_player_bolts[0] - ((VendorItem *)(g_action_table + g_item_slot_to_record[0x2E] * sizeof(VendorItem)))->cost;
                func_L00_0030C710(150);
                help_unlock_entry(46);
                moby_handle_request_slot_state(46);
                value_set_entry_by_index_pal(0x1226, -1);
                func_PAL_00289730(0x9BC, 19);
                if (*(s32 *)(state + 0x12C) != -1)
                    cam_lock_entry(*(s32 *)(state + 0x12C));
                MemcardSave(0, -1);
                if (STATE_CHILD) {
                    moby_mark_spawned(STATE_CHILD);
                    STATE_CHILD = 0;
                }
remove_self:
                moby_mark_spawned(moby);
                return;
            }
        }
        break;
    }
    if (moby->state) {
        if (!moby->animation && FastDecTimer(state + 0x11E)) {
            *(u16 *)(state + 0x11E) = FloatToInt((math_random_float_range(1200.0f, 2400.0f) * 5.0f + 2.0f) * 0.16666667f);
        } else if ((moby->animFlags & 2) && moby->animation) {
            func_PAL_002A7E68(moby, 0, 0, 8);
        }
    }
    turnRate = 0.02f;
    turnLimit = 0.3f;
    active = 0;
    if (!moby->animation) {
        active = 1;
        if (vec_distance_xy(moby->position, g_hero_position) < 8.0f &&
            FastDiffRots(moby->yaw, mat_fast_helper_a(((HeroView *)(g_hero_position - 0x80))->position[0] - moby->position[0],
                                                   ((HeroView *)(g_hero_position - 0x80))->position[1] - moby->position[1])) < 1.5707965f) {
            if (0.01f < FastVecLength(g_hero_position + 0x90))
                *(s32 *)(state + 0x114) = 100;
            else
                math_fast_float_d(state + 0x114);
        } else if (*(s32 *)(state + 0x114)) {
            *(s32 *)(state + 0x114) = 0;
            qcopy(state + 0x100, g_hero_target_point);
        }
        if (math_fast_float_d(state + 0x118)) {
            *(s32 *)(state + 0x118) = FloatToInt((math_random_float_range(180.0f, 300.0f) * 5.0f + 2.0f) * 0.16666667f);
            angle = FastAddRotations(moby->yaw, math_random_float_range(-90.0f, 90.0f) * 0.017453294f);
            vec_build_spherical_offset(state + 0x100, 6.0f, angle, math_random_float_range(0.0f, 30.0f) * 0.017453294f);
            FastVecAdd(state + 0x100, state + 0x100, moby->position);
        }
        if (*(s32 *)(state + 0x114)) {
            qcopy(target, g_hero_target_point);
            turnRate = 0.04f;
            turnLimit = 0.3f;
        } else {
            qcopy(target, state + 0x100);
        }
    }
    if (active) {
        qcopy(origin, moby->position);
        ((f32 *)origin)[2] += 2.0f;
        FastVecSub(delta, target, origin);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta[0], delta[1]), moby->yaw);
        pitch = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        if (1.5707965f < yaw)
            yaw = 1.5707965f;
        else if (yaw < -1.5707965f)
            yaw = -1.5707965f;
        if (0.17453295f < pitch)
            pitch = 0.17453295f;
        else if (pitch < -0.17453295f)
            pitch = -0.17453295f;
        *(f32 *)(state + 0x64) = pitch;
        *(f32 *)(state + 0x68) = yaw * 0.6f;
        *(f32 *)(state + 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags[0])
        *(f32 *)(state + 0x70) = 2.75f;
    moby_update_eased_node(moby, state, 0, turnRate * 1.44f, turnLimit * 1.44f);
    moby_update_eased_node(moby, state + 0x80, 1, turnRate * 1.44f, turnLimit * 1.44f);
    if (STATE_CHILD)
        moby_copy_joint_transform_to_object(moby, STATE_CHILD, 2, 0);
}
