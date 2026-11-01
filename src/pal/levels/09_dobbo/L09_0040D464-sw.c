#include "include_asm.h"

#include "common.h"
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001395D7[];
extern u8 D_001395D8[];
typedef struct { char pad[0x5c]; int state; int flags; } DobboPlayerFlags;
extern DobboPlayerFlags D_00139768;
extern char D_00189EA0[];
extern u8 D_0019B2E8[];
extern int D_00138324;
extern char D_L09_001B1458[], D_L09_001B1480[], D_L09_001B1498[], D_L09_001B14C0[], D_L09_001B14E8[], D_L09_001B14F8[], D_L09_001B1518[], D_L09_001B1540[];
extern char D_L09_001BFC00[], D_L09_0021DDE0[];
extern int D_001A79F8 SDATA(D_001A79F8);
extern int D_001A79F0 SDATA(D_001A79F0);
extern char *D_L09_001B294C SDATA(D_L09_001B294C);
extern int D_L09_001A8F00[] __attribute__((sda));
extern int D_L09_001B25A0[] __attribute__((sda));
extern int D_L09_0028E350[];
extern int D_L09_0028E360, D_L09_0028E364;
extern void func_0026FEB8(char *, ...);
extern void func_002A7750(char *, int, int);
extern void func_L01_003128C0(char *);
extern int func_002ACBC8(char *, int);
extern int func_00288AA0(char *, int);
extern void func_L01_003246D0(char *);
extern void func_00288BE8(char *);
extern int func_002F5D10(void);
extern void func_PAL_L00_002B9CD8(char *, char *, int, int);
extern int func_002B38B8(char *);
extern void func_PAL_002F6C18(void);
extern int func_L01_003245E0(char *, int, float);
extern void func_L01_00324550(int, int, int);
extern void func_002AD7B8(int);
extern void func_PAL_002AFC10(int);
extern void func_L06_0039A2F0(char *, int, char *, int, char *);
extern void func_002A0430(int);
extern void func_002DF3F8(char *, char *);
extern void func_0029B3E0(int, int);

void func_PAL_L09_0040D464(u8 *obj)
{
    char *p = *(char **)(obj + 0x68);
    char *entry;
    int startCurrency;
    int offerCurrency;
    int currency;
    int balance;
    int remaining;

    switch (obj[0x20]) {
    case 0:
        if (D_001A7AF8[0xDA]) {
            func_002A7750(obj, 9, -1);
            break;
        }
        if (D_00139768.flags & 1) {
            func_0026FEB8(D_L09_001B1458);
            startCurrency = D_001A79F8;
            if (D_001A7AF8[0x197]) {
                if (startCurrency < D_L09_0028E364)
                    goto start_six;
                else
                    func_002A7750(obj, 7, 1);
            } else {
                if (startCurrency < D_L09_0028E360) {
                start_six:
                    func_002A7750(obj, 6, 1);
                } else
                    func_002A7750(obj, 7, 1);
            }
        } else if (D_00139768.state < 0) {
            func_0026FEB8(D_L09_001B1480);
            if (D_001395D7[0]) {
                obj[0x30] = 0xff;
                func_0026FEB8(D_L09_001B1498);
                func_002A7750(obj, 4, 1);
            } else {
                obj[0x30] = 0xff;
                func_0026FEB8(D_L09_001B14C0);
                func_002A7750(obj, 3, 0);
            }
        } else {
            func_0026FEB8(D_L09_001B14E8);
            func_002A7750(obj, 1, 0);
        }
        func_L01_003128C0(obj);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, *(int *)p)) {
            func_0026FEB8(D_L09_001B14F8);
            if (func_00288AA0(D_L09_001BFC00, 0x5f)) {
                func_L01_003246D0(obj);
                func_00288BE8(D_L09_001BFC00);
                func_002A7750(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (func_002F5D10())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = D_L09_001B294C;
            entry += *(int *)(p + 8) << 7;
            func_PAL_L00_002B9CD8(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        func_002A7750(obj, 3, -1);
        break;
    case 3:
        obj[0x30] = 0xff;
        if (func_002B38B8(obj)) {
            D_001395D7[0] = 1;
            func_002A7750(obj, 4, 1);
        }
        break;
    case 4:
        obj[0x30] = 0xff;
        if (func_002ACBC8(D_00189EA0, *(int *)p)) {
            func_0026FEB8(D_L09_001B1518);
            if (func_00288AA0(D_L09_001BFC00, 0x60)) {
                func_00288BE8(D_L09_001BFC00);
                func_PAL_002F6C18();
                func_002A7750(obj, 5, -1);
            }
        }
        break;
    case 5:
        obj[0x30] = 0x40;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        D_L09_001B25A0[2] = 1;
        if (func_002F5D10())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = D_L09_001B294C;
            entry += *(int *)(p + 8) << 7;
            func_PAL_L00_002B9CD8(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        D_001395D8[0] = 1;
        offerCurrency = D_001A79F8;
        if (D_001A7AF8[0x197]) {
            if (offerCurrency < D_L09_0028E364)
                goto offer_six;
            else
                func_002A7750(obj, 7, -1);
        } else {
            if (offerCurrency < D_L09_0028E360) {
            offer_six:
                func_002A7750(obj, 6, -1);
            } else
                func_002A7750(obj, 7, -1);
        }
        break;
    case 6:
        currency = D_001A79F8;
        if (D_001A7AF8[0x197]) {
            if (D_L09_0028E350[5] < currency)
                goto change_seven;
        } else {
            if (D_L09_0028E350[4] < currency) {
            change_seven:
                func_002A7750(obj, 7, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 2.5f)) {
            func_L01_00324550(0x1323, D_001A7AF8[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            func_L01_003246D0(obj);
        }
        break;
    case 7:
        currency = D_001A79F8;
        if (D_001A7AF8[0x197]) {
            if (currency < D_L09_0028E350[5])
                goto change_six;
        } else {
            if (currency < D_L09_0028E350[4]) {
            change_six:
                func_002A7750(obj, 6, -1);
                break;
            }
        }
        if (func_L01_003245E0(obj, 10, 2.5f)) {
            func_L01_00324550(0x1324, D_001A7AF8[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            func_L01_003246D0(obj);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L09_001BFC00, 10)) {
                func_0026FEB8(D_L09_001B1540);
                balance = D_001A79F8;
                if (D_001A7AF8[0x197])
                    remaining = balance - D_L09_0028E350[5];
                else
                    remaining = balance - D_L09_0028E350[4];
                D_001A79F8 = remaining;
                func_00288AA0(D_L09_001BFC00, 0x61);
                func_00288AA0(D_L09_001BFC00, 0x62);
                func_00288BE8(D_L09_001BFC00);
                func_002A7750(obj, 8, -1);
            }
        }
        break;
    case 8:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (func_002F5D10())
            break;
        D_L09_001B25A0[2] = 0;
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        func_002AD7B8(10);
        func_PAL_002AFC10(10);
        func_002A7750(obj, 9, -1);
        func_L06_0039A2F0(obj + 0x20, 1, obj, 1, D_L09_0021DDE0);
        if (obj[0xb0] != 0xff) {
            if (!(D_0019B2E8[obj[0xb0] + (D_001A79F0 << 4)] & 0x80))
                func_002A0430(obj[0xb0]);
            func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
        } else
            func_0029B3E0(0, -1);
        break;
    }
}
