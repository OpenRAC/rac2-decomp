/* func_US2_L15_00432BA8: path-marker course step of a Gorn stage object. Its own unit:
 * the $gp-relative state needs -G8, and retail clears the stack vector at 0($sp)
 * with a materialised por zero (-frac2-zero-ti-por). */
#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int pointCount; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase g_gorn_challenge_vars NOT_SDA;
extern PathRoute *g_path_l15_table[] NOT_SDA;
extern int g_gorn_course_timer MACRO_ADDR;
extern char *g_moby_base MACRO_ADDR;
extern PathVector g_camera_l15_position NOT_SDA;
extern int g_current_map_index;
extern unsigned char g_level_progress_flags[];
extern void music_Unpause(void), moby_mark_spawned(void *), entry_init_all_registered(void), hero_set_state_value_b(int), hero_set_state_value_a(int), entry_spawn_list_objects_with_flag(char *, int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void), level_get_saved_value_b(void *), math_fast_float_d(int *);
extern char *CreateMoby(int), *level_find_object_by_class_id(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void gorn_finish_challenge_stage_us2(void *, int), ResetGornStageCounters(void *);
extern char *GetLocalizedString(int);
extern void pad_set_raw_input_value(unsigned int);
extern void hero_add_clamped_stat(float), effect_set_enabled(void *, int), effect_set_color(void *, unsigned int);
extern int level_l00_call_module_handler_with_arg_9_us2(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *pickup_spawn_if_not_taken(void *, int, int, int);
extern int g_cutscene_l15_started_flag __attribute__((sda));
extern char * g_gorn_path_first_node __attribute__((sda));
extern char * g_gorn_path_next_node __attribute__((sda));
extern char * g_gorn_path_effect __attribute__((sda));
extern float g_gorn_old_hero_value __attribute__((sda));
extern float g_gorn_old_camera_value __attribute__((sda));
extern int g_gorn_course_progress_flag __attribute__((sda));
extern int g_gorn_course_marker_index __attribute__((sda));
extern int g_gorn_course_miss_count __attribute__((sda));
extern int g_gorn_path_waiting_flag __attribute__((sda));
/* Retail reads this counter absolutely and writes the same address via $gp: D_L15_001B3698 through a second small-data declaration. */
extern int D_L15_001B3698_1 __attribute__((sda));
void func_US2_L15_00432BA8(char *self)
{
    PathVector up, camera, fromHero, fromCamera;
    char *state = *(char **)(self + 0x68), *object, *hero;
    PathRoute *path;
    char **list;
    float heroDot, cameraDot;
    int n, i;
    unsigned short objectFlags;
    char *oldFirst;
    up.q = 0;
    up.f[2] = 1;
    if (!g_cutscene_l15_started_flag) {
        g_gorn_path_first_node = 0; g_gorn_path_next_node = 0;
        g_gorn_old_camera_value = g_gorn_old_hero_value = -1;
        g_cutscene_l15_started_flag = 1;
        g_gorn_course_progress_flag = 0; g_gorn_course_marker_index = 0; g_gorn_course_miss_count = 0;
        g_gorn_course_timer = 0; g_gorn_challenge_vars.reset = 0;
        music_Unpause();
        if (g_gorn_path_effect) moby_mark_spawned(g_gorn_path_effect);
        entry_init_all_registered(); g_gorn_path_effect = 0;
        hero_set_state_value_b(1);
        g_gorn_challenge_vars.route = *(int *)(state + 0x30);
        hero_set_state_value_a(0);
        list = level_get_object_list(); n = level_get_saved_value();
        for (i = 0; i < n; i++) if (*(short *)(list[i] + 0xAA) == 0xF82) entry_spawn_list_objects_with_flag(list[i], 1);
        path = g_path_l15_table[*(int *)(state + 0x30)];
        while ((!g_gorn_path_first_node || !g_gorn_path_next_node) && g_gorn_course_marker_index != path->pointCount) {
            if (path->point[g_gorn_course_marker_index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((unsigned char *)object)[0x30] = 0xFF;
            objectFlags = *(unsigned short *)(object + 0x34);
            oldFirst = g_gorn_path_first_node;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = objectFlags | 0x100;
            if (!oldFirst) g_gorn_path_first_node = object; else g_gorn_path_next_node = object;
            if (g_gorn_course_marker_index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[g_gorn_course_marker_index - 1], &path->point[g_gorn_course_marker_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[g_gorn_course_marker_index + 1], &path->point[g_gorn_course_marker_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[g_gorn_course_marker_index]);
            *(int *)(object + 0x1C) = 0;
            }
            g_gorn_course_marker_index++;
        }
    }
    if (!g_gorn_path_first_node && !g_gorn_path_next_node && !g_gorn_path_waiting_flag) { gorn_finish_challenge_stage_us2(self, 3); return; }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82))) {
        g_gorn_path_waiting_flag = 1;
        if (math_fast_float_d((int *)(state + 0x64))) { g_gorn_path_waiting_flag = 0; *(int *)(state + 0x64) = 240; ResetGornStageCounters(self); entry_init_all_registered(); }
        else { pad_set_raw_input_value(10); level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x3074), -1); }
    } else if (g_gorn_course_miss_count >= 12) {
        g_gorn_path_waiting_flag = 1;
        if (!math_fast_float_d((int *)(state + 0x64))) { pad_set_raw_input_value(10); level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x3074), -1); }
        else { g_gorn_path_waiting_flag = 0; *(int *)(state + 0x64) = 240; ResetGornStageCounters(self); entry_init_all_registered(); }
    }
    if (g_gorn_path_waiting_flag) return;
    D_L15_001B3698_1 = g_gorn_course_timer + 1;
    if (D_L15_001B3698_1 < 2) return;
    hero = g_moby_base + (*(int *)(state + 0x20) << 8);
    qcopy(&camera, &g_camera_l15_position);
    FastVecSub(&fromCamera, &camera, g_gorn_path_first_node + 0x10);
    vec_scale_to_length(&fromCamera, &fromCamera, 1);
    FastVecSub(&fromHero, hero + 0x10, g_gorn_path_first_node + 0x10);
    vec_scale_to_length(&fromHero, &fromHero, 1);
    heroDot = FastVecDot(g_gorn_path_first_node + 0xC0, &fromHero);
    cameraDot = FastVecDot(g_gorn_path_first_node + 0xC0, &fromCamera);
    if ((heroDot != g_gorn_old_hero_value && heroDot > 0) || (cameraDot != g_gorn_old_camera_value && cameraDot > 0)) {
        path = g_path_l15_table[*(int *)(state + 0x30)];
        if (fast_vec_dist(&camera, g_gorn_path_first_node + 0x10) <= 1.25f || fast_vec_dist(hero + 0x10, g_gorn_path_first_node + 0x10) <= 1.25f) {
            snd_play_from_class_bank(15, 0, self, 0xFBF); hero_add_clamped_stat(0.5f);
        } else { hero_add_clamped_stat(-0.75f); g_gorn_course_miss_count++; }
        moby_mark_spawned(g_gorn_path_first_node); g_gorn_path_first_node = g_gorn_path_next_node; g_gorn_path_next_node = 0;
        while (!g_gorn_path_next_node && g_gorn_course_marker_index != path->pointCount) {
            if (path->point[g_gorn_course_marker_index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            g_gorn_path_next_node = object;
            if (g_gorn_course_marker_index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[g_gorn_course_marker_index - 1], &path->point[g_gorn_course_marker_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[g_gorn_course_marker_index + 1], &path->point[g_gorn_course_marker_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[g_gorn_course_marker_index]);
            *(int *)(object + 0x1C) = 0;
            }
            g_gorn_course_marker_index++;
        }
    }
    g_gorn_old_hero_value = heroDot; g_gorn_old_camera_value = cameraDot;
    if (g_gorn_path_first_node) {
        effect_set_enabled(g_gorn_path_first_node, 1);
        if (g_gorn_path_next_node) effect_set_color(g_gorn_path_first_node, 0x40008000);
        else effect_set_color(g_gorn_path_first_node, 0x4000C6FF);
    }
    if (g_gorn_path_next_node) { effect_set_enabled(g_gorn_path_next_node, 1); effect_set_color(g_gorn_path_next_node, 0x40808000); }
    else if (!g_gorn_course_miss_count && !g_gorn_path_effect && !g_level_progress_flags[g_current_map_index * 4]) g_gorn_path_effect = pickup_spawn_if_not_taken(g_gorn_path_first_node + 0x10, 0, -1, -1);
}
