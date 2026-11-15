/* func_L08_002CB6E8 (Tabora): the hero's per-frame state handler, a 147-way switch on the
   state at 0x2294 over 40 bodies (25416 bytes, level 8 only).  One function: one prologue,
   one return.  It is func_L20_002CD928's state machine with 23 of that level's bodies
   (the ones the jump table sends to the common tail here) left out; the C was derived from
   func_L20_002CD928's by the jump tables.  Level 4's func_L04_002E04A8 is the same
   function again (identical opcodes).

   The unit's flags (config/cflags.txt) are the ones func_L20_002CD928 needs, and each is
   needed by retail's code here too:
   -ffast-math      max.s;
   -g               the line labels that put the nop pairs before the div.s;
   -frac2-zero-ti-por           the por+sq clears of 0($sp);
   -frac2-keep-block-order and  no Cygnus block counting before cse;
   -frac2-no-null-pointer-checks
   (the quadword clears' zero in $a0 is the compiler's one-GPR TImode reload);
   -frac2-hazard-labels         branch targets on the mtc1 hazard nops.
   See docs/build/compiler-notes.md for each option.

   Stack: retail keeps the 0x20-byte vector at 0x20/0x40/0x30 and the matrix at 0x80 in
   case 0x2B, so that case uses v20, v40, v30 and m80 (v70 only reserves the 0x70 slot). */


#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct { s32 x0[7]; s32 x1C; u8 x20[0xC0]; } LevelInfo;
typedef struct { s32 w[11]; } Rec2C;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(d) (0)
extern char D_00138180[];
extern u8 D_00138320[];
extern u8 D_00138354[];
extern u8 D_00188660[];
extern char D_00189E20[];
extern char D_00189F10[];
extern char D_0018C750[];
extern u8 D_0018CF10[];
extern u32 D_001A7390 MACRO_ADDR;
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 D_001A7B08[0x40] MACRO_ADDR;
extern u8 D_001A7B2A MACRO_ADDR;
extern f32 D_L08_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L08_001A8FF0 MACRO_ADDR;
extern u8 D_L08_001ACF28[];
extern s32 D_L08_001B2508 MACRO_ADDR;
extern s32 D_L08_001B3170 MACRO_ADDR;
extern s32 D_L08_001B3178 MACRO_ADDR;
extern u8 D_L08_001B99C0[];
extern u8 D_L08_001B9B18[];
extern u8 D_L08_001B9D88[];
extern u8 D_L08_001C3FC0[];
extern u8 D_L08_00266590[];
extern Rec2C D_L08_00268110[];
extern u8 D_L08_00268490[];
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
extern s32 func_002A88A0(s32, s32, f32, f32, f32);
extern void func_002A8C00(s32, s32, s32, f32, s32);
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
extern void func_L00_002B94D8(f32);
extern void func_L00_002B9598(void);
extern f32 func_L00_002B9B38(s32, s32);
extern s32 func_L00_002B9B88(s32, s32);
extern void func_L00_002B9BB0(s32, s32, s32);
extern void func_L00_002B9F00(f32, f32, f32);
extern void func_L00_002BA138(s32, s32);
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
extern void func_L00_0041E958(f32, f32, f32);
extern s32 func_L04_002CC748(s32);
extern void func_L01_002B4DA0(s32);
/* Runs the hero's state handler each frame: walking, jumping, gliding and the other player actions. */
void func_L08_002CB6E8(void) {
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
    f32 v70[4] __attribute__((aligned(16)));
    f32 m80[16] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* varV0N3U2;
    void* varS1N5U2;
    f32 varF12N16U2;
    void* varA1N5U2;
    s32 varA0N2U2;
    void* varS0N3U2;
    s32 varV0N8U2;
    s32 varV1N4U2;
    void* varA0N13U2;
    s32 varA0N2U3;
    void* varS0N3U3;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 stackE0;
    f32 stackE4;
    f32 stackE8;
    f32 stackEC;
    f32 stackF0;
    f32 stackF4;
    f32 stackF8;
    s32 stackFC;
    f32 stack100;
    s32 stack104;
    f32 stack108;
    f32 stack10C;
    f32 stack110;
    s32 stack114;
    s32 stack118;
    s32 stack11C;
    f32 tmpF0;
    f32 tmpF0N10;
    f32 tmpF0N11;
    f32 tmpF0N12;
    f32 tmpF0N13;
    f32 tmpF0N14;
    f32 tmpF0N15;
    f32 tmpF0N16;
    f32 tmpF0N17;
    f32 tmpF0N18;
    f32 tmpF0N19;
    f32 tmpF0N20;
    f32 tmpF0N21;
    f32 tmpF0N22;
    f32 tmpF0N23;
    f32 tmpF0N24;
    f32 tmpF0N25;
    f32 tmpF0N26;
    f32 tmpF0N27;
    f32 tmpF0N28;
    f32 tmpF0N29;
    f32 tmpF0N2;
    f32 tmpF0N30;
    f32 tmpF0N3;
    f32 tmpF0N4;
    f32 tmpF0N5;
    f32 tmpF0N6;
    f32 tmpF0N7;
    f32 tmpF0N8;
    f32 tmpF0N9;
    f32 tmpF12;
    f32 tmpF12N2;
    f32 tmpF12N3;
    f32 tmpF12N4;
    f32 tmpF12N5;
    f32 tmpF12N6;
    f32 tmpF12N7;
    f32 tmpF1;
    f32 tmpF1N10;
    f32 tmpF1N11;
    f32 tmpF1N12;
    f32 tmpF1N13;
    f32 tmpF1N14;
    f32 tmpF1N15;
    f32 tmpF1N16;
    f32 tmpF1N17;
    f32 tmpF1N2;
    f32 tmpF1N3;
    f32 tmpF1N4;
    f32 tmpF1N5;
    f32 tmpF1N6;
    f32 tmpF1N7;
    f32 tmpF1N8;
    f32 tmpF1N9;
    f32 tmpF20;
    f32 tmpF20N10;
    f32 tmpF20N11;
    f32 tmpF20N12;
    f32 tmpF20N13;
    f32 tmpF20N14;
    f32 tmpF20N15;
    f32 tmpF20N16;
    f32 tmpF20N17;
    f32 tmpF20N18;
    f32 tmpF20N19;
    f32 tmpF20N2;
    f32 tmpF20N3;
    f32 tmpF20N4;
    f32 tmpF20N5;
    f32 tmpF20N6;
    f32 tmpF20N7;
    f32 tmpF20N8;
    f32 tmpF20N9;
    f32 tmpF21;
    f32 tmpF21N2;
    f32 tmpF21N3;
    f32 tmpF22;
    f32 tmpF22N2;
    f32 tmpF22N3;
    f32 tmpF24;
    f32 tmpF2;
    f32 tmpF2N2;
    f32 tmpF2N3;
    f32 tmpF2N4;
    f32 tmpF2N5;
    f32 tmpF2N6;
    f32 tmpF2N7;
    f32 tmpF3;
    f32 varF0;
    f32 varF0N10;
    f32 varF0N11;
    f32 varF0N12;
    f32 varF0N13;
    f32 varF0N14;
    f32 varF0N15;
    f32 varF0N2;
    f32 varF0N3;
    f32 varF0N4;
    f32 varF0N5;
    f32 varF0N6;
    f32 varF0N7;
    f32 varF0N8;
    f32 varF0N9;
    f32 varF12;
    f32 varF12N10;
    f32 varF12N11;
    f32 varF12N13;
    f32 varF12N14;
    f32 varF12N15;
    f32 varF12N16;
    f32 varF12N17;
    f32 varF12N18;
    f32 varF12N19;
    f32 varF12N20;
    f32 varF12N21;
    f32 varF12N22;
    f32 varF12N4;
    f32 varF12N5;
    f32 varF12N6;
    f32 varF12N7;
    f32 varF12N8;
    f32 varF12N9;
    f32 varF14;
    f32 varF14N2;
    f32 varF1;
    f32 varF1N2;
    f32 varF1N3;
    f32 varF1N4;
    f32 varF1N5;
    f32 varF20;
    f32 varF20N10;
    f32 varF20N11;
    f32 varF20N12;
    f32 varF20N13;
    f32 varF20N2;
    f32 varF20N3;
    f32 varF20N4;
    f32 varF20N5;
    f32 varF20N6;
    f32 varF20N7;
    f32 varF20N8;
    f32 varF20N9;
    f32 varF21;
    f32 varF21N2;
    f32 varF21N3;
    f32 varF21N4;
    f32 varF21N5;
    f32 varF21N6;
    f32 varF21N7;
    f32 varF22;
    f32 varF22N2;
    f32 varF23;
    f32 varF2;
    f32 varF2N2;
    f32 varF2N3;
    f32 varF2N4;
    f32 varF2N5;
    s16 tmpA2N5;
    s32 tmpV0N4;
    s16 tmpV0N8;
    s32 tmpV1N10;
    s32 tmpV1N9;
    s32 tmpA0N21;
    s32 tmpA0N3;
    s32 tmpA0N5;
    s32 tmpA0N7;
    s32 tmpA0N8;
    s32 tmpA0N9;
    s32 tmpA1N3;
    s32 tmpA1N4;
    s32 tmpA1N5;
    s32 tmpA1N7;
    s32 tmpA1N8;
    s32 tmpA2;
    s32 tmpA2N2;
    s32 tmpA2N3;
    s32 tmpA2N4;
    s32 tmpS0N5;
    s32 tmpS0N9;
    s32 tmpS7;
    s32 tmpV0;
    s32 tmpV0N12;
    s32 tmpV0N13;
    s32 tmpV0N14;
    s32 tmpV0N15;
    s32 tmpV0N16;
    s32 tmpV0N17;
    s32 tmpV0N2;
    s32 tmpV1N12;
    s32 tmpV1N14;
    s32 tmpV1N16;
    s32 tmpV1N18;
    s32 tmpV1N20;
    s32 tmpV1N21;
    s32 tmpV1N22;
    s32 tmpV1N23;
    s32 tmpV1N24;
    s32 tmpV1N26;
    s32 tmpV1N34;
    s32 tmpV1N35;
    s32 tmpV1N4;
    s32 tmpV1N5;
    s32 tmpV1N6;
    s32 tmpV1N7;
    s32 tmpV1N8;
    s32 varA0;
    s32 varA0N10;
    s32 varA0N11;
    s32 varA0N12;
    s32 varA0N2;
    s32 varA0N4;
    s32 varA0N5;
    s32 varA0N8;
    s32 varA0N9;
    s32 varA1N2;
    s32 varA2;
    s32 varS0;
    s32 varS0N2;
    s32 varS1;
    s32 varS1N2;
    s32 varS1N3;
    s32 varS7;
    s32 varV0;
    s32 varV0N2;
    s32 varV0N4;
    s32 varV0N5;
    s32 varV0N6;
    s32 varV0N7;
    s32 varV0N8;
    s32 varV1;
    s32 varV1N2;
    s32 varV1N3;
    s32 varV1N4;
    s32* varS1N4;
    s32* varS1N6;
    u16 tmpV0N3;
    u16 tmpV1N11;
    u16 tmpV1N2;
    u32 tmpA0;
    u32 tmpV1;
    u32 tmpV1N13;
    u32 tmpV1N27;
    u32 tmpV1N28;
    u32 tmpV1N29;
    u32 tmpV1N30;
    u32 tmpV1N31;
    u32 tmpV1N33;
    u32 tmpV1N36;
    u32 tmpV1N3;
    u32 varA1N3;
    u8 tmpA0N14;
    u8 tmpA0N2;
    u8 tmpV1N25;
    u8 varA0N6;
    void* tmpA0N10;
    void* tmpA0N11;
    void* tmpA0N12;
    void* tmpA0N13;
    void* tmpA0N15;
    void* tmpA0N16;
    void* tmpA0N17;
    void* tmpA0N4;
    void* tmpA0N6;
    void* tmpA1;
    void* tmpA1N2;
    void* tmpA1N6;
    void* tmpFp;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* tmpS0;
    void* tmpS0N2;
    void* tmpS0N3;
    void* tmpS0N4;
    void* tmpS0N6;
    void* tmpS0N7;
    void* tmpS0N8;
    void* tmpS1;
    void* tmpS1N2;
    void* tmpS1N3;
    void* tmpS1N4;
    void* tmpS1N5;
    void* tmpS1N6;
    void* tmpS1N7;
    void* tmpS1N8;
    void* tmpS2;
    void* tmpS2N2;
    void* tmpS2N3;
    void* tmpS2N4;
    void* tmpS2N5;
    void* tmpS4;
    void* tmpS4N2;
    void* tmpS5;
    void* tmpV0N10;
    void* tmpV0N5;
    void* tmpV0N6;
    void* tmpV0N7;
    void* tmpV0N9;
    void* tmpV1N15;
    void* tmpV1N17;
    void* tmpV1N32;
    void* tmpV1N37;
    void* tmpV1N38;
    void* tmpV1N39;
    void* varA0N13;
    void* varA0N7;
    void* varA1N5;
    void* varS0N3;
    void* varS1N5;
    void* varV0N3;

    stack114 = ((Hero *)gHeroState)->i[0x2298/4];
    tmpFp = ((Hero *)gHeroState)->ptr[0x2290/4];
    stack118 = (s32) M2C_FIELD(tmpFp, u8* , 0x43);
    switch (((Hero *)gHeroState)->u[0x2294/4]) {                              /* switch 1 */
    case 0x0:
    case 0x1:
    case 0x3:
    case 0x4:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x39:
    case 0x6D:
    case 0x6F:
    case 0x7D:
        if (((Hero *)gHeroState)->b[0x22B9] != 0) {
            SpawnJitteredParticleAfterDelay(0xF, 0x1E);
        }
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            BuildHeroMoveImpulse(0.7f, 0.0f);
        } else {
            BuildHeroMoveImpulse(0.5f, 0.033333335f);
        }
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ResolveStickInputToDirection(1.0f, 0);
        tmpV1 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((tmpV1 == 1) || (tmpV1 == 0x1D)) {
            if (((Hero *)gHeroState)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)gHeroState) + 0x190), (s32)((TI128*)v0), (s32)&D_L08_001B9B18[0x218]);
                ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)D_L08_001B9B18)->f[0];
                SteerHeroHeading(0, 1.0f, 0.0f, 2.9088826f);
                if ((((Hero *)gHeroState)->b[0x22BB] != 0) && (((Hero *)gHeroState)->i[0x1B8/4] == 0x78)) {
                    if (((Hero *)gProgressStatistics)->uh[0xD8/2] < 0xFFFF) {
                        ((Hero *)gProgressStatistics)->uh[0xD8/2]++;
                    }
                    if (D_001A7390 > ((Hero *)gProgressStatistics)->u[0xDC/4]) {
                        ((Hero *)gProgressStatistics)->u[0xDC/4] = D_001A7390;
                    }
                    ((Hero *)gProgressStatistics)->u[0xE0/4] = ((Hero *)gProgressStatistics)->u[0xE0/4] | (1 << gCurrentMapIndex) | 0x80000000;
                }
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 3) {
            if (TryStartHeroGrab() != 0) {
                break;
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 4) {
            if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) || (tmpA0N2 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43), (tmpA0N2 == 0xE)) || (tmpA0N2 == 0xF)) {
                if (((Hero *)gHeroState)->u[0x2294/4] == 4) {
                    SteerHeroHeading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) > 0.0058177654f) {
                    tmpA0N3 = ((Hero *)gHeroState)->f[0x1A4/4] < 0.0f;
                    tmpA0N3 += 0xE;
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) != tmpA0N3) {
                        set_hero_animation(tmpA0N3, 0, 5.0f);
                    }
                    tmpF0 = FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)gHeroState)->f[0xC20/4] = tmpF0;
                    if (tmpF0 < 0.55f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 0.55f;
                    }
                    if (((Hero *)gHeroState)->f[0xC20/4] > 2.5f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 2.5f;
                    }
                } else if (((Hero *)gHeroState)->f[0x1A4/4] == 0.0f) {
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) != 0xD) {
                        set_hero_animation(0xD, 0, 7.0f);
                    }
                }
            }
        }
            tmpV1N3 = ((Hero *)gHeroState)->u[0x2294/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            if (tmpV1N3 == 3) {
                varF12 = ((Hero *)gHeroState)->f[0x17C/4] + 1.0f;
                if (varF12 > 1.0f) {
                    varF12 = 1.0f;
                }
                tmpA0N4 = ((Hero *)gHeroState)->ptr[0x2290/4];
                varF20 = varF12 * 0.0075000003f;
                ((Hero *)gHeroState)->f[0x24AC/4] = varF20;
                if (M2C_FIELD(tmpA0N4, u8* , 0x42) == M2C_FIELD(tmpA0N4, u8* , 0x43)) {
                    varF1 = ((Hero *)gHeroState)->f[0x174/4] / varF20;
                    if ((varF1 > 5.0f) && ((f32) M2C_FIELD(tmpA0N4, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, varF1, 0.5f, -1.0f);
                        if (((Hero *)gHeroState)->f[0xC20/4] > 1.1f) {
                            ((Hero *)gHeroState)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (tmpV1N3 == 4) {
                varF20 = 0.0075000003f;
                if (((Hero *)gHeroState)->b[0x1492] != 0) {
                    varF20 = 0.00047222225f;
                }
            } else {
                varF20 = 0.004916667f;
            }
            ApproachHeroSpeed(0.0f, varF20);
            ClearVector128((s32)(gHeroState + 0xF0));
            ShrinkHeroVectorByAmount(varF20);
            if ((((Hero *)gHeroState)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                varA0N2 = (s32)(gHeroState + 0xF0);
                if (((Hero *)gHeroState)->f[0x31C/4] > 0.2f) {
                    ApplyHeroModeTransform(varA0N2, varA0N2 + 0x30, 0.0061111115f);
                } else {
                    ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.015000001f);
                    if (((Hero *)gHeroState)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)gHeroState)->q[0x80/16], &((Hero *)gHeroState)->q[0x2D0/16]);
                        ((Hero *)gHeroState)->f[0x31C/4] = 0.0f;
                        ((Hero *)gHeroState)->h[0x34E/2] = 0;
                    }
                }
            } else {
                ClipHeroVelocityAgainstWall(0);
                if (((Hero *)gHeroState)->h[0x34E/2] == 0) {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
                } else {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
                    CancelHeroVelocityIntoWall();
                }
            }
        break;
    case 0x7C:
        hero7C = (void*)gHeroState;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            tmpV0 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = tmpV0;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)tmpV0 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)tmpV0 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(tmpV0, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            tmpV1N4 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(tmpV1N4, u16* , 0x34) = (u16) (M2C_FIELD(tmpV1N4, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        tmpV1N6 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(tmpV1N6, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(tmpV1N6, u8* , 0x23) = 0x80U;
        }
        tmpA0N5 = ((Hero *)hero7C)->i[0x7A4/4];
        tmpA1 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)tmpA0N5 + 0x10, (u8 *)tmpA1 + 0x10);
        qcopy((u8 *)tmpA0N5 + 0xF0, (u8 *)tmpA1 + 0xF0);
        func_002A0F48(tmpA0N5);
        }
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), vec_length_xy((s32)(gHeroState + 0xF0)) * 0.92f);
        UpdateHeroHeightOffset();
        break;
    case 0x32:
    case 0x33:
    case 0x34:
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 0x47) {
                (*(u16*)&D_0018CF10) = 0xFFFF;
            }
            UpdateSoundSlotObject(5, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xF);
            QueueRecordsByIndex(0x16);
        } else {
            tmpA2 = ((Hero *)gHeroState)->i[0x2440/4];
            if (tmpA2 != -1) {
                tmpA0N6 = (tmpA2 * 0x70) + (s32)gSoundState;
                if (M2C_FIELD(tmpA0N6, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) {
                    if (M2C_FIELD(tmpA0N6, u8* , 0x74) != 0) {
                        StopSoundVoice(tmpA2);
                    }
                }
            }
            ((Hero *)gHeroState)->i[0x2440/4] = -1;
        }
        if (((Hero *)gHeroState)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)gHeroState) + 0xA4A));
            tmpA0N7 = (s32) ((u16) ((Hero *)gHeroState)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((tmpA0N7 >= 9) ? 8 : tmpA0N7, 0, 0);
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x32) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            tmpF1N2 = ((Hero *)gHeroState)->f[0xC38/4];
            if (tmpF1N2 > 0.0f) {
                if (tmpF1N2 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                tmpV1N7 = ((Hero *)gHeroState)->i[0x1B8/4];
                if (tmpV1N7 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - tmpV1N7) / 3) + 1, 1, 0);
                }
            }
        }
        tmpV1N8 = ((Hero *)gHeroState)->i[0x2298/4];
        if (tmpV1N8 == 1) {
            if (((Hero *)gHeroState)->i[0x1B8/4] == tmpV1N8) {
                EmitHeroDustAndDebris(3, 0x10, 0);
                if (D_L08_001B3170 != 0) {
                    RippleDisturb(D_L08_001B3170, D_L08_001B3178, 0, ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)gHeroState)->h[0xA4A/2] = 0x46;
            }
            tmpV0N2 = ((Hero *)gHeroState)->i[0xA20/4] + 1;
            ((Hero *)gHeroState)->i[0xA20/4] = tmpV0N2;
            if (tmpV0N2 >= 0x29) {
                ((Hero *)gHeroState)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)gPadState)->f[0x12C/4] > ((Hero *)gPadState)->f[0x128/4] ? ((Hero *)gPadState)->f[0x12C/4] : ((Hero *)gPadState)->f[0x128/4]) * 0.008726647f;
        varF12N4 = 0.0f;
        k02 = 0.2f;
        if ((((((Hero *)gPadState)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            varF12N6 = ((Hero *)gPadState)->f[0x12C/4] * 1.5f;
            if (varF12N6 > 1.0f) {
                varF12N6 = 1.0f;
            }
            if (varF12N6 < k02) {
                varF12N6 = k02;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                tmpV1N9 = ((Hero *)gHeroState)->uh[0xA42/2] + 1;
                ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
                varF12N6 = ((f32) (s16) tmpV1N9 * 0.025f) + 0.5f;
                ((Hero *)gHeroState)->uh[0xA42/2] = (u16) tmpV1N9;
                if (varF12N6 > 1.0f) {
                    varF12N6 = 1.0f;
                }
            }
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (varF12N6 < 0.35f)) {
                varF12N6 = 0.35f;
            }
            varF12N4 = varF12N6 * 1.361357f;
        } else if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            varF12N5 = ((Hero *)gPadState)->f[0x128/4] * 1.5f;
            if (varF12N5 > 1.0f) {
                varF12N5 = 1.0f;
            }
            if (varF12N5 < k02) {
                varF12N5 = k02;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)gHeroState)->uh[0xA40/2] + 1;
                ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
                ((Hero *)gHeroState)->h[0xA40/2] = cntA40;
                varF12N5 = ((f32) (s16) cntA40 * 0.025f) + 0.5f;
                if (varF12N5 > 1.0f) {
                    varF12N5 = 1.0f;
                }
            }
            if ((f32) ((Hero *)gHeroState)->i[0x24C0/4] < 1500.0f) {
                varF12N5 = 1.0f;
            }
            varF12N4 = varF12N5 * -1.361357f;
        } else {
            ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
            ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            ((Hero *)gHeroState)->uh[0xA4E/2] = (u16) (((Hero *)gHeroState)->uh[0xA4E/2] + 1);
            if (((Hero *)gPadState)->f[0x128/4] > 0.75f) {
                tmpV1N10 = ((Hero *)gHeroState)->uh[0xA4C/2] + 1;
                ((Hero *)gHeroState)->h[0xA4C/2] = tmpV1N10;
                if ((s16) tmpV1N10 >= 0x5B) {
                    tmpV1N11 = ((Hero *)gProgressStatistics)->uh[0x84/2];
                    if (tmpV1N11 <= 0xFFFEU) {
                        ((Hero *)gProgressStatistics)->uh[0x84/2] = (u16) (tmpV1N11 + 1);
                    }
                }
                tmpV1N12 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)gProgressStatistics)->u[0x88/4] < (u32) tmpV1N12) {
                    ((Hero *)gProgressStatistics)->u[0x88/4] = (u32) tmpV1N12;
                }
                ((Hero *)gProgressStatistics)->i[0x8C/4] = (s32) (((Hero *)gProgressStatistics)->i[0x8C/4] | (1 << (*(s32*)&gCurrentMapIndex)) | 0x80000000);
            } else {
                ((Hero *)gHeroState)->uh[0xA4C/2] = 0U;
            }
        } else {
            ((Hero *)gHeroState)->uh[0xA4E/2] = 0U;
            ((Hero *)gHeroState)->uh[0xA4C/2] = 0U;
        }
        if (((Hero *)gPadState)->i[0x1A4/4] & 0x40) {
            hp32 = (Hero *)gHeroState;
            if ((D_L08_001B2508 - hp32->i[0xA54/4]) < 0x46) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = D_L08_001B2508;
        }
        if ((s16) ((Hero *)gHeroState)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x80) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            varF12N4 = 0.0f;
        }
        tmpF20 = ((Hero *)gHeroState)->f[0x94/4];
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), varF12N4, (s32) (((void*)gHeroState) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        tmpF22 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x94/4], tmpF20);
        ResolveStickInputToDirection(1.0f, 0);
        SteerHeroHeading(0, 0.007f, 0.08f, 0.087266475f);
        ((Hero *)gHeroState)->f[0xA2C/4] = (f32) ((Hero *)gHeroState)->f[0x1A4/4];
        FastFloatHelperD((s32) (((void*)gHeroState) + 0xA34));
        if (((Hero *)gHeroState)->i[0x2298/4] == 1) {
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.10000001f;
        } else if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xA) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.116666675f;
            } else {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.04666667f;
            }
        } else {
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.050000004f;
        }
        varF2 = ((Hero *)gHeroState)->f[0x24B8/4];
        if (((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xC0) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            if (varF2 < 1.0f) {
                varF2 = 1.0f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.15f) {
            varF0N2 = 0.35f;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
                varF0N2 = 0.4f;
            }
            if (varF2 < varF0N2) {
                varF2 = varF0N2;
            }
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xA)) {
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * varF2);
        }
        if (FastFloatHelperD((s32)(gHeroState + 0xA30)) != 0) {
            heroA30 = (void*)gHeroState;
            TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)gHeroState)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)gHeroState)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            SpawnBubbleParticle((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            if ((f32) RandomIntBelow(0x64) < 40.0f) {
                varA0N4 = 4;
                varA1N2 = 0xB;
            } else {
                varA0N4 = 0x28;
                varA1N2 = 0x5A;
            }
            ((Hero *)heroA30)->i[0xA30/4] = RandomIntRange(varA0N4, varA1N2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)gHeroState) + 0xA38)) != 0) {
                tmpS4 = ((Hero *)gHeroState)->ptr[0x1310/4];
                if (tmpS4 != 0) {
                    if (M2C_FIELD(tmpS4, s16* , 0xAA) == 0x261) {
                        for (varS1 = 0; varS1 < 4; varS1++) {
                            TransformMobyJointToWorld((s32) tmpS4, varS1 % 2, (s32)((TI128*)v0));
                            (*(TI128*)v20) = 0;
                            v20[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((Hero *)gHeroState)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
                            v0[0] += RandomFloatRange(0.0f, 0.03f);
                            v0[1] += RandomFloatRange(0.0f, 0.03f);
                            v0[2] += RandomFloatRange(0.0f, 0.03f);
                            qcopy(v10, &((Hero *)gHeroState)->q[0x110/16]);
                            AddOffsetVector((s32) ((TI128*)v10), (s32) ((TI128*)v10), -0.012500001f, ((Hero *)gHeroState)->f[0x98/4], ((Hero *)gHeroState)->f[0x94/4]);
                            ((Hero *)gHeroState)->h[0xA38/2] = FloatToInt((0.116666675f - ((Hero *)gHeroState)->f[0x1B4/4]) * 42.85714f);
                            SpawnBubbleParticle((s32)((TI128*)v0), (s32) ((TI128*)v10), RandomFloatRange(6300.0f, 9450.0f), -1.0f);
                        }
                    }
                }
            }
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
                ApproachHeroSpeed(0.003611111f, 0.0022222223f);
            } else {
                goto block_198;
            }
        } else {
block_198:
            ApproachHeroSpeed(0.0019444445f, 0.0011111111f);
        }
        tmpF21 = FastAddRotations(-((Hero *)gHeroState)->f[0x94/4], 0.0f);
        tmpV1N13 = ((Hero *)gHeroState)->u[0x2294/4];
        if (tmpV1N13 == 0x34) {
            BuildSphericalOffset((s32) (((void*)gHeroState) + 0xF0), ((Hero *)gHeroState)->f[0x1B4/4], ((Hero *)gHeroState)->f[0x98/4], tmpF21);
        } else if (tmpV1N13 == 0x32) {
            varF12N7 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L08_00268490, 0x1E) * 5.0f;
            if ((((Hero *)gHeroState)->i[0x22A0/4] == 0x34) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xF) && (varF12N7 < 0.075f)) {
                varF12N7 = 0.075f;
            }
            BuildSphericalOffset((s32)(gHeroState + 0xF0), varF12N7, ((Hero *)gHeroState)->f[0x98/4], tmpF21);
        } else if (tmpV1N13 == 0x33) {
            stackE0 = FastVecLength((s32) (((void*)gHeroState) + 0x160));
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &stackE0, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &stackE0, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), stackE0);
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        }
        ClipHeroVelocityAgainstWall(0);
        tmpF21N2 = ((Hero *)gHeroState)->f[0xA2C/4] * FastSinOrCosA(tmpF21) * -7.0f;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), tmpF21N2, (s32) (((void*)gHeroState) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        tmpF2 = tmpF22 * 47.0f;
        ((Hero *)D_L08_00266590)->f[0x114/4] = tmpF2;
        ((Hero *)D_L08_00266590)->f[0x118/4] = (f32) (tmpF21N2 * 1.5f);
        ((Hero *)D_L08_00266590)->f[0x110/4] = (f32) (tmpF21N2 * 1.4f);
        if (tmpF2 > 0.8726647f) {
            ((Hero *)D_L08_00266590)->f[0x114/4] = 0.8726647f;
        } else if (tmpF2 < -0.8726647f) {
            ((Hero *)D_L08_00266590)->f[0x114/4] = -0.8726647f;
        }
        tmpF1N3 = tmpF22 * 40.0f;
        tmpF0N2 = tmpF21N2 * 1.1f;
        ((Hero *)D_L08_00266590)->f[0x364/4] = 0.03f;
        ((Hero *)D_L08_00266590)->f[0x368/4] = 0.22f;
        ((Hero *)D_L08_00266590)->f[0x324/4] = tmpF1N3;
        ((Hero *)D_L08_00266590)->f[0x328/4] = tmpF0N2;
        ((Hero *)D_L08_00266590)->f[0x414/4] = 0.03f;
        ((Hero *)D_L08_00266590)->f[0x418/4] = 0.22f;
        ((Hero *)D_L08_00266590)->f[0x3D4/4] = tmpF1N3;
        ((Hero *)D_L08_00266590)->f[0x3D8/4] = tmpF0N2;
        break;
    case 0x73:
        tmpA0N8 = 0xA - ((s32) ((Hero *)gHeroState)->i[0x1B8/4] / 3);
        tmpS1 = ((void*)gHeroState) + 0xF0;
        EmitHeroRandomizedMotionEffects((tmpA0N8 >= 9) ? 8 : tmpA0N8, 0, 0);
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) tmpS1, (s32) tmpS1, vec_length_xy((s32) tmpS1) * 0.92f);
        ClipHeroVelocityAgainstWall(0);
        break;
    case 0x72:
        SpawnJitteredParticleAfterDelay(0xF, 0x1E);
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), vec_length_xy((s32)(gHeroState + 0xF0)) * 0.92f);
        ClipHeroVelocityAgainstWall(0);
        UpdateHeroHeightOffset();
        break;
    case 0x67:
    case 0x7F:
        stackE4 = FastVecLength((s32)(gHeroState + 0x160));
        ApproachValue((s32) &stackE4, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), stackE4);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        if (FastFloatHelperD((s32) (((void*)(gHeroState + 0x160)) + 0x8D0)) == 2) {
            tmpS2 = ((void*)(gHeroState + 0x160)) - 0x160;
            TransformMobyJointToWorld(M2C_FIELD(tmpS2, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(tmpS2, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)gHeroState)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            SpawnBubbleParticle((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            tmpV1N14 = M2C_FIELD(tmpS2, s32* , 0x1B8);
            if (tmpV1N14 < 0x28) {
                lim67 = 5;
                varV0N2 = RandomIntRange(2, lim67) + ((s32) M2C_FIELD(tmpS2, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (tmpV1N14 >= 0x47) {
                varV0N2 = RandomIntRange(0xA, 0x14);
block_224:
                M2C_FIELD(tmpS2, s32* , 0xA30) = varV0N2;
            }
        }
        if (((Hero *)gHeroState)->f[0xA3C/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)gHeroState) + 0xA3C), -0.025000002f, 0.00041666668f);
        ((Hero *)gHeroState)->f[0xF8/4] = (f32) ((Hero *)gHeroState)->f[0xA3C/4];
        break;
    case 0x35:
    case 0x36:
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x36) {
            SpawnJitteredParticleAfterDelay(0xF, 0x1E);
        }
        if (((Hero *)gHeroState)->f[0x174/4] > 0.025000002f) {
            EmitHeroTrailSpark(4, 0xC);
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x35) && (((Hero *)gHeroState)->f[0x174/4] > 0.016666668f)) {
            EmitHeroSideParticles(0, 1);
        }
        if (((Hero *)gHeroState)->h[0xA4A/2] != 0) {
            ((Hero *)gHeroState)->h[0xA4A/2] -= 1;
            tmpA0N9 = ((Hero *)gHeroState)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((tmpA0N9 >= 7) ? 6 : tmpA0N9, 0, 0);
        }
        ((Hero *)gHeroState)->f[0xC20/4] = 0.6f;
        ResolveStickInputToDirection(0.050000004f, 0);
        if ((((Hero *)gPadState)->i[0x1D4/4] == 0) && (((Hero *)gHeroState)->f[0x1B0/4] < 0.025000002f)) {
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.025000002f;
        }
        SteerHeroHeading(0, 0.007f, 0.08f, 0.087266475f);
        FastFloatHelperD((s32)(gHeroState + 0x798));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x35) {
            if ((((Hero *)gPadState)->i[0x1D4/4] != 0) && (((Hero *)gHeroState)->i[0x798/4] != 0)) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.050000004f;
            }
            if (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 0.78539824f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            }
            ApproachHeroSpeed(0.0011111111f, 0.0013888889f);
            tmpF20N2 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L08_00268490, 0x1E) * 5.5f;
            ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * tmpF20N2);
            tmpF0N3 = FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * tmpF20N2;
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ((Hero *)gHeroState)->f[0xF4/4] = tmpF0N3;
        } else {
            ((Hero *)gHeroState)->f[0x1B4/4] = 0.0f;
            ClearVector128((s32)(gHeroState + 0xF0));
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x35) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            tmpF1N4 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((tmpF1N4 > 0.0f) && (tmpF1N4 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        ShrinkHeroVectorByAmount(0.0011666666f);
        ClipHeroVelocityAgainstWall(0);
        UpdateHeroHeightOffset();
        break;
    case 0x85:
        tmpA1N2 = ((Hero *)gHeroState)->ptr[0x1830/4];
        qcopy(&((Hero *)gHeroState)->q[0x80/16], (u8 *)tmpA1N2 + 0x10);
        qcopy(&((Hero *)gHeroState)->q[0x90/16], (u8 *)tmpA1N2 + 0xF0);
        break;
    case 0x2F:
        anim2F = -1;
        blend2F = 0;
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            BuildHeroMoveImpulse(0.7f, 0.0f);
        } else {
            BuildHeroMoveImpulse(0.5f, 0.033333335f);
        }
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ResolveStickInputToDirection(1.0f, 0);
        ApproachHeroSpeed(0.004916667f, 0.004916667f);
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.004916667f);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)(gHeroState + 0xF0)) + 0x20), 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.015000001f);
        }
        if ((anim2F != -1) && (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(anim2F, 0, (f32) blend2F);
        } else {
            tmpV1N15 = ((Hero *)gHeroState)->ptr[0x2290/4];
            if ((M2C_FIELD(tmpV1N15, u8* , 0x60) & 2) && (M2C_FIELD(tmpV1N15, u8* , 0x42) == 0x36)) {
                set_hero_animation(GetHeroWeaponAnimationId_L04(0), 0, 5.0f);
            }
        }
        break;
    case 0x8A:
    case 0x8B:
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ApproachHeroSpeed(0.004916667f, 0.004916667f);
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.004916667f);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)gHeroState) + 0x120), 0.0061111115f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.015000001f);
        }
        varV0N3 = ((Hero *)gHeroState)->ptr[0xB10/4];
        if (varV0N3 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(varV0N3, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(varV0N3, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x23:
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ApproachHeroSpeed(0.004916667f, 0.004916667f);
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.004916667f);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)gHeroState) + 0x120), 0.0061111115f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.015000001f);
        }
        varV0N3U2 = ((Hero *)gHeroState)->ptr[0xAA4/4];
        if (varV0N3U2 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(varV0N3U2, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(varV0N3U2, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:
        qcopy(v0, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        tmpF0N4 = fast_vec_dist((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)v0));
        ((Hero *)gHeroState)->f[0xAB0/4] = tmpF0N4;
        ((Hero *)gHeroState)->f[0xAAC/4] = 60.0f;
        if (((Hero *)gHeroState)->f[0xAA0/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xAAC/4] = (f32) (tmpF0N4 / ((Hero *)gHeroState)->f[0x170/4]);
        }
        tmpV1N16 = ((Hero *)gHeroState)->i[0x2298/4];
        if (tmpV1N16 == 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.45000002f, 0.022222223f);
            tmpV0N5 = ((Hero *)gHeroState)->ptr[0xAA4/4];
            varF20N2 = FastMatrixHelperA(M2C_FIELD(tmpV0N5, f32* , 0x10) - M2C_FIELD(tmpFp, f32* , 0x10), M2C_FIELD(tmpV0N5, f32* , 0x14) - M2C_FIELD(tmpFp, f32* , 0x14));
            if (((Hero *)gHeroState)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], varF20N2) > 1.5707964f) {
                    varF20N2 = FastAddRotations(varF20N2, 3.1415927f);
                }
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = varF20N2;
            SteerHeroHeading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (tmpV1N16 == 1) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((SolveQuadratic((s32) &stackE8, (s32) &stackEC, -0.0058333334f, ((Hero *)gHeroState)->f[0xAA0/4], 1.9f - ((Hero *)gHeroState)->f[0xAB0/4]) > 0) && (stackE8 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xAAC/4] = stackE8;
            ((Hero *)gHeroState)->i[0x2298/4] = 1;
        }
        ((Hero *)gHeroState)->h[0x226/2] = 3;
        if (((Hero *)gHeroState)->f[0xAAC/4] < 20.0f) {
            ((Hero *)gHeroState)->i[0xAB4/4] = 1;
        }
        if (((Hero *)gHeroState)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-FastMatrixHelperA(vec_distance_xy((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)v0)), v0[2] - ((Hero *)gHeroState)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, turn24, 0.10762865f);
        }
        v20[0] = FastSinOrCosA(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        tmpF0N5 = FastSinOrCosB(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = tmpF0N5;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)gHeroState) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)gHeroState) + 0xF0), (s32) ((TI128*)v10), ((Hero *)gHeroState)->f[0xAA0/4]);
        tmpF0N6 = ((Hero *)gHeroState)->f[0xAAC/4];
        if (tmpF0N6 < 30.0f) {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - ((30.0f - tmpF0N6) * 0.008055556f));
        }
        break;
    case 0x25:
        ApproachValue((s32)(gHeroState + 0xABC), ((Hero *)gHeroState)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x110/16]);
        FastVecScale((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.9f);
        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.004166667f);
        qcopy(v0, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        ((Hero *)gHeroState)->f[0xAB0/4] = fast_vec_dist((s32)(gHeroState + 0x80), (s32)((TI128*)v0));
        FastVecAdd((s32) ((TI128*)v10), (s32)(gHeroState + 0x80), (s32)(gHeroState + 0xF0));
        FastVecSub((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32)((TI128*)v0));
        vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), ((Hero *)gHeroState)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v30));
        FastVecSub((s32)(gHeroState + 0xF0), (s32) ((TI128*)v20), (s32)(gHeroState + 0x80));
        break;
    case 0x2B:
        if ((((Hero *)gHeroState)->i[0xC28/4] & 2) && (M2C_FIELD(tmpFp, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)gHeroState)->f[0xC20/4] = 0.3f;
        }
        tmpV1N17 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        tmpF24 = ((Hero *)gHeroState)->f[0xF8/4];
        if (tmpV1N17 != 0) {
            tmpV0N6 = M2C_FIELD(tmpV1N17, void** , 0x68);
            if ((tmpV0N6 != 0) && (M2C_FIELD(tmpV0N6, s32* , 0x34) != 0)) {
                varF20N3 = M2C_FIELD(tmpV1N17, f32* , 0xF8);
                if (FastDiffRots(varF20N3, ((Hero *)gHeroState)->f[0x98/4]) > 90.0f) {
                    varF20N3 = FastAddRotations(varF20N3, 3.1415927f);
                }
                ApproachWithVelocity((s32) (((void*)gHeroState) + 0xAEC), varF20N3, (s32) (((void*)gHeroState) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xAEC/4];
        SteerHeroHeading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)v0), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) (((void*)gHeroState) + 0x80));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        ClearVector128((s32) ((TI128*)v20));
        v20[2] = ((Hero *)gHeroState)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)v40), (s32) ((TI128*)v20));
        matrix_from_basis_rows((s32) ((TI128*)m80), (s32) ((TI128*)v40));
        transform_vector((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m80));
        v10[0] = -FastMatrixHelperA(square_root((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        tmpF0N7 = FastMatrixHelperA(v0[2], v0[0]);
        v10[1] = tmpF0N7;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), tmpF0N7, (s32) (((void*)gHeroState) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), v10[0], (s32) (((void*)gHeroState) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        varS7 = ((Hero *)gHeroState)->f[0x88/4] < M2C_FIELD(((Hero *)gHeroState)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
            if ((varS7 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0x29) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.25f)) {
                ResolveStickInputToDirection(1.0f, 0);
                varF20N4 = ((Hero *)gHeroState)->f[0x24B8/4] * 0.0035f;
                if (varF20N4 > 0.083333336f) {
                    varF20N4 = 0.083333336f;
                }
                v30[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0x1A0/4]) * varF20N4;
                tmpF0N8 = FastSinOrCosB(((Hero *)gHeroState)->f[0x1A0/4]) * varF20N4;
                tmpA0N10 = ((void*)gHeroState) + 0xF0;
                (*(s32*)&v30[2]) = 0;
                v30[1] = tmpF0N8;
                FastVecAdd((s32) tmpA0N10, (s32) tmpA0N10, (s32) ((TI128*)v30));
            }
            if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
                tmpS2N2 = ((void*)gHeroState) + 0x80;
                if ((vec_distance_xy((s32) tmpS2N2, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10)) < (((Hero *)gHeroState)->f[0xAE0/4] * 1.57f)) || (((Hero *)gHeroState)->f[0x31C/4] > 1.5f)) {
                    tmpS1N2 = ((void*)gHeroState) + 0xF0;
                    ApplyHeroModeTransform((s32) tmpS1N2, (s32) (((void*)gHeroState) + 0x110), 0.011111111f);
                    if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (GetViewSpaceHeight((s32) tmpS1N2) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)v30), (s32) tmpS2N2, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
                        ApplyHeroModeTransform((s32) tmpS1N2, (s32) tmpS1N2, 0.015833333f);
                    }
                }
                tmpF20N3 = FastVecLength((s32)(gHeroState + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)v30), (s32)(gHeroState + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), tmpF20N3);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)v30));
            }
        }
        tmpV0N7 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        if (tmpV0N7 != 0) {
            tmpS0 = M2C_FIELD(tmpV0N7, void** , 0x68);
            tmpS1N3 = ((void*)gHeroState) + 0xF0;
            if (tmpS0 != 0) {
                tmpF0N9 = FastVecLength((s32) tmpS1N3);
                tmpF12 = M2C_FIELD(tmpS0, f32* , 0xC);
                stackF0 = tmpF0N9;
                if (tmpF12 < tmpF0N9) {
                    ApproachValue((s32) &stackF0, tmpF12, 0.004166667f);
                    vec_scale_to_length((s32) tmpS1N3, (s32) tmpS1N3, stackF0);
                }
            }
        }
        tmpF0N10 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f);
        tmpS5 = ((void*)gHeroState) + 0x80;
        tmpS4N2 = ((void*)gHeroState) + 0xF0;
        vD0[0] = FastSinOrCosA(tmpF0N10) * 0.15f;
        tmpF0N11 = FastSinOrCosB(tmpF0N10) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = tmpF0N11;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) tmpS5);
        FastVecAdd((s32) ((TI128*)v30), (s32) &vD0[0], (s32) tmpS4N2);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)v30), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)gHeroState)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)v30), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) tmpS4N2, (s32) ((TI128*)v30), (s32) &vD0[0]);
        tmpF20N4 = ((Hero *)gHeroState)->f[0xAE4/4];
        SpringFloatToGoal((s32) (((void*)gHeroState) + 0xAE4), (s32) (((void*)gHeroState) + 0xAE8), ((Hero *)gHeroState)->f[0xAE0/4], ((Hero *)gHeroState)->f[0xB04/4], ((Hero *)gHeroState)->f[0xB08/4], ((Hero *)gHeroState)->f[0xB0C/4]);
        tmpF20N5 = ((Hero *)gHeroState)->f[0xAE4/4] - tmpF20N4;
        if (((Hero *)gHeroState)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), tmpF20N5);
            FastVecAdd((s32) tmpS5, (s32) tmpS5, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (varS7 != 0)) {
            min2B = 0.23333335f;
            tmpF0N12 = vec_length_xy((s32) tmpS4N2);
            stackF4 = tmpF0N12;
            if (tmpF0N12 < min2B) {
                SpringFloatToGoal((s32) &stackF4, (s32) (((void*)gHeroState) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                v30[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0xAEC/4]) * ((Hero *)gHeroState)->f[0xAF4/4];
                tmpF0N13 = FastSinOrCosB(((Hero *)gHeroState)->f[0xAEC/4]);
                v30[2] = 0.0f;
                v30[1] = tmpF0N13 * ((Hero *)gHeroState)->f[0xAF4/4];
                FastVecAdd((s32) tmpS4N2, (s32) tmpS4N2, (s32) ((TI128*)v30));
            }
        }
        if ((((Hero *)gHeroState)->h[0xADC/2] != 0) && (((Hero *)gHeroState)->h[0x34E/2] != 0) && (((tmpF24 < 0.0f) && (((Hero *)gHeroState)->f[0xF8/4] > 0.0f)) || (((Hero *)gHeroState)->h[0xAFC/2] != 0))) {
            ((Hero *)gHeroState)->h[0xAFE/2] = 0;
            tmpF20N6 = square_root(((Hero *)gHeroState)->f[0xAE0/4] / ((Hero *)gHeroState)->f[0xAF0/4]) * 3.1415927f;
            tmpV0N8 = ((Hero *)gHeroState)->h[0xAFC/2];
            if (tmpV0N8 != 0) {
                varV0N4 = tmpV0N8 == 1;
            } else {
                (*(TI128*)v30) = ((Hero *)gHeroState)->q[0x110/16];
                varV0N4 = GetSpeedAlongHeroForward((s32) ((TI128*)v30)) > 0.0f;
            }
            if (varV0N4 != 0) {
                if (M2C_FIELD(tmpFp, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 1;
                } else {
                    tmpV0N9 = ((Hero *)gHeroState)->ptr[0x2290/4];
                    if (M2C_FIELD(tmpV0N9, u8* , 0x42) == M2C_FIELD(tmpV0N9, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, tmpF20N6, 0.5f, -1.0f);
                        ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(tmpFp, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)gHeroState)->h[0xAFC/2] = 2;
            } else {
                tmpV0N10 = ((Hero *)gHeroState)->ptr[0x2290/4];
                if (M2C_FIELD(tmpV0N10, u8* , 0x42) == M2C_FIELD(tmpV0N10, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, tmpF20N6, 0.5f, -1.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            tmpA1N3 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (tmpA1N3 != 0) {
                tmpF1N5 = vec_distance_xy((s32) (((void*)gHeroState) + 0x80), tmpA1N3 + 0x10);
                varV1N2 = 0;
                if ((((Hero *)gHeroState)->b[0x1496] != 0) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->b[0x1495] != 0)) {
                    varV1N2 = 1;
                }
                if (((tmpF1N5 > 2.0f) && (tmpF1N5 < 5.0f)) || (varV1N2 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0011111111f, 0.0011111111f);
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
            } else {
                ApproachHeroSpeed(0.00055555557f, 0.00055555557f);
                tmpA0N11 = ((void*)gHeroState) + 0xF0;
                SetViewSpaceVectorLength((s32) tmpA0N11, (s32) tmpA0N11, ((Hero *)gHeroState)->f[0x1B4/4]);
            }
        } else {
            varS1N2 = 0;
            if ((((Hero *)gHeroState)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->f[0x31C/4] > 4.0f)) {
                varS1N2 = 1;
            }
            tmpA1N4 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (tmpA1N4 != 0) {
                FastVecSub((s32)((TI128*)v0), tmpA1N4 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                tmpF0N14 = GetViewSpaceVectorLength((s32)((TI128*)v0));
                if (((tmpF0N14 > 2.0f) && (tmpF0N14 < 5.0f)) || (varS1N2 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0069444445f, 0.0069444445f);
                vec_scale_to_length((s32) ((TI128*)v10), (s32)gHeroState, ((Hero *)gHeroState)->f[0x1B4/4]);
                SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)v10));
            } else {
                if ((varS1N2 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 0x46)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.004166667f, 0.004166667f);
                SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), ((Hero *)gHeroState)->f[0x1B4/4]);
            }
        }
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
            ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0xBEC/4];
            qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)gHeroState)->f[0xC38/4] < 25.0f) {
            SelectHeroAimTarget(8.0f, 1.0471977f, 1.0471977f);
        }
        tmpF1N6 = ((Hero *)gHeroState)->f[0x31C/4];
        varF21 = 0.12833333f;
        if (tmpF1N6 > 2.25f) {
            varF21 = 0.064166665f;
        } else if (tmpF1N6 > 1.8f) {
            varF21 = 0.08983333f;
        }
        if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 23.5f) && (((Hero *)gHeroState)->f[0x118/4] < 0.0f) && (((Hero *)gHeroState)->h[0x34E/2] != 0)) {
            qcopy(v0, &((Hero *)gHeroState)->q[0x80/16]);
            ApplyHeroModeTransformReversed((s32)((TI128*)v0), (s32)((TI128*)v0), -0.5f);
            vec_scale_to_length((s32) &v40[0], (s32)gHeroState, 2.0f);
            make_hit_descriptor((s32) ((TI128*)v10), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &v40[0]);
            v10[3] = 5627.925f;
            (*(u8*)((u8*)v20+9)) = 1;
            (*(u16*)((u8*)v20+10)) = 0x47;
            (*(u8*)((u8*)v20+8)) = 0;
            ProcessCollisionHit(0.4f, (s32)((TI128*)v0), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)v10));
        }
        if (IsBelowPlaneWithinDepth(25.7f) != 0) {
            QueueRecordsByIndex(0x19);
            ((Hero *)gHeroState)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L08_001B99C0)->f[0x180/4] = 0.1f;
                ((Hero *)D_L08_001B99C0)->i[0x188/4] = 0x1E;
                ((Hero *)gHeroState)->h[0x224/2] = 0x23;
                ((Hero *)D_L08_001B99C0)->i[0x16C/4] = 0;
            }
        }
        tmpV1N18 = ((Hero *)gHeroState)->i[0x1B8/4];
        lim3 = 0xE;
        if (tmpV1N18 < 9) {
            tmpS0N2 = ((void*)gHeroState) + 0xF0;
            stackF8 = GetViewSpaceHeight((s32) tmpS0N2);
            ApproachValue((s32) &stackF8, varF21, 0.041666668f);
            SetViewSpaceHeight((s32) tmpS0N2, (s32) tmpS0N2, stackF8);
        } else if (tmpV1N18 > lim3) {
            tmpS1N4 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) tmpS1N4, (s32) tmpS1N4, 0.036111113f);
            if (GetViewSpaceHeight((s32) tmpS1N4) < 0.0f) {
                ((Hero *)gHeroState)->f[0xC00/4] = 1.0f;
            }
            varF20N5 = -0.6166667f;
            if (D_L08_001A8FF0 != 0) {
                varF20N5 = -1.1666667f;
            }
            if (GetViewSpaceHeight((s32) tmpS1N4) < varF20N5) {
                SetViewSpaceHeight((s32) tmpS1N4, (s32) tmpS1N4, varF20N5);
            }
        }
        break;
    case 0x15:
    case 0x83:
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        varA0N8 = (((Hero *)gHeroState)->i[0x22A0/4] == 1) && (((Hero *)gHeroState)->i[0x22A8/4] >= 0x15);
        if (varA0N8 == 0) {
            if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
                varS1N3 = 0;
                if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                    tmpS0N3 = ((void*)gHeroState) + 0xBC0;
                    varF20N6 = GetDirectionAngleDelta((s32) tmpS0N3, 0);
                    varF0N3 = GetDirectionAngleDelta((s32) tmpS0N3, 1);
                } else {
                    varF20N6 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                    varF0N3 = GetShortestAngleDelta(1, ((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                }
                if (varF0N3 < 4.3633237f) {
                    varS1N3 = 1;
                }
                if (varF20N6 > 0.0f) {
                    ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (varF0N3 + 1.0f));
                }
                ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
                qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
                if (varS1N3 != 0) {
                    SteerHeroHeading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    SteerHeroHeading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    varA0N9 = 1;
                    if ((((Hero *)gHeroState)->u[0x2294/4] == 0x83) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xC)) {
                        varA0N9 = 0;
                    } else if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 6.0f)) {
                        varA0N9 = 0;
                    }
                    if (varA0N9 != 0) {
                        if (((Hero *)gHeroState)->u[0x2294/4] == 0x15) {
                            SelectHeroAimTarget(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (IsBelowPlaneWithinDepth(33.0f) != 0)) {
            if ((((Hero *)gHeroState)->b[0x1492] != 0) && (((Hero *)gHeroState)->f[0x170/4] < 0.033333335f)) {
                {
                    ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.021666666f));
                    ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.021666666f));
                    qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
                }
            }
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x15) {
                SetupHeroAttachedObjectTransform();
            }
        }
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            if (IsBelowPlaneWithinDepth(84.0f) != 0) {
                varF21N2 = 0.041666668f;
                tmpF20N7 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    varF21N2 = 0.050000004f;
                }
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(tmpF20N7) * varF21N2));
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(tmpF20N7) * varF21N2));
                qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
            }
            SteerHeroReferencePoint();
        } else {
            ApproachHeroSpeed(0.010277778f, 0.007777778f);
            ComputeHeroPushDirection(99999.0f);
            if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
                ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            } else {
                ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
                break;
            }
        }
        break;
    case 0x13:
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L08_00268110[((Hero *)gHeroState)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            SteerHeroReferencePoint();
            break;
        }
        tmpA1N5 = ((Hero *)gHeroState)->i[0xBE4/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        tmpS2N3 = (((Hero *)gHeroState)->h[0xBFC/2] * 0x2C) + (s32)D_L08_00268110;
        if ((tmpA1N5 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 4)) {
            tmpS1N5 = ((void*)gHeroState) + 0x80;
            varF12N13 = vec_distance_xy(tmpA1N5 + 0x10, (s32) tmpS1N5);
            if ((*(s32*)&D_L08_001A8FF0) != 0) {
                varF12N13 = fast_vec_dist(((Hero *)gHeroState)->i[0xBE4/4] + 0x10, (s32) tmpS1N5);
            }
            varF12N13 = varF12N13 - 0.5f;
            if (varF12N13 < 0.0f) {
                varF12N13 = 0.0f;
            }
            tmpV1N20 = M2C_FIELD(tmpS2N3, s32* , 4);
            if (tmpV1N20 == 0) {
                varF0N4 = 0.75f;
                varF21N3 = 0.8f;
                varF22 = 4.0f;
            } else if (tmpV1N20 == 1) {
                varF0N4 = 0.6f;
                varF21N3 = 1.7f;
                varF22 = 4.0f;
            } else {
                varF0N4 = 1.3f;
                varF21N3 = 1.7f;
                varF22 = 1.9f;
            }
            tmpF20N8 = varF12N13 - varF0N4;
            if (FloatAbs(tmpF20N8) < (varF21N3 + 3.0f)) {
                varF12N15 = tmpF20N8 * 1.1111112f;
                if (varF22 < varF12N15) {
                    varF12N15 = varF22;
                }
                if (varF12N15 > 1.0f) {
                    ((Hero *)gHeroState)->f[0xBF4/4] = varF12N15;
                }
            }
        }
        tmpV1N21 = M2C_FIELD(tmpS2N3, s32* , 4);
        switch (tmpV1N21) {
        case 0:
            if (((Hero *)gHeroState)->f[0xC38/4] < 18.0f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            tmpF1N7 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (tmpF1N7 < 9.0f)) {
                if (tmpF1N7 > 8.0f) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.050000004f;
                } else if (tmpF1N7 > 7.0f) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.075f;
                } else {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.095f;
                }
            }
            break;
        case 2:
            if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < 12.0f)) {
                ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.06166667f;
            }
            break;
        }
        ApproachValue((s32)(gHeroState + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
        if (((Hero *)gHeroState)->b[0x22C3] != 0) {
            varF0N5 = GetDirectionAngleDelta((s32)(gHeroState + 0xBC0), 0);
        } else {
            varF0N5 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
        }
        tmpF1N8 = FloatAbs(varF0N5);
        if ((M2C_FIELD(tmpS2N3, s32* , 4) == 1) && (varF0N5 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (tmpF1N8 + 1.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
        qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        varV1N3 = 1;
        if ((M2C_FIELD(tmpS2N3, s32* , 4) == 1) && (((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 7.0f)) {
            varV1N3 = 0;
        }
        if (varV1N3 != 0) {
            SelectHeroAimTarget(5.0f, 0.78539824f, 0.78539824f);
        }
    }
        ApproachHeroSpeed(0.010277778f, 0.007777778f);
        if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
            if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                SetHeroPushDirection((s32) (((void*)gHeroState) + 0xBC0));
            } else {
                ComputeHeroPushDirection(((Hero *)gHeroState)->f[0xBEC/4]);
            }
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0x130), 0.0069444445f);
        } else {
            tmpA0N12 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) tmpA0N12, (s32) tmpA0N12, 0.015000001f);
        }
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:
        ApproachValue((s32)(gHeroState + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L08_001A8FF0) != 0) {
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xBD0), ((Hero *)gHeroState)->f[0x1B4/4]);
            if (((Hero *)gHeroState)->f[0x31C/4] > 0.0f) {
                ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0x130), 0.0069444445f);
            } else {
                SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
            }
            FastVecScale((s32)(gHeroState + 0x190), (s32)(gHeroState + 0xBD0), -1.0f);
        } else {
            ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0xBF0/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
            ((Hero *)gHeroState)->f[0xF4/4] = (f32) (FastSinOrCosB(((Hero *)gHeroState)->f[0xBF0/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
            if (((Hero *)gHeroState)->f[0x31C/4] > 0.0f) {
                ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0x128/4] - 0.0069444445f);
            } else {
                ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = FastAddRotations(((Hero *)gHeroState)->f[0xBF0/4], 3.1415927f);
        }
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        break;
    case 0x1F:
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
            ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0xBEC/4];
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)gHeroState)->i[0x1B8/4] < 4) {
            SelectHeroAimTarget(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0xA;
        lim2 = 0x12;
        tmpV1N22 = ((Hero *)gHeroState)->i[0x1B8/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (tmpV1N22 > lim) {
            if (tmpV1N22 < 0x12) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)gHeroState)->i[0x1B8/4] == 8) && (((Hero *)gHeroState)->f[0x184/4] < 0.33333334f)) {
            tmpS0N4 = ((void*)gHeroState) + 0x18E0;
            InitPendingSlot((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) tmpS0N4);
            AppendRecordToFourEntryTable((s32) tmpS0N4, 0x30, 2, 0.0f);
            AppendRecordToFourEntryTable((s32) tmpS0N4, 0x17, 4, 0.0f);
            AppendRecordToFourEntryTable((s32) tmpS0N4, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)gHeroState)->i[0x1B8/4] > lim2) ? 5 : 0;
        UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), sel1F);
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            tmpV1N23 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((tmpV1N23 > lim) && (tmpV1N23 < 0x11) && (((Hero *)gHeroState)->f[0x178/4] < 0.14166668f)) {
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.020000001f));
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.020000001f));
                qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
            }
            SteerHeroReferencePoint();
        } else {
            if (((Hero *)gHeroState)->i[0x1B8/4] > lim) {
                ApproachHeroSpeed(0.05277778f, 0.025f);
            }
            if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
                ComputeHeroPushDirection(((Hero *)gHeroState)->f[0xBEC/4]);
            } else {
                ComputeHeroPushDirection(99999.0f);
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x1F) {
            tmpV1N24 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((tmpV1N24 > lim) && (tmpV1N24 < 0x16)) {
                tmpS2N4 = ((Hero *)gHeroState)->ptr[0x1220/4];
                if (tmpS2N4 != 0) {
                    tmpS1N6 = ((void*)gHeroState) + 0x80;
                    v30[0] = 2.0f * FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]);
                    v30[1] = 2.0f * FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    tmpF22N2 = ((Hero *)gHeroState)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(tmpS2N4, u16* , 0xAA);
                    v40[0] = FastSinOrCosA(tmpF22N2) * 0.8f;
                    tmpF0N15 = FastSinOrCosB(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N15;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    EmitEffectsAtNearbyObjects((s32) tmpS2N4, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) tmpS2N4, (s32)((TI128*)v0)));
                    tmpF22N2 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -0.8726647f);
                    v40[0] = FastSinOrCosA(tmpF22N2) * 0.8f;
                    tmpF0N17 = FastSinOrCosB(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N17;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    EmitEffectsAtNearbyObjects((s32) tmpS2N4, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    tmpF22N2 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 0.8726647f);
                    v40[0] = FastSinOrCosA(tmpF22N2) * 0.8f;
                    tmpF0N19 = FastSinOrCosB(tmpF22N2) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = tmpF0N19;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) tmpS1N6);
                    EmitEffectsAtNearbyObjects((s32) tmpS2N4, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) tmpS2N4, (s32)((TI128*)v0)));
                }
            }
        }
        if (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        ClipHeroVelocityAgainstWall(1);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x120, 0.0061111115f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x22:
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
            qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
            SteerHeroHeading(0, 0.04f, 0.2f, 0.2821616f);
        } else {
            SelectHeroAimTarget(11.0f, 0.8726647f, -1.0f);
        }
        ApproachHeroSpeed(0.008333334f, 0.009722223f);
        ComputeHeroPushDirection(99999.0f);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x110, 0.015000001f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x2:
    case 0x70:
        varA0N11 = 0;
        if ((((Hero *)gHeroState)->b[0x1494] != 0) && (((Hero *)gHeroState)->f[0x24C4/4] < 0.25f)) {
            varA0N11 = 1;
        }
        if ((((Hero *)gHeroState)->b[0x22B9] != 0) || (varA0N11 != 0)) {
            if (((Hero *)gHeroState)->f[0x174/4] > 0.016666668f) {
                EmitHeroSideParticles(0, 2);
            }
            if (((Hero *)gHeroState)->f[0x174/4] > 0.008333334f) {
                EmitHeroTrailSpark(2, 4);
            }
            EmitHeroRandomizedMotionEffects(5, 2, 0);
        }
        if (((Hero *)gHeroState)->h[0x1454/2] == 0) {
            if (((Hero *)gHeroState)->f[0x174/4] < 0.028333336f) {
                ((Hero *)gHeroState)->b[0x40C] = 1U;
                if ((FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)gHeroState)->b[0x40F] = 1U;
                }
            }
            tmpF20N9 = ReadPadFloatHistory(1);
            if ((FastDiffRots(tmpF20N9, ReadPadFloatHistory(7)) > 1.9198624f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
                ((Hero *)gHeroState)->b[0x40F] = 1U;
                ((Hero *)gHeroState)->b[0x40C] = 1U;
            }
            if (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) < 0.087266475f) {
                ((Hero *)gHeroState)->b[0x40C] = 0U;
            }
        }
        if ((((Hero *)gHeroState)->b[0x40F] != 0) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) < 0.06981318f)) {
            ((Hero *)gHeroState)->b[0x40F] = 0U;
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            if (((Hero *)gHeroState)->i[0x410/4] != 0) {
                ((Hero *)gHeroState)->b[0x40F] = 1U;
            }
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0x3F0/16]);
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x408/4];
        } else {
            UpdateHeroTargetSpeed();
            if ((hero_slot_item_id(0) == 0xA) && ((((Hero *)gHeroState)->f[0x24BC/4] == 1.0f) || (((Hero *)gHeroState)->i[0x410/4] != 0)) && (((Hero *)gHeroState)->b[0x22BA] == 0)) {
                qcopy(&((Hero *)gHeroState)->q[0x3F0/16], &((Hero *)gHeroState)->q[0x190/16]);
                ((Hero *)gHeroState)->i[0x410/4] = 1;
                ((Hero *)gHeroState)->f[0x408/4] = ((Hero *)gHeroState)->f[0x1A0/4];
            } else {
                qcopy(&((Hero *)gHeroState)->q[0x3F0/16], &((Hero *)gHeroState)->q[0x0/16]);
                ((Hero *)gHeroState)->f[0x408/4] = ((Hero *)gHeroState)->f[0x98/4];
            }
        }
        if (((Hero *)gHeroState)->f[0xA70/4] > 0.0f) {
            pA60 = ((void*)gHeroState) + 0xA60;
            BuildHeroMoveImpulse(0.7f, 0.0f);
            (*(TI128*)v0) = ((Hero *)gHeroState)->q[0xA60/16];
            tmpF1N9 = ((Hero *)gHeroState)->f[0x1B0/4] + GetSpeedAlongHeroForward((s32)((TI128*)v0));
            ((Hero *)gHeroState)->f[0x1B0/4] = tmpF1N9;
            if (tmpF1N9 < 0.011666667f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.011666667f;
            }
            ClearVector128((s32) pA60);
        }
        varF20N7 = 1.0f;
        if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
            UpdateHeroTurnFromAnimation();
        } else {
            ((Hero *)gHeroState)->f[0x1458/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
            qcopy(&((Hero *)gHeroState)->q[0x1440/16], &((Hero *)gHeroState)->q[0x0/16]);
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (((Hero *)gHeroState)->b[0x40F] == 0) && (((Hero *)gHeroState)->b[0x22BA] == 0)) {
                SteerHeroHeading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                tmpF2N2 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
                if (((((Hero *)gHeroState)->f[0x24B8/4] < 0.9f) || ((((Hero *)gHeroState)->b[0x22BA] != 0) && (((Hero *)gHeroState)->b[0x40F] == 0))) && (tmpF2N2 > 0.78539824f)) {
                    varF20N7 = 0.0f;
                }
                SetHeroTurnRates();
            }
        }
        ApplyHeroModePoseOffsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            varF2N2 = 0.09916667f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.029178405f);
            if (varF2N2 < 0.0f) {
                varF2N2 = 0.0f;
            }
            if (varF2N2 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = varF2N2;
            }
        }
        k005 = varF20N7 * 0.005f;
        varF20N8 = 0.0055555557f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            varF1N2 = 2.617994f - ((Hero *)gHeroState)->f[0x1A8/4];
            if (varF1N2 > 1.0f) {
                varF1N2 = 1.0f;
            }
            if (varF1N2 < 0.2f) {
                varF1N2 = 0.2f;
            }
            varF20N8 = 0.004722222f;
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * varF1N2);
        }
        tmpF2N3 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
        if ((((Hero *)gHeroState)->f[0x24B8/4] < 0.75f) && (tmpF2N3 > 0.6108653f)) {
            varF1N3 = 1.0f - (tmpF2N3 * 0.4f);
            if (varF1N3 < 0.0f) {
                varF1N3 = 0.0f;
            }
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * varF1N3);
        }
        ApproachHeroSpeed(k005, varF20N8);
        if ((((Hero *)gHeroState)->b[0x40C] != 0) || (((Hero *)gHeroState)->h[0x1454/2] != 0)) {
            if (((Hero *)gHeroState)->b[0x22C3] == 0) {
                if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                    ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1458/4]);
                } else {
                    ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1A0/4]);
                }
            } else if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                SetHeroPushDirection((s32) (((void*)gHeroState) + 0x1440));
            } else {
                SetHeroPushDirection((s32) (((void*)gHeroState) + 0x190));
            }
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        ClipHeroVelocityAgainstWall(1);
        if (((Hero *)gHeroState)->h[0x214/2] != 0) {
            TryHeroSurfacePushResponse(5.0f, 0.2f, 0.35f);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x7B:
        UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        ResolveStickInputToDirection(1.0f, 0);
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.19166668f;
        ClampStickToUnitRange((s32)((TI128*)v0), (s32) (((void*)gHeroState) + 0x9F0), 0.17f);
        varF21N4 = (((Hero *)gHeroState)->f[0x24B8/4] * 0.020362178f) * v0[0];
        if ((*(s32*)&D_L08_001A8FF0) == 0) {
            if (((Hero *)gHeroState)->i[0x1B8/4] < 0x3C) {
                varF21N4 *= 0.1f;
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            RotateHeroMatrix(0.0f, 0.0f, varF21N4);
        }
        ApproachHeroSpeed(0.027777778f, 0.004166667f);
        ComputeHeroPushDirection(99999.0f);
        if ((*(s32*)&D_L08_001A8FF0) != 0) {
            qcopy(v10, &((Hero *)gHeroState)->q[0x2D0/16]);
            ApplyHeroModeTransformReversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            SpringVectorToTarget((s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            SpringFloatToGoal((s32) (((void*)gHeroState) + 0x88), (s32) (((void*)gHeroState) + 0xA00), ((Hero *)gHeroState)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(gHeroState + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(gHeroState + 0xE0));
        tmpV0N12 = ProcessCollisionHit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        if (tmpV0N12 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(gHeroState + 0x110), 7.0f);
            for (varS0 = 0; varS0 < tmpV0N12; varS0++) {
                if (IsMobyInSpecialClassRange(((s32 *)D_L08_001C3FC0)[varS0]) != 0) {
                    QueueImpactEffect(((s32 *)D_L08_001C3FC0)[varS0], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        SetCameraLimitsSlot0(0.017f, 0.3f);
        SetCameraLimitsSlot2(0.025f, 0.3f);
        SetCameraLimitsSlot3(0.03f, 0.27f);
        varF2N3 = varF21N4 * 27.0f;
        if (varF2N3 > 1.7f) {
            varF2N3 = 1.7f;
        } else if (varF2N3 < -1.7f) {
            varF2N3 = -1.7f;
        }
        tmpF0N20 = varF2N3 * 0.5f;
        ((Hero *)D_L08_00266590)->f[0x60/4] = (f32) -varF2N3;
        ((Hero *)D_L08_00266590)->f[0x278/4] = tmpF0N20;
        ((Hero *)D_L08_00266590)->f[0x1C8/4] = tmpF0N20;
        break;
    case 0x2E:
        SteerHeroReferencePoint();
        SetCameraLimitsSlot0(0.04f, 0.2f);
        SetCameraLimitsSlot1(0.04f, 0.2f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        tmpV1N25 = M2C_FIELD(tmpFp, u8* , 0x43);
        if (tmpV1N25 == 0x37) {
            varF0N6 = 1.4f;
            varF20N9 = ((Hero *)gHeroState)->f[0x1A8/4];
            if ((varF20N9 > 1.4f) || (varF0N6 = -1.4f, (varF20N9 < -1.4f))) {
                varF20N9 = varF0N6;
            }
            ((Hero *)D_L08_00266590)->f[0x60/4] = (f32) (varF20N9 * -0.14f);
            ((Hero *)D_L08_00266590)->f[0x118/4] = (f32) (varF20N9 * 0.3f);
            ((Hero *)D_L08_00266590)->f[0x1C0/4] = (f32) (varF20N9 * -0.22f);
            ((Hero *)D_L08_00266590)->f[0x278/4] = (f32) (varF20N9 * 0.4f);
            ((Hero *)D_L08_00266590)->f[0x274/4] = (f32) (FloatAbs(varF20N9) * -0.09f);
            ((Hero *)D_L08_00266590)->f[0x270/4] = (f32) (FloatAbs(varF20N9) * 0.08f);
        } else if (tmpV1N25 == 0x66) {
            tmpF22N3 = FastAddRotations(fast_subtract_rotations(FastMatrixHelperA(((Hero *)gHeroState)->f[0x110/4], ((Hero *)gHeroState)->f[0x114/4]), ((Hero *)gHeroState)->f[0x98/4]), 3.1415927f);
            varF21N5 = ((Hero *)gHeroState)->f[0x174/4] * 6.9813175f;
            if (varF21N5 > 0.43633235f) {
                varF21N5 = 0.43633235f;
            }
            tmpF20N10 = FastSinOrCosA(tmpF22N3) * varF21N5;
            tmpF0N21 = -FastSinOrCosB(tmpF22N3);
            ((Hero *)D_L08_00266590)->f[0x114/4] = tmpF20N10;
            ((Hero *)D_L08_00266590)->f[0x110/4] = (f32) (tmpF0N21 * varF21N5);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            varF12N16 = 0.0069444445f;
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)gHeroState) + 0x110), varF12N16);
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x17:
    case 0x18:
        FastVecSub((s32)(gHeroState + 0x190), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(((Hero *)gHeroState)->f[0x190/4], ((Hero *)gHeroState)->f[0x194/4]);
        SteerHeroHeading(0, 0.04f, 0.2f, 0.10471977f);
        if (((Hero *)gHeroState)->b[0x22C3] != 2) {
            StepAngleTowardTarget((s32)(gHeroState + 0x94), 0, 0.0f, 0.078539826f);
        }
        FastVecSub((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0x550), (s32)(gHeroState + 0x80));
        ClampVectorLength((s32)(gHeroState + 0xF0), 0.06666667f);
        ApproachValue((s32)(gHeroState + 0x580), ((Hero *)gHeroState)->f[0x88/4], 0.050000004f);
        break;
    case 0x19:
    case 0x1A:
        FastVecSub((s32)(gHeroState + 0x190), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(((Hero *)gHeroState)->f[0x190/4], ((Hero *)gHeroState)->f[0x194/4]);
        SteerHeroHeading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)v60), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32)(gHeroState + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &v40[0], (s32)(gHeroState + 0x2C0), (s32) ((TI128*)v60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)v60), (s32)(gHeroState + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(gHeroState + 0x80), (s32) &v40[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &v50[0], (s32)(gHeroState + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)v0), (s32)(gHeroState + 0x80));
            varV0N8 = FloatToInt(((Hero *)gHeroState)->f[0xC38/4]) * 4;
            varV1N4 = (s32)D_L08_001ACF28;
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), *(f32*)(varV0N8 + varV1N4) * 0.5f);
        }
        break;
    case 0x76:
        ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0x32C/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity(0.0069444445f);
        ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) ((void*)gHeroState) + 0x130, 0.005f);
        break;
    case 0x6:
    case 0x2C:
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x2C) {
            varF12N18 = 0.0f;
            if (((Hero *)gHeroState)->f[0x31C/4] > 4.0f) {
                varF12N18 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)gHeroState)->q[0x90/16]);
            ApproachWithVelocity((s32) &v0[1], varF12N18, (s32) (((void*)gHeroState) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            ApproachWithVelocity((s32)((TI128*)v0), 0.0f, (s32) (((void*)gHeroState) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA0/4], ((Hero *)gHeroState)->f[0xA4/4], 0.0f);
            if (((Hero *)gHeroState)->f[0x31C/4] > 1.0f) {
                ((Hero *)gHeroState)->i[0x2298/4] = 1;
            }
        }
        UpdateHeroTargetSpeed();
        if (((Hero *)gHeroState)->h[0x1E0/2] == 0) {
            UpdateHeroAirborneSteering();
        }
        varS1N5 = ((void*)gHeroState) + 0xF0;
        ApplyHeroModePoseOffsets();
        BuildHeroMoveImpulse(0.7f, 0.0f);
        ApplyHeroModeTransform((s32) varS1N5, (s32) varS1N5, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) varS1N5) < -0.8333334f) {
            SetViewSpaceHeight((s32) varS1N5, (s32) varS1N5, -0.8333334f);
        }
        break;
    case 0x74:
        ((Hero *)gHeroState)->c[0x22BC] = 1;
        varS1N5U2 = ((void*)gHeroState) + 0xF0;
        ApproachValue((s32) (((void*)gHeroState) + 0xA88), ((Hero *)gHeroState)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)gHeroState) + 0xA8C), ((Hero *)gHeroState)->f[0xA94/4], 0.0024240687f);
        StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA88/4], ((Hero *)gHeroState)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) varS1N5U2, (s32) varS1N5U2, vec_length_xy((s32) varS1N5U2) * 0.9f);
        ApplyHeroModeTransform((s32) varS1N5U2, (s32) varS1N5U2, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) varS1N5U2) < -0.8333334f) {
            SetViewSpaceHeight((s32) varS1N5U2, (s32) varS1N5U2, -0.8333334f);
        }
        break;
    case 0x82:
        UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        ang82 = (f32) LerpInt(0x2D0, 0xB4, ((Hero *)gHeroState)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        ShowGaugePopup(2, UpdateAngleAndBlend((s32) (((void*)gHeroState) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)gHeroState)->f[0x5B0/4] * 0.02f));
        varA0N12 = (s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40;
        if (((Hero *)gHeroState)->f[0x5B0/4] == 0.0f) {
            varA0N12 = 0;
        }
        if (varA0N12 != 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0x5B0), 0.0f, 0.1f);
            tmpA0N15 = ((void*)gHeroState) + 0xF0;
            OffsetPointInViewSpace((s32) tmpA0N15, (s32) tmpA0N15, 0.025f);
        } else {
            ApproachValue((s32) (((void*)gHeroState) + 0x5B0), 0.0f, 0.02f);
        }
        if (((Hero *)gPadState)->i[0x1A4/4] & 0x40) {
            ApproachValue((s32)(gHeroState + 0x5B0), 0.0f, 0.5f);
        }
        ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0075000003f);
        if (GetViewSpaceHeight((s32)(gHeroState + 0xF0)) > 0.10000001f) {
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.10000001f);
        }
        if (GetViewSpaceHeight((s32)(gHeroState + 0xF0)) < -0.20000002f) {
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), -0.20000002f);
        }
        tmpF12N4 = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        if ((((Hero *)gHeroState)->f[0x5B0/4] > 25.0f) && (((Hero *)gHeroState)->h[0x5BE/2] < 0x5A) && (tmpF12N4 < 0.0f) && (tmpF2N6 = ((Hero *)gHeroState)->f[0x31C/4], (tmpF2N6 < 1.2f))) {
            varF0N10 = (tmpF2N6 - 0.25f) * 1.0526315f;
            ((Hero *)gHeroState)->h[0x5BE/2] = (s16) ((u16) ((Hero *)gHeroState)->h[0x5BE/2] + 1);
            if (varF0N10 < 0.0f) {
                varF0N10 = 0.0f;
            }
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), tmpF12N4 * varF0N10);
            if (((Hero *)gHeroState)->f[0x31C/4] < 0.25f) {
                SpringFloatToGoal((s32)(gHeroState + 0x88), (s32)(gHeroState + 0x5B4), ((Hero *)gHeroState)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (tmpF12N4 > 0.0f) {
            ((Hero *)gHeroState)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L08_001B9D88) = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        ApplyHeroModePoseOffsets();
        ResolveStickInputToDirection(((Hero *)gHeroState)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
        }
        SteerHeroHeading(0, 0.027f, 0.3f, ((Hero *)gHeroState)->f[0x24B8/4] * 0.087266475f);
        varF12N19 = 0.0013888889f;
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            varF12N19 = 0.00055555557f;
        }
        ApproachHeroVelocity(varF12N19);
        break;
    case 0x8:
        if (hero_slot_item_id(3) == 2) {
            tmpA2N3 = ((Hero *)gHeroState)->i[0x243C/4];
            if (tmpA2N3 != -1) {
                tmpA0N16 = (tmpA2N3 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(tmpA0N16, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(tmpA0N16, u8* , 0x74) != 0)) {
                    StopSoundVoice(tmpA2N3);
                }
            }
            ((Hero *)gHeroState)->i[0x243C/4] = -1;
            UpdateSoundSlotObject(3, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 2);
        } else {
            tmpA2N4 = ((Hero *)gHeroState)->i[0x2438/4];
            if (tmpA2N4 != -1) {
                tmpA0N17 = (tmpA2N4 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(tmpA0N17, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(tmpA0N17, u8* , 0x74) != 0)) {
                    StopSoundVoice(tmpA2N4);
                }
            }
            ((Hero *)gHeroState)->i[0x2438/4] = -1;
            UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        }
        varF22N2 = 0.050000004f;
        if (((Hero *)gHeroState)->i[0x1338/4] == 3) {
            varF22N2 = 0.083333336f;
        }
        varF23 = 0.72f;
        tmpF1N12 = ((Hero *)gHeroState)->f[0x24C8/4];
        if (((Hero *)gHeroState)->b[0x24EF] != 0) {
            varF22N2 = 0.12833333f;
            varF23 = 0.98640007f;
        }
        if (tmpF1N12 != 0.0f) {
            varF23 = tmpF1N12;
        }
        tmpS0N7 = ((void*)gHeroState) + 0xF0;
        stack110 = GetViewSpaceHeight((s32) tmpS0N7);
        ResolveStickInputToDirection(varF22N2, 0);
        SteerHeroHeading(0, 0.025f, 0.3f, 0.20943955f);
        ApproachHeroSpeed(0.004166667f, 0.0019444445f);
        ComputeHeroPushDirection(99999.0f);
        ApplyHeroModePoseOffsets();
        ProjectVectorOntoViewPlane((s32) tmpS0N7, (s32) tmpS0N7);
        SpringFloatToGoal((s32) &stack110, (s32) (((void*)gHeroState) + 0xA98), -varF22N2 * varF23, 0.025f, 0.3f, 0.28333336f);
        ApplyHeroModeTransform((s32) tmpS0N7, (s32) tmpS0N7, -stack110);
        tmpF12N5 = ((Hero *)gHeroState)->f[0x88/4];
        if (tmpF12N5 < ((Hero *)gHeroState)->f[0x490/4]) {
            ApproachValue((s32) (((void*)gHeroState) + 0x490), tmpF12N5, 0.06666667f);
        }
        ProbeHeroAirborneWallContact();
        break;
    case 0x7:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x1B:
    case 0x38:
    case 0x45:
    case 0x48:
    case 0x5B:
    case 0x66:
    case 0x6E:
    case 0x81:
    case 0x89:
    case 0x92:
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x1B) && (((Hero *)gHeroState)->h[0x24FC/2] == 0) && (((Hero *)gHeroState)->i[0x1338/4] == 3)) {
            if (IsBelowPlaneWithinDepth(10.0f) != 0) {
                PlayHeroSound(4, 0);
            }
        }
        if ((((Hero *)gHeroState)->h[0x528/2] != 0) && (((Hero *)gHeroState)->b[0x1492] != 0)) {
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) ((Hero *)gHeroState)->f[0x1B4/4];
        } else {
            if (((Hero *)gHeroState)->b[0x49C] != 0) {
                ResolveStickInputToDirection(0.09916667f, 0);
            }
            ResolveStickInputToDirection(((Hero *)gHeroState)->f[0x4A4/4], 0);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x12) {
            if (((Hero *)gHeroState)->i[0x1B8/4] == 0x14) {
                EmitHeroDustAndDebris(3, 0x10, 1);
                if (D_L08_001B3170 != 0) {
                    RippleDisturb(D_L08_001B3170, D_L08_001B3178, 0, ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            tmpF1N13 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((tmpF1N13 >= 4.0f) && (tmpF1N13 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        tmpA2N5 = ((Hero *)gHeroState)->h[0x4AC/2];
        tmpA1N8 = ((Hero *)gHeroState)->i[0x1B8/4];
        if (tmpA1N8 == tmpA2N5) {
            qcopy(&((Hero *)gHeroState)->q[0x460/16], &((Hero *)gHeroState)->q[0x80/16]);
        }
        if ((((Hero *)gHeroState)->b[0x49C] != 0) || ((tmpA1N8 < tmpA2N5) && (tmpV1N33 = ((Hero *)gHeroState)->u[0x2294/4], (tmpV1N33 != 0xB)) && (tmpV1N33 != 0x10) && (tmpV1N33 != 0xC) && (tmpV1N33 != 0x11) && (tmpV1N33 != 0x1B) && (tmpV1N33 != 0x89) && (tmpV1N33 != 0x48))) {
            if (((Hero *)gHeroState)->h[0x528/2] != 0) {
                SteerHeroReferencePoint();
                if ((((Hero *)gHeroState)->u[0x2294/4] == 0xA) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xA) && (((Hero *)gHeroState)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
                }
            } else {
                SteerHeroHeading(0, 0.015f, 0.2f, 0.2501639f);
                tmpF20N16 = ((Hero *)gHeroState)->f[0x1B4/4];
                if ((u8) ((Hero *)gHeroState)->b[0x49C] >= 2U) {
                    ((Hero *)gHeroState)->f[0x1B4/4] = (f32) (tmpF20N16 * 0.4f);
                }
                if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                    ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1458/4]);
                } else {
                    ComputeHeroPushDirection(99999.0f);
                }
                ((Hero *)gHeroState)->f[0x1B4/4] = tmpF20N16;
                if (((Hero *)gHeroState)->b[0x49C] != 1) {
                    ApproachHeroSpeed(((Hero *)gHeroState)->f[0x500/4], ((Hero *)gHeroState)->f[0x504/4]);
                }
                if (((Hero *)gHeroState)->b[0x49C] != 0) {
                    if ((*(s32*)&D_00138354) != 0) {
                        if (((Hero *)gHeroState)->h[0x34A/2] != 0) {
                            ((Hero *)gHeroState)->f[0x1B4/4] = 0.0f;
                        }
                    }
                    if (((Hero *)gHeroState)->b[0x49C] != 0) {
                        ShrinkHeroVectorByAmount(((Hero *)gHeroState)->f[0x504/4]);
                    }
                }
                BuildHeroMoveImpulse(0.5f, 0.033333335f);
                if (((Hero *)gHeroState)->u[0x2294/4] == 9) {
                    tmpV1N34 = ((Hero *)gHeroState)->i[0x1B8/4];
                    if (tmpV1N34 < (((Hero *)gHeroState)->h[0x4AC/2] + 4)) {
                        OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) tmpV1N34 * 0.0044444446f);
                    }
                }
                if (((Hero *)gHeroState)->u[0x2294/4] == 0xA) {
                    tmpV1N35 = ((Hero *)gHeroState)->i[0x1B8/4];
                    if (tmpV1N35 < 0x22) {
                        OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) tmpV1N35 * 0.014722222f);
                    }
                }
                if ((((Hero *)gHeroState)->i[0x1B8/4] < 0xA) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f)) {
                    qcopy(v0, &((Hero *)gHeroState)->q[0x80/16]);
                    OffsetPointInViewSpace((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    OffsetPointBySideDirection((s32) ((TI128*)v10), (s32)((TI128*)v0), 0.95f);
                    if (CollLine((s32)((TI128*)v0), (s32) ((TI128*)v10), 4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)gHeroState)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            UpdateHeroAirborneSteering();
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x12) {
                tmpS0N8 = ((void*)gHeroState) + 0xF0;
                varF0N11 = vec_length_xy((s32) tmpS0N8);
                if (varF0N11 > 0.06166667f) {
                    varF0N11 = 0.06166667f;
                }
                FastVectorNormalizeHelper((s32) tmpS0N8, (s32) tmpS0N8, varF0N11);
            }
        }
        tmpF1N14 = ((Hero *)gHeroState)->f[0x318/4];
        tmpF2N7 = ((Hero *)gHeroState)->f[0x490/4];
        if (tmpF2N7 < tmpF1N14) {
            tmpF0N29 = tmpF2N7 + 0.10000001f;
            ((Hero *)gHeroState)->f[0x490/4] = tmpF0N29;
            if (tmpF1N14 < tmpF0N29) {
                ((Hero *)gHeroState)->f[0x490/4] = tmpF1N14;
            }
        }
        tmpF1N15 = ((Hero *)gHeroState)->f[0x88/4];
        if (tmpF1N15 < ((Hero *)gHeroState)->f[0x490/4]) {
            ((Hero *)gHeroState)->f[0x490/4] = tmpF1N15;
        }
        if ((((Hero *)gHeroState)->h[0x4AC/2] < ((Hero *)gHeroState)->i[0x1B8/4]) && (GetViewSpaceHeight((s32) (((void*)gHeroState) + 0xF0)) < 0.001f) && ((((Hero *)gHeroState)->b[0x49D] == 0) || (((Hero *)gHeroState)->i[0x1B8/4] > ((Hero *)gHeroState)->i[0x434/4])) && ((((Hero *)gHeroState)->u[0x2294/4] != 0xE) || (((Hero *)gHeroState)->i[0x1B8/4] >= 0x12))) {
            tmpF1N16 = ((Hero *)gHeroState)->f[0x458/4];
            ((Hero *)gHeroState)->b[0x49E] = 1U;
            if (tmpF1N16 != 0.0f) {
                ((Hero *)gHeroState)->f[0x520/4] = tmpF1N16;
            }
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ApplyHeroModePoseOffsets();
        }
        tmpV1N36 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((tmpV1N36 == 0x10) || (tmpV1N36 == 0xD)) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x81) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x10) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 9) {
                if (((Hero *)gHeroState)->f[0xC38/4] < 28.0f) {
                    BuildHeroRelativePoint((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    tmpV0N17 = ProcessCollisionHit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
                    if (tmpV0N17 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0x110), 7.0f);
                        for (varS0N2 = 0; varS0N2 < tmpV0N17; varS0N2++) {
                            if (IsMobyInSpecialClassRange(((s32 *)D_L08_001C3FC0)[varS0N2]) != 0) {
                                QueueImpactEffect(((s32 *)D_L08_001C3FC0)[varS0N2], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        ApplyHeroGravityAndJumpMotion();
        ProbeHeroAirborneWallContact();
        break;
    case 0x16:
        varF20N13 = GetViewSpaceVectorLength((s32)(gHeroState + 0xF0));
        varF0N12 = 0.0011111111f;
        if ((((Hero *)gHeroState)->h[0x34E/2] == 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB)) {
            varF0N12 = 0.0027777778f;
        }
        varF20N13 = varF20N13 - varF0N12;
        if (varF20N13 < 0.0f) {
            varF20N13 = 0.0f;
        }
        if (((Hero *)gHeroState)->b[0x1497] != 0) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        varS0N3 = ((void*)gHeroState) + 0xF0;
        SetViewSpaceVectorLength((s32) varS0N3, (s32) varS0N3, varF20N13);
        ApplyHeroModeTransform((s32) varS0N3, (s32) varS0N3, 0.004f);
        break;
    case 0x8C:
        qzero(D_00189F10);
        ((Hero *)gHeroState)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:
        FastVecSub((s32)((TI128*)v0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(v0[0], v0[1]);
        tmpF0N30 = vec_length_xy((s32)((TI128*)v0));
        if (tmpF0N30 > 0.2f) {
            hp32 = (Hero *)gHeroState;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(v0[0], v0[1]);
            ((Hero *)gHeroState)->f[0x1B0/4] = tmpF0N30;
            if (tmpF0N30 < D_L08_001A7DAC[0][2]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L08_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L08_001A7DAC[1][1] * 0.016666668f;
            }
            if (((Hero *)gHeroState)->b[0x22B4] == 1) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)gHeroState)->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x18AC/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        }
        speed62 = 1.0f;
        if (((Hero *)gHeroState)->b[0x22B4] == 3) {
            SteerHeroHeading(0, 0.03f, 0.3f, 0.093084246f);
        } else if (((Hero *)gHeroState)->b[0x22B4] == 1) {
            SteerHeroHeading(0, 0.03f, 0.3f, 0.13089971f);
        } else if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            SteerHeroHeading(0, 0.03f, 0.3f, 0.13089971f);
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ApplyHeroModePoseOffsets();
        }
        ApproachHeroSpeed(speed62 * 0.005f, 0.0055555557f);
        ComputeHeroPushDirection(99999.0f);
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ClipHeroVelocityAgainstWall(1);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x110, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x63:
        FastVecSub((s32)((TI128*)v0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        if (FastVecDot((s32)((TI128*)v0), (s32)(gHeroState + 0x160)) < 0.0f) {
            ClearVector128((s32)(gHeroState + 0x160));
        }
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.0075000003f);
        ClipHeroVelocityAgainstWall(0);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0x18A0)) - 0x1790, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0xF0)), 0.015000001f);
        break;
    case 0x3C:
    case 0x64:
        ClearVector128((s32)(gHeroState + 0xF0));
        break;
    case 0x65:
        ClearVector128((s32)(gHeroState + 0xF0));
        if (((f32) ((Hero *)gHeroState)->i[0x18C0/4] * 0.5f) < (((Hero *)gHeroState)->f[0x334/4] - ((Hero *)gHeroState)->f[0x88/4])) {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.004166667f;
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.016666668f;
        }
        break;
    case 0x78:
        ClearVector128((s32)(gHeroState + 0xF0));
        M2C_FIELD(((void*)(gHeroState + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x60:
    case 0x61:
        ClearVector128((s32)(gHeroState + 0xF0));
        break;
    }
    if (stack114 != ((Hero *)gHeroState)->i[0x2298/4]) {
        ((Hero *)gHeroState)->i[0x1C0/4] = 0;
    }
    if (stack118 != M2C_FIELD(tmpFp, u8* , 0x43)) {
        ((Hero *)gHeroState)->i[0x1C4/4] = 0;
    }
}

