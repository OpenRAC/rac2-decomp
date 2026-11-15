/* State update: advances the spin and two wobble angles, fades out on its trigger and keeps the sound slot. */
#include "common.h"

extern f32 D_L03_001B0050 __attribute__((sda));
extern f32 D_L03_001B0054 __attribute__((sda));
extern f32 D_L03_001B0058[2] __attribute__((sda));
extern char D_L03_00188660[];
typedef struct { f32 scale; f32 spin; f32 wobble[2]; f32 roll; f32 fade; s32 slot; } SpinState;
extern void func_002A7750(char *moby, s32 a1, s32 a2);
extern f32  func_00283B98(f32 moby, f32 a1);
extern void func_L00_002E6CF0(void *moby, void *a1);
extern void func_L03_003C6208(void);
extern s32  func_002B38B8(char *moby);
extern f32  func_002AA2E8(f32 *moby, f32 a1, f32 a2);
extern void func_002E59F8(s32 moby);
extern s32  func_002E5CF8(s32 moby, s32 a1, char *a2);

/* Updates the spinning, wobbling rotor object. It keeps turning, fades out when its trigger is on, and looks after its looping sound. */
void func_L03_003C5FE8(char *moby)
{
    char *self = moby;
    SpinState *state = *(SpinState **)(self + 0x68);

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(f32 *)(self + 0x2C) = *(f32 *)(*(s32 *)(self + 0x24) + 0x24) * state->scale;
        SetMobyState(self, 1, -1);
        *(u16 *)(self + 0x34) |= 1;
        *(u8 *)(self + 0x31) = 0;
        state->fade = 1.0f;
        break;
    case 1: {
        f32 angleScale = 0.000290888245f;
        f32 *speedTable = D_L03_001B0058;
        f32 *wobbleAngle = state->wobble;
        s32 i;

        state->spin = FastAddRotations(state->spin, D_L03_001B0050 * angleScale);
        state->roll = FastAddRotations(state->roll, D_L03_001B0054 * angleScale);
        for (i = 1; i >= 0; i--) {
            *wobbleAngle = FastAddRotations(*wobbleAngle, *speedTable * 0.000290888245f);
            wobbleAngle++;
            speedTable++;
        }
        AddDrawCallbackToList1(DrawSpinningRotor, self);
        if (IsThirdPendingFlagSet(self) != 0) {
            ApproachValue(&state->fade, 0.0f, 0.0333333351f);
            if (state->fade <= 0.0f) {
                SetMobyState(self, 2, -1);
                *(s32 *)(self + 0x98) = 0;
            }
        }
        break;
    }
    }
    if (*(u8 *)(self + 0x20) == 1) {
        char *soundSlot = D_L03_00188660 + state->slot * 0x70;

        if (*(char **)(soundSlot + 0x88) != self || *(u8 *)(soundSlot + 0x74) == 0)
            state->slot = PlayMobySound(0, 4, self);
    } else {
        s32 slotIndex = state->slot;

        if (slotIndex != -1) {
            char *soundSlot = D_L03_00188660 + slotIndex * 0x70;

            if (*(char **)(soundSlot + 0x88) == self && *(u8 *)(soundSlot + 0x74) != 0)
                StopSoundVoice(slotIndex);
        }
        state->slot = -1;
    }
}
