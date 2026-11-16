#include "include_asm.h"

#include "common.h"
extern u8 g_moby_nibble_table[];
typedef struct { u8 pad[0x74]; u8 active; u8 pad75[0x13]; s32 owner; } SoundAnchor;
extern u8 g_sound_state[];
extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern s32 g_current_map_index;
extern s32 g_debris_sound_handle MACRO_ADDR;
extern s32 g_debris_sound_owner MACRO_ADDR;
extern s32 g_frame_l12_counter;
typedef struct { u8 pad[0x30]; f32 position[4]; u8 pad40[0x40]; } PathNode;
extern PathNode *g_path_waypoint_table MACRO_ADDR;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern s32 D_L12_001B1E00_gp SDATA(D_L12_001B1E00);
extern s32 D_L12_001B1E08_gp SDATA(D_L12_001B1E08);
extern s32 D_L12_001B1E10_gp SDATA(D_L12_001B1E10);
extern s32 g_pulse_color_a0, g_pulse_color_a1, g_pulse_color_b0, g_pulse_color_b1, g_pulse_color_c0, g_pulse_color_c1;
extern void moby_mark_spawned(void *);
extern void pushable_moby_update_pal(void *, void *, f32, f32, f32, s32);
extern f32 vec_distance_xy(void *, void *), FastVecLength(void *), IntToFloat(s32);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, f32);
extern void math_approach_target_with_braking(f32, f32, f32, f32, void *);
extern void moby_set_state(void *, s32, s32), mat_combine_and_store(void *, void *, void *, void *);
extern s32 flag_set_first_pending(void *), snd_play_from_class_bank(s32, s32, void *, s32);
extern u32 PulseColor(u32, u32, f32);
typedef struct { u8 pad[0x78]; u32 color; } ColorActor;

/* Moves a platform along its path towards a node, pulses its colour, and carries the hero with it (PAL: 50 Hz timings). */
void UpdateTodanoPathMover_pal(u8 *self) {
    f32 oldpos[4], oldrot[4], temp[4], delta[4];
    u8 *vars = *(u8 **)(self + 0x68);
    u16 flag = *(u16 *)(self + 0xb2);
    s32 packed;
    if (g_object_flags.flags[(s16)flag] ||
        ((packed = g_moby_nibble_table[((s16)flag >> 1) + (g_current_map_index << 10)]),
         (flag & 1) ? ((packed >> 4) & 7) : (packed & 7))) {
        moby_mark_spawned(self);
        return;
    }
    qcopy(oldpos, self + 0x10);
    qcopy(oldrot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        *(u16 *)(self + 0x34) |= 0x1000;
        *(s32 *)(vars + 0xdc) |= 1;
        self[0x20] = 1;
        g_debris_sound_handle = 0;
        break;
    case 1:
        pushable_moby_update_pal(self, vars + 0x50, 1.5f, 1.5f, 0.1f, *(s32 *)(vars + 0xec));
        if (*(s32 *)(vars + 0xe0) != -1) {
            qcopy(temp, g_path_waypoint_table[*(s32 *)(vars + 0xe0)].position);
            if (vec_distance_xy(self + 0x10, temp) < 1.0f) {
                *(u16 *)(self + 0x34) &= 0xefff;
                *(f32 *)(vars + 0xF0) = FastVecLength(vars + 0x50);
                self[0x20] = 2;
            }
        }
        break;
    case 2: {
        f32 angle;
        FastVecSub(delta, g_path_waypoint_table[*(s32 *)(vars + 0xe0)].position, self + 0x10);
        angle = FastVecLength(delta);
        math_approach_target_with_braking(angle, 0.008f, 0.008f, 0.080000006f, vars + 0xF0);
        vec_scale_to_length(temp, delta, *(f32 *)(vars + 0xF0));
        FastVecAdd(self + 0x10, self + 0x10, temp);
        if (angle < 0.001f) moby_set_state(self, 3, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(self)) snd_play_from_class_bank(2, 0, self, 0x10e9);
        break;
    }
    if (self[0x31] && self[0x20] != 3 && self[0x20] != 4) {
        f32 phase = IntToFloat(D_L12_001B29C8_gp % 50);
        f32 period = IntToFloat(50);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E00_gp, g_pulse_color_a1, phase - 3.14159274f);
    }
    if (self[0x31] && self[0x20] == 3) {
        f32 phase = IntToFloat(g_frame_l12_counter % 50);
        f32 period = IntToFloat(50);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E08_gp, g_pulse_color_b1, phase - 3.14159274f);
    }
    if (self[0x31] && self[0x20] == 4) {
        f32 phase = IntToFloat(g_frame_l12_counter % 50);
        f32 period = IntToFloat(50);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E10_gp, g_pulse_color_c1, phase - 3.14159274f);
        {
        SoundAnchor *sound = (SoundAnchor *)(g_debris_sound_handle * 112 + (s32)g_sound_state);
        if (sound->owner != g_debris_sound_owner || !sound->active) {
            g_debris_sound_handle = snd_play_from_class_bank(2, 0, self, 0x10e9);
            g_debris_sound_owner = (s32)self;
        }
        }
    }
    FastVecSub(temp, self + 0x10, oldpos);
    mat_combine_and_store(vars + 0xa0, temp, oldrot, self + 0xF0);
}
