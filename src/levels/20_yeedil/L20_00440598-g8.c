#include "common.h"
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E80(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern f32 func_00283C80(f32, f32);
extern void func_00285788(int, int);
extern void func_00285828(int, int, int, int);
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern int func_00288FB8(int);
extern void func_0029F338(void *);
extern float func_0029F530(char *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_002A89A8(void *, int, float);
extern int func_002A8C28(void *, void *, s32, s32, s32, s32, f32, f32, f32);
extern float func_002AA2E8(float *, float, float);
extern void func_002AA800(float *, int, f32, f32);
extern void func_002ACB48(float *, float);
extern int func_002ACBC8(void *, int);
extern s32 func_002AEB60(u8 *, f32);
extern int func_002B3868(u8 *);
extern int func_002B49E0(int, int, int, int, int);
extern void func_002BDBC0(char *, char *, int, int, int, float);
extern void func_002DF3F8(void *, void *);
extern void func_002E59F8(s32);
extern int func_002E5CF8(int, int, char *);
extern void func_L00_002B30E8(void);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_002F3478(void);
extern int func_L01_00322288(void *, float);
extern void func_L20_0036E720(void);
extern void func_L20_0039DE88(char *arg0);
extern void func_L20_0039F210(char *arg0, char *arg1, int arg2);
extern void func_L20_00442140(char *arg0);
extern void func_L20_004424A0(char *actor);
extern void func_L20_00442740(char *arg0, float f);
extern void func_L20_004427C8(char *arg0, char *arg1, float f);
extern void func_L20_00442C10(char *arg0);
extern void func_L20_00442F30(char *arg0);
extern int func_L20_00443508(char *arg0, char *arg1);
extern char * func_L20_00443790(char *arg0, int arg1, char *arg2);
extern void func_L20_00443B60(char *, char *, char *, float *);
extern void func_L20_00444088(char *arg0);
extern void func_L20_00444AA8(char *arg0, float *arg1);
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; } Hero;
extern u8 D_00189E20[];

extern void func_L20_00441CB8(char *);
extern int func_L20_004421A8(char *);
extern int func_L20_00442550(char *);
extern void func_L20_00442F80(char *);
extern void func_L20_00442CD8(char *);
extern void func_L20_004435A0(char *);
extern void func_L20_00443A10(char *, char *);
extern int func_L20_00443CF0(char *);
extern void func_L20_00443D58(char *);
extern void func_L20_00443DF0(char *);
extern int func_L20_00444018(char *);
extern void func_L20_004441D8(char *);
extern int func_L20_00440398(int);
extern char *func_L20_0039EEC8(char *, char *);
extern char *func_L20_0043F318(char *, char *, int, float, int, int);
extern void func_L20_00440570(void);
extern s32 D_L20_001A8F00[] __attribute__((sda));
/* The same word, read through $gp in some places and absolutely in others. */
extern s32 D_L20_001A8F00_gp SDATA(D_L20_001A8F00);
extern s32 D_L20_001A8F08 __attribute__((sda));
extern f32 D_L20_001B2030 __attribute__((sda));
extern f32 D_L20_001B2038 __attribute__((sda));
extern f32 D_L20_001B2040[] SDATA(D_L20_001B2040);
extern f32 D_L20_001B2054 __attribute__((sda));
extern f32 D_L20_001B2060[] SDATA(D_L20_001B2060);
extern s32 D_L20_001B2070 __attribute__((sda));
extern s32 D_L20_001B2074 __attribute__((sda));
extern f32 D_L20_001B209C __attribute__((sda));
extern f32 D_L20_001B20A0 __attribute__((sda));
extern f32 D_L20_001B20B0[] SDATA(D_L20_001B20B0);
extern s32 D_L20_001B20C4 __attribute__((sda));
extern s32 D_L20_001B20C8 __attribute__((sda));
extern f32 D_L20_001B2100[] SDATA(D_L20_001B2100);
extern u8 D_00188660[];
extern s32 D_L20_001B29C0[] MACRO_ADDR;
extern s32 D_L20_001B29E0[] MACRO_ADDR;
extern s32 D_L20_001B2AC8[] __attribute__((sda));
extern s32 D_L20_001B2AD4[] MACRO_ADDR;
extern f32 D_L20_001B2BE8[] MACRO_ADDR;
extern char * D_L20_001B2FA8[] __attribute__((sda));
extern char * D_L20_001B308C[] __attribute__((sda));
typedef union { u8 b[0x200]; s32 i[0x80]; f32 f[0x80]; } Blk200;
extern u8 D_L20_001B9E80[];
extern s16 D_L20_001C0184[];
extern u8 D_L20_001C01C0[];
extern s32 D_L20_001CA540[];
extern s32 D_L20_0021FC18[];
extern s8 D_L20_001A8F20[] __attribute__((sda));
/* Lane 3 of the D_L20_001B2100 vector, read absolutely. */
extern f32 D_L20_001B210C[] MACRO_ADDR;
extern char * D_0018C0B0[];
extern s32 D_0018C0B4[];
#define AT(T, p, o) (*(T *)((char *)(p) + (o)))

void func_L20_00440598(char *self) {
    float sp[16] __attribute__((aligned(16)));
    char *st;
    int ctr = D_L20_001CA540[0];
    int v1, v2, v3, v5, v6;
    int fl;
    char *s0_1, *s0_2, *s0_3, *s0_4, *s0_5, *s0_6, *s0_7, *tb_1, *tb_2, *tb_3;

    if (ctr == 2) {
        st = AT(char *, self, 0x68);
        func_L20_00441CB8(self);
        if (AT(u8, self, 0x95) == 6) {
            if (AT(u8, self, 0x20) == 0x18 || AT(u8, self, 0x20) == 0x19) {
                if (func_002ACBC8(D_00189E20 + 0x80, AT(s32, st, 0x230)) != 0) {
                    qcopy(sp, D_L20_001B2100);
                    qzero_nc(&sp[4]);
                    sp[6] = D_L20_001B210C[0];
                    func_002DF3F8(sp, &sp[4]);
                    D_L20_001B20A0 = D_L20_001B20A0 + 1.0f;
                    func_002A7750(self, 1, 0);
                    fl = D_L20_001A8F00[0];
                } else {
                    fl = D_L20_001A8F00_gp;
                }
                /* ctr is 2 here; retail compares against its saved copy. */
                if (fl == ctr) {
                    AT(s32, self, 0x98) = 0;
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
                } else {
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) & 0xFFBE) | 0x1000;
                    AT(s32, self, 0x98) = AT(s32, AT(char *, self, 0x24), 0x10);
                }
            }
            if (D_L20_001CA540[0] == 2) {
                D_L20_001B2BE8[0] = AT(f32, self, 0x18) - 2.0f;
            }
        }
        switch (AT(u8, self, 0x20)) {
        case 1:
            if (func_002B3868(self) != 0 && AT(u8, self, 0x43) != 0x13) {
                func_002A7470(self, 0x13, 0, 0x14);
            }
            s0_1 = D_0018C0B0[0];
            func_L01_00322288(self, func_00283248(AT(f32, s0_1, 0x10) - AT(f32, self, 0x10), AT(f32, s0_1, 0x14) - AT(f32, self, 0x14)));
            if (AT(u8, self, 0x60) & 2) {
                func_L20_00442C10(self);
            }
            break;
        case 2:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 6) {
                    func_002A7470(self, 6, 0, 0x14);
                }
                func_L20_00442140(self);
                AT(s32, self, 0x9C) = 1;
            }
            tb_1 = (char *)D_00188660 + AT(s32, st, 0x1854) * 0x70;
            if (AT(s32, tb_1, 0x88) != (s32)self || AT(u8, tb_1, 0x74) == 0) {
                AT(s32, st, 0x1854) = func_002E5CF8(1, 4, self);
            }
            if (AT(char *, st, 0x1850) != 0) {
                func_00283098(sp, D_L20_001B20B0, self + 0xC0);
                func_00282CC0(sp, sp, self + 0x10);
                func_L20_0039F210(AT(char *, st, 0x1850), (char *)sp, 1);
            }
            if (func_L20_004421A8(self) != 0) {
                func_002A7750(self, 3, -1);
                v1 = AT(s32, st, 0x1854);
                if (v1 != -1 && (tb_2 = (char *)D_00188660 + v1 * 0x70, AT(s32, tb_2, 0x88) == (s32)self)) {
                    if (AT(u8, tb_2, 0x74) != 0) {
                        func_002E59F8(v1);
                    }
                }
                AT(s32, st, 0x1854) = -1;
            }
            break;
        case 3:
            if (func_002B3868(self) != 0) {
                func_L20_004424A0(self);
                if (AT(u8, self, 0x43) != 6) {
                    func_002A7470(self, 6, 0, 0x14);
                }
                AT(s32, self, 0x9C) = 1;
                if (AT(char *, st, 0x1850) == 0) {
                    if (AT(s32, st, 0x17F8) != 0) {
                        AT(char *, st, 0x1850) = func_L20_0039EEC8(self, self + 0x10);
                    }
                }
            }
            if (AT(char *, st, 0x1850) != 0) {
                func_00283098(sp, D_L20_001B20B0, self + 0xC0);
                func_00282CC0(sp, sp, self + 0x10);
                func_L20_0039F210(AT(char *, st, 0x1850), (char *)sp, 0);
            }
            func_002AA800((float *)(st + 0x1804), 0, 0.0f, 0.10471977f);
            if (func_L20_00442550(self) != 0) {
                if (D_0018C0B4[0] != 0x8C && (func_00282948(st + 0x17F8) == 1 || D_L20_001B20C8 != 0)) {
                    if (AT(s32, st, 0x1810) > 0) {
                        AT(s32, st, 0x1810) = -1;
                        func_L20_00442F80(self);
                    }
                    func_L20_00442C10(self);
                    AT(s32, self, 0x9C) = 2;
                } else {
                    func_002A7750(self, 2, 1);
                }
            }
            break;
        case 4:
            if (func_002B3868(self) != 0) {
                func_L20_00442740(self, D_L20_001B2038);
                if (AT(u8, self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 0x14);
                }
            }
            { char *p = AT(char *, st, 0x17FC);
            func_L20_004427C8(self, p + 0x10, func_00283248(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
            if (func_L20_00443508(self, AT(char *, st, 0x17FC)) == 0) {
                func_002A7750(self, 1, -1);
            } else {
                if (AT(f32, st, 0x11C) <= D_L20_001B2038 || AT(u16, self, 0x96) >= 0x12DU) {
                    func_002A7750(self, 5, -1);
                }
            }
            break;
        case 5:
            if (func_002B3868(self) != 0 && AT(u8, self, 0x43) != 0xB) {
                func_002A7470(self, 0xB, 0, 0xF);
            }
            if (func_0029F530(self) < 31.0f) {
                { char *p = AT(char *, st, 0x17FC);
                func_L01_00322288(self, func_00283248(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
                if (func_L20_00443508(self, AT(char *, st, 0x17FC)) == 0) {
                    func_002A7750(self, 1, -1);
                }
            } else if (func_002AEB60((u8 *)self, 32.0f) != 0) {
                s0_2 = AT(char *, st, 0x17FC);
                func_00282D30(sp, D_L20_001B2040, D_L20_001B2030);
                func_00283098(sp, sp, self + 0xC0);
                func_00282CC0(sp, sp, self + 0x10);
                AT(char *, st, 0x17FC) = func_L20_00443790(s0_2, AT(s16, s0_2, 0xAA), (char *)sp);
                AT(s32, st, 0x183C) = AT(s16, s0_2, 0xAA);
                func_L20_00442F30(s0_2);
                AT(f32, self, 0x48) = D_L20_001B2054;
            } else if (func_002AEB60((u8 *)self, 50.0f) != 0) {
                AT(f32, self, 0x48) = 1.0f;
            }
            if (func_0029F530(self) >= 60.0f) {
                func_L20_00442CD8(self);
                func_002A7750(self, 6, 3);
            }
            break;
        case 6:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 0x14);
                }
                func_L20_00442740(self, AT(f32, st, 0x1838) * 0.5f);
            }
            s0_3 = (char *)(&((Hero *)D_00189E20)->b[0x80]);
            func_L20_004427C8(self, s0_3, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < AT(f32, st, 0x1838) && func_00283C80(AT(f32, self, 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                func_002A7750(self, AT(s32, st, 0x1834), -1);
            }
            break;
        case 7: {
            int n;
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    func_002A7470(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x180C) = 0;
            }
            func_L01_00322288(self, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14)));
            AT(s32, st, 0x1808) = D_L20_001B2AC8[0];
            func_00283098(sp, D_L20_001B2060, self + 0xC0);
            func_00282CC0(sp, sp, self + 0x10);
            for (n = 1; n >= 0; n -= 1) {
                qcopy(&sp[4], sp);
                func_002ACB48(&sp[4], 1.5f);
                sp[2] -= 0.5f;
                func_002BDBC0((char *)&sp[4], D_L20_001A8F20, 0x60309030, 0x107090, 0x2D, func_002A7878(2.0f, 3.0f) * 210000.0f);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && func_00282948(st + 0x180C) != 0) {
                AT(s32, st, 0x180C) = D_L20_001B2070;
                func_L20_00443B60(self, (char *)&sp[4], (char *)&sp[8], &sp[12]);
                sp[6] += 1.5f;
                func_L20_0043F318(self, (char *)&sp[4], 0x78, (f32)AT(u8, st, 0x35), func_002A77E0(2), (int)(st + 0x1808));
            }
            if (D_L20_001B2074 < (s32)AT(u16, self, 0x96)) {
                func_002A7750(self, 1, -1);
            }
            break;
        }
        case 11:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    func_002A7470(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = func_002A7820(0xA, 0xF);
            }
            func_L20_00444AA8(self, (float *)(&((Hero *)D_00189E20)->b[0x80]));
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (AT(u16, self, 0x96) % 60U) == 0x1E) {
                func_L20_00444088(self);
                func_00282948(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 10:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    func_002A7470(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = func_002A7820(0x1E, 0x32);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                func_L20_00443D58(self);
                func_00282948(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 8:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    func_002A7470(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = func_002A7820(0xA, 0x14);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                func_L20_00443DF0(self);
                func_00282948(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 9:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    func_002A7470(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = func_002A7820(4, 5);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                if (func_L20_00444018(self) != 0) {
                    func_00282948(st + 0x1840);
                } else {
                    AT(s32, st, 0x1840) = 0;
                }
            }
            if (AT(s32, st, 0x1840) == 0) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 12:
            if (func_002B3868(self) != 0 && AT(u8, self, 0x43) != 0x11) {
                func_002A7470(self, 0x11, 0, 0x14);
            }
            if ((D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                if (D_L20_001B20C4 != 0) {
                    func_002A7750(self, 0xD, -1);
                } else if (func_L20_00443CF0(self) == 0 || func_L20_00440398(AT(s32, st, 0x21C)) >= 0x15) {
                    func_002A7750(self, 0xD, -1);
                }
            }
            break;
        case 13:
            v2 = func_002B3868(self);
            s0_4 = st + 0x17D0;
            if (v2 != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 0x14);
                }
                func_L20_00443A10(self, s0_4);
                func_L20_00442740(self, 1.0f);
            }
            func_L20_004427C8(self, s0_4, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < 1.0f && func_00283C80(AT(f32, self, 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                func_002A7750(self, 0xE, -1);
            } else if (func_L20_00440398(AT(s32, st, 0x21C)) < 3) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 14:
            if (func_002B3868(self) != 0 && AT(u8, self, 0x43) != 1) {
                func_002A7470(self, 1, 0, 0x14);
            }
            func_L20_00444AA8(self, (float *)(&((Hero *)D_00189E20)->b[0x80]));
            if (func_00282E80(self + 0x10, D_00189E20 + 0x80) < D_L20_001B209C) {
                func_002A7750(self, 0xD, -1);
            }
            if (func_L20_00440398(AT(s32, st, 0x21C)) < 3) {
                func_002A7750(self, 1, -1);
            }
            break;
        case 15:
            if (func_002B3868(self) != 0 && AT(u8, self, 0x43) != 0x15) {
                func_002A7470(self, 0x15, 0, 0xA);
            }
            { float t = func_002A89A8(self + 0x10, 0, 0.5f); func_002AA2E8((f32 *)(self + 0x18), t, 0.16666667f); }
            if (AT(u8, self, 0x60) & 2) {
                if (AT(u8, self, 0xBC) != 0) {
                    func_002A7750(self, 1, 0);
                } else {
                    func_002A7750(self, 0x10, -1);
                }
                AT(u8, self, 0xBC) = 0;
            }
            break;
        case 16: {
            f32 dist;
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 7) {
                    func_002A7470(self, 7, 0, 0x14);
                }
                func_L20_00442740(self, 1.0f);
                AT(s32, st, 0x1830) = 0;
            }
            if (AT(u8, self, 0x60) & 2) {
                switch (AT(u8, self, 0x42)) {
                case 7:
                    if (AT(u8, self, 0x43) != 8) {
                        func_002A7470(self, 8, 0, 1);
                    }
                    break;
                case 8:
                    if (AT(u8, self, 0x43) != 9) {
                        func_002A7470(self, 9, 0, 1);
                    }
                    break;
                case 9:
                    AT(s32, st, 0x1830) = AT(s32, st, 0x1830) + 1;
                    break;
                }
            }
            if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x8C) {
                ((Hero *)D_00189E20)->h[0x1E0 / 2] = 0xF;
            }
            dist = func_0029F530(self);
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                if ((AT(u8, self, 0x42) == 8 && dist < 9.0f) || (AT(u8, self, 0x42) == 9 && dist > 12.0f && dist < 30.0f)) {
                    s0_5 = (char *)(&((Hero *)D_00189E20)->b[0x80]);
                    func_L20_004427C8(self, s0_5, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14)));
                    if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                        if ((AT(u8, self, 0x42) == 8 && dist < 9.0f && dist > 7.0f) || (AT(u8, self, 0x43) == 9 && dist > 25.0f && dist < 30.0f)) {
                            qcopy(sp, self + 0x10);
                            sp[2] += 1.0f;
                            func_002A8C28(self, sp, 0x10008, 0, 1, 0, 5.5f, (f32)AT(u8, st, 0x34), 2.0f);
                        }
                    }
                }
            }
            if (AT(u8, self, 0x42) == 8 && func_002AEB60((u8 *)self, 6.0f) != 0) {
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = 0.05f;
            }
            if (AT(u8, self, 0x42) == 9 && func_002AEB60((u8 *)self, 30.0f) != 0) {
                if (AT(s32, st, 0x1830) >= 2 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x8C) {
                    func_L20_004441D8(self);
                    func_002A7750(self, 3, -1);
                }
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = (f32)(AT(s32, st, 0x1830) + 1) * 0.05f;
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
            }
            break;
        }
        case 17:
            if (func_002B3868(self) != 0) {
                if (AT(u8, self, 0x43) != 0x15) {
                    func_002A7470(self, 0x15, 0, 0xA);
                }
                s0_6 = D_L20_001B2FA8[0];
                v3 = D_L20_001A8F00_gp;
                if (s0_6 != 0) {
                    /* Retail keeps these four in saved registers; with literals cc1 folds the two state
                       tests into one range check. */
                    int class_removed = 0xCBC, state_dead = 0xFE, state_dying = 0xFD;
                    int class_reset = 0xD0F;
                    int id;
                    do {
                        id = AT(s16, s0_6, 0xAA);
                        if (id == class_removed && s0_6 != 0) {
                            u8 k = AT(u8, s0_6, 0x20);
                            if (k != state_dead && k != state_dying) {
                                func_0029F338(s0_6);
                            }
                            id = AT(s16, s0_6, 0xAA);
                        }
                        if (id == class_reset && s0_6 != 0) {
                            u8 k = AT(u8, s0_6, 0x20);
                            if (k != state_dead && k != state_dying && AT(u8, s0_6, 0x21) == AT(s32, st, 0x21C)) {
                                func_002A6C58(s0_6, 0, 3);
                                func_L20_0039DE88(s0_6);
                            }
                        }
                        s0_6 = AT(char *, s0_6, 0x28);
                    } while (s0_6 != 0);
                    v3 = D_L20_001A8F00[0];
                }
            } else {
                v3 = D_L20_001A8F00[0];
            }
            if (v3 == 2) {
                AT(s32, self, 0x98) = 0;
                AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
            }
            if (AT(u8, self, 0x60) & 2) {
                AT(s32, self, 0x48) = 0;
            }
            break;
        case 18:
            if (func_002B3868(self) != 0) {
                D_L20_001B29C0[0] = 0;
                func_002B49E0(9, 1, 0, 0, 0);
            }
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && func_00288AA0(D_L20_001C01C0, 0x1E) != 0) {
                func_00288BE8(D_L20_001C01C0);
                func_002A7750(self, 0x13, -1);
            }
            break;
        case 19:
            if (D_L20_001A8F00[0] == 0) {
                if (D_L20_001A8F08 <= 0) {
                    D_L20_001B2AD4[0] = 1;
                    func_002B49E0(9, 1, 0, 0, 0);
                    func_002A7750(self, 0x14, -1);
                }
                if (D_L20_001A8F00[0] == 0) {
                    func_L00_002E6EF8(func_L20_00440570, self);
                }
            }
            break;
        case 20:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && func_00288AA0(D_L20_001C01C0, 0x1F) != 0) {
                func_00288BE8(D_L20_001C01C0);
                func_002A7750(self, 0x15, -1);
            }
            break;
        case 21:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0) {
                int a, b;
                func_002A7750(self, 0x16, -1);
                a = func_00288FB8(0x325E);
                b = func_00288FB8(0x3210);
                func_00285828(a, b, func_00288FB8(0xA1F), 1);
                func_00285788(0x40, 0x20);
                func_002B49E0(4, 1, 9, 0, 0);
            }
            break;
        case 22:
            D_L20_001B29E0[0] = 0;
            if (D_L20_001C0184[0] == 1) {
                func_L20_0036E720();
                func_002A7750(self, 0x17, -1);
            } else {
                char *t;
                func_L00_002F3478();
                t = D_L20_001B308C[0] + (AT(s32, st, 0x248) << 7);
                func_002DF3F8(t + 0x30, t + 0x70);
                D_L20_0021FC18[0] = 0;
                func_L00_002B30E8();
            }
            break;
        case 24:
            v5 = func_002B3868(self);
            s0_7 = st + 0x17D0;
            if (v5 != 0) {
                f32 mag = func_002A7878(5.0f, 15.0f);
                f32 ang = func_002A7940();
                char *target;
                f32 y;
                AT(f32, st, 0x17D0) = func_00283180(ang) * mag;
                y = func_00283198(ang) * mag;
                target = D_L20_001B308C[0] + (AT(s32, st, 0x230) << 7);
                AT(s32, st, 0x17D8) = 0;
                AT(f32, st, 0x17D4) = y;
                func_00282CC0(s0_7, s0_7, target + 0x30);
                if (AT(u8, self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 0x14);
                }
                func_L20_00442740(self, 1.5f);
            }
            func_L20_004427C8(self, s0_7, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) <= 1.5f && func_00283C80(AT(f32, self, 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                func_002A7750(self, 0x19, -1);
            }
            break;
        case 25: {
            int anim;
            if (func_002B3868(self) != 0) {
                anim = (func_002A77E0(3) != 0) ? 0x13 : 0x14;
                if (AT(u8, self, 0x43) != anim) {
                    func_002A7470(self, anim, 0, 0x14);
                }
            }
            if (AT(u8, self, 0x60) & 2) {
                func_002A7750(self, 0x18, -1);
            }
            break;
        }
        }
        func_L20_004435A0(self);
        if (AT(u8, self, 0x20) != 2) {
            v6 = AT(s32, st, 0x1854);
            if (v6 != -1) {
                tb_3 = (char *)D_00188660 + v6 * 0x70;
                if (AT(s32, tb_3, 0x88) == (s32)self && AT(u8, tb_3, 0x74) != 0) {
                    func_002E59F8(v6);
                }
            }
            AT(s32, st, 0x1854) = -1;
        }
    }
}
