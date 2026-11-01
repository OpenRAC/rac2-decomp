#include "common.h"

typedef int Quad_Dobbo __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern void func_0029FCC0(char *, int, void *);
extern float func_00283CE0(int);
extern char *func_002BAE50(void *, void *, int, int, int, int, int, int);

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern void func_L08_00328BB0();

extern int func_L01_00321178(char *, char *);

extern int func_002B4FF0(char *, float *, float);

extern char *D_L09_001B285C __attribute__((sda));

extern char *D_L09_001FFFB560[];

extern void func_2EA110(char *p);

extern void func_31F500(char *a0, char *a1, s32 a2, f32 f12, f32 f13);

extern void func_322578(char *a0, char *a1, s32 a2, s32 a3, f32 f12);

extern void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3);

extern void func_L09_00408138(char *a0, char *a1, s32 a2, s32 a3, s32 a4);

extern s32 func_325E78(char *a0, s32 a1);

extern void func_318450(char *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                        f32 f12, f32 f13, f32 f14);

extern char D_L09_00189EA0[];

extern void func_L09_00406BA0(s32 a0, u8 a1);

extern char D_L09_001B9C30[];

extern f32 func_2EA578(char *a0, char *a1);

extern f32 func_2EA3E0(f32 x);

extern void func_2EACD0(char *a0, char *a1);

extern void func_L09_00408058(char *a0, s32 a1, s32 a2, s32 a3);

extern float func_2EB5C0(int a0);
extern int func_2EB698(float *a0, float f12);
extern float func_316AC0(float lo, float hi);
extern void func_30D8D0(char *a0, int a1, float *a2);
extern char *func_32E560(float *a0, float *a1, int a2, int a3, int t0, int t1, int t2, int t3);
extern int func_2EB5D0(float a);

/* func_L09_0040AC48 is in L09_0040AC48-g8.c. */

/* func_L09_0040B0C8 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_0041D650 is in L09_0041D650-g8.c. */

/* func_L09_00421B80 is in L09_003FEA48-zp-g8.c. */

extern int func_316A68(int a, int b);
extern void func_316958(char *a0, int a1, int a2);
extern int func_2EA0E0(char *p);
extern void func_2E8450(char *a0, float *a1, float *a2, int a3, int a4, float f12, float f13, float f14, float f15, float f16);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.c (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.c. */

void func_L09_003FECF0(char *a0) {
    EffectVector a;
    EffectVector b;
    EffectVector c;
    EffectVector w;
    int i;
    int j;
    char *p;

    qcopy(a.value, a0 + 0x10);
    a.value[3] = 6.0f;
    if (func_2EB698(a.value, func_2EB5C0(*(s16 *)(a0 + 0x32))) == -1)
        return;
    for (i = 12; i < 14; i++) {
        w.bits = 0;
        w.value[2] = -(func_316AC0(3.5f, 4.5f) * 0.016666668f);
        c.bits = w.bits;
        for (j = 0; j < 2; j++) {
            func_30D8D0(a0, i, b.value);
            b.value[2] += func_2EB5C0(j) * 0.015f + 0.5f;
            if (j & 1)
                p = func_32E560(b.value, c.value, 0x77FF0000, 0x00FF0060, 0x13, 200, -100, 1);
            else
                p = func_32E560(b.value, c.value, 0x77FF0060, 0x00FF0000, 0x15, 300, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + func_2EB5D0(0.0f);
            p = func_32E560(b.value, c.value, 0x77FFFFFF, 0x00FF0000, 0xC, 100, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + func_2EB5D0(0.0f);
        }
    }
}

/* func_L09_003FEF00 is in L09_003FEA48-patrol-g8.c. */

/* func_L09_00402D50 is in L09_00402D50-g8.c. */

/* Level 09 helpers. */
void func_L09_00403080(char *a0) {
    s16 *p;
    s32 v;
    char *a1;
    char *a2;
    if (*(u8 *)(a0 + 0x21) == 0xFF) {
        return;
    }
    v = (s32)D_L09_001FFFB560[*(u8 *)(a0 + 0x21)];
    if (v == 0) {
        return;
    }
    p = (s16 *)v;
    a2 = D_L09_001B285C;
    do {
        a1 = a2 + ((*(u16 *)p & 0x7FFF) << 8);
        if (*(s8 *)(a1 + 0x20) >= 0) {
            if (*(s16 *)(a1 + 0xAA) == 0xD57) {
                *(u16 *)(*(char **)(a1 + 0x68) + 0x270) = 1;
            }
        }
    } while (*(s16 *)p++ >= 0);
}

extern s32 func_002A8508(s32 a0, s32 a1);

void func_L09_00403100(char *a0, s32 a1) {
    char *s1 = a0;
    char *base;
    u16 *p;
    char *rec;
    char *sub;

    if (a1 == 0) {
        return;
    }
    func_L09_00403080(a0);
    if ((u32)(a1 - 4) >= 2) {
        return;
    }
    if (*(u8 *)(s1 + 0x21) == 0xFF) {
        return;
    }
    if (func_002A8508(*(u8 *)(s1 + 0x21), -1) < 2) {
        return;
    }
    base = D_L09_001B285C;
    p = (u16 *)D_L09_001FFFB560[*(u8 *)(s1 + 0x21)];
    do {
        rec = base + ((*p & 0x7FFF) << 8);
        if (*(s16 *)(rec + 0xAA) == 0xD57) {
            sub = *(char **)(rec + 0x68);
            if (*(s16 *)(sub + 0x26A) == 0) {
                *(s16 *)(sub + 0x26A) = 1;
                return;
            }
        }
    } while ((s16)*p++ >= 0);
}

void func_L09_00403378(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    if (*(u8 *)(a0 + 0x20) == 9) {
        return;
    }
    *(f32 *)(a0 + 0x18) = *(f32 *)(p + 0x288);
}

/* func_L09_00403270 reads small data through $gp, so it is defined in
   L09_003FEA48-g8.c. */

INCLUDE_ASM("asm/levels", func_L09_00403398);

/* func_L09_00403700: 152 bytes, one register off - the loop's trip test compares
   into $v0 where retail compares into $v1.  Deposited in
   nonmatching/levels/func_L09_00403700.c. */

/* func_L09_00403798 is in L09_00403798-g8.c. */

/* func_L09_00404C50 is in L09_00404C50-g8.c. */

void func_L09_00404F90(char *a0, char *a1, s32 a2) {
    char *p = *(char **)(a0 + 0x68);
    if (a2 == 0) {
        func_L01_00321178(a0, a1);
    } else {
        func_002B4FF0(a0, (float *)a1, *(f32 *)(p + 0x33C));
    }
}

void func_L09_00404FC8(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u16 n;
    func_2EA110(s1 + 0x330);
    func_2EA110(s1 + 0x332);
    n = *(u16 *)(a0 + 0x96);
    if (n < 0xFFFF) {
        *(u16 *)(a0 + 0x96) = n + 1;
    }
    func_31F500(a0, s1 + 0x280, 0, 0.03f, 0.3f);
    func_322578(a0, s1 + 0x360, 0, 1, 1.5f);
}

void func_L09_00405060(char *a0) {
    s16 *p;
    s32 v;
    char *a1;
    char *a2;
    if (*(u8 *)(a0 + 0x21) == 0xFF) {
        return;
    }
    v = (s32)D_L09_001FFFB560[*(u8 *)(a0 + 0x21)];
    if (v == 0) {
        return;
    }
    p = (s16 *)v;
    a2 = D_L09_001B285C;
    do {
        a1 = a2 + ((*(u16 *)p & 0x7FFF) << 8);
        if (*(s8 *)(a1 + 0x20) >= 0) {
            if (*(s16 *)(a1 + 0xAA) == 0xD90) {
                *(u16 *)(*(char **)(a1 + 0x68) + 0x336) = 1;
            }
        }
    } while (*(s16 *)p++ >= 0);
}

/* Defined in L09_004050E0.c. */

/* func_L09_004052F8 is defined in L09_003FEA48-g8.c (it reads the group count through $gp). */

/* func_L09_00405490 is defined in L09_003FEA48-g8.c (it reads small data through $gp). */

/* func_L09_00405610 is defined in L09_00405610-g8.c (small data through $gp, and its own .rodata). */

void func_L09_00406BA0(s32 a0, u8 a1) {
    char *v1;
    if (a0 == -1) {
        return;
    }
    v1 = D_L09_001B285C;
    v1 += a0 << 8;
    if (v1 == 0) {
        return;
    }
    if (*(u8 *)(v1 + 0x20) == 0xFE) {
        return;
    }
    if (*(u8 *)(v1 + 0x20) == 0xFD) {
        return;
    }
    if (*(s16 *)(v1 + 0xAA) == 0x102 || *(s16 *)(v1 + 0xAA) == 0xDE0) {
        *(u8 *)(v1 + 0x95) = a1;
    }
}

void func_L09_00406C68(s32 a0) {
    if (a0 == -1) {
        return;
    }
    func_L08_00328BB0(a0);
}

/* func_L09_00406BF8: 112 bytes against retail's 108, one saved register too many.
   Deposited in nonmatching/levels/func_L09_00406BF8.c. */

void func_L09_00406C90(char *a0) {
    char *a1 = *(char **)(a0 + 0x68);
    s32 v1 = *(s32 *)(a1 + 0x5C);
    if (v1 == -1) {
        return;
    }
    *(u8 *)((char *)((v1 << 8) + (s32)D_L09_001B285C) + 0xBC) = 1;
    *(s32 *)(a1 + 0x5C) = -1;
}

/* func_L09_00406CC0 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406E78 is defined in L09_003FEA48-g8.c (it reads the object table through $gp). */

/* func_L09_00406FC8 is in L09_00406FC8-g8.c. */

/* Sets an entity's colour key, or hands an off-kind entity to the shared body. */
void func_L09_00408138(char *a0, char *a1, s32 a2, s32 a3, s32 a4)
{
    u8 c;
    s16 kind;
    char *p;

    if (a1 == 0) {
        return;
    }
    c = *(u8 *)(a1 + 0x20);
    if (c == 0xFE) {
        return;
    }
    if (c == 0xFD) {
        return;
    }
    kind = *(s16 *)(a1 + 0xAA);
    if (kind == 0xD0F) {
        p = *(char **)(a1 + 0x68);
        *(u8 *)(p + 0x31C) = a2;
        c = *(u8 *)(a1 + 0x30);
        if (c != 0xFF) {
            *(u8 *)(p + 0x31E) = c;
        }
        if (a2 != 0) {
            *(u8 *)(a1 + 0x30) = 0xFF;
        }
        return;
    }
    if (kind == 0xD09 || kind == 0xCEA) {
        func_L09_00408058(a1, 0, a3, a4);
        return;
    }
    if (kind == 0xDE0) {
        *(u8 *)(a1 + 0x95) = *(u8 *)(a0 + 0x95);
        return;
    }
    func_L09_00408058(a1, a2, a3, a4);
}

/* Hands the record's colour key to every entry the index names, negating the
   three offsets when the caller asks for it. */
void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3) {
    char *v1 = a2;
    char *p = D_L09_001B285C + (a1 << 8);

    if (p == 0) {
        return;
    }
    if (a3 != 0) {
        func_L09_00408138(a0, p, *(s8 *)(v1 + 0xBC), *(s8 *)(v1 + 0xBD),
                          *(s8 *)(v1 + 0xBF));
    } else {
        func_L09_00408138(a0, p, -*(s8 *)(v1 + 0xBC), -*(s8 *)(v1 + 0xBD),
                          -*(s8 *)(v1 + 0xBF));
    }
}

void func_L09_00408250(char *a0, char *a1, s32 a2, s32 a3) {
    s16 *p;
    p = (s16 *)D_L09_001FFFB560[a2];
    if (p == 0) {
        return;
    }
    do {
        func_L09_004081F0(a0, *(u16 *)p & 0x7FFF, a1, a3);
    } while (*(s16 *)p++ >= 0);
}

/* func_L09_004082D0 is in L09_004082D0.c. */

/* func_L09_00408478 reads D_001A7AF8[k] and stores D_L09_001B25A0[2] as elements of sda arrays:
 * (mem (const (plus sym k))) is a two-word move, so these stay out of delay slots. */
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
extern void func_L00_002B9D60(char *, char *, int, int);
extern int func_002B38B8(char *);
extern void func_002F5CC8(void);
extern int func_L01_003245E0(char *, int, float);
extern void func_L01_00324550(int, int, int);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern void func_L06_0039A2F0(char *, int, char *, int, char *);
extern void func_002A0430(int);
extern void func_002DF3F8(char *, char *);
extern void func_0029B3E0(int, int);
void func_L09_00408478(u8 *obj)
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
            func_L00_002B9D60(entry + 0x30, entry + 0x70, 0, 1);
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
                func_002F5CC8();
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
            func_L00_002B9D60(entry + 0x30, entry + 0x70, 0, 1);
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
            func_L01_00324550(0x27d1, D_001A7AF8[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
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
            func_L01_00324550(0x27d2, D_001A7AF8[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
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
        func_002AF0A8(10);
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

void func_L09_004091C8(char *obj)
{
    float pos[4];
    float vel[4];
    float initial[4];
    int i;
    *(Quad_Dobbo *)initial = 0;
    initial[2] = -(func_002A7878(3.5f, 4.5f) * 0.0166666675f);
    *(Quad_Dobbo *)vel = *(Quad_Dobbo *)initial;
    for (i = 0; i < 2; i++) {
        func_0029FCC0(obj, 2, pos);
        pos[2] += func_00283CE0(i) * 0.015f;
        if (i & 1)
            func_002BAE50(pos, vel, 0x77FF0000, 0xFF0060, 17, 150, -100, 1);
        else
            func_002BAE50(pos, vel, 0x77FF0060, 0xFF0000, 19, 220, -100, 1);
        func_002BAE50(pos, vel, 0x77FFFFFF, 0xFF0000, 10, 80, -80, 1);
    }
}

/* func_L09_00409308 is in L09_00409308.c. */

/* func_L09_0040A2E8 is in L09_0040A2E8-g8.c. */

void func_L09_0040B008(char *a0) {
    char *s1 = a0;
    char *s2 = s1 + 0xC0;
    char *s3 = *(char **)(s1 + 0x68);
    f32 a, b;
    *(s32 *)(s3 + 0x8) = 0;
    *(s32 *)(s3 + 0xC) = 0;
    *(f32 *)(s3 + 0x0) = 0.2f;
    *(f32 *)(s3 + 0x4) = 0.2f;
    func_2EACD0(s2, s1 + 0xF0);
    a = func_2EA3E0(func_2EA578(s2, D_L09_001B9C30));
    b = func_2EA3E0(func_2EA578(s1 + 0xD0, D_L09_001B9C30));
    if (b < a) {
        *(s32 *)(s3 + 0x14) = 1;
    } else {
        *(s32 *)(s3 + 0x14) = 0;
    }
}

void func_L09_00421D60(char *a0) {
    char *s2 = *(char **)(a0 + 0x68);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(int *)s2 = func_316A68(0, 0xF0);
        func_316958(a0, 1, -1);
        break;
    case 1:
        if (func_2EA0E0(s2)) {
            if (*(u8 *)(a0 + 0x31)) {
                EffectVector a;
                EffectVector b;
                a.bits = 0;
                b.bits = 0;
                a.value[1] = -0.033333335f;
                a.value[2] = 0.016666668f;
                b.value[2] = 2.0f;
                func_2E8450(a0, b.value, a.value, func_316A68(3, 7), 0, 0.0f, 0.033333335f, 0.7f, 15.0f, 1.0f);
            }
            *(int *)s2 = func_316A68(0x78, 0xF0);
        }
        break;
    }
}
