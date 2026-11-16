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
/* The dialogue gate is written before each poll and cleared on completion. */
extern volatile int g_arena_script_flags[] MACRO_ADDR;
extern int g_arena_state[] MACRO_ADDR;
extern void moby_reset_matching_effects_alt(u8 *);
extern void moby_set_state(u8 *, int, int);
extern void moby_reset_vars_defaults(char *);
extern int IsPointInCuboid(char *, int);
extern int req_push_queue(u8 *, int);
extern int req_launch_queued(BarlowUtilityQueueView *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(float *, float *, int, int);
extern int hero_is_reachable_for_count(u8 *, int, float);
extern void func_L00_0030C710(int);
extern void text_print_localized_formatted(int, int, int);
extern void level_apply_index_for_key(int);
extern void moby_set_byte_on_group(int, int);
extern void help_unlock_entry(int);
extern void value_set_entry_by_index(int, int);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(void *);
extern int FastDecTimer(void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void anim_start_blended(u8 *, int, int, int);
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

/* Updates the Shady Salesman (moby class 3733): he waits for the hero, offers an item for bolts, takes payment, and turns his head to watch the hero. */
void UpdateJobaPurchaseController(u8 *object) {
    float destination[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    int index, tracking;
    float rate;
    float yaw, pitch, distance, yaw_offset, pitch_offset, heading;
    moby_reset_matching_effects_alt(object);
    switch (object[0x20]) {
    case 0:
        if (g_inventory_have_flags) { moby_mark_spawned(object); return; }
        if (g_object_state_flags_d & 0x800) moby_set_state(object, 2, -1);
        else moby_set_state(object, 1, -1);
        moby_reset_vars_defaults((char *)object);
        break;
    case 1:
        if (IsPointInCuboid((char *)g_hero_state.position, *(int *)(vars + 0x120)) && req_push_queue(g_request_l11_queue, 0x6B)) {
            level_apply_index_for_key((int)object);
            req_launch_queued((BarlowUtilityQueueView *)g_request_l11_queue);
            moby_set_state(object, 2, -1);
        }
        break;
    case 2:
        g_arena_script_flags[0] = 1;
        if (g_arena_state[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            VendorRecord *record;
            g_arena_script_flags[0] = 0;
            record = (VendorRecord *)((u32)g_arena_camera_table[0] + *(int *)(vars + 0x120) * sizeof(VendorRecord));
            hero_reset_position_and_direction(record->position, record->rotation, 0, 1);
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (g_player_bolts < ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price) moby_set_state(object, 3, -1);
            else moby_set_state(object, 4, -1);
        }
        break;
    case 3:
        if (((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price < g_player_bolts) {
            moby_set_state(object, 4, -1);
        } else if (hero_is_reachable_for_count(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x27BC, ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price, -1);
            level_apply_index_for_key((int)object);
        }
        break;
    case 4:
        if (g_player_bolts < ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price) {
            func_L00_0030C710(180);
            moby_set_state(object, 3, -1);
        } else if (hero_is_reachable_for_count(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x27BB, ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price, -1);
            level_apply_index_for_key((int)object);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_request_l11_queue, 0x6C)) {
                req_launch_queued((BarlowUtilityQueueView *)g_request_l11_queue);
                moby_set_state(object, 5, -1);
            }
        }
        break;
    case 5:
        g_arena_script_flags[0] = 1;
        if (g_arena_state[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_arena_script_flags[0] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (object[0x21] != 0xFF) moby_set_byte_on_group(object[0x21], 1);
            if (!g_inventory_have_flags) {
                g_player_bolts = g_player_bolts - ((VendorOffer *)((u32)g_item_l11_record_table + g_item_slot_to_record[8] * sizeof(VendorOffer)))->price;
                func_L00_0030C710(180);
                help_unlock_entry(8);
            }
            index = *(int *)(vars + 0x124);
            if (index != -1) {
                VendorRecord *record = (VendorRecord *)((u32)g_arena_camera_table[0] + index * sizeof(VendorRecord));
                hero_reset_position_and_direction(record->position, record->rotation, 0, 1);
            }
            value_set_entry_by_index(0x1230, -1);
            MemcardSave(0, -1);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && FastDecTimer(vars + 0x11E)) {
            *(short *)(vars + 0x11E) = FloatToInt(math_random_float_range(1200.0f, 2400.0f));
            if (object[0x43] != 1) anim_start_blended(object, 1, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            anim_start_blended(object, 0, 0, 10);
        }
    }
    tracking = 0;
    rate = 0.02f;
    if (object[0x43] == 0) {
        tracking = 1;
        distance = vec_distance_xy(object + 0x10, g_hero_state.position);
        if (distance < 8.0f && FastDiffRots(*(float *)(object + 0xF8), mat_fast_helper_a(g_hero_state.aim[0] - *(float *)(object + 0x10), g_hero_state.aim[1] - *(float *)(object + 0x14))) < 1.5707965f) {
            if (FastVecLength(g_hero_state.velocity) > 0.01f) *(int *)(vars + 0x114) = 120;
            else math_fast_float_d(vars + 0x114);
        } else if (*(int *)(vars + 0x114)) {
            *(int *)(vars + 0x114) = 0;
            qcopy(vars + 0x100, g_hero_target_point);
        }
        if (math_fast_float_d(vars + 0x118)) {
            *(int *)(vars + 0x118) = FloatToInt(math_random_float_range(180.0f, 300.0f));
            yaw_offset = math_random_float_range(-90.0f, 90.0f);
            heading = FastAddRotations(*(float *)(object + 0xF8), yaw_offset * 0.017453294f);
            pitch_offset = math_random_float_range(0, 30.0f);
            vec_build_spherical_offset((float *)(vars + 0x100), 6.0f, heading, pitch_offset * 0.017453294f);
            FastVecAdd((float *)(vars + 0x100), (float *)(vars + 0x100), (float *)(object + 0x10));
        }
        if (*(int *)(vars + 0x114)) {
            qcopy(destination, g_hero_target_point);
            rate = 0.04f;
        } else qcopy(destination, vars + 0x100);
    }
    if (tracking) {
        qcopy(origin, object + 0x10);
        origin[2] += 2.0f;
        FastVecSub(difference, destination, origin);
        yaw = fast_subtract_rotations(mat_fast_helper_a(difference[0], difference[1]), *(float *)(object + 0xF8));
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
    for (index = 0; index < 2; index++)
        moby_update_eased_node((char *)object, vars + index * 0x80, (char *)index, rate, 0.3f);
    return;
}
