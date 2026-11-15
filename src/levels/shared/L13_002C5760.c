/* func_L13_002C5760: the hero's per-frame state handler, the twin of func_L20_002CD928 (see
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
/* Per-frame update of the hero (Ratchet): reads the controller and runs the hero's state machine
   (walking, jumping, swimming, weapons and so on) for this level. */
void func_L13_002C5760(void) {
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
    void* iVal1;
    void* iVal2;
    f32 fVal1;
    void* iVal3;
    s32 iVal4;
    void* iVal5;
    s32 iVal6;
    s32 iVal7;
    void* iVal8;
    s32 iVal9;
    void* iVal10;
    s32 lim;
    s32 lim2;
    s32 lim3;
    s32 sel1F;
    f32 k02;
    s32 cntA40;

    f32 iStack1;
    f32 iStack2;
    f32 iStack3;
    f32 iStack4;
    f32 iStack5;
    f32 iStack6;
    f32 iStack7;
    s32 iStack8;
    f32 iStack9;
    s32 iStack10;
    f32 iStack11;
    f32 iStack12;
    f32 iStack13;
    s32 iStack14;
    s32 iStack15;
    s32 iStack16;
    f32 fTemp1;
    f32 fTemp2;
    f32 fTemp3;
    f32 fTemp4;
    f32 fTemp5;
    f32 fTemp6;
    f32 fTemp7;
    f32 fTemp8;
    f32 fTemp9;
    f32 fTemp10;
    f32 fTemp11;
    f32 fTemp12;
    f32 fTemp13;
    f32 fTemp14;
    f32 fTemp15;
    f32 fTemp16;
    f32 fTemp17;
    f32 fTemp18;
    f32 fTemp19;
    f32 fTemp20;
    f32 fTemp21;
    f32 fTemp22;
    f32 fTemp23;
    f32 fTemp24;
    f32 fTemp25;
    f32 fTemp26;
    f32 fTemp27;
    f32 fTemp28;
    f32 fTemp29;
    f32 fTemp30;
    f32 fTemp31;
    f32 fTemp32;
    f32 fTemp33;
    f32 fTemp34;
    f32 fTemp35;
    f32 fTemp36;
    f32 fTemp37;
    f32 fTemp38;
    f32 fTemp39;
    f32 fTemp40;
    f32 fTemp41;
    f32 fTemp42;
    f32 fTemp43;
    f32 fTemp44;
    f32 fTemp45;
    f32 fTemp46;
    f32 fTemp47;
    f32 fTemp48;
    f32 fTemp49;
    f32 fTemp50;
    f32 fTemp51;
    f32 fTemp52;
    f32 fTemp53;
    f32 fTemp54;
    f32 fTemp55;
    f32 fTemp56;
    f32 fTemp57;
    f32 fTemp58;
    f32 fTemp59;
    f32 fTemp60;
    f32 fTemp61;
    f32 fTemp62;
    f32 fTemp63;
    f32 fTemp64;
    f32 fTemp65;
    f32 fTemp66;
    f32 fTemp67;
    f32 fTemp68;
    f32 fTemp69;
    f32 fTemp70;
    f32 fTemp71;
    f32 fTemp72;
    f32 fTemp73;
    f32 fTemp74;
    f32 fTemp75;
    f32 fTemp76;
    f32 fTemp77;
    f32 fTemp78;
    f32 fTemp79;
    f32 fTemp80;
    f32 fTemp81;
    f32 fTemp82;
    f32 fTemp83;
    f32 fTemp84;
    f32 fTemp85;
    f32 fTemp86;
    f32 fTemp87;
    f32 fTemp88;
    f32 fVal2;
    f32 fVal3;
    f32 fVal4;
    f32 fVal5;
    f32 fVal6;
    f32 fVal7;
    f32 fVal8;
    f32 fVal9;
    f32 fVal10;
    f32 fVal11;
    f32 fVal12;
    f32 fVal13;
    f32 fVal14;
    f32 fVal15;
    f32 fVal16;
    f32 fVal17;
    f32 fVal18;
    f32 fVal19;
    f32 fVal20;
    f32 fVal21;
    f32 fVal22;
    f32 fVal23;
    f32 fVal24;
    f32 fVal25;
    f32 fVal26;
    f32 fVal27;
    f32 fVal28;
    f32 fVal29;
    f32 fVal30;
    f32 fVal31;
    f32 fVal32;
    f32 fVal33;
    f32 fVal34;
    f32 fVal35;
    f32 fVal36;
    f32 fVal37;
    f32 fVal38;
    f32 fVal39;
    f32 fVal40;
    f32 fVal41;
    f32 fVal42;
    f32 fVal43;
    f32 fVal44;
    f32 fVal45;
    f32 fVal46;
    f32 fVal47;
    f32 fVal48;
    f32 fVal49;
    f32 fVal50;
    f32 fVal51;
    f32 fVal52;
    f32 fVal53;
    f32 fVal54;
    f32 fVal55;
    f32 fVal56;
    f32 fVal57;
    f32 fVal58;
    f32 fVal59;
    f32 fVal60;
    f32 fVal61;
    f32 fVal62;
    f32 fVal63;
    f32 fVal64;
    f32 fVal65;
    f32 fVal66;
    f32 fVal67;
    f32 fVal68;
    f32 fVal69;
    f32 fVal70;
    s16 iTemp1;
    s32 iTemp2;
    s16 iTemp3;
    s32 iTemp4;
    s32 iTemp5;
    s32 iTemp6;
    s32 iTemp7;
    s32 iTemp8;
    s32 iTemp9;
    s32 iTemp10;
    s32 iTemp11;
    s32 iTemp12;
    s32 iTemp13;
    s32 iTemp14;
    s32 iTemp15;
    s32 iTemp16;
    s32 iTemp17;
    s32 iTemp18;
    s32 iTemp19;
    s32 iTemp20;
    s32 iTemp21;
    s32 iTemp22;
    s32 iTemp23;
    s32 iTemp24;
    s32 iTemp25;
    s32 iTemp26;
    s32 iTemp27;
    s32 iTemp28;
    s32 iTemp29;
    s32 iTemp30;
    s32 iTemp31;
    s32 iTemp32;
    s32 iTemp33;
    s32 iTemp34;
    s32 iTemp35;
    s32 iTemp36;
    s32 iTemp37;
    s32 iTemp38;
    s32 iTemp39;
    s32 iTemp40;
    s32 iTemp41;
    s32 iTemp42;
    s32 iTemp43;
    s32 iTemp44;
    s32 iTemp45;
    s32 iTemp46;
    s32 iTemp47;
    s32 iTemp48;
    s32 iVal11;
    s32 iVal12;
    s32 iVal13;
    s32 iVal14;
    s32 iVal15;
    s32 iVal16;
    s32 iVal17;
    s32 iVal18;
    s32 iVal19;
    s32 iVal20;
    s32 iVal21;
    s32 iVal22;
    s32 iVal23;
    s32 iVal24;
    s32 iVal25;
    s32 iVal26;
    s32 iVal27;
    s32 iVal28;
    s32 iVal29;
    s32 iVal30;
    s32 iVal31;
    s32 iVal32;
    s32 iVal33;
    s32 iVal34;
    s32 iVal35;
    s32 iVal36;
    s32 iVal37;
    s32 iVal38;
    s32* iVal39;
    s32* iVal40;
    u16 iTemp49;
    u16 iTemp50;
    u16 iTemp51;
    u32 iTemp52;
    u32 iTemp53;
    u32 iTemp54;
    u32 iTemp55;
    u32 iTemp56;
    u32 iTemp57;
    u32 iTemp58;
    u32 iTemp59;
    u32 iTemp60;
    u32 iTemp61;
    u32 iTemp62;
    u32 iVal41;
    u8 iTemp63;
    u8 iTemp64;
    u8 iTemp65;
    u8 iVal42;
    void* iTemp66;
    void* iTemp67;
    void* iTemp68;
    void* iTemp69;
    void* iTemp70;
    void* iTemp71;
    void* iTemp72;
    void* iTemp73;
    void* iTemp74;
    void* iTemp75;
    void* iTemp76;
    void* iTemp77;
    void* fTemp89;
    void* hero7C;
    f32 turn24;
    f32 ang82;
    f32 min2B;
    void* heroA30;
    void* iTemp78;
    void* iTemp79;
    void* iTemp80;
    void* iTemp81;
    void* iTemp82;
    void* iTemp83;
    void* iTemp84;
    void* iTemp85;
    void* iTemp86;
    void* iTemp87;
    void* iTemp88;
    void* iTemp89;
    void* iTemp90;
    void* iTemp91;
    void* iTemp92;
    void* iTemp93;
    void* iTemp94;
    void* iTemp95;
    void* iTemp96;
    void* iTemp97;
    void* iTemp98;
    void* iTemp99;
    void* iTemp100;
    void* iTemp101;
    void* iTemp102;
    void* iTemp103;
    void* iTemp104;
    void* iTemp105;
    void* iTemp106;
    void* iTemp107;
    void* iTemp108;
    void* iTemp109;
    void* iTemp110;
    void* iTemp111;
    void* iVal43;
    void* iVal44;
    void* iVal45;
    void* iVal46;
    void* iVal47;
    void* iVal48;

    iStack14 = ((Hero *)gHeroState)->i[0x2298/4];
    fTemp89 = ((Hero *)gHeroState)->ptr[0x2290/4];
    iStack15 = (s32) M2C_FIELD(fTemp89, u8* , 0x43);
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
        iTemp53 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((iTemp53 == 1) || (iTemp53 == 0x1D)) {
            if (((Hero *)gHeroState)->b[0x22B5] != 0) {
                (*(TI128*)v0) = 0;
                v0[0] = 1.0f;
                matrix_mul_vec3((s32) (((void*)gHeroState) + 0x190), (s32)((TI128*)v0), (s32)&D_L20_001B9FD8[0x218]);
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
            if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) || (iTemp64 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43), (iTemp64 == 0xE)) || (iTemp64 == 0xF)) {
                if (((Hero *)gHeroState)->u[0x2294/4] == 4) {
                    SteerHeroHeading(0, 0.002f, 0.07f, 0.1163553f);
                }
                if (FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) > 0.0058177654f) {
                    iTemp7 = ((Hero *)gHeroState)->f[0x1A4/4] < 0.0f;
                    iTemp7 += 0xE;
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43) != iTemp7) {
                        set_hero_animation(iTemp7, 0, 5.0f);
                    }
                    fTemp1 = FloatAbs(((Hero *)gHeroState)->f[0x1A4/4]) * 18.093401f;
                    ((Hero *)gHeroState)->f[0xC20/4] = fTemp1;
                    if (fTemp1 < 0.55f) {
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
            iTemp62 = ((Hero *)gHeroState)->u[0x2294/4];
            ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
            if (iTemp62 == 3) {
                fVal17 = ((Hero *)gHeroState)->f[0x17C/4] + 1.0f;
                if (fVal17 > 1.0f) {
                    fVal17 = 1.0f;
                }
                iTemp73 = ((Hero *)gHeroState)->ptr[0x2290/4];
                fVal43 = fVal17 * 0.0075000003f;
                ((Hero *)gHeroState)->f[0x24AC/4] = fVal43;
                if (M2C_FIELD(iTemp73, u8* , 0x42) == M2C_FIELD(iTemp73, u8* , 0x43)) {
                    fVal38 = ((Hero *)gHeroState)->f[0x174/4] / fVal43;
                    if ((fVal38 > 5.0f) && ((f32) M2C_FIELD(iTemp73, u8* , 0x41) < 5.5f)) {
                        AdjustHeroAnimationSpeedForTargetFrame(13.0f, fVal38, 0.5f, -1.0f);
                        if (((Hero *)gHeroState)->f[0xC20/4] > 1.1f) {
                            ((Hero *)gHeroState)->f[0xC20/4] = 1.1f;
                        }
                    } else if ((f32) M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x41) > 6.5f) {
                        ((Hero *)gHeroState)->f[0xC20/4] = 1.0f;
                    }
                }
            } else if (iTemp62 == 4) {
                fVal43 = 0.0075000003f;
                if (((Hero *)gHeroState)->b[0x1492] != 0) {
                    fVal43 = 0.00047222225f;
                }
            } else {
                fVal43 = 0.004916667f;
            }
            ApproachHeroSpeed(0.0f, fVal43);
            ClearVector128((s32)(gHeroState + 0xF0));
            ShrinkHeroVectorByAmount(fVal43);
            if ((((Hero *)gHeroState)->b[0x1497] != 0) && (D_001A7B08[3] != 0)) {
                iVal15 = (s32)(gHeroState + 0xF0);
                if (((Hero *)gHeroState)->f[0x31C/4] > 0.2f) {
                    ApplyHeroModeTransform(iVal15, iVal15 + 0x30, 0.0061111115f);
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
        hero7C = (void*)gHeroState;
        if (((Hero *)hero7C)->i[0x7A4/4] == 0) {
            iTemp24 = CreateMoby(0x52A);
            ((Hero *)hero7C)->i[0x7A4/4] = iTemp24;
            if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
            qcopy((u8 *)iTemp24 + 0x10, &((Hero *)hero7C)->q[0x80/16]);
            qcopy((u8 *)iTemp24 + 0xF0, &((Hero *)hero7C)->q[0x90/16]);
            M2C_FIELD(iTemp24, s16* , 0x32) = 0x40;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x31) = 1;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], s8* , 0x30) = 0;
            M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) = 0U;
            iTemp44 = ((Hero *)hero7C)->i[0x7A4/4];
            M2C_FIELD(iTemp44, u16* , 0x34) = (u16) (M2C_FIELD(iTemp44, u16* , 0x34) | 0x800);
            func_002A0F48(((Hero *)hero7C)->i[0x7A4/4]);
            PlayMobySound(0, 0, ((Hero *)hero7C)->i[0x7A4/4]);
            }
        }
        if (((Hero *)hero7C)->i[0x7A4/4] != 0) {
        M2C_FIELD(((Hero *)hero7C)->i[0x7A4/4], u8* , 0x23) += FloatToInt(5.0f);
        iTemp46 = ((Hero *)hero7C)->i[0x7A4/4];
        if ((u8) M2C_FIELD(iTemp46, u8* , 0x23) >= 0x81U) {
            M2C_FIELD(iTemp46, u8* , 0x23) = 0x80U;
        }
        iTemp8 = ((Hero *)hero7C)->i[0x7A4/4];
        iTemp75 = ((Hero *)hero7C)->ptr[0x2290/4];
        qcopy((u8 *)iTemp8 + 0x10, (u8 *)iTemp75 + 0x10);
        qcopy((u8 *)iTemp8 + 0xF0, (u8 *)iTemp75 + 0xF0);
        func_002A0F48(iTemp8);
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
            iTemp17 = ((Hero *)gHeroState)->i[0x2440/4];
            if (iTemp17 != -1) {
                iTemp74 = (iTemp17 * 0x70) + (s32)gSoundState;
                if (M2C_FIELD(iTemp74, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) {
                    if (M2C_FIELD(iTemp74, u8* , 0x74) != 0) {
                        StopSoundVoice(iTemp17);
                    }
                }
            }
            ((Hero *)gHeroState)->i[0x2440/4] = -1;
        }
        if (((Hero *)gHeroState)->h[0xA4A/2] != 0) {
            FastDecTimer((s32) (((void*)gHeroState) + 0xA4A));
            iTemp9 = (s32) ((u16) ((Hero *)gHeroState)->h[0xA4A/2] << 0x10) >> 0x12;
            EmitHeroRandomizedMotionEffects((iTemp9 >= 9) ? 8 : iTemp9, 0, 0);
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x32) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            fTemp47 = ((Hero *)gHeroState)->f[0xC38/4];
            if (fTemp47 > 0.0f) {
                if (fTemp47 < 10.0f) {
                    EmitHeroRandomizedMotionEffects(4, 1, 0);
                }
            }
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                iTemp47 = ((Hero *)gHeroState)->i[0x1B8/4];
                if (iTemp47 < 0xF) {
                    EmitHeroRandomizedMotionEffects(((s32) (0x14 - iTemp47) / 3) + 1, 1, 0);
                }
            }
        }
        iTemp48 = ((Hero *)gHeroState)->i[0x2298/4];
        if (iTemp48 == 1) {
            if (((Hero *)gHeroState)->i[0x1B8/4] == iTemp48) {
                EmitHeroDustAndDebris(3, 0x10, 0);
                if (D_L20_001B3730 != 0) {
                    RippleDisturb(D_L20_001B3730, D_L20_001B3738, 0, ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x84/4], 0.4f, -0.3f);
                }
                ((Hero *)gHeroState)->h[0xA4A/2] = 0x46;
            }
            iTemp31 = ((Hero *)gHeroState)->i[0xA20/4] + 1;
            ((Hero *)gHeroState)->i[0xA20/4] = iTemp31;
            if (iTemp31 >= 0x29) {
                ((Hero *)gHeroState)->i[0x2298/4] = 0;
            }
        }
        stick_turn = 0.011635531f;
        stick_turn += (((Hero *)gPadState)->f[0x12C/4] > ((Hero *)gPadState)->f[0x128/4] ? ((Hero *)gPadState)->f[0x12C/4] : ((Hero *)gPadState)->f[0x128/4]) * 0.008726647f;
        fVal30 = 0.0f;
        k02 = 0.2f;
        if ((((((Hero *)gPadState)->d[0x1A0/8] & 0xC0) == 0x80)) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            fVal32 = ((Hero *)gPadState)->f[0x12C/4] * 1.5f;
            if (fVal32 > 1.0f) {
                fVal32 = 1.0f;
            }
            if (fVal32 < k02) {
                fVal32 = k02;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                iTemp5 = ((Hero *)gHeroState)->uh[0xA42/2] + 1;
                ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
                fVal32 = ((f32) (s16) iTemp5 * 0.025f) + 0.5f;
                ((Hero *)gHeroState)->uh[0xA42/2] = (u16) iTemp5;
                if (fVal32 > 1.0f) {
                    fVal32 = 1.0f;
                }
            }
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (fVal32 < 0.35f)) {
                fVal32 = 0.35f;
            }
            fVal30 = fVal32 * 1.361357f;
        } else if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            fVal31 = ((Hero *)gPadState)->f[0x128/4] * 1.5f;
            if (fVal31 > 1.0f) {
                fVal31 = 1.0f;
            }
            if (fVal31 < k02) {
                fVal31 = k02;
            }
            if (((Hero *)gPadState)->i[0x1DC/4] != 0x79) {
                cntA40 = ((Hero *)gHeroState)->uh[0xA40/2] + 1;
                ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
                ((Hero *)gHeroState)->h[0xA40/2] = cntA40;
                fVal31 = ((f32) (s16) cntA40 * 0.025f) + 0.5f;
                if (fVal31 > 1.0f) {
                    fVal31 = 1.0f;
                }
            }
            if ((f32) ((Hero *)gHeroState)->i[0x24C0/4] < 1500.0f) {
                fVal31 = 1.0f;
            }
            fVal30 = fVal31 * -1.361357f;
        } else {
            ((Hero *)gHeroState)->uh[0xA40/2] = 0U;
            ((Hero *)gHeroState)->uh[0xA42/2] = 0U;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40) {
            ((Hero *)gHeroState)->uh[0xA4E/2] = (u16) (((Hero *)gHeroState)->uh[0xA4E/2] + 1);
            if (((Hero *)gPadState)->f[0x128/4] > 0.75f) {
                iTemp4 = ((Hero *)gHeroState)->uh[0xA4C/2] + 1;
                ((Hero *)gHeroState)->h[0xA4C/2] = iTemp4;
                if ((s16) iTemp4 >= 0x5B) {
                    iTemp50 = ((Hero *)gProgressStatistics)->uh[0x84/2];
                    if (iTemp50 <= 0xFFFEU) {
                        ((Hero *)gProgressStatistics)->uh[0x84/2] = (u16) (iTemp50 + 1);
                    }
                }
                iTemp32 = (*(s32*)&D_001A7390);
                if ((u32) ((Hero *)gProgressStatistics)->u[0x88/4] < (u32) iTemp32) {
                    ((Hero *)gProgressStatistics)->u[0x88/4] = (u32) iTemp32;
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
            if ((D_L20_001B2AC8 - hp32->i[0xA54/4]) < 0x46) {
                hp32->i[0xA50/4]++;
            }
            hp32->i[0xA54/4] = D_L20_001B2AC8;
        }
        if ((s16) ((Hero *)gHeroState)->uh[0xA4E/2] >= 0x47) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if ((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x80) {
            ((Hero *)gHeroState)->i[0xA50/4] = 0;
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x33) {
            fVal30 = 0.0f;
        }
        fTemp55 = ((Hero *)gHeroState)->f[0x94/4];
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), fVal30, (s32) (((void*)gHeroState) + 0xA28), 0.015f, 0.2f, stick_turn, 0);
        fTemp77 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x94/4], fTemp55);
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
        fVal66 = ((Hero *)gHeroState)->f[0x24B8/4];
        if (((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xC0) || (((Hero *)gHeroState)->i[0x2298/4] == 1)) {
            if (fVal66 < 1.0f) {
                fVal66 = 1.0f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.15f) {
            fVal9 = 0.35f;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
                fVal9 = 0.4f;
            }
            if (fVal66 < fVal9) {
                fVal66 = fVal9;
            }
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] != 0x34) || !((s32) ((Hero *)gPadState)->d[0x1A0/8] & 0xA)) {
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * fVal66);
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
                iVal16 = 4;
                iVal20 = 0xB;
            } else {
                iVal16 = 0x28;
                iVal20 = 0x5A;
            }
            ((Hero *)heroA30)->i[0xA30/4] = RandomIntRange(iVal16, iVal20);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x34) {
            if (FastDecTimer((s32) (((void*)gHeroState) + 0xA38)) != 0) {
                iTemp98 = ((Hero *)gHeroState)->ptr[0x1310/4];
                if (iTemp98 != 0) {
                    if (M2C_FIELD(iTemp98, s16* , 0xAA) == 0x261) {
                        for (iVal24 = 0; iVal24 < 4; iVal24++) {
                            TransformMobyJointToWorld((s32) iTemp98, iVal24 % 2, (s32)((TI128*)v0));
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
        fTemp74 = FastAddRotations(-((Hero *)gHeroState)->f[0x94/4], 0.0f);
        iTemp54 = ((Hero *)gHeroState)->u[0x2294/4];
        if (iTemp54 == 0x34) {
            BuildSphericalOffset((s32) (((void*)gHeroState) + 0xF0), ((Hero *)gHeroState)->f[0x1B4/4], ((Hero *)gHeroState)->f[0x98/4], fTemp74);
        } else if (iTemp54 == 0x32) {
            fVal33 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L20_00269110, 0x1E) * 5.0f;
            if ((((Hero *)gHeroState)->i[0x22A0/4] == 0x34) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xF) && (fVal33 < 0.075f)) {
                fVal33 = 0.075f;
            }
            BuildSphericalOffset((s32)(gHeroState + 0xF0), fVal33, ((Hero *)gHeroState)->f[0x98/4], fTemp74);
        } else if (iTemp54 == 0x33) {
            iStack1 = FastVecLength((s32) (((void*)gHeroState) + 0x160));
            if (((Hero *)gHeroState)->i[0x22A0/4] == 0x34) {
                ApproachValue((s32) &iStack1, 0.0f, 0.0022222223f);
            } else {
                ApproachValue((s32) &iStack1, 0.0f, 0.0011111111f);
            }
            vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), iStack1);
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        }
        SlideYeedilHeroAlongWall(0);
        fTemp75 = ((Hero *)gHeroState)->f[0xA2C/4] * FastSinOrCosA(fTemp74) * -7.0f;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), fTemp75, (s32) (((void*)gHeroState) + 0xA24), 0.007f, 0.17f, 0.020362178f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        fTemp81 = fTemp77 * 47.0f;
        ((Hero *)D_L20_00267210)->f[0x114/4] = fTemp81;
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (fTemp75 * 1.5f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (fTemp75 * 1.4f);
        if (fTemp81 > 0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = 0.8726647f;
        } else if (fTemp81 < -0.8726647f) {
            ((Hero *)D_L20_00267210)->f[0x114/4] = -0.8726647f;
        }
        fTemp48 = fTemp77 * 40.0f;
        fTemp22 = fTemp75 * 1.1f;
        ((Hero *)D_L20_00267210)->f[0x364/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x368/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x324/4] = fTemp48;
        ((Hero *)D_L20_00267210)->f[0x328/4] = fTemp22;
        ((Hero *)D_L20_00267210)->f[0x414/4] = 0.03f;
        ((Hero *)D_L20_00267210)->f[0x418/4] = 0.22f;
        ((Hero *)D_L20_00267210)->f[0x3D4/4] = fTemp48;
        ((Hero *)D_L20_00267210)->f[0x3D8/4] = fTemp22;
        break;
    case 0x73:                                      /* switch 1 */
        iTemp10 = 0xA - ((s32) ((Hero *)gHeroState)->i[0x1B8/4] / 3);
        iTemp85 = ((void*)gHeroState) + 0xF0;
        EmitHeroRandomizedMotionEffects((iTemp10 >= 9) ? 8 : iTemp10, 0, 0);
        ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
        func_L00_002EE4D8((s32) iTemp85, (s32) iTemp85, vec_length_xy((s32) iTemp85) * 0.92f);
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
        iStack2 = FastVecLength((s32)(gHeroState + 0x160));
        ApproachValue((s32) &iStack2, 0.0f, 0.0011111111f);
        vec_scale_to_length((s32)(gHeroState + 0x160), (s32)(gHeroState + 0x160), iStack2);
        qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x160/16]);
        if (FastFloatHelperD((s32) (((void*)(gHeroState + 0x160)) + 0x8D0)) == 2) {
            iTemp93 = ((void*)(gHeroState + 0x160)) - 0x160;
            TransformMobyJointToWorld(M2C_FIELD(iTemp93, s32* , 0x2290), 4, (s32)((TI128*)v0));
            (*(TI128*)v20) = 0;
            v20[0] = 0.4f;
            matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), M2C_FIELD(iTemp93, s32* , 0x2290) + 0xC0);
            FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v20));
            qcopy(v10, &((Hero *)gHeroState)->q[0x110/16]);
            vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), 0.025000002f);
            FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
            v10[2] += 0.033333335f;
            SpawnBubbleParticle((s32)((TI128*)v0), (s32) ((TI128*)v10), 25200.0f, -1.0f);
            iTemp33 = M2C_FIELD(iTemp93, s32* , 0x1B8);
            if (iTemp33 < 0x28) {
                lim67 = 5;
                iVal29 = RandomIntRange(2, lim67) + ((s32) M2C_FIELD(iTemp93, s32* , 0x1B8) / lim67);
                goto block_224;
            }
            if (iTemp33 >= 0x47) {
                iVal29 = RandomIntRange(0xA, 0x14);
block_224:
                M2C_FIELD(iTemp93, s32* , 0xA30) = iVal29;
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
            iTemp11 = ((Hero *)gHeroState)->h[0xA4A/2] >> 3;
            EmitHeroRandomizedMotionEffects((iTemp11 >= 7) ? 6 : iTemp11, 0, 0);
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
            fTemp66 = ((Hero *)gHeroState)->f[0x1B4/4] * BlendTableEntriesByClock((s32)D_L20_00269110, 0x1E) * 5.5f;
            ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * fTemp66);
            fTemp24 = FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * fTemp66;
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ((Hero *)gHeroState)->f[0xF4/4] = fTemp24;
        } else {
            ((Hero *)gHeroState)->f[0x1B4/4] = 0.0f;
            ClearVector128((s32)(gHeroState + 0xF0));
        }
        if ((((Hero *)gHeroState)->u[0x2294/4] == 0x35) && (((Hero *)gHeroState)->i[0xC2C/4] == 0)) {
            fTemp49 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((fTemp49 > 0.0f) && (fTemp49 < 10.0f)) {
                EmitHeroRandomizedMotionEffects(4, 1, 0);
            }
        }
        ShrinkHeroVectorByAmount(0.0011666666f);
        SlideYeedilHeroAlongWall(0);
        UpdateHeroHeightOffset();
        break;
    case 0x85:                                      /* switch 1 */
        iTemp76 = ((Hero *)gHeroState)->ptr[0x1830/4];
        qcopy(&((Hero *)gHeroState)->q[0x80/16], (u8 *)iTemp76 + 0x10);
        qcopy(&((Hero *)gHeroState)->q[0x90/16], (u8 *)iTemp76 + 0xF0);
        break;
    case 0x86:                                      /* switch 1 */
        FastVecScale((s32)((TI128*)v0), (s32)(gHeroState + 0x2C0), -1.0f);
        fVal34 = 0.0f;
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            fVal34 = -((Hero *)gHeroState)->f[0x1FB4/4] * 0.75f;
        }
        SpringFloatToGoal((s32)(gHeroState + 0x7C0), (s32)(gHeroState + 0x7C4), fVal34, 0.007f, 0.3f, 0.03f);
        FastVecScale((s32) ((TI128*)v10), (s32)gHeroState, ((Hero *)gHeroState)->f[0x7C0/4]);
        FastVecAdd((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)v10));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        ApplyHeroReferenceTiltRotation((s32)((TI128*)v0), (s32) ((TI128*)v30), 0, 0.025f, 0.4f, 0.0f);
        ((Hero *)gHeroState)->f[0x1B4/4] = 0.21666668f;
        vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)gHeroState, 0.21666668f);
        SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
        ClearVector128((s32)((TI128*)v0));
        v0[1] = -((Hero *)gHeroState)->f[0x1FB0/4];
        matrix_mul_vec3((s32)(gHeroState + 0x190), (s32)((TI128*)v0), (s32)&D_L20_001B9FD8[0x218]);
        SteerHeroHeading(0, 0.02f, 0.3f, 0.034906592f);
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
            iTemp106 = ((Hero *)gHeroState)->ptr[0x2290/4];
            if ((M2C_FIELD(iTemp106, u8* , 0x60) & 2) && (M2C_FIELD(iTemp106, u8* , 0x42) == 0x36)) {
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
        iVal48 = ((Hero *)gHeroState)->ptr[0xB10/4];
        if (iVal48 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(iVal48, f32* , 0x10) - M2C_FIELD(fTemp89, f32* , 0x10), M2C_FIELD(iVal48, f32* , 0x14) - M2C_FIELD(fTemp89, f32* , 0x14));
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
        iVal1 = ((Hero *)gHeroState)->ptr[0xAA4/4];
        if (iVal1 != 0) {
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(M2C_FIELD(iVal1, f32* , 0x10) - M2C_FIELD(fTemp89, f32* , 0x10), M2C_FIELD(iVal1, f32* , 0x14) - M2C_FIELD(fTemp89, f32* , 0x14));
            SteerHeroHeading(0, 0.02f, 0.15f, 0.10471977f);
        }
        break;
    case 0x24:                                      /* switch 1 */
        qcopy(v0, (u8 *)((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10);
        fTemp25 = fast_vec_dist((s32) (((void*)gHeroState) + 0x80), (s32)((TI128*)v0));
        ((Hero *)gHeroState)->f[0xAB0/4] = fTemp25;
        ((Hero *)gHeroState)->f[0xAAC/4] = 60.0f;
        if (((Hero *)gHeroState)->f[0xAA0/4] > 0.0f) {
            ((Hero *)gHeroState)->f[0xAAC/4] = (f32) (fTemp25 / ((Hero *)gHeroState)->f[0x170/4]);
        }
        iTemp34 = ((Hero *)gHeroState)->i[0x2298/4];
        if (iTemp34 == 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.45000002f, 0.022222223f);
            iTemp102 = ((Hero *)gHeroState)->ptr[0xAA4/4];
            fVal48 = FastMatrixHelperA(M2C_FIELD(iTemp102, f32* , 0x10) - M2C_FIELD(fTemp89, f32* , 0x10), M2C_FIELD(iTemp102, f32* , 0x14) - M2C_FIELD(fTemp89, f32* , 0x14));
            if (((Hero *)gHeroState)->i[0x3A0/4] != 0) {
                if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], fVal48) > 1.5707964f) {
                    fVal48 = FastAddRotations(fVal48, 3.1415927f);
                }
            }
            ((Hero *)gHeroState)->f[0x1A0/4] = fVal48;
            SteerHeroHeading(0, 0.03f, 0.15f, 0.12217307f);
        } else if (iTemp34 == 1) {
            ApproachValue((s32) (((void*)gHeroState) + 0xAA0), 0.0f, 0.011666667f);
        }
        if ((SolveQuadratic((s32) &iStack3, (s32) &iStack4, -0.0058333334f, ((Hero *)gHeroState)->f[0xAA0/4], 1.9f - ((Hero *)gHeroState)->f[0xAB0/4]) > 0) && (iStack3 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xAAC/4] = iStack3;
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
        fTemp26 = FastSinOrCosB(FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f)) * -0.57f;
        v20[2] = 0;
        v20[1] = fTemp26;
        FastVecAdd((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)gHeroState) + 0x80));
        FastVecSub((s32) ((TI128*)v10), (s32) (((Hero *)gHeroState)->ptr[0xAA4/4] + 0x10), (s32) ((TI128*)v20));
        vec_scale_to_length((s32) (((void*)gHeroState) + 0xF0), (s32) ((TI128*)v10), ((Hero *)gHeroState)->f[0xAA0/4]);
        fTemp27 = ((Hero *)gHeroState)->f[0xAAC/4];
        if (fTemp27 < 30.0f) {
            ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - ((30.0f - fTemp27) * 0.008055556f));
        }
        break;
    case 0x25:                                      /* switch 1 */
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
    case 0x2B:                                      /* switch 1 */
        if ((((Hero *)gHeroState)->i[0xC28/4] & 2) && (M2C_FIELD(fTemp89, u8* , 0x43) == 0x34)) {
            set_hero_animation(0x35, 0xA, 12.0f);
            ((Hero *)gHeroState)->f[0xC20/4] = 0.3f;
        }
        iTemp107 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        fTemp80 = ((Hero *)gHeroState)->f[0xF8/4];
        if (iTemp107 != 0) {
            iTemp103 = M2C_FIELD(iTemp107, void** , 0x68);
            if ((iTemp103 != 0) && (M2C_FIELD(iTemp103, s32* , 0x34) != 0)) {
                fVal49 = M2C_FIELD(iTemp107, f32* , 0xF8);
                if (FastDiffRots(fVal49, ((Hero *)gHeroState)->f[0x98/4]) > 90.0f) {
                    fVal49 = FastAddRotations(fVal49, 3.1415927f);
                }
                ApproachWithVelocity((s32) (((void*)gHeroState) + 0xAEC), fVal49, (s32) (((void*)gHeroState) + 0xAF8), 0.02f, 0.3f, 0.0f, 0);
            }
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xAEC/4];
        SteerHeroHeading(0, 0.02f, 0.3f, 0.078539826f);
        FastVecSub((s32)((TI128*)v0), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) (((void*)gHeroState) + 0x80));
        vec_scale_to_length((s32)((TI128*)v0), (s32)((TI128*)v0), 1.0f);
        if (v0[2] < 0.23f) {
            v0[2] = 0.23f;
        }
        ClearVector128((s32) ((TI128*)v60));
        v60[2] = ((Hero *)gHeroState)->f[0x98/4];
        euler_to_matrix((s32) ((TI128*)v20), (s32) ((TI128*)v60));
        matrix_from_basis_rows((s32) ((TI128*)m70), (s32) ((TI128*)v20));
        transform_vector((s32)((TI128*)v0), (s32)((TI128*)v0), (s32) ((TI128*)m70));
        v10[0] = -FastMatrixHelperA(square_root((v0[0] * v0[0]) + (v0[2] * v0[2])), v0[1]);
        fTemp28 = FastMatrixHelperA(v0[2], v0[0]);
        v10[1] = fTemp28;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), fTemp28, (s32) (((void*)gHeroState) + 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), v10[0], (s32) (((void*)gHeroState) + 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        iVal27 = ((Hero *)gHeroState)->f[0x88/4] < M2C_FIELD(((Hero *)gHeroState)->ptr[0xAD4/4], f32* , 0x18);
        if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
            if ((iVal27 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0x29) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.25f)) {
                ResolveStickInputToDirection(1.0f, 0);
                fVal50 = ((Hero *)gHeroState)->f[0x24B8/4] * 0.0035f;
                if (fVal50 > 0.083333336f) {
                    fVal50 = 0.083333336f;
                }
                vB0[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0x1A0/4]) * fVal50;
                fTemp29 = FastSinOrCosB(((Hero *)gHeroState)->f[0x1A0/4]) * fVal50;
                iTemp66 = ((void*)gHeroState) + 0xF0;
                (*(s32*)&vB0[2]) = 0;
                vB0[1] = fTemp29;
                FastVecAdd((s32) iTemp66, (s32) iTemp66, (s32) ((TI128*)vB0));
            }
            if (((Hero *)gHeroState)->h[0xADC/2] != 0) {
                iTemp94 = ((void*)gHeroState) + 0x80;
                if ((vec_distance_xy((s32) iTemp94, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10)) < (((Hero *)gHeroState)->f[0xAE0/4] * 1.57f)) || (((Hero *)gHeroState)->f[0x31C/4] > 1.5f)) {
                    iTemp86 = ((void*)gHeroState) + 0xF0;
                    ApplyHeroModeTransform((s32) iTemp86, (s32) (((void*)gHeroState) + 0x110), 0.011111111f);
                    if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (GetViewSpaceHeight((s32) iTemp86) > 0.0f)) {
                        FastVecSub((s32) ((TI128*)vB0), (s32) iTemp94, (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
                        ApplyHeroModeTransform((s32) iTemp86, (s32) iTemp86, 0.015833333f);
                    }
                }
                fTemp67 = FastVecLength((s32)(gHeroState + 0xF0)) * 0.00025f;
                FastVecScale((s32) ((TI128*)vB0), (s32)(gHeroState + 0xF0), -1.0f);
                vec_scale_to_length((s32) ((TI128*)vB0), (s32) ((TI128*)vB0), fTemp67);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)vB0));
            }
        }
        iTemp104 = ((Hero *)gHeroState)->ptr[0xAD4/4];
        if (iTemp104 != 0) {
            iTemp78 = M2C_FIELD(iTemp104, void** , 0x68);
            iTemp87 = ((void*)gHeroState) + 0xF0;
            if (iTemp78 != 0) {
                fTemp30 = FastVecLength((s32) iTemp87);
                fTemp31 = M2C_FIELD(iTemp78, f32* , 0xC);
                iStack5 = fTemp30;
                if (fTemp31 < fTemp30) {
                    ApproachValue((s32) &iStack5, fTemp31, 0.004166667f);
                    vec_scale_to_length((s32) iTemp87, (s32) iTemp87, iStack5);
                }
            }
        }
        fTemp2 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -1.5707965f);
        iTemp100 = ((void*)gHeroState) + 0x80;
        iTemp99 = ((void*)gHeroState) + 0xF0;
        vD0[0] = FastSinOrCosA(fTemp2) * 0.15f;
        fTemp3 = FastSinOrCosB(fTemp2) * 0.15f;
        (*(s32*)&vD0[2]) = 0;
        vD0[1] = fTemp3;
        FastVecAdd((s32) &vD0[0], (s32) &vD0[0], (s32) iTemp100);
        FastVecAdd((s32) ((TI128*)vB0), (s32) &vD0[0], (s32) iTemp99);
        FastVecSub((s32) ((TI128*)vC0), (s32) ((TI128*)vB0), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10));
        vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), ((Hero *)gHeroState)->f[0xAE4/4]);
        FastVecAdd((s32) ((TI128*)vB0), (s32) (((Hero *)gHeroState)->ptr[0xAD4/4] + 0x10), (s32) ((TI128*)vC0));
        FastVecSub((s32) iTemp99, (s32) ((TI128*)vB0), (s32) &vD0[0]);
        fTemp68 = ((Hero *)gHeroState)->f[0xAE4/4];
        SpringFloatToGoal((s32) (((void*)gHeroState) + 0xAE4), (s32) (((void*)gHeroState) + 0xAE8), ((Hero *)gHeroState)->f[0xAE0/4], ((Hero *)gHeroState)->f[0xB04/4], ((Hero *)gHeroState)->f[0xB08/4], ((Hero *)gHeroState)->f[0xB0C/4]);
        fTemp69 = ((Hero *)gHeroState)->f[0xAE4/4] - fTemp68;
        if (((Hero *)gHeroState)->f[0xAE4/4] < FastVecLength((s32) ((TI128*)vC0))) {
            vec_scale_to_length((s32) ((TI128*)vC0), (s32) ((TI128*)vC0), fTemp69);
            FastVecAdd((s32) iTemp100, (s32) iTemp100, (s32) ((TI128*)vC0));
        }
        if ((((Hero *)gHeroState)->h[0xAFE/2] != 0) && (iVal27 != 0)) {
            min2B = 0.23333335f;
            fTemp4 = vec_length_xy((s32) iTemp99);
            iStack6 = fTemp4;
            if (fTemp4 < min2B) {
                SpringFloatToGoal((s32) &iStack6, (s32) (((void*)gHeroState) + 0xAF4), min2B, 0.047f, 0.3f, 0.0f);
                vB0[0] = FastSinOrCosA(((Hero *)gHeroState)->f[0xAEC/4]) * ((Hero *)gHeroState)->f[0xAF4/4];
                fTemp5 = FastSinOrCosB(((Hero *)gHeroState)->f[0xAEC/4]);
                vB0[2] = 0.0f;
                vB0[1] = fTemp5 * ((Hero *)gHeroState)->f[0xAF4/4];
                FastVecAdd((s32) iTemp99, (s32) iTemp99, (s32) ((TI128*)vB0));
            }
        }
        if ((((Hero *)gHeroState)->h[0xADC/2] != 0) && (((Hero *)gHeroState)->h[0x34E/2] != 0) && (((fTemp80 < 0.0f) && (((Hero *)gHeroState)->f[0xF8/4] > 0.0f)) || (((Hero *)gHeroState)->h[0xAFC/2] != 0))) {
            ((Hero *)gHeroState)->h[0xAFE/2] = 0;
            fTemp70 = square_root(((Hero *)gHeroState)->f[0xAE0/4] / ((Hero *)gHeroState)->f[0xAF0/4]) * 3.1415927f;
            iTemp3 = ((Hero *)gHeroState)->h[0xAFC/2];
            if (iTemp3 != 0) {
                iVal30 = iTemp3 == 1;
            } else {
                (*(TI128*)vB0) = ((Hero *)gHeroState)->q[0x110/16];
                iVal30 = GetSpeedAlongHeroForward((s32) ((TI128*)vB0)) > 0.0f;
            }
            if (iVal30 != 0) {
                if (M2C_FIELD(fTemp89, u8* , 0x43) != 0x35) {
                    set_hero_animation(0x35, 6, 17.0f);
                    ((Hero *)gHeroState)->h[0xAFC/2] = 1;
                } else {
                    iTemp105 = ((Hero *)gHeroState)->ptr[0x2290/4];
                    if (M2C_FIELD(iTemp105, u8* , 0x42) == M2C_FIELD(iTemp105, u8* , 0x43)) {
                        AdjustHeroAnimationSpeedForTargetFrame(42.0f, fTemp70, 0.5f, -1.0f);
                        ((Hero *)gHeroState)->h[0xAFC/2] = 0;
                    }
                }
            } else if (M2C_FIELD(fTemp89, u8* , 0x43) != 0x35) {
                set_hero_animation(0x35, 0x15, 9.0f);
                ((Hero *)gHeroState)->h[0xAFC/2] = 2;
            } else {
                iTemp101 = ((Hero *)gHeroState)->ptr[0x2290/4];
                if (M2C_FIELD(iTemp101, u8* , 0x42) == M2C_FIELD(iTemp101, u8* , 0x43)) {
                    AdjustHeroAnimationSpeedForTargetFrame(12.0f, fTemp70, 0.5f, -1.0f);
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
            iTemp12 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (iTemp12 != 0) {
                fTemp50 = vec_distance_xy((s32) (((void*)gHeroState) + 0x80), iTemp12 + 0x10);
                iVal36 = 0;
                if ((((Hero *)gHeroState)->b[0x1496] != 0) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->b[0x1495] != 0)) {
                    iVal36 = 1;
                }
                if (((fTemp50 > 2.0f) && (fTemp50 < 5.0f)) || (iVal36 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0011111111f, 0.0011111111f);
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * ((Hero *)gHeroState)->f[0x1B4/4]);
            } else {
                ApproachHeroSpeed(0.00055555557f, 0.00055555557f);
                iTemp67 = ((void*)gHeroState) + 0xF0;
                SetViewSpaceVectorLength((s32) iTemp67, (s32) iTemp67, ((Hero *)gHeroState)->f[0x1B4/4]);
            }
        } else {
            iVal25 = 0;
            if ((((Hero *)gHeroState)->d[0x1490/8] & (0xFFFFULL << 40)) || (((Hero *)gHeroState)->b[0x149B] != 0) || (((Hero *)gHeroState)->f[0x31C/4] > 4.0f)) {
                iVal25 = 1;
            }
            iTemp13 = ((Hero *)gHeroState)->i[0xBE4/4];
            if (iTemp13 != 0) {
                FastVecSub((s32)((TI128*)v0), iTemp13 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                fTemp6 = GetViewSpaceVectorLength((s32)((TI128*)v0));
                if (((fTemp6 > 2.0f) && (fTemp6 < 5.0f)) || (iVal25 != 0)) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = 0.075f;
                }
                ApproachHeroSpeed(0.0069444445f, 0.0069444445f);
                vec_scale_to_length((s32) ((TI128*)v10), (s32)gHeroState, ((Hero *)gHeroState)->f[0x1B4/4]);
                SetViewSpaceVectorLength((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), 0.0f);
                FastVecAdd((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), (s32) ((TI128*)v10));
            } else {
                if ((iVal25 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 0x46)) {
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
        fTemp51 = ((Hero *)gHeroState)->f[0x31C/4];
        fVal56 = 0.12833333f;
        if (fTemp51 > 2.25f) {
            fVal56 = 0.064166665f;
        } else if (fTemp51 > 1.8f) {
            fVal56 = 0.08983333f;
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
                ((Hero *)D_L20_001B9E80)->f[0x180/4] = 0.1f;
                ((Hero *)D_L20_001B9E80)->i[0x188/4] = 0x1E;
                ((Hero *)gHeroState)->h[0x224/2] = 0x23;
                ((Hero *)D_L20_001B9E80)->i[0x16C/4] = 0;
            }
        }
        iTemp35 = ((Hero *)gHeroState)->i[0x1B8/4];
        lim3 = 0xE;
        if (iTemp35 < 9) {
            iTemp79 = ((void*)gHeroState) + 0xF0;
            iStack7 = GetViewSpaceHeight((s32) iTemp79);
            ApproachValue((s32) &iStack7, fVal56, 0.041666668f);
            SetViewSpaceHeight((s32) iTemp79, (s32) iTemp79, iStack7);
        } else if (iTemp35 > lim3) {
            iTemp88 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) iTemp88, (s32) iTemp88, 0.036111113f);
            if (GetViewSpaceHeight((s32) iTemp88) < 0.0f) {
                ((Hero *)gHeroState)->f[0xC00/4] = 1.0f;
            }
            fVal51 = -0.6166667f;
            if (D_L20_001A8FF0 != 0) {
                fVal51 = -1.1666667f;
            }
            if (GetViewSpaceHeight((s32) iTemp88) < fVal51) {
                SetViewSpaceHeight((s32) iTemp88, (s32) iTemp88, fVal51);
            }
        }
        break;
    case 0x15:                                      /* switch 1 */
    case 0x83:                                      /* switch 1 */
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (((Hero *)gHeroState)->f[0xC38/4] < (f32) D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]].w[0x18/4])) {
            ((Hero *)gHeroState)->c[0x1239] = 2;
        }
        iVal18 = (((Hero *)gHeroState)->i[0x22A0/4] == 1) && (((Hero *)gHeroState)->i[0x22A8/4] >= 0x15);
        if (iVal18 == 0) {
            if ((((Hero *)gHeroState)->i[0xBE8/4] != 0) || (((Hero *)gHeroState)->i[0xBE4/4] != 0)) {
                iVal26 = 0;
                if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                    iTemp80 = ((void*)gHeroState) + 0xBC0;
                    fVal52 = GetDirectionAngleDelta((s32) iTemp80, 0);
                    fVal10 = GetDirectionAngleDelta((s32) iTemp80, 1);
                } else {
                    fVal52 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                    fVal10 = GetShortestAngleDelta(1, ((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
                }
                if (fVal10 < 4.3633237f) {
                    iVal26 = 1;
                }
                if (fVal52 > 0.0f) {
                    ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (fVal10 + 1.0f));
                }
                ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
                qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
                if (iVal26 != 0) {
                    SteerHeroHeading(1, 0.057f, 0.2f, 0.2821616f);
                } else {
                    SteerHeroHeading(0, 0.057f, 0.2f, 0.2821616f);
                }
            } else {
                    iVal19 = 1;
                    if ((((Hero *)gHeroState)->u[0x2294/4] == 0x83) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xC)) {
                        iVal19 = 0;
                    } else if ((((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 6.0f)) {
                        iVal19 = 0;
                    }
                    if (iVal19 != 0) {
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
                fVal57 = 0.041666668f;
                fTemp71 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 3.1415927f);
                if ((*(s32*)&D_00138320) & 8) {
                    fVal57 = 0.050000004f;
                }
                ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(fTemp71) * fVal57));
                ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(fTemp71) * fVal57));
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
        iTemp14 = ((Hero *)gHeroState)->i[0xBE4/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        iTemp95 = (((Hero *)gHeroState)->h[0xBFC/2] * 0x2C) + (s32)D_L20_00268D90;
        if ((iTemp14 != 0) && (((Hero *)gHeroState)->i[0x1B8/4] < 4)) {
            iTemp89 = ((void*)gHeroState) + 0x80;
            fVal20 = vec_distance_xy(iTemp14 + 0x10, (s32) iTemp89);
            if ((*(s32*)&D_L20_001A8FF0) != 0) {
                fVal20 = fast_vec_dist(((Hero *)gHeroState)->i[0xBE4/4] + 0x10, (s32) iTemp89);
            }
            fVal20 = fVal20 - 0.5f;
            if (fVal20 < 0.0f) {
                fVal20 = 0.0f;
            }
            iTemp36 = M2C_FIELD(iTemp95, s32* , 4);
            if (iTemp36 == 0) {
                fVal11 = 0.75f;
                fVal58 = 0.8f;
                fVal63 = 4.0f;
            } else if (iTemp36 == 1) {
                fVal11 = 0.6f;
                fVal58 = 1.7f;
                fVal63 = 4.0f;
            } else {
                fVal11 = 1.3f;
                fVal58 = 1.7f;
                fVal63 = 1.9f;
            }
            fTemp72 = fVal20 - fVal11;
            if (FloatAbs(fTemp72) < (fVal58 + 3.0f)) {
                fVal22 = fTemp72 * 1.1111112f;
                if (fVal63 < fVal22) {
                    fVal22 = fVal63;
                }
                if (fVal22 > 1.0f) {
                    ((Hero *)gHeroState)->f[0xBF4/4] = fVal22;
                }
            }
        }
        iTemp37 = M2C_FIELD(iTemp95, s32* , 4);
        switch (iTemp37) {
        case 0:
            if (((Hero *)gHeroState)->f[0xC38/4] < 18.0f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.07333334f;
            }
            break;
        case 1:
            fTemp52 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((((Hero *)gHeroState)->i[0xC2C/4] != 0) || (fTemp52 < 9.0f)) {
                if (fTemp52 > 8.0f) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = ((Hero *)gHeroState)->f[0xBF4/4] * 0.050000004f;
                } else if (fTemp52 > 7.0f) {
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
            fVal12 = GetDirectionAngleDelta((s32)(gHeroState + 0xBC0), 0);
        } else {
            fVal12 = fast_subtract_rotations(((Hero *)gHeroState)->f[0xBEC/4], ((Hero *)gHeroState)->f[0x98/4]);
        }
        fTemp53 = FloatAbs(fVal12);
        if ((M2C_FIELD(iTemp95, s32* , 4) == 1) && (fVal12 > 0.0f)) {
            ((Hero *)gHeroState)->f[0xC20/4] = (f32) (1.0f / (fTemp53 + 1.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xBEC/4];
        qcopy(&((Hero *)gHeroState)->q[0x190/16], &((Hero *)gHeroState)->q[0xBC0/16]);
        SteerHeroHeading(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        iVal37 = 1;
        if ((M2C_FIELD(iTemp95, s32* , 4) == 1) && (((Hero *)gHeroState)->i[0xC2C/4] == 0) && (((Hero *)gHeroState)->f[0xC38/4] > 7.0f)) {
            iVal37 = 0;
        }
        if (iVal37 != 0) {
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
            iTemp68 = ((void*)gHeroState) + 0xF0;
            ApplyHeroModeTransform((s32) iTemp68, (s32) iTemp68, 0.015000001f);
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
        lim = 0xA;
        lim2 = 0x12;
        iTemp38 = ((Hero *)gHeroState)->i[0x1B8/4];
        ((Hero *)gHeroState)->f[0x1B0/4] = 0.0f;
        if (iTemp38 > lim) {
            if (iTemp38 < 0x12) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.3f;
            }
        }
        if ((((Hero *)gHeroState)->i[0x1B8/4] == 8) && (((Hero *)gHeroState)->f[0x184/4] < 0.33333334f)) {
            iTemp81 = ((void*)gHeroState) + 0x18E0;
            InitPendingSlot((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) iTemp81);
            AppendRecordToFourEntryTable((s32) iTemp81, 0x30, 2, 0.0f);
            AppendRecordToFourEntryTable((s32) iTemp81, 0x17, 4, 0.0f);
            AppendRecordToFourEntryTable((s32) iTemp81, 0xC, 6, 0.0f);
        }
        sel1F = (((Hero *)gHeroState)->i[0x1B8/4] > lim2) ? 5 : 0;
        UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), sel1F);
        if (((Hero *)gHeroState)->b[0x1492] != 0) {
            iTemp39 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((iTemp39 > lim) && (iTemp39 < 0x11) && (((Hero *)gHeroState)->f[0x178/4] < 0.14166668f)) {
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
            iTemp40 = ((Hero *)gHeroState)->i[0x1B8/4];
            if ((iTemp40 > lim) && (iTemp40 < 0x16)) {
                iTemp96 = ((Hero *)gHeroState)->ptr[0x1220/4];
                if (iTemp96 != 0) {
                    iTemp90 = ((void*)gHeroState) + 0x80;
                    v30[0] = 2.0f * FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]);
                    v30[1] = 2.0f * FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]);
                    v30[2] = 1.3f;
                    make_hit_descriptor((s32)((TI128*)v0), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x30000, 3.0f, (s32) ((TI128*)v30));
                    (*(u8*)((u8*)v10+9)) = 3;
                    v0[3] = 5627.925f;
                    (*(u8*)((u8*)v10+8)) = 0;
                    fTemp78 = ((Hero *)gHeroState)->f[0x98/4];
                    (*(u16*)((u8*)v10+10)) = M2C_FIELD(iTemp96, u16* , 0xAA);
                    v40[0] = FastSinOrCosA(fTemp78) * 0.8f;
                    fTemp7 = FastSinOrCosB(fTemp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = fTemp7;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) iTemp90);
                    EmitEffectsAtNearbyObjects((s32) iTemp96, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) iTemp96, (s32)((TI128*)v0)));
                    fTemp78 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], -0.8726647f);
                    v40[0] = FastSinOrCosA(fTemp78) * 0.8f;
                    fTemp9 = FastSinOrCosB(fTemp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = fTemp9;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) iTemp90);
                    EmitEffectsAtNearbyObjects((s32) iTemp96, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)v0)));
                    fTemp78 = FastAddRotations(((Hero *)gHeroState)->f[0x98/4], 0.8726647f);
                    v40[0] = FastSinOrCosA(fTemp78) * 0.8f;
                    fTemp11 = FastSinOrCosB(fTemp78) * 0.8f;
                    v40[2] = 0.55f;
                    v40[1] = fTemp11;
                    FastVecAdd((s32) &v40[0], (s32) &v40[0], (s32) iTemp90);
                    EmitEffectsAtNearbyObjects((s32) iTemp96, ProcessCollisionHit(0.8f, (s32) &v40[0], 0, (s32) iTemp96, (s32)((TI128*)v0)));
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
        iVal13 = 0;
        if ((((Hero *)gHeroState)->b[0x1494] != 0) && (((Hero *)gHeroState)->f[0x24C4/4] < 0.25f)) {
            iVal13 = 1;
        }
        if ((((Hero *)gHeroState)->b[0x22B9] != 0) || (iVal13 != 0)) {
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
            fTemp73 = ReadPadFloatHistory(1);
            if ((FastDiffRots(fTemp73, ReadPadFloatHistory(7)) > 1.9198624f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] == 1.0f)) {
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
            fTemp54 = ((Hero *)gHeroState)->f[0x1B0/4] + GetSpeedAlongHeroForward((s32)((TI128*)v0));
            ((Hero *)gHeroState)->f[0x1B0/4] = fTemp54;
            if (fTemp54 < 0.011666667f) {
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.011666667f;
            }
            ClearVector128((s32) pA60);
        }
        fVal53 = 1.0f;
        if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
            UpdateHeroTurnFromAnimation();
        } else {
            ((Hero *)gHeroState)->f[0x1458/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
            qcopy(&((Hero *)gHeroState)->q[0x1440/16], &((Hero *)gHeroState)->q[0x0/16]);
            if ((((Hero *)gHeroState)->i[0x2298/4] == 1) && (((Hero *)gHeroState)->b[0x40F] == 0) && (((Hero *)gHeroState)->b[0x22BA] == 0)) {
                SteerHeroHeading(0, 0.02f, 0.17f, 0.16580631f);
            } else {
                fTemp82 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
                if (((((Hero *)gHeroState)->f[0x24B8/4] < 0.9f) || ((((Hero *)gHeroState)->b[0x22BA] != 0) && (((Hero *)gHeroState)->b[0x40F] == 0))) && (fTemp82 > 0.78539824f)) {
                    fVal53 = 0.0f;
                }
                SetHeroTurnRates();
            }
        }
        ApplyHeroModePoseOffsets();
        UpdateHeroLeanAndSwayParameters();
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            fVal67 = 0.09916667f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.029178405f);
            if (fVal67 < 0.0f) {
                fVal67 = 0.0f;
            }
            if (fVal67 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                ((Hero *)gHeroState)->f[0x1B0/4] = fVal67;
            }
        }
        k005 = fVal53 * 0.005f;
        fVal54 = 0.0055555557f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            fVal39 = 2.617994f - ((Hero *)gHeroState)->f[0x1A8/4];
            if (fVal39 > 1.0f) {
                fVal39 = 1.0f;
            }
            if (fVal39 < 0.2f) {
                fVal39 = 0.2f;
            }
            fVal54 = 0.004722222f;
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * fVal39);
        }
        fTemp83 = FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]);
        if ((((Hero *)gHeroState)->f[0x24B8/4] < 0.75f) && (fTemp83 > 0.6108653f)) {
            fVal40 = 1.0f - (fTemp83 * 0.4f);
            if (fVal40 < 0.0f) {
                fVal40 = 0.0f;
            }
            ((Hero *)gHeroState)->f[0x1B0/4] = (f32) (((Hero *)gHeroState)->f[0x1B0/4] * fVal40);
        }
        ApproachHeroSpeed(k005, fVal54);
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
        ClampStickToUnitRange((s32)((TI128*)v0), (s32) (((void*)gHeroState) + 0x9F0), 0.17f);
        fVal59 = (((Hero *)gHeroState)->f[0x24B8/4] * 0.020362178f) * v0[0];
        if ((*(s32*)&D_L20_001A8FF0) == 0) {
            if (((Hero *)gHeroState)->i[0x1B8/4] < 0x3C) {
                fVal59 *= 0.1f;
                ((Hero *)gHeroState)->f[0x1B0/4] = 0.5f;
            }
        }
        if (((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) {
            RotateHeroMatrix(0.0f, 0.0f, fVal59);
        }
        ApproachHeroSpeed(0.027777778f, 0.004166667f);
        ComputeHeroPushDirection(99999.0f);
        if ((*(s32*)&D_L20_001A8FF0) != 0) {
            qcopy(v10, &((Hero *)gHeroState)->q[0x2D0/16]);
            ApplyHeroModeTransformReversed((s32) ((TI128*)v10), (s32) ((TI128*)v10), 0.17f);
            SpringVectorToTarget((s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0xA00), 0.04f, 0.3f, 0.125f);
        } else {
            SpringFloatToGoal((s32) (((void*)gHeroState) + 0x88), (s32) (((void*)gHeroState) + 0xA00), ((Hero *)gHeroState)->f[0x318/4] + 0.17f, 0.04f, 0.3f, 0.125f);
        }
        FastVecScale((s32) ((TI128*)v10), (s32)(gHeroState + 0x110), 3.0f);
        FastVecAdd((s32) ((TI128*)v10), (s32) ((TI128*)v10), (s32)(gHeroState + 0xE0));
        iTemp25 = ProcessCollisionHit(0.57f, (s32) ((TI128*)v10), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        if (iTemp25 != 0) {
            FastVecScale((s32) ((TI128*)v20), (s32)(gHeroState + 0x110), 7.0f);
            for (iVal22 = 0; iVal22 < iTemp25; iVal22++) {
                if (IsMobyInSpecialClassRange(((s32 *)D_L20_001C4480)[iVal22]) != 0) {
                    QueueImpactEffect(((s32 *)D_L20_001C4480)[iVal22], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v20), 1.0f);
                }
            }
        }
        SetCameraLimitsSlot0(0.017f, 0.3f);
        SetCameraLimitsSlot2(0.025f, 0.3f);
        SetCameraLimitsSlot3(0.03f, 0.27f);
        fVal68 = fVal59 * 27.0f;
        if (fVal68 > 1.7f) {
            fVal68 = 1.7f;
        } else if (fVal68 < -1.7f) {
            fVal68 = -1.7f;
        }
        fTemp12 = fVal68 * 0.5f;
        ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) -fVal68;
        ((Hero *)D_L20_00267210)->f[0x278/4] = fTemp12;
        ((Hero *)D_L20_00267210)->f[0x1C8/4] = fTemp12;
        break;
    case 0x2E:                                      /* switch 1 */
        SteerHeroReferencePoint();
        SetCameraLimitsSlot0(0.04f, 0.2f);
        SetCameraLimitsSlot1(0.04f, 0.2f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        iTemp65 = M2C_FIELD(fTemp89, u8* , 0x43);
        if (iTemp65 == 0x37) {
            fVal13 = 1.4f;
            fVal55 = ((Hero *)gHeroState)->f[0x1A8/4];
            if ((fVal55 > 1.4f) || (fVal13 = -1.4f, (fVal55 < -1.4f))) {
                fVal55 = fVal13;
            }
            ((Hero *)D_L20_00267210)->f[0x60/4] = (f32) (fVal55 * -0.14f);
            ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (fVal55 * 0.3f);
            ((Hero *)D_L20_00267210)->f[0x1C0/4] = (f32) (fVal55 * -0.22f);
            ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (fVal55 * 0.4f);
            ((Hero *)D_L20_00267210)->f[0x274/4] = (f32) (FloatAbs(fVal55) * -0.09f);
            ((Hero *)D_L20_00267210)->f[0x270/4] = (f32) (FloatAbs(fVal55) * 0.08f);
        } else if (iTemp65 == 0x66) {
            fTemp79 = FastAddRotations(fast_subtract_rotations(FastMatrixHelperA(((Hero *)gHeroState)->f[0x110/4], ((Hero *)gHeroState)->f[0x114/4]), ((Hero *)gHeroState)->f[0x98/4]), 3.1415927f);
            fVal60 = ((Hero *)gHeroState)->f[0x174/4] * 6.9813175f;
            if (fVal60 > 0.43633235f) {
                fVal60 = 0.43633235f;
            }
            fTemp56 = FastSinOrCosA(fTemp79) * fVal60;
            fTemp13 = -FastSinOrCosB(fTemp79);
            ((Hero *)D_L20_00267210)->f[0x114/4] = fTemp56;
            ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (fTemp13 * fVal60);
        }
        if (((Hero *)gHeroState)->h[0x34E/2] != 0) {
            fVal23 = 0.0069444445f;
            ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) (((void*)gHeroState) + 0x110), fVal23);
        } else {
            ((Hero *)gHeroState)->f[0xF8/4] = 0.0f;
            ApplyHeroModeTransform((s32) ((void*)gHeroState) + 0xF0, (s32) ((void*)gHeroState) + 0xF0, 0.041666668f);
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        iTemp41 = (*(s32*)&gCurrentMapIndex);
        if (iTemp41 == 0) {
            UpdateSoundSlotObject(2, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x13);
            iVal32 = gCurrentMapIndex;
        } else {
            if (iTemp41 != 1) {
                UpdateSoundSlotObject(2, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 6);
            }
            iVal32 = (*(s32*)&gCurrentMapIndex);
        }
        if ((u32) iVal32 < 2U) {
            EmitHeroRandomizedMotionEffects(4, 2, 1);
        } else {
            EmitHeroRandomizedMotionEffects(4, 2, 0);
            v0[0] = ((Hero *)gHeroState)->f[0x80/4] + RandomFloatRange(-0.25f, 0.25f);
            v0[1] = ((Hero *)gHeroState)->f[0x84/4] + RandomFloatRange(-0.25f, 0.25f);
            v0[2] = ((Hero *)gHeroState)->f[0x88/4] + RandomFloatRange(-0.1f, 0.4f);
            FastVecScale((s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0x110), 0.9f);
            v10[0] += RandomFloatRange(-0.011666667f, 0.011666667f);
            v10[1] += RandomFloatRange(-0.011666667f, 0.011666667f);
            v10[2] = M2C_BITWISE(f32, v10[2]) + RandomFloatRange(0.016666668f, 0.033333335f);
            SpawnTwoPointEffect((s32)((TI128*)v0), (s32) ((TI128*)v10), RandomFloatRange(37800.0f, 75600.0f));
        }
        ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0xB40/4];
        fTemp57 = ((Hero *)gHeroState)->f[0x98/4];
        SteerHeroHeading(0, 0.033f, 0.3f, 0.069813184f);
        fVal61 = FastDiffRots(((Hero *)gHeroState)->f[0x98/4], fTemp57);
        ClearVector128((s32) (((void*)gHeroState) + 0xF0));
        ShrinkHeroVectorByAmount(0.0019444445f);
        fTemp14 = ((Hero *)gHeroState)->f[0x118/4] - 0.013888889f;
        ((Hero *)gHeroState)->f[0xF8/4] = fTemp14;
        if (fTemp14 > -0.011111111f) {
            ((Hero *)gHeroState)->f[0xF8/4] = -0.011111111f;
        }
        if (fVal61 > 0.023271061f) {
            fVal61 = 0.023271061f;
        }
        fTemp58 = fVal61 * 9.0f;
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x90), fTemp58 * 0.5f, (s32) (((void*)gHeroState) + 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        ApproachWithVelocity((s32) (((void*)gHeroState) + 0x94), -((Hero *)gHeroState)->f[0xB44/4], (s32) (((void*)gHeroState) + 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        SetCameraLimitsSlot1(0.009f, 0.22f);
        SetCameraLimitsSlot2(0.04f, 0.2f);
        SetCameraLimitsSlot3(0.02f, 0.2f);
        ((Hero *)D_L20_00267210)->f[0x118/4] = (f32) (fTemp58 * 2.1f);
        ((Hero *)D_L20_00267210)->f[0x110/4] = (f32) (fTemp58 * 3.5f);
        break;
    case 0x27:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
    case 0x29:                                      /* switch 1 */
    case 0x2A:                                      /* switch 1 */
    case 0x3E:                                      /* switch 1 */
        iTemp55 = ((Hero *)gHeroState)->u[0x2294/4];
        if (((u32) (iTemp55 - 0x28) >= 2U) && (iTemp55 != 0x3E)) {
            UpdateSoundSlotObject(0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
        } else {
            iTemp18 = ((Hero *)gHeroState)->i[0x242C/4];
            if (iTemp18 != -1) {
                iTemp69 = (iTemp18 * 0x70) + (s32)gSoundState;
                if (M2C_FIELD(iTemp69, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) {
                    if (M2C_FIELD(iTemp69, u8* , 0x74) != 0) {
                        StopSoundVoice(iTemp18);
                    }
                }
            }
            ((Hero *)gHeroState)->i[0x242C/4] = -1;
        }
        iTemp56 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((iTemp56 == 0x27) || (iTemp56 == 0x2A)) {
            qcopy(v0, &((Hero *)gHeroState)->q[0x80/16]);
            fTemp59 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.0f, 0.52359885f));
            fTemp76 = RandomFloatRange(0.06666667f, 0.116666675f);
            v10[0] = FastSinOrCosA(fTemp59) * fTemp76;
            fTemp15 = FastSinOrCosB(fTemp59) * fTemp76;
            v10[2] = 0.0f;
            v10[1] = fTemp15;
            v10[2] = RandomFloatRange(0.050000004f, 0.083333336f);
            v10[3] = -0.008333334f;
            SpawnWhiteFlashParticle((s32)((TI128*)v0), (s32) ((TI128*)v10), 0, -1.0f);
        }
        iTemp77 = ((Hero *)gHeroState)->ptr[0x1248/4];
        iStack16 = 0;
        iTemp23 = (((LevelInfo *)D_L20_0026D970)[gItemSlotToRecord[(s32)iTemp77]].x1C != 0);
        if ((s32)iTemp77 == 0xD) {
            iTemp23 = 0;
        }
        if (iTemp23 != 0) {
            iStack16 = ((Hero *)gHeroState)->b[0x22BA] != 0;
        }
        iTemp91 = ((void*)gHeroState) + 0x80;
        find_nearest_path_point(((Hero *)gHeroState)->i[0x630/4], (s32) iTemp91, (s32) (((void*)gHeroState) + 0x5D0), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], 999.0f, 2.0f, 2.5f);
        if (((Hero *)gHeroState)->i[0x660/4] != 0) {
            find_nearest_path_point(((Hero *)gHeroState)->i[0x664/4], (s32) iTemp91, (s32) (((void*)gHeroState) + 0x610), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], 999.0f, 2.0f, 2.5f);
        }
        iVal21 = 0;
        if (((Hero *)gHeroState)->f[0x31C/4] > 1.0699999f) {
            iTemp57 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((iTemp57 != 0x28) && (iTemp57 != 0x3E) && (((Hero *)gHeroState)->i[0x660/4] == 0)) {
                iVal21 = ((Hero *)gHeroState)->i[0x1BC/4] >= 0x1F;
            }
        }
        if (iVal21 != 0) {
            ((Hero *)gHeroState)->i[0x6C8/4] = (s32) (((Hero *)gHeroState)->i[0x6C8/4] + 1);
        } else {
            ((Hero *)gHeroState)->i[0x6C8/4] = 0;
        }
        iTemp26 = ((Hero *)gHeroState)->i[0x640/4];
        if (((iTemp26 != 0) && ((((Hero *)gHeroState)->i[0x640/4] = iTemp26 + 1) != 0)) || (iVal21 != 0)) {
            qcopy(&((Hero *)gHeroState)->q[0xF0/16], &((Hero *)gHeroState)->q[0x120/16]);
            iTemp108 = ((void*)(gHeroState + 0xF0)) - 0xF0;
            if ((u32) (M2C_FIELD(iTemp108, s32* , 0x2294) - 0x28) < 2U) {
                ApplyHeroGravityAndJumpMotion();
            } else {
                M2C_FIELD(iTemp108, f32* , 0xF8) = (f32) (M2C_FIELD(iTemp108, f32* , 0xF8) - 0.0061111115f);
            }
        } else {
            fTemp39 = (f32) ((Hero *)gHeroState)->i[0x648/4];
            fVal44 = ((Hero *)gHeroState)->f[0x644/4] * fTemp39;
            if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                fVal44 = ((Hero *)gHeroState)->f[0x69C/4] * fTemp39;
            }
            Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32)((TI128*)v0), (s32) (((void*)gHeroState) + 0x634), (s32) (((void*)gHeroState) + 0x638), ((Hero *)gHeroState)->i[0x654/4], fVal44);
            if (((Hero *)gHeroState)->i[0x660/4] != 0) {
                Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x664/4], (s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0x668), (s32) (((void*)gHeroState) + 0x66C), ((Hero *)gHeroState)->i[0x670/4], fVal44);
            }
            if (((Hero *)gHeroState)->i[0x1BC/4] >= 0x5B) {
                fTemp60 = ((Hero *)gHeroState)->f[0x170/4] * 30.0f;
                qcopy(v20, &((Hero *)gHeroState)->q[0x80/16]);
                iStack8 = ((Hero *)gHeroState)->i[0x634/4];
                iStack9 = ((Hero *)gHeroState)->f[0x638/4];
                iTemp21 = Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)v20), (s32) &iStack8, (s32) &iStack9, ((Hero *)gHeroState)->i[0x654/4], fTemp60);
                qcopy(v30, &((Hero *)gHeroState)->q[0x80/16]);
                iStack8 = ((Hero *)gHeroState)->i[0x634/4];
                iStack9 = ((Hero *)gHeroState)->f[0x638/4];
                if ((((iTemp21 | Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)v30), (s32) &iStack8, (s32) &iStack9, ((Hero *)gHeroState)->i[0x654/4], fTemp60 + 0.1f)) == 0) || (((Hero *)gHeroState)->i[0x654/4] != 0)) && (((Hero *)gHeroState)->u[0x2294/4] == 0x27)) {
                    fVal45 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x64C/4], FastMatrixHelperA(v30[0] - v20[0], v30[1] - v20[1])) * 0.47f;
                    if (fVal45 > 0.78539824f) {
                        fVal45 = 0.78539824f;
                    }
                    if (fVal45 < -0.78539824f) {
                        fVal45 = -0.78539824f;
                    }
                    SetCameraLimitsSlot0(0.03f, 0.2f);
                    if (((Hero *)gHeroState)->i[0x65C/4] != 0) {
                        (*(f32*)&D_L20_00267274) = -fVal45;
                    } else {
                        (*(f32*)&D_L20_00267274) = fVal45;
                    }
                }
            }
            iTemp58 = ((Hero *)gHeroState)->u[0x2294/4];
            if ((iTemp58 != 0x28) && (iTemp58 != 0x3E) && (iTemp58 != 0x29)) {
                (*(f32*)&D_L20_00267270) = FastMatrixHelperA(vec_length_xy((s32) (((void*)gHeroState) + 0x110)), ((Hero *)gHeroState)->f[0x118/4]);
            }
            if (iTemp23 != 0) {
                k03 = 0.3f;
                SetCameraLimitsSlot3(0.017f, k03);
                SetCameraLimitsSlot1(0.027f, k03);
                SetCameraLimitsSlot2(0.027f, k03);
                iTemp15 = ((Hero *)gHeroState)->i[0x6A8/4];
                if (iTemp15 != 0) {
                    FastVecSub((s32) ((TI128*)v20), iTemp15 + 0x10, (s32) (((void*)gHeroState) + 0x80));
                    matrix_mul_vec3((s32) ((TI128*)v20), (s32) ((TI128*)v20), (s32) (((void*)gHeroState) + 0x40));
                    fTemp32 = FastMatrixHelperA(v20[0], v20[1]);
                    if (M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x42) == 0x31) {
                        fTemp32 = fast_subtract_rotations(fTemp32, 1.5707965f);
                        fVal41 = 0.2f;
                    } else {
                        fTemp32 = fast_subtract_rotations(fTemp32, -1.5707965f);
                        fVal41 = 0.5f;
                    }
                    ((Hero *)D_L20_00267210)->f[0x1C8/4] = (f32) (fTemp32 * fVal41);
                    ((Hero *)D_L20_00267210)->f[0x278/4] = (f32) (fTemp32 * k03);
                } else {
                    iTemp63 = M2C_FIELD(((Hero *)gHeroState)->ptr[0x2290/4], u8* , 0x43);
                    if (iTemp63 == 0x31) {
                        fVal62 = 0.58823526f;
                        fVal15 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        fVal46 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = fVal15;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                    } else if (iTemp63 == 0x48) {
                        fVal62 = 0.5f;
                        fVal15 = FastAddRotations(0.13962635f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        fVal46 = -0.06981318f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = fVal15;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                    } else if (iTemp63 == 0x47) {
                        fVal62 = 0.58823526f;
                        fVal15 = FastAddRotations(-0.8203048f, ((Hero *)gHeroState)->f[0x6A0/4]);
                        fVal46 = 0.73303837f;
                        ((Hero *)D_L20_00267210)->f[0x278/4] = fVal15;
                        ((Hero *)D_L20_00267210)->f[0x118/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                        ((Hero *)D_L20_00267210)->f[0x1C8/4] = FastAddRotations(fVal46, ((Hero *)gHeroState)->f[0x6A0/4] * fVal62);
                    }
                }
            }
            iTemp28 = AdvancePathIndex(((Hero *)gHeroState)->i[0x630/4], ((Hero *)gHeroState)->i[0x634/4], ((Hero *)gHeroState)->i[0x648/4], ((Hero *)gHeroState)->i[0x654/4]);
            FastVecSub((s32) ((TI128*)v20), (s32) &((TI128 *)((Hero *)gHeroState)->ptr[0x630/4])[iTemp28 + 1], (s32)((TI128*)v0));
            if (FastVecLength((s32) ((TI128*)v20)) < 0.001f) {
                if (((Hero *)gHeroState)->i[0x634/4] == iTemp28) {
                    ((Hero *)gHeroState)->i[0x640/4] = 1;
                } else {
                    goto block_807;
                }
            } else {
                ((Hero *)gHeroState)->f[0x64C/4] = FastMatrixHelperA(v20[0], v20[1]);
                ((Hero *)gHeroState)->f[0x650/4] = FastMatrixHelperA(vec_length_xy((s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]));
block_807:
                ((Hero *)gHeroState)->f[0x1A0/4] = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], ((Hero *)gHeroState)->f[0x658/4]);
                SteerHeroHeading(0, 0.015f, 0.15f, 0.10471977f);
                iTemp59 = ((Hero *)gHeroState)->u[0x2294/4];
                if ((((u32) (iTemp59 - 0x28) < 2U) && (((Hero *)gHeroState)->b[0x49C] == 0)) || (iTemp59 == 0x3E)) {
                    if (((Hero *)gHeroState)->i[0x694/4] != 0) {
                        fTemp19 = FastMatrixHelperA(((Hero *)gHeroState)->f[0x620/4] - ((Hero *)gHeroState)->f[0x80/4], ((Hero *)gHeroState)->f[0x624/4] - ((Hero *)gHeroState)->f[0x84/4]);
                        if (FastDiffRots(((Hero *)gHeroState)->f[0x98/4], fTemp19) < 1.5707965f) {
                            ((Hero *)gHeroState)->f[0x1A0/4] = fTemp19;
                            SteerHeroHeading(0, 0.04f, 0.2f, 0.10471977f);
                        }
                    }
                    if ((((Hero *)gHeroState)->i[0x660/4] != 0) && (((Hero *)gHeroState)->i[0x678/4] < 0x31)) {
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        iTemp29 = ((Hero *)gHeroState)->i[0x678/4] + 1;
                        ((Hero *)gHeroState)->i[0x678/4] = iTemp29;
                        FastVecScale((s32) ((TI128*)v20), (s32) ((TI128*)v20), (f32) iTemp29 * 0.020833334f);
                        fTemp61 = (f32) (((Hero *)gHeroState)->i[0x678/4] - 1) * 0.020833334f;
                        FastVecSub((s32) ((TI128*)v30), (s32)((TI128*)v0), (s32) ((TI128*)v10));
                        FastVecScale((s32) ((TI128*)v30), (s32) ((TI128*)v30), fTemp61);
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + (M2C_BITWISE(f32, v20[2]) - v30[2]));
                        FastVecAdd((s32) ((TI128*)v30), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                        FastVecSub((s32) ((TI128*)v20), (s32) ((TI128*)v30), (s32) (((void*)gHeroState) + 0x80));
                        ((Hero *)gHeroState)->f[0xF0/4] = v20[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = v20[1];
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32) (((void*)gHeroState) + 0x5D0));
                        fTemp85 = ((Hero *)gHeroState)->f[0x5D8/4];
                        fTemp40 = ((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, v20[2]);
                        ((Hero *)gHeroState)->f[0x88/4] = fTemp40;
                        if (fTemp40 < fTemp85) {
                            if (((Hero *)gHeroState)->i[0x678/4] < 0x31) {
                                if (fTemp40 < fTemp85) {
                                    ((Hero *)gHeroState)->f[0x88/4] = fTemp85;
                                }
                            }
                        }
                    } else {
                        FastVecSub((s32) ((TI128*)v20), (s32)((TI128*)v0), (s32)(gHeroState + 0x5D0));
                        ((Hero *)gHeroState)->f[0xF0/4] = v20[0];
                        ((Hero *)gHeroState)->f[0xF4/4] = v20[1];
                        ((Hero *)gHeroState)->f[0x88/4] = (f32) (((Hero *)gHeroState)->f[0x88/4] + M2C_BITWISE(f32, v20[2]));
                        FastVecSub((s32) ((TI128*)v30), (s32)(gHeroState + 0x5D0), (s32)(gHeroState + 0x80));
                        v30[2] = 0.0f;
                        if (FastVecLength((s32) ((TI128*)v30)) > 0.016666668f) {
                            vec_scale_to_length((s32) ((TI128*)v30), (s32) ((TI128*)v30), 0.016666668f);
                        }
                        ((Hero *)gHeroState)->f[0x80/4] = (f32) (((Hero *)gHeroState)->f[0x80/4] + v30[0]);
                        ((Hero *)gHeroState)->f[0x84/4] = (f32) (((Hero *)gHeroState)->f[0x84/4] + v30[1]);
                    }
                    if (((Hero *)gHeroState)->u[0x2294/4] == 0x3E) {
                        ((Hero *)gHeroState)->f[0xF8/4] = (f32) (((Hero *)gHeroState)->f[0xF8/4] - 0.006388889f);
                    } else {
                        ApplyHeroGravityAndJumpMotion();
                    }
                } else {
                    ((Hero *)gHeroState)->i[0x660/4] = 0;
                    fVal16 = 0.0f;
                    if ((((Hero *)gHeroState)->f[0x24B8/4] > 0.2f) && (iStack16 != 0)) {
                        ResolveStickInputToDirection(1.0f, 0);
                        fVal16 = fast_subtract_rotations(((Hero *)gHeroState)->f[0x1A0/4], ((Hero *)gHeroState)->f[0x64C/4]);
                        if (fVal16 > 0.78539824f) {
                            fVal16 = 0.78539824f;
                        } else if (fVal16 < -0.78539824f) {
                            fVal16 = -0.78539824f;
                        }
                    }
                    ApproachWithVelocity((s32)(gHeroState + 0x6A0), fVal16, (s32)(gHeroState + 0x6A4), 0.015f, 0.3f, 0.0f, 0);
                    ApproachValue((s32)(gHeroState + 0x680), 0.20000002f, 0.004166667f);
                    iStack10 = ((Hero *)gHeroState)->i[0x634/4];
                    iStack11 = ((Hero *)gHeroState)->f[0x638/4];
                    qcopy(v20, &((Hero *)gHeroState)->q[0x80/16]);
                    Spline_AdvanceByDistance(((Hero *)gHeroState)->i[0x630/4], (s32) ((TI128*)v20), (s32) &iStack10, (s32) &iStack11, ((Hero *)gHeroState)->i[0x654/4], 0.3f);
                    fTemp16 = FastMatrixHelperA(vec_distance_xy((s32)(gHeroState + 0x5D0), (s32) ((TI128*)v20)), M2C_BITWISE(f32, v20[2]) - ((Hero *)gHeroState)->f[0x5D8/4]);
                    if (fTemp16 > 0.0f) {
                        fVal24 = fTemp16 * -0.07957746f;
                        if (fTemp16 > 0.26179942f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 0;
                        } else if ((fTemp16 < 0.13962635f) && (((Hero *)gHeroState)->i[0x67C/4] == 0)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    } else {
                        fVal24 = -fTemp16 * 0.38197184f;
                        if (fTemp16 < -0.19198623f) {
                            ((Hero *)gHeroState)->i[0x67C/4] = 1;
                        } else if ((fTemp16 > -0.122173056f) && (((Hero *)gHeroState)->i[0x67C/4] == 1)) {
                            ((Hero *)gHeroState)->i[0x67C/4] = -1;
                        }
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < fVal24) {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), fVal24, 0.0022222223f);
                    } else {
                        ApproachValue((s32) (((void*)gHeroState) + 0x674), fVal24, 0.00055555557f);
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] > 0.20000002f) {
                        ((Hero *)gHeroState)->f[0x674/4] = 0.20000002f;
                    }
                    if (((Hero *)gHeroState)->f[0x674/4] < -0.041666668f) {
                        ((Hero *)gHeroState)->f[0x674/4] = -0.041666668f;
                    }
                    fTemp17 = ((Hero *)gHeroState)->f[0x680/4] + ((Hero *)gHeroState)->f[0x674/4];
                    ((Hero *)gHeroState)->f[0x644/4] = fTemp17;
                    if (fTemp17 < 0.0f) {
                        ((Hero *)gHeroState)->f[0x644/4] = 0.0f;
                    }
                    iTemp82 = ((void*)gHeroState) + 0x5D0;
                    FastVecSub((s32) (((void*)gHeroState) + 0xF0), (s32)((TI128*)v0), (s32) iTemp82);
                    iTemp97 = ((void*)gHeroState) + 0x80;
                    FastVecSub((s32) ((TI128*)v20), (s32) iTemp82, (s32) iTemp97);
                    iStack12 = -FastVecLength((s32) ((TI128*)v20));
                    SpringFloatToGoal((s32) &iStack12, (s32) (((void*)gHeroState) + 0x6AC), 0.0f, 0.03f, 0.3f, 0.116666675f);
                    fTemp18 = FastVecLength((s32) ((TI128*)v20));
                    if (fTemp18 < ((Hero *)gHeroState)->f[0x6AC/4]) {
                        ((Hero *)gHeroState)->f[0x6AC/4] = fTemp18;
                    }
                    fTemp33 = ((Hero *)gHeroState)->f[0x6AC/4];
                    if (fTemp33 < fTemp18) {
                        vec_scale_to_length((s32) ((TI128*)v20), (s32) ((TI128*)v20), fTemp33);
                    }
                    FastVecAdd((s32) iTemp97, (s32) iTemp97, (s32) ((TI128*)v20));
                    fTemp88 = ((Hero *)gHeroState)->f[0x88/4];
                    fTemp84 = ((Hero *)gHeroState)->f[0x5D8/4];
                    if (fTemp88 < fTemp84) {
                        if (((Hero *)gHeroState)->f[0x31C/4] < 1.0f) {
                            if (fTemp88 < fTemp84) {
                                ((Hero *)gHeroState)->f[0x88/4] = fTemp84;
                            }
                        }
                    }
                }
                if (((Hero *)gHeroState)->u[0x2294/4] == 0x2A) {
                    if (((Hero *)gHeroState)->i[0x1B8/4] < 0x14) {
                        fTemp20 = FastAddRotations(((Hero *)gHeroState)->f[0x64C/4], RandomSignedFloatRange(0.3490659f, 0.6108653f));
                        v50[0] = FastSinOrCosA(fTemp20);
                        v50[1] = FastSinOrCosB(fTemp20);
                        v50[2] = 0.0f;
                        make_hit_descriptor((s32) ((TI128*)v20), (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, 1.0f, (s32) &v50[0]);
                        qcopy(v60, &((Hero *)gHeroState)->q[0x80/16]);
                        v60[2] += 0.6f;
                        ProcessCollisionHit(1.0f, (s32) ((TI128*)v60), 0x10, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32) ((TI128*)v20));
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
            iVal34 = FloatToInt(((Hero *)gHeroState)->f[0xC38/4]) * 4;
            iVal38 = (s32)D_L20_001ACEE8;
            vec_scale_to_length((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), *(f32*)(iVal34 + iVal38) * 0.5f);
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
            fVal25 = 0.0f;
            if (((Hero *)gHeroState)->f[0x31C/4] > 4.0f) {
                fVal25 = 0.43633235f;
            }
            qcopy(v0, &((Hero *)gHeroState)->q[0x90/16]);
            ApproachWithVelocity((s32) &v0[1], fVal25, (s32) (((void*)gHeroState) + 0xA4), 0.02f, 0.3f, 0.043633237f, 0);
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
        iVal47 = ((void*)gHeroState) + 0xF0;
        ApplyHeroModePoseOffsets();
        BuildHeroMoveImpulse(0.7f, 0.0f);
        ApplyHeroModeTransform((s32) iVal47, (s32) iVal47, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) iVal47) < -0.8333334f) {
            SetViewSpaceHeight((s32) iVal47, (s32) iVal47, -0.8333334f);
        }
        break;
    case 0x74:                                      /* switch 1 */
        ((Hero *)gHeroState)->c[0x22BC] = 1;
        iVal2 = ((void*)gHeroState) + 0xF0;
        ApproachValue((s32) (((void*)gHeroState) + 0xA88), ((Hero *)gHeroState)->f[0xA90/4], 0.0024240687f);
        ApproachValue((s32) (((void*)gHeroState) + 0xA8C), ((Hero *)gHeroState)->f[0xA94/4], 0.0024240687f);
        StartHeroPoseOffset(((Hero *)gHeroState)->f[0xA88/4], ((Hero *)gHeroState)->f[0xA8C/4], 0.0f);
        func_L00_002EE4D8((s32) iVal2, (s32) iVal2, vec_length_xy((s32) iVal2) * 0.9f);
        ApplyHeroModeTransform((s32) iVal2, (s32) iVal2, ((Hero *)gHeroState)->f[0xA80/4]);
        if (GetViewSpaceHeight((s32) iVal2) < -0.8333334f) {
            SetViewSpaceHeight((s32) iVal2, (s32) iVal2, -0.8333334f);
        }
        break;
    case 0x82:                                      /* switch 1 */
        UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        ang82 = (f32) LerpInt(0x2D0, 0xB4, ((Hero *)gHeroState)->f[0x5B0/4] * 0.02f) * 0.00029088825f;
        ShowGaugePopup(2, UpdateAngleAndBlend((s32) (((void*)gHeroState) + 0x5A0), 0x60FFFFFF, 0x40FFC0A0, ang82), 0, 1.0f - (((Hero *)gHeroState)->f[0x5B0/4] * 0.02f));
        iVal14 = (s32) ((Hero *)gPadState)->d[0x1A0/8] & 0x40;
        if (((Hero *)gHeroState)->f[0x5B0/4] == 0.0f) {
            iVal14 = 0;
        }
        if (iVal14 != 0) {
            ApproachValue((s32) (((void*)gHeroState) + 0x5B0), 0.0f, 0.1f);
            iTemp70 = ((void*)gHeroState) + 0xF0;
            OffsetPointInViewSpace((s32) iTemp70, (s32) iTemp70, 0.025f);
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
        fTemp34 = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        if ((((Hero *)gHeroState)->f[0x5B0/4] > 25.0f) && (((Hero *)gHeroState)->h[0x5BE/2] < 0x5A) && (fTemp34 < 0.0f) && (fTemp86 = ((Hero *)gHeroState)->f[0x31C/4], (fTemp86 < 1.2f))) {
            fVal3 = (fTemp86 - 0.25f) * 1.0526315f;
            ((Hero *)gHeroState)->h[0x5BE/2] = (s16) ((u16) ((Hero *)gHeroState)->h[0x5BE/2] + 1);
            if (fVal3 < 0.0f) {
                fVal3 = 0.0f;
            }
            SetViewSpaceHeight((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), fTemp34 * fVal3);
            if (((Hero *)gHeroState)->f[0x31C/4] < 0.25f) {
                SpringFloatToGoal((s32)(gHeroState + 0x88), (s32)(gHeroState + 0x5B4), ((Hero *)gHeroState)->f[0x318/4] + 0.25f, 0.027f, 0.3f, 0.083333336f);
            }
        } else if (fTemp34 > 0.0f) {
            ((Hero *)gHeroState)->h[0x5BE/2] = 0;
        }
        (*(f32*)&D_L20_001BA248) = GetViewSpaceHeight((s32)(gHeroState + 0xF0));
        ApplyHeroModePoseOffsets();
        ResolveStickInputToDirection(((Hero *)gHeroState)->f[0x24B8/4] * 0.20000002f, 0);
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            ((Hero *)gHeroState)->f[0x1A0/4] = (f32) ((Hero *)gHeroState)->f[0x98/4];
        }
        SteerHeroHeading(0, 0.027f, 0.3f, ((Hero *)gHeroState)->f[0x24B8/4] * 0.087266475f);
        fVal26 = 0.0013888889f;
        if (((Hero *)gHeroState)->f[0x24B8/4] < 0.2f) {
            fVal26 = 0.00055555557f;
        }
        ApproachHeroVelocity(fVal26);
        break;
    case 0x8:                                       /* switch 1 */
        if (hero_slot_item_id(3) == 2) {
            iTemp19 = ((Hero *)gHeroState)->i[0x243C/4];
            if (iTemp19 != -1) {
                iTemp71 = (iTemp19 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(iTemp71, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(iTemp71, u8* , 0x74) != 0)) {
                    StopSoundVoice(iTemp19);
                }
            }
            ((Hero *)gHeroState)->i[0x243C/4] = -1;
            UpdateSoundSlotObject(3, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 2);
        } else {
            iTemp20 = ((Hero *)gHeroState)->i[0x2438/4];
            if (iTemp20 != -1) {
                iTemp72 = (iTemp20 * 0x70) + (s32)gSoundState;
                if ((M2C_FIELD(iTemp72, s32* , 0x88) == ((Hero *)gHeroState)->ptr[0x2290/4]) && (M2C_FIELD(iTemp72, u8* , 0x74) != 0)) {
                    StopSoundVoice(iTemp20);
                }
            }
            ((Hero *)gHeroState)->i[0x2438/4] = -1;
            UpdateSoundSlotObject(4, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0xD);
        }
        fVal64 = 0.050000004f;
        if (((Hero *)gHeroState)->i[0x1338/4] == 3) {
            fVal64 = 0.083333336f;
        }
        fVal65 = 0.72f;
        fTemp41 = ((Hero *)gHeroState)->f[0x24C8/4];
        if (((Hero *)gHeroState)->b[0x24EF] != 0) {
            fVal64 = 0.12833333f;
            fVal65 = 0.98640007f;
        }
        if (fTemp41 != 0.0f) {
            fVal65 = fTemp41;
        }
        iTemp83 = ((void*)gHeroState) + 0xF0;
        iStack13 = GetViewSpaceHeight((s32) iTemp83);
        ResolveStickInputToDirection(fVal64, 0);
        SteerHeroHeading(0, 0.025f, 0.3f, 0.20943955f);
        ApproachHeroSpeed(0.004166667f, 0.0019444445f);
        ComputeHeroPushDirection(99999.0f);
        ApplyHeroModePoseOffsets();
        ProjectVectorOntoViewPlane((s32) iTemp83, (s32) iTemp83);
        SpringFloatToGoal((s32) &iStack13, (s32) (((void*)gHeroState) + 0xA98), -fVal64 * fVal65, 0.025f, 0.3f, 0.28333336f);
        ApplyHeroModeTransform((s32) iTemp83, (s32) iTemp83, -iStack13);
        fTemp35 = ((Hero *)gHeroState)->f[0x88/4];
        if (fTemp35 < ((Hero *)gHeroState)->f[0x490/4]) {
            ApproachValue((s32) (((void*)gHeroState) + 0x490), fTemp35, 0.06666667f);
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
            fTemp42 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((fTemp42 >= 4.0f) && (fTemp42 <= 7.0f)) {
                EmitHeroRandomizedMotionEffects(7, 0, 0);
            }
        }
        iTemp1 = ((Hero *)gHeroState)->h[0x4AC/2];
        iTemp16 = ((Hero *)gHeroState)->i[0x1B8/4];
        if (iTemp16 == iTemp1) {
            qcopy(&((Hero *)gHeroState)->q[0x460/16], &((Hero *)gHeroState)->q[0x80/16]);
        }
        if ((((Hero *)gHeroState)->b[0x49C] != 0) || ((iTemp16 < iTemp1) && (iTemp60 = ((Hero *)gHeroState)->u[0x2294/4], (iTemp60 != 0xB)) && (iTemp60 != 0x10) && (iTemp60 != 0xC) && (iTemp60 != 0x11) && (iTemp60 != 0x1B) && (iTemp60 != 0x89) && (iTemp60 != 0x48))) {
            if (((Hero *)gHeroState)->h[0x528/2] != 0) {
                SteerHeroReferencePoint();
                if ((((Hero *)gHeroState)->u[0x2294/4] == 0xA) && (((Hero *)gHeroState)->i[0x1B8/4] < 0xA) && (((Hero *)gHeroState)->f[0x178/4] < 0.116666675f)) {
                    ((Hero *)gHeroState)->f[0xF0/4] = (f32) (((Hero *)gHeroState)->f[0xF0/4] + (FastSinOrCosA(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    ((Hero *)gHeroState)->f[0xF4/4] = (f32) (((Hero *)gHeroState)->f[0xF4/4] + (FastSinOrCosB(((Hero *)gHeroState)->f[0x98/4]) * 0.011666667f));
                    qcopy(&((Hero *)gHeroState)->q[0x140/16], &((Hero *)gHeroState)->q[0xF0/16]);
                }
            } else {
                SteerHeroHeading(0, 0.015f, 0.2f, 0.2501639f);
                fTemp62 = ((Hero *)gHeroState)->f[0x1B4/4];
                if ((u8) ((Hero *)gHeroState)->b[0x49C] >= 2U) {
                    ((Hero *)gHeroState)->f[0x1B4/4] = (f32) (fTemp62 * 0.4f);
                }
                if (((Hero *)gHeroState)->h[0x1454/2] != 0) {
                    ComputeHeroPushDirection(((Hero *)gHeroState)->f[0x1458/4]);
                } else {
                    ComputeHeroPushDirection(99999.0f);
                }
                ((Hero *)gHeroState)->f[0x1B4/4] = fTemp62;
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
                    iTemp42 = ((Hero *)gHeroState)->i[0x1B8/4];
                    if (iTemp42 < (((Hero *)gHeroState)->h[0x4AC/2] + 4)) {
                        OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) iTemp42 * 0.0044444446f);
                    }
                }
                if (((Hero *)gHeroState)->u[0x2294/4] == 0xA) {
                    iTemp43 = ((Hero *)gHeroState)->i[0x1B8/4];
                    if (iTemp43 < 0x22) {
                        OffsetPointBySideDirection((s32) (((void*)gHeroState) + 0xF0), (s32) (((void*)gHeroState) + 0xF0), (f32) iTemp43 * 0.014722222f);
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
                iTemp84 = ((void*)gHeroState) + 0xF0;
                fVal4 = vec_length_xy((s32) iTemp84);
                if (fVal4 > 0.06166667f) {
                    fVal4 = 0.06166667f;
                }
                FastVectorNormalizeHelper((s32) iTemp84, (s32) iTemp84, fVal4);
            }
        }
        fTemp43 = ((Hero *)gHeroState)->f[0x318/4];
        fTemp87 = ((Hero *)gHeroState)->f[0x490/4];
        if (fTemp87 < fTemp43) {
            fTemp21 = fTemp87 + 0.10000001f;
            ((Hero *)gHeroState)->f[0x490/4] = fTemp21;
            if (fTemp43 < fTemp21) {
                ((Hero *)gHeroState)->f[0x490/4] = fTemp43;
            }
        }
        fTemp44 = ((Hero *)gHeroState)->f[0x88/4];
        if (fTemp44 < ((Hero *)gHeroState)->f[0x490/4]) {
            ((Hero *)gHeroState)->f[0x490/4] = fTemp44;
        }
        if ((((Hero *)gHeroState)->h[0x4AC/2] < ((Hero *)gHeroState)->i[0x1B8/4]) && (GetViewSpaceHeight((s32) (((void*)gHeroState) + 0xF0)) < 0.001f) && ((((Hero *)gHeroState)->b[0x49D] == 0) || (((Hero *)gHeroState)->i[0x1B8/4] > ((Hero *)gHeroState)->i[0x434/4])) && ((((Hero *)gHeroState)->u[0x2294/4] != 0xE) || (((Hero *)gHeroState)->i[0x1B8/4] >= 0x12))) {
            fTemp45 = ((Hero *)gHeroState)->f[0x458/4];
            ((Hero *)gHeroState)->b[0x49E] = 1U;
            if (fTemp45 != 0.0f) {
                ((Hero *)gHeroState)->f[0x520/4] = fTemp45;
            }
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 0) {
            ApplyHeroModePoseOffsets();
        }
        if (((Hero *)gHeroState)->b[0x22B4] == 1) {
            UpdateHeroMotionResponseParameters();
        }
        iTemp61 = ((Hero *)gHeroState)->u[0x2294/4];
        if ((iTemp61 == 0x10) || (iTemp61 == 0xD)) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xD) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x81) {
            UpdateTransformHistoryFollowers((s32) (((void*)gHeroState) + 0x18E0), (((Hero *)gHeroState)->i[0x1B8/4] < 0xE) ? 0 : 2);
        }
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x10) {
            if (((Hero *)gHeroState)->i[0x1B8/4] >= 9) {
                if (((Hero *)gHeroState)->f[0xC38/4] < 28.0f) {
                    BuildHeroRelativePoint((s32)((TI128*)v0), 1, 0.8f, 0.0f, 0.3f);
                    iTemp30 = ProcessCollisionHit(0.9f, (s32)((TI128*)v0), 0, (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0);
                    if (iTemp30 != 0) {
                        FastVecScale((s32) ((TI128*)v10), (s32) (((void*)gHeroState) + 0x110), 7.0f);
                        for (iVal23 = 0; iVal23 < iTemp30; iVal23++) {
                            if (IsMobyInSpecialClassRange(((s32 *)D_L20_001C4480)[iVal23]) != 0) {
                                QueueImpactEffect(((s32 *)D_L20_001C4480)[iVal23], (s32) ((Hero *)gHeroState)->ptr[0x2290/4], 0x10000, (s32) (((void*)gHeroState) + 0x80), (s32) ((TI128*)v10), 1.0f);
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
        fVal47 = GetViewSpaceVectorLength((s32)(gHeroState + 0xF0));
        fVal5 = 0.0011111111f;
        if ((((Hero *)gHeroState)->h[0x34E/2] == 0) && (((Hero *)gHeroState)->i[0x1B8/4] >= 0xB)) {
            fVal5 = 0.0027777778f;
        }
        fVal47 = fVal47 - fVal5;
        if (fVal47 < 0.0f) {
            fVal47 = 0.0f;
        }
        if (((Hero *)gHeroState)->b[0x1497] != 0) {
            TryHeroSurfacePushResponse(3.7f, 0.0f, 0.35f);
        }
        iVal46 = ((void*)gHeroState) + 0xF0;
        SetViewSpaceVectorLength((s32) iVal46, (s32) iVal46, fVal47);
        ApplyHeroModeTransform((s32) iVal46, (s32) iVal46, 0.004f);
        break;
    case 0x8C:                                      /* switch 1 */
        qzero(D_00189F10);
        ((Hero *)gHeroState)->f[0xF8/4] = -0.38333336f;
        break;
    case 0x62:                                      /* switch 1 */
        FastVecSub((s32)((TI128*)v0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(v0[0], v0[1]);
        fTemp23 = vec_length_xy((s32)((TI128*)v0));
        if (fTemp23 > 0.2f) {
            hp32 = (Hero *)gHeroState;
            hp32->f[0x24B8/4] = 1.0f;
            ((Hero *)gHeroState)->f[0x1A0/4] = FastMatrixHelperA(v0[0], v0[1]);
            ((Hero *)gHeroState)->f[0x1B0/4] = fTemp23;
            if (fTemp23 < D_L20_001A7DAC[0][2]) {
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
        FastVecSub((s32)((TI128*)v0), (s32)(gHeroState + 0x18A0), (s32)(gHeroState + 0x80));
        if (FastVecDot((s32)((TI128*)v0), (s32)(gHeroState + 0x160)) < 0.0f) {
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
        iTemp109 = (s32) &D_L20_00268D90[((Hero *)gHeroState)->h[0xBFC/2]];
        iTemp6 = M2C_FIELD(iTemp109, s32* , 4);
        switch (iTemp6) {
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
            fTemp46 = ((Hero *)gHeroState)->f[0xC38/4];
            if ((f32) M2C_FIELD(iTemp109, s32* , 0x1C) <= fTemp46) {
                if (fTemp46 <= (f32) M2C_FIELD(iTemp109, s32* , 0x20)) {
                    iTemp22 = ((M2C_FIELD(iTemp109, s32* , 4) ^ 1) == 0) ? 0 : 2;
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], iTemp22, (s32) ((TI128*)v10));
                    TransformMobyJointToWorld((s32) ((Hero *)gHeroState)->ptr[0x2290/4], iTemp22 | 1, (s32) ((TI128*)v20));
                    FastVecAdd((s32)((TI128*)v0), (s32) ((TI128*)v10), (s32) ((TI128*)v20));
                    FastVecScale((s32)((TI128*)v0), (s32)((TI128*)v0), 0.5f);
                    SweepCollisionFromObject((s32) ((Hero *)gHeroState)->ptr[0x2290/4], (s32)((TI128*)v0), 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
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
        fVal1 = 0.005f;
        iVal3 = ((void*)gHeroState) + 0x130;
        ApplyHeroModeTransform((s32)(gHeroState + 0xF0), (s32) iVal3, fVal1);
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
        fVal36 = 0.16580631f;
        fVal28 = 0.033f;
        if (((Hero *)gHeroState)->b[0x40F] != 0) {
            fVal36 = 0.19489513f;
            fVal28 = 0.037f;
        }
        SteerHeroHeading(0, fVal28, 0.15f, fVal36);
        ApproachHeroSpeed(0.005f, 0.0055555557f);
        if (((Hero *)gHeroState)->f[0x174/4] < 0.011666667f) {
            ((Hero *)gHeroState)->b[0x40C] = 1U;
            if ((FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.7453294f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
                ((Hero *)gHeroState)->b[0x40F] = 1U;
            }
        }
        fTemp64 = ReadPadFloatHistory(0);
        if ((FastDiffRots(fTemp64, ReadPadFloatHistory(2)) > 2.617994f) && (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) > 1.2217306f) && (((Hero *)gHeroState)->f[0x24B8/4] > 0.8f)) {
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
                fVal69 = 0.050000004f - (FloatAbs(((Hero *)gHeroState)->f[0x1A8/4]) * 0.02122066f);
                if (fVal69 < 0.0f) {
                    fVal69 = 0.0f;
                }
                if (fVal69 < ((Hero *)gHeroState)->f[0x1B0/4]) {
                    ((Hero *)gHeroState)->f[0x1B0/4] = fVal69;
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
        fTemp36 = vec_length_xy((s32)(gHeroState + 0xF0));
        if (*(s16 *)(gHeroState + 0x34E) != 0) {
            fTemp36 = fTemp36 * 0.99f;
        } else {
            fTemp36 = fTemp36 * 0.92f;
        }
        func_L00_002EE4D8((s32)(gHeroState + 0xF0), (s32)(gHeroState + 0xF0), fTemp36);
        iTemp110 = ((void*)(gHeroState + 0xF0)) - 0xF0;
        M2C_FIELD(iTemp110, s32* , 0xF8) = 0;
        if (M2C_FIELD(iTemp110, s16* , 0x34E) != 0) {
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
        FastVecSub((s32) ((TI128*)v60), (s32)(gHeroState + 0x560), (s32)(gHeroState + 0x550));
        ClearVector128((s32) (((void*)gHeroState) + 0xF0));
        if (((Hero *)gHeroState)->u[0x2294/4] == 0x49) {
            FastVecCross((s32) &v40[0], (s32) (((void*)gHeroState) + 0x2C0), (s32) ((TI128*)v60));
        } else {
            FastVecCross((s32) &v40[0], (s32) ((TI128*)v60), (s32) (((void*)gHeroState) + 0x2C0));
        }
        vec_scale_to_length((s32) &v40[0], (s32) &v40[0], 0.2f);
        FastVecAdd((s32) &v50[0], (s32)(gHeroState + 0x80), (s32) &v40[0]);
        if ((FindHeroLedgeGrab((s32)(gHeroState + 0x80), (s32)(gHeroState + 0x90), 0) != 0) && (FindHeroLedgeGrab((s32) &v50[0], (s32)(gHeroState + 0x90), (s32)((TI128*)v0)) != 0)) {
            FastVecSub((s32)(gHeroState + 0xF0), (s32)((TI128*)v0), (s32)(gHeroState + 0x80));
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
    if (iStack14 != ((Hero *)gHeroState)->i[0x2298/4]) {
        ((Hero *)gHeroState)->i[0x1C0/4] = 0;
    }
    if (iStack15 != M2C_FIELD(fTemp89, u8* , 0x43)) {
        ((Hero *)gHeroState)->i[0x1C4/4] = 0;
    }
}

