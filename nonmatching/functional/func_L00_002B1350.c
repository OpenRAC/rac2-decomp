/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Claude Opus 5.5 xhigh, task v1831, 31 October 2026: NOT MATCHING.
 * Default game profile: -O2 -G0 -ffunction-sections; USA v1.01. Keep it in its own unit:
 * the types below clash with L00_002AFBC0.c (D_00189E20 has another type there).
 * check.py: 3124 bytes versus retail 3136, 0 of 27 places match. Aligned against
 * retail, 9 rows differ (v1536's draft: 63), all of them delay-slot choices; every
 * other instruction, register and order agrees.
 * Still differs (retail offsets):
 *   +0x1D8 bnez $v0 has an empty slot; here it takes addiu $v1,$s5,%lo.
 *   +0x298 slot is addiu $v1,$zero,3; here addiu $a0,$a1,%lo.
 *   +0x2C8, +0x2E4 are bnel; here bnez, same slot insn.
 *   +0x2F0 beqz $s0 slot is addiu $v0,$zero,1; here addiu $a1,$s5,%lo.
 *   +0x358 is beql with lbu $v0,0x1497($a0); here beqz with addiu $a1,$zero,0x14.
 * What fixed the rest, each confirmed by compiling:
 *   D_001A7398 and D_001A7A80 are sda at every use: `la` is one length-2 insn, so it
 *   stays adjacent and never fills a slot (this explains the +0x7F0 nop).
 *   The +0x388 beql comes from written-out if/else stores with slot * sizeof(Slot);
 *   a ternary or if (!x) x = 0x77 gives movz/movn. Inferred mechanism: reorg steals
 *   li into an annulled slot, then deletes the `b` around the identical store.
 *   Restore path: taking int *tbl = D_001A7398 before the 0x77 test makes `la` born
 *   first; local-alloc's three-quantity sort is order sensitive, and this gives
 *   retail's la v0, xori v1. Store order: current, then tbl[slot].
 *   Helmet path: previous, keepHelmet, request. Skin check: read current[slot] into a
 *   local before testing slot == 0, so the load lands in the bnez slot.
 * Next (inference from reading reorg.c/resource.c from memory, not proven): the live
 * scan kills $v1 and $a1 on every path from +0x1EC and +0x394 within the jump limit,
 * so only a CODE_LABEL after the branch (own_fallthrough false) seems to explain
 * +0x1D8 and +0x358. No branch targets those places in retail, and what made such a
 * label is unknown. The other three rows may follow from the same cause.
 * Tied, do not repeat: -g, -frac2-keep-block-order, -frac2-gcse-unsplit-edges, the
 * last two together, and all three (each tried at the 19-row stage, before tbl);
 * call || pending as a local, as an empty then-arm, and with gotos. Written as two
 * arms with a duplicated body it is worse (3156 bytes).
 * No volatile accesses added. PAL/us2 and linking were not run: US fails.
 * Required declarations follow.
 */
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
extern int func_L00_0032EF10(int, int, int *);
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
            func_L00_003C3A70(ITEM_ENTRY(0x2D).fancy != 0);
            ((HeroState *)D_00189E20)->request[slot] = 0;
        }
    }
    changed = 0;
    if (((HeroState *)D_00189E20)->blocked && slot == 0 &&
        (!((HeroState *)D_00189E20)->pending || ((HeroState *)D_00189E20)->slots[slot].item == 10)) {
        ((HeroState *)D_00189E20)->pending = 0;
        return;
    }
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
        func_L00_003C3A70(ITEM_ENTRY(0x2D).fancy != 0);
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
        ((HeroState *)D_00189E20)->quickTimer = func_002A7820(0x32, 0x5A);
        func_L00_002B1308(((HeroState *)D_00189E20)->current[slot]);
        if (((HeroState *)D_00189E20)->refresh) func_L00_002AF7D0();
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
            func_002A7470(((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].moby, 2, 0, 2);
        if (((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster && slot != 3 &&
            ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster->cls->rank >= 3)
            func_002A7470(((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].holster, 2, 0, 2);
        ((HeroState *)(D_00189E20 + slot * sizeof(Slot)))->slots[0].mode = 3;
    }
    if (slot == 2 && !D_001A7398[2] && !((HeroState *)D_00189E20)->slots[2].moby)
        ((HeroState *)D_00189E20)->request[2] = 0x2F;
    if (slot == 1 && !D_001A7398[1] && !((HeroState *)D_00189E20)->slots[1].moby)
        ((HeroState *)D_00189E20)->request[1] = 0x34;
}
