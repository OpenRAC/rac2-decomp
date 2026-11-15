#include "common.h"

/* Opens the vendor menu (RAC1 open_vendor_menu). It calls the boot-only
   func_002F9778, so it has a unit of its own and the call stays extern. */

typedef struct { int id, kind; char pad[0x10]; } ShopSlot_002F8178;
typedef struct {
    int state, unused4, field8, fieldC;
    int base10, base14, unused18, base1C;
    char pad20[8];
    char *moby;
    char pad2C[0xC];
    int field38;
    char pad3C[8];
    int field44;
    int unused48, field4C, mode;
    char pad54[0xC];
    int restore, field64, field68, field6C;
    char pad70[8];
    int field78, field7C, index, field84, field88, field8C;
    char pad90[0x10];
    int fieldA0, fieldA4;
    char padA8[0xC];
    int fieldB4, fieldB8;
    float fieldBC;
    char padC0[0x10];
    float position[4], rotation[4];
    char padF0[0x50];
    ShopSlot_002F8178 slots[64];
    int count, field744;
    char pad748[0x18];
} Shop_002F8178;
extern Shop_002F8178 D_0021F240;
typedef struct { char pad[0xC]; int baseC, base10; } Resources_002F8178;
extern Resources_002F8178 D_001BAEC0;
typedef struct { char pad[0x20]; short level; } Settings_002F8178;
extern Settings_002F8178 D_001A79F8 MACRO_ADDR;
typedef struct {
    char pad[0x1248];
    int mode;
    char pad124C[0x1069];
    char flag22B5;
    char pad22B6[6];
    char flag22BC;
} Hero_002F8178;
extern Hero_002F8178 D_00189E20;
extern char D_001B5340[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern unsigned char D_001A7BB1;
extern int D_001A7B90;
extern int D_001A7AF0 MACRO_ADDR;
extern int D_001AD1C0;
extern int D_001AD1C4 __attribute__((sda)), D_001AD230 __attribute__((sda));
extern char D_001AD1E0[] SDATA(D_001AD1E0), D_001AD1F0[] SDATA(D_001AD1F0);
extern char D_001AD210[] SDATA(D_001AD210), D_001AD220[] SDATA(D_001AD220);
extern float D_001AD234 SDATA(D_001AD234), D_001AD238 SDATA(D_001AD238);
extern float D_001B2280, D_001B15A0;
extern int D_001B15A4;
extern int D_001B2238, D_001B2244, D_001B2248;
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001A8BB0;
extern struct { int w, h; } D_001A7340;
extern char D_00152CE4[], D_001C2AC0[];
extern void func_00282A60(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_002A0F48(void *);
extern void func_002F9778(void);
extern void func_002F6608(int);
extern void func_002F71B8(void);
extern void func_002F73A8(void);
extern void func_002F7738(void);
extern void func_00132AF8(int);
extern void func_002B72E8(int);
extern void func_00132028(void);
extern void func_0028E408(void);
extern void func_0029B698(int);
extern void func_0029B6D0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00288EA0(void);
extern unsigned int func_0026F748(int, int);
extern void func_0026F720(void);
extern void func_00283098(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_00335438(void *, void *, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_00272368(void);

/* Opens the vendor screen: clears its state, picks the menu type from the vendor or how it was called, builds the item list, and moves the camera to the vendor. */
void func_002F8178(char *moby)
{
    int openArg, npcAction, visible, count;
    float tempVec[4];

    ClearMemory(&gVendorMenuState, 0, 0x760);
    if (gIsPalVideo) D_001B2280 = 1.076923f;
    else D_001B2280 = 1.0f;
    gVendorMenuState.restore = 0;
    D_001AD1C0 = gPlayerBolts.level;
    openArg = (int)moby;
    if ((unsigned)moby < 4) {
        gVendorMenuState.restore = 1;
        moby = CreateMoby(11 /* Megacorp Vendor */);
        *(short *)(moby + 0x32) = 64;
        if (D_001A7BB1) qcopy(tempVec, D_001AD1F0);
        else qcopy(tempVec, D_001AD1E0);
        tempVec[2] = -tempVec[2];
        FastVecAdd(moby + 0x10, gCameraState_001B5340, tempVec);
        ClearVector128(moby + 0xF0);
        *(float *)(moby + 0xF8) = 3.1415927f;
        func_002A0F48(moby);
        gVendorMenuState.restore = 1;
        gVendorMenuState.field744 = 0;
        moby[0x20] = 3;
        if (openArg == 0) {
            gVendorMenuState.field744 = 0;
            gVendorMenuState.mode = 0;
        } else if (openArg == 1) {
            gVendorMenuState.mode = 1;
        } else if (openArg == 2) {
            gVendorMenuState.mode = 2;
            gVendorMenuState.fieldBC = -1.5707964f;
            gVendorMenuState.fieldB4 = 0;
            gVendorMenuState.fieldB8 = 0;
            gVendorMenuState.fieldA4 = 0;
        } else {
            gVendorMenuState.mode = 3;
        }
    } else if (*(short *)(moby + 0xAA) == 11 /* Megacorp Vendor */) {
        gVendorMenuState.field744 = 0;
        npcAction = *(int *)(*(char **)(moby + 0x68) + 0x94);
        if (npcAction == 0) {
            gVendorMenuState.mode = 0;
        } else if (npcAction == 1) {
            gVendorMenuState.mode = 1;
            RunShopMenuInput();
        } else if (npcAction == 4) {
            gVendorMenuState.mode = 2;
        } else if (npcAction == 2) {
            gVendorMenuState.mode = 3;
        } else if (npcAction == 3) {
            gVendorMenuState.field744 = 1;
            gVendorMenuState.mode = 0;
        }
    } else if (*(short *)(moby + 0xAA) == 0x1309 /* moby class 4873 */) {
        gVendorMenuState.moby = moby;
        gVendorMenuState.mode = 2;
    } else if (*(short *)(moby + 0xAA) == 0xDDC /* Slim Cognito Button */) {
        gVendorMenuState.moby = moby;
        gVendorMenuState.mode = 1;
        RunShopMenuInput();
    }
    if (D_001AD1C4 != -1) gVendorMenuState.mode = D_001AD1C4;
    gVendorMenuState.field88 = 0;
    gVendorMenuState.field8C = 0;
    gVendorMenuState.field38 = 0;
    gVendorMenuState.field44 = D_001A7BB4[0] - 1;
    if (gVendorMenuState.field44 < 0) gVendorMenuState.field44 = 0;
    gVendorMenuState.field78 = -1;
    gVendorMenuState.field7C = -1;
    gVendorMenuState.field64 = 0;
    gVendorMenuState.index = 0;
    D_001B2244 = 0;
    gVendorMenuState.field84 = 0;
    gVendorMenuState.field68 = -1;
    D_001AD234 = 0.8f;
    D_001AD238 = 1.0f;
    D_001B2290 = 96;
    D_001B2248 = 0;
    D_001B2238 = 0;
    D_001B2294 = 96;
    D_001AD230 = 0;
    D_001B2284 = 0;
    D_001B2288 = 0;
    D_001B2298 = 85;
    D_001B228C = 0;
    SendSoundCommand22(93);
    music_Pause(0);
    snd_Pump();
    if (gVendorMenuState.mode == 0) BuildVendorWeaponList(0);
    else if (gVendorMenuState.mode == 3) RebuildUnlockedSlotList();
    else if (gVendorMenuState.mode == 1) BuildShopChannelList();
    else if (gVendorMenuState.mode == 2) BuildFlagGatedVendorList();
    count = gVendorMenuState.count;
    visible = count / 2;
    if (count < 3) visible = 1;
    gVendorMenuState.index = count / 2;
    gVendorMenuState.field6C = (visible - count / 2) * 40;
    ResetWeaponMenu();
    if (gVendorMenuState.mode != 2) ForwardValueToLevelObject(0x112A880);
    if (gVendorMenuState.mode == 0 && gVendorMenuState.slots[gVendorMenuState.index].kind == 1 && gHeroState.mode != 10)
        ForwardPairToLevelObject(gVendorMenuState.slots[gVendorMenuState.index].id, 0x112A880);
    gVendorMenuState.state = 0;
    gVendorMenuState.base10 = D_001BAEC0.base10 + 0x60000;
    gVendorMenuState.base1C = gVendorMenuState.base10 + gScreenWidth.w * gScreenWidth.h * 4;
    gVendorMenuState.field8 = 0;
    gVendorMenuState.fieldC = 1;
    gVendorMenuState.moby = moby;
    gVendorMenuState.base14 = D_001BAEC0.baseC + 0x60000;
    PlayMobySound(3, 17, moby);
    gVendorMenuState.field4C = gEquipmentBits;
    gVendorMenuState.fieldA0 = *(short *)D_00152CE4;
    ClearSubtitleState();
    gCurrentGameMode = 5;
    gScreenFade = 0.0f;
    D_001B15A4 = 0;
    EmptyStubF748(97, 1);
    gHeroState.flag22BC = 1;
    gHeroState.flag22B5 = 1;
    EmptyStubF720();
    if (!gVendorMenuState.restore) {
        if (D_001A7BB1) matrix_mul_vec3(gVendorMenuState.position, D_001AD1F0, gVendorMenuState.moby + 0xC0);
        else matrix_mul_vec3(gVendorMenuState.position, D_001AD1E0, gVendorMenuState.moby + 0xC0);
        FastVecAdd(gVendorMenuState.position, gVendorMenuState.position, gVendorMenuState.moby + 0x10);
        gVendorMenuState.rotation[2] = FastAddRotations(*(float *)(gVendorMenuState.moby + 0xF8), 3.1415927f);
        SetCamera5Pose(gVendorMenuState.position, gVendorMenuState.rotation, 1, 0, 0);
        qcopy(tempVec, gVendorMenuState.position);
        if (gVendorMenuState.mode == 2) tempVec[1] += 5.0f;
        CopyVectorToSelectedObject(tempVec);
        SetCameraStateRotation(gVendorMenuState.rotation);
        UpdateCameraState();
    }
    matrix_mul_vec3(D_001C2AC0 + 0x10, D_001AD210, gVendorMenuState.moby + 0xC0);
    qcopy(D_001C2AC0, D_001AD220);
    qzero_nc(D_001C2AC0 + 0x30);
    qzero_nc(D_001C2AC0 + 0x20);
}
