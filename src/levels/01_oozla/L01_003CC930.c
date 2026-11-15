#include "names.h"
/* func_L01_003CC930 (4,624 bytes, 1 place). -O2 -G16 -Wa,-G16 -ffunction-sections
 * -frac2-hazard-labels.
 * - Plain (not sda) scalars for D_L01_001B255C / 001B2088 / 001A8F40 / 001B264C /
 *   001A79F0 (lui/lw in flow, $gp in delay slots); sda scalars for the 0x13A0..0x13DC
 *   $gp block; D_L01_001B03D8 is a 16-byte sda table (D_L01_001B03E8 follows it), which
 *   needs -G16.
 * - func_00355828, func_00337A60 and func_00355780 return values: v0 stays taken after
 *   the calls, so the constants stored after them are built in v1, as retail.
 * - One local per case and per loop; the mode-7 clamp as an if; qzero_nc for the
 *   pv+0xA0 clear (cse forgets its 0.0f there, so the later <= 0 test builds its own).
 * - Every local is initialised where it is declared and call results are named
 *   locals. The dead initialisers are deleted by flow but counted by gcse: 1,173
 *   insns give a 587-bucket expression table and retail's spill-slot order for the PRE
 *   addresses &v30/&v40/&v50/&v80/pv+0xDE (bucket of (plus (reg 1) N) is
 *   (14030 + N) % buckets). 1,172-1,175 insns all match.
 */
#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } Hero;

extern char g_hero_state[];
extern s32 D_L01_001B2088;
extern u8 *g_moby_l01_table;
extern u8 *D_L01_001B264C;
extern s32 D_L01_001A8F40;
extern s32 g_current_map_index;
extern f32 D_L01_001B0390 __attribute__((sda));
extern s32 D_L01_001B0398 __attribute__((sda));
extern s32 D_L01_001B039C __attribute__((sda));
extern f32 D_L01_001B03A0 __attribute__((sda));
extern f32 D_L01_001B03A4 __attribute__((sda));
extern f32 D_L01_001B03A8 __attribute__((sda));
extern f32 D_L01_001B03AC __attribute__((sda));
extern f32 D_L01_001B03B0 __attribute__((sda));
extern f32 D_L01_001B03B4 __attribute__((sda));
extern f32 D_L01_001B03B8 __attribute__((sda));
extern f32 D_L01_001B03BC __attribute__((sda));
extern f32 D_L01_001B03C0 __attribute__((sda));
extern f32 D_L01_001B03C4 __attribute__((sda));
extern f32 D_L01_001B03C8 __attribute__((sda));
extern s32 D_L01_001B03CC __attribute__((sda));
extern s32 D_L01_001B03D0 __attribute__((sda));
extern s32 D_L01_001B03D8[4] __attribute__((sda));
extern u8 *D_L01_001FE180[];
typedef struct { u8 pad[0x160]; f32 f160; s32 pad164; s32 i168; s32 i16C; } L01Fx;
extern L01Fx D_L01_001B9380;
extern u8 D_0019B2E8[];

extern s32 func_001163B0(void);
extern s32 func_002D77E8(void);
extern s32 func_002D9308(u8);
extern void func_002E3470(void *, void *, void *);
extern void func_002E34A0(void *, void *, void *);
extern void func_002E34E0(void *, void *, f32);
extern f32 func_002E35A0(void *);
extern f32 func_002E3650(void *, void *);
extern void func_002E3738(void *, void *, f32);
extern void func_002E37D0(void *, void *, f32);
extern f32 func_002E3B10(f32, f32);
extern f32 func_002E4460(f32, f32);
extern f32 func_002E44A8(f32, f32);
extern f32 func_002E4548(f32, f32);
extern s32 func_002E45B8(f32);
extern void func_00306250(u8 *);
extern f32 func_00306448(u8 *);
extern void func_00307390(u8 *, s32, void *);
extern void func_00307E70(u8);
extern void func_0030F920(u8 *, s32, s32);
extern void func_00310138(u8 *, s32, s32, s32);
extern void func_00310418(u8 *, s32, s32);
extern s32 func_003104E8(s32);
extern s32 func_00310528(s32, s32);
extern f32 func_00310580(f32, f32);
extern void func_00310D28(u8 *, void *, f32, f32, f32, f32);
extern f32 func_00311A00(void *, s32, f32);
extern s32 func_00311B48(void *, void *, s32);
extern s32 func_00312B68(u8 *, s32, s32);
extern void func_00316348(void *, f32);
extern u8 *func_00327360(void *, void *, void *, s32, s32, s32, s32, s32, s32);
extern s32 func_00337A60(void *, void *, void *, s32);
extern void func_0034ECD0(void *, void *);
extern s32 func_00355780(s32, s32, u8 *);
extern s32 func_00355828(s32, s32, u8 *, s32);
extern void swamp_monster_spawn_splash(u8 *, s32, s32, s32);
extern void swamp_monster_release_attack_slot(u8 *);
extern void swamp_monster_arm_init(u8 *);
extern void swamp_monster_release_arm_timers(u8 *);
extern void UpdateOozlaLinkedGroupDamage(u8 *);
extern void swamp_monster_test_attack_segment_hits_hero(u8 *, void *, void *, u8, void *);

/* Updates the swamp monster arm. It reaches for the hero, swings and sparks on a hit, then goes back to rest. */
void swamp_monster_arm_update(u8 *moby)
{
    f32 vecA[4];
    f32 vecB[4];
    f32 vecC[4];
    f32 vecD[4];
    f32 vecE[4];
    f32 vecF[4];
    f32 vecG[4];
    f32 vecH[4];
    u8 *vars = 0;
    u8 *e1 = 0;
    u8 *e2 = 0;
    u8 *e9 = 0;
    u8 *tgt5 = 0;
    u8 *tgt7 = 0;
    u8 *tbl7a = 0;
    u8 *tbl7b = 0;
    u8 *pos5 = 0;
    u8 *pos6 = 0;
    u8 *pos7 = 0;
    u8 *particle = 0;
    s32 flag = 0;
    s32 i1 = 0;
    s32 i2 = 0;
    s32 j = 0;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    f32 animFrame = 0.0f;
    f32 f5 = 0.0f;
    f32 f6a = 0.0f;
    f32 f6 = 0.0f;
    f32 f7 = 0.0f;
    f32 dir5a = 0.0f;
    f32 dir5b = 0.0f;
    f32 dir6a = 0.0f;
    f32 dir6b = 0.0f;
    u8 *e0 = 0;
    u8 *e3 = 0;
    u8 *heroTarget = 0;
    u8 *heroTarget6 = 0;
    s32 level = 0;
    f32 rnd = 0.0f;
    f32 ra = 0.0f;
    f32 rb = 0.0f;
    f32 rc = 0.0f;
    s32 mode6 = 0;
    s32 hit7 = 0;
    s32 busy1 = 0;
    s32 busy2 = 0;
    s32 busy3 = 0;
    f32 scale3 = 0.0f;
    f32 yaw5a = 0.0f;
    f32 yaw5b = 0.0f;
    f32 yaw6a = 0.0f;
    f32 yaw6b = 0.0f;
    f32 spinx = 0.0f;
    f32 spiny = 0.0f;
    f32 rise = 0.0f;
    f32 scale6 = 0.0f;
    f32 scale7 = 0.0f;
    s32 busy8 = 0;

    vars = *(u8 **)(moby + 0x68);
    UpdateOozlaLinkedGroupDamage(moby);
    switch (moby[0x95]) {
    case 0:
        if (D_L01_001B2088 < 2)
            return;
        swamp_monster_arm_init(moby);
        break;
    case 1:
        e1 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
        if (*(s32 *)(vars + 0xC8) != 0)
            func_00307390(moby, 7, e1 + 0x10);
        else
            func_00307390(moby, 8, e1 + 0x10);
        qcopy(e1 + 0xF0, moby + 0xF0);
        switch (moby[0x20]) {
        case 0:
            flag = 0;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE0);
            if (*(s32 *)(vars + 0x74) == 1) {
                if (*(s32 *)(vars + 0x7C) == 1)
                    flag = 1;
            }
            if (*(s32 *)(vars + 0xC0) > 0)
                flag = 1;
            e0 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (func_00312B68(e0, 0x10001, 0) != 0)
                flag = 1;
            if (flag) {
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                *(s32 *)(vars + 0xBC) = 0;
                func_00310418(moby, 1, -1);
            }
            break;
        case 1:
            if (*(s32 *)(vars + 0xBC) != 0)
                break;
            e2 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (*(s32 *)(vars + 0xC8) != 0) {
                if (moby[0x43] != 10)
                    func_00310138(moby, 10, 0, 7);
                func_00310138(e2, 8, 0, 7);
            } else {
                if (moby[0x43] != 6)
                    func_00310138(moby, 6, 0, 7);
            }
            func_00355828(0, 0, e2, 0xB1A);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 2, 1);
            break;
        case 2:
            busy1 = func_003104E8(4);
            if (busy1 == 0)
                swamp_monster_spawn_splash(moby, 3, 10, 1);
            if (!(moby[0x60] & 2))
                break;
            e3 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            e3[0x95] = 1;
            if (*(s32 *)(vars + 0xEC) == -1)
                goto done;
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            *(s32 *)(vars + 0xBC) = 0x28;
            if (moby[0x43] != 0)
                func_00310138(moby, 0, 0, 1);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
            func_00310418(moby, 0, 4);
            break;
        }
        break;
    case 2:
        busy2 = func_003104E8(5);
        if (busy2 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if ((moby[0x42] == 6 || moby[0x42] == 10) && (moby[0x60] & 2)) {
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            if (moby[0x43] != 0)
                func_00310138(moby, 0, 0, 0);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 4);
        }
        break;
    case 3:
        busy3 = func_003104E8(5);
        if (busy3 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 0xF0;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale3 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale3;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xEC);
            func_00310418(moby, 0, 5);
        }
        break;
    case 4:
        *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
        if (*(s32 *)(vars + 0x74) == 1 && *(s32 *)(vars + 0x7C) == 1) {
            if (*(s32 *)(vars + 0xBC) == 0)
                *(s32 *)(vars + 0xBC) = 0x78;
            if (*(s32 *)(vars + 0xBC) == 1) {
                if (*(f32 *)(vars + 0xD4) > 0.0f)
                    *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
                *(f32 *)(moby + 0x48) = 1.0f;
                if (moby[0x43] != 0)
                    func_00310138(moby, 0, 0, func_00310528(10, 15));
                func_00310418(moby, 0, 3);
            }
        }
        break;
    case 5:
        if (*(s32 *)(vars + 0x74) == 1) {
            func_00337A60(vars + 0x90, vars + 0x60, D_L01_001FE180[*(s32 *)(vars + 0xB8)] + 0x10, *(s32 *)D_L01_001FE180[*(s32 *)(vars + 0xB8)]);
            *(s32 *)(vars + 0xC0) = 0xF0;
            tgt5 = vars + 0x90;
        } else {
            qcopy(vars + 0x90, vars + 0x80);
            tgt5 = vars + 0x90;
        }
        heroTarget = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if (*(u8 **)(vars + 0x70) == heroTarget) {
            func_002E34E0(vecA, &((Hero *)g_hero_state)->b[0x110], D_L01_001B0390);
            func_002E3470(vecA, vecA, *(u8 **)(vars + 0x70) + 0x10);
        } else {
            qcopy(vecA, *(u8 **)(vars + 0x70) + 0x10);
        }
        pos5 = moby + 0x10;
        func_002E34A0(vecB, tgt5, pos5);
        func_002E34E0(vecB, vecB, 0.05f);
        func_002E37D0(vecB, vecB, 0.050000004f);
        vecB[2] = 0.0f;
        func_002E3470(pos5, pos5, vecB);
        dir5a = 0.09599312f;
        if (vars[0xDD] != 0)
            dir5a = -0.09599312f;
        yaw5a = func_002E4460(*(f32 *)(moby + 0xF8), dir5a);
        *(f32 *)(moby + 0xF8) = yaw5a;
        f5 = func_002E3B10(vecA[0] - *(f32 *)(moby + 0x10), vecA[1] - *(f32 *)(moby + 0x14));
        func_00310D28(moby, vars + 0xCC, f5, 0.002327106f, 0.1f, 0.13962637f);
        if (moby[0x60] & 2)
            *(f32 *)(moby + 0x48) = func_00310580(0.8f, 1.2f);
        if (D_L01_001A8F40 != 2 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F && *(s32 *)(vars + 0xC4) == 0 &&
            (moby[0x21] == 0xFF || **(s32 **)(vars + 0xD8) <= 0) && func_002E3650(pos5, vars + 0x60) < 35.0f &&
            (f5 = func_002E3B10(vecA[0] - *(f32 *)(moby + 0x10), vecA[1] - *(f32 *)(moby + 0x14)),
             func_002E4548(*(f32 *)(moby + 0xF8), f5) < 0.034906588f)) {
            vars[0xDC] = 1;
            if (moby[0x21] != 0xFF)
                **(s32 **)(vars + 0xD8) += 1;
            if (moby[0x43] != 2)
                func_00310138(moby, 2, 0, func_00310528(7, 12));
            func_00310418(moby, 0, 6);
            vars[0xDE] = 0;
        } else if (*(s32 *)(vars + 0xC0) == 0) {
            if (moby[0x43] != 6)
                func_00310138(moby, 6, 0, 0x14);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 2);
        }
        dir5b = 0.09599312f;
        if (vars[0xDD] != 0)
            dir5b = -0.09599312f;
        yaw5b = func_002E44A8(*(f32 *)(moby + 0xF8), dir5b);
        *(f32 *)(moby + 0xF8) = yaw5b;
        break;
    case 6:
        pos6 = moby + 0x10;
        animFrame = func_00306448(moby);
        func_002E34A0(vecA, vars + 0x90, pos6);
        func_002E34E0(vecA, vecA, 0.05f);
        func_002E37D0(vecA, vecA, 0.050000004f);
        vecA[2] = 0.0f;
        func_002E3470(pos6, pos6, vecA);
        if (animFrame > 46.0f && animFrame < 56.0f) {
            for (i1 = 1; i1 < 8; i1++) {
                func_00307390(moby, i1, vecB);
                func_00307390(moby, i1 + 1, vecD);
                func_002E3738(vecF, moby + 0xD0, 0.3f);
                func_002E3738(vecG, moby + 0xD0, 0.3f);
                func_002E3470(vecC, vecB, vecF);
                func_002E3470(vecE, vecD, vecG);
                func_002E34A0(vecB, vecB, vecF);
                func_002E34A0(vecD, vecD, vecG);
                swamp_monster_test_attack_segment_hits_hero(moby, vecB, vecD, vars[0x34], vars + 0xDE);
                swamp_monster_test_attack_segment_hits_hero(moby, vecC, vecE, vars[0x34], vars + 0xDE);
            }
            func_00307390(moby, 6, vecB);
            qcopy(vecC, vecB);
            vecB[2] += 0.5f;
            vecD[2] += 2.0f;
            vecC[2] += 2.0f;
            vecE[2] += 0.5f;
            swamp_monster_test_attack_segment_hits_hero(moby, vecB, vecD, vars[0x34], vars + 0xDE);
            swamp_monster_test_attack_segment_hits_hero(moby, vecC, vecE, vars[0x34], vars + 0xDE);
        }
        if (animFrame >= 56.0f && vars[0xDE] == 0) {
            func_00355780(2, 0, moby);
            vars[0xDE] = 1;
        }
        level = func_002D9308(moby[0xB0]);
        D_L01_001B03D0 = D_L01_001B03D8[level - 1];
        if (animFrame < (f32)D_L01_001B03D0 &&
            (animFrame < 20.0f || (((Hero *)g_hero_state)->i[0x340 / 4] != 0 && ((Hero *)g_hero_state)->h[0x34E / 2] == 0 &&
                           ((Hero *)g_hero_state)->i[0x229C / 4] != 4))) {
            dir6a = 0.09599312f;
            if (vars[0xDD] != 0)
                dir6a = -0.09599312f;
            yaw6a = func_002E4460(*(f32 *)(moby + 0xF8), dir6a);
            *(f32 *)(moby + 0xF8) = yaw6a;
            heroTarget6 = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
            if (*(u8 **)(vars + 0x70) == heroTarget6) {
                func_002E34E0(vecB, &((Hero *)g_hero_state)->b[0x110], 55.0f - animFrame);
                func_002E3470(vecB, vecB, *(u8 **)(vars + 0x70) + 0x10);
            } else {
                qcopy(vecB, *(u8 **)(vars + 0x70) + 0x10);
            }
            f6a = func_002E3B10(vecB[0] - *(f32 *)(moby + 0x10), vecB[1] - *(f32 *)(moby + 0x14));
            func_00310D28(moby, vars + 0xCC, f6a, 0.002327106f, 0.1f, 0.13962637f);
            dir6b = 0.09599312f;
            if (vars[0xDD] != 0)
                dir6b = -0.09599312f;
            yaw6b = func_002E44A8(*(f32 *)(moby + 0xF8), dir6b);
            *(f32 *)(moby + 0xF8) = yaw6b;
        }
        if (animFrame > 55.0f && animFrame < 58.0f) {
            if (animFrame <= 56.0f) {
                D_L01_001B9380.f160 = 0.2f;
                D_L01_001B9380.i168 = 0x14;
                D_L01_001B9380.i16C = 0;
            }
            f6 = *(f32 *)(moby + 0x18);
            for (i2 = 1; i2 < 8; i2++) {
                func_00307390(moby, i2, vecB);
                f6 = func_00311A00(vecB, 2, 0.5f);
                mode6 = func_002D77E8();
                if (mode6 != 3)
                    break;
            }
            vecB[2] = f6;
            func_00307390(moby, 8, vecC);
            vecC[2] = f6;
            func_002E34A0(vecC, vecC, vecB);
            qzero(vecH);
            vecH[3] = D_L01_001B03BC;
            for (j = 0; j < D_L01_001B03CC; j++) {
                rnd = func_00310580(0.0f, 1.0f);
                func_002E34E0(vecD, vecC, rnd);
                func_00316348(vecD, 0.1f);
                func_002E3470(vecD, vecD, vecB);
                spinx = func_00310580(-(D_L01_001B03C4 * 0.016666668f), D_L01_001B03C4 * 0.016666668f);
                func_002E3738(vecF, moby + 0xD0, spinx);
                spiny = func_00310580(-(D_L01_001B03C8 * 0.016666668f), D_L01_001B03C8 * 0.016666668f);
                func_002E3738(vecG, moby + 0xC0, spiny);
                func_002E3470(vecE, vecF, vecG);
                rise = func_00310580(0.0f, D_L01_001B03C0 * 0.016666668f);
                vecE[2] = rise;
                vecE[3] = D_L01_001B03B8;
                ra = func_00310580(D_L01_001B03A0, D_L01_001B03A4);
                a = func_002E45B8(ra);
                rb = func_00310580(D_L01_001B03A8, D_L01_001B03AC);
                b = func_002E45B8(rb);
                rc = func_00310580(D_L01_001B03B0, D_L01_001B03B4);
                c = func_002E45B8(rc);
                particle = func_00327360(vecD, vecE, vecH, D_L01_001B0398, D_L01_001B039C, a, b, c, -1);
                if (particle != 0 && (func_001163B0() & 1))
                    particle[3] = 0x48;
            }
        }
        if (moby[0x60] & 2) {
            swamp_monster_release_attack_slot(moby);
            *(s32 *)(vars + 0xC4) = 0xB4;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale6 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale6;
            func_00310418(moby, 0, 5);
        }
        break;
    case 7:
        moby[0xA8] = 0xFF;
        pos7 = moby + 0x10;
        func_002E3470(vecA, pos7, vars + 0xA0);
        tbl7a = D_L01_001FE180[*(s32 *)(vars + 0xB8)];
        hit7 = func_00311B48(vecA, tbl7a + 0x10, *(s32 *)tbl7a);
        if (hit7 != 0) {
            qcopy(pos7, vecA);
        } else {
            tbl7b = D_L01_001FE180[*(s32 *)(vars + 0xB8)];
            func_00337A60(pos7, vecA, tbl7b + 0x10, *(s32 *)tbl7b);
            func_002E34A0(vecB, vars + 0x80, pos7);
            func_002E3738(vecB, vecB, 0.033333335f);
            func_002E3470(pos7, pos7, vecB);
        }
        f7 = func_002E35A0((vars + 0xA0)) - 0.0030555557f;
        if (f7 < 0.0f) {
            f7 = 0.0f;
        }
        func_002E3738((vars + 0xA0), (vars + 0xA0), f7);
        if (!(moby[0x60] & 2))
            break;
        qzero_nc((vars + 0xA0));
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            if (moby[0x42] == 3) {
                if (moby[0x43] != 4)
                    func_00310138(moby, 4, 0, 10);
            } else {
                func_00310418(moby, 0, 9);
            }
        } else {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 0xF0;
            *(s32 *)(vars + 0xC4) = 0;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale7 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale7;
            func_00310418(moby, 0, 5);
        }
        break;
    case 8:
        busy8 = func_003104E8(4);
        if (busy8 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if (!(moby[0x60] & 2))
            break;
    case 9:
        func_0030F920(moby, 0x200, 3);
        if (*(s32 *)(vars + 0xE4) != -1 && !(D_0019B2E8[moby[0xB0] + (g_current_map_index << 4)] & 0x80)) {
            func_00307E70(moby[0xB0]);
            e9 = D_L01_001B264C + (*(s32 *)(vars + 0xE4) << 7);
            func_0034ECD0(e9 + 0x30, e9 + 0x70);
        }
    done:
        func_00306250(moby);
        return;
    }
    swamp_monster_release_arm_timers(moby);
}
