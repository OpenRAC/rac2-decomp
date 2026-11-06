/* func_PAL_L01_003D0A08, the PAL copy of func_L01_003CC930: the same C with 50 Hz values.
 * Timers 240, 180, 120, 40, 20 become 200, 150, 100, 33, 17; per-frame rates are scaled by 6/5
 * (0.05f and 0.050000004f both become 0.060000002f, so retail keeps it in a saved register);
 * 1/60 becomes 0.020000001f. The three random values passed to func_002E45B8 are floats, so
 * PAL's (x * 5 + 2) / 6 is written out with a multiply by the constant 1/6.
 * -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-hazard-labels, as the template's unit.
 */
#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } Hero;

extern char D_00189E20[];
extern s32 D_L01_001B2088;
extern u8 *D_L01_001B255C;
extern u8 *D_L01_001B264C;
extern s32 D_L01_001A8F40;
extern s32 D_001A79F0;
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
extern void func_PAL_002A7650(u8 *, s32, s32);
extern void func_PAL_002A7E68(u8 *, s32, s32, s32);
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
extern void func_PAL_L01_003CFDB0(u8 *, s32, s32, s32);
extern void func_L01_003CBFA8(u8 *);
extern void func_PAL_L01_003D00C8(u8 *);
extern void func_L01_003CC210(u8 *);
extern void func_PAL_L01_003D0358(u8 *);
extern void func_L01_003CC898(u8 *, void *, void *, u8, void *);

void func_PAL_L01_003D0A08(u8 *self)
{
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
    f32 v40[4];
    f32 v50[4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    u8 *pv = 0;
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
    u8 *p = 0;
    s32 flag = 0;
    s32 i1 = 0;
    s32 i2 = 0;
    s32 j = 0;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    f32 d = 0.0f;
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
    u8 *hero5 = 0;
    u8 *hero6 = 0;
    s32 lv = 0;
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

    pv = *(u8 **)(self + 0x68);
    func_PAL_L01_003D0358(self);
    switch (self[0x95]) {
    case 0:
        if (D_L01_001B2088 < 2)
            return;
        func_PAL_L01_003D00C8(self);
        break;
    case 1:
        e1 = D_L01_001B255C + (*(s32 *)(pv + 0xB4) << 8);
        if (*(s32 *)(pv + 0xC8) != 0)
            func_00307390(self, 7, e1 + 0x10);
        else
            func_00307390(self, 8, e1 + 0x10);
        qcopy(e1 + 0xF0, self + 0xF0);
        switch (self[0x20]) {
        case 0:
            flag = 0;
            *(s32 *)(pv + 0xF0) = *(s32 *)(pv + 0xE0);
            if (*(s32 *)(pv + 0x74) == 1) {
                if (*(s32 *)(pv + 0x7C) == 1)
                    flag = 1;
            }
            if (*(s32 *)(pv + 0xC0) > 0)
                flag = 1;
            e0 = D_L01_001B255C + (*(s32 *)(pv + 0xB4) << 8);
            if (func_00312B68(e0, 0x10001, 0) != 0)
                flag = 1;
            if (flag) {
                *(u16 *)(self + 0x34) &= 0xEFFF;
                *(s32 *)(pv + 0xBC) = 0;
                func_00310418(self, 1, -1);
            }
            break;
        case 1:
            if (*(s32 *)(pv + 0xBC) != 0)
                break;
            e2 = D_L01_001B255C + (*(s32 *)(pv + 0xB4) << 8);
            if (*(s32 *)(pv + 0xC8) != 0) {
                if (self[0x43] != 10)
                    func_PAL_002A7E68(self, 10, 0, 7);
                func_PAL_002A7E68(e2, 8, 0, 7);
            } else {
                if (self[0x43] != 6)
                    func_PAL_002A7E68(self, 6, 0, 7);
            }
            func_00355828(0, 0, e2, 0xB1A);
            *(u16 *)(self + 0x34) &= 0xEFFF;
            func_00310418(self, 2, 1);
            break;
        case 2:
            busy1 = func_003104E8(4);
            if (busy1 == 0)
                func_PAL_L01_003CFDB0(self, 3, 10, 1);
            if (!(self[0x60] & 2))
                break;
            e3 = D_L01_001B255C + (*(s32 *)(pv + 0xB4) << 8);
            e3[0x95] = 1;
            if (*(s32 *)(pv + 0xEC) == -1)
                goto done;
            if (*(f32 *)(pv + 0xD4) > 0.0f)
                *(f32 *)(self + 0x18) = *(f32 *)(pv + 0xD4);
            *(u16 *)(self + 0x34) &= 0xEFFF;
            *(s32 *)(pv + 0xBC) = 33;
            if (self[0x43] != 0)
                func_PAL_002A7E68(self, 0, 0, 1);
            *(f32 *)(self + 0x48) = 0.0f;
            *(s32 *)(pv + 0xF0) = *(s32 *)(pv + 0xE8);
            func_00310418(self, 0, 4);
            break;
        }
        break;
    case 2:
        busy2 = func_003104E8(5);
        if (busy2 == 0)
            func_PAL_L01_003CFDB0(self, 3, 10, 1);
        if ((self[0x42] == 6 || self[0x42] == 10) && (self[0x60] & 2)) {
            if (*(f32 *)(pv + 0xD4) > 0.0f)
                *(f32 *)(self + 0x18) = *(f32 *)(pv + 0xD4);
            if (self[0x43] != 0)
                func_PAL_002A7E68(self, 0, 0, 0);
            *(f32 *)(self + 0x48) = 0.0f;
            *(u16 *)(self + 0x34) &= 0xEFFF;
            func_00310418(self, 0, 4);
        }
        break;
    case 3:
        busy3 = func_003104E8(5);
        if (busy3 == 0)
            func_PAL_L01_003CFDB0(self, 3, 10, 1);
        if (self[0x60] & 2) {
            *(u16 *)(self + 0x34) |= 0x1000;
            *(s32 *)(pv + 0xC0) = 200;
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, func_00310528(10, 15));
            scale3 = func_00310580(0.8f, 1.2f);
            *(f32 *)(self + 0x48) = scale3;
            *(s32 *)(pv + 0xF0) = *(s32 *)(pv + 0xEC);
            func_00310418(self, 0, 5);
        }
        break;
    case 4:
        *(s32 *)(pv + 0xF0) = *(s32 *)(pv + 0xE8);
        if (*(s32 *)(pv + 0x74) == 1 && *(s32 *)(pv + 0x7C) == 1) {
            if (*(s32 *)(pv + 0xBC) == 0)
                *(s32 *)(pv + 0xBC) = 100;
            if (*(s32 *)(pv + 0xBC) == 1) {
                if (*(f32 *)(pv + 0xD4) > 0.0f)
                    *(f32 *)(self + 0x18) = *(f32 *)(pv + 0xD4);
                *(f32 *)(self + 0x48) = 1.0f;
                if (self[0x43] != 0)
                    func_PAL_002A7E68(self, 0, 0, func_00310528(10, 15));
                func_00310418(self, 0, 3);
            }
        }
        break;
    case 5:
        if (*(s32 *)(pv + 0x74) == 1) {
            func_00337A60(pv + 0x90, pv + 0x60, D_L01_001FE180[*(s32 *)(pv + 0xB8)] + 0x10, *(s32 *)D_L01_001FE180[*(s32 *)(pv + 0xB8)]);
            *(s32 *)(pv + 0xC0) = 200;
            tgt5 = pv + 0x90;
        } else {
            qcopy(pv + 0x90, pv + 0x80);
            tgt5 = pv + 0x90;
        }
        hero5 = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
        if (*(u8 **)(pv + 0x70) == hero5) {
            func_002E34E0(v10, &((Hero *)D_00189E20)->b[0x110], D_L01_001B0390);
            func_002E3470(v10, v10, *(u8 **)(pv + 0x70) + 0x10);
        } else {
            qcopy(v10, *(u8 **)(pv + 0x70) + 0x10);
        }
        pos5 = self + 0x10;
        func_002E34A0(v20, tgt5, pos5);
        func_002E34E0(v20, v20, 0.060000002f);
        func_002E37D0(v20, v20, 0.060000002f);
        v20[2] = 0.0f;
        func_002E3470(pos5, pos5, v20);
        dir5a = 0.09599312f;
        if (pv[0xDD] != 0)
            dir5a = -0.09599312f;
        yaw5a = func_002E4460(*(f32 *)(self + 0xF8), dir5a);
        *(f32 *)(self + 0xF8) = yaw5a;
        f5 = func_002E3B10(v10[0] - *(f32 *)(self + 0x10), v10[1] - *(f32 *)(self + 0x14));
        func_00310D28(self, pv + 0xCC, f5, 0.0033510327f, 0.1f, 0.16755164f);
        if (self[0x60] & 2)
            *(f32 *)(self + 0x48) = func_00310580(0.8f, 1.2f);
        if (D_L01_001A8F40 != 2 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6F && *(s32 *)(pv + 0xC4) == 0 &&
            (self[0x21] == 0xFF || **(s32 **)(pv + 0xD8) <= 0) && func_002E3650(pos5, pv + 0x60) < 35.0f &&
            (f5 = func_002E3B10(v10[0] - *(f32 *)(self + 0x10), v10[1] - *(f32 *)(self + 0x14)),
             func_002E4548(*(f32 *)(self + 0xF8), f5) < 0.034906588f)) {
            pv[0xDC] = 1;
            if (self[0x21] != 0xFF)
                **(s32 **)(pv + 0xD8) += 1;
            if (self[0x43] != 2)
                func_PAL_002A7E68(self, 2, 0, func_00310528(7, 12));
            func_00310418(self, 0, 6);
            pv[0xDE] = 0;
        } else if (*(s32 *)(pv + 0xC0) == 0) {
            if (self[0x43] != 6)
                func_PAL_002A7E68(self, 6, 0, 0x14);
            *(u16 *)(self + 0x34) &= 0xEFFF;
            func_00310418(self, 0, 2);
        }
        dir5b = 0.09599312f;
        if (pv[0xDD] != 0)
            dir5b = -0.09599312f;
        yaw5b = func_002E44A8(*(f32 *)(self + 0xF8), dir5b);
        *(f32 *)(self + 0xF8) = yaw5b;
        break;
    case 6:
        pos6 = self + 0x10;
        d = func_00306448(self);
        func_002E34A0(v10, pv + 0x90, pos6);
        func_002E34E0(v10, v10, 0.060000002f);
        func_002E37D0(v10, v10, 0.060000002f);
        v10[2] = 0.0f;
        func_002E3470(pos6, pos6, v10);
        if (d > 46.0f && d < 56.0f) {
            for (i1 = 1; i1 < 8; i1++) {
                func_00307390(self, i1, v20);
                func_00307390(self, i1 + 1, v40);
                func_002E3738(v60, self + 0xD0, 0.3f);
                func_002E3738(v70, self + 0xD0, 0.3f);
                func_002E3470(v30, v20, v60);
                func_002E3470(v50, v40, v70);
                func_002E34A0(v20, v20, v60);
                func_002E34A0(v40, v40, v70);
                func_L01_003CC898(self, v20, v40, pv[0x34], pv + 0xDE);
                func_L01_003CC898(self, v30, v50, pv[0x34], pv + 0xDE);
            }
            func_00307390(self, 6, v20);
            qcopy(v30, v20);
            v20[2] += 0.5f;
            v40[2] += 2.0f;
            v30[2] += 2.0f;
            v50[2] += 0.5f;
            func_L01_003CC898(self, v20, v40, pv[0x34], pv + 0xDE);
            func_L01_003CC898(self, v30, v50, pv[0x34], pv + 0xDE);
        }
        if (d >= 56.0f && pv[0xDE] == 0) {
            func_00355780(2, 0, self);
            pv[0xDE] = 1;
        }
        lv = func_002D9308(self[0xB0]);
        D_L01_001B03D0 = D_L01_001B03D8[lv - 1];
        if (d < (f32)D_L01_001B03D0 &&
            (d < 20.0f || (((Hero *)D_00189E20)->i[0x340 / 4] != 0 && ((Hero *)D_00189E20)->h[0x34E / 2] == 0 &&
                           ((Hero *)D_00189E20)->i[0x229C / 4] != 4))) {
            dir6a = 0.09599312f;
            if (pv[0xDD] != 0)
                dir6a = -0.09599312f;
            yaw6a = func_002E4460(*(f32 *)(self + 0xF8), dir6a);
            *(f32 *)(self + 0xF8) = yaw6a;
            hero6 = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
            if (*(u8 **)(pv + 0x70) == hero6) {
                func_002E34E0(v20, &((Hero *)D_00189E20)->b[0x110], 55.0f - d);
                func_002E3470(v20, v20, *(u8 **)(pv + 0x70) + 0x10);
            } else {
                qcopy(v20, *(u8 **)(pv + 0x70) + 0x10);
            }
            f6a = func_002E3B10(v20[0] - *(f32 *)(self + 0x10), v20[1] - *(f32 *)(self + 0x14));
            func_00310D28(self, pv + 0xCC, f6a, 0.0033510327f, 0.1f, 0.16755164f);
            dir6b = 0.09599312f;
            if (pv[0xDD] != 0)
                dir6b = -0.09599312f;
            yaw6b = func_002E44A8(*(f32 *)(self + 0xF8), dir6b);
            *(f32 *)(self + 0xF8) = yaw6b;
        }
        if (d > 55.0f && d < 58.0f) {
            if (d <= 56.0f) {
                D_L01_001B9380.f160 = 0.2f;
                D_L01_001B9380.i168 = 17;
                D_L01_001B9380.i16C = 0;
            }
            f6 = *(f32 *)(self + 0x18);
            for (i2 = 1; i2 < 8; i2++) {
                func_00307390(self, i2, v20);
                f6 = func_00311A00(v20, 2, 0.5f);
                mode6 = func_002D77E8();
                if (mode6 != 3)
                    break;
            }
            v20[2] = f6;
            func_00307390(self, 8, v30);
            v30[2] = f6;
            func_002E34A0(v30, v30, v20);
            qzero(v80);
            v80[3] = D_L01_001B03BC;
            for (j = 0; j < D_L01_001B03CC; j++) {
                rnd = func_00310580(0.0f, 1.0f);
                func_002E34E0(v40, v30, rnd);
                func_00316348(v40, 0.1f);
                func_002E3470(v40, v40, v20);
                spinx = func_00310580(-(D_L01_001B03C4 * 0.020000001f), D_L01_001B03C4 * 0.020000001f);
                func_002E3738(v60, self + 0xD0, spinx);
                spiny = func_00310580(-(D_L01_001B03C8 * 0.020000001f), D_L01_001B03C8 * 0.020000001f);
                func_002E3738(v70, self + 0xC0, spiny);
                func_002E3470(v50, v60, v70);
                rise = func_00310580(0.0f, D_L01_001B03C0 * 0.020000001f);
                v50[2] = rise;
                v50[3] = D_L01_001B03B8;
                ra = func_00310580(D_L01_001B03A0, D_L01_001B03A4);
                a = func_002E45B8((ra * 5.0f + 2.0f) * 0.16666667f);
                rb = func_00310580(D_L01_001B03A8, D_L01_001B03AC);
                b = func_002E45B8((rb * 5.0f + 2.0f) * 0.16666667f);
                rc = func_00310580(D_L01_001B03B0, D_L01_001B03B4);
                c = func_002E45B8((rc * 5.0f + 2.0f) * 0.16666667f);
                p = func_00327360(v40, v50, v80, D_L01_001B0398, D_L01_001B039C, a, b, c, -1);
                if (p != 0 && (func_001163B0() & 1))
                    p[3] = 0x48;
            }
        }
        if (self[0x60] & 2) {
            func_L01_003CBFA8(self);
            *(s32 *)(pv + 0xC4) = 150;
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, func_00310528(10, 15));
            scale6 = func_00310580(0.8f, 1.2f);
            *(f32 *)(self + 0x48) = scale6;
            func_00310418(self, 0, 5);
        }
        break;
    case 7:
        self[0xA8] = 0xFF;
        pos7 = self + 0x10;
        func_002E3470(v10, pos7, pv + 0xA0);
        tbl7a = D_L01_001FE180[*(s32 *)(pv + 0xB8)];
        hit7 = func_00311B48(v10, tbl7a + 0x10, *(s32 *)tbl7a);
        if (hit7 != 0) {
            qcopy(pos7, v10);
        } else {
            tbl7b = D_L01_001FE180[*(s32 *)(pv + 0xB8)];
            func_00337A60(pos7, v10, tbl7b + 0x10, *(s32 *)tbl7b);
            func_002E34A0(v20, pv + 0x80, pos7);
            func_002E3738(v20, v20, 0.040000003f);
            func_002E3470(pos7, pos7, v20);
        }
        f7 = func_002E35A0((pv + 0xA0)) - 0.0044f;
        if (f7 < 0.0f) {
            f7 = 0.0f;
        }
        func_002E3738((pv + 0xA0), (pv + 0xA0), f7);
        if (!(self[0x60] & 2))
            break;
        qzero_nc((pv + 0xA0));
        if (*(f32 *)(pv + 0x20) <= 0.0f) {
            if (self[0x42] == 3) {
                if (self[0x43] != 4)
                    func_PAL_002A7E68(self, 4, 0, 10);
            } else {
                func_00310418(self, 0, 9);
            }
        } else {
            *(u16 *)(self + 0x34) |= 0x1000;
            *(s32 *)(pv + 0xC0) = 200;
            *(s32 *)(pv + 0xC4) = 0;
            if (self[0x43] != 1)
                func_PAL_002A7E68(self, 1, 0, func_00310528(10, 15));
            scale7 = func_00310580(0.8f, 1.2f);
            *(f32 *)(self + 0x48) = scale7;
            func_00310418(self, 0, 5);
        }
        break;
    case 8:
        busy8 = func_003104E8(4);
        if (busy8 == 0)
            func_PAL_L01_003CFDB0(self, 3, 10, 1);
        if (!(self[0x60] & 2))
            break;
    case 9:
        func_PAL_002A7650(self, 0x200, 3);
        if (*(s32 *)(pv + 0xE4) != -1 && !(D_0019B2E8[self[0xB0] + (D_001A79F0 << 4)] & 0x80)) {
            func_00307E70(self[0xB0]);
            e9 = D_L01_001B264C + (*(s32 *)(pv + 0xE4) << 7);
            func_0034ECD0(e9 + 0x30, e9 + 0x70);
        }
    done:
        func_00306250(self);
        return;
    }
    func_L01_003CC210(self);
}
