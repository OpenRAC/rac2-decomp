#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* A 0x80-byte record of the level table at D_L13_001B2A0C; its point is at +0x30. */
typedef struct { u8 pad0[0x30]; TI128 v; u8 pad40[0x40]; } L13Cam;

extern char D_00189E20[];
extern float D_00189EA0[];
extern u8 *D_0018C0B0;
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));
extern u8 *D_L13_001B2A0C __attribute__((section(".sdata")));
extern char D_L13_001BFD00[];
extern s32 *D_L13_001FE580[];
extern char D_L13_001B11F8[];
extern char D_L13_001B1200[];
extern char D_L13_001B1208[];
extern char D_L13_001B1218[];
extern s32 D_001A79F0[] __attribute__((section(".sdata")));

extern void func_0026FEB8(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_002AEB60(void *, float);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002B6120(void *, void *);
extern int func_002B6228(void *, void *, int, int);
extern int func_L01_00321178(void *, void *);
extern int func_L01_00322288(void *, float);
extern void func_L01_003E9CF8(void *, int, void *);
extern int func_L02_002EF388(void *, void *, void *, void *, int);
extern int func_L13_0040A638(void *);
extern int func_L13_0040C3A0(void *);
extern void func_L13_0040CA00(void *);
extern u8 *func_L12_00408050(void *, void *, void *, int, float);
extern void func_002B5258(void *);
extern int func_002B3890(void *);
extern void func_0029F338(void *);
extern int func_L13_004095F8(char *, char *);
extern int func_L13_00409840(void *, void *);
extern void func_L13_0040A480(void *);

/* The per-frame update of the second level-13 guard kind, built like func_L13_00406F18:
   the action states (+0x95), the animation states (+0x20), then the shared timer update. */
void func_L13_0040A720(u8 *a0)
{
    float m[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    u8 *st;

    st = *(u8 **)(a0 + 0x68);
    if (func_L13_0040C3A0(a0) != 0) {
        func_L01_003E9CF8(a0, 0, 0);
    }
    switch (a0[0x95]) {
    case 0: {
        s32 r;
        r = *(s32 *)(st + 0x250);
        if (r == 1 && func_00282948(st + 0x248) != 0) {
            if (*(s32 *)(st + 0x2A8) == 0 || ((Hero *)D_00189E20)->h[0x348 / 2] == r) {
                *(s32 *)(st + 0x288) = r;
                func_002A7750(a0, 0x17, 2);
                if (a0[0x43] != 6) {
                    func_002A7470(a0, 6, 0, 0xA);
                }
                if (func_002A77E0(2) == r) {
                    if (a0[0x43] != 7) {
                        func_002A7470(a0, 7, 0, 0xA);
                    }
                }
                if (*(s32 *)(st + 0x268) != -1) {
                    func_002A7750(a0, 0x12, 2);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x294) != -1) {
                    func_002A7750(a0, 0xF, 2);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
            }
        } else if (*(s64 *)(st + 0x280) == 1 && func_00282948(st + 0x248) != 0) {
            if (*(s32 *)(st + 0x278) != -1) {
                func_002A7750(a0, 0xE, -1);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xA);
                }
                *(s32 *)(st + 0x284) = 1;
            }
        } else if (*(s32 *)(st + 0x24C) != 0) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                *(s32 *)(st + 0x288) = 1;
                if (a0[0x43] != 0xF) {
                    func_002A7470(a0, 0xF, 0, 0x19);
                }
                func_002A7750(a0, 0x13, 2);
                if (*(s32 *)(st + 0x268) != -1) {
                    func_002A7750(a0, 0x12, 2);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x294) != -1) {
                    func_002A7750(a0, 0xF, 2);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xF);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                    e[0x20] = 3;
                    *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
                }
            }
            *(s32 *)(st + 0x24C) = 0;
            if (*(s32 *)(st + 0x240) < 0x12C) {
                *(s32 *)(st + 0x240) = func_002A7820(0x1E0, 0x258);
            }
        }
        break;
    }
    case 8: {
        s32 r;
        s32 i;
        u8 *e;
        if (*(s32 *)(st + 0x298) != 0 && (i = *(s32 *)(st + 0x29C)) != -1) {
            e = D_L13_001B291C + (i << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD) {
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                func_L02_002EF388(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                *(s32 *)(st + 0x298) = 0;
                if (*(s32 *)(st + 0x2A0) != -1) {
                    func_002A7750(a0, 0x1B, 7);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xF);
                    }
                } else {
                    if (a0[0x43] != 5) {
                        func_002A7470(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == 1) {
                        if (a0[0x43] != 0xC) {
                            func_002A7470(a0, 0xC, 0, 0xA);
                        }
                    }
                    func_002A7750(a0, 0x15, 2);
                }
            }
        } else {
            r = *(s32 *)(st + 0x250);
            if (r == 1 && func_00282948(st + 0x248) != 0) {
                *(s32 *)(st + 0x288) = r;
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == r) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
                func_002A7750(a0, 0x15, 2);
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                func_L02_002EF388(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
            } else {
                r = a0[0xBC];
                if (r == 1) {
                    *(s32 *)(st + 0x288) = r;
                    if (a0[0x43] != 5) {
                        func_002A7470(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == r) {
                        if (a0[0x43] != 0xC) {
                            func_002A7470(a0, 0xC, 0, 0xA);
                        }
                    }
                    func_002A7750(a0, 0x15, 2);
                    *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                    *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) &= 0xFFBE;
                    *(u16 *)(*(u8 **)(st + 0x25C) + 0x34) |= 0x1000;
                    *(s32 *)(*(u8 **)(st + 0x25C) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(st + 0x25C) + 0x24) + 0x10);
                    func_L02_002EF388(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
                }
            }
        }
        break;
    }
    case 6: {
        u8 *e;
        e = D_L13_001B291C + (*(s32 *)(st + 0x29C) << 8);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || *(s32 *)(st + 0x2B8) == 1) {
            *(s32 *)(st + 0x298) = 0;
            if (*(s32 *)(st + 0x2A0) != -1) {
                func_002A7750(a0, 0x1B, 7);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xF);
                }
            } else {
                func_002A7750(a0, 0x15, 2);
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
            }
        }
        break;
    }
    case 4:
        func_002B5258(a0);
        if (*(s32 *)(st + 0x250) == 1) {
            func_002A7750(a0, 0x13, 5);
            if (a0[0x43] != 0xF) {
                func_002A7470(a0, 0xF, 0, 0x28);
            }
        }
        break;
    case 5:
        func_002B5258(a0);
        if (*(s32 *)(st + 0x250) != 1 && *(s32 *)(st + 0x254) != 1 && a0[0x20] != 0x12) {
            func_002A7750(a0, 1, 4);
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0x1E);
            }
        }
        break;
    case 1:
        if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
            *(s32 *)(st + 0x288) = 1;
            if (a0[0x43] != 0xF) {
                func_002A7470(a0, 0xF, 0, 0x19);
            }
            func_002A7750(a0, 0x13, 2);
            if (*(s32 *)(st + 0x268) != -1) {
                func_002A7750(a0, 0x12, 2);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xF);
                }
            }
            if (*(s32 *)(st + 0x294) != -1) {
                func_002A7750(a0, 0xF, 2);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xF);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x2AC) << 8);
                e[0x20] = 3;
                *(u8 **)(*(u8 **)(e + 0x68) + 0xC) = a0;
            }
        } else if (*(s32 *)(st + 0x240) == 0) {
            func_002A7750(a0, 1, 0);
        }
        break;
    case 2: {
        s32 r;
        if (func_002B3890(a0) != 0) {
            func_002B60B0(a0, 0.0033333334f, 0.10000001f, 0.006981318f, 0.8377582f);
        }
        if (*(s32 *)(st + 0x250) != 1 && *(s32 *)(st + 0x254) != 1 && a0[0x20] != 0x12) {
            func_002A7750(a0, 0xD, 1);
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0x1E);
            }
            *(s32 *)(st + 0x240) = func_002A7820(0x244, 0x258);
            r = func_002A77E0(4);
            *(s32 *)(st + 0x26C) = 0;
            *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
        }
        break;
    }
    case 3: {
        s32 r;
        r = func_002B1C20(a0, st + 0x140);
        if (r & 1) {
            u8 *p = *(u8 **)(st + 0x25C);
            if (p != 0 && *(s16 *)(p + 0xAA) == 0xEA9) {
                func_0029F338(p);
            }
            func_002A6C58(a0, 0, 3);
            func_L01_003E9CF8(a0, 0, 0);
            return;
        }
        if (r & 2) {
            if (*(s32 *)(st + 0x250) == 1 || *(s32 *)(st + 0x254) == 1) {
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
                func_002A7750(a0, 0x15, 2);
            } else {
                if (func_002A77E0(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_002A7470(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        func_002A7470(a0, 0, 0, 0x14);
                    }
                }
                if (func_002A77E0(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        func_002A7470(a0, 0xE, 0, 0x1E);
                    }
                }
                func_002A7750(a0, 0xD, 1);
                *(s32 *)(st + 0x240) = func_002A7820(0x244, 0x258);
            }
            if (*(s32 *)(st + 0x278) != -1 && *(s32 *)(st + 0x288) == 0) {
                func_002A7750(a0, 0x10, -1);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x294) != -1) {
                func_002A7750(a0, 0xF, 2);
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xF);
                }
            }
        }
        break;
    }
    }

    switch (a0[0x20]) {
    case 9:
        if (*(u16 *)(a0 + 0x96) >= 0x38) {
            func_002A7750(a0, 0xA, -1);
            if (a0[0x43] != func_002A77E0(3) + 0x13) {
                func_002A7470(a0, func_002A77E0(3) + 0x13, 0, 3);
            }
            if (a0[0x43] == 0x13) {
                *(s32 *)(st + 0x2C4) = 0;
                func_0026FEB8(D_L13_001B11F8);
            } else if (a0[0x43] == 0x15) {
                *(s32 *)(st + 0x2C4) = 1;
                func_0026FEB8(D_L13_001B1200);
            } else {
                *(s32 *)(st + 0x2C4) = 2;
                func_0026FEB8(D_L13_001B1208);
            }
        }
        break;
    case 12:
        if (*(u16 *)(a0 + 0x96) >= 0x47) {
            func_002A7750(a0, 0xA, -1);
            if (a0[0x43] != func_002A77E0(3) + 0x13) {
                func_002A7470(a0, func_002A77E0(3) + 0x13, 0, 3);
            }
            if (a0[0x43] == 0x13) {
                *(s32 *)(st + 0x2C4) = 0;
                func_0026FEB8(D_L13_001B11F8);
            } else if (a0[0x43] == 0x15) {
                *(s32 *)(st + 0x2C4) = 1;
                func_0026FEB8(D_L13_001B1200);
            } else {
                *(s32 *)(st + 0x2C4) = 2;
                func_0026FEB8(D_L13_001B1208);
            }
        }
        break;
    case 10: {
        s32 r;
        if (*(u16 *)(a0 + 0x96) >= 0x3D) {
            r = func_L13_0040A638(a0);
            if (r == 2) {
                func_002A7750(a0, 9, -1);
                if (a0[0x43] != 0x12) {
                    func_002A7470(a0, 0x12, 0, 3);
                }
            } else if (r == 0) {
                func_002A7750(a0, 0xB, -1);
                if (a0[0x43] != 7) {
                    func_002A7470(a0, 7, 0, 0xA);
                }
            } else {
                func_002A7750(a0, 0xB, -1);
                if (a0[0x43] != 0x16) {
                    func_002A7470(a0, 0x16, 0, 0xA);
                }
            }
        }
        break;
    }
    case 11:
        if (*(u16 *)(a0 + 0x96) >= 0x49) {
            func_002A7750(a0, 0xC, -1);
            if (a0[0x43] != 0x12) {
                func_002A7470(a0, 0x12, 0, 0x12);
            }
        }
        break;
    case 7:
        if (*(s32 *)(st + 0x2A4) != 0) {
            if (func_L13_00409840(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                func_002A7750(a0, 8, -1);
                if (func_002A77E0(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_002A7470(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        func_002A7470(a0, 0, 0, 0x14);
                    }
                }
                if (func_002A77E0(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        func_002A7470(a0, 0xE, 0, 0x1E);
                    }
                }
            }
        } else {
            if (func_002B6120(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)]) != 0) {
                func_002A7750(a0, 8, -1);
                if (func_002A77E0(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_002A7470(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        func_002A7470(a0, 0, 0, 0x14);
                    }
                }
                if (func_002A77E0(5) == 1) {
                    if (a0[0x43] != 0xE) {
                        func_002A7470(a0, 0xE, 0, 0x1E);
                    }
                }
            }
        }
        break;
    case 8: {
        s32 *path;
        float d;
        if (a0[0x60] & 2) {
            path = D_L13_001FE580[*(s32 *)(st + 0x2B0)];
            d = func_00282E80(a0 + 0x10, path + 4);
            if (func_00282E80(a0 + 0x10, path + *path * 4) < d) {
                func_002B6228(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)], 0, *path - 1);
            } else {
                func_002B6228(a0, D_L13_001FE580[*(s32 *)(st + 0x2B0)], *path - 1, 0);
            }
            func_002A7750(a0, 7, -1);
            if (a0[0x43] != 2) {
                func_002A7470(a0, 2, 0, 0x14);
            }
        }
        break;
    }
    case 5:
        if (a0[0x60] & 2) {
            func_002A7750(a0, 6, 0);
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0x28);
            }
        }
        break;
    case 4:
        if (a0[0x60] & 2) {
            func_002A7750(a0, 1, 0);
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0x14);
            }
        }
        break;
    case 6: {
        u8 *e = D_L13_001B291C + (*(s32 *)(st + 0x264) << 8);
        func_L01_00322288(a0, func_00283248(*(float *)(e + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(e + 0x14) - *(float *)(a0 + 0x14)));
        break;
    }
    case 13:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0xA);
            }
            func_002A7750(a0, 1, -1);
        }
        break;
    case 27: {
        s32 r;
        if (*(s32 *)(st + 0x2A4) != 0) {
            r = func_L13_00409840(a0, D_L13_001FE580[*(s32 *)(st + 0x2A0)]);
        } else {
            r = func_002B6120(a0, D_L13_001FE580[*(s32 *)(st + 0x2A0)]);
        }
        if (r != 0 || func_00282E80(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    func_002A7470(a0, 0xC, 0, 0xA);
                }
            }
            func_002A7750(a0, 0x15, -1);
        }
        break;
    }
    case 14:
        func_002A7750(a0, 0x10, -1);
        if (a0[0x43] != 3) {
            func_002A7470(a0, 3, 0, 0xA);
        }
        break;
    case 16:
        if (func_002B6120(a0, D_L13_001FE580[*(s32 *)(st + 0x278)]) != 0) {
            *(s32 *)(st + 0x288) = 1;
            func_002A7750(a0, 0x11, -1);
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0xA);
            }
        }
        break;
    case 17:
        func_0026FEB8(D_L13_001B1218);
        func_002A7750(a0, 1, -1);
        break;
    case 18: {
        s32 i;
        s32 j;
        if (func_002B3868(a0) != 0 && *(s32 *)(st + 0x2A8) != 0) {
            i = *(s32 *)(st + 0x350);
            if (i != -1) {
                j = *(s32 *)(st + 0x354);
                if (j != -1) {
                    u8 *base = D_L13_001B291C;
                    (base + (i << 8))[0x20] = 4;
                    (base + (j << 8))[0x20] = 4;
                    *(s32 *)(st + 0x350) = -1;
                    *(s32 *)(st + 0x354) = -1;
                }
            }
        }
        *(TI128 *)m = ((L13Cam *)D_L13_001B2A0C)[*(s32 *)(st + 0x268)].v;
        if (*(s32 *)(st + 0x2A4) != 0) {
            func_L13_004095F8(a0, m);
        } else {
            func_L01_00321178(a0, m);
        }
        if (func_00282E80(a0 + 0x10, m) < 0.5f) {
            func_002A7750(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xF);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    func_002A7470(a0, 0xC, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                func_002A7750(a0, 0x18, -1);
                if (a0[0x43] != 0x10) {
                    func_002A7470(a0, 0x10, 0, 0x14);
                }
            }
        }
        break;
    }
    case 29:
        *(TI128 *)m = *(TI128 *)(st + 0x360);
        if (*(s32 *)(st + 0x2A4) != 0) {
            func_L13_004095F8(a0, m);
        } else {
            func_L01_00321178(a0, m);
        }
        if (func_00282E80(a0 + 0x10, m) < 0.5f) {
            func_002A7750(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xF);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    func_002A7470(a0, 0xC, 0, 0xA);
                }
            }
            if (*(s32 *)(st + 0x2A8) != 0) {
                func_002A7750(a0, 0x18, -1);
                if (a0[0x43] != 0x10) {
                    func_002A7470(a0, 0x10, 0, 0x14);
                }
            }
        }
        break;
    case 15:
        if (*(s32 *)(st + 0x2A4) != 0) {
            if (func_L13_00409840(a0, D_L13_001FE580[*(s32 *)(st + 0x294)]) != 0) {
                func_002A7750(a0, 0x15, -1);
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
                *(s32 *)(st + 0x294) = -1;
            }
        } else if (func_002B6120(a0, D_L13_001FE580[*(s32 *)(st + 0x294)]) != 0
                   || func_00282E80(a0 + 0x10, *(u8 **)(st + 0x200) + 0x10) < 8.0f) {
            func_002A7750(a0, 0x15, -1);
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    func_002A7470(a0, 0xC, 0, 0xA);
                }
            }
            *(s32 *)(st + 0x294) = -1;
        }
        break;
    case 19:
        if (a0[0x60] & 2) {
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xA);
            }
            if (*(s32 *)(st + 0x290) == 1) {
                if (a0[0x43] != 0xC) {
                    func_002A7470(a0, 0xC, 0, 0xA);
                }
            }
            func_002A7750(a0, 0x15, -1);
        }
        break;
    case 25: {
        u8 *hit;
        if (func_00283C80(*(float *)(a0 + 0xF8),
                          func_00283248(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                        *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
            func_0029FCC0(a0, 2, m);
            func_00282CF0(v, st + 0x1F0, m);
            func_00282F20(v, v, 0.5f);
            if (func_002761F8(m, st + 0x1F0, 0, a0, 0) == 0) {
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
                func_002A7750(a0, 0x15, -1);
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == D_0018C0B0 || hit == *(u8 **)(st + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x200
                                 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    if (a0[0x43] != 5) {
                        func_002A7470(a0, 5, 0, 0xA);
                    }
                    if (*(s32 *)(st + 0x290) == 1) {
                        if (a0[0x43] != 0xC) {
                            func_002A7470(a0, 0xC, 0, 0xA);
                        }
                    }
                    func_002A7750(a0, 0x15, -1);
                }
            }
        }
        if (a0[0x60] & 2) {
            if (a0[0x42] == 4) {
                if (func_002A77E0(2) == 1) {
                    if (a0[0x43] != 1) {
                        func_002A7470(a0, 1, 0, 0x14);
                    }
                } else {
                    if (a0[0x43] != 0) {
                        func_002A7470(a0, 0, 0, 0x14);
                    }
                }
            } else {
                if (a0[0x43] != 4) {
                    func_002A7470(a0, 4, 0, 0x14);
                }
            }
        }
        break;
    }
    case 21: {
        u8 *hit;
        func_L01_00322288(a0, func_00283248(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            func_L13_0040A480(a0);
        }
        if (func_002AEB60(a0, 1.0f) != 0) {
            if (func_00283C80(*(float *)(a0 + 0xF8),
                              func_00283248(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                            *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
                func_0029FCC0(*(u8 **)(st + 0x25C), 0, m);
                func_00282CF0(v, st + 0x1F0, m);
                func_00282F20(v, v, 0.5f);
                if (func_002761F8(m, st + 0x1F0, 0, a0, 0) == 0) {
                    func_L12_00408050(a0, v, m, 0, st[0x34]);
                    (*(s32 *)(st + 0x26C))++;
                } else {
                    hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                    if (hit != 0 && (hit == D_0018C0B0 || hit == *(u8 **)(st + 0x200)
                                     || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                     || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x200
                                     || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                        func_L12_00408050(a0, v, m, 0, st[0x34]);
                        (*(s32 *)(st + 0x26C))++;
                    }
                }
            }
        }
        if (a0[0x60] & 2) {
            if (*(s32 *)(st + 0x26C) <= 0) {
                func_002A7750(a0, 0x19, -1);
                if (a0[0x43] != 4) {
                    func_002A7470(a0, 4, 0, 0xA);
                }
            } else {
                s32 r;
                func_002A7750(a0, 0x17, -1);
                if (a0[0x43] != 6) {
                    func_002A7470(a0, 6, 0, 0xA);
                }
                if (func_002A77E0(2) == 1) {
                    if (a0[0x43] != 7) {
                        func_002A7470(a0, 7, 0, 0xA);
                    }
                }
                r = func_002A77E0(4);
                *(s32 *)(st + 0x26C) = 0;
                *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
            }
        }
        break;
    }
    case 24:
        func_L01_00322288(a0, func_00283248(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            func_L13_0040A480(a0);
        }
        if (func_002AEB60(a0, 1.0f) != 0) {
            if (func_00283C80(*(float *)(a0 + 0xF8),
                              func_00283248(*(float *)(st + 0x1F0) - *(float *)(a0 + 0x10),
                                            *(float *)(st + 0x1F4) - *(float *)(a0 + 0x14))) < 0.78539824f) {
                (*(s32 *)(st + 0x26C))++;
                func_0029FCC0(*(u8 **)(st + 0x25C), 0, m);
                func_00282CF0(v, st + 0x1F0, m);
                func_00282F20(v, v, 0.5f);
                func_L12_00408050(a0, v, m, 0, st[0x34]);
            }
        }
        if ((a0[0x60] & 2) && *(s32 *)(st + 0x26C) > 0) {
            s32 r;
            func_002A7750(a0, 0x17, -1);
            if (a0[0x43] != 6) {
                func_002A7470(a0, 6, 0, 0xA);
            }
            if (func_002A77E0(2) == 1) {
                if (a0[0x43] != 7) {
                    func_002A7470(a0, 7, 0, 0xA);
                }
            }
            r = func_002A77E0(4);
            *(s32 *)(st + 0x26C) = 0;
            *(s32 *)(st + 0x274) = *(s32 *)(st + 0x270) + r;
        }
        break;
    case 22: {
        u8 *hit;
        func_L01_00322288(a0, func_00283248(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (*(s32 *)(st + 0x2A4) != 0) {
            func_L13_0040A480(a0);
        }
        if (func_002AEB60(a0, 1.0f) != 0) {
            func_0029FCC0(*(u8 **)(st + 0x25C), 0, m);
            func_00282CF0(v, st + 0x1F0, m);
            func_00282F20(v, v, 0.4166667f);
            if (func_002761F8(m, st + 0x1F0, 0, a0, 0) == 0) {
                func_L12_00408050(a0, v, m, 0, st[0x34]);
                (*(s32 *)(st + 0x26C))++;
            } else {
                hit = *(u8 **)(D_L13_001BFD00 + 0x18);
                if (hit != 0 && (hit == D_0018C0B0 || hit == *(u8 **)(st + 0x200)
                                 || *(s16 *)(hit + 0xAA) == 0xC87 || *(s16 *)(hit + 0xAA) == 0xC86
                                 || *(s16 *)(hit + 0xAA) == 0x1F4 || *(s16 *)(hit + 0xAA) == 0x200
                                 || *(s16 *)(hit + 0xAA) == 0x1FF)) {
                    func_L12_00408050(a0, v, m, 0, st[0x34]);
                    (*(s32 *)(st + 0x26C))++;
                }
            }
        }
        break;
    }
    case 23:
        func_L01_00322288(a0, func_00283248(*(float *)(*(u8 **)(st + 0x200) + 0x10) - *(float *)(a0 + 0x10),
                                             *(float *)(*(u8 **)(st + 0x200) + 0x14) - *(float *)(a0 + 0x14)));
        if (D_001A79F0[0] != 0x10) {
            if (a0[0x60] & 2) {
                func_002A7750(a0, 0x19, -1);
                if (a0[0x43] != 4) {
                    func_002A7470(a0, 4, 0, 0xA);
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    func_002A7750(a0, 0x18, -1);
                    if (a0[0x43] != 0x10) {
                        func_002A7470(a0, 0x10, 0, 0x14);
                    }
                }
                if (*(s32 *)(st + 0x358) != 0 && func_00282E80(a0 + 0x10, st + 0x360) > 4.0f) {
                    func_002A7750(a0, 0x1D, -1);
                    if (a0[0x43] != 3) {
                        func_002A7470(a0, 3, 0, 0xA);
                    }
                }
            }
        } else {
            if (*(u16 *)(a0 + 0x96) >= 0xB5) {
                func_002A7750(a0, 0x15, -1);
                if (a0[0x43] != 5) {
                    func_002A7470(a0, 5, 0, 0xA);
                }
                if (*(s32 *)(st + 0x290) == 1) {
                    if (a0[0x43] != 0xC) {
                        func_002A7470(a0, 0xC, 0, 0xA);
                    }
                }
                if (*(s32 *)(st + 0x2A8) != 0) {
                    func_002A7750(a0, 0x18, -1);
                    if (a0[0x43] != 0x10) {
                        func_002A7470(a0, 0x10, 0, 0x14);
                    }
                }
            }
            if (a0[0x60] & 2) {
                if (a0[0x43] != 4) {
                    func_002A7470(a0, 4, 0, 5);
                }
            }
        }
        break;
    case 1:
    default:
        break;
    }
    func_L13_0040CA00(a0);
}
