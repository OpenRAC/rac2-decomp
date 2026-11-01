#include "common.h"


extern void func_0029F338(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L08_003B2DB0(void *, void *, void *, int);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, int, int, float);

/* family c459a266b43242d6 - 352 bytes, 2 placements
   levels/19_grelbin @0x00412F70, levels/8_tabora @0x0041E630

   Fills five output floats from two pinned tables and a resident flag word,
   then clamps the three still free outputs to [-1, 1]. */

extern float D_00189E20_14[];

extern int D_00138180[];

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TI128 __attribute__((mode(TI)));

/* A resident word: the same address and the same value in every program.  It is
   read as a symbol here (the `sda` declaration leaves the one- or two-instruction
   choice to the assembler) and as a literal in func_L08_003DB4A0, whose two
   conditional loads the literal address form is what reproduces. */
extern s32 D_001A79F0 __attribute__((sda));

/* shared callee, named by its catalogue row (08:003289D0, 19:00319288) */
extern void func_L00_00326048(void *, s32, s32, s32, float);

extern char D_00189EA0[];
extern float func_00282E80(char *, void *);

/* Two 0x30-byte target records: [0] the tracked owner, [1] the nearest one seen. */
typedef struct {
    TI128 pos;      /* 0x00 */
    void *owner;    /* 0x10 */
    float dist;     /* 0x14 */
    s32 unk18;      /* 0x18 */
    s32 unk1C;      /* 0x1C */
    s32 valid;      /* 0x20 */
    s32 pad[3];
} L08Target;

extern L08Target D_L08_001B3490[] __attribute__((sda));

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L08Thing {
    u8 pad[0xAA];
    s16 kind;
} L08Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L08Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L08Thing *items[1];     /* bounded by count */
} L08Group;

extern L08Group D_L08_001BD800;
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L08_001B22E0[] __attribute__((sda));
extern f32 D_L08_001B2300[] __attribute__((sda));

extern void func_0029F978(u8 *, u32, u8 *);

/* For func_L08_00435A78. */
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
   an earlier symbol; bare names are loaded by $gp in a slot (docs/COMPILER-NOTES.md). */
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

/* Measures the resident actor position against POS: a nearer POS replaces record [1]
   (owner, distance, position), and record [0] is refreshed when OWNER is its owner.
   The records are reached as `sda` offsets, so every access is one assembler macro. */
void func_L08_003D3928(void *owner, void *pos)
{
    float d = func_00282E80(D_00189EA0, pos);

    if (d < D_L08_001B3490[1].dist) {
        D_L08_001B3490[1].unk1C = 0;
        D_L08_001B3490[1].owner = owner;
        D_L08_001B3490[1].unk18 = 0;
        D_L08_001B3490[1].dist = d;
        qcopy(&D_L08_001B3490[1].pos, pos);
        D_L08_001B3490[1].valid = 1;
    }
    if (D_L08_001B3490[0].owner == owner) {
        D_L08_001B3490[0].dist = d;
        qcopy(&D_L08_001B3490[0].pos, pos);
        D_L08_001B3490[0].valid = 1;
    }
}

INCLUDE_ASM("asm/levels", func_L08_003D39F0);

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
void func_L08_003D3EB8(u8 *a0)
{
    s32 v = *(s32 *)(a0 + 0x68);

    if (v == 0)
        return;
    func_L00_00326048(a0, v, 0x80AAAAD2, 0x80396464, 0.0610865355f);
}


void func_L08_003D4690(u8 *self)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(self + 0x68);
    int i;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        func_0029F338(self);
        return;
    }
    if ((self[0x60] & 2) && self[0x43])
        func_002A7470(self, 0, 0, 0);
    if (self[0xBC]) {
        self[0xBC] = 0;
        if (self[0x43] != 1) func_002A7470(self, 1, 0, 0);
        func_002AF000(direction, 1.0f, *(float *)(self+0xF8), -*(float *)(self+0xF4));
        func_0029FCC0(self, 0, position);
        func_L08_003B2DB0(self, position, direction, 0x5A);
        i = 4;
        do {
            *(TI128 *)random = 0;
            random[0] = func_002A7878(-1.0f, 1.0f);
            random[1] = func_002A7878(-1.0f, 1.0f);
            random[2] = func_002A7878(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random;
            func_00282F20(velocity, velocity, func_00282DF0(direction)*0.65f);
            func_00282CC0(velocity, direction, velocity);
            func_00282F20(velocity, velocity, func_002A7878(0.050000004f, 0.10000001f));
            func_L04_00358AE8(position, velocity, 0x5F2F4F6F, func_002A7820(5,10), 50000.0f);
        } while (--i >= 0);
        func_00282F20(direction, direction, 0.008333334f);
        func_L04_00358AE8(position, direction, 0x2F4F7F7F, func_002A7820(4,7), 500000.0f);
    }
}

/* The same resident word, but the 8 case falls through to a 1/2 selector. */
s32 func_L08_003DB4E8(void)
{
    s32 v = D_001A79F0;
    s32 r = 1;

    if (v == 8)
        return 1;
    if (v == 0x13)
        r = 2;
    return r;
}

INCLUDE_ASM("asm/levels", func_L08_003DB518);

/* func_L08_003DB8E8 is matched in its own unit, L08_003DB8E8-g8.c. */






INCLUDE_ASM("asm/levels", func_L08_003F6610);

/* func_L08_0041E4F8 is defined in L08_0041E4F8-flags-g8.c. */

/* shared native body of family c459a266b43242d6 */
void func_L08_0041E630(float *a0, float *a1, float *a2, float *a3, float *p4)
{
    float f1;
    float f2;
    int v1;

    *a0 = -D_00189E20_14[2028];
    *a2 = -D_00189E20_14[2029];
    v1 = D_00138180[104];
    f2 = 0.0f;
    if (v1 & 0x40)
        f2 = 1.0f;
    f1 = (v1 & 0x20) ? (f2 - 1.0f) : f2;
    *a1 = f1;
    *a3 = *(float *)&D_00138180[75];
    v1 = D_00138180[104];
    f1 = 0.0f;
    if (v1 & 0x1)
        f1 = 1.0f;
    if (v1 & 0x2)
        f1 = f1 - 1.0f;
    *p4 = f1;
    if (*a0 > 1.0f)
        *a0 = 1.0f;
    else if (*a0 < -1.0f)
        *a0 = -1.0f;
    if (*a1 > 1.0f)
        *a1 = 1.0f;
    else if (*a1 < -1.0f)
        *a1 = -1.0f;
    if (*p4 > 1.0f)
        *p4 = 1.0f;
    else if (*p4 < -1.0f)
        *p4 = -1.0f;
}

INCLUDE_ASM("asm/levels", func_L08_0041E790);

/* func_L08_0041EA88 is defined in L08_0041EA88-match.c. */

INCLUDE_ASM("asm/levels", func_L08_004207D0);

/* func_L08_0042E678 is defined in L08_0042E678-g8.c. */

/* func_L08_0042EF00 is defined in L08_0042EF00-g8.c. */

/* func_L08_00435600 is defined in L08_00435600-helpers.c. */

/* Stores one 16-byte block through the pointer at 0x68 of the argument. */
void func_L08_004356A0(u8 *a0, void *a1)
{
    *(volatile TI128 *)*(u32 *)(a0 + 0x68) = *(TI128 *)a1;
}

/* func_L08_004356B8 is defined in L08_004356B8-g8.c. */


/* For every listed entity of A0's kind, while the mode word is 2 and the resident
   flag is set, hands it to func_0029F978 with the level block at 0x001B22E0 unless its
   byte 1 is set, and sets the vector at 0x001B2300 to 2.3. */
void func_L08_00435990(L08Thing *a0)
{
    L08Thing *e;
    s32 i;

    if (D_L08_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L08_001BD800.count; i++) {
        e = D_L08_001BD800.items[i];
        if (e->kind != a0->kind)
            continue;
        if (D_L08_001B22E0[1] != 0)
            continue;
        func_0029F978((u8 *)e, 0, D_L08_001B22E0);
        D_L08_001B2300[0] = 2.3f;
        D_L08_001B2300[1] = 2.3f;
        D_L08_001B2300[2] = 2.3f;
    }
}

#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define QUANTITY (*(s16 *)(D_001A7A00 + 0x1A))
#define PRICE (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2])

/* An interaction state machine at byte 0x20: offers an item for its price while
   the quantity at D_001A7A00+0x1A covers it, then buys the remaining quantity back
   at 1000 (10000 with the flag at D_001A7A00+0xA) each; afterwards aims the head at the hero. */
void func_L08_00435A78(u8 *self)
{
    float dest[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *data = *(u8 **)(self + 0x68);
    int n, active;
    float speed, yaw, pitch, angle;
    float blend = 0.3f;

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
            if (QUANTITY <= 0)
                func_002A7750(self, 6, -1);
            else
                func_002A7750(self, 7, -1);
        } else if (D_001395B8[0x1B]) {
            if (QUANTITY < PRICE)
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
            if (QUANTITY < PRICE)
                func_002A7750(self, 3, -1);
            else
                func_002A7750(self, 4, -1);
        }
        break;
    case 3:
        if (QUANTITY >= PRICE)
            func_002A7750(self, 4, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x27A4, PRICE, -1);
            func_L01_003246D0(self);
        }
        break;
    case 4:
        if (QUANTITY < PRICE)
            func_002A7750(self, 3, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x2796, PRICE, -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L08_001BFD00, 0x5A);
                QUANTITY -= PRICE;
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
            if (QUANTITY <= 0)
                func_002A7750(self, 6, -1);
            else
                func_002A7750(self, 7, -1);
        }
        break;
    case 6:
        if (QUANTITY > 0)
            func_002A7750(self, 7, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (!D_L08_001B1FA8)
                func_L01_00324550(0x27D0, 0, -1);
            else
                func_L01_00324550(0x27A7, -1);
            func_L01_003246D0(self);
        }
        break;
    case 7:
        if (QUANTITY <= 0)
            func_002A7750(self, 6, -1);
        else {
            n = D_001A7A00[0xA] ? 10 : 1;
            if (func_L01_003245E0(self, 10, 2.5f)) {
                n *= 1000;
                func_L01_00324550(0x2797, QUANTITY, QUANTITY * n, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L08_00435938();
                    D_001A79F8 += QUANTITY * n;
                    func_002E5DA0(0, 0, self, func_002A7820(13, 17));
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    func_002A7750(self, 8, -1);
                }
            }
        }
        break;
    case 8:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > 40 && H(self, 0x96) < 90 && H(self, 0x96) % 4 == 0)
            func_002E5DA0(0, 0, self, func_002A7820(13, 17));
        if (func_L01_003245E0(self, 10, 2.5f))
            func_L01_00324550(0x27D0, D_L08_001B1FA8, -1);
        else
            func_002A7750(self, 6, -1);
        break;
    }
    if (self[0x20]) {
        if (self[0x43] == 1 && func_00282978(data + 0x11E)) {
            H(data, 0x11E) = func_00283CF0(func_002A7878(1200, 2400));
            if (self[0x43] != 2)
                func_002A7470(self, 2, 0, 10);
        } else if ((self[0x60] & 2) && self[0x43] != 1)
            func_002A7470(self, 1, 0, 10);
    }
    speed = 0.02f;
    active = 0;
    if (self[0x43] == 1) {
        active = 1;
        if (func_00282E80((char *)self + 0x10, D_00189E20.x80) < 8 &&
            func_00283C80(F(self, 0xF8), func_00283248(D_00189E20.pos[0] - F(self, 0x10),
                                                       D_00189E20.pos[1] - F(self, 0x14))) < 1.57079649f) {
            if (func_00282DF0(D_00189E20.x110) > 0.01f)
                I(data, 0x114) = 120;
            else
                func_00282948(data + 0x114);
        } else if (I(data, 0x114)) {
            I(data, 0x114) = 0;
            qcopy(data + 0x100, D_00189E20.pos);
        }
        if (func_00282948(data + 0x118)) {
            I(data, 0x118) = func_00283CF0(func_002A7878(180, 300));
            angle = func_00283B98(F(self, 0xF8), func_002A7878(-90, 90) * 0.0174532942f);
            pitch = func_002A7878(0, 30) * 0.0174532942f;
            func_002AF000(data + 0x100, 6, angle, pitch);
            func_00282CC0(data + 0x100, data + 0x100, self + 0x10);
        }
        if (I(data, 0x114)) {
            qcopy(dest, D_00189E20.pos);
            speed = 0.04f;
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
    func_002AEC48(self, data, 0, speed, blend);
    func_002AEC48(self, data + 0x80, 1, speed, blend);
}

#undef I
#undef H
#undef F
#undef QUANTITY
#undef PRICE
