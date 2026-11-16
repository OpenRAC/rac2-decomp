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
extern ActionView g_hero_state;
typedef union ButtonPair {
    struct { unsigned int buffered; unsigned int pressed; } word;
    unsigned long both;
} ButtonPair;
typedef struct InputView {
    unsigned char prefix[0x1A0];
    ButtonPair buttons;
} InputView;
extern InputView g_pad_state;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_action_flag;
/* Four per-slot item ids (also read in src/game/002C7748-g8.c); 0x001A739C is element 1. */
extern int g_menu_choice_table[] __attribute__((sda));
extern int g_hero_action_timer __attribute__((sda));
extern char g_hero_anim_timing_table[][44];
typedef struct ActionTableEntry {
    unsigned char prefix[0x14];
    int id;
    unsigned char suffix[0xC8];
} ActionTableEntry;
extern ActionTableEntry g_action_table[];
extern unsigned int PadPressedWithin(unsigned int, int, int *);
extern int moby_is_class_71(unsigned char *);
extern void hero_setup_attached_object_transform(void);
extern int SetHeroMoveState(long, int);
extern int get_ammo(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int PlayMobySound(int, int, char *);
extern char *SelectBestEligibleTarget(char *, int, int, float, float, float, float);
extern int CollLine(void *, void *, int, char *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern int FloatToInt(float);
extern int math_fast_float_d(int *);
extern void start_equipped_item_animation(void);

/* Field views retain the measured resident layout without asserting its extent. */
#define ACTION D_00189E20.action
#define MOTION D_00189E20.motion

/* Equipped-item input for the current hero state, as in RAC1's
 * process_hero_item_action_input: starts the matching move and returns 1 when
 * the state timer was reset. */
int ProcessHeroItemActionInput(void)
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

    if (g_hero_state.override && (g_hero_state.request != 10 || g_hero_state.stance != 1)) return 0;
    if (g_hero_state.mode) return 0;
    if (!g_hero_state.actionObject) return 0;
    if (g_hero_state.actionLock) return 0;
    if (g_hero_state.actionMode != 2) return 0;
    request = g_hero_state.request;
    mask = g_hero_state.actionMask;
    previousTimer = g_hero_state.transitionTimer;

    switch (request) {
    case 10:
        if (g_hero_state.attackDisabled) break;
        if (MOTION < 2 || (MOTION == 4 && g_hero_state.canAttack)) {
            if (PadPressedWithin(mask, 10, &scratch.attackBuffered)) {
                object = g_hero_state.actionObject;
                if (!object) goto clearPending;
                if (!moby_is_class_71((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                    goto clearPending;
                if ((g_pad_state.buttons.word.buffered & 8) ||
                    ((ACTION == 1 || ACTION == 0x1D) && g_hero_state.transitionTimer > 20)) {
                    if ((ACTION == 1 || ACTION == 0x1D) && g_hero_state.transitionTimer > 20) {
                        hero_setup_attached_object_transform();
                        goto clearPending;
                    }
                    SetHeroMoveState(0x15, 1);
                } else {
                    SetHeroMoveState(0x13, 1);
                }
            }
        } else {
            if (ACTION == 7 || ACTION == 9 || ACTION == 0x89 || ACTION == 8 || ACTION == 6 ||
                (ACTION == 0xE && g_hero_state.animationFrame > 32.0f) ||
                (ACTION == 0xB && g_hero_state.airStyle != 3 && g_hero_state.animationFrame > 18.0f) ||
                (ACTION == 0xB && g_hero_state.airStyle == 3 && g_hero_state.animationFrame > 20.0f) ||
                ACTION == 0x2C || ACTION == 0x11) {
                if (g_hero_state.transitionTimer > 10) {
                    int airWindow = 0xE;
                    if (ACTION == 0xB || ACTION == 0xE) airWindow = 0x12;
                    if (!PadPressedWithin(mask, airWindow, 0)) goto clearPending;
                    if ((!g_hero_state.highAttack && g_hero_state.height > 0.1f) ||
                        (g_hero_state.highAttack && g_hero_state.height > 0.57f) ||
                        (ACTION == 8 && g_hero_state.height > 0.57f)) {
                        if (!g_hero_state.attackBlock && !g_hero_state.pendingAttack)
                            SetHeroMoveState(0x14, 1);
                    } else {
                        SetHeroMoveState(0x13, 1);
                    }
                    goto clearPending;
                }
            }
            if (MOTION == 6) {
                timing = g_hero_anim_timing_table[g_hero_state.animationIndex];
                if (ACTION == 0x15 && g_hero_state.transitionTimer > 30) {
                    if (g_hero_state.actionLock) goto checkAnimationLock;
                    if (g_hero_state.animationLock) goto clearPending;
                    if ((float)*(int *)(timing + 0x10) <= g_hero_state.animationFrame &&
                        (g_pad_state.buttons.word.buffered & 8) && PadPressedWithin(mask, 15, 0)) {
                        SetHeroMoveState(0x15, 1);
                        goto complete;
                    }
                }
checkAnimationLock:
                if (!g_hero_state.animationLock) {
                    if (!g_hero_state.actionLock) {
                        float frame = g_hero_state.animationFrame;
                        if ((float)*(int *)(timing + 0x10) <= frame) {
                            window = (FloatToInt(frame) - *(int *)(timing + 0xC)) * 2;
                            window = window > 0 ? window : 1;
                            if (PadPressedWithin(mask, window < 16 ? window : 15, 0)) {
                                if (g_pad_state.buttons.word.buffered & 8)
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
        g_hero_state.pendingAttack = 0;
        break;

    case 22: case 65:
        if (ACTION == 1 || ACTION == 0x1D ||
            (MOTION > 1 && MOTION != 12 && (MOTION != 4 || !g_hero_state.canAttack)) ||
            (g_hero_state.queuedAction && g_hero_state.queuedAction != 22 && g_hero_state.queuedAction != 65)) break;
        if (!(g_pad_state.buttons.word.buffered & 0x20) || g_hero_state.actionAge < 23) break;
        if (get_ammo(request)) {
            SetHeroMoveState(0x83, 1);
            goto complete;
        }
        if (g_pad_state.buttons.word.pressed & 0x20)
            snd_play_from_class_bank(0, 0, g_hero_state.object,
                         (g_action_table + g_item_slot_to_record[request])->id);
        break;

    case 46: {
        char *target;
        if (g_pad_state.buttons.word.pressed & mask) {
            if (g_hero_state.target) {
                g_hero_state.target = 0;
                break;
            }
            target = SelectBestEligibleTarget((char *)&g_hero_state, 21, 0, 20.0f, g_hero_state.facing,
                                      0.52359885f, 0.6981318f);
            g_hero_state.target = target;
            if (target) {
                qcopy(&scratch.position, target + 0x10);
                ((float *)&scratch.position)[2] += 0.5f;
                if (CollLine(&scratch.position, g_hero_state.origin, 2, target, 0)) {
                    g_hero_state.target = 0;
                } else {
                    char *aimTarget = g_hero_state.target;
                    angle = mat_fast_helper_a(g_hero_state.position[0] - *(float *)(aimTarget + 0x10),
                                          g_hero_state.position[1] - *(float *)(aimTarget + 0x14));
                    g_hero_state.targetAngle = fast_subtract_rotations(*(float *)(g_hero_state.target + 0xF8), angle);
                }
            }
        }
        break;
    }

    case 12: case 15: case 17: case 31: {
        int actionAge;
        int actionWindow;
        if (((MOTION != 0 || ACTION == 0x1D) && MOTION != 1 && MOTION != 12 &&
             MOTION != 5 && MOTION != 15 && (MOTION != 4 || !g_hero_state.allowAction) &&
             (ACTION != 0x22 || !(g_hero_state.animationFrame > 55.0f))) || g_hero_state.busy) break;
        actionAge = g_hero_state.actionAge;
        actionWindow = actionAge;
        if (actionAge >= 7) actionWindow = 7;
        if (!PadPressedWithin(mask, actionWindow, &scratch.actionBuffered) && !(g_pad_state.buttons.word.buffered & 0x20)) break;
        if (actionAge < 23) break;
        if (get_ammo(-1)) {
            if (MOTION == 12 || MOTION == 0 || ACTION == 3 ||
                (MOTION == 1 && g_hero_state.blend < 0.7f)) {
                SetHeroMoveState(0x22, 1);
                goto complete;
            }
            start_equipped_item_animation();
        } else if (g_hero_state.actionObject && (g_pad_state.buttons.word.pressed & 0x20)) {
            PlayMobySound(0, 0, g_hero_state.actionObject);
        }
        break;
    }

    case 53: {
        int wrenchAge;
        int wrenchWindow;
        if (MOTION > 1 && (MOTION != 4 || !g_hero_state.canAttack)) break;
        if (ACTION != 1) {
            wrenchAge = g_hero_state.actionAge;
            wrenchWindow = 10;
            if (wrenchAge < 10) wrenchWindow = wrenchAge;
            if (PadPressedWithin(mask, wrenchWindow, &scratch.wrenchBuffered) && g_hero_state.actionObject) {
                SetHeroMoveState(31, 1);
                if (g_hero_state.actionObject) PlayMobySound(0, 0, g_hero_state.actionObject);
            }
        }
        break;
    }
    }

complete:
    if (g_hero_state.transitionTimer == previousTimer) {
        if (g_action_flag && g_menu_choice_table[1] == 0x36 &&
            ACTION != 0x1D && ACTION != 1 &&
            !(g_hero_state.flags & 0xFFFFFFFF00000000UL)) {
            math_fast_float_d(&g_hero_action_timer);
            if (g_hero_action_timer &&
                (MOTION < 2 || MOTION == 12 || ((MOTION == 2 || MOTION == 4) && g_hero_state.platformMode)) &&
                (g_pad_state.buttons.both & 0x800000008UL) == 0x800000008UL)
                SetHeroMoveState(0x7B, 1);
            if (g_pad_state.buttons.word.pressed & 8) g_hero_action_timer = 30;
        }
    }
    return g_hero_state.transitionTimer < previousTimer;
}
