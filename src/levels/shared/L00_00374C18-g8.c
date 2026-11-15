#include "common.h"

/* Partial layouts measured from the menu, controller and resource accesses. */
typedef struct {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
    int f60;
    int f64;
    int f68;
    int f6c;
    int f70;
    int f74;
    int f78;
    int f7c;
    int f80;
    int f84;
    int f88;
    int f8c;
    int f90;
    int f94;
    float f98;
    int f9c;
    int fa0;
    int fa4;
    float fa8;
    float fac;
    float fb0;
    float fb4;
    float fb8;
    float fbc;
    char rest[0x684];
} PurchaseMenuState;
extern PurchaseMenuState D_L00_0022F7C0[];
#define MENU ((char *)D_L00_0022F7C0)
extern float D_L00_001AD570 __attribute__((sda));
extern int D_L00_001B259C, D_L00_001B25A0, D_L00_001B25A4;
typedef struct {
    int pad[0x140 / 4];
    float x, y;
    char pad148[0x78];
    int held, pressed;
} PurchaseMenuInput;
extern PurchaseMenuInput D_00138180[];
typedef struct {
    int pad[0x4B40 / 4];
    struct { int value; char pad[16]; } entries[0];
} MenuResourceTable;
extern MenuResourceTable D_0014B540[];
extern short D_00152CE4 NOT_SDA;
extern unsigned char D_00139568[];
typedef struct {
    char prefix[0x3C];
    unsigned short value;
    char tail[0xE0 - 0x3E];
} MenuShopClass;
extern char D_L00_00262570[];
extern void func_L00_0030C788(int);
extern void func_002B7CE0(int);
extern void func_00294420(int);
extern void func_00294988(int);
extern void func_002F5220(void),func_002B6658(void),func_002E5F60(void);
extern void func_L00_002A6DD0(void);
extern void func_002B9390(void),func_002914B8(void),func_002F52B8(void);
extern int func_002B4B70(int,int);
extern int func_0028E138(int);
extern void func_00335370(void *),func_003353C8(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_L00_002EDCF0(float);
extern float func_00283B98(float,float);
extern void func_002A0F48(void *);
extern void func_00282D30(void *,void *,float);
extern void func_L00_0037A2E8(void),func_002FB1A0(void);
extern void func_L00_00374B98(void),func_L00_00374708(void);
extern void func_L00_0030C7C0(int),func_L00_0030C748(int,int),func_L00_0030C710(int);
extern void func_0029BCD8(void),func_002E4AC8(void);
#define MF(o) (*(float *)(m + (o)))
/* Advances the purchase menu and its model previews, then runs the shared update. */
void func_L00_00374C18(void)
{
    int i, itemId;
    char *m;
    float x, y;
    double stickMagnitude;
    float vec[4];

    switch (gPurchaseMenuModel[0].f00) {
    case 0:
        D_L00_001AD570 += 0.1f;
        CallLoadedModuleHandlerWithArg_L004427C8(1);
        if (D_L00_001AD570 >= 1.0f) {
            gPurchaseMenuModel[0].f00 = 1;
            D_L00_001AD570 = 1.0f;
            gPurchaseMenuModel[0].f04 = 0;
        }
        break;
    case 2:
        D_L00_001AD570 += 0.1f;
        CallLoadedModuleHandlerWithArg_L004427C8(0);
        if (D_L00_001AD570 < 1.0f)
            break;
        D_L00_001AD570 = 1.0f;
        if (gPurchaseMenuModel[0].f08) {
            gPurchaseMenuModel[0].f08 = 0;
            if (gPurchaseMenuModel[0].fa0 >= 0) {
                itemId = gCopySetupData[0].entries[gPurchaseMenuModel[0].fa0].value;
                PumpMusicAndDiscRead(1);
                LoadClassIntoFreeCacheSlot(itemId);
                PumpMusicAndDiscRead(1);
                SwitchCachedDiscAsset(itemId);
            } else {
                D_00152CE4 = -1;
            }
        }
        gPurchaseMenuModel[0].f04 = 0;
        if (!gPurchaseMenuModel[0].f60) {
            ResetFrameCounters();
            UpdateVisibleObjects();
            RunSoundCallbacks();
            UpdateHeroFrame_L00_2();
            UpdateParticles();
        }
        EndSlotRequest(0, 0);
        UpdateHudRecordTimers(1);
        if (!gPurchaseMenuModel[0].f60) {
            CopyVectorToSelectedObject(MENU + 0xD0);
            SetCameraStateRotation(MENU + 0xE0);
        }
        UpdateLightingEnvironment();
        UpdateIdleFrameCounters();
        break;
    case 1:
        if (gPadState[0].held & 0x8000)
            D_L00_001B259C++;
        else
            D_L00_001B259C = 0;
        if (gPadState[0].held & 0x2000)
            D_L00_001B25A0++;
        else
            D_L00_001B25A0 = 0;
        if (gPurchaseMenuModel[0].f90 == 0) {
            gPurchaseMenuModel[0].f94 += 3;
            if (gPurchaseMenuModel[0].f94 >= 128) {
                gPurchaseMenuModel[0].f94 = 128;
                gPurchaseMenuModel[0].f90 = 2;
            }
        } else if (gPurchaseMenuModel[0].f90 == 1) {
            gPurchaseMenuModel[0].f94 -= 16;
            gPurchaseMenuModel[0].f98 *= 0.9f;
            if (gPurchaseMenuModel[0].f94 <= 0) {
                gPurchaseMenuModel[0].f94 = 0;
                gPurchaseMenuModel[0].f90 = 3;
            }
        }
        if (gPurchaseMenuModel[0].f88) {
            for (i = 0; i < gPurchaseMenuModel[0].f34; i++) {
                float stickScale = 0.0033333334f;
                m = (char *)gPurchaseMenuModel[0].f2c + i * 256;
                matrix_mul_vec3(m + 16, MENU + 0xC0, (char *)gPurchaseMenuModel[0].f28 + 0xC0);
                FastVecAdd(m + 16, m + 16, (char *)gPurchaseMenuModel[0].f28 + 16);
                MF(0x2C) = *(float *)(*(char **)(m + 0x24) + 0x24) * gPurchaseMenuModel[0].f98;
                if (*(short *)(m + 0xAA) == 0x10E3 /* Spaceship Attachment */)
                    m[0x23] = gPurchaseMenuModel[0].f94 / 2;
                else
                    m[0x23] = gPurchaseMenuModel[0].f94;
                if (gPurchaseMenuModel[0].f50 != 2) {
                    MF(0xF8) = FastAddRotations(MF(0xF8), func_L00_002EDCF0(0.01f));
                } else {
                    x = gPadState[0].x * stickScale;
                    y = gPadState[0].y * stickScale;
                    if (gPurchaseMenuModel[0].fa4 <= 0) {
                        gPurchaseMenuModel[0].fb4 = FastAddRotations(gPurchaseMenuModel[0].fb4,
                            (gPurchaseMenuModel[0].fa8 - gPurchaseMenuModel[0].fb4) * 0.006666667f);
                        gPurchaseMenuModel[0].fb8 = FastAddRotations(gPurchaseMenuModel[0].fb8,
                            (gPurchaseMenuModel[0].fac - gPurchaseMenuModel[0].fb8) * 0.006666667f);
                        gPurchaseMenuModel[0].fbc = FastAddRotations(gPurchaseMenuModel[0].fbc,
                            (gPurchaseMenuModel[0].fb0 - gPurchaseMenuModel[0].fbc) * 0.006666667f);
                    } else {
                        gPurchaseMenuModel[0].fbc = FastAddRotations(gPurchaseMenuModel[0].fbc, x);
                        gPurchaseMenuModel[0].fb8 = FastAddRotations(gPurchaseMenuModel[0].fb8, y);
                    }
                    MF(0xF0) = gPurchaseMenuModel[0].fb4;
                    MF(0xF4) = gPurchaseMenuModel[0].fb8;
                    MF(0xF8) = gPurchaseMenuModel[0].fbc;
                    stickMagnitude = x;
                    if (stickMagnitude < 0.0)
                        stickMagnitude = 0.0 - stickMagnitude;
                    if (stickMagnitude > (double)0.0001f)
                        goto moved;
                    stickMagnitude = y;
                    if (stickMagnitude < 0.0)
                        stickMagnitude = 0.0 - stickMagnitude;
                    if (stickMagnitude > (double)0.0001f) {
                    moved:
                        gPurchaseMenuModel[0].fa4 = 180;
                    }
                }
                func_002A0F48(m);
                if (gPurchaseMenuModel[0].f50 != 2) {
                    FastVecScale(vec, m, 0.0009765625f);
                    MF(0x10) += MF(0x10) - vec[0];
                    MF(0x14) += MF(0x14) - vec[1];
                    func_002A0F48(m);
                }
            }
            if (gPurchaseMenuModel[0].fa4 > 0)
                gPurchaseMenuModel[0].fa4--;
        }
        if (gPurchaseMenuModel[0].f8c)
            BindVendorPreviewModel();
        else if (gPurchaseMenuModel[0].f90 == 3 && gPurchaseMenuModel[0].f84 == 0 &&
                 gPurchaseMenuModel[0].f6c == 0)
            PrepareVendorSelectionPreview();
        gPurchaseMenuModel[0].f04++;
        DispatchMenuByMode();
        DispatchPurchaseConfirmationByMode();
        D_L00_001B25A4 = gPadState[0].pressed;
        if (gPurchaseMenuModel[0].f50 == 0 &&
            *(int *)(MENU + 0x144 + gPurchaseMenuModel[0].f80 * 24) == 1) {
            CallLoadedModuleHandlerWithArg_L004427D0(*(int *)(MENU + 0x140 + gPurchaseMenuModel[0].f80 * 24));
            {
                int selected = *(int *)(MENU + 0x140 + gPurchaseMenuModel[0].f80 * 24);
                unsigned int classIndex = gItemSlotToRecord[selected];
                CallLoadedModuleHandlerWithArg_0034CAE8(((MenuShopClass *)gWeaponTable_L00)[classIndex].value, 10);
            }
        } else {
            CallLoadedModuleHandlerWithArg_L004427D0(0);
        }
        UpdateHudRecordTimers(1);
        if (gPurchaseMenuModel[0].f50 != 2)
            func_L00_0030C710(180);
        RunLevelCallbacks();
        break;
    }
    UpdateSoundVoices();
}
