#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef TI128 V4_F6a70b950;
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
typedef struct {
    char pad0[35];         
    unsigned char f35;     
    char pad36[8];         
    float f44;             
    unsigned char f48;     
    unsigned char f49;     
    unsigned short f50;    
    unsigned short f52;    
    char pad54[2];         
    long long f56;         
    char pad64[34];        
    unsigned char f98;     
    char pad99[21];        
    int f120;              
    unsigned short f124;   
    char pad126[26];       
    int f152;              
    char pad156[14];       
    short f170;            
} Src_F66766f2b;
typedef struct {
    char pad0[256];        
    int a[4];              
    int b[4];              
    Src_F66766f2b *c[4];             
    float d[4];            
    int pad320;            
    Src_F66766f2b *src;              
    int count;             
} List_F66766f2b;
extern f32 func_00282C48(f32);
extern void func_00282C88(TI128 *);
extern s32 func_002A7820(s32, s32);
extern f32 func_002A78D8(f32, f32);
extern void *func_002A9640(void *, u32, s32);
extern void func_002AC9F8(float *, float);
extern s32 func_L00_002A4EF0(s32);
extern void func_L00_002AB3E0(void);
extern u32 func_L00_002ADE68(s32);
extern s32 func_L00_002ADF80(void);
extern f32 func_L00_002AE070(int);
extern void func_PAL_L00_002AF6C0(void);
extern s32 func_L00_002B3248(u8 *);
extern void func_L00_002B6118(f32);
extern f32 func_L00_002B9B38(void *, int);
extern int func_L00_002B9B88(int, int);
extern int func_L00_002C3A78(void);
extern void func_L00_002D2470(s32, s32);
extern f32 func_L00_002D3A58(char *);
extern void func_L00_002D3B58(V4_F6a70b950 *, V4_F6a70b950 *, float);
extern int func_L00_002D6900(unsigned int);
extern void func_L00_002D6940(void);
extern void func_L00_00322A98(void *, char *);
extern void func_L00_00322AC0(List_F66766f2b *, int, int, float);
extern void func_L00_00322EC8(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern int func_L00_0035F5A0(int, int, int);
extern void func_L01_002C1988(int);
extern s32 func_L18_004283F0(u8 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern f32 func_00282E20(void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283C80(f32, f32);
extern s32 func_00283CF0(f32);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002FD1B8(void *, s32, u32, f32, f32, f32, f32);
extern void func_PAL_L00_002A4D58(int);
extern void func_PAL_L00_002A6058(int, int, int, int);
extern void func_L00_002A6708(void);
extern void func_PAL_L00_002AAAC8(int, int, int);
extern void func_PAL_L00_002AF2C8(int, int);
extern void func_L00_002B39F0(int, f32);
extern void func_L00_002B75A0(f32, f32, f32);
extern void func_PAL_L00_002BA480(void);
extern int func_PAL_L00_002CB2C8(void);
extern void func_PAL_L00_002D2668(int, int, f32);
extern void func_L00_0041E958(f32, f32, f32);
extern s32 func_L04_002CC748(int);
extern u32 D_001A7390;
extern s32 D_001A7B90;
extern u8 D_001A7A40[8];
extern u8 D_L04_001A7DE0[8] __attribute__((sda));
extern u8 D_L04_001A7E00[8] __attribute__((sda));
extern s32 D_L04_00276890[][11];
extern u8 *D_L04_001B2C70;
extern s32 D_L04_001B2C78;
extern u8 D_00189E20[];
extern u32 D_001A79F0;
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
extern Statistics D_0018C360[];
extern Statistics D_0018C750[];
extern s32 D_L04_001A8F00;
extern s32 D_L04_001A8FF4 __attribute__((sda));
extern f32 D_L04_001A7CD8 __attribute__((sda));
extern f32 D_L04_001A7CDC __attribute__((sda));
extern s32 D_L04_001A7DD8[2] __attribute__((sda));
extern f32 D_L04_00276A20[][25];
extern u8 D_L04_00276BB0[];
typedef struct { u8 pad0[0x148]; f32 f148; u8 pad14C[0x400 - 0x14C]; s32 i400; } L19State_1B9900;
extern L19State_1B9900 D_L04_001B9540;
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
#define HP ((Hero *)D_00189E20)
#define BYTE(o) (HP->b[(o)])
#define HALF(o) (HP->uh[(o)/2])
#define SHORT(o) (HP->h[(o)/2])
#define WORD(o) (HP->i[(o)/4])
#define BITS(o) (HP->u[(o)/4])
#define REAL(o) (HP->f[(o)/4])
#define PTR(o) (HP->ptr[(o)/4])
#define VEC(o) (D_00189E20 + (o))
#define COPY_VECTOR(dst,src) (*(TI128 *)VEC(dst) = *(TI128 *)VEC(src))

/* Changes the player's action, initializes its movement parameters and selects animation. */
s32 func_PAL_L04_002E7DA8(s32 action, s32 animate) {
    u8 *objectSnapshot;
    u8 *hit_10, *hit_29, *hit_44, *hit_45, *hit_52;
    s32 oldStep;
    u8 wasGliding;
    u8 oldWeapon;
    s32 current, mode, index;
    f32 angle_13;
    u32 animation_13;
    u32 animation_14;
    s32 selected_13;
    s32 selected_14;
    s32 selected_15;
    s32 selected_83;
    s32 selected_8, selected_9, selected_18, selected_21, selected_22, selected_52;
    u32 animation_16, animation_21, animation_22, animation_41, animation_43, animation_53;
    f32 frames;
    f32 angle_53;
    f32 value_18, value_21, value_22, value_37;
    if (WORD(0x229C) == 0x14 && (action != 0x61 || animate != 2)) return 0;
    if ((D_L04_001A8F00 == 2 || D_L04_001A8F00 == 6) && animate != 2) return 0;
    if (WORD(0x24CC) == 0 && (WORD(0x229C) == 2 || WORD(0x229C) == 7)) {
        if (action != 6 && action != 0x39 && action != 0x43 && action != 0x91 &&
            action != 0x5F && action != 0x74 && action != 0x78 && action != 0x79 &&
            action != 0x7C && action != 0x67 && action != 0x7D && action != 0x7F) return 0;
    }
    objectSnapshot = PTR(0x2290);
    oldStep = WORD(0x2298);
    wasGliding = BYTE(0x22B7);
    WORD(0x22AC) = WORD(0x22A0);
    WORD(0x22B0) = WORD(0x22A4);
    WORD(0x22A8) = WORD(0x1B8);
    WORD(0x22A0) = WORD(0x2294);
    WORD(0x22A4) = WORD(0x229C);
    WORD(0x2294) = action;
    WORD(0x2298) = 0;
    if (BYTE(0x22B5) == 1) BYTE(0x22B5) = 0;
    BYTE(0x22BC) = 0;
    if (BYTE(0x22B4) == 0) {
        *(s32 *)(PTR(0x2290) + 0x9C) = 0;
        BYTE(0x22BD) = 0;
        BYTE(0x22B7) = 0;
        BYTE(0x22C2) = 0;
        BYTE(0x22BF) = 0;
        HALF(0x2504) = 0;
        func_L00_00322EC8((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x18E0));
    }
    if (SHORT(0x1FA) == 0) func_L00_002D6940();
    func_PAL_L00_002AF2C8(WORD(0x22A0), WORD(0x2294));
    WORD(0x1188) = 0;
    switch (action) {
    case 0:
        WORD(0x229C) = 0;
        BITS(0x24A0) = 0;
        if (WORD(0x1248) == 0x1A) func_PAL_L00_002AF6C0();
        BYTE(0x24EF) = 0;
        WORD(0x11A0) = func_002A7820(42, 83);
        func_L00_002AB3E0();
        if (BYTE(0x22B4)) { func_L01_002C1988(0); return 1; }
        COPY_VECTOR(0x160, 0x120);
        if (BYTE(0x1492) && func_00282E20(VEC(0x160)) > 0.010000001f) { func_PAL_L04_002E7DA8(0x2E, 1); return 0; }
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { func_PAL_L04_002E7DA8(0x76, 1); return 0; }
        WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        if (func_L04_002CC748(0) == 0x51) func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 15.0f); else func_PAL_L00_002D2668(func_L04_002CC748(0), 0, -1.0f);
        goto finish;
    case 0x64:
        WORD(0x229C) = 0; BITS(0x24A0) = 0;
        func_00282C88((TI128 *)VEC(0x160)); WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        if (func_L04_002CC748(0) == 0x51) func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 15.0f); else func_PAL_L00_002D2668(func_L04_002CC748(0), 0, -1.0f);
        goto finish;
    case 0x3D:
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 7.0f);
        if (PTR(0x1854)) func_PAL_002A7E68(PTR(0x1854), 0, 0, 7);
        goto finish;
    case 0x39:
        WORD(0x229C) = 20; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x45, 0, 1e+01f); goto finish;
    case 0x7C:
        WORD(0x229C) = 20; HALF(0x1F0) = 10000; BITS(0x24A0) = 0;
        REAL(0x79C) = REAL(0x330) - 0.37f; WORD(0x24CC) = 0;
        REAL(0x794) = REAL(0x118) * 0.2f;
        if (REAL(0x794) < -0.14000002f) REAL(0x794) = -0.14000002f;
        BYTE(0x22B7) = 1; REAL(0x790) = REAL(0x88) - REAL(0x79C); BITS(0x7A0) = 0;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x6D, 0, 9.0f); goto finish;
    case 0x32: {
        s32 n;
        WORD(0x229C) = 17; BITS(0x24A0) = 11; BYTE(0x22B7) = 1; BITS(0xA3C) = 0;
        if (WORD(0x22A4) == 18) { func_L00_002B9B88(3, 0); WORD(0x2298) = 1; }
        else WORD(0xA34) = 37;
        WORD(0x1188) = 0x68; BITS(0xA20) = 0;
        n = 10;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x3B, 0, n); goto finish; }
    case 0x34: {
        s32 f;
        WORD(0x229C) = 17; BITS(0x24A0) = 11; BYTE(0x22B7) = 1; WORD(0xA34) = 50;
        if (WORD(0x22A4) == 18) { func_L00_002B9B88(3, 0); WORD(0x2298) = 1; }
        WORD(0x1188) = 0x68; BITS(0xA20) = 0;
        f = WORD(0x22A0) == 0x32 ? 12 : 9;
        if (animate) func_PAL_L00_002D2668(0x3D, 0, f);
        goto finish;
    }
    case 0x33:
        WORD(0x229C) = 17; BITS(0x24A0) = 11; BYTE(0x22B7) = 1;
        COPY_VECTOR(0x160, 0x120); WORD(0x1188) = 0x68;
        selected_8 = WORD(0x22A0) == 0x34 ? -2 : 29;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x3C, 0, (f32)selected_8); goto finish;
    case 0x36:
        WORD(0x229C) = 18; BYTE(0x22B7) = 1; BITS(0x24A0) = 0; HALF(0xA4A) = 0;
        if (WORD(0x22A4) == 17) {
            func_PAL_L00_002AAAC8(3, 10, 0);
            if (D_L04_001B2C70) func_002FD1B8(D_L04_001B2C70, D_L04_001B2C78, 0, REAL(0x80), REAL(0x84), 0.4f, 0.3f);
        } else if (REAL(0x118) < -0.010000001f) {
            selected_9 = func_00283CF0(func_00282C48(REAL(0x118)) * 300.0f);
            if (selected_9 > 40) selected_9 = 40;
            func_PAL_L00_002AAAC8(3, selected_9, 1);
            if (D_L04_001B2C70) func_002FD1B8(D_L04_001B2C70, D_L04_001B2C78, 0, REAL(0x80), REAL(0x84), 0.5f, -0.4f);
            HALF(0xA4A) = 62;
        }
        REAL(0x794) = REAL(0x118) * 0.37f; WORD(0x798) = 0;
        if (REAL(0x794) < -0.14000002f) REAL(0x794) = -0.14000002f;
        REAL(0x79C) = REAL(0x330); BITS(0x7A0) = 0;
        REAL(0x790) = (REAL(0x88) - REAL(0x330)) - -0.12f;
        COPY_VECTOR(0x160, 0x120); REAL(0x168) = 0;
        func_002AC9F8((f32 *)VEC(0x160), 0.11000001f);
        WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x3A, 0, 18.0f); goto finish;
    case 0x72: case 0x73:
        WORD(0x229C) = 7; BITS(0x24A0) = 0;
        func_L00_002B6118(0.5f); BYTE(0x22B7) = 1; COPY_VECTOR(0xF0, 0x110);
        hit_10 = func_002A9640(PTR(0x2290), 1, 0);
        if (hit_10) func_PAL_L00_002A4D58(func_00283CF0(*(f32 *)(hit_10 + 0x2C)));
        else func_PAL_L00_002A4D58(1);
        HALF(0x1DC) = 64;
        if (animate) {
            if (WORD(0x2294) == 0x72) func_PAL_L00_002D2668(0x69, 3, -3.0f);
            else func_PAL_L00_002D2668(0x68, 3, -3.0f);
            *(f32 *)(PTR(0x2290) + 0x44) = D_L04_00276A20[WORD(0xC30)][WORD(0xC34)++];
            goto finish;
        }
        goto finish;
    case 0x35:
        BITS(0x24A0) = 0; WORD(0x229C) = 18; BITS(0xA3C) = 0;
        BYTE(0x22B7) = 1; WORD(0x798) = 37; WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x5E, 0, 14.0f); goto finish;
    case 0x67:
        WORD(0x229C) = 20; BYTE(0x22B7) = 1; BITS(0x24A0) = 0;
        if (SHORT(0xA4E) > 42 && D_0018C750[12].count < 0xFFFF) D_0018C750[12].count++;
        if (D_0018C750[12].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C750[12].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C750[12].levels = (D_0018C750[12].levels | (1u << D_001A79F0)) | 0x80000000u;
        if (WORD(0xA50) > 2 && D_0018C750[29].count < 0xFFFF) D_0018C750[29].count++;
        if (D_0018C750[29].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C750[29].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C750[29].levels = (D_0018C750[29].levels | (1u << D_001A79F0)) | 0x80000000u;
        COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x58, 0, 8.0f); goto finish;
    case 0x7F:
        WORD(0x229C) = 20; BYTE(0x22B7) = 1; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x79, 0, 8.0f); goto finish;
    case 0x85:
        WORD(0x229C) = 32; BITS(0x24A0) = 8; BYTE(0x22B7) = 1; BYTE(0x22C2) = 1;
        if (animate) func_PAL_L00_002D2668(0x4F, 0, 4.0f);
        REAL(0x98) = *(f32 *)(PTR(0x1830) + 0xF8);
        *(TI128 *)VEC(0x80) = *(TI128 *)(PTR(0x1830) + 0x10);
        func_00282C88((TI128 *)VEC(0xF0)); goto finish;
    case 1:
        BITS(0x24A0) = 4;
        WORD(0x229C) = 0;
        if (BYTE(0x22BA)) goto finish;
        animation_16 = func_L04_002CC748(1);
        if (PTR(0x2290)[0x43] == animation_16 || !animate) goto finish;
        func_PAL_L00_002D2668(animation_16, 0, 15.0f); goto finish;
    case 0x2F:
        WORD(0x229C) = 8; BITS(0x24A0) = 0; COPY_VECTOR(0x160, 0x110);
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 4.0f); HALF(0x1EC) = 6;
        goto finish;
    case 2: case 0x70: case 0x2E:
        WORD(0x229C) = 1;
        BITS(0x24A0) = 0;
        if (WORD(0x22A4) != 4 && WORD(0x22B0) != 4) REAL(0x1B4) = func_L00_002D3A58((char *)VEC(0x120));
        COPY_VECTOR(0x3F0, 0);
        BITS(0x410) = 0;
        REAL(0x408) = REAL(0x98);
        if (REAL(0x1B4) > 0.14000002f) REAL(0x1B4) = 0.14000002f;
        BYTE(0x40F) = 0;
        func_L00_002B39F0(0, 1.0f);
        value_18 = func_00283C80(REAL(0x98), REAL(0x1A0));
        if (value_18 > 1.5707964897155762f &&
            (WORD(0x22A4) == 4 || WORD(0x22A0) == 3 || WORD(0x22AC) == 3)) REAL(0x1B4) = 0;
        WORD(0x1188) = 0x68;
        if (BYTE(0x149A)) {
            if (SHORT(0x34C) == 0 || REAL(0x31C) < 0.3f) { func_PAL_L04_002E7DA8(0x76, 1); return 0; }
        }
        if (BYTE(0x1492) || WORD(0x2294) == 0x2E) {
            if (REAL(0x1B4) > 0.15400001f) REAL(0x1B4) = 0.15400001f;
            BITS(0xF8) = 0;
            func_002AC9F8((f32 *)VEC(0xF0), 0.15400001f);
            WORD(0x2294) = 0x2E; BITS(0x404) = 0;
            func_PAL_L00_002D2668(0x37, 0, 7.0f); goto finish;
        }
        if (BYTE(0x22B9) || WORD(0x2294) == 0x70) {
            WORD(0x2294) = 0x70; func_PAL_L00_002D2668(0x59, 0, 7.0f); goto finish;
        }
        WORD(0x2298) = 0;
        BYTE(0x40C) = 0; BYTE(0x40E) = 0;
        if (!animate) goto finish;
        selected_18 = WORD(0x24CC) == 1 ? 10 : 7;
        if (WORD(0x22AC) == 0x22 || WORD(0x22A0) == 0x22) selected_18 = 12;
        if (WORD(0x22AC) == 0x83 || WORD(0x22A0) == 0x83) selected_18 = 12;
        if (WORD(0x22A0) == 0x13) selected_18 = 11;
        if (WORD(0x22AC) == 6 || WORD(0x22AC) == 0x2C) selected_18 = 15;
        if (WORD(0x22B0) == 4 && BYTE(0x49C) > 4) selected_18 = 11;
        func_PAL_L00_002D2668(WORD(0x2298) + 3, D_L04_001A7DD8[WORD(0x2298)], (f32)selected_18); goto finish;
    case 0x7B: {
        s32 n = -2;
        WORD(0x229C) = 28; WORD(0x1188) = 0x68; BITS(0x24A0) = 0;
        COPY_VECTOR(0xF0, 0x110);
        if (WORD(0x1298) != 0x36) { WORD(0x2304) = WORD(0x1298); WORD(0x22CC) = 0x36; }
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x8B, 0, n); goto finish; }
    case 0x62:
        WORD(0x229C) = 1; BITS(0x24A0) = 0; REAL(0x1B4) = func_00282E20(VEC(0x120));
        BYTE(0x22BC) = 1;
        if (!BYTE(0x22B4)) func_PAL_L00_002AF6C0();
        if (!animate) goto finish;
        if (BYTE(0x22B4) == 1) { func_PAL_L00_002D2668(2, 0, 7.0f); goto finish; }
        if (BYTE(0x22B4) != 0) goto finish;
        func_PAL_L00_002D2668(WORD(0x2298) + 3, D_L04_001A7DD8[WORD(0x2298)], 7.0f); goto finish;
    case 3:
        WORD(0x229C) = 1; BITS(0x24A0) = 0;
        COPY_VECTOR(0x160, 0x120);
        if (BYTE(0x1492)) { func_PAL_L04_002E7DA8(0x2E, 1); return 0; }
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { func_PAL_L04_002E7DA8(0x76, 1); return 0; }
        if (func_PAL_L00_002CB2C8()) return 0;
        if (func_L04_002CC748(0) == 0x51) {
            if (!animate) goto finish;
            if (func_PAL_L04_002E7DA8(0, 0)) func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 15.0f);
            return 0;
        }
        if (!animate) goto finish;
        animation_21 = objectSnapshot[0x42];
        {
            value_21 = REAL(0xC38); selected_21 = 6;
            if (func_L00_002A4EF0(animation_21) == 4 && value_21 > 3.0f && value_21 < 16.0f) selected_21 = 5;
            func_PAL_L00_002D2668(selected_21, 4, 7.0f);
            goto finish;
        }
    case 0x63:
        WORD(0x229C) = 1; BITS(0x24A0) = 0;
        REAL(0x1B4) = func_L00_002D3A58((char *)VEC(0x120)); COPY_VECTOR(0x160, 0x120);
        if (!animate) goto finish;
        animation_22 = objectSnapshot[0x42]; {
            value_22 = REAL(0xC38); selected_22 = 6;
            if (func_L00_002A4EF0(animation_22) == 4 && value_22 > 3.0f && value_22 < 16.0f) selected_22 = 5;
            func_PAL_L00_002D2668(selected_22, 4, 7.0f);
            goto finish;
        }
    case 4:
        WORD(0x229C) = 12; BITS(0x24A0) = 0;
        REAL(0x1B4) = func_00282E20(VEC(0x120));
        if (REAL(0x1B4) > 0.14000002f) REAL(0x1B4) = 0.14000002f;
        if (BYTE(0x149A) && SHORT(0x34C) == 0) { func_PAL_L04_002E7DA8(0x76, 1); return 0; }
        WORD(0x1188) = 0x68;
        COPY_VECTOR(0x160, 0x120);
        func_002AC9F8((float *)VEC(0x160), 0.14000002f);
        if (REAL(0x178) > 0.07000001f) func_L00_002B9B88(9, 0);
        if (animate) {
            if (PTR(0x2290)[0x42] == func_L04_002CC748(0)) func_PAL_L00_002D2668(13, 2, 7.0f);
            else func_PAL_L00_002D2668(13, 2, 12.0f);
            func_L00_002D2470(3, 18);
        }
        goto finish;
    case 0x8A:
        WORD(0x229C) = 33; BITS(0x24A0) = 0;
        if (D_0018C360[13].count < 0xFFFF) D_0018C360[13].count++;
        if (D_0018C360[13].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[13].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C360[13].levels = (D_0018C360[13].levels | (1u << D_001A79F0)) | 0x80000000u;
        REAL(0x1A0) = func_00283248(*(f32 *)(PTR(0xB10) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xB10) + 0x14) - REAL(0x84));
        BITS(0xB1C) = 0; { if (animate) { func_PAL_L00_002D2668(0x2F, 2, 4.0f); func_L00_002D2470(10, 14); } goto finish; }
    case 0x8B:
        WORD(0x229C) = 33; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        goto finish;
    case 0x23:
        WORD(0x229C) = 13; BITS(0x24A0) = 7;
        if (D_0018C360[13].count < 0xFFFF) D_0018C360[13].count++;
        if (D_0018C360[13].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[13].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C360[13].levels = (D_0018C360[13].levels | (1u << D_001A79F0)) | 0x80000000u;
        REAL(0x1A0) = func_00283248(*(f32 *)(PTR(0xAA4) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xAA4) + 0x14) - REAL(0x84));
        if (WORD(0x22A0) == 0x28) COPY_VECTOR(0x160, 0xF0);
        { if (animate) { func_PAL_L00_002D2668(0x2F, 2, 4.0f); func_L00_002D2470(10, 14); } goto finish; }
    case 0x24:
        WORD(0x229C) = 13; BITS(0x24A0) = 7; BITS(0xAA0) = 0;
        BITS(0xAB4) = 0; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x30, 1, 8.0f); goto finish;
    case 0x25:
        WORD(0x229C) = 13; BITS(0x24A0) = 7; BYTE(0x22BC) = 1;
        BITS(0xAA0) = 0; BITS(0xAB4) = 0;
        REAL(0xABC) = func_00282E48(VEC(0x80), PTR(0xAA4) + 0x10);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x30, 1, 4.0f); goto finish;
    case 0x2B:
        WORD(0x229C) = 14; BITS(0x24A0) = 7;
        if (D_0018C360[13].count < 0xFFFF) D_0018C360[13].count++;
        if (D_0018C360[13].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[13].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C360[13].levels = (D_0018C360[13].levels | (1u << D_001A79F0)) | 0x80000000u; HALF(0xAFE) = 1;
        BITS(0xAE8) = 0; BYTE(0x22BC) = 1; PTR(0xAD4) = PTR(0xAD0);
        HALF(0xADC) = 0; HALF(0xAFC) = 0; BITS(0xAF4) = 0; BITS(0xAF8) = 0;
        hit_29 = *(u8 **)(PTR(0xAD0) + 0x68);
        REAL(0xAE0) = *(f32 *)(hit_29 + 4);
        if (*(f32 *)(hit_29 + 0x10) == REAL(0xAE8)) *(f32 *)(hit_29 + 0x14) = *(f32 *)(hit_29 + 0xC);
        else *(f32 *)(hit_29 + 0x14) = *(f32 *)(hit_29 + 0x10);
        REAL(0xB04) = 0.036000002f; REAL(0xB08) = 0.47520003f; REAL(0xB0C) = 0.22000001f;
        func_00282C88((TI128 *)VEC(0xA0)); HALF(0x206) = 33;
        if (*(f32 *)(hit_29 + 0x24) != 0.0f) REAL(0xB04) = *(f32 *)(hit_29 + 0x24);
        if (*(f32 *)(hit_29 + 0x28) != 0.0f) REAL(0xB08) = *(f32 *)(hit_29 + 0x28);
        if (*(f32 *)(hit_29 + 0x2C) != 0.0f) REAL(0xB0C) = *(f32 *)(hit_29 + 0x2C);
        REAL(0xAEC) = func_00283248(*(f32 *)(PTR(0xAD4) + 0x10) - REAL(0x80),
                                    *(f32 *)(PTR(0xAD4) + 0x14) - REAL(0x84));
        REAL(0xAE4) = func_00282E48(VEC(0x80), PTR(0xAD4) + 0x10);
        REAL(0xAF0) = 0.0108f;
        if (WORD(0x22A4) == 4) REAL(0xAF0) = REAL(0x520);
        else if (WORD(0x22A4) == 2) REAL(0xAF0) = REAL(0xA80);
        if (animate) { func_PAL_L00_002D2668(0x34, 0, 9.0f); REAL(0xC20) = 0.7f; }
        goto finish;
    case 0x2C:
        WORD(0x229C) = 2; BITS(0x24A0) = 7;
        func_00282C88((TI128 *)VEC(0xA0)); COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(11, 0, 12.0f); goto finish;
    case 0x17:
        WORD(0x229C) = 3; BITS(0x24A0) = 13;
        REAL(0x57C) = 0.0088f; REAL(0x580) = REAL(0x88);
        if (WORD(0x22A4) == 4) { REAL(0x57C) = REAL(0x520); REAL(0x580) = REAL(0x490); }
        BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        if (REAL(0x174) > 0.07000001f) func_PAL_L00_002D2668(0x20, 0, 7.0f);
        else func_PAL_L00_002D2668(0x20, 1, 9.0f);
        goto finish;
    case 0x18:
        WORD(0x229C) = 3; BYTE(0x22BF) = 1; BITS(0x24A0) = 13;
        BYTE(0x22BC) = 1; WORD(0x1188) = 0x68;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x21, 0, 5.0f); goto finish;
    case 0x19:
        WORD(0x229C) = 3; BITS(0x24A0) = 13; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x24, 0, 5.0f); goto finish;
    case 0x1A:
        WORD(0x229C) = 3; BITS(0x24A0) = 13; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x25, 0, 5.0f); goto finish;
    case 0x76:
        WORD(0x229C) = 2; BITS(0x24A0) = 0; COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(11, 0, 1e+01f); goto finish;
    case 6: case 0x74:
        WORD(0x229C) = 2; BITS(0x24A0) = 0;
        if (WORD(0x2294) == 0x74) {
            WORD(0x229C) = 0x14;
            if (BYTE(0x22B4) == 1) {
                if (D_001A79F0 == 3) func_L00_0035F5A0(17, 0, (s32)PTR(0x2290));
                else if (D_001A79F0 == 14) func_L00_0035F5A0(21, 0, (s32)PTR(0x2290));
            }
        }
        REAL(0xA80) = 0.0088f;
        REAL(0xA84) = 0.0028000001f;
        if (WORD(0x2294) == 0x74) {
            if (!BYTE(0x22B4)) HALF(0x24D6) = func_L00_002B9B88(14, 0x20);
            REAL(0xA90) = func_002A78D8(0.062831864f, 0.08726648f);
            REAL(0xA94) = func_002A78D8(0.062831864f, 0.08726648f);
        }
        WORD(0x1188) = 0x68; WORD(0x2298) = 0;
        COPY_VECTOR(0xF0, 0x120);
        if (!animate) goto finish;
        if (REAL(0x31C) > 1.75f) { func_PAL_L00_002D2668(11, 0, 1e+01f); WORD(0x2298) = 1; goto finish; }
        func_PAL_L00_002D2668(10, 0, 8.0f); goto finish;
    case 0x82: {
        s32 n = -2;
        WORD(0x229C) = 30; BITS(0x24A0) = 0;
        if (WORD(0x22A0) != 0x16) {
            value_37 = REAL(0x5B8); REAL(0x5B0) = 50.0f;
            if (value_37 != 0.0f) { REAL(0x5B0) = value_37; REAL(0x5B8) = 0; }
        }
        BYTE(0x24EF) = 1; WORD(0x1188) = 0x68; WORD(0x7A8) = 0;
        HALF(0x5BE) = 0; WORD(0x5A8) = 0; WORD(0x5A4) = 0;
        COPY_VECTOR(0xF0, 0x110); HALF(0x5BC) = 6;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x13, 0, n); goto finish; }
    case 8: {
        s32 n = -2;
        WORD(0x229C) = 5; WORD(0x1188) = 0x68; BITS(0x24A0) = 0;
        if (REAL(0x170) > 0.09f) func_L00_002B6118(0.09f / REAL(0x170));
        WORD(0x24C8) = 0; COPY_VECTOR(0xF0, 0x110);
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x13, 0, n); goto finish; }
    case 7: case 9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF: case 0x10: case 0x11:
    case 0x12: case 0x1B: case 0x28: case 0x29: case 0x38: case 0x45: case 0x48: case 0x5B: case 0x66:
    case 0x6E: case 0x81: case 0x89: case 0x92:
        if (WORD(0x2294) != 0x81 && PTR(0x33C) &&
            (*(s16 *)(PTR(0x33C) + 0xAA) == 0x9B9 || *(s16 *)(PTR(0x33C) + 0xAA) == 0xF05)) {
            func_PAL_L04_002E7DA8(0x81, 1); return 0;
        }
        if (WORD(0x2294) != 0x6E && SHORT(0x348) == 1 && action != 0xE &&
            action != 0x38 && !D_L04_001A8FF4) { func_PAL_L04_002E7DA8(0x6E, 1); return 0; }
        if (WORD(0x22A0) == 0x11 && !BYTE(0x24DA)) BYTE(0x24DB)++;
        else BYTE(0x24DB) = 0;
        if (SHORT(0x1F2)) { func_PAL_L04_002E7DA8(0x82, 1); return 0; }
        if (SHORT(0x212)) {
            WORD(0x2294) = WORD(0x22A0); WORD(0x2298) = oldStep; WORD(0x1B8) = WORD(0x22A8);
            return 0;
        }
        WORD(0x229C) = 4;
        if ((u32)(action - 0x28) < 2) BITS(0x24A0) = 3; else BITS(0x24A0) = 0x50;
        if (WORD(0x2294) == 7 || WORD(0x2294) == 0xF || WORD(0x2294) == 0xD ||
            (WORD(0x2294) == 0xB && WORD(0x22A4) != 4)) {
            oldWeapon = BYTE(0x149D);
            func_PAL_L00_002A6058(oldWeapon, 0, 0, 30);
            func_PAL_L00_002A6058(oldWeapon, 1, 0, 30);
        }
        COPY_VECTOR(0xF0, 0x120);
        if (WORD(0x2294) != 0x12 && BYTE(0x1494) && REAL(0x88) < REAL(0x330) + 0.5f)
            func_PAL_L00_002AAAC8(3, 0x10, 0);
        {
        f32 c504, c514, c4A4;
        REAL(0x490) = REAL(0x88);
        REAL(0x520) = 0.011880001f;
        WORD(0x448) = -1;
        REAL(0x500) = 0.008f;
        c504 = 0.0044f;
        REAL(0x510) = 2.5f;
        HALF(0x528) = BYTE(0x1492);
        c514 = 0.5f;
        c4A4 = 0.119f;
        HALF(0x51A) = 67; REAL(0x494) = 0.30019668f;
        REAL(0x4A0) = 1.0000001f; BYTE(0x49E) = 0; BYTE(0x49C) = 0;
        BITS(0x4B0) = 0;
        BITS(0x4B4) = 0; BYTE(0x49D) = 0; REAL(0x504) = c504; HALF(0x524) = 0; BYTE(0x52C) = 0;
        BYTE(0x52E) = 0; BYTE(0x52F) = 0;
        HALF(0x52A) = 58; HALF(0x526) = 0; REAL(0x514) = c514; REAL(0x4A4) = c4A4;
        REAL(0x458) = 0.0f; BYTE(0x49F) = 0;
        BITS(0x594) = 0; HALF(0x24D8) = 0;
        }

        if (WORD(0x2294) == 7) {
            SHORT(0x4AC) = 4; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x50C) = 2.3f; REAL(0x4A8) = 1.28f; REAL(0x508) = 1.28f; BYTE(0x52C) = 1; BYTE(0x52E) = 1; HALF(0x518) = 12; BYTE(0x52F) = 1; REAL(0x458) = 0.013899601f;

        }
        else if (WORD(0x2294) == 0x81) {
            SHORT(0x4AC) = 4; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x4A8) = D_L04_001A7CD8; REAL(0x50C) = D_L04_001A7CD8 + 0.5f; REAL(0x508) = D_L04_001A7CD8; HALF(0x518) = 12; HALF(0x51A) = 333; REAL(0x510) = 300.0f; REAL(0x520) = D_L04_001A7CDC * 0.00040000002f; HALF(0x526) = 1000; HALF(0x52A) = 1000; REAL(0x4A4) = 0.14000002f;
            if (D_001A79F0 == 16) REAL(0x4A4) = 0.0f;
            func_L00_00322A98(PTR(0x2290), (char *)VEC(0x18E0));
            func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 70, 2, 0.0f);
            func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 35, 4, 0.0f);
            func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 17, 6, 0.0f);

        }
        else if (WORD(0x2294) == 0x12) {
            f32 frames18;
            SHORT(0x4AC) = 2; REAL(0x4B8) = 0.6f; REAL(0x4A8) = 0.1f; frames18 = 18.0f; REAL(0x4C8) = frames18; REAL(0x4CC) = 28.0f; REAL(0x4D0) = 14.0f; REAL(0x50C) = 0.2f; REAL(0x508) = 0.1f; HALF(0x518) = 8;
            if (REAL(0x24C4) < 1.25f) {
                SHORT(0x4AC) = 12; REAL(0x50C) = 1.98f;
                REAL(0x508) = 1.95f; REAL(0x4A8) = 1.95f;
            } else {
                f32 step = REAL(0x4B0);
                func_L00_002D3B58((V4_F6a70b950 *)VEC(0xF0), (V4_F6a70b950 *)VEC(0xF0), step);
                BYTE(0x49D) = 1; WORD(0x430) = 2;
                WORD(0x434) = 0x1F; REAL(0x438) = step; REAL(0x43C) = frames18;
                BITS(0x440) = 0x21; PTR(0x444) = D_L04_00276BB0;
            }
            BYTE(0x49F) = 1; BYTE(0x22B7) = 1;
        }
        else if (WORD(0x2294) == 9) {
            SHORT(0x4AC) = 4; REAL(0x4B8) = 0.6f; REAL(0x4A8) = 1.0f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 11.0f; REAL(0x50C) = 2.7f; REAL(0x508) = 1.0f; HALF(0x518) = 12; REAL(0x4A4) = 0.119f; BYTE(0x52C) = 1; BYTE(0x52E) = 1; BYTE(0x52F) = 1;

        }
        else if (WORD(0x2294) == 0x6E) {
            REAL(0x4A8) = 2.7f; SHORT(0x4AC) = 4; BYTE(0x52C) = 1; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f; REAL(0x4CC) = 30.0f; REAL(0x4D0) = 12.0f; REAL(0x50C) = 2.75f; REAL(0x508) = 2.7f; HALF(0x518) = 4; BYTE(0x49F) = 1; BYTE(0x52E) = 0; BYTE(0x52F) = 0; REAL(0x4A4) = 0.13923f;

        }
        else if (WORD(0x2294) == 10) {
            REAL(0x4A8) = 1.9f; SHORT(0x4AC) = 4; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 18.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 1e+01f;
            REAL(0x50C) = 1.95f; REAL(0x508) = 1.9f; HALF(0x518) = 12;
            REAL(0x520) = 0.0044f; BYTE(0x52E) = 1;
            HALF(0x51A) = 100; HALF(0x52A) = 75; HALF(0x526) = 58;

        }
        else if (WORD(0x2294) == 0x10) {
            REAL(0x4C8) = 18.0f; SHORT(0x4AC) = 4; REAL(0x4B8) = 0.8f;
            REAL(0x4CC) = 30.0f; REAL(0x4D0) = 11.0f; REAL(0x4A8) = 1.5f;
            REAL(0x50C) = 1.55f; REAL(0x508) = 1.5f; HALF(0x518) = 1;
            func_L00_002D6900(20);
            REAL(0x50C) = 0.9f; REAL(0x4A8) = 0.4f; REAL(0x508) = 0.4f;
            if (REAL(0x184) < 0.40000004f) {
                func_L00_00322A98(PTR(0x2290), (char *)VEC(0x18E0));
                func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 40, 2, 0.0f);
                func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 20, 4, 0.0f);
                func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 10, 6, 0.0f);
            }
            BYTE(0x52E) = 1; REAL(0x454) = 0.23000002f;
            if (REAL(0x31C) > 1.4f) REAL(0x454) = 0.11400001f;
            REAL(0x520) = 0.0034000003f; REAL(0x500) = 0.0176f; REAL(0x504) = 0.020000001f;

        }
        else if (WORD(0x2294) == 0x1B) {
            SHORT(0x4AC) = 8; REAL(0x4A8) = 2.0f; REAL(0x4B8) = 0.85f;
            REAL(0x4C8) = 20.0f; REAL(0x4CC) = 29.0f; REAL(0x4D0) = 19.0f;
            REAL(0x50C) = 2.05f; REAL(0x508) = 2.0f; REAL(0x514) = 1.0f;
            REAL(0x520) = 0.010000001f; HALF(0x518) = 1; BITS(0x4BC) = 0;
            BYTE(0x49F) = 1; BYTE(0x22BF) = 1; BYTE(0x22BC) = 1; BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0x11) {
            SHORT(0x4AC) = 7; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 12.0f; REAL(0x4CC) = 20.0f; REAL(0x4D0) = 1e+01f; HALF(0x518) = 10;
            if (BYTE(0x24DA)) { REAL(0x498) = 0.09800001f; REAL(0x50C) = 3.35f; REAL(0x508) = 3.3f; }
            else { REAL(0x498) = 0.034f; REAL(0x50C) = 1.85f; REAL(0x508) = 1.8f; }
            BYTE(0x49F) = 1; REAL(0x4A8) = REAL(0x508); func_L00_002D6900(27);
            HALF(0x52A) = 67; REAL(0x520) = 0.011600001f;
            COPY_VECTOR(0x4F0, 0x4E0); HALF(0x24D8) = 1; BYTE(0x22B7) = 1; BYTE(0x52C) = 1;

        }
        else if (WORD(0x2294) == 0xD) {
            REAL(0x4A8) = 4.0f; REAL(0x4C8) = 26.0f; SHORT(0x4AC) = 7;
            REAL(0x4CC) = 38.0f; REAL(0x4D0) = 18.0f; REAL(0x50C) = 4.07f;
            REAL(0x4B8) = 0.6f; REAL(0x508) = 4.0f; HALF(0x518) = 12;
            func_L00_002D6900(20); REAL(0x510) = 4.5f; HALF(0x51A) = 100;
            REAL(0x4A4) = 0.038000003f; HALF(0x526) = 31;
            if (REAL(0x184) < 0.40000004f) {
                func_L00_00322A98(PTR(0x2290), (char *)VEC(0x18E0));
                func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 40, 3, 0.0f);
                func_L00_00322AC0((List_F66766f2b *)VEC(0x18E0), 20, 5, 0.0f);
            }
            BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0xF) {
            REAL(0x4A8) = 1.65f; SHORT(0x4AC) = 7;
            REAL(0x4B8) = 0.6f; REAL(0x4C8) = 5e+01f; REAL(0x4CC) = 64.0f;
            REAL(0x4D0) = 28.0f; REAL(0x50C) = 1.7f; REAL(0x508) = 1.65f;
            HALF(0x518) = 4; REAL(0x510) = 4.5f; HALF(0x51A) = 108;
            REAL(0x4A4) = 0.06600001f; HALF(0x526) = 71; HALF(0x1D0) = 58; BYTE(0x49D) = 1;
            if (D_001A7B90) WORD(0x430) = 28; else WORD(0x430) = 29;
            WORD(0x434) = WORD(0x430) + 30; REAL(0x438) = 29.0f;
            REAL(0x43C) = 5e+01f; BITS(0x440) = 72; PTR(0x444) = (u8 *)D_L04_001A7E00;
            BYTE(0x52E) = 1;

        }
        else if (WORD(0x2294) == 0xE) {
            f32 run = 0.7f;
            if (REAL(0x31C) < 2.0f) run = (2.5f - REAL(0x31C)) * 0.5f + 0.7f;
            SHORT(0x4AC) = -1; REAL(0x4B8) = 0.6f;
            REAL(0x4C8) = 32.0f; REAL(0x4CC) = 43.0f; REAL(0x4D0) = 19.0f; REAL(0x4A8) = run;
            REAL(0x50C) = run + 0.05f; REAL(0x508) = run;
            HALF(0x518) = 12; REAL(0x514) = 1.0f; REAL(0x4A4) = 0.095000006f; HALF(0x526) = 25;

        }
        else if (WORD(0x2294) == 0xB) {
            SHORT(0x4AC) = 4; REAL(0x4B8) = 0.6f; REAL(0x4C8) = 18.0f;
            REAL(0x4A8) = 3.2f; REAL(0x4CC) = 31.0f; REAL(0x4D0) = 24.0f;
            REAL(0x50C) = 3.25f; REAL(0x508) = 3.2f; HALF(0x518) = 12;
            REAL(0x510) = 4.5f; HALF(0x52A) = 42; REAL(0x514) = 1.0f; BYTE(0x49F) = 1;
            REAL(0x4C4) = func_L00_002AE070(8); COPY_VECTOR(0x480, 0);
            WORD(0x4D4) = func_L00_002C3A78(); REAL(0x4C0) = REAL(0x1A0); COPY_VECTOR(0x470, 0x190);
            if (REAL(0x174) > 0.030000001f) REAL(0x4D8) = REAL(0x174); else REAL(0x4D8) = 0.0f;
            REAL(0x4DC) = 0.0f; BYTE(0x52C) = 1;
            if (SHORT(0x1454) && REAL(0x24B8) > 0.3f) {
                REAL(0x4C0) = REAL(0x1459); COPY_VECTOR(0x470, 0x1440);
                BYTE(0x52D) = 1; REAL(0x4DC) = 0.10000001f;
            } else BYTE(0x52D) = 0;
            BYTE(0x52E) = 1;

        }
        if (REAL(0x510) == 0.0f) REAL(0x510) = REAL(0x4A8) * 1.5f;
        if (!animate) goto finish;
        if (WORD(0x2294) == 7) { func_PAL_L00_002D2668(7, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0x6E) { func_PAL_L00_002D2668(7, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0x81) { func_PAL_L00_002D2668(7, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0x12) { func_PAL_L00_002D2668(0x6B, 1, -1.0f); goto finish; }
        else if (WORD(0x2294) == 9) {
            animation_41 = 8; index = func_00283CF0(REAL(0xC38));
            if (func_L00_002A4EF0(objectSnapshot[0x42]) == 4) animation_41 = D_L04_001A7DE0[index];
            func_PAL_L00_002D2668(animation_41, 0, 4.0f); goto finish;
        }
        else if (WORD(0x2294) == 10) { func_PAL_L00_002D2668(18, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0x10) {
            if (WORD(0x22A4) == 4 || (WORD(0x22A0) == 4 && WORD(0x1B8) < 6)) {
                func_PAL_L00_002D2668(0x26, 0, 7.0f); SHORT(0x4AC) += 2; goto finish;
            }
            func_PAL_L00_002D2668(0x26, 0, 4.0f); goto finish;
        } else if (WORD(0x2294) == 0x1B) { func_PAL_L00_002D2668(0x22, 0, 3.0f); goto finish; }
        else if (WORD(0x2294) == 0x89) { func_PAL_L00_002D2668(0x7D, 11, 7.0f); goto finish; }
        else if (WORD(0x2294) == 0x11) { frames = 6.0f; animation_41 = 0x23; { func_PAL_L00_002D2668(animation_41, 2, frames); goto finish; } }
        else if (WORD(0x2294) == 0xD) { func_PAL_L00_002D2668(17, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0xE) { func_PAL_L00_002D2668(0x16, 3, 6.0f); REAL(0xC20) = 0.96000004f; goto finish; }
        else if (WORD(0x2294) == 0xF) { func_PAL_L00_002D2668(21, 0, 4.0f); goto finish; }
        else if (WORD(0x2294) == 0xB) {
            s32 anim = WORD(0x4D4) + 28;
            if (D_001A7A40[5]) { if (anim == 28) anim = 29; else if (anim == 29) anim = 28; }
            if (WORD(0x22A4) == 4) { func_PAL_L00_002D2668(anim, 1, 3.0f); SHORT(0x4AC) = 1; goto finish; }
            func_PAL_L00_002D2668(anim, 0, 4.0f); goto finish;
        }
        goto finish;
    case 0x13: case 0x14: case 0x15: case 0x1F: case 0x22: case 0x4D: case 0x83: case 0x93:
        WORD(0x229C) = 6;
        if (WORD(0x1500) && (u32)(WORD(0x2294) - 0x13) < 3) {
            if (D_0018C750[1].count < 0xFFFF) D_0018C750[1].count++;
            if (D_0018C750[1].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C750[1].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C750[1].levels = (D_0018C750[1].levels | (1u << D_001A79F0)) | 0x80000000u;
            if (D_0018C360[56].count < 0xFFFF) D_0018C360[56].count++;
            if (D_0018C360[56].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[56].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C360[56].levels = (D_0018C360[56].levels | (1u << D_001A79F0)) | 0x80000000u;
            func_PAL_L00_002BA480(); WORD(0x2294) = WORD(0x22A0); WORD(0x229C) = WORD(0x22A4);
            goto finish;
        }
        if (action != 0x83) BITS(0x24A0) = 0;
        REAL(0xBF4) = 1.0f; WORD(0xBE8) = 0; BITS(0xBE4) = 0; HALF(0xBFE) = 0;
        switch (WORD(0x2294)) {
        case 0x14:
            if (D_0018C750[0].count < 0xFFFF) D_0018C750[0].count++;
            if (D_0018C750[0].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C750[0].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C750[0].levels = (D_0018C750[0].levels | (1u << D_001A79F0)) | 0x80000000u;
            BITS(0x24A0) = 0x50; SHORT(0xBFC) = 4; WORD(0x2300) = 0;
            func_L00_002B75A0(8.0f, 1.047197699546814f, -1.0f); BITS(0xC00) = 0;
            if (animate) {
                selected_14 = WORD(0x22A0) == 11 && WORD(0x22A8) < 35 ? 14 : 9;
                func_PAL_L00_002D2668(0x2B, 4, (f32)selected_14);
                animation_14 = func_L00_002ADE68(0);
                if (func_L00_002B3248((u8 *)animation_14)) func_PAL_002A7E68((u8 *)animation_14, 10, 4, selected_14 + 2);
            }
            goto finish;
        case 0x15:
            if (D_0018C750[1].count < 0xFFFF) D_0018C750[1].count++;
            if (D_0018C750[1].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C750[1].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C750[1].levels = (D_0018C750[1].levels | (1u << D_001A79F0)) | 0x80000000u;
            if (D_0018C360[56].count < 0xFFFF) D_0018C360[56].count++;
            if (D_0018C360[56].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[56].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C360[56].levels = (D_0018C360[56].levels | (1u << D_001A79F0)) | 0x80000000u;
            SHORT(0xBFC) = 3; WORD(0x2300) = 0;
            func_L00_002B75A0(14.0f, 0.523598849773407f, -1.0f);
            BITS(0xC0C) = BITS(0xC0C) == 0;
            if (animate) {
                selected_15 = PTR(0x2290)[0x43] == 0x1A ? 2 : 8;
                if (WORD(0x22A0) == 1) selected_15 = 14;
                func_PAL_L00_002D2668(0x1A, 0, (f32)selected_15); func_L00_002D2470(6, 21);
            }
            goto finish;
        case 0x83:
            SHORT(0xBFC) = 3;
            func_L00_0041E958(64.0f, 0.174532949924469f, 0.349065899848938f);
            if (animate) {
                selected_83 = PTR(0x2290)[0x43] == 0x1A ? 2 : 8;
                if (WORD(0x22A0) == 1) selected_83 = 14;
                func_PAL_L00_002D2668(0x1A, 0, (f32)selected_83);
            }
            goto finish;
        case 0x1F:
            if (WORD(0x1220)) {
                func_L00_002D6900(19);
                if (animate) {
                    func_PAL_L00_002D2668(0x60, 4, -1.0f);
                    func_PAL_002A7E68(PTR(0x1220), 3, 4, -1);
                }
                func_L00_002B75A0(11.0f, 0.8726646900177002f, -1.0f);
            }
            goto finish;
        case 0x13:
        if (D_0018C360[10].count < 0xFFFF) D_0018C360[10].count++;
        if (D_0018C360[10].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[10].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        D_0018C360[10].levels = (D_0018C360[10].levels | (1u << D_001A79F0)) | 0x80000000u;
        {
        s32 *entry = D_L04_00276890[SHORT(0xBFC)];
        mode = 0; WORD(0x2300) = 0;
        if ((WORD(0x22A0) == 0x13 && (f32)entry[2] > REAL(0xC38)) ||
            (WORD(0x22AC) == 0x13 && WORD(0x1B8) + WORD(0x22A8) < 22)) mode = (entry[1] + 1) % 3;
        }
        SHORT(0xBFC) = mode;
        func_L00_002B75A0(5.0f, 0.785398244857788f, 0.785398244857788f);
        if (animate) {
            current = 0;
            if (mode == 0) selected_13 = 4;
            else if (mode == 1) { current = 2; selected_13 = 6; }
            else { current = 4; selected_13 = 6; }
            if (WORD(0xBE8) && mode < 2) {
                if (BYTE(0x22C3)) angle_13 = func_L00_002B9B38(VEC(0xBC0), 0);
                else angle_13 = func_00283C80(REAL(0xBEC), REAL(0x98));
                selected_13 += func_00283CF0(angle_13 * 1.5f);
            }
            current /= 2;
            func_PAL_L00_002D2668(mode + 0x17, current, (f32)selected_13);
            animation_13 = func_L00_002ADE68(0);
            if (func_L00_002B3248((u8 *)animation_13)) func_PAL_002A7E68((u8 *)animation_13, mode + 3, current, selected_13);
        }
        goto finish;
        case 0x22:
            if (animate) func_PAL_L00_002D2668(0x2C, 7, 7.0f);
            if (WORD(0x1248) == 12 && PTR(0xBE0)) {
                WORD(0xBE8) = 1;
                REAL(0xBEC) = func_00283248(*(f32 *)(PTR(0xBE0) + 0x10) - REAL(0x80),
                                            *(f32 *)(PTR(0xBE0) + 0x14) - REAL(0x84));
                func_00282CF0(VEC(0xBC0), PTR(0xBE0) + 0x10, VEC(0x80));
            }
            goto finish;
        }
        goto finish;
    case 0x77:
        WORD(0x229C) = 10; BITS(0x24A0) = 0;
        REAL(0xBF0) = func_00283B98(REAL(0x98), 3.14159297943f);
        func_00282D30(VEC(0xBD0), VEC(0), -1.0f); REAL(0x1B4) = 0.18f;
        if (!animate) goto finish;
        frames = 7.0f; animation_43 = 0x29; { func_PAL_L00_002D2668(animation_43, 5, frames); goto finish; }
    case 0x16:
        WORD(0x229C) = 7; BITS(0x24A0) = 0;
        func_L00_002B6118(0.5f); func_L00_002D6900(18); HALF(0x20E) = 37;
        COPY_VECTOR(0xF0, 0x120); func_002AC9F8((f32 *)VEC(0xF0), 0.14000002f);
        hit_44 = func_002A9640(PTR(0x2290), 1, 0);
        if (hit_44) func_PAL_L00_002A4D58(func_00283CF0(*(f32 *)(hit_44 + 0x2C)));
        else func_PAL_L00_002A4D58(1);
        HALF(0x1DC) = 64;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x10, 3, -3.0f);
        *(f32 *)(PTR(0x2290) + 0x44) = D_L04_00276A20[WORD(0xC30)][WORD(0xC34)++];
        goto finish;
    case 0x8C:
        WORD(0x229C) = 7; BITS(0x24A0) = 0; func_L00_002B6118(0.5f);
        BYTE(0x22BC) = 1; func_L00_002D6900(18);
        hit_45 = func_002A9640(PTR(0x2290), 8, 0);
        if (hit_45) func_PAL_L00_002A4D58(func_00283CF0(*(f32 *)(hit_45 + 0x2C)));
        else func_PAL_L00_002A4D58(1);
        HALF(0x1DC) = 64;
        if (!animate) goto finish;
        func_PAL_L00_002D2668(0x96, 1, -3.0f);
        *(f32 *)(PTR(0x2290) + 0x44) = D_L04_00276A20[WORD(0xC30)][WORD(0xC34)++];
        goto finish;
    case 0x3E:
        WORD(0x229C) = 15; BITS(0x24A0) = 0;
        if (!WORD(0x640)) {
            if (PTR(0x6C4)) { func_PAL_L00_002A4D58(func_00283CF0(*(f32 *)(PTR(0x6C4) + 0x2C))); PTR(0x6C4) = 0; }
            else func_PAL_L00_002A4D58(1);
        }
        func_L00_002B9B88(20, 0);
        if (WORD(0x24CC) < 1) {
            angle_53 = func_00283B98(func_00283248(REAL(0xF0), REAL(0xF4)), 3.14159297943f);
            angle_53 = func_00283B98(angle_53, func_002A78D8(0.523598849774f, 0.610865294933f));
            REAL(0x120) = func_00283180(angle_53) * REAL(0x644) * 0.7f;
            REAL(0x124) = func_00283198(angle_53) * REAL(0x644) * 0.7f; REAL(0x128) = 0.09f;
            if (WORD(0x640) > 12 && WORD(0x24CC) < 2) WORD(0x24CC) = 2;
            PTR(0x2290)[0xA8] = 255; func_PAL_L04_002E7DA8(0x16, 1); HALF(0x1F4) = 125; HALF(0x1D0) = 58;
            return 0;
        }
        HALF(0x1DC) = 64; REAL(0x69C) = 0.050000004f;
        if (REAL(0x680) > 0.050000004f) REAL(0x680) = 0.050000004f;
        BITS(0x674) = 0; func_00282C88((TI128 *)VEC(0xF0)); func_00282C88((TI128 *)VEC(0x110));
        REAL(0x128) = REAL(0xF8) = 0.22000001f;
        if (!animate) goto finish;
        frames = -3.0f; animation_53 = 16; { func_PAL_L00_002D2668(animation_53, 2, frames); goto finish; }
    case 0x1C:
        WORD(0x229C) = 9; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 8.0f); goto finish;
    case 0x1D:
        BITS(0x24A0) = 0x51; WORD(0x229C) = 0;
        if (func_L00_002A4EF0(PTR(0x2290)[0x42]) == func_L04_002CC748(0)) goto finish;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 4.0f); goto finish;
    case 0x1E:
        WORD(0x229C) = 9; BITS(0x24A0) = 0;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 8.0f); goto finish;
    case 0x6F:
        WORD(0x229C) = 9; BYTE(0x22BC) = 1; BITS(0x24A0) = 0;
        func_PAL_L00_002AF6C0();
        if (!animate) goto finish;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 8.0f); goto finish;
    case 0x26:
        WORD(0x229C) = 8; BITS(0x24A0) = 0;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, 8.0f); goto finish;
    case 0x31:
        WORD(0x229C) = 9; BITS(0x24A0) = 0; BYTE(0x22B7) = 1;
        BYTE(0x22BD) = 1; BYTE(0x22BC) = 1; func_L00_00322EC8((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x1A30));
        if (!animate) goto finish;
        func_PAL_L00_002D2668(func_L04_002CC748(0), 0, -1.0f); goto finish;
    case 0x75:
        WORD(0x229C) = 9; BITS(0x24A0) = 0; BYTE(0x22B7) = 1; BYTE(0x22BC) = 1;
        func_00282C88((TI128 *)VEC(0xF0));
        if (!animate) goto finish;
        func_PAL_L00_002D2668(11, 0, -1.0f); goto finish;
    case 0x60: case 0x61:
        WORD(0x229C) = 24; BYTE(0x22BC) = 1;
        func_L00_00322EC8((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)VEC(0x1A30)); func_PAL_L00_002AF6C0();
        if (animate) func_PAL_L00_002D2668(func_L04_002CC748(0), 0, -1.0f);
        goto finish;
    default:
        goto finish;
    }
finish:
    if (wasGliding && !BYTE(0x22B7)) BITS(0x231C) = 1;
    if (SHORT(0x348) == 0 && WORD(0x1298) == 0x13 && WORD(0x2304)) BITS(0x2320) = 1;
    if ((u32)(WORD(0x229C) - 13) > 2 && (WORD(0x2294) != 6 || WORD(0x22A0) != 0x24) &&
        WORD(0x1298) == 20 && WORD(0x2304)) BITS(0x2320) = 1;
    if (WORD(0x229C) == 20) { func_PAL_L00_002AF6C0(); BYTE(0x22BC) = 1; }
    if ((!func_L00_002ADF80() || WORD(0x229C) == 18) &&
        (REAL(0x330) < D_L04_001B9540.f148 || WORD(0x229C) == 0)) D_L04_001B9540.i400 = 0;
    if (WORD(0x229C) != WORD(0x22A4)) func_L00_002A6708();
    WORD(0x1B8) = 0;
    BITS(0x1C0) = 0;
    if (WORD(0x229C) != WORD(0x22A4)) BITS(0x1BC) = 0;
    BITS(0x1C4) = 0;
    return 1;
}
