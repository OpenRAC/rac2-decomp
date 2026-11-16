/* func_US2_L14_00427280, the USA v2.00 copy of func_L14_00425CB0: the same C. */
#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;

#define I(p, o) (*(s32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

extern u8 g_item_seller_busy MACRO_ADDR, g_item_seller_flags[] MACRO_ADDR, g_item_seller_done_flag MACRO_ADDR;
extern u8 g_shop_flags[] MACRO_ADDR, g_unlocked_item_flags MACRO_ADDR;
extern s32 g_seller_state_words[] MACRO_ADDR;

extern s32 g_pad_held_flags NOT_SDA;
extern s32 g_player_bolts MACRO_ADDR; /* the player's bolts */
extern s32 g_shop_mode MACRO_ADDR;
extern u8 g_item_request_queue[];
extern char g_request_flag_table[];

typedef struct { char pad[0x28]; s32 lo; s32 hi; } PriceTable;
extern PriceTable g_item_l14_price_table;
extern s32 g_item_price_low NOT_SDA, g_item_price_high NOT_SDA;
#define PRICE_LT(m) (D_L14_001A7C88[7] ? (m) < D_L14_0029187C : (m) < D_L14_00291878)

typedef struct { char pad[0x80]; char obj[0x60]; V pos; } HeroRecord;
extern HeroRecord g_hero_state;

extern void part_spawn_effect_on_matching_things(s32, s32, s32, float);
extern s8 *moby_get_or_create_linked(s32);
extern void moby_set_state(s32, s32, s32);
extern void moby_reset_vars_defaults(s32);
extern int req_push_queue(void *, s32);
extern void level_apply_index_for_key(s32);
extern s32 req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern int hero_is_reachable_for_count(s32, s32, float);
extern void func_L00_0030C710(s32), text_print_localized_formatted(s32, s32, s32);
extern void moby_mark_spawned(s32), moby_set_byte_on_group(s32, s32);
extern int MemcardSave(s32, s32);
extern int math_fast_float_d(s32);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void anim_start_blended(s32, s32, s32, s32);
extern float vec_distance_xy(s32, void *), mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float FastVecLength(void *), FastAddRotations(float, float);
extern void vec_build_spherical_offset(s32, float, float, float), FastVecAdd(s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern float fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void moby_update_eased_node(s32, s32, s32, float, float);
extern void moby_copy_joint_transform_to_object(s32, s32, s32, s32);

static inline void update_joint(s32 obj, s32 joint, s32 index, float speed, float rate) {
    moby_update_eased_node(obj, joint, index, speed, rate);
}

/* Item seller (USA v2.00): a shopkeeper that sells one item for bolts, with a price check,
   a purchase prompt and idle head tracking of the hero. */
void item_seller_update_us2(s32 moby) {
    V target, raised, delta;
    s32 vars = I(moby, 0x68), price_ptr;
    float speed, yaw, pitch, ang;

    part_spawn_effect_on_matching_things(moby, 0, 0x11D3, 2.5f);
    switch (B(moby, 0x20)) {
    case 0:
        I(vars, 0x120) = 0;
        if (g_item_seller_busy || g_item_seller_flags[1] || (price_ptr = (s32)g_request_flag_table, I(price_ptr, 0x7C) < 0)) {
            moby_mark_spawned(moby);
            return;
        }
        moby_reset_vars_defaults(moby);
        if (I(price_ptr, 0x7C) & 0x40000000) {
            if (moby_get_or_create_linked(moby)) moby_set_state(moby, 2, -1);
        } else {
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            level_apply_index_for_key(moby);
            if (req_push_queue(g_item_request_queue, 0x7E)) {
                req_launch_queued(g_item_request_queue);
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 2:
        g_seller_state_words[1] = 1;
        if (g_shop_mode == 2) {
            B(moby, 0x31) = 0;
            H(moby, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            F(moby, 0xf8) = FastAddRotations(F(moby, 0xf8), 3.1415927f);
            g_seller_state_words[1] = 0;
            B(moby, 0x31) = 1;
            H(moby, 0x34) &= 0xfffe;
            if (moby_get_or_create_linked(moby)) {
                if (B(moby, 0x43) != 1) anim_start_blended(moby, 1, 0, 10);
                {
                    s32 bolts = g_player_bolts;
                    if (PRICE_LT(bolts)) moby_set_state(moby, 3, -1);
                    else moby_set_state(moby, 4, -1);
                }
            }
        }
        break;
    case 3:
        {
            s32 bolts = g_player_bolts;
            if (g_shop_flags[7] ? g_item_l14_price_table.hi <= bolts : g_item_l14_price_table.lo <= bolts) {
                moby_set_state(moby, 4, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1327, g_shop_flags[7] ? g_item_l14_price_table.hi : g_item_l14_price_table.lo, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 4:
        {
            s32 bolts = g_player_bolts;
            if (g_shop_flags[7] ? bolts < g_item_l14_price_table.hi : bolts < g_item_l14_price_table.lo) {
                func_L00_0030C710(180);
                moby_set_state(moby, 3, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1328, g_shop_flags[7] ? g_item_l14_price_table.hi : g_item_l14_price_table.lo, -1);
            level_apply_index_for_key(moby);
            if (g_pad_held_flags & 0x10) {
                {
                    s32 bolts = g_player_bolts;
                    g_player_bolts = bolts - (g_shop_flags[7] ? g_item_l14_price_table.hi : g_item_l14_price_table.lo);
                }
                if (req_push_queue(g_item_request_queue, 0x7f)) {
                    req_launch_queued(g_item_request_queue);
                    moby_set_state(moby, 5, -1);
                }
            }
        }
        break;
    case 5:
        g_seller_state_words[1] = 1;
        if (g_shop_mode == 2) {
            B(moby, 0x31) = 0;
            H(moby, 0x34) |= 1;
        }
        if (I(vars, 0x120) && g_shop_mode == 2) {
            H(I(vars, 0x120), 0x34) |= 1;
            B(I(vars, 0x120), 0x31) = 0;
        }
        if (!game_is_either_mode_two()) {
            g_seller_state_words[1] = 0;
            B(moby, 0x31) = 1;
            H(moby, 0x34) &= 0xfffe;
            if (B(moby, 0x21) != 0xff) moby_set_byte_on_group(B(moby, 0x21), 1);
            if (I(vars, 0x120)) {
                moby_mark_spawned(I(vars, 0x120));
                I(vars, 0x120) = 0;
            }
            if (!g_item_seller_flags[1]) {
                g_item_seller_flags[1] = 1;
                g_item_seller_done_flag = 1;
            }
            MemcardSave(0, -1);
            F(moby, 0xf8) = FastAddRotations(F(moby, 0xf8), 3.1415927f);
            if (B(moby, 0x43)) anim_start_blended(moby, 0, 0, 10);
            moby_set_state(moby, 6, -1);
        }
        break;
    }

    if (B(moby, 0x20) == 1 || B(moby, 0x20) == 2 || B(moby, 0x20) == 6) {
        if (!B(moby, 0x43) && math_fast_float_d(vars + 0x11C))
            I(vars, 0x11C) = FloatToInt(math_random_float_range(1200.f, 2400.f));
        else if ((B(moby, 0x60) & 2) && B(moby, 0x43))
            anim_start_blended(moby, 0, 0, 10);
    }

    speed = .02f;
    if (vec_distance_xy(moby + 0x10, g_hero_state.obj) < 8.f
        && FastDiffRots(F(moby, 0xf8), mat_fast_helper_a(g_hero_state.pos.f[0] - F(moby, 0x10),
                                                     g_hero_state.pos.f[1] - F(moby, 0x14))) < 1.5707964897155762f) {
        if (FastVecLength(g_hero_state.obj + 0x90) > .01f) I(vars, 0x114) = 120;
        else math_fast_float_d(vars + 0x114);
    } else if (I(vars, 0x114)) {
        I(vars, 0x114) = 0;
        qcopy((void *)(vars + 0x100), &g_hero_state.pos);
    }
    if (math_fast_float_d(vars + 0x118)) {
        I(vars, 0x118) = FloatToInt(math_random_float_range(180.f, 300.f));
        ang = FastAddRotations(F(moby, 0xf8), math_random_float_range(-90.f, 90.f) * 0.01745329424738884f);
        pitch = math_random_float_range(0.f, 30.f) * 0.01745329424738884f;
        vec_build_spherical_offset(vars + 0x100, 6.f, ang, pitch);
        FastVecAdd(vars + 0x100, vars + 0x100, moby + 0x10);
    }
    if (I(vars, 0x114)) {
        qcopy(&target, &g_hero_state.pos);
        speed = .04f;
    } else {
        qcopy(&target, (void *)(vars + 0x100));
    }
    qcopy(&raised, (void *)(moby + 0x10));
    raised.f[2] += 2.f;
    FastVecSub(&delta, &target, &raised);
    yaw = fast_subtract_rotations(mat_fast_helper_a(delta.f[0], delta.f[1]), F(moby, 0xf8));
    pitch = -mat_fast_helper_a(vec_length_xy(&delta), delta.f[2]);
    if (yaw > .8726647f) yaw = .8726647f;
    else if (yaw < -.8726647f) yaw = -.8726647f;
    if (pitch > .52359885f) pitch = .52359885f;
    else if (pitch < -.017453294f) pitch = -.017453294f;
    F(vars, 0x64) = pitch;
    F(vars, 0x68) = yaw * .5f;
    F(vars, 0xe8) = yaw * .3f;
    if (I(vars, 0x120)) moby_copy_joint_transform_to_object(moby, I(vars, 0x120), 2, 0);
    if (g_unlocked_item_flags) F(vars, 0x70) = 2.75f;
    update_joint(moby, vars, 0, speed, .3f);
    update_joint(moby, vars + 0x80, 1, speed, .3f);
}
