#include "common.h"

/* Needs -frac2-zero-ti-por for the quadword clear of the up vector (config/cflags.txt). */

typedef int GateQuad __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    } v;
    GateQuad q;
} GateVec;

typedef struct GatePath {
    int count;
    char pad04[12];
    GateVec points[0];
} GatePath;

typedef struct GateObject {
    char pad00[0x10];
    GateVec position;
    char pad20[0x10];
    u8 opacity, pad31;
    u16 drawFlags, flags;
    char pad36[0x32];
    void *state;
    char pad6c[0x3e];
    short classId;
    char padac[0x14];
    GateVec forward, right, up;
} GateObject;

extern int g_mission_initialized __attribute__((sda));
extern GateObject *g_gate_first __attribute__((sda));
extern GateObject *g_gate_second __attribute__((sda));
extern char *g_gate_pending_moby __attribute__((sda));
extern float g_gate_best_player_dot __attribute__((sda)), g_gate_best_view_dot __attribute__((sda));
extern int g_gate_scan_start_index __attribute__((sda)), g_gate_l10_path_index __attribute__((sda));
extern int g_gate_frame_counter __attribute__((sda));
extern int g_gate_search_flag __attribute__((sda));
extern int g_mission_time_value MACRO_ADDR;

typedef struct {
    char pad[0x2c];
    int field2c;
    char pad30[8];
    int field38;
} GateGlobals;

extern GateGlobals g_mission_state;
extern GatePath *g_gate_l10_path_table[];
extern char *g_moby_base_table[] __attribute__((sda));
extern char g_view_origin_vec[];
extern int g_current_map_index;
extern unsigned char g_level_progress_flags[];

extern void music_Unpause(void), cloud_destroy_leftover_objects(void), entry_init_all_registered(void);
extern void hero_set_state_value_b(int), hero_set_state_value_a(int);
extern GateObject **level_get_object_list(void);
extern int level_get_saved_value(void);
extern GateObject *level_find_object_by_class_id(int);
extern int level_get_saved_value_b(void *);
extern void entry_spawn_list_objects_with_flag(void *, int);
extern GateObject *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void hrugis_finish_mission_reward(void *, int), hrugis_reset_mission_state(void *);
extern int math_fast_float_d(int *);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void hero_add_clamped_stat(float);
extern void effect_set_enabled(void *, int), effect_set_color(void *, int);
extern char *pickup_spawn_if_not_taken(void *, int, int, int);

/* Runs the gate course: keeps the next two gate markers ahead, scores the player when passing
   through one and shows a warning after too many misses. */
void UpdateGateCourse(GateObject *controller)
{
    GateVec up, view_pos, to_player, to_view;
    char *vars = controller->state, *player;
    GatePath *path;
    GateObject *gate;
    GateObject **moby_list;
    int count, i;
    float player_dot, view_dot;

    up.q = 0;
    up.v.z = 1;

    if (!g_mission_initialized) {
        g_gate_best_player_dot = -1;
        g_gate_best_view_dot = -1;
        g_mission_initialized = 1;
        g_gate_first = 0;
        g_gate_second = 0;
        g_gate_scan_start_index = 0;
        g_gate_l10_path_index = 0;
        g_gate_frame_counter = 0;
        g_mission_time_value = 0;
        g_mission_state.field2c = 0;
        music_Unpause();
        cloud_destroy_leftover_objects();
        if (g_gate_pending_moby)
            moby_mark_spawned(g_gate_pending_moby);
        entry_init_all_registered();
        g_gate_pending_moby = 0;
        hero_set_state_value_b(1);
        g_mission_state.field38 = *(int *)(vars + 0x20);
        hero_set_state_value_a(0);
        moby_list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (moby_list[i]->classId == 0xf82 /* moby class 3970 */)
                entry_spawn_list_objects_with_flag(moby_list[i], 1);
        }
        path = g_gate_l10_path_table[*(int *)(vars + 0x20)];
        while ((!g_gate_first || !g_gate_second) && g_gate_l10_path_index != path->count) {
            if (path->points[g_gate_l10_path_index].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                if (!g_gate_first)
                    g_gate_first = gate;
                else
                    g_gate_second = gate;
                if (g_gate_l10_path_index == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + g_gate_l10_path_index * 16,
                                  (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (g_gate_l10_path_index * 16 + 0x20),
                                  (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                gate->position.v.w = 0;
            }
            g_gate_l10_path_index++;
        }
    }

    if (!g_gate_first && !g_gate_second && !g_gate_search_flag) {
        hrugis_finish_mission_reward(controller, 3);
        return;
    }

    if (level_get_saved_value_b(level_find_object_by_class_id(0xf82 /* moby class 3970 */))) {
        g_gate_search_flag = 1;
        if (math_fast_float_d((int *)(vars + 0x50))) {
            g_gate_search_flag = 0;
            *(int *)(vars + 0x50) = 240;
            hrugis_reset_mission_state(controller);
            entry_init_all_registered();
        } else
            goto warning;
    } else if (g_gate_frame_counter >= 12) {
        g_gate_search_flag = 1;
        if (!math_fast_float_d((int *)(vars + 0x50))) {
        warning:
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x31de), -1);
        } else {
            g_gate_search_flag = 0;
            hrugis_reset_mission_state(controller);
            entry_init_all_registered();
            *(int *)(vars + 0x50) = 240;
        }
    }

    if (g_gate_search_flag)
        return;
    g_mission_time_value = g_mission_time_value + 1;
    if (g_mission_time_value < 2)
        return;

    player = g_moby_base_table[0] + (*(int *)(vars + 0x24) << 8);
    qcopy(&view_pos, g_view_origin_vec);
    FastVecSub(&to_view, &view_pos, &g_gate_first->position);
    vec_scale_to_length(&to_view, &to_view, 1);
    FastVecSub(&to_player, player + 0x10, &g_gate_first->position);
    vec_scale_to_length(&to_player, &to_player, 1);
    player_dot = FastVecDot(&g_gate_first->forward, &to_player);
    view_dot = FastVecDot(&g_gate_first->forward, &to_view);

    if ((player_dot != g_gate_best_player_dot && player_dot > 0) || (view_dot != g_gate_best_view_dot && view_dot > 0)) {
        path = g_gate_l10_path_table[*(int *)(vars + 0x20)];
        if (fast_vec_dist(&view_pos, &g_gate_first->position) <= 1.25f
            || fast_vec_dist(player + 0x10, &g_gate_first->position) <= 1.25f) {
            snd_play_from_class_bank(15, 0, controller, 0xfbf);
            hero_add_clamped_stat(0.5f);
        } else {
            hero_add_clamped_stat(-0.75f);
            g_gate_frame_counter++;
        }
        moby_mark_spawned(g_gate_first);
        g_gate_first = g_gate_second;
        g_gate_second = 0;
        while (!g_gate_second && g_gate_l10_path_index != path->count) {
            if (path->points[g_gate_l10_path_index].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                g_gate_second = gate;
                if (g_gate_l10_path_index == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + g_gate_l10_path_index * 16,
                                  (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (g_gate_l10_path_index * 16 + 0x20),
                                  (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (g_gate_l10_path_index * 16 + 0x10));
                gate->position.v.w = 0;
            }
            g_gate_l10_path_index++;
        }
    }

    g_gate_best_player_dot = player_dot;
    g_gate_best_view_dot = view_dot;

    if (g_gate_first) {
        effect_set_enabled(g_gate_first, 1);
        if (g_gate_second)
            effect_set_color(g_gate_first, 0x40008000);
        else
            effect_set_color(g_gate_first, 0x4000c6ff);
    }

    if (g_gate_second) {
        effect_set_enabled(g_gate_second, 1);
        effect_set_color(g_gate_second, 0x40808000);
    } else if (!g_gate_frame_counter && !g_gate_pending_moby && !g_level_progress_flags[g_current_map_index * 4]) {
        g_gate_pending_moby = pickup_spawn_if_not_taken(&g_gate_first->position, 0, -1, -1);
    }
}
