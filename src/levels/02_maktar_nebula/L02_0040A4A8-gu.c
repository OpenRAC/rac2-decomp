#include "names.h"
/* func_L02_0040A4A8: own unit for -frac2-gcse-unsplit-edges (hero %hi kept in $s1 across case 7).
 * The second particle loop's preheader follows loop.c move_movables: a movable is hoisted in
 * the first pass only while threshold * savings * lifetime >= the loop's insn count, with the
 * threshold starting at 61 and dropping by 3 per hoisted insn. Retail hoists all seven
 * constants in one pass in the order palette %hi/%lo, 0x44, 0x48, 0x7F, 0x70707F, 0x70, so
 * 127 is set before 0x70707F (alpha, set after the 0x48 store) and the loop has at most 46
 * insns: the particle template is passed through tmpl, a register argument, which drops the
 * argument copy gcse leaves for &particle.
 * Also needed: hero target/heading through one symbol (D_00189E20 + 0x80 and
 * ((Hero *)D_00189E20)->f[0x20]), qcopy() for the matrix row copy, the D_L02_00200080
 * palette struct (+0x5C), the tail = part + 0x20 local, separate loop counters,
 * func_L00_0042AB40 taking one argument, func_002A8C28 with its first float before the int,
 * int flags from func_002B1C20, and an explicit goal = state + 0x2C0 local.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled; u8 count; u8 kind;
    u8 reserved_1b[0x65]; u8 payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L02_Palette;
extern L02_Palette D_L02_00200080;
extern void flamethrower_robot_update_common(u8 *);
extern void moby_set_state(u8 *, u8, s32);
extern s32 math_random_int_below(s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern void moby_l01_turn_toward_target(char *, char *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern char *arena_get_camera_point(char *);
extern void robot_pick_random_walk_target(u8 *, void *);
extern void flamethrower_robot_save_state_turn(u8 *);
extern float FastDiffRots(float, float);
extern s32 moby_dispatch_action_by_kind(void *, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void moby_set_anim_type_three(void *, s32, s32);
extern void flamethrower_robot_knock_out(u8 *);
extern s32 flag_set_first_pending(u8 *);
extern s32 flag_set_second_pending(u8 *);
extern s32 arena_get_state_word(char *);
extern s32 coll_point_inside_record_volume(void *, s32);
extern s32 cam_hook_return_minus_one(char *);
extern void moby_step_at_own_position_factor(void *, float);
extern s32 moby_turn_toward_target_and_step(char *, float *, float);
extern s32 moby_step_controller(void *, void *, float);
extern s32 robot_turn_toward_target(u8 *);
extern s32 math_fast_helper_a(void *, float);
extern void moby_transform_joint_point(char *, s32, char *);
extern void moby_transform_joint_to_world(char *, s32, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void *part_spawn_gravity_fade(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 coll_sweep_from_object(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *part_spawn_burst(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 math_random_int_range(s32, s32);
extern void flamethrower_robot_update_hit_effects(u8 *);
extern void flamethrower_robot_draw_glow_trails(u8 *);
extern void gfx_add_draw_callback_third(void (*)(u8 *), void *);

/* Update the sentry's patrol, alert state and close-range flame effect. */
/* Update handler of the Megacorp Security Robot - Flamethrower (moby class 3131). */
void flamethrower_l02_robot_update(u8 *object)
{
    ActorVector target;
    ActorVector bounds[2];
    ActorVector matrix[4];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    u8 *state;
    float heading;
    float range;
    float angle;
    s32 selection;
    u8 *hp;
    float dx;
    float dy;
    u8 *goal;

    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    state = *(u8 **)(object + 0x68);
    flamethrower_robot_update_common(object);
    if (object[0x20] == 1 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    if (*(s16 *)(state + 0x2E2) == 0 && object[0x95] == 3) {
        moby_set_state(object, 4, 2);
        if (math_random_int_below(2)) {
            if (object[0x43] != 2)
                anim_start_blended(object, 2, 0, 10);
        } else if (object[0x43] != 3)
            anim_start_blended(object, 3, 0, 10);
    }
    if (*(u8 **)(state + 0x2D4)) {
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2D4) + 0x10);
        heading = mat_fast_helper_a(*(float *)(*(u8 **)(state + 0x2D4) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x2D4) + 0x14) - *(float *)(object + 0x14));
    } else {
        target.quad = *(TI128 *)(g_hero_state + 0x80);
        heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(object + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(object + 0x14));
    }
    range = vec_distance_xy(object + 0x10, &target);
    switch (object[0x95]) {
    case 2: {
        if (flag_set_second_pending(object)) {
            if (object[0x43] != 10)
                anim_start_blended(object, 10, 0, 10);
            object[0xBC] = 0;
            moby_set_controller_speed_limits(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
            robot_pick_random_walk_target(object, arena_get_camera_point(*(char **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 301) {
            selection = math_random_int_below(5);
            switch (selection) {
            case 0: if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10); break;
            case 1: if (object[0x43] != 3) anim_start_blended(object, 3, 0, 10); break;
            case 2: if (object[0x43] != 5) anim_start_blended(object, 5, 0, 10); break;
            case 3: if (object[0x43] != 6) anim_start_blended(object, 6, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = math_random_int_below(100);
        }
        if (*(s16 *)(state + 0x2E2)) {
            moby_set_state(object, 5, 3);
            if (math_random_int_below(2)) {
                if (object[0x43] != 1) anim_start_blended(object, 1, 0, 10);
            } else if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
        }
        angle = mat_fast_helper_a(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        if (FastDiffRots(*(float *)(object + 0xF8), angle) > 2.7925272f)
            flamethrower_robot_save_state_turn(object);
        goal = state + 0x2C0;
        if (!object[0xBC] && vec_distance_xy(object + 0x10, goal) < 0.5f)
            object[0xBC] = 1;
        else
            moby_l01_turn_toward_target((char *)object, (char *)goal);
        break;
    }
    case 4: {
        s32 flags = moby_dispatch_action_by_kind(object, (Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(state + 0x50));
        if ((object[0x42] == 16 && math_random_int_below(30) == 0) || (flags & 1)) {
            moby_set_anim_type_three(object, 0, -1);
            flamethrower_robot_knock_out(object);
        } else if (flags & 2)
            moby_set_state(object, 7, 3);
    }
        break;
    }
    switch (object[0x20]) {
    case 3:
        if (flag_set_first_pending(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 0);
            *(s32 *)(state + 0x13C) = -1;
        }
        if (object[0xBC] == 0 && (s32)*(u16 *)(object + 0x96) > *(s16 *)(state + 0x2E8)) {
            if (object[0x43] != 10) anim_start_blended(object, 10, 0, 10);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (coll_point_inside_record_volume(object + 0x10, arena_get_state_word(*(char **)(object + 0xB8)))) {
                moby_set_state(object, 4, 2);
                *(s32 *)(state + 0x13C) = cam_hook_return_minus_one(*(char **)(object + 0xB8));
            }
            moby_l01_turn_toward_target((char *)object, arena_get_camera_point(*(char **)(object + 0xB8)));
        }
        break;
    case 6:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 9) anim_start_blended(object, 9, 0, 10);
            moby_set_controller_speed_limits(object, 0.0044444446f, 0.13333334f, 0.003490659f, 0.4188791f);
        }
        moby_step_at_own_position_factor(object, heading);
        /* Fall through: both states leave when the movement flag is set. */
    case 5:
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(object)) {
            moby_set_controller_speed_limits(object, 0.0044444446f, 0.13333334f, 0.0005817765f, 0.052359886f);
            if (object[0x43] != 10) anim_start_blended(object, 10, 0, 15);
        }
        if (object[0x42] != 13 && vec_distance_xy(object + 0x10, &((Hero *)g_hero_state)->q[8]) < 15.0f &&
            FastDiffRots(*(float *)(object + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(object + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(object + 0x14))) < 1.5707965f) {
            if (object[0x43] != 13) anim_start_blended(object, 13, 0, 10);
            moby_set_controller_speed_limits(object, 0.0011111111f, 0.033333335f, 0.0005817765f, 0.052359886f);
        } else if (vec_distance_xy(object + 0x10, &((Hero *)g_hero_state)->q[8]) > 2.8f) {
            if (!robot_turn_toward_target(object))
                moby_turn_toward_target_and_step((char *)object, target.f, *(float *)(state + 0x2D8));
        } else {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(object + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(object + 0x14));
            moby_step_controller(object, object + 0x10, angle);
        }
        angle = mat_fast_helper_a(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        if (FastDiffRots(*(float *)(object + 0xF8), angle) > 2.7925272f)
            flamethrower_robot_save_state_turn(object);
        if (object[0x42] == 13) {
            bounds[1].quad = 0;
            bounds[1].f[0] = *(float *)(object + 0x10);
            bounds[1].f[1] = *(float *)(object + 0x14);
            bounds[1].f[2] = *(float *)(object + 0x18);
            bounds[1].f[3] = 2.0f;
            bounds[0].quad = bounds[1].quad;
            if (math_fast_helper_a(bounds, 128.0f) > 0) {
                s32 i;
                s32 j;
                ActorVector *tmpl;
                moby_transform_joint_point((char *)object, 4, (char *)matrix);
                qcopy(&bounds[1], &matrix[1]);
                moby_transform_joint_to_world((char *)object, 4, (char *)&effect);
                vec_scale_to_length(&near_point, bounds + 1, 0.85f);
                vec_scale_to_length(&far_point, bounds + 1, 1.6f);
                vec_scale_to_length(&velocity, matrix + 1, 0.25f);
                vec_scale_to_length(bounds + 1, bounds + 1, 3.0f);
                FastVecAdd(&near_point, &near_point, &effect);
                FastVecAdd(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                tmpl = &particle;
                far_point.f[2] -= 0.1f;
                i = 2;
                do {
                    float first;
                    float second;
                    float third;
                    vec_add_random_offset(effect.f, 0.1f);
                    first = math_random_float_range(0.2f, 0.4f) * 210000.0f;
                    second = math_random_float_range(1.0f, 1.5f) * 210000.0f;
                    third = math_random_signed_float_range(0.0f, 0.01f);
                    part_spawn_gravity_fade(&effect, &velocity, 9, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        coll_sweep_from_object(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                } while (--i >= 0);
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = part_spawn_burst(&near_point, tmpl, 15, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L02_00200080.ids;
                        part[3] = 0x44;
                        if (math_random_int_range(0, 1)) {
                            u8 *tail;
                            u16 alpha;
                            part[3] = 0x48;
                            alpha = 127;
                            *(u32 *)(part + 4) = 0x70707F;
                            tail = part + 0x20;
                            tail[0x11] = 0x70;
                            tail[0x12] = 0x70;
                            tail[0x13] = 0x70;
                            *(u16 *)(tail + 0x1E) = alpha;
                        }
                    }
                }
            }
        }
        break;
    }
    flamethrower_robot_update_hit_effects(object);
    gfx_add_draw_callback_third(flamethrower_robot_draw_glow_trails, object);
}
