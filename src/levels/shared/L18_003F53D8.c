#include "common.h"
extern void *func_002A9640(void *, u32, s32);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002B0ED8(void *, void *, s32);
extern void func_L18_003F7AB8(u8 *);
extern void func_L18_003F74B8(u8 *, s32);
extern void func_002A6C58(u8 *, s32, s32);
extern s32 func_L18_0033B628(s32, s32, s32);
extern s32 func_002B3BA8(u8 *, s32, void *, s32, float, float);
extern void func_L18_003F8E30(u8 *);
extern s32 D_0018C0B4;
/* Checks if the Protopet was hit or lost its target, and switches its state when needed. */
void func_L18_003F53D8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *contact;
    u8 saved;
    u64 mode;
    contact = FindOwnedEffectSlot(object, 0x10000, 1);
    if (contact && *(u8 **)(contact + 0x20) && *(s16 *)(*(u8 **)(contact + 0x20) + 0xAA) == 0xF9E /* moby class 3998 */) {
        if (object[0x20] < 6 || object[0x20] == 19 || object[0x20] == 18) return;
        SetMobyState(object, 18, -1);
        return;
    }
    saved = object[0x94];
    if (ApplyDamageToObject(object, state + 0x50, 0)) {
        if (object[0x94] == 17 || object[0x94] == 8 || object[0x94] == 9 || object[0x94] == 16 || object[0x94] == 10 || object[0x94] == 7) object[0x94] = saved;
        if (object[0x94] != 14) UpdateGroupMembers(object);
    }
    object[0xA8] = 255;
    if (*(float *)(object + 0x18) < 90.0f || (*(float *)(state + 0x2A0) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x2A0))) EndCurrentAction(object, 0);
    if (state[0x2E] == 2) {
        EndCurrentAction(object, 1);
        return;
    }
    contact = *(u8 **)(state + 0x188);
    if (contact && *(s16 *)(contact + 0xAA) == 0xF59 /* moby class 3929 */) {
        SetDeathBits(object, 0, 1);
        goto stop;
    }
    mode = object[0x20];
    if (*(s32 *)(state + 0x180) > 300 && mode != 2) goto stop;
    if ((u8)mode >= 6 && *(s32 *)(state + 0x260) != -1 && !RunSlotHandler((s32)(object + 0x10), *(s32 *)(state + 0x260), 0)) {
stop:
        EndCurrentAction(object, 0);
        return;
    }
    *(s32 *)(state + 0x248) = SelectAimTarget_002B3BA8(object, *(s32 *)(state + 0x240), 0, 0, *(float *)(state + 0x244), 0.0f);
    if (*(u8 **)(state + 0x258)) SetReadyFlag(*(u8 **)(state + 0x258));
    if (D_0018C0B4 == 0x6F && (u32)(object[0x20] - 9) < 4) SetMobyState(object, 6, -1);
}
