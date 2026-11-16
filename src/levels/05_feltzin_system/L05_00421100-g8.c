#include "common.h"

/* Built with -G8 and -frac2-zero-ti-por: the course state is reached through $gp, and the
   opening quadword clear of the up vector at 0($sp) keeps its por-materialised zero. */

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

/* A path: its point count, then the points; a point whose w is -1.0f gets no gate. */
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

extern void func_003404B8(void);
extern void func_0037B210(void);
extern void func_00379F28(s32 a0);
extern void func_00379F18(s32 a0);
extern void func_00328870(void *moby);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern void func_0037B280(u8 *a0, s32 a1);
extern GateMoby *func_00328508(s32 oclass);
extern u8 *func_00379ED0(s32 a0);
extern s32 func_L05_00417748(u8 *a0);
extern void UpdateFeltzinMissionReward(u8 *actor, s32 mission);
extern void feltzin_mission_handle_failure(u8 *a0, s32 a1);
extern void func_00306660(void *dst, void *a, void *b);
extern void func_00306748(void *dst, void *a, void *b);
extern void func_003068F8(void *dst, void *src, f32 scale);
extern f32 func_00306720(void *a, void *b);
extern f32 func_003067D8(void *a, void *b);
extern void func_0037ADD8(f32 a0);
extern void func_003719A8(s32 a0, s32 a1, void *a2, s32 a3);
extern void effect_set_enabled(void *moby, s32 a1);
extern void effect_set_color(void *moby, u32 color);
extern char *pickup_spawn_if_not_taken(void *pos, s32 a1, s32 a2, s32 a3);

/* Mission 3 of the Feltzin dispatcher: gates (class 0x114A) are spawned along the selected path,
   two at a time, each facing along the path. When the player's or the second tracked position's
   dot product with the current gate's forward axis turns positive (and differs from last frame's),
   a pass within 1.25 units of the gate scores, otherwise the miss count rises and the next gate
   takes over. Twelve misses or func_L05_00417748 fail the mission; once no gate is left, the
   reward is paid through func_L05_00420788. */
void UpdateFeltzinGateCourse(u8 *actor)
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
        func_003404B8();
        if (g_feltzin_record_c) {
            func_00328870((void *)g_feltzin_record_c);
        }
        func_0037B210();
        g_feltzin_record_c = 0;
        func_00379F28(1);
        g_feltzin_challenge_state.path = *(s32 *)(state + 0x20);
        func_00379F18(0);
        objects = func_00379EB8();
        found = func_00379EC8();
        for (n = 0; n < found; n++) {
            if (*(s16 *)(objects[n] + 0xAA) == 0xF82 /* moby class 3970 */) {
                func_0037B280(objects[n], 1);
            }
        }
        path = g_gate_l05_path_table[*(s32 *)(state + 0x20)];
        while ((!g_feltzin_record_a || !g_feltzin_record_b) && g_feltzin_path_index != path->count) {
            if (path->points[g_feltzin_path_index].f[3] != -1.0f) {
                gate = func_00328508(0x114A /* moby class 4426 */);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                if (!g_feltzin_record_a) {
                    g_feltzin_record_a = gate;
                } else {
                    g_feltzin_record_b = gate;
                }
                if (g_feltzin_path_index == path->count - 1) {
                    func_00306660(&gate->forward, &path->points[g_feltzin_path_index - 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    func_003068F8(&gate->forward, &gate->forward, -1.0f);
                } else {
                    func_00306660(&gate->forward, &path->points[g_feltzin_path_index + 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    func_003068F8(&gate->forward, &gate->forward, 1.0f);
                }
                func_00306748(&gate->right, &gate->forward, &v.up);
                func_003068F8(&gate->right, &gate->right, 1.0f);
                func_00306748(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[g_feltzin_path_index]);
                gate->position.i[3] = 0;
            }
            g_feltzin_path_index++;
        }
    }
    if (!g_feltzin_record_a && !g_feltzin_record_b && !g_feltzin_failure_flag) {
        UpdateFeltzinMissionReward(actor, 3);
        return;
    }
    if (func_L05_00417748(func_00379ED0(0xF82))) {
        g_feltzin_failure_flag = 1;
        feltzin_mission_handle_failure(actor, 3);
        func_0037B210();
    } else if (g_feltzin_countdown_timer >= 12) {
        g_feltzin_failure_flag = 1;
        feltzin_mission_handle_failure(actor, 3);
        func_0037B210();
    }
    if (g_feltzin_failure_flag) {
        return;
    }
    if (++*(s32 *)g_feltzin_timer < 2) {
        return;
    }
    player = g_feltzin_target_mobys + (*(s32 *)(state + 0x24) << 8);
    qcopy(&v.pos, g_origin_vec);
    func_00306660(&v.away, &v.pos, &g_feltzin_record_a->position);
    func_003068F8(&v.away, &v.away, 1.0f);
    func_00306660(&v.toward, player + 0x10, &g_feltzin_record_a->position);
    func_003068F8(&v.toward, &v.toward, 1.0f);
    dotPlayer = func_00306720(&g_feltzin_record_a->forward, &v.toward);
    dotOther = func_00306720(&g_feltzin_record_a->forward, &v.away);
    if ((dotPlayer != g_feltzin_best_dot_player && dotPlayer > 0)
        || (dotOther != g_feltzin_best_dot_other && dotOther > 0)) {
        path = g_gate_l05_path_table[*(s32 *)(state + 0x20)];
        if (func_003067D8(&v.pos, &g_feltzin_record_a->position) <= 1.25f
            || func_003067D8(player + 0x10, &g_feltzin_record_a->position) <= 1.25f) {
            func_0037ADD8(0.5f);
            func_003719A8(15, 0, actor, 0xFBF);
        } else {
            func_0037ADD8(-0.75f);
            g_feltzin_countdown_timer++;
        }
        func_00328870((void *)g_feltzin_record_a);
        g_feltzin_record_a = g_feltzin_record_b;
        g_feltzin_record_b = 0;
        while (!g_feltzin_record_b && g_feltzin_path_index != path->count) {
            if (path->points[g_feltzin_path_index].f[3] != -1.0f) {
                gate = func_00328508(0x114A /* moby class 4426 */);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                g_feltzin_record_b = gate;
                if (g_feltzin_path_index == path->count - 1) {
                    func_00306660(&gate->forward, &path->points[g_feltzin_path_index - 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    func_003068F8(&gate->forward, &gate->forward, -1.0f);
                } else {
                    func_00306660(&gate->forward, &path->points[g_feltzin_path_index + 1],
                                  &path->points[g_feltzin_path_index]);
                    gate->forward.i[3] = 0;
                    func_003068F8(&gate->forward, &gate->forward, 1.0f);
                }
                func_00306748(&gate->right, &gate->forward, &v.up);
                func_003068F8(&gate->right, &gate->right, 1.0f);
                func_00306748(&gate->up, &gate->right, &gate->forward);
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
