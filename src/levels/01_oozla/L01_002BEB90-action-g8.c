#include "include_asm.h"
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
/* A measured resident view, not a claim about the full allocation size. */
typedef struct ActionView {
    unsigned char gap0[0x80];
    float position[4];
    unsigned char gap90[0x8];
    float facing;
    unsigned char gap9C[0x44];
    float origin[4];
    unsigned char gapF0[0xC8];
    int transitionTimer;
    unsigned char gap1BC[0x54];
    unsigned long flags;
    unsigned char gap218[0x104];
    float height;
    unsigned char gap320[0x20];
    int platformMode;
    unsigned char gap344[0x4];
    short stance;
    unsigned char gap34A[0x152];
    unsigned char canAttack;
    unsigned char gap49D[0x1];
    unsigned char highAttack;
    unsigned char gap49F[0x35];
    int airStyle;
    unsigned char gap4D8[0x54];
    unsigned char allowAction;
    unsigned char gap52D[0x67];
    int pendingAttack;
    unsigned char gap598[0x28];
    char * target;
    float targetAngle;
    unsigned char gap5C8[0x124];
    int attackBlock;
    unsigned char gap6F0[0x50C];
    short animationIndex;
    unsigned char gapBFE[0x2E];
    int animationLock;
    unsigned char gapC30[0x8];
    float animationFrame;
    unsigned char gapC3C[0x5E4];
    char * actionObject;
    unsigned char gap1224[0xC];
    unsigned int actionMask;
    unsigned char gap1234[0x6];
    unsigned char actionLock;
    unsigned char gap123B[0x5];
    int actionAge;
    int actionMode;
    int request;
    unsigned char gap124C[0x24E];
    unsigned char attackDisabled;
    unsigned char gap149B[0xDF5];
    char * object;
    int action;
    unsigned char gap2298[0x4];
    unsigned int motion;
    unsigned char gap22A0[0x14];
    unsigned char mode;
    unsigned char gap22B5[0x3];
    unsigned char busy;
    unsigned char gap22B9[0x3];
    unsigned char override;
    unsigned char gap22BD[0x27];
    int queuedAction;
    unsigned char gap22E8[0x1D0];
    float blend;
} ActionView;
extern ActionView D_00189E20;
typedef union ButtonPair {
    struct { unsigned int buffered; unsigned int pressed; } word;
    unsigned long both;
} ButtonPair;
typedef struct InputView {
    unsigned char prefix[0x1A0];
    ButtonPair buttons;
} InputView;
extern InputView D_00138180;
extern unsigned char D_00139568[];
extern unsigned char D_001A7B2E;
/* Four per-slot item ids (also read in src/game/002C7748-g8.c); 0x001A739C is element 1. */
extern int D_001A7398[] __attribute__((sda));
extern int D_L01_001A7CC4 __attribute__((sda));
extern char D_L01_0025EC90[][44];
typedef struct ActionTableEntry {
    unsigned char prefix[0x14];
    int id;
    unsigned char suffix[0xC8];
} ActionTableEntry;
extern ActionTableEntry D_L01_002637A0[];
extern unsigned int func_L00_0032EF10(unsigned int, int, int *);
extern int func_L00_002B3248(unsigned char *);
extern void func_L00_002BA508(void);
extern int func_L01_002BEB90(long, int);
extern int func_L00_002D4040(int);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_002AE888(char *, int, int, float, float, float, float);
extern int func_002761F8(void *, void *, int, char *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern int func_00283CF0(float);
extern int func_00282948(int *);
extern void func_L00_002AF568(void);

/* Field views retain the measured resident layout without asserting its extent. */
#define ACTION D_00189E20.action
#define MOTION D_00189E20.motion

/* Equipped-item input for the current hero state, as in RAC1's
 * process_hero_item_action_input: starts the matching move and returns 1 when
 * the state timer was reset. */
int func_L01_002C1A70(void)
{
    int request;
    int previousTimer;
    unsigned int mask;
    struct {
        Quadword position;
        int attackBuffered;
        int actionBuffered;
        int wrenchBuffered;
    } scratch;
    char *object;
    char *timing;
    int window;
    float angle;

    if (gHeroState.override && (gHeroState.request != 10 || gHeroState.stance != 1)) return 0;
    if (gHeroState.mode) return 0;
    if (!gHeroState.actionObject) return 0;
    if (gHeroState.actionLock) return 0;
    if (gHeroState.actionMode != 2) return 0;
    request = gHeroState.request;
    mask = gHeroState.actionMask;
    previousTimer = gHeroState.transitionTimer;

    switch (request) {
    case 10:
        if (gHeroState.attackDisabled) break;
        if (MOTION < 2 || (MOTION == 4 && gHeroState.canAttack)) {
            if (PadPressedWithin(mask, 10, &scratch.attackBuffered)) {
                object = gHeroState.actionObject;
                if (!object) goto clearPending;
                if (!IsMobyClass71((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                    goto clearPending;
                if ((gPadState.buttons.word.buffered & 8) ||
                    ((ACTION == 1 || ACTION == 0x1D) && gHeroState.transitionTimer > 20)) {
                    if ((ACTION == 1 || ACTION == 0x1D) && gHeroState.transitionTimer > 20) {
                        SetupHeroAttachedObjectTransform();
                        goto clearPending;
                    }
                    SetHeroMoveState(0x15, 1);
                } else {
                    SetHeroMoveState(0x13, 1);
                }
            }
        } else {
            if (ACTION == 7 || ACTION == 9 || ACTION == 0x89 || ACTION == 8 || ACTION == 6 ||
                (ACTION == 0xE && gHeroState.animationFrame > 32.0f) ||
                (ACTION == 0xB && gHeroState.airStyle != 3 && gHeroState.animationFrame > 18.0f) ||
                (ACTION == 0xB && gHeroState.airStyle == 3 && gHeroState.animationFrame > 20.0f) ||
                ACTION == 0x2C || ACTION == 0x11) {
                if (gHeroState.transitionTimer > 10) {
                    int airWindow = 0xE;
                    if (ACTION == 0xB || ACTION == 0xE) airWindow = 0x12;
                    if (!PadPressedWithin(mask, airWindow, 0)) goto clearPending;
                    if ((!gHeroState.highAttack && gHeroState.height > 0.1f) ||
                        (gHeroState.highAttack && gHeroState.height > 0.57f) ||
                        (ACTION == 8 && gHeroState.height > 0.57f)) {
                        if (!gHeroState.attackBlock && !gHeroState.pendingAttack)
                            SetHeroMoveState(0x14, 1);
                    } else {
                        SetHeroMoveState(0x13, 1);
                    }
                    goto clearPending;
                }
            }
            if (MOTION == 6) {
                timing = D_L01_0025EC90[gHeroState.animationIndex];
                if (ACTION == 0x15 && gHeroState.transitionTimer > 30) {
                    if (gHeroState.actionLock) goto checkAnimationLock;
                    if (gHeroState.animationLock) goto clearPending;
                    if ((float)*(int *)(timing + 0x10) <= gHeroState.animationFrame &&
                        (gPadState.buttons.word.buffered & 8) && PadPressedWithin(mask, 15, 0)) {
                        SetHeroMoveState(0x15, 1);
                        goto complete;
                    }
                }
checkAnimationLock:
                if (!gHeroState.animationLock) {
                    if (!gHeroState.actionLock) {
                        float frame = gHeroState.animationFrame;
                        if ((float)*(int *)(timing + 0x10) <= frame) {
                            window = (FloatToInt(frame) - *(int *)(timing + 0xC)) * 2;
                            window = window > 0 ? window : 1;
                            if (PadPressedWithin(mask, window < 16 ? window : 15, 0)) {
                                if (gPadState.buttons.word.buffered & 8)
                                    SetHeroMoveState(0x15, 1);
                                else
                                    SetHeroMoveState(0x13, 1);
                                goto clearPending;
                            }
                        }
                    }
                    goto clearPending;
                }
            }
        }
clearPending:
        gHeroState.pendingAttack = 0;
        break;

    case 22: case 65:
        if (ACTION == 1 || ACTION == 0x1D ||
            (MOTION > 1 && MOTION != 12 && (MOTION != 4 || !gHeroState.canAttack)) ||
            (gHeroState.queuedAction && gHeroState.queuedAction != 22 && gHeroState.queuedAction != 65)) break;
        if (!(gPadState.buttons.word.buffered & 0x20) || gHeroState.actionAge < 23) break;
        if (get_ammo(request)) {
            SetHeroMoveState(0x83, 1);
            goto complete;
        }
        if (gPadState.buttons.word.pressed & 0x20)
            PlaySoundFromClassBank(0, 0, gHeroState.object,
                         (D_L01_002637A0 + gItemSlotToRecord[request])->id);
        break;

    case 46: {
        char *target;
        if (gPadState.buttons.word.pressed & mask) {
            if (gHeroState.target) {
                gHeroState.target = 0;
                break;
            }
            target = SelectBestEligibleTarget((char *)&gHeroState, 21, 0, 20.0f, gHeroState.facing,
                                      0.52359885f, 0.6981318f);
            gHeroState.target = target;
            if (target) {
                qcopy(&scratch.position, target + 0x10);
                ((float *)&scratch.position)[2] += 0.5f;
                if (CollLine(&scratch.position, gHeroState.origin, 2, target, 0)) {
                    gHeroState.target = 0;
                } else {
                    char *aimTarget = gHeroState.target;
                    angle = FastMatrixHelperA(gHeroState.position[0] - *(float *)(aimTarget + 0x10),
                                          gHeroState.position[1] - *(float *)(aimTarget + 0x14));
                    gHeroState.targetAngle = fast_subtract_rotations(*(float *)(gHeroState.target + 0xF8), angle);
                }
            }
        }
        break;
    }

    case 12: case 15: case 17: case 31: {
        int actionAge;
        int actionWindow;
        if (((MOTION != 0 || ACTION == 0x1D) && MOTION != 1 && MOTION != 12 &&
             MOTION != 5 && MOTION != 15 && (MOTION != 4 || !gHeroState.allowAction) &&
             (ACTION != 0x22 || !(gHeroState.animationFrame > 55.0f))) || gHeroState.busy) break;
        actionAge = gHeroState.actionAge;
        actionWindow = actionAge;
        if (actionAge >= 7) actionWindow = 7;
        if (!PadPressedWithin(mask, actionWindow, &scratch.actionBuffered) && !(gPadState.buttons.word.buffered & 0x20)) break;
        if (actionAge < 23) break;
        if (get_ammo(-1)) {
            if (MOTION == 12 || MOTION == 0 || ACTION == 3 ||
                (MOTION == 1 && gHeroState.blend < 0.7f)) {
                SetHeroMoveState(0x22, 1);
                goto complete;
            }
            start_equipped_item_animation();
        } else if (gHeroState.actionObject && (gPadState.buttons.word.pressed & 0x20)) {
            PlayMobySound(0, 0, gHeroState.actionObject);
        }
        break;
    }

    case 53: {
        int wrenchAge;
        int wrenchWindow;
        if (MOTION > 1 && (MOTION != 4 || !gHeroState.canAttack)) break;
        if (ACTION != 1) {
            wrenchAge = gHeroState.actionAge;
            wrenchWindow = 10;
            if (wrenchAge < 10) wrenchWindow = wrenchAge;
            if (PadPressedWithin(mask, wrenchWindow, &scratch.wrenchBuffered) && gHeroState.actionObject) {
                SetHeroMoveState(31, 1);
                if (gHeroState.actionObject) PlayMobySound(0, 0, gHeroState.actionObject);
            }
        }
        break;
    }
    }

complete:
    if (gHeroState.transitionTimer == previousTimer) {
        if (D_001A7B2E && D_001A7398[1] == 0x36 &&
            ACTION != 0x1D && ACTION != 1 &&
            !(gHeroState.flags & 0xFFFFFFFF00000000UL)) {
            FastFloatHelperD(&D_L01_001A7CC4);
            if (D_L01_001A7CC4 &&
                (MOTION < 2 || MOTION == 12 || ((MOTION == 2 || MOTION == 4) && gHeroState.platformMode)) &&
                (gPadState.buttons.both & 0x800000008UL) == 0x800000008UL)
                SetHeroMoveState(0x7B, 1);
            if (gPadState.buttons.word.pressed & 8) D_L01_001A7CC4 = 30;
        }
    }
    return gHeroState.transitionTimer < previousTimer;
}
