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
extern GateObject *D_L10_001B1400 __attribute__((sda));
extern GateObject *D_L10_001B1404 __attribute__((sda));
extern char *D_L10_001B1408 __attribute__((sda));
extern float D_L10_001B140C __attribute__((sda)), D_L10_001B1410 __attribute__((sda));
extern int D_L10_001B1414 __attribute__((sda)), D_L10_001B1418 __attribute__((sda));
extern int D_L10_001B141C __attribute__((sda));
extern int D_L10_001B1434 __attribute__((sda));
extern int D_L10_001B3550 MACRO_ADDR;

typedef struct {
    char pad[0x2c];
    int field2c;
    char pad30[8];
    int field38;
} GateGlobals;

extern GateGlobals D_L10_00221CD0;
extern GatePath *D_L10_001FE340[];
extern char *D_L10_001B251C[] __attribute__((sda));
extern char D_L10_001B9680[];
extern int g_current_map_index;
extern unsigned char D_0019B278[];

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
extern void level_l00_call_module_handler_with_arg_9(void *, int);
extern void snd_play_from_class_bank(int, int, void *, int);
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
        D_L10_001B140C = -1;
        D_L10_001B1410 = -1;
        g_mission_initialized = 1;
        D_L10_001B1400 = 0;
        D_L10_001B1404 = 0;
        D_L10_001B1414 = 0;
        D_L10_001B1418 = 0;
        D_L10_001B141C = 0;
        D_L10_001B3550 = 0;
        D_L10_00221CD0.field2c = 0;
        music_Unpause();
        cloud_destroy_leftover_objects();
        if (D_L10_001B1408)
            moby_mark_spawned(D_L10_001B1408);
        entry_init_all_registered();
        D_L10_001B1408 = 0;
        hero_set_state_value_b(1);
        D_L10_00221CD0.field38 = *(int *)(vars + 0x20);
        hero_set_state_value_a(0);
        moby_list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (moby_list[i]->classId == 0xf82 /* moby class 3970 */)
                entry_spawn_list_objects_with_flag(moby_list[i], 1);
        }
        path = D_L10_001FE340[*(int *)(vars + 0x20)];
        while ((!D_L10_001B1400 || !D_L10_001B1404) && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                if (!D_L10_001B1400)
                    D_L10_001B1400 = gate;
                else
                    D_L10_001B1404 = gate;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                gate->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    if (!D_L10_001B1400 && !D_L10_001B1404 && !D_L10_001B1434) {
        hrugis_finish_mission_reward(controller, 3);
        return;
    }

    if (level_get_saved_value_b(level_find_object_by_class_id(0xf82 /* moby class 3970 */))) {
        D_L10_001B1434 = 1;
        if (math_fast_float_d((int *)(vars + 0x50))) {
            D_L10_001B1434 = 0;
            *(int *)(vars + 0x50) = 240;
            hrugis_reset_mission_state(controller);
            entry_init_all_registered();
        } else
            goto warning;
    } else if (D_L10_001B141C >= 12) {
        D_L10_001B1434 = 1;
        if (!math_fast_float_d((int *)(vars + 0x50))) {
        warning:
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x31de), -1);
        } else {
            D_L10_001B1434 = 0;
            hrugis_reset_mission_state(controller);
            entry_init_all_registered();
            *(int *)(vars + 0x50) = 240;
        }
    }

    if (D_L10_001B1434)
        return;
    D_L10_001B3550 = D_L10_001B3550 + 1;
    if (D_L10_001B3550 < 2)
        return;

    player = D_L10_001B251C[0] + (*(int *)(vars + 0x24) << 8);
    qcopy(&view_pos, D_L10_001B9680);
    FastVecSub(&to_view, &view_pos, &D_L10_001B1400->position);
    vec_scale_to_length(&to_view, &to_view, 1);
    FastVecSub(&to_player, player + 0x10, &D_L10_001B1400->position);
    vec_scale_to_length(&to_player, &to_player, 1);
    player_dot = FastVecDot(&D_L10_001B1400->forward, &to_player);
    view_dot = FastVecDot(&D_L10_001B1400->forward, &to_view);

    if ((player_dot != D_L10_001B140C && player_dot > 0) || (view_dot != D_L10_001B1410 && view_dot > 0)) {
        path = D_L10_001FE340[*(int *)(vars + 0x20)];
        if (fast_vec_dist(&view_pos, &D_L10_001B1400->position) <= 1.25f
            || fast_vec_dist(player + 0x10, &D_L10_001B1400->position) <= 1.25f) {
            snd_play_from_class_bank(15, 0, controller, 0xfbf);
            hero_add_clamped_stat(0.5f);
        } else {
            hero_add_clamped_stat(-0.75f);
            D_L10_001B141C++;
        }
        moby_mark_spawned(D_L10_001B1400);
        D_L10_001B1400 = D_L10_001B1404;
        D_L10_001B1404 = 0;
        while (!D_L10_001B1404 && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                D_L10_001B1404 = gate;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                gate->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    D_L10_001B140C = player_dot;
    D_L10_001B1410 = view_dot;

    if (D_L10_001B1400) {
        effect_set_enabled(D_L10_001B1400, 1);
        if (D_L10_001B1404)
            effect_set_color(D_L10_001B1400, 0x40008000);
        else
            effect_set_color(D_L10_001B1400, 0x4000c6ff);
    }

    if (D_L10_001B1404) {
        effect_set_enabled(D_L10_001B1404, 1);
        effect_set_color(D_L10_001B1404, 0x40808000);
    } else if (!D_L10_001B141C && !D_L10_001B1408 && !D_0019B278[g_current_map_index * 4]) {
        D_L10_001B1408 = pickup_spawn_if_not_taken(&D_L10_001B1400->position, 0, -1, -1);
    }
}
