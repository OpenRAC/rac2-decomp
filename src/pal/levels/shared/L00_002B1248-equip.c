/* func_PAL_L00_002B1248, the PAL copy of func_L00_002B1350: the same C, where func_L00_003C3A70
   becomes func_PAL_L00_003C77F0; 0x32 becomes 0x2a; 0x5A becomes 0x4B; func_L00_002B1308 becomes
   func_PAL_L00_002B1200; func_L00_002AF7D0 becomes func_PAL_L00_002AF6C0; func_002A7470 becomes
   func_PAL_002A7E68. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { u8 pad00[0xC]; u8 rank; } MobyClass;
typedef struct { u8 pad00[0x24]; MobyClass *cls; u8 pad28[0x54]; s16 visible; } SlotMoby;
typedef struct { u8 pad00[0x34]; int dirty; } Panel;
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
extern void func_PAL_L00_003C77F0(int);
extern int func_L00_0032EF10(u32, int, int *);
extern int func_L00_002D6418(void);
extern int func_L00_002ADF80(void);
extern int func_002829A8(void *);
extern int func_00294630(int);
extern void func_00294420(int);
extern void func_L00_002AB3E0(void);
extern int func_002A7820(int, int);
extern void func_PAL_L00_002B1200(int);
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_002A7E68(void *, int, int, int);

#define ITEM_ENTRY(id) (*(ItemClass *)(D_00139568[(id)] * sizeof(ItemClass) + (u8 *)D_L00_00262570))

/* Applies the hero's pending item request for equipment slot SLOT. */
void func_PAL_L00_002B1248(int slot) {
    Vector point;
    int changed, keepHelmet, keepSuit, combo, sound, cur;
    u8 *pose;
    if (slot == 0) {
        if (((HeroState *)D_00189E20)->locked && ((HeroState *)D_00189E20)->slots[slot].item != 10)
            ((HeroState *)D_00189E20)->pending = 1;
    }
    if (slot == 0 && ((HeroState *)D_00189E20)->locked && ((HeroState *)D_00189E20)->slots[slot].item == 10) {
        if (((HeroState *)D_00189E20)->request[slot] == 0x1F) {
            qcopy(&point, &((HeroState *)D_00189E20)->position);
            point.f[2] += 1.5f;
            if (ITEM_ENTRY(0x1F).fancy) func_L00_003ECC90(&point, 0xB02);
            else func_L00_003ECC90(&point, 0xCB2);
            ((HeroState *)D_00189E20)->request[slot] = 0;
        }
        if (((HeroState *)D_00189E20)->request[slot] == 9) {
            if (func_L00_002D3F30(9, 1)) ((HeroState *)D_00189E20)->armed = 1;
            else ((HeroState *)D_00189E20)->armed = 0;
            ((HeroState *)D_00189E20)->request[slot] = 0;
        }
        if (((HeroState *)D_00189E20)->request[slot] == 0x2D) {
            func_PAL_L00_003C77F0(ITEM_ENTRY(0x2D).fancy != 0);
            ((HeroState *)D_00189E20)->request[slot] = 0;
        }
    }
    if (((HeroState *)D_00189E20)->blocked && slot == 0 &&
        (!((HeroState *)D_00189E20)->pending || ((HeroState *)D_00189E20)->slots[slot].item == 10)) {
        ((HeroState *)D_00189E20)->pending = 0;
        return;
    }
    changed = 0;

    if (func_L00_0032EF10(0x80, 3, 0) || ((HeroState *)D_00189E20)->pending) {
        if (slot == 0 && ((HeroState *)D_00189E20)->slots[slot].item != 10) {
            if (((HeroState *)D_00189E20)->pending) {
                if (((HeroState *)D_00189E20)->slots[slot].item != 0 && ((HeroState *)D_00189E20)->slots[slot].item != 0x1F && ((HeroState *)D_00189E20)->slots[slot].item != 0x2D && ((HeroState *)D_00189E20)->slots[slot].item != 9)
                    ((HeroState *)D_00189E20)->previous[slot] = ((HeroState *)D_00189E20)->slots[slot].item;
            }
            ((HeroState *)D_00189E20)->current[slot] = 10;
            changed = 1;
        }
    }
    if (slot == 0) {
        combo = 0;
        if (((HeroState *)D_00189E20)->slots[0].item == 10 && D_001A7398[0] && (D_001A7A80[D_001A7398[0]] & 0x20)) {
            if ((D_00138180[0x1A0 / 4] & 3) == 3 && (D_00138180[0x1A4 / 4] & 3)) combo = 1;
        }
        if (((D_00138180[0x1A4 / 4] & 0x20) || ((D_00138180[0x1A4 / 4] & 5) && func_L00_002D6418()) || combo) &&
            !((HeroState *)D_00189E20)->locked) {
            int item = D_001A7398[slot];
            if (((HeroState *)D_00189E20)->slots[0].item != item && item) {
                changed = 1;
                ((HeroState *)D_00189E20)->current[slot] = item;
            }
        }
    }
    if (slot == 1) {
        if (((HeroState *)D_00189E20)->state == 0xF && D_001A7B08[4]) {
            if (D_001A7398[1] != 0x14 || !((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item) {
                ((HeroState *)D_00189E20)->request[1] = 0x14;
                if (((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)D_00189E20)->previous[slot] = ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)D_00189E20)->previous[slot] = 0x77;
            }
        }
        {
            if (((HeroState *)D_00189E20)->swimming && D_001A7B08[3] &&
                (D_001A7398[1] != 0x13 || !((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item)) {
                ((HeroState *)D_00189E20)->request[1] = 0x13;
                if (((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)D_00189E20)->previous[slot] = ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)D_00189E20)->previous[slot] = 0x77;
            }
        }
    }
    if (slot == 2 && ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby) {
        if (((HeroState *)D_00189E20)->state == 0x11 || ((HeroState *)D_00189E20)->move == 0x73 ||
            ((HeroState *)D_00189E20)->move == 0x67 || ((HeroState *)D_00189E20)->move == 0x7F ||
            ((HeroState *)D_00189E20)->diving)
            ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby->visible = 1;
        else ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby->visible = 0;
    }
    keepHelmet = 0;
    keepSuit = 0;
    if (slot == 3) {
        if (func_L00_002ADF80() || ((HeroState *)D_00189E20)->move == 0x12) {
            if (D_001A7398[3] != 4 && ((HeroState *)D_00189E20)->slots[slot].item != 4) {
                ((HeroState *)D_00189E20)->previous[slot] = ((HeroState *)D_00189E20)->slots[slot].item;
                keepHelmet = 1;
                ((HeroState *)D_00189E20)->request[slot] = 4;
            }
        } else if (((HeroState *)D_00189E20)->slots[slot].item == 4 && ((HeroState *)D_00189E20)->previous[slot]) {
            ((HeroState *)D_00189E20)->restore[slot] = 1;
        }
        if (((HeroState *)D_00189E20)->move == 0x82) {
            if (D_001A7398[slot] != 8 && ((HeroState *)D_00189E20)->slots[slot].item != 8) {
                keepSuit = 1;
                ((HeroState *)D_00189E20)->previous[slot] = ((HeroState *)D_00189E20)->slots[slot].item;
                ((HeroState *)D_00189E20)->request[slot] = 8;
            }
        } else if (((HeroState *)D_00189E20)->slots[slot].item == 8 && ((HeroState *)D_00189E20)->previous[slot]) {
            ((HeroState *)D_00189E20)->restore[slot] = 1;
        }
        if (((HeroState *)D_00189E20)->move == 8 &&
            (D_001A7398[slot] == 4 || D_001A7398[slot] == ((HeroState *)D_00189E20)->move)) {
            if (D_001A7A00[9]) ((HeroState *)D_00189E20)->request[slot] = 3;
            else ((HeroState *)D_00189E20)->request[slot] = 2;
        }
    }
    if (((HeroState *)D_00189E20)->restore[slot]) {
        int item;
        ((HeroState *)D_00189E20)->restore[slot] = 0;
        item = ((HeroState *)D_00189E20)->previous[slot];
        if (item && item != ((HeroState *)D_00189E20)->slots[slot].item) {
            { int *tbl = D_001A7398;
            if (item == 0x77) item = 0;
            ((HeroState *)D_00189E20)->previous[slot] = 0;
            ((HeroState *)D_00189E20)->current[slot] = item;
            tbl[slot] = item; }
            if (slot == 0) ITEM_ENTRY(((HeroState *)D_00189E20)->current[0]).flags = 0x20;
            changed = 1;
        }
    }
    if (((HeroState *)D_00189E20)->request[slot] == 0x1F || ((HeroState *)D_00189E20)->request[slot] == 0x3D) {
        qcopy(&point, &((HeroState *)D_00189E20)->position);
        point.f[2] += 1.5f;
        if (ITEM_ENTRY(0x1F).fancy) func_L00_003ECC90(&point, 0xB02);
        else func_L00_003ECC90(&point, 0xCB2);
        ((HeroState *)D_00189E20)->request[slot] = 0;
    }
    if (((HeroState *)D_00189E20)->request[slot] == 9) {
        if (func_L00_002D3F30(9, 1)) ((HeroState *)D_00189E20)->armed = 1;
        else ((HeroState *)D_00189E20)->armed = 0;
        ((HeroState *)D_00189E20)->request[slot] = 0;
    }
    if (((HeroState *)D_00189E20)->request[slot] == 0x2D) {
        func_PAL_L00_003C77F0(ITEM_ENTRY(0x2D).fancy != 0);
        ((HeroState *)D_00189E20)->request[slot] = 0;
    }
    if (((HeroState *)D_00189E20)->request[slot]) {
        if (((HeroState *)D_00189E20)->request[slot] != ((HeroState *)D_00189E20)->current[slot]) {
            if (slot == 1 && !((HeroState *)D_00189E20)->previous[slot]) {
                *(s16 *)&D_001A7A00[0x24] = ((HeroState *)D_00189E20)->request[slot];
                if (*(s16 *)&D_001A7A00[0x24] == 0x77) *(s16 *)&D_001A7A00[0x24] = 0;
            }
            if (((HeroState *)D_00189E20)->request[slot] == 0x77) {
                ((HeroState *)D_00189E20)->current[slot] = 0;
                D_001A7398[slot] = 0;
            } else {
                int item;
                if (slot == 0) {
                    int item = D_001A7398[0];
                    if (item != 0x26 && item != 0x33 && item && ((HeroState *)D_00189E20)->request[0] != 0x26 &&
                        ((HeroState *)D_00189E20)->request[0] != 0x33 && ((HeroState *)D_00189E20)->request[0] != item)
                        *(int *)&D_001A7A00[4] = item;
                }
                item = ((HeroState *)D_00189E20)->request[slot];
                ((HeroState *)D_00189E20)->current[slot] = item;
                if (!keepHelmet || item != 4) D_001A7398[slot] = item;
                if (!keepSuit || ((HeroState *)D_00189E20)->current[slot] != 8)
                    D_001A7398[slot] = ((HeroState *)D_00189E20)->current[slot];
                if (slot == 0) ITEM_ENTRY(((HeroState *)D_00189E20)->current[0]).flags = 0x20;
            }
            changed = 1;
        } else {
            ((HeroState *)D_00189E20)->request[slot] = 0;
        }
    }
    if (((HeroState *)D_00189E20)->slots[slot].state == 2) changed = 0;
    if (((HeroState *)D_00189E20)->slots[slot].state == 1 && !((HeroState *)D_00189E20)->slots[slot].pose) ((HeroState *)D_00189E20)->slots[slot].pose = ((HeroState *)D_00189E20)->slots[slot].restPose;
    pose = &((HeroState *)D_00189E20)->slots[0].pose;
    if (!func_002829A8(pose + slot * sizeof(Slot))) changed = 0;
    if (slot == 0) {
        if (changed) {
            changed = 0;
            ((HeroState *)D_00189E20)->queued = *(int *)(pose + 0x10AB);
        }
        if (((HeroState *)D_00189E20)->queued) {
            sound = ITEM_ENTRY(((HeroState *)D_00189E20)->queued).sound;
            if (!func_00294630(sound)) {
                func_00294420(sound);
            } else {
                changed = 1;
                *(int *)(pose + 0x10AB) = ((HeroState *)D_00189E20)->queued;
                ((HeroState *)D_00189E20)->queued = 0;
            }
        }
    }
    if (changed) {
        ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].anim = 3;
        func_L00_002AB3E0();
        ((HeroState *)D_00189E20)->quickTimer = func_002A7820(0x2a, 0x4B);
        func_PAL_L00_002B1200(((HeroState *)D_00189E20)->current[slot]);
        if (((HeroState *)D_00189E20)->refresh) func_PAL_L00_002AF6C0();
        if (slot == 0) {
            if (((HeroState *)D_00189E20)->current[0] == 10) D_001A7A00[8] = 1;
            else D_001A7A00[8] = 0;
        }
        if (slot == 3) {
            if (((HeroState *)D_00189E20)->slots[3].item == 3) D_001A7A00[9] = 1;
            else D_001A7A00[9] = 0;
        }
        ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].swap = 0;
        ((HeroState *)D_00189E20)->request[slot] = 0;
        ((HeroState *)D_00189E20)->pending = 0;
        cur = ((HeroState *)D_00189E20)->current[slot];
        if (slot == 0 && ITEM_ENTRY(cur).skin != ((HeroState *)D_00189E20)->skin) {
            if (((HeroState *)D_00189E20)->panel[0]) ((HeroState *)D_00189E20)->panel[0]->dirty = 1;
            if (((HeroState *)D_00189E20)->panel[1]) ((HeroState *)D_00189E20)->panel[1]->dirty = 1;
        }
        if (((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby && ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby->cls->rank >= 3)
            func_PAL_002A7E68(((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby, 2, 0, 2);
        if (((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster && slot != 3 &&
            ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster->cls->rank >= 3)
            func_PAL_002A7E68(((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster, 2, 0, 2);
        ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].mode = 3;
    }
    if (slot == 2 && !D_001A7398[2] && !((HeroState *)D_00189E20)->slots[2].moby)
        ((HeroState *)D_00189E20)->request[2] = 0x2F;
    if (slot == 1 && !D_001A7398[1] && !((HeroState *)D_00189E20)->slots[1].moby)
        ((HeroState *)D_00189E20)->request[1] = 0x34;
}
