/* func_US2_L10_00426260, the v2.00 course step of Hrugis Cloud's path markers: the same C as
 * func_US2_L15_00432BA8 with this level's state offsets, its extra func_L10_00425798 call and
 * func_L10_00424528's order in the second expiry arm. Its own unit: the $gp-relative state
 * needs -G8, and retail clears the stack vector at 0($sp) with a materialised por zero
 * (-frac2-zero-ti-por). */
#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int pointCount; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase g_mission_state NOT_SDA;
extern PathRoute *g_gate_l10_path_table[] NOT_SDA;
extern int g_mission_time_value MACRO_ADDR;
extern char *g_moby_base_table MACRO_ADDR;
extern PathVector g_view_origin_vec NOT_SDA;
extern int g_current_map_index;
extern unsigned char g_level_progress_flags[];
extern void music_Unpause(void), cloud_destroy_leftover_objects(void), moby_mark_spawned(void *), entry_init_all_registered(void), hero_set_state_value_b(int), hero_set_state_value_a(int), entry_spawn_list_objects_with_flag(char *, int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void), level_get_saved_value_b(void *), math_fast_float_d(int *);
extern char *CreateMoby(int), *level_find_object_by_class_id(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void hrugis_finish_mission_reward_us2(void *, int), hrugis_reset_mission_state(void *);
extern char *GetLocalizedString(int);
extern void pad_set_raw_input_value(unsigned int);
extern void hero_add_clamped_stat(float), effect_set_enabled(void *, int), effect_set_color(void *, unsigned int);
extern int level_l00_call_module_handler_with_arg_9_us2(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *pickup_spawn_if_not_taken(void *, int, int, int);
extern int g_mission_initialized __attribute__((sda));
extern char * g_gate_first __attribute__((sda));
extern char * g_gate_second __attribute__((sda));
extern char * g_gate_pending_moby __attribute__((sda));
extern float g_gate_best_player_dot __attribute__((sda));
extern float g_gate_best_view_dot __attribute__((sda));
extern int g_gate_scan_start_index __attribute__((sda));
extern int g_gate_l10_path_index __attribute__((sda));
extern int g_gate_frame_counter __attribute__((sda));
extern int g_gate_search_flag __attribute__((sda));
/* Retail reads this counter absolutely and writes the same address via $gp: D_L10_001B3550 through a second small-data declaration. */
extern int D_L10_001B3550_1 __attribute__((sda));
void func_US2_L10_00426260(char *self)
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
    if (!g_mission_initialized) {
        g_gate_best_view_dot = g_gate_best_player_dot = -1;
        g_mission_initialized = 1;
        g_gate_first = 0; g_gate_second = 0;
        g_gate_scan_start_index = 0; g_gate_l10_path_index = 0; g_gate_frame_counter = 0;
        g_mission_time_value = 0; g_mission_state.reset = 0;
        music_Unpause();
        cloud_destroy_leftover_objects();
        if (g_gate_pending_moby) moby_mark_spawned(g_gate_pending_moby);
        entry_init_all_registered(); g_gate_pending_moby = 0;
        hero_set_state_value_b(1);
        g_mission_state.route = *(int *)(state + 0x20);
        hero_set_state_value_a(0);
        list = level_get_object_list(); n = level_get_saved_value();
        for (i = 0; i < n; i++) if (*(short *)(list[i] + 0xAA) == 0xF82) entry_spawn_list_objects_with_flag(list[i], 1);
        path = g_gate_l10_path_table[*(int *)(state + 0x20)];
        while ((!g_gate_first || !g_gate_second) && g_gate_l10_path_index != path->pointCount) {
            if (path->point[g_gate_l10_path_index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((unsigned char *)object)[0x30] = 0xFF;
            objectFlags = *(unsigned short *)(object + 0x34);
            oldFirst = g_gate_first;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = objectFlags | 0x100;
            if (!oldFirst) g_gate_first = object; else g_gate_second = object;
            if (g_gate_l10_path_index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[g_gate_l10_path_index - 1], &path->point[g_gate_l10_path_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[g_gate_l10_path_index + 1], &path->point[g_gate_l10_path_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[g_gate_l10_path_index]);
            *(int *)(object + 0x1C) = 0;
            }
            g_gate_l10_path_index++;
        }
    }
    if (!g_gate_first && !g_gate_second && !g_gate_search_flag) { hrugis_finish_mission_reward_us2(self, 3); return; }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82))) {
        g_gate_search_flag = 1;
        if (math_fast_float_d((int *)(state + 0x50))) { g_gate_search_flag = 0; *(int *)(state + 0x50) = 240; hrugis_reset_mission_state(self); entry_init_all_registered(); }
        else { pad_set_raw_input_value(10); level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x3074), -1); }
    } else if (g_gate_frame_counter >= 12) {
        g_gate_search_flag = 1;
        if (!math_fast_float_d((int *)(state + 0x50))) { pad_set_raw_input_value(10); level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x3074), -1); }
        else { g_gate_search_flag = 0; hrugis_reset_mission_state(self); entry_init_all_registered(); *(int *)(state + 0x50) = 240; }
    }
    if (g_gate_search_flag) return;
    D_L10_001B3550_1 = g_mission_time_value + 1;
    if (D_L10_001B3550_1 < 2) return;
    hero = g_moby_base_table + (*(int *)(state + 0x24) << 8);
    qcopy(&camera, &g_view_origin_vec);
    FastVecSub(&fromCamera, &camera, g_gate_first + 0x10);
    vec_scale_to_length(&fromCamera, &fromCamera, 1);
    FastVecSub(&fromHero, hero + 0x10, g_gate_first + 0x10);
    vec_scale_to_length(&fromHero, &fromHero, 1);
    heroDot = FastVecDot(g_gate_first + 0xC0, &fromHero);
    cameraDot = FastVecDot(g_gate_first + 0xC0, &fromCamera);
    if ((heroDot != g_gate_best_player_dot && heroDot > 0) || (cameraDot != g_gate_best_view_dot && cameraDot > 0)) {
        path = g_gate_l10_path_table[*(int *)(state + 0x20)];
        if (fast_vec_dist(&camera, g_gate_first + 0x10) <= 1.25f || fast_vec_dist(hero + 0x10, g_gate_first + 0x10) <= 1.25f) {
            snd_play_from_class_bank(15, 0, self, 0xFBF); hero_add_clamped_stat(0.5f);
        } else { hero_add_clamped_stat(-0.75f); g_gate_frame_counter++; }
        moby_mark_spawned(g_gate_first); g_gate_first = g_gate_second; g_gate_second = 0;
        while (!g_gate_second && g_gate_l10_path_index != path->pointCount) {
            if (path->point[g_gate_l10_path_index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            g_gate_second = object;
            if (g_gate_l10_path_index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[g_gate_l10_path_index - 1], &path->point[g_gate_l10_path_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[g_gate_l10_path_index + 1], &path->point[g_gate_l10_path_index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[g_gate_l10_path_index]);
            *(int *)(object + 0x1C) = 0;
            }
            g_gate_l10_path_index++;
        }
    }
    g_gate_best_player_dot = heroDot; g_gate_best_view_dot = cameraDot;
    if (g_gate_first) {
        effect_set_enabled(g_gate_first, 1);
        if (g_gate_second) effect_set_color(g_gate_first, 0x40008000);
        else effect_set_color(g_gate_first, 0x4000C6FF);
    }
    if (g_gate_second) { effect_set_enabled(g_gate_second, 1); effect_set_color(g_gate_second, 0x40808000); }
    else if (!g_gate_frame_counter && !g_gate_pending_moby && !g_level_progress_flags[g_current_map_index * 4]) g_gate_pending_moby = pickup_spawn_if_not_taken(g_gate_first + 0x10, 0, -1, -1);
}
