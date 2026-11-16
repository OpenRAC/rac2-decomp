#include "include_asm.h"

#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int point_count; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase g_gorn_challenge_vars NOT_SDA;
extern PathRoute *g_path_l15_table[] NOT_SDA;
extern int g_gorn_course_timer MACRO_ADDR;
extern char *g_moby_base MACRO_ADDR;
extern PathVector g_camera_l15_position NOT_SDA;
extern int g_current_map_index;
extern unsigned char g_level_progress_flags[];
extern void music_Unpause(void), moby_mark_spawned(void *), entry_init_all_registered(void), hero_set_state_value_b(int), hero_set_state_value_a(int), entry_spawn_list_objects_with_flag_pal(char *, int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void), level_get_saved_value_b(void *), math_fast_float_d(int *);
extern char *CreateMoby(int), *level_find_object_by_class_id(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void gorn_finish_challenge_stage_pal(void *, int), ResetGornStageCounters(void *);
extern char *GetLocalizedString(int);
extern void hero_add_clamped_stat(float), effect_set_enabled(void *, int), effect_set_color(void *, unsigned int);
extern int level_l00_call_module_handler_with_arg_9_pal(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *pickup_spawn_if_not_taken_pal(void *, int, int, int);
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
extern int D_L15_001B3698_1 __attribute__((sda));
#define init D_L15_001B1534
#define first D_L15_001B1584
#define next D_L15_001B1588
#define effect D_L15_001B158C
#define oldHero D_L15_001B1590
#define oldCamera D_L15_001B1594
#define index D_L15_001B159C
#define misses D_L15_001B15A4
#define waiting D_L15_001B15C0
#define count D_L15_001B3698_1

/* Gorn path challenge: lays out ring markers along a route, scores the hero and camera passing each one, and ends the stage when they run out. */
void gorn_path_marker_course_update_pal(char *self)
{
    PathVector up, camera, from_hero, from_camera;
    char *state = *(char **)(self + 0x68), *object, *hero;
    PathRoute *path;
    char **list;
    float hero_dot, camera_dot;
    int n, i;
    unsigned short object_flags;
    char *old_first;
    up.q = 0;
    up.f[2] = 1;
    if (!init) {
        first = 0; next = 0;
        oldCamera = oldHero = -1;
        init = 1;
        g_gorn_course_progress_flag = 0; index = 0; misses = 0;
        g_gorn_course_timer = 0; g_gorn_challenge_vars.reset = 0;
        music_Unpause();
        if (effect) moby_mark_spawned(effect);
        entry_init_all_registered(); effect = 0;
        hero_set_state_value_b(1);
        g_gorn_challenge_vars.route = *(int *)(state + 0x30);
        hero_set_state_value_a(0);
        list = level_get_object_list(); n = level_get_saved_value();
        for (i = 0; i < n; i++) if (*(short *)(list[i] + 0xAA) == 0xF82) entry_spawn_list_objects_with_flag_pal(list[i], 1);
        path = g_path_l15_table[*(int *)(state + 0x30)];
        while ((!first || !next) && index != path->point_count) {
            if (path->point[index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((unsigned char *)object)[0x30] = 0xFF;
            object_flags = *(unsigned short *)(object + 0x34);
            old_first = first;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = object_flags | 0x100;
            if (!old_first) first = object; else next = object;
            if (index == path->point_count - 1) {
                FastVecSub(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    if (!first && !next && !waiting) { gorn_finish_challenge_stage_pal(self, 3); return; }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82))) {
        waiting = 1;
        if (math_fast_float_d((int *)(state + 0x64))) { waiting = 0; *(int *)(state + 0x64) = 200; ResetGornStageCounters(self); entry_init_all_registered(); }
        else level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10F6), -1);
    } else if (misses >= 12) {
        waiting = 1;
        if (!math_fast_float_d((int *)(state + 0x64))) level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10F6), -1);
        else { waiting = 0; *(int *)(state + 0x64) = 200; ResetGornStageCounters(self); entry_init_all_registered(); }
    }
    if (waiting) return;
    count = g_gorn_course_timer + 1;
    if (count < 2) return;
    hero = g_moby_base + (*(int *)(state + 0x20) << 8);
    qcopy(&camera, &g_camera_l15_position);
    FastVecSub(&from_camera, &camera, first + 0x10);
    vec_scale_to_length(&from_camera, &from_camera, 1);
    FastVecSub(&from_hero, hero + 0x10, first + 0x10);
    vec_scale_to_length(&from_hero, &from_hero, 1);
    hero_dot = FastVecDot(first + 0xC0, &from_hero);
    camera_dot = FastVecDot(first + 0xC0, &from_camera);
    if ((hero_dot != oldHero && hero_dot > 0) || (camera_dot != oldCamera && camera_dot > 0)) {
        path = g_path_l15_table[*(int *)(state + 0x30)];
        if (fast_vec_dist(&camera, first + 0x10) <= 1.25f || fast_vec_dist(hero + 0x10, first + 0x10) <= 1.25f) {
            snd_play_from_class_bank(15, 0, self, 0xFBF); hero_add_clamped_stat(0.5f);
        } else { hero_add_clamped_stat(-0.75f); misses++; }
        moby_mark_spawned(first); first = next; next = 0;
        while (!next && index != path->point_count) {
            if (path->point[index].f[3] != -1) {
            object = CreateMoby(0x114A);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            next = object;
            if (index == path->point_count - 1) {
                FastVecSub(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    oldHero = hero_dot; oldCamera = camera_dot;
    if (first) {
        effect_set_enabled(first, 1);
        if (next) effect_set_color(first, 0x40008000);
        else effect_set_color(first, 0x4000C6FF);
    }
    if (next) { effect_set_enabled(next, 1); effect_set_color(next, 0x40808000); }
    else if (!misses && !effect && !g_level_progress_flags[g_current_map_index * 4]) effect = pickup_spawn_if_not_taken_pal(first + 0x10, 0, -1, -1);
}
