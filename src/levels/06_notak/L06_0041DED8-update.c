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
extern void SetDeathBits(char *, int, int);
extern void func_L06_004294A0(char *, int, int);
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
extern char *D_L06_001BFC98;
extern float vec_distance_xy(char *, char *);
extern float math_random_signed_float_range(float, float);
extern int math_is_value_within_step(char *, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void *D_L06_001B3760[6];
extern void part_spawn_colored_burst(float *, int);
extern void moby_spawn_child_in_slot(char *, float *, float *, int, float);
extern void lerp_vector(void *, void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern void coll_sweep_from_object(char *, void *, int, int, int, int, float, float, float);
extern void actor_aim_body_at_target(char *);

/* Updates the actor's alert mode, movement and attack animation states. */
void patrol_shooter_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int *pathData;
    int hitFlags;
    float pos[4], target[4], direction[4];
    float frame, savedW, groundHeight;
    int i;

    actor_init_and_check_hits(moby);
    pathData = g_path_list[*(int *)(vars + 0x23C)];
    switch (*(unsigned char *)(moby + 0x95)) {
    case 0:
        if (*(int *)(vars + 0x228) == 1) {
            if (*(int *)(vars + 0x5C8)) {
                *(int *)(vars + 0x5C8) = 0;
                PlayMobySound(11, 0, moby);
            }
            actor_choose_idle_anim(moby);
            if (*(int *)(vars + 0x5C0)) {
                *(int *)(vars + 0x238) = *(int *)(vars + 0x234);
                *(int *)(vars + 0x220) = *(int *)(vars + 0x224);
            }
        } else if (*(int *)(vars + 0x258)) {
            actor_choose_idle_anim(moby);
        }
        break;
    case 1:
        if (*(int *)(vars + 0x228) == 1 || *(int *)(vars + 0x22C) == 1)
            actor_choose_idle_anim(moby);
        else if (*(short *)(vars + 0x24A) == 0)
            moby[0x95] = 0;
        *(int *)(vars + 0x258) = 0;
        break;
    case 2:
        if (*(int *)(vars + 0x228) != 1 && *(int *)(vars + 0x22C) != 1 && (moby[0x60] & 2)) {
            if (*(int *)(vars + 0x23C) != -1)
                *(int *)(vars + 0x478) = pathData[0] - 1;
            *(float *)(vars + 0x494) = 2.0f;
            moby_set_state(moby, 14, 4);
            *(short *)(vars + 0x24A) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        hitFlags = moby_dispatch_action_by_kind(moby, vars + 0x60);
        if (hitFlags & 1) {
            SetDeathBits(moby, 0, 3);
            func_L06_004294A0(moby, 0, 0);
            return;
        }
        if (hitFlags & 2) {
            if (*(int *)(vars + 0x228) == 1 || *(int *)(vars + 0x22C) == 1) {
                if (FastDiffRots(*(float *)(moby + 0xF8),
                        mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                    moby_set_state(moby, 11, 2);
                    if (*(unsigned char *)(moby + 0x43) != 9)
                        anim_start_blended(moby, 9, 0, 2);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(8.0f);
                } else {
                    moby_set_state(moby, 9, 2);
                    if (*(unsigned char *)(moby + 0x43) != 18)
                        anim_start_blended(moby, 18, 0, 10);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(24.0f);
                }
            } else {
                *(short *)(vars + 0x24A) = math_random_int_range(580, 600);
                moby_set_state(moby, 5, 1);
                if (*(unsigned char *)(moby + 0x43) != 18)
                    anim_start_blended(moby, 18, 0, 20);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            }
        }
        break;
    case 4:
        if (*(float *)(vars + 0x494) <= 0.0f) {
            *(float *)(vars + 0x5A4) = math_random_angle();
            qcopy(vars + 0x5B0, vars + 0x460);
            *(short *)(vars + 0x24C) = 270;
            moby_set_state(moby, 4, -1);
            if (*(unsigned char *)(moby + 0x43) != 6)
                anim_start_blended(moby, 6, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
            moby_set_state(moby, 5, 1);
        }
        break;
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 1:
        if (FastDecTimer(vars + 0x24C) && *(short *)(vars + 0x492) == 0) {
            if (*(unsigned char *)(moby + 0x43) != 2)
                anim_start_blended(moby, 2, 0, 20);
            *(short *)(vars + 0x24C) = math_random_int_range(900, 1200);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        } else if ((moby[0x60] & 2) && *(short *)(vars + 0x492) == 0) {
            if (*(unsigned char *)(moby + 0x43) != 1)
                anim_start_blended(moby, 1, 0, 5);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 2:
    case 3:
        break;
    case 5:
        if (moby[0x60] & 2) {
            *(float *)(vars + 0x5A4) = math_random_angle();
            actor_find_path_area_point(moby, vars);
            *(short *)(vars + 0x24C) = 270;
            moby_set_state(moby, 4, -1);
            if (*(unsigned char *)(moby + 0x43) != 6)
                anim_start_blended(moby, 6, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 4:
        if (actor_steer_toward_goal(moby, vars + 0x5B0, *(float *)(vars + 0x5A4), 4.0f,
                              0.25f, *(float *)(vars + 0x47C)) ||
            FastDecTimer(vars + 0x24C)) {
            moby_set_state(moby, 5, -1);
            if (*(unsigned char *)(moby + 0x43) != 7)
                anim_start_blended(moby, 7, 0, 10);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        }
        break;
    case 7:
        if (moby[0x60] & 2) {
            moby[0x20] = 9;
            if (*(unsigned char *)(moby + 0x43) != 18)
                anim_start_blended(moby, 18, 0, 20);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
            *(int *)(vars + 0x5A0) = 0;
        } else if (*(int *)(vars + 0x5C4)) {
            frame = moby_get_anim_value(moby);
            if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                savedW = *(float *)(moby + 0x1C);
                pos[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 0.16f;
                pos[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(moby + 0x10, (char *)pos, moby + 0x10);
                groundHeight = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
                *(float *)(moby + 0x18) -= 0.1666666716337204f;
                if (*(float *)(moby + 0x18) < groundHeight)
                    *(float *)(moby + 0x18) = groundHeight;
                *(float *)(moby + 0x1C) = savedW;
            }
            qcopy(pos, moby + 0x10);
            pos[2] += 0.6f;
            target[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8));
            target[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
        } else {
            frame = moby_get_anim_value(moby);
            if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] &&
                frame >= 4.0f && frame <= 22.0f) {
                savedW = *(float *)(moby + 0x1C);
                pos[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 0.16f;
                pos[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 0.16f;
                pos[2] = 0.0f;
                FastVecAdd(moby + 0x10, (char *)pos, moby + 0x10);
                *(float *)(moby + 0x1C) = savedW;
            }
            qcopy(pos, moby + 0x10);
            pos[2] += 0.6f;
            target[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8));
            target[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8));
            target[2] = 0.0f;
            FastVecAdd((char *)pos, (char *)target, (char *)pos);
            if (coll_test_point((char *)pos, 0, moby, 0.5f)) {
                char *hitMoby = D_L06_001BFC98;
                if (hitMoby && *(short *)(hitMoby + 0xAA) == 0xFDC /* moby class 4060 */)
                    part_emit_spark_burst_remove(hitMoby);
            }
        }
        break;
    case 6:
        if (moby[0x60] & 2) {
            moby_set_state(moby, 9, 2);
            if (*(unsigned char *)(moby + 0x43) != 18)
                anim_start_blended(moby, 18, 0, 20);
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 8:
        if (*(int *)(vars + 0x23C) != -1) {
            char *waypoint = (char *)(pathData + 4) + *(int *)(vars + 0x478) * 16;
            actor_steer_toward_goal(moby, waypoint,
                mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                            *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
                8.0f, 0.25f, 0.0f);
            if (vec_distance_xy(moby + 0x10, (char *)(pathData + 4) + *(int *)(vars + 0x478) * 16) < 1.5f)
                ++*(int *)(vars + 0x478);
            {
                int count = pathData[0];
                if (*(int *)(vars + 0x478) >= count) {
                    *(int *)(vars + 0x5A0) = 0;
                    *(int *)(vars + 0x478) = count - 1;
                    if (FastDiffRots(*(float *)(moby + 0xF8),
                        mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                        qcopy(vars + 0x460, moby + 0x10);
                        moby_set_state(moby, 10, -1);
                        if (*(unsigned char *)(moby + 0x43) != 21)
                            anim_start_blended(moby, 21, 0, 16);
                        vars[0x48] = FloatToInt(20.0f);
                        vars[0x4A] = FloatToInt(8.0f);
                    }
                }
            }
        } else {
            moby_set_state(moby, 9, -1);
        }
        break;
    case 9:
        if (*(unsigned short *)(moby + 0x96) < 2)
            *(float *)(vars + 0x47C) = math_random_signed_float_range(10.0f, 25.0f) * 0.01745329424738884f;
        if (actor_steer_toward_goal(moby, vars + 0x200,
            mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                        *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            8.0f, 16.0f, *(float *)(vars + 0x47C))) {
            if (FastDiffRots(*(float *)(moby + 0xF8),
                mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                            *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                moby_set_state(moby, 10, -1);
                if (*(unsigned char *)(moby + 0x43) != 21)
                    anim_start_blended(moby, 21, 0, 16);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 10:
        actor_steer_toward_goal(moby, moby + 0x10,
            mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                        *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            6.0f, 6.0f, 0.0f);
        if (moby[0x60] & 2) {
            if (vec_distance_xy(moby + 0x10, vars + 0x200) < 3.0f) {
                moby_set_state(moby, 12, -1);
                if (*(unsigned char *)(moby + 0x43) != 13)
                    anim_start_blended(moby, 13, 10, 20);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            } else {
                moby_set_state(moby, 11, -1);
                if (*(unsigned char *)(moby + 0x43) != 9)
                    anim_start_blended(moby, 9, 0, 2);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(8.0f);
            }
        }
        break;
    case 11:
        if (moby[0x60] & 2) {
            moby_set_state(moby, 13, -1);
            if (*(unsigned char *)(moby + 0x43) != 10)
                anim_start_blended(moby, 10, 0, math_random_int_range(10, 30));
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(8.0f);
        } else if (math_is_value_within_step(moby, 2.0f)) {
            moby_transform_joint_to_world(moby, 0, pos);
            qcopy(target, vars + 0x200);
            FastVecSub((char *)direction, (char *)target, (char *)pos);
            vec_scale_to_length((char *)direction, (char *)direction, 0.1666666716337204f);
            *(int *)(vars + 0x498) = -1;
            for (i = 0; i < 6; i++) {
                if (!D_L06_001B3760[i]) {
                    *(int *)(vars + 0x498) = i;
                    break;
                }
            }
            if (*(int *)(vars + 0x498) != -1) {
                part_spawn_colored_burst(pos, 10);
                moby_spawn_child_in_slot(moby, direction, pos, *(int *)(vars + 0x498),
                                  (float)*(unsigned char *)(vars + 0x35));
                *(int *)(vars + 0x498) = -1;
            }
            vars[0xD7] = 0;
        }
        break;
    case 12:
        frame = moby_get_anim_value(moby);
        if ((unsigned char)moby[0x42] == (unsigned char)moby[0x43] && frame >= 17.0f && frame <= 25.0f) {
            vars[0xD7] = 0;
            moby_transform_joint_to_world(moby, 0, pos);
            qcopy(target, moby + 0x10);
            target[2] += 2.0f;
            lerp_vector(direction, pos, target, 0.5f);
            direction[3] = fast_vec_dist(direction, target) * 0.75f;
            coll_sweep_from_object(moby, direction, 1, 0, 1, 0, direction[3], *(float *)(vars + 0x5AC), 1.0f);
        } else if (moby[0x60] & 2) {
            moby_set_state(moby, 13, -1);
            if (*(unsigned char *)(moby + 0x43) != 11)
                anim_start_blended(moby, 11, 0, math_random_int_range(10, 30));
            vars[0x48] = FloatToInt(20.0f);
            vars[0x4A] = FloatToInt(24.0f);
        }
        break;
    case 13:
        if (moby[0x60] & 2) {
            if ((unsigned char)moby[0x95] == 4) {
                *(float *)(vars + 0x494) -= 1.0f;
                moby_set_state(moby, 14, -1);
            } else {
                moby_set_state(moby, 9, -1);
                if (*(unsigned char *)(moby + 0x43) != 18)
                    anim_start_blended(moby, 18, 0, 10);
                vars[0x48] = FloatToInt(20.0f);
                vars[0x4A] = FloatToInt(24.0f);
            }
            if (vec_distance_xy(moby + 0x10, vars + 0x200) < 16.0f) {
                if (FastDiffRots(*(float *)(moby + 0xF8),
                    mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                *(float *)(vars + 0x204) - *(float *)(moby + 0x14))) < 0.4363323450088501f) {
                    moby_set_state(moby, 10, -1);
                    if (*(unsigned char *)(moby + 0x43) != 21)
                        anim_start_blended(moby, 21, 0, 16);
                    vars[0x48] = FloatToInt(20.0f);
                    vars[0x4A] = FloatToInt(8.0f);
                }
            }
        }
        break;
    case 14:
        moby_set_state(moby, 10, -1);
        if (*(unsigned char *)(moby + 0x43) != 21)
            anim_start_blended(moby, 21, 0, 16);
        vars[0x48] = FloatToInt(20.0f);
        vars[0x4A] = FloatToInt(8.0f);
        break;
    }
    actor_aim_body_at_target(moby);
}
