#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad[0x80];
    s32 cost;
    u8 tail[0x5C];
} VendorItem;
typedef struct {
    u8 pad[0xE0];
    f32 position[4];
} HeroView;
typedef struct PurchaseMoby {
    u8 pad00[0x10];
    f32 position[4];
    u8 state, group;
    u8 pad22[0xE];
    u8 field30, enabled;
    u16 field32, flags;
    u8 pad36[0xD];
    u8 animation;
    u8 pad44[0x1C];
    u8 animFlags;
    u8 pad61[7];
    u8 *data;
    u8 pad6C[0x8C];
    f32 yaw;
} PurchaseMoby;
extern u8 D_001A7B26[] MACRO_ADDR;
extern u8 D_001A7A40[] MACRO_ADDR;
extern s32 D_001A79F8[] MACRO_ADDR;
extern u8 D_0013978C;
extern u8 D_00139568[];
extern s32 D_00138324;
extern u8 D_00189EA0[], D_00189F00[];
extern u8 D_L01_002637A0[];
extern u8 D_L01_001BF6C0[];
extern u8 *D_L01_001B264C[] MACRO_ADDR;
extern s32 D_L01_001A8F40 MACRO_ADDR;
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;
extern void func_L01_003209F8(void *, s32, s32, f32);
extern void func_002A7750(void *, s32, s32);
extern void func_L01_003128C0(void *);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(void *);
extern void func_002AB650(void *);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(void *, s32);
extern void func_L01_003246D0(void *);
extern void func_00288BE8(void *);
extern s32 func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern s32 func_L01_003245E0(void *, s32, f32);
extern void func_L00_0030C710(s32);
extern void func_L01_00324550(s32, s32, s32);
extern void func_002A8598(s32, s32);
extern void func_00288308(s32);
extern void func_002AD860(s32);
extern void func_US2_002B1880(s32, s32);
extern void func_US2_00289840(s32, s32);
extern void func_L00_00429020(s32);
extern void func_0029B3E0(s32, s32);
extern void func_0029F338(void *);
extern s32 func_00282978(void *);
extern f32 func_002A7878(f32, f32);
extern s32 func_00283CF0(f32);
extern void func_002A7470(void *, s32, s32, s32);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00282DF0(void *);
extern s32 func_00282948(void *);
extern f32 func_00283B98(f32, f32);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00282E20(void *);
extern void func_002AEC48(void *, void *, s32, f32, f32);
extern void func_002AF1D0(void *, void *, s32, s32);
#define ITEM_COST ((VendorItem *)(D_L01_002637A0 + D_00139568[0x2E] * sizeof(VendorItem)))->cost
#define STATE_CHILD (*(u8 **)(state + 0x128))
/* Inlined, so its 0.3f is a constant loaded at each call rather than a pseudo shared across
   the first call. */
static __inline__ void TurnJoint(void *moby, void *joint, s32 index, f32 rate)
{
    func_002AEC48(moby, joint, index, rate, 0.3f);
}

/* An item vendor: offers the current item table entry, compares its cost with D_001A79F8, takes
   the cost on purchase and removes itself. */
void func_US2_L01_003D42B0(PurchaseMoby *moby)
{
    u8 target[16] __attribute__((aligned(16)));
    u8 origin[16] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    u8 *state = moby->data;
    u8 *child, *record;
    f32 turnRate, angle, yaw, pitch;
    s32 active;
    u64 flag;

    func_L01_003209F8(moby, 0, 0xB1A, 2.5f);
    switch (moby->state) {
    case 0:
        if (D_001A7B26[0])
            goto remove_self;
        flag = D_0013978C;
        if (flag >> 7) {
            if (D_001A79F8[0] < ITEM_COST)
                func_002A7750(moby, 3, -1);
            else
                func_002A7750(moby, 4, -1);
        } else {
            func_002A7750(moby, 1, -1);
        }
        func_L01_003128C0(moby);
        child = func_0029EFD0(0xD7E);
        STATE_CHILD = child;
        if (child) {
            child[0x30] = moby->field30;
            *(u16 *)(STATE_CHILD + 0x32) = moby->field32;
            STATE_CHILD[0x31] = 1;
            func_002A0F48(STATE_CHILD);
            func_002AB650(STATE_CHILD);
        }
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 0x120)) && func_00288AA0(D_L01_001BF6C0, 0x27)) {
            func_L01_003246D0(moby);
            func_00288BE8(D_L01_001BF6C0);
            func_002A7750(moby, 2, -1);
        }
        break;
    case 2:
        D_L01_001B22A0.busy = 1;
        if (D_L01_001A8F40 == 2) {
            moby->enabled = 0;
            moby->flags |= 1;
            if (D_L01_001A8F40 == 2) {
                *(u16 *)(STATE_CHILD + 0x34) |= 1;
                STATE_CHILD[0x31] = 0;
            }
        }
        if (!func_002F5D10()) {
            D_L01_001B22A0.busy = 0;
            record = D_L01_001B264C[0] + (*(s32 *)(state + 0x120) << 7);
            func_L00_002B9D60(record + 0x30, record + 0x70, 0, 1);
            moby->enabled = 1;
            moby->flags &= 0xFFFE;
            *(u16 *)(STATE_CHILD + 0x34) &= 0xFFFE;
            STATE_CHILD[0x31] = 1;
            if (D_001A79F8[0] < ITEM_COST)
                func_002A7750(moby, 3, -1);
            else
                func_002A7750(moby, 4, -1);
        }
        break;
    case 3:
        if (ITEM_COST < D_001A79F8[0]) {
            func_002A7750(moby, 4, -1);
        } else if (func_L01_003245E0(moby, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x1300, ITEM_COST, -1);
            func_L01_003246D0(moby);
        }
        break;
    case 4:
        if (D_001A79F8[0] < ITEM_COST) {
            func_L00_0030C710(180);
            func_002A7750(moby, 3, -1);
        } else if (func_L01_003245E0(moby, 10, 2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x12FE, ITEM_COST, -1);
            func_L01_003246D0(moby);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L01_001BF6C0, 40)) {
                func_00288BE8(D_L01_001BF6C0);
                func_002A7750(moby, 5, -1);
            }
        }
        break;
    case 5:
        D_L01_001B22A0.busy = 1;
        if (D_L01_001A8F40 == 2) {
            moby->enabled = 0;
            moby->flags |= 1;
            if (D_L01_001A8F40 == 2) {
                *(u16 *)(STATE_CHILD + 0x34) |= 1;
                STATE_CHILD[0x31] = 0;
            }
        }
        if (!func_002F5D10()) {
            D_L01_001B22A0.busy = 0;
            moby->enabled = 1;
            moby->flags &= 0xFFFE;
            *(u16 *)(STATE_CHILD + 0x34) &= 0xFFFE;
            STATE_CHILD[0x31] = 1;
            func_002A8598(moby->group, 1);
            if (!D_001A7B26[0]) {
                D_001A79F8[0] = D_001A79F8[0] - ITEM_COST;
                func_L00_0030C710(180);
                func_00288308(46);
                func_002AD860(46);
                func_US2_002B1880(0x1226, -1);
                func_US2_00289840(0x9BC, 19);
                if (*(s32 *)(state + 0x12C) != -1)
                    func_L00_00429020(*(s32 *)(state + 0x12C));
                func_0029B3E0(0, -1);
                if (STATE_CHILD) {
                    func_0029F338(STATE_CHILD);
                    STATE_CHILD = 0;
                }
remove_self:
                func_0029F338(moby);
                return;
            }
        }
        break;
    }
    if (moby->state) {
        if (!moby->animation && func_00282978(state + 0x11E)) {
            *(u16 *)(state + 0x11E) = func_00283CF0(func_002A7878(1200.0f, 2400.0f));
        } else if ((moby->animFlags & 2) && moby->animation) {
            func_002A7470(moby, 0, 0, 10);
        }
    }
    turnRate = 0.02f;
    active = 0;
    if (!moby->animation) {
        active = 1;
        if (func_00282E80(moby->position, D_00189EA0) < 8.0f &&
            func_00283C80(moby->yaw, func_00283248(((HeroView *)(D_00189EA0 - 0x80))->position[0] - moby->position[0],
                                                   ((HeroView *)(D_00189EA0 - 0x80))->position[1] - moby->position[1])) < 1.5707965f) {
            if (0.01f < func_00282DF0(D_00189EA0 + 0x90))
                *(s32 *)(state + 0x114) = 120;
            else
                func_00282948(state + 0x114);
        } else if (*(s32 *)(state + 0x114)) {
            *(s32 *)(state + 0x114) = 0;
            qcopy(state + 0x100, D_00189F00);
        }
        if (func_00282948(state + 0x118)) {
            *(s32 *)(state + 0x118) = func_00283CF0(func_002A7878(180.0f, 300.0f));
            angle = func_00283B98(moby->yaw, func_002A7878(-90.0f, 90.0f) * 0.017453294f);
            func_002AF000(state + 0x100, 6.0f, angle, func_002A7878(0.0f, 30.0f) * 0.017453294f);
            func_00282CC0(state + 0x100, state + 0x100, moby->position);
        }
        if (*(s32 *)(state + 0x114)) {
            qcopy(target, D_00189F00);
            turnRate = 0.04f;
        } else {
            qcopy(target, state + 0x100);
        }
    }
    if (active) {
        qcopy(origin, moby->position);
        ((f32 *)origin)[2] += 2.0f;
        func_00282CF0(delta, target, origin);
        yaw = func_00283BE0(func_00283248(delta[0], delta[1]), moby->yaw);
        pitch = -func_00283248(func_00282E20(delta), delta[2]);
        if (1.5707965f < yaw)
            yaw = 1.5707965f;
        else if (yaw < -1.5707965f)
            yaw = -1.5707965f;
        if (0.17453295f < pitch)
            pitch = 0.17453295f;
        else if (pitch < -0.17453295f)
            pitch = -0.17453295f;
        *(f32 *)(state + 0x64) = pitch;
        *(f32 *)(state + 0x68) = yaw * 0.6f;
        *(f32 *)(state + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40[0])
        *(f32 *)(state + 0x70) = 2.75f;
    TurnJoint(moby, state, 0, turnRate);
    TurnJoint(moby, state + 0x80, 1, turnRate);
    if (STATE_CHILD)
        func_002AF1D0(moby, STATE_CHILD, 2, 0);
}
