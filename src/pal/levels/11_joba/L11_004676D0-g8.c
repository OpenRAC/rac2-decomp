#include "names.h"
/* func_PAL_L11_004676D0, the PAL copy of func_L11_004618C0: the same C with 50 Hz timers, sound ids and
   both look rates scaled by 1.44 (1.2 squared), which the two calls at the end share. */
#include "common.h"
typedef struct BarlowUtilityQueueView BarlowUtilityQueueView;
extern u8 g_inventory_have_flags, g_unlocked_item_flags;
extern u32 g_object_state_flags_d NOT_SDA;
extern u32 g_pad_held_flags NOT_SDA;
extern u8 g_item_slot_to_record[];
extern int g_player_bolts MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; float position[4]; float rotation[4];
    u8 padA0[0x40]; float aim[4]; u8 padF0[0x20]; float velocity[4];
} JobaPlayerView;
extern JobaPlayerView g_hero_state;
extern u8 g_hero_target_point[];
extern u8 g_request_l11_queue[];
typedef struct {
    u8 pad[0x30];
    float position[4];
    u8 pad40[0x30];
    float rotation[4];
} VendorRecord;
extern VendorRecord *g_arena_camera_table[] MACRO_ADDR;
typedef struct {
    u8 pad[0x80];
    int price;
    u8 tail[0x5C];
} VendorOffer;
extern VendorOffer g_item_l11_record_table[];
extern int g_level_state_flags[] __attribute__((sda));
extern int g_arena_state[] MACRO_ADDR;
extern void moby_reset_matching_effects_alt(u8 *);
extern void moby_set_state(u8 *, int, int);
extern void moby_reset_vars_defaults(char *);
extern int IsPointInCuboid(char *, int);
extern int req_push_queue(u8 *, int);
extern int req_launch_queued(BarlowUtilityQueueView *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction_pal(float *, float *, int, int);
extern int hero_is_reachable_for_count(u8 *, int, float);
extern void func_L00_0030C710(int);
extern void text_print_localized_formatted(int, int, int);
extern void level_apply_index_for_key(int);
extern void moby_set_byte_on_group(int, int);
extern void help_unlock_entry(int);
extern void value_set_entry_by_index_pal(int, int);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(void *);
extern int FastDecTimer(void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void anim_start_blended_pal(u8 *, int, int, int);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastVecLength(void *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, float *);
extern void FastVecSub(float *, float *, float *);
extern float fast_subtract_rotations(float, float);
extern float vec_length_xy(void *);
extern void moby_update_eased_node(char *, u8 *, char *, float, float);

/* Per-frame update of the Joba vendor: it waits for the player, runs the purchase flow (price check, prompts, bolts and unlock) and keeps its head turned toward the player (PAL: 50 Hz timings). */
void joba_purchase_controller_update_pal(u8 *moby) {
    float destination[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    int record_index, tracking;
    float rate, blend;
    float yaw, pitch, distance, yaw_jitter, pitch_jitter, heading;
    moby_reset_matching_effects_alt(moby);
    switch (moby[0x20]) {
    case 0:
        if (g_inventory_have_flags) { moby_mark_spawned(moby); return; }
        if (g_object_state_flags_d & 0x800) moby_set_state(moby, 2, -1);
        else moby_set_state(moby, 1, -1);
        moby_reset_vars_defaults((char *)moby);
        break;
    case 1:
        if (IsPointInCuboid((char *)g_hero_state.position, *(int *)(vars + 0x120)) && req_push_queue(g_request_l11_queue, 0x6B)) {
            level_apply_index_for_key((int)moby);
            req_launch_queued((BarlowUtilityQueueView *)g_request_l11_queue);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        g_level_state_flags[2] = 1;
        if (g_arena_state[0] == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            VendorRecord *record;
            g_level_state_flags[2] = 0;
            record = (VendorRecord *)((u32)g_arena_camera_table[0] + *(int *)(vars + 0x120) * sizeof(VendorRecord));
            hero_reset_position_and_direction_pal(record->position, record->rotation, 0, 1);
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            if (g_player_bolts < ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price) moby_set_state(moby, 3, -1);
            else moby_set_state(moby, 4, -1);
        }
        break;
    case 3:
        if (((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price < g_player_bolts) {
            moby_set_state(moby, 4, -1);
        } else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x130E, ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price, -1);
            level_apply_index_for_key((int)moby);
        }
        break;
    case 4:
        if (g_player_bolts < ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price) {
            func_L00_0030C710(150);
            moby_set_state(moby, 3, -1);
        } else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x130D, ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price, -1);
            level_apply_index_for_key((int)moby);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_request_l11_queue, 0x6C)) {
                req_launch_queued((BarlowUtilityQueueView *)g_request_l11_queue);
                moby_set_state(moby, 5, -1);
            }
        }
        break;
    case 5:
        g_level_state_flags[2] = 1;
        if (g_arena_state[0] == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_level_state_flags[2] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            if (moby[0x21] != 0xFF) moby_set_byte_on_group(moby[0x21], 1);
            if (!g_inventory_have_flags) {
                g_player_bolts = g_player_bolts - ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price;
                func_L00_0030C710(150);
                help_unlock_entry(8);
            }
            record_index = *(int *)(vars + 0x124);
            if (record_index != -1) {
                VendorRecord *record = (VendorRecord *)((u32)g_arena_camera_table[0] + record_index * sizeof(VendorRecord));
                hero_reset_position_and_direction_pal(record->position, record->rotation, 0, 1);
            }
            value_set_entry_by_index_pal(0x1230, -1);
            MemcardSave(0, -1);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    if (moby[0x20] != 0) {
        if (moby[0x43] == 0 && FastDecTimer(vars + 0x11E)) {
            *(short *)(vars + 0x11E) = FloatToInt(((math_random_float_range(1200.0f, 2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
            if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 8);
        } else if ((moby[0x60] & 2) && moby[0x43] != 0) {
            anim_start_blended_pal(moby, 0, 0, 8);
        }
    }
    tracking = 0;
    rate = 0.02f;
    blend = 0.3f;
    if (moby[0x43] == 0) {
        tracking = 1;
        distance = vec_distance_xy(moby + 0x10, g_hero_state.position);
        if (distance < 8.0f && FastDiffRots(*(float *)(moby + 0xF8), mat_fast_helper_a(g_hero_state.aim[0] - *(float *)(moby + 0x10), g_hero_state.aim[1] - *(float *)(moby + 0x14))) < 1.5707965f) {
            if (FastVecLength(g_hero_state.velocity) > 0.01f) *(int *)(vars + 0x114) = 100;
            else math_fast_float_d(vars + 0x114);
        } else if (*(int *)(vars + 0x114)) {
            *(int *)(vars + 0x114) = 0;
            qcopy(vars + 0x100, g_hero_target_point);
        }
        if (math_fast_float_d(vars + 0x118)) {
            *(int *)(vars + 0x118) = FloatToInt(((math_random_float_range(180.0f, 300.0f)) * 5.0f + 2.0f) * 0.16666667f);
            yaw_jitter = math_random_float_range(-90.0f, 90.0f);
            heading = FastAddRotations(*(float *)(moby + 0xF8), yaw_jitter * 0.017453294f);
            pitch_jitter = math_random_float_range(0, 30.0f);
            vec_build_spherical_offset((float *)(vars + 0x100), 6.0f, heading, pitch_jitter * 0.017453294f);
            FastVecAdd((float *)(vars + 0x100), (float *)(vars + 0x100), (float *)(moby + 0x10));
        }
        if (*(int *)(vars + 0x114)) {
            qcopy(destination, g_hero_target_point);
            rate = 0.04f;
            blend = 0.3f;
        } else qcopy(destination, vars + 0x100);
    }
    if (tracking) {
        qcopy(origin, moby + 0x10);
        origin[2] += 2.0f;
        FastVecSub(difference, destination, origin);
        yaw = fast_subtract_rotations(mat_fast_helper_a(difference[0], difference[1]), *(float *)(moby + 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(difference), difference[2]);
        if (yaw > 1.5707965f) yaw = 1.5707965f;
        else if (yaw < -1.5707965f) yaw = -1.5707965f;
        if (pitch > 0.52359885f) pitch = 0.52359885f;
        else if (pitch < -0.52359885f) pitch = -0.52359885f;
        *(float *)(vars + 0x64) = pitch;
        *(float *)(vars + 0x68) = yaw * 0.6f;
        *(float *)(vars + 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags) *(float *)(vars + 0x70) = 2.75f;
    moby_update_eased_node((char *)moby, vars, (char *)0, rate * 1.44f, blend * 1.44f);
    moby_update_eased_node((char *)moby, vars + 0x80, (char *)1, rate * 1.44f, blend * 1.44f);
    return;
}
