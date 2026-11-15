/* func_L00_002BA7D8: the hero's per-frame state handler, the twin of func_L20_002CD928 (see
   src/levels/20_yeedil/L20_002CD928.c for what each flag in this unit's config/cflags.txt line is for).
   One function: one prologue, one return, a switch on the state at 0x2294. */

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
extern void func_L18_002C4000(void);
extern s32 func_L18_00428738(s32);
extern s32 func_L20_002B7A48(s32);
extern void func_L20_002C5A48(s32);
extern void func_L20_002C7588(s32);
extern void func_L20_002D7730(s32, s32);
extern s32 ref_L00_002BA7D8_00 MACRO_ADDR;
extern void func_L00_002ADCF8(f32 *);
/* Runs the hero's state machine once per frame. It picks the code for the current state (walk, jump,
 * swing, swim, hurt and so on) and moves, animates and steers the hero accordingly. */
void func_L00_002BA7D8(void) {
    Hero *heroPtrA;
    s32 indexA;
    s32 countA;
    f32 scalar1;
    f32 scalar2;
    f32 scalar3;
    f32 speed;
    s32 limitA;
    s32 *countPtr;
    Hero *heroPtrB;
    f32 vecA[4] __attribute__((aligned(16)));
    f32 vecB[4] __attribute__((aligned(16)));
    f32 vecC[4] __attribute__((aligned(16)));
    f32 vecD[4] __attribute__((aligned(16)));
    f32 vecE[4] __attribute__((aligned(16)));
    f32 vecF[4] __attribute__((aligned(16)));
    f32 vecG[4] __attribute__((aligned(16)));
    f32 matrixA[16] __attribute__((aligned(16)));
    f32 vecH[4] __attribute__((aligned(16)));
    f32 vecI[4] __attribute__((aligned(16)));
    f32 vecJ[4] __attribute__((aligned(16)));
    f32 stickTurn;
    f32 constA;
    s32 animIdA;
    s32 blendA;
    f32 constB;
    void *ptrA60;
    void* ptr1;
    void* ptr2;
    f32 scalar4;
    void* ptr3;
    s32 value1;
    void* ptr4;
    s32 value2;
    s32 value3;
    void* ptr5;
    s32 value4;
    void* ptr6;
    s32 limit;
    s32 limit2;
    s32 limit3;
    s32 selectionA;
    f32 constC;
    s32 countB;

    f32 scalar5;
    f32 scalar6;
    f32 scalar7;
    f32 scalar8;
    f32 scalar9;
    f32 scalar10;
    f32 scalar11;
    s32 value5;
    f32 scalar12;
    s32 value6;
    f32 scalar13;
    f32 scalar14;
    f32 scalarSpN;
    f32 scalar15;
    s32 savedSubState;
    s32 savedAnimId;
    s32 flagA;
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
    f32 scalar159;
    f32 scalar160;
    f32 scalar161;
    f32 scalar162;
    f32 scalar163;
    f32 scalar164;
    f32 scalar165;
    f32 scalar166;
    f32 scalar167;
    f32 scalar168;
    f32 scalar169;
    f32 scalar170;
    f32 scalar171;
    f32 scalar172;
    s16 shortVal1;
    s32 value7;
    s16 shortVal2;
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
    u16 shortVal3;
    u16 shortVal4;
    u16 shortVal5;
    u32 value81;
    u32 value82;
    u32 value83;
    u32 value84;
    u32 value85;
    u32 value86;
    u32 value87;
    u32 value88;
    u32 value89;
    u32 value90;
    u32 value91;
    u32 value92;
    u8 byteVal1;
    u8 byteVal2;
    u8 byteVal3;
    u8 byteVal4;
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
    void* heroObject;
    void* heroBlock;
    f32 turnAmount;
    f32 angleA;
    f32 minValueA;
    void* heroBlockA30;
    void* ptr21;
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

    savedSubState = ((Hero *)gHeroState)->i[0x2298/4];
    heroObject = ((Hero *)gHeroState)->ptr[0x2290/4];
    savedAnimId = (s32) M2C_FIELD(heroObject, u8* , 0x43);
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
        value82 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value82 == 1) || (value82 == 0x1D)) {
            if (((Hero *)gHeroState)->b[0x22B5] != 0) {
                (*(TI128*)vecA) = 0;
                vecA[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)gHeroState) + 0x190), (s32)((TI128*)vecA), (s32)&D_L20_001B9FD8[0x218]);
                ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)D_L20_001B9FD8)->f[0];
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
            if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) || (byteVal2 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43), (byteVal2 == 0xE)) || (byteVal2 == 0xF)) {
                if (((Hero *)gHeroState)->u[0x2294/4] == 4) {
                    SteerHeroHeading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) > 0.0058177654f) {
                    value11 = ((Hero *)gHeroState)->f[0x1A4/4] < 0.0f;
                    value11 += 0xE;
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) != value11) {
                        set_hero_animation(value11, 0, 5.0f);
                    }
                    scalar16 = FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)gHeroState)->f[0xC20/4] = scalar16;
                    if (scalar16 < 0.55f) {
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
            value91 = ((Hero *)gHeroState)->u[0x2294/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            if (value91 == 3) {
                scalar119 = ((Hero *)gHeroState)->f[0x17C/4] + 1.0f;
                if (scalar119 > 1.0f) {
                    scalar119 = 1.0f;
                }
                ptr16 = ((Hero *)gHeroState)->ptr[0x2290/4];
                scalar145 = scalar119 * 0.0075000003f;
                ((Hero *)gHeroState)->f[0x24AC/4] = scalar145;
                if (M2C_FIELD(ptr16, u8* , 0x42) == M2C_FIELD(ptr16, u8* , 0x43)) {
                    scalar140 = ((Hero *)gHeroState)->f[0x174/4] / scalar145;
                    if ((scalar140 > 5.0f) && ((f32) M2C_FIELD(ptr16, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, scalar140, 0.5f, -1.0f);
                        if (((Hero *)gHeroState)->f[0xC20/4] > 1.1f) {
                            ((Hero *)gHeroState)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (value91 == 4) {
                scalar145 = 0.0075000003f;
                if (((Hero *)gHeroState)->b[0x1492] != 0) {
                    scalar145 = 0.00047222225f;
                }
            } else {
                scalar145 = 0.004916667f;
            }
            ApproachHeroSpeed(0.0f, scalar145);
            ClearVector128((s32)(gHeroState + 0xF0));
            ShrinkHeroVectorByAmount(scalar145);
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
                SlideYeedilHeroAlongWall(0);
                if (((Hero *)gHeroState)->h[0x34E/2] == 0) {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
                } else {
                    ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
                    CancelHeroVelocityIntoWall();
                }
            }
        break;
    case 0x7C:                                      /* switch 1 */
        heroBlock = (void*)gHeroState;
        if (((Hero *)heroBlock)->i[0x7A4/4] == 0) {
            value28 = CreateMoby(0x52A /* moby class 1322 */);
            ((Hero *)heroBlock)->i[0x7A4/4] = value28;
            if (((Hero *)heroBlock)->i[0x7A4/4] != 0) {
            qcopy((u8 *)value28 + 0x10, &((Hero *)heroBlock)->q[0x80/16]);
            qcopy((u8 *)value28 + 0xF0, &((Hero *)heroBlock)->q[0x90/16]);
            M2C_FIELD(value28, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)heroBlock)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)heroBlock)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)heroBlock)->i[0x7A4/4], u8* , 0x23) = 0U;
            value48 = ((Hero *)heroBlock)->i[0x7A4/4];
            M2C_FIELD(value48, u16* , 0x34) = (u16) (M2C_FIELD(value48, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)heroBlock)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)heroBlock)->i[0x7A4/4]);
            }
        }
        if (((Hero *)heroBlock)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)heroBlock)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        value50 = ((Hero *)heroBlock)->i[0x7A4/4];
        if ((u8) M2C_FIELD(value50, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(value50, u8* , 0x23) = 0x80U;
        }
        value12 = ((Hero *)heroBlock)->i[0x7A4/4];
        ptr18 = ((Hero *)heroBlock)->ptr[0x2290/4];
        qcopy((u8 *)value12 + 0x10, (u8 *)ptr18 + 0x10);
        qcopy((u8 *)value12 + 0xF0, (u8 *)ptr18 + 0xF0);
        func_002A0F48(value12);
        }
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), vec_length_xy((s32)(gHeroState + 0xF0)) * 0.92f);
        UpdateHeroHeightOffset();
        break;
    case 0x32:                                      /* switch 1 */
    case 0x33:                                      /* switch 1 */
    case 0x34:                                      /* switch 1 */
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 0x47) {
                (*(u16*)&D_0018CF10) = 0xFFFF;
            }
            UpdateSoundSlotObject(5, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xF);
            QueueRecordsByIndex(0x16);
        } else {
            value21 = ((Hero *)gHeroState)->i[0x2440/4];
            if (value21 != -1) {
                ptr17 = (value21 * 0x70) + (s32)gSoundState;
                if (M2C_FIELD(ptr17, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) {
                    if (M2C_FIELD(ptr17, u8* , 0x74) != 0) {
                        StopSoundVoice(value21);
                    }
                }
            }
            ((Hero *)gHeroState)->i[0x2440/4] = -1;
        }
        if (((Hero *)gHeroState)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)gHeroState) + 0xA4A));
            value13 = (s32) ((u16) ((Hero *)gHeroState)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((value13 >= 9) ? 8 : value13, 0, 0);
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x32) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            scalar62 = ((Hero *)gHeroState)->f[0xC38/4];
            if (scalar62 > 0.0f) {
                if (scalar62 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                value51 = ((Hero *)gHeroState)->i[0x1B8/4];
                if (value51 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - value51) / 3) + 1, 1, 0);
                }
            }
        }
        value52 = ((Hero *)gHeroState)->i[0x2298/4];
        if (value52 == 1) {
            if (((Hero *)gHeroState)->i[0x1B8/4] == value52) {
                EmitHeroDustAndDebris(3, 0x10, 0);
                if (D_L20_001B3730 != 0) {
                    RippleDisturb(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)gHeroState)->h[0xA4A/2] = 0x46;
            }
            value35 = ((Hero *)gHeroState)->i[0xA20/4] + 1;
            ((Hero *)gHeroState)->i[0xA20/4] = value35;
            if (value35 >= 0x29) {
                ((Hero *)gHeroState)->i[0x2298/4] = 0;
            }
        }
        stickTurn = 0.011635531f;
        stickTurn += (((Hero *)gPadState)->f[0x12C/4] > ((Hero *)gPadState)->f[0x128/4] ? ((Hero *)gPadState)->f[0x12C/4] : ((Hero *)gPadState)->f[0x128/4]) * 0.008726647f;
        scalar132 = 0.0f;
        constC = 0.2f;
        if ((((((Hero *)gPadState)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            scalar134 = ((Hero *)gPadState)->f[0x12C/4] * 1.5f;
            if (scalar134 > 1.0f) {
                scalar134 = 1.0f;
            }
            if (scalar134 < constC) {
                scalar134 = constC;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                value9 = ((Hero *)gHeroState)->uh[0xA42/2] + 1;
                ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
                scalar134 = ((f32) (s16) value9 * 0.025f) + 0.5f;
                ((Hero *)gHeroState)->uh[0xA42/2] = (u16) value9;
                if (scalar134 > 1.0f) {
                    scalar134 = 1.0f;
                }
            }
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (scalar134 < 0.35f)) {
                scalar134 = 0.35f;
            }
            scalar132 = scalar134 * 1.361357f;
        } else if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            scalar133 = ((Hero *)gPadState)->f[0x128/4] * 1.5f;
            if (scalar133 > 1.0f) {
                scalar133 = 1.0f;
            }
            if (scalar133 < constC) {
                scalar133 = constC;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                countB = ((Hero *)gHeroState)->uh[0xA40/2] + 1;
                ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
                ((Hero *)gHeroState)->h[0xA40/2] = countB;
                scalar133 = ((f32) (s16) countB * 0.025f) + 0.5f;
                if (scalar133 > 1.0f) {
                    scalar133 = 1.0f;
                }
            }
            if ((f32) ((Hero *)gHeroState)->i[0x24C0/4] < 1500.0f) {
                scalar133 = 1.0f;
            }
            scalar132 = scalar133 * -1.361357f;
        } else {
            ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
            ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            ((Hero *)gHeroState)->uh[0xA4E/2] = (u16) (((Hero *)gHeroState)->uh[0xA4E/2] + 1);
            if (((Hero *)gPadState)->f[0x128/4] > 0.75f) {
                value8 = ((Hero *)gHeroState)->uh[0xA4C/2] + 1;
                ((Hero *)gHeroState)->h[0xA4C/2] = value8;
                if ((s16) value8 >= 0x5B) {
                    shortVal4 = ((Hero *)gProgressStatistics)->uh[0x84/2];
                    if (shortVal4 <= 0xFFFEU) {
                        ((Hero *)gProgressStatistics)->uh[0x84/2] = (u16) (shortVal4 + 1);
                    }
                }
                value36 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)gProgressStatistics)->u[0x88/4] < (u32) value36) {
                    ((Hero *)gProgressStatistics)->u[0x88/4] = (u32) value36;
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
            heroPtrB = (Hero *)gHeroState;
            if ((D_L20_001B2AC8 - heroPtrB->i[0xA54/4]) < 0x46) {
                heroPtrB->i[0xA50/4]++;
            }
            heroPtrB->i[0xA54/4] = D_L20_001B2AC8;
        }
        if ((s16) ((Hero *)gHeroState)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x80) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            scalar132 = 0.0f;
        }
        scalar70 = ((Hero *)gHeroState)->f[0x94/4];
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), scalar132, (s32) (((void*)gHeroState) + 0xA28), 0.015f, 0.2f, stickTurn, 0);
        scalar92 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x94/4], scalar70);
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
        scalar168 = ((Hero *)gHeroState)->f[0x24B8/4];
        if (((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xC0) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            if (scalar168 < 1.0f) {
                scalar168 = 1.0f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.15f) {
            scalar111 = 0.35f;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
                scalar111 = 0.4f;
            }
            if (scalar168 < scalar111) {
                scalar168 = scalar111;
            }
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xA)) {
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * scalar168);
        }
        if (FastFloatHelperD((s32)(gHeroState + 0xA30)) != 0) {
            heroBlockA30 = (void*)gHeroState;
            TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], 4, (s32)((TI128*)vecA));
            (*(TI128*)vecC) = 0;
            vecC[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((Hero *)gHeroState)->ptr[0x2290/4] + 0xC0));
            FastVecAdd((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)vecC));
            qcopy(vecB, &((Hero *)gHeroState)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), (s32) ((TI128*)vecC));
            vecB[2] += 0.033333335f;
            SpawnBubbleParticle((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 25200.0f, -1.0f);
            if ((f32) RandomIntBelow(0x64) < 40.0f) {
                value58 = 4;
                value62 = 0xB;
            } else {
                value58 = 0x28;
                value62 = 0x5A;
            }
            ((Hero *)heroBlockA30)->i[0xA30/4] = RandomIntRange(value58, value62);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)gHeroState) + 0xA38)) != 0) {
                ptr41 = ((Hero *)gHeroState)->ptr[0x1310/4];
                if (ptr41 != 0) {
                    if (M2C_FIELD(ptr41, s16* , 0xAA) == 0x261 /* moby class 609 */) {
                        for (value66 = 0; value66 < 4; value66++) {
                            TransformMobyJointToWorld((s32) ptr41, value66 % 2, (s32)((TI128*)vecA));
                            (*(TI128*)vecC) = 0;
                            vecC[0] = -0.15f;
                            matrix_mul_vec3((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((Hero *)gHeroState)->ptr[0x2290/4] + 0xC0));
                            FastVecAdd((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)vecC));
                            vecA[0] += RandomFloatRange(0.0f, 0.03f);
                            vecA[1] += RandomFloatRange(0.0f, 0.03f);
                            vecA[2] += RandomFloatRange(0.0f, 0.03f);
                            qcopy(vecB, &((Hero *)gHeroState)->q[0x110/16]);
                            AddOffsetVector((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), -0.012500001f, ((Hero *)gHeroState)->f[0x98/4], ((Hero *)gHeroState)->f[0x94/4]);
                            ((Hero *)gHeroState)->h[0xA38/2] = FloatToInt((0.116666675f - ((Hero *)gHeroState)->f[0x1B4/4]) * 42.85714f);
                            SpawnBubbleParticle((s32)((TI128*)vecA), (s32) ((TI128*)vecB), RandomFloatRange(6300.0f, 9450.0f), -1.0f);
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
        scalar89 = FastAddRotations(-((Hero *)gHeroState)->f[0x94/4], 0.0f);
        value83 = ((Hero *)gHeroState)->u[0x2294/4];
        if (value83 == 0x34) {
            BuildSphericalOffset((s32) (((void*)gHeroState) + 0xF0), ((Hero *)gHeroState)->f[0x1B4/4], ((Hero *)gHeroState)->f[0x98/4], scalar89);
        } else if (value83 == 0x32) {
            scalar135 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L20_00269110, 0x1E) * 5.0f;
            if ((((Hero *)gHeroState)->i[0x22A0/4] == 0x34) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xF) && (scalar135 < 0.075f)) {
                scalar135 = 0.075f;
            }
            BuildSphericalOffset((s32)(gHeroState + 0xF0), scalar135, ((Hero *)gHeroState)->f[0x98/4], scalar89);
        } else if (value83 == 0x33) {
            scalar5 = FastVecLength((s32) (((void*)gHeroState) + 0x160));
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &scalar5, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &scalar5, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), scalar5);
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        }
        SlideYeedilHeroAlongWall(0);
        scalar90 = ((Hero *)gHeroState)->f[0xA2C/4] * FastSinOrCosA(scalar89) * -7.0f;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), scalar90, (s32) (((void*)gHeroState) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        scalar96 = scalar92 * 47.0f;
        ((Hero *)D_L20_00267210)->f[0x114/4] = scalar96;
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar90 * 1.5f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar90 * 1.4f);
        if (scalar96 > 0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = 0.8726647f;
        } else if (scalar96 < -0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = -0.8726647f;
        }
        scalar63 = scalar92 * 40.0f;
        scalar37 = scalar90 * 1.1f;
        ((Hero *)D_L20_00267210)->f[0x364/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x368/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x324/4] = scalar63;
        ((Hero *)D_L20_00267210)->f[0x328/4] = scalar37;
        ((Hero *)D_L20_00267210)->f[0x414/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x418/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x3D4/4] = scalar63;
        ((Hero *)D_L20_00267210)->f[0x3D8/4] = scalar37;
        break;
    case 0x73:                                      /* switch 1 */
        value14 = 0xA - ((s32) ((Hero *)gHeroState)->i[0x1B8/4] / 3);
        ptr28 = ((void*)gHeroState) + 0xF0;
        EmitHeroRandomizedMotionEffects((value14 >= 9) ? 8 : value14, 0, 0);
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) ptr28, (s32) ptr28, vec_length_xy((s32) ptr28) * 0.92f);
        SlideYeedilHeroAlongWall(0);
        break;
    case 0x72:                                      /* switch 1 */
        SpawnJitteredParticleAfterDelay(0xF, 0x1E);
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), vec_length_xy((s32)(gHeroState + 0xF0)) * 0.92f);
        SlideYeedilHeroAlongWall(0);
        UpdateHeroHeightOffset();
        break;
    case 0x67:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
        scalar6 = FastVecLength((s32)(gHeroState + 0x160));
        ApproachValue((s32) &scalar6, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), scalar6);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        if (FastFloatHelperD((s32) (((void*)(gHeroState + 0x160)) + 0x8D0)) == 2) {
            ptr36 = ((void*)(gHeroState + 0x160)) - 0x160;
            TransformMobyJointToWorld(M2C_FIELD(ptr36, s32* , 0x2290), 4, (s32)((TI128*)vecA));
            (*(TI128*)vecC) = 0;
            vecC[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), M2C_FIELD(ptr36, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)vecC));
            qcopy(vecB, &((Hero *)gHeroState)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), 0.025000002f);
            FastVecAdd((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), (s32) ((TI128*)vecC));
            vecB[2] += 0.033333335f;
            SpawnBubbleParticle((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 25200.0f, -1.0f);
            value37 = M2C_FIELD(ptr36, s32* , 0x1B8);
            if (value37 < 0x28) {
                limitA = 5;
                value71 = RandomIntRange(2, limitA) + ((s32) M2C_FIELD(ptr36, s32* , 0x1B8) / limitA);
                goto block_224;
            }
            if (value37 >= 0x47) {
                value71 = RandomIntRange(0xA, 0x14);
block_224:
                M2C_FIELD(ptr36, s32* , 0xA30) = value71;
            }
        }
        if (((Hero *)gHeroState)->f[0xA3C/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xA3C/4] = 0.0f;
        }
        ApproachValue((s32) (((void*)gHeroState) + 0xA3C), -0.025000002f, 0.00041666668f);
        ((Hero *)gHeroState)->f[0xF8/4] = (f32) ((Hero *)gHeroState)->f[0xA3C/4];
        break;
    case 0x35:                                      /* switch 1 */
    case 0x36:                                      /* switch 1 */
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
            value15 = ((Hero *)gHeroState)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((value15 >= 7) ? 6 : value15, 0, 0);
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
            scalar81 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L20_00269110, 0x1E) * 5.5f;
            ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * scalar81);
            scalar39 = FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * scalar81;
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ((Hero *)gHeroState)->f[0xF4/4] = scalar39;
        } else {
            ((Hero *)gHeroState)->f[0x1B4/4] = 0.0f;
            ClearVector128((s32)(gHeroState + 0xF0));
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x35) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            scalar64 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((scalar64 > 0.0f) && (scalar64 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        ShrinkHeroVectorByAmount(0.0011666666f);
        SlideYeedilHeroAlongWall(0);
        UpdateHeroHeightOffset();
        break;
    case 0x85:                                      /* switch 1 */
        ptr19 = ((Hero *)gHeroState)->ptr[0x1830/4];
        qcopy(&((Hero *)gHeroState)->q[0x80/16], (u8 *)ptr19 + 0x10);
        qcopy(&((Hero *)gHeroState)->q[0x90/16], (u8 *)ptr19 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)vecA), (s32)(gHeroState + 0x2C0), -1.0f);
        scalar136 = 0.0f;
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            scalar136 = -((Hero *)gHeroState)->f[0x1FB4/4] * 0.75f;
        }
        SpringFloatToGoal((s32)(gHeroState + 0x7C0), (s32)(gHeroState + 0x7C4), scalar136, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)vecB), (s32)gHeroState, ((Hero *)gHeroState)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)vecB));
        vec_scale_to_length((s32)((TI128*)vecA), (s32)((TI128*)vecA), 1.0f);
        ApplyHeroReferenceTiltRotation((s32)((TI128*)vecA), (s32) ((TI128*)vecD), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)gHeroState)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)gHeroState, 0.21666668f);
        SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
        ClearVector128((s32)((TI128*)vecA));
        vecA[1] = -((Hero *)gHeroState)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(gHeroState + 0x190), (s32)((TI128*)vecA), (s32)&D_L20_001B9FD8[0x218]);
        SteerHeroHeading(0, 0.02f, 0.3f, 0.034906592f);
        break;
    case 0x2F:                                      /* switch 1 */
        animIdA = -1;
        blendA = 0;
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
        if ((animIdA != -1) && (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x42) != 0x36)) {
            set_hero_animation(animIdA, 0, (f32) blendA);
        } else {
            ptr49 = ((Hero *)gHeroState)->ptr[0x2290/4];
            if ((M2C_FIELD(ptr49, u8* , 0x60) & 2) && (M2C_FIELD(ptr49, u8* , 0x42) == 0x36)) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 5.0f);
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
        ptr60 = ((Hero *)gHeroState)->ptr[0xB10/4];
        if (ptr60 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(ptr60, f32* , 0x10) - M2C_FIELD(heroObject, f32* , 0x10), M2C_FIELD(ptr60, f32* , 0x14) - M2C_FIELD(heroObject, f32* , 0x14));
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
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(ptr1, f32* , 0x10) - M2C_FIELD(heroObject, f32* , 0x10), M2C_FIELD(ptr1, f32* , 0x14) - M2C_FIELD(heroObject, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(vecA, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        scalar40 = fast_vec_dist((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)vecA));
        ((Hero *)gHeroState)->f[0xAB0/4] = scalar40;
        ((Hero *)gHeroState)->f[0xAAC/4] = 60.0f;
        if (((Hero *)gHeroState)->f[0xAA0/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xAAC/4] = (f32) (scalar40 / ((Hero *)gHeroState)->f[0x170/4]);
        }
        value38 = ((Hero *)gHeroState)->i[0x2298/4];
        if (value38 == 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.45000002f, 0.022222223f);
            ptr45 = ((Hero *)gHeroState)->ptr[0xAA4/4];
            scalar150 = FastMatrixHelperA(M2C_FIELD(ptr45, f32* , 0x10) - M2C_FIELD(heroObject, f32* , 0x10), M2C_FIELD(ptr45, f32* , 0x14) - M2C_FIELD(heroObject, f32* , 0x14));
            if (((Hero *)gHeroState)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], scalar150) > 1.5707964f) {
                    scalar150 = FastAddRotations(scalar150, 3.1415927f);
                }
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = scalar150;
            SteerHeroHeading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (value38 == 1) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((SolveQuadratic((s32) &scalar7, (s32) &scalar8, -0.0058333334f, ((Hero *)gHeroState)->f[0xAA0/4], 1.9f - ((Hero *)gHeroState)->f[0xAB0/4]) > 0) && (scalar7 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xAAC/4] = scalar7;
            ((Hero *)gHeroState)->i[0x2298/4] = 1;
        }
        ((Hero *)gHeroState)->h[0x226/2] = 3;
        if (((Hero *)gHeroState)->f[0xAAC/4] < 20.0f) {
            ((Hero *)gHeroState)->i[0xAB4/4] = 1;
        }
        if (((Hero *)gHeroState)->i[0xAB4/4] != 0) {
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, 0.0f, 0.06399541f);
        } else {
            turnAmount = FastAddRotations(-FastMatrixHelperA(vec_distance_xy((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)vecA)), vecA[2] - ((Hero *)gHeroState)->f[0x88/4]), 1.5707965f);
            StepAngleTowardTarget((s32) (((void*)gHeroState) + 0x94), 0, turnAmount, 0.10762865f);
        }
        vecC[0] = FastSinOrCosA(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        scalar41 = FastSinOrCosB(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        vecC[2] = 0;
        vecC[1] = scalar41;
        FastVecAdd((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((void*)gHeroState) + 0x80));
        FastVecSub((s32) ((TI128*)vecB), (s32) (((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)vecC));
        vec_scale_to_length((s32) (((void*)gHeroState) + 0xF0), (s32) ((TI128*)vecB), ((Hero *)gHeroState)->f[0xAA0/4]);
        scalar42 = ((Hero *)gHeroState)->f[0xAAC/4];
        if (scalar42 < 30.0f) {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - ((30.0f - scalar42) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
        ApproachValue((s32)(gHeroState + 0xABC), ((Hero *)gHeroState)->f[0xAC0/4], 0.16666667f);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x110/16]);
        FastVecScale((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.9f);
        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.004166667f);
        qcopy(vecA, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        ((Hero *)gHeroState)->f[0xAB0/4] = fast_vec_dist((s32)(gHeroState + 0x80), (s32)((TI128*)vecA));
        FastVecAdd((s32) ((TI128*)vecB), (s32)(gHeroState + 0x80), (s32)(gHeroState + 0xF0));
        FastVecSub((s32) ((TI128*)vecD), (s32) ((TI128*)vecB), (s32)((TI128*)vecA));
        vec_scale_to_length((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), ((Hero *)gHeroState)->f[0xABC/4]);
        FastVecAdd((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) ((TI128*)vecD));
        FastVecSub((s32)(gHeroState + 0xF0), (s32) ((TI128*)vecC), (s32)(gHeroState + 0x80));
        break;
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC28/4] & 2) && (M2C_FIELD(heroObject, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)gHeroState)->f[0xC20/4] = 0.3f;
        }
        ptr50 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        scalar95 = ((Hero *)gHeroState)->f[0xF8/4];
        if (ptr50 != 0) {
            ptr46 = M2C_FIELD(ptr50, void** , 0x68);
            if ((ptr46 != 0) && (M2C_FIELD(ptr46, s32* , 0x34) != 0)) {
                scalar151 = M2C_FIELD(ptr50, f32* , 0xF8);
                if (FastDiffRots(scalar151, ((Hero *)gHeroState)->f[0x98/4]) > 90.0f) {
                    scalar151 = FastAddRotations(scalar151, 3.1415927f);
                }
                ApproachWithVelocity((s32) (((void*)gHeroState) + 0xAEC), scalar151, (s32) (((void*)gHeroState) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xAEC/4];
        SteerHeroHeading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)vecA), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) (((void*)gHeroState) + 0x80));
        vec_scale_to_length((s32)((TI128*)vecA), (s32)((TI128*)vecA), 1.0f);
        if (vecA[2] < 0.23f) {
            vecA[2] = 0.23f;
        }
        ClearVector128((s32) ((TI128*)vecG));
        vecG[2] = ((Hero *)gHeroState)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)vecC), (s32) ((TI128*)vecG));
        matrix_from_basis_rows((s32) ((TI128*)matrixA), (s32) ((TI128*)vecC));
        transform_vector((s32)((TI128*)vecA), (s32)((TI128*)vecA), (s32) ((TI128*)matrixA));
        vecB[0] = -FastMatrixHelperA(square_root((vecA[0] * vecA[0]) + (vecA[2] * vecA[2])), vecA[1]);
        scalar43 = FastMatrixHelperA(vecA[2], vecA[0]);
        vecB[1] = scalar43;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), scalar43, (s32) (((void*)gHeroState) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), vecB[0], (s32) (((void*)gHeroState) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        value69 = ((Hero *)gHeroState)->f[0x88/4] < M2C_FIELD(((Hero *)gHeroState)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
            if ((value69 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0x29) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.25f)) {
                ResolveStickInputToDirection(1.0f, 0);
                scalar152 = ((Hero *)gHeroState)->f[0x24B8/4] * 0.0035f;
                if (scalar152 > 0.083333336f) {
                    scalar152 = 0.083333336f;
                }
                vecH[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0x1A0/4]) * scalar152;
                scalar44 = FastSinOrCosB(((Hero *)gHeroState)->f[0x1A0/4]) * scalar152;
                ptr9 = ((void*)gHeroState) + 0xF0;
                (*(s32*)&vecH[2]) = 0;
                vecH[1] = scalar44;
                FastVecAdd((s32) ptr9, (s32) ptr9, (s32) ((TI128*)vecH));
            }
            if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
                ptr37 = ((void*)gHeroState) + 0x80;
                if ((vec_distance_xy((s32) ptr37, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10)) < (((Hero *)gHeroState)->f[0xAE0/4] * 1.57f)) || (((Hero *)gHeroState)->f[0x31C/4] > 1.5f)) {
                    ptr29 = ((void*)gHeroState) + 0xF0;
                    ApplyHeroModeTransform((s32) ptr29, (s32) (((void*)gHeroState) + 0x110), 0.011111111f);
                    if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (GetViewSpaceHeight((s32) ptr29) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vecH), (s32) ptr37, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
                        ApplyHeroModeTransform((s32) ptr29, (s32) ptr29, 0.015833333f);
                    }
                }
                scalar82 = FastVecLength((s32)(gHeroState + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vecH), (s32)(gHeroState + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vecH), (s32) ((TI128*)vecH), scalar82);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)vecH));
            }
        }
        ptr47 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        if (ptr47 != 0) {
            ptr21 = M2C_FIELD(ptr47, void** , 0x68);
            ptr30 = ((void*)gHeroState) + 0xF0;
            if (ptr21 != 0) {
                scalar45 = FastVecLength((s32) ptr30);
                scalar46 = M2C_FIELD(ptr21, f32* , 0xC);
                scalar9 = scalar45;
                if (scalar46 < scalar45) {
                    ApproachValue((s32) &scalar9, scalar46, 0.004166667f);
                    vec_scale_to_length((s32) ptr30, (s32) ptr30, scalar9);
                }
            }
        }
        scalar17 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f);
        ptr43 = ((void*)gHeroState) + 0x80;
        ptr42 = ((void*)gHeroState) + 0xF0;
        vecJ[0] = FastSinOrCosA(scalar17) * 0.15f;
        scalar18 = FastSinOrCosB(scalar17) * 0.15f;
        (*(s32*)&vecJ[2]) = 0;
        vecJ[1] = scalar18;
        FastVecAdd((s32) &vecJ[0], (s32) &vecJ[0], (s32) ptr43);
        FastVecAdd((s32) ((TI128*)vecH), (s32) &vecJ[0], (s32) ptr42);
        FastVecSub((s32) ((TI128*)vecI), (s32) ((TI128*)vecH), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vecI), (s32) ((TI128*)vecI), ((Hero *)gHeroState)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vecH), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vecI));
        FastVecSub((s32) ptr42, (s32) ((TI128*)vecH), (s32) &vecJ[0]);
        scalar83 = ((Hero *)gHeroState)->f[0xAE4/4];
        SpringFloatToGoal((s32) (((void*)gHeroState) + 0xAE4), (s32) (((void*)gHeroState) + 0xAE8), ((Hero *)gHeroState)->f[0xAE0/4], ((Hero *)gHeroState)->f[0xB04/4], ((Hero *)gHeroState)->f[0xB08/4], ((Hero *)gHeroState)->f[0xB0C/4]);
        scalar84 = ((Hero *)gHeroState)->f[0xAE4/4] - scalar83;
        if (((Hero *)gHeroState)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vecI))) {
            vec_scale_to_length((s32) ((TI128*)vecI), (s32) ((TI128*)vecI), scalar84);
            FastVecAdd((s32) ptr43, (s32) ptr43, (s32) ((TI128*)vecI));
        }
        if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (value69 != 0)) {
            minValueA = 0.23333335f;
            scalar19 = vec_length_xy((s32) ptr42);
            scalar10 = scalar19;
            if (scalar19 < minValueA) {
                SpringFloatToGoal((s32) &scalar10, (s32) (((void*)gHeroState) + 0xAF4), minValueA, 0.047f, 0.3f, 0.0f);
                vecH[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0xAEC/4]) * ((Hero *)gHeroState)->f[0xAF4/4];
                scalar20 = FastSinOrCosB(((Hero *)gHeroState)->f[0xAEC/4]);
                vecH[2] = 0.0f;
                vecH[1] = scalar20 * ((Hero *)gHeroState)->f[0xAF4/4];
                FastVecAdd((s32) ptr42, (s32) ptr42, (s32) ((TI128*)vecH));
            }
        }
        if ((((Hero *)gHeroState)->h[0xADC/2] != 0) && (((Hero *)gHeroState)->h[0x34E/2] != 0) && (((scalar95 < 0.0f) && (((Hero *)gHeroState)->f[0xF8/4] > 0.0f)) || (((Hero *)gHeroState)->h[0xAFC/2] != 0))) {
            ((Hero *)gHeroState)->h[0xAFE/2] = 0;
            scalar85 = square_root(((Hero *)gHeroState)->f[0xAE0/4] / ((Hero *)gHeroState)->f[0xAF0/4]) * 3.1415927f;
            shortVal2 = ((Hero *)gHeroState)->h[0xAFC/2];
            if (shortVal2 != 0) {
                value72 = shortVal2 == 1;
            } else {
                (*(TI128*)vecH) = ((Hero *)gHeroState)->q[0x110/16];
                value72 = GetSpeedAlongHeroForward((s32) ((TI128*)vecH)) > 0.0f;
            }
            if (value72 != 0) {
                if (M2C_FIELD(heroObject, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 1;
                } else {
                    ptr48 = ((Hero *)gHeroState)->ptr[0x2290/4];
                    if (M2C_FIELD(ptr48, u8* , 0x42) == M2C_FIELD(ptr48, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, scalar85, 0.5f, -1.0f);
                        ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(heroObject, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)gHeroState)->h[0xAFC/2] = 2;
            } else {
                ptr44 = ((Hero *)gHeroState)->ptr[0x2290/4];
                if (M2C_FIELD(ptr44, u8* , 0x42) == M2C_FIELD(ptr44, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, scalar85, 0.5f, -1.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                }
            }
        }
        break;
    case 0x14:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            value16 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (value16 != 0) {
                scalar65 = vec_distance_xy((s32) (((void*)gHeroState) + 0x80), value16 + 0x10);
                value78 = 0;
                if ((((Hero *)gHeroState)->b[0x1496] != 0) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->b[0x1495] != 0)) {
                    value78 = 1;
                }
                if (((scalar65 > 2.0f) && (scalar65 < 5.0f)) || (value78 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0011111111f, 0.0011111111f);
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
            } else {
                ApproachHeroSpeed(0.00055555557f, 0.00055555557f);
                ptr10 = ((void*)gHeroState) + 0xF0;
                SetViewSpaceVectorLength((s32) ptr10, (s32) ptr10, ((Hero *)gHeroState)->f[0x1B4/4]);
            }
        } else {
            value67 = 0;
            if ((((Hero *)gHeroState)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->f[0x31C/4] > 4.0f)) {
                value67 = 1;
            }
            value17 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (value17 != 0) {
                FastVecSub((s32)((TI128*)vecA), value17 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                scalar21 = GetViewSpaceVectorLength((s32)((TI128*)vecA));
                if (((scalar21 > 2.0f) && (scalar21 < 5.0f)) || (value67 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0069444445f, 0.0069444445f);
                vec_scale_to_length((s32) ((TI128*)vecB), (s32)gHeroState, ((Hero *)gHeroState)->f[0x1B4/4]);
                SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)vecB));
            } else {
                if ((value67 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 0x46)) {
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
        scalar66 = ((Hero *)gHeroState)->f[0x31C/4];
        scalar158 = 0.12833333f;
        if (scalar66 > 2.25f) {
            scalar158 = 0.064166665f;
        } else if (scalar66 > 1.8f) {
            scalar158 = 0.08983333f;
        }
        if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 23.5f) && (((Hero *)gHeroState)->f[0x118/4] < 0.0f) && (((Hero *)gHeroState)->h[0x34E/2] != 0)) {
            qcopy(vecA, &((Hero *)gHeroState)->q[0x80/16]);
            ApplyHeroModeTransformReversed((s32)((TI128*)vecA), (s32)((TI128*)vecA), -0.5f);
            vec_scale_to_length((s32) &vecE[0], (s32)gHeroState, 2.0f);
            make_hit_descriptor((s32) ((TI128*)vecB), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 2.0f, (s32) &vecE[0]);
            vecB[3] = 5627.925f;
            (*(u8*)((u8*)vecC+9)) = 1;
            (*(u16*)((u8*)vecC+10)) = 0x47;
            (*(u8*)((u8*)vecC+8)) = 0;
            ProcessCollisionHit(0.4f, (s32)((TI128*)vecA), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)vecB));
        }
        if (IsBelowPlaneWithinDepth(25.7f) != 0) {
            QueueRecordsByIndex(0x19);
            ((Hero *)gHeroState)->h[0x1FA/2] = 0x32;
            if (D_001A7B2A != 0) {
                ((Hero *)D_L20_001B9E80)->f[0x180/4] = 0.1f;
                ((Hero *)D_L20_001B9E80)->i[0x188/4] = 0x1E;
                ((Hero *)gHeroState)->h[0x224/2] = 0x23;
                ((Hero *)D_L20_001B9E80)->i[0x16C/4] = 0;
            }
        }
        value39 = ((Hero *)gHeroState)->i[0x1B8/4];
        limit3 = 0xE;
        if (value39 < 9) {
            ptr22 = ((void*)gHeroState) + 0xF0;
            scalar11 = GetViewSpaceHeight((s32) ptr22);
            ApproachValue((s32) &scalar11, scalar158, 0.041666668f);
            SetViewSpaceHeight((s32) ptr22, (s32) ptr22, scalar11);
        } else if (value39 > limit3) {
            ptr31 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) ptr31, (s32) ptr31, 0.036111113f);
            if (GetViewSpaceHeight((s32) ptr31) < 0.0f) {
                ((Hero *)gHeroState)->f[0xC00/4] = 1.0f;
            }
            scalar153 = -0.6166667f;
            if (D_L20_001A8FF0 != 0) {
                scalar153 = -1.1666667f;
            }
            if (GetViewSpaceHeight((s32) ptr31) < scalar153) {
                SetViewSpaceHeight((s32) ptr31, (s32) ptr31, scalar153);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        value60 = (((Hero *)gHeroState)->i[0x22A0/4] == 1) && (((Hero *)gHeroState)->i[0x22A8/4] >= 0x15);
        if (value60 == 0) {
            if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
                value68 = 0;
                if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                    ptr23 = ((void*)gHeroState) + 0xBC0;
                    scalar154 = GetDirectionAngleDelta((s32) ptr23, 0);
                    scalar112 = GetDirectionAngleDelta((s32) ptr23, 1);
                } else {
                    scalar154 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                    scalar112 = GetShortestAngleDelta(1, ((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                }
                if (scalar112 < 4.3633237f) {
                    value68 = 1;
                }
                if (scalar154 > 0.0f) {
                    ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (scalar112 + 1.0f));
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
                scalar159 = 0.041666668f;
                scalar86 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    scalar159 = 0.050000004f;
                }
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(scalar86) * scalar159));
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(scalar86) * scalar159));
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
    case 0x13:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]].w[0x20/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            SteerHeroReferencePoint();
            break;
        }
        value18 = ((Hero *)gHeroState)->i[0xBE4/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ptr38 = (((Hero *)gHeroState)->h[0xBFC/2] * 0x2C) + (s32)D_L20_00268D90;
        if ((value18 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 4)) {
            ptr32 = ((void*)gHeroState) + 0x80;
            scalar122 = vec_distance_xy(value18 + 0x10, (s32) ptr32);
            if ((*(s32*)&D_L20_001A8FF0) != 0) {
                scalar122 = fast_vec_dist(((Hero *)gHeroState)->i[0xBE4/4] + 0x10, (s32) ptr32);
            }
            scalar122 = scalar122 - 0.5f;
            if (scalar122 < 0.0f) {
                scalar122 = 0.0f;
            }
            value40 = M2C_FIELD(ptr38, s32* , 4);
            if (value40 == 0) {
                scalar113 = 0.75f;
                scalar160 = 0.8f;
                scalar165 = 4.0f;
            } else if (value40 == 1) {
                scalar113 = 0.6f;
                scalar160 = 1.7f;
                scalar165 = 4.0f;
            } else {
                scalar113 = 1.3f;
                scalar160 = 1.7f;
                scalar165 = 1.9f;
            }
            scalar87 = scalar122 - scalar113;
            if (FloatAbs(scalar87) < (scalar160 + 3.0f)) {
                scalar124 = scalar87 * 1.1111112f;
                if (scalar165 < scalar124) {
                    scalar124 = scalar165;
                }
                if (scalar124 > 1.0f) {
                    ((Hero *)gHeroState)->f[0xBF4/4] = scalar124;
                }
            }
        }
        value41 = M2C_FIELD(ptr38, s32* , 4);
        switch (value41) {
        case 0:
            if (((Hero *)gHeroState)->f[0xC38/4] < 18.0f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            scalar67 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (scalar67 < 9.0f)) {
                if (scalar67 > 8.0f) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.050000004f;
                } else if (scalar67 > 7.0f) {
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
            scalar114 = GetDirectionAngleDelta((s32)(gHeroState + 0xBC0), 0);
        } else {
            scalar114 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
        }
        scalar68 = FloatAbs(scalar114);
        if ((M2C_FIELD(ptr38, s32* , 4) == 1) && (scalar114 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (scalar68 + 1.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
        qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        value79 = 1;
        if ((M2C_FIELD(ptr38, s32* , 4) == 1) && (((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 7.0f)) {
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
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
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
        limit = 0xA;
        limit2 = 0x12;
        value42 = ((Hero *)gHeroState)->i[0x1B8/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (value42 > limit) {
            if (value42 < 0x12) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)gHeroState)->i[0x1B8/4] == 8) && (((Hero *)gHeroState)->f[0x184/4] < 0.33333334f)) {
            ptr24 = ((void*)gHeroState) + 0x18E0;
            InitPendingSlot((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ptr24);
            AppendRecordToFourEntryTable((s32) ptr24, 0x30, 2, 0.0f);
            AppendRecordToFourEntryTable((s32) ptr24, 0x17, 4, 0.0f);
            AppendRecordToFourEntryTable((s32) ptr24, 0xC, 6, 0.0f);
        }
        selectionA = (((Hero *)gHeroState)->i[0x1B8/4] > limit2) ? 5 : 0;
        UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), selectionA);
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            value43 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((value43 > limit) && (value43 < 0x11) && (((Hero *)gHeroState)->f[0x178/4] < 0.14166668f)) {
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.020000001f));
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.020000001f));
                qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
            }
            SteerHeroReferencePoint();
        } else {
            if (((Hero *)gHeroState)->i[0x1B8/4] > limit) {
                ApproachHeroSpeed(0.05277778f, 0.025f);
            }
            if (((Hero *)gHeroState)->i[0xBE8/4] != 0) {
                ComputeHeroPushDirection(((Hero *)gHeroState)->f[0xBEC/4]);
            } else {
                ComputeHeroPushDirection(99999.0f);
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x1F) {
            value44 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((value44 > limit) && (value44 < 0x16)) {
                ptr39 = ((Hero *)gHeroState)->ptr[0x1220/4];
                if (ptr39 != 0) {
                    ptr33 = ((void*)gHeroState) + 0x80;
                    vecD[0] = 2.0f * FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]);
                    vecD[1] = 2.0f * FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]);
                    vecD[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)vecA), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)vecD));
                    (*(u8*)((u8*)vecB+9)) = 3;
                    vecA[3] = 5627.925f;
                    (*(u8*)((u8*)vecB+8)) = 0;
                    scalar93 = ((Hero *)gHeroState)->f[0x98/4];
                    (*(u16*)((u8*)vecB+10)) = M2C_FIELD(ptr39, u16* , 0xAA);
                    vecE[0] = FastSinOrCosA(scalar93) * 0.8f;
                    scalar22 = FastSinOrCosB(scalar93) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = scalar22;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) ptr33);
                    EmitEffectsAtNearbyObjects((s32) ptr39, ProcessCollisionHit(0.8f, (s32) &vecE[0], 0, (s32) ptr39, (s32)((TI128*)vecA)));
                    scalar93 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -0.8726647f);
                    vecE[0] = FastSinOrCosA(scalar93) * 0.8f;
                    scalar24 = FastSinOrCosB(scalar93) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = scalar24;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) ptr33);
                    EmitEffectsAtNearbyObjects((s32) ptr39, ProcessCollisionHit(0.8f, (s32) &vecE[0], 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)vecA)));
                    scalar93 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 0.8726647f);
                    vecE[0] = FastSinOrCosA(scalar93) * 0.8f;
                    scalar26 = FastSinOrCosB(scalar93) * 0.8f;
                    vecE[2] = 0.55f;
                    vecE[1] = scalar26;
                    FastVecAdd((s32) &vecE[0], (s32) &vecE[0], (s32) ptr33);
                    EmitEffectsAtNearbyObjects((s32) ptr39, ProcessCollisionHit(0.8f, (s32) &vecE[0], 0, (s32) ptr39, (s32)((TI128*)vecA)));
                }
            }
        }
        if (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        SlideYeedilHeroAlongWall(1);
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
        value55 = 0;
        if ((((Hero *)gHeroState)->b[0x1494] != 0) && (((Hero *)gHeroState)->f[0x24C4/4] < 0.25f)) {
            value55 = 1;
        }
        if ((((Hero *)gHeroState)->b[0x22B9] != 0) || (value55 != 0)) {
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
            scalar88 = ReadPadFloatHistory(1);
            if ((FastDiffRots(scalar88, ReadPadFloatHistory(7)) > 1.9198624f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
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
            ptrA60 = ((void*)gHeroState) + 0xA60;
            BuildHeroMoveImpulse(0.7f, 0.0f);
            (*(TI128*)vecA) = ((Hero *)gHeroState)->q[0xA60/16];
            scalar69 = ((Hero *)gHeroState)->f[0x1B0/4] + GetSpeedAlongHeroForward((s32)((TI128*)vecA));
            ((Hero *)gHeroState)->f[0x1B0/4] = scalar69;
            if (scalar69 < 0.011666667f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.011666667f;
            }
            ClearVector128((s32) ptrA60);
        }
        scalar155 = 1.0f;
        if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
            UpdateHeroTurnFromAnimation();
        } else {
            ((Hero *)gHeroState)->f[0x1458/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
            qcopy(&((Hero *)gHeroState)->q[0x1440/16], &((Hero *)gHeroState)->q[0x0/16]);
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (((Hero *)gHeroState)->b[0x40F] == 0) && (((Hero *)gHeroState)->b[0x22BA] == 0)) {
                SteerHeroHeading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                scalar97 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
                if (((((Hero *)gHeroState)->f[0x24B8/4] < 0.9f) || ((((Hero *)gHeroState)->b[0x22BA] != 0) && (((Hero *)gHeroState)->b[0x40F] == 0))) && (scalar97 > 0.78539824f)) {
                    scalar155 = 0.0f;
                }
                SetHeroTurnRates();
            }
        }
        ApplyHeroModePoseOffsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar169 = 0.09916667f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.029178405f);
            if (scalar169 < 0.0f) {
                scalar169 = 0.0f;
            }
            if (scalar169 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = scalar169;
            }
        }
        constB = scalar155 * 0.005f;
        scalar156 = 0.0055555557f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar141 = 2.617994f - ((Hero *)gHeroState)->f[0x1A8/4];
            if (scalar141 > 1.0f) {
                scalar141 = 1.0f;
            }
            if (scalar141 < 0.2f) {
                scalar141 = 0.2f;
            }
            scalar156 = 0.004722222f;
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * scalar141);
        }
        scalar98 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
        if ((((Hero *)gHeroState)->f[0x24B8/4] < 0.75f) && (scalar98 > 0.6108653f)) {
            scalar142 = 1.0f - (scalar98 * 0.4f);
            if (scalar142 < 0.0f) {
                scalar142 = 0.0f;
            }
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * scalar142);
        }
        ApproachHeroSpeed(constB, scalar156);
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
        SlideYeedilHeroAlongWall(1);
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
        ClampStickToUnitRange((s32)((TI128*)vecA), (s32) (((void*)gHeroState) + 0x9F0), 0.17f);
        scalar161 = (((Hero *)gHeroState)->f[0x24B8/4] * 0.020362178f) * vecA[0];
        if ((*(s32*)&D_L20_001A8FF0) == 0) {
            if (((Hero *)gHeroState)->i[0x1B8/4] < 0x3C) {
                scalar161 *= 0.1f;
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            RotateHeroMatrix(0.0f, 0.0f, scalar161);
        }
        ApproachHeroSpeed(0.027777778f, 0.004166667f);
        ComputeHeroPushDirection(99999.0f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
            qcopy(vecB, &((Hero *)gHeroState)->q[0x2D0/16]);
            ApplyHeroModeTransformReversed((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), 0.17f);
            SpringVectorToTarget((s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            SpringFloatToGoal((s32) (((void*)gHeroState) + 0x88), (s32) (((void*)gHeroState) + 0xA00), ((Hero *)gHeroState)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)vecB), (s32)(gHeroState + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)vecB), (s32) ((TI128*)vecB), (s32)(gHeroState + 0xE0));
        value29 = ProcessCollisionHit(0.57f, (s32) ((TI128*)vecB), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        if (value29 != 0) {
            FastVecScale((s32) ((TI128*)vecC), (s32)(gHeroState + 0x110), 7.0f);
            for (value64 = 0; value64 < value29; value64++) {
                if (IsMobyInSpecialClassRange(((s32 *)D_L20_001C4480)[value64]) != 0) {
                    QueueImpactEffect(((s32 *)D_L20_001C4480)[value64], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vecC), 1.0f);
                }
            }
        }
        SetCameraLimitsSlot0(0.017f, 0.3f);
        SetCameraLimitsSlot2(0.025f, 0.3f);
        SetCameraLimitsSlot3(0.03f, 0.27f);
        scalar170 = scalar161 * 27.0f;
        if (scalar170 > 1.7f) {
            scalar170 = 1.7f;
        } else if (scalar170 < -1.7f) {
            scalar170 = -1.7f;
        }
        scalar27 = scalar170 * 0.5f;
        ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) -scalar170;
        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar27;
        ((Hero *)D_L20_00267210)->f[0x1C8/4] = scalar27;
        break;
    case 0x2E:                                      /* switch 1 */
        SteerHeroReferencePoint();
        SetCameraLimitsSlot0(0.04f, 0.2f);
        SetCameraLimitsSlot1(0.04f, 0.2f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        byteVal3 = M2C_FIELD(heroObject, u8* , 0x43);
        if (byteVal3 == 0x37) {
            scalar115 = 1.4f;
            scalar157 = ((Hero *)gHeroState)->f[0x1A8/4];
            if ((scalar157 > 1.4f) || (scalar115 = -1.4f, (scalar157 < -1.4f))) {
                scalar157 = scalar115;
            }
            ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) (scalar157 * -0.14f);
            ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar157 * 0.3f);
            ((Hero *)D_L20_00267210)->f[0x1C0/4] = (f32) (scalar157 * -0.22f);
            ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (scalar157 * 0.4f);
            ((Hero *)D_L20_00267210)->f[0x274/4] = (f32) (FloatAbs(scalar157) * -0.09f);
            ((Hero *)D_L20_00267210)->f[0x270/4] = (f32) (FloatAbs(scalar157) * 0.08f);
        } else if (byteVal3 == 0x66) {
            scalar94 = FastAddRotations(fast_subtract_rotations(FastMatrixHelperA(((Hero *)gHeroState)->f[0x110/4], ((Hero *)gHeroState)->f[0x114/4]), ((Hero *)gHeroState)->f[0x98/4]), 3.1415927f);
            scalar162 = ((Hero *)gHeroState)->f[0x174/4] * 6.9813175f;
            if (scalar162 > 0.43633235f) {
                scalar162 = 0.43633235f;
            }
            scalar71 = FastSinOrCosA(scalar94) * scalar162;
            scalar28 = -FastSinOrCosB(scalar94);
            ((Hero *)D_L20_00267210)->f[0x114/4] = scalar71;
            ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar28 * scalar162);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            scalar125 = 0.0069444445f;
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)gHeroState) + 0x110), scalar125);
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        value45 = (*(s32*)&gCurrentMapIndex);
        if (value45 == 0) {
            UpdateSoundSlotObject(2, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x13);
            value74 = gCurrentMapIndex;
        } else {
            if (value45 != 1) {
                UpdateSoundSlotObject(2, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 6);
            }
            value74 = (*(s32*)&gCurrentMapIndex);
        }
        if ((u32) value74 < 2U) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            vecA[0] = ((Hero *)gHeroState)->f[0x80/4] + RandomFloatRange(-0.25f, 0.25f);
            vecA[1] = ((Hero *)gHeroState)->f[0x84/4] + RandomFloatRange(-0.25f, 0.25f);
            vecA[2] = ((Hero *)gHeroState)->f[0x88/4] + RandomFloatRange(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0x110), 0.9f);
            vecB[0] += RandomFloatRange(-0.011666667f, 0.011666667f);
            vecB[1] += RandomFloatRange(-0.011666667f, 0.011666667f);
            vecB[2] = M2C_BITWISE(f32, vecB[2]) + RandomFloatRange(0.016666668f, 0.033333335f);
            SpawnTwoPointEffect((s32)((TI128*)vecA), (s32) ((TI128*)vecB), RandomFloatRange(37800.0f, 75600.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xB40/4];
        scalar72 = ((Hero *)gHeroState)->f[0x98/4];
        SteerHeroHeading(0, 0.033f, 0.3f, 0.069813184f);
        scalar163 = FastDiffRots(((Hero *)gHeroState)->f[0x98/4], scalar72);
        ClearVector128((s32) (((void*)gHeroState) + 0xF0));
        ShrinkHeroVectorByAmount(0.0019444445f);
        scalar29 = ((Hero *)gHeroState)->f[0x118/4] - 0.013888889f;
        ((Hero *)gHeroState)->f[0xF8/4] = scalar29;
        if (scalar29 > -0.011111111f) {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.011111111f;
        }
        if (scalar163 > 0.023271061f) {
            scalar163 = 0.023271061f;
        }
        scalar73 = scalar163 * 9.0f;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), scalar73 * 0.5f, (s32) (((void*)gHeroState) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), -((Hero *)gHeroState)->f[0xB44/4], (s32) (((void*)gHeroState) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (scalar73 * 2.1f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (scalar73 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        value84 = ((Hero *)gHeroState)->u[0x2294/4];
        if (((u32) (value84 - 0x28) >= 2U) && (value84 != 0x3E)) {
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
        value85 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value85 == 0x27) || (value85 == 0x2A)) {
            qcopy(vecA, &((Hero *)gHeroState)->q[0x80/16]);
            scalar74 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.0f, 0.52359885f));
            scalar91 = RandomFloatRange(0.06666667f, 0.116666675f);
            vecB[0] = FastSinOrCosA(scalar74) * scalar91;
            scalar30 = FastSinOrCosB(scalar74) * scalar91;
            vecB[2] = 0.0f;
            vecB[1] = scalar30;
            vecB[2] = RandomFloatRange(0.050000004f, 0.083333336f);
            vecB[3] = -0.008333334f;
            SpawnWhiteFlashParticle((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 0, -1.0f);
        }
        ptr20 = ((Hero *)gHeroState)->ptr[0x1248/4];
        flagA = 0;
        value27 = (((LevelInfo *)D_L20_0026D970)[gItemSlotToRecord[(s32)ptr20]].x1C != 0);
        if ((s32)ptr20 == 0xD) {
            value27 = 0;
        }
        if (value27 != 0) {
            flagA = ((Hero *)gHeroState)->b[0x22BA] != 0;
        }
        ptr34 = ((void*)gHeroState) + 0x80;
        find_nearest_path_point(((Hero *)gHeroState)->i[0x630/4], (s32) ptr34, (s32) (((void*)gHeroState) + 0x5D0), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)gHeroState)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)gHeroState)->i[0x664/4], (s32) ptr34, (s32) (((void*)gHeroState) + 0x610), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        value63 = 0;
        if (((Hero *)gHeroState)->f[0x31C/4] > 1.0699999f) {
            value86 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((value86 != 0x28) && (value86 != 0x3E) && (((Hero *)gHeroState)->i[0x660/4] == 0)) {
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
            ptr51 = ((void*)(gHeroState + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(ptr51, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion();
            } else {
                M2C_FIELD(ptr51, f32* , 0xF8) = (f32) (M2C_FIELD(ptr51, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            scalar54 = (f32) ((Hero *)gHeroState)->i[0x648/4];
            scalar146 = ((Hero *)gHeroState)->f[0x644/4] * scalar54;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                scalar146 = ((Hero *)gHeroState)->f[0x69C/4] * scalar54;
            }
            Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32)((TI128*)vecA), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], scalar146);
            if (((Hero *)gHeroState)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x664/4], (s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], scalar146);
            }
            if (((Hero *)gHeroState)->i[0x1BC/4] >= 0x5B) {
                scalar75 = ((Hero *)gHeroState)->f[0x170/4] * 30.0f;
                qcopy(vecC, &((Hero *)gHeroState)->q[0x80/16]);
                value5 = ((Hero *)gHeroState)->i[0x634/4];
                scalar12 = ((Hero *)gHeroState)->f[0x638/4];
                value25 = Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vecC), (s32) &value5, (s32) &scalar12, ((Hero *)gHeroState)->i[0x654/4], scalar75);
                qcopy(vecD, &((Hero *)gHeroState)->q[0x80/16]);
                value5 = ((Hero *)gHeroState)->i[0x634/4];
                scalar12 = ((Hero *)gHeroState)->f[0x638/4];
                if ((((value25 | Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vecD), (s32) &value5, (s32) &scalar12, ((Hero *)gHeroState)->i[0x654/4], scalar75 + 0.1f)) == 0) || (((Hero *)gHeroState)->i[0x654/4] != 0)) && (((Hero *)gHeroState)->u[0x2294/4] == 0x27)) {
                    scalar147 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x64C/4], FastMatrixHelperA(vecD[0] - vecC[0], vecD[1] - vecC[1])) * 0.47f;
                    if (scalar147 > 0.78539824f) {
                        scalar147 = 0.78539824f;
                    }
                    if (scalar147 < -0.78539824f) {
                        scalar147 = -0.78539824f;
                    }
                    SetCameraLimitsSlot0(0.03f, 0.2f);
                    if (((Hero *)gHeroState)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L20_00267274) = -scalar147;
                    } else {
                        (*(f32*)&D_L20_00267274) = scalar147;
                    }
                }
            }
            value87 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((value87 != 0x28) && (value87 != 0x3E) && (value87 != 0x29)) {
                (*(f32*)&D_L20_00267270) = FastMatrixHelperA(vec_length_xy((s32) (((void*)gHeroState) + 0x110)), ((Hero *)gHeroState)->f[0x118/4]);
            }
            if (value27 != 0) {
                constA = 0.3f;
                SetCameraLimitsSlot3(0.017f, constA);
                SetCameraLimitsSlot1(0.027f, constA);
                SetCameraLimitsSlot2(0.027f, constA);
                value19 = ((Hero *)gHeroState)->i[0x6A8/4];
                if (value19 != 0) {
                    FastVecSub((s32) ((TI128*)vecC), value19 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (s32) (((void*)gHeroState) + 0x40));
                    scalar47 = FastMatrixHelperA(vecC[0], vecC[1]);
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        scalar47 = fast_subtract_rotations(scalar47, 1.5707965f);
                        scalar143 = 0.2f;
                    } else {
                        scalar47 = fast_subtract_rotations(scalar47, -1.5707965f);
                        scalar143 = 0.5f;
                    }
                    ((Hero *)D_L20_00267210)->f[0x1C8/4] = (f32) (scalar47 * scalar143);
                    ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (scalar47 * constA);
                } else {
                    byteVal1 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43);
                    if (byteVal1 == 0x31) {
                        scalar164 = 0.58823526f;
                        scalar117 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar148 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                    } else if (byteVal1 == 0x48) {
                        scalar164 = 0.5f;
                        scalar117 = FastAddRotations(0.13962635f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar148 = -0.06981318f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                    } else if (byteVal1 == 0x47) {
                        scalar164 = 0.58823526f;
                        scalar117 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        scalar148 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = scalar117;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(scalar148, ((Hero *)gHeroState)->f[0x6A0/4] * scalar164);
                    }
                }
            }
            value32 = AdvancePathIndex(((Hero *)gHeroState)->i[0x630/4], ((Hero *)gHeroState)->i[0x634/4], ((Hero *)gHeroState)->i[0x648/4], ((Hero *)gHeroState)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)vecC), (s32) &((TI128 *)((Hero *)gHeroState)->ptr[0x630/4])[value32 + 1], (s32)((TI128*)vecA));
            if (FastVecLength((s32) ((TI128*)vecC)) < 0.001f) {
                if (((Hero *)gHeroState)->i[0x634/4] == value32) {
                    ((Hero *)gHeroState)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)gHeroState)->f[0x64C/4] = FastMatrixHelperA(vecC[0], vecC[1]);
                ((Hero *)gHeroState)->f[0x650/4] = FastMatrixHelperA(vec_length_xy((s32) ((TI128*)vecC)), M2C_BITWISE(f32, vecC[2]));
block_807:
                ((Hero *)gHeroState)->f[0x1A0/4] = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], ((Hero *)gHeroState)->f[0x658/4]);
                SteerHeroHeading(0, 0.015f, 0.15f, 0.10471977f);
                value88 = ((Hero *)gHeroState)->u[0x2294/4];
                if ((((u32) (value88 - 0x28) < 2U) && (((Hero *)gHeroState)->b[0x49C] == 0)) || (value88 == 0x3E)) {
                    if (((Hero *)gHeroState)->i[0x694/4] != 0) {
                        scalar34 = FastMatrixHelperA(((Hero *)gHeroState)->f[0x620/4] - ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x624/4] - ((Hero *)gHeroState)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], scalar34) < 1.5707965f) {
                            ((Hero *)gHeroState)->f[0x1A0/4] = scalar34;
                            SteerHeroHeading(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)gHeroState)->i[0x660/4] != 0) && (((Hero *)gHeroState)->i[0x678/4] < 0x31)) {
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) ((TI128*)vecB));
                        value33 = ((Hero *)gHeroState)->i[0x678/4] + 1;
                        ((Hero *)gHeroState)->i[0x678/4] = value33;
                        FastVecScale((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), (f32) value33 * 0.020833334f);
                        scalar76 = (f32) (((Hero *)gHeroState)->i[0x678/4] - 1) * 0.020833334f;
                        FastVecSub((s32) ((TI128*)vecD), (s32)((TI128*)vecA), (s32) ((TI128*)vecB));
                        FastVecScale((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), scalar76);
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + (M2C_BITWISE(f32, vecC[2]) - vecD[2]));
                        FastVecAdd((s32) ((TI128*)vecD), (s32) ((TI128*)vecB), (s32) ((TI128*)vecC));
                        FastVecSub((s32) ((TI128*)vecC), (s32) ((TI128*)vecD), (s32) (((void*)gHeroState) + 0x80));
                        ((Hero *)gHeroState)->f[0xF0/4] = vecC[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = vecC[1];
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32) (((void*)gHeroState) + 0x5D0));
                        scalar100 = ((Hero *)gHeroState)->f[0x5D8/4];
                        scalar55 = ((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, vecC[2]);
                        ((Hero *)gHeroState)->f[0x88/4] = scalar55;
                        if (scalar55 < scalar100) {
                            if (((Hero *)gHeroState)->i[0x678/4] < 0x31) {
                                if (scalar55 < scalar100) {
                                    ((Hero *)gHeroState)->f[0x88/4] = scalar100;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)vecC), (s32)((TI128*)vecA), (s32)(gHeroState + 0x5D0));
                        ((Hero *)gHeroState)->f[0xF0/4] = vecC[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = vecC[1];
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, vecC[2]));
                        FastVecSub((s32) ((TI128*)vecD), (s32)(gHeroState + 0x5D0), (s32)(gHeroState + 0x80));
                        vecD[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)vecD)) > 0.016666668f) {
                            vec_scale_to_length((s32) ((TI128*)vecD), (s32) ((TI128*)vecD), 0.016666668f);
                        }
                        ((Hero *)gHeroState)->f[0x80/4] = (f32) (((Hero *)gHeroState)->f[0x80/4] + vecD[0]);
                        ((Hero *)gHeroState)->f[0x84/4] = (f32) (((Hero *)gHeroState)->f[0x84/4] + vecD[1]);
                    }
                    if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.006388889f);
                    } else {
                        ApplyHeroGravityAndJumpMotion();
                    }
                } else {
                    ((Hero *)gHeroState)->i[0x660/4] = 0;
                    scalar118 = 0.0f;
                    if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) && (flagA != 0)) {
                        ResolveStickInputToDirection(1.0f, 0);
                        scalar118 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x1A0/4], ((Hero *)gHeroState)->f[0x64C/4]);
                        if (scalar118 > 0.78539824f) {
                            scalar118 = 0.78539824f;
                        } else if (scalar118 < -0.78539824f) {
                            scalar118 = -0.78539824f;
                        }
                    }
                    ApproachWithVelocity((s32)(gHeroState + 0x6A0), scalar118, (s32)(gHeroState + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    ApproachValue((s32)(gHeroState + 0x680), 0.20000002f, 0.004166667f);
                    value6 = ((Hero *)gHeroState)->i[0x634/4];
                    scalar13 = ((Hero *)gHeroState)->f[0x638/4];
                    qcopy(vecC, &((Hero *)gHeroState)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)vecC), (s32) &value6, (s32) &scalar13, ((Hero *)gHeroState)->i[0x654/4], 0.3f);
                    scalar31 = FastMatrixHelperA(vec_distance_xy((s32)(gHeroState + 0x5D0), (s32) ((TI128*)vecC)), M2C_BITWISE(f32, vecC[2]) - ((Hero *)gHeroState)->f[0x5D8/4]);
                    if (scalar31 > 0.0f) {
                        scalar126 = scalar31 * -0.07957746f;
                        if (scalar31 > 0.26179942f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 0;
                        } else if ((scalar31 < 0.13962635f) && (((Hero *)gHeroState)->i[0x67C/4] == 0)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    } else {
                        scalar126 = -scalar31 * 0.38197184f;
                        if (scalar31 < -0.19198623f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 1;
                        } else if ((scalar31 > -0.122173056f) && (((Hero *)gHeroState)->i[0x67C/4] == 1)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < scalar126) {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), scalar126, 0.0022222223f);
                    } else {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), scalar126, 0.00055555557f);
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)gHeroState)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)gHeroState)->f[0x674/4] = -0.041666668f;
                    }
                    scalar32 = ((Hero *)gHeroState)->f[0x680/4] + ((Hero *)gHeroState)->f[0x674/4];
                    ((Hero *)gHeroState)->f[0x644/4] = scalar32;
                    if (scalar32 < 0.0f) {
                        ((Hero *)gHeroState)->f[0x644/4] = 0.0f;
                    }
                    ptr25 = ((void*)gHeroState) + 0x5D0;
                    FastVecSub((s32) (((void*)gHeroState) + 0xF0), (s32)((TI128*)vecA), (s32) ptr25);
                    ptr40 = ((void*)gHeroState) + 0x80;
                    FastVecSub((s32) ((TI128*)vecC), (s32) ptr25, (s32) ptr40);
                    scalar14 = -FastVecLength((s32) ((TI128*)vecC));
                    SpringFloatToGoal((s32) &scalar14, (s32) (((void*)gHeroState) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    scalar33 = FastVecLength((s32) ((TI128*)vecC));
                    if (scalar33 < ((Hero *)gHeroState)->f[0x6AC/4]) {
                        ((Hero *)gHeroState)->f[0x6AC/4] = scalar33;
                    }
                    scalar48 = ((Hero *)gHeroState)->f[0x6AC/4];
                    if (scalar48 < scalar33) {
                        vec_scale_to_length((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), scalar48);
                    }
                    FastVecAdd((s32) ptr40, (s32) ptr40, (s32) ((TI128*)vecC));
                    scalar103 = ((Hero *)gHeroState)->f[0x88/4];
                    scalar99 = ((Hero *)gHeroState)->f[0x5D8/4];
                    if (scalar103 < scalar99) {
                        if (((Hero *)gHeroState)->f[0x31C/4] < 1.0f) {
                            if (scalar103 < scalar99) {
                                ((Hero *)gHeroState)->f[0x88/4] = scalar99;
                            }
                        }
                    }
                }
                if (((Hero *)gHeroState)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)gHeroState)->i[0x1B8/4] < 0x14) {
                        scalar35 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.3490659f, 0.6108653f));
                        vecF[0] = FastSinOrCosA(scalar35);
                        vecF[1] = FastSinOrCosB(scalar35);
                        vecF[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)vecC), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &vecF[0]);
                        qcopy(vecG, &((Hero *)gHeroState)->q[0x80/16]);
                        vecG[2] += 0.6f;
                        ProcessCollisionHit(1.0f, (s32) ((TI128*)vecG), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)vecC));
                    }
                }
            }
        }
        break;
    case 0x71:                                      /* switch 1 */
        GetHeroOffsetVector(vecA);
        heroPtrA = (Hero *)gHeroState;
        if (M2C_FIELD(heroPtrA->ptr[0x2290/4], u8* , 0x43) == 0x5F) {
            UpdateSoundSlotObject(0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
            if (ref_L00_002BA7D8_00 & 1) {
                qcopy(vecB, vecA);
                FastVecScale((s32) ((TI128*)vecC), (s32) (((void*)gHeroState) + 0x110), 0.4f);
                scalar1 = FastAddRotations(((Hero *)gHeroState)->f[0x700/4], RandomSignedFloatRange(0.0f, 0.52359885f));
                scalar2 = RandomFloatRange(0.0f, 0.06666667f);
                vecC[0] += FastSinOrCosA(scalar1) * scalar2;
                vecC[1] += FastSinOrCosB(scalar1) * scalar2;
                vecC[2] = RandomFloatRange(0.050000004f, 0.083333336f);
                vecC[3] = -0.009722223f;
                SpawnWhiteFlashParticle((s32) ((TI128*)vecB), (s32) ((TI128*)vecC), 0, -1.0f);
            }
        }
        find_nearest_path_point(((Hero *)gHeroState)->i[0x6E0/4], (s32) ((TI128*)vecA), (s32) (((void*)gHeroState) + 0x6D0), (s32) (((void*)gHeroState) + 0x6E4), (s32) (((void*)gHeroState) + 0x6E8), ((Hero *)gHeroState)->i[0x6FC/4], 999.0f, 8.0f, 2.5f);
        countA = ((Hero *)gHeroState)->i[0x6F0/4];
        if (countA != 0) {
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x120/16]);
            ((Hero *)gHeroState)->i[0x6F0/4] = countA + 1;
            ((Hero *)gHeroState)->f[0xF8/4] = ((Hero *)gHeroState)->f[0xF8/4] - 0.0061111115f;
        } else {
            scalar3 = ((Hero *)gHeroState)->f[0x6F4/4];
            /* retail evaluates the float (fifth) argument first */
            ((s32 (*)(s32, s32, s32, s32, f32, s32))Spline_AdvanceByDistance)(((Hero *)gHeroState)->i[0x6E0/4], (s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0x6E4), (s32) (((void*)gHeroState) + 0x6E8), scalar3, ((Hero *)gHeroState)->i[0x6FC/4]);
            indexA = AdvancePathIndex(((Hero *)gHeroState)->i[0x6E0/4], ((Hero *)gHeroState)->i[0x6E4/4], 1, ((Hero *)gHeroState)->i[0x6FC/4]);
            FastVecSub((s32) ((TI128*)vecC), (s32)((u8 *)((Hero *)gHeroState)->ptr[0x6E0/4] + (indexA * 16 + 0x10)), (s32) ((TI128*)vecB));
            if (FastVecLength((s32) ((TI128*)vecC)) < 0.001f) {
                if (((Hero *)gHeroState)->i[0x6E4/4] == indexA) {
                    ((Hero *)gHeroState)->i[0x6F0/4] = 1;
                    break;
                }
            } else {
                ((Hero *)gHeroState)->f[0x700/4] = FastMatrixHelperA(vecC[0], vecC[1]);
                ((Hero *)gHeroState)->f[0x704/4] = FastMatrixHelperA(vec_length_xy((s32) ((TI128*)vecC)), vecC[2]);
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0x700/4];
            SteerHeroHeading(0, 0.018f, 0.2f, 0.10762865f);
            ApproachValue((s32) (((void*)gHeroState) + 0x6F4), 0.23333335f, 0.0025f);
            FastVecSub((s32) (((void*)gHeroState) + 0xF0), (s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0x6D0));
            FastVecSub((s32) ((TI128*)vecC), (s32) (((void*)gHeroState) + 0x6D0), (s32) ((TI128*)vecA));
            scalarSpN = -FastVecLength((s32) ((TI128*)vecC));
            SpringFloatToGoal((s32) &scalarSpN, (s32) (((void*)gHeroState) + 0x708), 0.0f, 0.05f, 0.3f, 0.16666667f);
            scalar3 = FastVecLength((s32) ((TI128*)vecC));
            if (scalar3 < ((Hero *)gHeroState)->f[0x708/4]) {
                ((Hero *)gHeroState)->f[0x708/4] = scalar3;
            }
            if (((Hero *)gHeroState)->f[0x708/4] < scalar3) {
                vec_scale_to_length((s32) ((TI128*)vecC), (s32) ((TI128*)vecC), ((Hero *)gHeroState)->f[0x708/4]);
            }
            FastVecAdd((s32) (((void*)gHeroState) + 0x80), (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vecC));
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
        FastVecSub((s32) ((TI128*)vecG), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32)(gHeroState + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x19) {
            FastVecCross((s32) &vecE[0], (s32)(gHeroState + 0x2C0), (s32) ((TI128*)vecG));
        } else {
            FastVecCross((s32) &vecE[0], (s32) ((TI128*)vecG), (s32)(gHeroState + 0x2C0));
        }
        vec_scale_to_length((s32) &vecE[0], (s32) &vecE[0], 0.2f);
        FastVecAdd((s32) &vecF[0], (s32)(gHeroState + 0x80), (s32) &vecE[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &vecF[0], (s32)(gHeroState + 0x90), (s32)((TI128*)vecA)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)vecA), (s32)(gHeroState + 0x80));
            value76 = FloatToInt(((Hero *)gHeroState)->f[0xC38/4]) * 4;
            value80 = (s32)D_L20_001ACEE8;
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), *(f32*)(value76 + value80) * 0.5f);
        }
        break;
    case 0x76:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1A0/4] = ((Hero *)gHeroState)->f[0x32C/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.09166667f;
        ApproachHeroVelocity(0.0069444445f);
        ApplyHeroModeTransform((s32) (((void*)gHeroState) + 0xF0), (s32) ((void*)gHeroState) + 0x130, 0.005f);
        break;
    case 0x6:                                       /* switch 1 */
    case 0x2C:                                      /* switch 1 */
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x2C) {
            scalar127 = 0.0f;
            if (((Hero *)gHeroState)->f[0x31C/4] > 4.0f) {
                scalar127 = 0.43633235f;
            }
            qcopy(vecA, &((Hero *)gHeroState)->q[0x90/16]);
            ApproachWithVelocity((s32) &vecA[1], scalar127, (s32) (((void*)gHeroState) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
            ApproachWithVelocity((s32)((TI128*)vecA), 0.0f, (s32) (((void*)gHeroState) + 0xA0), 0.02f, 0.3f, 0.043633237f, 0);
            StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA0/4], ((Hero *)gHeroState)->f[0xA4/4], 0.0f);
            if (((Hero *)gHeroState)->f[0x31C/4] > 1.0f) {
                ((Hero *)gHeroState)->i[0x2298/4] = 1;
            }
        }
        UpdateHeroTargetSpeed();
        if (((Hero *)gHeroState)->h[0x1E0/2] == 0) {
            UpdateHeroAirborneSteering();
        }
        ptr59 = ((void*)gHeroState) + 0xF0;
        ApplyHeroModePoseOffsets();
        BuildHeroMoveImpulse(0.7f, 0.0f);
        ApplyHeroModeTransform((s32) ptr59, (s32) ptr59, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) ptr59) < -0.8333334f) {
            SetViewSpaceHeight((s32) ptr59, (s32) ptr59, -0.8333334f);
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
        angleA = (f32) LerpInt(0x2D0, 0xB4, ((Hero *)gHeroState)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        ShowGaugePopup(2, UpdateAngleAndBlend((s32) (((void*)gHeroState) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, angleA), 0, 1.0f - (((Hero *)gHeroState)->f[0x5B0/4] * 0.02f));
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
        scalar49 = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        if ((((Hero *)gHeroState)->f[0x5B0/4] > 25.0f) && (((Hero *)gHeroState)->h[0x5BE/2] < 0x5A) && (scalar49 < 0.0f) && (scalar101 = ((Hero *)gHeroState)->f[0x31C/4], (scalar101 < 1.2f))) {
            scalar105 = (scalar101 - 0.25f) * 1.0526315f;
            ((Hero *)gHeroState)->h[0x5BE/2] = (s16) ((u16) ((Hero *)gHeroState)->h[0x5BE/2] + 1);
            if (scalar105 < 0.0f) {
                scalar105 = 0.0f;
            }
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), scalar49 * scalar105);
            if (((Hero *)gHeroState)->f[0x31C/4] < 0.25f) {
                SpringFloatToGoal((s32)(gHeroState + 0x88), (s32)(gHeroState + 0x5B4), ((Hero *)gHeroState)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (scalar49 > 0.0f) {
            ((Hero *)gHeroState)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L20_001BA248) = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        ApplyHeroModePoseOffsets();
        ResolveStickInputToDirection(((Hero *)gHeroState)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
        }
        SteerHeroHeading(0, 0.027f, 0.3f, ((Hero *)gHeroState)->f[0x24B8/4] * 0.087266475f);
        scalar128 = 0.0013888889f;
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            scalar128 = 0.00055555557f;
        }
        ApproachHeroVelocity(scalar128);
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
        scalar166 = 0.050000004f;
        if (((Hero *)gHeroState)->i[0x1338/4] == 3) {
            scalar166 = 0.083333336f;
        }
        scalar167 = 0.72f;
        scalar56 = ((Hero *)gHeroState)->f[0x24C8/4];
        if (((Hero *)gHeroState)->b[0x24EF] != 0) {
            scalar166 = 0.12833333f;
            scalar167 = 0.98640007f;
        }
        if (scalar56 != 0.0f) {
            scalar167 = scalar56;
        }
        ptr26 = ((void*)gHeroState) + 0xF0;
        scalar15 = GetViewSpaceHeight((s32) ptr26);
        ResolveStickInputToDirection(scalar166, 0);
        SteerHeroHeading(0, 0.025f, 0.3f, 0.20943955f);
        ApproachHeroSpeed(0.004166667f, 0.0019444445f);
        ComputeHeroPushDirection(99999.0f);
        ApplyHeroModePoseOffsets();
        ProjectVectorOntoViewPlane((s32) ptr26, (s32) ptr26);
        SpringFloatToGoal((s32) &scalar15, (s32) (((void*)gHeroState) + 0xA98), -scalar166 * scalar167, 0.025f, 0.3f, 0.28333336f);
        ApplyHeroModeTransform((s32) ptr26, (s32) ptr26, -scalar15);
        scalar50 = ((Hero *)gHeroState)->f[0x88/4];
        if (scalar50 < ((Hero *)gHeroState)->f[0x490/4]) {
            ApproachValue((s32) (((void*)gHeroState) + 0x490), scalar50, 0.06666667f);
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
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x12) {
            if (((Hero *)gHeroState)->i[0x1B8/4] == 0x14) {
                EmitHeroDustAndDebris(3, 0x10, 1);
                if (D_L20_001B3730 != 0) {
                    RippleDisturb(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x84/4], 0.4f, 0.35f);
                }
            }
            scalar57 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((scalar57 >= 4.0f) && (scalar57 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        shortVal1 = ((Hero *)gHeroState)->h[0x4AC/2];
        value20 = ((Hero *)gHeroState)->i[0x1B8/4];
        if (value20 == shortVal1) {
            qcopy(&((Hero *)gHeroState)->q[0x460/16], &((Hero *)gHeroState)->q[0x80/16]);
        }
        if ((((Hero *)gHeroState)->b[0x49C] != 0) || ((value20 < shortVal1) && (value89 = ((Hero *)gHeroState)->u[0x2294/4], (value89 != 0xB)) && (value89 != 0x10) && (value89 != 0xC) && (value89 != 0x11) && (value89 != 0x1B) && (value89 != 0x89) && (value89 != 0x48))) {
            if (((Hero *)gHeroState)->h[0x528/2] != 0) {
                SteerHeroReferencePoint();
                if ((((Hero *)gHeroState)->u[0x2294/4] == 0xA) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xA) && (((Hero *)gHeroState)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
                }
            } else {
                SteerHeroHeading(0, 0.015f, 0.2f, 0.2501639f);
                scalar77 = ((Hero *)gHeroState)->f[0x1B4/4];
                if ((u8) ((Hero *)gHeroState)->b[0x49C] >= 2U) {
                    ((Hero *)gHeroState)->f[0x1B4/4] = (f32) (scalar77 * 0.4f);
                }
                if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                    ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1458/4]);
                } else {
                    ComputeHeroPushDirection(99999.0f);
                }
                ((Hero *)gHeroState)->f[0x1B4/4] = scalar77;
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
                    qcopy(vecA, &((Hero *)gHeroState)->q[0x80/16]);
                    OffsetPointInViewSpace((s32)((TI128*)vecA), (s32)((TI128*)vecA), 0.5f);
                    OffsetPointBySideDirection((s32) ((TI128*)vecB), (s32)((TI128*)vecA), 0.95f);
                    if (CollLine((s32)((TI128*)vecA), (s32) ((TI128*)vecB), 4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0) != 0) {
                        ((Hero *)gHeroState)->h[0x524/2] = 1;
                    }
                }
            }
        } else {
            UpdateHeroAirborneSteering();
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x12) {
                ptr27 = ((void*)gHeroState) + 0xF0;
                scalar106 = vec_length_xy((s32) ptr27);
                if (scalar106 > 0.06166667f) {
                    scalar106 = 0.06166667f;
                }
                FastVectorNormalizeHelper((s32) ptr27, (s32) ptr27, scalar106);
            }
        }
        scalar58 = ((Hero *)gHeroState)->f[0x318/4];
        scalar102 = ((Hero *)gHeroState)->f[0x490/4];
        if (scalar102 < scalar58) {
            scalar36 = scalar102 + 0.10000001f;
            ((Hero *)gHeroState)->f[0x490/4] = scalar36;
            if (scalar58 < scalar36) {
                ((Hero *)gHeroState)->f[0x490/4] = scalar58;
            }
        }
        scalar59 = ((Hero *)gHeroState)->f[0x88/4];
        if (scalar59 < ((Hero *)gHeroState)->f[0x490/4]) {
            ((Hero *)gHeroState)->f[0x490/4] = scalar59;
        }
        if ((((Hero *)gHeroState)->h[0x4AC/2] < ((Hero *)gHeroState)->i[0x1B8/4]) && (GetViewSpaceHeight((s32) (((void*)gHeroState) + 0xF0)) < 0.001f) && ((((Hero *)gHeroState)->b[0x49D] == 0) || (((Hero *)gHeroState)->i[0x1B8/4] > ((Hero *)gHeroState)->i[0x434/4])) && ((((Hero *)gHeroState)->u[0x2294/4] != 0xE) || (((Hero *)gHeroState)->i[0x1B8/4] >= 0x12))) {
            scalar60 = ((Hero *)gHeroState)->f[0x458/4];
            ((Hero *)gHeroState)->b[0x49E] = 1U;
            if (scalar60 != 0.0f) {
                ((Hero *)gHeroState)->f[0x520/4] = scalar60;
            }
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ApplyHeroModePoseOffsets();
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters();
        }
        value90 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((value90 == 0x10) || (value90 == 0xD)) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x81) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x10) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 9) {
                if (((Hero *)gHeroState)->f[0xC38/4] < 28.0f) {
                    BuildHeroRelativePoint((s32)((TI128*)vecA), 1, 0.8f, 0.0f, 0.3f);
                    value34 = ProcessCollisionHit(0.9f, (s32)((TI128*)vecA), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
                    if (value34 != 0) {
                        FastVecScale((s32) ((TI128*)vecB), (s32) (((void*)gHeroState) + 0x110), 7.0f);
                        for (value65 = 0; value65 < value34; value65++) {
                            if (IsMobyInSpecialClassRange(((s32 *)D_L20_001C4480)[value65]) != 0) {
                                QueueImpactEffect(((s32 *)D_L20_001C4480)[value65], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)vecB), 1.0f);
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
        scalar149 = GetViewSpaceVectorLength((s32)(gHeroState + 0xF0));
        scalar107 = 0.0011111111f;
        if ((((Hero *)gHeroState)->h[0x34E/2] == 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB)) {
            scalar107 = 0.0027777778f;
        }
        scalar149 = scalar149 - scalar107;
        if (scalar149 < 0.0f) {
            scalar149 = 0.0f;
        }
        if (((Hero *)gHeroState)->b[0x1497] != 0) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        ptr58 = ((void*)gHeroState) + 0xF0;
        SetViewSpaceVectorLength((s32) ptr58, (s32) ptr58, scalar149);
        ApplyHeroModeTransform((s32) ptr58, (s32) ptr58, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)gHeroState)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vecA), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(vecA[0], vecA[1]);
        scalar38 = vec_length_xy((s32)((TI128*)vecA));
        if (scalar38 > 0.2f) {
            heroPtrB = (Hero *)gHeroState;
            heroPtrB->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(vecA[0], vecA[1]);
            ((Hero *)gHeroState)->f[0x1B0/4] = scalar38;
            if (scalar38 < D_L20_001A7DAC[0][2]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L20_001A7DAC[0][1] * 0.016666668f;
            } else {
                ((Hero *)gHeroState)->f[0x1B0/4] = D_L20_001A7DAC[1][1] * 0.016666668f;
            }
            if (((Hero *)gHeroState)->b[0x22B4] == 1) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.015000001f;
            }
        } else {
            ((Hero *)gHeroState)->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x18AC/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        }
        speed = 1.0f;
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
        ApproachHeroSpeed(speed * 0.005f, 0.0055555557f);
        ComputeHeroPushDirection(99999.0f);
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            SlideYeedilHeroAlongWall(1);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x110, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        break;
    case 0x63:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)vecA), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        if (FastVecDot((s32)((TI128*)vecA), (s32)(gHeroState + 0x160)) < 0.0f) {
            ClearVector128((s32)(gHeroState + 0x160));
        }
        ClearVector128((s32)(gHeroState + 0xF0));
        ShrinkHeroVectorByAmount(0.0075000003f);
        SlideYeedilHeroAlongWall(0);
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
    case 0x65:                                      /* switch 1 */
        ClearVector128((s32)(gHeroState + 0xF0));
        if (((f32) ((Hero *)gHeroState)->i[0x18C0/4] * 0.5f) < (((Hero *)gHeroState)->f[0x334/4] - ((Hero *)gHeroState)->f[0x88/4])) {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.004166667f;
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.016666668f;
        }
        break;
    case 0x79:                                      /* switch 1 */
        EmitHeroRadialParticles();
        /* fallthrough */
    case 0x78:                                      /* switch 1 */
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
        SlideYeedilHeroAlongWall(0);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            CancelHeroVelocityIntoWall();
            break;
        }
        ApplyHeroModeTransform((s32) ((void*)(gHeroState + 0xF0)), (s32) ((void*)(gHeroState + 0xF0)), 0.015000001f);
        break;
    case 0x4D:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        ptr52 = (s32) &D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]];
        value10 = M2C_FIELD(ptr52, s32* , 4);
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
            scalar61 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((f32) M2C_FIELD(ptr52, s32* , 0x1C) <= scalar61) {
                if (scalar61 <= (f32) M2C_FIELD(ptr52, s32* , 0x20)) {
                    value26 = ((M2C_FIELD(ptr52, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], value26, (s32) ((TI128*)vecB));
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], value26 | 1, (s32) ((TI128*)vecC));
                    FastVecAdd((s32)((TI128*)vecA), (s32) ((TI128*)vecB), (s32) ((TI128*)vecC));
                    FastVecScale((s32)((TI128*)vecA), (s32)((TI128*)vecA), 0.5f);
                    SweepCollisionFromObject((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)vecA), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
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
        ApproachHeroVelocity(0.0069444445f);
        scalar4 = 0.005f;
        ptr3 = ((void*)gHeroState) + 0x130;
        ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) ptr3, scalar4);
        break;
    case 0x41:                                      /* switch 1 */
        ResolveStickInputToDirection(0.050000004f, 0);
        if (((Hero *)gHeroState)->h[0x1E0/2] == 0) {
            UpdateHeroAirborneSteering();
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
        scalar138 = 0.16580631f;
        scalar130 = 0.033f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            scalar138 = 0.19489513f;
            scalar130 = 0.037f;
        }
        SteerHeroHeading(0, scalar130, 0.15f, scalar138);
        ApproachHeroSpeed(0.005f, 0.0055555557f);
        if (((Hero *)gHeroState)->f[0x174/4] < 0.011666667f) {
            ((Hero *)gHeroState)->b[0x40C] = 1U;
            if ((FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)gHeroState)->b[0x40F] = 1U;
            }
        }
        scalar79 = ReadPadFloatHistory(0);
        if ((FastDiffRots(scalar79, ReadPadFloatHistory(2)) > 2.617994f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
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
                scalar171 = 0.050000004f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.02122066f);
                if (scalar171 < 0.0f) {
                    scalar171 = 0.0f;
                }
                if (scalar171 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = scalar171;
                }
            }
        }
        if (((Hero *)gHeroState)->b[0x40C] != 0) {
            ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1A0/4]);
        } else {
            ComputeHeroPushDirection(99999.0f);
        }
        SlideYeedilHeroAlongWall(1);
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0x130, 0.0069444445f);
            CancelHeroVelocityIntoWall();
        } else {
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.015000001f);
        }
        break;
    case 0x42:                                      /* switch 1 */
        scalar51 = vec_length_xy((s32)(gHeroState + 0xF0));
        if (*(s16 *)(gHeroState + 0x34E) != 0) {
            scalar51 = scalar51 * 0.99f;
        } else {
            scalar51 = scalar51 * 0.92f;
        }
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), scalar51);
        ptr53 = ((void*)(gHeroState + 0xF0)) - 0xF0;
        M2C_FIELD(ptr53, s32* , 0xF8) = 0;
        if (M2C_FIELD(ptr53, s16* , 0x34E) != 0) {
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
        FastVecSub((s32) ((TI128*)vecG), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32) (((void*)gHeroState) + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &vecE[0], (s32) (((void*)gHeroState) + 0x2C0), (s32) ((TI128*)vecG));
        } else {
            FastVecCross((s32) &vecE[0], (s32) ((TI128*)vecG), (s32) (((void*)gHeroState) + 0x2C0));
        }
        vec_scale_to_length((s32) &vecE[0], (s32) &vecE[0], 0.2f);
        FastVecAdd((s32) &vecF[0], (s32)(gHeroState + 0x80), (s32) &vecE[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &vecF[0], (s32)(gHeroState + 0x90), (s32)((TI128*)vecA)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)vecA), (s32)(gHeroState + 0x80));
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), D_L20_00298970[FloatToInt(((Hero *)gHeroState)->f[0xC38/4])] * 0.5f);
            break;
        }
        break;
    case 0x37:                                      /* switch 1 */
        if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) == 0x44) {
            SteerHeroHeading(0, 0.137f, 0.25f, 0.20362177f);
        } else {
            SteerHeroHeading(0, 1.0f, 0.1f, 0.40724355f);
        }
        break;
    case 0x60:                                      /* switch 1 */
    case 0x61:                                      /* switch 1 */
        ClearVector128((s32)(gHeroState + 0xF0));
        break;
    }
    if (savedSubState != ((Hero *)gHeroState)->i[0x2298/4]) {
        ((Hero *)gHeroState)->i[0x1C0/4] = 0;
    }
    if (savedAnimId != M2C_FIELD(heroObject, u8* , 0x43)) {
        ((Hero *)gHeroState)->i[0x1C4/4] = 0;
    }
}

