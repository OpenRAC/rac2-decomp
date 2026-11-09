/* func_US2_L22_0039EB38, the USA v2.00 copy of func_L22_0039D708: the same C, where rename func_L22_003A15D0 becomes func_US2_L22_003A2A00; rename func_L22_002C9898 becomes func_US2_L22_002C9B20; rename func_002B0A18 becomes func_US2_002B1880; rename func_002AEB60 becomes func_US2_002AF9C8; rename func_002A6C58 becomes func_US2_002A7AA8; rename func_0029B758 becomes func_US2_0029C548. */
/* func_US2_L22_0039EB38 needs its own unit: -G8 (sda reads), -frac2-qcopy with
 * -frac2-qcopy-barrier, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -frac2-sticky-volatile-refs (case 3's a0 in the bc1f slot) and
 * -frac2-hazard-labels (two branches target the nop before a bc1f).
 * The one-pass `do { d = &scratch[0].q; } while (0);` before the 0x43 copy
 * keeps the addiu of sp+32 ahead of the reload, as retail's delay slot has it.
 */
#include "common.h"
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; unsigned char b[16]; unsigned short h[8]; } ScratchD708;
typedef struct { ScratchD708 rows[4]; } MatrixD708;
typedef struct { s32 count; s32 pad[3]; ScratchD708 points[1]; } PathD708;
typedef struct { s8 pad[0x2A0]; s32 paths[44]; } OwnerD708;
typedef struct {
    ScratchD708 direction;
    s32 owner, flags;
    u8 first, second;
    u16 objectId;
    float amount;
    s32 enabled;
    u32 opaque;
} QueryD708;
typedef union {
    MatrixD708 matrix;
    struct { QueryD708 query; ScratchD708 direction; } query_view;
} FirstD708;
#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))
#define NULL ((void *)0)

extern void * func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_0027D330(int);
extern int func_00282948(void *);
extern int func_00282978(int);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_US2_0029C548(int, int);
extern void func_0029CE80(void);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_0029FCC0(int, int, int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void func_US2_002A7AA8(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void func_002A7A00(void *, float, float);
extern void func_002A8BD0(void *, int, int, float);
extern void func_002A8C00(int, int, int, float, int);
extern int func_002A8C28(int, int, int, float, float, float, int, int, int);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_002A8E20(void *, void *);
extern void * func_002A9640(void *, int, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AB6D8(void *, void *);
extern void func_002AC728(void *, void *, float, float, int);
extern int func_US2_002AF9C8(void *, float);
extern float func_002B0360(void *);
extern void func_US2_002B1880(int, int);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_002B3890(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern int func_002E5E58(int, int, void *);
extern void * func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_00335438(void *, void *, int, int, int);
extern void func_L00_002AF7D0(void);
extern int func_L00_002D6900(int);
extern void func_L00_00310C88(void *, void *);
extern void func_L00_003294F0(void *, int);
extern int func_L00_0035F5A0(int, int, int);
extern float func_L02_00329C48(void *, void *, void *);
extern int func_L02_00332630(void *, void *);
extern void func_L02_00333438(void *, void *);
extern void func_L08_004356A0(void *, void *);
extern void func_L11_003404E0(void *);
extern int func_US2_L22_002C9B20(int, int);
extern void func_L22_00328220(void *, void *, void *, void *, float, float, float);
extern void func_L22_003A1E50(void *);
extern void func_L22_003A2988(void *, float);
extern void func_L22_003A2A08(void);
extern void func_L22_003A2A28(void *, int);
extern void func_L22_003A2B90(void *, void *, void *, int);
extern void func_L22_003A45F0(void *, int, int, int, int, float);
extern void func_L22_003A47E8(void *, int, int, int, int);
extern int func_L22_003A4C68(int, int);
extern void func_L22_003A4EE8(void *);
extern int func_L22_003A61A8(void *);
extern void func_L22_003B9128(void *, void *, int);
extern void func_L22_003B9358(int);
extern void * func_L22_003F85A0(void *, void *);
extern void func_US2_L22_003A2A00(s8 *);
extern void func_L22_003A2160(s8 *);
extern s32 func_L22_003A2780(s8 *, s8 *, s128 *);
extern void func_L22_003A2E50(s8 *, s32, s32, f32);
extern void func_L22_003A3D50(s8 *);
extern s32 func_L22_003A4128(s8 *, s128 *);
extern void func_L22_003A4490(s8 *);
extern void func_L22_003A4938(s8 *);
extern void func_L22_003A4CA8(s8 *);
extern void func_L22_003A5BD8(s8 *, s32, s32);
extern void func_L22_003A5F90(s8 *);
extern void func_L22_003A6640(s32, s32, s32, f32);
extern s32 D_00138324 __attribute__((nosda));
extern s8 D_001395E6 __attribute__((nosda));
extern unsigned char D_00189E20[];
extern s16 D_0018A16E __attribute__((nosda));
extern s32 D_0018B694 __attribute__((nosda));
extern s32 D_0018C0B0 __attribute__((nosda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern s32 D_L22_001A8F00 MACRO_ADDR;
extern s32 D_L22_001A903C MACRO_ADDR;
extern void * D_L22_001AF2E0 __attribute__((sda));
extern s32 D_L22_001AF2E4 __attribute__((sda));
extern s32 D_L22_001AF2E8 __attribute__((sda));
extern f32 D_L22_001AF2F4 __attribute__((sda));
extern s32 D_L22_001AF2F8 __attribute__((sda));
extern s32 D_L22_001AF2FC __attribute__((sda));
extern s32 D_L22_001AF300 __attribute__((sda));
extern s32 D_L22_001AF304 __attribute__((sda));
extern f32 D_L22_001AF30C __attribute__((sda));
extern f32 D_L22_001AF310 __attribute__((sda));
extern s32 D_L22_001AF318 __attribute__((sda));
extern s32 D_L22_001AF354 __attribute__((sda));
extern f32 D_L22_001AF358 __attribute__((sda));
extern f32 D_L22_001AF35C __attribute__((sda));
extern s32 D_L22_001AF364 __attribute__((sda));
extern s32 D_L22_001AF368 __attribute__((sda));
extern s32 D_L22_001AF36C __attribute__((sda));
extern f32 D_L22_001AF370 __attribute__((sda));
extern f32 D_L22_001AF388 __attribute__((sda));
extern f32 D_L22_001AF38C __attribute__((sda));
extern f32 D_L22_001AF390 __attribute__((sda));
extern s32 D_L22_001AF394 __attribute__((sda));
extern s32 D_L22_001AF398 __attribute__((sda));
extern f32 D_L22_001AF3D8 __attribute__((sda));
extern f32 D_L22_001AF3DC __attribute__((sda));
extern f32 D_L22_001AF3E0 __attribute__((sda));
extern f32 D_L22_001AF3E4 __attribute__((sda));
extern f32 D_L22_001AF3E8 __attribute__((sda));
extern f32 D_L22_001AF3EC __attribute__((sda));
extern f32 D_L22_001AF3F0 __attribute__((sda));
extern f32 D_L22_001AF3F4 __attribute__((sda));
extern f32 D_L22_001AF3F8 __attribute__((sda));
extern f32 D_L22_001AF3FC __attribute__((sda));
extern f32 D_L22_001AF400 __attribute__((sda));
extern void * D_L22_001B2128 MACRO_ADDR;
extern s16 D_L22_001B2A88 MACRO_ADDR;
extern f32 D_L22_001B2A94 MACRO_ADDR;
extern f32 D_L22_001B2A98 MACRO_ADDR;
extern f32 D_L22_001B2A9C MACRO_ADDR;
extern f32 D_L22_001B2AA0 MACRO_ADDR;
extern f32 D_L22_001B2AA4 MACRO_ADDR;
extern s32 D_L22_001B2AA8 MACRO_ADDR;
extern f32 D_L22_001B2AAC MACRO_ADDR;
extern s32 D_L22_001B2AB0 MACRO_ADDR;
extern void * D_L22_001B2AB4 MACRO_ADDR;
extern unsigned char D_L22_001B9C80[];
extern unsigned char D_L22_001B9EB0[];
extern s128 D_L22_001C00E0 __attribute__((nosda));
extern s8 *D_L22_001FE940[];
extern s32 D_L22_003A6858 __attribute__((nosda));

/* The moby vars block (temp_s6): only the 0x448 member is named. */
typedef struct { u8 pad[0x448]; void *p448; } VarsD708;
void func_US2_L22_0039EB38(s8 *arg0) {
    /* The two matrices and the collision record reuse these eight vectors.
     * Component stores must address their vectors, not unrelated scalar locals. */
    union {
        ScratchD708 vectors[8];
        struct { FirstD708 first; MatrixD708 second; } pair;
        struct { ScratchD708 rotation; MatrixD708 basis; } shifted;
        struct { MatrixD708 basis; ScratchD708 rotation; QueryD708 query; } collision;
    } workspace;
#define scratch workspace.vectors
    ScratchD708 spA0;
    ScratchD708 spB0;
    s32 spC0;
    f32 spC4;
    s32 spC8;
    s32 **temp_v0_11;
    s32 **temp_v0_12;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f20;
    f32 temp_f21;
    f32 var_f12;
    f32 var_f20;
    f32 var_f20_2;
    s128 *temp_s0_3;
    s128 *var_a0_2;
    s128 *var_a0_3;
    s128 *var_v0_3;
    s128 *var_v0_6;
    s128 *var_v1_2;
    s128 var_v0_10;
    u8 *base9;
    u8 *base10;
    f32 frame;
    void *hit;
    s32 mode3A6;
    f32 len8;
    s32 saved398;
    u8 *game;
    u8 *game10;
    s32 temp_a1_3;
    f32 temp_f_dist;
    s16 temp_v0_6;
    s16 temp_v1_6;
    s32 var_a2;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_5;
    s32 *temp_s0_6;
    s32 temp_a0_12;
    s32 temp_a0_14;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_9;
    s32 temp_a1;
    s32 temp_a1_4;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_5;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_11;
    s32 temp_v1_13;
    s32 temp_v1_8;
    s8 **paths;
    s32 var_a1;
    s32 var_a1_10;
    s32 var_a1_13;
    s32 var_a1_14;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_9;
    s32 var_condition_bit;
    s32 var_fp;
    s8 *near;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0_4;
    s32 var_v0_9;
    s8 *temp_s0;
    s8 *temp_s2;
    s8 *var_a0_4;
    s8 *var_s5;
    u16 temp_a0;
    u16 temp_a0_13;
    u16 temp_a1_2;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1_14;
    u16 var_v0_7;
    u16 var_v0_8;
    u8 temp_a0_11;
    u8 temp_v0_4;
    s32 temp_v1_10;
    u8 temp_v1_2;
    s32 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_9;
    void *temp_a0_10;
    void *temp_a0_15;
    void *temp_a0_16;
    void *temp_a0_17;
    void *temp_a0_18;
    void *temp_a0_5;
    void *temp_a0_8;
    void *temp_a2;
    void *temp_s0_2;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_s3;
    void *temp_s3_2;
    void *temp_s4;
    void *temp_s5;
    void *temp_s6;
    void *temp_v1;
    void *temp_v1_12;
    void *temp_v1_15;
    void *temp_v1_7;
    void *var_a0;
    void *var_v1;

    if (D_L22_001AF2E4 == 0) {
        D_00138324 = 0;
        if ((D_L22_001AF2E0 == NULL) && (D_L22_001A8F00 != 2) && (M2C_FIELD(arg0, u8 *, 0x20) == 0)) {
            for (var_a0 = D_L22_001B2128; var_a0 != NULL; var_a0 = M2C_FIELD(var_a0, void **, 0x28)) {
                if (M2C_FIELD(var_a0, s16 *, 0xAA) == 0xF6E) {
                    D_L22_001AF2E0 = var_a0;
                    M2C_FIELD(var_a0, u8 *, 0x30) = 0xFF;
                    temp_v1 = M2C_FIELD(D_L22_001AF2E0, void **, 0x68);
                    M2C_FIELD(temp_v1, s8 *, 8) = 0;
                    M2C_FIELD(temp_v1, s8 *, 0xA) = 0;
                    M2C_FIELD(temp_v1, s8 *, 0xC) = -1;
                }
            }
            M2C_FIELD(M2C_FIELD(D_L22_001AF2E0, void **, 0x68), s8 *, 8) = 0;
            func_L00_003294F0(D_L22_001AF2E0, 1);
            func_002A7750(arg0, 0x27, 0xB);
            func_0027D330(0);
            M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) | 0x41);
            return;
        }
        if (M2C_FIELD(arg0, u8 *, 0x20) == 0x27) {
            for (var_v1 = D_L22_001B2128; var_v1 != NULL; var_v1 = M2C_FIELD(var_v1, void **, 0x28)) {
                if (M2C_FIELD(var_v1, s16 *, 0xAA) == 0xF6E) {
                    return;
                }
            }
            D_L22_001AF2E0 = NULL;
            D_L22_001AF2E4 = 1;
            func_002A7750(arg0, 0, -1);
            M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) & 0xFFBE);
            return;
        }
    }
    {
        temp_s6 = M2C_FIELD(arg0, void **, 0x68);
        func_00282948(&D_L22_001B2AB0);
        if (D_L22_001B2AB0 != 0) {
            M2C_FIELD(arg0, u8 *, 0xA8) = 0xFF;
        }
        temp_s3 = func_002A9640(arg0, 0x30000, 1);
        func_US2_L22_003A2A00(arg0);
        if (D_L22_001AF304 >= 0xC9) {
            func_L22_003A4490(arg0);
        } else {
            if (D_L22_001AF304 == 0) {
                D_L22_001AF2E8 += 1;
            }
            if (M2C_FIELD(arg0, u8 *, 0x20) != 0) {
                {
                    f32 x = M2C_FIELD(temp_s6, f32 *, 0x330);
                    f32 y = M2C_FIELD(temp_s6, f32 *, 0x334);
                    f32 z = M2C_FIELD(temp_s6, f32 *, 0x338);
                    f32 w = M2C_FIELD(temp_s6, f32 *, 0x33C);
                    D_L22_001B2A94 = x;
                    D_L22_001B2A98 = y;
                    D_L22_001B2A9C = z;
                    D_L22_001B2AA0 = w;
                }
                func_L22_003A4938(arg0);
                if (D_L22_001AF318 != 0) {
                    func_00282F20(&scratch[3].q, arg0 + 0xC0, -10.0f);
                    scratch[3].f[3] = 5627.925f;
                    func_002A8C00((s32) &workspace.pair.first.query_view.query, D_0018C0B0, 0x10000, 20.0f, (s32) &scratch[3].q);
                    func_002A8E20(arg0, &workspace.pair.first.query_view.query);
                    D_L22_001AF318 = 0;
                }
            }
            temp_a1 = (s32) M2C_FIELD(temp_s6, f32 *, 0x20);
            D_L22_001AF394 = 0;
            M2C_FIELD(temp_s6, s16 *, 0x41C) = (temp_a1 < ((s32) (D_L22_001B2AA8 * 2) / 3)) && (((s32) D_L22_001B2AA8 / 6) < temp_a1);
            if ((temp_s3 != NULL) && (M2C_FIELD(temp_s3, s32 *, 0x20) != D_0018C0B0)) {
                M2C_FIELD(temp_s6, s32 *, 0x4EC) = 0;
            }
            if (((u32) (M2C_FIELD(arg0, u8 *, 0x95) - 4) < 2U) && (((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U) == 0)) {
                temp_v0 = func_L02_00332630(arg0, (s128 *) (D_00189E20 + 0x80));
                M2C_FIELD(temp_s6, s32 *, 0x3D0) = temp_v0;
            } else {
                func_00282CF0(&scratch[0].q, (s128 *) (D_00189E20 + 0x80), arg0 + 0x10);
                temp_f1 = func_L02_00329C48(arg0, &scratch[0].q, NULL);
                M2C_FIELD(temp_s6, s32 *, 0x3D4) = 0;
                M2C_FIELD(temp_s6, s32 *, 0x3D0) = 0;
                if (temp_f1 <= 0.7853982f) {
                    M2C_FIELD(temp_s6, s32 *, 0x3D0) = 1;
                }
                if (temp_f1 <= 1.0471976f) {
                    M2C_FIELD(temp_s6, s32 *, 0x3D4) = 1;
                }
            }
            if ((temp_s3 != NULL) && (M2C_FIELD(temp_s6, s32 *, 0x3D0) == 0)) {
                M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
            }
            var_a0_2 = (s128 *) (D_00189E20 + 0x80);
            temp_s1 = temp_s6 + 0x3F0;
            M2C_FIELD(temp_s6, s128 *, 0x3F0) = (s128) M2C_FIELD(var_a0_2, s128 *, 0);
            temp_s0_2 = temp_s6 + 0x400;
            func_L22_003A2988(temp_s1, 0.0f);
            M2C_FIELD(temp_s6, s128 *, 0x400) = *(s128 *)(arg0 + 0x10);
            func_L22_003A2988(temp_s0_2, 0.0f);
            M2C_FIELD(temp_s6, f32 *, 0x410) = func_002B0360((arg0 + 0x10));
            M2C_FIELD(temp_s6, f32 *, 0x414) = func_002B0360(M2C_FIELD(var_a0_2, s32 *, 0x2210) + 0x10);
            M2C_FIELD(temp_s6, f32 *, 0x3DC) = func_00282E48(var_a0_2, (arg0 + 0x10));
            M2C_FIELD(temp_s6, f32 *, 0x3E0) = func_00282E48(temp_s1, temp_s0_2);
            if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 50.0f) {
                M2C_FIELD(temp_s6, s32 *, 0x3D8) = func_L22_003A2780(arg0, (arg0 + 0x10), var_a0_2);
            } else {
                M2C_FIELD(temp_s6, s32 *, 0x3D8) = 0;
            }
            if (M2C_FIELD(temp_s6, s32 *, 0x344) != 0) {
                game = D_00189E20;
                M2C_FIELD(game, s16 *, 0x1DC) = 0x7D00;
                func_002A7750(arg0, 0x26, 0xA);
                M2C_FIELD(game, s32 *, 0x2294) = 0;
                func_L00_002AF7D0();
                func_L00_00310C88(M2C_FIELD(game, void **, 0x2290), game + 0x1870);
                M2C_FIELD(game, s32 *, 0x187C) = 0;
                func_US2_L22_002C9B20(0, 1);
                M2C_FIELD(temp_s6, s32 *, 0x344) = 0;
            }
            temp_a0 = M2C_FIELD(temp_s6, u16 *, 0x41E);
            if ((M2C_FIELD(temp_s6, s16 *, 0x41E) == 0) && (M2C_FIELD(temp_s6, f32 *, 0x20) < (f32) ((s32) (D_L22_001B2AA8 * 2) / 3)) && (M2C_FIELD(temp_s6, s16 *, 0x468) == 0)) {
                M2C_FIELD(temp_s6, s16 *, 0x41E) = 1;
                D_L22_001B2A88 = 1;
                D_L22_001AF394 = 1;
                M2C_FIELD(temp_s6, s16 *, 0x468) = 1;
            } else if (((s16) temp_a0 == 1) && (M2C_FIELD(temp_s6, f32 *, 0x20) < (f32) ((s32) D_L22_001B2AA8 / 3)) && (M2C_FIELD(temp_s6, s16 *, 0x46A) == 0)) {
                saved398 = D_L22_001AF398;
                M2C_FIELD(temp_s6, s16 *, 0x41E) = 2;
                D_L22_001B2A88 = 2;
                {
                    s32 one = (s16) temp_a0;
                    D_L22_001AF394 = one;
                    M2C_FIELD(temp_s6, s32 *, 0x464) = saved398;
                    M2C_FIELD(temp_s6, s16 *, 0x46A) = one;
                }
            }
            temp_a0_3 = M2C_FIELD(temp_s6, s32 *, 0x440);
            func_002A8C28(temp_a0_3, temp_a0_3 + 0x10, 0x04000000, 5.4f, 1.0f, 1.0f, 0, 1, 0);
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x95);
            switch (temp_v1_2) {                    /* switch 1 */
            case 0:                                 /* switch 1 */
                if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) < 35.0f) && (M2C_FIELD(temp_s6, s32 *, 0x3D4) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                    if ((M2C_FIELD(temp_s6, s32 *, 0x418) != 0) && (M2C_FIELD(arg0, u8 *, 0x20) != 0xF)) {
                        func_002A7750(arg0, 6, 4);
                    } else if ((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2)) {
                        func_002A7750(arg0, 0x13, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x41C) == 0) {
                        if ((M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0) || (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0)) {
                            func_002A7750(arg0, 0x1D, 3);
                        } else if (func_002A77E0(2) == 0) {
                            func_002A7750(arg0, 0x12, 9);
                        } else if (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0) {
                            func_002A7750(arg0, 0x1C, 3);
                        } else {
                            func_002A7750(arg0, 0x12, 9);
                        }
                    } else if (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) D_L22_001B2AA8 / 6)) {
                        func_002A7750(arg0, 0x12, 9);
                    } else if ((M2C_FIELD(temp_s6, s16 *, 0x32A) / 2 < M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC)) || (M2C_FIELD(temp_s6, s16 *, 0x32E) / 2 < M2C_FIELD(D_L22_001B2AB4, s32 *, 8))) {
                        func_002A7750(arg0, 0x1D, 3);
                    } else if ((func_002A77E0(2) == 0) && ((M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0) || (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0))) {
                        func_002A7750(arg0, 0x1D, 3);
                    } else if ((func_002A77E0(2) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0)) {
                        func_002A7750(arg0, 0x1C, 3);
                    } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                        func_002A7750(arg0, 0x12, 9);
                    }
                }
                break;
            case 9:                                 /* switch 1 */
                if (((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x2EU) && (func_L22_003A61A8(arg0) != 0)) {
                    if ((M2C_FIELD(temp_s6, s16 *, 0x41E) != 2) || (M2C_FIELD(temp_s6, s32 *, 0x464) == 0)) {
                        func_L22_003A45F0(arg0, 0xD, 0, 4, 3, D_L22_001AF3E8);
                        func_002A7750(arg0, 0x1F, 4);
                    }
                }
                break;
            case 3:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                    func_002A7750(arg0, 6, 4);
                } else if (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) D_L22_001B2AA8 / 6)) {
                    func_002A7750(arg0, 0x12, 9);
                }
                break;
            case 4:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                    func_002A7750(arg0, 6, 4);
                } else if (((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2))
                        || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) D_L22_001B2AA8 / 6))
                        || ((D_0018A16E >= 0x15) && (M2C_FIELD(arg0, u8 *, 0x20) == 0x1E))) {
                    func_002A7750(arg0, 0x12, 9);
                }
                break;
            case 6:                                 /* switch 1 */
                if (M2C_FIELD(temp_s6, s32 *, 0x418) == 0) {
                    func_002A7750(arg0, 0x1E, 4);
                }
                break;
            case 5:                                 /* switch 1 */
                func_L22_003A5BD8(arg0, 2, 1);
                func_L22_003A5BD8(arg0, 3, 0);
                break;
            case 8:                                 /* switch 1 */
                len8 = func_00282DF0(((s128 *) (temp_s6 + 0xE0)));
                if (len8 > 0.0f) {
                    var_v0_10 = 0;
                    if (M2C_FIELD(temp_s6, f32 *, 0x410) < D_L22_001B2AA4) {
                        func_L22_003A2988((arg0 + 0x10), 0.0f);
                        var_v0_10 = 0;
                    }
                    scratch[2].q = var_v0_10;
                    scratch[2].f[2] = M2C_FIELD(temp_s6, f32 *, 0x94);
                    var_v0_10 = scratch[2].q;
                    scratch[1].q = var_v0_10;
                    func_00283098(&scratch[1].q, &scratch[1].q, arg0 + 0xC0);
                    func_00282CC0(&scratch[1].q, &scratch[1].q, (arg0 + 0x10));
                    func_00282F20(&scratch[0].q, ((s128 *) (temp_s6 + 0xE0)), 4.0f);
                    func_00282CC0(&scratch[1].q, &scratch[1].q, &scratch[0].q);
                    func_002A8C28((s32) arg0, (s32) &scratch[1].q, 0x90000, 5.0f, 100.0f, 0.0f, 0, 1, 0);
                }
                if (func_002B3890(arg0) != 0) {
                    M2C_FIELD(temp_s6, s16 *, 0x26) = 0x1E;
                    if (temp_s3 != NULL) {
                        if ((func_00282DF0(((s128 *) (temp_s6 + 0xE0))) > 0.0f) && ((M2C_FIELD(temp_s6, f32 *, 0x20) - M2C_FIELD(temp_s3, f32 *, 0x2C)) <= 0.0f)) {
                            func_00282F20(((s128 *) (temp_s6 + 0xE0)), ((s128 *) (temp_s6 + 0xE0)), 0.6f);
                        }
                        if (M2C_FIELD(temp_s3, f32 *, 0x2C) == 50.0f) {
                            func_L00_0035F5A0(0x13, 0, 0);
                        }
                        if ((M2C_FIELD(D_0018C0B0, u8 *, 0x43) == 4) && (M2C_FIELD(temp_s3, s32 *, 0x20) == D_0018C0B0)) {
                            func_00282CF0(&scratch[0].q, temp_s6 + 0x400, temp_s6 + 0x3F0);
                            func_00282F20(((s128 *) (temp_s6 + 0xE0)), &scratch[0].q, D_L22_001AF3F8);
                            func_0032C700(M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 1, 0xA, 0xA, 0xA, 0x14, 0x32, 0, 1.2f, 20.0f, 0, 1, 0, 0);
                        }
                    }
                    func_L22_003A45F0(arg0, (s32) M2C_FIELD(arg0, u8 *, 0x43), 0, 4, 2, 1.0f);
                    func_002A7470(((VarsD708 *) temp_s6)->p448, 6, 0, 4);
                    M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 0.9f;
                    M2C_FIELD(arg0, f32 *, 0x48) = 0.9f;
                    temp_a0_11 = M2C_FIELD(arg0, u8 *, 0x43);
                    if ((temp_a0_11 == 4) || (temp_a0_11 == 8)) {
                        func_L22_003B9358((s32) arg0);
                    }
                } else if ((M2C_FIELD(((VarsD708 *) temp_s6)->p448, u8 *, 0x60) & 2) && (func_002A77E0(3) == 0)) {
                    func_002A7470(((VarsD708 *) temp_s6)->p448, 7, 0, 4);
                }
                if (M2C_FIELD(temp_s6, s16 *, 0x43A) == 0) {
                    M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                }
                M2C_FIELD(temp_s6, f32 *, 0x3E4) = M2C_FIELD(temp_s6, f32 *, 0x3E8) = 0.0f;
                temp_v0_8 = func_002B1C20(arg0, temp_s6 + 0x60);
                if (temp_v0_8 & 1) {
                    M2C_FIELD(temp_s6, s32 *, 0x344) = 1;
                } else if (temp_v0_8 & 2) {
                    M2C_FIELD(temp_s6, s32 *, 0x37C) = 0xF0;
                    func_002A7750(arg0, 5, 0);
                    func_L22_003A45F0(arg0, 0, 0, 4, 3, 1.0f);
                }
                goto block_184;
            case 10:                                /* switch 1 */
                game10 = D_00189E20;
                M2C_FIELD(game10, s16 *, 0x1E0) = 0xA;
                temp_v1_12 = M2C_FIELD(temp_s6, void **, 0x388);
                M2C_FIELD(temp_v1_12, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_12, u16 *, 0x34) | 0x41);
                if (func_002B3868(arg0) != 0) {
                    if ((M2C_FIELD(temp_s6, s32 *, 0x4EC) != 0) && (D_001A7A60[8] == 0)) {
                        D_001A7A60[8] = 1;
                        func_002E5E58(1, 0, NULL);
                        func_US2_002B1880(0x1233, -1);
                        D_L22_001A903C = 1;
                    }
                    func_0027D330(D_L22_001AF2F8);
                    goto block_183;
                }
                temp_a0_13 = M2C_FIELD(arg0, u16 *, 0x96);
                temp_v0_9 = (s32) D_L22_001AF2F8 / 2;
                if (temp_v0_9 < (s32) temp_a0_13) {
                    if ((func_US2_002AF9C8(arg0, 27.0f) != 0) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1) && ((((s32) D_L22_001AF2F8 / 2) - 4) < (s32) M2C_FIELD(arg0, u16 *, 0x96))) {
                        func_002A8C28((s32) arg0, (s32) (arg0 + 0x10), 0x90000, 25.0f, 100.0f, 0.0f, 0, 1, 0);
                        func_L02_00333438(arg0, game10 + 0x80);

                        func_US2_002A7AA8(arg0, 0, 3);
                        func_002AC728(arg0, (arg0 + 0x10), 2.0f, 7.0f, -1);
                        for (var_s0_2 = 0; var_s0_2 < 5; var_s0_2++) {
                            func_002A7A00(&scratch[0].q, D_L22_001AF388 * 0.016666668f, D_L22_001AF38C * 0.016666668f);
                            scratch[0].f[2] = func_00282C48(scratch[0].f[2]) * D_L22_001AF390;
                            func_00283098(&scratch[0].q, &scratch[0].q, M2C_FIELD(temp_s6, s32 *, 0x440) + 0xC0);
                            temp_a0_14 = M2C_FIELD(temp_s6, s32 *, 0x440);
                            temp_v0_11 = func_00273730((void *) temp_a0_14, 1, (s32) M2C_FIELD(temp_a0_14, s16 *, 0xAA), var_s0_2, temp_a0_14 + 0x10, temp_a0_14 + 0xF0, &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)temp_v0_11 + 0x64) = &D_L22_003A6858;
                        }
                        for (var_s0_3 = 0; var_s0_3 < 2; var_s0_3++) {
                            func_002A7A00(&scratch[0].q, D_L22_001AF388 * 0.016666668f, D_L22_001AF38C * 0.016666668f);
                            scratch[0].f[2] = func_00282C48(scratch[0].f[2]) * D_L22_001AF390;
                            func_00283098(&scratch[0].q, &scratch[0].q, ((void *) (arg0 + 0xC0)));
                            temp_v0_12 = func_00273730(arg0, 1, (s32) M2C_FIELD(arg0, s16 *, 0xAA), var_s0_3, (arg0 + 0x10), ((void *) (arg0 + 0xF0)), &scratch[0].q, 0xFF, 30.0f, 15.0f);
                            *(s32 **)((s8 *)temp_v0_12 + 0x64) = &D_L22_003A6858;
                        }
                        func_0032C700(M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0, 0x73, 0x50, 0x46, 0x4E, 0x4B, 1, 7.5f, 20.0f, 1, 1, 0, 0);
                        func_0032C700((arg0 + 0x10), 1, 0x2D, 0x28, 0x28, 0x28, 0x3A, 1, 3.0f, 20.0f, 1, 1, 0, 0);
                        M2C_FIELD(arg0, u16 *, 0x34) = (u16) (M2C_FIELD(arg0, u16 *, 0x34) | 0x41);
                        temp_a0_15 = M2C_FIELD(temp_s6, void **, 0x388);
                        M2C_FIELD(temp_a0_15, u16 *, 0x34) = (u16) (M2C_FIELD(temp_a0_15, u16 *, 0x34) | 0x41);
                        temp_v1_13 = M2C_FIELD(temp_s6, s32 *, 0x440);
                        M2C_FIELD(temp_v1_13, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_13, u16 *, 0x34) | 0x41);
                        temp_a0_16 = M2C_FIELD(temp_s6, void **, 0x444);
                        M2C_FIELD(temp_a0_16, u16 *, 0x34) = (u16) (M2C_FIELD(temp_a0_16, u16 *, 0x34) | 0x41);
                        temp_a0_17 = ((VarsD708 *) temp_s6)->p448;
                        M2C_FIELD(temp_a0_17, s128 *, 0x10) = *(s128 *)(arg0 + 0x10);
                        func_002A7470(temp_a0_17, 6, 0, 4);
                        {
                            f32 v = D_L22_001AF30C;
                            M2C_FIELD(((VarsD708 *) temp_s6)->p448, f32 *, 0x48) = 3.2f;
                            D_L22_001B2AAC = v;
                            func_L22_003A2988(((VarsD708 *) temp_s6)->p448 + 0x10, v);
                        }
                        goto block_183;
                    }
                    temp_v1_14 = M2C_FIELD(arg0, u16 *, 0x96);
                    if (temp_v1_14 >= 0x169U) {
                        func_0029F338(M2C_FIELD(temp_s6, void **, 0x388));
                        M2C_FIELD(temp_s6, void **, 0x388) = NULL;
                        func_0029F338((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                        M2C_FIELD(temp_s6, s32 *, 0x440) = 0;
                        func_0029F338(M2C_FIELD(temp_s6, void **, 0x444));
                        M2C_FIELD(temp_s6, void **, 0x444) = NULL;
                        func_0029F338(((VarsD708 *) temp_s6)->p448);
                        ((VarsD708 *) temp_s6)->p448 = NULL;
                        func_US2_0029C548(0, 0);
                        D_001395E6 = 1;
                        func_0029CE80();
                        func_0029F338(arg0);
                        return;
                    } else {
                        if ((temp_v1_14 >= 0x105U) && (M2C_FIELD(arg0, u16 *, 0x34) & 1) && (temp_a0_18 = ((VarsD708 *) temp_s6)->p448, (((M2C_FIELD(temp_a0_18, u16 *, 0x34) ^ 1) & 1) != 0))) {
                            temp_f12_3 = D_L22_001B2AAC - D_L22_001AF310;
                            D_L22_001B2AAC = temp_f12_3;
                            if (temp_f12_3 > 0.0f) {
                                func_L22_003A2988(temp_a0_18 + 0x10, temp_f12_3);
                                M2C_FIELD(((VarsD708 *) temp_s6)->p448, f32 *, 0x48) = 3.2f;
                                func_002A05A8(((VarsD708 *) temp_s6)->p448);
                                func_002A0F48(((VarsD708 *) temp_s6)->p448);
                            } else {
                                if ((M2C_FIELD(temp_a0_18, u16 *, 0x34) ^ 1) & 1) {
                                    func_00282D30(&scratch[0].q, temp_a0_18 + 0xC0, 2.2f);
                                    func_00282CC0(&scratch[0].q, &scratch[0].q, ((VarsD708 *) temp_s6)->p448 + 0x10);
                                    func_L22_003A2988(&scratch[0].q, 0.5f);
                                    func_0032C700(&scratch[0].q, 1, 0xA, 0xA, 0xA, 0xA, 0x14, 0, 0.9f, 20.0f, 0, 0, 0, 0);
                                    func_002E5CF8(D_L22_001AF2FC, 0, arg0);
                                    temp_v1_15 = ((VarsD708 *) temp_s6)->p448;
                                    M2C_FIELD(temp_v1_15, u16 *, 0x34) = (u16) (M2C_FIELD(temp_v1_15, u16 *, 0x34) | 0x41);
                                }
                            }
                        } else {
                            if (!(M2C_FIELD(arg0, u16 *, 0x96) & 7) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1)) {
                                if (func_002A77E0(2) != 0) {
                                    func_0029FCC0((s32) arg0, func_002A77E0(4), (s32) &scratch[0].q);
                                } else {
                                    func_0029FCC0(M2C_FIELD(temp_s6, s32 *, 0x440), func_002A77E0(6), (s32) &scratch[0].q);
                                }
                                func_0032C700(&scratch[0].q, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, func_002A7878(1.0f, 1.9f), 20.0f, 0, 0, 0, 0);
                            }
                            if (!(M2C_FIELD(arg0, u16 *, 0x96) & 0xF) && ((M2C_FIELD(arg0, u16 *, 0x34) ^ 1) & 1)) {
                                func_002E5CF8(D_L22_001AF300, 0, arg0);
                            }
                        }
                        goto block_183;
                    }
                } else {
                    temp_v0_10 = temp_v0_9 - 4;
                    if (temp_a0_13 == temp_v0_10) {
                        func_0027D330(1);
                        func_L22_003A2988((arg0 + 0x10), 0.0f);
                        scratch[4].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0);
                        scratch[5].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0x10);
                        scratch[6].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0x20);
                        qzero_nc(&scratch[7].q);
                        func_002AB6D8(&workspace.pair.second, &scratch[0].q);
                        temp_s2 = (arg0 + 0x10);
                        func_00335438(D_L22_001B9C80, &scratch[0].q, 1, 0, 0);
                        func_L22_003A45F0(arg0, 0xE, 0, 4, 3, 0.6f);
                        M2C_FIELD(temp_s6, f32 *, 0x138) = 0.01f;
                        func_00282CF0(&scratch[7].q, temp_s6 + 0x3F0, temp_s2);
                        func_00282F20(&scratch[6].q, &scratch[7].q, -(D_L22_001AF2F4 * 33.0f));
                        func_00282CC0(&scratch[6].q, &scratch[6].q, temp_s2);
                        func_L22_003A2988(&scratch[6].q, 2.0f);
                        func_00282F20(&scratch[5].q, &scratch[7].q, -(D_L22_001AF2F4 * 55.0f));
                        func_00282CC0(&scratch[5].q, &scratch[5].q, temp_s2);
                        func_L22_003A2988(&scratch[5].q, D_L22_001AF2F4 * 45.0f);
                        func_00282F20(&scratch[7].q, &scratch[7].q, 1.0f);
                        scratch[0].q = scratch[7].q;
                        {
                            u8 *g = D_00189E20;
                            scratch[1].q = M2C_FIELD(M2C_FIELD(g, void **, 0x2290), s128 *, 0xD0);
                        }

                        qzero_nc(&scratch[3].q);
                        func_00282DD8(&scratch[2].q, &scratch[0].q, &scratch[1].q);
                        func_002AB6D8(&workspace.pair.first.matrix, &scratch[4].q);
                        func_003353C8(&scratch[4].q);
                        func_00335370(&scratch[5].q);
                    } else if (temp_v0_10 < (s32) temp_a0_13) {
                        scratch[1].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0);
                        scratch[2].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0x10);
                        scratch[3].q = M2C_FIELD(D_L22_001B9EB0, s128 *, 0x20);
                        qzero_nc(&scratch[4].q);
                        func_002AB6D8(&workspace.shifted.basis, &workspace.shifted.rotation);
                        func_00335438(D_L22_001B9C80, &scratch[0].q, 1, 0, 0);
                        func_00282CF0(&scratch[0].q, (arg0 + 0x10), D_L22_001B9C80);
                        func_00282F20(&scratch[0].q, &scratch[0].q, 1.0f);
                        scratch[2].q = M2C_FIELD(arg0, s128 *, 0xE0);
                        qzero_nc(&scratch[3].q);
                        temp_s3_2 = D_00189E20;
                        func_00282F20(&scratch[0].q, &scratch[0].q, 1.0f);
                        func_00282F20(&scratch[2].q, &scratch[2].q, 1.0f);
                        func_00282DD8(&scratch[1].q, &scratch[0].q, &scratch[2].q);
                        func_00282F20(&scratch[1].q, &scratch[1].q, 1.0f);
                        func_002AB6D8(&workspace.pair.first.matrix, &scratch[4].q);
                        func_003353C8(&scratch[4].q);
                        func_0027D330(1);
                        func_002A8BD0(&workspace.collision.query, M2C_FIELD(temp_s3_2, s32 *, 0x2290), 0xB0000, 50.0f);
                        scratch[6].b[8] = 7;
                        scratch[6].b[9] = 1;

                        scratch[6].h[5] = M2C_FIELD(M2C_FIELD(temp_s3_2, s32 *, 0x2290), u16 *, 0xAA);
                        func_002A8C28((s32) arg0, (s32) D_L22_001B9C80, 0x90000, 10.0f, 100.0f, 0.0f, 0, 1, 0);
                        temp_s4 = D_L22_001B9C80 + 0x240;
                        func_002761F8(D_L22_001B9C80, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        temp_s5 = D_L22_001B9C80 + 0x250;
                        func_00282D30(&spA0, M2C_FIELD(temp_s3_2, s32 *, 0x2290) + 0xE0, 4.0f);
                        func_00282CC0(&spA0, &spA0, temp_s3_2 + 0x80);
                        func_002761F8(&spA0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        temp_f20 = D_L22_001AF2F4 * 6.875f;
                        temp_f21 = -temp_f20;
                        func_00282D30(&spB0, temp_s4, temp_f20);
                        func_00282CC0(&spB0, &spB0, D_L22_001B9C80);
                        func_002761F8(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        func_00282D30(&spB0, temp_s4, temp_f21);
                        func_00282CC0(&spB0, &spB0, D_L22_001B9C80);
                        func_002761F8(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        func_00282D30(&spB0, temp_s5, temp_f20);
                        func_00282CC0(&spB0, &spB0, D_L22_001B9C80);
                        func_002761F8(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                        func_00282D30(&spB0, temp_s5, temp_f21);
                        func_00282CC0(&spB0, &spB0, D_L22_001B9C80);
                        func_002761F8(&spB0, M2C_FIELD(temp_s6, s32 *, 0x440) + 0x10, 0x10, 0, &workspace.collision.query);
                    } else {
                        func_0027D330(1);
                    }
block_183:
                    qzero_nc(((s128 *) (temp_s6 + 0xE0)));
                    func_L11_003404E0(arg0);
                    goto block_184;
                }
                break;
            }
block_184:
                temp_v0_4 = M2C_FIELD(arg0, u8 *, 0x20);
                switch (temp_v0_4) {                /* switch 2 */
                case 5:                             /* switch 2 */
                    if ((M2C_FIELD(temp_s6, s32 *, 0x464) == 0) || (M2C_FIELD(temp_s6, s16 *, 0x41E) != 2)) {
                        if (M2C_FIELD(temp_s6, s16 *, 0x380) != 0) {
                            func_00282978((s32) (temp_s6 + 0x380));
                        } else {
                            temp_f1_4 = D_L22_001AF3EC;
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (D_00189E20 + 0x80);
                            if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < temp_f1_4) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 0)) {
                                func_002A7750(arg0, 6, 0);
                            } else {
                                func_002A7750(arg0, 7, 0);
                            }
                        }
                        M2C_FIELD(temp_s6, s32 *, 0x190) = 0;
                        func_L22_003A45F0(arg0, 0xC, 0, 4, 3, 1.0f);
                    } else {
                    case 18:                        /* switch 2 */
                        if ((M2C_FIELD(arg0, u8 *, 0x94) != 0x12) && (M2C_FIELD(arg0, u8 *, 0x43) != 0xB)) {
                            func_L22_003A45F0(arg0, 0xB, 0, 4, 3, 1.0f);
                        }
                        func_L22_003A4EE8(arg0);
                        func_002A7750(arg0, 0x13, 9);
                    }
                    break;
                case 19:                            /* switch 2 */
                    temp_a0_4 = M2C_FIELD(temp_s6, s32 *, 0x440);
                    if (M2C_FIELD(temp_a0_4, u8 *, 0x43) == 3) {
                        if ((M2C_FIELD(temp_a0_4, u8 *, 0x60) & 2) && ((M2C_FIELD(D_L22_001B2AB4, s32 *, 8) == 0) || (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 70.0f))) {
                            func_L22_003A45F0(arg0, 0xB, (s32) func_0029F530(arg0), 4, 2, 1.0f);
                        } else if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                            func_L22_003A47E8(arg0, 1, D_0018C0B0, 0, 0);
                        } else if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                            func_L22_003A47E8(arg0, 2, D_0018C0B0, 0, 0);
                        }
                    } else if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) < 70.0f) && (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x464) == 0)) {
                        func_L22_003A45F0(arg0, 3, 0, 4, 2, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 7, 0, 4);
                    }
                    if (func_00282E48((arg0 + 0x10), M2C_FIELD(temp_s6, s128 **, 0x3AC)) < 8.0f) {
                        func_002A7750(arg0, 0x14, 9);
                        break;
                    }
                    func_L22_003A2160(arg0);
                    if (((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1FU) && (M2C_FIELD(temp_s6, f32 *, 0x43C) <= M2C_FIELD(temp_s6, f32 *, 0x140))) {
                        func_00282CF0(&scratch[0].q, (arg0 + 0x10), (s128 *) (D_00189E20 + 0x80));
                        func_00282F20(&scratch[0].q, &scratch[0].q, 1.0f);
                        if ((func_00282DB0(arg0 + 0xC0, &scratch[0].q) < -0.5f) && (func_00282DF0(&scratch[0].q) < 10.0f)) {
                            func_002A7750(arg0, 0x21, 9);
                            if (M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0) {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                            } else if (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0) {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                            } else {
                                M2C_FIELD(temp_s6, s16 *, 0x3A6) = 2;
                            }
                            M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                        }
                    }
                    break;
                case 20:                            /* switch 2 */
                    if ((func_002B3868(arg0) != 0) && (M2C_FIELD(arg0, u8 *, 0x43) == 4)) {
                        func_L22_003A45F0(arg0, 0, 0, 0x14, 3, 1.0f);
                    } else if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1FU) {
                        if (func_L22_003A4128(arg0, &scratch[0].q) != 0) {
                            M2C_FIELD(temp_s6, s128 *, 0x3B0) = (s128) scratch[0].q;
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (temp_s6 + 0x3B0);
                            func_002A7750(arg0, 0x15, 9);
                            func_L22_003A45F0(arg0, 0xB, 0, 4, 3, 1.0f);
                        } else {
                            func_L22_003A5F90(arg0);
                            if ((((f32) ((s32) (D_L22_001B2AA8 * 2) / 3) <= M2C_FIELD(temp_s6, f32 *, 0x20)) || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) D_L22_001B2AA8 / 6))
                                    || ((func_002A77E0(2) == 0) && ((M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0) || (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0))))
                                && ((M2C_FIELD(temp_s6, s32 *, 0x464) == 0) || (M2C_FIELD(temp_s6, s16 *, 0x41E) != 2))) {
                                if (((f32) ((s32) D_L22_001B2AA8 / 6) < M2C_FIELD(temp_s6, f32 *, 0x20))
                                        && ((M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0) || (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0))
                                        && (func_002A77E0(5) == 0)) {
                                    func_002A7750(arg0, 0x1D, 3);
                                } else {
                                    func_002A7750(arg0, 5, 0);
                                }
                            } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                                func_002A7750(arg0, 0x12, 9);
                            }
                        }
                    }
                    break;
                case 21:                            /* switch 2 */
                    if (func_00282E48((arg0 + 0x10), M2C_FIELD(temp_s6, s128 **, 0x3AC)) < 8.0f) {
                        func_002A7750(arg0, 0x16, 9);
                        func_L22_003A45F0(arg0, 0, 0, 0x14, 3, 1.0f);
                        break;
                    }
                    func_L22_003A2160(arg0);
                    break;
                case 22:                            /* switch 2 */
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1FU) {
                        if (((f32) ((s32) (D_L22_001B2AA8 * 2) / 3) <= M2C_FIELD(temp_s6, f32 *, 0x20)) || (M2C_FIELD(temp_s6, f32 *, 0x20) <= (f32) ((s32) D_L22_001B2AA8 / 6))) {
                            func_002A7750(arg0, 5, 0);
                        } else if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 55.0f) {
                            func_002A7750(arg0, 0x12, 9);
                        } else {
                            func_002A7750(arg0, 0x14, 9);
                        }
                    }
                    break;
                case 7:                             /* switch 2 */
                    if (M2C_FIELD(temp_s6, f32 *, 0x3E0) < 33.0f) {
                        func_002A7750(arg0, 0x1E, 4);
                    } else {
                        func_L22_003A2160(arg0);
                    }
                    break;
                case 6:                             /* switch 2 */
                    temp_f1_4 = M2C_FIELD(temp_s6, f32 *, 0x3E0);
                    if (M2C_FIELD(temp_s6, s32 *, 0x418) != 0) {
                        if (temp_f1_4 < 20.0f) {
                            func_002A7750(arg0, 0xF, 6);
                        } else {
                            func_L22_003A2160(arg0);
                        }
                    } else if (temp_f1_4 < D_L22_001AF3EC) {
                        func_002A7750(arg0, 0x1E, 4);
                    } else {
                        func_L22_003A2160(arg0);
                    }
                    break;
                case 28:                            /* switch 2 */
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 0xB, 0, 6, 3, 1.0f);
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < D_L22_001AF3EC) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                        func_002A7750(arg0, 0x1E, 4);
                    }
                    M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (D_00189E20 + 0x80);
                    func_L22_003A2160(arg0);
                    break;
                case 29:                            /* switch 2 */
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 0xC, 0, 0x14, 3, 1.0f);
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3E0) < 29.0f) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                        func_002A7750(arg0, 0x1E, 4);
                    }
                    M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (D_00189E20 + 0x80);
                    func_L22_003A2160(arg0);
                    break;
                case 31:                            /* switch 2 */
                    temp_v1_3 = M2C_FIELD(arg0, u8 *, 0x43);
                    switch (temp_v1_3) {            /* switch 3; irregular */
                    case 9:                         /* switch 3 */
                        if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) > 7.0f) && (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            func_002A8D70((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 3, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            func_L22_003A2160(arg0);
                            func_L22_003A45F0(arg0, 0xA, 0, 4, 3, D_L22_001AF3E8);
                        }
                        if ((func_0029F530(arg0) > 0.0f) && (func_0029F530(arg0) < 23.0f)) {
                            func_L02_00333438(arg0, (s128 *) (D_00189E20 + 0x80));
                        }
                        break;
                    case 10:                        /* switch 3 */
                        if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) > 7.0f) && (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            func_002A8D70((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 4, 4.0f, 10.0f, 0x10007, 1.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            func_L22_003A45F0(arg0, 0xD, 0, 4, 3, D_L22_001AF3E8);
                        }
                        func_L02_00333438(arg0, (s128 *) (D_00189E20 + 0x80));
                        break;
                    case 13:                        /* switch 3 */
                        if (func_002B3868(arg0) != 0) {
                            D_L22_001B2AB0 = 0;
                        }
                        if (M2C_FIELD(arg0, u8 *, 0x60) & 2) {
                            if ((D_L22_001B2AB0 != 0) && ((func_002A77E0(4) == 0) || ((f32) (D_0018B694 * 7) < M2C_FIELD(temp_s6, f32 *, 0x20)))) {
                                if ((M2C_FIELD(temp_s6, f32 *, 0x20) == (f32) M2C_FIELD(temp_s6, s16 *, 0x326)) && (D_0018B694 < 0x64)) {
                                    func_002A7750(arg0, 4, 2);
                                } else {
                                    func_002A7750(arg0, 3, 2);
                                }
                            } else if (func_L22_003A61A8(arg0) != 0) {
                                func_L22_003A45F0(arg0, 0xD, 0, 4, 3, D_L22_001AF3E8);
                                func_002A7750(arg0, 0x1F, 4);
                            } else {
                                func_002A7750(arg0, 0x12, 9);
                            }
                        } else if (D_L22_001AF3F0 < func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440))) {
                            if (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < D_L22_001AF3F4) {
                                func_0029FCC0(M2C_FIELD(temp_s6, s32 *, 0x440), 4, (s32) &scratch[1].q);
                                func_0029FCC0(M2C_FIELD(temp_s6, s32 *, 0x440), 3, (s32) &scratch[0].q);
                                func_00282CC0(&scratch[2].q, &scratch[0].q, &scratch[1].q);
                                func_00282D30(&scratch[2].q, &scratch[2].q, 0.5f);
                                M2C_FIELD(arg0, s32 *, 0x98) = 0;
                                func_002A8C28((s32) arg0, (s32) &scratch[2].q, 0x10007, 4.0f, 100.0f, 14.5f, 0, 2, 0);
                                {
                                    u8 *g = D_00189E20;
                                    f32 reach = D_L22_001AF358;
                                    M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                                    func_00282D30(&scratch[3].q, M2C_FIELD(g, void **, 0x2290) + 0xE0, reach);
                                    func_00282CC0(&scratch[3].q, &scratch[3].q, g + 0x80);
                                }

                                if (func_00282E48(&scratch[2].q, &scratch[3].q) < D_L22_001AF35C) {
                                    func_L00_002D6900(0x2B);
                                    D_L22_001B2AB0 = D_L22_001AF354;
                                }
                            }
                        }
                        func_002B60B0(arg0, D_L22_001AF3E0 * 0.00027777778f, D_L22_001AF3E4 * 0.016666668f, D_L22_001AF3D8 * 0.0000048481375f, D_L22_001AF3DC * 0.00029088825f);
                        func_L02_00333438(arg0, (s128 *) (D_00189E20 + 0x80));
                        break;
                    }
                    if ((M2C_FIELD(arg0, u8 *, 0x95) != 6) && (M2C_FIELD(temp_s6, f32 *, 0x3DC) > D_L22_001AF3EC) && (D_L22_001B2AB0 == 0)) {
                        func_002A7750(arg0, 0x12, 9);
                    }
                    break;
                case 15:                            /* switch 2 */
                    func_L02_00333438(arg0, (s128 *) (D_00189E20 + 0x80));
                    func_00282D30(&scratch[0].q, arg0 + 0xC0, 3.0f);
                    func_00282CC0(&scratch[0].q, &scratch[0].q, (arg0 + 0x10));
                    if (func_L22_003A2780(arg0, (arg0 + 0x10), &scratch[0].q) == 0) {
                        func_L22_003A45F0(arg0, 9, 0, 4, 3, D_L22_001AF3E8);
                        func_002A7750(arg0, 0x1F, 6);
                        break;
                    }
                    break;
                case 32:                            /* switch 2 */
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 3, 0, 4, 2, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 1, 0, 4);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = func_002A7820(0x78, 0xF0);
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(((VarsD708 *) temp_s6)->p448, u8 *, 0x60) & 2) {
                        if (func_002A77E0(4) == 0) {
                            func_002A7470(((VarsD708 *) temp_s6)->p448, 7, 0, 4);
                        } else {
                            func_002A7470(((VarsD708 *) temp_s6)->p448, 1, 0, 4);
                        }
                    }
                    if ((M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) || (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) == 0) || (M2C_FIELD(temp_s6, s32 *, 0x3D8) == 0)
                        || ((temp_f1_5 = M2C_FIELD(temp_s6, f32 *, 0x3DC)) > 60.0f)
                        || ((temp_a0_6 = M2C_FIELD(temp_s6, s32 *, 0x440), (M2C_FIELD(temp_a0_6, u8 *, 0x60) & 2)) && (temp_f1_5 < D_L22_001AF3EC))) {
                        func_002A7750(arg0, 5, 0);
                    } else if (M2C_FIELD(temp_a0_6, u8 *, 0x60) & 2) {
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                    } else if (M2C_FIELD(temp_a0_6, u8 *, 0x43) == 3) {
                        if ((func_0029F530((void *) temp_a0_6) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                            func_L22_003A47E8(arg0, 1, D_0018C0B0, 0, 0);
                        } else if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                            func_L22_003A47E8(arg0, 2, D_0018C0B0, 0, 0);
                        }
                    } else {
                        func_00282978((s32) (temp_s6 + 0x386));
                        if (M2C_FIELD(temp_s6, s16 *, 0x386) <= 0) {
                            func_L22_003A45F0(arg0, 3, 0, 4, 2, 1.0f);
                            func_002A7470(((VarsD708 *) temp_s6)->p448, 1, 0, 4);
                        }
                    }
                    if (M2C_FIELD(temp_s6, f32 *, 0x3E0) < D_L22_001AF3EC) {
                        func_L22_003A45F0(arg0, 0xD, 0, 4, 3, D_L22_001AF3E8);
                        func_002A7750(arg0, 0x1F, 4);
                        break;
                    }
                    temp_v1_4 = M2C_FIELD(arg0, u8 *, 0x43);
                    if (temp_v1_4 == 0xC) {
                        if (M2C_FIELD(temp_s6, f32 *, 0x3DC) < 37.0f) {
                            func_L22_003A45F0(arg0, 0, 0, 4, 1, 1.0f);
                        } else {
                            func_L22_003A2160(arg0);
                        }
                    } else if (temp_v1_4 == 0xB) {
                        if ((M2C_FIELD(D_L22_001B2AB4, s32 *, 8) >= M2C_FIELD(temp_s6, s16 *, 0x430)) && (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 32.0f)) {
                            func_L22_003A45F0(arg0, 0, 0, 4, 1, 1.0f);
                        } else {
                            func_L22_003A2160(arg0);
                        }
                    } else {
                        if (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) < M2C_FIELD(temp_s6, s16 *, 0x430)) {
                            func_L22_003A45F0(arg0, 0xB, 0, 4, 1, 1.0f);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (D_00189E20 + 0x80);
                            M2C_FIELD(temp_s6, s16 *, 0x430) = 0x3E8;
                        }
                        temp_f1_6 = M2C_FIELD(temp_s6, f32 *, 0x3DC);
                        if (temp_f1_6 > 42.0f) {
                            func_L22_003A45F0(arg0, 0xC, 0, 4, 1, 1.0f);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = (s128 *) (D_00189E20 + 0x80);
                        } else if (temp_f1_6 < 25.0f) {
                            func_L22_003A45F0(arg0, 0xB, 0, 4, 1, 1.0f);
                            temp_s0_3 = temp_s6 + 0x3B0;
                            func_00282CF0(&scratch[0].q, (arg0 + 0x10), (s128 *) (D_00189E20 + 0x80));
                            func_00282D30(&scratch[0].q, &scratch[0].q, 20.0f);
                            func_00282CC0(&scratch[0].q, (arg0 + 0x10), &scratch[0].q);
                            func_L22_003A2B90(arg0, temp_s0_3, &scratch[0].q, 1);
                            M2C_FIELD(temp_s6, s128 **, 0x3AC) = temp_s0_3;
                        } else {
                            func_L11_003404E0(arg0);
                        }
                    }
                    break;
                case 33:                            /* switch 2 */
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 5, 0, 4, 3, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 0, 0, 4);
                    }
                    func_L22_003A2A28(arg0, 1);
                    temp_s0_4 = temp_s6 + 0x360;
                    M2C_FIELD(temp_s6, s128 *, 0x360) = (s128) M2C_FIELD(((M2C_FIELD(temp_s6, s16 *, 0x356) * 0x10) + D_L22_001FE940[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]]), s128 *, 0x10);
                    func_L22_003A2988(temp_s0_4, 8.0f);
                    M2C_FIELD(temp_s6, f32 *, 0x3A0) = func_00282E48((arg0 + 0x10), temp_s0_4);
                    func_002A7750(arg0, 0x22, 5);
                    M2C_FIELD(temp_s6, u16 *, 0x3A4) = 0U;
                    if (M2C_FIELD(temp_s6, s16 *, 0x3A6) == 3) {
                        if (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) == 0) {
                            M2C_FIELD(temp_s6, s16 *, 0x3A6) = 0;
                        } else {
                            M2C_FIELD(temp_s6, s16 *, 0x3A6) = 1;
                        }
                    }
                    break;
                case 34:                            /* switch 2 */
                    temp_s0_5 = temp_s6 + 0x360;
                    if (func_00282E48((arg0 + 0x10), temp_s0_5) < 2.0f) {
                        *(s128 *)(arg0 + 0x10) = M2C_FIELD(temp_s6, s128 *, 0x360);
                        func_002A7750(arg0, 0x23, 5);
                        func_L22_003A45F0(arg0, 6, 0, 0x14, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = func_002A7820(0x168, 0x258);
                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                        M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                    } else {
                        func_00282CF0(&scratch[0].q, temp_s0_5, (arg0 + 0x10));
                        spC0 = 0;
                        temp_f_dist = func_00282DF0(&scratch[0].q);
                        func_002AA548(&spC0, temp_s6 + 0x3A8, temp_f_dist, 0.011111111f, 0.0055555557f, 0.33333334f);
                        func_00282F20(&scratch[0].q, &scratch[0].q, M2C_FIELD(temp_s6, f32 *, 0x3A8));
                        func_00282CC0((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                        if ((M2C_FIELD(arg0, u8 *, 0x60) & 2) && (M2C_FIELD(arg0, u8 *, 0x43) == 5)) {
                            func_L22_003A45F0(arg0, 6, 0, 0x14, 3, 1.0f);
                        }
                    }
                    break;
                case 35:                            /* switch 2 */
                    if ((M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) || (M2C_FIELD(temp_s6, s32 *, 0x3D8) == 0) || (M2C_FIELD(temp_s6, s32 *, 0x418) != 0)
                        || ((M2C_FIELD(temp_s6, s32 *, 0x464) != 0) && (M2C_FIELD(temp_s6, s16 *, 0x41E) == 2))
                        || ((temp_a1_2 = (u16) M2C_FIELD(temp_s6, s16 *, 0x3A6), (M2C_FIELD(temp_s6, s16 *, 0x3A6) == 1))
                            && ((M2C_FIELD(D_L22_001B2AB4, s32 *, 8) == 0) || ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x79U)))) {
                        var_s5 = arg0 + 0xE0;
                        func_002A7750(arg0, 0x24, 5);
                        func_L22_003A45F0(arg0, 2, 0, 4, 2, 1.0f);
                        M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                    } else {
                                temp_a0_7 = M2C_FIELD(temp_s6, s32 *, 0x440);
                                if (M2C_FIELD(temp_a0_7, u8 *, 0x60) & 2) {
                                    mode3A6 = (s16) temp_a1_2;
                                    if (mode3A6 == 0) {
                                        if (M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) == 0) {
                                            var_s5 = arg0 + 0xE0;
                                            func_002A7750(arg0, 0x24, 5);
                                            func_L22_003A45F0(arg0, 6, 0, 4, 3, 1.0f);
                                            M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                                        } else {
                                        var_s5 = arg0 + 0xE0;
                                        func_L22_003A2A08();
                                        }
                                    } else if (mode3A6 == 1) {
                                        func_L22_003A45F0(arg0, 2, 0, 4, 2, 1.0f);
                                        var_s5 = arg0 + 0xE0;
                                        M2C_FIELD(temp_s6, s16 *, 0x386) = 0;
                                    } else {
                                        var_s5 = arg0 + 0xE0;
                                        if (mode3A6 == 2) {
                                            if (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 30.0f) {
                                                func_002A7750(arg0, 0x24, 5);
                                                M2C_FIELD(temp_s6, f32 *, 0x3A8) = 0.0f;
                                            }
                                        }
                                    }
                                } else {
                                    temp_v1_5 = M2C_FIELD(temp_a0_7, u8 *, 0x43);
                                    if (temp_v1_5 == 3) {
                                        if ((func_0029F530((void *) temp_a0_7) >= 4.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 4.0f)) {
                                            func_L22_003A47E8(arg0, 1, D_0018C0B0, 0, 0);
                                            var_s5 = arg0 + 0xE0;
                                        } else {
                                            var_s5 = arg0 + 0xE0;
                                            if ((func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 2.0f) && (M2C_FIELD(temp_s6, f32 *, 0x44C) < 2.0f)) {
                                                func_L22_003A47E8(arg0, 2, D_0018C0B0, 0, 0);
                                            }
                                        }
                                    } else if (temp_v1_5 == 14) {
                                        if ((func_0029F530((void *) temp_a0_7) > 22.0f) && (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 55.0f)) {
                                            var_s5 = arg0 + 0xE0;
                                            M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 1.0f;
                                        } else {
                                            var_s5 = arg0 + 0xE0;
                                            if (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) >= 10.0f) {
                                                f32 t = func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                                                s128 *d = &scratch[0].q;
                                                if (t <= 22.0f) {
                                                *d = *(s128 *)(arg0 + 0x10);
                                                func_00282F20(&scratch[1].q, var_s5, 3.0f);
                                                func_00282CC0(&scratch[1].q, &scratch[1].q, arg0 + 0xC0);
                                                func_00282CC0(d, d, &scratch[1].q);
                                                func_L22_003B9128(arg0, d, 0);
                                                M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), f32 *, 0x48) = 0.35f;
                                                }
                                            }
                                        }
                                    } else {
                                        var_s5 = arg0 + 0xE0;
                                        func_00282978((s32) (temp_s6 + 0x386));
                                        if (M2C_FIELD(temp_s6, s16 *, 0x386) <= 0) {
                                            temp_v1_6 = M2C_FIELD(temp_s6, s16 *, 0x3A6);
                                            if (temp_v1_6 == 1) {
                                                func_L22_003A45F0(arg0, 3, 0, 4, 2, 1.0f);
                                                func_002A7470(((VarsD708 *) temp_s6)->p448, 5, 0, 4);
                                            } else if (temp_v1_6 == 0) {
                                                temp_v0_5 = M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC);
                                                if (temp_v0_5 > 0) {
                                                    M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) = (s32) (temp_v0_5 - 1);
                                                }
                                                func_L22_003A45F0(arg0, 0xE, 0, 4, 2, 1.0f);
                                                func_002A7470(((VarsD708 *) temp_s6)->p448, 5, 0, 4);
                                            }
                                        }
                                    }
                                }
                    }
                    if ((M2C_FIELD(temp_s6, f32 *, 0x3DC) >= 38.0f) || (M2C_FIELD(temp_s6, f32 *, 0x3DC) <= 32.0f)) {
                        spC8 = 0;
                        if (M2C_FIELD(temp_s6, f32 *, 0x3DC) > 32.0f) {
                            var_fp = 3;
                            var_f20 = func_00282C48(M2C_FIELD(temp_s6, f32 *, 0x3DC) - 35.0f);
                            if ((u16) M2C_FIELD(temp_s6, u16 *, 0x3A4) >= 2U) {
                                spC8 = 1;
                                M2C_FIELD(temp_s6, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(temp_s6, u16 *, 0x352);
                            }
                            var_v0_7 = 1;
                        } else {
                            var_fp = 2;
                            var_f20 = func_00282C48(M2C_FIELD(temp_s6, f32 *, 0x3DC) - 35.0f);
                            temp_v0_6 = (s16) M2C_FIELD(temp_s6, u16 *, 0x3A4);

                            if ((temp_v0_6 != 0) && (temp_v0_6 != 2)) {
                                spC8 = 1;
                                M2C_FIELD(temp_s6, u16 *, 0x352) = (u16) -(s32) M2C_FIELD(temp_s6, u16 *, 0x352);
                            }
                            var_v0_7 = 2;
                        }
                        M2C_FIELD(temp_s6, u16 *, 0x3A4) = var_v0_7;
                        if ((u16) M2C_FIELD(arg0, u16 *, 0x96) < 0x3CU) {
                            temp_s0_6 = (s32 *) D_L22_001FE940[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]];
                            if (spC8 == 0) {
                                var_s3 = M2C_FIELD(temp_s6, s16 *, 0x356) + 1;
                                if (var_s3 >= *temp_s0_6) {
                                    var_s3 = -1;
                                    M2C_FIELD(temp_s6, u16 *, 0x352) = 1U;
                                } else {
                                    {
                                        s128 next = M2C_FIELD(((s8 *) temp_s0_6 + (var_s3 * 0x10)), s128 *, 0x10);
                                        scratch[0].q = next;
                                    }
                                    func_L22_003A2988(&scratch[0].q, 8.0f);
                                }
                                var_s2 = M2C_FIELD(temp_s6, s16 *, 0x356) - 1;
                                if (var_s2 < 0) {
                                    var_s2 = -1;
                                    M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                } else {
                                    {
                                        s128 prev = M2C_FIELD(((s8 *) temp_s0_6 + (var_s2 * 0x10)), s128 *, 0x10);
                                        scratch[1].q = prev;
                                    }
                                    func_L22_003A2988(&scratch[1].q, 8.0f);
                                }
                                if (var_s3 != -1) {
                                    func_00282CF0(&scratch[3].q, &scratch[0].q, (arg0 + 0x10));
                                    func_00282CF0(&scratch[4].q, (s128 *) (D_00189E20 + 0x80), (arg0 + 0x10));
                                    scratch[2].f[0] = func_00282DB0(&scratch[3].q, &scratch[4].q);
                                }
                                if (var_s2 != -1) {
                                    func_00282CF0(&scratch[3].q, &scratch[1].q, (arg0 + 0x10));
                                    func_00282CF0(&scratch[4].q, (s128 *) (D_00189E20 + 0x80), (arg0 + 0x10));
                                    scratch[2].f[1] = func_00282DB0(&scratch[3].q, &scratch[4].q);
                                }
                                if (var_fp == 3) {
                                    if ((var_s3 != -1) && (var_s2 != -1)) {
                                        if ((scratch[2].f[0] > scratch[2].f[1]) && (scratch[2].f[0] > 0.0f)) {
                                            M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                        }
                                    } else if ((var_s3 == -1) && (scratch[2].f[1] > 0.0f)) {
                                        M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                    } else if ((var_s2 == -1) && (scratch[2].f[0] > 0.0f)) {
                                        M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                    }
                                } else if (var_fp == 2) {
                                    if ((var_s3 != -1) && (var_s2 != -1)) {
                                        if (scratch[2].f[0] < scratch[2].f[1]) {
                                            M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                        } else {
                                            M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                        }
                                    } else if ((var_s3 == -1) && (scratch[2].f[1] < 0.0f)) {
                                        M2C_FIELD(temp_s6, s16 *, 0x352) = -1;
                                    } else if ((var_s2 == -1) && (scratch[2].f[0] < 0.0f)) {
                                        M2C_FIELD(temp_s6, u16 *, 0x352) = 1;
                                    }
                                }
                            }
                        }
                        if ((spC8 != 0) || (near = ((s128 *) (temp_s6 + 0x360)), func_00282E48((arg0 + 0x10), near) < 2.0f)) {
                            temp_a1_3 = M2C_FIELD(temp_s6, s16 *, 0x356) + M2C_FIELD(temp_s6, s16 *, 0x352);
                            temp_a2 = D_L22_001FE940[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]];
                            if (temp_a1_3 < 0) {
                                func_L22_003A2E50(arg0, var_fp, 1, M2C_FIELD(temp_a2, f32 *, 0x1C));
                            } else {
                                temp_v1_8 = M2C_FIELD(temp_a2, s32 *, 0);
                                if (temp_a1_3 >= temp_v1_8) {
                                    func_L22_003A2E50(arg0, var_fp, 1, ((PathD708 *) temp_a2)->points[temp_v1_8 - 1].f[3]);
                                } else {
                                    M2C_FIELD(temp_s6, s16 *, 0x356) = temp_a1_3;
                                }
                            }
                            *((s128 *) (temp_s6 + 0x360)) = M2C_FIELD(((M2C_FIELD(temp_s6, s16 *, 0x356) * 0x10) + D_L22_001FE940[((OwnerD708 *) temp_s6)->paths[M2C_FIELD(temp_s6, s16 *, 0x354)]]), s128 *, 0x10);
                            func_L22_003A2988(((s128 *) (temp_s6 + 0x360)), 8.0f);
                        } else {
                            func_00282CF0(&scratch[0].q, near, (arg0 + 0x10));
                            var_f20 = var_f20 * 0.0625f;
                            if (var_f20 > 0.5f) {
                                var_f20 = 0.5f;
                            }
                            func_00282F20(&scratch[0].q, &scratch[0].q, var_f20);
                            func_00282CC0((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                            func_L22_003A2988((arg0 + 0x10), 8.0f);
                            M2C_FIELD(temp_s6, s32 *, 0x3E8) = 0;
                        }
                    }
                    func_L22_00328220(arg0, temp_s6 + 0x3E4, temp_s6 + 0x3E8, var_s5, D_L22_001AF3FC, D_L22_001AF400, -1.0f);
                    break;
                case 36:                            /* switch 2 */
                    if (func_002B0360((arg0 + 0x10)) <= D_L22_001B2AA4) {
                        func_002A7750(arg0, 5, 0);
                        M2C_FIELD(temp_s6, s16 *, 0x350) = 0;
                        M2C_FIELD(temp_s6, f32 *, 0x3E4) = M2C_FIELD(temp_s6, f32 *, 0x3E8) = 0.0f;
                    } else {
                        spC4 = func_002B0360((arg0 + 0x10)) - D_L22_001B2AA4;
                        scratch[1].q = *(s128 *)(arg0 + 0x10);
                        func_L22_003A2988(&scratch[1].q, 0.0f);
                        func_00282CF0(&scratch[0].q, &scratch[1].q, (arg0 + 0x10));
                        func_002AA548(&spC4, temp_s6 + 0x3A8, 0.0f, 0.011111111f, 0.011111111f, 0.33333334f);
                        func_00282F20(&scratch[0].q, &scratch[0].q, -M2C_FIELD(temp_s6, f32 *, 0x3A8));
                        func_00282CC0((arg0 + 0x10), (arg0 + 0x10), &scratch[0].q);
                    }
                    break;
                case 30:                            /* switch 2 */
                    if (M2C_FIELD(arg0, u8 *, 0x20) == 0x1E) {
                        if ((M2C_FIELD(temp_s6, s32 *, 0x3D0) != 0) && (M2C_FIELD(temp_s6, s32 *, 0x3D8) != 0)) {
                            temp_f1_7 = M2C_FIELD(temp_s6, f32 *, 0x3DC);
                            if (temp_f1_7 < D_L22_001AF3EC) {
                                if ((func_002A77E0(5) == 0) && (M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0)) {
                                    func_002A7750(arg0, 0x21, 5);
                                    M2C_FIELD(temp_s6, s16 *, 0x3A6) = 3;
                                } else {
                                    func_L22_003A45F0(arg0, 0xD, 0, 4, 3, D_L22_001AF3E8);
                                    func_002A7750(arg0, 0x1F, 4);
                                }
                            } else if (temp_f1_7 < 33.0f) {
                                var_s1_2 = 0;
                                var_s0 = M2C_FIELD(D_L22_001B2AB4, s32 *, 8) != 0;
                                if (M2C_FIELD(temp_s6, s16 *, 0x41E) > 0) {
                                    var_s1_2 = M2C_FIELD(D_L22_001B2AB4, s32 *, 0xC) != 0;
                                }
                                if ((var_s0 != 0) && (var_s1_2 != 0)) {
                                    if (func_002A77E0(2) != 0) {
                                        var_s0 = 0;
                                    } else {
                                        var_s1_2 = 0;
                                    }
                                }
                                if (var_s0 != 0) {
                                    temp_a1_4 = M2C_FIELD(D_L22_001B2AB4, s32 *, 8);
                                    if (temp_a1_4 >= 0x32) {
                                        M2C_FIELD(temp_s6, s16 *, 0x430) = (s16) ((u16) M2C_FIELD(D_L22_001B2AB4, s32 *, 8) - func_002A77E0(0x23));
                                    } else {
                                        if (temp_a1_4 >= 3) {
                                            M2C_FIELD(temp_s6, s16 *, 0x430) = (s16) func_002A77E0(temp_a1_4 / 2);
                                        } else {
                                            M2C_FIELD(temp_s6, s16 *, 0x430) = 1;
                                        }
                                    }
                                    if (func_002A77E0(4) != 0) {
                                        func_002A7750(arg0, 0x20, 4);
                                    } else {
                                        func_002A7750(arg0, 0x21, 5);
                                        M2C_FIELD(temp_s6, s16 *, 0x3A6) = 1;
                                    }
                                } else if (var_s1_2 != 0) {
                                    func_002A7750(arg0, 0x21, 5);
                                    M2C_FIELD(temp_s6, s16 *, 0x3A6) = 0;
                                } else {
                                    func_002A7750(arg0, 0x12, 9);
                                }
                            } else {
                                func_L22_003A2160(arg0);
                            }
                        } else {
                            func_L22_003A2160(arg0);
                        }
                    }
                    break;
                case 1:                             /* switch 2 */
                    if (D_L22_001AF304 < 0xC8) {
                        func_L02_00332630(arg0, (s128 *) (D_00189E20 + 0x80));
                        if (func_002B3868(arg0) != 0) {
                            func_L22_003A45F0(arg0, 0, 0, 0, 3, 1.0f);
                            func_002A7470(((VarsD708 *) temp_s6)->p448, 7, 0, 0);
                        }
                        if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                            func_L11_003404E0(arg0);
                        }
                    }
                    break;
                case 2:                             /* switch 2 */
                    func_L02_00332630(arg0, (s128 *) (D_00189E20 + 0x80));
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 0, 0, 4, 3, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 4, 0, 4);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_L22_003A45F0(arg0, 0, 0, 0x14, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (func_002A77E0(7) + 0x1B);
                    }
                    func_00282978((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        func_L11_003404E0(arg0);
                    }
                    break;
                case 3:                             /* switch 2 */
                    func_L02_00332630(arg0, (s128 *) (D_00189E20 + 0x80));
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 0, 0, 4, 3, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 4, 0, 4);
                    }
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x8FU) {
                        func_002A7750(arg0, 0x12, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_L22_003A45F0(arg0, 0, 0, 0x14, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (func_002A77E0(7) + 0x1B);
                    }
                    func_00282978((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        func_L11_003404E0(arg0);
                    }
                    break;
                case 4:                             /* switch 2 */
                    if (func_002B3868(arg0) != 0) {
                        func_L22_003A45F0(arg0, 0, 0, 4, 3, 1.0f);
                        func_002A7470(((VarsD708 *) temp_s6)->p448, 4, 0, 4);
                    }
                    if ((u16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x4B1U) {
                        func_002A7750(arg0, 0x12, 9);
                    } else if (M2C_FIELD(temp_s6, s16 *, 0x384) <= 0) {
                        func_L22_003A45F0(arg0, 0, 0, 0x14, 3, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x384) = (s16) (func_002A77E0(7) + 0x1B);
                    }
                    func_00282978((s32) (temp_s6 + 0x384));
                    if (M2C_FIELD(temp_s6, s16 *, 0x1D0) == 0) {
                        func_L11_003404E0(arg0);
                    }
                    break;
                case 37:                            /* switch 2 */
                    break;
                }
                temp_a0_8 = M2C_FIELD(temp_s6, void **, 0x388);

                if (temp_a0_8 == NULL) {
                    M2C_FIELD(temp_s6, void **, 0x388) = func_L22_003F85A0(arg0, (arg0 + 0x10));
                } else {
                    func_L08_004356A0(temp_a0_8, (arg0 + 0x10));
                }
                M2C_FIELD(temp_s6, f32 *, 0x38C) = func_0029F530(arg0);
                M2C_FIELD(temp_s6, f32 *, 0x44C) = func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440));
                func_L22_003A4490(arg0);
                func_L22_003A3D50(arg0);
                func_L22_003A1E50(arg0);
                func_L22_003A4CA8(arg0);
                if (M2C_FIELD(temp_s6, s16 *, 0x350) == 3) {
                if ((func_L22_003A4C68((s32) arg0, (s32) M2C_FIELD(temp_s6, s16 *, 0x354)) != 0) && ((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U)) {
                    temp_a0_9 = M2C_FIELD(temp_s6, s32 *, 0x440);
                    temp_v1_9 = M2C_FIELD(temp_a0_9, u8 *, 0x43);
                    switch (temp_v1_9) {
                    case 0xA:
                        if ((func_0029F530((void *) temp_a0_9) > 7.0f) && (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            func_002A8D70((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 3, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                            func_L22_003A45F0(arg0, 9, 0, 4, 2, 1.0f);
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        }
                        break;
                    case 9:
                        if ((func_0029F530((void *) temp_a0_9) > 7.0f) && (func_0029F530((void *) M2C_FIELD(temp_s6, s32 *, 0x440)) < 12.0f)) {
                            M2C_FIELD(arg0, s32 *, 0x98) = 0;
                            func_002A8D70((void *) M2C_FIELD(temp_s6, s32 *, 0x440), 4, 4.0f, 50.0f, 0x8B0000, 0.0f, 0, 2, 0);
                            M2C_FIELD(arg0, s32 *, 0x98) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x10);
                        }
                        if (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2) {
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                            func_L22_003A45F0(arg0, 0xA, 0, 4, 2, 1.0f);
                            M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        }
                        break;
                    default:
                        M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                        func_L22_003A45F0(arg0, 9, 0, 4, 2, 1.0f);
                        M2C_FIELD(temp_s6, s16 *, 0x34C) = 1;
                        break;
                    }
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 1;
                } else if ((M2C_FIELD(temp_s6, s16 *, 0x43A) != 0) && (M2C_FIELD(M2C_FIELD(temp_s6, s32 *, 0x440), u8 *, 0x60) & 2)) {
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 0;
                    M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                    frame = func_0029F530(arg0);
                    func_L22_003A45F0(arg0, (s32) M2C_FIELD(arg0, u8 *, 0x43), (s32) frame, 4, 2, 1.0f);
                }
                } else {
                    M2C_FIELD(temp_s6, s16 *, 0x43A) = 0;
                    M2C_FIELD(temp_s6, s16 *, 0x34C) = 0;
                }
                temp_a0_10 = ((VarsD708 *) temp_s6)->p448;
                if (M2C_FIELD(temp_a0_10, u8 *, 0x60) & 2) {
                    temp_v1_10 = M2C_FIELD(arg0, u8 *, 0x95);
                    if ((u32) (temp_v1_10 - 4) >= 2U) {
                        temp_v1_11 = temp_v1_10 & 0xFF;
                        if ((temp_v1_11 != 8) && (temp_v1_11 != 1) && (temp_v1_11 != 2) && (M2C_FIELD(arg0, u8 *, 0x20) != 0x26)) {
                            if (func_002A77E0(5) != 0) {
                                func_002A7470(((VarsD708 *) temp_s6)->p448, 0, 0, 0xA);
                            } else {
                                func_002A7470(((VarsD708 *) temp_s6)->p448, 7, 0, 0xA);
                            }
                        }
                    }
                } else if ((M2C_FIELD(temp_a0_10, u8 *, 0x43) == 6) && (M2C_FIELD(arg0, u8 *, 0x95) != 8) && (M2C_FIELD(arg0, u8 *, 0x20) != 0x26)) {
                    func_002A7470(temp_a0_10, 7, 0, 0xA);
                }
                if ((u32) (M2C_FIELD(arg0, u8 *, 0x43) - 0xB) < 2U) {
                    s128 *d;
                    do { d = &scratch[0].q; } while (0);
                    *d = *(s128 *)(arg0 + 0x10);
                    func_00282F20(&scratch[1].q, temp_s6 + 0x200, 12.0f);
                    func_00282CC0(&scratch[1].q, &scratch[1].q, d);
                    if (func_002761F8(d, &scratch[1].q, 0x12, 0, 0) != 0) {
                        *(s128 *)(arg0 + 0x10) = D_L22_001C00E0;
                    }
                }
                if (M2C_FIELD(arg0, u8 *, 0x20) != 0x26) {
                    temp_f1_8 = (f32) ((s16) M2C_FIELD(temp_s6, s16 *, 0x24) / 3);
                    temp_f0 = M2C_FIELD(temp_s6, f32 *, 0x20);
                    if (temp_f0 < temp_f1_8) {
                        if (D_L22_001AF36C == 0) {
                            {
                                f32 ratio = temp_f0 / (f32) ((s16) M2C_FIELD(temp_s6, s16 *, 0x24) / 3);
                                D_L22_001AF36C = D_L22_001AF368 + (s32) ((f32) (D_L22_001AF364 - D_L22_001AF368) * ratio);
                            }
                            if (func_002A77E0(2) != 0) {
                                func_L22_003A6640((s32) arg0, func_002A77E0(4), 0, D_L22_001AF370);
                            } else {
                                func_L22_003A6640(M2C_FIELD(temp_s6, s32 *, 0x440), func_002A77E0(6), 0, D_L22_001AF370);
                            }
                        } else {
                            func_00282948(&D_L22_001AF36C);
                        }
                    }
                }
        }
    }
}
