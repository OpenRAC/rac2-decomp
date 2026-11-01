#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 x0[7]; s32 x1C; u8 x20[0xC0]; } LevelInfo;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
extern char D_00138180[];
extern u8 D_00138320[];
extern f32 D_L20_00298970[];
extern u8 D_00138354[];
extern u8 D_00139568[];
extern u8 D_00188660[];
extern char D_00189E20[];
extern char D_00189F10[];
extern char D_0018C750[];
extern u8 D_0018CF10[];
extern u32 D_001A7390 MACRO_ADDR;
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 D_001A7B08[0x40] MACRO_ADDR;
extern u8 D_001A7B2A MACRO_ADDR;
extern f32 D_L20_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L20_001A8FF0 MACRO_ADDR;
extern u8 D_L20_001ACEE8[];
extern s32 D_L20_001AFF00 MACRO_ADDR;
extern s32 D_L20_001B2AC8 MACRO_ADDR;
extern s32 D_L20_001B3730 MACRO_ADDR;
extern s32 D_L20_001B3738 MACRO_ADDR;
extern u8 D_L20_001B9E80[];
extern u8 D_L20_001B9FD8[];
extern u8 D_L20_001BA248[];
extern u8 D_L20_001C4480[];
extern u8 D_L20_00267210[];
extern u8 D_L20_00267270[];
extern u8 D_L20_00267274[];
extern Rec2C D_L20_00268D90[];
extern u8 D_L20_00269110[];
extern u8 D_L20_0026D970[];
extern s32 func_002761F8(s32, s32, s32, s32, s32);
extern s32 func_00277F48(f32, s32, s32, s32, s32);
extern s32 func_00282948(s32);
extern s32 func_00282978(s32);
extern f32 func_00282C10(f32);
extern f32 func_00282C48(f32);
extern void func_00282C88(s32);
extern void func_00282CC0(s32, s32, s32);
extern void func_00282CF0(s32, s32, s32);
extern void func_00282D30(s32, s32, f32);
extern f32 func_00282DB0(s32, s32);
extern void func_00282DD8(s32, s32, s32);
extern f32 func_00282DF0(s32);
extern f32 func_00282E20(s32);
extern f32 func_00282E48(s32, s32);
extern f32 func_00282E80(s32, s32);
extern void func_00282F20(s32, s32, f32);
extern void func_00282F70(s32, s32, f32);
extern void func_00283098(s32, s32, s32);
extern void func_002830C0(s32, s32, s32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00283248(f32, f32);
extern void func_00283410(s32, s32);
extern void func_00283698(s32, s32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283C80(f32, f32);
extern s32 func_00283CF0(f32);
extern void func_00290010(s32, s32, s32, f32);
extern s32 func_0029EFD0(s32);
extern void func_0029FCC0(s32, s32, s32);
extern void func_002A0F48(s32);
extern s32 func_002A77E0(s32);
extern s32 func_002A7820(s32, s32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002A78D8(f32, f32);
extern s32 func_002A88A0(s32, s32, f32, f32, f32);
extern void func_002A8C00(s32, s32, s32, f32, s32);
extern void func_002A8C28(s32, s32, s32, f32, f32, f32, s32, s32, s32);
extern void func_002A8F70(s32, s32, s32, s32, s32, f32);
extern f32 func_002AA2E8(s32, f32, f32);
extern f32 func_002AA3A8(s32, s32, f32, f32, f32, f32);
extern f32 func_002AA458(s32, s32, s32, f32, f32, f32);
extern f32 func_002AA738(s32, f32, f32);
extern void func_002AA800(s32, s32, f32, f32);
extern f32 func_002AA898(s32, f32, s32, f32, f32, f32, s32);
extern s32 func_002ABB78(s32);
extern void func_002AC9F8(s32, f32);
extern void func_002AF000(s32, f32, f32, f32);
extern void func_002BE278(s32, s32, s32, f32);
extern s32 func_002BF728(s32, s32, f32, f32);
extern void func_002E59F8(s32);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_002FD1B8(s32, s32, void *, f32, f32, f32, f32);
extern void func_L00_002A9D38(s32, s32, f32);
extern void func_L00_002A9E30(f32, f32, f32, f32);
extern f32 func_L00_002A9F30(s32, s32);
extern void func_L00_002AA0F0(f32, f32, f32);
extern void func_L00_002AA478(s32, s32);
extern void func_L00_002AA570(s32, s32);
extern void func_L00_002AA750(s32, s32);
extern void func_L00_002AA938(s32, s32, s32);
extern void func_L00_002AABE0(s32, s32, s32);
extern void func_L00_002AAE00(void);
extern void func_L00_002AB0A8(f32, f32);
extern void func_L00_002AB0C0(f32, f32);
extern void func_L00_002AB0D8(f32, f32);
extern void func_L00_002AB0F0(f32, f32);
extern void func_L00_002AC578(void);
extern s32 func_L00_002ACF88(s32, s32, s32);
extern s32 func_L00_002ADEA0(s32);
extern void func_L00_002B35A0(void);
extern s32 func_L00_002B3998(f32);
extern void func_L00_002B39F0(f32, s32);
extern void func_L00_002B3D10(void);
extern void func_L00_002B3DC0(f32, f32, f32);
extern void func_L00_002B3EF8(s32, f32, f32, f32);
extern void func_L00_002B3F68(void);
extern void func_L00_002B41B8(f32, f32);
extern void func_L00_002B4208(f32);
extern void func_L00_002B42D8(s32);
extern void func_L00_002B4308(void);
extern void func_L00_002B54F8(f32, f32);
extern f32 func_L00_002B5590(s32);
extern void func_L00_002B6198(f32);
extern void func_L00_002B6560(void);
extern void func_L00_002B6BC8(void);
extern void func_L00_002B75A0(f32, f32, f32);
extern void func_L00_002B7B80(void);
extern void func_L00_002B8930(void);
extern void func_L00_002B8CB8(void);
extern void func_L00_002B8F00(s32, s32, s32, f32, f32, f32);
extern void func_L00_002B94D8(f32);
extern void func_L00_002B9598(void);
extern f32 func_L00_002B9B38(s32, s32);
extern s32 func_L00_002B9B88(s32, s32);
extern void func_L00_002B9BB0(s32, s32, s32);
extern void func_L00_002B9F00(f32, f32, f32);
extern void func_L00_002BA138(s32, s32);
extern void func_L00_002BA220(void);
extern void func_L00_002BA508(void);
extern void func_L00_002C9228(void);
extern s32 func_L00_002CAF20(void);
extern void func_L00_002D2168(s32, s32, f32);
extern void func_L00_002D34C0(s32, s32, f32);
extern void func_L00_002D36E0(s32, s32, f32, f32, f32);
extern void func_L00_002D3778(s32, s32, f32);
extern void func_L00_002D3798(s32, s32, f32);
extern void func_L00_002D38A0(s32, s32, f32);
extern void func_L00_002D3960(s32, s32);
extern f32 func_L00_002D3A58(s32);
extern f32 func_L00_002D3B00(s32);
extern void func_L00_002D3B58(s32, s32, f32);
extern void func_L00_002D3BD8(s32, s32, f32);
extern s32 func_L00_002D6900(s32);
extern s32 func_L00_002EE4D8(s32, s32, f32);
extern s32 func_L00_0031D620(s32, s32, f32);
extern void func_L00_00322A98(s32, s32);
extern void func_L00_00322AC0(s32, s32, s32, f32);
extern void func_L00_00322BE0(s32, s32);
extern void func_L00_00323F28(s32, s32, f32, f32, f32);
extern s32 func_L00_00325FC8(s32, s32, s32, f32);
extern f32 func_L00_0032F038(s32);
extern s32 func_L00_00338D28(s32, s32, f32);
extern s32 func_L00_003417B8(s32, s32, s32, s32);
extern s32 func_L00_00341820(s32, s32, s32, s32, s32, f32);
extern s32 func_L00_00341FA8(s32, s32, s32, s32, s32, s32, f32, f32, f32);
extern void func_L00_0041E958(f32, f32, f32);
extern s32 func_L18_00428738(s32);
extern s32 func_L00_002A4E48(s32);
extern void func_L00_002B4458(s32);
extern s32 ref_US2_L13_002C58E8_01;
extern char D_US2_001A8F20[] MACRO_ADDR;
extern void func_L02_00392C70();
extern void func_L02_003948D0();

void func_US2_L13_002C58E8(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    f32 v50[4] __attribute__((aligned(16)));
    f32 v60[4] __attribute__((aligned(16)));
    f32 m70[16] __attribute__((aligned(16)));
    f32 vB0[4] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* var_v0_3_u2;
    void* var_s1_5_u2;
    f32 var_f12_16_u2;
    void* var_a1_5_u2;
    s32 var_a0_2_u2;
    void* var_s0_3_u2;
    s32 var_v0_8_u2;
    s32 var_v1_4_u2;
    void* var_a0_13_u2;
    s32 var_a0_2_u3;
    void* var_s0_3_u3;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 spE0;
    f32 spE4;
    f32 spE8;
    f32 spEC;
    f32 spF0;
    f32 spF4;
    f32 spF8;
    s32 spFC;
    f32 sp100;
    s32 sp104;
    f32 sp108;
    f32 sp10C;
    f32 sp110;
    s32 sp114;
    s32 sp118;
    s32 sp11C;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_20;
    f32 temp_f0_21;
    f32 temp_f0_22;
    f32 temp_f0_23;
    f32 temp_f0_24;
    f32 temp_f0_25;
    f32 temp_f0_26;
    f32 temp_f0_27;
    f32 temp_f0_28;
    f32 temp_f0_29;
    f32 temp_f0_2;
    f32 temp_f0_30;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f12_7;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f1_11;
    f32 temp_f1_12;
    f32 temp_f1_13;
    f32 temp_f1_14;
    f32 temp_f1_15;
    f32 temp_f1_16;
    f32 temp_f1_17;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f1_9;
    f32 temp_f20;
    f32 temp_f20_10;
    f32 temp_f20_11;
    f32 temp_f20_12;
    f32 temp_f20_13;
    f32 temp_f20_14;
    f32 temp_f20_15;
    f32 temp_f20_16;
    f32 temp_f20_17;
    f32 temp_f20_18;
    f32 temp_f20_19;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f20_6;
    f32 temp_f20_7;
    f32 temp_f20_8;
    f32 temp_f20_9;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f3;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_12;
    f32 var_f0_13;
    f32 var_f0_14;
    f32 var_f0_15;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f12;
    f32 var_f12_10;
    f32 var_f12_11;
    f32 var_f12_13;
    f32 var_f12_14;
    f32 var_f12_15;
    f32 var_f12_16;
    f32 var_f12_17;
    f32 var_f12_18;
    f32 var_f12_19;
    f32 var_f12_20;
    f32 var_f12_21;
    f32 var_f12_22;
    f32 var_f12_4;
    f32 var_f12_5;
    f32 var_f12_6;
    f32 var_f12_7;
    f32 var_f12_8;
    f32 var_f12_9;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f20;
    f32 var_f20_10;
    f32 var_f20_11;
    f32 var_f20_12;
    f32 var_f20_13;
    f32 var_f20_2;
    f32 var_f20_3;
    f32 var_f20_4;
    f32 var_f20_5;
    f32 var_f20_6;
    f32 var_f20_7;
    f32 var_f20_8;
    f32 var_f20_9;
    f32 var_f21;
    f32 var_f21_2;
    f32 var_f21_3;
    f32 var_f21_4;
    f32 var_f21_5;
    f32 var_f21_6;
    f32 var_f21_7;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f23;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    s16 temp_a2_5;
    s32 temp_v0_4;
    s16 temp_v0_8;
    s32 temp_v1_10;
    s32 temp_v1_9;
    s32 temp_a0_21;
    s32 temp_a0_3;
    s32 temp_a0_5;
    s32 temp_a0_7;
    s32 temp_a0_8;
    s32 temp_a0_9;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_7;
    s32 temp_a1_8;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_s0_5;
    s32 temp_s0_9;
    s32 temp_s7;
    s32 temp_v0;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_16;
    s32 temp_v0_17;
    s32 temp_v0_2;
    s32 temp_v1_12;
    s32 temp_v1_14;
    s32 temp_v1_16;
    s32 temp_v1_18;
    s32 temp_v1_20;
    s32 temp_v1_21;
    s32 temp_v1_22;
    s32 temp_v1_23;
    s32 temp_v1_24;
    s32 temp_v1_26;
    s32 temp_v1_34;
    s32 temp_v1_35;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a0;
    s32 var_a0_10;
    s32 var_a0_11;
    s32 var_a0_12;
    s32 var_a0_2;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_8;
    s32 var_a0_9;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32* var_s1_4;
    s32* var_s1_6;
    u16 temp_v0_3;
    u16 temp_v1_11;
    u16 temp_v1_2;
    u32 temp_a0;
    u32 temp_v1;
    u32 temp_v1_13;
    u32 temp_v1_27;
    u32 temp_v1_28;
    u32 temp_v1_29;
    u32 temp_v1_30;
    u32 temp_v1_31;
    u32 temp_v1_33;
    u32 temp_v1_36;
    u32 temp_v1_3;
    u32 var_a1_3;
    u8 temp_a0_14;
    u8 temp_a0_2;
    u8 temp_v1_25;
    u8 var_a0_6;
    void* temp_a0_10;
    void* temp_a0_11;
    void* temp_a0_12;
    void* temp_a0_13;
    void* temp_a0_15;
    void* temp_a0_16;
    void* temp_a0_17;
    void* temp_a0_4;
    void* temp_a0_6;
    void* temp_a1;
    void* temp_a1_2;
    void* temp_a1_6;
    void* temp_fp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* temp_s0;
    void* temp_s0_2;
    void* temp_s0_3;
    void* temp_s0_4;
    void* temp_s0_6;
    void* temp_s0_7;
    void* temp_s0_8;
    void* temp_s1;
    void* temp_s1_2;
    void* temp_s1_3;
    void* temp_s1_4;
    void* temp_s1_5;
    void* temp_s1_6;
    void* temp_s1_7;
    void* temp_s1_8;
    void* temp_s2;
    void* temp_s2_2;
    void* temp_s2_3;
    void* temp_s2_4;
    void* temp_s2_5;
    void* temp_s4;
    void* temp_s4_2;
    void* temp_s5;
    void* temp_v0_10;
    void* temp_v0_5;
    void* temp_v0_6;
    void* temp_v0_7;
    void* temp_v0_9;
    void* temp_v1_15;
    void* temp_v1_17;
    void* temp_v1_32;
    void* temp_v1_37;
    void* temp_v1_38;
    void* temp_v1_39;
    void* var_a0_13;
    void* var_a0_7;
    void* var_a1_5;
    void* var_s0_3;
    void* var_s1_5;
    void* var_v0_3;

    sp114 = ((Hero *)D_00189E20)->i[0x2298/4];
    temp_fp = ((Hero *)D_00189E20)->ptr[0x2290/4];
    sp118 = (s32) M2C_FIELD(temp_fp, u8* , 0x43);
    switch (((Hero *)D_00189E20)->u[0x2294/4]) {                              /* switch 1 */
    case 0x0:                                       /* switch 1 */
    case 0x1:                                       /* switch 1 */
    case 0x3:                                       /* switch 1 */
    case 0x4:                                       /* switch 1 */
    case 0x1C:                                      /* switch 1 */
    case 0x1D:                                      /* switch 1 */
    case 0x1E:                                      /* switch 1 */
    case 0x39:                                      /* switch 1 */
    case 0x6D:                                      /* switch 1 */
    case 0x6F:                                      /* switch 1 */
    case 0x7D:                                      /* switch 1 */
        if (((Hero *)D_00189E20)->b[0x22B9] != 0) {
            func_L00_002AA478(0xF, 0x1E);
        }
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            func_L00_002B54F8(0.7f, 0.0f);
        } else {
            func_L00_002B54F8(0.5f, 0.033333335f);
        }
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        func_L00_002B39F0(1.0f, 0);
        temp_v1 = ((Hero *)D_00189E20)->u[0x2294/4];
        if ((temp_v1 == 1) || (temp_v1 == 0x1D)) {
            if (((Hero *)D_00189E20)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                func_00283098((s32) (((void*)D_00189E20) + 0x190), (s32)((TI128*)v0), (s32)&D_L20_001B9FD8[0x218]);
                ((Hero *)D_00189E20)->f[0x1A0/4] = ((Hero *)D_L20_001B9FD8)->f[0];
                func_L00_002B3EF8(0, 1.0f, 0.0f, 2.9088826f);
                if ((((Hero *)D_00189E20)->b[0x22BB] != 0) && (((Hero *)D_00189E20)->i[0x1B8/4] == 0x78)) {
                    if (((Hero *)D_0018C750)->uh[0xD8/2] < 0xFFFF) {
                        ((Hero *)D_0018C750)->uh[0xD8/2]++;
                    }
                    if (D_001A7390 > ((Hero *)D_0018C750)->u[0xDC/4]) {
                        ((Hero *)D_0018C750)->u[0xDC/4] = D_001A7390;
                    }
                    ((Hero *)D_0018C750)->u[0xE0/4] = ((Hero *)D_0018C750)->u[0xE0/4] | (1 << D_001A79F0) | 0x80000000;
                }
            }
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 3) {
            if (func_L00_002CAF20() != 0) {
                break;
            }
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 4) {
            if ((((Hero *)D_00189E20)->f[0x24B8/4] > 0.2f) || (temp_a0_2 = M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43), (temp_a0_2 == 0xE)) || (temp_a0_2 == 0xF)) {
                if (((Hero *)D_00189E20)->u[0x2294/4] == 4) {
                    func_L00_002B3EF8(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (func_00282C48(((Hero *)D_00189E20)->f[0x1A4/4]) > 0.0058177654f) {
                    temp_a0_3 = ((Hero *)D_00189E20)->f[0x1A4/4] < 0.0f;
                    temp_a0_3 += 0xE;
                    if (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43) != temp_a0_3) {
                        func_L00_002D2168(temp_a0_3, 0, 5.0f);
                    }
                    temp_f0 = func_00282C48(((Hero *)D_00189E20)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)D_00189E20)->f[0xC20/4] = temp_f0;
                    if (temp_f0 < 0.55f) {
                        ((Hero *)D_00189E20)->f[0xC20/4] = 0.55f;
                    }
                    if (((Hero *)D_00189E20)->f[0xC20/4] > 2.5f) {
                        ((Hero *)D_00189E20)->f[0xC20/4] = 2.5f;
                    }
                } else if (((Hero *)D_00189E20)->f[0x1A4/4] == 0.0f) {
                    if (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43) != 0xD) {
                        func_L00_002D2168(0xD, 0, 7.0f);
                    }
                }
            }
        }
            temp_v1_3 = ((Hero *)D_00189E20)->u[0x2294/4];
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
            if (temp_v1_3 == 3) {
                var_f12 = ((Hero *)D_00189E20)->f[0x17C/4] + 1.0f;
                if (var_f12 > 1.0f) {
                    var_f12 = 1.0f;
                }
                temp_a0_4 = ((Hero *)D_00189E20)->ptr[0x2290/4];
                var_f20 = var_f12 * 0.0075000003f;
                ((Hero *)D_00189E20)->f[0x24AC/4] = var_f20;
                if (M2C_FIELD(temp_a0_4, u8* , 0x42) == M2C_FIELD(temp_a0_4, u8* , 0x43)) {
                    var_f1 = ((Hero *)D_00189E20)->f[0x174/4] / var_f20;
                    if ((var_f1 > 5.0f) && ((f32) M2C_FIELD(temp_a0_4, u8* , 0x41) < 5.5f)) {
                        func_L00_002A9E30(13.0f, var_f1, 0.5f, -1.0f);
                        if (((Hero *)D_00189E20)->f[0xC20/4] > 1.1f) {
                            ((Hero *)D_00189E20)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)D_00189E20)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (temp_v1_3 == 4) {
                var_f20 = 0.0075000003f;
                if (((Hero *)D_00189E20)->b[0x1492] != 0) {
                    var_f20 = 0.00047222225f;
                }
            } else {
                var_f20 = 0.004916667f;
            }
            func_L00_002B41B8(0.0f, var_f20);
            func_00282C88((s32)(D_00189E20 + 0xF0));
            func_L00_002B94D8(var_f20);
            if ((((Hero *)D_00189E20)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                var_a0_2 = (s32)(D_00189E20 + 0xF0);
                if (((Hero *)D_00189E20)->f[0x31C/4] > 0.2f) {
                    func_L00_002D34C0(var_a0_2, var_a0_2 + 0x30, 0.0061111115f);
                } else {
                    func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.015000001f);
                    if (((Hero *)D_00189E20)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)D_00189E20)->q[0x80/16], &((Hero *)D_00189E20)->q[0x2D0/16]);
                        ((Hero *)D_00189E20)->f[0x31C/4] = 0.0f;
                        ((Hero *)D_00189E20)->h[0x34E/2] = 0;
                    }
                }
            } else {
                func_L00_002B4458(0);
                if (((Hero *)D_00189E20)->h[0x34E/2] == 0) {
                    func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
                } else {
                    func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x130, 0.0069444445f);
                    func_L00_002B4308();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        hero7C = (void*)D_00189E20;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            temp_v0 = func_0029EFD0(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = temp_v0;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)temp_v0 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)temp_v0 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(temp_v0, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            temp_v1_4 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(temp_v1_4, u16* , 0x34) = (u16) (M2C_FIELD(temp_v1_4, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            func_002E5CF8(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += func_00283CF0(5.0f);
        temp_v1_6 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(temp_v1_6, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(temp_v1_6, u8* , 0x23) = 0x80U;
        }
        temp_a0_5 = ((Hero *)hero7C)->i[0x7A4/4];
        temp_a1 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)temp_a0_5 + 0x10, (u8 *)temp_a1 + 0x10);
        qcopy((u8 *)temp_a0_5 + 0xF0, (u8 *)temp_a1 + 0xF0);
        func_002A0F48(temp_a0_5);
        }
        ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), func_00282E20((s32)(D_00189E20 + 0xF0)) * 0.92f);
        func_L00_002C9228();
        break;
    case 0x32:                                      /* switch 1 */
    case 0x33:                                      /* switch 1 */
    case 0x34:                                      /* switch 1 */
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x34) {
            if (((Hero *)D_00189E20)->i[0x1B8/4] >= 0x47) {
                (*(u16*)&D_0018CF10) = 0xFFFF;
            }
            func_L00_002B9BB0(5, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0xF);
            func_L00_002D6900(0x16);
        } else {
            temp_a2 = ((Hero *)D_00189E20)->i[0x2440/4];
            if (temp_a2 != -1) {
                temp_a0_6 = (temp_a2 * 0x70) + (s32)D_00188660;
                if (M2C_FIELD(temp_a0_6, s32* , 0x88) == ((Hero *)D_00189E20)->ptr[0x2290/4]) {
                    if (M2C_FIELD(temp_a0_6, u8* , 0x74) != 0) {
                        func_002E59F8(temp_a2);
                    }
                }
            }
            ((Hero *)D_00189E20)->i[0x2440/4] = -1;
        }
        if (((Hero *)D_00189E20)->h[0xA4A/2] != 0) {
            func_00282978((s32) (((void*)D_00189E20) + 0xA4A));
            temp_a0_7 = (s32) ((u16) ((Hero *)D_00189E20)->h[0xA4A/2] << 0x10) >> 0x12;
            func_L00_002AA938((temp_a0_7 >= 9) ? 8 : temp_a0_7, 0, 0);
        }
        if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x32) && (((Hero *)D_00189E20)->i[0xC2C/4] == 0)) {
            temp_f1_2 = ((Hero *)D_00189E20)->f[0xC38/4];
            if (temp_f1_2 > 0.0f) {
                if (temp_f1_2 < 10.0f) {
                    func_L00_002AA938(4, 1, 0);
                }
            }
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x33) {
            if (((Hero *)D_00189E20)->i[0x22A0/4] == 0x34) {
                temp_v1_7 = ((Hero *)D_00189E20)->i[0x1B8/4];
                if (temp_v1_7 < 0xF) {
                    func_L00_002AA938(((s32) (0x14 - temp_v1_7) / 3) + 1, 1, 0);
                }
            }
        }
        temp_v1_8 = ((Hero *)D_00189E20)->i[0x2298/4];
        if (temp_v1_8 == 1) {
            if (((Hero *)D_00189E20)->i[0x1B8/4] == temp_v1_8) {
                func_L00_002AABE0(3, 0x10, 0);
                if (D_L20_001B3730 != 0) {
                    func_002FD1B8(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)D_00189E20)->f[0x80/4], ((Hero *)D_00189E20)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)D_00189E20)->h[0xA4A/2] = 0x46;
            }
            temp_v0_2 = ((Hero *)D_00189E20)->i[0xA20/4] + 1;
            ((Hero *)D_00189E20)->i[0xA20/4] = temp_v0_2;
            if (temp_v0_2 >= 0x29) {
                ((Hero *)D_00189E20)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)D_00138180)->f[0x12C/4] > ((Hero *)D_00138180)->f[0x128/4] ? ((Hero *)D_00138180)->f[0x12C/4] : ((Hero *)D_00138180)->f[0x128/4]) * 0.008726647f;
        var_f12_4 = 0.0f;
        k02 = 0.2f;
        if ((((((Hero *)D_00138180)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)D_00189E20)->i[0x2298/4] == 1)) {
            var_f12_6 = ((Hero *)D_00138180)->f[0x12C/4] * 1.5f;
            if (var_f12_6 > 1.0f) {
                var_f12_6 = 1.0f;
            }
            if (var_f12_6 < k02) {
                var_f12_6 = k02;
            }
            if (((Hero *)D_00138180)->i[0x1DC/4] != 0x79) {
                temp_v1_9 = ((Hero *)D_00189E20)->uh[0xA42/2] + 1;
                ((Hero *)D_00189E20)->uh[0xA40/2] = 0U;
                var_f12_6 = ((f32) (s16) temp_v1_9 * 0.025f) + 0.5f;
                ((Hero *)D_00189E20)->uh[0xA42/2] = (u16) temp_v1_9;
                if (var_f12_6 > 1.0f) {
                    var_f12_6 = 1.0f;
                }
            }
            if ((((Hero *)D_00189E20)->i[0x2298/4] == 1) && (var_f12_6 < 0.35f)) {
                var_f12_6 = 0.35f;
            }
            var_f12_4 = var_f12_6 * 1.361357f;
        } else if ((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0x40) {
            var_f12_5 = ((Hero *)D_00138180)->f[0x128/4] * 1.5f;
            if (var_f12_5 > 1.0f) {
                var_f12_5 = 1.0f;
            }
            if (var_f12_5 < k02) {
                var_f12_5 = k02;
            }
            if (((Hero *)D_00138180)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)D_00189E20)->uh[0xA40/2] + 1;
                ((Hero *)D_00189E20)->uh[0xA42/2] = 0U;
                ((Hero *)D_00189E20)->h[0xA40/2] = cntA40;
                var_f12_5 = ((f32) (s16) cntA40 * 0.025f) + 0.5f;
                if (var_f12_5 > 1.0f) {
                    var_f12_5 = 1.0f;
                }
            }
            if ((f32) ((Hero *)D_00189E20)->i[0x24C0/4] < 1500.0f) {
                var_f12_5 = 1.0f;
            }
            var_f12_4 = var_f12_5 * -1.361357f;
        } else {
            ((Hero *)D_00189E20)->uh[0xA40/2] = 0U;
            ((Hero *)D_00189E20)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0x40) {
            ((Hero *)D_00189E20)->uh[0xA4E/2] = (u16) (((Hero *)D_00189E20)->uh[0xA4E/2] + 1);
            if (((Hero *)D_00138180)->f[0x128/4] > 0.75f) {
                temp_v1_10 = ((Hero *)D_00189E20)->uh[0xA4C/2] + 1;
                ((Hero *)D_00189E20)->h[0xA4C/2] = temp_v1_10;
                if ((s16) temp_v1_10 >= 0x5B) {
                    temp_v1_11 = ((Hero *)D_0018C750)->uh[0x84/2];
                    if (temp_v1_11 <= 0xFFFEU) {
                        ((Hero *)D_0018C750)->uh[0x84/2] = (u16) (temp_v1_11 + 1);
                    }
                }
                temp_v1_12 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)D_0018C750)->u[0x88/4] < (u32) temp_v1_12) {
                    ((Hero *)D_0018C750)->u[0x88/4] = (u32) temp_v1_12;
                }
                ((Hero *)D_0018C750)->i[0x8C/4] = (s32) (((Hero *)D_0018C750)->i[0x8C/4] | (1 << (*(s32*)&D_001A79F0)) | 0x80000000);
            } else {
                ((Hero *)D_00189E20)->uh[0xA4C/2] = 0U;
            }
        } else {
            ((Hero *)D_00189E20)->uh[0xA4E/2] = 0U;
            ((Hero *)D_00189E20)->uh[0xA4C/2] = 0U;
        }
        if (((Hero *)D_00138180)->i[0x1A4/4] & 0x40) {
            hp32 = (Hero *)D_00189E20;
            if ((D_L20_001B2AC8 - hp32->i[0xA54/4]) < 0x46) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = D_L20_001B2AC8;
        }
        if ((s16) ((Hero *)D_00189E20)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)D_00189E20)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0x80) {
            ((Hero *)D_00189E20)->i[0xA50/4] = 0;
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x33) {
            var_f12_4 = 0.0f;
        }
        temp_f20 = ((Hero *)D_00189E20)->f[0x94/4];
        func_002AA898((s32) (((void*)D_00189E20) + 0x94), var_f12_4, (s32) (((void*)D_00189E20) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        temp_f22 = func_00283BE0(((Hero *)D_00189E20)->f[0x94/4], temp_f20);
        func_L00_002B39F0(1.0f, 0);
        func_L00_002B3EF8(0, 0.007f, 0.08f, 0.087266475f);
        ((Hero *)D_00189E20)->f[0xA2C/4] = (f32) ((Hero *)D_00189E20)->f[0x1A4/4];
        func_00282948((s32) (((void*)D_00189E20) + 0xA34));
        if (((Hero *)D_00189E20)->i[0x2298/4] == 1) {
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.10000001f;
        } else if (((Hero *)D_00189E20)->u[0x2294/4] == 0x34) {
            if ((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0xA) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.116666675f;
            } else {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.04666667f;
            }
        } else {
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.050000004f;
        }
        var_f2 = ((Hero *)D_00189E20)->f[0x24B8/4];
        if (((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0xC0) || (((Hero *)D_00189E20)->i[0x2298/4] == 1)) {
            if (var_f2 < 1.0f) {
                var_f2 = 1.0f;
            }
        }
        if (((Hero *)D_00189E20)->f[0x24B8/4] > 0.15f) {
            var_f0_2 = 0.35f;
            if (((Hero *)D_00189E20)->u[0x2294/4] == 0x34) {
                var_f0_2 = 0.4f;
            }
            if (var_f2 < var_f0_2) {
                var_f2 = var_f0_2;
            }
        }
        if ((((Hero *)D_00189E20)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0xA)) {
            ((Hero *)D_00189E20)->f[0x1B0/4] = (f32) (((Hero *)D_00189E20)->f[0x1B0/4] * var_f2);
        }
        if (func_00282948((s32)(D_00189E20 + 0xA30)) != 0) {
            heroA30 = (void*)D_00189E20;
            func_0029FCC0((s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            func_00283098((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)D_00189E20)->ptr[0x2290/4] + 0xC0));
            func_00282CC0((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)D_00189E20)->q[0x110/16]);
            func_00282F20((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            func_00282CC0((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            func_002BF728((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            if ((f32) func_002A77E0(0x64) < 40.0f) {
                var_a0_4 = 4;
                var_a1_2 = 0xB;
            } else {
                var_a0_4 = 0x28;
                var_a1_2 = 0x5A;
            }
            ((Hero *)heroA30)->i[0xA30/4] = func_002A7820(var_a0_4, var_a1_2);
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x34) {
            if (func_00282978((s32) (((void*)D_00189E20) + 0xA38)) != 0) {
                temp_s4 = ((Hero *)D_00189E20)->ptr[0x1310/4];
                if (temp_s4 != 0) {
                    if (M2C_FIELD(temp_s4, s16* , 0xAA) == 0x261) {
                        for (var_s1 = 0; var_s1 < 4; var_s1++) {
                            func_0029FCC0((s32) temp_s4, var_s1 % 2, (s32)((TI128*)v0));
                            (*(TI128*)v20) = 0;
                            v20[0] = -0.15f;
                            func_00283098((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)D_00189E20)->ptr[0x2290/4] + 0xC0));
                            func_00282CC0((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
                            v0[0] += func_002A7878(0.0f, 0.03f);
                            v0[1] += func_002A7878(0.0f, 0.03f);
                            v0[2] += func_002A7878(0.0f, 0.03f);
                            qcopy(v10, &((Hero *)D_00189E20)->q[0x110/16]);
                            func_L00_00323F28((s32) ((TI128*)v10), (s32) ((TI128*)v10), -0.012500001f, ((Hero *)D_00189E20)->f[0x98/4], ((Hero *)D_00189E20)->f[0x94/4]);
                            ((Hero *)D_00189E20)->h[0xA38/2] = func_00283CF0((0.116666675f - ((Hero *)D_00189E20)->f[0x1B4/4]) * 42.85714f);
                            func_002BF728((s32)((TI128*)v0), (s32) ((TI128*)v10), func_002A7878(6300.0f, 9450.0f), -1.0f);
                        }
                    }
                }
            }
            if (((Hero *)D_00189E20)->u[0x2294/4] == 0x34) {
                func_L00_002B41B8(0.003611111f, 0.0022222223f);
            } else {
                goto block_198;
            }
        } else {
block_198:
            func_L00_002B41B8(0.0019444445f, 0.0011111111f);
        }
        temp_f21 = func_00283B98(-((Hero *)D_00189E20)->f[0x94/4], 0.0f);
        temp_v1_13 = ((Hero *)D_00189E20)->u[0x2294/4];
        if (temp_v1_13 == 0x34) {
            func_002AF000((s32) (((void*)D_00189E20) + 0xF0), ((Hero *)D_00189E20)->f[0x1B4/4], ((Hero *)D_00189E20)->f[0x98/4], temp_f21);
        } else if (temp_v1_13 == 0x32) {
            var_f12_7 = ((Hero *)D_00189E20)->f[0x1B4/4] * func_L00_002A9F30((s32)D_L20_00269110, 0x1E) * 5.0f;
            if ((((Hero *)D_00189E20)->i[0x22A0/4] == 0x34) && (((Hero *)D_00189E20)->i[0x1B8/4] < 0xF) && (var_f12_7 < 0.075f)) {
                var_f12_7 = 0.075f;
            }
            func_002AF000((s32)(D_00189E20 + 0xF0), var_f12_7, ((Hero *)D_00189E20)->f[0x98/4], temp_f21);
        } else if (temp_v1_13 == 0x33) {
            spE0 = func_00282DF0((s32) (((void*)D_00189E20) + 0x160));
            if (((Hero *)D_00189E20)->i[0x22A0/4] == 0x34) {
                func_002AA2E8((s32) &spE0, 0.0f, 0.0022222223f);
            } else {
                func_002AA2E8((s32) &spE0, 0.0f, 0.0011111111f);
            }
            func_00282F20((s32)(D_00189E20 + 0x160), (s32)(D_00189E20 + 0x160), spE0);
            qcopy(&((Hero *)D_00189E20)->q[0xF0/16], &((Hero *)D_00189E20)->q[0x160/16]);
        }
        func_L00_002B4458(0);
        temp_f21_2 = ((Hero *)D_00189E20)->f[0xA2C/4] * func_00283180(temp_f21) * -7.0f;
        func_002AA898((s32) (((void*)D_00189E20) + 0x90), temp_f21_2, (s32) (((void*)D_00189E20) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        func_L00_002AB0C0(0.009f, 0.22f);
        func_L00_002AB0D8(0.04f, 0.2f);
        func_L00_002AB0F0(0.02f, 0.2f);
        temp_f2 = temp_f22 * 47.0f;
        ((Hero *)D_L20_00267210)->f[0x114/4] = temp_f2;
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (temp_f21_2 * 1.5f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (temp_f21_2 * 1.4f);
        if (temp_f2 > 0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = 0.8726647f;
        } else if (temp_f2 < -0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = -0.8726647f;
        }
        temp_f1_3 = temp_f22 * 40.0f;
        temp_f0_2 = temp_f21_2 * 1.1f;
        ((Hero *)D_L20_00267210)->f[0x364/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x368/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x324/4] = temp_f1_3;
        ((Hero *)D_L20_00267210)->f[0x328/4] = temp_f0_2;
        ((Hero *)D_L20_00267210)->f[0x414/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x418/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x3D4/4] = temp_f1_3;
        ((Hero *)D_L20_00267210)->f[0x3D8/4] = temp_f0_2;
        break;
    case 0x73:                                      /* switch 1 */
        temp_a0_8 = 0xA - ((s32) ((Hero *)D_00189E20)->i[0x1B8/4] / 3);
        temp_s1 = ((void*)D_00189E20) + 0xF0;
        func_L00_002AA938((temp_a0_8 >= 9) ? 8 : temp_a0_8, 0, 0);
        ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) temp_s1, (s32) temp_s1, func_00282E20((s32) temp_s1) * 0.92f);
        func_L00_002B4458(0);
        break;
    case 0x72:                                      /* switch 1 */
        func_L00_002AA478(0xF, 0x1E);
        ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), func_00282E20((s32)(D_00189E20 + 0xF0)) * 0.92f);
        func_L00_002B4458(0);
        func_L00_002C9228();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        spE4 = func_00282DF0((s32)(D_00189E20 + 0x160));
        func_002AA2E8((s32) &spE4, 0.0f, 0.0011111111f);
        func_00282F20((s32)(D_00189E20 + 0x160), (s32)(D_00189E20 + 0x160), spE4);
        qcopy(&((Hero *)D_00189E20)->q[0xF0/16], &((Hero *)D_00189E20)->q[0x160/16]);
        if (func_00282948((s32) (((void*)(D_00189E20 + 0x160)) + 0x8D0)) == 2) {
            temp_s2 = ((void*)(D_00189E20 + 0x160)) - 0x160;
            func_0029FCC0(M2C_FIELD(temp_s2, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            func_00283098((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(temp_s2, s32* , 0x2290) + 0xC0);
            func_00282CC0((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)D_00189E20)->q[0x110/16]);
            func_00282F20((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            func_00282CC0((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            func_002BF728((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            temp_v1_14 = M2C_FIELD(temp_s2, s32* , 0x1B8);
            if (temp_v1_14 < 0x28) {
                lim67 = 5;
                var_v0_2 = func_002A7820(2, lim67) + ((s32) M2C_FIELD(temp_s2, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (temp_v1_14 >= 0x47) {
                var_v0_2 = func_002A7820(0xA, 0x14);
block_224:
                M2C_FIELD(temp_s2, s32* , 0xA30) = var_v0_2;
            }
        }
        if (((Hero *)D_00189E20)->f[0xA3C/4] > 0.0f) {
            ((Hero *)D_00189E20)->f[0xA3C/4] = 0.0f;
        }
        func_002AA2E8((s32) (((void*)D_00189E20) + 0xA3C), -0.025000002f, 0.00041666668f);
        ((Hero *)D_00189E20)->f[0xF8/4] = (f32) ((Hero *)D_00189E20)->f[0xA3C/4];
        break;
    case 0x35:                                      /* switch 1 */
    case 0x36:                                      /* switch 1 */
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x36) {
            func_L00_002AA478(0xF, 0x1E);
        }
        if (((Hero *)D_00189E20)->f[0x174/4] > 0.025000002f) {
            func_L00_002AA750(4, 0xC);
        }
        if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x35) && (((Hero *)D_00189E20)->f[0x174/4] > 0.016666668f)) {
            func_L00_002AA570(0, 1);
        }
        if (((Hero *)D_00189E20)->h[0xA4A/2] != 0) {
            ((Hero *)D_00189E20)->h[0xA4A/2] -= 1;
            temp_a0_9 = ((Hero *)D_00189E20)->h[0xA4A/2] >> 3;
            func_L00_002AA938((temp_a0_9 >= 7) ? 6 : temp_a0_9, 0, 0);
        }
        ((Hero *)D_00189E20)->f[0xC20/4] = 0.6f;
        func_L00_002B39F0(0.050000004f, 0);
        if ((((Hero *)D_00138180)->i[0x1D4/4] == 0) && (((Hero *)D_00189E20)->f[0x1B0/4] < 0.025000002f)) {
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.025000002f;
        }
        func_L00_002B3EF8(0, 0.007f, 0.08f, 0.087266475f);
        func_00282948((s32)(D_00189E20 + 0x798));
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x35) {
            if ((((Hero *)D_00138180)->i[0x1D4/4] != 0) && (((Hero *)D_00189E20)->i[0x798/4] != 0)) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.050000004f;
            }
            if (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) > 0.78539824f) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
            }
            func_L00_002B41B8(0.0011111111f, 0.0013888889f);
            temp_f20_2 = ((Hero *)D_00189E20)->f[0x1B4/4] * func_L00_002A9F30((s32)D_L20_00269110, 0x1E) * 5.5f;
            ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (func_00283180(((Hero *)D_00189E20)->f[0x98/4]) * temp_f20_2);
            temp_f0_3 = func_00283198(((Hero *)D_00189E20)->f[0x98/4]) * temp_f20_2;
            ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
            ((Hero *)D_00189E20)->f[0xF4/4] = temp_f0_3;
        } else {
            ((Hero *)D_00189E20)->f[0x1B4/4] = 0.0f;
            func_00282C88((s32)(D_00189E20 + 0xF0));
        }
        if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x35) && (((Hero *)D_00189E20)->i[0xC2C/4] == 0)) {
            temp_f1_4 = ((Hero *)D_00189E20)->f[0xC38/4];
            if ((temp_f1_4 > 0.0f) && (temp_f1_4 < 10.0f)) {
                func_L00_002AA938(4, 1, 0);
            }
        }
        func_L00_002B94D8(0.0011666666f);
        func_L00_002B4458(0);
        func_L00_002C9228();
        break;
    case 0x85:                                      /* switch 1 */
        temp_a1_2 = ((Hero *)D_00189E20)->ptr[0x1830/4];
        qcopy(&((Hero *)D_00189E20)->q[0x80/16], (u8 *)temp_a1_2 + 0x10);
        qcopy(&((Hero *)D_00189E20)->q[0x90/16], (u8 *)temp_a1_2 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        func_00282D30((s32)((TI128*)v0), (s32)(D_00189E20 + 0x2C0), -1.0f);
        var_f12_8 = 0.0f;
        if (((Hero *)D_00189E20)->f[0x24B8/4] > 0.2f) {
            var_f12_8 = -((Hero *)D_00189E20)->f[0x1FB4/4] * 0.75f;
        }
        func_002AA3A8((s32)(D_00189E20 + 0x7C0), (s32)(D_00189E20 + 0x7C4), var_f12_8, 0.007f, 0.3f, 0.03f);
        func_00282D30((s32) ((TI128*)v10), (s32)D_00189E20, ((Hero *)D_00189E20)->f[0x7C0/4]);
        func_00282CC0((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v10));
        func_00282F20((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        func_L00_002B8F00((s32)((TI128*)v0), (s32) ((TI128*)v30), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)D_00189E20)->f[0x1B4/4] = 0.21666668f;
        func_00282F20((s32)(D_00189E20 + 0xF0), (s32)D_00189E20, 0.21666668f);
        func_L00_002D3B58((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.0f);
        func_00282C88((s32)((TI128*)v0));
        v0[1] = -((Hero *)D_00189E20)->f[0x1FB0/4];
        func_00283098((s32)(D_00189E20 + 0x190), (s32)((TI128*)v0), (s32)&D_L20_001B9FD8[0x218]);
        func_L00_002B3EF8(0, 0.02f, 0.3f, 0.034906592f);
        break;
    case 0x2F:                                      /* switch 1 */
        anim2F = -1;
        blend2F = 0;
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            func_L00_002B54F8(0.7f, 0.0f);
        } else {
            func_L00_002B54F8(0.5f, 0.033333335f);
        }
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        func_L00_002B39F0(1.0f, 0);
        func_L00_002B41B8(0.004916667f, 0.004916667f);
        func_00282C88((s32)(D_00189E20 + 0xF0));
        func_L00_002B94D8(0.004916667f);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32) (((void*)(D_00189E20 + 0xF0)) + 0x20), 0.0069444445f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.015000001f);
        }
        if ((anim2F != -1) && (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            func_L00_002D2168(anim2F, 0, (f32) blend2F);
        } else {
            temp_v1_15 = ((Hero *)D_00189E20)->ptr[0x2290/4];
            if ((M2C_FIELD(temp_v1_15, u8* , 0x60) & 2) && (M2C_FIELD(temp_v1_15, u8* , 0x42) == 0x36)) {
                func_L00_002D2168(func_L00_002A4E48(0), 0, 5.0f);
            }
        }
        break;
    case 0x8A:                                      /* switch 1 */
    case 0x8B:                                      /* switch 1 */
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        func_L00_002B41B8(0.004916667f, 0.004916667f);
        func_00282C88((s32)(D_00189E20 + 0xF0));
        func_L00_002B94D8(0.004916667f);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32) (((void*)D_00189E20) + 0x120), 0.0061111115f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.015000001f);
        }
        var_v0_3 = ((Hero *)D_00189E20)->ptr[0xB10/4];
        if (var_v0_3 != 0) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(M2C_FIELD(var_v0_3, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(var_v0_3, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            func_L00_002B3EF8(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x23:                                      /* switch 1 */
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        func_L00_002B41B8(0.004916667f, 0.004916667f);
        func_00282C88((s32)(D_00189E20 + 0xF0));
        func_L00_002B94D8(0.004916667f);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32) (((void*)D_00189E20) + 0x120), 0.0061111115f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.015000001f);
        }
        var_v0_3_u2 = ((Hero *)D_00189E20)->ptr[0xAA4/4];
        if (var_v0_3_u2 != 0) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(M2C_FIELD(var_v0_3_u2, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(var_v0_3_u2, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            func_L00_002B3EF8(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(v0, (u8 *)((Hero *)D_00189E20)->ptr[0xAA4/4] + 0x10);
        temp_f0_4 = func_00282E48((s32) (((void*)D_00189E20) + 0x80), (s32)((TI128*)v0));
        ((Hero *)D_00189E20)->f[0xAB0/4] = temp_f0_4;
        ((Hero *)D_00189E20)->f[0xAAC/4] = 60.0f;
        if (((Hero *)D_00189E20)->f[0xAA0/4] > 0.0f) {
            ((Hero *)D_00189E20)->f[0xAAC/4] = (f32) (temp_f0_4 / ((Hero *)D_00189E20)->f[0x170/4]);
        }
        temp_v1_16 = ((Hero *)D_00189E20)->i[0x2298/4];
        if (temp_v1_16 == 0) {
            func_002AA2E8((s32) (((void*)D_00189E20) + 0xAA0), 0.45000002f, 0.022222223f);
            temp_v0_5 = ((Hero *)D_00189E20)->ptr[0xAA4/4];
            var_f20_2 = func_00283248(M2C_FIELD(temp_v0_5, f32* , 0x10) - M2C_FIELD(temp_fp, f32* , 0x10), M2C_FIELD(temp_v0_5, f32* , 0x14) - M2C_FIELD(temp_fp, f32* , 0x14));
            if (((Hero *)D_00189E20)->i[0x3A0/4] != 0) {
                if (func_00283C80(((Hero *)D_00189E20)->f[0x98/4], var_f20_2) > 1.5707964f) {
                    var_f20_2 = func_00283B98(var_f20_2, 3.1415927f);
                }
            }
            ((Hero *)D_00189E20)->f[0x1A0/4] = var_f20_2;
            func_L00_002B3EF8(0, 0.03f, 0.15f, 0.12217307f);
        } else if (temp_v1_16 == 1) {
            func_002AA2E8((s32) (((void*)D_00189E20) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((func_002A88A0((s32) &spE8, (s32) &spEC, -0.0058333334f, ((Hero *)D_00189E20)->f[0xAA0/4], 1.9f - ((Hero *)D_00189E20)->f[0xAB0/4]) > 0) && (spE8 > 0.0f)) {
            ((Hero *)D_00189E20)->f[0xAAC/4] = spE8;
            ((Hero *)D_00189E20)->i[0x2298/4] = 1;
        }
        ((Hero *)D_00189E20)->h[0x226/2] = 3;
        if (((Hero *)D_00189E20)->f[0xAAC/4] < 20.0f) {
            ((Hero *)D_00189E20)->i[0xAB4/4] = 1;
        }
        if (((Hero *)D_00189E20)->i[0xAB4/4] != 0) {
            func_002AA800((s32) (((void*)D_00189E20) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = func_00283B98(-func_00283248(func_00282E80((s32) (((void*)D_00189E20) + 0x80), (s32)((TI128*)v0)), v0[2] - ((Hero *)D_00189E20)->f[0x88/4]), 1.5707965f);
            func_002AA800((s32) (((void*)D_00189E20) + 0x94), 0, turn24, 0.10762865f);
        }
        v20[0] = func_00283180(func_00283B98(((Hero *)D_00189E20)->f[0x98/4], -1.5707965f)) * -0.57f;
        temp_f0_5 = func_00283198(func_00283B98(((Hero *)D_00189E20)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = temp_f0_5;
        func_00282CC0((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)D_00189E20) + 0x80));
        func_00282CF0((s32) ((TI128*)v10), (s32) (((Hero *)D_00189E20)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        func_00282F20((s32) (((void*)D_00189E20) + 0xF0), (s32) ((TI128*)v10), ((Hero *)D_00189E20)->f[0xAA0/4]);
        temp_f0_6 = ((Hero *)D_00189E20)->f[0xAAC/4];
        if (temp_f0_6 < 30.0f) {
            ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0xF8/4] - ((30.0f - temp_f0_6) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        func_002AA2E8((s32)(D_00189E20 + 0xABC), ((Hero *)D_00189E20)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)D_00189E20)->q[0xF0/16], &((Hero *)D_00189E20)->q[0x110/16]);
        func_00282D30((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.9f);
        ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0xF8/4] - 0.004166667f);
        qcopy(v0, (u8 *)((Hero *)D_00189E20)->ptr[0xAA4/4] + 0x10);
        ((Hero *)D_00189E20)->f[0xAB0/4] = func_00282E48((s32)(D_00189E20 + 0x80), (s32)((TI128*)v0));
        func_00282CC0((s32) ((TI128*)v10), (s32)(D_00189E20 + 0x80), (s32)(D_00189E20 + 0xF0));
        func_00282CF0((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32)((TI128*)v0));
        func_00282F20((s32) ((TI128*)v30), (s32) ((TI128*)v30), ((Hero *)D_00189E20)->f[0xABC/4]);
        func_00282CC0((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v30));
        func_00282CF0((s32)(D_00189E20 + 0xF0), (s32) ((TI128*)v20), (s32)(D_00189E20 + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)D_00189E20)->i[0xC28/4] & 2) && (M2C_FIELD(temp_fp, u8* , 0x43) == 0x34)) {
            func_L00_002D2168(0x35, 0xA, 12.0f);
            ((Hero *)D_00189E20)->f[0xC20/4] = 0.3f;
        }
        temp_v1_17 = ((Hero *)D_00189E20)->ptr[0xAD4/4];
        temp_f24 = ((Hero *)D_00189E20)->f[0xF8/4];
        if (temp_v1_17 != 0) {
            temp_v0_6 = M2C_FIELD(temp_v1_17, void** , 0x68);
            if ((temp_v0_6 != 0) && (M2C_FIELD(temp_v0_6, s32* , 0x34) != 0)) {
                var_f20_3 = M2C_FIELD(temp_v1_17, f32* , 0xF8);
                if (func_00283C80(var_f20_3, ((Hero *)D_00189E20)->f[0x98/4]) > 90.0f) {
                    var_f20_3 = func_00283B98(var_f20_3, 3.1415927f);
                }
                func_002AA898((s32) (((void*)D_00189E20) + 0xAEC), var_f20_3, (s32) (((void*)D_00189E20) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xAEC/4];
        func_L00_002B3EF8(0, 0.02f, 0.3f, 0.078539826f);
        func_00282CF0((s32)((TI128*)v0), (s32) (((Hero *)D_00189E20)->ptr[0xAD4/4] + 0x10), (s32) (((void*)D_00189E20) + 0x80));
        func_00282F20((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        func_00282C88((s32) ((TI128*)v60));
        v60[2] = ((Hero *)D_00189E20)->f[0x98/4];
        func_00283410((s32) ((TI128*)v20), (s32) ((TI128*)v60));
        func_00283698((s32) ((TI128*)m70), (s32) ((TI128*)v20));
        func_002830C0((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m70));
        v10[0] = -func_00283248(func_00282C10((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        temp_f0_7 = func_00283248(v0[2], v0[0]);
        v10[1] = temp_f0_7;
        func_002AA898((s32) (((void*)D_00189E20) + 0x94), temp_f0_7, (s32) (((void*)D_00189E20) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        func_002AA898((s32) (((void*)D_00189E20) + 0x90), v10[0], (s32) (((void*)D_00189E20) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        var_s7 = ((Hero *)D_00189E20)->f[0x88/4] < M2C_FIELD(((Hero *)D_00189E20)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)D_00189E20)->h[0xADC/2] != 0) {
            if ((var_s7 != 0) && (((Hero *)D_00189E20)->i[0x1B8/4] >= 0x29) && (((Hero *)D_00189E20)->f[0x24B8/4] > 0.25f)) {
                func_L00_002B39F0(1.0f, 0);
                var_f20_4 = ((Hero *)D_00189E20)->f[0x24B8/4] * 0.0035f;
                if (var_f20_4 > 0.083333336f) {
                    var_f20_4 = 0.083333336f;
                }
                vB0[0] = func_00283180(((Hero *)D_00189E20)->f[0x1A0/4]) * var_f20_4;
                temp_f0_8 = func_00283198(((Hero *)D_00189E20)->f[0x1A0/4]) * var_f20_4;
                temp_a0_10 = ((void*)D_00189E20) + 0xF0;
                (*(s32*)&vB0[2]) = 0;
                vB0[1] = temp_f0_8;
                func_00282CC0((s32) temp_a0_10, (s32) temp_a0_10, (s32) ((TI128*)vB0));
            }
            if (((Hero *)D_00189E20)->h[0xADC/2] != 0) {
                temp_s2_2 = ((void*)D_00189E20) + 0x80;
                if ((func_00282E80((s32) temp_s2_2, (s32) (((Hero *)D_00189E20)->ptr[0xAD4/4] + 0x10)) < (((Hero *)D_00189E20)->f[0xAE0/4] * 1.57f)) || (((Hero *)D_00189E20)->f[0x31C/4] > 1.5f)) {
                    temp_s1_2 = ((void*)D_00189E20) + 0xF0;
                    func_L00_002D34C0((s32) temp_s1_2, (s32) (((void*)D_00189E20) + 0x110), 0.011111111f);
                    if ((((Hero *)D_00189E20)->h[0xAFE/2] != 0) && (func_L00_002D3B00((s32) temp_s1_2) > 0.0f)) {
                        func_00282CF0((s32) ((TI128*)vB0), (s32) temp_s2_2, (s32) (((Hero *)D_00189E20)->ptr[0xAD4/4] + 0x10));
                        func_L00_002D34C0((s32) temp_s1_2, (s32) temp_s1_2, 0.015833333f);
                    }
                }
                temp_f20_3 = func_00282DF0((s32)(D_00189E20 + 0xF0)) * 0.00025f;
                func_00282D30((s32) ((TI128*)vB0), (s32)(D_00189E20 + 0xF0), -1.0f);
                func_00282F20((s32) ((TI128*)vB0), (s32) ((TI128*)vB0), temp_f20_3);
                func_00282CC0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), (s32) ((TI128*)vB0));
            }
        }
        temp_v0_7 = ((Hero *)D_00189E20)->ptr[0xAD4/4];
        if (temp_v0_7 != 0) {
            temp_s0 = M2C_FIELD(temp_v0_7, void** , 0x68);
            temp_s1_3 = ((void*)D_00189E20) + 0xF0;
            if (temp_s0 != 0) {
                temp_f0_9 = func_00282DF0((s32) temp_s1_3);
                temp_f12 = M2C_FIELD(temp_s0, f32* , 0xC);
                spF0 = temp_f0_9;
                if (temp_f12 < temp_f0_9) {
                    func_002AA2E8((s32) &spF0, temp_f12, 0.004166667f);
                    func_00282F20((s32) temp_s1_3, (s32) temp_s1_3, spF0);
                }
            }
        }
        temp_f0_10 = func_00283B98(((Hero *)D_00189E20)->f[0x98/4], -1.5707965f);
        temp_s5 = ((void*)D_00189E20) + 0x80;
        temp_s4_2 = ((void*)D_00189E20) + 0xF0;
        vD0[0] = func_00283180(temp_f0_10) * 0.15f;
        temp_f0_11 = func_00283198(temp_f0_10) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = temp_f0_11;
        func_00282CC0((s32) &vD0[0], (s32) &vD0[0], (s32) temp_s5);
        func_00282CC0((s32) ((TI128*)vB0), (s32) &vD0[0], (s32) temp_s4_2);
        func_00282CF0((s32) ((TI128*)vC0), (s32) ((TI128*)vB0), (s32) (((Hero *)D_00189E20)->ptr[0xAD4/4] + 0x10));
        func_00282F20((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)D_00189E20)->f[0xAE4/4]);
        func_00282CC0((s32) ((TI128*)vB0), (s32) (((Hero *)D_00189E20)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        func_00282CF0((s32) temp_s4_2, (s32) ((TI128*)vB0), (s32) &vD0[0]);
        temp_f20_4 = ((Hero *)D_00189E20)->f[0xAE4/4];
        func_002AA3A8((s32) (((void*)D_00189E20) + 0xAE4), (s32) (((void*)D_00189E20) + 0xAE8), ((Hero *)D_00189E20)->f[0xAE0/4], ((Hero *)D_00189E20)->f[0xB04/4], ((Hero *)D_00189E20)->f[0xB08/4], ((Hero *)D_00189E20)->f[0xB0C/4]);
        temp_f20_5 = ((Hero *)D_00189E20)->f[0xAE4/4] - temp_f20_4;
        if (((Hero *)D_00189E20)->f[0xAE4/4] < func_00282DF0((s32) ((TI128*)vC0))) {
            func_00282F20((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), temp_f20_5);
            func_00282CC0((s32) temp_s5, (s32) temp_s5, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)D_00189E20)->h[0xAFE/2] != 0) && (var_s7 != 0)) {
            min2B = 0.23333335f;
            temp_f0_12 = func_00282E20((s32) temp_s4_2);
            spF4 = temp_f0_12;
            if (temp_f0_12 < min2B) {
                func_002AA3A8((s32) &spF4, (s32) (((void*)D_00189E20) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vB0[0] = func_00283180(((Hero *)D_00189E20)->f[0xAEC/4]) * ((Hero *)D_00189E20)->f[0xAF4/4];
                temp_f0_13 = func_00283198(((Hero *)D_00189E20)->f[0xAEC/4]);
                vB0[2] = 0.0f;
                vB0[1] = temp_f0_13 * ((Hero *)D_00189E20)->f[0xAF4/4];
                func_00282CC0((s32) temp_s4_2, (s32) temp_s4_2, (s32) ((TI128*)vB0));
            }
        }
        if ((((Hero *)D_00189E20)->h[0xADC/2] != 0) && (((Hero *)D_00189E20)->h[0x34E/2] != 0) && (((temp_f24 < 0.0f) && (((Hero *)D_00189E20)->f[0xF8/4] > 0.0f)) || (((Hero *)D_00189E20)->h[0xAFC/2] != 0))) {
            ((Hero *)D_00189E20)->h[0xAFE/2] = 0;
            temp_f20_6 = func_00282C10(((Hero *)D_00189E20)->f[0xAE0/4] / ((Hero *)D_00189E20)->f[0xAF0/4]) * 3.1415927f;
            temp_v0_8 = ((Hero *)D_00189E20)->h[0xAFC/2];
            if (temp_v0_8 != 0) {
                var_v0_4 = temp_v0_8 == 1;
            } else {
                (*(TI128*)vB0) = ((Hero *)D_00189E20)->q[0x110/16];
                var_v0_4 = func_L00_002B5590((s32) ((TI128*)vB0)) > 0.0f;
            }
            if (var_v0_4 != 0) {
                if (M2C_FIELD(temp_fp, u8* , 0x43) != 0x35) {
                    func_L00_002D2168(0x35, 6, 17.0f);
                    ((Hero *)D_00189E20)->h[0xAFC/2] = 1;
                } else {
                    temp_v0_9 = ((Hero *)D_00189E20)->ptr[0x2290/4];
                    if (M2C_FIELD(temp_v0_9, u8* , 0x42) == M2C_FIELD(temp_v0_9, u8* , 0x43)) {
                        func_L00_002A9E30(42.0f, temp_f20_6, 0.5f, -1.0f);
                        ((Hero *)D_00189E20)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(temp_fp, u8* , 0x43) != 0x35) {
                func_L00_002D2168(0x35, 0x15, 9.0f);
                ((Hero *)D_00189E20)->h[0xAFC/2] = 2;
            } else {
                temp_v0_10 = ((Hero *)D_00189E20)->ptr[0x2290/4];
                if (M2C_FIELD(temp_v0_10, u8* , 0x42) == M2C_FIELD(temp_v0_10, u8* , 0x43)) {
                    func_L00_002A9E30(12.0f, temp_f20_6, 0.5f, -1.0f);
                    ((Hero *)D_00189E20)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)D_00189E20)->i[0xC2C/4] != 0) || (((Hero *)D_00189E20)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)D_00189E20)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)D_00189E20)->c[0x1239] = 2;
        }
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            temp_a1_3 = ((Hero *)D_00189E20)->i[0xBE4/4];
            if (temp_a1_3 != 0) {
                temp_f1_5 = func_00282E80((s32) (((void*)D_00189E20) + 0x80), temp_a1_3 + 0x10);
                var_v1_2 = 0;
                if ((((Hero *)D_00189E20)->b[0x1496] != 0) || (((Hero *)D_00189E20)->b[0x149B] != 0) || (((Hero *)D_00189E20)->b[0x1495] != 0)) {
                    var_v1_2 = 1;
                }
                if (((temp_f1_5 > 2.0f) && (temp_f1_5 < 5.0f)) || (var_v1_2 != 0)) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = 0.075f;
                }
                func_L00_002B41B8(0.0011111111f, 0.0011111111f);
                ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (func_00283180(((Hero *)D_00189E20)->f[0x98/4]) * ((Hero *)D_00189E20)->f[0x1B4/4]);
                ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (func_00283198(((Hero *)D_00189E20)->f[0x98/4]) * ((Hero *)D_00189E20)->f[0x1B4/4]);
            } else {
                func_L00_002B41B8(0.00055555557f, 0.00055555557f);
                temp_a0_11 = ((void*)D_00189E20) + 0xF0;
                func_L00_002D3BD8((s32) temp_a0_11, (s32) temp_a0_11, ((Hero *)D_00189E20)->f[0x1B4/4]);
            }
        } else {
            var_s1_2 = 0;
            if ((((Hero *)D_00189E20)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)D_00189E20)->b[0x149B] != 0) || (((Hero *)D_00189E20)->f[0x31C/4] > 4.0f)) {
                var_s1_2 = 1;
            }
            temp_a1_4 = ((Hero *)D_00189E20)->i[0xBE4/4];
            if (temp_a1_4 != 0) {
                func_00282CF0((s32)((TI128*)v0), temp_a1_4 + 0x10, (s32) (((void*)D_00189E20) + 0x80));
                temp_f0_14 = func_L00_002D3A58((s32)((TI128*)v0));
                if (((temp_f0_14 > 2.0f) && (temp_f0_14 < 5.0f)) || (var_s1_2 != 0)) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = 0.075f;
                }
                func_L00_002B41B8(0.0069444445f, 0.0069444445f);
                func_00282F20((s32) ((TI128*)v10), (s32)D_00189E20, ((Hero *)D_00189E20)->f[0x1B4/4]);
                func_L00_002D3BD8((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.0f);
                func_00282CC0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), (s32) ((TI128*)v10));
            } else {
                if ((var_s1_2 != 0) && (((Hero *)D_00189E20)->i[0x1B8/4] < 0x46)) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = 0.075f;
                }
                func_L00_002B41B8(0.004166667f, 0.004166667f);
                func_L00_002D3BD8((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), ((Hero *)D_00189E20)->f[0x1B4/4]);
            }
        }
        if ((((Hero *)D_00189E20)->i[0xBE8/4] != 0) || (((Hero *)D_00189E20)->i[0xBE4/4] != 0)) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = ((Hero *)D_00189E20)->f[0xBEC/4];
            qcopy(&((Hero *)D_00189E20)->q[0x190/16], &((Hero *)D_00189E20)->q[0xBC0/16]);
            func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)D_00189E20)->f[0xC38/4] < 25.0f) {
            func_L00_002B75A0(8.0f, 1.0471977f, 1.0471977f);
        }
        temp_f1_6 = ((Hero *)D_00189E20)->f[0x31C/4];
        var_f21 = 0.12833333f;
        if (temp_f1_6 > 2.25f) {
            var_f21 = 0.064166665f;
        } else if (temp_f1_6 > 1.8f) {
            var_f21 = 0.08983333f;
        }
        if ((((Hero *)D_00189E20)->i[0xC2C/4] == 0) && (((Hero *)D_00189E20)->f[0xC38/4] > 23.5f) && (((Hero *)D_00189E20)->f[0x118/4] < 0.0f) && (((Hero *)D_00189E20)->h[0x34E/2] != 0)) {
            qcopy(v0, &((Hero *)D_00189E20)->q[0x80/16]);
            func_L00_002D3778((s32)((TI128*)v0), (s32)((TI128*)v0), -0.5f);
            func_00282F20((s32) &v40[0], (s32)D_00189E20, 2.0f);
            func_002A8C00((s32) ((TI128*)v10), (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &v40[0]);
            v10[3] = 5627.925f;
            (*(u8*)((u8*)v20+9)) = 1;
            (*(u16*)((u8*)v20+10)) = 0x47;
            (*(u8*)((u8*)v20+8)) = 0;
            func_00277F48(0.4f, (s32)((TI128*)v0), 0x10, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], (s32) ((TI128*)v10));
        }
        if (func_L00_002B3998(25.7f) != 0) {
            func_L00_002D6900(0x19);
            ((Hero *)D_00189E20)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L20_001B9E80)->f[0x180/4] = 0.1f;
                ((Hero *)D_L20_001B9E80)->i[0x188/4] = 0x1E;
                ((Hero *)D_00189E20)->h[0x224/2] = 0x23;
                ((Hero *)D_L20_001B9E80)->i[0x16C/4] = 0;
            }
        }
        temp_v1_18 = ((Hero *)D_00189E20)->i[0x1B8/4];
        lim3 = 0xE;
        if (temp_v1_18 < 9) {
            temp_s0_2 = ((void*)D_00189E20) + 0xF0;
            spF8 = func_L00_002D3B00((s32) temp_s0_2);
            func_002AA2E8((s32) &spF8, var_f21, 0.041666668f);
            func_L00_002D3B58((s32) temp_s0_2, (s32) temp_s0_2, spF8);
        } else if (temp_v1_18 > lim3) {
            temp_s1_4 = ((void*)D_00189E20) + 0xF0;
            func_L00_002D34C0((s32) temp_s1_4, (s32) temp_s1_4, 0.036111113f);
            if (func_L00_002D3B00((s32) temp_s1_4) < 0.0f) {
                ((Hero *)D_00189E20)->f[0xC00/4] = 1.0f;
            }
            var_f20_5 = -0.6166667f;
            if (D_L20_001A8FF0 != 0) {
                var_f20_5 = -1.1666667f;
            }
            if (func_L00_002D3B00((s32) temp_s1_4) < var_f20_5) {
                func_L00_002D3B58((s32) temp_s1_4, (s32) temp_s1_4, var_f20_5);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)D_00189E20)->i[0xC2C/4] != 0) || (((Hero *)D_00189E20)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)D_00189E20)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)D_00189E20)->c[0x1239] = 2;
        }
        var_a0_8 = (((Hero *)D_00189E20)->i[0x22A0/4] == 1) && (((Hero *)D_00189E20)->i[0x22A8/4] >= 0x15);
        if (var_a0_8 == 0) {
            if ((((Hero *)D_00189E20)->i[0xBE8/4] != 0) || (((Hero *)D_00189E20)->i[0xBE4/4] != 0)) {
                var_s1_3 = 0;
                if (((Hero *)D_00189E20)->b[0x22C3] != 0) {
                    temp_s0_3 = ((void*)D_00189E20) + 0xBC0;
                    var_f20_6 = func_L00_002B9B38((s32) temp_s0_3, 0);
                    var_f0_3 = func_L00_002B9B38((s32) temp_s0_3, 1);
                } else {
                    var_f20_6 = func_00283BE0(((Hero *)D_00189E20)->f[0xBEC/4], ((Hero *)D_00189E20)->f[0x98/4]);
                    var_f0_3 = func_002AA738(1, ((Hero *)D_00189E20)->f[0xBEC/4], ((Hero *)D_00189E20)->f[0x98/4]);
                }
                if (var_f0_3 < 4.3633237f) {
                    var_s1_3 = 1;
                }
                if (var_f20_6 > 0.0f) {
                    ((Hero *)D_00189E20)->f[0xC20/4] = (f32) (1.0f / (var_f0_3 + 1.0f));
                }
                ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xBEC/4];
                qcopy(&((Hero *)D_00189E20)->q[0x190/16], &((Hero *)D_00189E20)->q[0xBC0/16]);
                if (var_s1_3 != 0) {
                    func_L00_002B3EF8(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    func_L00_002B3EF8(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    var_a0_9 = 1;
                    if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x83) && (((Hero *)D_00189E20)->i[0x1B8/4] >= 0xC)) {
                        var_a0_9 = 0;
                    } else if ((((Hero *)D_00189E20)->i[0xC2C/4] == 0) && (((Hero *)D_00189E20)->f[0xC38/4] > 6.0f)) {
                        var_a0_9 = 0;
                    }
                    if (var_a0_9 != 0) {
                        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x15) {
                            func_L00_002B75A0(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            func_L00_0041E958(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)D_00189E20)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (func_L00_002B3998(33.0f) != 0)) {
            if ((((Hero *)D_00189E20)->b[0x1492] != 0) && (((Hero *)D_00189E20)->f[0x170/4] < 0.033333335f)) {
                {
                    ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (((Hero *)D_00189E20)->f[0xF0/4] + (func_00283180(((Hero *)D_00189E20)->f[0x98/4]) * 0.021666666f));
                    ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (((Hero *)D_00189E20)->f[0xF4/4] + (func_00283198(((Hero *)D_00189E20)->f[0x98/4]) * 0.021666666f));
                    qcopy(&((Hero *)D_00189E20)->q[0x140/16], &((Hero *)D_00189E20)->q[0xF0/16]);
                }
            }
            if (((Hero *)D_00189E20)->u[0x2294/4] == 0x15) {
                func_L00_002BA508();
            }
        }
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            if (func_L00_002B3998(84.0f) != 0) {
                var_f21_2 = 0.041666668f;
                temp_f20_7 = func_00283B98(((Hero *)D_00189E20)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    var_f21_2 = 0.050000004f;
                }
                ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (((Hero *)D_00189E20)->f[0xF0/4] + (func_00283180(temp_f20_7) * var_f21_2));
                ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (((Hero *)D_00189E20)->f[0xF4/4] + (func_00283198(temp_f20_7) * var_f21_2));
                qcopy(&((Hero *)D_00189E20)->q[0x140/16], &((Hero *)D_00189E20)->q[0xF0/16]);
            }
            func_L00_002B9598();
        } else {
            func_L00_002B41B8(0.010277778f, 0.007777778f);
            func_L00_002B4208(99999.0f);
            if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
                func_L00_002D34C0((s32) (((void*)D_00189E20) + 0xF0), (s32) ((void*)D_00189E20) + 0x130, 0.0069444445f);
            } else {
                func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
                break;
            }
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)D_00189E20)->i[0xC2C/4] != 0) || (((Hero *)D_00189E20)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)D_00189E20)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)D_00189E20)->c[0x1239] = 2;
        }
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            func_L00_002B9598();
            break;
        }
        temp_a1_5 = ((Hero *)D_00189E20)->i[0xBE4/4];
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        temp_s2_3 = (((Hero *)D_00189E20)->h[0xBFC/2] * 0x2C) + (s32)D_L20_00268D90;
        if ((temp_a1_5 != 0) && (((Hero *)D_00189E20)->i[0x1B8/4] < 4)) {
            temp_s1_5 = ((void*)D_00189E20) + 0x80;
            var_f12_13 = func_00282E80(temp_a1_5 + 0x10, (s32) temp_s1_5);
            if ((*(s32*)&D_L20_001A8FF0) != 0) {
                var_f12_13 = func_00282E48(((Hero *)D_00189E20)->i[0xBE4/4] + 0x10, (s32) temp_s1_5);
            }
            var_f12_13 = var_f12_13 - 0.5f;
            if (var_f12_13 < 0.0f) {
                var_f12_13 = 0.0f;
            }
            temp_v1_20 = M2C_FIELD(temp_s2_3, s32* , 4);
            if (temp_v1_20 == 0) {
                var_f0_4 = 0.75f;
                var_f21_3 = 0.8f;
                var_f22 = 4.0f;
            } else if (temp_v1_20 == 1) {
                var_f0_4 = 0.6f;
                var_f21_3 = 1.7f;
                var_f22 = 4.0f;
            } else {
                var_f0_4 = 1.3f;
                var_f21_3 = 1.7f;
                var_f22 = 1.9f;
            }
            temp_f20_8 = var_f12_13 - var_f0_4;
            if (func_00282C48(temp_f20_8) < (var_f21_3 + 3.0f)) {
                var_f12_15 = temp_f20_8 * 1.1111112f;
                if (var_f22 < var_f12_15) {
                    var_f12_15 = var_f22;
                }
                if (var_f12_15 > 1.0f) {
                    ((Hero *)D_00189E20)->f[0xBF4/4] = var_f12_15;
                }
            }
        }
        temp_v1_21 = M2C_FIELD(temp_s2_3, s32* , 4);
        switch (temp_v1_21) {
        case 0:
            if (((Hero *)D_00189E20)->f[0xC38/4] < 18.0f) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = ((Hero *)D_00189E20)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            temp_f1_7 = ((Hero *)D_00189E20)->f[0xC38/4];
            if ((((Hero *)D_00189E20)->i[0xC2C/4] != 0) || (temp_f1_7 < 9.0f)) {
                if (temp_f1_7 > 8.0f) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = ((Hero *)D_00189E20)->f[0xBF4/4] * 0.050000004f;
                } else if (temp_f1_7 > 7.0f) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = ((Hero *)D_00189E20)->f[0xBF4/4] * 0.075f;
                } else {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = ((Hero *)D_00189E20)->f[0xBF4/4] * 0.095f;
                }
            }
            break;
        case 2:
            if ((((Hero *)D_00189E20)->i[0xC2C/4] != 0) || (((Hero *)D_00189E20)->f[0xC38/4] < 12.0f)) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = ((Hero *)D_00189E20)->f[0xBF4/4] * 0.06166667f;
            }
            break;
        }
        func_002AA2E8((s32)(D_00189E20 + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)D_00189E20)->i[0xBE8/4] != 0) || (((Hero *)D_00189E20)->i[0xBE4/4] != 0)) {
        if (((Hero *)D_00189E20)->b[0x22C3] != 0) {
            var_f0_5 = func_L00_002B9B38((s32)(D_00189E20 + 0xBC0), 0);
        } else {
            var_f0_5 = func_00283BE0(((Hero *)D_00189E20)->f[0xBEC/4], ((Hero *)D_00189E20)->f[0x98/4]);
        }
        temp_f1_8 = func_00282C48(var_f0_5);
        if ((M2C_FIELD(temp_s2_3, s32* , 4) == 1) && (var_f0_5 > 0.0f)) {
            ((Hero *)D_00189E20)->f[0xC20/4] = (f32) (1.0f / (temp_f1_8 + 1.0f));
        }
        ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xBEC/4];
        qcopy(&((Hero *)D_00189E20)->q[0x190/16], &((Hero *)D_00189E20)->q[0xBC0/16]);
        func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        var_v1_3 = 1;
        if ((M2C_FIELD(temp_s2_3, s32* , 4) == 1) && (((Hero *)D_00189E20)->i[0xC2C/4] == 0) && (((Hero *)D_00189E20)->f[0xC38/4] > 7.0f)) {
            var_v1_3 = 0;
        }
        if (var_v1_3 != 0) {
            func_L00_002B75A0(5.0f, 0.78539824f, 0.78539824f);
        }
    }
        func_L00_002B41B8(0.010277778f, 0.007777778f);
        if (((Hero *)D_00189E20)->i[0xBE8/4] != 0) {
            if (((Hero *)D_00189E20)->b[0x22C3] != 0) {
                func_L00_002B42D8((s32) (((void*)D_00189E20) + 0xBC0));
            } else {
                func_L00_002B4208(((Hero *)D_00189E20)->f[0xBEC/4]);
            }
        } else {
            func_L00_002B4208(99999.0f);
        }
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) (((void*)D_00189E20) + 0xF0), (s32) (((void*)D_00189E20) + 0x130), 0.0069444445f);
        } else {
            temp_a0_12 = ((void*)D_00189E20) + 0xF0;
            func_L00_002D34C0((s32) temp_a0_12, (s32) temp_a0_12, 0.015000001f);
        }
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        func_002AA2E8((s32)(D_00189E20 + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
            func_00282F20((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xBD0), ((Hero *)D_00189E20)->f[0x1B4/4]);
            if (((Hero *)D_00189E20)->f[0x31C/4] > 0.0f) {
                func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0x130), 0.0069444445f);
            } else {
                func_L00_002D3B58((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.0f);
            }
            func_00282D30((s32)(D_00189E20 + 0x190), (s32)(D_00189E20 + 0xBD0), -1.0f);
        } else {
            ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (func_00283180(((Hero *)D_00189E20)->f[0xBF0/4]) * ((Hero *)D_00189E20)->f[0x1B4/4]);
            ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (func_00283198(((Hero *)D_00189E20)->f[0xBF0/4]) * ((Hero *)D_00189E20)->f[0x1B4/4]);
            if (((Hero *)D_00189E20)->f[0x31C/4] > 0.0f) {
                ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0x128/4] - 0.0069444445f);
            } else {
                ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
            }
            ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283B98(((Hero *)D_00189E20)->f[0xBF0/4], 3.1415927f);
        }
        func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
        break;
    case 0x1F:                                      /* switch 1 */
        if ((((Hero *)D_00189E20)->i[0xBE8/4] != 0) || (((Hero *)D_00189E20)->i[0xBE4/4] != 0)) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = ((Hero *)D_00189E20)->f[0xBEC/4];
            func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)D_00189E20)->i[0x1B8/4] < 4) {
            func_L00_002B75A0(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0xA;
        lim2 = 0x12;
        temp_v1_22 = ((Hero *)D_00189E20)->i[0x1B8/4];
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        if (temp_v1_22 > lim) {
            if (temp_v1_22 < 0x12) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)D_00189E20)->i[0x1B8/4] == 8) && (((Hero *)D_00189E20)->f[0x184/4] < 0.33333334f)) {
            temp_s0_4 = ((void*)D_00189E20) + 0x18E0;
            func_L00_00322A98((s32) ((Hero *)D_00189E20)->ptr[0x2290/4], (s32) temp_s0_4);
            func_L00_00322AC0((s32) temp_s0_4, 0x30, 2, 0.0f);
            func_L00_00322AC0((s32) temp_s0_4, 0x17, 4, 0.0f);
            func_L00_00322AC0((s32) temp_s0_4, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)D_00189E20)->i[0x1B8/4] > lim2) ? 5 : 0;
        func_L00_00322BE0((s32) (((void*)D_00189E20) + 0x18E0), sel1F);
        if (((Hero *)D_00189E20)->b[0x1492] != 0) {
            temp_v1_23 = ((Hero *)D_00189E20)->i[0x1B8/4];
            if ((temp_v1_23 > lim) && (temp_v1_23 < 0x11) && (((Hero *)D_00189E20)->f[0x178/4] < 0.14166668f)) {
                ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (((Hero *)D_00189E20)->f[0xF0/4] + (func_00283180(((Hero *)D_00189E20)->f[0x98/4]) * 0.020000001f));
                ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (((Hero *)D_00189E20)->f[0xF4/4] + (func_00283198(((Hero *)D_00189E20)->f[0x98/4]) * 0.020000001f));
                qcopy(&((Hero *)D_00189E20)->q[0x140/16], &((Hero *)D_00189E20)->q[0xF0/16]);
            }
            func_L00_002B9598();
        } else {
            if (((Hero *)D_00189E20)->i[0x1B8/4] > lim) {
                func_L00_002B41B8(0.05277778f, 0.025f);
            }
            if (((Hero *)D_00189E20)->i[0xBE8/4] != 0) {
                func_L00_002B4208(((Hero *)D_00189E20)->f[0xBEC/4]);
            } else {
                func_L00_002B4208(99999.0f);
            }
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x1F) {
            temp_v1_24 = ((Hero *)D_00189E20)->i[0x1B8/4];
            if ((temp_v1_24 > lim) && (temp_v1_24 < 0x16)) {
                temp_s2_4 = ((Hero *)D_00189E20)->ptr[0x1220/4];
                if (temp_s2_4 != 0) {
                    temp_s1_6 = ((void*)D_00189E20) + 0x80;
                    v30[0] = 2.0f * func_00283180(((Hero *)D_00189E20)->f[0x98/4]);
                    v30[1] = 2.0f * func_00283198(((Hero *)D_00189E20)->f[0x98/4]);
                    v30[2] = 1.3f;
                    func_002A8C00((s32)((TI128*)v0), (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    temp_f22_2 = ((Hero *)D_00189E20)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(temp_s2_4, u16* , 0xAA);
                    v40[0] = func_00283180(temp_f22_2) * 0.8f;
                    temp_f0_15 = func_00283198(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_15;
                    func_00282CC0((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    func_L00_002BA138((s32) temp_s2_4, func_00277F48(0.8f, (s32) &v40[0], 0, (s32) temp_s2_4, (s32)((TI128*)v0)));
                    temp_f22_2 = func_00283B98(((Hero *)D_00189E20)->f[0x98/4], -0.8726647f);
                    v40[0] = func_00283180(temp_f22_2) * 0.8f;
                    temp_f0_17 = func_00283198(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_17;
                    func_00282CC0((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    func_L00_002BA138((s32) temp_s2_4, func_00277F48(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    temp_f22_2 = func_00283B98(((Hero *)D_00189E20)->f[0x98/4], 0.8726647f);
                    v40[0] = func_00283180(temp_f22_2) * 0.8f;
                    temp_f0_19 = func_00283198(temp_f22_2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = temp_f0_19;
                    func_00282CC0((s32) &v40[0], (s32) &v40[0], (s32) temp_s1_6);
                    func_L00_002BA138((s32) temp_s2_4, func_00277F48(0.8f, (s32) &v40[0], 0, (s32) temp_s2_4, (s32)((TI128*)v0)));
                }
            }
        }
        if (((Hero *)D_00189E20)->i[0x1B8/4] >= 0xB) {
            func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        }
        func_L00_002B4458(1);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x120, 0.0061111115f);
            func_L00_002B4308();
            break;
        }
        func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
        break;
    case 0x22:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        if (((Hero *)D_00189E20)->i[0xBE8/4] != 0) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xBEC/4];
            qcopy(&((Hero *)D_00189E20)->q[0x190/16], &((Hero *)D_00189E20)->q[0xBC0/16]);
            func_L00_002B3EF8(0, 0.04f, 0.2f, 0.2821616f);
        } else {
            func_L00_002B75A0(11.0f, 0.8726647f, -1.0f);
        }
        func_L00_002B41B8(0.008333334f, 0.009722223f);
        func_L00_002B4208(99999.0f);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x110, 0.015000001f);
            func_L00_002B4308();
            break;
        }
        func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
        break;
    case 0x2:                                       /* switch 1 */
    case 0x70:                                      /* switch 1 */
        var_a0_11 = 0;
        if ((((Hero *)D_00189E20)->b[0x1494] != 0) && (((Hero *)D_00189E20)->f[0x24C4/4] < 0.25f)) {
            var_a0_11 = 1;
        }
        if ((((Hero *)D_00189E20)->b[0x22B9] != 0) || (var_a0_11 != 0)) {
            if (((Hero *)D_00189E20)->f[0x174/4] > 0.016666668f) {
                func_L00_002AA570(0, 2);
            }
            if (((Hero *)D_00189E20)->f[0x174/4] > 0.008333334f) {
                func_L00_002AA750(2, 4);
            }
            func_L00_002AA938(5, 2, 0);
        }
        if (((Hero *)D_00189E20)->h[0x1454/2] == 0) {
            if (((Hero *)D_00189E20)->f[0x174/4] < 0.028333336f) {
                ((Hero *)D_00189E20)->b[0x40C] = 1U;
                if ((func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)D_00189E20)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)D_00189E20)->b[0x40F] = 1U;
                }
            }
            temp_f20_9 = func_L00_0032F038(1);
            if ((func_00283C80(temp_f20_9, func_L00_0032F038(7)) > 1.9198624f) && (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)D_00189E20)->f[0x24B8/4] == 1.0f)) {
                ((Hero *)D_00189E20)->b[0x40F] = 1U;
                ((Hero *)D_00189E20)->b[0x40C] = 1U;
            }
            if (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) < 0.087266475f) {
                ((Hero *)D_00189E20)->b[0x40C] = 0U;
            }
        }
        if ((((Hero *)D_00189E20)->b[0x40F] != 0) && (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) < 0.06981318f)) {
            ((Hero *)D_00189E20)->b[0x40F] = 0U;
        }
        if (((Hero *)D_00189E20)->f[0x24B8/4] < 0.2f) {
            if (((Hero *)D_00189E20)->i[0x410/4] != 0) {
                ((Hero *)D_00189E20)->b[0x40F] = 1U;
            }
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
            qcopy(&((Hero *)D_00189E20)->q[0x190/16], &((Hero *)D_00189E20)->q[0x3F0/16]);
            ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0x408/4];
        } else {
            func_L00_002B3D10();
            if ((func_L00_002ADEA0(0) == 0xA) && ((((Hero *)D_00189E20)->f[0x24BC/4] == 1.0f) || (((Hero *)D_00189E20)->i[0x410/4] != 0)) && (((Hero *)D_00189E20)->b[0x22BA] == 0)) {
                qcopy(&((Hero *)D_00189E20)->q[0x3F0/16], &((Hero *)D_00189E20)->q[0x190/16]);
                ((Hero *)D_00189E20)->i[0x410/4] = 1;
                ((Hero *)D_00189E20)->f[0x408/4] = ((Hero *)D_00189E20)->f[0x1A0/4];
            } else {
                qcopy(&((Hero *)D_00189E20)->q[0x3F0/16], &((Hero *)D_00189E20)->q[0x0/16]);
                ((Hero *)D_00189E20)->f[0x408/4] = ((Hero *)D_00189E20)->f[0x98/4];
            }
        }
        if (((Hero *)D_00189E20)->f[0xA70/4] > 0.0f) {
            pA60 = ((void*)D_00189E20) + 0xA60;
            func_L00_002B54F8(0.7f, 0.0f);
            (*(TI128*)v0) = ((Hero *)D_00189E20)->q[0xA60/16];
            temp_f1_9 = ((Hero *)D_00189E20)->f[0x1B0/4] + func_L00_002B5590((s32)((TI128*)v0));
            ((Hero *)D_00189E20)->f[0x1B0/4] = temp_f1_9;
            if (temp_f1_9 < 0.011666667f) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.011666667f;
            }
            func_00282C88((s32) pA60);
        }
        var_f20_7 = 1.0f;
        if (((Hero *)D_00189E20)->h[0x1454/2] != 0) {
            func_L00_002B35A0();
        } else {
            ((Hero *)D_00189E20)->f[0x1458/4] = (f32) ((Hero *)D_00189E20)->f[0x98/4];
            qcopy(&((Hero *)D_00189E20)->q[0x1440/16], &((Hero *)D_00189E20)->q[0x0/16]);
            if ((((Hero *)D_00189E20)->i[0x2298/4] == 1) && (((Hero *)D_00189E20)->b[0x40F] == 0) && (((Hero *)D_00189E20)->b[0x22BA] == 0)) {
                func_L00_002B3EF8(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                temp_f2_2 = func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]);
                if (((((Hero *)D_00189E20)->f[0x24B8/4] < 0.9f) || ((((Hero *)D_00189E20)->b[0x22BA] != 0) && (((Hero *)D_00189E20)->b[0x40F] == 0))) && (temp_f2_2 > 0.78539824f)) {
                    var_f20_7 = 0.0f;
                }
                func_L00_002B3F68();
            }
        }
        func_L00_002B7B80();
        func_L00_002B8CB8();
        if (((Hero *)D_00189E20)->b[0x40F] != 0) {
            var_f2_2 = 0.09916667f - (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) * 0.029178405f);
            if (var_f2_2 < 0.0f) {
                var_f2_2 = 0.0f;
            }
            if (var_f2_2 < ((Hero *)D_00189E20)->f[0x1B0/4]) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = var_f2_2;
            }
        }
        k005 = var_f20_7 * 0.005f;
        var_f20_8 = 0.0055555557f;
        if (((Hero *)D_00189E20)->b[0x40F] != 0) {
            var_f1_2 = 2.617994f - ((Hero *)D_00189E20)->f[0x1A8/4];
            if (var_f1_2 > 1.0f) {
                var_f1_2 = 1.0f;
            }
            if (var_f1_2 < 0.2f) {
                var_f1_2 = 0.2f;
            }
            var_f20_8 = 0.004722222f;
            ((Hero *)D_00189E20)->f[0x1B0/4] = (f32) (((Hero *)D_00189E20)->f[0x1B0/4] * var_f1_2);
        }
        temp_f2_3 = func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]);
        if ((((Hero *)D_00189E20)->f[0x24B8/4] < 0.75f) && (temp_f2_3 > 0.6108653f)) {
            var_f1_3 = 1.0f - (temp_f2_3 * 0.4f);
            if (var_f1_3 < 0.0f) {
                var_f1_3 = 0.0f;
            }
            ((Hero *)D_00189E20)->f[0x1B0/4] = (f32) (((Hero *)D_00189E20)->f[0x1B0/4] * var_f1_3);
        }
        func_L00_002B41B8(k005, var_f20_8);
        if ((((Hero *)D_00189E20)->b[0x40C] != 0) || (((Hero *)D_00189E20)->h[0x1454/2] != 0)) {
            if (((Hero *)D_00189E20)->b[0x22C3] == 0) {
                if (((Hero *)D_00189E20)->h[0x1454/2] != 0) {
                    func_L00_002B4208(((Hero *)D_00189E20)->f[0x1458/4]);
                } else {
                    func_L00_002B4208(((Hero *)D_00189E20)->f[0x1A0/4]);
                }
            } else if (((Hero *)D_00189E20)->h[0x1454/2] != 0) {
                func_L00_002B42D8((s32) (((void*)D_00189E20) + 0x1440));
            } else {
                func_L00_002B42D8((s32) (((void*)D_00189E20) + 0x190));
            }
        } else {
            func_L00_002B4208(99999.0f);
        }
        func_L00_002B4458(1);
        if (((Hero *)D_00189E20)->h[0x214/2] != 0) {
            func_L00_002B9F00(5.0f, 0.2f, 0.35f);
        }
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x130, 0.0069444445f);
            func_L00_002B4308();
            break;
        }
        func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
        break;
    case 0x7B:                                      /* switch 1 */
        func_L00_002B9BB0(4, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0xD);
        func_L00_002B39F0(1.0f, 0);
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.19166668f;
        func_L00_002A9D38((s32)((TI128*)v0), (s32) (((void*)D_00189E20) + 0x9F0), 0.17f);
        var_f21_4 = (((Hero *)D_00189E20)->f[0x24B8/4] * 0.020362178f) * v0[0];
        if ((*(s32*)&D_L20_001A8FF0) == 0) {
            if (((Hero *)D_00189E20)->i[0x1B8/4] < 0x3C) {
                var_f21_4 *= 0.1f;
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)D_00189E20)->f[0x24B8/4] > 0.2f) {
            func_L00_002B3DC0(0.0f, 0.0f, var_f21_4);
        }
        func_L00_002B41B8(0.027777778f, 0.004166667f);
        func_L00_002B4208(99999.0f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
            qcopy(v10, &((Hero *)D_00189E20)->q[0x2D0/16]);
            func_L00_002D3778((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            func_002AA458((s32) (((void*)D_00189E20) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)D_00189E20) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            func_002AA3A8((s32) (((void*)D_00189E20) + 0x88), (s32) (((void*)D_00189E20) + 0xA00), ((Hero *)D_00189E20)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        func_00282D30((s32) ((TI128*)v10), (s32)(D_00189E20 + 0x110), 3.0f);
        func_00282CC0((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(D_00189E20 + 0xE0));
        temp_v0_12 = func_00277F48(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0);
        if (temp_v0_12 != 0) {
            func_00282D30((s32) ((TI128*)v20), (s32)(D_00189E20 + 0x110), 7.0f);
            for (var_s0 = 0; var_s0 < temp_v0_12; var_s0++) {
                if (func_002ABB78(((s32 *)D_L20_001C4480)[var_s0]) != 0) {
                    func_002A8F70(((s32 *)D_L20_001C4480)[var_s0], (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x10000, (s32) (((void*)D_00189E20) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        func_L00_002AB0A8(0.017f, 0.3f);
        func_L00_002AB0D8(0.025f, 0.3f);
        func_L00_002AB0F0(0.03f, 0.27f);
        var_f2_3 = var_f21_4 * 27.0f;
        if (var_f2_3 > 1.7f) {
            var_f2_3 = 1.7f;
        } else if (var_f2_3 < -1.7f) {
            var_f2_3 = -1.7f;
        }
        temp_f0_20 = var_f2_3 * 0.5f;
        ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) -var_f2_3;
        ((Hero *)D_L20_00267210)->f[0x278/4] = temp_f0_20;
        ((Hero *)D_L20_00267210)->f[0x1C8/4] = temp_f0_20;
        break;
    case 0x2E:                                      /* switch 1 */
        func_L00_002B9598();
        func_L00_002AB0A8(0.04f, 0.2f);
        func_L00_002AB0C0(0.04f, 0.2f);
        func_L00_002AB0D8(0.04f, 0.2f);
        func_L00_002AB0F0(0.02f, 0.2f);
        temp_v1_25 = M2C_FIELD(temp_fp, u8* , 0x43);
        if (temp_v1_25 == 0x37) {
            var_f0_6 = 1.4f;
            var_f20_9 = ((Hero *)D_00189E20)->f[0x1A8/4];
            if ((var_f20_9 > 1.4f) || (var_f0_6 = -1.4f, (var_f20_9 < -1.4f))) {
                var_f20_9 = var_f0_6;
            }
            ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) (var_f20_9 * -0.14f);
            ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (var_f20_9 * 0.3f);
            ((Hero *)D_L20_00267210)->f[0x1C0/4] = (f32) (var_f20_9 * -0.22f);
            ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (var_f20_9 * 0.4f);
            ((Hero *)D_L20_00267210)->f[0x274/4] = (f32) (func_00282C48(var_f20_9) * -0.09f);
            ((Hero *)D_L20_00267210)->f[0x270/4] = (f32) (func_00282C48(var_f20_9) * 0.08f);
        } else if (temp_v1_25 == 0x66) {
            temp_f22_3 = func_00283B98(func_00283BE0(func_00283248(((Hero *)D_00189E20)->f[0x110/4], ((Hero *)D_00189E20)->f[0x114/4]), ((Hero *)D_00189E20)->f[0x98/4]), 3.1415927f);
            var_f21_5 = ((Hero *)D_00189E20)->f[0x174/4] * 6.9813175f;
            if (var_f21_5 > 0.43633235f) {
                var_f21_5 = 0.43633235f;
            }
            temp_f20_10 = func_00283180(temp_f22_3) * var_f21_5;
            temp_f0_21 = -func_00283198(temp_f22_3);
            ((Hero *)D_L20_00267210)->f[0x114/4] = temp_f20_10;
            ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (temp_f0_21 * var_f21_5);
        }
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            var_f12_16 = 0.0069444445f;
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32) (((void*)D_00189E20) + 0x110), var_f12_16);
        } else {
            ((Hero *)D_00189E20)->f[0xF8/4] = 0.0f;
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        temp_v1_26 = (*(s32*)&D_001A79F0);
        if (temp_v1_26 == 0 || (temp_v1_26 == 1 && ref_US2_L13_002C58E8_01 == 0)) {
            func_L00_002B9BB0(2, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x13);
        }
        var_v0_6 = D_001A79F0;
        if ((u32) var_v0_6 < 2U) {
            func_L00_002AA938(4, 2, 1);
        } else {
            func_L00_002AA938(4, 2, 0);
            v0[0] = ((Hero *)D_00189E20)->f[0x80/4] + func_002A7878(-0.25f, 0.25f);
            v0[1] = ((Hero *)D_00189E20)->f[0x84/4] + func_002A7878(-0.25f, 0.25f);
            v0[2] = ((Hero *)D_00189E20)->f[0x88/4] + func_002A7878(-0.1f, 0.4f);
            func_00282D30((s32) ((TI128*)v10), (s32) (((void*)D_00189E20) + 0x110), 0.9f);
            v10[0] += func_002A7878(-0.011666667f, 0.011666667f);
            v10[1] += func_002A7878(-0.011666667f, 0.011666667f);
            v10[2] = M2C_BITWISE(f32, v10[2]) + func_002A7878(0.016666668f, 0.033333335f);
            func_L00_00338D28((s32)((TI128*)v0), (s32) ((TI128*)v10), func_002A7878(37800.0f, 75600.0f));
        }
        ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xB40/4];
        temp_f20_11 = ((Hero *)D_00189E20)->f[0x98/4];
        func_L00_002B3EF8(0, 0.033f, 0.3f, 0.069813184f);
        var_f21_6 = func_00283C80(((Hero *)D_00189E20)->f[0x98/4], temp_f20_11);
        func_00282C88((s32) (((void*)D_00189E20) + 0xF0));
        func_L00_002B94D8(0.0019444445f);
        temp_f0_22 = ((Hero *)D_00189E20)->f[0x118/4] - 0.013888889f;
        ((Hero *)D_00189E20)->f[0xF8/4] = temp_f0_22;
        if (temp_f0_22 > -0.011111111f) {
            ((Hero *)D_00189E20)->f[0xF8/4] = -0.011111111f;
        }
        if (var_f21_6 > 0.023271061f) {
            var_f21_6 = 0.023271061f;
        }
        temp_f20_12 = var_f21_6 * 9.0f;
        func_002AA898((s32) (((void*)D_00189E20) + 0x90), temp_f20_12 * 0.5f, (s32) (((void*)D_00189E20) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        func_002AA898((s32) (((void*)D_00189E20) + 0x94), -((Hero *)D_00189E20)->f[0xB44/4], (s32) (((void*)D_00189E20) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        func_L00_002AB0C0(0.009f, 0.22f);
        func_L00_002AB0D8(0.04f, 0.2f);
        func_L00_002AB0F0(0.02f, 0.2f);
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (temp_f20_12 * 2.1f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (temp_f20_12 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        temp_v1_27 = ((Hero *)D_00189E20)->u[0x2294/4];
        if (((u32) (temp_v1_27 - 0x28) >= 2U) && (temp_v1_27 != 0x3E)) {
            func_L00_002B9BB0(0, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0);
        } else {
            temp_a2_2 = ((Hero *)D_00189E20)->i[0x242C/4];
            if (temp_a2_2 != -1) {
                temp_a0_13 = (temp_a2_2 * 0x70) + (s32)D_00188660;
                if (M2C_FIELD(temp_a0_13, s32* , 0x88) == ((Hero *)D_00189E20)->ptr[0x2290/4]) {
                    if (M2C_FIELD(temp_a0_13, u8* , 0x74) != 0) {
                        func_002E59F8(temp_a2_2);
                    }
                }
            }
            ((Hero *)D_00189E20)->i[0x242C/4] = -1;
        }
        temp_v1_28 = ((Hero *)D_00189E20)->u[0x2294/4];
        if ((temp_v1_28 == 0x27) || (temp_v1_28 == 0x2A)) {
            qcopy(v0, &((Hero *)D_00189E20)->q[0x80/16]);
            temp_f20_13 = func_00283B98(((Hero *)D_00189E20)->f[0x64C/4], func_002A78D8(0.0f, 0.52359885f));
            temp_f21_3 = func_002A7878(0.06666667f, 0.116666675f);
            v10[0] = func_00283180(temp_f20_13) * temp_f21_3;
            temp_f0_23 = func_00283198(temp_f20_13) * temp_f21_3;
            v10[2] = 0.0f;
            v10[1] = temp_f0_23;
            v10[2] = func_002A7878(0.050000004f, 0.083333336f);
            v10[3] = -0.008333334f;
            func_002BE278((s32)((TI128*)v0), (s32) ((TI128*)v10), 0, -1.0f);
        }
        temp_a1_6 = ((Hero *)D_00189E20)->ptr[0x1248/4];
        sp11C = 0;
        temp_s7 = (((LevelInfo *)D_L20_0026D970)[D_00139568[(s32)temp_a1_6]].x1C != 0);
        if ((s32)temp_a1_6 == 0xD) {
            temp_s7 = 0;
        }
        if (temp_s7 != 0) {
            sp11C = ((Hero *)D_00189E20)->b[0x22BA] != 0;
        }
        temp_s1_7 = ((void*)D_00189E20) + 0x80;
        func_L00_00341FA8(((Hero *)D_00189E20)->i[0x630/4], (s32) temp_s1_7, (s32) (((void*)D_00189E20) + 0x5D0), (s32) (((void*)D_00189E20) + 0x634), (s32) (((void*)D_00189E20) + 0x638), ((Hero *)D_00189E20)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)D_00189E20)->i[0x660/4] != 0) {
            func_L00_00341FA8(((Hero *)D_00189E20)->i[0x664/4], (s32) temp_s1_7, (s32) (((void*)D_00189E20) + 0x610), (s32) (((void*)D_00189E20) + 0x668), (s32) (((void*)D_00189E20) + 0x66C), ((Hero *)D_00189E20)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        var_a2 = 0;
        if (((Hero *)D_00189E20)->f[0x31C/4] > 1.0699999f) {
            temp_v1_29 = ((Hero *)D_00189E20)->u[0x2294/4];
            if ((temp_v1_29 != 0x28) && (temp_v1_29 != 0x3E) && (((Hero *)D_00189E20)->i[0x660/4] == 0)) {
                var_a2 = ((Hero *)D_00189E20)->i[0x1BC/4] >= 0x1F;
            }
        }
        if (var_a2 != 0) {
            ((Hero *)D_00189E20)->i[0x6C8/4] = (s32) (((Hero *)D_00189E20)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)D_00189E20)->i[0x6C8/4] = 0;
        }
        temp_v0_13 = ((Hero *)D_00189E20)->i[0x640/4];
        if (((temp_v0_13 != 0) && ((((Hero *)D_00189E20)->i[0x640/4] = temp_v0_13 + 1) != 0)) || (var_a2 != 0)) {
            qcopy(&((Hero *)D_00189E20)->q[0xF0/16], &((Hero *)D_00189E20)->q[0x120/16]);
            temp_v1_32 = ((void*)(D_00189E20 + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(temp_v1_32, s32* , 0x2294) - 0x28) < 2U) {
                func_L00_002B6560();
            } else {
                if (func_00282E20((s32)(D_00189E20 + 0xF0)) < 0.041666668f) {
                    func_002AA2E8((s32)(D_00189E20 + 0xF0) + 0xC4, 0.06666667f, 0.011111111f);
                    M2C_FIELD(temp_v1_32, f32* , 0xF0) = func_00283180(M2C_FIELD(temp_v1_32, f32* , 0x64C)) * M2C_FIELD(temp_v1_32, f32* , 0x1B4);
                    M2C_FIELD(temp_v1_32, f32* , 0xF4) = func_00283198(M2C_FIELD(temp_v1_32, f32* , 0x64C)) * M2C_FIELD(temp_v1_32, f32* , 0x1B4);
                }
                M2C_FIELD(temp_v1_32, f32* , 0xF8) = (f32) (M2C_FIELD(temp_v1_32, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            temp_f1_10 = (f32) ((Hero *)D_00189E20)->i[0x648/4];
            var_f20_10 = ((Hero *)D_00189E20)->f[0x644/4] * temp_f1_10;
            if (((Hero *)D_00189E20)->u[0x2294/4] == 0x3E) {
                var_f20_10 = ((Hero *)D_00189E20)->f[0x69C/4] * temp_f1_10;
            }
            func_L00_00341820(((Hero *)D_00189E20)->i[0x630/4], (s32)((TI128*)v0), (s32) (((void*)D_00189E20) + 0x634), (s32) (((void*)D_00189E20) + 0x638), ((Hero *)D_00189E20)->i[0x654/4], var_f20_10);
            if (((Hero *)D_00189E20)->i[0x660/4] != 0) {
                func_L00_00341820(((Hero *)D_00189E20)->i[0x664/4], (s32) ((TI128*)v10), (s32) (((void*)D_00189E20) + 0x668), (s32) (((void*)D_00189E20) + 0x66C), ((Hero *)D_00189E20)->i[0x670/4], var_f20_10);
            }
            if (((Hero *)D_00189E20)->i[0x1BC/4] >= 0x5B) {
                temp_f20_14 = ((Hero *)D_00189E20)->f[0x170/4] * 30.0f;
                qcopy(v20, &((Hero *)D_00189E20)->q[0x80/16]);
                spFC = ((Hero *)D_00189E20)->i[0x634/4];
                sp100 = ((Hero *)D_00189E20)->f[0x638/4];
                temp_s0_5 = func_L00_00341820(((Hero *)D_00189E20)->i[0x630/4], (s32) ((TI128*)v20), (s32) &spFC, (s32) &sp100, ((Hero *)D_00189E20)->i[0x654/4], temp_f20_14);
                qcopy(v30, &((Hero *)D_00189E20)->q[0x80/16]);
                spFC = ((Hero *)D_00189E20)->i[0x634/4];
                sp100 = ((Hero *)D_00189E20)->f[0x638/4];
                if ((((temp_s0_5 | func_L00_00341820(((Hero *)D_00189E20)->i[0x630/4], (s32) ((TI128*)v30), (s32) &spFC, (s32) &sp100, ((Hero *)D_00189E20)->i[0x654/4], temp_f20_14 + 0.1f)) == 0) || (((Hero *)D_00189E20)->i[0x654/4] != 0)) && (((Hero *)D_00189E20)->u[0x2294/4] == 0x27)) {
                    var_f20_11 = func_00283BE0(((Hero *)D_00189E20)->f[0x64C/4], func_00283248(v30[0] - v20[0], v30[1] - v20[1])) * 0.47f;
                    if (var_f20_11 > 0.78539824f) {
                        var_f20_11 = 0.78539824f;
                    }
                    if (var_f20_11 < -0.78539824f) {
                        var_f20_11 = -0.78539824f;
                    }
                    func_L00_002AB0A8(0.03f, 0.2f);
                    if (((Hero *)D_00189E20)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L20_00267274) = -var_f20_11;
                    } else {
                        (*(f32*)&D_L20_00267274) = var_f20_11;
                    }
                }
            }
            temp_v1_30 = ((Hero *)D_00189E20)->u[0x2294/4];
            if ((temp_v1_30 != 0x28) && (temp_v1_30 != 0x3E) && (temp_v1_30 != 0x29)) {
                (*(f32*)&D_L20_00267270) = func_00283248(func_00282E20((s32) (((void*)D_00189E20) + 0x110)), ((Hero *)D_00189E20)->f[0x118/4]);
            }
            if (temp_s7 != 0) {
                k03 = 0.3f;
                func_L00_002AB0F0(0.017f, k03);
                func_L00_002AB0C0(0.027f, k03);
                func_L00_002AB0D8(0.027f, k03);
                temp_a1_7 = ((Hero *)D_00189E20)->i[0x6A8/4];
                if (temp_a1_7 != 0) {
                    func_00282CF0((s32) ((TI128*)v20), temp_a1_7 + 0x10, (s32) (((void*)D_00189E20) + 0x80));
                    func_00283098((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)D_00189E20) + 0x40));
                    temp_f12_2 = func_00283248(v20[0], v20[1]);
                    if (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        temp_f12_2 = func_00283BE0(temp_f12_2, 1.5707965f);
                        var_f1_4 = 0.2f;
                    } else {
                        temp_f12_2 = func_00283BE0(temp_f12_2, -1.5707965f);
                        var_f1_4 = 0.5f;
                    }
                    ((Hero *)D_L20_00267210)->f[0x1C8/4] = (f32) (temp_f12_2 * var_f1_4);
                    ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (temp_f12_2 * k03);
                } else {
                    temp_a0_14 = M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43);
                    if (temp_a0_14 == 0x31) {
                        var_f21_7 = 0.58823526f;
                        var_f0_8 = func_00283B98(-0.8203048f, ((Hero *)D_00189E20)->f[0x6A0/4]);
                        var_f20_12 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = var_f0_8;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                    } else if (temp_a0_14 == 0x48) {
                        var_f21_7 = 0.5f;
                        var_f0_8 = func_00283B98(0.13962635f, ((Hero *)D_00189E20)->f[0x6A0/4]);
                        var_f20_12 = -0.06981318f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = var_f0_8;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                    } else if (temp_a0_14 == 0x47) {
                        var_f21_7 = 0.58823526f;
                        var_f0_8 = func_00283B98(-0.8203048f, ((Hero *)D_00189E20)->f[0x6A0/4]);
                        var_f20_12 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = var_f0_8;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = func_00283B98(var_f20_12, ((Hero *)D_00189E20)->f[0x6A0/4] * var_f21_7);
                    }
                }
            }
            temp_v0_15 = func_L00_003417B8(((Hero *)D_00189E20)->i[0x630/4], ((Hero *)D_00189E20)->i[0x634/4], ((Hero *)D_00189E20)->i[0x648/4], ((Hero *)D_00189E20)->i[0x654/4]);
            func_00282CF0((s32) ((TI128*)v20), (s32) &((TI128 *)((Hero *)D_00189E20)->ptr[0x630/4])[temp_v0_15 + 1], (s32)((TI128*)v0));
            if (func_00282DF0((s32) ((TI128*)v20)) < 0.001f) {
                if (((Hero *)D_00189E20)->i[0x634/4] == temp_v0_15) {
                    ((Hero *)D_00189E20)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)D_00189E20)->f[0x64C/4] = func_00283248(v20[0], v20[1]);
                ((Hero *)D_00189E20)->f[0x650/4] = func_00283248(func_00282E20((s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]));
block_807:
                ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283B98(((Hero *)D_00189E20)->f[0x64C/4], ((Hero *)D_00189E20)->f[0x658/4]);
                func_L00_002B3EF8(0, 0.015f, 0.15f, 0.10471977f);
                temp_v1_31 = ((Hero *)D_00189E20)->u[0x2294/4];
                if ((((u32) (temp_v1_31 - 0x28) < 2U) && (((Hero *)D_00189E20)->b[0x49C] == 0)) || (temp_v1_31 == 0x3E)) {
                    if (((Hero *)D_00189E20)->i[0x694/4] != 0) {
                        temp_f0_27 = func_00283248(((Hero *)D_00189E20)->f[0x620/4] - ((Hero *)D_00189E20)->f[0x80/4], ((Hero *)D_00189E20)->f[0x624/4] - ((Hero *)D_00189E20)->f[0x84/4]);
                        if (func_00283C80(((Hero *)D_00189E20)->f[0x98/4], temp_f0_27) < 1.5707965f) {
                            ((Hero *)D_00189E20)->f[0x1A0/4] = temp_f0_27;
                            func_L00_002B3EF8(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)D_00189E20)->i[0x660/4] != 0) && (((Hero *)D_00189E20)->i[0x678/4] < 0x31)) {
                        func_00282CF0((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        temp_v0_16 = ((Hero *)D_00189E20)->i[0x678/4] + 1;
                        ((Hero *)D_00189E20)->i[0x678/4] = temp_v0_16;
                        func_00282D30((s32) ((TI128*)v20), (s32) ((TI128*)v20), (f32) temp_v0_16 * 0.020833334f);
                        temp_f20_15 = (f32) (((Hero *)D_00189E20)->i[0x678/4] - 1) * 0.020833334f;
                        func_00282CF0((s32) ((TI128*)v30), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        func_00282D30((s32) ((TI128*)v30), (s32) ((TI128*)v30), temp_f20_15);
                        ((Hero *)D_00189E20)->f[0x88/4] = (f32) (((Hero *)D_00189E20)->f[0x88/4] + (M2C_BITWISE(f32, v20[2]) - v30[2]));
                        func_00282CC0((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                        func_00282CF0((s32) ((TI128*)v20), (s32) ((TI128*)v30), (s32) (((void*)D_00189E20) + 0x80));
                        ((Hero *)D_00189E20)->f[0xF0/4] = v20[0];
                        ((Hero *)D_00189E20)->f[0xF4/4] = v20[1];
                        func_00282CF0((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) (((void*)D_00189E20) + 0x5D0));
                        temp_f2_5 = ((Hero *)D_00189E20)->f[0x5D8/4];
                        temp_f1_11 = ((Hero *)D_00189E20)->f[0x88/4] + M2C_BITWISE(f32, v20[2]);
                        ((Hero *)D_00189E20)->f[0x88/4] = temp_f1_11;
                        if (temp_f1_11 < temp_f2_5) {
                            if (((Hero *)D_00189E20)->i[0x678/4] < 0x31) {
                                if (temp_f1_11 < temp_f2_5) {
                                    ((Hero *)D_00189E20)->f[0x88/4] = temp_f2_5;
                                }
                            }
                        }
                    } else {
                        func_00282CF0((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32)(D_00189E20 + 0x5D0));
                        ((Hero *)D_00189E20)->f[0xF0/4] = v20[0];
                        ((Hero *)D_00189E20)->f[0xF4/4] = v20[1];
                        ((Hero *)D_00189E20)->f[0x88/4] = (f32) (((Hero *)D_00189E20)->f[0x88/4] + M2C_BITWISE(f32, v20[2]));
                        func_00282CF0((s32) ((TI128*)v30), (s32)(D_00189E20 + 0x5D0), (s32)(D_00189E20 + 0x80));
                        v30[2] = 0.0f;
                        if (func_00282DF0((s32) ((TI128*)v30)) > 0.016666668f) {
                            func_00282F20((s32) ((TI128*)v30), (s32) ((TI128*)v30), 0.016666668f);
                        }
                        ((Hero *)D_00189E20)->f[0x80/4] = (f32) (((Hero *)D_00189E20)->f[0x80/4] + v30[0]);
                        ((Hero *)D_00189E20)->f[0x84/4] = (f32) (((Hero *)D_00189E20)->f[0x84/4] + v30[1]);
                    }
                    if (((Hero *)D_00189E20)->u[0x2294/4] == 0x3E) {
                        ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0xF8/4] - 0.006388889f);
                    } else {
                        func_L00_002B6560();
                    }
                } else {
                    ((Hero *)D_00189E20)->i[0x660/4] = 0;
                    var_f0_9 = 0.0f;
                    if ((((Hero *)D_00189E20)->f[0x24B8/4] > 0.2f) && (sp11C != 0)) {
                        func_L00_002B39F0(1.0f, 0);
                        var_f0_9 = func_00283BE0(((Hero *)D_00189E20)->f[0x1A0/4], ((Hero *)D_00189E20)->f[0x64C/4]);
                        if (var_f0_9 > 0.78539824f) {
                            var_f0_9 = 0.78539824f;
                        } else if (var_f0_9 < -0.78539824f) {
                            var_f0_9 = -0.78539824f;
                        }
                    }
                    func_002AA898((s32)(D_00189E20 + 0x6A0), var_f0_9, (s32)(D_00189E20 + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    func_002AA2E8((s32)(D_00189E20 + 0x680), 0.20000002f, 0.004166667f);
                    sp104 = ((Hero *)D_00189E20)->i[0x634/4];
                    sp108 = ((Hero *)D_00189E20)->f[0x638/4];
                    qcopy(v20, &((Hero *)D_00189E20)->q[0x80/16]);
                    func_L00_00341820(((Hero *)D_00189E20)->i[0x630/4], (s32) ((TI128*)v20), (s32) &sp104, (s32) &sp108, ((Hero *)D_00189E20)->i[0x654/4], 0.3f);
                    temp_f0_24 = func_00283248(func_00282E80((s32)(D_00189E20 + 0x5D0), (s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]) - ((Hero *)D_00189E20)->f[0x5D8/4]);
                    if (temp_f0_24 > 0.0f) {
                        var_f12_17 = temp_f0_24 * -0.07957746f;
                        if (temp_f0_24 > 0.26179942f) {
                            ((Hero *)D_00189E20)->i[0x67C/4] = 0;
                        } else if ((temp_f0_24 < 0.13962635f) && (((Hero *)D_00189E20)->i[0x67C/4] == 0)) {
                            ((Hero *)D_00189E20)->i[0x67C/4] = -1;
                        }
                    } else {
                        var_f12_17 = -temp_f0_24 * 0.38197184f;
                        if (temp_f0_24 < -0.19198623f) {
                            ((Hero *)D_00189E20)->i[0x67C/4] = 1;
                        } else if ((temp_f0_24 > -0.122173056f) && (((Hero *)D_00189E20)->i[0x67C/4] == 1)) {
                            ((Hero *)D_00189E20)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)D_00189E20)->f[0x674/4] < var_f12_17) {
                        func_002AA2E8((s32) (((void*)D_00189E20) + 0x674), var_f12_17, 0.0022222223f);
                    } else {
                        func_002AA2E8((s32) (((void*)D_00189E20) + 0x674), var_f12_17, 0.00055555557f);
                    }
                    if (((Hero *)D_00189E20)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)D_00189E20)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)D_00189E20)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)D_00189E20)->f[0x674/4] = -0.041666668f;
                    }
                    temp_f0_25 = ((Hero *)D_00189E20)->f[0x680/4] + ((Hero *)D_00189E20)->f[0x674/4];
                    ((Hero *)D_00189E20)->f[0x644/4] = temp_f0_25;
                    if (temp_f0_25 < 0.0f) {
                        ((Hero *)D_00189E20)->f[0x644/4] = 0.0f;
                    }
                    temp_s0_6 = ((void*)D_00189E20) + 0x5D0;
                    func_00282CF0((s32) (((void*)D_00189E20) + 0xF0), (s32)((TI128*)v0), (s32) temp_s0_6);
                    temp_s2_5 = ((void*)D_00189E20) + 0x80;
                    func_00282CF0((s32) ((TI128*)v20), (s32) temp_s0_6, (s32) temp_s2_5);
                    sp10C = -func_00282DF0((s32) ((TI128*)v20));
                    func_002AA3A8((s32) &sp10C, (s32) (((void*)D_00189E20) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    temp_f0_26 = func_00282DF0((s32) ((TI128*)v20));
                    if (temp_f0_26 < ((Hero *)D_00189E20)->f[0x6AC/4]) {
                        ((Hero *)D_00189E20)->f[0x6AC/4] = temp_f0_26;
                    }
                    temp_f12_3 = ((Hero *)D_00189E20)->f[0x6AC/4];
                    if (temp_f12_3 < temp_f0_26) {
                        func_00282F20((s32) ((TI128*)v20), (s32) ((TI128*)v20), temp_f12_3);
                    }
                    func_00282CC0((s32) temp_s2_5, (s32) temp_s2_5, (s32) ((TI128*)v20));
                    temp_f3 = ((Hero *)D_00189E20)->f[0x88/4];
                    temp_f2_4 = ((Hero *)D_00189E20)->f[0x5D8/4];
                    if (temp_f3 < temp_f2_4) {
                        if (((Hero *)D_00189E20)->f[0x31C/4] < 1.0f) {
                            if (temp_f3 < temp_f2_4) {
                                ((Hero *)D_00189E20)->f[0x88/4] = temp_f2_4;
                            }
                        }
                    }
                }
                if (((Hero *)D_00189E20)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)D_00189E20)->i[0x1B8/4] < 0x14) {
                        temp_f0_28 = func_00283B98(((Hero *)D_00189E20)->f[0x64C/4], func_002A78D8(0.3490659f, 0.6108653f));
                        v50[0] = func_00283180(temp_f0_28);
                        v50[1] = func_00283198(temp_f0_28);
                        v50[2] = 0.0f;
                        func_002A8C00((s32) ((TI128*)v20), (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &v50[0]);
                        qcopy(v60, &((Hero *)D_00189E20)->q[0x80/16]);
                        v60[2] += 0.6f;
                        func_00277F48(1.0f, (s32) ((TI128*)v60), 0x10, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], (s32) ((TI128*)v20));
                    }
                }
            }
        }
        break;
    case 0x17:                                      /* switch 1 */
    case 0x18:                                      /* switch 1 */
        func_00282CF0((s32)(D_00189E20 + 0x190), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(((Hero *)D_00189E20)->f[0x190/4], ((Hero *)D_00189E20)->f[0x194/4]);
        func_L00_002B3EF8(0, 0.04f, 0.2f, 0.10471977f);
        if (((Hero *)D_00189E20)->b[0x22C3] != 2) {
            func_002AA800((s32)(D_00189E20 + 0x94), 0, 0.0f, 0.078539826f);
        }
        func_00282CF0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0x550), (s32)(D_00189E20 + 0x80));
        func_002AC9F8((s32)(D_00189E20 + 0xF0), 0.06666667f);
        func_002AA2E8((s32)(D_00189E20 + 0x580), ((Hero *)D_00189E20)->f[0x88/4], 0.050000004f);
        break;
    case 0x46:                                      /* switch 1 */
    case 0x47:                                      /* switch 1 */
        func_00282CF0((s32)(D_00189E20 + 0x190), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(((Hero *)D_00189E20)->f[0x190/4], ((Hero *)D_00189E20)->f[0x194/4]);
        func_L00_002B3EF8(0, 0.02f, 0.2f, 0.078539826f);
        func_00282CF0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0x550), (s32)(D_00189E20 + 0x80));
        func_002AC9F8((s32)(D_00189E20 + 0xF0), 0.028333336f);
        func_002AA2E8((s32)(D_00189E20 + 0x580), ((Hero *)D_00189E20)->f[0x88/4], 0.050000004f);
        break;
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        func_00282CF0((s32)(D_00189E20 + 0x190), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(((Hero *)D_00189E20)->f[0x190/4], ((Hero *)D_00189E20)->f[0x194/4]);
        func_L00_002B3EF8(0, 0.02f, 0.2f, 0.078539826f);
        func_00282CF0((s32) ((TI128*)v60), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        func_00282C88((s32)(D_00189E20 + 0xF0));
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x19) {
            func_00282DD8((s32) &v40[0], (s32)(D_00189E20 + 0x2C0), (s32) ((TI128*)v60));
        } else {
            func_00282DD8((s32) &v40[0], (s32) ((TI128*)v60), (s32)(D_00189E20 + 0x2C0));
        }
        func_00282F20((s32) &v40[0], (s32) &v40[0], 0.2f);
        func_00282CC0((s32) &v50[0], (s32)(D_00189E20 + 0x80), (s32) &v40[0]);
        if ((func_L00_002ACF88((s32)(D_00189E20 + 0x80), (s32)(D_00189E20 + 0x90), 0) != 0) && (func_L00_002ACF88((s32) &v50[0], (s32)(D_00189E20 + 0x90), (s32)((TI128*)v0)) != 0)) {
            func_00282CF0((s32)(D_00189E20 + 0xF0), (s32)((TI128*)v0), (s32)(D_00189E20 + 0x80));
            var_v0_8 = func_00283CF0(((Hero *)D_00189E20)->f[0xC38/4]) * 4;
            var_v1_4 = (s32)D_L20_001ACEE8;
            func_00282F20((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), *(f32*)(var_v0_8 + var_v1_4) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0x1A0/4] = ((Hero *)D_00189E20)->f[0x32C/4];
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.09166667f;
        func_L00_002B6198(0.0069444445f);
        func_L00_002D34C0((s32) (((void*)D_00189E20) + 0xF0), (s32) ((void*)D_00189E20) + 0x130, 0.005f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x2C) {
            var_f12_18 = 0.0f;
            if (((Hero *)D_00189E20)->f[0x31C/4] > 4.0f) {
                var_f12_18 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)D_00189E20)->q[0x90/16]);
            func_002AA898((s32) &v0[1], var_f12_18, (s32) (((void*)D_00189E20) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            func_002AA898((s32)((TI128*)v0), 0.0f, (s32) (((void*)D_00189E20) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            func_L00_002AA0F0(((Hero *)D_00189E20)->f[0xA0/4], ((Hero *)D_00189E20)->f[0xA4/4], 0.0f);
            if (((Hero *)D_00189E20)->f[0x31C/4] > 1.0f) {
                ((Hero *)D_00189E20)->i[0x2298/4] = 1;
            }
        }
        func_L00_002B3D10();
        if (((Hero *)D_00189E20)->h[0x1E0/2] == 0) {
            func_L00_002B6BC8();
        }
        var_s1_5 = ((void*)D_00189E20) + 0xF0;
        func_L00_002B7B80();
        func_L00_002B54F8(0.7f, 0.0f);
        func_L00_002D34C0((s32) var_s1_5, (s32) var_s1_5, ((Hero *)D_00189E20)->f[0xA80/4]);
        if (func_L00_002D3B00((s32) var_s1_5) < -0.8333334f) {
            func_L00_002D3B58((s32) var_s1_5, (s32) var_s1_5, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)D_00189E20)->c[0x22BC] = 1;
        var_s1_5_u2 = ((void*)D_00189E20) + 0xF0;
        func_002AA2E8((s32) (((void*)D_00189E20) + 0xA88), ((Hero *)D_00189E20)->f[0xA90/4], 0.0024240687f);
        func_002AA2E8((s32) (((void*)D_00189E20) + 0xA8C), ((Hero *)D_00189E20)->f[0xA94/4], 0.0024240687f);
        func_L00_002AA0F0(((Hero *)D_00189E20)->f[0xA88/4], ((Hero *)D_00189E20)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) var_s1_5_u2, (s32) var_s1_5_u2, func_00282E20((s32) var_s1_5_u2) * 0.9f);
        func_L00_002D34C0((s32) var_s1_5_u2, (s32) var_s1_5_u2, ((Hero *)D_00189E20)->f[0xA80/4]);
        if (func_L00_002D3B00((s32) var_s1_5_u2) < -0.8333334f) {
            func_L00_002D3B58((s32) var_s1_5_u2, (s32) var_s1_5_u2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        func_L00_002B9BB0(4, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0xD);
        ang82 = (f32) func_L00_0031D620(0x2D0, 0xB4, ((Hero *)D_00189E20)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        func_00290010(2, func_L00_00325FC8((s32) (((void*)D_00189E20) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)D_00189E20)->f[0x5B0/4] * 0.02f));
        var_a0_12 = (s32) ((Hero *)D_00138180)->d[0x1A0/8] & 0x40;
        if (((Hero *)D_00189E20)->f[0x5B0/4] == 0.0f) {
            var_a0_12 = 0;
        }
        if (var_a0_12 != 0) {
            func_002AA2E8((s32) (((void*)D_00189E20) + 0x5B0), 0.0f, 0.1f);
            temp_a0_15 = ((void*)D_00189E20) + 0xF0;
            func_L00_002D38A0((s32) temp_a0_15, (s32) temp_a0_15, 0.025f);
        } else {
            func_002AA2E8((s32) (((void*)D_00189E20) + 0x5B0), 0.0f, 0.02f);
        }
        if (((Hero *)D_00138180)->i[0x1A4/4] & 0x40) {
            func_002AA2E8((s32)(D_00189E20 + 0x5B0), 0.0f, 0.5f);
        }
        func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.0075000003f);
        if (func_L00_002D3B00((s32)(D_00189E20 + 0xF0)) > 0.10000001f) {
            func_L00_002D3B58((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.10000001f);
        }
        if (func_L00_002D3B00((s32)(D_00189E20 + 0xF0)) < -0.20000002f) {
            func_L00_002D3B58((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), -0.20000002f);
        }
        temp_f12_4 = func_L00_002D3B00((s32)(D_00189E20 + 0xF0));
        if ((((Hero *)D_00189E20)->f[0x5B0/4] > 25.0f) && (((Hero *)D_00189E20)->h[0x5BE/2] < 0x5A) && (temp_f12_4 < 0.0f) && (temp_f2_6 = ((Hero *)D_00189E20)->f[0x31C/4], (temp_f2_6 < 1.2f))) {
            var_f0_10 = (temp_f2_6 - 0.25f) * 1.0526315f;
            ((Hero *)D_00189E20)->h[0x5BE/2] = (s16) ((u16) ((Hero *)D_00189E20)->h[0x5BE/2] + 1);
            if (var_f0_10 < 0.0f) {
                var_f0_10 = 0.0f;
            }
            func_L00_002D3B58((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), temp_f12_4 * var_f0_10);
            if (((Hero *)D_00189E20)->f[0x31C/4] < 0.25f) {
                func_002AA3A8((s32)(D_00189E20 + 0x88), (s32)(D_00189E20 + 0x5B4), ((Hero *)D_00189E20)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (temp_f12_4 > 0.0f) {
            ((Hero *)D_00189E20)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L20_001BA248) = func_L00_002D3B00((s32)(D_00189E20 + 0xF0));
        func_L00_002B7B80();
        func_L00_002B39F0(((Hero *)D_00189E20)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)D_00189E20)->f[0x24B8/4] < 0.2f) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0x98/4];
        }
        func_L00_002B3EF8(0, 0.027f, 0.3f, ((Hero *)D_00189E20)->f[0x24B8/4] * 0.087266475f);
        var_f12_19 = 0.0013888889f;
        if (((Hero *)D_00189E20)->f[0x24B8/4] < 0.2f) {
            var_f12_19 = 0.00055555557f;
        }
        func_L00_002B6198(var_f12_19);
        break;
    case 0x8:                                       /* switch 1 */
        if (func_L00_002ADEA0(3) == 2) {
            temp_a2_3 = ((Hero *)D_00189E20)->i[0x243C/4];
            if (temp_a2_3 != -1) {
                temp_a0_16 = (temp_a2_3 * 0x70) + (s32)D_00188660;
                if ((M2C_FIELD(temp_a0_16, s32* , 0x88) == ((Hero *)D_00189E20)->ptr[0x2290/4]) && (M2C_FIELD(temp_a0_16, u8* , 0x74) != 0)) {
                    func_002E59F8(temp_a2_3);
                }
            }
            ((Hero *)D_00189E20)->i[0x243C/4] = -1;
            func_L00_002B9BB0(3, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 2);
        } else {
            temp_a2_4 = ((Hero *)D_00189E20)->i[0x2438/4];
            if (temp_a2_4 != -1) {
                temp_a0_17 = (temp_a2_4 * 0x70) + (s32)D_00188660;
                if ((M2C_FIELD(temp_a0_17, s32* , 0x88) == ((Hero *)D_00189E20)->ptr[0x2290/4]) && (M2C_FIELD(temp_a0_17, u8* , 0x74) != 0)) {
                    func_002E59F8(temp_a2_4);
                }
            }
            ((Hero *)D_00189E20)->i[0x2438/4] = -1;
            func_L00_002B9BB0(4, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0xD);
        }
        var_f22_2 = 0.050000004f;
        if (((Hero *)D_00189E20)->i[0x1338/4] == 3) {
            var_f22_2 = 0.083333336f;
        }
        var_f23 = 0.72f;
        temp_f1_12 = ((Hero *)D_00189E20)->f[0x24C8/4];
        if (((Hero *)D_00189E20)->b[0x24EF] != 0) {
            var_f22_2 = 0.12833333f;
            var_f23 = 0.98640007f;
        }
        if (temp_f1_12 != 0.0f) {
            var_f23 = temp_f1_12;
        }
        temp_s0_7 = ((void*)D_00189E20) + 0xF0;
        sp110 = func_L00_002D3B00((s32) temp_s0_7);
        func_L00_002B39F0(var_f22_2, 0);
        func_L00_002B3EF8(0, 0.025f, 0.3f, 0.20943955f);
        func_L00_002B41B8(0.004166667f, 0.0019444445f);
        func_L00_002B4208(99999.0f);
        func_L00_002B7B80();
        func_L00_002D3960((s32) temp_s0_7, (s32) temp_s0_7);
        func_002AA3A8((s32) &sp110, (s32) (((void*)D_00189E20) + 0xA98), -var_f22_2 * var_f23, 0.025f, 0.3f, 0.28333336f);
        func_L00_002D34C0((s32) temp_s0_7, (s32) temp_s0_7, -sp110);
        temp_f12_5 = ((Hero *)D_00189E20)->f[0x88/4];
        if (temp_f12_5 < ((Hero *)D_00189E20)->f[0x490/4]) {
            func_002AA2E8((s32) (((void*)D_00189E20) + 0x490), temp_f12_5, 0.06666667f);
        }
        func_L00_002AC578();
        break;
    case 0x7:                                       /* switch 1 */
    case 0x9:                                       /* switch 1 */
    case 0xA:                                       /* switch 1 */
    case 0xB:                                       /* switch 1 */
    case 0xC:                                       /* switch 1 */
    case 0xD:                                       /* switch 1 */
    case 0xE:                                       /* switch 1 */
    case 0xF:                                       /* switch 1 */
    case 0x10:                                      /* switch 1 */
    case 0x11:                                      /* switch 1 */
    case 0x12:                                      /* switch 1 */
    case 0x1B:                                      /* switch 1 */
    case 0x38:                                      /* switch 1 */
    case 0x45:                                      /* switch 1 */
    case 0x48:                                      /* switch 1 */
    case 0x5B:                                      /* switch 1 */
    case 0x66:                                      /* switch 1 */
    case 0x6E:                                      /* switch 1 */
    case 0x81:                                      /* switch 1 */
    case 0x89:                                      /* switch 1 */
    case 0x92:                                      /* switch 1 */
        if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x1B) && (((Hero *)D_00189E20)->h[0x24FC/2] == 0) && (((Hero *)D_00189E20)->i[0x1338/4] == 3)) {
            if (func_L00_002B3998(10.0f) != 0) {
                func_L00_002B9B88(4, 0);
            }
        }
        if ((((Hero *)D_00189E20)->h[0x528/2] != 0) && (((Hero *)D_00189E20)->b[0x1492] != 0)) {
            ((Hero *)D_00189E20)->f[0x1B0/4] = (f32) ((Hero *)D_00189E20)->f[0x1B4/4];
        } else {
            if (((Hero *)D_00189E20)->b[0x49C] != 0) {
                func_L00_002B39F0(0.09916667f, 0);
            }
            func_L00_002B39F0(((Hero *)D_00189E20)->f[0x4A4/4], 0);
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x12) {
            if (((Hero *)D_00189E20)->i[0x1B8/4] == 0x14) {
                func_L00_002AABE0(3, 0x10, 1);
                if (D_L20_001B3730 != 0) {
                    func_002FD1B8(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)D_00189E20)->f[0x80/4], ((Hero *)D_00189E20)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            temp_f1_13 = ((Hero *)D_00189E20)->f[0xC38/4];
            if ((temp_f1_13 >= 4.0f) && (temp_f1_13 <= 7.0f)) {
                func_L00_002AA938(7, 0, 0);
            }
        }
        temp_a2_5 = ((Hero *)D_00189E20)->h[0x4AC/2];
        temp_a1_8 = ((Hero *)D_00189E20)->i[0x1B8/4];
        if (temp_a1_8 == temp_a2_5) {
            qcopy(&((Hero *)D_00189E20)->q[0x460/16], &((Hero *)D_00189E20)->q[0x80/16]);
        }
        if ((((Hero *)D_00189E20)->b[0x49C] != 0) || ((temp_a1_8 < temp_a2_5) && (temp_v1_33 = ((Hero *)D_00189E20)->u[0x2294/4], (temp_v1_33 != 0xB)) && (temp_v1_33 != 0x10) && (temp_v1_33 != 0xC) && (temp_v1_33 != 0x11) && (temp_v1_33 != 0x1B) && (temp_v1_33 != 0x89) && (temp_v1_33 != 0x48))) {
            if (((Hero *)D_00189E20)->h[0x528/2] != 0) {
                func_L00_002B9598();
                if ((((Hero *)D_00189E20)->u[0x2294/4] == 0xA) && (((Hero *)D_00189E20)->i[0x1B8/4] < 0xA) && (((Hero *)D_00189E20)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)D_00189E20)->f[0xF0/4] = (f32) (((Hero *)D_00189E20)->f[0xF0/4] + (func_00283180(((Hero *)D_00189E20)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)D_00189E20)->f[0xF4/4] = (f32) (((Hero *)D_00189E20)->f[0xF4/4] + (func_00283198(((Hero *)D_00189E20)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)D_00189E20)->q[0x140/16], &((Hero *)D_00189E20)->q[0xF0/16]);
                }
            } else {
                func_L00_002B3EF8(0, 0.015f, 0.2f, 0.2501639f);
                temp_f20_16 = ((Hero *)D_00189E20)->f[0x1B4/4];
                if ((u8) ((Hero *)D_00189E20)->b[0x49C] >= 2U) {
                    ((Hero *)D_00189E20)->f[0x1B4/4] = (f32) (temp_f20_16 * 0.4f);
                }
                if (((Hero *)D_00189E20)->h[0x1454/2] != 0) {
                    func_L00_002B4208(((Hero *)D_00189E20)->f[0x1458/4]);
                } else {
                    func_L00_002B4208(99999.0f);
                }
                ((Hero *)D_00189E20)->f[0x1B4/4] = temp_f20_16;
                if (((Hero *)D_00189E20)->b[0x49C] != 1) {
                    func_L00_002B41B8(((Hero *)D_00189E20)->f[0x500/4], ((Hero *)D_00189E20)->f[0x504/4]);
                }
                if (((Hero *)D_00189E20)->b[0x49C] != 0) {
                    if ((*(s32*)&D_00138354) != 0) {
                        if (((Hero *)D_00189E20)->h[0x34A/2] != 0) {
                            ((Hero *)D_00189E20)->f[0x1B4/4] = 0.0f;
                        }
                    }
                    if (((Hero *)D_00189E20)->b[0x49C] != 0) {
                        func_L00_002B94D8(((Hero *)D_00189E20)->f[0x504/4]);
                    }
                }
                func_L00_002B54F8(0.5f, 0.033333335f);
                if (((Hero *)D_00189E20)->u[0x2294/4] == 9) {
                    temp_v1_34 = ((Hero *)D_00189E20)->i[0x1B8/4];
                    if (temp_v1_34 < (((Hero *)D_00189E20)->h[0x4AC/2] + 4)) {
                        func_L00_002D3798((s32) (((void*)D_00189E20) + 0xF0), (s32) (((void*)D_00189E20) + 0xF0), (f32) temp_v1_34 * 0.0044444446f);
                    }
                }
                if (((Hero *)D_00189E20)->u[0x2294/4] == 0xA) {
                    temp_v1_35 = ((Hero *)D_00189E20)->i[0x1B8/4];
                    if (temp_v1_35 < 0x22) {
                        func_L00_002D3798((s32) (((void*)D_00189E20) + 0xF0), (s32) (((void*)D_00189E20) + 0xF0), (f32) temp_v1_35 * 0.014722222f);
                    }
                }
                if ((((Hero *)D_00189E20)->i[0x1B8/4] < 0xA) && (((Hero *)D_00189E20)->f[0x24B8/4] > 0.2f)) {
                    qcopy(v0, &((Hero *)D_00189E20)->q[0x80/16]);
                    func_L00_002D38A0((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    func_L00_002D3798((s32) ((TI128*)v10), (s32)((TI128*)v0), 0.95f);
                    if (func_002761F8((s32)((TI128*)v0), (s32) ((TI128*)v10), 4, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)D_00189E20)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            func_L00_002B6BC8();
            if (((Hero *)D_00189E20)->u[0x2294/4] == 0x12) {
                temp_s0_8 = ((void*)D_00189E20) + 0xF0;
                var_f0_11 = func_00282E20((s32) temp_s0_8);
                if (var_f0_11 > 0.06166667f) {
                    var_f0_11 = 0.06166667f;
                }
                func_00282F70((s32) temp_s0_8, (s32) temp_s0_8, var_f0_11);
            }
        }
        temp_f1_14 = ((Hero *)D_00189E20)->f[0x318/4];
        temp_f2_7 = ((Hero *)D_00189E20)->f[0x490/4];
        if (temp_f2_7 < temp_f1_14) {
            temp_f0_29 = temp_f2_7 + 0.10000001f;
            ((Hero *)D_00189E20)->f[0x490/4] = temp_f0_29;
            if (temp_f1_14 < temp_f0_29) {
                ((Hero *)D_00189E20)->f[0x490/4] = temp_f1_14;
            }
        }
        temp_f1_15 = ((Hero *)D_00189E20)->f[0x88/4];
        if (temp_f1_15 < ((Hero *)D_00189E20)->f[0x490/4]) {
            ((Hero *)D_00189E20)->f[0x490/4] = temp_f1_15;
        }
        if ((((Hero *)D_00189E20)->h[0x4AC/2] < ((Hero *)D_00189E20)->i[0x1B8/4]) && (func_L00_002D3B00((s32) (((void*)D_00189E20) + 0xF0)) < 0.001f) && ((((Hero *)D_00189E20)->b[0x49D] == 0) || (((Hero *)D_00189E20)->i[0x1B8/4] > ((Hero *)D_00189E20)->i[0x434/4])) && ((((Hero *)D_00189E20)->u[0x2294/4] != 0xE) || (((Hero *)D_00189E20)->i[0x1B8/4] >= 0x12))) {
            temp_f1_16 = ((Hero *)D_00189E20)->f[0x458/4];
            ((Hero *)D_00189E20)->b[0x49E] = 1U;
            if (temp_f1_16 != 0.0f) {
                ((Hero *)D_00189E20)->f[0x520/4] = temp_f1_16;
            }
        }
        if (((Hero *)D_00189E20)->b[0x22B4] == 0) {
            func_L00_002B7B80();
        }
        if (((Hero *)D_00189E20)->b[0x22B4] == 1) {
            func_L00_002B8930();
        }
        temp_v1_36 = ((Hero *)D_00189E20)->u[0x2294/4];
        if ((temp_v1_36 == 0x10) || (temp_v1_36 == 0xD)) {
            func_L00_00322BE0((s32) (((void*)D_00189E20) + 0x18E0), (((Hero *)D_00189E20)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x81) {
            func_L00_00322BE0((s32) (((void*)D_00189E20) + 0x18E0), (((Hero *)D_00189E20)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x10) {
            if (((Hero *)D_00189E20)->i[0x1B8/4] >= 9) {
                if (((Hero *)D_00189E20)->f[0xC38/4] < 28.0f) {
                    func_L00_002D36E0((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    temp_v0_17 = func_00277F48(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0);
                    if (temp_v0_17 != 0) {
                        func_00282D30((s32) ((TI128*)v10), (s32) (((void*)D_00189E20) + 0x110), 7.0f);
                        for (var_s0_2 = 0; var_s0_2 < temp_v0_17; var_s0_2++) {
                            if (func_002ABB78(((s32 *)D_L20_001C4480)[var_s0_2]) != 0) {
                                func_002A8F70(((s32 *)D_L20_001C4480)[var_s0_2], (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x10000, (s32) (((void*)D_00189E20) + 0x80), (s32) ((TI128*)v10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        if ((((Hero *)D_00189E20)->u[0x2294/4] == 0x38) && (((Hero *)D_00189E20)->b[0x49E] == 0) && (((Hero *)D_00189E20)->f[0xF8/4] > 0.025000002f)) {
            func_L00_002AAE00();
        }
        func_L00_002B6560();
        func_L00_002AC578();
        break;
    case 0x16:                                      /* switch 1 */
        var_f20_13 = func_L00_002D3A58((s32)(D_00189E20 + 0xF0));
        var_f0_12 = 0.0011111111f;
        if ((((Hero *)D_00189E20)->h[0x34E/2] == 0) && (((Hero *)D_00189E20)->i[0x1B8/4] >= 0xB)) {
            var_f0_12 = 0.0027777778f;
        }
        var_f20_13 = var_f20_13 - var_f0_12;
        if (var_f20_13 < 0.0f) {
            var_f20_13 = 0.0f;
        }
        if (((Hero *)D_00189E20)->b[0x1497] != 0) {
            func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        }
        var_s0_3 = ((void*)D_00189E20) + 0xF0;
        func_L00_002D3BD8((s32) var_s0_3, (s32) var_s0_3, var_f20_13);
        func_L00_002D34C0((s32) var_s0_3, (s32) var_s0_3, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)D_00189E20)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        func_00282CF0((s32)((TI128*)v0), (s32)(D_00189E20 + 0x18A0), (s32)(D_00189E20 + 0x80));
        ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(v0[0], v0[1]);
        temp_f0_30 = func_00282E20((s32)((TI128*)v0));
        if (temp_f0_30 > 0.2f) {
            hp32 = (Hero *)D_00189E20;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(v0[0], v0[1]);
            ((Hero *)D_00189E20)->f[0x1B0/4] = temp_f0_30;
            if (temp_f0_30 < D_L20_001A7DAC[0][2]) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = D_L20_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)D_00189E20)->f[0x1B0/4] = D_L20_001A7DAC[1][1] * 0.016666668f;
            }
            if (((Hero *)D_00189E20)->b[0x22B4] == 1) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)D_00189E20)->f[0x24B8/4] = 1.0f;
            ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0x18AC/4];
            ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        }
        speed62 = 1.0f;
        if (((Hero *)D_00189E20)->b[0x22B4] == 3) {
            func_L00_002B3EF8(0, 0.03f, 0.3f, 0.093084246f);
        } else if (((Hero *)D_00189E20)->b[0x22B4] == 1) {
            func_L00_002B3EF8(0, 0.03f, 0.3f, 0.13089971f);
        } else if (((Hero *)D_00189E20)->b[0x22B4] == 0) {
            func_L00_002B3EF8(0, 0.03f, 0.3f, 0.13089971f);
        }
        if (((Hero *)D_00189E20)->b[0x22B4] == 0) {
            func_L00_002B7B80();
        }
        func_L00_002B41B8(speed62 * 0.005f, 0.0055555557f);
        func_L00_002B4208(99999.0f);
        if (((Hero *)D_00189E20)->b[0x22B4] == 0) {
            func_L00_002B4458(1);
        }
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x110, 0.0069444445f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
        }
        {
            s32 found, k, m;
            qcopy(v10, &((Hero *)D_00189E20)->q[0xE0/16]);
            found = func_00277F48(((Hero *)D_00189E20)->f[0x264/4] + 0.2f, (s32)((TI128*)v10), 0, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0);
            for (k = 0; k < found; k++) {
                m = ((s32 *)D_L20_001C4480)[k];
                if (m != 0) {
                    switch (*(s16 *)(m + 0xAA)) {
                    case 0xCB:
                        func_002A8F70(m, (s32) ((Hero *)D_00189E20)->ptr[0x2290/4], 0x10000, (s32) (((void*)D_00189E20) + 0xE0), (s32) D_US2_001A8F20, 100.0f);
                        break;
                    case 0x1366:
                        func_L02_00392C70();
                        break;
                    case 0x1367:
                        func_L02_003948D0();
                        break;
                    }
                }
            }
        }
        break;
    case 0x63:                                      /* switch 1 */
        func_00282CF0((s32)((TI128*)v0), (s32)(D_00189E20 + 0x18A0), (s32)(D_00189E20 + 0x80));
        if (func_00282DB0((s32)((TI128*)v0), (s32)(D_00189E20 + 0x160)) < 0.0f) {
            func_00282C88((s32)(D_00189E20 + 0x160));
        }
        func_00282C88((s32)(D_00189E20 + 0xF0));
        func_L00_002B94D8(0.0075000003f);
        func_L00_002B4458(0);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)(D_00189E20 + 0xF0)), (s32) ((void*)(D_00189E20 + 0x18A0)) - 0x1790, 0.0069444445f);
            func_L00_002B4308();
            break;
        }
        func_L00_002D34C0((s32) ((void*)(D_00189E20 + 0xF0)), (s32) ((void*)(D_00189E20 + 0xF0)), 0.015000001f);
        break;
    case 0x3C:                                      /* switch 1 */
    case 0x64:                                      /* switch 1 */
        func_00282C88((s32)(D_00189E20 + 0xF0));
        break;
    case 0x65:                                      /* switch 1 */
        func_00282C88((s32)(D_00189E20 + 0xF0));
        if (((f32) ((Hero *)D_00189E20)->i[0x18C0/4] * 0.5f) < (((Hero *)D_00189E20)->f[0x334/4] - ((Hero *)D_00189E20)->f[0x88/4])) {
            ((Hero *)D_00189E20)->f[0xF8/4] = -0.004166667f;
        } else {
            ((Hero *)D_00189E20)->f[0xF8/4] = -0.016666668f;
        }
        break;
    case 0x79:                                      /* switch 1 */
        func_L00_002BA220();
        /* fallthrough */
    case 0x78:                                      /* switch 1 */
        func_00282C88((s32)(D_00189E20 + 0xF0));
        M2C_FIELD(((void*)(D_00189E20 + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x7A:                                      /* switch 1 */
        func_00282C88((s32)(D_00189E20 + 0xF0));
        M2C_FIELD(((void*)(D_00189E20 + 0xF0)), f32* , 8) = -0.0058333334f;
        break;
    case 0x3F:                                      /* switch 1 */
    case 0x43:                                      /* switch 1 */
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        func_L00_002B39F0(1.0f, 0);
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        func_L00_002B41B8(0.0f, 0.0035f);
        func_00282C88((s32)(D_00189E20 + 0xF0));
        func_L00_002B4458(0);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)(D_00189E20 + 0xF0)), (s32) ((void*)D_00189E20) + 0x130, 0.0069444445f);
            func_L00_002B4308();
            break;
        }
        func_L00_002D34C0((s32) ((void*)(D_00189E20 + 0xF0)), (s32) ((void*)(D_00189E20 + 0xF0)), 0.015000001f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.0f;
        temp_v1_37 = (s32) &D_L20_00268D90[((Hero *)D_00189E20)->h[0xBFC/2]];
        temp_a0_21 = M2C_FIELD(temp_v1_37, s32* , 4);
        switch (temp_a0_21) {
        case 0:
            if (((Hero *)D_00189E20)->f[0xC38/4] < 5.5f) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        case 1:
            if (((Hero *)D_00189E20)->f[0xC38/4] < 5.5f) {
                ((Hero *)D_00189E20)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        }
        if (((Hero *)D_00189E20)->i[0xC2C/4] == 0) {
            temp_f1_17 = ((Hero *)D_00189E20)->f[0xC38/4];
            if ((f32) M2C_FIELD(temp_v1_37, s32* , 0x1C) <= temp_f1_17) {
                if (temp_f1_17 <= (f32) M2C_FIELD(temp_v1_37, s32* , 0x20)) {
                    temp_s0_9 = ((M2C_FIELD(temp_v1_37, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    func_0029FCC0((s32) ((Hero *)D_00189E20)->ptr[0x2290/4], temp_s0_9, (s32) ((TI128*)v10));
                    func_0029FCC0((s32) ((Hero *)D_00189E20)->ptr[0x2290/4], temp_s0_9 | 1, (s32) ((TI128*)v20));
                    func_00282CC0((s32)((TI128*)v0), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                    func_00282D30((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    func_002A8C28((s32) ((Hero *)D_00189E20)->ptr[0x2290/4], (s32)((TI128*)v0), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
                }
            }
        }
        func_002AA2E8((s32)(D_00189E20 + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)D_00189E20)->i[0xBE8/4] != 0) || (((Hero *)D_00189E20)->i[0xBE4/4] != 0)) {
            ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0xBEC/4];
            func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
        } else {
            func_L00_002B75A0(5.0f, 0.78539824f, 0.78539824f);
        }
        func_L00_002B41B8(0.010277778f, 0.007777778f);
        if (((Hero *)D_00189E20)->i[0xBE8/4] != 0) {
            if (((Hero *)D_00189E20)->b[0x22C3] == 2) {
                func_L00_002B42D8((s32) (((void*)D_00189E20) + 0xBC0));
            } else {
                func_L00_002B4208(((Hero *)D_00189E20)->f[0xBEC/4]);
            }
        } else {
            func_L00_002B4208(99999.0f);
        }
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0x118/4] - 0.0069444445f);
            func_L00_002B4308();
        } else {
            ((Hero *)D_00189E20)->f[0xF8/4] = (f32) (((Hero *)D_00189E20)->f[0xF8/4] - 0.015000001f);
        }
        func_L00_002B9F00(0.7f, 0.0f, 0.3f);
        break;
    case 0x4B:                                      /* switch 1 */
        func_L00_002B39F0(0.033333335f, 0);
        func_L00_002B3EF8(0, 0.04f, 0.2f, 0.14544412f);
        func_L00_002B41B8(0.004166667f, 0.0019444445f);
        func_L00_002B4208(99999.0f);
        func_L00_002D3960((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0));
        func_L00_002D34C0((s32) ((void*)(D_00189E20 + 0xF0)), (s32) ((void*)(D_00189E20 + 0xF0)), 0.024000002f);
        break;
    case 0x4E:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0x1A0/4] = (f32) ((Hero *)D_00189E20)->f[0x32C/4];
        ((Hero *)D_00189E20)->f[0x1B0/4] = 0.09166667f;
        func_L00_002B6198(0.0069444445f);
        var_f12_16_u2 = 0.005f;
        var_a1_5_u2 = ((void*)D_00189E20) + 0x130;
        func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32) var_a1_5_u2, var_f12_16_u2);
        break;
    case 0x41:                                      /* switch 1 */
        func_L00_002B39F0(0.050000004f, 0);
        if (((Hero *)D_00189E20)->h[0x1E0/2] == 0) {
            func_L00_002B6BC8();
        }
        func_L00_002D34C0((s32) (((void*)D_00189E20) + 0xF0), (s32) (((void*)D_00189E20) + 0xF0), 0.0033333334f);
        if (((Hero *)D_00189E20)->f[0xF8/4] < -0.16666667f) {
            ((Hero *)D_00189E20)->f[0xF8/4] = -0.16666667f;
        }
        break;
    case 0x44:                                      /* switch 1 */
        if (((Hero *)D_00189E20)->f[0xF8/4] > 0.0f) {
            func_L00_002AA0F0(0.0f, 0.20943955f, 0.0f);
        }
        func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.0055555557f);
        break;
    case 0x40:                                      /* switch 1 */
    case 0x4C:                                      /* switch 1 */
        func_L00_002B39F0(0.050000004f, 0);
        var_f14 = 0.16580631f;
        var_f12_21 = 0.033f;
        if (((Hero *)D_00189E20)->b[0x40F] != 0) {
            var_f14 = 0.19489513f;
            var_f12_21 = 0.037f;
        }
        func_L00_002B3EF8(0, var_f12_21, 0.15f, var_f14);
        func_L00_002B41B8(0.005f, 0.0055555557f);
        if (((Hero *)D_00189E20)->f[0x174/4] < 0.011666667f) {
            ((Hero *)D_00189E20)->b[0x40C] = 1U;
            if ((func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)D_00189E20)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)D_00189E20)->b[0x40F] = 1U;
            }
        }
        temp_f20_18 = func_L00_0032F038(0);
        if ((func_00283C80(temp_f20_18, func_L00_0032F038(2)) > 2.617994f) && (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)D_00189E20)->f[0x24B8/4] > 0.8f)) {
            ((Hero *)D_00189E20)->b[0x40F] = 1U;
            ((Hero *)D_00189E20)->b[0x40C] = 1U;
        }
        if (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) < 0.087266475f) {
            ((Hero *)D_00189E20)->b[0x40C] = 0U;
        }
        if (((Hero *)D_00189E20)->b[0x40F] != 0) {
            if (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) < 0.06981318f) {
                ((Hero *)D_00189E20)->b[0x40F] = 0U;
            }
            if (((Hero *)D_00189E20)->b[0x40F] != 0) {
                var_f2_4 = 0.050000004f - (func_00282C48(((Hero *)D_00189E20)->f[0x1A8/4]) * 0.02122066f);
                if (var_f2_4 < 0.0f) {
                    var_f2_4 = 0.0f;
                }
                if (var_f2_4 < ((Hero *)D_00189E20)->f[0x1B0/4]) {
                    ((Hero *)D_00189E20)->f[0x1B0/4] = var_f2_4;
                }
            }
        }
        if (((Hero *)D_00189E20)->b[0x40C] != 0) {
            func_L00_002B4208(((Hero *)D_00189E20)->f[0x1A0/4]);
        } else {
            func_L00_002B4208(99999.0f);
        }
        func_L00_002B4458(1);
        if (((Hero *)D_00189E20)->h[0x34E/2] != 0) {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0x130, 0.0069444445f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0((s32) ((void*)D_00189E20) + 0xF0, (s32) ((void*)D_00189E20) + 0xF0, 0.015000001f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        temp_f12_6 = func_00282E20((s32)(D_00189E20 + 0xF0));
        if (*(s16 *)(D_00189E20 + 0x34E) != 0) {
            temp_f12_6 = temp_f12_6 * 0.99f;
        } else {
            temp_f12_6 = temp_f12_6 * 0.92f;
        }
        func_L00_002EE4D8((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), temp_f12_6);
        temp_v1_38 = ((void*)(D_00189E20 + 0xF0)) - 0xF0;
        M2C_FIELD(temp_v1_38, s32* , 0xF8) = 0;
        if (M2C_FIELD(temp_v1_38, s16* , 0x34E) != 0) {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0) + 0x30, 0.0061111115f);
        } else {
            func_L00_002D34C0((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), 0.004f);
        }
        break;
    case 0x49:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
        ((Hero *)D_00189E20)->f[0xC20/4] = 1.3f;
        func_00282CF0((s32)(D_00189E20 + 0x190), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        ((Hero *)D_00189E20)->f[0x1A0/4] = func_00283248(((Hero *)D_00189E20)->f[0x190/4], ((Hero *)D_00189E20)->f[0x194/4]);
        func_L00_002B3EF8(0, 0.02f, 0.2f, 0.078539826f);
        func_00282CF0((s32) ((TI128*)v60), (s32)(D_00189E20 + 0x560), (s32)(D_00189E20 + 0x550));
        func_00282C88((s32) (((void*)D_00189E20) + 0xF0));
        if (((Hero *)D_00189E20)->u[0x2294/4] == 0x49) {
            func_00282DD8((s32) &v40[0], (s32) (((void*)D_00189E20) + 0x2C0), (s32) ((TI128*)v60));
        } else {
            func_00282DD8((s32) &v40[0], (s32) ((TI128*)v60), (s32) (((void*)D_00189E20) + 0x2C0));
        }
        func_00282F20((s32) &v40[0], (s32) &v40[0], 0.2f);
        func_00282CC0((s32) &v50[0], (s32)(D_00189E20 + 0x80), (s32) &v40[0]);
        if ((func_L00_002ACF88((s32)(D_00189E20 + 0x80), (s32)(D_00189E20 + 0x90), 0) != 0) && (func_L00_002ACF88((s32) &v50[0], (s32)(D_00189E20 + 0x90), (s32)((TI128*)v0)) != 0)) {
            func_00282CF0((s32)(D_00189E20 + 0xF0), (s32)((TI128*)v0), (s32)(D_00189E20 + 0x80));
            func_00282F20((s32)(D_00189E20 + 0xF0), (s32)(D_00189E20 + 0xF0), D_L20_00298970[func_00283CF0(((Hero *)D_00189E20)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x37:                                      /* switch 1 */
        if (M2C_FIELD(((Hero *)D_00189E20)->ptr[0x2290/4], u8* , 0x43) == 0x44) {
            func_L00_002B3EF8(0, 0.137f, 0.25f, 0.20362177f);
        } else {
            func_L00_002B3EF8(0, 1.0f, 0.1f, 0.40724355f);
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        func_00282C88((s32)(D_00189E20 + 0xF0));
        break;
    }
    if (sp114 != ((Hero *)D_00189E20)->i[0x2298/4]) {
        ((Hero *)D_00189E20)->i[0x1C0/4] = 0;
    }
    if (sp118 != M2C_FIELD(temp_fp, u8* , 0x43)) {
        ((Hero *)D_00189E20)->i[0x1C4/4] = 0;
    }
}
