/* func_US2_L14_00427280, the USA v2.00 copy of func_L14_00425CB0: the same C. */
#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;

#define I(p, o) (*(s32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

extern u8 D_001A7AFF MACRO_ADDR, D_001A7B28[] MACRO_ADDR, D_001A7B61 MACRO_ADDR;
extern u8 D_L14_001A7C88[] MACRO_ADDR, D_001A7A40 MACRO_ADDR;
extern s32 D_L14_001B22E4[] MACRO_ADDR;

extern s32 D_00138324 NOT_SDA;
extern s32 g_player_bolts MACRO_ADDR; /* the player's bolts */
extern s32 D_L14_001A8F00 MACRO_ADDR;
extern u8 D_L14_001BF700[];
extern char D_00139768[];

typedef struct { char pad[0x28]; s32 lo; s32 hi; } PriceTable;
extern PriceTable D_L14_00291850;
extern s32 D_L14_00291878 NOT_SDA, D_L14_0029187C NOT_SDA;
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

void func_US2_L14_00427280(s32 obj) {
    V target, raised, delta;
    s32 data = I(obj, 0x68), p;
    float speed, yaw, pitch, ang;

    part_spawn_effect_on_matching_things(obj, 0, 0x11D3, 2.5f);
    switch (B(obj, 0x20)) {
    case 0:
        I(data, 0x120) = 0;
        if (D_001A7AFF || D_001A7B28[1] || (p = (s32)D_00139768, I(p, 0x7C) < 0)) {
            moby_mark_spawned(obj);
            return;
        }
        moby_reset_vars_defaults(obj);
        if (I(p, 0x7C) & 0x40000000) {
            if (moby_get_or_create_linked(obj)) moby_set_state(obj, 2, -1);
        } else {
            moby_set_state(obj, 1, -1);
        }
        break;
    case 1:
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            level_apply_index_for_key(obj);
            if (req_push_queue(D_L14_001BF700, 0x7E)) {
                req_launch_queued(D_L14_001BF700);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L14_001B22E4[1] = 1;
        if (D_L14_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            F(obj, 0xf8) = FastAddRotations(F(obj, 0xf8), 3.1415927f);
            D_L14_001B22E4[1] = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (moby_get_or_create_linked(obj)) {
                if (B(obj, 0x43) != 1) anim_start_blended(obj, 1, 0, 10);
                {
                    s32 bolts = g_player_bolts;
                    if (PRICE_LT(bolts)) moby_set_state(obj, 3, -1);
                    else moby_set_state(obj, 4, -1);
                }
            }
        }
        break;
    case 3:
        {
            s32 bolts = g_player_bolts;
            if (D_L14_001A7C88[7] ? D_L14_00291850.hi <= bolts : D_L14_00291850.lo <= bolts) {
                moby_set_state(obj, 4, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1327, D_L14_001A7C88[7] ? D_L14_00291850.hi : D_L14_00291850.lo, -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 4:
        {
            s32 bolts = g_player_bolts;
            if (D_L14_001A7C88[7] ? bolts < D_L14_00291850.hi : bolts < D_L14_00291850.lo) {
                func_L00_0030C710(180);
                moby_set_state(obj, 3, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1328, D_L14_001A7C88[7] ? D_L14_00291850.hi : D_L14_00291850.lo, -1);
            level_apply_index_for_key(obj);
            if (D_00138324 & 0x10) {
                {
                    s32 bolts = g_player_bolts;
                    g_player_bolts = bolts - (D_L14_001A7C88[7] ? D_L14_00291850.hi : D_L14_00291850.lo);
                }
                if (req_push_queue(D_L14_001BF700, 0x7f)) {
                    req_launch_queued(D_L14_001BF700);
                    moby_set_state(obj, 5, -1);
                }
            }
        }
        break;
    case 5:
        D_L14_001B22E4[1] = 1;
        if (D_L14_001A8F00 == 2) {
            B(obj, 0x31) = 0;
            H(obj, 0x34) |= 1;
        }
        if (I(data, 0x120) && D_L14_001A8F00 == 2) {
            H(I(data, 0x120), 0x34) |= 1;
            B(I(data, 0x120), 0x31) = 0;
        }
        if (!game_is_either_mode_two()) {
            D_L14_001B22E4[1] = 0;
            B(obj, 0x31) = 1;
            H(obj, 0x34) &= 0xfffe;
            if (B(obj, 0x21) != 0xff) moby_set_byte_on_group(B(obj, 0x21), 1);
            if (I(data, 0x120)) {
                moby_mark_spawned(I(data, 0x120));
                I(data, 0x120) = 0;
            }
            if (!D_001A7B28[1]) {
                D_001A7B28[1] = 1;
                D_001A7B61 = 1;
            }
            MemcardSave(0, -1);
            F(obj, 0xf8) = FastAddRotations(F(obj, 0xf8), 3.1415927f);
            if (B(obj, 0x43)) anim_start_blended(obj, 0, 0, 10);
            moby_set_state(obj, 6, -1);
        }
        break;
    }

    if (B(obj, 0x20) == 1 || B(obj, 0x20) == 2 || B(obj, 0x20) == 6) {
        if (!B(obj, 0x43) && math_fast_float_d(data + 0x11C))
            I(data, 0x11C) = FloatToInt(math_random_float_range(1200.f, 2400.f));
        else if ((B(obj, 0x60) & 2) && B(obj, 0x43))
            anim_start_blended(obj, 0, 0, 10);
    }

    speed = .02f;
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
    qcopy(&raised, (void *)(obj + 0x10));
    raised.f[2] += 2.f;
    FastVecSub(&delta, &target, &raised);
    yaw = fast_subtract_rotations(mat_fast_helper_a(delta.f[0], delta.f[1]), F(obj, 0xf8));
    pitch = -mat_fast_helper_a(vec_length_xy(&delta), delta.f[2]);
    if (yaw > .8726647f) yaw = .8726647f;
    else if (yaw < -.8726647f) yaw = -.8726647f;
    if (pitch > .52359885f) pitch = .52359885f;
    else if (pitch < -.017453294f) pitch = -.017453294f;
    F(data, 0x64) = pitch;
    F(data, 0x68) = yaw * .5f;
    F(data, 0xe8) = yaw * .3f;
    if (I(data, 0x120)) moby_copy_joint_transform_to_object(obj, I(data, 0x120), 2, 0);
    if (D_001A7A40) F(data, 0x70) = 2.75f;
    update_joint(obj, data, 0, speed, .3f);
    update_joint(obj, data + 0x80, 1, speed, .3f);
}
