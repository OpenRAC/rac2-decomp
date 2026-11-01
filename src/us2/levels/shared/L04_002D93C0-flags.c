#include "include_asm.h"

#include "common.h"
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern int D_001A8F00[] __attribute__((sda));
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char D_001A7A32 MACRO_ADDR;
extern char D_L04_001C3D40[];
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(f32 *,f32 *,f32 *);
extern void func_L00_002D36E0(void *,int,float,float,float);
extern void func_US2_L04_002E7F28(int,int);
extern char *func_002A9640(void *,int,int);
extern void func_US2_L00_002A4EF8(int);
extern void func_L00_002B9B88(int,int);
extern void func_L00_002B2C58(void *,int,float,float);
extern void func_L00_002D3C68(void *,void *,float);
#define AB(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define AH(p,o) (*(short *)((char *)(p)+(o)))
#define AI(p,o) (*(int *)((char *)(p)+(o)))
#define AF(p,o) (*(float *)((char *)(p)+(o)))
#define AP(p,o) (*(char **)((char *)(p)+(o)))
typedef union {
    unsigned char b[0x2500];
    short h[0x1280];
    int i[0x940];
    float f[0x940];
    char *p[0x940];
} GroundHero;
#define GROUND_HERO (*(GroundHero *)&D_00189E20)
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern u32 func_00282978(u8 *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern float func_00282DB0(void *, void *);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 D_00189E20;
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;
extern s32 func_002A8600(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u32 *out, u32 value, s32 arg2, s32 arg3);
extern f32 func_00282DB0(void *a, void *b);
extern f32 func_00282C10(f32 x);
extern f32 func_00283248(f32 a, f32 b);
extern s32 func_001163B0(void);
extern u8 *ref_L04_00358868_00[];
extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
extern void func_00282CC0(void *, void *, void *);
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);
extern u32 func_00282978(u8 *ptr);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#define MACRO_ADDR __attribute__((section(".sdata")))
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);
extern u32 D_L04_001B2E84 __attribute__((sda));

/* Check the hero's surface contact and optionally apply its movement impulse. */
int func_US2_L04_002D93C0(int update) {
    char *entry, *m;
    HopVector delta;
    int special;
    float amount;

    if (GROUND_HERO.i[0x229C / 4] == 20) return 0;
    if (GROUND_HERO.i[0x229C / 4] == 7) return 0;
    if (GROUND_HERO.i[0x2294 / 4] == 0x31) return 0;
    if (GROUND_HERO.h[0x1DC / 2]) return 0;
    if (D_001A8F00[0]) return 0;
    GROUND_HERO.i[0x249C / 4] = 0;
    m = GROUND_HERO.p[0x2290 / 4];
    if (AB(m, 0xA8) == 255) return 0;
    entry = D_L04_001C3D40 + AB(m, 0xA8) * 64;
    if (AP(entry, 0x38) != m) return 0;
    if (!(AI(entry, 0x24) & 9)) return 0;
    if (AF(entry, 0x2C) != 0.0f) {
        D_001A7A33 = 0;
        D_001A7A32 = 1;
    }
    if (func_L00_0037E668() != 0.0f && !GROUND_HERO.b[0x22B4]) {
        AF(entry, 0x2C) = func_L00_0037E5F0(AF(entry, 0x2C));
        if (AF(entry, 0x2C) == 0.0f) return 0;
    }
    GROUND_HERO.p[0x249C / 4] = AP(entry, 0x20);
    if (!update) return 1;
    func_L00_002A6708();
    special = 0;
    if (AI(entry, 0x30) & 1) {
        qcopy(&delta, entry + 0x10);
        if (AF(entry, 0x1C) == 5627.925f) special = 1;
    } else if (AP(entry, 0x20)) {
        func_00282CF0(delta.f, (float *)(GROUND_HERO.b + 0x80),
                     (float *)(AP(entry, 0x20) + 0x10));
    } else {
        func_L00_002D36E0(&delta, 0, -1.0f, 0.0f, 0.0f);
    }
    if (!GROUND_HERO.b[0x22B4]) {
        char *m = GROUND_HERO.p[0x249C / 4];
        if (m && (AH(m, 0xAA) == 0x4EB || AH(m, 0xAA) == 0x558)) {
            func_US2_L04_002E7F28(0x7D, 1);
            return 1;
        }
        if ((GROUND_HERO.i[0x2294 / 4] == 1 ||
             GROUND_HERO.i[0x2294 / 4] == 0x1D || GROUND_HERO.i[0x1500 / 4]) &&
            !(AI(entry, 0x24) & 8)) {
            char *m = func_002A9640(GROUND_HERO.p[0x2290 / 4], 1, 0);
            if (m) func_US2_L00_002A4EF8(func_00283CF0(AF(m, 0x2C)));
            if (!GROUND_HERO.i[0x24CC / 4]) func_US2_L04_002E7F28(0x16, 1);
            GROUND_HERO.h[0x1DC / 2] = 0x4D;
            if (!GROUND_HERO.h[0x21C / 2]) GROUND_HERO.h[0x21C / 2] = 0x12;
            func_L00_002B9B88(20, 0);
            return 0;
        }
        if (GROUND_HERO.i[0x229C / 4] == 0x12) func_US2_L04_002E7F28(0x72, 1);
        else if (GROUND_HERO.i[0x229C / 4] == 0x11) func_US2_L04_002E7F28(0x73, 1);
        else if (AI(entry, 0x24) & 8) func_US2_L04_002E7F28(0x8C, 1);
        else func_US2_L04_002E7F28(0x16, 1);
        if (GROUND_HERO.i[0x2294 / 4] == 0x8C) {
            qzero(&delta);
        } else {
            amount = 0.055000003427267075f;
            if (GROUND_HERO.b[0x1497]) amount = 0.0f;
            func_L00_002B2C58(&delta, special, amount, 0.028333336f);
            if (special && AB(entry, 0x28) == 4)
                func_L00_002D3C68(&delta, &delta, 2.0f);
        }
    }
    func_00282CC0(GROUND_HERO.b + 0xF0, GROUND_HERO.b + 0xF0, &delta);
    func_00282CC0(GROUND_HERO.b + 0x110, GROUND_HERO.b + 0x110, &delta);
    return 1;
}
