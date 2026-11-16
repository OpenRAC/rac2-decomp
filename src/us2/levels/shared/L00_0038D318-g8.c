#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x70];
    f32 f70;
    f32 f74;
    u8 pad78[0x68];
} LevelClass;
typedef struct {
    s32 i0;
    s32 i4;
    u8 pad8[0x14];
    s32 i1C;
    s32 i20;
    u8 pad24[8];
} CamMode;
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
} CollResult;
typedef struct {
    f32 v[4];
    char *moby;
    s32 mask;
    s8 b18;
    s8 b19;
    u16 h1A;
    f32 f1C;
    s32 i20;
} CollQuery;
extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern u8 g_sound_state[];
extern LevelClass g_weapon_l00_table[];
extern CamMode g_hero_l00_action_table[];
extern CollResult g_collision_result __attribute__((aligned(16)));
extern char *g_area_hit_targets __attribute__((nosda));
extern int g_current_weapon_channel;
extern void hud_add_moby_marker(void *, int, int, int, int, int, float, float, float);
extern void ref_L00_0038BF18_00(void *, void *);
extern void UpdateTrailStrips(void *);
extern void anim_start_blended(void *, int, int, int);
extern void weapon_sync_anim_to_hero(char *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float FastVecLength(void *);
extern void vec_scale_by_angle_limit(char *);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern int moby_is_missing_or_class_502(char *);
extern int PlayMobySound(int, int, void *);
extern void part_spawn_weapon_impact_sparks(char *);
extern void part_queue_impact_effect(void *, void *, int, void *, void *, float);
extern int math_is_below_plane_within_depth(float);
extern void hero_apply_mode_transform_reversed(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void vec_add_transformed_point(void *, void *, float, float, float);
extern int coll_sweep_segment_for_hit(char *, char *, char *, char *, void *, void *, int);
extern int record_is_current_flag_set(void);
extern int record_is_current_byte_one(void);
extern int coll_process_hit(float, void *, int, void *, void *);
extern void moby_update_transform_history_followers(void *, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern int math_fast_float_d(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float ApproachValue(float *, float, float);
extern void moby_trigger_nearby_response_us2(char *);
extern void hero_set_anim_mode(int);
extern void snd_stop_voice(int);
extern int hero_play_sound(int, int);
extern void level_release_slot_list(void *);
extern int moby_is_in_special_class_range(char *);
extern float *moby_get_private_value_0(char *);
extern void LerpVector4(void *, void *, void *, float);
extern void part_l00_spawn_spark_pairs(void *, int);

/* Updates the hero's wrench object: checks what the swing hits, and handles the throw out and the return to the hero (USA v2.00). */
void wrench_update_us2(char *moby)
{
    f32 vectors[8][4] __attribute__((aligned(16)));
    char *vars;
    float angle;
    char *hero_moby;
    char *hero_moby_check;
    char *hit_class;
    char *mode;
    char *pos;
    char *sound;
    float *link;
    float yaw;
    float yaw_diff;
    float lim;
    float range;
    float pull;
    float reach_scale;
    float distance_to_hero;
    float moby_z;
    float check_radius;
    float ground_z;
    LevelClass *level_class;
    CamMode *cam_mode;
    int can_hit;
    int swing_allowed;
    int did_hit;
    int arrived;
    int too_far;

    vars = *(char **)(moby + 0x68);
    ((Hero *)g_hero_state)->b[0x123C] = 0;
    if (((Hero *)g_hero_state)->i[0x1244 / 4] == 3) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(void **)(moby + 0xB8) = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if ((((Hero *)g_hero_state)->i[0x2294 / 4] == 1 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D)
            && (*(u16 *)((char *)((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x34) & 1)) {
            hud_add_moby_marker(moby, 0xFF917267, 0, 0x25, -1, 4, 1.0f, 0.0f, 90.0f);
        }
        if (vars != 0 && *(f32 *)(vars + 0x70) != 0.0f) {
            ref_L00_0038BF18_00(UpdateTrailStrips, moby);
        }
        if (g_current_weapon_channel == 0) {
            *(u16 *)(moby + 0x34) &= ~0x10;
        } else {
            *(u32 *)(moby + 0x78) = 0x80909090;
            *(u16 *)(moby + 0x34) |= 0x10;
        }
        if (*(u8 *)(moby + 0x43) != 0) {
            if (*(u8 *)(moby + 0x43) == 0xE) {
                if (*(u8 *)(moby + 0x60) & 2) {
                    anim_start_blended(moby, 1, 0, 5);
                }
                return;
            }
            if (((Hero *)g_hero_state)->b[0x22BE] != 0) {
                if ((u8)(*(u8 *)(moby + 0x43) - 0xF) >= 2) {
                    anim_start_blended(moby, 0xF, 0, 4);
                } else if ((*(u8 *)(moby + 0x60) & 2) && *(u8 *)(moby + 0x43) == 0xF) {
                    anim_start_blended(moby, 0x10, 0, 5);
                }
                return;
            }
            if ((u8)(*(u8 *)(moby + 0x43) - 0xF) < 2) {
                anim_start_blended(moby, 0xE, 0, 2);
                return;
            }
        }
        if ((*(u8 *)(moby + 0x60) & 2) && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x37 && ((Hero *)g_hero_state)->i[0x229C / 4] != 0x22
            && *(u8 *)(moby + 0x43) != 1) {
            anim_start_blended(moby, 1, 0, 5);
        }
        weapon_sync_anim_to_hero(moby);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x13 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x20 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A
            && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x14
            && *(u8 *)(moby + 0x43) >= 3 && *(u8 *)(moby + 0x43) < 6) {
            anim_start_blended(moby, 1, 0, 4);
        }
        hero_moby = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if (*(u8 *)(hero_moby + 0x43) != *(u8 *)(hero_moby + 0x42) || *(u8 *)(hero_moby + 0x41) - *(u8 *)(hero_moby + 0x40) >= 3) {
            *(u16 *)(vars + 0x74) += 1;
        }
        *(f32 *)(moby + 0x48) = ((Hero *)g_hero_state)->f[0xC20 / 4];
        cam_mode = &g_hero_l00_action_table[((Hero *)g_hero_state)->h[0xBFC / 2]];
        if (((Hero *)g_hero_state)->i[0x229C / 4] != 6 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A) {
            return;
        }
        can_hit = 1;
        if (((Hero *)g_hero_state)->i[0xC2C / 4] != 0 || ((Hero *)g_hero_state)->f[0xC38 / 4] < (f32)cam_mode->i1C || (f32)cam_mode->i20 < ((Hero *)g_hero_state)->f[0xC38 / 4]) {
            can_hit = 0;
        }
        swing_allowed = 0;
        if (*(s16 *)(vars + 0x7C) != *(s16 *)(vars + 0x74)) {
            hero_moby_check = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
            if (*(u8 *)(hero_moby_check + 0x42) == *(u8 *)(hero_moby_check + 0x43)) {
                if (*(u8 *)(hero_moby_check + 0x42) == 0x17) {
                    swing_allowed = 1;
                    if (!(0.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        swing_allowed = 0;
                    }
                } else if (*(u8 *)(hero_moby_check + 0x42) == 0x18) {
                    swing_allowed = 1;
                    if (!(0.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        swing_allowed = 0;
                    }
                } else if (*(u8 *)(hero_moby_check + 0x42) == 0x19) {
                    swing_allowed = 1;
                    if (!(12.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        swing_allowed = 0;
                    }
                } else if (*(u8 *)(hero_moby_check + 0x42) == 0x2B) {
                    swing_allowed = 1;
                    if (!(23.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        swing_allowed = 0;
                    }
                }
            }
        }
        if (swing_allowed != 0) {
            *(f32 *)(vars + 0x70) = 1.0f;
            *(s16 *)(vars + 0x7C) = *(s16 *)(vars + 0x74);
        }
        yaw_diff = 0.0f;
        yaw = ((Hero *)g_hero_state)->f[0x98 / 4];
        qcopy(&((Hero *)g_hero_state)->b[0xB90], &((Hero *)g_hero_state)->b[0xB70]);
        qcopy(&((Hero *)g_hero_state)->b[0xB80], &((Hero *)g_hero_state)->b[0xB60]);
        moby_transform_joint_to_world(moby, 1, &((Hero *)g_hero_state)->b[0xB70]);
        moby_transform_joint_to_world(((Hero *)g_hero_state)->ptr[0x2290 / 4], 0, &((Hero *)g_hero_state)->b[0xB60]);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x13 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6D || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x2A) {
            yaw = mat_fast_helper_a(((Hero *)g_hero_state)->f[0xB70 / 4] - ((Hero *)g_hero_state)->f[0x80 / 4], ((Hero *)g_hero_state)->f[0xB74 / 4] - ((Hero *)g_hero_state)->f[0x84 / 4]);
            if (g_hero_l00_action_table[((Hero *)g_hero_state)->h[0xBFC / 2]].i4 == 1) {
                yaw = FastAddRotations(yaw, -1.57079649f);
            } else {
                yaw = FastAddRotations(yaw, 1.57079649f);
            }
        }
        {
            FastVecSub(vectors[0], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60]);
            vec_scale_to_length(vectors[0], vectors[0], FastVecLength(vectors[0]) + 0.17f);
            if (((Hero *)g_hero_state)->i[0x229C / 4] != 0xF && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x14) {
                yaw_diff = FastDiffRots(((Hero *)g_hero_state)->f[0x98 / 4],
                                     mat_fast_helper_a(((Hero *)g_hero_state)->f[0xB70 / 4] - ((Hero *)g_hero_state)->f[0x80 / 4],
                                                   ((Hero *)g_hero_state)->f[0xB74 / 4] - ((Hero *)g_hero_state)->f[0x84 / 4]));
                if (yaw_diff > 1.57079649f) {
                    can_hit = 0;
                }
                vec_scale_by_angle_limit((char *)vectors[0]);
            }
            FastVecAdd(&((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60], vectors[0]);
            if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && yaw_diff < 1.22173059f
                && ((Hero *)g_hero_state)->i[0x1B8 / 4] >= 11) {
                qcopy(vectors[0], &((Hero *)g_hero_state)->b[0x80]);
                vectors[0][2] = vectors[0][2] + 0.5f;
                angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0xB70 / 4] - ((Hero *)g_hero_state)->f[0x80 / 4], ((Hero *)g_hero_state)->f[0xB74 / 4] - ((Hero *)g_hero_state)->f[0x84 / 4]);
                qcopy(vectors[1], &((Hero *)g_hero_state)->b[0x80]);
                vectors[1][2] = vectors[1][2] + 0.5f;
                vectors[2][0] = math_fast_sin_or_cos_a(angle) * 1.4f;
                vectors[2][1] = math_fast_sin_or_cos_b(angle) * 1.4f;
                vectors[2][2] = 0.0f;
                vec_scale_by_angle_limit((char *)vectors[2]);
                FastVecAdd(vectors[1], vectors[1], vectors[2]);
                if (((Hero *)g_hero_state)->h[0xBFE / 2] == 0 && CollLine(vectors[0], vectors[1], 2, 0, 0) != 0 && GetCollHitMaterial() != 0
                    && (g_collision_result.moby == 0 || moby_is_missing_or_class_502(g_collision_result.moby) != 0)) {
                    ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                    PlayMobySound(2, 0, moby);
                    part_spawn_weapon_impact_sparks(moby);
                    if (g_collision_result.moby != 0) {
                        if (((Hero *)g_hero_state)->b[0x22C3] == 0) {
                            vectors[3][0] = math_fast_sin_or_cos_a(yaw);
                            vectors[3][1] = math_fast_sin_or_cos_b(yaw);
                            vectors[3][2] = 0.0f;
                        } else {
                            qcopy(vectors[3], &((Hero *)g_hero_state)->b[0]);
                        }
                        part_queue_impact_effect(g_collision_result.moby, moby, 0x10000, g_collision_result.pos, vectors[3], 1.0f);
                    }
                }
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14 && math_is_below_plane_within_depth(27.0f) != 0) {
                PlayMobySound(2, 0, moby);
                qcopy(vectors[0], &((Hero *)g_hero_state)->b[0xB70]);
                qcopy(vectors[1], vectors[0]);
                hero_apply_mode_transform_reversed(vectors[0], vectors[0], 0.7f);
                hero_apply_mode_transform_reversed(vectors[1], vectors[1], -0.9f);
                if (CollLine(vectors[0], vectors[1], 2, 0, 0) != 0) {
                    part_spawn_weapon_impact_sparks(moby);
                }
            }
        }
        if (can_hit != 0) {
            level_class = &g_weapon_l00_table[g_item_slot_to_record[0xA]];
            reach_scale = 1.0f;
            range = level_class->f70;
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14) {
                range = level_class->f74;
                reach_scale = 1.55f;
            }
            vectors[3][0] = math_fast_sin_or_cos_a(yaw);
            vectors[3][1] = math_fast_sin_or_cos_b(yaw);
            vectors[3][2] = 0.0f;
            make_hit_descriptor(vectors[0], moby, 0x10000, vectors[3], range);
            vec_fast_normalize_helper(vectors[0], vectors[0], reach_scale);
            vectors[0][2] = 1.0f;
            vectors[0][3] = 5627.9248f;
            ((CollQuery *)vectors[0])->b19 = 1;
            ((CollQuery *)vectors[0])->h1A = *(u16 *)(moby + 0xAA);
            ((CollQuery *)vectors[0])->b18 = 0;
            if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                qzero_nc(vectors[3]);
                vec_add_transformed_point(((Hero *)g_hero_state)->ptr[0x2290 / 4], vectors[3], 1.0f, 0.0f, 1.0f);
            }
            if (coll_sweep_segment_for_hit(&((Hero *)g_hero_state)->b[0xB60], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB80], &((Hero *)g_hero_state)->b[0xB90],
                                  ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vectors[0], 5) != 0
                && g_collision_result.moby != 0 && record_is_current_flag_set() == 0 && ((Hero *)g_hero_state)->h[0xBFE / 2] == 0
                && (g_collision_result.moby == 0 || *(char **)(g_collision_result.moby + 0x24) == 0
                    || *(s16 *)(*(char **)(g_collision_result.moby + 0x24) + 0x46) != 0x14)) {
                ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                PlayMobySound(record_is_current_byte_one(), 0, moby);
                part_spawn_weapon_impact_sparks(moby);
            }
            FastVecSub(vectors[5], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60]);
            vec_scale_to_length(vectors[5], vectors[5], FastVecLength(vectors[5]) - 0.085f);
            FastVecAdd(vectors[4], vectors[5], &((Hero *)g_hero_state)->b[0xB60]);
            check_radius = 0.35f;
            if (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF) {
                check_radius = 0.7f;
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14) {
                check_radius = 0.47f;
            }
            if (coll_process_hit(check_radius, vectors[4], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vectors[0]) == 0) {
                return;
            }
            if (g_area_hit_targets != 0 && *(char **)(g_area_hit_targets + 0x24) != 0
                && *(s16 *)(*(char **)(g_area_hit_targets + 0x24) + 0x46) == 0x12) {
                return;
            }
            if (record_is_current_flag_set() != 0) {
                return;
            }
            if (((Hero *)g_hero_state)->h[0xBFE / 2] != 0) {
                return;
            }
            ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
            PlayMobySound(record_is_current_byte_one(), 0, moby);
            part_spawn_weapon_impact_sparks(moby);
        }
        break;
    case 10:
    case 11: {
        moby_update_transform_history_followers(&((Hero *)g_hero_state)->b[0x1A30], 0);
        *(void **)(moby + 0xB8) = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        ((Hero *)g_hero_state)->b[0x123C] = 2;
        if (*(u8 *)(moby + 0x20) == 10) {
            sound = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
            if (*(void **)(sound + 0x88) != ((Hero *)g_hero_state)->ptr[0x2290 / 4] || *(u8 *)(sound + 0x74) == 0) {
                ((Hero *)g_hero_state)->i[0x2430 / 4] = PlayMobySound(0xB, 4, ((Hero *)g_hero_state)->ptr[0x2290 / 4]);
            }
        }
        mat_apply_offset_to_object(moby, 0.0f, 0.0f, 0.40724355f);
        if (((Hero *)g_hero_state)->h[0xBFE / 2] != 0 && math_fast_float_d(vars + 0x6C) != 0) {
            ((Hero *)g_hero_state)->h[0xBFE / 2] = 0;
        }
        pos = moby + 0x10;
        if (((Hero *)g_hero_state)->b[0x22C3] == 0) {
            ground_z = coll_probe_ground_height_below(pos, 0, 0.5f);
            moby_z = *(f32 *)(moby + 0x18);
            if (moby_z - ground_z < 0.8f) {
                ground_z = ground_z + 0.55f;
                if (moby_z < ground_z) {
                    ApproachValue((f32 *)(moby + 0x18), ground_z, 0.06666667f);
                } else {
                    ApproachValue((f32 *)(moby + 0x18), ground_z, 0.016666668f);
                }
            }
        }
        qcopy(vectors[0], pos);
        if (*(u8 *)(moby + 0x20) == 10) {
            qcopy(vectors[1], &((Hero *)g_hero_state)->b[0x150]);
            FastVecScale(vectors[1], vectors[1], 0.98f);
            FastVecAdd(pos, pos, vectors[1]);
            vec_scale_to_length(vectors[1], vars + 0x40, *(f32 *)(vars + 0x60));
            FastVecAdd(pos, pos, vectors[1]);
            *(f32 *)(vars + 0x64) = *(f32 *)(vars + 0x64) + 0.000787037017f;
            ApproachValue((f32 *)(vars + 0x60), 0.0f, *(f32 *)(vars + 0x64));
            if (*(f32 *)(vars + 0x60) == 0.0f) {
                *(u8 *)(moby + 0x20) = 11;
            }
        } else {
            qcopy(vectors[1], &((Hero *)g_hero_state)->b[0x150]);
            FastVecScale(vectors[1], vectors[1], 0.98f);
            arrived = 0;
            FastVecAdd(pos, pos, vectors[1]);
            moby_trigger_nearby_response_us2(moby);
            FastVecSub(vectors[1], &((Hero *)g_hero_state)->b[0x1200], pos);
            *(f32 *)(vars + 0x64) = *(f32 *)(vars + 0x64) + 0.00025f;
            *(f32 *)(vars + 0x60) = *(f32 *)(vars + 0x60) + *(f32 *)(vars + 0x64);
            distance_to_hero = FastVecLength(vectors[1]);
            if (distance_to_hero / *(f32 *)(vars + 0x60) < 5.0f && *(u8 *)(moby + 0x43) != 1) {
                anim_start_blended(moby, 1, 0, 5);
            }
            if (distance_to_hero <= *(f32 *)(vars + 0x60)) {
                *(f32 *)(vars + 0x60) = distance_to_hero;
                arrived = 1;
            }
            vec_scale_to_length(vectors[1], vectors[1], *(f32 *)(vars + 0x60));
            FastVecAdd(pos, pos, vectors[1]);
            if (distance_to_hero / *(f32 *)(vars + 0x60) < 4.0f && ((Hero *)g_hero_state)->i[0xC40 / 4] != -1) {
                hero_set_anim_mode(2);
                ((Hero *)g_hero_state)->i[0xC44 / 4] = 0x1A;
                if (((Hero *)g_hero_state)->i[0x2430 / 4] != -1) {
                    sound = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(sound + 0x88) == ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(u8 *)(sound + 0x74) != 0) {
                        snd_stop_voice(((Hero *)g_hero_state)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)g_hero_state)->i[0x2430 / 4] = -1;
            }
            too_far = 0;
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x31 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x61 || distance_to_hero > 32.0f) {
                too_far = 1;
            }
            if (arrived != 0 || too_far != 0) {
                if (too_far == 0) {
                    hero_play_sound(5, 0);
                }
                if (((Hero *)g_hero_state)->i[0x2430 / 4] != -1) {
                    sound = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(sound + 0x88) == ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(u8 *)(sound + 0x74) != 0) {
                        snd_stop_voice(((Hero *)g_hero_state)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)g_hero_state)->i[0x2430 / 4] = -1;
                level_release_slot_list(&((Hero *)g_hero_state)->b[0x1A30]);
                ((Hero *)g_hero_state)->b[0x123A] = 0;
                *(u8 *)(moby + 0x20) = 0;
            }
        }
        did_hit = 0;
        if (CollLine(vectors[0], pos, 2, 0, 0) != 0 && GetCollHitMaterial() != 0
            && (g_collision_result.moby == 0 || moby_is_in_special_class_range(g_collision_result.moby) == 0)) {
            did_hit = g_collision_result.count != 0;
        }
        if (did_hit != 0 || *(s16 *)(vars + 0x76) != 0) {
            *(s16 *)(vars + 0x76) = 0;
            if (((Hero *)g_hero_state)->h[0xBFE / 2] == 0) {
                *(int *)(vars + 0x6C) = 0x1E;
                ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                PlayMobySound(2, 0, moby);
            }
            if (*(u8 *)(moby + 0x20) == 10) {
                part_spawn_weapon_impact_sparks(moby);
                *(f32 *)(vars + 0x60) = *(f32 *)(vars + 0x60) * 0.5f;
                *(u8 *)(moby + 0x20) = 11;
            }
        }
        pull = 1.2f;
        if (*(u8 *)(moby + 0x20) == 11) {
            pull = -0.37f;
        }
        vec_scale_to_length(vectors[4], vars + 0x40, pull);
        make_hit_descriptor(vectors[1], moby, 0x10000, vectors[4], (&g_weapon_l00_table[g_item_slot_to_record[0xA]])->f70);
        vectors[1][2] = 1.0f;
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            qzero_nc(vectors[1]);
            vec_add_transformed_point(((Hero *)g_hero_state)->ptr[0x2290 / 4], vectors[1], pull, 0.0f, 1.0f);
        }
        vectors[1][3] = 5627.9248f;
        ((CollQuery *)vectors[1])->b19 = 1;
        ((CollQuery *)vectors[1])->h1A = ((Hero *)g_hero_state)->uh[0xC0C / 2] + 1;
        ((CollQuery *)vectors[1])->b18 = 0;
        moby_transform_joint_to_world(moby, 1, vectors[5]);
        if ((coll_process_hit(0.4f, vectors[5], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vectors[1]) != 0
             || (moby_transform_joint_to_world(moby, 0, vectors[5]), coll_process_hit(0.4f, vectors[5], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vectors[1]) != 0))
            && ((Hero *)g_hero_state)->h[0xBFE / 2] == 0 && g_collision_result.moby != 0) {
            hit_class = *(char **)(g_collision_result.moby + 0x24);
            if (hit_class == 0 || *(s16 *)(hit_class + 0x46) != 0x14) {
                link = moby_get_private_value_0(g_collision_result.moby);
                if (link == 0 || *(s16 *)((char *)link + 0x1C) == 0 || *(char **)((char *)link + 0x18) != moby) {
                    *(TI128 *)vectors[7] = *(TI128 *)(g_collision_result.moby + 0x10);
                    LerpVector4(vectors[6], vectors[5], vectors[7], 0.5f);
                    part_l00_spawn_spark_pairs(vectors[6], 5);
                    *(int *)(vars + 0x6C) = 0x1E;
                    ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                    PlayMobySound(record_is_current_byte_one(), 0, moby);
                }
            }
        }
        break;
    }
    }
}
