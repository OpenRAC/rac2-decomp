#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(char *, int);
extern void anim_start_blended_pal(char *, int, int, int);
extern void STUB_printf(char *);
extern float mat_fast_helper_a(float, float);
extern int follower_init_and_check_hits_pal(char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern int actor_move_toward_goal_pal(char *, float, float, float, float, int);
extern char g_str_path_gunner_debug[];
extern char *g_path_list[];
extern void DrawPath(void *, int, unsigned int, int, int, float);
extern int vec_find_point_nearest_wanted_distance(void *, void *, float);
extern int Spline_AdvanceByDistance(void *, void *, int *, float *, int, float);
extern unsigned char *effect_create_timed(void *, void *, int, unsigned int, int, int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float FastAddRotations(float, float);
extern int actor_move_local_axes_pal(char *, int, void *, void *, float, float, float, float,
                            float, float, float, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern float moby_get_anim_value(void *);
extern void *part_spawn_spinning_effect_moby_pal(void *, void *, void *, int, int, float);
extern char *part_spawn_blast_effect_moby_pal(void *, void *, void *, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void vec_random_direction(void *, float, float);
extern float math_fabs(float);
extern char *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void moby_fade_out_update_pal(void);
extern void SetDeathBits_pal(void *, int, int);
extern void moby_mark_spawned(void *);
extern void actor_tick_timers_spawn_dust_pal(void *);
extern char g_up_vector[] MACRO_ADDR;
extern char g_hero_position[];
extern char g_hero_l06_position[];
extern char g_effect_vector[] MACRO_ADDR;
extern char g_sound_state[];
extern char *g_region_table MACRO_ADDR;
extern int g_game_l06_frame_counter MACRO_ADDR;
typedef int L06Quad __attribute__((mode(TI)));
typedef struct {
    int count;
    int pad[3];
    float points[1][4];
} L06Path;
typedef struct {
    float direction[4];
    float side[4];
    float up[4];
    float inverse[16];
} L06Basis;

/* Updates a gunner that follows a path, tracks the hero and fires shots; it blows up with a burst of debris when it dies (PAL: 50 Hz timings). */
void path_gunner_update_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    unsigned int state_id;
    int hit_flags;
    if (follower_init_and_check_hits_pal(obj)) {
        moby_mark_spawned(obj);
    } else {
        switch ((unsigned char)obj[0x95]) {
        case 0:
            state_id = (unsigned char)obj[0x20];
            if (*(int *)(state + 0x258) > 0) {
                if (state_id < 3) {
                    moby_set_state(obj, 2, 1);
                } else if (state_id < 8) {
                    if (IsPointInCuboid(obj + 0x10, *(int *)(state + 0x268))) {
                        if (*(int *)(state + 0x2A0) != -1) moby_set_state(obj, 6, 1);
                        else moby_set_state(obj, 5, 1);
                    } else {
                        if (*(int *)(state + 0x2A0) != -1) moby_set_state(obj, 4, 1);
                        else moby_set_state(obj, 3, 1);
                    }
                }
            } else if (state_id >= 4) {
                if (state_id < 8) {
                    if (IsPointInCuboid(obj + 0x10, *(int *)(state + 0x268))) {
                        if (*(int *)(state + 0x2A0) != -1) moby_set_state(obj, 6, 1);
                        else moby_set_state(obj, 5, 1);
                    } else {
                        if (*(int *)(state + 0x2A0) != -1) moby_set_state(obj, 4, 1);
                        else moby_set_state(obj, 3, 1);
                    }
                }
            }
            *(int *)(state + 0x278) = 0;
            break;
        case 1:
            *(int *)(state + 0x278) = 0;
            if (*(int *)(state + 0x258) != 1) {
                if (*(int *)(state + 0x258) == 2) {
                    if ((unsigned int)((unsigned char)obj[0x20] - 3) < 5) obj[0x95] = 2;
                } else if ((unsigned int)((unsigned char)obj[0x20] - 3) < 5) {
                    if (*(int *)(state + 0x2A0) != -1) moby_set_state(obj, 4, 1);
                    else moby_set_state(obj, 3, 1);
                }
            }
            break;
        case 2:
            *(int *)(state + 0x278) = 0;
            if (*(int *)(state + 0x258) == 1) obj[0x95] = 1;
            else if (*(int *)(state + 0x258) == 0) obj[0x95] = 0;
            break;
        case 3:
            ++*(int *)(state + 0x278);
            hit_flags = moby_dispatch_action_by_kind(obj, state + 0x60);
            if (hit_flags & 1) {
                moby_set_state(obj, 8, -1);
            } else if (hit_flags & 2) {
                if (*(unsigned char *)(obj + 0x43) != 1) anim_start_blended_pal(obj, 1, 0, 10);
                *(int *)(state + 0x278) = 0;
                qzero(state + 0x230);
                obj[0x95] = 0;
            }
            break;
        }
        switch ((unsigned char)obj[0x20]) {
        case 0:
            STUB_printf(g_str_path_gunner_debug);
            break;
        case 2: {
            char *path;
            if (actor_move_toward_goal_pal(obj, 12.0f, 12.0f,
                                 mat_fast_helper_a(*(float *)(state + 0x220) - *(float *)(obj + 0x10),
                                             *(float *)(state + 0x224) - *(float *)(obj + 0x14)),
                                 0.0f, 0)) {
                path = g_path_list[*(int *)(state + 0x274)];
                ++*(int *)(state + 0x26C);
                if (*(int *)(state + 0x26C) >= *(int *)path) {
                    if (*(int *)(state + 0x2A0) == -1) {
                        *(int *)(state + 0x26C) = 0;
                        qcopy(state + 0x220, g_path_list[*(int *)(state + 0x270)] + 0x10);
                        qcopy(state + 0x210, state + 0x220);
                        moby_set_state(obj, 3, -1);
                    } else moby_set_state(obj, 4, -1);
                } else qcopy(state + 0x220, ((L06Path *)path)->points[*(int *)(state + 0x26C)]);
            }
            break;
        }
        case 3: {
            /* Its own block: these stack slots are free again for the next case. */
            {
                L06Basis basis;
                float offset[4], target[4], test[4];
                L06Basis basis2;
                int index;
                float fraction, distance, yaw;
                char *path, *up;
                int node;
                DrawPath(obj, *(int *)(state + 0x270), 0x80808080, 4, 1, 0.75f);
                path = g_path_list[*(int *)(state + 0x270)];
                node = vec_find_point_nearest_wanted_distance(state + 0x1C0, path, 0.0f);
                if (node > 0)
                    FastVecSub(basis.direction, path + ((node << 4) + 0x10), path + (node << 4));
                else
                    FastVecSub(basis.direction, path + ((node << 4) + 0x20), path + ((node << 4) + 0x10));
                up = g_up_vector;
                vec_scale_to_length(basis.direction, basis.direction, 1.0f);
                qcopy(basis.up, up);
                FastVecCross(basis.side, basis.direction, basis.up);
                matrix_from_basis_rows(basis.inverse, basis.direction);
                FastVecSub(offset, state + 0x1C0, path + ((node << 4) + 0x10));
                transform_vector(offset, offset, basis.inverse);
                qcopy(target, g_hero_position);
                target[2] += 2.0f;
                /* Retail restarts from the target before each component update. */
                qcopy(test, target);
                test[0] += offset[0];
                qcopy(test, target);
                test[1] += offset[1];
                qcopy(test, target);
                test[2] += offset[2];
                index = node;
                while (index > 0 && vec_distance_xy(state + 0x1C0, path + ((index << 4) + 0x10)) < 6.0f)
                    --index;
                distance = vec_distance_xy(state + 0x1C0, path + ((index << 4) + 0x10)) - 6.0f;
                fraction = 0.0f;
                effect_create_timed(path + ((index << 4) + 0x10), obj, 2, 0x80000080, 0x7F, 20, 255, 0.33f);
                Spline_AdvanceByDistance(path, target, &index, &fraction, 0, distance);
                effect_create_timed(target, obj, 3, 0x80008000, 0x7F, 20, 255, 1.0f);
                yaw = mat_fast_helper_a(*(float *)(state + 0x1C0) - *(float *)(obj + 0x10),
                                   *(float *)(state + 0x1C4) - *(float *)(obj + 0x14));
                if (vec_distance_xy(obj + 0x10, state + 0x1C0) > 8.0f)
                    yaw = FastAddRotations(yaw, math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_game_l06_frame_counter) * 0.02f)) * 0.7853982448577881f);
                index = vec_find_point_nearest_wanted_distance(target, path, 0.0f);
                if (actor_move_toward_goal_pal(obj, 12.0f, 6.0f, yaw, 0.0f, 1)) {
                    int desired = index;
                    if (desired < *(int *)(state + 0x26C)) ++desired;
                    else --desired;
                    if (desired < 0) desired = 0;
                    if (desired < *(int *)(state + 0x26C)) {
                        --*(int *)(state + 0x26C);
                        qcopy(state + 0x210, ((L06Path *)path)->points[*(int *)(state + 0x26C)]);
                    } else if (desired > *(int *)(state + 0x26C)) {
                        ++*(int *)(state + 0x26C);
                        qcopy(state + 0x210, ((L06Path *)path)->points[*(int *)(state + 0x26C)]);
                    } else {
                        qcopy(state + 0x210, target);
                        *(int *)(state + 0x26C) = desired;
                    }
                    if (*(int *)(state + 0x26C) > *(int *)path - 1)
                        *(int *)(state + 0x26C) = *(int *)path - 1;
                    else if (*(int *)(state + 0x26C) < 0)
                        *(int *)(state + 0x26C) = 0;
                }
                node = *(int *)(state + 0x26C);
                if (node > 0)
                    FastVecSub(basis2.direction, path + ((node << 4) + 0x10), path + (node << 4));
                else
                    FastVecSub(basis2.direction, path + ((node << 4) + 0x20), path + ((node << 4) + 0x10));
                vec_scale_to_length(basis2.direction, basis2.direction, 1.0f);
                qcopy(basis2.up, g_up_vector);
                FastVecCross(basis2.side, basis2.direction, basis2.up);
                offset[0] = 0.0f;
                offset[2] = 0.0f;
                if (offset[1] > *(float *)(state + 0x29C)) offset[1] = *(float *)(state + 0x29C);
                else if (offset[1] < -*(float *)(state + 0x29C)) offset[1] = -*(float *)(state + 0x29C);
                matrix_mul_vec3(offset, offset, basis2.direction);
                FastVecAdd(state + 0x220, state + 0x210, offset);
                effect_create_timed(state + 0x220, obj, 5, 0x80800080, 0x7F, 30, 255, 1.2f);
            }
            break;
        }
        case 4:
        case 6: {
            /* Its own block: these stack slots are free again for the next case. */
            {
                float local[4];
                L06Basis basis;
                float target[4], offset[4], velocity[4], acceleration[4], shot[4], joint[4];
                float width, height, distance, phase;
                char *record = g_region_table + (*(int *)(state + 0x2A0) << 7);
                FastVecSub(local, state + 0x190, record + 0x30);
                euler_rotation_basis(basis.direction, record + 0x70);
                matrix_from_basis_rows(basis.inverse, basis.direction);
                transform_vector(local, local, basis.inverse);
                local[0] -= 6.0f;
                width = FastVecLength(record);
                height = FastVecLength(record + 0x10);
                if (local[0] > width) local[0] = width;
                else if (local[0] < -width) local[0] = -width;
                if (local[1] > height) local[1] = height;
                else if (local[1] < -height) local[1] = -height;
                local[2] = 0.0f;
                matrix_mul_vec3(local, local, basis.direction);
                FastVecAdd(state + 0x220, record + 0x30, local);
                if (*(int *)(state + 0x258) == 0) {
                    char *path = g_path_list[*(int *)(state + 0x274)];
                    qcopy(state + 0x220, ((L06Path *)path)->points[*(int *)path - 1]);
                }
                if (vec_distance_xy(obj + 0x10, *(char **)(state + 0x1A0) + 0x10) < 13.0f) {
                    target[0] = math_fast_sin_or_cos_a(*(float *)(record + 0x78)) * 8.0f;
                    target[1] = math_fast_sin_or_cos_b(*(float *)(record + 0x78)) * 8.0f;
                    target[2] = 0.0f;
                    FastVecAdd(target, obj + 0x10, target);
                    *(L06Quad *)(state + 0x220) = *(L06Quad *)target;
                }
                if (*(int *)(state + 0x334)) qcopy(state + 0x220, obj + 0x10);
                *(float *)(state + 0x228) = *(float *)(record + 0x38) + 1.0f;
                if ((unsigned char)obj[0x20] == 6)
                    mat_fast_helper_a(*(float *)(state + 0x190) - *(float *)(obj + 0x10),
                                *(float *)(state + 0x194) - *(float *)(obj + 0x14));
                actor_move_local_axes_pal(obj, 1, basis.direction, basis.inverse,
                    mat_fast_helper_a(*(float *)(state + 0x190) - *(float *)(obj + 0x10),
                                *(float *)(state + 0x194) - *(float *)(obj + 0x14)),
                    0.0f, 5.0f, 12.0f, 10.0f, 10.0f, 10.0f, 10.0f, 0.02f, 6.0f);
                distance = vec_distance_xy(obj + 0x10, state + 0x190);
                moby_transform_joint_to_world(obj, 4, target);
                FastVecSub(offset, state + 0x190, state + 0x190);
                FastVecScale(offset, offset, 0.0f);
                FastVecAdd(offset, offset, state + 0x190);
                *(float *)(state + 0x314) = mat_fast_helper_a(vec_distance_xy(state + 0x190, target), target[2] - *(float *)(state + 0x198));
                moby_update_eased_node(obj, state + 0x2B0, 1, 0.0432f, 0.43200004f);
                if (distance < *(float *)(state + 0x338) * 20.0f) {
                    if (*(unsigned char *)(obj + 0x43) != 4) {
                        *(float *)(obj + 0x48) = 0.5f;
                        if (*(unsigned char *)(obj + 0x43) != 3) anim_start_blended_pal(obj, 3, 0, 10);
                    } else if ((unsigned char)obj[0x42] == *(unsigned char *)(obj + 0x43) && (obj[0x60] & 2)) {
                        *(float *)(obj + 0x48) = 0.5f;
                        anim_start_blended_pal(obj, 3, 0, 8);
                    }
                    moby_transform_joint_point(obj, 1, joint);
                    vec_scale_to_length(velocity, joint, 0.40000004f);
                    FastVecAdd(velocity, velocity, state + 0x230);
                    FastVecScale(acceleration, velocity, 1.0f / IntToFloat(6));
                    if ((unsigned char)obj[0x42] == 3) {
                        phase = moby_get_anim_value(obj);
                        if (phase >= 4.0f) {
                            if (phase < 4.4f) {
                                FastVecSub(shot, state + 0x190, target);
                                vec_scale_to_length(shot, shot, 0.40000004f);
                                part_spawn_spinning_effect_moby_pal(obj, shot, target, 0, 0, *(float *)(state + 0x2A8));
                                *(float *)(state + 0x2AC) += 1.0f;
                            }
                        }
                        if (*(float *)(state + 0x2AC) == 4.0f) {
                            *(float *)(state + 0x2AC) = 0.0f;
                            if (*(unsigned char *)(obj + 0x43) != 4) anim_start_blended_pal(obj, 4, 0, 8);
                            *(float *)(obj + 0x48) = 0.5f;
                        }
                    }
                } else {
                    *(float *)(obj + 0x48) = 1.0f;
                    if (*(unsigned char *)(obj + 0x43) != 0) anim_start_blended_pal(obj, 0, 0, 10);
                }
            }
            break;
        }
        case 8: {
            float local[4], direction[4], velocity[4];
            char *rec, *effect;
            int i;
            /* Retail reads sp+0x10 here without initializing it on this path. */
            FastVecSub(direction, g_hero_l06_position, local);
            vec_scale_to_length(direction, direction, 1.0f);
            part_spawn_blast_effect_moby_pal(obj, obj + 0x10, direction, 5.0f);
            PlayMobySound(3, 0, obj);
            if (*(int *)(state + 0x254) != -1) {
                rec = g_sound_state + *(int *)(state + 0x254) * 0x70;
                if (*(char **)(rec + 0x88) == obj && *(unsigned char *)(rec + 0x74))
                    snd_stop_voice(*(int *)(state + 0x254));
            }
            *(int *)(state + 0x254) = -1;
            for (i = 0; i < 6; ++i) {
                vec_random_direction(velocity, 0.16000001f, 0.24000001f);
                velocity[2] = math_fabs(velocity[2]) * 2.5f;
                FastVecAdd(velocity, velocity, g_effect_vector);
                effect = cam_moby_create_pal(obj, 1, *(short *)(obj + 0xAA), i, obj + 0x10, obj + 0xF0, velocity, 255, 30.0f, 15.0f);
                *(void (**)(void))(effect + 0x64) = moby_fade_out_update_pal;
            }
            SetDeathBits_pal(obj, 0, 3);
            moby_mark_spawned(obj);
            goto done;
        }
        default:
            break;
        }
        actor_tick_timers_spawn_dust_pal(obj);
    }
done:
    return;
}
