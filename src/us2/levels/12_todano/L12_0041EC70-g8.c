#include "include_asm.h"

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
extern void hero_set_move_state_by_speed(void);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, void *);
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 math_approach_target_with_direction_mode(void *, void *, f32, f32, f32, f32, s32);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

void UpdateTodanoRotatingLift_us2(u8 *self)
{
    f32 oldpos[4] __attribute__((aligned(16)));
    f32 oldrot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    LiftVars *p = *(LiftVars **)(self + 0x68);
    f32 target, speed, y;

    qcopy(oldpos, self + 0x10);
    qcopy(oldrot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        F(self, 0xF8) = FastAddRotations(F(self, 0xF8), 1.5707964897155762f);
        qcopy_nc(p->origin, self + 0x10);
        p->origin[3] = F(self, 0xF8);
        moby_set_state(self, 2, -1);
        break;
    case 2:
        p->targetHeight = p->destination ?
            F((u8 *)(p->node * 128 + (u32)g_path_waypoint_table), 0x38) : p->origin[2];
        p->targetAngle = p->destination ?
            FastAddRotations(F((u8 *)(p->node * 128 + (u32)g_path_waypoint_table), 0x78),
                          4.7123894691467285f) : p->origin[3];
        y = F((u8 *)(p->node * 128 + (u32)g_path_waypoint_table), 0x38);
        if (g_hero_state.lift == self && g_hero_state.active) {
            TryClaimNotice(8, 0x12EC, 1);
            if (g_pad_held_flags & 16) {
                p->destination = (p->destination + 1) & 1;
                moby_set_state(self, 3, -1);
            }
        } else if (p->destination) {
            if (math_fabs(g_hero_state.position[2] - p->origin[2]) < 4.0f &&
                vec_distance_xy(g_hero_state.position, self + 0x10) < 32.0f) {
                p->destination = 0;
                moby_set_state(self, 1, -1);
            }
        } else if (math_fabs(g_hero_state.position[2] - y) < 4.0f &&
                   vec_distance_xy(g_hero_state.position, self + 0x10) < 32.0f) {
            p->destination = 1;
            moby_set_state(self, 1, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            hero_start_target_state(self + 0x10, 0, F(g_hero_moby, 0xF8));
            p->timer = 0;
        }
        if (++p->timer >= 361) {
            hero_set_move_state_by_speed();
            moby_set_state(self, 2, -1);
        } else if (hero_get_target_state_kind() != 1) {
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(self)) {
            p->angularSpeed = 0;
            p->speed = 0;
        }
        p->targetHeight = p->destination ?
            F((u8 *)(p->node * 128 + (u32)g_path_waypoint_table), 0x38) : p->origin[2];
        p->targetAngle = p->destination ?
            FastAddRotations(F((u8 *)(p->node * 128 + (u32)g_path_waypoint_table), 0x78),
                          4.7123894691467285f) : p->origin[3];
        target = p->targetHeight;
        speed = 0.003888889f;
        if (p->destination) {
            if (g_hero_state.position[2] < F(self, 0x18) - 1.0f &&
                IsPointInCuboid(g_hero_state.position, p->node)) {
                target += 3.0f;
                speed = 0.007777778f;
            } else {
                target += 0.5f;
            }
        }
        math_step_value_toward_target(self + 0x18, &p->speed, target, 0.0019444445f, speed, 0.5f);
        if (math_fabs(p->targetHeight - F(self, 0x18)) < 0.6f &&
            math_fabs(p->speed) < 0.01f) {
            {
                s32 index = p->sound;

                if (index != -1) {
                    LiftSound *entry = (LiftSound *)(index * 0x70 + (s32)g_sound_state);

                    if (entry->owner == self && entry->active)
                        snd_stop_voice(index);
                }
            }
            p->sound = -1;
            moby_set_state(self, 2, -1);
        } else {
            LiftSound *entry = (LiftSound *)(p->sound * 0x70 + (s32)g_sound_state);

            if (entry->owner != self || !entry->active)
                p->sound = PlayMobySound(0, 4, self);
        }
        math_approach_target_with_direction_mode(self + 0xF8, &p->angularSpeed, p->targetAngle,
                      0.00014544412260875106f, 0.00014544412260875106f, 0.10471977f, 0);
        break;
    }
    FastVecSub(delta, self + 0x10, oldpos);
    mat_combine_and_store((u8 *)p + 0x20, delta, oldrot, self + 0xF0);
}
