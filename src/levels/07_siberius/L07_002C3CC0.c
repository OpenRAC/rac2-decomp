/* func_L07_002C3CC0 (Siberius): the hero's state-transition decider, a 141-way switch on the state at
   0x2294 (jump table 0x002A0E30; 15892 bytes, level 7 only).  One function: one prologue
   (frame 0xA0), one return.

   Ported from Dobbo's func_L09_002C9738 (symbols renamed by aligning the retail listings);
   states 0x30 and 0x6D from the func_L00_002CB3A8 draft and 0x7C from func_L19_002CAAB0; no 0x32-0x36, 0x72, 0x73, 0x79.  An older version: the head calls only func_L00_002C9448 and func_L00_002C8C00, case 0x2 has no 0x22B9/0x70 blocks, 0x16 no 0x1495 test.
   Case 0x6D adds the row offset as `rec -= -off` after `rec = table`: cse treats a pointer
   known to hold a constant address as the second operand of a PLUS and would swap it, while
   the MINUS keeps retail's `addu v0, table, offset` order.  Idioms behind the other spots:
   func_L19_002CAAB0's and func_L04_002EDBC8's headers.

   The unit's flags (config/cflags.txt): -G16 -Wa,-G16 for the 16-byte sda records,
   -frac2-zero-ti-por, -frac2-qcopy -frac2-qcopy-barrier for the 128-bit copies,
   -frac2-hazard-labels for the branches onto compare hazard nops.
   See docs/build/compiler-notes.md for each option. */

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef TI128 s128;
#define NULL ((void *)0)
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
#define M2C_ERROR(d) (0)
#define M2C_UNK s32
extern char D_00138180[];
extern char D_00139568[];
extern char D_00188660[];
extern char D_00189E20[];
extern char D_00189F10[];
extern u8 D_001A7BB2[] MACRO_ADDR;
extern u8 D_001A7AF8[] MACRO_ADDR;
extern s32 D_001A79F0;
extern f32 D_L07_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L07_001A7DDC;
extern s32 D_L07_001A8FF4;
extern f32 D_L07_001B1F28;
extern s32 D_L07_001A8FB4;
extern s32 D_L07_001B1E04;
extern s32 D_L07_001A8A48;
extern u8 D_L07_001A7CA0[16] __attribute__((sda));
extern u8 D_L07_001A7CB0[16] __attribute__((sda));
extern s32 D_L07_001A7DD8[2] __attribute__((sda));
extern char D_L07_0025C000[];
extern char D_L07_0025C210[];
extern char D_L07_0025DD90[];
extern char D_L07_002628A0[];
extern char D_L07_001B90C0[];
s32 func_002761F8(void *, void *, s32, void *, s32);
s32 func_00277258(void *, s32, void *, f32);
s32 func_00282948(void *);
s32 func_00282978(s16 *);
f32 func_00282C48(f32);
void func_00282CC0(void *, void *, void *);
void func_00282D30(void *, void *, f32);
f32 func_00282DF0(void *);
f32 func_00282E20(void *);
f32 func_00282E48(void *, void *);
f32 func_00282E80(void *, void *);
void func_00282F20(void *, void *, f32);
f32 func_00283180(f32);
f32 func_00283198(f32);
f32 func_00283B98(f32 a0, f32 a1);
f32 func_00283C80(f32 a0, f32 a1);
s32 func_00283CF0(f32);
void func_0028B3D0(s32, s32, void *, void *, void *, s32, s32);
void func_0028BDB0(u8 *object);
void func_0028BE00(s8 *);
s32 func_0028C6D0(s8 *);
void func_0028CC98(void *a0);
void func_0028CCE0(u8 *object);
void func_0028D1E8();
void func_0029FCC0(s8 *a0, s32 a1, s8 *a2);
void func_002A7470(u8 *object, s32 animation, s32 frame, s32 rate);
s32 func_002A7820(s32 a0, s32 a1);
f32 func_002A7878(f32 a0, f32 a1);
f32 func_002AA2E8(f32 *value, f32 target, f32 step);
void func_002AC9F8(f32 *, f32);
void func_002E59F8(s32 a0);
s32 func_L01_002A7248(s32 arg);
u32 func_L00_002A4EF0(u32 param_1);
void func_L00_002A6188(void);
void func_L00_002A61C8(s32 kind, s32 side, s32 play_sound, s32 duration);
void func_L00_002A6708(void);
void func_L00_002A9E30(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_L00_002AABE0(s32 dust, s32 debris, s32 model);
s32 func_L00_002AB108(f32 *out, f32 scale, f32 amount);
s32 func_L01_002AE128(s8 *, s8 *, s8 *);
s32 func_L00_002ADEA0(s32 index);
void func_L00_002AF7D0(void);
void func_L00_002B30E8(void);
s32 func_L00_002B3248(u8 *object);
s32 func_L00_002B3268(f32 x);
s32 func_L00_002B3998(f32 value);
void func_L00_002B39F0(s32, f32);
void func_L01_002B46A0(void);
s32 func_L00_002B9B88(s32 index, s32 flags);
s32 func_L00_002C3A40(void);
s32 func_L07_002BE770(s32, s32);
void func_L01_002C1988(s32 a0);
s32 func_L00_002C8C00(void);
s32 func_L00_002C8CB0(void);
s32 func_L00_002C8E10(void);
s32 func_L00_002C9448(void);
s32 func_L00_002C9FC8(s32 arg0, s32 arg1);
void func_L00_002CA0B0(void);
void func_L00_002CA478(void);
s32 func_L00_002CA4E0(s32 *selected);
void func_L01_002C2CF0(void);
s32 func_L00_002CAB08(void);
s32 func_L00_002CAD90(void);
s32 func_L00_002CAF20(void);
void func_L00_002CB038(void);
void func_L00_002CB218(void);
void func_L00_002CB2D8(void);
void func_L00_002D1AE8(void);
void func_L18_002C4000(void);
void func_L00_002D2168(s32 a0, s32 a1, f32 f12);
void func_L00_002D24B8(void);
void func_L00_002D24D0(s32 value);
f32 func_L01_002C81D0(f32 time, f32 acceleration, f32 height);
void func_L00_002D3248(s16, u8, u8, u8, f32, f32);
void func_L00_002D36E0(f32 *p, s32 flag, f32 x, f32 y, f32 z);
f32 func_L00_002D3B00(s8 *in);
void func_L00_002D3B58(void *dst, void *src, f32 k);
f32 func_L00_002D3D98(f32 *a0, f32 *a1, s32 *out, f32 scale);
void func_L00_0030C710(s32 argument);
void func_L00_0030C7F8(s32 argument);
f32 func_L00_0031B9F8(f32 *a0, f32 *a1, s32 *a2, f32 factor);
f32 func_L00_0031CDD0(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
void func_L00_003294F0(u8 *entity, s32 enabled);
s32 func_L00_0032EF10(u32 mask, s32 arg1, s32 *out);
void *func_L00_0033C0D0(s8 *object,void *position,f32 *velocity,s32 *config,s32 flag);
s32 func_L00_00341820(void *path, void *out, s32 *index, f32 *offset, s32 wrap, f32 step);
s32 func_L00_00341FA8(void *, void *, void *, s32 *, f32 *, s32, f32, f32, f32);
void func_L00_0038B888(void *position,s32 count);
s32 func_L00_004272A0(void);
s32 func_L01_002B3788(s32);
s32 func_L00_002AD868(s8 *, void **, s128 *, void *, void *, s32 *, void *, s32, s32);

/* Looks at the buttons and the world each frame and decides when the hero should switch to a new state. */
void func_L07_002C3CC0(void) {
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    s32 selectedMove;
    s32 specialCost;
    s32 sp48;
    f32 sp4C;
    void *sp50;
    void *sp54;
    void *sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 hitDistance;
    s32 specialCostLimit;
    s32 sp70;
    void *heroObject;
    s32 phaseBefore;
    s32 movementBefore;
    s32 animationBefore;
    s32 temp_a0_11;
    s32 prevState;
    s32 padButtons;

    heroObject = FLD(gHeroState, void *, 0x2290);
    phaseBefore = FLD(gHeroState, s32, 0x229C);
    movementBefore = FLD(gHeroState, s32, 0x2298);
    animationBefore = FLD(heroObject, u8, 0x43);
    if (ApplyHazardContactToHero_L01(1) != 0) {
        goto end;
    }
    UpdateHeroHeldTarget();
    if (FLD(gHeroState, s32, 0x24CC) <= 0) {
        if ((FLD(gHeroState, u32, 0x2294) == 0) || (FLD(gHeroState, u32, 0x2294) == 2)) {
            EnterHeroState_L07(0x39, 1);
            goto end;
        }
    }
    if (ProcessHeroEquippedItemInput() != 0) {
        goto end;
    }
    if (TryStartHeroTransition() != 0) {
        goto end;
    }
    if (((FLD(gPadState, s32, 0x1A4) & 0x10) || (FLD(gPadState, s32, 0x1C4) & 0x10)) && (FLD(gHeroState, u8, 0x123C) != 2) && (D_L07_001A8FB4 == 0) && (D_001A7BB2[1] == 0) && (D_L07_001B1E04 >= 8)) {
        if (((FLD(gHeroState, u8, 0x22BC) == 0) || (FLD(gHeroState, u8, 0x22B4) == 1) || (FLD(gHeroState, s16, 0x1D2) != 0))
            && ((FLD(gHeroState, u8, 0x22B7) == 0) || (FLD(gHeroState, u8, 0x22B4) == 1) || (FLD(gHeroState, s16, 0x1D2) != 0))) {
            if ((FLD(gHeroState, u8, 0x22B4) == 0) || (FLD(gHeroState, u8, 0x22B4) == 3)) {
                if (FLD(gHeroState, s16, 0x24FA) != 0) {
                    FLD(gHeroState, s16, 0x24F6) = 0x1B;
                } else {
                    FLD(gHeroState, s16, 0x24F6) = 0xF;
                }
                SetHudSlotContents(0x23, 0, InitMenuPanelLayout, UpdateRadialWeaponSelect, DrawWeaponWheel, 0, 0);
                CallLoadedModuleHandlerWithArg_0034B000(0x168);
                func_L00_0030C710(0xB4);
            }
        }
    }
    UpdateHeroButtonHoldTimers();
    ApplyPendingHeroChange();
    if (FLD(gHeroState, f32, 0x88) < D_L07_001B1F28) {
        if ((FLD(gHeroState, f32, 0x31C) > 2.0f) && (FLD(gHeroState, u8, 0x22B4) != 2) && (FLD(gHeroState, u32, 0x2294) != 0x74)) {
            EnterHeroState_L07(0x74, 1);
            goto end;
        }
    }
    switch (FLD(gHeroState, u32, 0x2294)) {
    case 0x0:
    {
        s32 anim;
        u8 *obj;
        if ((FLD(gPadState, s32, 0x1A0) & 4) && (FLD(gHeroState, s32, 0x1500) == 0) && (GetLevelSavedValue() == 0)) {
            EnterHeroState_L07(1, 1);
            break;
        }
        ClearHeroQueuedAnimation();
        if (FLD(gHeroState, u8, 0x24EF) != 0) {
            EnterHeroState_L07(0x82, 1);
            break;
        }
        {
        s32 one = 1;
        FLD(gHeroState, s8, 0x1456) = 0;
        if (FLD(gHeroState, s32, 0x1334) == 2) {
            obj = FLD(gHeroState, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != one)) {
                StartAnimationBlended(obj, one, 0, 7);
            }
            obj = FLD(gHeroState, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != 1)) {
                StartAnimationBlended(obj, 1, 0, 7);
            }
        }
        }
        if ((FLD(D_L07_0025C210, f32, 0x258) > 0.6108653f) || (FLD(D_L07_0025C210, f32, 0x254) > 0.43633235f)) {
            obj = FLD(gHeroState, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                StartAnimationBlended(obj, 1, 0, 0xC);
            }
            obj = FLD(gHeroState, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                StartAnimationBlended(obj, 1, 0, 0xC);
            }
        }
        anim = ReturnArgument_L00(FLD(heroObject, u8, 0x43));
        if (anim == GetHeroWeaponAnimationId_L01(0)) {
            if (ChooseHeroIdleAnimation(&selectedMove) != 0) {
                u8 *rec;
                FLD(gHeroState, s16, 0x208) = 0x78;
                FLD(gHeroState, s32, 0x248C) = selectedMove;
                rec = D_L07_0025C000 + selectedMove * 0x70;
                FLD(rec, s32, 0x60) = FLD(rec, f32, 0x5C) * 60.0f;
                if (FLD(rec, s32, 0x44) != 0) {
                    EnterHeroState_L07(0x3C, 1);
                } else {
                    set_hero_animation(FLD(rec, s32, 0x48), 0, 12.0f);
                }
            }
        } else if (FLD(gHeroState, s32, 0xC28) & 2) {
            s32 keep = 0;
            if ((FLD(gHeroState, u8, 0x22B8) != 0) && (FLD(gHeroState, u8, 0x22BA) != 0) && ((FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) == FLD(gHeroState, s32, 0x24B0)) || (FLD(gHeroState, s32, 0xE98) != 0))) {
                keep = 1;
            }
            if (keep == 0) {
                FLD(gHeroState, s8, 0x22B8) = 0;
                if (GetHeroWeaponAnimationId_L01(0) == 0x51) {
                    set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 18.0f);
                } else {
                    set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, -2.0f);
                }
            }
        }
        if (FLD(gHeroState, s32, 0x1B8) >= 0xB) {
            u8 *o2 = FLD(gHeroState, u8 *, 0x1314);
            if ((o2 != NULL) && (FLD(o2, u8, 0x43) == 1) && (FastFloatHelperD(gHeroState + 0x24E8) != 0) && (FLD(D_L07_0025C210, f32, 0x258) < 0.5585054f) && (FLD(D_L07_0025C210, f32, 0x254) < 0.3490659f) && (FLD(gHeroState, s32, 0x1334) == 2)) {
                FLD(gHeroState, s32, 0x24E8) = RandomIntRange(0x6E, 0x10E);
                SetLinkedObjectsAnimation();
            }
        }
        if ((FLD(gHeroState, u8, 0x22B8) != 0) && (FLD(gHeroState, s32, 0xC2C) == 0) && (FLD(gHeroState, u8, 0x22BA) != 0) && (FLD(gHeroState, s16, 0x24EC) == 0)) {
            s32 slot = hero_slot_item_id(0);
            if (slot != FLD(gHeroState, s32, 0x24B4)) {
                cancel_hero_item_animation();
            } else {
                s32 want = FLD(D_L07_002628A0 + ((u8 *)gItemSlotToRecord)[slot] * 0xE0, s32, 0x28);
                if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) != want) {
                    if (FLD(gHeroState, s32, 0xE98) != 0) {
                        FLD(gHeroState, s32, 0xEA4) = 1;
                    }
                    FLD(gHeroState, s32, 0x24B0) = want;
                    set_hero_animation(want, 0, -4.0f);
                }
            }
        }
        ResolveStickInputToDirection(0, 1.0f);
        if ((FLD(gHeroState, u8, 0x149A) != 0) && (FLD(gHeroState, s16, 0x34C) == 0)) {
            EnterHeroState_L07(0x76, 1);
            break;
        }
        if ((FLD(gHeroState, s16, 0x34E) >= 5) && (FLD(gHeroState, f32, 0x31C) > 0.4f)) {
            if ((FLD(gHeroState, s32, 0x22A0) != 8) || (FLD(gHeroState, s32, 0x1B8) >= 0xF)) {
                EnterHeroState_L07(6, 1);
            }
            break;
        }
        if (FLD(gHeroState, s16, 0x1E0) != 0) {
            break;
        }
        {
            s32 ok = 1;
            if ((FLD(gHeroState, s32, 0x22A0) == 1) || (FLD(gHeroState, s32, 0x22A0) == 0x1D)) {
                if (FLD(gHeroState, s32, 0x1B8) <= 4) {
                    ok = 0;
                }
            }
            if (ok && (FLD(gHeroState, s16, 0x348) != 1)) {
                if (TryStartHeroMoveFromBuffer((FLD(gHeroState, s16, 0x1EE) != 0) ? 1 : 7, 0) != 0) {
                    break;
                }
            }
        }
        if ((FLD(gHeroState, s16, 0x348) == 1) && (D_L07_001A8FF4 == 0) && (PadPressedWithin(0x40, 7, NULL) != 0)) {
            EnterHeroState_L07(0x6E, 1);
            break;
        }
        if ((FLD(gPadState, s32, 0x1A0) & 8) && (FLD(gHeroState, s32, 0x340) != 0)) {
            if ((FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) != 0x1A) || (FLD(gHeroState, f32, 0xC38) >= 108.0f)) {
                EnterHeroState_L07(4, 1);
                break;
            }
        }
        {
            s32 go = 1;
            s32 turned;
            if (((FLD(gHeroState, s32, 0x22A0) == 1) || (FLD(gHeroState, s32, 0x22A0) == 0x1D)) && (FLD(gHeroState, s32, 0x1B8) < 0x18) && (FLD(gHeroState, s16, 0x348) != 1)) {
                ResolveStickInputToDirection(0, 1.0f);
                if ((FastDiffRots(FLD(gHeroState, f32, 0x1A0), FLD(D_L07_001B90C0, f32, 0x158)) > 1.2217306f) && (fast_vec_dist(gHeroState + 0x80, D_L07_001B90C0 + 0x140) < 2.5f)) {
                    go = 0;
                }
            }
            turned = IsHeroTurnedPastAngle(0.17453295f);
            if (go == 0) {
                break;
            }
            if ((turned != 0) || (FLD(gHeroState, f32, 0x24B8) > 0.22f)) {
                s32 side = FLD(gHeroState, u8, 0x149D);
                PlayFootstepSoundAndDust(side, 0, 0, 0x1E);
                PlayFootstepSoundAndDust(side, 1, 0, 0x1E);
                EnterHeroState_L07(2, 1);
            }
        }
        break;
    }
    case 0x3C:
        if ((FLD(gPadState, s32, 0x1A0) & 4) && (FLD(gHeroState, s32, 0x1500) == 0) && (GetLevelSavedValue() == 0)) {
            EnterHeroState_L07(1, 1);
            break;
        }
        if ((FLD(gHeroState, s16, 0x34E) != 0) || ((padButtons = FLD(gPadState, s32, 0x1A0)) & 0x40) || (padButtons & 8)) {
            EnterHeroState_L07(0x3D, 1);
            break;
        }
        RefreshHeroSpeedFromTimer();
        if (FLD(gHeroState, f32, 0x1B0) > 0.0f) {
            EnterHeroState_L07(0x3D, 1);
            break;
        }
        if (FLD(gHeroState, s32, 0xC28) & 2) {
            ClearHeroTargetFlags();
            EnterHeroState_L07(0, 1);
        }
        break;
    case 0x3D:
        if (FLD(gHeroState, s32, 0x1B8) < 9) {
            break;
        }
        ClearHeroTargetFlags();
        if (FLD(gHeroState, s16, 0x34E) != 0) {
            EnterHeroState_L07(6, 1);
            break;
        }
        if (TryStartHeroMoveFromBuffer(7, 0) != 0) {
            break;
        }
        if (FLD(gPadState, s32, 0x1A0) & 8) {
            EnterHeroState_L07(4, 1);
            break;
        }
        RefreshHeroSpeedFromTimer();
        if (FLD(gHeroState, f32, 0x1B0) > 0.0f) {
            EnterHeroState_L07(2, 1);
            break;
        }
        EnterHeroState_L07(0, 1);
        break;
    case 0x39:
    case 0x43:
    case 0x5F:
    case 0x67:
    case 0x7D:
    case 0x7F:
        if ((FLD(gHeroState, s32, 0xC28) & 2) || (FLD(gHeroState, u8, 0x22C0) != 0)) {
            if (FLD(gHeroState, s16, 0x21E) != 0) {
                FLD(gHeroState, u8, 0x22C0) = 1;
                FLD(gHeroState, s32, 0xC20) = 0;
                FastDecTimer(gHeroState + 0x21E);
                return;
            }
            RecordHeroPlayCounters();
            return;
        }
        break;
    case 0x7C:
        if (FLD(gHeroState, s32, 0x1B8) < 0xDD) {
            break;
        }
        RecordHeroPlayCounters();
        return;
    case 0x1:
    {
        u8 *p;
        s32 ok;
        s32 late;
        s32 anim;
        if ((FLD(gHeroState, u8, 0x22B4) == 0) && ((FLD(gHeroState, u8, 0x22BA) == 0) || (FLD(gHeroState, u8, 0x22B5) != 0))) {
            if (FLD(gPadState, s32, 0x1A0) & 8) {
                set_hero_animation(0xD, 0, 8.0f);
            } else {
                s32 anim0 = GetHeroWeaponAnimationId_L01(1);
                if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) != anim0) {
                    set_hero_animation(anim0, 0, 8.0f);
                }
            }
        }
        p = FLD(gHeroState, u8 *, 0x1220);
        ok = 1;
        if ((p != NULL) && (IsMobyClass71(p) != 0)) {
            if (FLD(p, u8, 0x20) != 0) {
                ok = 0;
            }
        }
        late = 0;
        if (FLD(gHeroState, u8, 0x22B5) == 0) {
            late = FLD(gHeroState, s32, 0x1B8) >= 0x1F;
        }
        if ((!(FLD(gPadState, s32, 0x1A0) & 4) && ok) || late) {
            if (FLD(gHeroState, u8, 0x22B4) != 0) {
                StartHeroMoveStateOneOrTwo(0);
            } else if (FLD(gPadState, s32, 0x1A0) & 8) {
                EnterHeroState_L07(4, 1);
            } else {
                EnterHeroState_L07(0, 0);
                anim = GetHeroWeaponAnimationId_L01(1);
                if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 8.0f);
                }
            }
        }
        break;
    }
    case 0x2F:
        if (!(FLD(gPadState, s32, 0x1A0) & FLD(gHeroState, s32, 0x1230)) && (FLD(gHeroState, s16, 0x1EC) == 0)) {
            if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) == 0x36) {
                EnterHeroState_L07(0, 0);
            } else {
                EnterHeroState_L07(0, 1);
            }
        }
        break;
    case 0x14:
    {
        u8 *rec;
        s32 frames;
        if (FLD(gHeroState, u32, 0x2294) == 0x14) {
            s32 n = FloatToInt(SolveHeroFallCollisionTime(60.0f, 0.036111113f, -1.0f));
            f32 c00 = FLD(gHeroState, f32, 0xC00);
            s32 top = 0x1A;
            if (c00 == 0.0f) {
                FLD(gHeroState, f32, 0xC20) = 0.33f;
            } else if ((c00 != 0.0f) && (FLD(gHeroState, s16, 0x34E) != 0) && (n != 0) && (((f32)top - FLD(gHeroState, f32, 0xC38)) > 1.0f)) {
                AdjustHeroAnimationSpeedForTargetFrame((f32)top, (f32)n, 0.5f, -1.0f);
                if ((FLD(gHeroState, f32, 0x31C) < 0.7f) && (FLD(gHeroState, f32, 0xC20) < 0.75f)) {
                    FLD(gHeroState, f32, 0xC20) = 0.75f;
                }
            } else if ((FLD(gHeroState, s16, 0x34E) == 0) && (FLD(gHeroState, f32, 0xC38) < (f32)top)) {
                FLD(gHeroState, f32, 0xC20) = 2.0f;
            } else {
                FLD(gHeroState, f32, 0xC20) = 1.0f;
            }
        }
        rec = D_L07_0025DD90 + FLD(gHeroState, s16, 0xBFC) * 0x2C;
        frames = (FloatToInt(FLD(gHeroState, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        if ((f32)FLD(rec, s32, 0x14) < FLD(gHeroState, f32, 0xC38)) {
            if (FLD(gHeroState, s32, 0xC2C) != 0) {
                break;
            }
            if (PadPressedWithin(0x40, frames, NULL) != 0) {
                if (!(FLD(gPadState, s32, 0x1A0) & 8)) {
                    EnterHeroState_L07(7, 1);
                    break;
                }
                if (ChooseHeroJumpOrRollMove() != 0) {
                    break;
                }
            }
        }
        if ((FLD(gHeroState, s32, 0xC2C) == 0) && ((f32)FLD(rec, s32, 0x18) < FLD(gHeroState, f32, 0xC38))) {
            EnterHeroState_L07(0, 0);
        }
        break;
    }
    case 0x13:
    case 0x15:
    {
        u8 *rec = D_L07_0025DD90 + FLD(gHeroState, s16, 0xBFC) * 0x2C;
        s32 frames = (FloatToInt(FLD(gHeroState, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        u32 st = FLD(gHeroState, u32, 0x2294);
        s32 lim;
        f32 h;
        if (st == 0x15) {
            frames = 8;
        }
        if ((f32)FLD(rec, s32, 0x14) < FLD(gHeroState, f32, 0xC38)) {
            if (FLD(gHeroState, s32, 0xC2C) != 0) {
                goto tail13;
            }
            if ((st != 0x15) || (FLD(gHeroState, s16, 0x348) != 1)) {
                if (PadPressedWithin(0x40, frames, NULL) != 0) {
                    if (!(FLD(gPadState, s32, 0x1A0) & 8)) {
                        EnterHeroState_L07(7, 1);
                        break;
                    }
                    if (ChooseHeroJumpOrRollMove() != 0) {
                        break;
                    }
                }
            }
        }
        if (FLD(gHeroState, s32, 0xC2C) != 0) {
            goto tail13;
        }
        if ((FLD(gHeroState, f32, 0xC38) > 34.0f) && (FLD(gHeroState, f32, 0x24B8) > 0.9f)) {
            EnterHeroState_L07(2, 0);
            set_hero_animation(3, D_L07_001A7DD8[FLD(gHeroState, s32, 0x2298)], 13.0f);
            break;
        }
        if (FLD(gHeroState, s32, 0xC2C) != 0) {
            goto tail13;
        }
        lim = FLD(rec, s32, 0x18);
        h = FLD(gHeroState, f32, 0xC38);
        if ((f32)lim < h) {
            if (FLD(gHeroState, f32, 0x24B8) > 0.8f) {
                EnterHeroState_L07(2, 1);
                break;
            }
            if ((f32)(lim + 5) < h) {
                EnterHeroState_L07(0, 0);
                break;
            }
            if (FLD(gHeroState, s32, 0xC28) & 2) {
                EnterHeroState_L07(0, 0);
            }
            break;
        }
    tail13:
        if (FLD(gHeroState, u32, 0x2294) == 0x15) {
            if (FLD(gHeroState, s32, 0x1248) != 0xA) {
                EnterHeroState_L07(0, 1);
                break;
            }
            if ((FLD(gHeroState, s32, 0x1B8) >= 0x65) && (FLD(gHeroState, s32, 0xC44) < 0x1A)) {
                SetHeroAnimationMode(2);
                FLD(gHeroState, s32, 0xC44) = 0x1A;
            }
        }
        break;
    }
    case 0x83:
        if (FLD(gHeroState, f32, 0xC38) > 37.0f) {
            if (FLD(gHeroState, s32, 0xC2C) != 0) {
                goto tail83;
            }
            if (PadPressedWithin(0x40, 7, NULL) != 0) {
                if (!(FLD(gPadState, s32, 0x1A0) & 8)) {
                    EnterHeroState_L07(7, 1);
                    break;
                }
                if (ChooseHeroJumpOrRollMove() != 0) {
                    break;
                }
            }
        }
        if ((FLD(gHeroState, s32, 0xC2C) == 0) && (FLD(gHeroState, f32, 0xC38) > 37.0f)) {
            EnterHeroState_L07(0, 0);
            set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 15.0f);
            break;
        }
    tail83:
        if ((FLD(gHeroState, u32, 0x2294) == 0x15) && (FLD(gHeroState, s32, 0x1B8) >= 0x65) && (FLD(gHeroState, s32, 0xC44) < 0x1A)) {
            SetHeroAnimationMode(2);
            FLD(gHeroState, s32, 0xC44) = 0x1A;
        }
        break;
    case 0x77:
        if (FLD(gHeroState, s32, 0xC28) & 2) {
            EnterHeroState_L07(0, 1);
        }
        break;
    case 0x2:
    case 0x2E:
    case 0x70:
    {
        s32 n;
        s32 turned;
        u32 st;
        if ((FLD(gHeroState, u8, 0x40E) != 0) && ((FLD(heroObject, f32, 0x44) > 0.9f) || (FLD(heroObject, u8, 0x42) != 0xFF))) {
            FLD(gHeroState, u8, 0x40E) = 0;
        }
        if ((FLD(gHeroState, u8, 0x149A) != 0) && (FLD(gHeroState, s16, 0x34C) == 0)) {
            EnterHeroState_L07(0x76, 1);
            break;
        }
        if ((FLD(gHeroState, s16, 0x34E) >= 5) && ((FLD(gHeroState, s32, 0x22A4) != 0x12) || (FLD(gHeroState, u8, 0x22B9) == 0)) && (FLD(gHeroState, f32, 0x31C) > 1.35f) && (CheckStepAheadOfHero() == 0)) {
            EnterHeroState_L07(6, 1);
            break;
        }
        n = 9;
        if (FLD(gHeroState, s16, 0x1EE) != 0) {
            n = 1;
        }
        if ((PadPressedWithin(0x40, n, NULL) != 0) && ((FLD(gHeroState, s16, 0x34E) < 5) || (FLD(gHeroState, s16, 0x202) != 0))) {
            ResolveStickInputToDirection(0, 1.0f);
            if (TryStartHeroMoveFromBuffer(n, 1) != 0) {
                break;
            }
            if (FLD(gHeroState, f32, 0x24B8) > 0.85f) {
                if (FLD(gHeroState, s16, 0x1454) == 0) {
                    EnterHeroState_L07(9, 1);
                } else {
                    EnterHeroState_L07(7, 1);
                }
            } else {
                EnterHeroState_L07(7, 1);
            }
            break;
        }
        if (FLD(gHeroState, s16, 0x34E) != 0) {
            break;
        }
        if (((FLD(gHeroState, u8, 0x1492) == 0) || ((FLD(gHeroState, f32, 0x174) < 0.033333335f) && (FLD(gHeroState, f32, 0x320) < 0.087266475f))) && (FLD(gPadState, s32, 0x1A0) & 4) && (FLD(gHeroState, s32, 0x1500) == 0) && (GetLevelSavedValue() == 0)) {
            EnterHeroState_L07(1, 1);
            break;
        }
        if (FLD(gPadState, s32, 0x1A0) & 8) {
            EnterHeroState_L07(4, 1);
            break;
        }
        turned = IsHeroTurnedPastAngle(0.03490659f);
        st = FLD(gHeroState, u32, 0x2294);
        if (st == 2) {
            if (((FLD(gHeroState, f32, 0x24B8) < 0.17f) || (FLD(gHeroState, s16, 0x1E0) != 0)) && (turned == 0) && ((FLD(gHeroState, s32, 0x410) == 0) || (FloatAbs(FLD(gHeroState, f32, 0x1A8)) < 0.017453294f))) {
                s32 anim;
                if (TryStartHeroGrab() != 0) {
                    break;
                }
                if (EnterHeroState_L07(0, 0) == 0) {
                    break;
                }
                ClampVectorLength(gHeroState + 0x160, 0.025000002f);
                if (FLD(gHeroState, f32, 0x1B4) > 0.025000002f) {
                    FLD(gHeroState, f32, 0x1B4) = 0.025000002f;
                }
                anim = GetHeroWeaponAnimationId_L01(1);
                if (anim == 0x51) {
                    set_hero_animation(0x51, 0, 15.0f);
                } else {
                    set_hero_animation(anim, 0, -1.0f);
                }
            } else {
                UpdateHeroAnimationScale();
            }
        }
        break;
    }
    case 0x7B:
    {
        s32 one = 1;
        s32 flag = 0;
        if (FLD(gHeroState, s16, 0x348) != 0) {
            flag = 1;
        }
        if (!(FLD(gPadState, s32, 0x1A0) & 8)) {
            if (FLD(gHeroState, s32, 0x1B8) >= 0x3D) {
                flag = one;
            }
        }
        if (FLD(gHeroState, u8, 0x22B8) != 0) {
            flag = one;
        }
        if (flag != 0) {
            if (FLD(gHeroState, s32, 0x2304) != 0) {
                FLD(gHeroState, s32, 0x2320) = one;
            }
            PlayHeroSound(9, 0);
            FLD(gHeroState, s16, 0x1E0) = 0x1E;
            EnterHeroState_L07(3, 0);
            set_hero_animation(6, 4, 11.0f);
        } else {
            if (FLD(gHeroState, u8, 0x287) != 0) {
                f32 a = FastVecLength(gHeroState + 0x110);
                if (a < FastVecLength(gHeroState + 0xF0) * 0.75f) {
                    EnterHeroState_L07(0x77, 1);
                    break;
                }
                if (TestHeroReachBlend(NULL, 1.0f, 1.25f) != 0) {
                    EnterHeroState_L07(0x77, 1);
                    break;
                }
            }
            *(s128 *)v30 = 0;
            v30[0] = -0.083333336f;
            TransformMobyJointToWorld(FLD(gHeroState, s8 *, 0x2290), 0x16, (s8 *)v10);
            TransformMobyJointToWorld(FLD(gHeroState, s8 *, 0x2290), 0x17, (s8 *)v20);
            SpawnObjectRelativeParticle(FLD(gHeroState, s8 *, 0x2290), v10, v30, (s32 *)D_L07_001A7CA0, 1);
            SpawnObjectRelativeParticle(FLD(gHeroState, s8 *, 0x2290), v10, v30, (s32 *)D_L07_001A7CB0, 1);
            SpawnObjectRelativeParticle(FLD(gHeroState, s8 *, 0x2290), v20, v30, (s32 *)D_L07_001A7CA0, 1);
            SpawnObjectRelativeParticle(FLD(gHeroState, s8 *, 0x2290), v20, v30, (s32 *)D_L07_001A7CB0, 1);
        }
        break;
    }
    case 0x62:
        if (vec_distance_xy(gHeroState + 0x80, gHeroState + 0x18A0) < 0.2f) {
            if ((FLD(gHeroState, f32, 0x170) < 0.045f) && (FastDiffRots(FLD(gHeroState, f32, 0x98), FLD(gHeroState, f32, 0x18AC)) < 0.03490659f)) {
                EnterHeroState_L07(0x64, 1);
                break;
            }
            if ((FLD(gHeroState, u8, 0x22B4) != 0) && (FLD(gHeroState, f32, 0x170) >= 0.045f)) {
                EnterHeroState_L07(0x63, 1);
            }
        } else {
            UpdateHeroAnimationScale();
        }
        break;
    case 0x63:
        if (FLD(gHeroState, s32, 0xC28) & 2) {
            EnterHeroState_L07(0x62, 1);
        }
        break;
    case 0x64:
        if ((FLD(gHeroState, s32, 0xC28) & 2) || (FLD(gHeroState, s32, 0x18B0) != 0)) {
            EnterHeroState_L07(0, 1);
        }
        if (vec_distance_xy(gHeroState + 0x80, gHeroState + 0x18A0) > 0.2f) {
            EnterHeroState_L07(0x62, 1);
        }
        break;
    case 0x65:
    {
        s32 n = FLD(gHeroState, s32, 0x18C0);
        if ((n < 3) && (((n * 7) + 0xA) < FLD(gHeroState, s32, 0x1B8)) && (PadPressedWithin(0x40, 7, &specialCost) != 0)) {
            EnterHeroState_L07(0x66, 1);
        }
        if (FLD(gHeroState, f32, 0x88) < (FLD(gHeroState, f32, 0x334) - 1.2f)) {
            RecordHeroPlayCounters();
            return;
        }
        if (FLD(gHeroState, s32, 0x1B8) < 0xAB) {
            break;
        }
        RecordHeroPlayCounters();
        return;
    }
    case 0x78:
        if (FLD(gHeroState, f32, 0x88) < (FLD(gHeroState, f32, 0x334) - 1.2f)) {
            RecordHeroPlayCounters();
            return;
        }
        if (FLD(gHeroState, s32, 0x1B8) < 0x97) {
            break;
        }
        RecordHeroPlayCounters();
        return;
    case 0x6D:
    {
        u8 *rec = D_L07_0025DD90;
        s32 off = FLD(gHeroState, s16, 0xBFC) * 0x2C;
        rec -= -off;
        if ((f32)FLD(rec, s32, 0x18) < FLD(gHeroState, f32, 0xC38)) {
            EnterHeroState_L07(0, 1);
        }
        break;
    }
    case 0x30:
        if (((FLD(gHeroState, u8, 0x1493) == 0) && (FLD(gHeroState, s16, 0x200) == 0)) || (FLD(gHeroState, f32, 0x31C) > 1.0f)) {
            s32 slot = FLD(gHeroState, s32, 0x2434);
            if (slot != -1) {
                u8 *ent = gSoundState + slot * 0x70;
                if ((FLD(ent, s32, 0x88) == FLD(gHeroState, s32, 0x2290)) && (FLD(ent, u8, 0x74) != 0)) {
                    StopSoundVoice(slot);
                }
            }
            FLD(gHeroState, s32, 0x2434) = -1;
            if (EnterHeroState_L07(0, 0) != 0) {
                set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 17.0f);
                FLD(gHeroState, s128, 0x160) = FLD(gHeroState, s128, 0x150);
            }
        }
        break;
    case 0x3:
        if ((FLD(gPadState, s32, 0x1A0) & 4) && (FLD(gHeroState, s32, 0x1500) == 0) && (GetLevelSavedValue() == 0)) {
            EnterHeroState_L07(1, 1);
            break;
        }
        if (FLD(gHeroState, s16, 0x1E0) == 0) {
            if (FLD(gPadState, s32, 0x1A4) & 0x40) {
                EnterHeroState_L07(7, 1);
                break;
            }
            if (FLD(gPadState, s32, 0x1A0) & 8) {
                EnterHeroState_L07(4, 1);
                break;
            }
        }
        if ((FLD(gHeroState, s16, 0x34E) >= 9) && (FLD(gHeroState, f32, 0x31C) > 0.3f)) {
            EnterHeroState_L07(6, 1);
            break;
        }
        if (FLD(gHeroState, s32, 0xC28) & 2) {
            EnterHeroState_L07(0, 1);
            break;
        }
        if (!(FLD(gHeroState, f32, 0x24B8) > 0.2f) || (FLD(gHeroState, s16, 0x1E0) != 0)) {
            break;
        }
        if (GetHeroWeaponAnimationId_L01(0) != 0x51) {
            if (FLD(gHeroState, f32, 0x1B4) == 0.0f) {
                EnterHeroState_L07(0, 0);
                break;
            }
        } else if ((FLD(gHeroState, f32, 0xC38) > 10.0f) && (EnterHeroState_L07(0, 0) != 0)) {
            set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 17.0f);
        }
        if (FLD(gHeroState, f32, 0x24B8) > 0.5f) {
            EnterHeroState_L07(2, 1);
        }
        break;
    case 0x4:
        if ((FLD(gPadState, s32, 0x1A0) & 4) && (FLD(gHeroState, s32, 0x1500) == 0) && (GetLevelSavedValue() == 0)) {
            EnterHeroState_L07(1, 1);
            break;
        }
        if ((FLD(gHeroState, s32, 0x1B8) >= 0xC) && !(FLD(gPadState, s32, 0x1A0) & 8)) {
            EnterHeroState_L07(0, 0);
            set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, -2.0f);
            break;
        }
        if ((FLD(gHeroState, u8, 0x149A) != 0) && (FLD(gHeroState, s16, 0x34C) == 0)) {
            EnterHeroState_L07(0x76, 1);
            break;
        }
        if (ChooseHeroJumpOrRollMove() != 0) {
            break;
        }
        if ((PadPressedWithin(0x80, 0xF, NULL) != 0) && (FLD(gHeroState, u8, 0x123A) == 0) && (FLD(gHeroState, s32, 0x1248) == 0xA)) {
            EnterHeroState_L07(0x15, 1);
        }
        if (FLD(gHeroState, s16, 0x34E) >= 9) {
            if ((FLD(gHeroState, s32, 0x22A0) != 8) || (FLD(gHeroState, s32, 0x1B8) >= 0xF)) {
                EnterHeroState_L07(6, 1);
            }
        }
        break;
    case 0x8A:
        if (FLD(gHeroState, s32, 0x1248) != 0xD) {
            EnterHeroState_L07(0, 1);
            break;
        }
        if (FLD(gHeroState, s32, 0xB1C) != 0) {
            u8 *obj = FLD(gHeroState, u8 *, 0xB10);
            if (obj != NULL) {
                SetObjectFlagBit(obj, 1);
            }
            EnterHeroState_L07(0x8B, 1);
        }
        break;
    case 0x8B:
        if (FLD(gHeroState, s32, 0x1B8) >= 0x5B) {
            EnterHeroState_L07(0, 1);
        }
        break;
    case 0x23:
        if (FLD(gHeroState, s32, 0x1248) != 0xD) {
            EnterHeroState_L07(0, 1);
        }
        break;
    case 0x24:
    {
        s32 go;
        AdjustHeroAnimationSpeedForTargetFrame(10.0f, FLD(gHeroState, f32, 0xAAC), 0.5f, -1.0f);
        if ((FLD(gHeroState, f32, 0xAAC) < 22.0f) && (FLD(gHeroState, f32, 0xAAC) < 30.0f)) {
            set_hero_animation(0xA, 0, 16.0f);
        }
        go = 0;
        if (!(FLD(gPadState, s32, 0x1A0) & FLD(gHeroState, s32, 0x1230))) {
            if (FLD(gHeroState, f32, 0xAAC) > 25.0f) {
                FLD(gHeroState, s32, 0xAC8) = 1;
            }
            go = 1;
        }
        if ((FLD(gHeroState, s32, 0x2298) == 1) && (FLD(gHeroState, f32, 0xAA0) < 0.06666667f)) {
            go = 1;
        }
        if (go != 0) {
            FLD(gHeroState, f32, 0x1B4) = FLD(gHeroState, f32, 0xAA0);
            if (FLD(gHeroState, f32, 0x1B4) > 0.116666675f) {
                FLD(gHeroState, f32, 0x1B4) = 0.116666675f;
            }
            if (FLD(gHeroState, f32, 0x31C) < 0.3f) {
                EnterHeroState_L07(0, 0);
                set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 30.0f);
                break;
            }
            if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) == 0xA) {
                EnterHeroState_L07(6, 0);
            } else {
                EnterHeroState_L07(6, 0);
                set_hero_animation(0xA, 0, 17.0f);
            }
            FLD(gHeroState, f32, 0xA84) = 0.011666667f;
            FLD(gHeroState, f32, 0xA80) = 0.008055556f;
            FLD(gHeroState, s32, 0x24A0) = 0;
        }
        break;
    }
    case 0x25:
        if (!(FLD(gPadState, s32, 0x1A0) & FLD(gHeroState, s32, 0x1230))) {
            FLD(gHeroState, f32, 0x1B4) = FLD(gHeroState, f32, 0xAA0);
            if (FLD(gHeroState, f32, 0x1B4) > 0.116666675f) {
                FLD(gHeroState, f32, 0x1B4) = 0.116666675f;
            }
            if (FLD(gHeroState, f32, 0x31C) < 0.4f) {
                EnterHeroState_L07(0, 1);
            } else {
                EnterHeroState_L07(6, 1);
                FLD(gHeroState, s32, 0x24A0) = 0;
            }
        }
        break;
    case 0x2B:
        if (!(FLD(gPadState, s32, 0x1A0) & FLD(gHeroState, s32, 0x1230))) {
            s32 t = FLD(gHeroState, s32, 0x1B8);
            if (t >= 0xB) {
                if (t < 0x28) {
                    FLD(gHeroState, s32, 0xAC8) = 1;
                }
                EnterHeroState_L07(0x2C, 1);
                FLD(gHeroState, f32, 0xA84) = 0.0019444445f;
                FLD(gHeroState, f32, 0xA80) = 0.0075000003f;
            }
        }
        break;
    case 0x17:
        if (FLD(gHeroState, f32, 0xC38) > 13.5f) {
            EnterHeroState_L07(0x18, 0);
        }
        break;
    case 0x18:
        if ((FLD(gHeroState, s32, 0xC28) & 2) && (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) == 0x20)) {
            set_hero_animation(0x21, 0, 6.0f);
        }
        ResolveStickInputToDirection(0, 1.0f);
        if (ProbeLedgeGrab((s8 *)(gHeroState + 0x80), (s8 *)(gHeroState + 0x90), NULL) == 0) {
            EnterHeroState_L07(6, 1);
            FLD(gHeroState, s16, 0x1D0) = 0xA;
            break;
        }
        if (((FLD(gHeroState, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FLD(gHeroState, f32, 0x98)) > 2.3561947f)) || (FLD(gPadState, s32, 0x1A4) & 8)) {
            EnterHeroState_L07(6, 1);
            FLD(gHeroState, s8, 0x22BF) = 1;
            FLD(gHeroState, s16, 0x1D0) = 0xA;
            break;
        }
        if (PadPressedWithin(0x40, 0x11, NULL) != 0) {
            EnterHeroState_L07(0x1B, 1);
            break;
        }
        if (FLD(gHeroState, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FastAddRotations(FLD(gHeroState, f32, 0x98), 1.5707965f)) < 0.78539824f) {
                qcopy(v10, gHeroState + 0x80);
                v10[0] += FastSinOrCosA(FastAddRotations(FLD(gHeroState, f32, 0x98), 1.5707965f)) * 0.3f;
                v10[1] += FastSinOrCosB(FastAddRotations(FLD(gHeroState, f32, 0x98), 1.5707965f)) * 0.3f;
                if (ProbeLedgeGrab((s8 *)v10, (s8 *)(gHeroState + 0x90), NULL) != 0) {
                    EnterHeroState_L07(0x19, 1);
                }
                break;
            }
        }
        if (FLD(gHeroState, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FastAddRotations(FLD(gHeroState, f32, 0x98), -1.5707965f)) < 0.78539824f) {
                qcopy(v10, gHeroState + 0x80);
                v10[0] += FastSinOrCosA(FastAddRotations(FLD(gHeroState, f32, 0x98), -1.5707965f)) * 0.3f;
                v10[1] += FastSinOrCosB(FastAddRotations(FLD(gHeroState, f32, 0x98), -1.5707965f)) * 0.3f;
                if (ProbeLedgeGrab((s8 *)v10, (s8 *)(gHeroState + 0x90), NULL) != 0) {
                    EnterHeroState_L07(0x1A, 1);
                }
            }
        }
        break;
    case 0x19:
    case 0x1A:
    {
        f32 side;
        *(s128 *)v10 = FLD(gHeroState + 0x80, s128, 0);
        side = 1.5707965f;
        if (FLD(gHeroState, u32, 0x2294) == 0x1A) {
            side = -1.5707965f;
        }
        v10[0] += FastSinOrCosA(FastAddRotations(FLD(gHeroState, f32, 0x98), side)) * 0.3f;
        v10[1] += FastSinOrCosB(FastAddRotations(FLD(gHeroState, f32, 0x98), side)) * 0.3f;
        ResolveStickInputToDirection(0, 1.0f);
        if ((FLD(gHeroState, f32, 0x24B8) < 0.5f) || (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FastAddRotations(FLD(gHeroState, f32, 0x98), side)) > 0.78539824f) || (ProbeLedgeGrab((s8 *)v10, (s8 *)(gHeroState + 0x90), NULL) == 0)) {
            if (FLD(gHeroState, s32, 0xC28) & 2) {
                EnterHeroState_L07(0x18, 1);
                break;
            }
        }
        if ((FLD(gHeroState, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FLD(gHeroState, f32, 0x98)) > 2.3561947f)) {
            EnterHeroState_L07(6, 1);
            FLD(gHeroState, s8, 0x22BF) = 1;
            FLD(gHeroState, s16, 0x1D0) = 0x28;
            break;
        }
        if (PadPressedWithin(0x40, 9, NULL) != 0) {
            EnterHeroState_L07(0x1B, 1);
        }
        break;
    }
    case 0x76:
        if (FLD(gHeroState, s32, 0x1B8) >= 0x12D) {
            RecordHeroPlayCounters();
        }
        if (FLD(gHeroState, u8, 0x149A) == 0) {
            if (FLD(gHeroState, s16, 0x34E) != 0) {
                EnterHeroState_L07(6, 1);
            } else {
                EnterHeroState_L07(0, 1);
            }
        }
        break;
    case 0x6:
    case 0x2C:
        if ((FLD(gHeroState, s32, 0x2298) == 0) && ((FLD(gHeroState, s32, 0x1B8) >= 0x12) || (FLD(gHeroState, f32, 0x31C) > 1.75f))) {
            set_hero_animation(0xB, 0, 16.0f);
            FLD(gHeroState, s32, 0x2298) = 1;
            if (FLD(gHeroState, u32, 0x2294) == 0x2C) {
                FLD(gHeroState, s32, 0x24A0) = 7;
            } else {
                FLD(gHeroState, s32, 0x24A0) = 0;
            }
        }
        if (FLD(gHeroState, s16, 0x34E) == 0) {
            PlayHeroFootstepEffect();
            if (FLD(gHeroState, f32, 0x118) < -0.15f) {
                FLD(gHeroState, f32, 0x118) = -0.15f;
            }
            if (FLD(gHeroState, f32, 0xF8) < -0.15f) {
                FLD(gHeroState, f32, 0xF8) = -0.15f;
            }
            if (FLD(gHeroState, s32, 0x24CC) <= 0) {
                EnterHeroState_L07(0x39, 1);
            } else {
                s32 one = 1;
                s32 low = FLD(gHeroState, s32, 0x33C) == 0;
                if (FLD(gHeroState, s32, 0x1B8) >= 0x5A) {
                    if (EnterHeroState_L07(0, 0) != 0) {
                        set_hero_animation(0xC, 4, 6.0f);
                    }
                    if (low != 0) {
                        FLD(gHeroState, s16, 0x1E0) = 0x16;
                    }
                    SetHeroLevelClockAndBytes(0xA, 4, 0, 1, 0.022f, 0.004f);
                } else if (FLD(gHeroState, s32, 0x2298) == one) {
                    if (EnterHeroState_L07(0, 0) != 0) {
                        set_hero_animation(0xC, 9, -1.0f);
                    }
                    SetViewSpaceHeight(gHeroState + 0x160, gHeroState + 0x160, 0.0f);
                    ClampVectorLength((f32 *)(gHeroState + 0x160), 0.116666675f);
                    FLD(gHeroState, s16, 0x1E0) = 7;
                    if (FLD(gHeroState, s32, 0x22A0) == 0x2C) {
                        FLD(gHeroState, s16, 0x1E0) = 0xA;
                    }
                    if ((low != 0) && (FLD(gHeroState, s32, 0x1B8) >= 0x33)) {
                        FLD(gHeroState, s16, 0x1E0) = 0x12;
                    }
                    SetHeroLevelClockAndBytes(0xA, 2, 0, 1, 0.019f, 0.002f);
                } else if ((FLD(gHeroState, f32, 0x24B8) > 0.5f) && (FLD(gHeroState, s16, 0x1E0) == 0)) {
                    EnterHeroState_L07(2, 1);
                    SetHeroLevelClockAndBytes(7, 2, 0, 1, 0.016f, 0.002f);
                } else if (FLD(gHeroState, f32, 0x174) > 0.050000004f) {
                    if (EnterHeroState_L07(3, 0) != 0) {
                        set_hero_animation(6, 0, 12.0f);
                        ClampVectorLength((f32 *)(gHeroState + 0x160), 0.12833333f);
                    }
                } else {
                    EnterHeroState_L07(0, 1);
                    SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
                }
            }
        } else if (FLD(gHeroState, s32, 0x24CC) > 0) {
            if ((FLD(gPadState, s32, 0x1A0) & 0x40) && (gItemOwnedFlags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(gHeroState, s16, 0x24FC) == 0) && (FLD(gHeroState, s16, 0x1E0) == 0) && (FLD(gHeroState, f32, 0x31C) > 0.6f)) {
                EnterHeroState_L07(8, 1);
                break;
            }
            if ((FLD(gHeroState, s16, 0x202) >= 0x15) && (TryStartHeroMoveFromBuffer((FLD(gHeroState, s16, 0x1EE) != 0) ? 1 : 6, 0) != 0)) {
                break;
            }
            if (FLD(gHeroState, s32, 0x578) != 0) {
                EnterHeroState_L07(0x17, 1);
                break;
            }
        }
        break;
    case 0x74:
        if (gCurrentMapIndex == 0xD) {
            f32 y = FLD(gHeroState, f32, 0x88);
            if ((FLD(gHeroState, s32, 0x22A4) == 0x1E) || (FLD(gHeroState, s32, 0x22B0) == 0x1E)) {
                s32 t = FLD(gHeroState, s32, 0x1B8);
                if (((y < 51.0f) && (t >= 0x1F)) || (t >= 0x1F) && (FLD(gHeroState, u8, 0x287) != 0) && ((FLD(gHeroState, f32, 0x118) >= 0.0f) || (FLD(gHeroState, u8, 0x149B) != 0))) {
                    RecordHeroPlayCounters();
                    return;
                }
            } else if ((y < 89.0f) || ((FLD(gHeroState, s32, 0x1B8) >= 0x15) && (FLD(gHeroState, u8, 0x287) != 0) && (FLD(gHeroState, f32, 0x118) >= 0.0f))) {
                RecordHeroPlayCounters();
                return;
            }
        }
        if (FLD(gHeroState, s32, 0x1B8) < 0x79) {
            break;
        }
        RecordHeroPlayCounters();
        return;
    case 0x82:
    {
        u8 *p = gHeroState + 0xF0;
        if (GetViewSpaceHeight((s8 *)p) < 0.0f) {
            p -= 0xF0;
            if (FLD(p, s32, 0x340) != 0) {
                u8 *q = FLD(p, u8 *, 0x33C);
                if ((q == NULL) || (FLD(q, s16, 0xAA) == 0x8E2)) {
                    if (EnterHeroState_L07(0, 0) != 0) {
                        FLD(p, s8, 0x24EF) = 0;
                        set_hero_animation(7, 0x17, 9.0f);
                        SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
                    }
                }
            }
        }
        if (FLD(gHeroState, f32, 0x5B0) == 0.0f) {
            if (gCurrentMapIndex == 0xD) {
                if (FLD(gHeroState, f32, 0x318) < 69.0f) {
                    EnterHeroState_L07(0x74, 1);
                } else {
                    EnterHeroState_L07(6, 1);
                }
            } else {
                EnterHeroState_L07(6, 1);
            }
        }
        break;
    }
    case 0x8:
        if ((FLD(gHeroState, s32, 0x1D4) != 0) && (FLD(gHeroState, s32, 0x1B8) < 9)) {
            s32 prev = FLD(gHeroState, s32, 0x22A0);
            s32 ok = 0;
            if ((prev == 7) || (prev == 9) || (prev == 0xE) || (prev == 0x11)) {
                ok = 1;
            }
            if (ok != 0) {
                EnterHeroState_L07(0x11, 1);
            }
            break;
        }
        if ((FLD(gHeroState, s32, 0x1B8) >= 0x1F) && !(FLD(gPadState, s32, 0x1A0) & 0x40) && !(FLD(gPadState, s32, 0x1C0) & 0x40)) {
            EnterHeroState_L07(6, 1);
            break;
        }
        if (FLD(gHeroState, s32, 0x578) != 0) {
            EnterHeroState_L07(0x17, 1);
            break;
        }
        if ((FLD(gHeroState, s16, 0x34E) != 0) && !(FLD(gHeroState, f32, 0x31C) < 0.4f)) {
            break;
        }
        if (FLD(gHeroState, s32, 0x1B8) < 0xA) {
            FLD(gHeroState, s16, 0x1EE) = 0xC - FLD(gHeroState, u16, 0x1B8);
        }
        ResolveStickInputToDirection(0, 1.0f);
        if ((FLD(gHeroState, s32, 0x22A0) == 0x10) && (FLD(gHeroState, s32, 0x1B8) < 4)) {
            if (EnterHeroState_L07(3, 0) != 0) {
                set_hero_animation(5, 0, -1.0f);
                FLD(gHeroState, s16, 0x1E0) = 0x22;
            }
            break;
        }
        if (FLD(gPadState, s32, 0x1A0) & 8) {
            EnterHeroState_L07(4, 1);
            SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
            break;
        }
        if ((FLD(gHeroState, f32, 0x1B0) > D_L07_001A7DAC[0][2]) && (FastDiffRots(FLD(gHeroState, f32, 0x1A0), FLD(gHeroState, f32, 0x98)) < 1.5707964f)) {
            if ((FLD(gHeroState, u8, 0x1492) != 0) || (FLD(gHeroState, u8, 0x22B9) != 0)) {
                EnterHeroState_L07(2, 1);
                break;
            }
            EnterHeroState_L07(2, 0);
            if (FLD(gHeroState, u32, 0x2294) == 2) {
                FLD(gHeroState, s32, 0x2298) = 1;
                set_hero_animation(4, 2, 8.0f);
                FLD(gHeroState, s8, 0x40E) = 1;
            }
            SetHeroLevelClockAndBytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (FLD(gHeroState, f32, 0x1B0) > D_L07_001A7DAC[0][2]) {
            if ((FLD(gHeroState, u8, 0x1492) != 0) || (FLD(gHeroState, u8, 0x22B9) != 0)) {
                EnterHeroState_L07(2, 1);
                break;
            }
            EnterHeroState_L07(2, 0);
            if (FLD(gHeroState, u32, 0x2294) == 2) {
                FLD(gHeroState, s32, 0x2298) = 1;
                set_hero_animation(4, D_L07_001A7DDC, 12.0f);
            }
            SetHeroLevelClockAndBytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (FLD(gHeroState, s16, 0x34E) == 0) {
            if (EnterHeroState_L07(0, 0) != 0) {
                set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, -2.0f);
                SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
            }
        } else if (EnterHeroState_L07(0, 0) != 0) {
            set_hero_animation(7, 0x17, 9.0f);
            SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
        }
        break;
    case 0x7:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x1B:
    case 0x38:
    case 0x66:
    case 0x6E:
    case 0x81:
    case 0x89:
    {
        s32 near;
        s16 lo;
        s32 now;
        u32 st;
        u32 st1;
        s32 lim;
        s32 frames;
        if (FLD(gHeroState, u8, 0x52E) != 0) {
            s32 n = GetStepOffsetFromDirection();
            if ((n > 0) && ((FLD(gHeroState, s32, 0x1B8) < n) || (FLD(gHeroState, u8, 0x49C) != 0)) && (FLD(gHeroState, s32, 0x340) != 0)) {
                if ((FLD(gHeroState, u32, 0x2294) != 0xB) || (PadPressedWithin(0x40, 7, NULL) != 0)) {
                    s32 go = 1;
                    if ((FLD(gHeroState, u32, 0x2294) == 0x1B) || (FLD(gHeroState, u8, 0x49C) != 0)) {
                        if (PadPressedWithin(0x40, 7, NULL) == 0) {
                            go = 0;
                        }
                    }
                    if (FLD(gHeroState, u32, 0x2294) == 0xB) {
                        if (FLD(gHeroState, u8, 0x49C) == 0) {
                            go = 0;
                        }
                    }
                    if ((go != 0) && (PadPressedWithin(0x1F000, 5, NULL) != 0) && (FLD(gPadState, s32, 0x1A0) & 8)) {
                        EnterHeroState_L07(0xB, 1);
                        break;
                    }
                }
            }
        }
        if ((FLD(gHeroState, s16, 0x1F2) != 0) && ((FLD(gHeroState, u32, 0x2294) == 7) || (FLD(gHeroState, u32, 0x2294) == 9)) && (FLD(gHeroState, s32, 0x1B8) < 0x14)) {
            EnterHeroState_L07(0x82, 1);
            break;
        }
        if ((FLD(gHeroState, u32, 0x2294) == 0x1B) && (FLD(gHeroState, s32, 0x1B8) >= 0x15) && (FLD(gHeroState, f32, 0x278) > 0.7f)) {
            FLD(gHeroState, s8, 0x22BF) = 0;
            FLD(gHeroState, s8, 0x22BC) = 0;
        }
        if ((FLD(gHeroState, s32, 0x1B8) < 7) && (PadPressedWithin(8, 2, NULL) != 0) && ((st1 = FLD(gHeroState, u32, 0x2294)) != 0x10) && (st1 != 0xA) && (st1 != 0x12) && (st1 != 0x38) && (st1 != 0x11) && (st1 != 0xE) && (st1 != 0x66)) {
            if ((hero_slot_item_id(3) == 2) && (gItemOwnedFlags[2] != 0) && (FLD(gHeroState, s16, 0x24FC) == 0) && (FLD(gHeroState, f32, 0x178) > 0.015000001f)) {
                EnterHeroState_L07(0xA, 1);
            } else if ((hero_slot_item_id(3) == 3) && (FLD(gHeroState, s16, 0x24FC) == 0) && (FLD(gHeroState, f32, 0x178) > 0.015000001f) && (FLD(gHeroState, s16, 0x1E4) == 0)) {
                EnterHeroState_L07(0x10, 1);
            }
        }
        {
            if (FLD(gHeroState, s16, 0x51A) < FLD(gHeroState, s32, 0x1B8)) {
                if (FLD(gHeroState, u8, 0x49C) == 0) {
                    EnterHeroState_L07(6, 1);
                    break;
                }
            } else if ((FLD(gHeroState, u8, 0x49C) == 0) && ((FLD(gHeroState, u32, 0x2294) == 0xA) || (FLD(gHeroState, u32, 0x2294) == 0x10)) && (FLD(gHeroState, f32, 0x278) < 0.9f) && (FLD(gHeroState, u8, 0x287) != 0) && (FastVecLength(gHeroState + 0xF0) > 0.116666675f)) {
                f32 a = FastVecLength(gHeroState + 0x110);
                if ((a < FastVecLength(gHeroState + 0xF0) * 0.5f) && (FLD(gHeroState, s32, 0x578) == 0) && (FLD(gHeroState, f32, 0x31C) < 2.0f)) {
                    EnterHeroState_L07(0x77, 1);
                    break;
                }
            }
        }
        near = 0;
        if ((FLD(gHeroState, u32, 0x2294) == 0xE) && (FLD(gHeroState, f32, 0xC38) < 35.0f)) {
            near = 1;
        }
        lo = FLD(gHeroState, s16, 0x4AC);
        now = FLD(gHeroState, s32, 0x1B8);
        if (!(lo < now)) {
            break;
        }
        if (now == lo + 1) {
            if (FLD(gHeroState, u8, 0x49D) != 0) {
                f32 left = (f32)(FLD(gHeroState, s32, 0x430) - now);
                if (left > 0.0f) {
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(gHeroState, f32, 0x438), left, FLD(gHeroState, f32, 0x514), -1.0f);
                }
            } else if (FLD(gHeroState, u32, 0x2294) != 0xE) {
                EvaluateQuantizedHeight((f32 *)(gHeroState + 0x80), (f32 *)(gHeroState + 0xF0), &hitDistance, FLD(gHeroState, f32, 0x520));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(gHeroState, f32, 0x4C8), (f32)hitDistance, FLD(gHeroState, f32, 0x514), -1.0f);
                if (FLD(gHeroState, f32, 0xC20) > 1.5f) {
                    FLD(gHeroState, f32, 0xC20) = 1.5f;
                }
            }
            break;
        }
        if ((FLD(gHeroState, u8, 0x49D) != 0) && (now >= FLD(gHeroState, s32, 0x430)) && (now < FLD(gHeroState, s32, 0x434))) {
            f32 left = (f32)(FLD(gHeroState, s32, 0x440) - FLD(gHeroState, s32, 0x430));
            if (left > 0.0f) {
                AdjustHeroAnimationSpeedForTargetFrame(FLD(gHeroState, f32, 0x4C8), left, FLD(gHeroState, f32, 0x514), -1.0f);
            }
            break;
        }
        if (FLD(gHeroState, s32, 0x338) == 1) {
            PlayHeroSound(0xC, 0);
            EmitHeroDustAndDebris(3, 0x18, 1);
        }
        {
            u8 c = FLD(gHeroState, u8, 0x49C);
            if (c != 0) {
                FLD(gHeroState, u8, 0x49C) = c + 1;
            } else if ((FLD(gHeroState, s16, 0x34E) == 0) && (FLD(gHeroState, u8, 0x49E) != 0) && (near == 0)) {
                PlayHeroFootstepEffect();
                FLD(gHeroState, u8, 0x49C) = 1;
                FLD(gHeroState, s8, 0x24DB) = 0;
                if ((FLD(gHeroState, f32, 0x24B8) < 0.2f) && (FLD(gHeroState, f32, 0x1B4) > 0.041666668f)) {
                    FLD(gHeroState, f32, 0x1B4) = 0.041666668f;
                }
                SetHeroLevelClockAndBytes(5, 2, 0, 1, 0.016f, 0.002f);
                if (near == 0) {
                    s32 k = FloatToInt(FLD(gHeroState, f32, 0x4D0)) + 2;
                    if (FLD(gHeroState, f32, 0xC38) < FLD(gHeroState, f32, 0x4CC) - 1.5f) {
                        set_hero_animation(ReturnArgument_L00(FLD(heroObject, u8, 0x43)), k, 7.0f);
                    }
                }
            }
        }
        if (FLD(gHeroState, u8, 0x49C) != 0) {
            FLD(gHeroState, f32, 0xC20) = 1.0f;
        } else if (FLD(gHeroState, u8, 0x49E) != 0) {
            s32 cur;
            if ((s32)FLD(heroObject, u8, 0x41) < FloatToInt(FLD(gHeroState, f32, 0x4D0))) {
                if ((FLD(gHeroState, u32, 0x2294) == 0xE) && (FLD(gHeroState, f32, 0xC38) < 37.0f)) {
                    ApproachValue((f32 *)(gHeroState + 0xC20), 1.0f, 0.15f);
                } else {
                    FLD(gHeroState, s16, 0x4AE) = FloatToInt(SolveHeroFallCollisionTime(60.0f, FLD(gHeroState, f32, 0x520), -1.0f));
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(gHeroState, f32, 0x4CC), (f32)FLD(gHeroState, s16, 0x4AE), FLD(gHeroState, f32, 0x514), 0.2f);
                }
                if (near == 0) {
                    s32 k = FloatToInt(FLD(gHeroState, f32, 0x4D0)) + 2;
                    if (FLD(gHeroState, f32, 0xC20) > 1.8f) {
                        set_hero_animation(ReturnArgument_L00(FLD(heroObject, u8, 0x43)), k, (f32)(FLD(gHeroState, s16, 0x4AE) + 3));
                    }
                }
                if (FLD(gHeroState, f32, 0xC20) < 0.2f) {
                    FLD(gHeroState, f32, 0xC20) = 0.2f;
                }
                if (FLD(gHeroState, f32, 0xC20) > 2.7f) {
                    FLD(gHeroState, f32, 0xC20) = 2.7f;
                }
            }
            cur = FLD(gHeroState, u32, 0x2294);
            if ((cur == 9) && ((FLD(gHeroState, f32, 0x4CC) - FLD(gHeroState, f32, 0xC38)) > 6.0f) && ((ReturnArgument_L00(FLD(heroObject, u8, 0x42)) == 8) || (ReturnArgument_L00(FLD(heroObject, u8, 0x42)) == cur)) && (FLD(heroObject, u8, 0x42) == FLD(heroObject, u8, 0x43)) && (FLD(gHeroState, f32, 0x1B0) < D_L07_001A7DAC[1][1] * 0.0016666668f) && (FLD(gHeroState, f32, 0x174) < 0.041666668f)) {
                f32 rate = 9.0f / FLD(gHeroState, f32, 0xC20);
                s32 at;
                if (rate > 10.0f) {
                    rate = 10.0f;
                }
                at = FloatToInt(FLD(gHeroState, f32, 0xC38)) + 4;
                set_hero_animation(7, at / 2, rate);
                FLD(gHeroState, s32, 0x2294) = 7;
            }
            {
                s32 a = FloatToInt(FLD(gHeroState, f32, 0xC38));
                if (a == FloatToInt(FLD(gHeroState, f32, 0x4CC))) {
                    FLD(gHeroState, s32, 0xC20) = 0;
                }
            }
        }
        if (FLD(gHeroState, u8, 0x49C) != 0) {
            if (FLD(gHeroState, u32, 0x2294) == 0xA) {
                if (EnterHeroState_L07(3, 0) != 0) {
                    set_hero_animation(5, 0, -2.0f);
                    FastVecScale(gHeroState + 0x160, gHeroState + 0x160, 0.8f);
                }
                break;
            }
            if ((FLD(gHeroState, u8, 0x149A) == 0) && (FLD(gHeroState, s16, 0x1E0) == 0) && (PadPressedWithin(0x40, 8, NULL) != 0) && (FLD(gHeroState, s16, 0x34E) < 4)) {
                if (!(FLD(gHeroState, f32, 0x1B0) > D_L07_001A7DAC[0][2])) {
                    EnterHeroState_L07(7, 1);
                } else if (!(FastDiffRots(FLD(gHeroState, f32, 0x1A0), FLD(gHeroState, f32, 0x98)) < 1.0471976f)) {
                    EnterHeroState_L07(7, 1);
                } else if (D_L07_001A7DAC[1][1] * 0.014166668f < FLD(gHeroState, f32, 0x174)) {
                    EnterHeroState_L07(9, 1);
                } else {
                    EnterHeroState_L07(7, 1);
                }
                break;
            }
        }
        if ((FLD(gHeroState, u8, 0x49C) >= 2) && (FLD(gHeroState, u32, 0x2294) != 0xA)) {
            ChooseHeroAction();
        } else if ((FLD(gHeroState, u8, 0x49E) != 0) && (FLD(gHeroState, s32, 0x1B8) >= FLD(gHeroState, s16, 0x52A)) && (FLD(gHeroState, f32, 0x31C) > FLD(gHeroState, f32, 0x510))) {
            EnterHeroState_L07(6, 1);
        }
        if ((FLD(gHeroState, u32, 0x2294) == 0x10) && (FLD(gHeroState, s32, 0x1B8) >= 0x3D) && (FLD(gHeroState, f32, 0x31C) > 1.5f)) {
            EnterHeroState_L07(6, 1);
            break;
        }
        {
            u32 s = FLD(gHeroState, u32, 0x2294);
            s32 ok = 0;
            if ((s == 7) || (s == 9) || (s == 0x11)) {
                ok = 1;
            }
            if ((FLD(gHeroState, s32, 0x1D4) != 0) && (FLD(gHeroState, u8, 0x49C) == 0) && (ok != 0) && ((FLD(gHeroState, u32, 0x2294) != 0x11) || (FLD(gHeroState, s32, 0x1B8) >= 0x1A)) && (PadPressedWithin(0x40, 7, &specialCostLimit) != 0) && (specialCostLimit < FLD(gHeroState, s32, 0x1B8))) {
                EnterHeroState_L07(0x11, 1);
                break;
            }
        }
        if (((FLD(gHeroState, u32, 0x2294) == 0xA) || (FLD(gHeroState, u32, 0x2294) == 0x10)) && (FLD(gHeroState, s32, 0x1B8) >= 0x1A) && (FLD(gHeroState, s16, 0x34A) != 0)) {
            FLD(gHeroState, s16, 0x526) = 0x14;
        }
        st = FLD(gHeroState, u32, 0x2294);
        lim = 0x14;
        if (st == 0x10) {
            lim = 8;
        }
        if ((st == 0xE) && (FLD(gHeroState, f32, 0x31C) > 4.0f)) {
            if ((FLD(gHeroState, u8, 0x49E) == 0) && (FLD(gHeroState, f32, 0xC20) < 1.3f)) {
                ApproachValue((f32 *)(gHeroState + 0xC20), 1.3f, 0.1f);
            }
            lim = 0x11;
            FLD(gHeroState, s16, 0x526) = lim;
        }
        frames = FLD(gHeroState, s32, 0x1B8) - 4;
        if (frames <= 1) {
            frames = 2;
        }
        if (frames >= 0x1F) {
            frames = 0x1E;
        }
        if (!(FLD(gHeroState, s64, 0x498) & 0xFF0000FF00000000LL)) {
            if ((PadPressedWithin(0x40, frames, NULL) != 0) || (FLD(gHeroState, u32, 0x2294) == 0xE) || (FLD(gHeroState, u32, 0x2294) == 0xF) || (FLD(gHeroState, u32, 0x2294) == 0xD)) {
                if ((FLD(gHeroState, u32, 0x2294) != 0xE) && (FLD(gHeroState, u8, 0x22B8) == 0) && ((FLD(gHeroState, u8, 0x149A) == 0) || (FLD(gHeroState, f32, 0x31C) >= 0.4f)) && (FLD(gHeroState, u8, 0x52F) != 0) && (FLD(gHeroState, s32, 0x1B8) >= 0xF) && ((FLD(gHeroState, u8, 0x49E) == 0) || ((FLD(gHeroState, f32, 0x31C) > 0.7f) && (FloatAbs(GetViewSpaceHeight((s8 *)(gHeroState + 0xF0))) < 0.09666667f)))) {
                    EnterHeroState_L07(0xE, 1);
                } else if ((gItemOwnedFlags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(gHeroState, s16, 0x24FC) == 0) && (FLD(gPadState, s32, 0x1A0) & 0x40) && (lim < FLD(gHeroState, s32, 0x1B8)) && (FLD(gHeroState, s16, 0x526) < FLD(gHeroState, s32, 0x1B8))) {
                    f32 need = 0.6f;
                    if ((FLD(gHeroState, u32, 0x2294) == 9) || (FLD(gHeroState, u32, 0x2294) == 7)) {
                        need = 1.0f;
                    }
                    if (FLD(gHeroState, u32, 0x2294) == 0xE) {
                        need = 1.5f;
                    }
                    if (need < FLD(gHeroState, f32, 0x31C)) {
                        EnterHeroState_L07(8, 1);
                    }
                }
            }
        }
        if ((FLD(gHeroState, s32, 0x578) != 0) && (FLD(gHeroState, u32, 0x2294) != 0xB)) {
            EnterHeroState_L07(0x17, 1);
        }
        break;
    }
    case 0x16:
        if ((FLD(gHeroState, f32, 0xC38) > 12.5f) && (FLD(gHeroState, u8, 0x24EF) == 0) && (FLD(gHeroState, s16, 0x34E) != 0) && (FLD(gHeroState, f32, 0x31C) > 1.0f)) {
            EnterHeroState_L07(6, 1);
            break;
        }
        if (FLD(gHeroState, s32, 0x1B8) >= 0x1C) {
            if (FLD(gHeroState, s32, 0x24CC) <= 0) {
                EnterHeroState_L07(0x39, 1);
            } else if (FLD(gHeroState, u8, 0x24EF) != 0) {
                EnterHeroState_L07(0x82, 1);
            } else {
                EnterHeroState_L07(0, 0);
            }
        }
        break;
    case 0x8C:
        if (FLD(gHeroState, s32, 0xC28) & 2) {
            set_hero_animation(0x97, 0, 2.0f);
        }
        if ((FLD(gHeroState, s32, 0x1B8) >= 0x33) && (FLD(gHeroState, s16, 0x1E0) == 0)) {
            if (FLD(gHeroState, s32, 0x24CC) <= 0) {
                EnterHeroState_L07(0x39, 1);
            } else if (EnterHeroState_L07(0, 0) != 0) {
                set_hero_animation(GetHeroWeaponAnimationId_L01(0), 0, 13.0f);
            }
        }
        break;
    case 0x85:
        if ((FLD(gHeroState, s32, 0x1B8) >= 4) && (FLD(gPadState, s32, 0x1A4) & 0x10)) {
            StartHeroMoveStateOneOrTwo(0);
        }
        break;
    case 0x1D:
        if ((FLD(gHeroState, u8, 0x22B4) == 0) && ((FLD(gHeroState, u8, 0x22BA) == 0) || (FLD(gHeroState, u8, 0x22B5) != 0))) {
            if (FLD(gPadState, s32, 0x1A0) & 8) {
                set_hero_animation(0xD, 0, 8.0f);
            } else {
                set_hero_animation(GetHeroWeaponAnimationId_L01(1), 0, 8.0f);
            }
        }
        if (!(FLD(gPadState, s32, 0x1A0) & 4)) {
            if (FLD(gHeroState, u32, 0x2294) == 0x1D) {
                s32 anim;
                EnterHeroState_L07(0, 0);
                anim = GetHeroWeaponAnimationId_L01(1);
                if (FLD(FLD(gHeroState, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 8.0f);
                }
            }
            D_L07_001A8A48 = 0;
        }
        break;
    case 0x1F:
        if ((FLD(gHeroState, s32, 0x1220) != 0) && (FLD(gHeroState, s32, 0xC2C) == 0) && (FLD(gHeroState, f32, 0xC38) > 20.0f)) {
            EnterHeroState_L07(0, 0);
        }
        break;
    case 0x22:
        if (FLD(gHeroState, f32, 0xC38) > 19.0f) {
            if (PadPressedWithin(0x40, 0xB, NULL) != 0) {
                if (FLD(gPadState, s32, 0x1A0) & 8) {
                    ChooseHeroJumpOrRollMove();
                    break;
                }
                EnterHeroState_L07(7, 1);
                break;
            }
        }
        if (FLD(gHeroState, f32, 0xC38) >= 21.0f) {
            EnterHeroState_L07(0, 0);
        }
        break;
    default:
        break;
    }
end:
    if (phaseBefore != FLD(gHeroState, s32, 0x229C)) {
        ClearTrackedSlots();
    }
    prevState = FLD(gHeroState, s32, 0x22A0);
    if (((prevState == 0x3C) && (FLD(gHeroState, s32, 0x2294) != 0x3D)) || ((prevState == 0x3D) && (FLD(gHeroState, s32, 0x1854) != 0))) {
        ClearHeroTargetFlags();
    }
    if (movementBefore != FLD(gHeroState, s32, 0x2298)) {
        FLD(gHeroState, s32, 0x1C0) = 0;
    }
    if (animationBefore != FLD(heroObject, u8, 0x43)) {
        FLD(gHeroState, s32, 0x1C4) = 0;
    }
}