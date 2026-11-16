#include "include_asm.h"

#include "common.h"
typedef struct {
    float x, y, z, w;
} UpdateVec;
typedef struct {
    UpdateVec start, end, velocity;
    void *object;
    void *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} UpdateQuery;
typedef union {
    UpdateQuery query;
    struct {
        UpdateVec angles, adjusted, transform[4];
    } attachment;
} UpdateWorkspace;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    UpdateVec point, extra, normal;
} UpdateCollision;
extern char g_vehicle_gravity_direction[] MACRO_ADDR;
extern UpdateCollision g_collision_hit;
extern char g_coll_hit_normal[];
extern char g_hero_state[];
extern char *g_camera_state_ptr __attribute__((nosda));
extern int g_resident_data_base[] MACRO_ADDR;
extern int g_game_mode __attribute__((nosda));
extern int g_pad_held_flags __attribute__((nosda));
extern int g_current_game_mode __attribute__((sda));
extern float g_ridden_vehicle_rate __attribute__((sda));
extern char *g_hud_timer_b_state __attribute__((sda));
extern int g_ridden_vehicle_value __attribute__((sda));
extern float g_ridden_vehicle_probe_lift __attribute__((sda));
extern float g_ridden_vehicle_probe_radius __attribute__((sda));
extern int g_hud_timer_b[] MACRO_ADDR;
extern int update_timer SDATA(D_001B2840);
extern int g_vehicle_align_override[] MACRO_ADDR;
extern int update_collision SDATA(D_001B2844);
extern int g_vehicle_probe_skip[] MACRO_ADDR;
extern int update_water SDATA(D_001B2848);
extern int g_vehicle_part_steer_effects[] MACRO_ADDR;
extern int update_handle SDATA(D_001B2858);
extern char *g_turret_target_moby[] MACRO_ADDR;
extern float g_ring_angle_table[][2];
extern void gravity_get_dir_at_object(void *, void *, int);
extern void moby_get_facing_direction(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern void vec_scale_to_length(void *, void *, float);
extern int ForceClaimNotice(int, int, int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void level_store_value_pair_us2(int, void (*)(void *));
extern int hud_draw_timer_b(void *);
extern void cam_call_helper(void);
extern void object_set_root_data_active(void);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern unsigned int stub_empty_9_us2(int, int);
extern void part_setup_object_effect_entry(void *, void *, void *);
extern void anim_start_blended(void *, int, int, int);
extern int PlayMobySound(int, int, void *);
extern void func_US2_00330BE8(void *), moby_steer_heading_to_aim(void *), vehicle_update_speed_and_move(void *);
extern void moby_push_nearby_away(void *), snd_play_on_threshold_crossing(void);
extern int math_fast_float_d(void *);
extern int CollideSweptSphere(UpdateQuery *);
extern int weapon_get_group(int);
extern void vec_clear_128(void *);
extern float FastVecLength(void *);
extern char *part_spawn_blast_effect_moby(void *, void *, void *, float);
extern void QueueRadialMobyImpacts(void *);
extern void table_clear_entry_flag(int), slot_free(int), moby_mark_spawned(void *);
extern void copy_matrix_rotation(void *, void *), mat_get_euler_angles(void *, void *);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void euler_rotation_basis(void *, void *), func_US2_003303C0(void *);
extern void gfx_register_final_draw_callback(void (*)(void *), void *);
extern void part_draw_ring_effect_and_trail(void *);
extern void part_queue_ground_shadow(void *, float);
#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define P(p, n) (*(char **)((char *)(p) + (n)))
#define STATE(p) (*(unsigned char *)((p) + 0x20))

/* Advances launch, grounded movement, falling and teardown states of a timed actor. */
void func_US2_0032F944(char *obj)
{
    /* The query and attachment transform use the same workspace in separate phases. */
    struct {
        UpdateVec previous, ahead, behind;
        UpdateWorkspace workspace;
        UpdateVec rotation;
    } scratch;
    char *vars = P(obj, 0x68);
    int i, hit, action;
    float (*particles)[2];
    char *hero;

    if (STATE(obj) >= 2)
    gravity_get_dir_at_object(obj, g_vehicle_gravity_direction, 1);
    else
    moby_get_facing_direction(obj + 0x10, g_vehicle_gravity_direction);
    FastVecScale(g_vehicle_gravity_direction, g_vehicle_gravity_direction, -1.0f);
    FastVecScale(&scratch.ahead, obj + 0xE0, g_ridden_vehicle_probe_lift);
    FastVecAdd(&scratch.ahead, obj + 0x10, &scratch.ahead);
    FastVecScale(&scratch.behind, obj + 0xE0, -1.0f);
    FastVecAdd(&scratch.behind, obj + 0x10, &scratch.behind);
    if (CollLine(&scratch.ahead, &scratch.behind, 2, obj, 0)) {
        if (GetCollHitMaterial() == 2) {
            FastVecScale(g_vehicle_gravity_direction, g_coll_hit_normal, 0.0009765625f);
            vec_scale_to_length(g_vehicle_gravity_direction, g_vehicle_gravity_direction, -1.0f);
            g_vehicle_align_override[0] = 1;
        } else {
            update_collision = 0;
        }
        if (GetCollHitMaterial() == 6)
        update_water = 1;
        else
        update_water = 0;
    } else {
        update_collision = 0;
        g_vehicle_probe_skip[0] = 0;
    }
    ForceClaimNotice(6, 0, 1);
    switch (STATE(obj)) {
    case 0:
        STATE(obj) = 1;
        I(vars, 0x58) = 0;
        F(obj, 0x2C) = 0.00025f;
        I(obj, 0x98) = 0;
        particles = g_ring_angle_table;
        for (i = 97; i >= 0; i--) {
            (*particles)[0] = math_random_angle();
            (*particles)[1] = math_random_signed_float_range(720.0f, 2160.0f) * 0.00029088825f;
            particles++;
        }
        update_timer = 1800;
        if (g_resident_data_base[0])
            level_store_value_pair_us2(0, hud_draw_timer_b);
        /* fall through */
    case 1:
        hero = g_hero_state;
        action = I(hero, 0x2294);
        if (action == 98 || g_current_game_mode == 2 || action == 111 || action == 100 ||
            action == 99 || action == 23 || action == 24 || action == 129 || action == 39) {
            cam_call_helper();
            STATE(obj) = 7;
            object_set_root_data_active();
            I(vars, 0x60) = 0;
            break;
        }
        F(obj, 0x2C) += 0.01f;
        if (F(obj, 0x2C) > 0.023f)
            F(obj, 0x2C) = 0.023f;
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        part_steer_effect_direction(g_vehicle_part_steer_effects[0], vars, 0);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        shop_trigger_current_state_effect(vars, vars);
        vec_add_object_direction_scaled(obj + 0x10, vars, 0.0030555557f);
        if (CollLine(&scratch.previous, obj + 0x10, 0, obj, 0)) {
            UpdateCollision *collision = &g_collision_hit;
            char *other = collision->hit;
            if (other && (other == P(hero, 0x2290) || *(short *)(other + 0xAA) == 0x907))
                break;
            qcopy(obj + 0x10, &collision->point);
            ForceClaimNotice(6, 0, 1);
            stub_empty_9_us2(28, 1);
            part_setup_object_effect_entry(obj + 0x10, obj + 0xF0, obj);
            STATE(obj) = 2;
            anim_start_blended(obj, 1, 0, 10);
            I(obj, 0x48) = 0;
        }
        break;
    case 2:
        STATE(obj) = 3;
        PlayMobySound(2, 0, obj);
        if (g_game_mode != 28 || g_current_game_mode == 2) {
            cam_call_helper();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 3:
        func_US2_00330BE8(obj);
        moby_steer_heading_to_aim(obj);
        vehicle_update_speed_and_move(obj);
        moby_push_nearby_away(obj);
        snd_play_on_threshold_crossing();
        if (math_fast_float_d(g_hud_timer_b)) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (g_pad_held_flags & 32) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (g_game_mode != 28 || g_current_game_mode == 2) {
            cam_call_helper();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 4:
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        vec_add_object_direction_scaled(obj + 0x10, vars, 0.0061111115f);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        shop_trigger_current_state_effect(vars, vars);
        qcopy(&scratch.workspace.query.start, &scratch.previous);
        qcopy(&scratch.workspace.query.end, obj + 0x10);
        qcopy(&scratch.workspace.query.velocity, vars);
        scratch.workspace.query.radius = 0.2f;
        scratch.workspace.query.friction = 0.85f;
        scratch.workspace.query.bounce = 0.75f;
        scratch.workspace.query.response = 1;
        scratch.workspace.query.object = obj;
        scratch.workspace.query.ignore = 0;
        scratch.workspace.query.ignoreCount = 0;
        scratch.workspace.query.flags = 0;
        scratch.workspace.query.mask = 0;
        scratch.workspace.query.gravity = 0;
        hit = CollideSweptSphere(&scratch.workspace.query);
        qcopy(obj + 0x10, &scratch.workspace.query.end);
        qcopy(vars, &scratch.workspace.query.velocity);
        if (hit == 2) {
            if (weapon_get_group(scratch.workspace.query.surface) || scratch.workspace.query.surface == 12) {
                STATE(obj) = 9;
                I(vars, 0x60) = 10;
            } else {
                STATE(obj) = 2;
                vec_clear_128(vars);
            }
        } else if (FastVecLength(vars) > 0.4f) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        break;
    case 9:
        STATE(obj) = 5;
        object_set_root_data_active();
        /* fall through */
    case 5:
        if (math_fast_float_d(vars + 0x60)) {
            PlayMobySound(1, 0, obj);
            vec_scale_to_length(&scratch.rotation, obj + 0xC0, 1.0f);
            part_spawn_blast_effect_moby(obj, obj + 0x10, &scratch.rotation, F(obj, 0x18));
            STATE(obj) = 6;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            if (g_game_mode != 28 || g_current_game_mode == 2) {
                cam_call_helper();
                I(vars, 0x60) = 0;
            } else
                I(vars, 0x60) = g_ridden_vehicle_value;
            I(vars, 0x64) = 0;
        }
        break;
    case 6:
        QueueRadialMobyImpacts(obj);
        F(vars, 0x64) += g_ridden_vehicle_rate * 0.016666668f;
        if (math_fast_float_d(vars + 0x60) && !I(vars, 0x68))
            STATE(obj) = 8;
        break;
    case 7:
        if (math_fast_float_d(vars + 0x60))
            STATE(obj) = 8;
        break;
    case 8:
        if (g_game_mode == 28)
            stub_empty_9_us2(0, 1);
        if (*(short *)(g_camera_state_ptr + 0x86) == 27)
            cam_call_helper();
        table_clear_entry_flag(update_handle);
        slot_free(I(vars, 0x6C));
        slot_free(I(vars, 0x70));
        slot_free(I(vars, 0x74));
        g_hud_timer_b_state = 0;
        level_store_value_pair_us2(0, 0);
        moby_mark_spawned(obj);
        return;
    }
    if (STATE(obj) >= 2 && g_turret_target_moby[0]) {
        copy_matrix_rotation(scratch.workspace.attachment.transform, obj + 0xC0);
        mat_get_euler_angles(scratch.workspace.attachment.transform, &scratch.workspace.attachment.angles);
        moby_transform_point_and_rotation_by_parent(obj, g_turret_target_moby[0], obj + 0x10,
                     &scratch.workspace.attachment.angles, obj + 0x10,
                     &scratch.workspace.attachment.adjusted);
        euler_rotation_basis(obj + 0xC0, &scratch.workspace.attachment.adjusted);
    }
    if ((unsigned int)(STATE(obj) - 2) < 2)
        func_US2_003303C0(obj);
    gfx_register_final_draw_callback(part_draw_ring_effect_and_trail, obj);
    part_queue_ground_shadow(obj, g_ridden_vehicle_probe_radius);
}
