#include "include_asm.h"

#include "common.h"
typedef struct { float pad[32]; float x, y, z; } Target;
extern Target g_hero_state;
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern float D_L12_001AFC70 __attribute__((sda));
extern float D_L12_001AFC74 __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float math_fabs(float);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern char *moby_l00_spawn_child(void *, int, int);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern float math_approach_target_with_direction_mode(void *, float, void *, int, float, float, float);
extern void moby_update_eased_node(void *, void *, int, float, float);

void func_PAL_L12_003C21C8(u8 *o) {
    u8 *d = *(u8 **)(o + 0x68);
    float yaw = 0, pitch = 0;
    float acceleration, damping;
    float half_pitch, half_yaw;

    *(u16 *)(o + 0x34) |= 4;
    switch (o[0x20]) {
    case 0:
        moby_set_state(o, 1, -1);
        break;
    case 1:
        yaw = 0;
        if (vec_distance_xy(o + 0x10, g_hero_position) < 16.0f) {
            o[0x20] = 2;
            if (o[0x43] != 1)
                func_PAL_002A7E68(o, 1, 0, 25);
        }
        if (part_find_owned_effect_slot(o, 0x4010000, 0) && !*(int *)(d + 0x110))
            moby_set_state(o, 3, -1);
        o[0xA8] = 255;
        break;
    case 2: {
        float *target;

        yaw = FastAddRotations(fast_subtract_rotations(mat_fast_helper_a(g_hero_state.x - *(float *)(o + 0x10), g_hero_state.y - *(float *)(o + 0x14)), *(float *)(o + 0xF8)), 1.5707964897155762f);
        target = &g_hero_state.x;
        pitch = mat_fast_helper_a(vec_distance_xy(target, o + 0x10), *(float *)(o + 0x18) - g_hero_state.z);
        if (vec_distance_xy(o + 0x10, target) > 20.0f) {
            o[0x20] = 1;
            if (o[0x43] != 0)
                func_PAL_002A7E68(o, 0, 0, 25);
        }
        if (part_find_owned_effect_slot(o, 0x4010000, 0) && !*(int *)(d + 0x110))
            moby_set_state(o, 3, -1);
        o[0xA8] = 255;
        break;
    }
    case 3:
        moby_l00_spawn_child(o, 0x1132, o[0x30]);
        PlayMobySound(0, 0, o);
        {
            int id = *(int *)(d + 0x114);
            u8 *effect;

            if (id != -1) {
                effect = g_sound_state + id * 0x70;
                if (*(u8 **)(effect + 0x88) == o && effect[0x74])
                    snd_stop_voice(id);
            }
        }
        *(int *)(d + 0x114) = -1;
        moby_mark_spawned(o);
        return;
    }
    if (math_fabs(fast_subtract_rotations(yaw, *(float *)(d + 0x100))) > D_L12_001AFC74 * 0.017453294f) {
        u8 *effect = g_sound_state + *(int *)(d + 0x114) * 0x70;

        if (*(u8 **)(effect + 0x88) != o || !effect[0x74])
            *(int *)(d + 0x114) = PlayMobySound(1, 4, o);
    } else {
        int id = *(int *)(d + 0x114);
        u8 *effect;

        if (id != -1) {
            effect = g_sound_state + id * 0x70;
            if (*(u8 **)(effect + 0x88) == o && effect[0x74])
                snd_stop_voice(id);
        }
        *(int *)(d + 0x114) = -1;
    }
    acceleration = 0.0432f;
    math_approach_target_with_direction_mode(d + 0x100, yaw, d + 0x108, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    damping = 0.43200004f;
    math_approach_target_with_direction_mode(d + 0x104, pitch, d + 0x10C, 0, 0.0025132746f, 0.0025132746f, 0.12566373f);
    half_pitch = *(float *)(d + 0x104) * 0.5f;
    half_yaw = *(float *)(d + 0x100) * 0.5f;
    *(float *)(d + 0x68) = half_yaw;
    *(float *)(d + 0x60) = half_pitch;
    *(float *)(d + 0xE0) = half_pitch;
    *(float *)(d + 0xE8) = half_yaw;
    moby_update_eased_node(o, d, 0, acceleration, damping);
    moby_update_eased_node(o, d + 0x80, 1, acceleration, damping);
    func_002A0F48(o);
    *(float *)(o + 0xC) = D_L12_001AFC70;
}
