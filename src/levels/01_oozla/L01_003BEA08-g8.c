#include "common.h"

/* func_L01_003BEA08: the level's state-machine update for a swimming critter (states 0-11 at
   moby + 0x20, sub-state at + 0x95, pvars at + 0x68), followed by the shared out-of-bounds check.
   Built -G8 in its own unit so the three level scalars are $gp-relative. Values that retail keeps in
   saved registers across the sub-switches (moby + 0x10 in state 8, data + 0x1E0 / + 0x100) are left
   to gcse: written out at each use, its reaching registers reproduce retail's copies. Each state has
   its own locals so the block-local ones go through local-alloc, as in retail. */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

extern char D_00189E20[];
extern s32 D_L01_001AFE44 __attribute__((sda));
extern s32 D_L01_001AFE48 __attribute__((sda));
extern s32 D_L01_001A8F40 __attribute__((sda));
extern u8 *D_L01_001BF918[];

extern s32 func_002D4CE0(void *, s32, u8 *, f32);
extern s32 func_002E30E0(void *);
extern f32 func_002E33E0(f32);
extern void func_002E3470(void *, void *, void *);
extern void func_002E34A0(void *, void *, void *);
extern f32 func_002E3650(void *, void *);
extern void func_002E3738(void *, void *, f32);
extern f32 func_002E3A48(f32);
extern f32 func_002E3A60(f32);
extern f32 func_002E4460(f32, f32);
extern void func_002F2A30(s32);
extern void func_00306250(u8 *);
extern f32 func_00306448(u8 *);
extern void func_00307390(u8 *, s32, void *);
extern void func_0030F920(u8 *, s32, s32);
extern void func_00310138(u8 *, s32, s32, s32);
extern void func_00310418(u8 *, s32, s32);
extern s32 func_003104E8(s32);
extern s32 func_00310528(s32, s32);
extern f32 func_00310580(f32, f32);
extern void func_00311EB8(u8 *, void *, s32, s32, s32, s32, f32, f32, f32);
extern void func_00313BF8(void *, f32, f32, f32, void *, f32);
extern s32 func_003165E8(void *, s32, s32, s32, s32);
extern s32 func_0031D548(u8 *, void *);
extern void func_003258B8(s32);
extern void func_003BD178(u8 *, void *, s32, f32, f32, f32, f32, f32, f32);
extern void func_003BD410(u8 *);
extern void func_003BD6B0(u8 *);
extern void func_003BDB28(u8 *);
extern void func_003BDBB0(u8 *);
extern void func_003BDBE8(u8 *);
extern void func_003BDF28(u8 *);
extern s32 func_003BE058(u8 *, f32, f32, f32, f32, f32, f32, f32, f32);
extern void func_003BE4D0(u8 *);
extern void func_003BE628(u8 *);
extern void func_003E9CF8(u8 *, s32, s32);

/* Updates the Mutant Firefly. It wanders, chases and attacks the player, and is removed when it dies or leaves the level. */
void func_L01_003BEA08(u8 *moby)
{
    f32 vec[4] __attribute__((aligned(16)));
    u8 *vars;
    u8 *pos;
    u8 *position;
    u8 *target;
    f32 targetHeight;
    f32 speed;
    s32 gotHit;
    s32 flags;
    s32 inRange;

    vars = *(u8 **)(moby + 0x68);
    if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x6F) {
        if (*(s16 *)(vars + 0x202) != -1) {
            *(s32 *)(vars + 0x204) = 0;
            func_002F2A30(*(s16 *)(vars + 0x202));
            *(s16 *)(vars + 0x202) = -1;
        }
        if (*(s32 *)(vars + 0x290) != 0) {
            func_003258B8(*(s32 *)(vars + 0x290));
            *(s32 *)(vars + 0x290) = 0;
        }
        moby[0x31] = 0;
        *(u16 *)(moby + 0x34) |= 1;
        return;
    }
    if ((*(u16 *)(moby + 0x34) & 1) && *(s16 *)(vars + 0x202) == -1) {
        *(u16 *)(moby + 0x34) &= 0xFFFE;
        moby[0x31] = 1;
    }
    if (moby[0x20] != 0) {
        func_003BE628(moby);
    }
    switch (moby[0x20]) {
    case 0:
        func_003BD6B0(moby);
        break;
    case 1:
        *(f32 *)(vars + 0x22C) = 0;
        *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x294);
        gotHit = 0;
        if (*(s32 *)(vars + 0x114) == 1) {
            gotHit = 1;
        }
        if (moby[0xBC] != 0) {
            gotHit = 1;
        }
        if (moby[0xBC] & 2) {
            gotHit = 1;
        }
        if (gotHit) {
            moby[0x30] = vars[0x200];
            qzero(vars + 0x1F0);
            *(s32 *)(vars + 0x230) = func_00310528(D_L01_001AFE44, D_L01_001AFE48);
            func_00310418(moby, 3, -1);
        }
        break;
    case 3:
        if (func_002E30E0(vars + 0x230) != 0) {
            if (moby[0x43] != 0) {
                func_00310138(moby, 0, 0, 0xA);
            }
            func_00310418(moby, 2, 0);
        }
        break;
    case 2:
        targetHeight = *(f32 *)(moby + 0x18);
        switch (moby[0x95]) {
        case 0:
            targetHeight = *(f32 *)(vars + 0x228);
            break;
        case 1:
            targetHeight = *(f32 *)(vars + 0x224) - 1.7f;
            break;
        }
        func_00313BF8(moby + 0x18, targetHeight, 0.0069444445f, 0.0041666669f, vars + 0x1F8, 0.5f);
        if (func_00306448(moby) < 12.0f) {
            qcopy(vec, moby + 0x10);
            vec[2] = *(f32 *)(vars + 0x224);
            func_003BD178(moby, vec, 3, 1.0f, 1.5f, 0.5f, 0.0f, 0.1f, 0.8f);
        }
        if (func_002E33E0(*(f32 *)(moby + 0x18) - targetHeight) < 0.2f) {
            switch (moby[0x95]) {
            case 0:
                *(u16 *)(moby + 0x34) |= 0x1000;
                if (moby[0x43] != 3) {
                    func_00310138(moby, 3, 0, 3);
                }
                *(s32 *)(vars + 0x230) = func_00310528(0xB4, 0x168);
                func_00310418(moby, 5, -1);
                break;
            case 1:
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                if (moby[0x43] != 1) {
                    func_00310138(moby, 1, 0, 3);
                }
                *(s32 *)(vars + 0x230) = 0;
                *(f32 *)(vars + 0x22C) = 0;
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x294);
                func_00310418(moby, 1, -1);
                break;
            }
        }
        break;
    case 4:
        pos = moby + 0x10;
        func_002E3470(pos, pos, vars + 0x1F0);
        *(f32 *)(vars + 0x1F8) -= 0.0027222224f;
        *(f32 *)(moby + 0x18) += 0.3f;
        if (func_002D4CE0(pos, 0, moby, 0.3f) != 0 &&
            (D_L01_001BF918[0] == 0 || *(s16 *)(D_L01_001BF918[0] + 0xAA) != 0x945 /* moby class 2373 */)) {
            if (moby[0x43] != 3) {
                func_00310138(moby, 3, 0, 3);
            }
            *(s32 *)(vars + 0x230) = func_00310528(0xB4, 0x168);
            func_00310418(moby, 5, -1);
        }
        if (*(f32 *)(vars + 0x1F8) < 0.0f || *(s32 *)(vars + 0x234) >= 0xF1) {
            if (moby[0x43] != 3) {
                func_00310138(moby, 3, 0, 3);
            }
            *(s32 *)(vars + 0x230) = func_00310528(0xB4, 0x168);
            func_00310418(moby, 5, -1);
        }
        *(f32 *)(moby + 0x18) -= 0.3f;
        *(f32 *)(vars + 0x1F8) -= 0.0027222224f;
        if (*(f32 *)(moby + 0x18) < *(f32 *)(vars + 0x224)) {
            *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0x224);
        }
        break;
    case 5:
        if (func_002E30E0(vars + 0x258) != 0) {
            *(f32 *)(vars + 0x260) = func_00310580(10.0f, 180.0f) * 0.00029088825f;
            *(s32 *)(vars + 0x258) = func_00310528(0x1E, 0xB4);
        }
        if (func_002E30E0(vars + 0x25C) != 0) {
            *(f32 *)(vars + 0x264) = func_00310580(60.0f, 170.0f) * 0.00029088825f;
            *(s32 *)(vars + 0x25C) = func_00310528(0x3C, 0xC8);
        }
        if (func_002E30E0(vars + 0x278) != 0) {
            *(f32 *)(vars + 0x268) = func_00310580(30.0f, 160.0f) * 0.00029088825f;
            *(s32 *)(vars + 0x278) = func_00310528(0x2D, 0x5A);
        }
        *(f32 *)(vars + 0x26C) = func_002E4460(*(f32 *)(vars + 0x26C), *(f32 *)(vars + 0x260));
        *(f32 *)(vars + 0x270) = func_002E4460(*(f32 *)(vars + 0x270), *(f32 *)(vars + 0x264) * func_002E3A60(*(f32 *)(vars + 0x26C)));
        *(f32 *)(vars + 0x274) = func_002E4460(*(f32 *)(vars + 0x274),
            *(f32 *)(vars + 0x268) * func_002E4460(func_002E3A48(*(f32 *)(vars + 0x26C)), func_002E3A60(*(f32 *)(vars + 0x270))));
        *(f32 *)(vars + 0x1E0) = func_002E3A48(func_002E4460(*(f32 *)(moby + 0xF8), func_002E3A60(*(f32 *)(vars + 0x270)) * 0.16289742f));
        *(f32 *)(vars + 0x1E4) = func_002E3A60(func_002E4460(*(f32 *)(moby + 0xF8), func_002E3A60(*(f32 *)(vars + 0x270)) * 0.16289742f));
        *(f32 *)(vars + 0x1E8) = 0.0f;
        func_002E3470(vars + 0x1E0, vars + 0x1E0, moby + 0x10);
        func_003BDBE8(moby);
        func_003BE058(moby, 360.0f, 180.0f, 560.0f, 20.0f, 0.0f, 16.0f,
                      *(f32 *)(vars + 0x24C) + func_002E3A60(*(f32 *)(vars + 0x274)) * 2.0f, -2.0f);
        if (*(s32 *)(vars + 0x230) == 0) {
            if (moby[0x43] != 1) {
                func_00310138(moby, 1, 0, 3);
            }
            *(f32 *)(vars + 0x22C) = 0.0f;
            func_00310418(moby, 6, 0);
        }
        break;
    case 6:
        switch (moby[0x95]) {
        case 0:
            if (*(s32 *)(vars + 0x230) == 0) {
                *(s32 *)(vars + 0x230) = func_00310528(0x1E, 0x5A);
                if (*(s32 *)(vars + 0x230) >= 7 && moby[0x43] != 3) {
                    func_00310138(moby, 3, 0, 3);
                }
                *(f32 *)(vars + 0x22C) = 0;
                func_00310418(moby, 6, 1);
            }
            break;
        case 1:
            func_003BE058(moby, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f, *(f32 *)(vars + 0x24C) + 1.7f, 1.0f);
            if (*(s32 *)(vars + 0x230) == 0) {
                func_003BDF28(moby);
                *(s32 *)(vars + 0x230) = func_00310528(0, 0);
                if (*(s32 *)(vars + 0x230) >= 7 && moby[0x43] != 1) {
                    func_00310138(moby, 1, 0, 3);
                }
                *(f32 *)(vars + 0x22C) = 0;
                func_00310418(moby, 6, 0);
            }
            break;
        case 2:
            qcopy(vars + 0x1E0, vars + 0x1D0);
            if (func_003BE058(moby, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f, *(f32 *)(vars + 0x24C) + 1.7f, 1.0f) & 8) {
                if (moby[0x43] != 2) {
                    func_00310138(moby, 2, 0, 0xA);
                }
                func_00310418(moby, 2, 1);
            }
            break;
        }
        *(f32 *)(vars + 0x22C) = 0;
        if (*(s32 *)(vars + 0x114) == 1 || *(s32 *)(vars + 0x238) != 0) {
            if (func_003104E8(9) == 0) {
                *(s32 *)(vars + 0x238) = func_00310528(0x12C, 0x168);
                *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 7, 0);
            }
        } else if (moby[0x20] == 6 && *(s32 *)(vars + 0x208) == 0) {
            *(f32 *)(vars + 0x22C) = 0;
            func_00310418(moby, 6, 2);
        }
        break;
    case 7:
        switch (moby[0x95]) {
        case 0:
            if (*(s32 *)(vars + 0x230) == 0) {
                *(s32 *)(vars + 0x230) = func_00310528(0x1E, 0x5A);
                if (*(s32 *)(vars + 0x230) >= 7 && moby[0x43] != 3) {
                    func_00310138(moby, 3, 0, 3);
                }
                *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 7, 1);
            }
            break;
        case 1:
            if (func_003BE058(moby, 250.0f, 180.0f, 250.0f, 32.0f, 0.1f, 13.0f, *(f32 *)(vars + 0x24C) + 1.7f, 1.0f) & 8) {
                *(s32 *)(vars + 0x230) = 0;
            }
            if (*(s32 *)(vars + 0x230) == 0) {
                func_003BDF28(moby);
                *(s32 *)(vars + 0x230) = func_00310528(0, 0);
                if (*(s32 *)(vars + 0x230) >= 7 && moby[0x43] != 1) {
                    func_00310138(moby, 1, 0, 3);
                }
                *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 7, 0);
            }
            break;
        }
        *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
        *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
        if (*(s32 *)(vars + 0x114) == 0 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x31 ||
            ((Hero *)gHeroState)->i[0x229C / 4] == 0x11 || ((Hero *)gHeroState)->i[0x229C / 4] == 0x12 ||
            D_L01_001A8F40 == 2 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x6F) {
            *(s32 *)(vars + 0x114) = 0;
            if (*(s32 *)(vars + 0x238) == 0) {
                *(f32 *)(vars + 0x22C) = 0;
                func_00310418(moby, 6, 0);
            }
        } else if (**(s32 **)(vars + 0x250) < 3 && *(s32 *)(vars + 0x23C) == 0) {
            position = moby + 0x10;
            target = vars + 0x100;
            if (func_002E3650(position, target) < 12.0f &&
                func_003165E8(position, *(s32 *)(vars + 0x210), *(s32 *)(vars + 0x218), *(s32 *)(vars + 0x21C), -1) != 0) {
                *(s32 *)(vars + 0x254) = 1;
                qcopy(vars + 0x1E0, target);
                *(f32 *)(vars + 0x22C) = 0;
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 8, 0);
                **(s32 **)(vars + 0x250) += 1;
            }
        }
        break;
    case 8:
        qcopy(vars + 0x1E0, vars + 0x100);
        switch (moby[0x95]) {
        case 0:
            func_003BE058(moby, 260.0f, 180.0f, 270.0f, 32.0f, 0.2f, 3.5f, 0.4f, 0.5f);
            if (func_002E3650(moby + 0x10, vars + 0x100) < 1.0f &&
                func_002E33E0(*(f32 *)(moby + 0x18) - *(f32 *)(*(u8 **)(vars + 0x110) + 0x18)) < 1.3f) {
                if (moby[0x43] != 4) {
                    func_00310138(moby, 4, 0, 0xA);
                }
                *(f32 *)(vars + 0x22C) = 0;
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 8, 1);
            }
            break;
        case 1:
            func_003BE058(moby, 260.0f, 180.0f, 270.0f, 32.0f, 0.2f, 3.5f, 0.4f, 0.5f);
            *(f32 *)(vars + 0x22C) = 0;
            *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
            func_00310418(moby, 8, 2);
            break;
        case 2:
            speed = 0.4f;
            func_003BE058(moby, 260.0f, 180.0f, 270.0f, 32.0f, 0.2f, 3.5f, speed, 0.5f);
            if (moby[0x42] == 4) {
                if (func_00306448(moby) > 19.5f && func_00306448(moby) < 29.0f) {
                    func_00307390(moby, 1, vec);
                    func_00311EB8(moby, vec, 0x4000001, 0, 1, 0, speed, vars[0x34], 1.0f);
                }
                if (moby[0x60] & 2) {
                    *(s32 *)(vars + 0x230) = 0x78;
                    *(s32 *)(vars + 0x23C) = func_00310528(0xB4, 0x104);
                    if (moby[0x43] != 1) {
                        func_00310138(moby, 1, 0, 3);
                    }
                    *(f32 *)(vars + 0x22C) = 0;
                    *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                    func_00310418(moby, 8, 3);
                }
            }
            break;
        case 3:
            if (func_002E30E0(vars + 0x230) != 0) {
                if (func_002E3650(moby + 0x10, vars + 0x100) < 1.0f &&
                    func_002E33E0(*(f32 *)(moby + 0x18) - *(f32 *)(*(u8 **)(vars + 0x110) + 0x18)) < 1.3f) {
                    if (moby[0x43] != 4) {
                        func_00310138(moby, 4, 0, 3);
                    }
                    *(f32 *)(vars + 0x22C) = 0;
                    *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                    func_00310418(moby, 8, 1);
                } else {
                    qcopy(vars + 0x1E0, vars + 0x100);
                    *(f32 *)(vars + 0x22C) = 0;
                    *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                    func_00310418(moby, 8, 0);
                }
            }
            break;
        }
        *(f32 *)(vars + 0x22C) = 0;
        *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
        inRange = func_003165E8(moby + 0x10, *(s32 *)(vars + 0x210), *(s32 *)(vars + 0x218), *(s32 *)(vars + 0x21C), -1) != 0;
        if (*(s32 *)(vars + 0x114) == 0 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x31 ||
            ((Hero *)gHeroState)->i[0x229C / 4] == 0x11 || ((Hero *)gHeroState)->i[0x229C / 4] == 0x12 ||
            !inRange || D_L01_001A8F40 == 2 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x6F) {
            if (*(s32 *)(vars + 0x238) != 0) {
                func_003BDBB0(moby);
                *(s32 *)(vars + 0x230) = 0;
                if (moby[0x43] != 3) {
                    func_00310138(moby, 3, 0, 3);
                }
                *(f32 *)(vars + 0x22C) = 0;
                func_00310418(moby, 6, 1);
            } else {
                func_003BDBB0(moby);
                func_002E34A0(vars + 0x1E0, moby + 0x10, vars + 0x1E0);
                func_002E3470(vars + 0x1E0, vars + 0x1E0, moby + 0x10);
                func_002E3738(vars + 0x1E0, vars + 0x1E0, 5.0f);
                func_003BDBE8(moby);
                *(f32 *)(vars + 0x244) *= 3.0f;
                if (inRange) {
                    func_003BE058(moby, 260.0f, 180.0f, 270.0f, 32.0f, 0.2f, 3.5f, 0.3f, 0.5f);
                } else {
                    func_003BE058(moby, 780.0f, 180.0f, 810.0f, 32.0f, 0.2f, 3.5f, 0.3f, 0.5f);
                }
                *(s32 *)(vars + 0x230) = 0;
                if (moby[0x43] != 3) {
                    func_00310138(moby, 3, 0, 3);
                }
                *(s32 *)(vars + 0x23C) = func_00310528(0xB4, 0x104);
                *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
                *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
                func_00310418(moby, 7, 1);
            }
        }
        break;
    case 9:
        *(s32 *)(vars + 0x220) += 1;
        flags = func_0031D548(moby, vars + 0x50);
        if (flags & 1) {
            func_00310418(moby, 0xB, -1);
        } else if ((flags & 2) || *(s32 *)(vars + 0x220) >= 0x169) {
            vars[0x6A] = 2;
            if (moby[0x43] != 1) {
                func_00310138(moby, 1, 0, 3);
            }
            *(s32 *)(vars + 0x220) = 0;
            qzero(vars + 0x1F0);
            *(f32 *)(vars + 0x22C) = *(f32 *)(vars + 0x20C);
            *(s32 *)(vars + 0x29C) = *(s32 *)(vars + 0x298);
            func_00310418(moby, 7, 0);
        }
        break;
    case 11:
        func_003BDB28(moby);
        if (*(s16 *)(vars + 0x202) != -1) {
            *(s32 *)(vars + 0x204) = 0;
            func_002F2A30(*(s16 *)(vars + 0x202));
            *(s16 *)(vars + 0x202) = -1;
        }
        *(s16 *)(vars + 0x188) = 0;
        func_003BD410(moby);
        func_003BDBB0(moby);
        vars[0x54] = 0x40;
        vars[0x55] = 0x40;
        vars[0x56] = 0x40;
        func_003E9CF8(moby, 0, 0);
        func_0030F920(moby, 0, 3);
        func_00306250(moby);
        return;
    }
    func_003BE4D0(moby);
    if (*(f32 *)(moby + 0x10) < 30.0f || *(f32 *)(moby + 0x10) > 993.0f ||
        *(f32 *)(moby + 0x14) < 30.0f || *(f32 *)(moby + 0x14) > 993.0f ||
        *(f32 *)(moby + 0x18) < 30.0f || *(f32 *)(moby + 0x18) > 993.0f) {
        func_00306250(moby);
    }
}
