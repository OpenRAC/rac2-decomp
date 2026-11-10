/* func_PAL_L08_0043B690, the PAL copy of func_L08_00435A78: the same C, with PAL's text ids,
   the 50 Hz scale on its timers and random periods, and 1.44f on the final speed and blend. */
#include "common.h"

typedef struct L08Thing L08Thing;

extern void func_0029F338(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern float func_00282E80(char *, void *);
extern void func_L08_00435990(L08Thing *);

extern u8 D_001A7A40[] __attribute__((sda));
extern s32 D_L08_001A8F00[] __attribute__((sda));

extern void func_002A7750(void *, int, int);
extern s32 func_L08_00435938(void);
extern void func_L08_0036EFC8(void), func_L01_003128C0(void *);
extern int func_L01_003245E0(void *, int, float);
extern void func_L01_003246D0(void *), func_L01_00324550(int, ...);
extern int func_00288AA0(void *, int), func_002F5D10(void);
extern void func_00288BE8(void *), func_002A8598(int, int), func_L08_0036F030(void);
extern void func_0026FEB8(const char *, ...);
extern int func_0029B3E0(int, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_0030C710(int);
extern int func_00282978(void *), func_00282948(void *), func_00283CF0(float);
extern float func_00283248(float, float), func_00283C80(float, float);
extern float func_00283B98(float, float), func_00283BE0(float, float), func_00282E20(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);

/* The hero: read at 0x80 (centre), 0xE0 (position) and 0x110 (velocity). */
typedef struct {
    u8 pad0[0x80];
    char x80[0x60];
    f32 pos[4];
    u8 padF0[0x20];
    f32 x110[4];
} L08Hero;
extern L08Hero D_00189E20;

/* One 0x100-byte entity of the table at D_L08_001B29DC. */
typedef struct {
    u8 pad0[0x31];
    u8 x31;
    u8 pad32[2];
    u16 x34;
    u8 pad36[0xBC - 0x36];
    u8 xBC;
    u8 padBD[0x100 - 0xBD];
} L08Moby;
extern L08Moby *D_L08_001B29DC MACRO_ADDR;

/* Words retail never moves into a delay slot are fields read at an offset from
   an earlier symbol; bare names are loaded by $gp in a slot (docs/build/compiler-notes.md). */
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern int D_L08_001B2724[] __attribute__((sda));
extern int D_L08_001B2508 MACRO_ADDR;
extern int D_L08_001B1FA8 MACRO_ADDR;
extern int D_001A79F8 MACRO_ADDR;
extern u8 D_001395B8[];
extern int D_00138324;
extern int D_L08_00295E50[];
extern u8 D_L08_001BFD00[];
extern char D_L08_001B1FB0[];

#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))

/* An interaction state machine at byte 0x20: offers an item for its price while
   the quantity at D_001A7A00+0x1A covers it, then buys the remaining quantity back
   at 1000 (10000 with the flag at D_001A7A00+0xA) each; afterwards aims the head at the hero. */
void func_PAL_L08_0043B690(u8 *self)
{
    float dest[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *data = *(u8 **)(self + 0x68);
    int n, active;
    float speed, yaw, pitch, angle;
    float blend;

    func_L08_00435990((L08Thing *)self);
    if (D_L08_001A8F00[0] == 6) {
        self[0x31] = 0;
        H(self, 0x34) |= 1;
        F(self, 0xF4) = -3.14159274f;
    } else {
        self[0x31] = 1;
        F(self, 0xF4) = 0;
        H(self, 0x34) &= 0xFFFE;
    }
    if (D_L08_001B2508 == 5)
        func_L08_00435938();
    switch (self[0x20]) {
    case 0:
        if (!D_001395B8[0x1C])
            func_L08_0036EFC8();
        else if (I(data, 0x124) != -1) {
            func_0029F338(&D_L08_001B29DC[I(data, 0x124)]);
            I(data, 0x124) = -1;
        }
        func_L08_00435938();
        func_L01_003128C0(self);
        if (D_001395B8[0x1C]) {
            if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
                func_002A7750(self, 6, -1);
            else
                func_002A7750(self, 7, -1);
        } else if (D_001395B8[0x1B]) {
            if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
                func_002A7750(self, 3, -1);
            else
                func_002A7750(self, 4, -1);
        } else
            func_002A7750(self, 1, -1);
        break;
    case 1:
        if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_003246D0(self);
            if (func_00288AA0(D_L08_001BFD00, 0x59)) {
                D_001395B8[0x1B] = 1;
                func_00288BE8(D_L08_001BFD00);
                func_002A7750(self, 2, -1);
            }
        }
        break;
    case 2:
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            D_L08_001B29DC[I(data, 0x124)].x34 |= 1;
            D_L08_001B29DC[I(data, 0x124)].x31 = 0;
        }
        D_L08_001B2724[1] = 1;
        if (!func_002F5D10()) {
            D_L08_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (I(data, 0x124) != -1) {
                D_L08_001B29DC[I(data, 0x124)].x34 &= 0xFFFE;
                D_L08_001B29DC[I(data, 0x124)].x31 = 1;
            }
            if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
                func_002A7750(self, 3, -1);
            else
                func_002A7750(self, 4, -1);
        }
        break;
    case 3:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) >= (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
            func_002A7750(self, 4, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x12F6, (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]), -1);
            func_L01_003246D0(self);
        }
        break;
    case 4:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
            func_002A7750(self, 3, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x12E8, (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]), -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L08_001BFD00, 0x5A);
                (*(s16 *)(D_001A7A00 + 0x1A)) -= (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]);
                func_00288BE8(D_L08_001BFD00);
                func_002A7750(self, 5, -1);
            }
        }
        break;
    case 5:
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            func_0029F338(&D_L08_001B29DC[I(data, 0x124)]);
            I(data, 0x124) = -1;
        }
        D_L08_001B2724[1] = 1;
        if (!func_002F5D10()) {
            D_L08_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (self[0x21] != 0xFF)
                func_002A8598(self[0x21], 1);
            D_001395B8[0x1C] = 1;
            func_L08_0036F030();
            func_0026FEB8(D_L08_001B1FB0);
            if (I(data, 0x124) != -1) {
                func_0029F338(&D_L08_001B29DC[I(data, 0x124)]);
                I(data, 0x124) = -1;
            }
            if (I(data, 0x120) != -1)
                D_L08_001B29DC[I(data, 0x120)].xBC = 1;
            func_0029B3E0(0, -1);
            if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
                func_002A7750(self, 6, -1);
            else
                func_002A7750(self, 7, -1);
        }
        break;
    case 6:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) > 0)
            func_002A7750(self, 7, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (!D_L08_001B1FA8)
                func_L01_00324550(0x1322, 0, -1);
            else
                func_L01_00324550(0x12F9, -1);
            func_L01_003246D0(self);
        }
        break;
    case 7:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
            func_002A7750(self, 6, -1);
        else {
            n = D_001A7A00[0xA] ? 10 : 1;
            if (func_L01_003245E0(self, 10, 2.5f)) {
                n *= 1000;
                func_L01_00324550(0x12E9, (*(s16 *)(D_001A7A00 + 0x1A)), (*(s16 *)(D_001A7A00 + 0x1A)) * n, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L08_00435938();
                    D_001A79F8 += (*(s16 *)(D_001A7A00 + 0x1A)) * n;
                    func_002E5DA0(0, 0, self, func_002A7820(13, 17));
                    (*(s16 *)(D_001A7A00 + 0x1A)) = 0;
                    func_L00_0030C710(150);
                    func_002A7750(self, 8, -1);
                }
            }
        }
        break;
    case 8:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > 33 && H(self, 0x96) < 75 && H(self, 0x96) % 3 == 0)
            func_002E5DA0(0, 0, self, func_002A7820(13, 17));
        if (func_L01_003245E0(self, 10, 2.5f))
            func_L01_00324550(0x1322, D_L08_001B1FA8, -1);
        else
            func_002A7750(self, 6, -1);
        break;
    }
    if (self[0x20]) {
        if (self[0x43] == 1 && func_00282978(data + 0x11E)) {
            H(data, 0x11E) = func_00283CF0((func_002A7878(1200, 2400) * 5 + 2) * 0.16666667f);
            if (self[0x43] != 2)
                func_002A7470(self, 2, 0, 8);
        } else if ((self[0x60] & 2) && self[0x43] != 1)
            func_002A7470(self, 1, 0, 8);
    }
    speed = 0.02f;
    blend = 0.3f;
    active = 0;
    if (self[0x43] == 1) {
        active = 1;
        if (func_00282E80((char *)self + 0x10, D_00189E20.x80) < 8 &&
            func_00283C80(F(self, 0xF8), func_00283248(D_00189E20.pos[0] - F(self, 0x10),
                                                       D_00189E20.pos[1] - F(self, 0x14))) < 1.57079649f) {
            if (func_00282DF0(D_00189E20.x110) > 0.01f)
                I(data, 0x114) = 100;
            else
                func_00282948(data + 0x114);
        } else if (I(data, 0x114)) {
            I(data, 0x114) = 0;
            qcopy(data + 0x100, D_00189E20.pos);
        }
        if (func_00282948(data + 0x118)) {
            I(data, 0x118) = func_00283CF0((func_002A7878(180, 300) * 5 + 2) * 0.16666667f);
            angle = func_00283B98(F(self, 0xF8), func_002A7878(-90, 90) * 0.0174532942f);
            pitch = func_002A7878(0, 30) * 0.0174532942f;
            func_002AF000(data + 0x100, 6, angle, pitch);
            func_00282CC0(data + 0x100, data + 0x100, self + 0x10);
        }
        if (I(data, 0x114)) {
            qcopy(dest, D_00189E20.pos);
            speed = 0.04f;
            blend = 0.3f;
        } else
            qcopy(dest, data + 0x100);
    }
    if (active) {
        qcopy(pos, self + 0x10);
        pos[2] += 2;
        func_00282CF0(delta, dest, pos);
        yaw = func_00283BE0(func_00283248(delta[0], delta[1]), F(self, 0xF8));
        pitch = -func_00283248(func_00282E20(delta), delta[2]);
        if (yaw > 1.57079649f)
            yaw = 1.57079649f;
        else if (yaw < -1.57079649f)
            yaw = -1.57079649f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F(data, 0x64) = pitch;
        F(data, 0x68) = yaw * 0.6f;
        F(data, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40[0])
        F(data, 0x70) = 2.75f;
    func_002AEC48(self, data, 0, speed * 1.44f, blend * 1.44f);
    func_002AEC48(self, data + 0x80, 1, speed * 1.44f, blend * 1.44f);
}
