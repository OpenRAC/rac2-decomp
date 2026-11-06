/* func_US2_L01_002C1D90, the USA v2.00 copy of func_L01_002C1A70: the same C, with three new tests of the
 * short at 0x1E0 that block the item actions (cases 10, the 12/15/17/31 group, and 53). */
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
    unsigned char gap1BC[0x24];
    short itemBlock;
    unsigned char gap1E2[0x2E];
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
extern int func_US2_L01_002BEEA8(int, int);
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
int func_US2_L01_002C1D90(void)
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

    if (D_00189E20.override && (D_00189E20.request != 10 || D_00189E20.stance != 1)) return 0;
    if (D_00189E20.mode) return 0;
    if (!D_00189E20.actionObject) return 0;
    if (D_00189E20.actionLock) return 0;
    if (D_00189E20.actionMode != 2) return 0;
    request = D_00189E20.request;
    mask = D_00189E20.actionMask;
    previousTimer = D_00189E20.transitionTimer;

    switch (request) {
    case 10:
        if (D_00189E20.attackDisabled) break;
        if (!D_00189E20.itemBlock && (MOTION < 2 || (MOTION == 4 && D_00189E20.canAttack))) {
            if (func_L00_0032EF10(mask, 10, &scratch.attackBuffered)) {
                object = D_00189E20.actionObject;
                if (!object) goto clearPending;
                if (!func_L00_002B3248((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                    goto clearPending;
                if ((D_00138180.buttons.word.buffered & 8) ||
                    ((ACTION == 1 || ACTION == 0x1D) && D_00189E20.transitionTimer > 20)) {
                    if ((ACTION == 1 || ACTION == 0x1D) && D_00189E20.transitionTimer > 20) {
                        func_L00_002BA508();
                        goto clearPending;
                    }
                    func_US2_L01_002BEEA8(0x15, 1);
                } else {
                    func_US2_L01_002BEEA8(0x13, 1);
                }
            }
        } else {
            if (ACTION == 7 || ACTION == 9 || ACTION == 0x89 || ACTION == 8 || ACTION == 6 ||
                (ACTION == 0xE && D_00189E20.animationFrame > 32.0f) ||
                (ACTION == 0xB && D_00189E20.airStyle != 3 && D_00189E20.animationFrame > 18.0f) ||
                (ACTION == 0xB && D_00189E20.airStyle == 3 && D_00189E20.animationFrame > 20.0f) ||
                ACTION == 0x2C || ACTION == 0x11) {
                if (D_00189E20.transitionTimer > 10) {
                    int airWindow = 0xE;
                    if (ACTION == 0xB || ACTION == 0xE) airWindow = 0x12;
                    if (!func_L00_0032EF10(mask, airWindow, 0)) goto clearPending;
                    if ((!D_00189E20.highAttack && D_00189E20.height > 0.1f) ||
                        (D_00189E20.highAttack && D_00189E20.height > 0.57f) ||
                        (ACTION == 8 && D_00189E20.height > 0.57f)) {
                        if (!D_00189E20.attackBlock && !D_00189E20.pendingAttack)
                            func_US2_L01_002BEEA8(0x14, 1);
                    } else {
                        func_US2_L01_002BEEA8(0x13, 1);
                    }
                    goto clearPending;
                }
            }
            if (MOTION == 6) {
                timing = D_L01_0025EC90[D_00189E20.animationIndex];
                if (ACTION == 0x15 && D_00189E20.transitionTimer > 30) {
                    if (D_00189E20.actionLock) goto checkAnimationLock;
                    if (D_00189E20.animationLock) goto clearPending;
                    if ((float)*(int *)(timing + 0x10) <= D_00189E20.animationFrame &&
                        (D_00138180.buttons.word.buffered & 8) && func_L00_0032EF10(mask, 15, 0)) {
                        func_US2_L01_002BEEA8(0x15, 1);
                        goto complete;
                    }
                }
checkAnimationLock:
                if (!D_00189E20.animationLock) {
                    if (!D_00189E20.actionLock) {
                        float frame = D_00189E20.animationFrame;
                        if ((float)*(int *)(timing + 0x10) <= frame) {
                            window = (func_00283CF0(frame) - *(int *)(timing + 0xC)) * 2;
                            window = window > 0 ? window : 1;
                            if (func_L00_0032EF10(mask, window < 16 ? window : 15, 0)) {
                                if (D_00138180.buttons.word.buffered & 8)
                                    func_US2_L01_002BEEA8(0x15, 1);
                                else
                                    func_US2_L01_002BEEA8(0x13, 1);
                                goto clearPending;
                            }
                        }
                    }
                    goto clearPending;
                }
            }
        }
clearPending:
        D_00189E20.pendingAttack = 0;
        break;

    case 22: case 65:
        if (ACTION == 1 || ACTION == 0x1D ||
            (MOTION > 1 && MOTION != 12 && (MOTION != 4 || !D_00189E20.canAttack)) ||
            (D_00189E20.queuedAction && D_00189E20.queuedAction != 22 && D_00189E20.queuedAction != 65)) break;
        if (!(D_00138180.buttons.word.buffered & 0x20) || D_00189E20.actionAge < 23) break;
        if (func_L00_002D4040(request)) {
            func_US2_L01_002BEEA8(0x83, 1);
            goto complete;
        }
        if (D_00138180.buttons.word.pressed & 0x20)
            func_002E5DA0(0, 0, D_00189E20.object,
                         (D_L01_002637A0 + D_00139568[request])->id);
        break;

    case 46: {
        char *target;
        if (D_00138180.buttons.word.pressed & mask) {
            if (D_00189E20.target) {
                D_00189E20.target = 0;
                break;
            }
            target = func_L00_002AE888((char *)&D_00189E20, 21, 0, 20.0f, D_00189E20.facing,
                                      0.52359885f, 0.6981318f);
            D_00189E20.target = target;
            if (target) {
                qcopy(&scratch.position, target + 0x10);
                ((float *)&scratch.position)[2] += 0.5f;
                if (func_002761F8(&scratch.position, D_00189E20.origin, 2, target, 0)) {
                    D_00189E20.target = 0;
                } else {
                    char *aimTarget = D_00189E20.target;
                    angle = func_00283248(D_00189E20.position[0] - *(float *)(aimTarget + 0x10),
                                          D_00189E20.position[1] - *(float *)(aimTarget + 0x14));
                    D_00189E20.targetAngle = func_00283BE0(*(float *)(D_00189E20.target + 0xF8), angle);
                }
            }
        }
        break;
    }

    case 12: case 15: case 17: case 31: {
        int actionAge;
        int actionWindow;
        if (((MOTION != 0 || ACTION == 0x1D) && MOTION != 1 && MOTION != 12 &&
             MOTION != 5 && MOTION != 15 && (MOTION != 4 || !D_00189E20.allowAction) &&
             (ACTION != 0x22 || !(D_00189E20.animationFrame > 55.0f))) || D_00189E20.busy ||
            D_00189E20.itemBlock) break;
        actionAge = D_00189E20.actionAge;
        actionWindow = actionAge;
        if (actionAge >= 7) actionWindow = 7;
        if (!func_L00_0032EF10(mask, actionWindow, &scratch.actionBuffered) && !(D_00138180.buttons.word.buffered & 0x20)) break;
        if (actionAge < 23) break;
        if (func_L00_002D4040(-1)) {
            if (MOTION == 12 || MOTION == 0 || ACTION == 3 ||
                (MOTION == 1 && D_00189E20.blend < 0.7f)) {
                func_US2_L01_002BEEA8(0x22, 1);
                goto complete;
            }
            func_L00_002AF568();
        } else if (D_00189E20.actionObject && (D_00138180.buttons.word.pressed & 0x20)) {
            func_002E5CF8(0, 0, D_00189E20.actionObject);
        }
        break;
    }

    case 53: {
        int wrenchAge;
        int wrenchWindow;
        if (D_00189E20.itemBlock) break;
        if (MOTION > 1 && (MOTION != 4 || !D_00189E20.canAttack)) break;
        if (ACTION != 1) {
            wrenchAge = D_00189E20.actionAge;
            wrenchWindow = 10;
            if (wrenchAge < 10) wrenchWindow = wrenchAge;
            if (func_L00_0032EF10(mask, wrenchWindow, &scratch.wrenchBuffered) && D_00189E20.actionObject) {
                func_US2_L01_002BEEA8(31, 1);
                if (D_00189E20.actionObject) func_002E5CF8(0, 0, D_00189E20.actionObject);
            }
        }
        break;
    }
    }

complete:
    if (D_00189E20.transitionTimer == previousTimer) {
        if (D_001A7B2E && D_001A7398[1] == 0x36 &&
            ACTION != 0x1D && ACTION != 1 &&
            !(D_00189E20.flags & 0xFFFFFFFF00000000UL)) {
            func_00282948(&D_L01_001A7CC4);
            if (D_L01_001A7CC4 &&
                (MOTION < 2 || MOTION == 12 || ((MOTION == 2 || MOTION == 4) && D_00189E20.platformMode)) &&
                (D_00138180.buttons.both & 0x800000008UL) == 0x800000008UL)
                func_US2_L01_002BEEA8(0x7B, 1);
            if (D_00138180.buttons.word.pressed & 8) D_L01_001A7CC4 = 30;
        }
    }
    return D_00189E20.transitionTimer < previousTimer;
}
