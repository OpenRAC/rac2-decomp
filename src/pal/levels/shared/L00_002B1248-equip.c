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
extern u8 g_hero_state[];
extern u32 g_pad_state[];
extern u8 g_item_slot_to_record[];
extern ItemClass g_weapon_l00_table[];
extern int D_001A7398[] __attribute__((sda));
extern u8 D_001A7A80[] __attribute__((sda));
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_001A7B08[] __attribute__((sda));
extern void synthenoid_spawn_or_kilonoid(Vector *, int);
extern int weapon_spend_ammo(int, int);
extern void func_PAL_L00_003C77F0(int);
extern int PadPressedWithin(u32, int, int *);
extern int hero_is_action_allowed(void);
extern int hero_is_in_special_kind_or_mode(void);
extern int vec_fast_helper_a(void *);
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void hero_clear_slot_records(void);
extern int math_random_int_range(int, int);
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
        if (((HeroState *)g_hero_state)->locked && ((HeroState *)g_hero_state)->slots[slot].item != 10)
            ((HeroState *)g_hero_state)->pending = 1;
    }
    if (slot == 0 && ((HeroState *)g_hero_state)->locked && ((HeroState *)g_hero_state)->slots[slot].item == 10) {
        if (((HeroState *)g_hero_state)->request[slot] == 0x1F) {
            qcopy(&point, &((HeroState *)g_hero_state)->position);
            point.f[2] += 1.5f;
            if (ITEM_ENTRY(0x1F).fancy) synthenoid_spawn_or_kilonoid(&point, 0xB02);
            else synthenoid_spawn_or_kilonoid(&point, 0xCB2);
            ((HeroState *)g_hero_state)->request[slot] = 0;
        }
        if (((HeroState *)g_hero_state)->request[slot] == 9) {
            if (weapon_spend_ammo(9, 1)) ((HeroState *)g_hero_state)->armed = 1;
            else ((HeroState *)g_hero_state)->armed = 0;
            ((HeroState *)g_hero_state)->request[slot] = 0;
        }
        if (((HeroState *)g_hero_state)->request[slot] == 0x2D) {
            func_PAL_L00_003C77F0(ITEM_ENTRY(0x2D).fancy != 0);
            ((HeroState *)g_hero_state)->request[slot] = 0;
        }
    }
    if (((HeroState *)g_hero_state)->blocked && slot == 0 &&
        (!((HeroState *)g_hero_state)->pending || ((HeroState *)g_hero_state)->slots[slot].item == 10)) {
        ((HeroState *)g_hero_state)->pending = 0;
        return;
    }
    changed = 0;

    if (PadPressedWithin(0x80, 3, 0) || ((HeroState *)g_hero_state)->pending) {
        if (slot == 0 && ((HeroState *)g_hero_state)->slots[slot].item != 10) {
            if (((HeroState *)g_hero_state)->pending) {
                if (((HeroState *)g_hero_state)->slots[slot].item != 0 && ((HeroState *)g_hero_state)->slots[slot].item != 0x1F && ((HeroState *)g_hero_state)->slots[slot].item != 0x2D && ((HeroState *)g_hero_state)->slots[slot].item != 9)
                    ((HeroState *)g_hero_state)->previous[slot] = ((HeroState *)g_hero_state)->slots[slot].item;
            }
            ((HeroState *)g_hero_state)->current[slot] = 10;
            changed = 1;
        }
    }
    if (slot == 0) {
        combo = 0;
        if (((HeroState *)g_hero_state)->slots[0].item == 10 && D_001A7398[0] && (D_001A7A80[D_001A7398[0]] & 0x20)) {
            if ((g_pad_state[0x1A0 / 4] & 3) == 3 && (g_pad_state[0x1A4 / 4] & 3)) combo = 1;
        }
        if (((g_pad_state[0x1A4 / 4] & 0x20) || ((g_pad_state[0x1A4 / 4] & 5) && hero_is_action_allowed()) || combo) &&
            !((HeroState *)g_hero_state)->locked) {
            int item = D_001A7398[slot];
            if (((HeroState *)g_hero_state)->slots[0].item != item && item) {
                changed = 1;
                ((HeroState *)g_hero_state)->current[slot] = item;
            }
        }
    }
    if (slot == 1) {
        if (((HeroState *)g_hero_state)->state == 0xF && D_001A7B08[4]) {
            if (D_001A7398[1] != 0x14 || !((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item) {
                ((HeroState *)g_hero_state)->request[1] = 0x14;
                if (((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)g_hero_state)->previous[slot] = ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)g_hero_state)->previous[slot] = 0x77;
            }
        }
        {
            if (((HeroState *)g_hero_state)->swimming && D_001A7B08[3] &&
                (D_001A7398[1] != 0x13 || !((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item)) {
                ((HeroState *)g_hero_state)->request[1] = 0x13;
                if (((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item)
                    ((HeroState *)g_hero_state)->previous[slot] = ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].item;
                else ((HeroState *)g_hero_state)->previous[slot] = 0x77;
            }
        }
    }
    if (slot == 2 && ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby) {
        if (((HeroState *)g_hero_state)->state == 0x11 || ((HeroState *)g_hero_state)->move == 0x73 ||
            ((HeroState *)g_hero_state)->move == 0x67 || ((HeroState *)g_hero_state)->move == 0x7F ||
            ((HeroState *)g_hero_state)->diving)
            ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby->visible = 1;
        else ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby->visible = 0;
    }
    keepHelmet = 0;
    keepSuit = 0;
    if (slot == 3) {
        if (hero_is_in_special_kind_or_mode() || ((HeroState *)g_hero_state)->move == 0x12) {
            if (D_001A7398[3] != 4 && ((HeroState *)g_hero_state)->slots[slot].item != 4) {
                ((HeroState *)g_hero_state)->previous[slot] = ((HeroState *)g_hero_state)->slots[slot].item;
                keepHelmet = 1;
                ((HeroState *)g_hero_state)->request[slot] = 4;
            }
        } else if (((HeroState *)g_hero_state)->slots[slot].item == 4 && ((HeroState *)g_hero_state)->previous[slot]) {
            ((HeroState *)g_hero_state)->restore[slot] = 1;
        }
        if (((HeroState *)g_hero_state)->move == 0x82) {
            if (D_001A7398[slot] != 8 && ((HeroState *)g_hero_state)->slots[slot].item != 8) {
                keepSuit = 1;
                ((HeroState *)g_hero_state)->previous[slot] = ((HeroState *)g_hero_state)->slots[slot].item;
                ((HeroState *)g_hero_state)->request[slot] = 8;
            }
        } else if (((HeroState *)g_hero_state)->slots[slot].item == 8 && ((HeroState *)g_hero_state)->previous[slot]) {
            ((HeroState *)g_hero_state)->restore[slot] = 1;
        }
        if (((HeroState *)g_hero_state)->move == 8 &&
            (D_001A7398[slot] == 4 || D_001A7398[slot] == ((HeroState *)g_hero_state)->move)) {
            if (D_001A7A00[9]) ((HeroState *)g_hero_state)->request[slot] = 3;
            else ((HeroState *)g_hero_state)->request[slot] = 2;
        }
    }
    if (((HeroState *)g_hero_state)->restore[slot]) {
        int item;
        ((HeroState *)g_hero_state)->restore[slot] = 0;
        item = ((HeroState *)g_hero_state)->previous[slot];
        if (item && item != ((HeroState *)g_hero_state)->slots[slot].item) {
            { int *tbl = D_001A7398;
            if (item == 0x77) item = 0;
            ((HeroState *)g_hero_state)->previous[slot] = 0;
            ((HeroState *)g_hero_state)->current[slot] = item;
            tbl[slot] = item; }
            if (slot == 0) ITEM_ENTRY(((HeroState *)g_hero_state)->current[0]).flags = 0x20;
            changed = 1;
        }
    }
    if (((HeroState *)g_hero_state)->request[slot] == 0x1F || ((HeroState *)g_hero_state)->request[slot] == 0x3D) {
        qcopy(&point, &((HeroState *)g_hero_state)->position);
        point.f[2] += 1.5f;
        if (ITEM_ENTRY(0x1F).fancy) synthenoid_spawn_or_kilonoid(&point, 0xB02);
        else synthenoid_spawn_or_kilonoid(&point, 0xCB2);
        ((HeroState *)g_hero_state)->request[slot] = 0;
    }
    if (((HeroState *)g_hero_state)->request[slot] == 9) {
        if (weapon_spend_ammo(9, 1)) ((HeroState *)g_hero_state)->armed = 1;
        else ((HeroState *)g_hero_state)->armed = 0;
        ((HeroState *)g_hero_state)->request[slot] = 0;
    }
    if (((HeroState *)g_hero_state)->request[slot] == 0x2D) {
        func_PAL_L00_003C77F0(ITEM_ENTRY(0x2D).fancy != 0);
        ((HeroState *)g_hero_state)->request[slot] = 0;
    }
    if (((HeroState *)g_hero_state)->request[slot]) {
        if (((HeroState *)g_hero_state)->request[slot] != ((HeroState *)g_hero_state)->current[slot]) {
            if (slot == 1 && !((HeroState *)g_hero_state)->previous[slot]) {
                *(s16 *)&D_001A7A00[0x24] = ((HeroState *)g_hero_state)->request[slot];
                if (*(s16 *)&D_001A7A00[0x24] == 0x77) *(s16 *)&D_001A7A00[0x24] = 0;
            }
            if (((HeroState *)g_hero_state)->request[slot] == 0x77) {
                ((HeroState *)g_hero_state)->current[slot] = 0;
                D_001A7398[slot] = 0;
            } else {
                int item;
                if (slot == 0) {
                    int item = D_001A7398[0];
                    if (item != 0x26 && item != 0x33 && item && ((HeroState *)g_hero_state)->request[0] != 0x26 &&
                        ((HeroState *)g_hero_state)->request[0] != 0x33 && ((HeroState *)g_hero_state)->request[0] != item)
                        *(int *)&D_001A7A00[4] = item;
                }
                item = ((HeroState *)g_hero_state)->request[slot];
                ((HeroState *)g_hero_state)->current[slot] = item;
                if (!keepHelmet || item != 4) D_001A7398[slot] = item;
                if (!keepSuit || ((HeroState *)g_hero_state)->current[slot] != 8)
                    D_001A7398[slot] = ((HeroState *)g_hero_state)->current[slot];
                if (slot == 0) ITEM_ENTRY(((HeroState *)g_hero_state)->current[0]).flags = 0x20;
            }
            changed = 1;
        } else {
            ((HeroState *)g_hero_state)->request[slot] = 0;
        }
    }
    if (((HeroState *)g_hero_state)->slots[slot].state == 2) changed = 0;
    if (((HeroState *)g_hero_state)->slots[slot].state == 1 && !((HeroState *)g_hero_state)->slots[slot].pose) ((HeroState *)g_hero_state)->slots[slot].pose = ((HeroState *)g_hero_state)->slots[slot].restPose;
    pose = &((HeroState *)g_hero_state)->slots[0].pose;
    if (!vec_fast_helper_a(pose + slot * sizeof(Slot))) changed = 0;
    if (slot == 0) {
        if (changed) {
            changed = 0;
            ((HeroState *)g_hero_state)->queued = *(int *)(pose + 0x10AB);
        }
        if (((HeroState *)g_hero_state)->queued) {
            sound = ITEM_ENTRY(((HeroState *)g_hero_state)->queued).sound;
            if (!load_is_class_cached(sound)) {
                LoadClassIntoFreeCacheSlot(sound);
            } else {
                changed = 1;
                *(int *)(pose + 0x10AB) = ((HeroState *)g_hero_state)->queued;
                ((HeroState *)g_hero_state)->queued = 0;
            }
        }
    }
    if (changed) {
        ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].anim = 3;
        hero_clear_slot_records();
        ((HeroState *)g_hero_state)->quickTimer = math_random_int_range(0x2a, 0x4B);
        func_PAL_L00_002B1200(((HeroState *)g_hero_state)->current[slot]);
        if (((HeroState *)g_hero_state)->refresh) func_PAL_L00_002AF6C0();
        if (slot == 0) {
            if (((HeroState *)g_hero_state)->current[0] == 10) D_001A7A00[8] = 1;
            else D_001A7A00[8] = 0;
        }
        if (slot == 3) {
            if (((HeroState *)g_hero_state)->slots[3].item == 3) D_001A7A00[9] = 1;
            else D_001A7A00[9] = 0;
        }
        ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].swap = 0;
        ((HeroState *)g_hero_state)->request[slot] = 0;
        ((HeroState *)g_hero_state)->pending = 0;
        cur = ((HeroState *)g_hero_state)->current[slot];
        if (slot == 0 && ITEM_ENTRY(cur).skin != ((HeroState *)g_hero_state)->skin) {
            if (((HeroState *)g_hero_state)->panel[0]) ((HeroState *)g_hero_state)->panel[0]->dirty = 1;
            if (((HeroState *)g_hero_state)->panel[1]) ((HeroState *)g_hero_state)->panel[1]->dirty = 1;
        }
        if (((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby && ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby->cls->rank >= 3)
            func_PAL_002A7E68(((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].moby, 2, 0, 2);
        if (((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].holster && slot != 3 &&
            ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].holster->cls->rank >= 3)
            func_PAL_002A7E68(((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].holster, 2, 0, 2);
        ((HeroState *)(g_hero_state + slot * sizeof(Slot)))->slots[0].mode = 3;
    }
    if (slot == 2 && !D_001A7398[2] && !((HeroState *)g_hero_state)->slots[2].moby)
        ((HeroState *)g_hero_state)->request[2] = 0x2F;
    if (slot == 1 && !D_001A7398[1] && !((HeroState *)g_hero_state)->slots[1].moby)
        ((HeroState *)g_hero_state)->request[1] = 0x34;
}
