#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
#define I(p, o) (*(s32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
extern u8 g_level_flag_bytes[] MACRO_ADDR, g_price_flag_block[] MACRO_ADDR, g_unlocked_item_flags MACRO_ADDR;
#define D_001A7BDA D_001A7BD8[2]
#define D_L17_001A7C8F D_L17_001A7C88[7]
extern s32 g_message_switch_busy_flags[] MACRO_ADDR;
#define BUSY D_L17_001B2964[1]
extern s32 g_object_state_flags_g NOT_SDA, g_pad_held_flags NOT_SDA;
extern s32 g_player_bolts MACRO_ADDR;
extern s32 g_spark_effect_state MACRO_ADDR, g_linked_moby_base MACRO_ADDR, g_moby_l17_pool MACRO_ADDR;
extern u8 g_request_l17_queue[];
typedef struct { char pad[0x30]; s32 lo; s32 hi; } PriceTable;
extern PriceTable g_vendor_l17_price_table;
extern s32 g_vendor_price_low NOT_SDA, g_vendor_price_high NOT_SDA;
#define PRICE_LT(m) (D_L17_001A7C8F ? (m) < D_L17_0028C584 : (m) < D_L17_0028C580)
typedef struct { char pad[0x80]; char obj[0x60]; V pos; } HeroRecord;
extern HeroRecord g_hero_state;
extern void moby_reset_matching_effects(s32);
extern void moby_set_state(s32, s32, s32);
extern void moby_reset_vars_defaults(s32);
extern int IsPointInCuboid(void *, s32);
extern int req_push_queue(void *, s32);
extern void level_apply_index_for_key(s32);
extern s32 req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(s32, s32, s32, s32);
extern int hero_is_reachable_for_count(s32, s32, float);
extern void func_L00_0030C710(s32), text_print_localized_formatted(s32, s32, s32);
extern void moby_mark_flag_and_append_to_list(s32), snd_play_indexed_us2(s32), moby_mark_spawned(s32);
extern int MemcardSave(s32, s32);
extern int FastDecTimer(s32), math_fast_float_d(s32);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void anim_start_blended(s32, s32, s32, s32);
extern float vec_distance_xy(s32, void *), mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float FastVecLength(void *), FastAddRotations(float, float);
extern void vec_build_spherical_offset(s32, float, float, float), FastVecAdd(s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern float fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void moby_update_eased_node(s32, s32, s32, float, float);
/* A constant rate reaches the argument register directly, so each call loads it again. */
static inline void update_joint(s32 obj, s32 joint, s32 index, float speed, float rate) {
    moby_update_eased_node(obj, joint, index, speed, rate);
}

void UpdateBoltPurchaseMoby_us2(s32 obj) {
    V target, raised, delta;
    s32 data = I(obj, 0x68), active;
    float speed, yaw, pitch, ang;

    moby_reset_matching_effects(obj);
    switch (B(obj, 0x20)) {
    case 0:
        if (g_joint_destroy_flag) goto destroy;
        if (g_object_state_flags_g & 0x200) {
            s32 bolts = g_player_bolts;
            if (PRICE_LT(bolts)) moby_set_state(obj, 3, -1);
            else moby_set_state(obj, 4, -1);
        } else {
            moby_set_state(obj, 1, -1);
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_state.obj, I(data, 0x120)) && req_push_queue(g_request_l17_queue, 0x89)) {
            level_apply_index_for_key(obj);
            req_launch_queued(g_request_l17_queue);
            moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        BUSY = 1;
        if (g_spark_effect_state == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            BUSY = 0;
            {
                s32 p = g_linked_moby_base + (I(data, 0x120) << 7);
                hero_reset_position_and_direction(p + 0x30, p + 0x70, 0, 1);
            }
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            {
                s32 bolts = g_player_bolts;
                if (PRICE_LT(bolts)) moby_set_state(obj, 3, -1);
                else moby_set_state(obj, 4, -1);
            }
        }
        break;
    case 3:
        {
            s32 bolts = g_player_bolts;
            if (g_price_use_high_flag ? g_vendor_l17_price_table.hi < bolts : g_vendor_l17_price_table.lo < bolts) {
                moby_set_state(obj, 4, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 4.f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1329, g_price_use_high_flag ? g_vendor_l17_price_table.hi : g_vendor_l17_price_table.lo, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 4:
        {
            s32 bolts = g_player_bolts;
            if (g_price_use_high_flag ? bolts < g_vendor_l17_price_table.hi : bolts < g_vendor_l17_price_table.lo) {
                func_L00_0030C710(180);
                moby_set_state(obj, 3, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 4.f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x132A, g_price_use_high_flag ? g_vendor_l17_price_table.hi : g_vendor_l17_price_table.lo, -1);
            level_apply_index_for_key(obj);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_request_l17_queue, 0x8a)) {
                req_push_queue(g_request_l17_queue, 0x12);
                req_push_queue(g_request_l17_queue, 0x8b);
                req_launch_queued(g_request_l17_queue);
                moby_set_state(obj, 5, -1);
            }
        }
        break;
    case 5:
        BUSY = 1;
        if (g_spark_effect_state == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            BUSY = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (!g_joint_destroy_flag) {
                {
                    s32 bolts = g_player_bolts;
                    g_player_bolts = bolts - (g_price_use_high_flag ? g_vendor_price_high : g_vendor_price_low);
                }
                func_L00_0030C710(180);
                moby_mark_flag_and_append_to_list(0x12);
                snd_play_indexed_us2(0x12);
                if (I(data, 0x124) != -1) B((I(data, 0x124) << 8) + g_moby_l17_pool, 0xbc) = 1;
                MemcardSave(0, -1);
destroy:
                moby_mark_spawned(obj);
                return;
            }
        }
        break;
    }

    if (B(obj, 0x20)) {
        if (!B(obj, 0x43) && FastDecTimer(data + 0x11e))
            H(data, 0x11e) = FloatToInt(math_random_float_range(1200.f, 2400.f));
        else if ((B(obj, 0x60) & 2) && B(obj, 0x43))
            anim_start_blended(obj, 0, 0, 10);
    }

    speed = .02f;
    active = 0;
    if (!B(obj, 0x43)) {
        active = 1;
        if (vec_distance_xy(obj + 0x10, g_hero_state.obj) < 8.f
            && FastDiffRots(F(obj, 0xf8), mat_fast_helper_a(g_hero_state.pos.f[0] - F(obj, 0x10),
                                                         g_hero_state.pos.f[1] - F(obj, 0x14))) < 1.5707964897155762f) {
            if (FastVecLength(g_hero_state.obj + 0x90) > .01f) I(data, 0x114) = 120;
            else math_fast_float_d(data + 0x114);
        } else if (I(data, 0x114)) {
            I(data, 0x114) = 0;
            qcopy((void *)(data + 0x100), &g_hero_state.pos);
        }
        if (math_fast_float_d(data + 0x118)) {
            I(data, 0x118) = FloatToInt(math_random_float_range(180.f, 300.f));
            ang = FastAddRotations(F(obj, 0xf8), math_random_float_range(-90.f, 90.f) * 0.01745329424738884f);
            pitch = math_random_float_range(0.f, 30.f) * 0.01745329424738884f;
            vec_build_spherical_offset(data + 0x100, 6.f, ang, pitch);
            FastVecAdd(data + 0x100, data + 0x100, obj + 0x10);
        }
        if (I(data, 0x114)) {
            qcopy(&target, &g_hero_state.pos);
            speed = .04f;
        } else {
            qcopy(&target, (void *)(data + 0x100));
        }
    }

    if (active) {
        qcopy(&raised, (void *)(obj + 0x10));
        raised.f[2] += 2.f;
        FastVecSub(&delta, &target, &raised);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta.f[0], delta.f[1]), F(obj, 0xf8));
        pitch = -mat_fast_helper_a(vec_length_xy(&delta), delta.f[2]);
        if (yaw > 1.5707964897155762f) yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f) yaw = -1.5707964897155762f;
        if (pitch > .52359885f) pitch = .52359885f;
        else if (pitch < -.52359885f) pitch = -.52359885f;
        F(data, 0x64) = pitch;
        F(data, 0x68) = yaw * .6f;
        F(data, 0xe8) = yaw * .4f;
    }

    if (g_unlocked_item_flags) F(data, 0x70) = 2.75f;
    update_joint(obj, data, 0, speed, .3f);
    update_joint(obj, data + 0x80, 1, speed, .3f);
}
