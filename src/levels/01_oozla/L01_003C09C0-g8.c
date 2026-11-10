/* func_L01_003C09C0 (Oozla, 7,360 bytes): a moby update with an outer switch on the state byte
   at 0x95 and per-state inner switches.  One function: one prologue, one return.
   Byte offsets into the moby (arg0) and its state block (+0x68) go through the UView union so the
   accesses are aggregate memory, which lets sched move gp-relative loads over them as retail
   does; the two stores before the D_0018C0B4 test stay plain word accesses (retail keeps that
   load behind them).  Tables are indexed as (index << n) + (s32)base, the operand order retail
   adds in.  Two addressing forms of the 0x1B255C and 0x1B264C pointers: the _sda names are the
   $gp form.  -frac2-hazard-labels gives the forward branch onto the 17.0f compare its hazard nop
   target (docs/build/compiler-notes.md, Labels on hazard nops). */
#include "common.h"
typedef union { u8 b[0x800]; s8 c[0x800]; s16 h[0x400]; u16 uh[0x400]; s32 i[0x200]; u32 u[0x200]; f32 f[0x200]; void *p[0x200]; } UView;
extern int func_002761F8(void *,void *,int,void *,void *);
extern s32 func_00277F48(f32, s32, s32, s32, s32);
extern void func_0027D330(s32);
extern s32 func_002829A8(void *a0);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern f32 func_00282DF0(void *);
extern f32 func_00282E20(void *);
extern f32 func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern f32 func_00283C80(f32, f32);
extern float func_00283CE0(int);
extern void func_0029F338(void *);
extern float func_0029F530(char *);
extern void func_0029FCC0(void *, int, void *);
typedef int TI128 __attribute__((mode(TI)));
extern void func_L01_003C01C0(void);
extern void func_L01_003BFE48(void *);
extern void func_L01_003C0140(void *);
extern float func_L01_003C0408(void *);
extern void func_L01_003C06E8(void *);
extern void func_L01_003C0760(void *);
extern void func_L01_003C07C8(void *);
extern void func_L01_003C0830(void *);
extern void func_L01_003C08A0(void *);
extern void func_L01_003DA300(void *, void *, void *, float);
extern void *func_L01_004171C8(void *, int, int, int);
extern void func_L01_00394240(void *);
extern int func_001163B0(void);
#define NULL ((void *)0)
extern void func_002A0430(u32 a0);
extern void func_002A0F48(void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7750(char *, int, int);
extern float func_002A7790(float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_002A8BD0(void *a0, int a1, int a2, float a3);
extern s32 func_002A8D70(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern void func_002A8E20(s32, void *);
extern s32 func_002AEB60(u8 *, f32);
extern int func_002B1C20(void *, void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002DF3F8(void *, void *);
extern void func_L00_002B30E8(void);
extern void func_L00_002B9D60(int a0, int a1, int a2, int a3);
extern void * func_L00_002D70A0(s32 size);
extern void func_L00_002D7140(char *);
extern void func_L00_00303530(int, int);
extern f32 func_L00_0031CDD0(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
extern s32 func_L01_002BEB90(s32 action, s32 animate);
extern int func_L01_00322288(void *, float);
extern void func_L01_00323310(int, int);
extern float func_L01_003BAFB0(void);
extern void func_L01_003BFDC8(void *, int, int, int);
typedef struct { u8 pad[0x80]; f32 x; f32 y; f32 z; u8 pad2[0x2204]; s32 a2290; s32 a2294; u8 pad3[4]; s32 a229c; u8 pad4[0x15]; u8 a22b5; u8 pad5[0x1EA]; s32 a24a0; u8 pad6[0x28]; s32 a24cc; } HeroV;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern u8 D_00189E20[] NOT_SDA;
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_0018C0D5 __attribute__((nosda));
extern u8 D_00189EA0[] NOT_SDA;

extern s32 D_001A79F0 __attribute__((sda));
extern f32 D_L01_001AFE54 __attribute__((sda));
extern f32 D_L01_001AFE58 __attribute__((sda));
extern f32 D_L01_001AFE5C __attribute__((sda));
extern f32 D_L01_001AFE60 __attribute__((sda));
extern f32 D_L01_001AFE68 __attribute__((sda));
extern f32 D_L01_001AFE6C __attribute__((sda));
extern f32 D_L01_001AFE74 __attribute__((sda));
extern f32 D_L01_001AFE78 __attribute__((sda));
extern f32 D_L01_001AFE7C __attribute__((sda));
extern f32 D_L01_001AFE84 __attribute__((sda));
extern f32 D_L01_001AFE88 __attribute__((sda));
extern f32 D_L01_001AFE8C __attribute__((sda));
extern f32 D_L01_001AFE94 __attribute__((sda));
extern f32 D_L01_001AFE98 __attribute__((sda));
extern f32 D_L01_001AFE9C __attribute__((sda));
extern f32 D_L01_001AFEA0 __attribute__((sda));
extern f32 D_L01_001AFEA4 __attribute__((sda));
extern f32 D_L01_001AFEA8 __attribute__((sda));
extern f32 D_L01_001AFEAC __attribute__((sda));
extern f32 D_L01_001AFEB0 __attribute__((sda));
extern f32 D_L01_001AFEB4 __attribute__((sda));
extern f32 D_L01_001AFEB8 __attribute__((sda));
extern s32 D_L01_001AFEC0 __attribute__((sda));
extern s32 D_L01_001AFEC4 __attribute__((sda));
extern u8 D_L01_001AFEC8 __attribute__((sda));
extern s32 D_L01_001AFECC __attribute__((sda));
extern f32 D_L01_001AFEEC __attribute__((sda));
extern f32 D_L01_001AFEF0 __attribute__((sda));
extern f32 D_L01_001AFEF4 __attribute__((sda));
extern f32 D_L01_001AFEF8 __attribute__((sda));
extern u8 *D_L01_001B255C_sda __attribute__((sda));
extern u8 *D_L01_001B264C_sda __attribute__((sda));
extern u8 D_00189F10[] NOT_SDA;
extern u8 D_0019B2E8[] NOT_SDA;
extern u8 *D_L01_001B255C;
extern u8 *D_L01_001B264C;

void func_L01_003C09C0(u8 *arg0) {
    float sp[20] __attribute__((aligned(16)));
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f22;
    f32 temp_f23;
    f32 var_f12_2;
    u8 *temp_a0_6;
    s32 temp_a1;
    s32 temp_a1_2;
    u8 *temp_a2;
    s32 temp_v0_4;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_19;
    s32 temp_v1_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s5;
    u8 *temp_a0;
    u8 *temp_a0_3;
    u8 *temp_s1;
    u8 *temp_v1_12;
    u8 temp_s0;
    u8 temp_v0_2;
    u8 temp_v1;
    u8 temp_v1_10;
    u8 temp_v1_11;
    u8 temp_v1_17;
    u8 temp_v1_18;
    u8 temp_v1_2;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    u8 temp_v1_8;
    u8 temp_v1_9;
    u8 *temp_a0_2;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a1_3;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *temp_s4;
    u8 *temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1_16;

    temp_s4 = ((u8 *)((UView *)(arg0))->p[0x1A]);
    func_L01_003C01C0();
    temp_v1 = ((UView *)(arg0))->b[0x95];
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if ((((UView *)(arg0))->b[0xB0] != 0xFF) && (D_0019B2E8[((UView *)(arg0))->b[0xB0] + (D_001A79F0 * 0x10)] & 0x80)) {
            temp_v1_3 = ((UView *)(temp_s4))->i[0xC2];
            if (temp_v1_3 != -1) {
                D_L01_001B255C_sda[(temp_v1_3 << 8) + 0xBC] = 1;
            }
            func_0029F338(arg0);
            return;
        }
        func_L01_003BFE48(arg0);
    default:
        break;
    case 1:                                         /* switch 1 */
        if (((UView *)(temp_s4))->i[0x49] == 1) {
            if (((u8 *)((UView *)(temp_s4))->p[0xB9]) == NULL) {
                func_L01_00323310(((UView *)(temp_s4))->i[0xC4], ((UView *)(temp_s4))->i[0xC6]);
                ((u8 *)((UView *)(temp_s4))->p[0xB9]) = func_L00_002D70A0(5);
            }
            func_002A7750(arg0, 0, 2);
        }
        break;
    case 2:                                         /* switch 1 */
        temp_f0 = func_L01_003C0408(arg0);
        if (temp_f0 == -1000.0f) {
            temp_a0 = ((u8 *)((UView *)(temp_s4))->p[0xB9]);
            if (temp_a0 != NULL) {
                func_L00_002D7140(temp_a0);
                ((u8 *)((UView *)(temp_s4))->p[0xB9]) = NULL;
            }
            func_002A7750(arg0, 0, 1);
            func_L01_003BFDC8(arg0, 0, 0, 0xA);
        } else {
            temp_v0 = ((u8 *)((UView *)(temp_s4))->p[0x48]);
            temp_f21 = func_00283C80(((UView *)(arg0))->f[0x3E], func_00283248(*(f32 *)(temp_v0 + 0x10) - ((UView *)(arg0))->f[0x4], *(f32 *)(temp_v0 + 0x14) - ((UView *)(arg0))->f[0x5]));
            switch (((UView *)(arg0))->b[0xBC]) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((temp_f0 <= D_L01_001AFE5C) && (temp_f21 < (D_L01_001AFEAC * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                    var_s0 = 1;
                    func_L01_003C06E8(arg0);
                } else {
                    var_s0 = D_L01_001AFECC < (s32) ((UView *)(arg0))->uh[0x4B];
                }
                if (var_s0 != 0) {
                    func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(arg0))->b[0xBC] = 1U;
                }
                if (((UView *)(temp_s4))->f[0x8] < (2.0f * func_00283CE0((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE88 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(arg0))->b[0xBC] = 3U;
                    func_L01_003BFDC8(arg0, 0x10, 0, 0xD);
                    func_002A7750(arg0, 0, 5);
                }
            default:                                /* switch 2 */
                break;
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
                temp_v1_5 = ((UView *)(arg0))->b[0xBC];
                var_s1 = 0;
                switch (temp_v1_5) {                /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    if ((temp_f0 <= D_L01_001AFE5C) && (temp_f21 < (D_L01_001AFEAC * 0.017453294f))) {
                        if ((func_002A77E0(D_L01_001AFEC0 - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                            func_L01_003C06E8(arg0);
                        } else {
                            goto block_36;
                        }
                    } else {
block_36:
                        if ((D_L01_001AFE5C < temp_f0) && (temp_f0 <= D_L01_001AFE60) && (temp_f21 < (D_L01_001AFEB0 * 0.017453294f))) {
                            if ((func_002A77E0(D_L01_001AFEC4 - 1) == 0) && (((UView *)(temp_s4))->h[0x16D] == 0)) {
                                func_L01_003C07C8(arg0);
                            } else {
                                goto block_43;
                            }
                        } else {
block_43:
                            if (D_L01_001AFE68 < temp_f0) {
                                ((UView *)(temp_s4))->b[0x2E1] = 4U;
                                ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                                ((UView *)(temp_s4))->c[0x2E0] = 0;
                                func_002B60B0(arg0, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                                ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                                ((UView *)(arg0))->b[0xBC] = 2U;
                                ((UView *)(temp_s4))->c[0x71] = 0xF;
                                ((UView *)(temp_s4))->c[0x72] = 0xF;
                                func_L01_003BFDC8(arg0, 3, 0, 0xD);
                                func_002A7750(arg0, 0, 5);
                            }
                        }
                    }
                    break;
                case 2:                             /* switch 3 */
                    var_s1 = 0x3C;
                    ((UView *)(arg0))->i[0x26] = 0;
                    if ((temp_f0 <= D_L01_001AFE5C) && ((temp_v1_6 = ((UView *)(arg0))->b[0x42], (temp_v1_6 == 0x16)) || (temp_v1_6 == 0))) {
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                        ((UView *)(arg0))->b[0xBC] = 1U;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        func_L01_003BFDC8(arg0, 0x16, 0, 0x14);
                        func_002A7750(arg0, 0, 5);
                    }
                    break;
                }
                if (((UView *)(temp_s4))->f[0x8] < (2.0f * func_00283CE0((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE88 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(arg0))->b[0xBC] = 3U;
                    func_L01_003BFDC8(arg0, 0x10, 0, var_s1 + 0xD);
                    func_002A7750(arg0, 0, 5);
                }
                break;
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                temp_s0 = ((UView *)(arg0))->b[0xBC];
                switch (temp_s0) {                  /* switch 4; irregular */
                case 3:                             /* switch 4 */
                    if ((temp_f0 <= D_L01_001AFE54) && (temp_f21 < (D_L01_001AFEB4 * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16F] == 0)) {
                        func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE8C * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE58;
                        ((UView *)(arg0))->b[0xBC] = 4U;
                        ((UView *)(temp_s4))->b[0x2E3] = (u8) D_L01_001AFEC8;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        func_L01_003C0830(arg0);
                    }
                    break;
                case 4:                             /* switch 4 */
                    if ((D_L01_001AFE5C < temp_f0) && (temp_f0 <= D_L01_001AFE58) && (temp_f21 < (D_L01_001AFEB8 * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if (func_002829A8(temp_s4 + 0x2E3) != 0) {
                            func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                            ((UView *)(arg0))->b[0xBC] = 5U;
                            ((UView *)(temp_s4))->c[0x2E0] = 0;
                            ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                            ((UView *)(temp_s4))->b[0x2E1] = temp_s0;
                            ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                            ((UView *)(temp_s4))->c[0x71] = 0xF;
                            ((UView *)(temp_s4))->c[0x72] = 0xF;
                            func_L01_003BFDC8(arg0, 3, 0, 0xD);
                            func_002A7750(arg0, 0, 5);
                        }
                        func_L01_003C0760(arg0);
                    }
                    break;
                case 5:                             /* switch 4 */
                    ((UView *)(arg0))->i[0x26] = 0;
                    if (temp_f0 <= D_L01_001AFE5C) {
                        temp_v1_7 = ((UView *)(arg0))->b[0x42];
                        if (temp_v1_7 != 0x16) {
                            if (temp_v1_7 == 0) {
                                goto block_72;
                            }
                        } else {
block_72:
                            ((UView *)(temp_s4))->c[0x2E0] = 1;
                            ((UView *)(temp_s4))->b[0x2E1] = 1U;
                            ((UView *)(temp_s4))->c[0x71] = 0x13;
                            ((UView *)(temp_s4))->c[0x72] = 0x13;
                            ((UView *)(temp_s4))->c[0x2E2] = 0;
                            func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                            ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE58;
                            ((UView *)(arg0))->b[0xBC] = 6U;
                            ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                            func_L01_003BFDC8(arg0, 0x16, 0, 0x14);
                            func_002A7750(arg0, 0, 5);
                        }
                    }
                    break;
                case 6:                             /* switch 4 */
                    ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                    if ((temp_f0 <= D_L01_001AFE58) && (temp_f21 < (D_L01_001AFEAC * 0.017453294f)) && (func_002A77E0(D_L01_001AFEC0 - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if ((D_L01_001AFE5C < temp_f0) && (func_001163B0() & 1)) {
                            func_L01_003C0760(arg0);
                        } else {
                            func_L01_003C06E8(arg0);
                        }
                    }
                    break;
                }
                temp_v0_2 = ((UView *)(arg0))->b[0xBC];
                if ((temp_v0_2 != 5) && (temp_v0_2 < 7U) && (D_L01_001AFE68 < temp_f0)) {
                    func_002B60B0(arg0, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                    ((UView *)(arg0))->b[0xBC] = 5U;
                    ((UView *)(temp_s4))->c[0x2E0] = 0;
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(temp_s4))->c[0x71] = 0xF;
                    ((UView *)(temp_s4))->c[0x72] = 0xF;
                    ((UView *)(temp_s4))->b[0x2E1] = 4U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                }
                if (((UView *)(temp_s4))->f[0x8] < (func_00283CE0((s32) ((UView *)(temp_s4))->h[0x12]) * 0.33333334f)) {
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE54;
                    ((UView *)(temp_s4))->b[0x2E1] = 5U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0xE;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE94 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    ((UView *)(arg0))->b[0xBC] = 7U;
                    func_L01_003BFDC8(arg0, 0x10, 0, 0xD);
                    func_002A7750(arg0, 0, 5);
                }
                break;
            case 7:                                 /* switch 2 */
                if ((temp_f0 <= D_L01_001AFE54) && (temp_f21 < (D_L01_001AFEB4 * 0.017453294f)) && (((UView *)(temp_s4))->h[0x16F] == 0)) {
                    ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                    ((UView *)(arg0))->b[0xBC] = 9U;
                    ((UView *)(temp_s4))->c[0x2E0] = 1;
                    ((UView *)(temp_s4))->b[0x2E1] = 1U;
                    ((UView *)(temp_s4))->c[0x2E2] = 0;
                    ((UView *)(temp_s4))->c[0x71] = 0x13;
                    ((UView *)(temp_s4))->c[0x72] = 0x13;
                    func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE98 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                    func_L01_003C0830(arg0);
                }
                break;
            case 8:                                 /* switch 2 */
                ((UView *)(arg0))->i[0x26] = 0;
                if (temp_f0 <= D_L01_001AFE5C) {
                    temp_v1_8 = ((UView *)(arg0))->b[0x42];
                    if (temp_v1_8 != 0x16) {
                        if (temp_v1_8 == 0) {
                            goto block_95;
                        }
                    } else {
block_95:
                        ((UView *)(temp_s4))->c[0x2E0] = 1;
                        ((UView *)(temp_s4))->b[0x2E1] = 1U;
                        ((UView *)(temp_s4))->c[0x71] = 0x13;
                        ((UView *)(temp_s4))->c[0x72] = 0x13;
                        ((UView *)(temp_s4))->c[0x2E2] = 0;
                        func_002B60B0(arg0, D_L01_001AFE74 * 0.00027777778f, D_L01_001AFE84 * 0.016666668f, D_L01_001AFE78 * 0.0000048481375f, D_L01_001AFE7C * 0.00029088825f);
                        ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                        ((UView *)(arg0))->b[0xBC] = 9U;
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        func_L01_003BFDC8(arg0, 0x16, 0, 0x14);
                        func_002A7750(arg0, 0, 5);
                    }
                }
                break;
            case 9:                                 /* switch 2 */
                ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                if ((temp_f0 <= D_L01_001AFE5C) && (temp_f21 < (D_L01_001AFEAC * 0.017453294f))) {
                    if ((func_002A77E0(D_L01_001AFEC0 - 1) == 0) && (((UView *)(temp_s4))->h[0x16E] == 0)) {
                        if (func_001163B0() & 1) {
                            func_L01_003C06E8(arg0);
                        } else {
                            func_L01_003C0760(arg0);
                        }
                    } else {
                        goto block_105;
                    }
                } else {
block_105:
                    if ((D_L01_001AFE5C < temp_f0) && (temp_f0 <= D_L01_001AFE60) && (temp_f21 < (D_L01_001AFEB0 * 0.017453294f))) {
                        if ((func_002A77E0(D_L01_001AFEC4 - 1) == 0) && (((UView *)(temp_s4))->h[0x16D] == 0)) {
                            func_L01_003C07C8(arg0);
                        } else {
                            goto block_112;
                        }
                    } else {
block_112:
                        if (D_L01_001AFE68 < temp_f0) {
                            ((UView *)(temp_s4))->b[0x2E1] = 4U;
                            ((UView *)(temp_s4))->c[0x2E2] = 0x16;
                            ((UView *)(temp_s4))->c[0x2E0] = 0;
                            func_002B60B0(arg0, D_L01_001AFE9C * 0.00027777778f, D_L01_001AFEA0 * 0.016666668f, D_L01_001AFEA4 * 0.0000048481375f, D_L01_001AFEA8 * 0.00029088825f);
                            ((UView *)(temp_s4))->f[0xBB] = (f32) D_L01_001AFE5C;
                            ((UView *)(arg0))->b[0xBC] = 8U;
                            ((UView *)(temp_s4))->c[0x71] = 0xF;
                            ((UView *)(temp_s4))->c[0x72] = 0xF;
                            func_L01_003BFDC8(arg0, 3, 0, 0xD);
                            func_002A7750(arg0, 0, 5);
                        }
                    }
                }
                break;
            }
            if ((((UView *)(arg0))->b[0x42] == 0x16) && (((UView *)(arg0))->b[0x60] & 2)) {
                ((UView *)(temp_s4))->c[0x2E2] = 0;
                func_L01_003BFDC8(arg0, 0, 0, 0xA);
            }
        }
        break;
    case 3:                                         /* switch 1 */
        temp_f20 = func_0029F530(arg0);
        switch (((UView *)(arg0))->b[0x20]) {                        /* switch 5; irregular */
        case 1:                                     /* switch 5 */
            func_L01_00322288(arg0, func_00283248(((HeroV *)D_00189E20)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)D_00189E20)->y - ((UView *)(arg0))->f[0x5]));
            if ((temp_f20 > 44.0f) && (temp_f20 < 68.0f)) {
                temp_v1_10 = ((UView *)(arg0))->b[0x42];
                var_s5 = -1;
                if (temp_v1_10 == 6) {
                    var_s5 = 0;
                } else if (temp_v1_10 == 7) {
                    var_s5 = 4;
                }
                if (var_s5 >= 0) {
                    func_0029FCC0(arg0, var_s5, (sp + 4));
                    for (var_s1_2 = 1; var_s1_2 < 3; var_s1_2++) {
                        func_002A8BD0((sp + 8), (s32) arg0, 1, (f32) ((UView *)(temp_s4))->b[0x34]);
                        qcopy(sp, sp + 4);
                        func_0029FCC0(arg0, var_s5 + var_s1_2, sp + 4);
                        func_00277F48(0.5f, (s32) (sp + 4), 0, (s32) arg0, (s32) (sp + 8));
                        sp[4] += func_002A7878(-0.3f, 0.3f);
                        sp[5] += func_002A7878(-0.3f, 0.3f);
                        sp[6] += func_002A7878(-0.3f, 0.3f);
                        func_002761F8(sp, (sp + 4), 9, arg0, (sp + 8));
                    }
                }
            }
            break;
        case 2:                                     /* switch 5 */
            func_L01_00322288(arg0, func_00283248(((HeroV *)D_00189E20)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)D_00189E20)->y - ((UView *)(arg0))->f[0x5]));
            if (func_002AEB60((u8 *) arg0, 16.0f) != 0) {
                func_0029FCC0(arg0, 0xA, sp);
                func_00282CF0((sp + 4), ((u8 *)((UView *)(temp_s4))->p[0x48]) + 0x10, sp);
                func_00282F20((sp + 4), (sp + 4), D_L01_001AFEF4 * 0.016666668f);
                sp[6] = func_L00_0031CDD0(sp, ((u8 *)((UView *)(temp_s4))->p[0x48]) + 0x10, NULL, D_L01_001AFEF4 * 0.016666668f, -(D_L01_001AFEF8 * 0.00027777778f));
                func_L01_003DA300(sp, (sp + 4), arg0, (f32) ((UView *)(temp_s4))->b[0x34]);
            }
            break;
        case 3:                                     /* switch 5 */
            if ((temp_f20 > 34.0f) && (temp_f20 < 41.0f)) {
                temp_a1 = (func_001163B0() & 1) | 8;
                func_002A8D70(arg0, 2.2f, (f32) ((UView *)(temp_s4))->b[0x34], temp_a1, 1, 1.0f, 0, 1, 0);
            }
            break;
        case 4:                                     /* switch 5 */
            func_L01_00322288(arg0, func_00283248(((HeroV *)D_00189E20)->x - ((UView *)(arg0))->f[0x4], ((HeroV *)D_00189E20)->y - ((UView *)(arg0))->f[0x5]));
            if (((UView *)(temp_s4))->b[0x2F4] == 0) {
                if (temp_f20 > 12.0f) {
                    if (temp_f20 <= 17.0f) {
                        func_0029FCC0(arg0, 0xC, sp);
                        sp[2] -= 2.4f;
                        if ((func_00282E48(sp, &((HeroV *)D_00189E20)->x) < D_L01_001AFE6C) && (*(s32 *)(D_00189E20 + 0x2294) != 0x6F)) {
                            ((UView *)(temp_s4))->b[0x2F4] = 1U;
                        }
                    } else {
                        goto block_149;
                    }
                } else {
block_149:
                    if ((temp_f20 > 17.0f) && (temp_f20 < 19.0f)) {
                        ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                        temp_a1 = (func_001163B0() & 1) | 0xC;
                        func_002A8D70(arg0, 2.0f, (f32) ((UView *)(temp_s4))->b[0x35], temp_a1, 1, 1.0f, 0, 1, 0);
                    }
                }
            } else if (temp_f20 > 19.0f) {
                ((HeroV *)D_00189E20)->a22b5 = 1;
            }
            break;
        }
        if (((UView *)(temp_s4))->b[0x2F4] != 0) {
            func_L01_003C08A0(arg0);
            if (((UView *)(arg0))->b[0x60] & 2) {
                if (((HeroV *)D_00189E20)->a24cc < 2) {
                    func_L00_002B30E8();
                } else {
                    func_002A8BD0(sp, (s32) arg0, 1, (f32) ((UView *)(temp_s4))->b[0x36]);
                    func_002A8E20(((HeroV *)D_00189E20)->a2290, sp);
                }
                ((HeroV *)D_00189E20)->a22b5 = 1;
                func_L01_003BFDC8(arg0, 0xB, 0, 0x14);
                func_002A7750(arg0, 0, 4);
            }
        } else {
            if (((UView *)(arg0))->b[0x60] & 2) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                func_002A7750(arg0, 0, 2);
                func_L01_003BFDC8(arg0, 0, 0, 0x14);
            }
        }
        break;
    case 4:                                         /* switch 1 */
        temp_f23 = func_0029F530(arg0);
        temp_v0_3 = (u8 *)((((UView *)(temp_s4))->i[0xB3] << 7) + (s32)D_L01_001B264C);
        temp_f0_2 = func_00283248(*(f32 *)(temp_v0_3 + 0x30) - ((UView *)(arg0))->f[0x4], *(f32 *)(temp_v0_3 + 0x34) - ((UView *)(arg0))->f[0x5]);
        temp_f22 = func_00283B98(temp_f0_2, 1.5707965f);
        temp_f21_2 = func_00283BE0(temp_f0_2, 1.5707965f);
        temp_f20_2 = func_00283C80(((UView *)(arg0))->f[0x3E], temp_f22);
        func_L01_00322288(arg0, temp_f20_2 < func_00283C80(((UView *)(arg0))->f[0x3E], temp_f21_2) ? temp_f22 : temp_f21_2);
        if (((UView *)(arg0))->b[0x42] == 0xB) {
            var_s2 = 1;
            func_0029FCC0(arg0, 0xE, sp);
            temp_f0_3 = func_00282E48(sp, &((Hero *)D_00189E20)->b[0x80]);
            if (!(temp_f0_3 > 13.0f)) {
                var_s2 = 0;
            }
            if (((UView *)(temp_s4))->b[0x2F4] != 0) {
                if (temp_f23 > 33.0f) {
                    func_L01_002BEB90(0x16, 1);
                    ((Hero *)D_00189E20)->i[0x2294 / 4] = 0x6F;
                    ((Hero *)D_00189E20)->i[0x24A0 / 4] = 0;
                    ((Hero *)D_00189E20)->i[0x229C / 4] = 9;
                    ((Hero *)D_00189E20)->c[0x22B5] = 0;
                    ((UView *)(temp_s4))->b[0x2F4] = 0U;
                } else {
                    ((Hero *)D_00189E20)->c[0x22B5] = 1;
                    func_L01_003C08A0(arg0);
                }
            }
            if ((((UView *)(temp_s4))->b[0x2F4] == 0) && (var_s2 == 0)) {
                func_00282F20((sp + 4), arg0 + 0xC0, D_L01_001AFEEC);
                func_00282F20((sp + 8), (sp + 4), D_L01_001AFEF0 * 0.016666668f);
                temp_f20_3 = func_00282E20((sp + 8));
                sp[10] = temp_f20_3 * (func_002A7790(1.0f - (temp_f0_3 * 0.006666667f)) * 0.7f);
                qcopy(&((Hero *)D_00189E20)->b[0xF0], sp + 8);
                qcopy(&((Hero *)D_00189E20)->b[0x110], sp + 8);
                func_00282CC0(&((Hero *)D_00189E20)->b[0x80], &((Hero *)D_00189E20)->b[0x80], (sp + 8));
            }
            if (var_s2 != 0) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                *(s32 *)(arg0 + 0x98) = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                if (D_0018C0B4 == 0x6F) {
                    func_L01_002BEB90(0x16, 1);
                }
            }
            if (((UView *)(arg0))->b[0x60] & 2) {
                ((UView *)(arg0))->i[0x27] = (s32) (((UView *)(arg0))->i[0x27] & ~0x30);
                ((UView *)(arg0))->i[0x26] = (s32) *(s32 *)(((u8 *)((UView *)(arg0))->p[0x9]) + 0x10);
                func_L01_003BFDC8(arg0, 0xC, 0, 0x14);
                func_002A7750(arg0, 0, 5);
                if (D_0018C0B4 == 0x6F) {
                    func_L01_002BEB90(0x16, 1);
                }
            }
        } else {
            if (((UView *)(arg0))->b[0x95] == 4) {
                temp_v1_11 = ((UView *)(temp_s4))->b[0x2F4];
                if (temp_v1_11 == 1) {
                    D_0018C0D5 = temp_v1_11;
                }
            }
        }
        break;
    case 5:                                         /* switch 1 */
        if (((UView *)(arg0))->b[0x60] & 2) {
            func_002A7750(arg0, 0, 2);
            func_L01_003BFDC8(arg0, (s32) ((UView *)(temp_s4))->b[0x2E1], 0, 0x14);
            ((UView *)(arg0))->b[0xA8] = 0xFF;
        }
        break;
    case 6:                                         /* switch 1 */
        temp_v0_4 = func_002B1C20(arg0, temp_s4 + 0x60);
        if (temp_v0_4 & 1) {
            func_002A7750(arg0, 0, 7);
        } else if (temp_v0_4 & 2) {
            func_L01_003BFDC8(arg0, (s32) ((UView *)(temp_s4))->b[0x2E1], 0, 0xC);
            func_002A7750(arg0, 0, 2);
        }
        break;
    case 7:                                         /* switch 1 */
        ((UView *)(arg0))->i[0x12] = 0;
        ((UView *)(arg0))->uh[0x1A] = (u16) (((UView *)(arg0))->uh[0x1A] | 0x41);
        temp_a0_3 = ((u8 *)((UView *)(temp_s4))->p[0xB9]);
        if (temp_a0_3 != NULL) {
            func_L00_002D7140(temp_a0_3);
            ((u8 *)((UView *)(temp_s4))->p[0xB9]) = NULL;
        }
        temp_s1 = arg0 + 0x10;
        temp_v0_5 = func_L01_004171C8(temp_s1, 1, -1, -1);
        ((u8 *)((UView *)(temp_s4))->p[0xC0]) = temp_v0_5;
        if (temp_v0_5 != NULL) {
            func_L01_002BEB90(0x6F, 1);
            temp_s0_2 = temp_s4 + 0x2A0;
            temp_v0_6 = ((u8 *)((UView *)(temp_s4))->p[0xC0]);
            *(f32 *)(temp_v0_6 + 0x18) = (f32) (*(f32 *)(temp_v0_6 + 0x18) - 0.5f);
            func_00282CF0(temp_s0_2, temp_s1, D_00189EA0);
            ((UView *)(temp_s4))->f[0xAA] = (f32) (((UView *)(temp_s4))->f[0xAA] + 1.0f);
            func_00282D30(temp_s0_2, temp_s0_2, 0.85f);
            ((UView *)(temp_s4))->f[0xAB] = 1.0f;
            func_002A7750(arg0, 0, 8);
        }
        break;
    case 8:                                         /* switch 1 */
        temp_v1_13 = ((UView *)(temp_s4))->i[0xBE];
        temp_f21_3 = ((UView *)(temp_s4))->f[0xAB] - 0.00625f;
        ((UView *)(temp_s4))->f[0xAB] = temp_f21_3;
        if (temp_v1_13 != -1) {
            temp_v1_14 = (*(s32 *)((u8 *)((*(u8 **)((u8 *)((temp_v1_13 << 8) + (s32)D_L01_001B255C) + 0x68))) + 0x28));
            temp_a2 = D_L01_001B264C_sda;
            if (temp_v1_14 != -1) {
                temp_a1_2 = temp_v1_14 << 7;
                qcopy(D_00189EA0, (u8 *)(temp_a1_2 + (s32)temp_a2) + 0x30);
                temp_a1_3 = (u8 *)(temp_a1_2 + (s32)temp_a2);
                qcopy(D_00189EA0 + 0x10, (u8 *)temp_a1_3 + 0x70);
            }
        }
        if ((u8) *(u8 *)(((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x20) < 2U) {
            temp_v1_15 = ((UView *)(temp_s4))->i[0xBE];
            if (temp_v1_15 != -1) {
                temp_v1_16 = (u8 *)((temp_v1_15 << 8) + (s32)D_L01_001B255C_sda);
                if (*(u8 *)(temp_v1_16 + 0xBC) != 0) {
                    *(u8 *)(temp_v1_16 + 0xBC) = 0U;
                    func_L01_00394240(D_L01_001B255C + (((UView *)(temp_s4))->i[0xBE] << 8));
                }
            }
            temp_s1_2 = temp_s4 + 0x2A0;
            temp_s0_3 = ((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x10;
            func_00282F20(temp_s0_3, temp_s1_2, temp_f21_3 * func_00282DF0(temp_s1_2));

            *(f32 *)((((u8 *)((UView *)(temp_s4))->p[0xC0])) + 0x18) = (f32) (*(f32 *)((((u8 *)((UView *)(temp_s4))->p[0xC0])) + 0x18) + (func_00283198(temp_f21_3 * 3.1415927f) * 4.0f));
            temp_a0_4 = ((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x10;
            func_00282CC0(temp_a0_4, temp_a0_4, D_00189EA0);
            temp_s1_3 = *(u8 **)(((u8 *)((UView *)(temp_s4))->p[0xC0]) + 0x68);
            temp_s0_4 = temp_s1_3 + 0x10;
            func_00282CF0(temp_s0_4, arg0 + 0x10, D_00189EA0);
            func_00282F20(temp_s0_4, temp_s0_4, 2.5f);
            *(f32 *)(temp_s1_3 + 0x1C) = func_00283B98(func_00283248(*(f32 *)(temp_s1_3 + 0x10), *(f32 *)(temp_s1_3 + 0x14)), 3.1415927f);
            func_00282CC0(temp_s0_4, temp_s0_4, D_00189EA0);
            func_002A0F48(((u8 *)((UView *)(temp_s4))->p[0xC0]));
            ((UView *)(temp_s4))->f[0xAB] = temp_f21_3;
        }
        temp_a0_5 = ((u8 *)((UView *)(temp_s4))->p[0xC0]);
        if ((temp_a0_5 == NULL) || (*(s16 *)(temp_a0_5 + 0xAA) != 0x1250) || (temp_v1_17 = *(u8 *)(temp_a0_5 + 0x20), (temp_v1_17 == 0xFE)) || (temp_v1_17 == 0xFD)) {
            func_002A6C58(arg0, 0, 3);

            if ((((UView *)(arg0))->b[0xB0]) != 0xFF) {
                func_002A0430((u32) (((UView *)(arg0))->b[0xB0]));
            }
            if (((UView *)(temp_s4))->i[0xC1] != -1) {
                func_0027D330(0x10);
                func_L00_00303530(0, 0);
                temp_a0_6 = D_L01_001B264C + (((UView *)(temp_s4))->i[0xC1] << 7);
                func_L00_002B9D60(temp_a0_6 + 0x30, temp_a0_6 + 0x70, 0, 1);
                func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
            }
            temp_v1_19 = ((UView *)(temp_s4))->i[0xC2];
            if (temp_v1_19 != -1) {
                (*(s8 *)((u8 *)((temp_v1_19 << 8) + (s32)D_L01_001B255C_sda) + 0xBC)) = 1;
            }
            func_L01_00323310(((UView *)(temp_s4))->i[0xC5], ((UView *)(temp_s4))->i[0xC7]);
            func_0029F338(arg0);
            return;
        }
        break;
    }
        temp_f1 = func_L01_003BAFB0();
        if ((((UView *)(arg0))->b[0x95] != 0) && (((HeroV *)D_00189E20)->z < (temp_f1 - 1.8f)) && (((HeroV *)D_00189E20)->z < (((UView *)(arg0))->f[0x6] - 1.0f)) && (func_00282E80(arg0 + 0x10, &((HeroV *)D_00189E20)->x) < 10.0f)) {
            func_L00_002B30E8();
        }
        func_L01_003C0140(arg0);
}
