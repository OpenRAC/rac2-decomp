/* func_L03_002BF8F0 (Endako): the hero's per-frame state handler, a 147-way switch on the
   state at 0x2294 over 45 bodies (24860 bytes, level 3 only).  One function: one prologue,
   one return.  It is func_L20_002CD928's sibling: the same code with the states 0x2E, 0x30,
   0x32-0x37, 0x65, 0x67, 0x72, 0x73, 0x78, 0x7C, 0x7F, 0x86 and 0x8D-0x94 left out (they go to
   the common tail), and without the 0x1492 and 0x22B9 branches Yeedil has in the shared
   states.  Ported from that match by renaming the per-level symbols and pruning.

   The unit's flags (config/cflags.txt) are the ones L20_002CD928 needs, minus the two for its
   state 0x7C (see its header and docs/build/compiler-notes.md): -g, -ffast-math, -frac2-zero-ti-por,
   -frac2-hazard-labels.  Dropping any of them breaks the match. */

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
extern f32 D_L03_00291DB0[];
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
extern f32 D_L03_001A7DAC[][4] MACRO_ADDR;
extern s32 D_L03_001A8FF0 MACRO_ADDR;
extern u8 D_L03_001ACEA8[];
extern s32 D_L03_001AFF00 MACRO_ADDR;
extern s32 D_L03_001B2AC8 MACRO_ADDR;
extern s32 D_L03_001B3730 MACRO_ADDR;
extern s32 D_L03_001B3738 MACRO_ADDR;
extern u8 D_L03_001B9840[];
extern u8 D_L03_001B9998[];
extern u8 D_L03_001B9C08[];
extern u8 D_L03_001C3E40[];
extern u8 D_L03_00260710[];
extern u8 D_L03_00260770[];
extern u8 D_L03_00260774[];
extern Rec2C D_L03_00262290[];
extern u8 D_L03_00262610[];
extern u8 D_L03_00266DA0[];
extern s32 func_002761F8(s32, s32, s32, s32, s32);
extern s32 func_00277F48(f32, s32, s32, s32, s32);
extern void func_0027D330(s32);
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
extern void func_L01_002B46A0(void);
extern void func_L00_002B3DC0(f32, f32, f32);
extern void func_L00_002B3EF8(s32, f32, f32, f32);
extern void func_L00_002B3F68(void);
extern void func_L00_002B41B8(f32, f32);
extern void func_L00_002B4208(f32);
extern void func_L00_002B42D8(s32);
extern void func_L00_002B4308(void);
extern void func_L00_002B54F8(f32, f32);
extern f32 func_L00_002B5590(s32);
extern void func_L01_002B6948(f32);
extern void func_L00_002B6560(void);
extern void func_L03_002BC430(void);
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
extern void func_L18_002C4000(void);
extern s32 func_L18_00428738(s32);
extern s32 func_L03_002AB5C8(s32);
extern void func_L20_002C5A48(s32);
extern void func_L00_002B4458(s32);
extern void func_L20_002D7730(s32, s32);
void func_L03_002BF8F0(void) {
    f32 speed62;
    s32 lim67;
    s32 *cnt32;
    Hero *hp32;
    f32 vec0[4] __attribute__((aligned(16)));
    f32 vec10[4] __attribute__((aligned(16)));
    f32 vec20[4] __attribute__((aligned(16)));
    f32 vec30[4] __attribute__((aligned(16)));
    f32 vec40[4] __attribute__((aligned(16)));
    f32 vec50[4] __attribute__((aligned(16)));
    f32 vec60[8] __attribute__((aligned(16)));
    f32 matrix70[16] __attribute__((aligned(16)));
    f32 vecC0[4] __attribute__((aligned(16)));
    f32 vecD0[4] __attribute__((aligned(16)));
    f32 stick_turn;
    f32 k03;
    s32 anim2F;
    s32 blend2F;
    f32 k005;
    void *pA60;
    void* ptr1;
    void* ptr2;
    f32 scalar1;
    void* ptr3;
    s32 value1;
    void* ptr4;
    s32 value2;
    s32 value3;
    void* ptr5;
    s32 value4;
    void* ptr6;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 spillFloat1;
    f32 spillFloat2;
    f32 spillFloat3;
    f32 spillFloat4;
    f32 spillFloat5;
    f32 spillFloat6;
    f32 spillFloat7;
    s32 spill1;
    f32 spillFloat8;
    s32 spill2;
    f32 spillFloat9;
    f32 spillFloat10;
    f32 spillFloat11;
    s32 spill3;
    s32 spill4;
    s32 spill5;
    f32 scalar2;
    f32 scalar3;
    f32 scalar4;
    f32 scalar5;
    f32 scalar6;
    f32 scalar7;
    f32 scalar8;
    f32 scalar9;
    f32 scalar10;
    f32 scalar11;
    f32 scalar12;
    f32 scalar13;
    f32 scalar14;
    f32 scalar15;
    f32 scalar16;
    f32 scalar17;
    f32 scalar18;
    f32 scalar19;
    f32 scalar20;
    f32 scalar21;
    f32 scalar22;
    f32 scalar23;
    f32 scalar24;
    f32 scalar25;
    f32 scalar26;
    f32 scalar27;
    f32 scalar28;
    f32 scalar29;
    f32 scalar30;
    f32 scalar31;
    f32 scalar32;
    f32 scalar33;
    f32 scalar34;
    f32 scalar35;
    f32 scalar36;
    f32 scalar37;
    f32 scalar38;
    f32 scalar39;
    f32 scalar40;
    f32 scalar41;
    f32 scalar42;
    f32 scalar43;
    f32 scalar44;
    f32 scalar45;
    f32 scalar46;
    f32 scalar47;
    f32 scalar48;
    f32 scalar49;
    f32 scalar50;
    f32 scalar51;
    f32 scalar52;
    f32 scalar53;
    f32 scalar54;
    f32 scalar55;
    f32 scalar56;
    f32 scalar57;
    f32 scalar58;
    f32 scalar59;
    f32 scalar60;
    f32 scalar61;
    f32 scalar62;
    f32 scalar63;
    f32 scalar64;
    f32 scalar65;
    f32 scalar66;
    f32 scalar67;
    f32 scalar68;
    f32 scalar69;
    f32 scalar70;
    f32 scalar71;
    f32 scalar72;
    f32 scalar73;
    f32 scalar74;
    f32 scalar75;
    f32 scalar76;
    f32 scalar77;
    f32 scalar78;
    f32 scalar79;
    f32 scalar80;
    f32 scalar81;
    f32 scalar82;
    f32 scalar83;
    f32 scalar84;
    f32 scalar85;
    f32 scalar86;
    f32 scalar87;
    f32 scalar88;
    f32 scalar89;
    f32 scalar90;
    f32 scalar91;
    f32 scalar92;
    f32 scalar93;
    f32 scalar94;
    f32 scalar95;
    f32 scalar96;
    f32 scalar97;
    f32 scalar98;
    f32 scalar99;
    f32 scalar100;
    f32 scalar101;
    f32 scalar102;
    f32 scalar103;
    f32 scalar104;
    f32 scalar105;
    f32 scalar106;
    f32 scalar107;
    f32 scalar108;
    f32 scalar109;
    f32 scalar110;
    f32 scalar111;
    f32 scalar112;
    f32 scalar113;
    f32 scalar114;
    f32 scalar115;
    f32 scalar116;
    f32 scalar117;
    f32 scalar118;
    f32 scalar119;
    f32 scalar120;
    f32 scalar121;
    f32 scalar122;
    f32 scalar123;
    f32 scalar124;
    f32 scalar125;
    f32 scalar126;
    f32 scalar127;
    f32 scalar128;
    f32 scalar129;
    f32 scalar130;
    f32 scalar131;
    f32 scalar132;
    f32 scalar133;
    f32 scalar134;
    f32 scalar135;
    f32 scalar136;
    f32 scalar137;
    f32 scalar138;
    f32 scalar139;
    f32 scalar140;
    f32 scalar141;
    f32 scalar142;
    f32 scalar143;
    f32 scalar144;
    f32 scalar145;
    f32 scalar146;
    f32 scalar147;
    f32 scalar148;
    f32 scalar149;
    f32 scalar150;
    f32 scalar151;
    f32 scalar152;
    f32 scalar153;
    f32 scalar154;
    f32 scalar155;
    f32 scalar156;
    f32 scalar157;
    f32 scalar158;
    s16 value5;
    s32 value6;
    s16 value7;
    s32 value8;
    s32 value9;
    s32 value10;
    s32 value11;
    s32 value12;
    s32 value13;
    s32 value14;
    s32 value15;
    s32 value16;
    s32 value17;
    s32 value18;
    s32 value19;
    s32 value20;
    s32 value21;
    s32 value22;
    s32 value23;
    s32 value24;
    s32 value25;
    s32 value26;
    s32 value27;
    s32 value28;
    s32 value29;
    s32 value30;
    s32 value31;
    s32 value32;
    s32 value33;
    s32 value34;
    s32 value35;
    s32 value36;
    s32 value37;
    s32 value38;
    s32 value39;
    s32 value40;
    s32 value41;
    s32 value42;
    s32 value43;
    s32 value44;
    s32 value45;
    s32 value46;
    s32 value47;
    s32 value48;
    s32 value49;
    s32 value50;
    s32 value51;
    s32 value52;
    s32 value53;
    s32 value54;
    s32 value55;
    s32 value56;
    s32 value57;
    s32 value58;
    s32 value59;
    s32 value60;
    s32 value61;
    s32 value62;
    s32 value63;
    s32 value64;
    s32 value65;
    s32 value66;
    s32 value67;
    s32 value68;
    s32 value69;
    s32 value70;
    s32 value71;
    s32 value72;
    s32 value73;
    s32 value74;
    s32 value75;
    s32 value76;
    s32 value77;
    s32 value78;
    s32 value79;
    s32 value80;
    s32* ptr7;
    s32* ptr8;
    u16 value81;
    u16 value82;
    u16 value83;
    u32 value84;
    u32 value85;
    u32 value86;
    u32 value87;
    u32 value88;
    u32 value89;
    u32 value90;
    u32 value91;
    u32 value92;
    u32 value93;
    u32 value94;
    u32 value95;
    u8 value96;
    u8 value97;
    u8 value98;
    u8 value99;
    void* ptr9;
    void* ptr10;
    void* ptr11;
    void* ptr12;
    void* ptr13;
    void* ptr14;
    void* ptr15;
    void* ptr16;
    void* ptr17;
    void* ptr18;
    void* ptr19;
    void* ptr20;
    void* ptr21;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* ptr22;
    void* ptr23;
    void* ptr24;
    void* ptr25;
    void* ptr26;
    void* ptr27;
    void* ptr28;
    void* ptr29;
    void* ptr30;
    void* ptr31;
    void* ptr32;
    void* ptr33;
    void* ptr34;
    void* ptr35;
    void* ptr36;
    void* ptr37;
    void* ptr38;
    void* ptr39;
    void* ptr40;
    void* ptr41;
    void* ptr42;
    void* ptr43;
    void* ptr44;
    void* ptr45;
    void* ptr46;
    void* ptr47;
    void* ptr48;
    void* ptr49;
    void* ptr50;
    void* ptr51;
    void* ptr52;
    void* ptr53;
    void* ptr54;
    void* ptr55;
    void* ptr56;
    void* ptr57;
    void* ptr58;
    void* ptr59;
    void* ptr60;
    void* ptr61;

    spill3 = ((Hero *)gHeroState)->i[0x2298/4];
    ptr21 = ((Hero *)gHeroState)->ptr[0x2290/4];
    spill4 = (s32) M2C_FIELD(ptr21, u8* , 0x43);
    switch (((Hero *)gHeroState)->u[0x2294/4]) {                              /* switch 1 */
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
        BuildHeroMoveImpulse(0.5f, 0.033333335f);
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ResolveStickInputToDirection(1.0f, 0);
        value85 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value85 == 1) || (value85 == 0x1D)) {
            if (((Hero *)gHeroState)->b[0x22B5] != 0) {
                (*(TI128*)vec0) = 0;
                vec0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)gHeroState) + 0x190), (s32)((TI128*)vec0), (s32)&D_L03_001B9998[0x218]);
                ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)D_L03_001B9998)->f[0];
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
            if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) || (value97 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43), (value97 == 0xE)) || (value97 == 0xF)) {
                if (((Hero *)gHeroState)->u[0x2294/4] == 4) {
                    SteerHeroHeading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) > 0.0058177654f) {
                    value11 = ((Hero *)gHeroState)->f[0x1A4/4] < 0.0f;
                    value11 += 0xE;
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) != value11) {
                        set_hero_animation(value11, 0, 5.0f);
                    }
                    scalar2 = FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)gHeroState)->f[0xC20/4] = scalar2;
                    if (scalar2 < 0.55f) {
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
            value94 = ((Hero *)gHeroState)->u[0x2294/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            if (value94 == 3) {
                scalar105 = ((Hero *)gHeroState)->f[0x17C/4] + 1.0f;
                if (scalar105 > 1.0f) {
                    scalar105 = 1.0f;
                }
                ptr16 = ((Hero *)gHeroState)->ptr[0x2290/4];
                scalar131 = scalar105 * 0.0075000003f;
                ((Hero *)gHeroState)->f[0x24AC/4] = scalar131;
                if (M2C_FIELD(ptr16, u8* , 0x42) == M2C_FIELD(ptr16, u8* , 0x43)) {
                    scalar126 = ((Hero *)gHeroState)->f[0x174/4] / scalar131;
                    if ((scalar126 > 5.0f) && ((f32) M2C_FIELD(ptr16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, scalar126, 0.5f, -1.0f);
                        if (((Hero *)gHeroState)->f[0xC20/4] > 1.1f) {
                            ((Hero *)gHeroState)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (value94 == 4) {
                scalar131 = 0.0075000003f;
            } else {
                scalar131 = 0.004916667f;
            }
            ApproachHeroSpeed(0.0f, scalar131);
            ClearVector128((s32)(gHeroState + 0xF0));
            ShrinkHeroVectorByAmount(scalar131);
            if ((((Hero *)gHeroState)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                value57 = (s32)(gHeroState + 0xF0);
                if (((Hero *)gHeroState)->f[0x31C/4] > 0.2f) {
                    ApplyHeroModeTransform(value57, value57 + 0x30, 0.0061111115f);
                } else {
                    ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.015000001f);
                    if (((Hero *)gHeroState)->i[0x33C/4] != 0) {
                        qcopy(&((Hero *)gHeroState)->q[0x80/16], &((Hero *)gHeroState)->q[0x2D0/16]);
                        ((Hero *)gHeroState)->f[0x31C/4] = 0.0f;
                        ((Hero *)gHeroState)->h[0x34E/2] = 0;
                    }
                }
            } else {
                DeflectHeroOffSteepSurface(0);
                if (((Hero *)gHeroState)->h[0x34E/2] == 0) {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
                } else {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
                    CancelHeroVelocityIntoWall();
                }
            }
        break;
    case 0x85:                                      /* switch 1 */
        ptr19 = ((Hero *)gHeroState)->ptr[0x1830/4];
        qcopy(&((Hero *)gHeroState)->q[0x80/16], (u8 *)ptr19 + 0x10);
        qcopy(&((Hero *)gHeroState)->q[0x90/16], (u8 *)ptr19 + 0xF0);
        break;
    case 0x2F:                                      /* switch 1 */
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
            ptr50 = ((Hero *)gHeroState)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr50, u8* , 0x60) & 2) && (M2C_FIELD(ptr50, u8* , 0x42) == 0x36)) {
                set_hero_animation(GetHeroGadgetValue(0), 0, 5.0f);
            }
        }
        break;
    case 0x8A:                                      /* switch 1 */
    case 0x8B:                                      /* switch 1 */
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
        ptr61 = ((Hero *)gHeroState)->ptr[0xB10/4];
        if (ptr61 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(ptr61, f32* , 0x10) - M2C_FIELD(ptr21, f32* , 0x10), M2C_FIELD(ptr61, f32* , 0x14) - M2C_FIELD(ptr21, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x23:                                      /* switch 1 */
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
        ptr1 = ((Hero *)gHeroState)->ptr[0xAA4/4];
        if (ptr1 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(ptr1, f32* , 0x10) - M2C_FIELD(ptr21, f32* , 0x10), M2C_FIELD(ptr1, f32* , 0x14) - M2C_FIELD(ptr21, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vec0, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        scalar26 = fast_vec_dist((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)vec0));
        ((Hero *)gHeroState)->f[0xAB0/4] = scalar26;
        ((Hero *)gHeroState)->f[0xAAC/4] = 60.0f;
        if (((Hero *)gHeroState)->f[0xAA0/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xAAC/4] = (f32) (scalar26 / ((Hero *)gHeroState)->f[0x170/4]);
        }
        value38 = ((Hero *)gHeroState)->i[0x2298/4];
        if (value38 == 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.45000002f, 0.022222223f);
            ptr46 = ((Hero *)gHeroState)->ptr[0xAA4/4];
            scalar136 = FastMatrixHelperA(M2C_FIELD(ptr46, f32* , 0x10) - M2C_FIELD(ptr21, f32* , 0x10), M2C_FIELD(ptr46, f32* , 0x14) - M2C_FIELD(ptr21, f32* , 0x14));
            if (((Hero *)gHeroState)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], scalar136) > 1.5707964f) {
                    scalar136 = FastAddRotations(scalar136, 3.1415927f);
                }
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = scalar136;
            SteerHeroHeading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (value38 == 1) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((SolveQuadratic((s32) &spillFloat3, (s32) &spillFloat4, -0.0058333334f, ((Hero *)gHeroState)->f[0xAA0/4], 1.9f - ((Hero *)gHeroState)->f[0xAB0/4]) > 0) && (spillFloat3 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xAAC/4] = spillFloat3;
            ((Hero *)gHeroState)->i[0x2298/4] = 1;
        }
        ((Hero *)gHeroState)->h[0x226/2] = 3;
        if (((Hero *)gHeroState)->f[0xAAC/4] < 20.0f) {
            ((Hero *)gHeroState)->i[0xAB4/4] = 1;
        }
        if (((Hero *)gHeroState)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turn24 = FastAddRotations(-FastMatrixHelperA(vec_distance_xy((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)vec0)), vec0[2] - ((Hero *)gHeroState)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, turn24, 0.10762865f);
        }
        vec20[0] = FastSinOrCosA(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        scalar27 = FastSinOrCosB(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        vec20[2] = 0;
        vec20[1] = scalar27;
        FastVecAdd((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((void*)gHeroState) + 0x80));
        FastVecSub((s32) ((TI128*)vec10), (s32) (((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vec20));
        vec_scale_to_length((s32) (((void*)gHeroState) + 0xF0), (s32) ((TI128*)vec10), ((Hero *)gHeroState)->f[0xAA0/4]);
        scalar28 = ((Hero *)gHeroState)->f[0xAAC/4];
        if (scalar28 < 30.0f) {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - ((30.0f - scalar28) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(gHeroState + 0xABC), ((Hero *)gHeroState)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x110/16]);
        FastVecScale((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.9f);
        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.004166667f);
        qcopy(vec0, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        ((Hero *)gHeroState)->f[0xAB0/4] = fast_vec_dist((s32)(gHeroState + 0x80), (s32)((TI128*)vec0));
        FastVecAdd((s32) ((TI128*)vec10), (s32)(gHeroState + 0x80), (s32)(gHeroState + 0xF0));
        FastVecSub((s32) ((TI128*)vec30), (s32) ((TI128*)vec10), (s32)((TI128*)vec0));
        vec_scale_to_length((s32) ((TI128*)vec30), (s32) ((TI128*)vec30), ((Hero *)gHeroState)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vec20), (s32)((TI128*)vec0), (s32) ((TI128*)vec30));
        FastVecSub((s32)(gHeroState + 0xF0), (s32) ((TI128*)vec20), (s32)(gHeroState + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC28/4] & 2) && (M2C_FIELD(ptr21, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)gHeroState)->f[0xC20/4] = 0.3f;
        }
        ptr51 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        scalar81 = ((Hero *)gHeroState)->f[0xF8/4];
        if (ptr51 != 0) {
            ptr47 = M2C_FIELD(ptr51, void** , 0x68);
            if ((ptr47 != 0) && (M2C_FIELD(ptr47, s32* , 0x34) != 0)) {
                scalar137 = M2C_FIELD(ptr51, f32* , 0xF8);
                if (FastDiffRots(scalar137, ((Hero *)gHeroState)->f[0x98/4]) > 90.0f) {
                    scalar137 = FastAddRotations(scalar137, 3.1415927f);
                }
                ApproachWithVelocity((s32) (((void*)gHeroState) + 0xAEC), scalar137, (s32) (((void*)gHeroState) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xAEC/4];
        SteerHeroHeading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vec0), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) (((void*)gHeroState) + 0x80));
        vec_scale_to_length((s32)((TI128*)vec0), (s32)((TI128*)vec0), 1.0f);
        if (vec0[2] < 0.23f) {
            vec0[2] = 0.23f;
        }
        ClearVector128((s32) ((TI128*)vec20));
        vec20[2] = ((Hero *)gHeroState)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vec40), (s32) ((TI128*)vec20));
        matrix_from_basis_rows((s32) ((TI128*)matrix70), (s32) ((TI128*)vec40));
        transform_vector((s32)((TI128*)vec0), (s32)((TI128*)vec0), (s32) ((TI128*)matrix70));
        vec10[0] = -FastMatrixHelperA(square_root((vec0[0] * vec0[0]) + (vec0[2] * vec0[2])), vec0[1]);
        scalar29 = FastMatrixHelperA(vec0[2], vec0[0]);
        vec10[1] = scalar29;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), scalar29, (s32) (((void*)gHeroState) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), vec10[0], (s32) (((void*)gHeroState) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        value69 = ((Hero *)gHeroState)->f[0x88/4] < M2C_FIELD(((Hero *)gHeroState)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
            if ((value69 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0x29) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.25f)) {
                ResolveStickInputToDirection(1.0f, 0);
                scalar138 = ((Hero *)gHeroState)->f[0x24B8/4] * 0.0035f;
                if (scalar138 > 0.083333336f) {
                    scalar138 = 0.083333336f;
                }
                vec30[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0x1A0/4]) * scalar138;
                scalar30 = FastSinOrCosB(((Hero *)gHeroState)->f[0x1A0/4]) * scalar138;
                ptr9 = ((void*)gHeroState) + 0xF0;
                (*(s32*)&vec30[2]) = 0;
                vec30[1] = scalar30;
                FastVecAdd((s32) ptr9, (s32) ptr9, (s32) ((TI128*)vec30));
            }
            if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
                ptr38 = ((void*)gHeroState) + 0x80;
                if ((vec_distance_xy((s32) ptr38, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10)) < (((Hero *)gHeroState)->f[0xAE0/4] * 1.57f)) || (((Hero *)gHeroState)->f[0x31C/4] > 1.5f)) {
                    ptr30 = ((void*)gHeroState) + 0xF0;
                    ApplyHeroModeTransform((s32) ptr30, (s32) (((void*)gHeroState) + 0x110), 0.011111111f);
                    if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (GetViewSpaceHeight((s32) ptr30) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vec30), (s32) ptr38, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
                        ApplyHeroModeTransform((s32) ptr30, (s32) ptr30, 0.015833333f);
                    }
                }
                scalar68 = FastVecLength((s32)(gHeroState + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vec30), (s32)(gHeroState + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vec30), (s32) ((TI128*)vec30), scalar68);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)vec30));
            }
        }
        ptr48 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        if (ptr48 != 0) {
            ptr22 = M2C_FIELD(ptr48, void** , 0x68);
            ptr31 = ((void*)gHeroState) + 0xF0;
            if (ptr22 != 0) {
                scalar31 = FastVecLength((s32) ptr31);
                scalar32 = M2C_FIELD(ptr22, f32* , 0xC);
                spillFloat5 = scalar31;
                if (scalar32 < scalar31) {
                    ApproachValue((s32) &spillFloat5, scalar32, 0.004166667f);
                    vec_scale_to_length((s32) ptr31, (s32) ptr31, spillFloat5);
                }
            }
        }
        scalar3 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f);
        ptr44 = ((void*)gHeroState) + 0x80;
        ptr43 = ((void*)gHeroState) + 0xF0;
        vecD0[0] = FastSinOrCosA(scalar3) * 0.15f;
        scalar4 = FastSinOrCosB(scalar3) * 0.15f;
        (*(s32*)&vecD0[2]) = 0;
        vecD0[1] = scalar4;
        FastVecAdd((s32) &vecD0[0], (s32) &vecD0[0], (s32) ptr44);
        FastVecAdd((s32) ((TI128*)vec30), (s32) &vecD0[0], (s32) ptr43);
        FastVecSub((s32) ((TI128*)vecC0), (s32) ((TI128*)vec30), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vecC0), (s32) ((TI128*)vecC0), ((Hero *)gHeroState)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vec30), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vecC0));
        FastVecSub((s32) ptr43, (s32) ((TI128*)vec30), (s32) &vecD0[0]);
        scalar69 = ((Hero *)gHeroState)->f[0xAE4/4];
        SpringFloatToGoal((s32) (((void*)gHeroState) + 0xAE4), (s32) (((void*)gHeroState) + 0xAE8), ((Hero *)gHeroState)->f[0xAE0/4], ((Hero *)gHeroState)->f[0xB04/4], ((Hero *)gHeroState)->f[0xB08/4], ((Hero *)gHeroState)->f[0xB0C/4]);
        scalar70 = ((Hero *)gHeroState)->f[0xAE4/4] - scalar69;
        if (((Hero *)gHeroState)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vecC0))) {
            vec_scale_to_length((s32) ((TI128*)vecC0), (s32) ((TI128*)vecC0), scalar70);
            FastVecAdd((s32) ptr44, (s32) ptr44, (s32) ((TI128*)vecC0));
        }
        if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (value69 != 0)) {
            min2B = 0.23333335f;
            scalar5 = vec_length_xy((s32) ptr43);
            spillFloat6 = scalar5;
            if (scalar5 < min2B) {
                SpringFloatToGoal((s32) &spillFloat6, (s32) (((void*)gHeroState) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vec30[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0xAEC/4]) * ((Hero *)gHeroState)->f[0xAF4/4];
                scalar6 = FastSinOrCosB(((Hero *)gHeroState)->f[0xAEC/4]);
                vec30[2] = 0.0f;
                vec30[1] = scalar6 * ((Hero *)gHeroState)->f[0xAF4/4];
                FastVecAdd((s32) ptr43, (s32) ptr43, (s32) ((TI128*)vec30));
            }
        }
        if ((((Hero *)gHeroState)->h[0xADC/2] != 0) && (((Hero *)gHeroState)->h[0x34E/2] != 0) && (((scalar81 < 0.0f) && (((Hero *)gHeroState)->f[0xF8/4] > 0.0f)) || (((Hero *)gHeroState)->h[0xAFC/2] != 0))) {
            ((Hero *)gHeroState)->h[0xAFE/2] = 0;
            scalar71 = square_root(((Hero *)gHeroState)->f[0xAE0/4] / ((Hero *)gHeroState)->f[0xAF0/4]) * 3.1415927f;
            value7 = ((Hero *)gHeroState)->h[0xAFC/2];
            if (value7 != 0) {
                value72 = value7 == 1;
            } else {
                (*(TI128*)vec30) = ((Hero *)gHeroState)->q[0x110/16];
                value72 = GetSpeedAlongHeroForward((s32) ((TI128*)vec30)) > 0.0f;
            }
            if (value72 != 0) {
                if (M2C_FIELD(ptr21, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 1;
                } else {
                    ptr49 = ((Hero *)gHeroState)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr49, u8* , 0x42) == M2C_FIELD(ptr49, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, scalar71, 0.5f, -1.0f);
                        ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(ptr21, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)gHeroState)->h[0xAFC/2] = 2;
            } else {
                ptr45 = ((Hero *)gHeroState)->ptr[0x2290/4];
                if (M2C_FIELD(ptr45, u8* , 0x42) == M2C_FIELD(ptr45, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, scalar71, 0.5f, -1.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L03_00262290[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        value67 = 0;
        if ((((Hero *)gHeroState)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->f[0x31C/4] > 4.0f)) {
            value67 = 1;
        }
        value17 = ((Hero *)gHeroState)->i[0xBE4/4];
        if (value17 != 0) {
            FastVecSub((s32)((TI128*)vec0), value17 + 0x10, (s32) (((void*)gHeroState) + 0x80));
            scalar7 = GetViewSpaceVectorLength((s32)((TI128*)vec0));
            if (((scalar7 > 2.0f) && (scalar7 < 5.0f)) || (value67 != 0)) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
            }
            ApproachHeroSpeed(0.0069444445f, 0.0069444445f);
            vec_scale_to_length((s32) ((TI128*)vec10), (s32)gHeroState, ((Hero *)gHeroState)->f[0x1B4/4]);
            SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
            FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)vec10));
        } else {
            if ((value67 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 0x46)) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
            }
            ApproachHeroSpeed(0.004166667f, 0.004166667f);
            SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), ((Hero *)gHeroState)->f[0x1B4/4]);
        }
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
            ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0xBEC/4];
            qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)gHeroState)->f[0xC38/4] < 25.0f) {
            SelectHeroAimTarget(8.0f, 1.0471977f, 1.0471977f);
        }
        scalar52 = ((Hero *)gHeroState)->f[0x31C/4];
        scalar144 = 0.12833333f;
        if (scalar52 > 2.25f) {
            scalar144 = 0.064166665f;
        } else if (scalar52 > 1.8f) {
            scalar144 = 0.08983333f;
        }
        if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 23.5f) && (((Hero *)gHeroState)->f[0x118/4] < 0.0f) && (((Hero *)gHeroState)->h[0x34E/2] != 0)) {
            qcopy(vec0, &((Hero *)gHeroState)->q[0x80/16]);
            ApplyHeroModeTransformReversed((s32)((TI128*)vec0), (s32)((TI128*)vec0), -0.5f);
            vec_scale_to_length((s32) &vec40[0], (s32)gHeroState, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vec10), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vec40[0]);
            vec10[3] = 5627.925f;
            (*(u8*)((u8*)vec20+9)) = 1;
            (*(u16*)((u8*)vec20+10)) = 0x47;
            (*(u8*)((u8*)vec20+8)) = 0;
            ProcessCollisionHit(0.4f, (s32)((TI128*)vec0), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)vec10));
        }
        if (IsBelowPlaneWithinDepth(25.7f) != 0) {
            QueueRecordsByIndex(0x19);
            ((Hero *)gHeroState)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L03_001B9840)->f[0x180/4] = 0.1f;
                ((Hero *)D_L03_001B9840)->i[0x188/4] = 0x1E;
                ((Hero *)gHeroState)->h[0x224/2] = 0x23;
                ((Hero *)D_L03_001B9840)->i[0x16C/4] = 0;
            }
        }
        value39 = ((Hero *)gHeroState)->i[0x1B8/4];
        lim3 = 0xE;
        if (value39 < 9) {
            ptr23 = ((void*)gHeroState) + 0xF0;
            spillFloat7 = GetViewSpaceHeight((s32) ptr23);
            ApproachValue((s32) &spillFloat7, scalar144, 0.041666668f);
            SetViewSpaceHeight((s32) ptr23, (s32) ptr23, spillFloat7);
        } else if (value39 > lim3) {
            ptr32 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) ptr32, (s32) ptr32, 0.036111113f);
            if (GetViewSpaceHeight((s32) ptr32) < 0.0f) {
                ((Hero *)gHeroState)->f[0xC00/4] = 1.0f;
            }
            scalar139 = -0.6166667f;
            if (D_L03_001A8FF0 != 0) {
                scalar139 = -1.1666667f;
            }
            if (GetViewSpaceHeight((s32) ptr32) < scalar139) {
                SetViewSpaceHeight((s32) ptr32, (s32) ptr32, scalar139);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L03_00262290[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        value60 = (((Hero *)gHeroState)->i[0x22A0/4] == 1) && (((Hero *)gHeroState)->i[0x22A8/4] >= 0x15);
        if (value60 == 0) {
            if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
                value68 = 0;
                if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                    ptr24 = ((void*)gHeroState) + 0xBC0;
                    scalar140 = GetDirectionAngleDelta((s32) ptr24, 0);
                    scalar98 = GetDirectionAngleDelta((s32) ptr24, 1);
                } else {
                    scalar140 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                    scalar98 = GetShortestAngleDelta(1, ((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                }
                if (scalar98 < 4.3633237f) {
                    value68 = 1;
                }
                if (scalar140 > 0.0f) {
                    ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (scalar98 + 1.0f));
                }
                ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
                qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
                if (value68 != 0) {
                    SteerHeroHeading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    SteerHeroHeading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    value61 = 1;
                    if ((((Hero *)gHeroState)->u[0x2294/4] == 0x83) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xC)) {
                        value61 = 0;
                    } else if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 6.0f)) {
                        value61 = 0;
                    }
                    if (value61 != 0) {
                        if (((Hero *)gHeroState)->u[0x2294/4] == 0x15) {
                            SelectHeroAimTarget(14.0f, 0.52359885f, 0.78539824f);
                        } else {
                            UpdateHeroAimTarget(64.0f, 0.17453295f, 0.3490659f);
                        }
                    }
                }
        }
        if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) == 0x1A) && (IsBelowPlaneWithinDepth(33.0f) != 0)) {
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x15) {
                SetupHeroAttachedObjectTransform();
            }
        }
        ApproachHeroSpeed(0.010277778f, 0.007777778f);
        ComputeHeroPushDirection(99999.0f);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
        } else {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L03_00262290[((Hero *)gHeroState)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        value18 = ((Hero *)gHeroState)->i[0xBE4/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ptr39 = (((Hero *)gHeroState)->h[0xBFC/2] * 0x2C) + (s32)D_L03_00262290;
        if ((value18 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 4)) {
            ptr33 = ((void*)gHeroState) + 0x80;
            scalar108 = vec_distance_xy(value18 + 0x10, (s32) ptr33);
            if ((*(s32*)&D_L03_001A8FF0) != 0) {
                scalar108 = fast_vec_dist(((Hero *)gHeroState)->i[0xBE4/4] + 0x10, (s32) ptr33);
            }
            scalar108 = scalar108 - 0.5f;
            if (scalar108 < 0.0f) {
                scalar108 = 0.0f;
            }
            value40 = M2C_FIELD(ptr39, s32* , 4);
            if (value40 == 0) {
                scalar99 = 0.75f;
                scalar146 = 0.8f;
                scalar151 = 4.0f;
            } else if (value40 == 1) {
                scalar99 = 0.6f;
                scalar146 = 1.7f;
                scalar151 = 4.0f;
            } else {
                scalar99 = 1.3f;
                scalar146 = 1.7f;
                scalar151 = 1.9f;
            }
            scalar73 = scalar108 - scalar99;
            if (FloatAbs(scalar73) < (scalar146 + 3.0f)) {
                scalar110 = scalar73 * 1.1111112f;
                if (scalar151 < scalar110) {
                    scalar110 = scalar151;
                }
                if (scalar110 > 1.0f) {
                    ((Hero *)gHeroState)->f[0xBF4/4] = scalar110;
                }
            }
        }
        value41 = M2C_FIELD(ptr39, s32* , 4);
        switch (value41) {
        case 0:
            if (((Hero *)gHeroState)->f[0xC38/4] < 18.0f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            scalar53 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (scalar53 < 9.0f)) {
                if (scalar53 > 8.0f) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.050000004f;
                } else if (scalar53 > 7.0f) {
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
            scalar100 = GetDirectionAngleDelta((s32)(gHeroState + 0xBC0), 0);
        } else {
            scalar100 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
        }
        scalar54 = FloatAbs(scalar100);
        if ((M2C_FIELD(ptr39, s32* , 4) == 1) && (scalar100 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (scalar54 + 1.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
        qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        value79 = 1;
        if ((M2C_FIELD(ptr39, s32* , 4) == 1) && (((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 7.0f)) {
            value79 = 0;
        }
        if (value79 != 0) {
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
            ptr11 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) ptr11, (s32) ptr11, 0.015000001f);
        }
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
            break;
    case 0x77:                                      /* switch 1 */
        ApproachValue((s32)(gHeroState + 0x1B4), 0.0f, 0.006666667f);
        if ((*(s32*)&D_L03_001A8FF0) != 0) {
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
    case 0x1F:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
            ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0xBEC/4];
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else if (((Hero *)gHeroState)->i[0x1B8/4] < 4) {
            SelectHeroAimTarget(11.0f, 0.8726647f, -1.0f);
        }
        lim = 0xA;
        lim2 = 0x12;
        value42 = ((Hero *)gHeroState)->i[0x1B8/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (value42 > lim) {
            if (value42 < 0x12) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)gHeroState)->i[0x1B8/4] == 8) && (((Hero *)gHeroState)->f[0x184/4] < 0.33333334f)) {
            ptr25 = ((void*)gHeroState) + 0x18E0;
            InitPendingSlot((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ptr25);
            AppendRecordToFourEntryTable((s32) ptr25, 0x30, 2, 0.0f);
            AppendRecordToFourEntryTable((s32) ptr25, 0x17, 4, 0.0f);
            AppendRecordToFourEntryTable((s32) ptr25, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)gHeroState)->i[0x1B8/4] > lim2) ? 5 : 0;
        UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), sel1F);
        if (((Hero *)gHeroState)->i[0x1B8/4] > lim) {
            ApproachHeroSpeed(0.05277778f, 0.025f);
        }
        if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
            ComputeHeroPushDirection(((Hero *)gHeroState)->f[0xBEC/4]);
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x1F) {
            value44 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((value44 > lim) && (value44 < 0x16)) {
                ptr40 = ((Hero *)gHeroState)->ptr[0x1220/4];
                if (ptr40 != 0) {
                    ptr34 = ((void*)gHeroState) + 0x80;
                    vec30[0] = 2.0f * FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]);
                    vec30[1] = 2.0f * FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]);
                    vec30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vec0), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vec30));
                    (*(u8*)((u8*)vec10+9)) = 3;
                    vec0[3] = 5627.925f;
                    (*(u8*)((u8*)vec10+8)) = 0;
                    scalar79 = ((Hero *)gHeroState)->f[0x98/4];
                    (*(u16*)((u8*)vec10+10)) = M2C_FIELD(ptr40, u16* , 0xAA);
                    vec40[0] = FastSinOrCosA(scalar79) * 0.8f;
                    scalar8 = FastSinOrCosB(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar8;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr34);
                    EmitEffectsAtNearbyObjects((s32) ptr40, ProcessCollisionHit(0.8f, (s32) &vec40[0], 0, (s32) ptr40, (s32)((TI128*)vec0)));
                    scalar79 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -0.8726647f);
                    vec40[0] = FastSinOrCosA(scalar79) * 0.8f;
                    scalar10 = FastSinOrCosB(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar10;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr34);
                    EmitEffectsAtNearbyObjects((s32) ptr40, ProcessCollisionHit(0.8f, (s32) &vec40[0], 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)vec0)));
                    scalar79 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 0.8726647f);
                    vec40[0] = FastSinOrCosA(scalar79) * 0.8f;
                    scalar12 = FastSinOrCosB(scalar79) * 0.8f;
                    vec40[2] = 0.55f;
                    vec40[1] = scalar12;
                    FastVecAdd((s32) &vec40[0], (s32) &vec40[0], (s32) ptr34);
                    EmitEffectsAtNearbyObjects((s32) ptr40, ProcessCollisionHit(0.8f, (s32) &vec40[0], 0, (s32) ptr40, (s32)((TI128*)vec0)));
                }
            }
        }
        if (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        DeflectHeroOffSteepSurface(1);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x120, 0.0061111115f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x22:                                      /* switch 1 */
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
    case 0x2:                                       /* switch 1 */
    case 0x70:                                      /* switch 1 */
        if (((Hero *)gHeroState)->h[0x1454/2] == 0) {
            if (((Hero *)gHeroState)->f[0x174/4] < 0.028333336f) {
                ((Hero *)gHeroState)->b[0x40C] = 1U;
                if ((FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 2.0943954f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
                    ((Hero *)gHeroState)->b[0x40F] = 1U;
                }
            }
            scalar74 = ReadPadFloatHistory(1);
            if ((FastDiffRots(scalar74, ReadPadFloatHistory(7)) > 1.9198624f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
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
            RefreshHeroSpeedFromTimer();
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
            (*(TI128*)vec0) = ((Hero *)gHeroState)->q[0xA60/16];
            scalar55 = ((Hero *)gHeroState)->f[0x1B0/4] + GetSpeedAlongHeroForward((s32)((TI128*)vec0));
            ((Hero *)gHeroState)->f[0x1B0/4] = scalar55;
            if (scalar55 < 0.011666667f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.011666667f;
            }
            ClearVector128((s32) pA60);
        }
        scalar141 = 1.0f;
        if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
            UpdateHeroTurnFromAnimation();
        } else {
            ((Hero *)gHeroState)->f[0x1458/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
            qcopy(&((Hero *)gHeroState)->q[0x1440/16], &((Hero *)gHeroState)->q[0x0/16]);
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (((Hero *)gHeroState)->b[0x40F] == 0) && (((Hero *)gHeroState)->b[0x22BA] == 0)) {
                SteerHeroHeading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                scalar83 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
                if (((((Hero *)gHeroState)->f[0x24B8/4] < 0.9f) || ((((Hero *)gHeroState)->b[0x22BA] != 0) && (((Hero *)gHeroState)->b[0x40F] == 0))) && (scalar83 > 0.78539824f)) {
                    scalar141 = 0.0f;
                }
                SetHeroTurnRates();
            }
        }
        ApplyHeroModePoseOffsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar155 = 0.09916667f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.029178405f);
            if (scalar155 < 0.0f) {
                scalar155 = 0.0f;
            }
            if (scalar155 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = scalar155;
            }
        }
        k005 = scalar141 * 0.005f;
        scalar142 = 0.0055555557f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar127 = 2.617994f - ((Hero *)gHeroState)->f[0x1A8/4];
            if (scalar127 > 1.0f) {
                scalar127 = 1.0f;
            }
            if (scalar127 < 0.2f) {
                scalar127 = 0.2f;
            }
            scalar142 = 0.004722222f;
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * scalar127);
        }
        scalar84 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
        if ((((Hero *)gHeroState)->f[0x24B8/4] < 0.75f) && (scalar84 > 0.6108653f)) {
            scalar128 = 1.0f - (scalar84 * 0.4f);
            if (scalar128 < 0.0f) {
                scalar128 = 0.0f;
            }
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * scalar128);
        }
        ApproachHeroSpeed(k005, scalar142);
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
        DeflectHeroOffSteepSurface(1);
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
    case 0x7B:                                      /* switch 1 */
        UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        ResolveStickInputToDirection(1.0f, 0);
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.19166668f;
        ClampStickToUnitRange((s32)((TI128*)vec0), (s32) (((void*)gHeroState) + 0x9F0), 0.17f);
        scalar147 = (((Hero *)gHeroState)->f[0x24B8/4] * 0.020362178f) * vec0[0];
        if ((*(s32*)&D_L03_001A8FF0) == 0) {
            if (((Hero *)gHeroState)->i[0x1B8/4] < 0x3C) {
                scalar147 *= 0.1f;
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            RotateHeroMatrix(0.0f, 0.0f, scalar147);
        }
        ApproachHeroSpeed(0.027777778f, 0.004166667f);
        ComputeHeroPushDirection(99999.0f);
        if ((*(s32*)&D_L03_001A8FF0) != 0) {
            qcopy(vec10, &((Hero *)gHeroState)->q[0x2D0/16]);
            ApplyHeroModeTransformReversed((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), 0.17f);
            SpringVectorToTarget((s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vec10), (s32) (((void*)gHeroState) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            SpringFloatToGoal((s32) (((void*)gHeroState) + 0x88), (s32) (((void*)gHeroState) + 0xA00), ((Hero *)gHeroState)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vec10), (s32)(gHeroState + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vec10), (s32) ((TI128*)vec10), (s32)(gHeroState + 0xE0));
        value29 = ProcessCollisionHit(0.57f, (s32) ((TI128*)vec10), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        if (value29 != 0) {
            FastVecScale((s32) ((TI128*)vec20), (s32)(gHeroState + 0x110), 7.0f);
            for (value64 = 0; value64 < value29; value64++) {
                if (IsMobyInSpecialClassRange(((s32 *)D_L03_001C3E40)[value64]) != 0) {
                    QueueImpactEffect(((s32 *)D_L03_001C3E40)[value64], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vec20), 1.0f);
                }
            }
        }
        SetCameraLimitsSlot0(0.017f, 0.3f);
        SetCameraLimitsSlot2(0.025f, 0.3f);
        SetCameraLimitsSlot3(0.03f, 0.27f);
        scalar156 = scalar147 * 27.0f;
        if (scalar156 > 1.7f) {
            scalar156 = 1.7f;
        } else if (scalar156 < -1.7f) {
            scalar156 = -1.7f;
        }
        scalar13 = scalar156 * 0.5f;
        ((Hero *)D_L03_00260710)->f[0x60/4] = (f32) -scalar156;
        ((Hero *)D_L03_00260710)->f[0x278/4] = scalar13;
        ((Hero *)D_L03_00260710)->f[0x1C8/4] = scalar13;
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        value87 = ((Hero *)gHeroState)->u[0x2294/4];
        if (((u32) (value87 - 0x28) >= 2U) && (value87 != 0x3E)) {
            UpdateSoundSlotObject(0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        } else {
            value22 = ((Hero *)gHeroState)->i[0x242C/4];
            if (value22 != -1) {
                ptr12 = (value22 * 0x70) + (s32)gSoundState;
                if (M2C_FIELD(ptr12, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr12, u8* , 0x74) != 0) {
                        StopSoundVoice(value22);
                    }
                }
            }
            ((Hero *)gHeroState)->i[0x242C/4] = -1;
        }
        value88 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value88 == 0x27) || (value88 == 0x2A)) {
            qcopy(vec0, &((Hero *)gHeroState)->q[0x80/16]);
            scalar60 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.0f, 0.52359885f));
            scalar77 = RandomFloatRange(0.06666667f, 0.116666675f);
            vec10[0] = FastSinOrCosA(scalar60) * scalar77;
            scalar16 = FastSinOrCosB(scalar60) * scalar77;
            vec10[2] = 0.0f;
            vec10[1] = scalar16;
            vec10[2] = RandomFloatRange(0.050000004f, 0.083333336f);
            vec10[3] = -0.008333334f;
            SpawnWhiteFlashParticle((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 0, -1.0f);
        }
        ptr20 = ((Hero *)gHeroState)->ptr[0x1248/4];
        spill5 = 0;
        value27 = (((LevelInfo *)D_L03_00266DA0)[gItemSlotToRecord[(s32)ptr20]].x1C != 0);
        if ((s32)ptr20 == 0xD) {
            value27 = 0;
        }
        if (value27 != 0) {
            spill5 = ((Hero *)gHeroState)->b[0x22BA] != 0;
        }
        ptr35 = ((void*)gHeroState) + 0x80;
        find_nearest_path_point(((Hero *)gHeroState)->i[0x630/4], (s32) ptr35, (s32) (((void*)gHeroState) + 0x5D0), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)gHeroState)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)gHeroState)->i[0x664/4], (s32) ptr35, (s32) (((void*)gHeroState) + 0x610), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        value63 = 0;
        if (((Hero *)gHeroState)->f[0x31C/4] > 1.0699999f) {
            value89 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((value89 != 0x28) && (value89 != 0x3E) && (((Hero *)gHeroState)->i[0x660/4] == 0)) {
                value63 = ((Hero *)gHeroState)->i[0x1BC/4] >= 0x1F;
            }
        }
        if (value63 != 0) {
            ((Hero *)gHeroState)->i[0x6C8/4] = (s32) (((Hero *)gHeroState)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)gHeroState)->i[0x6C8/4] = 0;
        }
        value30 = ((Hero *)gHeroState)->i[0x640/4];
        if (((value30 != 0) && ((((Hero *)gHeroState)->i[0x640/4] = value30 + 1) != 0)) || (value63 != 0)) {
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x120/16]);
            ptr52 = ((void*)(gHeroState + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(ptr52, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion();
            } else {
                M2C_FIELD(ptr52, f32* , 0xF8) = (f32) (M2C_FIELD(ptr52, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            scalar40 = (f32) ((Hero *)gHeroState)->i[0x648/4];
            scalar132 = ((Hero *)gHeroState)->f[0x644/4] * scalar40;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                scalar132 = ((Hero *)gHeroState)->f[0x69C/4] * scalar40;
            }
            Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32)((TI128*)vec0), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], scalar132);
            if (((Hero *)gHeroState)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x664/4], (s32) ((TI128*)vec10), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], scalar132);
            }
            if (((Hero *)gHeroState)->i[0x1BC/4] >= 0x5B) {
                scalar61 = ((Hero *)gHeroState)->f[0x170/4] * 30.0f;
                qcopy(vec20, &((Hero *)gHeroState)->q[0x80/16]);
                spill1 = ((Hero *)gHeroState)->i[0x634/4];
                spillFloat8 = ((Hero *)gHeroState)->f[0x638/4];
                value25 = Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vec20), (s32) &spill1, (s32) &spillFloat8, ((Hero *)gHeroState)->i[0x654/4], scalar61);
                qcopy(vec30, &((Hero *)gHeroState)->q[0x80/16]);
                spill1 = ((Hero *)gHeroState)->i[0x634/4];
                spillFloat8 = ((Hero *)gHeroState)->f[0x638/4];
                if ((((value25 | Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vec30), (s32) &spill1, (s32) &spillFloat8, ((Hero *)gHeroState)->i[0x654/4], scalar61 + 0.1f)) == 0) || (((Hero *)gHeroState)->i[0x654/4] != 0)) && (((Hero *)gHeroState)->u[0x2294/4] == 0x27)) {
                    scalar133 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x64C/4], FastMatrixHelperA(vec30[0] - vec20[0], vec30[1] - vec20[1])) * 0.47f;
                    if (scalar133 > 0.78539824f) {
                        scalar133 = 0.78539824f;
                    }
                    if (scalar133 < -0.78539824f) {
                        scalar133 = -0.78539824f;
                    }
                    SetCameraLimitsSlot0(0.03f, 0.2f);
                    if (((Hero *)gHeroState)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L03_00260774) = -scalar133;
                    } else {
                        (*(f32*)&D_L03_00260774) = scalar133;
                    }
                }
            }
            value90 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((value90 != 0x28) && (value90 != 0x3E) && (value90 != 0x29)) {
                (*(f32*)&D_L03_00260770) = FastMatrixHelperA(vec_length_xy((s32) (((void*)gHeroState) + 0x110)), ((Hero *)gHeroState)->f[0x118/4]);
            }
            if (value27 != 0) {
                k03 = 0.3f;
                SetCameraLimitsSlot3(0.017f, k03);
                SetCameraLimitsSlot1(0.027f, k03);
                SetCameraLimitsSlot2(0.027f, k03);
                value19 = ((Hero *)gHeroState)->i[0x6A8/4];
                if (value19 != 0) {
                    FastVecSub((s32) ((TI128*)vec20), value19 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (s32) (((void*)gHeroState) + 0x40));
                    scalar33 = FastMatrixHelperA(vec20[0], vec20[1]);
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        scalar33 = fast_subtract_rotations(scalar33, 1.5707965f);
                        scalar129 = 0.2f;
                    } else {
                        scalar33 = fast_subtract_rotations(scalar33, -1.5707965f);
                        scalar129 = 0.5f;
                    }
                    ((Hero *)D_L03_00260710)->f[0x1C8/4] = (f32) (scalar33 * scalar129);
                    ((Hero *)D_L03_00260710)->f[0x278/4] = (f32) (scalar33 * k03);
                } else {
                    value96 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43);
                    if (value96 == 0x31) {
                        scalar150 = 0.58823526f;
                        scalar103 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar134 = 0.73303837f;
                        ((Hero *)D_L03_00260710)->f[0x278/4] = scalar103;
                        ((Hero *)D_L03_00260710)->f[0x118/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                        ((Hero *)D_L03_00260710)->f[0x1C8/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                    } else if (value96 == 0x48) {
                        scalar150 = 0.5f;
                        scalar103 = FastAddRotations(0.13962635f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar134 = -0.06981318f;
                        ((Hero *)D_L03_00260710)->f[0x278/4] = scalar103;
                        ((Hero *)D_L03_00260710)->f[0x118/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                        ((Hero *)D_L03_00260710)->f[0x1C8/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                    } else if (value96 == 0x47) {
                        scalar150 = 0.58823526f;
                        scalar103 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar134 = 0.73303837f;
                        ((Hero *)D_L03_00260710)->f[0x278/4] = scalar103;
                        ((Hero *)D_L03_00260710)->f[0x118/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                        ((Hero *)D_L03_00260710)->f[0x1C8/4] = FastAddRotations(scalar134, ((Hero *)gHeroState)->f[0x6A0/4] * scalar150);
                    }
                }
            }
            value32 = AdvancePathIndex(((Hero *)gHeroState)->i[0x630/4], ((Hero *)gHeroState)->i[0x634/4], ((Hero *)gHeroState)->i[0x648/4], ((Hero *)gHeroState)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)vec20), (s32) &((TI128 *)((Hero *)gHeroState)->ptr[0x630/4])[value32 + 1], (s32)((TI128*)vec0));
            if (FastVecLength((s32) ((TI128*)vec20)) < 0.001f) {
                if (((Hero *)gHeroState)->i[0x634/4] == value32) {
                    ((Hero *)gHeroState)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)gHeroState)->f[0x64C/4] = FastMatrixHelperA(vec20[0], vec20[1]);
                ((Hero *)gHeroState)->f[0x650/4] = FastMatrixHelperA(vec_length_xy((s32) ((TI128*)vec20)), M2C_BITWISE(f32, vec20[2]));
block_807:
                ((Hero *)gHeroState)->f[0x1A0/4] = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], ((Hero *)gHeroState)->f[0x658/4]);
                SteerHeroHeading(0, 0.015f, 0.15f, 0.10471977f);
                value91 = ((Hero *)gHeroState)->u[0x2294/4];
                if ((((u32) (value91 - 0x28) < 2U) && (((Hero *)gHeroState)->b[0x49C] == 0)) || (value91 == 0x3E)) {
                    if (((Hero *)gHeroState)->i[0x694/4] != 0) {
                        scalar20 = FastMatrixHelperA(((Hero *)gHeroState)->f[0x620/4] - ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x624/4] - ((Hero *)gHeroState)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], scalar20) < 1.5707965f) {
                            ((Hero *)gHeroState)->f[0x1A0/4] = scalar20;
                            SteerHeroHeading(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)gHeroState)->i[0x660/4] != 0) && (((Hero *)gHeroState)->i[0x678/4] < 0x31)) {
                        FastVecSub((s32) ((TI128*)vec20), (s32)((TI128*)vec0), (s32) ((TI128*)vec10));
                        value33 = ((Hero *)gHeroState)->i[0x678/4] + 1;
                        ((Hero *)gHeroState)->i[0x678/4] = value33;
                        FastVecScale((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), (f32) value33 * 0.020833334f);
                        scalar62 = (f32) (((Hero *)gHeroState)->i[0x678/4] - 1) * 0.020833334f;
                        FastVecSub((s32) ((TI128*)vec30), (s32)((TI128*)vec0), (s32) ((TI128*)vec10));
                        FastVecScale((s32) ((TI128*)vec30), (s32) ((TI128*)vec30), scalar62);
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + (M2C_BITWISE(f32, vec20[2]) - vec30[2]));
                        FastVecAdd((s32) ((TI128*)vec30), (s32) ((TI128*)vec10), (s32) ((TI128*)vec20));
                        FastVecSub((s32) ((TI128*)vec20), (s32) ((TI128*)vec30), (s32) (((void*)gHeroState) + 0x80));
                        ((Hero *)gHeroState)->f[0xF0/4] = vec20[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = vec20[1];
                        FastVecSub((s32) ((TI128*)vec20), (s32)((TI128*)vec0), (s32) (((void*)gHeroState) + 0x5D0));
                        scalar86 = ((Hero *)gHeroState)->f[0x5D8/4];
                        scalar41 = ((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, vec20[2]);
                        ((Hero *)gHeroState)->f[0x88/4] = scalar41;
                        if (scalar41 < scalar86) {
                            if (((Hero *)gHeroState)->i[0x678/4] < 0x31) {
                                if (scalar41 < scalar86) {
                                    ((Hero *)gHeroState)->f[0x88/4] = scalar86;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)vec20), (s32)((TI128*)vec0), (s32)(gHeroState + 0x5D0));
                        ((Hero *)gHeroState)->f[0xF0/4] = vec20[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = vec20[1];
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, vec20[2]));
                        FastVecSub((s32) ((TI128*)vec30), (s32)(gHeroState + 0x5D0), (s32)(gHeroState + 0x80));
                        vec30[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)vec30)) > 0.016666668f) {
                            vec_scale_to_length((s32) ((TI128*)vec30), (s32) ((TI128*)vec30), 0.016666668f);
                        }
                        ((Hero *)gHeroState)->f[0x80/4] = (f32) (((Hero *)gHeroState)->f[0x80/4] + vec30[0]);
                        ((Hero *)gHeroState)->f[0x84/4] = (f32) (((Hero *)gHeroState)->f[0x84/4] + vec30[1]);
                    }
                    if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.006388889f);
                    } else {
                        ApplyHeroGravityAndJumpMotion();
                    }
                } else {
                    ((Hero *)gHeroState)->i[0x660/4] = 0;
                    scalar104 = 0.0f;
                    if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) && (spill5 != 0)) {
                        ResolveStickInputToDirection(1.0f, 0);
                        scalar104 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x1A0/4], ((Hero *)gHeroState)->f[0x64C/4]);
                        if (scalar104 > 0.78539824f) {
                            scalar104 = 0.78539824f;
                        } else if (scalar104 < -0.78539824f) {
                            scalar104 = -0.78539824f;
                        }
                    }
                    ApproachWithVelocity((s32)(gHeroState + 0x6A0), scalar104, (s32)(gHeroState + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    ApproachValue((s32)(gHeroState + 0x680), 0.20000002f, 0.004166667f);
                    spill2 = ((Hero *)gHeroState)->i[0x634/4];
                    spillFloat9 = ((Hero *)gHeroState)->f[0x638/4];
                    qcopy(vec20, &((Hero *)gHeroState)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vec20), (s32) &spill2, (s32) &spillFloat9, ((Hero *)gHeroState)->i[0x654/4], 0.3f);
                    scalar17 = FastMatrixHelperA(vec_distance_xy((s32)(gHeroState + 0x5D0), (s32) ((TI128*)vec20)), M2C_BITWISE(f32, vec20[2]) - ((Hero *)gHeroState)->f[0x5D8/4]);
                    if (scalar17 > 0.0f) {
                        scalar112 = scalar17 * -0.07957746f;
                        if (scalar17 > 0.26179942f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 0;
                        } else if ((scalar17 < 0.13962635f) && (((Hero *)gHeroState)->i[0x67C/4] == 0)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    } else {
                        scalar112 = -scalar17 * 0.38197184f;
                        if (scalar17 < -0.19198623f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 1;
                        } else if ((scalar17 > -0.122173056f) && (((Hero *)gHeroState)->i[0x67C/4] == 1)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < scalar112) {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), scalar112, 0.0022222223f);
                    } else {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), scalar112, 0.00055555557f);
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)gHeroState)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)gHeroState)->f[0x674/4] = -0.041666668f;
                    }
                    scalar18 = ((Hero *)gHeroState)->f[0x680/4] + ((Hero *)gHeroState)->f[0x674/4];
                    ((Hero *)gHeroState)->f[0x644/4] = scalar18;
                    if (scalar18 < 0.0f) {
                        ((Hero *)gHeroState)->f[0x644/4] = 0.0f;
                    }
                    ptr26 = ((void*)gHeroState) + 0x5D0;
                    FastVecSub((s32) (((void*)gHeroState) + 0xF0), (s32)((TI128*)vec0), (s32) ptr26);
                    ptr41 = ((void*)gHeroState) + 0x80;
                    FastVecSub((s32) ((TI128*)vec20), (s32) ptr26, (s32) ptr41);
                    spillFloat10 = -FastVecLength((s32) ((TI128*)vec20));
                    SpringFloatToGoal((s32) &spillFloat10, (s32) (((void*)gHeroState) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    scalar19 = FastVecLength((s32) ((TI128*)vec20));
                    if (scalar19 < ((Hero *)gHeroState)->f[0x6AC/4]) {
                        ((Hero *)gHeroState)->f[0x6AC/4] = scalar19;
                    }
                    scalar34 = ((Hero *)gHeroState)->f[0x6AC/4];
                    if (scalar34 < scalar19) {
                        vec_scale_to_length((s32) ((TI128*)vec20), (s32) ((TI128*)vec20), scalar34);
                    }
                    FastVecAdd((s32) ptr41, (s32) ptr41, (s32) ((TI128*)vec20));
                    scalar89 = ((Hero *)gHeroState)->f[0x88/4];
                    scalar85 = ((Hero *)gHeroState)->f[0x5D8/4];
                    if (scalar89 < scalar85) {
                        if (((Hero *)gHeroState)->f[0x31C/4] < 1.0f) {
                            if (scalar89 < scalar85) {
                                ((Hero *)gHeroState)->f[0x88/4] = scalar85;
                            }
                        }
                    }
                }
                if (((Hero *)gHeroState)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)gHeroState)->i[0x1B8/4] < 0x14) {
                        scalar21 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.3490659f, 0.6108653f));
                        vec50[0] = FastSinOrCosA(scalar21);
                        vec50[1] = FastSinOrCosB(scalar21);
                        vec50[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)vec20), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &vec50[0]);
                        qcopy(vec60, &((Hero *)gHeroState)->q[0x80/16]);
                        vec60[2] += 0.6f;
                        ProcessCollisionHit(1.0f, (s32) ((TI128*)vec60), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)vec20));
                    }
                }
            }
        }
        break;
    case 0x17:                                      /* switch 1 */
    case 0x18:                                      /* switch 1 */
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
    case 0x46:                                      /* switch 1 */
    case 0x47:                                      /* switch 1 */
        FastVecSub((s32)(gHeroState + 0x190), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(((Hero *)gHeroState)->f[0x190/4], ((Hero *)gHeroState)->f[0x194/4]);
        SteerHeroHeading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0x550), (s32)(gHeroState + 0x80));
        ClampVectorLength((s32)(gHeroState + 0xF0), 0.028333336f);
        ApproachValue((s32)(gHeroState + 0x580), ((Hero *)gHeroState)->f[0x88/4], 0.050000004f);
        break;
    case 0x19:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
        FastVecSub((s32)(gHeroState + 0x190), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(((Hero *)gHeroState)->f[0x190/4], ((Hero *)gHeroState)->f[0x194/4]);
        SteerHeroHeading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)vec60), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32)(gHeroState + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vec40[0], (s32)(gHeroState + 0x2C0), (s32) ((TI128*)vec60));
        } else {
            FastVecCross((s32) &vec40[0], (s32) ((TI128*)vec60), (s32)(gHeroState + 0x2C0));
        }
        vec_scale_to_length((s32) &vec40[0], (s32) &vec40[0], 0.2f);
        FastVecAdd((s32) &vec50[0], (s32)(gHeroState + 0x80), (s32) &vec40[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &vec50[0], (s32)(gHeroState + 0x90), (s32)((TI128*)vec0)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)vec0), (s32)(gHeroState + 0x80));
            value76 = FloatToInt(((Hero *)gHeroState)->f[0xC38/4]) * 4;
            value80 = (s32)D_L03_001ACEA8;
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), *(f32*)(value76 + value80) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0x32C/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity_L01(0.0069444445f);
        ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) ((void*)gHeroState) + 0x130, 0.005f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x2C) {
            scalar113 = 0.0f;
            if (((Hero *)gHeroState)->f[0x31C/4] > 4.0f) {
                scalar113 = 0.43633235f;
            }
            qcopy(vec0, &((Hero *)gHeroState)->q[0x90/16]);
            ApproachWithVelocity((s32) &vec0[1], scalar113, (s32) (((void*)gHeroState) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            ApproachWithVelocity((s32)((TI128*)vec0), 0.0f, (s32) (((void*)gHeroState) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA0/4], ((Hero *)gHeroState)->f[0xA4/4], 0.0f);
            if (((Hero *)gHeroState)->f[0x31C/4] > 1.0f) {
                ((Hero *)gHeroState)->i[0x2298/4] = 1;
            }
        }
        RefreshHeroSpeedFromTimer();
        if (((Hero *)gHeroState)->h[0x1E0/2] == 0) {
            HeroUpdateHopVelocity();
        }
        ptr60 = ((void*)gHeroState) + 0xF0;
        ApplyHeroModePoseOffsets();
        BuildHeroMoveImpulse(0.7f, 0.0f);
        ApplyHeroModeTransform((s32) ptr60, (s32) ptr60, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) ptr60) < -0.8333334f) {
            SetViewSpaceHeight((s32) ptr60, (s32) ptr60, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)gHeroState)->c[0x22BC] = 1;
        ptr2 = ((void*)gHeroState) + 0xF0;
        ApproachValue((s32) (((void*)gHeroState) + 0xA88), ((Hero *)gHeroState)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)gHeroState) + 0xA8C), ((Hero *)gHeroState)->f[0xA94/4], 0.0024240687f);
        StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA88/4], ((Hero *)gHeroState)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) ptr2, (s32) ptr2, vec_length_xy((s32) ptr2) * 0.9f);
        ApplyHeroModeTransform((s32) ptr2, (s32) ptr2, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) ptr2) < -0.8333334f) {
            SetViewSpaceHeight((s32) ptr2, (s32) ptr2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        ang82 = (f32) LerpInt(0x2D0, 0xB4, ((Hero *)gHeroState)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        ShowGaugePopup(2, UpdateAngleAndBlend((s32) (((void*)gHeroState) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)gHeroState)->f[0x5B0/4] * 0.02f));
        value56 = (s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40;
        if (((Hero *)gHeroState)->f[0x5B0/4] == 0.0f) {
            value56 = 0;
        }
        if (value56 != 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0x5B0), 0.0f, 0.1f);
            ptr13 = ((void*)gHeroState) + 0xF0;
            OffsetPointInViewSpace((s32) ptr13, (s32) ptr13, 0.025f);
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
        scalar35 = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        if ((((Hero *)gHeroState)->f[0x5B0/4] > 25.0f) && (((Hero *)gHeroState)->h[0x5BE/2] < 0x5A) && (scalar35 < 0.0f) && (scalar87 = ((Hero *)gHeroState)->f[0x31C/4], (scalar87 < 1.2f))) {
            scalar91 = (scalar87 - 0.25f) * 1.0526315f;
            ((Hero *)gHeroState)->h[0x5BE/2] = (s16) ((u16) ((Hero *)gHeroState)->h[0x5BE/2] + 1);
            if (scalar91 < 0.0f) {
                scalar91 = 0.0f;
            }
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), scalar35 * scalar91);
            if (((Hero *)gHeroState)->f[0x31C/4] < 0.25f) {
                SpringFloatToGoal((s32)(gHeroState + 0x88), (s32)(gHeroState + 0x5B4), ((Hero *)gHeroState)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (scalar35 > 0.0f) {
            ((Hero *)gHeroState)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L03_001B9C08) = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        ApplyHeroModePoseOffsets();
        ResolveStickInputToDirection(((Hero *)gHeroState)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
        }
        SteerHeroHeading(0, 0.027f, 0.3f, ((Hero *)gHeroState)->f[0x24B8/4] * 0.087266475f);
        scalar114 = 0.0013888889f;
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            scalar114 = 0.00055555557f;
        }
        ApproachHeroVelocity_L01(scalar114);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            value23 = ((Hero *)gHeroState)->i[0x243C/4];
            if (value23 != -1) {
                ptr14 = (value23 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(ptr14, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(ptr14, u8* , 0x74) != 0)) {
                    StopSoundVoice(value23);
                }
            }
            ((Hero *)gHeroState)->i[0x243C/4] = -1;
            UpdateSoundSlotObject(3, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 2);
        } else {
            value24 = ((Hero *)gHeroState)->i[0x2438/4];
            if (value24 != -1) {
                ptr15 = (value24 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(ptr15, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(ptr15, u8* , 0x74) != 0)) {
                    StopSoundVoice(value24);
                }
            }
            ((Hero *)gHeroState)->i[0x2438/4] = -1;
            UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        }
        scalar152 = 0.050000004f;
        if (((Hero *)gHeroState)->i[0x1338/4] == 3) {
            scalar152 = 0.083333336f;
        }
        scalar153 = 0.72f;
        scalar42 = ((Hero *)gHeroState)->f[0x24C8/4];
        if (((Hero *)gHeroState)->b[0x24EF] != 0) {
            scalar152 = 0.12833333f;
            scalar153 = 0.98640007f;
        }
        if (scalar42 != 0.0f) {
            scalar153 = scalar42;
        }
        ptr27 = ((void*)gHeroState) + 0xF0;
        spillFloat11 = GetViewSpaceHeight((s32) ptr27);
        ResolveStickInputToDirection(scalar152, 0);
        SteerHeroHeading(0, 0.025f, 0.3f, 0.20943955f);
        ApproachHeroSpeed(0.004166667f, 0.0019444445f);
        ComputeHeroPushDirection(99999.0f);
        ApplyHeroModePoseOffsets();
        ProjectVectorOntoViewPlane((s32) ptr27, (s32) ptr27);
        SpringFloatToGoal((s32) &spillFloat11, (s32) (((void*)gHeroState) + 0xA98), -scalar152 * scalar153, 0.025f, 0.3f, 0.28333336f);
        ApplyHeroModeTransform((s32) ptr27, (s32) ptr27, -spillFloat11);
        scalar36 = ((Hero *)gHeroState)->f[0x88/4];
        if (scalar36 < ((Hero *)gHeroState)->f[0x490/4]) {
            ApproachValue((s32) (((void*)gHeroState) + 0x490), scalar36, 0.06666667f);
        }
        ProbeHeroAirborneWallContact();
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
        value5 = ((Hero *)gHeroState)->h[0x4AC/2];
        value20 = ((Hero *)gHeroState)->i[0x1B8/4];
        if (value20 == value5) {
            qcopy(&((Hero *)gHeroState)->q[0x460/16], &((Hero *)gHeroState)->q[0x80/16]);
        }
        if ((((Hero *)gHeroState)->b[0x49C] != 0) || ((value20 < value5) && (value92 = ((Hero *)gHeroState)->u[0x2294/4], (value92 != 0xB)) && (value92 != 0x10) && (value92 != 0xC) && (value92 != 0x11) && (value92 != 0x1B) && (value92 != 0x89) && (value92 != 0x48))) {
            SteerHeroHeading(0, 0.015f, 0.2f, 0.2501639f);
            scalar63 = ((Hero *)gHeroState)->f[0x1B4/4];
            if ((u8) ((Hero *)gHeroState)->b[0x49C] >= 2U) {
                ((Hero *)gHeroState)->f[0x1B4/4] = (f32) (scalar63 * 0.4f);
            }
            if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1458/4]);
            } else {
                ComputeHeroPushDirection(99999.0f);
            }
            ((Hero *)gHeroState)->f[0x1B4/4] = scalar63;
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
                value46 = ((Hero *)gHeroState)->i[0x1B8/4];
                if (value46 < (((Hero *)gHeroState)->h[0x4AC/2] + 4)) {
                    OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) value46 * 0.0044444446f);
                }
            }
            if (((Hero *)gHeroState)->u[0x2294/4] == 0xA) {
                value47 = ((Hero *)gHeroState)->i[0x1B8/4];
                if (value47 < 0x22) {
                    OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) value47 * 0.014722222f);
                }
            }
            if ((((Hero *)gHeroState)->i[0x1B8/4] < 0xA) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f)) {
                qcopy(vec0, &((Hero *)gHeroState)->q[0x80/16]);
                OffsetPointInViewSpace((s32)((TI128*)vec0), (s32)((TI128*)vec0), 0.5f);
                OffsetPointBySideDirection((s32) ((TI128*)vec10), (s32)((TI128*)vec0), 0.95f);
                if (CollLine((s32)((TI128*)vec0), (s32) ((TI128*)vec10), 4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0) != 0) {
                    ((Hero *)gHeroState)->h[0x524/2] = 1;
                }
            }
        } else {
            HeroUpdateHopVelocity();
        }
        scalar44 = ((Hero *)gHeroState)->f[0x318/4];
        scalar88 = ((Hero *)gHeroState)->f[0x490/4];
        if (scalar88 < scalar44) {
            scalar22 = scalar88 + 0.10000001f;
            ((Hero *)gHeroState)->f[0x490/4] = scalar22;
            if (scalar44 < scalar22) {
                ((Hero *)gHeroState)->f[0x490/4] = scalar44;
            }
        }
        scalar45 = ((Hero *)gHeroState)->f[0x88/4];
        if (scalar45 < ((Hero *)gHeroState)->f[0x490/4]) {
            ((Hero *)gHeroState)->f[0x490/4] = scalar45;
        }
        if ((((Hero *)gHeroState)->h[0x4AC/2] < ((Hero *)gHeroState)->i[0x1B8/4]) && (GetViewSpaceHeight((s32) (((void*)gHeroState) + 0xF0)) < 0.001f) && ((((Hero *)gHeroState)->b[0x49D] == 0) || (((Hero *)gHeroState)->i[0x1B8/4] > ((Hero *)gHeroState)->i[0x434/4])) && ((((Hero *)gHeroState)->u[0x2294/4] != 0xE) || (((Hero *)gHeroState)->i[0x1B8/4] >= 0x12))) {
            scalar46 = ((Hero *)gHeroState)->f[0x458/4];
            ((Hero *)gHeroState)->b[0x49E] = 1U;
            if (scalar46 != 0.0f) {
                ((Hero *)gHeroState)->f[0x520/4] = scalar46;
            }
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ApplyHeroModePoseOffsets();
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters();
        }
        value93 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value93 == 0x10) || (value93 == 0xD)) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x81) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x10) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 9) {
                if (((Hero *)gHeroState)->f[0xC38/4] < 28.0f) {
                    BuildHeroRelativePoint((s32)((TI128*)vec0), 1, 0.8f, 0.0f, 0.3f);
                    value34 = ProcessCollisionHit(0.9f, (s32)((TI128*)vec0), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
                    if (value34 != 0) {
                        FastVecScale((s32) ((TI128*)vec10), (s32) (((void*)gHeroState) + 0x110), 7.0f);
                        for (value65 = 0; value65 < value34; value65++) {
                            if (IsMobyInSpecialClassRange(((s32 *)D_L03_001C3E40)[value65]) != 0) {
                                QueueImpactEffect(((s32 *)D_L03_001C3E40)[value65], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vec10), 1.0f);
                            }
                        }
                    }
                }
            }
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x38) && (((Hero *)gHeroState)->b[0x49E] == 0) && (((Hero *)gHeroState)->f[0xF8/4] > 0.025000002f)) {
            EmitHeroTimedEffects();
        }
        ApplyHeroGravityAndJumpMotion();
        ProbeHeroAirborneWallContact();
        break;
    case 0x16:                                      /* switch 1 */
        scalar135 = GetViewSpaceVectorLength((s32)(gHeroState + 0xF0));
        scalar93 = 0.0011111111f;
        if ((((Hero *)gHeroState)->h[0x34E/2] == 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB)) {
            scalar93 = 0.0027777778f;
        }
        scalar135 = scalar135 - scalar93;
        if (scalar135 < 0.0f) {
            scalar135 = 0.0f;
        }
        if (((Hero *)gHeroState)->b[0x1497] != 0) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        ptr59 = ((void*)gHeroState) + 0xF0;
        SetViewSpaceVectorLength((s32) ptr59, (s32) ptr59, scalar135);
        ApplyHeroModeTransform((s32) ptr59, (s32) ptr59, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)gHeroState)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(vec0[0], vec0[1]);
        scalar24 = vec_length_xy((s32)((TI128*)vec0));
        if (scalar24 > 0.2f) {
            hp32 = (Hero *)gHeroState;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(vec0[0], vec0[1]);
            ((Hero *)gHeroState)->f[0x1B0/4] = scalar24;
            if (scalar24 < D_L03_001A7DAC[0][2]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L03_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L03_001A7DAC[1][1] * 0.016666668f;
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
            DeflectHeroOffSteepSurface(1);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x110, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vec0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        if (FastVecDot((s32)((TI128*)vec0), (s32)(gHeroState + 0x160)) < 0.0f) {
            ClearVector128((s32)(gHeroState + 0x160));
        }
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.0075000003f);
        DeflectHeroOffSteepSurface(0);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0x18A0)) - 0x1790, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0xF0)), 0.015000001f);
        break;
    case 0x3C:                                      /* switch 1 */
    case 0x64:                                      /* switch 1 */
        ClearVector128((s32)(gHeroState + 0xF0));
        break;
    case 0x79:                                      /* switch 1 */
        EmitHeroRadialParticles();
        ClearVector128((s32)(gHeroState + 0xF0));
        M2C_FIELD(((void*)(gHeroState + 0xF0)), f32* , 8) = -0.016666668f;
        break;
    case 0x7A:                                      /* switch 1 */
        ClearVector128((s32)(gHeroState + 0xF0));
        M2C_FIELD(((void*)(gHeroState + 0xF0)), f32* , 8) = -0.0058333334f;
        break;
    case 0x3F:                                      /* switch 1 */
    case 0x43:                                      /* switch 1 */
        TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        ResolveStickInputToDirection(1.0f, 0);
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ApproachHeroSpeed(0.0f, 0.0035f);
        ClearVector128((s32)(gHeroState + 0xF0));
        DeflectHeroOffSteepSurface(0);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0xF0)), 0.015000001f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ptr53 = (s32) &D_L03_00262290[((Hero *)gHeroState)->h[0xBFC/2]];
        value10 = M2C_FIELD(ptr53, s32* , 4);
        switch (value10) {
        case 0:
            if (((Hero *)gHeroState)->f[0xC38/4] < 5.5f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        case 1:
            if (((Hero *)gHeroState)->f[0xC38/4] < 5.5f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.058333337f;
            }
            break;
        }
        if (((Hero *)gHeroState)->i[0xC2C/4] == 0) {
            scalar47 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((f32) M2C_FIELD(ptr53, s32* , 0x1C) <= scalar47) {
                if (scalar47 <= (f32) M2C_FIELD(ptr53, s32* , 0x20)) {
                    value26 = ((M2C_FIELD(ptr53, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], value26, (s32) ((TI128*)vec10));
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], value26 | 1, (s32) ((TI128*)vec20));
                    FastVecAdd((s32)((TI128*)vec0), (s32) ((TI128*)vec10), (s32) ((TI128*)vec20));
                    FastVecScale((s32)((TI128*)vec0), (s32)((TI128*)vec0), 0.5f);
                    SweepCollisionFromObject((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)vec0), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
                }
            }
        }
        ApproachValue((s32)(gHeroState + 0xC20), 1.0f, 0.2f);
        if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
            SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
        } else {
            SelectHeroAimTarget(5.0f, 0.78539824f, 0.78539824f);
        }
        ApproachHeroSpeed(0.010277778f, 0.007777778f);
        if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
            if (((Hero *)gHeroState)->b[0x22C3] == 2) {
                SetHeroPushDirection((s32) (((void*)gHeroState) + 0xBC0));
            } else {
                ComputeHeroPushDirection(((Hero *)gHeroState)->f[0xBEC/4]);
            }
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0x118/4] - 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.015000001f);
        }
        TryHeroSurfacePushResponse(0.7f, 0.0f, 0.3f);
        break;
    case 0x4B:                                      /* switch 1 */
        ResolveStickInputToDirection(0.033333335f, 0);
        SteerHeroHeading(0, 0.04f, 0.2f, 0.14544412f);
        ApproachHeroSpeed(0.004166667f, 0.0019444445f);
        ComputeHeroPushDirection(99999.0f);
        ProjectVectorOntoViewPlane((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0));
        ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0xF0)), 0.024000002f);
        break;
    case 0x4E:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x32C/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity_L01(0.0069444445f);
        scalar1 = 0.005f;
        ptr3 = ((void*)gHeroState) + 0x130;
        ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) ptr3, scalar1);
        break;
    case 0x41:                                      /* switch 1 */
        ResolveStickInputToDirection(0.050000004f, 0);
        if (((Hero *)gHeroState)->h[0x1E0/2] == 0) {
            HeroUpdateHopVelocity();
        }
        ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), 0.0033333334f);
        if (((Hero *)gHeroState)->f[0xF8/4] < -0.16666667f) {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.16666667f;
        }
        break;
    case 0x44:                                      /* switch 1 */
        if (((Hero *)gHeroState)->f[0xF8/4] > 0.0f) {
            StartHeroPoseOffset(0.0f, 0.20943955f, 0.0f);
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.0055555557f);
        break;
    case 0x40:                                      /* switch 1 */
    case 0x4C:                                      /* switch 1 */
        ResolveStickInputToDirection(0.050000004f, 0);
        scalar124 = 0.16580631f;
        scalar116 = 0.033f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar124 = 0.19489513f;
            scalar116 = 0.037f;
        }
        SteerHeroHeading(0, scalar116, 0.15f, scalar124);
        ApproachHeroSpeed(0.005f, 0.0055555557f);
        if (((Hero *)gHeroState)->f[0x174/4] < 0.011666667f) {
            ((Hero *)gHeroState)->b[0x40C] = 1U;
            if ((FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)gHeroState)->b[0x40F] = 1U;
            }
        }
        scalar65 = ReadPadFloatHistory(0);
        if ((FastDiffRots(scalar65, ReadPadFloatHistory(2)) > 2.617994f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
            ((Hero *)gHeroState)->b[0x40F] = 1U;
            ((Hero *)gHeroState)->b[0x40C] = 1U;
        }
        if (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) < 0.087266475f) {
            ((Hero *)gHeroState)->b[0x40C] = 0U;
        }
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            if (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) < 0.06981318f) {
                ((Hero *)gHeroState)->b[0x40F] = 0U;
            }
            if (((Hero *)gHeroState)->b[0x40F] != 0) {
                scalar157 = 0.050000004f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.02122066f);
                if (scalar157 < 0.0f) {
                    scalar157 = 0.0f;
                }
                if (scalar157 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = scalar157;
                }
            }
        }
        if (((Hero *)gHeroState)->b[0x40C] != 0) {
            ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1A0/4]);
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        DeflectHeroOffSteepSurface(1);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        scalar37 = vec_length_xy((s32)(gHeroState + 0xF0));
        if (*(s16 *)(gHeroState + 0x34E) != 0) {
            scalar37 = scalar37 * 0.99f;
        } else {
            scalar37 = scalar37 * 0.92f;
        }
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), scalar37);
        ptr54 = ((void*)(gHeroState + 0xF0)) - 0xF0;
        M2C_FIELD(ptr54, s32* , 0xF8) = 0;
        if (M2C_FIELD(ptr54, s16* , 0x34E) != 0) {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0) + 0x30, 0.0061111115f);
        } else {
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.004f);
        }
        break;
    case 0x49:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0xC20/4] = 1.3f;
        FastVecSub((s32)(gHeroState + 0x190), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(((Hero *)gHeroState)->f[0x190/4], ((Hero *)gHeroState)->f[0x194/4]);
        SteerHeroHeading(0, 0.02f, 0.2f, 0.078539826f);
        FastVecSub((s32) ((TI128*)vec60), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32) (((void*)gHeroState) + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &vec40[0], (s32) (((void*)gHeroState) + 0x2C0), (s32) ((TI128*)vec60));
        } else {
            FastVecCross((s32) &vec40[0], (s32) ((TI128*)vec60), (s32) (((void*)gHeroState) + 0x2C0));
        }
        vec_scale_to_length((s32) &vec40[0], (s32) &vec40[0], 0.2f);
        FastVecAdd((s32) &vec50[0], (s32)(gHeroState + 0x80), (s32) &vec40[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &vec50[0], (s32)(gHeroState + 0x90), (s32)((TI128*)vec0)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)vec0), (s32)(gHeroState + 0x80));
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), D_L03_00291DB0[FloatToInt(((Hero *)gHeroState)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        ClearVector128((s32)(gHeroState + 0xF0));
        break;
    }
    if (spill3 != ((Hero *)gHeroState)->i[0x2298/4]) {
        ((Hero *)gHeroState)->i[0x1C0/4] = 0;
    }
    if (spill4 != M2C_FIELD(ptr21, u8* , 0x43)) {
        ((Hero *)gHeroState)->i[0x1C4/4] = 0;
    }
}

