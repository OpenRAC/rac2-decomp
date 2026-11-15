/* Contact response (the level-20 copy of func_L11_002CB130's routine): pushes the hero along the contact direction. */
#include "common.h"


typedef int TI16 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x80];
    TI16 f80;
    u8 pad90[0xF0 - 0x90];
    TI16 fF0;
    u8 pad100[0x10];
    TI16 f110;
    u8 pad120[0x1DC - 0x120];
    s16 f1DC;
    u8 pad1DE[0x21C - 0x1DE];
    s16 f21C;
    u8 pad21E[0x68E - 0x21E];
    s16 f68E;
    u8 pad690[0x6C4 - 0x690];
    void *f6C4;
    u8 pad6C8[0x1497 - 0x6C8];
    u8 f1497;
    u8 pad1498[0x1500 - 0x1498];
    s32 f1500;
    u8 pad1504[0x1874 - 0x1504];
    s32 f1874;
    u8 pad1878[0x2290 - 0x1878];
    u8 *f2290;
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 f22B4;
    u8 pad22B5[0x249C - 0x22B5];
    u8 *f249C;
    u8 pad24A0[0x24CC - 0x24A0];
    s32 f24CC;
} Player_002C5D00;

typedef struct {
    u8 pad0[0x10];
    float f10;
    float f14;
    float f18;
    float f1C;
    u8 *f20;
    s32 f24;
    u8 f28;
    u8 pad29[3];
    float f2C;
    s32 f30;
    u8 pad34[4];
    u8 *f38;
    u8 pad3C[4];
} Entry_002C5D00;

extern Player_002C5D00 D_00189E20;
extern Entry_002C5D00 D_L20_001C4680[];
extern s32 D_L20_001A8F00 __attribute__((sda));
extern s32 D_L20_001AFF00 __attribute__((sda));
extern u8 D_001A7A32 __attribute__((sda));
extern u8 D_001A7A33 __attribute__((sda));

extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern s32 func_00283CF0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_L00_002D36E0(void *, s32, float, float, float);
extern void func_L20_002D7730(s32, s32);
extern u8 *func_002A9640(u8 *, s32, s32);
extern void func_L00_002A4EF8(s32);
extern void func_L00_002B9B88(s32, s32);
extern void func_L00_002B2C58(void *, s32, float, float);
extern void func_L00_002D3C68(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Handles the hero touching a hurting object and, when asked, pushes the hero away and plays the hurt animation. Returns 1 if the hero was hit. */
s32 func_L20_002C5D00(s32 applyPush) {
    TI16 vec;
    Entry_002C5D00 *e;
    u8 *moby;
    u8 *other;
    s32 flag;
    s32 bits;

    if (gHeroState.f229C == 20 || gHeroState.f229C == 7) {
        return 0;
    }
    if (gHeroState.f2294 == 0x31) {
        return 0;
    }
    if (gHeroState.f1DC != 0) {
        return 0;
    }
    if (D_L20_001A8F00 != 0) {
        return 0;
    }
    gHeroState.f249C = 0;
    moby = gHeroState.f2290;
    if (moby[0xA8] == 0xFF) {
        return 0;
    }
    e = &D_L20_001C4680[moby[0xA8]];
    if (e->f38 != moby) {
        return 0;
    }
    if (gHeroState.f22B4 == 4) {
        if (D_L20_001AFF00 != 0 || gHeroState.f2294 == 0x6F) {
            return 0;
        }
    } else if ((e->f24 & 9) == 0) {
        return 0;
    }
    if (e->f2C != 0.0f) {
        D_001A7A33 = 0;
        gBoltMultiplier = 1;
    }
    if (GetFadeValue() != 0.0f && gHeroState.f22B4 == 0) {
        e->f2C = ReduceFadeValue(e->f2C);
        if (e->f2C == 0.0f) {
            return 0;
        }
    }
    gHeroState.f249C = e->f20;
    if (gHeroState.f229C == 15) {
        gHeroState.f6C4 = e;
        gHeroState.f68E = 1;
        return 0;
    }
    if (gHeroState.f22B4 == 4 && D_L20_001AFF00 == 0 && gHeroState.f2294 != 0x6F) {
        u8 *m = *(u8 **)(gHeroState.f2290 + 0x68);
        *(s16 *)(m + 0x3BC) -= 0xB4;
        if (*(s16 *)(m + 0x3BC) < 0) {
            *(s16 *)(m + 0x3BC) = 0;
        }
    }
    if (applyPush == 0) {
        return 1;
    }
    flag = 0;
    ClearTrackedSlots();
    if (e->f30 & 1) {
        qcopy(&vec, &e->f10);
        if (e->f1C == 5627.9248046875f) {
            flag = 1;
        }
    } else if (e->f20 != 0) {
        FastVecSub(&vec, &gHeroState.f80, e->f20 + 0x10);
    } else {
        BuildHeroRelativePoint(&vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (gHeroState.f22B4) {
    case 0:
        other = gHeroState.f249C;
        if (other != 0 && (*(s16 *)(other + 0xAA) == 0x4EB /* moby class 1259 */ || *(s16 *)(other + 0xAA) == 0x558 /* moby class 1368 */)) {
            YeedilEnterHeroAction(0x7D, 1);
            return 1;
        }
        if ((gHeroState.f2294 == 1 || gHeroState.f2294 == 0x1D || gHeroState.f1500 != 0)
            && !(e->f24 & 8)) {
            u8 *r = FindOwnedEffectSlot(gHeroState.f2290, 1, 0);

            if (r != 0) {
                AdjustPlayerHealth(FloatToInt(*(float *)(r + 0x2C)));
            }
            if (gHeroState.f24CC == 0) {
                YeedilEnterHeroAction(0x16, 1);
            }
            gHeroState.f1DC = 0x4D;
            if (gHeroState.f21C == 0) {
                gHeroState.f21C = 0x12;
            }
            PlayHeroSound(0x14, 0);
            return 0;
        }
        if (gHeroState.f229C == 0x12) {
            YeedilEnterHeroAction(0x72, 1);
        } else if (gHeroState.f229C == 0x11) {
            YeedilEnterHeroAction(0x73, 1);
        } else if (e->f24 & 8) {
            YeedilEnterHeroAction(0x8C, 1);
        } else {
            YeedilEnterHeroAction(0x16, 1);
        }
        if (gHeroState.f2294 == 0x8C) {
            qzero(&vec);
        } else {
            FlattenPushVectorAndSetStrength(&vec, flag, gHeroState.f1497 ? 0.0f : 0.055000003f, 0.028333336f);
            if (flag != 0 && e->f28 == 4) {
                ScaleViewSpaceHeight(&vec, &vec, 2.0f);
            }
        }
        break;
    case 1:
        YeedilEnterHeroAction(0x42, 1);
        FlattenPushVectorAndSetStrength(&vec, flag, 0.083333336f, 0.050000004f);
        break;
    case 4:
        YeedilEnterHeroAction(0x90, 1);
        FlattenPushVectorAndSetStrength(&vec, flag, 0.083333336f, 0.050000004f);
        break;
    }
    FastVecAdd(&gHeroState.fF0, &gHeroState.fF0, &vec);
    FastVecAdd(&gHeroState.f110, &gHeroState.f110, &vec);
    return 1;
}
