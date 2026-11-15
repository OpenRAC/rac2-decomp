#include "include_asm.h"
#include "names.h"

/* Built with -frac2-hazard-labels (config/cflags.txt). The second `t20 <= 0.0f` test reuses
   the compare its other path already made, so a forward branch reaches the join label
   between that c.le.s and its bc1fl. Retail keeps the label on the hazard nop the assembler
   inserts there; GNU as without the switch moves it behind the nop, and the bc1f at +0xE4
   lands one word late (docs/build/compiler-notes.md, labels in front of the hazard nop). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern u16 *D_L18_001FB320[];
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));

extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *func_002A9640(u8 *, s32, s32);
extern s32 func_002B0ED8(u8 *, u8 *, s32);
extern void func_002A6C58(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern void func_002B3380(u8 *, u8 *, u8 *);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(u8 *);
extern void func_002A7470(u8 *, s32, s32, s32);
extern void func_002A04B8(u8 *, s32 *, s32 *, s32 *);
extern void func_002A0488(u8 *, s32, s32, s32);
extern s32 func_002B3BA8(u8 *, s32, s32, s32, float, float);
extern void func_L18_004329B0(u8 *);
extern void func_L18_00432D60(u8 *);
extern void func_L18_00432E78(u8 *, s32, s32, s32);
extern s32 func_L18_00432E28(u8 *);

/* Handles hits on an Extermibot: its damage reactions, its death, the extra part it spawns, and keeping its attached parts sized and placed. */
void func_L18_004308F0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *hit;
    u8 *otherMoby;
    u16 *idList;
    u8 savedAnim;
    s32 b0;
    s32 b1;
    s32 b2;
    float health;

    hit = FindOwnedEffectSlot(object, 0x10000, 1);
    if (hit != 0) {
        if (*(u8 **)(hit + 0x20) != 0) {
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0xF0A /* Extermibot Legs */ || *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) == 0xF9E /* moby class 3998 */)
                *(s32 *)(hit + 0x2C) = 0;
        }
        if ((u8)(object[0x20] - 1) < 2)
            *(s32 *)(hit + 0x2C) = 0;
    }
    savedAnim = object[0x94];
    if (ApplyDamageToObject(object, state + 0x50, 0)) {
        if (object[0x94] == 0xD || object[0x94] == 9 || object[0x94] == 0xA || object[0x94] == 0xB ||
            object[0x94] == 0xC || object[0x94] == 5)
            object[0x94] = savedAnim;
        health = *(float *)(state + 0x20);
        if (*(u8 **)(state + 0x7C0) == 0) {
            if (health <= 0.0f) {
                SetDeathBits(object, 0, 3);
                DestroyPieceAndParts(object);
                return;
            }
        }
        if (health <= 0.0f && RandomIntBelow(7) == 0) {
            *(float *)(state + 0x20) = 8.0f;
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            SetMobyState(object, 0xE, -1);
            *(s16 *)(state + 0x88) = 0;
            state[0x6A] = 0;
        } else {
            SetAnimOnMobyAndParts(object, object[0x43], 0, 3);
        }
        ReleaseAllGroupPieces(object);
    }
    object[0xA8] = 0xFF;
    if (*(u8 **)(state + 0x188) != 0 && *(s16 *)(*(u8 **)(state + 0x188) + 0xAA) == 0xF59 /* moby class 3929 */) {
        SetDeathBits(object, 0, 3);
        DestroyPieceAndParts(object);
    }
    if (*(u8 **)(state + 0x7C0) != 0) {
        SpawnDamageDebrisOnHealthLoss(*(u8 **)(state + 0x7C0), *(u8 **)(*(u8 **)(state + 0x7C0) + 0x68) + 0x20, state + 0x20);
        if (!(*(u16 *)(*(u8 **)(state + 0x7C0) + 0x7C) & 2) && *(u8 **)(state + 0x7C4) == 0) {
            u8 *newPart = CreateMoby(0xF0C /* moby class 3852 */);
            *(u8 **)(state + 0x7C4) = newPart;
            if (newPart != 0) {
                newPart[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x32) = *(u16 *)(object + 0x32);
                *(long *)(*(u8 **)(state + 0x7C4) + 0x38) = *(long *)(object + 0x38);
                func_002A0F48(*(u8 **)(state + 0x7C4));
                *(s32 *)(*(u8 **)(state + 0x7C4) + 0x98) = 0;
                if ((*(u8 **)(state + 0x7C4))[0x43] != 0x14)
                    StartAnimationBlended(*(u8 **)(state + 0x7C4), 0x14, 0, 3);
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= 6;
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= *(u16 *)(object + 0x34) & 0x8000;
                *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                    *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
            } else {
                DestroyPieceAndParts(object);
            }
        }
        if (*(u8 **)(state + 0x7C0) != 0) {
            get_moby_color(object, &b0, &b1, &b2);
            set_moby_color(*(u8 **)(state + 0x7C0), b0, b1, b2);
        }
    }
    if (*(u8 **)(state + 0x7C4) != 0) {
        get_moby_color(object, &b0, &b1, &b2);
        set_moby_color(*(u8 **)(state + 0x7C4), b0, b1, b2);
    }
    if (*(s16 *)(state + 0x7F4) != -1) {
        *(u16 *)(state + 0x7F6) = 0;
        for (idList = D_L18_001FB320[object[0x21]];
             object[0x21] != 0xFF && object[0x21] <= D_L18_001B2838[0] && idList != 0 &&
             ((idList != 0 && (s16)idList[-1] >= 0) || idList == D_L18_001FB320[object[0x21]]);
             idList++) {
            otherMoby = gMobyTable_L18[0] + ((*idList & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (IsInAttackState(otherMoby))
                *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F6) + 1;
        }
    } else {
        *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F4);
    }
    if (*(float *)(object + 0x18) < 90.0f ||
        (*(float *)(state + 0x800) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x800)))
        DestroyPieceAndParts(object);
    if (state[0x2E] == 2)
        DestroyPieceAndParts(object);
    if (*(float *)(state + 0x20) <= 0.0f) {
        if (object[0x20] != 0xD)
            DestroyPieceAndParts(object);
    }
    *(s32 *)(state + 0x79C) =
        SelectAimTarget_002B3BA8(object, *(s32 *)(state + 0x790), 0, 0, *(float *)(state + 0x794), 0.0f);
    if (object[0x20] < 4) {
        if (object[0x20] != 3)
            return;
        if (object[0xBC] == 0)
            return;
    }
    if (*(float *)(state + 0x7E8) < 1.5f) {
        *(float *)(state + 0x7E8) = *(float *)(state + 0x7E8) + 0.01f;
        *(float *)(object + 0x2C) = *(float *)(*(u8 **)(object + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C0) != 0)
            *(float *)(*(u8 **)(state + 0x7C0) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C0) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C4) != 0)
            *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C8) != 0)
            *(float *)(*(u8 **)(state + 0x7C8) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C8) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
    }
}
