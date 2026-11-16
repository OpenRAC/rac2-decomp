#include "include_asm.h"

#include "common.h"
extern int PlayMobySound(int, int, char *);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern int FloatToInt(float);
extern float mat_fast_helper_a(float, float);
extern float math_random_angle(void);
extern void actor_init_and_check_hits(char *);
extern void actor_choose_idle_anim(char *);
extern int math_random_int_range(int, int);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void func_US2_002A7AA8(char *, int, int);
extern void part_queue_moby_for_glow(char *, int, int);
extern float FastDiffRots(float, float);
extern int *g_path_list[];
extern int FastDecTimer(char *);
extern void part_emit_spark_burst_remove(char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int actor_find_path_area_point(char *, char *);
extern int actor_steer_toward_goal(char *, char *, float, float, float, float);
extern float moby_get_anim_value(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float coll_probe_ground_height_below(char *, int, float);
extern int coll_test_point(char *, int, char *, float);
extern char *g_hit_l06_result;
extern float vec_distance_xy(char *, char *);
extern float math_random_signed_float_range(float, float);
extern int math_is_value_within_step_us2(char *, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void *g_child_slot_used[6];
extern void part_spawn_colored_burst(float *, int);
extern char *moby_spawn_child_in_slot(char *, float *, float *, int, float);
extern void lerp_vector(void *, void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern int coll_sweep_from_object(char *, void *, int, int, int, int, float, float, float);
extern void actor_aim_body_at_target(char *);

/* Updates the actor's alert mode, movement and attack animation states. */
void patrol_shooter_update_us2(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    int *sequence;
    int hit;
    float pos[4], target[4], direction[4];
    float frame, saved_w, ground;
    int i;

    actor_init_and_check_hits(obj);
    sequence = g_path_list[*(int *)(st + 0x23C)];
    switch (*(unsigned char *)(obj + 0x95)) {
    case 0:
        if (*(int *)(st + 0x228) == 1) {
            if (*(int *)(st + 0x5C8)) {
                *(int *)(st + 0x5C8) = 0;
                PlayMobySound(11, 0, obj);
            }
            actor_choose_idle_anim(obj);
            if (*(int *)(st + 0x5C0)) {
                *(int *)(st + 0x238) = *(int *)(st + 0x234);
                *(int *)(st + 0x220) = *(int *)(st + 0x224);
            }
        } else if (*(int *)(st + 0x258)) {
            actor_choose_idle_anim(obj);
        }
        break;
    case 1:
        if (*(int *)(st + 0x228) == 1 || *(int *)(st + 0x22C) == 1)
            actor_choose_idle_anim(obj);
        else if (*(short *)(st + 0x24A) == 0)
            obj[0x95] = 0;
        *(int *)(st + 0x258) = 0;
        break;
    case 2:
        if (*(int *)(st + 0x228) != 1 && *(int *)(st + 0x22C) != 1 && (obj[0x60] & 2)) {
            if (*(int *)(st + 0x23C) != -1)
                *(int *)(st + 0x478) = sequence[0] - 1;
            *(float *)(st + 0x494) = 2.0f;
            moby_set_state(obj, 14, 4);
            *(short *)(st + 0x24A) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        hit = moby_dispatch_action_by_kind(obj, st + 0x60);
        if (hit & 1) {
            func_US2_002A7AA8(obj, 0, 3);
            part_queue_moby_for_glow(obj, 0, 0);
            return;
        }
        if (hit & 2) {
            if (*(int *)(st + 0x228) == 1 || *(int *)(st + 0x22C) == 1) {
                if (FastDiffRots(*(float *)(obj + 0xF8),
                        mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                    moby_set_state(obj, 11, 2);
                    if (*(unsigned char *)(obj + 0x43) != 9)
                        anim_start_blended(obj, 9, 0, 2);
                    st[0x48] = FloatToInt(20.0f);
                    st[0x4A] = FloatToInt(8.0f);
                } else {
                    moby_set_state(obj, 9, 2);
                    if (*(unsigned char *)(obj + 0x43) != 18)
                        anim_start_blended(obj, 18, 0, 10);
                    st[0x48] = FloatToInt(20.0f);
                    st[0x4A] = FloatToInt(24.0f);
                }
            } else {
                *(short *)(st + 0x24A) = math_random_int_range(580, 600);
                moby_set_state(obj, 5, 1);
                if (*(unsigned char *)(obj + 0x43) != 18)
                    anim_start_blended(obj, 18, 0, 20);
                st[0x48] = FloatToInt(20.0f);
                st[0x4A] = FloatToInt(24.0f);
            }
        }
        break;
    case 4:
        if (*(float *)(st + 0x494) <= 0.0f) {
            *(float *)(st + 0x5A4) = math_random_angle();
            qcopy(st + 0x5B0, st + 0x460);
            *(short *)(st + 0x24C) = 270;
            moby_set_state(obj, 4, -1);
            if (*(unsigned char *)(obj + 0x43) != 6)
                anim_start_blended(obj, 6, 0, 10);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
            moby_set_state(obj, 5, 1);
        }
        break;
    }
    switch (*(unsigned char *)(obj + 0x20)) {
    case 1:
        if (FastDecTimer(st + 0x24C) && *(short *)(st + 0x492) == 0) {
            if (*(unsigned char *)(obj + 0x43) != 2)
                anim_start_blended(obj, 2, 0, 20);
            *(short *)(st + 0x24C) = math_random_int_range(900, 1200);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
        } else if ((obj[0x60] & 2) && *(short *)(st + 0x492) == 0) {
            if (*(unsigned char *)(obj + 0x43) != 1)
                anim_start_blended(obj, 1, 0, 5);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 2:
    case 3:
        break;
    case 5:
        if (obj[0x60] & 2) {
            *(float *)(st + 0x5A4) = math_random_angle();
            actor_find_path_area_point(obj, st);
            *(short *)(st + 0x24C) = 270;
            moby_set_state(obj, 4, -1);
            if (*(unsigned char *)(obj + 0x43) != 6)
                anim_start_blended(obj, 6, 0, 10);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 4:
        if (actor_steer_toward_goal(obj, st + 0x5B0, *(float *)(st + 0x5A4), 4.0f,
                              0.25f, *(float *)(st + 0x47C)) ||
            FastDecTimer(st + 0x24C)) {
            moby_set_state(obj, 5, -1);
            if (*(unsigned char *)(obj + 0x43) != 7)
                anim_start_blended(obj, 7, 0, 10);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 7:
        if (obj[0x60] & 2) {
            obj[0x20] = 9;
            if (*(unsigned char *)(obj + 0x43) != 18)
                anim_start_blended(obj, 18, 0, 20);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
            *(int *)(st + 0x5A0) = 0;
        } else if (*(int *)(st + 0x5C4)) {
            frame = moby_get_anim_value(obj);
            if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                saved_w = *(float *)(obj + 0x1C);
                pos[0] = math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * 0.16f;
                pos[1] = math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(obj + 0x10, (char *)pos, obj + 0x10);
                ground = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
                *(float *)(obj + 0x18) -= 0.1666666716337204f;
                if (*(float *)(obj + 0x18) < ground)
                    *(float *)(obj + 0x18) = ground;
                *(float *)(obj + 0x1C) = saved_w;
            }
            qcopy(pos, obj + 0x10);
            pos[2] += 0.6f;
            target[0] = math_fast_sin_or_cos_a(*(float *)(obj + 0xF8));
            target[1] = math_fast_sin_or_cos_b(*(float *)(obj + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
        } else {
            frame = moby_get_anim_value(obj);
            if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                saved_w = *(float *)(obj + 0x1C);
                pos[0] = math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * 0.16f;
                pos[1] = math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(obj + 0x10, (char *)pos, obj + 0x10);
                *(float *)(obj + 0x1C) = saved_w;
            }
            qcopy(pos, obj + 0x10);
            pos[2] += 0.6f;
            target[0] = math_fast_sin_or_cos_a(*(float *)(obj + 0xF8));
            target[1] = math_fast_sin_or_cos_b(*(float *)(obj + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
            if (coll_test_point((char *)pos, 0, obj, 0.5f)) {
                char *hit_obj = g_hit_l06_result;
                if (hit_obj && *(short *)(hit_obj + 0xAA) == 0xFDC)
                    part_emit_spark_burst_remove(hit_obj);
            }
        }
        break;
    case 6:
        if (obj[0x60] & 2) {
            moby_set_state(obj, 9, 2);
            if (*(unsigned char *)(obj + 0x43) != 18)
                anim_start_blended(obj, 18, 0, 20);
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 8:
        if (*(int *)(st + 0x23C) != -1) {
            char *waypoint = (char *)(sequence + 4) + *(int *)(st + 0x478) * 16;
            actor_steer_toward_goal(obj, waypoint,
                mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                            *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
                8.0f, 0.25f, 0.0f);
            if (vec_distance_xy(obj + 0x10, (char *)(sequence + 4) + *(int *)(st + 0x478) * 16) < 1.5f)
                ++*(int *)(st + 0x478);
            {
                int count = sequence[0];
                if (*(int *)(st + 0x478) >= count) {
                    *(int *)(st + 0x5A0) = 0;
                    *(int *)(st + 0x478) = count - 1;
                    if (FastDiffRots(*(float *)(obj + 0xF8),
                        mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                        qcopy(st + 0x460, obj + 0x10);
                        moby_set_state(obj, 10, -1);
                        if (*(unsigned char *)(obj + 0x43) != 21)
                            anim_start_blended(obj, 21, 0, 16);
                        st[0x48] = FloatToInt(20.0f);
                        st[0x4A] = FloatToInt(8.0f);
                    }
                }
            }
        } else {
            moby_set_state(obj, 9, -1);
        }
        break;
    case 9:
        if (*(unsigned short *)(obj + 0x96) < 2)
            *(float *)(st + 0x47C) = math_random_signed_float_range(10.0f, 25.0f) * 0.01745329424738884f;
        if (actor_steer_toward_goal(obj, st + 0x200,
            mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                        *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            8.0f, 16.0f, *(float *)(st + 0x47C))) {
            if (FastDiffRots(*(float *)(obj + 0xF8),
                mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                            *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                moby_set_state(obj, 10, -1);
                if (*(unsigned char *)(obj + 0x43) != 21)
                    anim_start_blended(obj, 21, 0, 16);
                st[0x48] = FloatToInt(20.0f);
                st[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 10:
        actor_steer_toward_goal(obj, obj + 0x10,
            mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                        *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            6.0f, 6.0f, 0.0f);
        if (obj[0x60] & 2) {
            if (vec_distance_xy(obj + 0x10, st + 0x200) < 3.0f) {
                moby_set_state(obj, 12, -1);
                if (*(unsigned char *)(obj + 0x43) != 13)
                    anim_start_blended(obj, 13, 10, 20);
                st[0x48] = FloatToInt(20.0f);
                st[0x4A] = FloatToInt(24.0f);
            } else {
                moby_set_state(obj, 11, -1);
                if (*(unsigned char *)(obj + 0x43) != 9)
                    anim_start_blended(obj, 9, 0, 2);
                st[0x48] = FloatToInt(20.0f);
                st[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 11:
        if (obj[0x60] & 2) {
            moby_set_state(obj, 13, -1);
            if (*(unsigned char *)(obj + 0x43) != 10)
                anim_start_blended(obj, 10, 0, math_random_int_range(10, 30));
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(8.0f);
        } else if (math_is_value_within_step_us2(obj, 2.0f)) {
            moby_transform_joint_to_world(obj, 0, pos);
            qcopy(target, st + 0x200);
            FastVecSub((char *)direction, (char *)target, (char *)pos);
            vec_scale_to_length((char *)direction, (char *)direction, 0.1666666716337204f);
            *(int *)(st + 0x498) = -1;
            for (i = 0; i < 6; i++) {
                if (!g_child_slot_used[i]) {
                    *(int *)(st + 0x498) = i;
                    break;
                }
            }
            if (*(int *)(st + 0x498) != -1) {
                part_spawn_colored_burst(pos, 10);
                moby_spawn_child_in_slot(obj, direction, pos, *(int *)(st + 0x498),
                                  (float)*(unsigned char *)(st + 0x35));
                *(int *)(st + 0x498) = -1;
            }
            st[0xD7] = 0;
        }
        break;
    case 12:
        frame = moby_get_anim_value(obj);
        if ((unsigned char)obj[0x42] == (unsigned char)obj[0x43] && frame >= 17.0f && frame <= 25.0f) {
            st[0xD7] = 0;
            moby_transform_joint_to_world(obj, 0, pos);
            qcopy(target, obj + 0x10);
            target[2] += 2.0f;
            lerp_vector(direction, pos, target, 0.5f);
            direction[3] = fast_vec_dist(direction, target) * 0.75f;
            coll_sweep_from_object(obj, direction, 1, 0, 1, 0, direction[3], *(float *)(st + 0x5AC), 1.0f);
        } else if (obj[0x60] & 2) {
            moby_set_state(obj, 13, -1);
            if (*(unsigned char *)(obj + 0x43) != 11)
                anim_start_blended(obj, 11, 0, math_random_int_range(10, 30));
            st[0x48] = FloatToInt(20.0f);
            st[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 13:
        if (obj[0x60] & 2) {
            if ((unsigned char)obj[0x95] == 4) {
                *(float *)(st + 0x494) -= 1.0f;
                moby_set_state(obj, 14, -1);
            } else {
                moby_set_state(obj, 9, -1);
                if (*(unsigned char *)(obj + 0x43) != 18)
                    anim_start_blended(obj, 18, 0, 10);
                st[0x48] = FloatToInt(20.0f);
                st[0x4A] = FloatToInt(24.0f);
            }
            if (vec_distance_xy(obj + 0x10, st + 0x200) < 16.0f) {
                if (FastDiffRots(*(float *)(obj + 0xF8),
                    mat_fast_helper_a(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                *(float *)(st + 0x204) - *(float *)(obj + 0x14))) < 0.4363323450088501f) {
                    moby_set_state(obj, 10, -1);
                    if (*(unsigned char *)(obj + 0x43) != 21)
                        anim_start_blended(obj, 21, 0, 16);
                    st[0x48] = FloatToInt(20.0f);
                    st[0x4A] = FloatToInt(8.0f);
                }
            }
        }
        break;
    case 14:
        moby_set_state(obj, 10, -1);
        if (*(unsigned char *)(obj + 0x43) != 21)
            anim_start_blended(obj, 21, 0, 16);
        st[0x48] = FloatToInt(20.0f);
        st[0x4A] = FloatToInt(8.0f);
        break;
    }
    actor_aim_body_at_target(obj);
}
