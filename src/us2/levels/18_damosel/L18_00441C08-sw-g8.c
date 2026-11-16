#include "include_asm.h"

#include "common.h"
#define S32_AT(p, o) (*(int *)((u8 *)(p) + (o)))
#define F32_AT(p, o) (*(float *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x84]; u8 first; u8 pad85; u8 second; u8 pad87[2]; u8 third; } PurchaseParts;
typedef struct { u8 pad[0x37]; u8 planet; } PurchaseSave;
typedef struct { u8 pad[0x80]; int cost; u8 tail[0x5C]; } PurchaseLevelInfo;
typedef struct { u8 pad[0xE0]; float x; float y; } PurchaseHero;
extern u8 g_hero_position[], g_weapon_l18_table[], g_request_l18_queue[];
extern PurchaseParts g_game_flag_table;
extern PurchaseSave g_item_slot_to_record;
extern int g_object_state_flags_h NOT_SDA;
extern int g_player_bolts;
extern int g_pad_held_flags NOT_SDA;
extern u8 g_mover_trigger_flag;
extern u8 g_purchase_level_index NOT_SDA;
extern u8 g_unlocked_item_flags;
extern int g_game_l18_mode_state;
extern int g_door_trigger_flags[] __attribute__((sda));
extern u8 *g_waypoint_table, *g_moby_l18_table;
extern void moby_reset_matching_effects(void *), moby_reset_vars_defaults(void *), level_apply_index_for_key(void *);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int), req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern int hero_is_reachable_for_count(void *, int, float);
extern void text_print_localized_formatted(int, int, int), func_L00_0030C710(int), moby_mark_table_entry_flagged(int);
extern void help_unlock_entry(int), value_set_entry_by_index_us2(int, int);
extern int moby_handle_request_slot_state(int);
extern int subtitle_request_voice_line_us2(int, int);
extern void level_capture_checkpoint_state(void *, void *), moby_mark_spawned(void *);
extern int MemcardSave(int, int);
extern int math_fast_float_d(void *), FastDecTimer(void *), FloatToInt(float);
extern float math_random_float_range(float, float), vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float), FastVecLength(void *), FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void anim_start_blended(void *, int, int, int), vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);

/* Updates the ship parts shop character (moby class 4754): it checks which parts the player has, talks about the price, takes the bolts when the player buys, and turns its head toward the player (USA v2.00 copy). */
void UpdatePartsPurchaseNpc_us2(u8 *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    float speed, yaw, pitch, random_yaw;
    float blend = 0.3f;
    int active;

    moby_reset_matching_effects(obj);
    switch (U8_AT(obj, 0x20)) {
    case 0:
        if (g_mover_trigger_flag)
            goto remove_object;
        if (g_object_state_flags_h & 0x10000)
            moby_set_state(obj, 3, -1);
        else
            moby_set_state(obj, 1, -1);
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, S32_AT(state, 0x120)) && req_push_queue(g_request_l18_queue, 0x90)) {
            level_apply_index_for_key(obj);
            req_launch_queued(g_request_l18_queue);
            moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        g_door_trigger_flags[1] = 1;
        if (g_game_l18_mode_state == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            hero_reset_position_and_direction(g_waypoint_table + S32_AT(state, 0x120) * 128 + 0x30,
                              g_waypoint_table + S32_AT(state, 0x120) * 128 + 0x70, 0, 1);
            U8_AT(obj, 0x31) = 1;
            U16_AT(obj, 0x34) &= 0xFFFE;
            g_door_trigger_flags[1] = 0;
            moby_set_state(obj, 3, -1);
        }
        break;
    case 3:
        if (g_game_flag_table.first && g_game_flag_table.second && g_game_flag_table.third) {
            if (g_player_bolts >= ((PurchaseLevelInfo *)g_weapon_l18_table)[g_purchase_level_index].cost)
                moby_set_state(obj, 5, -1);
            else
                moby_set_state(obj, 4, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            int count = 3;
            if (g_game_flag_table.first)
                count = 2;
            if (g_game_flag_table.second)
                count--;
            if (g_game_flag_table.third)
                count--;
            text_print_localized_formatted(0x132B, count, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 4:
        if (((PurchaseLevelInfo *)g_weapon_l18_table)[g_item_slot_to_record.planet].cost < g_player_bolts) {
            moby_set_state(obj, 5, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x132C, ((PurchaseLevelInfo *)g_weapon_l18_table)[g_item_slot_to_record.planet].cost, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 5:
        if (g_player_bolts < ((PurchaseLevelInfo *)g_weapon_l18_table)[g_item_slot_to_record.planet].cost) {
            func_L00_0030C710(180);
            moby_set_state(obj, 4, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x132D, ((PurchaseLevelInfo *)g_weapon_l18_table)[g_item_slot_to_record.planet].cost, -1);
            level_apply_index_for_key(obj);
            if ((g_pad_held_flags & 16) && req_push_queue(g_request_l18_queue, 0x91)) {
                req_launch_queued(g_request_l18_queue);
                moby_set_state(obj, 6, -1);
                moby_mark_table_entry_flagged(U8_AT(obj, 0xB0));
            }
        }
        break;
    case 6:
        if (g_game_l18_mode_state == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        {
            unsigned int timer = U16_AT(obj, 0x96);
            unsigned int elapsed = timer++;
            U16_AT(obj, 0x96) = timer;
            if (elapsed >= 20) {
                g_door_trigger_flags[1] = 1;
                if (!game_is_either_mode_two()) {
                    g_door_trigger_flags[1] = 0;
                    U8_AT(obj, 0x31) = 1;
                    U16_AT(obj, 0x34) &= 0xFFFE;
                    if (!g_mover_trigger_flag) {
                        g_player_bolts -= ((PurchaseLevelInfo *)g_weapon_l18_table)[g_purchase_level_index].cost;
                        func_L00_0030C710(180);
                        if (S32_AT(state, 0x124) != -1)
                            U8_AT(g_moby_l18_table + S32_AT(state, 0x124) * 256, 0xBC) = 1;
                        help_unlock_entry(55);
                        moby_handle_request_slot_state(55);
                    }
                    moby_set_state(obj, 7, -1);
                    U8_AT(obj, 0x31) = 0;
                    U16_AT(obj, 0x34) |= 1;
                }
            }
        }
        break;
    case 7: {
        unsigned int timer = U16_AT(obj, 0x96);
        unsigned int elapsed = timer++;
        U16_AT(obj, 0x96) = timer;
        if (elapsed >= 41) {
            value_set_entry_by_index_us2(0x1231, -1);
            subtitle_request_voice_line_us2(0xA11, 0x68);
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 16);
            MemcardSave(0, -1);
        remove_object:
            moby_mark_spawned(obj);
            return;
        }
        break;
    }
    }
    if (U8_AT(obj, 0x20)) {
        if (!U8_AT(obj, 0x43) && FastDecTimer(state + 0x11E)) {
            U16_AT(state, 0x11E) = FloatToInt(math_random_float_range(1200, 2400));
            if (U8_AT(obj, 0x43) != 1)
                anim_start_blended(obj, 1, 0, 10);
        } else if ((U8_AT(obj, 0x60) & 2) && U8_AT(obj, 0x43)) {
            anim_start_blended(obj, 0, 0, 10);
        }
    }
    speed = 0.02f;
    active = 0;
    if (!U8_AT(obj, 0x43)) {
        active = 1;
        if (vec_distance_xy(obj + 0x10, g_hero_position) < 8 &&
            FastDiffRots(F32_AT(obj, 0xF8),
                          mat_fast_helper_a(((PurchaseHero *)(g_hero_position - 128))->x - F32_AT(obj, 0x10),
                                        ((PurchaseHero *)(g_hero_position - 128))->y - F32_AT(obj, 0x14))) < 1.5707965f) {
            if (FastVecLength(g_hero_position + 0x90) > 0.01f)
                S32_AT(state, 0x114) = 120;
            else
                math_fast_float_d(state + 0x114);
        } else if (S32_AT(state, 0x114)) {
            S32_AT(state, 0x114) = 0;
            qcopy_nc(state + 0x100, g_hero_position + 0x60);
        }
        if (math_fast_float_d(state + 0x118)) {
            S32_AT(state, 0x118) = FloatToInt(math_random_float_range(180, 300));
            random_yaw = FastAddRotations(F32_AT(obj, 0xF8), math_random_float_range(-90, 90) * 0.017453294f);
            pitch = math_random_float_range(0, 30);
            vec_build_spherical_offset(state + 0x100, 6, random_yaw, pitch * 0.017453294f);
            FastVecAdd(state + 0x100, state + 0x100, obj + 0x10);
        }
        if (S32_AT(state, 0x114)) {
            qcopy_nc(target, g_hero_position + 0x60);
            speed = 0.04f;
        } else {
            qcopy_nc(target, state + 0x100);
        }
    }
    if (active) {
        qcopy_nc(position, obj + 0x10);
        position[2] += 2;
        FastVecSub(delta, target, position);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta[0], delta[1]), F32_AT(obj, 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        if (yaw > 1.5707965f)
            yaw = 1.5707965f;
        else if (yaw < -1.5707965f)
            yaw = -1.5707965f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F32_AT(state, 0x64) = pitch;
        F32_AT(state, 0x68) = yaw * 0.6f;
        F32_AT(state, 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags)
        F32_AT(state, 0x70) = 2.75f;
    moby_update_eased_node(obj, state, 0, speed, blend);
    moby_update_eased_node(obj, state + 0x80, 1, speed, blend);
}
