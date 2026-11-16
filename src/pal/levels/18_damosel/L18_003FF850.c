/* func_PAL_L18_003FF850, the PAL copy of func_L18_003FB708: the same C at 50 Hz (frame constants
   rescaled, tick counts through (x * 5 + 2) / 6).
   Per-frame update of the grelbin-style effect moby (L18, L19 and L20): a seven-state switch that
   blends the instance's colors and vectors from the state timer, steps the timer, and
   handles the hero hit loop and the sound slots. Needs -g and -ffast-math (min/max). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* the frame counter of the effect moby, a u16 at +0x96 */
static inline u16 moby_timer(char *m)
{
    return *(u16 *)(m + 0x96);
}

/* the moby's per-instance variables (m + 0x68) */
typedef struct {
    u8 pad0[8];
    s32 i8;
    u8 padC[0x14];
    f32 v20[4][4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    f32 v90[4];
    f32 vA0[4];
    s32 iB0;
    s32 iB4;
    s32 iB8;
    s32 iBC;
    f32 fC0;
    s32 iC4;
    s32 iC8;
    s32 iCC;
    f32 fD0;
    s32 iD4;
    f32 fD8;
    f32 fDC;
    s32 iE0;
    s32 iE4;
} PvVars;

/* one 0x100-byte record of the level's moby-class table at D_L18_001B281C */
typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    u8 pad20[3];
    u8 b23;
    u8 pad24[0x10];
    u16 h34;
    u8 pad36[0x62];
    s32 i98;
    u8 pad9C[0x24];
    f32 mat[4][4];
} ClassRec;

extern char g_hero_state[];
extern u8 g_sound_state[];
extern int g_player_stats[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char g_camera_l18_position[];
extern char *g_path_l18_table[];
extern ClassRec *g_moby_l18_table[] __attribute__((sda));
extern char *g_nearby_hit_targets[];
extern f32 g_train_l18_value_mid[] __attribute__((sda));
extern f32 g_train_l18_value_high[] __attribute__((sda));
extern f32 g_train_sink_rate __attribute__((sda));
extern f32 g_train_turn_angle __attribute__((sda));
extern f32 g_train_offset_vector_a[4] __attribute__((sda));
extern f32 g_train_l18_hit_radius __attribute__((sda));
extern f32 g_train_push_speed_forward __attribute__((sda));
extern f32 g_train_push_speed_back __attribute__((sda));
extern int g_train_timer_start __attribute__((sda));
extern f32 g_train_offset_vector_b[4] __attribute__((sda));
extern int g_train_flash_count __attribute__((sda));
extern f32 g_train_flash_scale_min __attribute__((sda));
extern f32 g_train_flash_scale_max __attribute__((sda));
extern f32 g_train_l18_speed_min __attribute__((sda));
extern f32 g_train_l18_speed_max __attribute__((sda));
extern f32 g_train_speed_a __attribute__((sda));
extern f32 g_train_speed_b __attribute__((sda));
extern f32 g_train_speed_by_video[2] __attribute__((sda));
extern f32 g_train_l18_accel_by_video[2] __attribute__((sda));
extern f32 g_train_phase_one_frames __attribute__((sda));
extern f32 g_train_l18_drag_by_video[2] __attribute__((sda));
extern f32 g_train_phase_two_frames __attribute__((sda));
extern f32 g_train_offset_vector_c[4] __attribute__((sda));
extern f32 g_train_offset_vector_d[4] __attribute__((sda));
extern f32 g_train_l18_value_low __attribute__((sda));
extern int g_train_color_table[] __attribute__((sda));
extern int g_frame_l18_counter __attribute__((sda));
extern char g_train_draw_callback_b[];
extern char g_train_draw_callback_a[];
extern char g_train_draw_callback_first[];

extern int coll_process_hit(float, void *, int, void *, void *);
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void mat_fast_helper_c(float *, float *);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void part_queue_impact_effect(void *, void *, int, void *, void *, float);
extern int IsPointInCuboid(void *, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int flag_set_first_pending(char *);
extern void part_spawn_white_flash(void *, void *, int, float);
extern void path_sample_position(char *, int, void *, void *, int, float);
extern void snd_stop_voice(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void hero_record_play_counters(void);
extern void gfx_add_draw_callback_first(void *, void *);
extern int coll_point_inside_region(void *, int);
extern void gfx_queue_draw_callback(void *, void *);
extern void protopet_start_enter_anim(char *, int);
extern void part_spawn_upward(char *);
extern void part_spawn_spray(char *);
extern s32 hero_l18_set_action(int, int);

void func_PAL_L18_003FF850(char *m)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 vm[3][4] __attribute__((aligned(16)));
    PvVars *pv;
    char *path;
    char *rec;
    ClassRec *tbl;
    ClassRec *tbl2;
    char *src;
    char *snd;
    char *t;
    int n;
    int i;
    int k;
    int cls;
    int st;
    int j;
    float f;
    float g;
    float r;

    pv = *(PvVars **)(m + 0x68);
    qcopy(pos, m + 0x10);
    qcopy(rot, m + 0xF0);
    if (pv->iD4 != -1 && coll_point_inside_region(g_camera_l18_position, pv->iD4) != 0) {
        protopet_start_enter_anim(m, 0);
    }
    if (pv->iE0 > 0) {
        math_fast_float_d(&pv->iE0);
        if (pv->iE0 < 2) {
            hero_record_play_counters();
        }
    }
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        qcopy(pv->v60, m + 0x10);
        qcopy(pv->v70, m + 0xF0);
        if (pv->iB0 != -1) {
            pv->fD8 = 0.0f;
            path = g_path_l18_table[pv->iB0];
            r = 1.0f / fast_vec_dist(path + 0x10, path + 0x20);
            pv->fDC = r * (0.020000001f * pv->fD0);
            qcopy(m + 0x10, path + 0x10);
            pv->iE0 = -1;
        }
        if (*(s16 *)(m + 0xAA) != 0xD9B && *(s16 *)(m + 0xAA) != 0x11CF) {
            pv->i8 = 0;
        }
        if (pv->iC8 != -1) {
            FastVecSub(pv->vA0, m + 0x10, g_moby_l18_table[0][pv->iC8].pos);
            mat_fast_helper_c(vm[0], (float *)g_moby_l18_table[0][pv->iC8].mat);
            matrix_mul_vec3(pv->vA0, pv->vA0, vm[0]);
        }
        if (pv->iB4 != -1) {
            *(u16 *)(m + 0x34) |= 1;
            moby_set_state(m, 4, -1);
        } else {
            moby_set_state(m, 1, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(m) != 0) {
            *(u16 *)(m + 0x34) |= 1;
        }
        if (IsPointInCuboid(g_hero_state + 0x80, pv->iB4) != 0) {
            if (pv->iC8 == -1) {
                *(u16 *)(m + 0x34) |= 0x100;
                vec_scale_to_length(m + 0xC0, m + 0xC0, 0.03234f);
                moby_set_state(m, 7, -1);
            } else {
                moby_set_state(m, 1, -1);
            }
        }
        break;
    case 1:
        if (flag_set_first_pending(m) != 0) {
            vec_scale_to_length(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
        }
        if (pv->iB0 != -1) {
            path_sample_position(g_path_l18_table[pv->iB0], 0, m + 0x10, m + 0xF0, 0, pv->fD8);
            pv->fD8 = pv->fD8 + pv->fDC;
        } else {
            if (pv->iC8 != -1) {
                tbl = g_moby_l18_table[0];
                *(u16 *)(m + 0x34) = tbl[pv->iC8].h34;
                *(u8 *)(m + 0x23) = tbl[pv->iC8].b23;
                tbl2 = g_moby_l18_table[0];
                *(u16 *)(m + 0x34) = tbl2[pv->iC8].h34;
                *(int *)(m + 0x98) = tbl2[pv->iC8].i98;
                cls = pv->iC8;
                for (k = 0; k < 4; k++) {
                    qcopy(m + 0xC0 + k * 16, tbl2[cls].mat[k]);
                }
                matrix_mul_vec3(vm[0], pv->vA0, m + 0xC0);
                FastVecAdd(m + 0x10, vm[0], g_moby_l18_table[0][pv->iC8].pos);
            } else {
                FastVecAdd(m + 0x10, m + 0x10, pv->v80);
            }
            if (pv->iE4 == -1
                || *(char **)((snd = (char *)g_sound_state + pv->iE4 * 0x70) + 0x88) != m
                || *(u8 *)(snd + 0x74) == 0) {
                pv->iE4 = snd_play_from_class_bank(0, 4, m, 0xD5C);
            }
            if (pv->iB8 != -1 && pv->iC8 == -1 && IsPointInCuboid(m + 0x10, pv->iB8) != 0) {
                if (pv->iE4 != -1) {
                    snd = (char *)g_sound_state + pv->iE4 * 0x70;
                    if (*(char **)(snd + 0x88) == m && *(u8 *)(snd + 0x74) != 0) {
                        snd_stop_voice(pv->iE4);
                    }
                }
                pv->iE4 = -1;
                if (*(s16 *)(m + 0xAA) == 0xD9B || *(s16 *)(m + 0xAA) == 0x11CF) {
                    moby_set_state(m, 5, -1);
                } else {
                    moby_set_state(m, 6, -1);
                }
            }
        }
        if (*(s16 *)(m + 0xAA) == 0xD9B) {
            matrix_mul_vec3(vm[0], g_train_offset_vector_a, m + 0xC0);
            FastVecAdd(vm[0], vm[0], m + 0x10);
            n = coll_process_hit(g_train_l18_hit_radius, vm[0], 0, m, 0);
            if (n != 0) {
                for (j = 0; j < n; j++) {
                    t = g_nearby_hit_targets[j];
                    if (t == ((Hero *)g_hero_state)->ptr[0x2290 / 4]) {
                        FastVecScale(vm[1], m + 0xC0, -g_train_push_speed_back);
                        vm[1][2] = g_train_push_speed_back * 4.0f;
                        vm[1][3] = 5627.9248f;
                        hero_l18_set_action(0, 1);
                        g = (f32)g_player_stats[0] * 30.0f;
                        part_queue_impact_effect(t, m, 0x10001, g_hero_state + 0x80, vm[1], g > 100.0f ? g : 100.0f);
                        pv->iE0 = (g_train_timer_start * 5 + 2) / 6;
                        SpawnExplosion(g_hero_state + 0x80, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                    } else {
                        FastVecScale(vm[1], m + 0xC0, g_train_push_speed_forward);
                        vm[1][3] = 5627.9248f;
                        vm[1][2] = g_train_push_speed_forward * 4.0f;
                        part_queue_impact_effect(t, m, 0x10001, t + 0x10, vm[1], 50.0f);
                    }
                }
            }
            part_spawn_upward(m);
            if (*(u8 *)(m + 0x31) != 0 && (g_frame_l18_counter & 0xF) == (((int)m >> 8) & 0xF)) {
                for (i = 0; i < g_train_flash_count; i++) {
                    matrix_mul_vec3(vm[1], g_train_offset_vector_b, m + 0xC0);
                    FastVecAdd(vm[1], vm[1], m + 0x10);
                    f = math_random_float_range(g_train_l18_speed_min, g_train_l18_speed_max) * 0.020000001f;
                    vec_scale_to_length(vm[2], m + 0xD0, math_random_int_below(2) != 0 ? -f : f);
                    vm[2][2] = math_random_float_range(-0.10000001f, 0.020000001f);
                    vm[2][3] = -0.012f;
                    part_spawn_white_flash(vm[1], vm[2], 0, math_random_float_range(g_train_flash_scale_min, g_train_flash_scale_max));
                }
            }
        }
        break;
    case 5:
        flag_set_first_pending(m);
        r = g_train_turn_angle * 0.0003490659f;
        pv->v80[2] = pv->v80[2] - g_train_sink_rate * 0.00040000002f;
        *(f32 *)(m + 0xF4) = FastAddRotations(*(f32 *)(m + 0xF4), r);
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 6:
        if (flag_set_first_pending(m) != 0) {
            *(u8 *)(m + 0xBC) = 0;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) |= 0x100;
            pv->fC0 = g_train_l18_value_low;
            matrix_mul_vec3(pv->v90, g_train_offset_vector_c, m + 0xC0);
            FastVecAdd(pv->v90, m + 0x10, pv->v90);
            vec_scale_to_length(pv->v80, m + 0xC0, g_train_speed_a * 0.020000001f);
            *(u16 *)(m + 0x34) |= 8;
            snd_play_from_class_bank(1, 0, m, 0xD5C);
            if (*(u8 *)(m + 0x31) != 0) {
                part_spawn_spray(m);
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            FastVecScale(m + 0xC0, m + 0xC0, g_train_l18_accel_by_video[g_is_pal_video[0] != 0] * 0.020000001f + 1.0f);
            pv->fC0 = g_train_l18_value_low + (g_train_l18_value_mid[0] - g_train_l18_value_low) * (IntToFloat(moby_timer(m)) / ((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f), g_train_color_table[0], g_train_color_table[1]);
            if (((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f) < (f32)moby_timer(m)) {
                *(u8 *)(m + 0xBC) = 1;
                vec_scale_to_length(pv->v80, m + 0xC0, g_train_speed_b * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 1) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f - g_train_l18_drag_by_video[g_is_pal_video[0] != 0] * 0.020000001f);
            pv->fC0 = g_train_l18_value_mid[0] + (g_train_l18_value_high[0] - g_train_l18_value_mid[0]) * (IntToFloat(moby_timer(m)) / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f), g_train_color_table[1], g_train_color_table[2]);
            *(u8 *)(m + 0x23) = FloatToInt((1.0f - IntToFloat(moby_timer(m)) / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f)) * 128.0f);
            if (g_train_phase_two_frames < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                if (pv->iBC != 0) {
                    pv->fD8 = 0.0f;
                    qcopy(m + 0x10, pv->v60);
                    qcopy(m + 0xF0, pv->v70);
                    moby_set_state(m, 7, -1);
                } else {
                    *(u16 *)(m + 0x34) &= ~0x100;
                    protopet_start_enter_anim(m, 1);
                }
            }
        }
        if (*(u8 *)(m + 0x31) != 0) {
            gfx_queue_draw_callback(g_train_draw_callback_b, m);
            gfx_queue_draw_callback(g_train_draw_callback_a, m);
            gfx_add_draw_callback_first(g_train_draw_callback_first, m);
        }
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 7:
        if (flag_set_first_pending(m) != 0) {
            *(u8 *)(m + 0xBC) = 1;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & ~1) | 0x100;
            pv->fC0 = g_train_l18_value_low;
            *(u8 *)(m + 0x23) = 0;
            for (i = 0; i < 3; i++) {
                vec_scale_to_length(vm[i], m + 0xC0 + i * 0x10, 1.0f);
            }
            matrix_mul_vec3(pv->v90, g_train_offset_vector_d, vm[0]);
            FastVecScale(pv->v90, pv->v90, IntToFloat(pv->iCC) + 1.0f);
            FastVecAdd(pv->v90, m + 0x10, pv->v90);
            vec_scale_to_length(pv->v80, m + 0xC0, (IntToFloat(pv->iCC) + 1.0f) * (0.020000001f * g_train_speed_by_video[g_is_pal_video[0] != 0]));
            *(u16 *)(m + 0x34) |= 8;
            if (*(u8 *)(m + 0x31) != 0) {
                part_spawn_spray(m);
            }
            snd_play_from_class_bank(1, 0, m, 0xD5C);
        } else if (*(u8 *)(m + 0xBC) == 1) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f / (1.0f - g_train_l18_drag_by_video[g_is_pal_video[0] != 0] * 0.020000001f));
            pv->fC0 = g_train_l18_value_high[0] + (g_train_l18_value_mid[0] - g_train_l18_value_high[0]) * (IntToFloat(moby_timer(m)) / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f), g_train_color_table[2], g_train_color_table[1]);
            *(u8 *)(m + 0x23) = FloatToInt(IntToFloat(moby_timer(m)) * 128.0f / ((g_train_phase_two_frames * 5.0f + 2.0f) / 6.0f));
            if (g_train_phase_two_frames < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                *(u8 *)(m + 0x23) = 0x80;
                *(u8 *)(m + 0xBC) = 0;
                *(u16 *)(m + 0x34) &= ~8;
                vec_scale_to_length(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            FastVecScale(m + 0xC0, m + 0xC0, 1.0f / (g_train_l18_accel_by_video[g_is_pal_video[0] != 0] * 0.020000001f + 1.0f));
            pv->fC0 = g_train_l18_value_mid[0] + (g_train_l18_value_low - g_train_l18_value_mid[0]) * (IntToFloat(moby_timer(m)) / ((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = FastTweenColor(IntToFloat(moby_timer(m)) / ((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f), g_train_color_table[1], g_train_color_table[0]);
            if (((g_train_phase_one_frames * 5.0f + 2.0f) / 6.0f) < (f32)moby_timer(m)) {
                *(u16 *)(m + 0x34) &= ~0x100;
                moby_set_state(m, 1, -1);
            }
        }
        if (pv->iE4 == -1
            || *(char **)((snd = (char *)g_sound_state + pv->iE4 * 0x70) + 0x88) != m
            || *(u8 *)(snd + 0x74) == 0) {
            pv->iE4 = snd_play_from_class_bank(0, 4, m, 0xD5C);
        }
        if (*(u8 *)(m + 0x31) != 0) {
            gfx_queue_draw_callback(g_train_draw_callback_b, m);
            gfx_queue_draw_callback(g_train_draw_callback_a, m);
            gfx_add_draw_callback_first(g_train_draw_callback_first, m);
        }
        FastVecAdd(m + 0x10, m + 0x10, pv->v80);
        break;
    case 2:
        if (pv->iD4 != -1 && coll_point_inside_region(g_camera_l18_position, pv->iD4) == 0) {
            rec = *(char **)(m + 0x24);
            st = *(u8 *)(m + 0x94);
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(u8 *)(m + 0x20) = st;
        }
        break;
    }
    FastVecSub(vm[0], m + 0x10, pos);
    mat_combine_and_store(pv->v20, vm[0], rot, m + 0xF0);
    if (*(f32 *)(m + 0x18) < 85.0f && *(u8 *)(m + 0x20) == 5) {
        SpawnExplosion(m + 0x10, 0, 5, 0, 5, 0x14, 0, 0, 4.0f, 0.0f, 1, 0, 0, 0);
        protopet_start_enter_anim(m, 1);
    }
    if (moby_timer(m) < 0xFFFF) {
        *(u16 *)(m + 0x96) = moby_timer(m) + 1;
    }
    
}
