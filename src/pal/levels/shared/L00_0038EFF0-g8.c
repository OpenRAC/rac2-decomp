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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void weapon_sync_anim_to_hero_pal(char *);
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
extern void part_spawn_weapon_impact_sparks_pal(char *);
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
extern void moby_trigger_nearby_response_pal(char *);
extern void func_PAL_L00_002D29D0(int);
extern void snd_stop_voice(int);
extern int hero_play_sound(int, int);
extern void level_release_slot_list(void *);
extern int moby_is_in_special_class_range(char *);
extern float *moby_get_private_value_0(char *);
extern void LerpVector4(void *, void *, void *, float);
extern void part_l00_spawn_spark_pairs_pal(void *, int);

void wrench_update_pal(char *m)
{
    f32 vec[8][4] __attribute__((aligned(16)));
    char *pv;
    float ang;
    char *t;
    char *t2;
    char *t3;
    char *mode;
    char *pos;
    char *snd;
    float *r;
    float yaw;
    float diff;
    float lim;
    float range;
    float k;
    float sc;
    float d;
    float zf;
    float g;
    float top;
    LevelClass *cls;
    CamMode *cm;
    int ok;
    int found;
    int hit;
    int done;
    int far;

    pv = *(char **)(m + 0x68);
    ((Hero *)g_hero_state)->b[0x123C] = 0;
    if (((Hero *)g_hero_state)->i[0x1244 / 4] == 3) {
        return;
    }
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        *(void **)(m + 0xB8) = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if ((((Hero *)g_hero_state)->i[0x2294 / 4] == 1 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D)
            && (*(u16 *)((char *)((Hero *)g_hero_state)->ptr[0x2290 / 4] + 0x34) & 1)) {
            hud_add_moby_marker(m, 0xFF917267, 0, 0x25, -1, 4, 1.0f, 0.0f, 90.0f);
        }
        if (pv != 0 && *(f32 *)(pv + 0x70) != 0.0f) {
            ref_L00_0038BF18_00(UpdateTrailStrips, m);
        }
        if (g_current_weapon_channel == 0) {
            *(u16 *)(m + 0x34) &= ~0x10;
        } else {
            *(u32 *)(m + 0x78) = 0x80909090;
            *(u16 *)(m + 0x34) |= 0x10;
        }
        if (*(u8 *)(m + 0x43) != 0) {
            if (*(u8 *)(m + 0x43) == 0xE) {
                if (*(u8 *)(m + 0x60) & 2) {
                    func_PAL_002A7E68(m, 1, 0, 4);
                }
                return;
            }
            if (((Hero *)g_hero_state)->b[0x22BE] != 0) {
                if ((u8)(*(u8 *)(m + 0x43) - 0xF) >= 2) {
                    func_PAL_002A7E68(m, 0xF, 0, 3);
                } else if ((*(u8 *)(m + 0x60) & 2) && *(u8 *)(m + 0x43) == 0xF) {
                    func_PAL_002A7E68(m, 0x10, 0, 4);
                }
                return;
            }
            if ((u8)(*(u8 *)(m + 0x43) - 0xF) < 2) {
                func_PAL_002A7E68(m, 0xE, 0, 2);
                return;
            }
        }
        if ((*(u8 *)(m + 0x60) & 2) && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x37 && ((Hero *)g_hero_state)->i[0x229C / 4] != 0x22
            && *(u8 *)(m + 0x43) != 1) {
            func_PAL_002A7E68(m, 1, 0, 4);
        }
        weapon_sync_anim_to_hero_pal(m);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x13 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x20 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A
            && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x14
            && *(u8 *)(m + 0x43) >= 3 && *(u8 *)(m + 0x43) < 6) {
            func_PAL_002A7E68(m, 1, 0, 3);
        }
        t = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if (*(u8 *)(t + 0x43) != *(u8 *)(t + 0x42) || *(u8 *)(t + 0x41) - *(u8 *)(t + 0x40) >= 3) {
            *(u16 *)(pv + 0x74) += 1;
        }
        *(f32 *)(m + 0x48) = ((Hero *)g_hero_state)->f[0xC20 / 4];
        cm = &g_hero_l00_action_table[((Hero *)g_hero_state)->h[0xBFC / 2]];
        if (((Hero *)g_hero_state)->i[0x229C / 4] != 6 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A) {
            return;
        }
        ok = 1;
        if (((Hero *)g_hero_state)->i[0xC2C / 4] != 0 || ((Hero *)g_hero_state)->f[0xC38 / 4] < (f32)cm->i1C || (f32)cm->i20 < ((Hero *)g_hero_state)->f[0xC38 / 4]) {
            ok = 0;
        }
        found = 0;
        if (*(s16 *)(pv + 0x7C) != *(s16 *)(pv + 0x74)) {
            t2 = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
            if (*(u8 *)(t2 + 0x42) == *(u8 *)(t2 + 0x43)) {
                if (*(u8 *)(t2 + 0x42) == 0x17) {
                    found = 1;
                    if (!(0.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x18) {
                    found = 1;
                    if (!(0.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x19) {
                    found = 1;
                    if (!(12.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x2B) {
                    found = 1;
                    if (!(23.0f <= ((Hero *)g_hero_state)->f[0xC38 / 4])) {
                        found = 0;
                    }
                }
            }
        }
        if (found != 0) {
            *(f32 *)(pv + 0x70) = 1.0f;
            *(s16 *)(pv + 0x7C) = *(s16 *)(pv + 0x74);
        }
        diff = 0.0f;
        yaw = ((Hero *)g_hero_state)->f[0x98 / 4];
        qcopy(&((Hero *)g_hero_state)->b[0xB90], &((Hero *)g_hero_state)->b[0xB70]);
        qcopy(&((Hero *)g_hero_state)->b[0xB80], &((Hero *)g_hero_state)->b[0xB60]);
        moby_transform_joint_to_world(m, 1, &((Hero *)g_hero_state)->b[0xB70]);
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
            FastVecSub(vec[0], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60]);
            vec_scale_to_length(vec[0], vec[0], FastVecLength(vec[0]) + 0.17f);
            if (((Hero *)g_hero_state)->i[0x229C / 4] != 0xF && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x14) {
                diff = FastDiffRots(((Hero *)g_hero_state)->f[0x98 / 4],
                                     mat_fast_helper_a(((Hero *)g_hero_state)->f[0xB70 / 4] - ((Hero *)g_hero_state)->f[0x80 / 4],
                                                   ((Hero *)g_hero_state)->f[0xB74 / 4] - ((Hero *)g_hero_state)->f[0x84 / 4]));
                if (diff > 1.57079649f) {
                    ok = 0;
                }
                vec_scale_by_angle_limit((char *)vec[0]);
            }
            FastVecAdd(&((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60], vec[0]);
            if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2A && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6D && diff < 1.22173059f
                && ((Hero *)g_hero_state)->i[0x1B8 / 4] >= 9) {
                qcopy(vec[0], &((Hero *)g_hero_state)->b[0x80]);
                vec[0][2] = vec[0][2] + 0.5f;
                ang = mat_fast_helper_a(((Hero *)g_hero_state)->f[0xB70 / 4] - ((Hero *)g_hero_state)->f[0x80 / 4], ((Hero *)g_hero_state)->f[0xB74 / 4] - ((Hero *)g_hero_state)->f[0x84 / 4]);
                qcopy(vec[1], &((Hero *)g_hero_state)->b[0x80]);
                vec[1][2] = vec[1][2] + 0.5f;
                vec[2][0] = math_fast_sin_or_cos_a(ang) * 1.4f;
                vec[2][1] = math_fast_sin_or_cos_b(ang) * 1.4f;
                vec[2][2] = 0.0f;
                vec_scale_by_angle_limit((char *)vec[2]);
                FastVecAdd(vec[1], vec[1], vec[2]);
                if (((Hero *)g_hero_state)->h[0xBFE / 2] == 0 && CollLine(vec[0], vec[1], 2, 0, 0) != 0 && GetCollHitMaterial() != 0
                    && (g_collision_result.moby == 0 || moby_is_missing_or_class_502(g_collision_result.moby) != 0)) {
                    ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                    PlayMobySound(2, 0, m);
                    part_spawn_weapon_impact_sparks_pal(m);
                    if (g_collision_result.moby != 0) {
                        if (((Hero *)g_hero_state)->b[0x22C3] == 0) {
                            vec[3][0] = math_fast_sin_or_cos_a(yaw);
                            vec[3][1] = math_fast_sin_or_cos_b(yaw);
                            vec[3][2] = 0.0f;
                        } else {
                            qcopy(vec[3], &((Hero *)g_hero_state)->b[0]);
                        }
                        part_queue_impact_effect(g_collision_result.moby, m, 0x10000, g_collision_result.pos, vec[3], 1.0f);
                    }
                }
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14 && math_is_below_plane_within_depth(27.0f) != 0) {
                PlayMobySound(2, 0, m);
                qcopy(vec[0], &((Hero *)g_hero_state)->b[0xB70]);
                qcopy(vec[1], vec[0]);
                hero_apply_mode_transform_reversed(vec[0], vec[0], 0.7f);
                hero_apply_mode_transform_reversed(vec[1], vec[1], -0.9f);
                if (CollLine(vec[0], vec[1], 2, 0, 0) != 0) {
                    part_spawn_weapon_impact_sparks_pal(m);
                }
            }
        }
        if (ok != 0) {
            cls = &g_weapon_l00_table[g_item_slot_to_record[0xA]];
            sc = 1.0f;
            range = cls->f70;
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14) {
                range = cls->f74;
                sc = 1.55f;
            }
            vec[3][0] = math_fast_sin_or_cos_a(yaw);
            vec[3][1] = math_fast_sin_or_cos_b(yaw);
            vec[3][2] = 0.0f;
            make_hit_descriptor(vec[0], m, 0x10000, vec[3], range);
            vec_fast_normalize_helper(vec[0], vec[0], sc);
            vec[0][2] = 1.0f;
            vec[0][3] = 5627.9248f;
            ((CollQuery *)vec[0])->b19 = 1;
            ((CollQuery *)vec[0])->h1A = *(u16 *)(m + 0xAA);
            ((CollQuery *)vec[0])->b18 = 0;
            if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
                qzero_nc(vec[3]);
                vec_add_transformed_point(((Hero *)g_hero_state)->ptr[0x2290 / 4], vec[3], 1.0f, 0.0f, 1.0f);
            }
            if (coll_sweep_segment_for_hit(&((Hero *)g_hero_state)->b[0xB60], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB80], &((Hero *)g_hero_state)->b[0xB90],
                                  ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vec[0], 5) != 0
                && g_collision_result.moby != 0 && record_is_current_flag_set() == 0 && ((Hero *)g_hero_state)->h[0xBFE / 2] == 0
                && (g_collision_result.moby == 0 || *(char **)(g_collision_result.moby + 0x24) == 0
                    || *(s16 *)(*(char **)(g_collision_result.moby + 0x24) + 0x46) != 0x14)) {
                ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                PlayMobySound(record_is_current_byte_one(), 0, m);
                part_spawn_weapon_impact_sparks_pal(m);
            }
            FastVecSub(vec[5], &((Hero *)g_hero_state)->b[0xB70], &((Hero *)g_hero_state)->b[0xB60]);
            vec_scale_to_length(vec[5], vec[5], FastVecLength(vec[5]) - 0.085f);
            FastVecAdd(vec[4], vec[5], &((Hero *)g_hero_state)->b[0xB60]);
            g = 0.35f;
            if (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF) {
                g = 0.7f;
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x14) {
                g = 0.47f;
            }
            if (coll_process_hit(g, vec[4], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vec[0]) == 0) {
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
            PlayMobySound(record_is_current_byte_one(), 0, m);
            part_spawn_weapon_impact_sparks_pal(m);
        }
        break;
    case 10:
    case 11: {
        moby_update_transform_history_followers(&((Hero *)g_hero_state)->b[0x1A30], 0);
        *(void **)(m + 0xB8) = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        ((Hero *)g_hero_state)->b[0x123C] = 2;
        if (*(u8 *)(m + 0x20) == 10) {
            snd = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
            if (*(void **)(snd + 0x88) != ((Hero *)g_hero_state)->ptr[0x2290 / 4] || *(u8 *)(snd + 0x74) == 0) {
                ((Hero *)g_hero_state)->i[0x2430 / 4] = PlayMobySound(0xB, 4, ((Hero *)g_hero_state)->ptr[0x2290 / 4]);
            }
        }
        mat_apply_offset_to_object(m, 0.0f, 0.0f, 0.48869228f);
        if (((Hero *)g_hero_state)->h[0xBFE / 2] != 0 && math_fast_float_d(pv + 0x6C) != 0) {
            ((Hero *)g_hero_state)->h[0xBFE / 2] = 0;
        }
        pos = m + 0x10;
        if (((Hero *)g_hero_state)->b[0x22C3] == 0) {
            top = coll_probe_ground_height_below(pos, 0, 0.5f);
            zf = *(f32 *)(m + 0x18);
            if (zf - top < 0.8f) {
                top = top + 0.55f;
                if (zf < top) {
                    ApproachValue((f32 *)(m + 0x18), top, 0.080000006f);
                } else {
                    ApproachValue((f32 *)(m + 0x18), top, 0.020000001f);
                }
            }
        }
        qcopy(vec[0], pos);
        if (*(u8 *)(m + 0x20) == 10) {
            qcopy(vec[1], &((Hero *)g_hero_state)->b[0x150]);
            FastVecScale(vec[1], vec[1], 0.98f);
            FastVecAdd(pos, pos, vec[1]);
            vec_scale_to_length(vec[1], pv + 0x40, *(f32 *)(pv + 0x60));
            FastVecAdd(pos, pos, vec[1]);
            *(f32 *)(pv + 0x64) = *(f32 *)(pv + 0x64) + 0.00136f;
            ApproachValue((f32 *)(pv + 0x60), 0.0f, *(f32 *)(pv + 0x64));
            if (*(f32 *)(pv + 0x60) == 0.0f) {
                *(u8 *)(m + 0x20) = 11;
            }
        } else {
            qcopy(vec[1], &((Hero *)g_hero_state)->b[0x150]);
            FastVecScale(vec[1], vec[1], 0.98f);
            done = 0;
            FastVecAdd(pos, pos, vec[1]);
            moby_trigger_nearby_response_pal(m);
            FastVecSub(vec[1], &((Hero *)g_hero_state)->b[0x1200], pos);
            *(f32 *)(pv + 0x64) = *(f32 *)(pv + 0x64) + 0.00036f;
            *(f32 *)(pv + 0x60) = *(f32 *)(pv + 0x60) + *(f32 *)(pv + 0x64);
            d = FastVecLength(vec[1]);
            if (d / *(f32 *)(pv + 0x60) < 4.0f && *(u8 *)(m + 0x43) != 1) {
                func_PAL_002A7E68(m, 1, 0, 4);
            }
            if (d <= *(f32 *)(pv + 0x60)) {
                *(f32 *)(pv + 0x60) = d;
                done = 1;
            }
            vec_scale_to_length(vec[1], vec[1], *(f32 *)(pv + 0x60));
            FastVecAdd(pos, pos, vec[1]);
            if (d / *(f32 *)(pv + 0x60) < 3.0f && ((Hero *)g_hero_state)->i[0xC40 / 4] != -1) {
                func_PAL_L00_002D29D0(2);
                ((Hero *)g_hero_state)->i[0xC44 / 4] = 0x1A;
                if (((Hero *)g_hero_state)->i[0x2430 / 4] != -1) {
                    snd = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(snd + 0x88) == ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(u8 *)(snd + 0x74) != 0) {
                        snd_stop_voice(((Hero *)g_hero_state)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)g_hero_state)->i[0x2430 / 4] = -1;
            }
            far = 0;
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x31 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x61 || d > 32.0f) {
                far = 1;
            }
            if (done != 0 || far != 0) {
                if (far == 0) {
                    hero_play_sound(5, 0);
                }
                if (((Hero *)g_hero_state)->i[0x2430 / 4] != -1) {
                    snd = (char *)g_sound_state + ((Hero *)g_hero_state)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(snd + 0x88) == ((Hero *)g_hero_state)->ptr[0x2290 / 4] && *(u8 *)(snd + 0x74) != 0) {
                        snd_stop_voice(((Hero *)g_hero_state)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)g_hero_state)->i[0x2430 / 4] = -1;
                level_release_slot_list(&((Hero *)g_hero_state)->b[0x1A30]);
                ((Hero *)g_hero_state)->b[0x123A] = 0;
                *(u8 *)(m + 0x20) = 0;
            }
        }
        hit = 0;
        if (CollLine(vec[0], pos, 2, 0, 0) != 0 && GetCollHitMaterial() != 0
            && (g_collision_result.moby == 0 || moby_is_in_special_class_range(g_collision_result.moby) == 0)) {
            hit = g_collision_result.count != 0;
        }
        if (hit != 0 || *(s16 *)(pv + 0x76) != 0) {
            *(s16 *)(pv + 0x76) = 0;
            if (((Hero *)g_hero_state)->h[0xBFE / 2] == 0) {
                *(int *)(pv + 0x6C) = 0x19;
                ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                PlayMobySound(2, 0, m);
            }
            if (*(u8 *)(m + 0x20) == 10) {
                part_spawn_weapon_impact_sparks_pal(m);
                *(f32 *)(pv + 0x60) = *(f32 *)(pv + 0x60) * 0.5f;
                *(u8 *)(m + 0x20) = 11;
            }
        }
        k = 1.2f;
        if (*(u8 *)(m + 0x20) == 11) {
            k = -0.37f;
        }
        vec_scale_to_length(vec[4], pv + 0x40, k);
        make_hit_descriptor(vec[1], m, 0x10000, vec[4], (&g_weapon_l00_table[g_item_slot_to_record[0xA]])->f70);
        vec[1][2] = 1.0f;
        if (((Hero *)g_hero_state)->b[0x22C3] != 0) {
            qzero_nc(vec[1]);
            vec_add_transformed_point(((Hero *)g_hero_state)->ptr[0x2290 / 4], vec[1], k, 0.0f, 1.0f);
        }
        vec[1][3] = 5627.9248f;
        ((CollQuery *)vec[1])->b19 = 1;
        ((CollQuery *)vec[1])->h1A = ((Hero *)g_hero_state)->uh[0xC0C / 2] + 1;
        ((CollQuery *)vec[1])->b18 = 0;
        moby_transform_joint_to_world(m, 1, vec[5]);
        if ((coll_process_hit(0.4f, vec[5], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vec[1]) != 0
             || (moby_transform_joint_to_world(m, 0, vec[5]), coll_process_hit(0.4f, vec[5], 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], (CollQuery *)vec[1]) != 0))
            && ((Hero *)g_hero_state)->h[0xBFE / 2] == 0 && g_collision_result.moby != 0) {
            t3 = *(char **)(g_collision_result.moby + 0x24);
            if (t3 == 0 || *(s16 *)(t3 + 0x46) != 0x14) {
                r = moby_get_private_value_0(g_collision_result.moby);
                if (r == 0 || *(s16 *)((char *)r + 0x1C) == 0 || *(char **)((char *)r + 0x18) != m) {
                    *(TI128 *)vec[7] = *(TI128 *)(g_collision_result.moby + 0x10);
                    LerpVector4(vec[6], vec[5], vec[7], 0.5f);
                    part_l00_spawn_spark_pairs_pal(vec[6], 5);
                    *(int *)(pv + 0x6C) = 0x19;
                    ((Hero *)g_hero_state)->h[0xBFE / 2] = 1;
                    PlayMobySound(record_is_current_byte_one(), 0, m);
                }
            }
        }
        break;
    }
    }
}
