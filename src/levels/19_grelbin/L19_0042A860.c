#include "common.h"

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L19Thing {
    u8 pad[0xAA];
    s16 kind;
} L19Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L19Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L19Thing *items[1];     /* bounded by count */
} L19Group;

extern L19Group D_L19_001BD740;
extern s32 D_L19_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L19_001B22E0[] __attribute__((sda));
extern f32 D_L19_001B2300[] __attribute__((sda));

extern void func_0029F978(u8 *, u32, u8 *);
extern int func_L19_0042A860(void);
extern int func_002F5D10(void);
extern void func_002A7750(void *, int, int);
extern void func_L01_003128C0(void *);
extern int func_L01_003245E0(void *, int, float);
extern void func_L01_00324550(int, ...);
extern void func_L01_003246D0(void *);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern void func_002A8598(int, int);
extern void func_0029F338(void *);
extern int func_0029B3E0(int, int);
extern void func_002B0A18(int, int);
extern int func_00288E18(int, int);
extern int func_00288D58(void);
extern void func_L00_0030C710(int);
extern int func_002A7820(int, int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_002AEC48(void *, void *, void *, float, float);

extern int D_L19_001B2508[] __attribute__((sda));
extern int D_L19_001B2724[] __attribute__((sda));
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern int D_L19_001B1FB8[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern u8 D_L19_001A7C80[] __attribute__((sda));
extern u8 D_001395B8[];
extern u32 D_00139800, D_00138324;
extern int D_L19_0028E950[];
extern u8 D_L19_001BFC40[];

void func_L19_0042A8B8(void)
{
    L19Thing *e;
    s32 i;

    if (D_L19_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L19_001BD740.count; i++) {
        e = D_L19_001BD740.items[i];
        if (e->kind != 0xE3E)
            continue;
        if (D_L19_001B22E0[1] != 0)
            continue;
        func_0029F978((u8 *)e, 0, D_L19_001B22E0);
        D_L19_001B2300[0] = 1.9f;
        D_L19_001B2300[1] = 1.9f;
        D_L19_001B2300[2] = 1.9f;
    }
}

/* func_L19_0042A9A0 is in L19_0042A9A0.c. */

void func_L19_0042AF70(L19Thing *a0)
{
    L19Thing *e;
    s32 i;

    if (D_L19_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L19_001BD740.count; i++) {
        e = D_L19_001BD740.items[i];
        if (e->kind != a0->kind)
            continue;
        if (D_L19_001B22E0[1] != 0)
            continue;
        func_0029F978((u8 *)e, 0, D_L19_001B22E0);
        D_L19_001B2300[0] = 1.9f;
        D_L19_001B2300[1] = 1.9f;
        D_L19_001B2300[2] = 1.9f;
    }
}

#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define QUANTITY D_001A79F8[9]
/* The two prices in the level's table, each with a second value used when the flag is set. */
#define PRICE_A (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14])
#define PRICE_B (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16])

/* An interaction state machine at byte 0x20, a larger cousin of func_L08_00435A78: offers two
   purchases for the quantity at D_001A79F8[9] (states 1-2 and 4-5, each followed by a movie in
   state 3 or 6), then buys the remaining quantity back at 30000 or 3000 each (states 7-8). */
void func_L19_0042B058(u8 *self)
{
    u8 *data = *(u8 **)(self + 0x68);
    u8 *companion;
    int remaining;

    func_L19_0042AF70((L19Thing *)self);
    if (D_L19_001B2508[0] == 5)
        func_L19_0042A860();
    switch (self[0x20]) {
    case 0:
        if (func_002F5D10())
            break;
        if (D_00139800 & 0x4000000) {
            H(self, 0x34) = (H(self, 0x34) & 0xFFBE) | 0x1000;
            I(self, 0x98) = I(*(u8 **)(self + 0x24), 0x10);
            if (D_001395B8[0x89]) {
                func_L19_0042A860();
                if (QUANTITY < 1)
                    func_002A7750(self, 7, -1);
                else
                    func_002A7750(self, 8, -1);
            } else if (QUANTITY < PRICE_B)
                func_002A7750(self, 4, -1);
            else
                func_002A7750(self, 5, -1);
            func_L01_003128C0(self);
        } else if (D_00139800 & 0x1000000) {
            func_L19_0042A860();
            H(self, 0x34) = (H(self, 0x34) & 0xFFBE) | 0x1000;
            I(self, 0x98) = I(*(u8 **)(self + 0x24), 0x10);
            if (QUANTITY < PRICE_A)
                func_002A7750(self, 1, -1);
            else
                func_002A7750(self, 2, -1);
        } else {
            I(self, 0x98) = 0;
            H(self, 0x34) = (H(self, 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 1:
        if (QUANTITY >= PRICE_A)
            func_002A7750(self, 2, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x27DC, PRICE_A, -1);
            func_L01_003246D0(self);
        }
        break;
    case 2:
        if (QUANTITY < PRICE_A)
            func_002A7750(self, 1, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x27DD, PRICE_A, -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L19_001BFC40, 0x9A);
                QUANTITY -= PRICE_A;
                func_00288BE8(D_L19_001BFC40);
                func_002A7750(self, 3, -1);
            }
        }
        break;
    case 3:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x80) != -1 && D_L19_001A8F00[0] == 2) {
            companion = D_L19_001B2A1C;
            H(companion + I(data, 0x80) * 0x100, 0x34) |= 1;
            (companion + I(data, 0x80) * 0x100)[0x31] = 0;
        }
        if (!func_002F5D10()) {
            D_L19_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (self[0x21] != 0xFF)
                func_002A8598(self[0x21], 1);
            if (I(data, 0x80) != -1) {
                func_0029F338(D_L19_001B2A1C + I(data, 0x80) * 0x100);
                I(data, 0x80) = -1;
            }
            func_0029B3E0(0, -1);
            if ((u32)QUANTITY <= PRICE_B)
                func_002A7750(self, 4, -1);
            else
                func_002A7750(self, 5, -1);
        }
        break;
    case 4:
        if (QUANTITY >= PRICE_B)
            func_002A7750(self, 5, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x27DE, PRICE_B, -1);
            func_L01_003246D0(self);
        }
        break;
    case 5:
        if (QUANTITY < PRICE_B)
            func_002A7750(self, 4, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x27DF, PRICE_B, -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L19_001BFC40, 0x99);
                QUANTITY -= PRICE_B;
                func_00288BE8(D_L19_001BFC40);
                func_002A7750(self, 6, -1);
            }
        }
        break;
    case 6:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (!func_002F5D10()) {
            D_L19_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (self[0x21] != 0xFF)
                func_002A8598(self[0x21], 1);
            D_001395B8[0x89] = 1;
            func_002B0A18(0x1294, -1);
            remaining = 2;
            if (D_001395B8[0x84])
                remaining--;
            if (D_001395B8[0x86])
                remaining--;
            if (remaining > 0)
                func_00288E18(0xA0F, 0x66);
            else
                func_00288E18(0xA10, 0x67);
            func_0029B3E0(0, -1);
            if (QUANTITY < 1)
                func_002A7750(self, 7, -1);
            else
                func_002A7750(self, 8, -1);
        }
        break;
    case 7:
        if (QUANTITY > 0)
            func_002A7750(self, 8, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (!D_L19_001B1FB8[0])
                func_L01_00324550(0x27E2, 0, -1);
            else
                func_L01_00324550(0x27E0, -1);
            func_L01_003246D0(self);
        }
        break;
    case 8:
        if (QUANTITY < 1)
            func_002A7750(self, 7, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (func_00288D58()) {
                func_L01_00324550(0x27E1, QUANTITY, QUANTITY * 30000, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L19_0042A860();
                    D_001A79F8[0] += QUANTITY * 30000;
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    func_002E5DA0(0, 0, (char *)self, func_002A7820(13, 17));
                    func_002A7750(self, 9, -1);
                }
            } else {
                func_L01_00324550(0x27E1, QUANTITY, QUANTITY * 3000, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L19_0042A860();
                    D_001A79F8[0] += QUANTITY * 3000;
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    func_002A7750(self, 9, -1);
                }
            }
        }
        break;
    case 9:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > 40 && H(self, 0x96) < 90 && H(self, 0x96) % 4 == 0)
            func_002E5DA0(0, 0, (char *)self, func_002A7820(13, 17));
        if (func_L01_003245E0(self, 10, 2.5f))
            func_L01_00324550(0x27E2, D_L19_001B1FB8[0], -1);
        else
            func_002A7750(self, 7, -1);
        break;
    }
    if (D_001A7A40[0])
        *(float *)(data + 0x70) = 2.75f;
    func_002AEC48(self, data, 0, 0.02f, 0.3f);
}
