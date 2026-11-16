
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float v[4]; } Vector;
struct Rac2Native_5f824a0e369ccf7b_src_record;
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    float f20;
    unsigned char f24;
    unsigned char f25;
    short f26;
    unsigned char f28;
    unsigned char f29;
    unsigned char f30;
    unsigned char f31;
    unsigned char pad32[16];
    short f48;
    short f50;
    int f52;
    int f56;
    int f60;
} PoolRecord64;
typedef struct {
    unsigned char prefix[0x80];
    Vector position;
    unsigned char pad90[0x50];
    Vector eye;
    unsigned char padF0[0x24C];
    char *interaction;
    int active;
} HeroView;
extern HeroView g_hero_state;
extern unsigned char g_moby_group_flags[];
extern int g_current_map_index MACRO_ADDR;
extern char *g_path_l01_table[];
extern char *g_moby_l01_table __attribute__((sda));
extern float g_water_l01_height[] __attribute__((sda));
extern float g_ferry_height_offsets_alt[], g_ferry_height_offsets[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_ferry_src_record_a;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_ferry_src_record_b;
extern struct Rac2Native_5f824a0e369ccf7b_src_record g_ferry_src_record_c;
extern float level_get_water_height(void);
extern int func_001163B0(void);
extern void anim_start_blended(unsigned char *, int, int, int);
extern void moby_set_state(unsigned char *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float vec_length_xy(void *);
extern float FastVecLength(void *);
extern float mat_fast_helper_a(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float fast_subtract_rotations(float, float), FastDiffRots(float, float);
extern int FloatToInt(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern float math_move_angle_toward_target(float, float, float);
extern float ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float math_approach_target_with_direction_mode(float *, float, float *, int, float, float, float);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern void vec_clamp_length(float *, float), vec_add_random_offset(float *, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void moby_scale_owner_words_by_angles(float *, float *, float *, float, float, float);
extern void value_set_and_smooth(void *, float *, float, int, int);
extern char *part_spawn_drifting(void *, float, float, void *, int);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern int slot_copy_records_to_free(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void slot_reset_active(int);
extern PoolRecord64 *cam_alloc_override_slot(int);
extern void cam_end_override(unsigned char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))

/* Real field accesses: the stores to these two fields must not order against the
 * scalar read of D_001A79F0 in state 1 (a fixed scalar cannot alias a member of a
 * structure at a varying address). */
typedef struct {
    unsigned char pad00[0x34];
    unsigned short f34;
    unsigned char pad36[0x62];
    int f98;
} ObjectView;

/* Runs a boat-like creature that carries the player along an outward path and a return path. It waits to be used, goes along the path with bubbles trailing, turns around and comes back. */
void path_ferry_update(unsigned char *object)
{
    Vector old_position, old_rotation, direction, target, velocity;
    char *context = P(object, 0x68);
    char *outbound = g_path_l01_table[I(context, 0x290)];
    char *inbound = g_path_l01_table[I(context, 0x294)];
    char *hit, *child, *other;
    float surface;
    int i, index;
    unsigned char animation;
    qcopy(&old_position, object+0x10);
    qcopy(&old_rotation, object+0xF0);
    surface = level_get_water_height();
    if (object[0x20] > 1) F(object, 0x18) = F(context, 0x2A8);
    switch (object[0x20]) {
    case 0:
        if (surface > 0.0f) {
            F(context, 0x2B4) = 1.0f / fast_vec_dist(outbound + 0x10, outbound + 0x20);
            F(context, 0x2B8) = 1.0f / fast_vec_dist(inbound + 0x10, inbound + 0x20);
            I(context, 0x2F0) = -1;
            qcopy(object+0x10, outbound+0x10);
            F(object, 0xF8) = mat_fast_helper_a(F(outbound, 0x20) - F(object, 0x10), F(outbound, 0x24) - F(object, 0x14));
            F(context, 0x2D4) = F(object, 0x18);
            I(context, 0x2AC) = 0;
            animation = object[0x43];
            if (animation != (func_001163B0() & 1)) {
                index = func_001163B0() & 1;
                anim_start_blended(object, index, 0, math_random_int_range(10, 20));
            }
            I(context, 0x8C) |= 0x10;
            if (I(context, 0x2D8) != 0) {
                object[0x31] = 0;
                ((ObjectView *)object)->f98 = 0;
                ((ObjectView *)object)->f34 |= 1;
                moby_set_state(object, 1, -1);
            } else {
                moby_set_state(object, 2, -1);
            }
        }
        break;
    case 1: {
        int i, index, ready, bank;
        object[0x31] = 0;
        ((ObjectView *)object)->f98 = 0;
        ((ObjectView *)object)->f34 |= 1;
        bank = g_current_map_index*16;
        ready = 1;
        for (i = 0; i < 5; ++i) {
            index = I(context, 0x2DC + 4*i);
            if (index != -1 && !(g_moby_group_flags[index + bank] & 0x80)) ready = 0;
        }
        if (ready) {
            object[0x31] = 1;
            ((ObjectView *)object)->f34 &= ~1;
            ((ObjectView *)object)->f98 = I(P(object, 0x24), 0x10);
            moby_set_state(object, 2, -1);
        }
        break;
    }
    case 2: {
        float rate, yaw;
        int i;
        hit = part_find_owned_effect_slot(object, 0x10000, 0);
        if (hit && (!P(hit, 0x20) || H(P(hit, 0x20), 0xAA) != 0xCE7 /* moby class 3303 */)) {
            if (g_hero_state.interaction == (char *)object && g_hero_state.active) slot_copy_records_to_free(&g_ferry_src_record_a);
            if (object[0x43] != 2) anim_start_blended(object, 2, 5, 3);
            moby_set_state(object, 3, -1);
        } else {
            rate = vec_distance_xy(object + 0x10, &g_hero_state.position);
            if (rate < 10.0f) {
                if (object[0x43]) anim_start_blended(object, 0, 0, math_random_int_range(10, 20));
                moby_transform_joint_to_world(object, 0, (char *)&direction);
                FastVecSub(&direction, &g_hero_state.eye, &direction);
                yaw = mat_fast_helper_a(direction.v[0], direction.v[1]);
                yaw = fast_subtract_rotations(yaw, F(object, 0xF8));
                rate = -mat_fast_helper_a(vec_length_xy(&direction), direction.v[2]);
                if (yaw > 2.2689283f) yaw = 2.2689283f;
                else if (yaw < -2.2689283f) yaw = -2.2689283f;
                if (rate > 0.52359885f) rate = 0.52359885f;
                else if (rate < -0.52359885f) rate = -0.52359885f;
                F(context, 0xF4) = rate;
                for (i = 0; i < 3; ++i) F(context, 0xF0 + i*0x80) = yaw * 0.33333334f;
            } else if ((object[0x60] & 2) && !math_random_int_below(1)) {
                if (object[0x42] == 0 && !math_random_int_below(2)) {
                    if (object[0x43] != 1) anim_start_blended(object, 1, 0, 10);
                } else if (object[0x42] == 1 && object[0x43] != 0) {
                    anim_start_blended(object, 0, 0, 10);
                }
                F(object, 0x48) = math_random_float_range(0.8f, 1.2f);
            }
            if (g_hero_state.interaction == (char *)object && g_hero_state.active) {
                slot_copy_records_to_free(&g_ferry_src_record_a);
                if (object[0x43] != 2) anim_start_blended(object, 2, 5, 3);
                moby_set_state(object, 3, -1);
            }
        }
        object[0xA8] = 0xFF;
        break;
    }
    case 3:
        if (object[0x60] & 2) {
            if (g_hero_state.interaction == (char *)object && g_hero_state.active) I(context, 0x2F0) = slot_copy_records_to_free(&g_ferry_src_record_b);
            if (object[0x43] != 3) anim_start_blended(object, 3, 0, 6);
            F(context, 0x2CC) = F(context, 0x2D0) = 10.0f;
            moby_set_state(object, 4, -1);
            object[0xA8] = 0xFF;
        }
        break;
    case 4: {
        float rate, lookahead;
        float *point;
        int i, index;
        i = FloatToInt(F(context, 0x2B0));
        point = (float *)outbound;
        point += i*4;
        if (point[7] > 0.0f) {
            i = FloatToInt(F(context, 0x2B0));
            point = (float *)outbound;
            point += i*4;
            F(context, 0x2CC) = point[7];
        }
        ApproachValue((float *)(context + 0x2D0), F(context, 0x2CC), 0.33333334f);
        {
            float rate = F(context, 0x2B4);
            math_step_value_toward_target((float *)(context+0x2B0), (float *)(context+0x2BC), (float)(I(outbound, 0)-1), rate*0.005f, rate*0.0016666667f, F(context, 0x2D0)*(rate*0.016666668f));
        }
        path_sample_position(outbound, 0, object+0x10, &direction, 0, F(context, 0x2B0));
        F(object, 0xF8) = math_move_angle_toward_target(F(object, 0xF8), direction.v[2], 0.5f);
        lookahead = F(context, 0x2B0)+6.0f;
        qzero_nc(&target);
        if (lookahead < (float)(I(outbound, 0)-1)) {
            float yaw;
            qcopy(&target, object+0x10);
            qcopy(&velocity, object+0xF0);
            path_sample_position(outbound, 0, &target, &velocity, 0, lookahead);
            FastVecSub(&target, &target, object+0x10);
            yaw = mat_fast_helper_a(target.v[0], target.v[1]);
            yaw = fast_subtract_rotations(yaw, F(object, 0xF8));
            F(context, 0xF0) = yaw; F(context, 0xF8) = yaw*0.5f;
            F(context, 0x174) = yaw*0.33333334f; F(context, 0x1F4) = -yaw*0.5f;
        }
        target.v[0] = math_fast_sin_or_cos_a(F(object, 0xF8))*10.0f;
        target.v[1] = math_fast_sin_or_cos_b(F(object, 0xF8))*10.0f;
        target.v[2] = 0.0f;
        FastVecAdd(&target, &target, object+0x10);
        target.v[3] = 12345.0f;
        if (!math_random_int_below(4)) {
            qcopy(&velocity, object+0x10);
            vec_add_random_offset(velocity.v, 0.05f);
            velocity.v[2] = surface;
            rate = math_random_float_range(2.0f, 3.0f);
            i = math_random_int_below(6);
            child = part_spawn_drifting(&velocity, rate, 13000.0f, g_water_l01_height, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = FloatToInt(16.0f)+32;
        }
        if ((float)(I(outbound, 0)-1) <= F(context, 0x2B0)) {
            slot_reset_active(I(context, 0x2F0));
            I(context, 0x2F0) = -1;
            if (g_hero_state.interaction == (char *)object && g_hero_state.active) slot_copy_records_to_free(&g_ferry_src_record_c);
            if (object[0x43] != 6) anim_start_blended(object, 6, 0, 10);
            U(object, 0x96) = 0;
            object[0x20] = 5;
            I(context, 0x2C0) = 20;
            F(context, 0x2B0) = 0.0f;
        }
        if ((I(context, 0x298) == -1 && target.v[3] != 12345.0f) ||
            g_hero_state.interaction != (char *)object || !g_hero_state.active) {
            if (P(context, 0x2AC)) { cam_end_override(P(context, 0x2AC)); P(context, 0x2AC) = 0; }
            break;
        }
        index = I(context, 0x298);
        if (index != -1) {
            other = g_moby_l01_table + index*0x100;
            if (vec_distance_xy(object+0x10, other+0x10) < F(context, 0x29C)) {
                qcopy(&target, other+0x10);
                target.v[3] = 12345.0f;
            }
        }
        if (target.v[3] == 12345.0f) {
            if (!P(context, 0x2AC)) {
                P(context, 0x2AC) = (char *)cam_alloc_override_slot(5);
                if (!P(context, 0x2AC)) break;
            }
            child = P(context, 0x2AC);
            FastVecSub(child+0x20, &target, &g_hero_state.position);
            ((PoolRecord64 *)child)->f31 = 1;
            ((PoolRecord64 *)child)->f52 = 3;
        }
        break;
    }
    case 5:
    case 7: {
        float rate, yaw;
        moby_transform_joint_to_world(object, 0, (char *)&target);
        if (object[0x20] == 5) {
            qcopy(&direction, inbound+0x10);
            direction.v[2] -= 1.5f;
        } else {
            qcopy(&direction, outbound+0x10);
        }
        if (object[0x20] == 5)
            yaw = mat_fast_helper_a(F(inbound, 0x20)-direction.v[0], F(inbound, 0x24)-direction.v[1]);
        else
            yaw = mat_fast_helper_a(F(outbound, 0x20)-direction.v[0], F(outbound, 0x24)-direction.v[1]);
        FastVecSub(&velocity, &direction, object+0x10);
        rate = FastVecLength(&velocity);
        math_approach_target_with_braking(context+0x2C4, rate, 0.0016666667f, 0.0016666667f, 0.10000001f);
        vec_clamp_length(velocity.v, F(context, 0x2C4));
        FastVecAdd(object+0x10, object+0x10, &velocity);
        if (object[0x20] == 5) F(object, 0x18) = F(outbound, 0x18) + g_ferry_height_offsets_alt[U(object, 0x96)];
        else F(object, 0x18) = F(outbound, 0x18) + g_ferry_height_offsets[U(object, 0x96)];
        if (U(object, 0x96) < 180) {
            U(object, 0x96)++;
            if (!math_random_int_below(8)) {
                vec_add_random_offset(target.v, 0.01f);
                target.v[2] = surface;
                rate = math_random_float_range(0.02f, 0.1f); i = math_random_int_below(6);
                part_spawn_drifting(&target, rate, 8000.0f, g_water_l01_height, ((u32)(i+20)<<24)|0x5060U);
            }
        } else {
            if (object[0x43]) anim_start_blended(object, 0, 0, 10);
            math_approach_target_with_direction_mode((float *)(object+0xF8), yaw, (float *)(context+0x2C8), 0, 0.000387851f, 0.0003393696097191423f, 0.02617994323372841f);
            if (FastDiffRots(F(object, 0xF8), yaw) < 0.001f) {
                object[0xA8] = 0xFF; object[0x20] = object[0x20] == 5 ? 6 : 2;
                F(context, 0x2B0) = 0.0f;
            }
        }
        if (surface < target.v[2] && !math_random_int_below(6)) {
            qcopy(&target, object+0x10);
            vec_add_random_offset(target.v, 0.5f); target.v[2] = surface;
            rate = math_random_float_range(2.0f, 3.0f); i = math_random_int_below(6);
            child = part_spawn_drifting(&target, rate, 13000.0f, g_water_l01_height, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = FloatToInt(16.0f)+32;
        }
        if (P(context, 0x2AC)) { cam_end_override(P(context, 0x2AC)); P(context, 0x2AC) = 0; }
        break;
    }
    case 6: {
        float rate;
        rate = F(context, 0x2B8)*0.0022222223f;
        math_step_value_toward_target((float *)(context+0x2B0), (float *)(context+0x2BC), (float)(I(inbound, 0)-1), rate, rate, F(context, 0x2B8)*0.16666667f);
        path_sample_position(inbound, 0, object+0x10, object+0xF0, 0, F(context, 0x2B0));
        F(object, 0x18) -= 1.5f;
        if ((float)(I(inbound, 0)-1) <= F(context, 0x2B0)) {
            U(object, 0x96) = 0;
            if (object[0x43] != 7) anim_start_blended(object, 7, 0, 10);
            object[0x20] = 7; F(context, 0x2B0) = 0.0f;
        }
        break;
    }
    }
    if (object[0x20] > 1) {
        float rate;
        F(context, 0x2A8) = F(object, 0x18);
        F(object, 0x18) = F(object, 0x18) - F(context, 0x2D4) + surface;
        moby_scale_owner_words_by_angles((float *)object, (float *)(context+0x2A0), (float *)(context+0x2A4), 0.03490659f, 0.05f, 0.01f);
        for (i = 0; i < 3; ++i) moby_update_eased_node(object, context+0x90+i*0x80, i, 0.02f, 0.3f);
        if (object[0x20] != 6 && object[0x20] != 0 && !math_random_int_below(49)) {
            rate = math_random_float_range(3.0f, 5.0f); i = math_random_int_below(6);
            child = part_spawn_drifting(object+0x10, rate, 13000.0f, g_water_l01_height, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = FloatToInt(16.0f)+32;
        }
        FastVecSub(&direction, object+0x10, &old_position);
        if (surface-0.2f < F(object, 0x18)) mat_combine_and_store(context+0x50, &direction, object+0xF0, object+0xF0);
    }
    value_set_and_smooth(object, (float *)(context+0x300), 2.5f, 4, 1);
}
