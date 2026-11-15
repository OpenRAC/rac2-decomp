#include "common.h"

extern void func_L01_003CBFA8(u8 *);
extern s32 func_00283CF0(f32);
extern void func_002A7750(u8 *, s32, s32);
extern u8 *D_L01_001B255C;
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 D_00189EA0[], D_L01_001B94C0[];
extern u8 D_L01_001AFE18[] __attribute__((sda));
extern f32 D_L01_001B2F40;
extern u8 *func_002A9640(void *, s32, s32);
extern f32 func_002A96A0(void *, void *);
extern u8 *func_002AB1F0(void *);
extern void func_002AB800(void *, void *);
extern void func_002AB8C0(void *, void *);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern s32 func_002A77E0(s32);
extern void func_002ACB48(void *, f32);
extern f32 func_L01_003BAFB0(void);
extern f32 func_002A7878(f32, f32);
extern void func_002C19D8(void *, void *, u32, f32, f32);
extern void func_002B3BA8(void *, s32, s32, s32, f32, f32);
extern f32 func_00282E48(void *, void *);
extern void func_002A93B0(void *);

/* Applies incoming damage to the linked group or this object's timer, updates its
   animation and effects, and adjusts the nearby-object reaction and height.
   The isolated profile retains the timer branch's state + 0x50 calculation and
   keeps the shared floating-point branch labels on their hazard nops. */
/* Handles damage to the swamp monster parts and reacts with hit animations, pushes and bubbles. */
void func_L01_003CC280(u8 *moby)
{
    u8 pos[16] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *attacker, *groupMember, *hitRecord, *linked;
    u16 *memberList;
    f32 damage, pushStrength;
    s32 hitDuration, otherState, ignoresHit;
    s32 particleColor;
    u16 classId;

    if (moby[0x95] == 1 || ((moby[0x95] >= 5 && moby[0x95] <= 6) && 0.0f < *(f32 *)(state + 0x20))) {
        attacker = FindOwnedEffectSlot(moby, 0x10000, 0);
        if (*(short *)(state + 0x26) >= 1)
            attacker = 0;
        damage = UpdateAimTargetStrength(moby, attacker);
        if (attacker && 0.0f < damage && moby[0x95] >= 5) {
            if (*(s32 *)(state + 0xB0) != -1) {
                *(s32 *)(state + 0xC0) = 240;
                if (moby[0x21] != 0xFF) {
                    classId = *(u16 *)(*(u8 **)(attacker + 0x20) + 0xAA);
                    hitDuration = (classId == 0xCE4 /* moby class 3300 */ || classId == 0xCE5 /* moby class 3301 */) ? 60 : 0;
                    for (memberList = D_L01_001FB020[moby[0x21]];
                         moby[0x21] != 0xFF && moby[0x21] <= D_L01_001B2578[0] && memberList &&
                         ((memberList != 0 && (short)memberList[-1] >= 0) || memberList == D_L01_001FB020[moby[0x21]]); memberList++) {
                        groupMember = gMobyTable_L01 + ((*memberList & 0x7FFF) << 8);
                        if (!groupMember)
                            break;
                        hitRecord = GetMobyPrivateValue0(groupMember);
                        if (hitRecord) {
                            *(u16 *)(hitRecord + 6) = hitDuration;
                            *(f32 *)hitRecord -= damage;
                            hitRecord[0x17] = state[0x37];
                            *(s32 *)(hitRecord + 0x18) = *(s32 *)(state + 0x38);
                            *(u16 *)(hitRecord + 0x1C) = *(u16 *)(state + 0x3C);
                        }
                        groupMember[0xA8] = 0xFF;
                    }
                }
            } else {
                *(f32 *)(state + 0x20) -= damage;
            }
        }
        moby[0xA8] = 0xFF;

        if (0.0f < damage) {
            state[0x57] = FloatToInt(damage * 20.0f) + 100;
            StartColorFade(moby, state + 0x50);
        }
        if (moby[0x95] == 1 && attacker) {
            *(s32 *)(state + 0xBC) = 0;
            if (moby[0x20] == 0)
                SetMobyState(moby, 1, -1);
        } else {
            if (*(f32 *)(state + 0x20) < 0.0f ||
                (*(s32 *)(state + 0xB0) != -1 && (!(linked = D_L01_001B255C_base[0] + (*(s32 *)(state + 0xB0) << 8)) || (otherState = linked[0x20]) == 0xFE || otherState == 0xFD))) {
                ReleaseAttackSlot_L01_2(moby);
                if (moby[0x43] != 4)
                    StartAnimationBlended(moby, 4, 0, 10);
                *(u32 *)(state + 0x20) = 0;
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                SetMobyState(moby, 0, 7);
            } else {
                ignoresHit = 0;
                if (attacker && *(u8 **)(attacker + 0x20))
                    ignoresHit = *(short *)(*(u8 **)(attacker + 0x20) + 0xAA) == 0x47 /* moby class 71 */;
                if (!ignoresHit) {
                    if (1.0f <= damage) {
                        ReleaseAttackSlot_L01_2(moby);
                        if (moby[0x42] == 1) {
                            if (moby[0x43] != 3)
                                StartAnimationBlended(moby, 3, 5, 5);
                        } else if (moby[0x42] == 2) {
                            if (moby[0x43] != 3)
                                StartAnimationBlended(moby, 3, 0, 20);
                        } else if (moby[0x43] != 3) {
                            StartAnimationBlended(moby, 3, 2, 10);
                        }
                        *(u16 *)(moby + 0x34) &= 0xEFFF;
                        SetMobyState(moby, 0, 7);
                    }
                    if (0.1f < damage) {
                        FastVecSub(state + 0xA0, moby + 0x10, gHeroPosition);
                        pushStrength = (damage + damage + 3.0f) * 0.016666668f;
                        if (0.20000002f < pushStrength)
                            pushStrength = 0.20000002f;
                        vec_scale_to_length(state + 0xA0, state + 0xA0, pushStrength);
                        *(s32 *)(state + 0xA8) = 0;
                    }
                }
            }
        }
    } else {
        moby[0xA8] = 0xFF;
    }
    UpdateColorFade(moby, state + 0x50);
    if (0.0f < *(f32 *)(moby + 0x48) && moby[0x95] != 2 && moby[0x31] && RandomIntBelow(9) == 0) {
        qcopy(pos, moby + 0x10);
        AddRandomOffsetToVector(&pos, 0.15f);
        ((f32 *)pos)[2] = GetWaterHeight();
        damage = RandomFloatRange(0.5f, 3.0f);
        particleColor = ((RandomIntBelow(6) + 20) << 24) | 0x5060;
        SpawnDriftingParticle_002C19D8(&pos, D_L01_001AFE18, particleColor, damage, 12000.0f);
    }
    SelectAimTarget_002B3BA8(moby, *(s32 *)(state + 0xF0), 0, moby[0x95] < 5, 0.0f, 0.0f);
    otherState = moby[0x31];
    if (otherState && fast_vec_dist(moby + 0x10, D_L01_001B94C0) < 48.0f) {
        UpdateMobyGroundCheck(moby);
        moby[0x6F] = 45;
    }
    *(f32 *)(moby + 0x74) = 1.0f;
    *(f32 *)(moby + 0x70) = 109.0f - *(f32 *)(moby + 0x18);
    if (moby[0x95] >= 3 && moby[0x95] <= 7)
        D_L01_001B2F40 = 0.20943953f;
}
