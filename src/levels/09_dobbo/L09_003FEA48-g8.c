#include "common.h"

extern f32 D_L09_001B13F0 __attribute__((sda));
extern f32 D_L09_001B13F4 __attribute__((sda));
extern void func_L08_00316678(char *a, s32 b, s32 c, s32 d);

typedef union {
    u16 h;
    s32 w;
} U16S32;

extern U16S32 D_L09_001B13C0 __attribute__((sda));
extern void func_2EA110(char *p);

void func_L09_00404B90(char *a0, s32 a1) {
    char *v = a0;
    f32 f = D_L09_001B13F0 * 0.0166666675f;
    char *p = *(char **)(v + 0x68);
    *(f32 *)(p + 0x1D4) = 3.0f;
    *(f32 *)(p + 0x1D0) = f;
    if (*(u8 *)(v + 0x43) == 7) {
        return;
    }
    func_L08_00316678(a0, 7, 0, a1);
}

void func_L09_00404BF0(char *a0, s32 a1) {
    char *v = a0;
    f32 f = D_L09_001B13F4 * 0.0166666675f;
    char *p = *(char **)(v + 0x68);
    *(f32 *)(p + 0x1D4) = 1.75f;
    *(f32 *)(p + 0x1D0) = f;
    if (*(u8 *)(v + 0x43) == 6) {
        return;
    }
    func_L08_00316678(a0, 6, 0, a1);
}

void func_L09_004031D8(char *a0) {
    char *s1 = a0;
    char *s0 = *(char **)(s1 + 0x68);
    u16 n;
    if (*(s16 *)(s0 + 0x270) != 0
        || (*(s32 *)(s0 + 0x234) == 1 && *(s16 *)(s0 + 0x26C) < D_L09_001B13C0.w / 2)) {
        *(u16 *)(s0 + 0x26C) = D_L09_001B13C0.h;
        *(s16 *)(s0 + 0x270) = 0;
    }
    func_2EA110(s0 + 0x26C);
    func_2EA110(s0 + 0x26E);
    n = *(u16 *)(s1 + 0x96);
    if (n < 0xFFFF) {
        *(u16 *)(s1 + 0x96) = n + 1;
    }
}


/* Small-data handles: the resident mode word (-0x7600 -> 0x001A79F0), the resident
   release word (-0x5FB0 -> 0x001A9040) and the level's record table (0x386C ->
   0x001B285C), all read with $gp pinned at 0x001AEFF0. */
extern s32 D_L09_001A79F0 __attribute__((sda));
extern s32 D_L09_001A9040 __attribute__((sda));
extern char *D_L09_001B285C __attribute__((sda));

extern s32 func_323340(char *a0, char *a1, s32 a2);
extern char *func_L09_00326E90(char *a0);
extern void func_L09_003FE978(char *a0);
extern void func_326368(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);

/* Drops the record the sub-object points at, once, when the resident mode word says 9,
   then rebuilds the sub-object's effect with both blend weights at zero. */
void func_L09_003FEA48(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);
    s16 idx;

    if (func_323340(a0, s0 + 0x160, 0) != 0) {
        if (D_L09_001A79F0 == 9) {
            idx = *(s16 *)(s0 + 0x1D0);
            if (idx != -1) {
                if (func_L09_00326E90(D_L09_001B285C + (idx << 8)) == 0) {
                    D_L09_001A9040 = 0;
                }
                *(s16 *)(s0 + 0x1D0) = -1;
            }
        }
        func_L09_003FE978(a0);
    }
    func_326368(a0, *(s32 *)(s0 + 0x448), 0, 0, 0.0f, 0.0f);
}

/* The same resident mode word, read here as an ordinary global (lui + lw) rather than
   through $gp: the two references name the same word, one small and one not. */
extern s32 D_001A79F0;

extern void func_L09_00404C50(void);
extern float func_00282E48(char *a0, char *a1);
extern void func_002A93B0(void *a0);
extern s32 func_002B0ED8(char *a0, char *a1, s32 a2);
extern void func_L09_00405060(char *a0);
extern void func_L09_004050E0(char *a0);
extern s32 func_002B3BA8(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern char D_L09_001B9A00[];

/* Releases the record the sub-object holds once the resident mode word says 9, then
   rebuilds the sub-object's effect. */
void func_L09_00404E58(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    s32 s2;
    s16 idx;

    if (*(u8 *)(s0 + 0x20) == 0) {
        func_L09_00404C50();
    }
    if (*(u8 *)(s0 + 0x31) != 0) {
        if (func_00282E48(s0 + 0x10, D_L09_001B9A00) < 24.0f) {
            func_002A93B0(s0);
            *(u8 *)(s0 + 0x6F) = 0x16;
        }
    }
    s2 = func_002B0ED8(s0, s1 + 0x50, 0);
    if (D_001A79F0 == 9) {
        idx = *(s16 *)(s1 + 0xC0);
        if (idx != -1) {
            if (func_L09_00326E90(D_L09_001B285C + (idx << 8)) == 0) {
                D_L09_001A9040 = 0;
            }
            *(s16 *)(s1 + 0xC0) = -1;
        }
    }
    if (s2 != 0) {
        func_L09_00405060(s0);
        if (s2 >= 4) {
            func_L09_004050E0(s0);
        }
    }
    if (*(u8 *)(s0 + 0x95) != 3 && *(u8 *)(s0 + 0x95) != 4) {
        *(s16 *)(s1 + 0x334) = func_002B3BA8(s0, *(s32 *)(s1 + 0x230), 0, 0, 16.0f, 0.0f);
    }
}

extern void func_L09_00402D50(void);
extern void func_L09_00403100(char *a0, s32 a1);

/* The same release as func_L09_00404E58, with this level's own calls: when the
   resident mode word says 9 the record the sub-object holds is released, then the
   record's update runs with the value func_002B0ED8 returned, and the sub-object's
   effect is rebuilt from the sub-object's own index and position. */
void func_L09_00403270(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    s32 s2;
    s16 idx;

    if (*(u8 *)(s0 + 0x20) == 0) {
        func_L09_00402D50();
    }
    if (*(u8 *)(s0 + 0x31) != 0) {
        if (func_00282E48(s0 + 0x10, D_L09_001B9A00) < 48.0f) {
            func_002A93B0(s0);
            *(u8 *)(s0 + 0x6F) = 0x2D;
        }
    }
    s2 = func_002B0ED8(s0, s1 + 0x50, 0);
    if (D_001A79F0 == 9) {
        idx = *(s16 *)(s1 + 0xC0);
        if (idx != -1) {
            if (func_L09_00326E90(D_L09_001B285C + (idx << 8)) == 0) {
                D_L09_001A9040 = 0;
            }
            *(s16 *)(s1 + 0xC0) = -1;
        }
    }
    func_L09_00403100(s0, s2);
    func_002B3BA8(s0, *(s32 *)(s1 + 0x28C), 0, 0, *(f32 *)(s1 + 0x24C), 0.0f);
}

/* The walks below read the group table of id lists absolute. The group count and the entity base
   are plain externs here, which come out as bare `lui`/`lw` pairs in ordinary flow and as $gp
   loads in a branch delay slot; the base takes a second name because D_L09_001B285C above is the
   $gp form. */
extern s32 D_L09_001B2878;

extern u8 *D_L09_001B285C_1;

extern u16 *D_L09_001FB560[];

/* The vector the scaled copy starts from: small data, so its address is a $gp offset. */
extern char D_L09_001B1410[1] __attribute__((sda));

/* The colour pair func_00283D38 blends. */
extern s32 D_L09_001B1420[2];

extern void func_00282D30(char *, char *, f32);

extern void func_002830C0(char *, char *, char *);

extern s32 func_00283D38(s32, s32, f32);

extern void func_L00_00325AE8(char *, s32, f32, f32);

typedef struct {
    s32 a, b;
} ColorPair;

/* The object's blended colour word: a member store, which the scheduler knows cannot alias the
   scalar global D_L09_001B2388 (a plain cast store it must keep in front of that load). */
typedef struct {
    u8 pad[0x78];
    s32 colour;
} TintedObject;

extern ColorPair D_L09_001B1400[2];

extern s32 D_L09_001B2388;

extern f32 func_00283B98(f32, f32);

extern f32 func_00283198(f32);

extern void func_0029FC20(u8 *, s32, u8 *);

extern void func_L00_002E6CF0(void *, u8 *);

void func_L09_00405490(u8 *a0);

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
void func_L09_004052F8(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    ColorPair color = D_L09_001B1400[0];
    u16 *p;
    u8 *e;
    u8 *sub;
    f32 angle;
    f32 wave;

    angle = func_00283B98(*(f32 *)(state + 0x348), 0.20943954f);
    *(f32 *)(state + 0x348) = angle;
    wave = func_00283198(angle) * 0.5f + 0.5f;
    *(f32 *)(state + 0x34C) = wave;
    ((TintedObject *)a0)->colour = func_00283D38(color.a, color.b, wave);
    if (*(s32 *)(state + 0x350) != D_L09_001B2388) {
        for (p = D_L09_001FB560[a0[0x21]];
             a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
             p++) {
            e = D_L09_001B285C_1 + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x31] != 0 && *(s16 *)(e + 0xAA) == 0xD90) {
                if (e[0x20] != 0xFE) {
                    if (e[0x20] != 0xFD) {
                        sub = *(u8 **)(e + 0x68);
                        func_0029FC20(e, 0, sub + 0x240);
                        *(s32 *)(sub + 0x350) = D_L09_001B2388;
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L09_00405490, a0);
    }
}

/* Callback of func_L09_004052F8 for every class-0xD90 entity of the object's group that is not
   hidden (byte 0x31) or in state 0xFE or 0xFD: scales the sub-object's vector by its float at
   +0x344, transforms it by the matrix at +0x240, blends the colour pair by the float at +0x34C
   and hands the result to func_L00_00325AE8 with the +0x344 float scaled by 0.2. */
void func_L09_00405490(u8 *a0) {
    f32 buf[4];
    u16 *p;
    u16 *q;
    u8 *e;
    u8 *state;
    s32 r;

    if (a0[0x21] == 0xFF)
        return;
    q = D_L09_001FB560[a0[0x21]];
    if (q == 0)
        return;
    for (p = q;
         a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
         p++) {
        e = D_L09_001B285C_1 + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x31] != 0 && *(s16 *)(e + 0xAA) == 0xD90) {
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    state = *(u8 **)(e + 0x68);
                    func_00282D30((char *)buf, D_L09_001B1410, *(f32 *)(state + 0x344));
                    func_002830C0((char *)buf, (char *)buf, (char *)(state + 0x240));
                    r = func_00283D38(D_L09_001B1420[0], D_L09_001B1420[1],
                                      *(f32 *)(state + 0x34C));
                    func_L00_00325AE8((char *)buf, r, *(f32 *)(state + 0x344) * 0.2f, 0.08f);
                }
            }
        }
    }
}

extern int func_316A28(int a);
extern int func_316A68(int a, int b);
extern void func_31F4D0(char *a0, int a1);
extern float func_2EB478(float a, float b);
extern float func_2EAA60(float a);
extern float func_2EAA78(float a);
extern int func_2EB5D0(float a);
extern void func_2EA750(float f12, void *a0, void *a1);
extern int D_L09_001B15B8 __attribute__((sda));
extern int D_L09_001B15B8_4[] MACRO_ADDR;
extern float D_L09_001B15C4 __attribute__((sda));
extern float D_L09_001B15C0 __attribute__((sda));
extern int D_L09_001B15B4 __attribute__((sda));
extern u8 D_L09_001B15B0 __attribute__((sda));

void func_L09_0040B0C8(char *a0) {
    char *s3 = *(char **)(a0 + 0x68);
    char *s1;
    float v[3];
    int n;
    float count;
    int sel;
    if (func_316A28(7)) {
        sel = D_L09_001B15B8;
    } else {
        sel = D_L09_001B15B8_4[1];
    }
    func_31F4D0(a0, sel);
    s1 = a0 + 0xC0;
    *(float *)(s3 + 0x10) = func_2EB478(*(float *)(s3 + 0x10), D_L09_001B15C4 * 0.00029088825f);
    v[0] = func_2EAA60(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[1] = func_2EAA78(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[2] = 0;
    count = (float)D_L09_001B15B4;
    *(float *)(a0 + 0xF0) = v[0];
    *(float *)(a0 + 0xF4) = v[1];
    n = func_2EB5D0(count * (*(float *)s3 + *(float *)(s3 + 4)) * 0.5f);
    *(u8 *)(a0 + 0x23) = D_L09_001B15B0 + n + func_316A68(-9, 9);
    *(u16 *)(a0 + 0x34) |= 0x800;
    func_2EACD0(s1, a0 + 0xF0);
    func_2EA750(*(float *)s3, s1, s1);
    func_2EA750(*(float *)(s3 + 4), a0 + 0xD0, a0 + 0xD0);
}

typedef struct { u8 pad[0x464]; u8 spent[1]; } L09_CellFlags;
extern L09_CellFlags D_L09_0021E9F0;
extern u8 D_0019B4A8[];
extern char *D_L09_001B294C[] __attribute__((sda));
extern void func_317B40(int a0, int a1, int a2, int a3);

void func_L09_00406E78(char *a0) {
    char *t1 = *(char **)(a0 + 0x68);
    char *o;
    char *a3;
    int id;
    int v;
    s32 idx = *(s32 *)(t1 + 0x64);

    if (idx == -1)
        return;
    o = (char *)((idx << 8) + (int)D_L09_001B285C);
    if (*(u8 *)(o + 0x20) == 0xFE)
        return;
    if (*(u8 *)(o + 0x20) == 0xFD)
        return;
    a3 = *(char **)(o + 0x68);
    if (*(s32 *)(a3 + 0x70) == -1)
        return;
    if (*(s32 *)(t1 + 0x50) != -1
        && (id = *(u16 *)((*(s32 *)(t1 + 0x50) << 8) + (int)D_L09_001B285C + 0xB2),
            D_L09_0021E9F0.spent[(s16)id] != 0
            || (v = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)],
                (id & 1) ? (v >> 4) & 7 : v & 7) != 0)) {
        *(float *)((*(s32 *)(a3 + 0x70) << 7) + (int)D_L09_001B294C[0] + 0x38) = 325.25f;
        func_317B40(*(s32 *)(t1 + 0x4C), 1, 1, 1);
    } else {
        *(float *)((*(s32 *)(a3 + 0x70) << 7) + (int)D_L09_001B294C[0] + 0x38) = 325.0f;
        func_317B40(*(s32 *)(t1 + 0x4C), 0, 0, 0);
    }
}

extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_0019B278[];
extern u8 D_001A7A28[] __attribute__((sda));
extern void func_30C790(char *a0);
extern void func_L09_00406C90(char *a0);

s32 func_L09_00406CC0(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    s32 s0;
    s32 idx;
    s32 id;

    if (D_0018C0B4 == 0x31)
        return 0;
    if (*(s32 *)(s1 + 0x2C) != -1) {
        char *o = (char *)((*(s32 *)(s1 + 0x2C) << 8) + (s32)D_L09_001B285C);
        if (*(u8 *)(o + 0x20) != 0xFE) {
            if (*(u8 *)(o + 0x20) != 0xFD) {
                if (D_0019B278[*(s32 *)*(char **)(o + 0x68) + (D_001A79F0 << 2)] == 0)
                    return 0;
            }
        }
    }
    if (*(s32 *)(s1 + 0x7C) != -1) {
        char *o = (char *)((*(s32 *)(s1 + 0x7C) << 8) + (s32)D_L09_001B285C);
        if (*(u8 *)(o + 0x20) != 0xFE) {
            if (*(u8 *)(o + 0x20) != 0xFD) {
                if (*(u8 *)(*(s32 *)*(char **)(o + 0x68) + (s32)D_001A7A28) == 0)
                    return 0;
            }
        }
    }
    idx = *(s32 *)(s1 + 0x50);
    if (idx != -1) {
        id = *(u16 *)((idx << 8) + (s32)D_L09_001B285C + 0xB2);
        if (D_L09_0021E9F0.spent[(s16)id] == 0) {
            s32 v = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
            if (id & 1)
                v = (v >> 4) & 7;
            else
                v = v & 7;
            if (v == 0)
                return 0;
        }
    }
    s0 = -1;
    idx = *(s32 *)(s1 + 0x64);
    if (idx != s0) {
        func_30C790((idx << 8) + D_L09_001B285C);
        *(s32 *)(s1 + 0x64) = s0;
    }
    idx = *(s32 *)(s1 + 0x68);
    if (idx != s0) {
        func_30C790((idx << 8) + D_L09_001B285C);
        *(s32 *)(s1 + 0x68) = s0;
    }
    func_L09_00406C90(a0);
    return 1;
}
