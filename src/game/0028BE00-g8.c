#include "common.h"

typedef struct { char pad[0x14]; int name; char pad18[0x70]; unsigned short valid; char pad8a[4]; unsigned short ammo; char pad90[0x50]; } Info;
typedef struct { char pad[0x148]; float x, y; char pad150[0x70]; int held, pressed, pad1c8, inhibit, pad1d0, pad1d4, repeat; } Controller;
typedef struct { char pad[0xf0]; unsigned short uses; char padf2[2]; unsigned int maxFrame, levels; } Stats;
typedef struct { char pad[0x1248]; int selected; char pad124c[0x107c]; int pending; } Hero;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; } Slot;
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

extern int D_001A8C64;
extern unsigned char D_001A7BB0[] __attribute__((sda));
#define D_001A7BB3 D_001A7BB0[3]
extern int D_001A8CFC;
extern int D_001A8D30 __attribute__((sda));
extern int D_001A8D48 __attribute__((sda));
extern int D_001A8D90[] __attribute__((sda));
extern int D_001B18D0;
extern Slot **D_001B18D4;
extern float D_001A8E10;
extern int D_001B1900;
extern int D_001B18FC;
extern int D_001B1598, D_001B18F8;
extern unsigned char D_00139568[];
extern int D_00139688[];
extern Info D_00239BA0[];
extern Controller D_00138180;
extern char D_0018C316[];
extern char D_001A8E18[];
extern Stats D_0018C750;
extern Hero D_00189E20;
extern unsigned int D_001A7390;
extern int D_001A79F0;
extern short D_001A63AC NOT_SDA;
extern int func_00287E48(void), func_00290748(void);
extern void func_00290730(void), func_00287E60(void);
extern void func_0034CB88(void *, int);
extern int func_00282978(void *);
extern float func_00282C10(float), func_00283248(float, float), func_00283CE0(int), func_00283BE0(float, float), func_00283C80(float, float), func_00283C28(float);
extern int func_00283CF0(float);
extern void func_0026FEB8(void *), func_002B7AD0(void), func_002E5E58(int, int, int);
extern int func_00294630(int);
extern void func_00294420(int), func_00287E18(void), func_00290728(void), func_00290720(void);
extern int func_0028B5D0(int);

static inline Info *InfoOf(int id)
{
    return &gWeaponTable_00239BA0[gItemSlotToRecord[id]];
}

/* Updates the round weapon-select menu: reads the stick, picks a slot, plays the click sound and equips the chosen weapon when the button is let go. */
void func_0028BE00(Selector *selector)
{
    float stickX, stickY, stickMagnitude, stickAngle, shiftedAngle, slotPosition, oldSlotAngle;
    int oldSelection, nudge, slot, nextSlot, weaponId;
    int active;
    unsigned char *fade, *fadeStart;

    if (gNoticeOwner) return;
    active = 0;
    if (!D_001A7BB3 || IsMenuStateSeven() || !D_001A7BB3) {
        active = 1;
        if (!D_001A7BB3) {
            RequestHudOpen();
            if (!IsHudOpenDone()) active = 0;
        }
    }
    fadeStart = selector->fade;
    if (active && D_001A8CFC) {
        SetScreenValueAndRestartSixFades((char *)D_001A8CFC + 0x376C8, IsMenuStateSeven() ? D_001A8D30 : 2);
        SetStateWordToThree();
    }
    selector->timeout = 180;
    selector->timer = 24;
    if (FastDecTimer(D_0018C316) && !D_001A7BB3) gPadState.inhibit = 2;
    stickX = gPadState.x;
    stickY = gPadState.y;
    stickMagnitude = square_root(stickX * stickX + stickY * stickY);
    if (stickMagnitude != 0.0f) {
        stickX /= stickMagnitude;
        stickY /= stickMagnitude;
    }
    stickAngle = FastMatrixHelperA(stickX, stickY);
    if ((selector->state >> 24) == 0) {
        if ((gPadState.pressed & 0xF000) || stickMagnitude < 0.5f || --selector->state == -1) {
            selector->selected = -1;
            selector->state = 0x10000FF;
        }
    }
    nudge = 0;
    oldSelection = selector->selected;
    if ((selector->state >> 24) == 1 && (gPadState.held & 0x10) && active) {
        if (stickMagnitude > 0.9f) {
            shiftedAngle = stickAngle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)gRadialSlotCount;
            slotPosition = shiftedAngle * 0.15915494f * (float)gRadialSlotCount;
            oldSlotAngle = (float)oldSelection * 6.2831855f / IntToFloat(gRadialSlotCount) - 3.1415927f;
            if (oldSelection == -1 || FastDiffRots(oldSlotAngle, fast_subtract_rotations(stickAngle, 1.5707964f)) > 0.5890487f) {
                slot = (int)slotPosition % gRadialSlotCount;
                if ((slot ^ 1) & 1) {
                    float fraction = slotPosition - (float)FloatToInt(slotPosition);
                    if (fraction > 0.8f) slot++;
                    else if (fraction < 0.2f) slot--;
                    slot = (slot + gRadialSlotCount) % gRadialSlotCount;
                }
                selector->selected = slot;
                nudge = -1;
                D_001A8E10 = FastFloatHelperG(shiftedAngle - ((float)slot * 0.78539824f + 0.39269912f));
                if (D_001A8E10 > 0.0f) nudge = 1;
            }
        } else if (gPadState.repeat == 0 && (gPadState.pressed & 0xF000)) {
            int wanted;
            wanted = oldSelection;
            if (gPadState.pressed & 0x1000) {
                int target;
                if (wanted == -1) target = D_001A8D90[4];
                else target = gRadialMenuPages[gRadialMenuPageIndex][wanted].f10;
                wanted = target;
            }
            if (gPadState.pressed & 0x4000) {
                int target;
                if (wanted == -1) target = D_001A8D90[5];
                else target = gRadialMenuPages[gRadialMenuPageIndex][wanted].f14;
                wanted = target;
            }
            if (gPadState.pressed & 0x8000) {
                int target;
                if (wanted == -1) target = D_001A8D90[2];
                else target = gRadialMenuPages[gRadialMenuPageIndex][wanted].f8;
                wanted = target;
            }
            if (gPadState.pressed & 0x2000) {
                int target;
                if (wanted == -1) target = D_001A8D90[3];
                else target = gRadialMenuPages[gRadialMenuPageIndex][wanted].fC;
                wanted = target;
            }
            selector->selected = wanted;
        }
        {
            Slot *target = gRadialMenuPages[gRadialMenuPageIndex];
            int current = selector->selected;
            if (target[current].f0 == 0 && nudge != 0) {
                nextSlot = (current + nudge) % gRadialSlotCount;
                if (target[nextSlot].f0 != 0) selector->selected = nextSlot;
            }
        }
    }
    fade = selector->fade;
    if (selector->selected != oldSelection) {
        STUB_printf(D_001A8E18);
        RequestDiscReadBreak();
        fade[1] = 0;
        PlaySoundFromGlobalBank(3, 0, 0);
    } else if (fade[1] < 8) fade[1]++;
    if (selector->selected >= 0 && !IsClassCached(InfoOf(gRadialMenuPages[gRadialMenuPageIndex][selector->selected].f18)->name)) {
        LoadClassIntoFreeCacheSlot(InfoOf(gRadialMenuPages[gRadialMenuPageIndex][selector->selected].f18)->name);
    } else {
        if (!(gPadState.held & 0x10) && !D_001A63AC) {
            if (fade[0]) fade[0]--;
            if (fade[0] == 0 && selector->selected >= 0 && (weaponId = gRadialMenuPages[gRadialMenuPageIndex][selector->selected].f18) != 0) {
                Info *info;
                if (gHeroState.selected != weaponId && gProgressStatistics.uses < 0xFFFF) gProgressStatistics.uses++;
                if (gProgressStatistics.maxFrame < D_001A7390) gProgressStatistics.maxFrame = D_001A7390;
                gProgressStatistics.levels = gProgressStatistics.levels | (1 << gCurrentMapIndex) | 0x80000000;
                gHeroState.pending = weaponId;
                info = InfoOf(weaponId);
                if (info->valid && info->ammo < gItemAmmoCounts[weaponId]) gItemAmmoCounts[weaponId] = info->ammo;
            }
            if (D_001A7BB3) AdvanceMenuStateOnMode7();
            else {
                ClearHudFlagB();
                ClearHudFlagA();
            }
        } else if (fade[0] < 8) fade[0]++;
    }
    if (fadeStart[0] == 0) {
        {
            int state = selector->state;
            D_001B1900 = selector->selected;
            D_001B18FC = state;
        }
        CloseHudElementByKey(selector->handle);
        selector->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
