/* func_00286738 needs its own unit: -O2 -G8 -ffunction-sections -frac2-zero-ti-por
 * (config/cflags.txt). D_001B17D0's sda declaration gives retail's repeated
 * lui/addiu; D_0018C0D4, D_001F29A0 and D_001F2930 need absolute addressing;
 * D_001B1680 uses an incomplete sda view for its absolute store macro.
 * func_002AA548 returns float; func_0028B3D0 and func_002E4AC8 return int.
 * ref_00286738_00 is 0x1A8A44 in the boot and 0x1A8D94 in every level, where
 * func_L00_003A0C00 uses the name D_001A8A44 for a different word at 0x1A8A44.
 */

#include "common.h"

/* Modal state observed by the menu and camera transition handlers. */
typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    float cameraPosition[4];
    float cameraAngles[4];
    float returnPosition[4];
    float returnAngles[4];
    int mode;
    int countdown;
    char reserved48[12];
    int selection;
    int phase;
    int elapsed;
    int inputDelay;
    int reserved64;
    int pending;
    float fraction;
    float angle;
    char reserved74[8];
    short timer;
    short cameraActive;
    int savedValue;
    short result;
    short reserved86;
    int enabled;
    unsigned int acceptMask;
    unsigned int cancelMask;
    int gameState;
} ModalState;

typedef struct {
    char reserved00[0x100];
    float roll;
    char reserved104[0x44];
    float horizontal;
    float vertical;
    char reserved150[0x54];
    unsigned int buttons;
    char reserved1A8[0x18];
    unsigned int held;
    unsigned int pressed;
} ModalInput;

typedef struct CameraObject CameraObject;
struct CameraObject {
    char reserved00[0x64];
    void (*update)(CameraObject *);
    char reserved68[0x42];
    short kind;
    char reservedAC[0x54];
};

extern ModalState D_001BAC80;
extern ModalInput D_00138180;
extern int D_001B170C;
extern int D_001A7420;
extern int D_001A7424;
extern int D_001A8C88;
extern int D_001A8C8C;
extern int D_001F29A0 NOT_SDA;
typedef struct {
    char reserved00[0x18];
    int selection;
    char reserved1C[0xE4];
    int savedSelection;
} ModalSelection;
extern ModalSelection D_001F2840;
extern int *D_001F2930 NOT_SDA;
extern unsigned short D_0018C958[];
extern unsigned char D_001B1F10;
typedef struct {
    char reserved00[8];
    int status;
    char reserved0C[4];
    int result;
} ModalCardState;
extern ModalCardState D_001393E0;
extern int D_0013955C[];
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680[] __attribute__((sda));
extern int D_001A8A78 __attribute__((sda));
extern float D_001A8A7C __attribute__((sda));
typedef struct {
    float position[4];
    float angles[4];
    char reserved20[0x210];
    float matrix[16];
} ModalCamera;
extern ModalCamera D_001B5340;
extern float D_001B17D0[4] __attribute__((sda));
extern unsigned char D_001A7A44;
extern int D_001A79F0;
extern CameraObject *D_001B1B5C;
extern CameraObject *D_001B1B60;
extern unsigned char D_0018C0D4 NOT_SDA;
extern int D_001A8A40 __attribute__((sda));
extern int ref_00286738_00 __attribute__((sda));
extern int D_001A8A48 __attribute__((sda));
extern int D_001A8A60 __attribute__((sda));
extern int D_001A7BB8;

extern int func_002E4AC8(void);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern void func_0027D330(int);
extern int func_00288D80(void);
extern void func_00288D68(void);
extern void func_00287E80(void);
extern int func_002DF1D0(void);
extern int func_002C9A50(void);
extern void func_00298D28(int *);
extern void func_00287EA8(void);
extern int func_002B4B70(int, int);
extern void func_00298E08(void);
extern void func_002F64A8(void);
extern void func_002DE990(int);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00282DF0(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00287BD8(char *, int);
extern void func_00283098(void *, const void *, const void *);
extern void func_002AC9F8(float *, float);
extern void func_00282D30(void *, const void *, float);
extern void func_00287D98(char *);
extern void func_00287D20(float *);
extern void func_00283698(void *, const void *);
extern void func_002AB6D8(float *, float *);
extern void func_00282D08(void *, const void *, const void *, float);
extern void func_002A91F0(void *, float *);
extern void func_00283810(void *, const void *, const void *, float);
extern void func_00283958(const void *, void *);
extern void func_0026F7B0(void);
extern void func_00290670(void);
extern void func_00287E60(void);
extern int func_0028B3D0(int, int, void (*)(unsigned char *), void (*)(), void (*)(), int, int);
extern void func_0028BDB0(unsigned char *);
extern void func_0028BE00();
extern void func_0028C6D0();
extern void func_0028CC98(unsigned char *);
extern void func_0028CCE0();
extern void func_0028D1E8();
extern void func_0029CE38(void);
extern void func_0029B720(int);
extern void func_0029B698(int);
extern void func_00290728(void);
extern void func_00290720(void);
extern void func_002B49C0(int);
extern int func_002E5E58(int, int, void *);
extern void func_002857B8(void);

/* Run the active modal dialog, camera return, or display-confirmation phase. */
void func_00286738(void)
{
    float delta[4], target[4], transform[16];
    float distance;
    ModalState *loadDialog, *saveDialog, *phaseDialog;
    ModalInput *saveInput;

    UpdateSoundVoices();
    D_001B170C = gModalState.gameState;
    if (gModalState.countdown)
        --gModalState.countdown;
    if (gModalState.timer)
        --gModalState.timer;
    switch (gModalState.mode) {
    case 2:
        ++gModalState.elapsed;
        if (gModalState.elapsed > 90 && gModalState.inputDelay)
            --gModalState.inputDelay;
        if (gSaveMenuScreen == 2) {
            BeginSlotRequest(4, 2, 1, 0, 0);
            break;
        }
        if (gModalState.elapsed >= 121 && (gPadState.buttons & 0x40)) {
            if (!gSubtitleHistory[0x84 / 2])
                gSubtitleHistory[0x84 / 2] = 1;
            { EndSlotRequest(0, 0); break; }
        }
        break;
    case 5:
        ++gModalState.elapsed;
        if (gModalState.elapsed > 30 && gModalState.inputDelay)
            --gModalState.inputDelay;
        if (!gModalState.inputDelay && (gPadState.buttons & 0x40)) {
            gSaveMenuFlags &= ~0x40;
            D_0013955C[0] = 0;
            { RestartGameKeepingProgress(-1); LoadDataAndSetupCallback(); break; }
        }
        break;
    case 4:
        ++gModalState.elapsed;
        if (gModalState.elapsed > 30 && gModalState.inputDelay)
            --gModalState.inputDelay;
        if (!gModalState.inputDelay && (gPadState.buttons & 0x40)) {
            D_0013955C[0] = 0;
            { RestartGameKeepingProgress(-1); LoadDataAndSetupCallback(); break; }
        }
        break;
    case 3:
        switch (gModalState.phase) {
        case 0:
            if (!gModalState.countdown)
                gModalState.phase = 1;
            break;
        case 1:
            if (gPadState.buttons & 0x10)
                { EndSlotRequest(0, 0); break; }
            if (gPadState.buttons & 0x40) {
                FadeToBlack(4);
                D_001B1F10 = 0;
                gModalState.phase = 2;
                gModalState.elapsed = 600;
            }
            break;
        case 2:
            if (!gModalState.elapsed || --gModalState.elapsed == 0) {
                D_001B1F10 = 1;
                gModalState.phase = 3;
                break;
            }
            if (gPadState.buttons & 0x10) {
                FadeToBlack(4);
                D_001B1F10 = 1;
                { EndSlotRequest(0, 0); break; }
            } else if (gPadState.buttons & 0x40) {
                D_001B1F10 = 0;
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 3:
            if (!(gPadState.buttons & 0x40))
                break;
        default:
            { EndSlotRequest(0, 0); break; }
        }
        break;
    case 1:
        ++gModalState.elapsed;
        if (gModalState.elapsed > 30 && gModalState.inputDelay)
            --gModalState.inputDelay;
        if (GetFlagWord()) {
            if (!(gPadState.buttons & 0x40))
                break;
            ClearFlagWord();
            ClearMenuCounter_00287E80();
            { EndSlotRequest(0, 0); break; }
        }
        switch (gSaveMenuScreen) {
        case 2:
            if (!gModalState.inputDelay && (gPadState.buttons & 0x40)) {
                gModalState.result = 2;
                gSaveMenuFlags &= ~1;
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 6:
            if (!gModalState.inputDelay && (gPadState.buttons & 0x20)) {
                gSaveMenuFlags |= 8;
                gModalState.result = 2;
                break;
            }
            if (gModalState.countdown || !(gPadState.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                gModalState.result = 2;
                { RestartGameKeepingProgress(-1); LoadDataAndSetupCallback(); break; }
            }
            gSaveMenuFlags |= 0x20;
            if (!IsKnownMenuScreenActive())
                gSaveMenuFlags &= ~2;
            gSaveMenuFlags &= ~4;
            gModalState.result = 1;
            if (!D_001A8C88) {
                EndSlotRequest(0, 0);
                break;
            }
            break;
        case 13:
            if (!gModalState.inputDelay && (gPadState.buttons & 0x20)) {
                gSaveMenuFlags |= 0x10;
                gModalState.result = 2;
                break;
            }
            if (gModalState.countdown || !(gPadState.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                gModalState.result = 2;
                { RestartGameKeepingProgress(-1); LoadDataAndSetupCallback(); break; }
            }
            gSaveMenuFlags |= 0x20;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
            gModalState.result = 1;
            if (!D_001A8C88)
                { EndSlotRequest(0, 0); break; }
            break;
        case 20:
            if (gModalState.inputDelay || !(gPadState.buttons & 0x40))
                break;
            gSaveMenuFlags &= ~0x40;
                gSaveMenuFlags &= ~0x400;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
            gModalState.result = 2;
            if (!D_001A8C88) {
                if (GetMenuSavedValue()) {
                    LoadSavePacket(D_001F2930);
                    EndSlotRequest(0, 0);
                } else {
                    D_0013955C[0] = 0;
                    D_001B1680[0] = -1;
                    D_001A8B84 = 1;
                }
                break;
            }
            EndSlotRequest(0, 0);
            break;
        case 17:
        case 18:
        case 21:
            if (gModalState.pending > 0) {
                if (--gModalState.pending <= 0) {
                    if (gMemcardState.status == 2) {
                        if (!gMemcardState.result) {
                            gSaveMenuScreen = 9;
                        } else if (gMemcardState.result == -1) {
                            gSaveMenuScreen = 9;
                            gMemcardState.result = 0;
                        } else if (gMemcardState.result == -2) {
                            gSaveMenuScreen = 5;
                        } else {
                            gSaveMenuScreen = 12;
                        }
                        EndSlotRequest(0, 0);
                    } else {
                        gModalState.result = 2;
                        ClearConfirmPending();
                        RestartGameKeepingProgress(-1);
                        LoadDataAndSetupCallback();
                    }
                    break;
                }
            } else {
                if (gModalState.inputDelay || !(gPadState.buttons & 0x40))
                    break;
                ClearConfirmPending();
                if (D_001A8C8C) {
                    gModalState.pending = 15;
                } else {
                    gModalState.result = 2;
                    gSaveMenuFlags &= ~0x40;
                    gSaveMenuFlags &= ~0x400;
                    gSaveMenuFlags &= ~2;
                    gSaveMenuFlags &= ~4;
                    EndSlotRequest(0, 0);
                }
            }
            break;
        case 1:
        case 16:
            EndSlotRequest(0, 0);
            gPauseMenuState.selection = gModalState.selection;
            gPauseMenuState.savedSelection = gModalState.selection;
            break;
        case 12:
            if (!D_001F29A0)
                break;
        case 3:
        case 5:
            if (!gModalState.inputDelay && (gPadState.buttons & 0x10)) {
                gModalState.result = 1;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 19:
            if (D_001A8C88 && !D_001F29A0) {
                /* Set once, unlike a shared pointer, so alias analysis knows its
                 * base and the cancel arm's store has no tie to D_001A7424. The
                 * accept body below merges with case 23's copy at jump2. */
                ModalState *pickDialog = &gModalState;
                if (pickDialog->inputDelay)
                    break;
                if (gPadState.buttons & 0x40) {
                    LoadGameDataAndResetSaveMenu();
                    pickDialog->result = 2;
                    gSaveMenuFlags &= ~2;
                    gSaveMenuFlags &= ~4;
                    gSaveMenuFlags |= 0x20;
                    LoadDataAndSetupCallback();
                    break;
                }
                if (!(gPadState.buttons & 0x10))
                    break;
                pickDialog->result = 1;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
                { EndSlotRequest(0, 0); break; }
            }
            if (D_001A8C8C)
                goto acceptReload;
            {
                if (gModalState.inputDelay)
                    break;
                if (!(gPadState.buttons & 0x40) || D_001F29A0) {
                    if (!(gPadState.buttons & 0x10) || !D_001F29A0)
                        break;
                }
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
                gModalState.result = 1;
                { EndSlotRequest(0, 0); break; }
            }
        case 23:
        case 24:
            loadDialog = &gModalState;
            if (loadDialog->inputDelay)
                break;
            if (gPadState.buttons & 0x40) {
                LoadGameDataAndResetSaveMenu();
                loadDialog->result = 2;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
                gSaveMenuFlags |= 0x20;
                LoadDataAndSetupCallback();
                break;
            }
            if (gPadState.buttons & 0x10) {
                loadDialog->result = 1;
                gSaveMenuFlags |= 0x20;
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 4:
            if (D_001A8C88) {
                if (!D_001F29A0) {
                    saveDialog = &gModalState;
                    if (saveDialog->inputDelay)
                        break;
                    saveInput = &gPadState;
                    if (saveInput->buttons & 0x40) {
                        LoadGameDataAndResetSaveMenu();
                        saveDialog->result = 2;
                        gSaveMenuFlags &= ~2;
                        gSaveMenuFlags &= ~4;
                        LoadDataAndSetupCallback();
                    }
                    if (!saveDialog->inputDelay && (saveInput->buttons & 0x10)) {
                        saveDialog->result = 1;
                        gSaveMenuFlags |= 0x20;
                        gSaveMenuFlags &= ~2;
                        gSaveMenuFlags &= ~4;
                        EndSlotRequest(0, 0);
                    }
                    break;
                }
            } else if (D_001A8C8C) {
acceptReload:
                if (!gModalState.inputDelay && (gPadState.buttons & 0x40)) {
                    gModalState.result = 2;
                    RestartGameKeepingProgress(-1);
                    LoadDataAndSetupCallback();
                }
                break;
            }
            if (!gModalState.inputDelay && (gPadState.buttons & 0x10)) {
                gModalState.result = 1;
                gSaveMenuFlags |= 0x20;
                gSaveMenuFlags &= ~2;
                gSaveMenuFlags &= ~4;
                EndSlotRequest(0, 0);
            }
            break;
        case 9:
            if (!(gSaveMenuFlags & 6))
                { EndSlotRequest(0, 0); break; }
            break;
        }
        break;
    case 6:
        switch (gModalState.phase) {
        case 0:
            qcopy(gModalState.cameraPosition, gCameraState_001B5340.position);
            qcopy(gModalState.cameraAngles, gCameraState_001B5340.angles);
            gModalState.phase = 1;
            break;
        case 1:
            D_001B170C = 3;
            FastVecSub(delta, gCameraState_001B5340.position, D_001B17D0);
            distance = FastVecLength(delta);
            StepValueTowardTarget(&distance, &gModalState.fraction, (float)D_001A8A78,
                    0.041666668f, 0.041666668f, 5.0000005f);
            vec_scale_to_length(delta, delta, distance);
            FastVecAdd(gCameraState_001B5340.position, delta, D_001B17D0);
            UpdateCameraFollowRotation((char *)&gModalState.angle, 0);
            if ((float)D_001A8A78 <= distance)
                gModalState.phase = 2;
            break;
        case 2:
            D_001B170C = 3;
            if (gPadState.horizontal != 0.0f || gPadState.vertical != 0.0f) {
                *(Quadword *)target = 0;
                target[1] = gPadState.horizontal;
                target[2] = gPadState.vertical;
                *(Quadword *)delta = *(Quadword *)target;
                matrix_mul_vec3(delta, delta, gCameraState_001B5340.matrix);
                ClampVectorLength(delta, 1.0f);
                FastVecScale(delta, delta,
                        (float)-D_001A8A78 * 0.00029088825f * D_001A8A7C);
                OffsetCameraDirection((char *)delta);
            }
            UpdateCameraFollowRotation((char *)&gModalState.angle, 1);
            ApplyCameraRoll(&gPadState.roll);
            break;
        case 3: {
            float speed;
            D_001B170C = 3;
            speed = (float)D_001A8A78 * 0.00029088825f * D_001A8A7C;
            FastVecSub(target, gModalState.cameraPosition, D_001B17D0);
            vec_scale_to_length(target, target, (float)D_001A8A78);
            FastVecAdd(target, target, D_001B17D0);
            FastVecSub(delta, target, gCameraState_001B5340.position);
            matrix_from_basis_rows(transform, gCameraState_001B5340.matrix);
            matrix_mul_vec3(delta, delta, transform);
            delta[0] = 0.0f;
            if (delta[1] == 0.0f && delta[2] == 0.0f)
                delta[1] = 1.0f;
            ClampVectorLength(delta, speed);
            matrix_mul_vec3(delta, delta, gCameraState_001B5340.matrix);
            OffsetCameraDirection((char *)delta);
            UpdateCameraFollowRotation((char *)&gModalState.angle, 1);
            if (FastVecLength(delta) < speed - 0.01f) {
                /* The transition publishes its separate state word before capturing the return pose. */
                { extern int D_001B1710; D_001B1710 = 2; }
                qcopy(gModalState.returnPosition, gCameraState_001B5340.position);
                if (D_001A7A44) {
                    FastVecScale(gCameraState_001B5340.matrix + 4, gCameraState_001B5340.matrix + 4, -1.0f);
                    GetEulerAnglesFromMatrix(gCameraState_001B5340.matrix, gModalState.returnAngles);
                    FastVecScale(gCameraState_001B5340.matrix + 4, gCameraState_001B5340.matrix + 4, -1.0f);
                } else {
                    GetEulerAnglesFromMatrix(gCameraState_001B5340.matrix, gModalState.returnAngles);
                }
                gModalState.phase = 4;
            }
            break;
        }
        case 4:
            D_001B170C = 3;
            StepValueTowardTarget(&gModalState.fraction, &gModalState.angle,
                    1.0f, 0.00055555557f, 0.00055555557f, 0.025000002f);
            lerp_vector(gCameraState_001B5340.position, gModalState.returnPosition,
                    gModalState.cameraPosition, gModalState.fraction);
            BuildRotationFromAngles(delta, gModalState.returnAngles);
            BuildRotationFromAngles(target, gModalState.cameraAngles);
            FastVectorNormalize3(transform, delta, target, gModalState.fraction);
            quaternion_to_rotation_basis(transform, gCameraState_001B5340.matrix);
            if (D_001A7A44)
                FastVecScale(gCameraState_001B5340.matrix + 4, gCameraState_001B5340.matrix + 4, -1.0f);
            if (gModalState.fraction >= 1.0f)
                EndSlotRequest(0, 0);
            break;
        }
        gModalState.cameraActive = 1;
        if ((gPadState.buttons & 0x500) && gModalState.phase == 2) {
            gModalState.fraction = 0.0f;
            gModalState.phase = 3;
            gModalState.angle = 0.0f;
        }
        if ((unsigned)(gCurrentMapIndex - 22) < 2) {
            CameraObject *object = D_001B1B5C;
            if (object < D_001B1B60) {
                do {
                    if (object->kind == 0xD3D /* moby class 3389 */ && object->update)
                        object->update(object);
                    ++object;
                } while (object < D_001B1B60);
            }
        }
        break;
    case 7:
        switch (gModalState.phase) {
        case 0:
            gModalState.cameraActive = 1;
            gModalState.phase = 1;
            if (D_0018C0D4 != 1)
                EmptyStubF7B0();
            D_001A8A48 = 0;
            D_001A8A40 = ref_00286738_00;
            RequestLetterboxBars();
            SetStateWordToThree();
            break;
        case 1:
            if (D_0018C0D4 != 1) {
                EmptyStubF7B0();
                SetHudSlotContents(0x23, 0, InitMenuPanelLayout, UpdateRadialWeaponSelect, DrawWeaponWheel, 0, 0);
            } else {
                SetHudSlotContents(0x23, 0, InitRadialWeaponMenu, UpdateRadialMenuSelection, DrawRadialSelectorPanel, 0, 0);
            }
            func_0029CE38();
            ForwardValueToLevelObjectB(360);
            ForwardValueToLevelObject(180);
            RequestLetterboxBars();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            --D_001A8A60;
            if (D_001A8A60 < 0)
                D_001A8A60 = 0;
            if (!D_001A8A60)
                ++gModalState.phase;
            break;
        case 2:
            if (D_0018C0D4 != 1) {
                EmptyStubF7B0();
                SetHudSlotContents(0x23, 0, InitMenuPanelLayout, UpdateRadialWeaponSelect, DrawWeaponWheel, 0, 0);
            } else {
                SetHudSlotContents(0x23, 0, InitRadialWeaponMenu, UpdateRadialMenuSelection, DrawRadialSelectorPanel, 0, 0);
            }
            func_0029CE38();
            ForwardValueToLevelObjectB(360);
            ForwardValueToLevelObject(180);
            RequestLetterboxBars();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            if (D_001A8A40 <= 0) {
                D_001A8A40 = 0;
                ++gModalState.phase;
            }
            break;
        case 3:
            if (D_0018C0D4 != 1)
                EmptyStubF7B0();
            ClearHudFlagB();
            ClearHudFlagA();
            { EndSlotRequest(0, 0); break; }
        }
        break;
    case 8:
        phaseDialog = &gModalState;
        if (phaseDialog->phase != 2) {
            if (phaseDialog->phase >= 3)
                break;
            if (phaseDialog->phase < 0)
                break;
            ++phaseDialog->phase;
            break;
        }
        BeginSlotRequest(3, 2, phaseDialog->selection, 0, 0);
        SetRequestSettingB(3);
        goto advanceModalPhase;
    case 9:
        phaseDialog = &gModalState;
        switch (phaseDialog->phase) {
        case 1:
            if (gPadState.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                EndSlotRequest(0, 0);
            } else if (gPadState.held & phaseDialog->cancelMask) {
                phaseDialog->result = 1;
                EndSlotRequest(0, 0);
            }
            break;
        case 0:
            goto initializeDialog;
        }
        break;
    case 10:
        phaseDialog = &gModalState;
        switch (phaseDialog->phase) {
        case 0:
initializeDialog:
            ClearMenuCounter_00287E80();
advanceModalPhase:
            ++phaseDialog->phase;
            break;
        case 1:
            if (gPadState.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                PlaySoundFromGlobalBank(0x12, 0, 0);
                EndSlotRequest(0, 0);
            }
            break;
        default:
            break;
        }
        break;
    case 11:
        switch (gModalState.phase) {
        case 0:
            ClearMenuCounter_00287E80();
            ++gModalState.phase;
            if (gWidescreenFlag) {
                gWidescreenFlag = !gWidescreenFlag;
                ApplyScreenAspectMode();
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 1:
            if (gPadState.pressed & 0x40) {
                gModalState.result = 2;
                ++gModalState.phase;
            } else if (gPadState.held & 0x10) {
                gModalState.result = 1;
                { EndSlotRequest(0, 0); break; }
            }
            break;
        case 2:
            gModalState.elapsed = 900;
            gModalState.inputDelay = 0;
            ++gModalState.phase;
            gModalState.result = 0;
            gWidescreenFlag = !gWidescreenFlag;
            ApplyScreenAspectMode();
            break;
        case 3:
            if (gPadState.pressed & 0x40)
                gModalState.result = 2;
            else if (gPadState.pressed & 0x10)
                gModalState.result = 1;
            --gModalState.elapsed;
            if (gModalState.elapsed <= 0)
                goto advanceConfirmation;
            if (!gModalState.result)
                break;
            goto advanceConfirmation;
        case 4:
            if (gModalState.result < 0)
                goto advanceConfirmation;
            if (gModalState.result < 2) {
                gWidescreenFlag = !gWidescreenFlag;
                ApplyScreenAspectMode();
            }
advanceConfirmation:
            ++gModalState.phase;
            break;
        case 5:
            EndSlotRequest(0, 0);
            break;
        }
        break;
    }

}
