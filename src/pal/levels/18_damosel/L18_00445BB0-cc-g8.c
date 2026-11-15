/* func_PAL_L18_00445BB0, the PAL copy of func_L18_00440718: the same C, where the timers and fades take the 50 Hz scale,
   the text ids become 0x132B to 0x132D, and the two blend calls take speed and blend times 1.44f. */
#include "common.h"

#define S32_AT(p, o) (*(int *)((u8 *)(p) + (o)))
#define F32_AT(p, o) (*(float *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x84]; u8 first; u8 pad85; u8 second; u8 pad87[2]; u8 third; } PurchaseParts;
typedef struct { u8 pad[0x37]; u8 planet; } PurchaseSave;
typedef struct { u8 pad[0x80]; int cost; u8 tail[0x5C]; } PurchaseLevelInfo;
typedef struct { u8 pad[0xE0]; float x; float y; } PurchaseHero;

extern u8 g_hero_position[], D_L18_0026BCF0[], D_L18_001BF9C0[];
extern PurchaseParts D_001395B8;
extern PurchaseSave g_item_slot_to_record;
extern int D_001397F8 NOT_SDA;
extern int g_player_bolts;
extern int D_00138324 NOT_SDA;
extern u8 D_001A7B2F;
extern u8 D_0013959F NOT_SDA;
extern u8 D_001A7A40;
extern int D_L18_001A8F00;
extern int D_L18_001B2564[] __attribute__((sda));
extern u8 *g_waypoint_table, *g_moby_l18_table;

extern void moby_reset_matching_effects(void *), moby_reset_vars_defaults(void *), level_apply_index_for_key(void *);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int), req_push_queue(void *, int);
extern void req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern int hero_is_reachable_for_count(void *, int, float);
extern void text_print_localized_formatted(int, int, int), func_L00_0030C710(int), moby_mark_table_entry_flagged(int);
extern void help_unlock_entry(int), moby_handle_request_slot_state(int), value_set_entry_by_index(int, int), subtitle_request_voice_line(int, int);
extern void level_capture_checkpoint_state(void *, void *), MemcardSave(int, int), moby_mark_spawned(void *);
extern int math_fast_float_d(void *), FastDecTimer(void *), FloatToInt(float);
extern float math_random_float_range(float, float), vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float), FastVecLength(void *), FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void anim_start_blended(void *, int, int, int), vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);

void func_PAL_L18_00445BB0(u8 *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    float speed, yaw, pitch, random_yaw;
    float blend;
    int active;

    moby_reset_matching_effects(obj);
    switch (U8_AT(obj, 0x20)) {
    case 0:
        if (D_001A7B2F)
            goto remove_object;
        if (D_001397F8 & 0x10000)
            moby_set_state(obj, 3, -1);
        else
            moby_set_state(obj, 1, -1);
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, S32_AT(state, 0x120)) && req_push_queue(D_L18_001BF9C0, 0x90)) {
            level_apply_index_for_key(obj);
            req_launch_queued(D_L18_001BF9C0);
            moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        D_L18_001B2564[1] = 1;
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            hero_reset_position_and_direction(g_waypoint_table + S32_AT(state, 0x120) * 128 + 0x30,
                              g_waypoint_table + S32_AT(state, 0x120) * 128 + 0x70, 0, 1);
            U8_AT(obj, 0x31) = 1;
            U16_AT(obj, 0x34) &= 0xFFFE;
            D_L18_001B2564[1] = 0;
            moby_set_state(obj, 3, -1);
        }
        break;
    case 3:
        if (D_001395B8.first && D_001395B8.second && D_001395B8.third) {
            if (g_player_bolts >= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost)
                moby_set_state(obj, 5, -1);
            else
                moby_set_state(obj, 4, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            int count = 3;
            if (D_001395B8.first)
                count = 2;
            if (D_001395B8.second)
                count--;
            if (D_001395B8.third)
                count--;
            text_print_localized_formatted(0x132B, count, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 4:
        if (((PurchaseLevelInfo *)D_L18_0026BCF0)[g_item_slot_to_record.planet].cost < g_player_bolts) {
            moby_set_state(obj, 5, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x132C, ((PurchaseLevelInfo *)D_L18_0026BCF0)[g_item_slot_to_record.planet].cost, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 5:
        if (g_player_bolts < ((PurchaseLevelInfo *)D_L18_0026BCF0)[g_item_slot_to_record.planet].cost) {
            func_L00_0030C710(150);
            moby_set_state(obj, 4, -1);
        } else if (hero_is_reachable_for_count(obj, 10, 1.0f)) {
            func_L00_0030C710(150);
            text_print_localized_formatted(0x132D, ((PurchaseLevelInfo *)D_L18_0026BCF0)[g_item_slot_to_record.planet].cost, -1);
            level_apply_index_for_key(obj);
            if ((D_00138324 & 16) && req_push_queue(D_L18_001BF9C0, 0x91)) {
                req_launch_queued(D_L18_001BF9C0);
                moby_set_state(obj, 6, -1);
                moby_mark_table_entry_flagged(U8_AT(obj, 0xB0));
            }
        }
        break;
    case 6:
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        {
            unsigned int timer = U16_AT(obj, 0x96);
            unsigned int elapsed = timer++;
            U16_AT(obj, 0x96) = timer;
            if (elapsed >= 17) {
                D_L18_001B2564[1] = 1;
                if (!game_is_either_mode_two()) {
                    D_L18_001B2564[1] = 0;
                    U8_AT(obj, 0x31) = 1;
                    U16_AT(obj, 0x34) &= 0xFFFE;
                    if (!D_001A7B2F) {
                        g_player_bolts -= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost;
                        func_L00_0030C710(150);
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
        if (elapsed >= 34) {
            value_set_entry_by_index(0x1231, -1);
            subtitle_request_voice_line(0xA11, 0x68);
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
            U16_AT(state, 0x11E) = FloatToInt((math_random_float_range(1200, 2400) * 5 + 2) * 0.16666667f);
            if (U8_AT(obj, 0x43) != 1)
                anim_start_blended(obj, 1, 0, 8);
        } else if ((U8_AT(obj, 0x60) & 2) && U8_AT(obj, 0x43)) {
            anim_start_blended(obj, 0, 0, 8);
        }
    }
    speed = 0.02f;
    blend = 0.3f;
    active = 0;
    if (!U8_AT(obj, 0x43)) {
        active = 1;
        if (vec_distance_xy(obj + 0x10, g_hero_position) < 8 &&
            FastDiffRots(F32_AT(obj, 0xF8),
                          mat_fast_helper_a(((PurchaseHero *)(g_hero_position - 128))->x - F32_AT(obj, 0x10),
                                        ((PurchaseHero *)(g_hero_position - 128))->y - F32_AT(obj, 0x14))) < 1.5707965f) {
            if (FastVecLength(g_hero_position + 0x90) > 0.01f)
                S32_AT(state, 0x114) = 100;
            else
                math_fast_float_d(state + 0x114);
        } else if (S32_AT(state, 0x114)) {
            S32_AT(state, 0x114) = 0;
            qcopy_nc(state + 0x100, g_hero_position + 0x60);
        }
        if (math_fast_float_d(state + 0x118)) {
            S32_AT(state, 0x118) = FloatToInt((math_random_float_range(180, 300) * 5 + 2) * 0.16666667f);
            random_yaw = FastAddRotations(F32_AT(obj, 0xF8), math_random_float_range(-90, 90) * 0.017453294f);
            pitch = math_random_float_range(0, 30);
            vec_build_spherical_offset(state + 0x100, 6, random_yaw, pitch * 0.017453294f);
            FastVecAdd(state + 0x100, state + 0x100, obj + 0x10);
        }
        if (S32_AT(state, 0x114)) {
            qcopy_nc(target, g_hero_position + 0x60);
            speed = 0.04f;
            blend = 0.3f;
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
    if (D_001A7A40)
        F32_AT(state, 0x70) = 2.75f;
    moby_update_eased_node(obj, state, 0, speed * 1.44f, blend * 1.44f);
    moby_update_eased_node(obj, state + 0x80, 1, speed * 1.44f, blend * 1.44f);
}
