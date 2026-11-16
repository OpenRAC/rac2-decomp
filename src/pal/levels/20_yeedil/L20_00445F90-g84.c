#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x30];
    float f30;
    float f34;
    unsigned char pad1[0x48];
} Rec_42550;
extern float g_yeedil_grab_turn_scale __attribute__((sda));
extern float g_yeedil_jump_velocity_scale __attribute__((sda));
extern char g_hero_state[];
extern Rec_42550 *g_linked_moby_table;
extern float ApproachValue(float *, float, float);
extern void StepAngleTowardTarget(char *, int, float, float);
extern float vec_distance_xy(char *, char *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int PlayMobySound(int, int, char *);

/* Makes the enemy fall and bounce on the ground while it turns toward the hero or its target. Returns 1 when the bouncing has stopped. (PAL) */
int UpdateBouncingMoby_pal(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *hero;
    char *hero_pos;
    float value;
    int link_index;
    Rec_42550 *linked;

    ApproachValue((float *)(self + 0x48), 1.0f, 0.040000003f);

    if (*(u8 *)(self + 0x94) == 2) {
        StepAngleTowardTarget(vars + 0x1804, 1, 0.0f, g_yeedil_grab_turn_scale * 0.00017453295f);
    }
    value = *(float *)(vars + 0xF8);
    hero = g_hero_state;
    *(float *)(self + 0x18) += value;

    *(float *)(vars + 0xF8) -= *(float *)(vars + 0x7C);

    if (*(int *)(hero + 0x2294) == 0x8C) {
        float value;
        hero_pos = hero + 0x80;
        value = vec_distance_xy(hero_pos, self + 0x10);
        if (value <= 4.0f) {
            value = *(float *)(hero + 0x88);
            value += 5.0f;
            *(float *)(hero + 0x88) = value;
            value = coll_probe_ground_height_below(hero_pos, 0, 0.5f);
            *(float *)(hero + 0x88) = value;
            *(unsigned short *)(hero + 0x1E0) = 5;
            *(unsigned short *)(hero + 0x1F0) = 5;
        }
        link_index = *(int *)(vars + 0x230);
        linked = (Rec_42550 *)((link_index << 7) + (unsigned int)g_linked_moby_table);
        value = mat_fast_helper_a(linked->f30 - *(float *)(self + 0x10), linked->f34 - *(float *)(self + 0x14));
        moby_start_effect_from_entry(self, value);

    } else {
        moby_start_effect_from_entry(self, mat_fast_helper_a(
            *(float *)(hero + 0x80) - *(float *)(self + 0x10),
            *(float *)(hero + 0x84) - *(float *)(self + 0x14)));
    }

    if (*(float *)(self + 0x18) <= *(float *)(vars + 0xE0)) {
        float velocity;
        *(float *)(self + 0x18) = *(float *)(vars + 0xE0);
        PlayMobySound(0, 0, self);
        velocity = *(float *)(vars + 0xF8) * -g_yeedil_jump_velocity_scale;
        *(float *)(vars + 0xF8) = velocity;
        if (velocity < 0.020000001f) {
            *(int *)(vars + 0xF8) = 0;
            return 1;
        }
    }
    return 0;
}

extern float g_yeedil_jump_small_angle __attribute__((sda));
extern float g_yeedil_jump_angle __attribute__((sda));
extern float g_yeedil_jump_accel __attribute__((sda));
extern float g_yeedil_jump_height __attribute__((sda));
extern void moby_set_controller_speed_limits(unsigned char *, float, float, float, float);
extern float square_root(float);

/* Gets the enemy ready to jump. It picks the turn speed, remembers the ground height and works out how fast to go up. (PAL) */
void yeedil_boss_start_jump_pal(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    moby_set_controller_speed_limits((unsigned char *)actor, 0.0f, 0.0f,
                 g_yeedil_jump_small_angle * 6.981318e-06f,
                 g_yeedil_jump_angle * 0.0003490659f);
    *(float *)(state + 0x7C) = g_yeedil_jump_accel * 0.00040000002f;
    *(float *)(state + 0xE0) = coll_probe_ground_height_below(actor + 0x10, 0, 0.5f);
    qzero(state + 0xF0);
    *(float *)(state + 0xF8) = square_root(*(float *)(state + 0x7C) * 2.0f * g_yeedil_jump_height);
}
