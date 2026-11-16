#include "include_asm.h"

#include "common.h"
typedef struct { float pad[32]; float x, y, z; } Target;
extern Target g_hero_state;
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern float g_tracking_head_value __attribute__((sda));
extern float g_tracking_head_max_yaw __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float math_fabs(float);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern char *moby_l00_spawn_child(void *, int, int);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern float math_approach_target_with_direction_mode(void *, float, void *, int, float, float, float);
extern void moby_update_eased_node(void *, void *, int, float, float);

void hero_tracking_head_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float yaw = 0, pitch = 0;
    float acceleration, damping;
    float half_pitch, half_yaw;

    *(u16 *)(moby + 0x34) |= 4;
    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        yaw = 0;
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 16.0f) {
            moby[0x20] = 2;
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, 25);
        }
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !*(int *)(vars + 0x110))
            moby_set_state(moby, 3, -1);
        moby[0xA8] = 255;
        break;
    case 2: {
        float *target;

        yaw = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(g_hero_state.x - *(float *)(moby + 0x10), g_hero_state.y - *(float *)(moby + 0x14)), *(float *)(moby + 0xF8)), 1.5707964897155762f);
        target = &g_hero_state.x;
        pitch = mat_fast_helper_a(vec_distance_xy(target, moby + 0x10), *(float *)(moby + 0x18) - g_hero_state.z);
        if (vec_distance_xy(moby + 0x10, target) > 20.0f) {
            moby[0x20] = 1;
            if (moby[0x43] != 0)
                anim_start_blended_pal(moby, 0, 0, 25);
        }
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !*(int *)(vars + 0x110))
            moby_set_state(moby, 3, -1);
        moby[0xA8] = 255;
        break;
    }
    case 3:
        moby_l00_spawn_child(moby, 0x1132, moby[0x30]);
        PlayMobySound(0, 0, moby);
        {
            int id = *(int *)(vars + 0x114);
            u8 *effect;

            if (id != -1) {
                effect = g_sound_state + id * 0x70;
                if (*(u8 **)(effect + 0x88) == moby && effect[0x74])
                    snd_stop_voice(id);
            }
        }
        *(int *)(vars + 0x114) = -1;
        moby_mark_spawned(moby);
        return;
    }
    if (math_fabs(fast_subtract_rotations(yaw, *(float *)(vars + 0x100))) > g_tracking_head_max_yaw * 0.017453294f) {
        u8 *effect = g_sound_state + *(int *)(vars + 0x114) * 0x70;

        if (*(u8 **)(effect + 0x88) != moby || !effect[0x74])
            *(int *)(vars + 0x114) = PlayMobySound(1, 4, moby);
    } else {
        int id = *(int *)(vars + 0x114);
        u8 *effect;

        if (id != -1) {
            effect = g_sound_state + id * 0x70;
            if (*(u8 **)(effect + 0x88) == moby && effect[0x74])
                snd_stop_voice(id);
        }
        *(int *)(vars + 0x114) = -1;
    }
    acceleration = 0.0432f;
    math_approach_target_with_direction_mode(vars + 0x100, yaw, vars + 0x108, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    damping = 0.43200004f;
    math_approach_target_with_direction_mode(vars + 0x104, pitch, vars + 0x10C, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    half_pitch = *(float *)(vars + 0x104) * 0.5f;
    half_yaw = *(float *)(vars + 0x100) * 0.5f;
    *(float *)(vars + 0x68) = half_yaw;
    *(float *)(vars + 0x60) = half_pitch;
    *(float *)(vars + 0xE0) = half_pitch;
    *(float *)(vars + 0xE8) = half_yaw;
    moby_update_eased_node(moby, vars, 0, acceleration, damping);
    moby_update_eased_node(moby, vars + 0x80, 1, acceleration, damping);
    func_002A0F48(moby);
    *(float *)(moby + 0xC) = g_tracking_head_value;
}
