/* func_PAL_L12_00422B60, the PAL copy of func_L12_0041D808: the same C, where template us2 func_US2_L12_0041EC70; rename func_L01_002C98B8 becomes func_PAL_L01_002C9B28; lit 0.0028000001f becomes 0.6f; lit 0.5f becomes 0.6f; lit 0.6f becomes 0.0028000001f. */

#include "common.h"
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
typedef struct {
    u8 pad[0x60];
    s32 node;
    s32 destination;
    f32 angularSpeed;
    f32 speed;
    f32 origin[4];
    s32 sound;
    f32 targetHeight;
    f32 targetAngle;
    s32 timer;
} LiftVars;
extern u8 *g_path_waypoint_table MACRO_ADDR;
typedef struct {
    u8 pad0[0x80];
    f32 position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
} LiftHero;
extern LiftHero g_hero_state;
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    u8 *owner;
} LiftSound;
extern u8 g_sound_state[];
extern u8 *g_hero_moby NOT_SDA;
extern s32 g_pad_held_flags NOT_SDA;
extern f32 FastAddRotations(f32, f32);
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern void moby_set_state(void *, s32, s32);
extern s32 TryClaimNotice(s32, s32, s32);
extern s32 flag_set_first_pending(void *);
extern s32 hero_get_target_state_kind(void);
extern s32 IsPointInCuboid(void *, s32);
extern void hero_start_target_state(void *, s32, f32);
extern void hero_set_move_state_by_speed_pal(void);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, void *);
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 math_approach_target_with_direction_mode(void *, void *, f32, f32, f32, f32, s32);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Moves a lift up and down while turning it, when the hero stands on it and asks, or walks up to it (PAL: 50 Hz timings). */
void UpdateTodanoRotatingLift_pal(u8 *self)
{
    f32 old_pos[4] __attribute__((aligned(16)));
    f32 old_rot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    LiftVars *vars = *(LiftVars **)(self + 0x68);
    f32 target, max_speed, node_height;

    qcopy(old_pos, self + 0x10);
    qcopy(old_rot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        F(self, 0xF8) = FastAddRotations(F(self, 0xF8), 1.5707964897155762f);
        qcopy_nc(vars->origin, self + 0x10);
        vars->origin[3] = F(self, 0xF8);
        moby_set_state(self, 2, -1);
        break;
    case 2:
        vars->targetHeight = vars->destination ?
            F((u8 *)(vars->node * 128 + (u32)g_path_waypoint_table), 0x38) : vars->origin[2];
        vars->targetAngle = vars->destination ?
            FastAddRotations(F((u8 *)(vars->node * 128 + (u32)g_path_waypoint_table), 0x78),
                          4.7123894691467285f) : vars->origin[3];
        node_height = F((u8 *)(vars->node * 128 + (u32)g_path_waypoint_table), 0x38);
        if (g_hero_state.lift == self && g_hero_state.active) {
            TryClaimNotice(8, 0x12EC, 1);
            if (g_pad_held_flags & 16) {
                vars->destination = (vars->destination + 1) & 1;
                moby_set_state(self, 3, -1);
            }
        } else if (vars->destination) {
            if (math_fabs(g_hero_state.position[2] - vars->origin[2]) < 4.0f &&
                vec_distance_xy(g_hero_state.position, self + 0x10) < 32.0f) {
                vars->destination = 0;
                moby_set_state(self, 1, -1);
            }
        } else if (math_fabs(g_hero_state.position[2] - node_height) < 4.0f &&
                   vec_distance_xy(g_hero_state.position, self + 0x10) < 32.0f) {
            vars->destination = 1;
            moby_set_state(self, 1, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            hero_start_target_state(self + 0x10, 0, F(g_hero_moby, 0xF8));
            vars->timer = 0;
        }
        if (++vars->timer >= 301) {
            hero_set_move_state_by_speed_pal();
            moby_set_state(self, 2, -1);
        } else if (hero_get_target_state_kind() != 1) {
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            vars->angularSpeed = 0;
            vars->speed = 0;
        }
        vars->targetHeight = vars->destination ?
            F((u8 *)(vars->node * 128 + (u32)g_path_waypoint_table), 0x38) : vars->origin[2];
        vars->targetAngle = vars->destination ?
            FastAddRotations(F((u8 *)(vars->node * 128 + (u32)g_path_waypoint_table), 0x78),
                          4.7123894691467285f) : vars->origin[3];
        target = vars->targetHeight;
        max_speed = 0.0056000003f;
        if (vars->destination) {
            if (g_hero_state.position[2] < F(self, 0x18) - 1.0f &&
                IsPointInCuboid(g_hero_state.position, vars->node)) {
                target += 3.0f;
                max_speed = 0.0112000005f;
            } else {
                target += 0.5f;
            }
        }
        math_step_value_toward_target(self + 0x18, &vars->speed, target, 0.0028000001f, max_speed, 0.6f);
        if (math_fabs(vars->targetHeight - F(self, 0x18)) < 0.6f &&
            math_fabs(vars->speed) < 0.01f) {
            {
                s32 index = vars->sound;

                if (index != -1) {
                    LiftSound *entry = (LiftSound *)(index * 0x70 + (s32)g_sound_state);

                    if (entry->owner == self && entry->active)
                        snd_stop_voice(index);
                }
            }
            vars->sound = -1;
            moby_set_state(self, 2, -1);
        } else {
            LiftSound *entry = (LiftSound *)(vars->sound * 0x70 + (s32)g_sound_state);

            if (entry->owner != self || !entry->active)
                vars->sound = PlayMobySound(0, 4, self);
        }
        math_approach_target_with_direction_mode(self + 0xF8, &vars->angularSpeed, vars->targetAngle,
                      0.00020943955f, 0.00020943955f, 0.12566373f, 0);
        break;
    }
    FastVecSub(delta, self + 0x10, old_pos);
    mat_combine_and_store((u8 *)vars + 0x20, delta, old_rot, self + 0xF0);
}
