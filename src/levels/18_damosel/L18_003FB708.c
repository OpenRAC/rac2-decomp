/* Per-frame update of the grelbin-style effect moby (L18, L19 and L20): a seven-state switch that
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
extern int D_001A7A00[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern char g_camera_l18_position[];
extern char *D_L18_001FE480[];
extern ClassRec *g_moby_l18_table[] __attribute__((sda));
extern char *g_nearby_hit_targets[];
extern f32 D_L18_001B06AC[] __attribute__((sda));
extern f32 D_L18_001B06B0[] __attribute__((sda));
extern f32 D_L18_001B05E0 __attribute__((sda));
extern f32 D_L18_001B05E4 __attribute__((sda));
extern f32 D_L18_001B05F0[4] __attribute__((sda));
extern f32 D_L18_001B0600 __attribute__((sda));
extern f32 D_L18_001B0604 __attribute__((sda));
extern f32 D_L18_001B0608 __attribute__((sda));
extern int D_L18_001B060C __attribute__((sda));
extern f32 D_L18_001B0620[4] __attribute__((sda));
extern int D_L18_001B0630 __attribute__((sda));
extern f32 D_L18_001B0634 __attribute__((sda));
extern f32 D_L18_001B0638 __attribute__((sda));
extern f32 D_L18_001B063C __attribute__((sda));
extern f32 D_L18_001B0640 __attribute__((sda));
extern f32 D_L18_001B0644 __attribute__((sda));
extern f32 D_L18_001B0648 __attribute__((sda));
extern f32 D_L18_001B0650[2] __attribute__((sda));
extern f32 D_L18_001B0658[2] __attribute__((sda));
extern f32 D_L18_001B0660 __attribute__((sda));
extern f32 D_L18_001B0668[2] __attribute__((sda));
extern f32 D_L18_001B0670 __attribute__((sda));
extern f32 D_L18_001B0680[4] __attribute__((sda));
extern f32 D_L18_001B0690[4] __attribute__((sda));
extern f32 D_L18_001B06A8 __attribute__((sda));
extern int D_L18_001B06B8[] __attribute__((sda));
extern int D_L18_001B2348 __attribute__((sda));
extern char D_L18_003FD630[];
extern char D_L18_003FCA38[];
extern char D_L18_003FD730[];

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

/* Updates the train: it rides its rail path or follows another object, speeds up
   and slows down, falls when released, and plays its sounds and effects. */
void train_l18_update(char *moby)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 vm[3][4] __attribute__((aligned(16)));
    PvVars *vars;
    char *path;
    char *rec;
    ClassRec *class_table;
    ClassRec *class_table2;
    char *src;
    char *sound;
    char *target;
    int hit_count;
    int i;
    int k;
    int parent_index;
    int saved_state;
    int j;
    float f;
    float g;
    float r;

    vars = *(PvVars **)(moby + 0x68);
    qcopy(pos, moby + 0x10);
    qcopy(rot, moby + 0xF0);
    if (vars->iD4 != -1 && coll_point_inside_region(g_camera_l18_position, vars->iD4) != 0) {
        protopet_start_enter_anim(moby, 0);
    }
    if (vars->iE0 > 0) {
        math_fast_float_d(&vars->iE0);
        if (vars->iE0 < 2) {
            hero_record_play_counters();
        }
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        qcopy(vars->v60, moby + 0x10);
        qcopy(vars->v70, moby + 0xF0);
        if (vars->iB0 != -1) {
            vars->fD8 = 0.0f;
            path = D_L18_001FE480[vars->iB0];
            r = 1.0f / fast_vec_dist(path + 0x10, path + 0x20);
            vars->fDC = r * (0.016666668f * vars->fD0);
            qcopy(moby + 0x10, path + 0x10);
            vars->iE0 = -1;
        }
        if (*(s16 *)(moby + 0xAA) != MOBY_CLASS_TRAIN && *(s16 *)(moby + 0xAA) != 0x11CF /* moby class 4559 */) {
            vars->i8 = 0;
        }
        if (vars->iC8 != -1) {
            FastVecSub(vars->vA0, moby + 0x10, g_moby_l18_table[0][vars->iC8].pos);
            mat_fast_helper_c(vm[0], (float *)g_moby_l18_table[0][vars->iC8].mat);
            matrix_mul_vec3(vars->vA0, vars->vA0, vm[0]);
        }
        if (vars->iB4 != -1) {
            *(u16 *)(moby + 0x34) |= 1;
            moby_set_state(moby, 4, -1);
        } else {
            moby_set_state(moby, 1, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby) != 0) {
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (IsPointInCuboid(g_hero_state + 0x80, vars->iB4) != 0) {
            if (vars->iC8 == -1) {
                *(u16 *)(moby + 0x34) |= 0x100;
                vec_scale_to_length(moby + 0xC0, moby + 0xC0, 0.03234f);
                moby_set_state(moby, 7, -1);
            } else {
                moby_set_state(moby, 1, -1);
            }
        }
        break;
    case 1:
        if (flag_set_first_pending(moby) != 0) {
            vec_scale_to_length(vars->v80, moby + 0xC0, vars->fD0 * 0.016666668f);
        }
        if (vars->iB0 != -1) {
            path_sample_position(D_L18_001FE480[vars->iB0], 0, moby + 0x10, moby + 0xF0, 0, vars->fD8);
            vars->fD8 = vars->fD8 + vars->fDC;
        } else {
            if (vars->iC8 != -1) {
                class_table = g_moby_l18_table[0];
                *(u16 *)(moby + 0x34) = class_table[vars->iC8].h34;
                *(u8 *)(moby + 0x23) = class_table[vars->iC8].b23;
                class_table2 = g_moby_l18_table[0];
                *(u16 *)(moby + 0x34) = class_table2[vars->iC8].h34;
                *(int *)(moby + 0x98) = class_table2[vars->iC8].i98;
                parent_index = vars->iC8;
                for (k = 0; k < 4; k++) {
                    qcopy(moby + 0xC0 + k * 16, class_table2[parent_index].mat[k]);
                }
                matrix_mul_vec3(vm[0], vars->vA0, moby + 0xC0);
                FastVecAdd(moby + 0x10, vm[0], g_moby_l18_table[0][vars->iC8].pos);
            } else {
                FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
            }
            if (vars->iE4 == -1
                || *(char **)((sound = (char *)g_sound_state + vars->iE4 * 0x70) + 0x88) != moby
                || *(u8 *)(sound + 0x74) == 0) {
                vars->iE4 = snd_play_from_class_bank(0, 4, moby, 0xD5C);
            }
            if (vars->iB8 != -1 && vars->iC8 == -1 && IsPointInCuboid(moby + 0x10, vars->iB8) != 0) {
                if (vars->iE4 != -1) {
                    sound = (char *)g_sound_state + vars->iE4 * 0x70;
                    if (*(char **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0) {
                        snd_stop_voice(vars->iE4);
                    }
                }
                vars->iE4 = -1;
                if (*(s16 *)(moby + 0xAA) == MOBY_CLASS_TRAIN || *(s16 *)(moby + 0xAA) == 0x11CF /* moby class 4559 */) {
                    moby_set_state(moby, 5, -1);
                } else {
                    moby_set_state(moby, 6, -1);
                }
            }
        }
        if (*(s16 *)(moby + 0xAA) == MOBY_CLASS_TRAIN) {
            matrix_mul_vec3(vm[0], D_L18_001B05F0, moby + 0xC0);
            FastVecAdd(vm[0], vm[0], moby + 0x10);
            hit_count = coll_process_hit(D_L18_001B0600, vm[0], 0, moby, 0);
            if (hit_count != 0) {
                for (j = 0; j < hit_count; j++) {
                    target = g_nearby_hit_targets[j];
                    if (target == ((Hero *)g_hero_state)->ptr[0x2290 / 4]) {
                        FastVecScale(vm[1], moby + 0xC0, -D_L18_001B0608);
                        vm[1][2] = D_L18_001B0608 * 4.0f;
                        vm[1][3] = 5627.9248f;
                        hero_l18_set_action(0, 1);
                        g = (f32)D_001A7A00[0] * 30.0f;
                        part_queue_impact_effect(target, moby, 0x10001, g_hero_state + 0x80, vm[1], g > 100.0f ? g : 100.0f);
                        vars->iE0 = D_L18_001B060C;
                        SpawnExplosion(g_hero_state + 0x80, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                    } else {
                        FastVecScale(vm[1], moby + 0xC0, D_L18_001B0604);
                        vm[1][3] = 5627.9248f;
                        vm[1][2] = D_L18_001B0604 * 4.0f;
                        part_queue_impact_effect(target, moby, 0x10001, target + 0x10, vm[1], 50.0f);
                    }
                }
            }
            part_spawn_upward(moby);
            if (*(u8 *)(moby + 0x31) != 0 && (D_L18_001B2348 & 0xF) == (((int)moby >> 8) & 0xF)) {
                for (i = 0; i < D_L18_001B0630; i++) {
                    matrix_mul_vec3(vm[1], D_L18_001B0620, moby + 0xC0);
                    FastVecAdd(vm[1], vm[1], moby + 0x10);
                    f = math_random_float_range(D_L18_001B063C, D_L18_001B0640) * 0.016666668f;
                    vec_scale_to_length(vm[2], moby + 0xD0, math_random_int_below(2) != 0 ? -f : f);
                    vm[2][2] = math_random_float_range(-0.083333336f, 0.016666668f);
                    vm[2][3] = -0.008333334f;
                    part_spawn_white_flash(vm[1], vm[2], 0, math_random_float_range(D_L18_001B0634, D_L18_001B0638));
                }
            }
        }
        break;
    case 5:
        flag_set_first_pending(moby);
        r = D_L18_001B05E4 * 0.00029088825f;
        vars->v80[2] = vars->v80[2] - D_L18_001B05E0 * 0.00027777778f;
        *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4), r);
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 6:
        if (flag_set_first_pending(moby) != 0) {
            *(u8 *)(moby + 0xBC) = 0;
            *(u16 *)(moby + 0x96) = 0;
            *(u16 *)(moby + 0x34) |= 0x100;
            vars->fC0 = D_L18_001B06A8;
            matrix_mul_vec3(vars->v90, D_L18_001B0680, moby + 0xC0);
            FastVecAdd(vars->v90, moby + 0x10, vars->v90);
            vec_scale_to_length(vars->v80, moby + 0xC0, D_L18_001B0644 * 0.016666668f);
            *(u16 *)(moby + 0x34) |= 8;
            snd_play_from_class_bank(1, 0, moby, 0xD5C);
            if (*(u8 *)(moby + 0x31) != 0) {
                part_spawn_spray(moby);
            }
        } else if (*(u8 *)(moby + 0xBC) == 0) {
            FastVecScale(moby + 0xC0, moby + 0xC0, D_L18_001B0658[g_is_pal_video[0] != 0] * 0.016666668f + 1.0f);
            vars->fC0 = D_L18_001B06A8 + (D_L18_001B06AC[0] - D_L18_001B06A8) * (IntToFloat(moby_timer(moby)) / D_L18_001B0660);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0660, D_L18_001B06B8[0], D_L18_001B06B8[1]);
            if (D_L18_001B0660 < (f32)moby_timer(moby)) {
                *(u8 *)(moby + 0xBC) = 1;
                vec_scale_to_length(vars->v80, moby + 0xC0, D_L18_001B0648 * 0.016666668f);
                *(u16 *)(moby + 0x96) = 0;
            }
        } else if (*(u8 *)(moby + 0xBC) == 1) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f - D_L18_001B0668[g_is_pal_video[0] != 0] * 0.016666668f);
            vars->fC0 = D_L18_001B06AC[0] + (D_L18_001B06B0[0] - D_L18_001B06AC[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0670);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0670, D_L18_001B06B8[1], D_L18_001B06B8[2]);
            *(u8 *)(moby + 0x23) = FloatToInt((1.0f - IntToFloat(moby_timer(moby)) / D_L18_001B0670) * 128.0f);
            if (D_L18_001B0670 < (f32)moby_timer(moby) || *(f32 *)(moby + 0xE8) < 0.0f) {
                if (vars->iBC != 0) {
                    vars->fD8 = 0.0f;
                    qcopy(moby + 0x10, vars->v60);
                    qcopy(moby + 0xF0, vars->v70);
                    moby_set_state(moby, 7, -1);
                } else {
                    *(u16 *)(moby + 0x34) &= ~0x100;
                    protopet_start_enter_anim(moby, 1);
                }
            }
        }
        if (*(u8 *)(moby + 0x31) != 0) {
            gfx_queue_draw_callback(D_L18_003FD630, moby);
            gfx_queue_draw_callback(D_L18_003FCA38, moby);
            gfx_add_draw_callback_first(D_L18_003FD730, moby);
        }
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 7:
        if (flag_set_first_pending(moby) != 0) {
            *(u8 *)(moby + 0xBC) = 1;
            *(u16 *)(moby + 0x96) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & ~1) | 0x100;
            vars->fC0 = D_L18_001B06A8;
            *(u8 *)(moby + 0x23) = 0;
            for (i = 0; i < 3; i++) {
                vec_scale_to_length(vm[i], moby + 0xC0 + i * 0x10, 1.0f);
            }
            matrix_mul_vec3(vars->v90, D_L18_001B0690, vm[0]);
            FastVecScale(vars->v90, vars->v90, IntToFloat(vars->iCC) + 1.0f);
            FastVecAdd(vars->v90, moby + 0x10, vars->v90);
            vec_scale_to_length(vars->v80, moby + 0xC0, (IntToFloat(vars->iCC) + 1.0f) * (0.016666668f * D_L18_001B0650[g_is_pal_video[0] != 0]));
            *(u16 *)(moby + 0x34) |= 8;
            if (*(u8 *)(moby + 0x31) != 0) {
                part_spawn_spray(moby);
            }
            snd_play_from_class_bank(1, 0, moby, 0xD5C);
        } else if (*(u8 *)(moby + 0xBC) == 1) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f / (1.0f - D_L18_001B0668[g_is_pal_video[0] != 0] * 0.016666668f));
            vars->fC0 = D_L18_001B06B0[0] + (D_L18_001B06AC[0] - D_L18_001B06B0[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0670);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0670, D_L18_001B06B8[2], D_L18_001B06B8[1]);
            *(u8 *)(moby + 0x23) = FloatToInt(IntToFloat(moby_timer(moby)) * 128.0f / D_L18_001B0670);
            if (D_L18_001B0670 < (f32)moby_timer(moby) || *(f32 *)(moby + 0xE8) < 0.0f) {
                *(u8 *)(moby + 0x23) = 0x80;
                *(u8 *)(moby + 0xBC) = 0;
                *(u16 *)(moby + 0x34) &= ~8;
                vec_scale_to_length(vars->v80, moby + 0xC0, vars->fD0 * 0.016666668f);
                *(u16 *)(moby + 0x96) = 0;
            }
        } else if (*(u8 *)(moby + 0xBC) == 0) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f / (D_L18_001B0658[g_is_pal_video[0] != 0] * 0.016666668f + 1.0f));
            vars->fC0 = D_L18_001B06AC[0] + (D_L18_001B06A8 - D_L18_001B06AC[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0660);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0660, D_L18_001B06B8[1], D_L18_001B06B8[0]);
            if (D_L18_001B0660 < (f32)moby_timer(moby)) {
                *(u16 *)(moby + 0x34) &= ~0x100;
                moby_set_state(moby, 1, -1);
            }
        }
        if (vars->iE4 == -1
            || *(char **)((sound = (char *)g_sound_state + vars->iE4 * 0x70) + 0x88) != moby
            || *(u8 *)(sound + 0x74) == 0) {
            vars->iE4 = snd_play_from_class_bank(0, 4, moby, 0xD5C);
        }
        if (*(u8 *)(moby + 0x31) != 0) {
            gfx_queue_draw_callback(D_L18_003FD630, moby);
            gfx_queue_draw_callback(D_L18_003FCA38, moby);
            gfx_add_draw_callback_first(D_L18_003FD730, moby);
        }
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 2:
        if (vars->iD4 != -1 && coll_point_inside_region(g_camera_l18_position, vars->iD4) == 0) {
            rec = *(char **)(moby + 0x24);
            saved_state = *(u8 *)(moby + 0x94);
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(moby + 0x98) = *(int *)(rec + 0x10);
            *(int *)(moby + 0x98) = *(int *)(rec + 0x10);
            *(u8 *)(moby + 0x20) = saved_state;
        }
        break;
    }
    FastVecSub(vm[0], moby + 0x10, pos);
    mat_combine_and_store(vars->v20, vm[0], rot, moby + 0xF0);
    if (*(f32 *)(moby + 0x18) < 85.0f && *(u8 *)(moby + 0x20) == 5) {
        SpawnExplosion(moby + 0x10, 0, 5, 0, 5, 0x14, 0, 0, 4.0f, 0.0f, 1, 0, 0, 0);
        protopet_start_enter_anim(moby, 1);
    }
    if (moby_timer(moby) < 0xFFFF) {
        *(u16 *)(moby + 0x96) = moby_timer(moby) + 1;
    }
    
}
