#include "common.h"
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x74]; u8 active; u8 pad75[0x13]; s32 owner; } SoundAnchor;
extern u8 g_sound_state[];
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern s32 g_current_map_index;
extern s32 D_L12_001B3DA8 MACRO_ADDR;
extern s32 D_L12_001B3DAC MACRO_ADDR;
extern s32 D_L12_001B29C8;
typedef struct { u8 pad[0x30]; f32 position[4]; u8 pad40[0x40]; } PathNode;
extern PathNode *D_L12_001B2F8C MACRO_ADDR;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern s32 D_L12_001B1E00_gp SDATA(D_L12_001B1E00);
extern s32 D_L12_001B1E08_gp SDATA(D_L12_001B1E08);
extern s32 D_L12_001B1E10_gp SDATA(D_L12_001B1E10);
extern s32 D_L12_001B1E00, D_L12_001B1E04, D_L12_001B1E08, D_L12_001B1E0C, D_L12_001B1E10, D_L12_001B1E14;
extern void moby_mark_spawned(void *);
/* Typed interleaving preserves the three GPR and three FP inputs. */
extern void pushable_moby_update(void *, void *, f32, f32, f32, s32);
extern f32 vec_distance_xy(void *, void *), FastVecLength(void *), IntToFloat(s32);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, f32);
/* The pointer and four FP inputs retain their physical EE ABI slots. */
extern void math_approach_target_with_braking(f32, f32, f32, f32, void *);
extern void moby_set_state(void *, s32, s32), mat_combine_and_store(void *, void *, void *, void *);
extern s32 flag_set_first_pending(void *), snd_play_from_class_bank(s32, s32, void *, s32);
extern u32 PulseColor(u32, u32, f32);
typedef struct { u8 pad[0x78]; u32 color; } ColorActor;
/* Moves a platform along its path towards a node, pulses its colour, and carries the hero with it. */
void UpdateTodanoPathMover(u8 *self) {
    f32 oldpos[4], oldrot[4], temp[4], delta[4];
    u8 *st = *(u8 **)(self + 0x68);
    u16 flag = *(u16 *)(self + 0xb2);
    s32 savedBits;
    if (D_L12_0021EDF0.flags[(s16)flag] ||
        ((savedBits = D_0019B4A8[((s16)flag >> 1) + (g_current_map_index << 10)]),
         (flag & 1) ? ((savedBits >> 4) & 7) : (savedBits & 7))) {
        moby_mark_spawned(self);
        return;
    }
    qcopy(oldpos, self + 0x10);
    qcopy(oldrot, self + 0xf0);
    switch (self[0x20]) {
    case 0:
        *(u16 *)(self + 0x34) |= 0x1000;
        *(s32 *)(st + 0xdc) |= 1;
        self[0x20] = 1;
        D_L12_001B3DA8 = 0;
        break;
    case 1:
        pushable_moby_update(self, st + 0x50, 1.5f, 1.5f, 0.1f, *(s32 *)(st + 0xec));
        if (*(s32 *)(st + 0xe0) != -1) {
            qcopy(temp, D_L12_001B2F8C[*(s32 *)(st + 0xe0)].position);
            if (vec_distance_xy(self + 0x10, temp) < 1.0f) {
                *(u16 *)(self + 0x34) &= 0xefff;
                *(f32 *)(st + 0xf0) = FastVecLength(st + 0x50);
                self[0x20] = 2;
            }
        }
        break;
    case 2: {
        f32 angle;
        FastVecSub(delta, D_L12_001B2F8C[*(s32 *)(st + 0xe0)].position, self + 0x10);
        angle = FastVecLength(delta);
        math_approach_target_with_braking(angle, 0.0055555557f, 0.0055555557f, 0.06666667f, st + 0xf0);
        vec_scale_to_length(temp, delta, *(f32 *)(st + 0xf0));
        FastVecAdd(self + 0x10, self + 0x10, temp);
        if (angle < 0.001f) moby_set_state(self, 3, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(self)) snd_play_from_class_bank(2, 0, self, 0x10e9);
        break;
    }
    if (self[0x31] && self[0x20] != 3 && self[0x20] != 4) {
        f32 phase = IntToFloat(D_L12_001B29C8_gp % 60);
        f32 period = IntToFloat(60);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E00_gp, D_L12_001B1E04, phase - 3.14159274f);
    }
    if (self[0x31] && self[0x20] == 3) {
        f32 phase = IntToFloat(D_L12_001B29C8 % 60);
        f32 period = IntToFloat(60);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E08_gp, D_L12_001B1E0C, phase - 3.14159274f);
    }
    if (self[0x31] && self[0x20] == 4) {
        f32 phase = IntToFloat(D_L12_001B29C8 % 60);
        f32 period = IntToFloat(60);
        phase *= 6.28318548f;
        phase /= period;
        ((ColorActor *)self)->color = PulseColor(D_L12_001B1E10_gp, D_L12_001B1E14, phase - 3.14159274f);
        {
        SoundAnchor *sound = (SoundAnchor *)(D_L12_001B3DA8 * 112 + (s32)g_sound_state);
        if (sound->owner != D_L12_001B3DAC || !sound->active) {
            D_L12_001B3DA8 = snd_play_from_class_bank(2, 0, self, 0x10e9);
            D_L12_001B3DAC = (s32)self;
        }
        }
    }
    FastVecSub(temp, self + 0x10, oldpos);
    mat_combine_and_store(st + 0xa0, temp, oldrot, self + 0xf0);
}
