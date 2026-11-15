#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { u8 pad00[0xC]; u8 rank; } MobyClass;
typedef struct { u8 pad00[0x24]; MobyClass *cls; u8 pad28[0x54]; s16 visible; } SlotMoby;
typedef struct { u8 pad00[0x34]; int dirty; } Panel;
/* One equipment slot of the hero (0x50 bytes). */
typedef struct {
    SlotMoby *moby, *holster;
    u8 pad08[0x11];
    u8 pose, swap, pad1B, state, restPose, pad1E[2];
    int anim, mode, item;
    u8 pad2C[0x24];
} Slot;
typedef struct {
    u8 pad0000[0x80];
    Vector position;
    u8 pad0090[0xE00];
    Panel *panel[2];
    u8 pad0E98[0x308];
    int quickTimer;
    u8 pad11A4[0x7C];
    Slot slots[4];
    u8 pad1360[0x137];
    u8 swimming;
    u8 pad1498[0x43C];
    int armed;
    u8 pad18D8[0x9BC];
    int move, pad2298, state;
    u8 pad22A0[0x16];
    u8 pending, locked, refresh, pad22B9[2], skin, blocked, pad22BD[0xB];
    int request[4], pad22D8[3], current[4], pad22F4[3], previous[4], pad2310[3], restore[4];
    int pad232C[3], queued;
    u8 pad233C[0x1B4];
    u8 diving;
} HeroState;
typedef struct { u8 pad00[4]; u8 fancy; u8 pad05[0xF]; int sound; u8 pad18[4]; int skin, pad20, flags; u8 pad28[0xB8]; } ItemClass;
extern u8 D_00189E20[];
extern u32 D_00138180[];
extern u8 D_00139568[];
extern ItemClass D_L00_00262570[];
extern int D_001A7398[] __attribute__((sda));
extern u8 D_001A7A80[] __attribute__((sda));
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_001A7B08[] __attribute__((sda));
extern void func_L00_003ECC90(Vector *, int);
extern int func_L00_002D3F30(int, int);
extern void func_L00_003C3A70(int);
extern int func_L00_0032EF10(u32, int, int *);
extern int func_L00_002D6418(void);
extern int func_L00_002ADF80(void);
extern int func_002829A8(void *);
extern int func_00294630(int);
extern void func_00294420(int);
extern void func_L00_002AB3E0(void);
extern int func_002A7820(int, int);
extern void func_L00_002B1308(int);
extern void func_L00_002AF7D0(void);
extern void func_002A7470(void *, int, int, int);

#define ITEM_ENTRY(id) (*(ItemClass *)(D_00139568[(id)] * sizeof(ItemClass) + (u8 *)D_L00_00262570))

/* Applies the hero's pending item request for equipment slot SLOT. */
void func_L00_002B1350(int slot) {
    Vector point;
    int changed, keepHelmet, keepSuit, combo, sound, cur;
    u8 *pose;
    if (slot == 0) {
        if (((HeroState *)gHeroState)->locked && ((HeroState *)gHeroState)->slots[slot].item != 10)
            ((HeroState *)gHeroState)->pending = 1;
    }
    if (slot == 0 && ((HeroState *)gHeroState)->locked && ((HeroState *)gHeroState)->slots[slot].item == 10) {
        if (((HeroState *)gHeroState)->request[slot] == 0x1F) {
            qcopy(&point, &((HeroState *)gHeroState)->position);
            point.f[2] += 1.5f;
            if (ITEM_ENTRY(0x1F).fancy) SpawnKilonoidOrSynthenoid(&point, 0xB02);
            else SpawnKilonoidOrSynthenoid(&point, 0xCB2);
            ((HeroState *)gHeroState)->request[slot] = 0;
        }
        if (((HeroState *)gHeroState)->request[slot] == 9) {
            if (SpendWeaponAmmo(9, 1)) ((HeroState *)gHeroState)->armed = 1;
            else ((HeroState *)gHeroState)->armed = 0;
            ((HeroState *)gHeroState)->request[slot] = 0;
        }
        if (((HeroState *)gHeroState)->request[slot] == 0x2D) {
            CreateTrailOwnerMoby(ITEM_ENTRY(0x2D).fancy != 0);
            ((HeroState *)gHeroState)->request[slot] = 0;
        }
    }
    if (((HeroState *)gHeroState)->blocked && slot == 0 &&
        (!((HeroState *)gHeroState)->pending || ((HeroState *)gHeroState)->slots[slot].item == 10)) {
        ((HeroState *)gHeroState)->pending = 0;
        return;
    }
    changed = 0;

    if (PadPressedWithin(0x80, 3, 0) || ((HeroState *)gHeroState)->pending) {
        if (slot == 0 && ((HeroState *)gHeroState)->slots[slot].item != 10) {
            if (((HeroState *)gHeroState)->pending) {
                if (((HeroState *)gHeroState)->slots[slot].item != 0 && ((HeroState *)gHeroState)->slots[slot].item != 0x1F && ((HeroState *)gHeroState)->slots[slot].item != 0x2D && ((HeroState *)gHeroState)->slots[slot].item != 9)
                    ((HeroState *)gHeroState)->previous[slot] = ((HeroState *)gHeroState)->slots[slot].item;
            }
            ((HeroState *)gHeroState)->current[slot] = 10;
            changed = 1;
        }
    }
    if (slot == 0) {
        combo = 0;
        if (((HeroState *)gHeroState)->slots[0].item == 10 && D_001A7398[0] && (D_001A7A80[D_001A7398[0]] & 0x20)) {
            if ((gPadState[0x1A0 / 4] & 3) == 3 && (gPadState[0x1A4 / 4] & 3)) combo = 1;
        }
        if (((gPadState[0x1A4 / 4] & 0x20) || ((gPadState[0x1A4 / 4] & 5) && IsHeroActionAllowed()) || combo) &&
            !((HeroState *)gHeroState)->locked) {
            int item = D_001A7398[slot];
            if (((HeroState *)gHeroState)->slots[0].item != item && item) {
                changed = 1;
                ((HeroState *)gHeroState)->current[slot] = item;
            }
        }
    }
    if (slot == 1) {
        if (((HeroState *)gHeroState)->state == 0xF && D_001A7B08[4]) {
            if (D_001A7398[1] != 0x14 || !((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item) {
                ((HeroState *)gHeroState)->request[1] = 0x14;
                if (((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)gHeroState)->previous[slot] = ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)gHeroState)->previous[slot] = 0x77;
            }
        }
        {
            if (((HeroState *)gHeroState)->swimming && D_001A7B08[3] &&
                (D_001A7398[1] != 0x13 || !((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item)) {
                ((HeroState *)gHeroState)->request[1] = 0x13;
                if (((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)gHeroState)->previous[slot] = ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)gHeroState)->previous[slot] = 0x77;
            }
        }
    }
    if (slot == 2 && ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby) {
        if (((HeroState *)gHeroState)->state == 0x11 || ((HeroState *)gHeroState)->move == 0x73 ||
            ((HeroState *)gHeroState)->move == 0x67 || ((HeroState *)gHeroState)->move == 0x7F ||
            ((HeroState *)gHeroState)->diving)
            ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby->visible = 1;
        else ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby->visible = 0;
    }
    keepHelmet = 0;
    keepSuit = 0;
    if (slot == 3) {
        if (IsHeroInSpecialKindOrMode() || ((HeroState *)gHeroState)->move == 0x12) {
            if (D_001A7398[3] != 4 && ((HeroState *)gHeroState)->slots[slot].item != 4) {
                ((HeroState *)gHeroState)->previous[slot] = ((HeroState *)gHeroState)->slots[slot].item;
                keepHelmet = 1;
                ((HeroState *)gHeroState)->request[slot] = 4;
            }
        } else if (((HeroState *)gHeroState)->slots[slot].item == 4 && ((HeroState *)gHeroState)->previous[slot]) {
            ((HeroState *)gHeroState)->restore[slot] = 1;
        }
        if (((HeroState *)gHeroState)->move == 0x82) {
            if (D_001A7398[slot] != 8 && ((HeroState *)gHeroState)->slots[slot].item != 8) {
                keepSuit = 1;
                ((HeroState *)gHeroState)->previous[slot] = ((HeroState *)gHeroState)->slots[slot].item;
                ((HeroState *)gHeroState)->request[slot] = 8;
            }
        } else if (((HeroState *)gHeroState)->slots[slot].item == 8 && ((HeroState *)gHeroState)->previous[slot]) {
            ((HeroState *)gHeroState)->restore[slot] = 1;
        }
        if (((HeroState *)gHeroState)->move == 8 &&
            (D_001A7398[slot] == 4 || D_001A7398[slot] == ((HeroState *)gHeroState)->move)) {
            if (D_001A7A00[9]) ((HeroState *)gHeroState)->request[slot] = 3;
            else ((HeroState *)gHeroState)->request[slot] = 2;
        }
    }
    if (((HeroState *)gHeroState)->restore[slot]) {
        int item;
        ((HeroState *)gHeroState)->restore[slot] = 0;
        item = ((HeroState *)gHeroState)->previous[slot];
        if (item && item != ((HeroState *)gHeroState)->slots[slot].item) {
            { int *tbl = D_001A7398;
            if (item == 0x77) item = 0;
            ((HeroState *)gHeroState)->previous[slot] = 0;
            ((HeroState *)gHeroState)->current[slot] = item;
            tbl[slot] = item; }
            if (slot == 0) ITEM_ENTRY(((HeroState *)gHeroState)->current[0]).flags = 0x20;
            changed = 1;
        }
    }
    if (((HeroState *)gHeroState)->request[slot] == 0x1F || ((HeroState *)gHeroState)->request[slot] == 0x3D) {
        qcopy(&point, &((HeroState *)gHeroState)->position);
        point.f[2] += 1.5f;
        if (ITEM_ENTRY(0x1F).fancy) SpawnKilonoidOrSynthenoid(&point, 0xB02);
        else SpawnKilonoidOrSynthenoid(&point, 0xCB2);
        ((HeroState *)gHeroState)->request[slot] = 0;
    }
    if (((HeroState *)gHeroState)->request[slot] == 9) {
        if (SpendWeaponAmmo(9, 1)) ((HeroState *)gHeroState)->armed = 1;
        else ((HeroState *)gHeroState)->armed = 0;
        ((HeroState *)gHeroState)->request[slot] = 0;
    }
    if (((HeroState *)gHeroState)->request[slot] == 0x2D) {
        CreateTrailOwnerMoby(ITEM_ENTRY(0x2D).fancy != 0);
        ((HeroState *)gHeroState)->request[slot] = 0;
    }
    if (((HeroState *)gHeroState)->request[slot]) {
        if (((HeroState *)gHeroState)->request[slot] != ((HeroState *)gHeroState)->current[slot]) {
            if (slot == 1 && !((HeroState *)gHeroState)->previous[slot]) {
                *(s16 *)&D_001A7A00[0x24] = ((HeroState *)gHeroState)->request[slot];
                if (*(s16 *)&D_001A7A00[0x24] == 0x77) *(s16 *)&D_001A7A00[0x24] = 0;
            }
            if (((HeroState *)gHeroState)->request[slot] == 0x77) {
                ((HeroState *)gHeroState)->current[slot] = 0;
                D_001A7398[slot] = 0;
            } else {
                int item;
                if (slot == 0) {
                    int item = D_001A7398[0];
                    if (item != 0x26 && item != 0x33 && item && ((HeroState *)gHeroState)->request[0] != 0x26 &&
                        ((HeroState *)gHeroState)->request[0] != 0x33 && ((HeroState *)gHeroState)->request[0] != item)
                        *(int *)&D_001A7A00[4] = item;
                }
                item = ((HeroState *)gHeroState)->request[slot];
                ((HeroState *)gHeroState)->current[slot] = item;
                if (!keepHelmet || item != 4) D_001A7398[slot] = item;
                if (!keepSuit || ((HeroState *)gHeroState)->current[slot] != 8)
                    D_001A7398[slot] = ((HeroState *)gHeroState)->current[slot];
                if (slot == 0) ITEM_ENTRY(((HeroState *)gHeroState)->current[0]).flags = 0x20;
            }
            changed = 1;
        } else {
            ((HeroState *)gHeroState)->request[slot] = 0;
        }
    }
    if (((HeroState *)gHeroState)->slots[slot].state == 2) changed = 0;
    if (((HeroState *)gHeroState)->slots[slot].state == 1 && !((HeroState *)gHeroState)->slots[slot].pose) ((HeroState *)gHeroState)->slots[slot].pose = ((HeroState *)gHeroState)->slots[slot].restPose;
    pose = &((HeroState *)gHeroState)->slots[0].pose;
    if (!FastVectorHelperA(pose + slot * sizeof(Slot))) changed = 0;
    if (slot == 0) {
        if (changed) {
            changed = 0;
            ((HeroState *)gHeroState)->queued = *(int *)(pose + 0x10AB);
        }
        if (((HeroState *)gHeroState)->queued) {
            sound = ITEM_ENTRY(((HeroState *)gHeroState)->queued).sound;
            if (!IsClassCached(sound)) {
                LoadClassIntoFreeCacheSlot(sound);
            } else {
                changed = 1;
                *(int *)(pose + 0x10AB) = ((HeroState *)gHeroState)->queued;
                ((HeroState *)gHeroState)->queued = 0;
            }
        }
    }
    if (changed) {
        ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].anim = 3;
        ClearHeroSlotRecords();
        ((HeroState *)gHeroState)->quickTimer = RandomIntRange(0x32, 0x5A);
        StartHeroTimedStateForMode(((HeroState *)gHeroState)->current[slot]);
        if (((HeroState *)gHeroState)->refresh) cancel_hero_item_animation();
        if (slot == 0) {
            if (((HeroState *)gHeroState)->current[0] == 10) D_001A7A00[8] = 1;
            else D_001A7A00[8] = 0;
        }
        if (slot == 3) {
            if (((HeroState *)gHeroState)->slots[3].item == 3) D_001A7A00[9] = 1;
            else D_001A7A00[9] = 0;
        }
        ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].swap = 0;
        ((HeroState *)gHeroState)->request[slot] = 0;
        ((HeroState *)gHeroState)->pending = 0;
        cur = ((HeroState *)gHeroState)->current[slot];
        if (slot == 0 && ITEM_ENTRY(cur).skin != ((HeroState *)gHeroState)->skin) {
            if (((HeroState *)gHeroState)->panel[0]) ((HeroState *)gHeroState)->panel[0]->dirty = 1;
            if (((HeroState *)gHeroState)->panel[1]) ((HeroState *)gHeroState)->panel[1]->dirty = 1;
        }
        if (((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby && ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby->cls->rank >= 3)
            StartAnimationBlended(((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].moby, 2, 0, 2);
        if (((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].holster && slot != 3 &&
            ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].holster->cls->rank >= 3)
            StartAnimationBlended(((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].holster, 2, 0, 2);
        ((HeroState *)(gHeroState + slot * sizeof(Slot)))->slots[0].mode = 3;
    }
    if (slot == 2 && !D_001A7398[2] && !((HeroState *)gHeroState)->slots[2].moby)
        ((HeroState *)gHeroState)->request[2] = 0x2F;
    if (slot == 1 && !D_001A7398[1] && !((HeroState *)gHeroState)->slots[1].moby)
        ((HeroState *)gHeroState)->request[1] = 0x34;
}
