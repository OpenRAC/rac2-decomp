#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; s32 i[4]; } Vec;
typedef struct {
    u8 pad00[0x10];
    Vec position;
    u8 pad20[0x10];
    u8 opacity;
    u8 pad31;
    s16 mode;
    u16 flags;
    u8 pad36[0x8A];
    Vec forward;
    Vec right;
    Vec up;
} GateMoby;
typedef struct { s32 count; s32 pad04[3]; Vec points[1]; } GatePath;
typedef struct { s32 count; u8 pad04[0x28]; s32 reset; u8 pad30[8]; s32 path; } FeltzinState;
extern s32 g_feltzin_challenge_active __attribute__((sda));
extern GateMoby *g_feltzin_record_a __attribute__((sda));
extern GateMoby *g_feltzin_record_b __attribute__((sda));
extern s32 g_feltzin_record_c __attribute__((sda));
extern f32 g_feltzin_best_dot_player __attribute__((sda));
extern f32 g_feltzin_best_dot_other __attribute__((sda));
extern s32 g_feltzin_gate_flag __attribute__((sda));
extern s32 g_feltzin_path_index __attribute__((sda));
extern s32 g_feltzin_countdown_timer __attribute__((sda));
extern s32 g_feltzin_failure_flag __attribute__((sda));
extern u8 g_feltzin_timer[] MACRO_ADDR;
extern FeltzinState g_feltzin_challenge_state;
extern u8 g_origin_vec[];
extern GatePath *g_gate_l05_path_table[];
extern u8 *g_feltzin_target_mobys;
extern s32 g_current_map_index;
extern u8 g_level_progress_flags[];
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_b(s32 a0);
extern void hero_set_state_value_a(s32 a0);
extern void moby_mark_spawned(void *moby);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern GateMoby *CreateMoby(s32 oclass);
extern u8 *level_find_object_by_class_id(s32 a0);
extern s32 level_get_saved_value_b(u8 *a0);
extern void UpdateFeltzinMissionReward_us2(u8 *actor, s32 mission);
extern void func_US2_L05_00422780(u8 *a0, s32 a1);
extern void FastVecSub(void *dst, void *a, void *b);
extern void FastVecCross(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, f32 scale);
extern f32 FastVecDot(void *a, void *b);
extern f32 fast_vec_dist(void *a, void *b);
extern void hero_add_clamped_stat(f32 a0);
extern int snd_play_from_class_bank(s32 a0, s32 a1, void *a2, s32 a3);
extern void effect_set_enabled(void *moby, s32 a1);
extern void effect_set_color(void *moby, u32 color);
extern char *pickup_spawn_if_not_taken(void *pos, s32 a1, s32 a2, s32 a3);

/* Mission 3 of the Feltzin dispatcher: gates (class 0x114A) are spawned along the selected path,
   two at a time, each facing along the path. When the player's or the second tracked position's
   dot product with the current gate's forward axis turns positive (and differs from last frame's),
   a pass within 1.25 units of the gate scores, otherwise the miss count rises and the next gate
   takes over. Twelve misses or func_L00_0042B730 fail the mission; once no gate is left, the
   reward is paid through func_US2_L05_00422530. */
void UpdateFeltzinGateCourse_us2(u8 *actor)
{
    struct { Vec up, pos, toward, away; } v;
    u8 *state = *(u8 **)(actor + 0x68);
    GatePath *path;
    GateMoby *gate;
    u8 *player;
    u8 **objects;
    s32 found;
    s32 n;
    f32 dotPlayer, dotOther;

    v.up.q = 0;
    v.up.f[2] = 1.0f;
    if (!g_feltzin_challenge_active) {
        g_feltzin_record_a = 0;
        g_feltzin_record_b = 0;
        g_feltzin_best_dot_player = -1.0f;
        g_feltzin_best_dot_other = -1.0f;
        g_feltzin_gate_flag = 0;
        g_feltzin_path_index = 0;
        g_feltzin_countdown_timer = 0;
        g_feltzin_challenge_active = 1;
        *(s32 *)g_feltzin_timer = 0;
        g_feltzin_challenge_state.reset = 0;
        music_Unpause();
        if (g_feltzin_record_c) {
            moby_mark_spawned((void *)g_feltzin_record_c);
        }
        entry_init_all_registered();
        g_feltzin_record_c = 0;
        hero_set_state_value_b(1);
        g_feltzin_challenge_state.path = *(s32 *)(state + 0x20);
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        found = level_get_saved_value();
        for (n = 0; n < found; n++) {
            if (*(s16 *)(objects[n] + 0xAA) == 0xF82) {
                entry_spawn_list_objects_with_flag(objects[n], 1);
            }
        }
        path = g_gate_l05_path_table[*(s32 *)(state + 0x20)];
        while ((!g_feltzin_record_a || !g_feltzin_record_b) && g_feltzin_path_index != path->count) {
            if (path->points[g_feltzin_path_index].f[3] != -1.0f) {
                gate = CreateMoby(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                if (!g_feltzin_record_a) {
                    g_feltzin_record_a = gate;
                } else {
                    g_feltzin_record_b = gate;
                }
                if (g_feltzin_path_index == path->count - 1) {
                    FastVecSub(&gate->forward, &path->points[g_feltzin_path_index - 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1.0f);
                } else {
                    FastVecSub(&gate->forward, &path->points[g_feltzin_path_index + 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1.0f);
                }
                FastVecCross(&gate->right, &gate->forward, &v.up);
                vec_scale_to_length(&gate->right, &gate->right, 1.0f);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[g_feltzin_path_index]);
                gate->position.i[3] = 0;
            }
            g_feltzin_path_index++;
        }
    }
    if (!g_feltzin_record_a && !g_feltzin_record_b && !g_feltzin_failure_flag) {
        UpdateFeltzinMissionReward_us2(actor, 3);
        return;
    }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82))) {
        g_feltzin_failure_flag = 1;
        func_US2_L05_00422780(actor, 3);
        entry_init_all_registered();
    } else if (g_feltzin_countdown_timer >= 12) {
        g_feltzin_failure_flag = 1;
        func_US2_L05_00422780(actor, 3);
        entry_init_all_registered();
    }
    if (g_feltzin_failure_flag) {
        return;
    }
    if (++*(s32 *)g_feltzin_timer < 2) {
        return;
    }
    player = g_feltzin_target_mobys + (*(s32 *)(state + 0x24) << 8);
    qcopy(&v.pos, g_origin_vec);
    FastVecSub(&v.away, &v.pos, &g_feltzin_record_a->position);
    vec_scale_to_length(&v.away, &v.away, 1.0f);
    FastVecSub(&v.toward, player + 0x10, &g_feltzin_record_a->position);
    vec_scale_to_length(&v.toward, &v.toward, 1.0f);
    dotPlayer = FastVecDot(&g_feltzin_record_a->forward, &v.toward);
    dotOther = FastVecDot(&g_feltzin_record_a->forward, &v.away);
    if ((dotPlayer != g_feltzin_best_dot_player && dotPlayer > 0)
        || (dotOther != g_feltzin_best_dot_other && dotOther > 0)) {
        path = g_gate_l05_path_table[*(s32 *)(state + 0x20)];
        if (fast_vec_dist(&v.pos, &g_feltzin_record_a->position) <= 1.25f
            || fast_vec_dist(player + 0x10, &g_feltzin_record_a->position) <= 1.25f) {
            hero_add_clamped_stat(0.5f);
            snd_play_from_class_bank(15, 0, actor, 0xFBF);
        } else {
            hero_add_clamped_stat(-0.75f);
            g_feltzin_countdown_timer++;
        }
        moby_mark_spawned((void *)g_feltzin_record_a);
        g_feltzin_record_a = g_feltzin_record_b;
        g_feltzin_record_b = 0;
        while (!g_feltzin_record_b && g_feltzin_path_index != path->count) {
            if (path->points[g_feltzin_path_index].f[3] != -1.0f) {
                gate = CreateMoby(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                g_feltzin_record_b = gate;
                if (g_feltzin_path_index == path->count - 1) {
                    FastVecSub(&gate->forward, &path->points[g_feltzin_path_index - 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1.0f);
                } else {
                    FastVecSub(&gate->forward, &path->points[g_feltzin_path_index + 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1.0f);
                }
                FastVecCross(&gate->right, &gate->forward, &v.up);
                vec_scale_to_length(&gate->right, &gate->right, 1.0f);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[g_feltzin_path_index]);
                gate->position.i[3] = 0;
            }
            g_feltzin_path_index++;
        }
    }
    g_feltzin_best_dot_player = dotPlayer;
    g_feltzin_best_dot_other = dotOther;
    if (g_feltzin_record_a) {
        effect_set_enabled((void *)g_feltzin_record_a, 1);
        if (g_feltzin_record_b) {
            effect_set_color((void *)g_feltzin_record_a, 0x40008000);
        } else {
            effect_set_color((void *)g_feltzin_record_a, 0x4000C6FF);
        }
    }
    if (g_feltzin_record_b) {
        effect_set_enabled((void *)g_feltzin_record_b, 1);
        effect_set_color((void *)g_feltzin_record_b, 0x40808000);
    } else if (!g_feltzin_countdown_timer && !g_feltzin_record_c && !g_level_progress_flags[g_current_map_index * 4]) {
        g_feltzin_record_c = pickup_spawn_if_not_taken(&g_feltzin_record_a->position, 0, -1, -1);
    }
}
