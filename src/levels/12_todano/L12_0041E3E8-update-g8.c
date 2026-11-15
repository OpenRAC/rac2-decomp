#include "common.h"
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x74]; u8 active; u8 pad75[0x13]; s32 owner; } SoundAnchor;
extern u8 D_00188660[];
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern s32 D_001A79F0;
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
extern void func_0029F338(void *);
/* Typed interleaving preserves the three GPR and three FP inputs. */
extern void func_L01_0031AB20(void *, void *, f32, f32, f32, s32);
extern f32 func_00282E80(void *, void *), func_00282DF0(void *), func_00283CE0(s32);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282F20(void *, void *, f32);
/* The pointer and four FP inputs retain their physical EE ABI slots. */
extern void func_002AAC80(f32, f32, f32, f32, void *);
extern void func_002A7750(void *, s32, s32), func_002AD6F0(void *, void *, void *, void *);
extern s32 func_002B3868(void *), func_002E5DA0(s32, s32, void *, s32);
extern u32 func_L01_0031BC68(u32, u32, f32);
typedef struct { u8 pad[0x78]; u32 color; } ColorActor;
/* Moves a platform along its path towards a node, pulses its colour, and carries the hero with it. */
void func_L12_0041E3E8(u8 *self) {
    f32 oldpos[4], oldrot[4], temp[4], delta[4];
    u8 *st = *(u8 **)(self + 0x68);
    u16 flag = *(u16 *)(self + 0xb2);
    s32 savedBits;
    if (D_L12_0021EDF0.flags[(s16)flag] ||
        ((savedBits = D_0019B4A8[((s16)flag >> 1) + (gCurrentMapIndex << 10)]),
         (flag & 1) ? ((savedBits >> 4) & 7) : (savedBits & 7))) {
        MarkMobySpawned(self);
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
        UpdatePushableMoby(self, st + 0x50, 1.5f, 1.5f, 0.1f, *(s32 *)(st + 0xec));
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
        ApproachTargetWithBraking(angle, 0.0055555557f, 0.0055555557f, 0.06666667f, st + 0xf0);
        vec_scale_to_length(temp, delta, *(f32 *)(st + 0xf0));
        FastVecAdd(self + 0x10, self + 0x10, temp);
        if (angle < 0.001f) SetMobyState(self, 3, -1);
        break;
    }
    case 3:
        if (SetFirstPendingFlag(self)) PlaySoundFromClassBank(2, 0, self, 0x10e9);
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
        SoundAnchor *sound = (SoundAnchor *)(D_L12_001B3DA8 * 112 + (s32)gSoundState);
        if (sound->owner != D_L12_001B3DAC || !sound->active) {
            D_L12_001B3DA8 = PlaySoundFromClassBank(2, 0, self, 0x10e9);
            D_L12_001B3DAC = (s32)self;
        }
        }
    }
    FastVecSub(temp, self + 0x10, oldpos);
    CombineTransformsAndStore(st + 0xa0, temp, oldrot, self + 0xf0);
}
