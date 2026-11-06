#include "common.h"

/* func_PAL_L19_00430C78, the PAL copy of func_L19_0042B058: the same C, where the text ids move to 0x132E-0x1334,
   the timers scale to 50 Hz, the two final speeds scale by 1.44, and the price is taken after the movie (states 3
   and 6) instead of at the purchase (states 2 and 5). */
extern int D_L19_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));

extern int func_L19_0042A860(void);
extern void func_L19_0042AF70(void *);
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

#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
/* The two prices in the level's table, each with a second value used when the flag is set. */

void func_PAL_L19_00430C78(u8 *self)
{
    u8 *data = *(u8 **)(self + 0x68);
    u8 *companion;
    int remaining;

    func_L19_0042AF70(self);
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
                if (D_001A79F8[9] < 1)
                    func_002A7750(self, 7, -1);
                else
                    func_002A7750(self, 8, -1);
            } else if (D_001A79F8[9] < (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]))
                func_002A7750(self, 4, -1);
            else
                func_002A7750(self, 5, -1);
            func_L01_003128C0(self);
        } else if (D_00139800 & 0x1000000) {
            func_L19_0042A860();
            H(self, 0x34) = (H(self, 0x34) & 0xFFBE) | 0x1000;
            I(self, 0x98) = I(*(u8 **)(self + 0x24), 0x10);
            if (D_001A79F8[9] < (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]))
                func_002A7750(self, 1, -1);
            else
                func_002A7750(self, 2, -1);
        } else {
            I(self, 0x98) = 0;
            H(self, 0x34) = (H(self, 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 1:
        if (D_001A79F8[9] >= (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]))
            func_002A7750(self, 2, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x132E, (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]), -1);
            func_L01_003246D0(self);
        }
        break;
    case 2:
        if (D_001A79F8[9] < (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]))
            func_002A7750(self, 1, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x132F, (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]), -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L19_001BFC40, 0x9A);
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
            D_001A79F8[9] -= (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14]);
            if (self[0x21] != 0xFF)
                func_002A8598(self[0x21], 1);
            if (I(data, 0x80) != -1) {
                func_0029F338(D_L19_001B2A1C + I(data, 0x80) * 0x100);
                I(data, 0x80) = -1;
            }
            func_0029B3E0(0, -1);
            if ((u32)D_001A79F8[9] <= (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]))
                func_002A7750(self, 4, -1);
            else
                func_002A7750(self, 5, -1);
        }
        break;
    case 4:
        if (D_001A79F8[9] >= (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]))
            func_002A7750(self, 5, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x1330, (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]), -1);
            func_L01_003246D0(self);
        }
        break;
    case 5:
        if (D_001A79F8[9] < (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]))
            func_002A7750(self, 4, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            func_L01_00324550(0x1331, (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]), -1);
            func_L01_003246D0(self);
            if (D_00138324 & 0x10) {
                func_00288AA0(D_L19_001BFC40, 0x99);
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
            D_001A79F8[9] -= (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16]);
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
            if (D_001A79F8[9] < 1)
                func_002A7750(self, 7, -1);
            else
                func_002A7750(self, 8, -1);
        }
        break;
    case 7:
        if (D_001A79F8[9] > 0)
            func_002A7750(self, 8, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (!D_L19_001B1FB8[0])
                func_L01_00324550(0x1334, 0, -1);
            else
                func_L01_00324550(0x1332, -1);
            func_L01_003246D0(self);
        }
        break;
    case 8:
        if (D_001A79F8[9] < 1)
            func_002A7750(self, 7, -1);
        else if (func_L01_003245E0(self, 10, 2.5f)) {
            if (func_00288D58()) {
                func_L01_00324550(0x1333, D_001A79F8[9], D_001A79F8[9] * 30000, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L19_0042A860();
                    D_001A79F8[0] += D_001A79F8[9] * 30000;
                    D_001A79F8[9] = 0;
                    func_L00_0030C710(((s32)(180) * 5 + 2) / 6);
                    func_002E5DA0(0, 0, (char *)self, func_002A7820(13, 17));
                    func_002A7750(self, 9, -1);
                }
            } else {
                func_L01_00324550(0x1333, D_001A79F8[9], D_001A79F8[9] * 3000, -1);
                func_L01_003246D0(self);
                if (D_00138324 & 0x10) {
                    func_L19_0042A860();
                    D_001A79F8[0] += D_001A79F8[9] * 3000;
                    D_001A79F8[9] = 0;
                    func_L00_0030C710(((s32)(180) * 5 + 2) / 6);
                    func_002A7750(self, 9, -1);
                }
            }
        }
        break;
    case 9:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > ((s32)(40) * 5 + 2) / 6 && H(self, 0x96) < ((s32)(90) * 5 + 2) / 6 && H(self, 0x96) % (((s32)(4) * 5 + 2) / 6) == 0)
            func_002E5DA0(0, 0, (char *)self, func_002A7820(13, 17));
        if (func_L01_003245E0(self, 10, 2.5f))
            func_L01_00324550(0x1334, D_L19_001B1FB8[0], -1);
        else
            func_002A7750(self, 7, -1);
        break;
    }
    if (D_001A7A40[0])
        *(float *)(data + 0x70) = 2.75f;
    func_002AEC48(self, data, 0, 0.028800001f, 0.43200004f);
}
