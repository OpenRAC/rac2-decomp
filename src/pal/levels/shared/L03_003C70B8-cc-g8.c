#include "common.h"
/* func_PAL_L03_003C70B8, the PAL copy of func_L03_003C3220: the same C, where D_001A7390, D_L03_001AFEFC and the tilt timer
   are scaled to 50 Hz and the frame counts and turn_step are PAL's literals. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } StateVector;
typedef struct { u16 count, padding; u32 tick, flags; } ChallengeProgress;
extern ChallengeProgress g_subtitle_history[];
typedef struct {
    u8 padding_0[0x20];
    float movement_scale;
    s16 movement_enabled;
    u8 padding_26[0x2];
    u8 movement_mode;
    u8 padding_29[0xE7];
    float collision_radius;
    float collision_height;
    float movement_limit;
    float movement_acceleration;
    float turn_scale;
    u8 padding_124[0x18];
    float turn_step;
    float turn_limit;
    float movement_speed;
    u8 padding_148[0x10];
    u8 * movement_data;
    u8 * path_data;
    u8 padding_160[0x40];
    float floor_height;
    u8 padding_1A4[0x44];
    int path_index;
    u8 padding_1EC[0x14];
    int groups[8];
    u32 area_id;
    u8 padding_224[0x130];
    u8 * child;
    u8 * target;
    u8 padding_35C[0x8];
    int command_cooldown;
    u8 padding_368[0x1C];
    int tilt_timer;
    float tilt_pitch;
    float tilt_yaw;
    u8 padding_390[0x14];
    float initial_height;
} TargetState;

typedef struct {
    u8 padding_0[0x10];
    float position[4];
    u8 state, group;
    u8 padding_22[2];
    u8 *data;
    u8 padding_28[4];
    float scale;
    u8 padding_30;
    u8 active;
    u16 field_32, flags;
    u8 padding_36[0xD];
    u8 animation;
    u8 padding_44[0x24];
    TargetState *vars;
    u8 padding_6C[3];
    u8 event;
    u8 padding_70[0xC];
    u16 field_7C;
    u8 flags_7E;
    u8 padding_7F[0x16];
    u8 mode;
    u8 padding_96[0x12];
    u8 flags_A8;
    u8 padding_A9;
    s16 type;
    u8 padding_AC[0x14];
    StateVector forward;
} TargetMoby;
extern u32 D_001A7390;
extern int g_current_map_index;
typedef struct {
    u8 padding_0[0x80];
    float position[4];
    u8 padding_90[0x2454];
    int command;
} TargetHero;
extern TargetHero g_hero_state;
/* Level statistics block. L03 reads and writes ints at +0, +4 and +8 from other functions, then
   these five halfwords. Every counter sits at a nonzero offset, so its macro access stays two words. */
typedef struct {
    int words[3];
    u16 near_player, active, near_940, near_93C, near_A59;
} TargetCounters;
extern TargetCounters D_L03_001B2750 __attribute__((sda));
extern float D_L03_001AFEE0 __attribute__((sda));
extern float D_L03_001AFEE4 __attribute__((sda));
extern int D_L03_001AFEF8 __attribute__((sda));
extern int D_L03_001AFEFC __attribute__((sda));
extern u16 D_L03_001AFF00 __attribute__((sda));
extern float D_L03_001B9980[];
extern int D_L03_001B2A38[] __attribute__((sda));
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u16 *D_L03_001FB5A0[];
extern int g_frame_l03_counter;
extern void moby_compute_point_ahead(void *, void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float coll_probe_ground_height_below(u8 *, int, float);
extern u8 *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_state(u8 *, s32, s32);
extern void anim_start_blended(u8 *, int, int, int);
extern void route_set_node_enabled_flag(u32, u8 *, s32);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_add_id_to_frame_list(int);
extern void *part_find_owned_effect_slot(void *, u32, int);
extern int subtract_integer_with_clamp(int);
extern u8 *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, unsigned char);
extern float *ChooseVisibleGroupTarget(u8 *, float *, float *);
extern void moby_fuse_linked_objects(void *, void *, void *, int, int);
extern u8 *moby_find_entity_nearby(u8 *);
extern u8 *moby_find_nearest_entity_b(u8 *);
extern u8 *moby_find_nearest_pickup_target(u8 *);
extern u8 *moby_find_nearest_tilt_target(u8 *);
extern u8 *moby_find_nearest_entity_a(u8 *);
extern int subtitle_request_voice_line(int, int);
extern void moby_compute_point_ahead_unit(void *, void *);
extern int route_check_points(u32, void *, void *);
extern void moby_compute_opposite_points(void *, void *, void *);
extern void mat_compute_side_step_offset(void *, void *, void *);
extern void moby_compute_point_ahead_scaled(void *, void *);
extern void moby_set_flag_bit(void *, int);
extern int group_is_state_word_matching(void *);
extern void moby_place_held_object(void *);
#define ANIM_COUNT(p, offset) (*(u8 *)(*(u8 **)(*(u8 **)((p) + 0x24) + (offset)) + 0x10))


void func_PAL_L03_003C70B8(u8 *object)
{
    StateVector point, first, second;
    TargetMoby *mob = (TargetMoby *)object;
    TargetState *vars = mob->vars;
    u8 *state = (u8 *)vars;
    u8 *target;
    int type, i;
    float distance;
    int permitted;
    if (mob->state == 0) {
        if (math_random_int_below(2)) mob->flags |= 0x8000;
        else mob->flags &= 0x7FFF;
        mob->flags_7E |= 1;
        mob->position[2] = coll_probe_ground_height_below((u8 *)mob->position, 0, 0.5f);
        vars->initial_height = mob->position[2];
        type = mob->type;
        if (type == 0x964) {
            vars->child = CreateMoby(0x972);
            if (vars->child) {
                moby_init_child_from_parent(vars->child, object);
                *(u16 *)(vars->child + 0x32) = 0x30;
            }
        } else {
            vars->child = CreateMoby(0xD75);
            if (vars->child) {
                moby_init_child_from_parent(vars->child, object);
                *(u16 *)(vars->child + 0x7C) = D_L03_001AFF00;
                *(u16 *)(vars->child + 0x32) = 0x30;
                if (mob->type == 0x93C) {
                    *(float *)(vars->child + 0x2C) = *(float *)(*(u8 **)(vars->child + 0x24) + 0x24) * 1.2f;
                }
            }
        }
        vars->movement_mode = 3;
        vars->movement_scale = 1.0f;
        vars->movement_enabled = 1;
        vars->movement_speed = D_L03_001AFEE0;
        vars->collision_height = 0.3f;
        switch (mob->type) {
        case 0x93C:
            vars->collision_radius = 0.42f;
            mob->position[2] += 0.089f;
            break;
        case 0x940:
            vars->collision_radius = 0.39f;
            mob->position[2] += 0.089f;
            vec_scale_to_length(&point, &mob->forward, -0.2f);
            FastVecAdd(mob->position, &point, mob->position);
            break;
        case 0xA59:
            vars->collision_radius = 0.42f;
            mob->position[2] += 0.089f;
            break;
        default:
            vars->collision_radius = 0.15f;
            mob->position[2] += 0.089f;
            break;
        }
        vars->movement_limit = 0.5f;
        vars->movement_acceleration = 0.5f;
        vars->turn_scale = 1.5882498f;
        vars->turn_limit = 0.523598849773407f;
        vars->movement_data = state + 0x240;
        vars->path_data = state + 0x2C0;
        vars->turn_step = 0.008f;
        moby_set_state(object, 1, 0);
        if (mob->animation)
            anim_start_blended(object, 0, math_random_int_below(ANIM_COUNT(object, 0x48)), 0);
        if (mob->type == 0x940) {
            for (i = 0; i < 8; i++) {
                u16 *ids;
                if (vars->groups[i] == -1) continue;
                for (ids = D_L03_001FB5A0[vars->groups[i]];
                     (vars->groups[i] & 255) != 255 && vars->groups[i] <= D_L03_001B2A38[0] && ids != 0 &&
                     ((s16)ids[-1] >= 0 || ids == D_L03_001FB5A0[vars->groups[i]]);
                     ids++) {
                    u8 *member = D_L03_001B2A1C[0] + ((*ids & 0x7FFF) << 8);
                    if (member == 0) break;
                    if (*(s16 *)(member + 0xAA) == 0x97A)
                        route_set_node_enabled_flag(vars->area_id, member + 0x10, 0);
                }
            }
        } else if (mob->type == 0xA59 && mob->animation != 6) {
            anim_start_blended(object, 6, 0, 0);
        }
    }
    if (mob->active && fast_vec_dist(mob->position, D_L03_001B9980) < 24.0f) {
        moby_update_ground_check(object);
        mob->event = 0x16;
    }
    if (mob->state > 1 && mob->mode != 4) moby_add_id_to_frame_list((int)object);
    if (part_find_owned_effect_slot(object, 1, 0) ||
        (mob->position[2] < vars->initial_height - 10.0f &&
         mob->position[2] - 10.0f < vars->floor_height)) {
        if (subtract_integer_with_clamp(D_L03_001AFEF8 - g_frame_l03_counter) > ((s32)(D_L03_001AFEFC) * 5 + 2) / 6) {
            point.q = 0;
            point.f[2] = 0.5f;
            D_L03_001AFEF8 = g_frame_l03_counter;
            FastVecAdd(&point, &point, mob->position);
            SpawnExplosion(mob->position,0,5,5,5,10,20,0,0.25f,20.0f,1,0,0,0);
            if (mob->type == 0x964)
                part_spawn_masked_debris((char *)object, 15, (float *)(state + 0x1B0), 3.0f, 6.0f, 3.0f, 6.0f, 255);
            moby_set_state(object, 4, 1);
            qzero(state + 0x1B0);
            vars->path_index = -1;
            ChooseVisibleGroupTarget(object, first.f, second.f);
            moby_fuse_linked_objects(object, &first, &second, 0, 0);
        }
        mob->flags_A8 = 255;
    }
    if (mob->mode == 4) D_L03_001B2750.active++;
    if (g_subtitle_history[39].count < 65535 && mob->type == 0x940 && mob->state != 1 && moby_find_entity_nearby(object)) {
        if (g_subtitle_history[39].count != 0) {
            if (((s32)D_001A7390 * 5 + 2) / 6 - g_subtitle_history[39].tick > 900 || g_subtitle_history[39].tick == 0)
                subtitle_request_voice_line(0x9D0, 0x27);
            else if (g_subtitle_history[39].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[39].tick = ((s32)D_001A7390 * 5 + 2) / 6;
        } else {
            g_subtitle_history[39].count++;
            if (g_subtitle_history[39].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[39].tick = ((s32)D_001A7390 * 5 + 2) / 6;
            g_subtitle_history[39].flags = (g_subtitle_history[39].flags | (1U << g_current_map_index)) | 0x80000000U;
        }
    }
    if (g_subtitle_history[128].count < 65535 && mob->type == 0x93C && mob->state != 1 && moby_find_nearest_entity_b(object)) {
        if (g_subtitle_history[128].count != 0) {
            if (((s32)D_001A7390 * 5 + 2) / 6 - g_subtitle_history[128].tick > 900 || g_subtitle_history[128].tick == 0)
                subtitle_request_voice_line(0xA29, 0x80);
            else if (g_subtitle_history[128].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[128].tick = ((s32)D_001A7390 * 5 + 2) / 6;
        } else {
            g_subtitle_history[128].count++;
            if (g_subtitle_history[128].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[128].tick = ((s32)D_001A7390 * 5 + 2) / 6;
            g_subtitle_history[128].flags = (g_subtitle_history[128].flags | (1U << g_current_map_index)) | 0x80000000U;
        }
    }
    if (g_subtitle_history[97].count < 65535 && mob->type == 0xA59 && mob->state != 1 && moby_find_nearest_pickup_target(object)) {
        if (g_subtitle_history[97].count != 0) {
            if (((s32)D_001A7390 * 5 + 2) / 6 - g_subtitle_history[97].tick > 900 || g_subtitle_history[97].tick == 0)
                subtitle_request_voice_line(0xA0A, 0x61);
            else if (g_subtitle_history[97].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[97].tick = ((s32)D_001A7390 * 5 + 2) / 6;
        } else {
            g_subtitle_history[97].count++;
            if (g_subtitle_history[97].tick < ((s32)D_001A7390 * 5 + 2) / 6) g_subtitle_history[97].tick = ((s32)D_001A7390 * 5 + 2) / 6;
            g_subtitle_history[97].flags = (g_subtitle_history[97].flags | (1U << g_current_map_index)) | 0x80000000U;
        }
    }
    if (mob->state != 1 && vec_distance_xy(mob->position, g_hero_state.position) < 16.0f) {
        D_L03_001B2750.near_player++;
        switch (mob->type) {
        case 0x940: D_L03_001B2750.near_940++; break;
        case 0x93C: D_L03_001B2750.near_93C++; break;
        case 0xA59: D_L03_001B2750.near_A59++; break;
        }
    }
    permitted = 1;
    if (g_hero_state.command == 0 || mob->state == 1 || mob->state == 13 || mob->mode == 7)
        permitted = 0;
    else if (vars->command_cooldown) permitted = 0;
    else if (mob->mode == 4 && g_hero_state.command != 6) permitted = 0;
    else if (mob->mode == 5 && g_hero_state.command != 5) permitted = 0;
    if (!permitted) return;
    switch (g_hero_state.command) {
    case 1:
        if (mob->mode == 1) return;
        distance = vec_distance_xy(mob->position, g_hero_state.position);
        if (distance > D_L03_001AFEE4) {
            moby_set_state(object, 3, 1);
            if (mob->animation == 2) return;
            anim_start_blended(object, 2, math_random_int_below(ANIM_COUNT(object, 0x50)), 8);
        } else {
            moby_set_state(object, 4, 1);
            if (mob->animation == 0) return;
            anim_start_blended(object, 0, math_random_int_below(ANIM_COUNT(object, 0x48)), 8);
        }
        break;
    case 3:
        if (mob->mode == 2 || mob->type != 0x964) return;
        vars->target = moby_find_nearest_tilt_target(object);
        if (vars->target) {
            moby_set_state(object, 9, 2);
            if (mob->animation != 3)
                anim_start_blended(object, 3, math_random_int_below(ANIM_COUNT(object, 0x54)), 8);
        } else {
            moby_set_state(object, 11, 2);
            if (mob->animation != 0)
                anim_start_blended(object, 0, math_random_int_below(ANIM_COUNT(object, 0x48)), 8);
        }
        break;
    case 2:
        if (mob->mode != 0) {
            moby_set_state(object, 2, 0);
            if (mob->animation) anim_start_blended(object, 0, math_random_int_below(ANIM_COUNT(object, 0x48)), 8);
            vars->tilt_timer = ((s32)(math_random_int_range(60, 120)) * 5 + 2) / 6;
            vars->tilt_pitch = 0;
            vars->tilt_yaw = 0;
        }
        break;
    case 4:
        if (mob->type != 0x964) return;
        vars->command_cooldown = 25;
        if (mob->mode != 3) {
            vars->target = moby_find_nearest_entity_a(object);
            if (!vars->target) return;
            moby_compute_point_ahead_unit(vars->target, &point);
            if (route_check_points(vars->area_id, mob->position, &point)) {
                qcopy(state + 0x340, &point);
                moby_set_state(object, 12, 3);
                if (mob->animation != 2) anim_start_blended(object, 2, 0, 8);
            } else vars->target = 0;
        } else if (mob->state != 13) {
            moby_set_state(object, 4, 1);
            if (mob->animation != 0) anim_start_blended(object, 0, 0, 8);
        }
        break;
    case 6:
        if (mob->type != 0x940) return;
        vars->command_cooldown = 25;
        if (mob->mode != 4) {
            vars->target = moby_find_entity_nearby(object);
            if (!vars->target) return;
            moby_set_state(object, 14, 4);
            if (mob->animation != 2) anim_start_blended(object, 2, 0, 8);
            moby_compute_opposite_points(vars->target, &point, &first);
            if (route_check_points(vars->area_id, mob->position, &point))
                qcopy(state + 0x340, &point);
            else qcopy(state + 0x340, &first);
        } else if (mob->state == 14) {
            moby_set_state(object, 4, 1);
            if (mob->animation) anim_start_blended(object, 0, 0, 17);
        } else if (mob->state == 16 && !group_is_state_word_matching(object)) moby_place_held_object(object);
        break;
    case 5:
        if (mob->type != 0x93C) return;
        if (mob->mode != 5) {
            vars->target = moby_find_nearest_entity_b(object);
            if (!vars->target) return;
            moby_set_state(object, 18, 5);
            if (mob->animation != 2) anim_start_blended(object, 2, 0, 8);
            vars->command_cooldown = 25;
            mat_compute_side_step_offset(vars->target, mob->position, state + 0x340);
            return;
        }
        if (mob->state != 19) {
            moby_set_flag_bit(vars->target, 0);
            vars->target = 0; vars->command_cooldown = 25;
            moby_set_state(object, 4, 1);
            if (mob->animation) anim_start_blended(object, 0, 0, 17);
        }
        break;
    case 7:
        if (mob->type != 0xA59) return;
        if (mob->mode != 6) {
            vars->target = moby_find_nearest_pickup_target(object);
            if (!vars->target) return;
            moby_set_state(object, 20, 6);
            if (mob->animation != 2) anim_start_blended(object, 2, 0, 8);
            target = vars->target; vars->command_cooldown = 25;
            switch (*(s16 *)(target + 0xAA)) {
            case 0xB10: moby_compute_point_ahead(target, state + 0x340); break;
            case 0xF4D: moby_compute_point_ahead_scaled(target, state + 0x340); break;
            }
        } else if (mob->state != 21) {
            moby_set_flag_bit(vars->target, 0);
            vars->target = 0; vars->command_cooldown = 25;
            moby_set_state(object, 4, 1);
            if (mob->animation) anim_start_blended(object, 0, 0, 17);
        }
        break;
    case 8:
        if (mob->type == 0x964) {
            if (mob->mode != 1) moby_set_state(object, 4, 1);
        } else moby_set_state(object, 6, 1);
        break;
    }
}
