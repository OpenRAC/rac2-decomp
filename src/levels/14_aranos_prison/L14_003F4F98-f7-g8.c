/* Family F7: one body per level (L02, L05, L06, L10, L11, L12, L13, L15, L18, L22, L23), the
   same opcodes in each. Built with -malign-loops=2 (config/cflags.txt): see the print below. */
#include "common.h"

typedef struct {
    int msg;          /* 0x0 */
    int link;         /* 0x4 */
    unsigned char idx;   /* 0x8 */
    signed char item;    /* 0x9 */
    unsigned char on;    /* 0xA */
    signed char count;   /* 0xB */
    union { int word; signed char low; struct { char pad[1]; unsigned char quiet; char pad2; unsigned char had; } b; } tail; /* 0xC */
} TriggerVars;


extern void func_0026FEB8(const char *, ...);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);  /* its result is tested elsewhere */
extern void func_00288CB0(int, int);
extern void func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern void func_002A0430(int);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern int func_002B38B8(void *);
extern void func_002DF3F8(void *, void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);

extern unsigned int D_00139768[];
typedef struct {
    char pad0[0x80]; char body[0x2294 - 0x80];
    int mode; char pad2298[0x24CC - 0x2298];
    int health;
} HeroView;
extern HeroView D_00189E20;
extern char D_00189EA0[];
extern unsigned char D_0019B2E8[];
extern int D_001A79F0;
extern unsigned char D_001A7BC8[] MACRO_ADDR;
extern int D_L14_001A8F00;
extern char D_L14_001B15E0[];
extern int D_L14_001B20C8;
extern char *D_L14_001B268C;
extern char D_L14_001BF700[];
extern short **D_L14_002A71A0[];
extern char D_L14_002AA2C0[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

/* Updates a trigger that checks the player has the needed item, then plays the result and removes itself. */
void func_L14_00421BC0(Thing *trigger)
{
    TriggerVars *vars = trigger->vars;
    int notify, index, missing, fail;
    int played;

    switch (trigger->state) {
    case 0:
        if ((vars->item != -1 && D_001A7BC8[vars->item] != 0)
            || (trigger->group != 0xFF && (D_0019B2E8[trigger->group + gCurrentMapIndex * 16] & 0x80))) {
            MarkMobySpawned(trigger);
            break;
        }
        SetMobyState(trigger, 1, -1);
    case 1:
        if (vars->on == 0 && IsThirdPendingFlagSet(trigger) == 0 && trigger->hit == 0)
            break;
        vars->on = 1;
        SetMobyState(trigger, 2, -1);
    case 2:
        if (vars->on == 0) {
            SetMobyState(trigger, 1, -1);
            break;
        }
        if (gHeroState.mode == 0x1C)
            break;
        if (gHeroState.health <= 0)
            break;
        if (D_L14_001A8F00 != 0)
            break;
        if (vars->msg != -1 && IsPointInCuboid(gHeroState.body, vars->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_L14_002A71A0[gCurrentMapIndex] != 0 && D_L14_002A71A0[gCurrentMapIndex][vars->idx] != 0) {
            for (index = 0; D_L14_002A71A0[gCurrentMapIndex][vars->idx][index] != -1; index++) {
                int itemId = D_L14_002A71A0[gCurrentMapIndex][vars->idx][index];

                missing = 0;
                if (vars->tail.b.quiet == 0) {
                    int bit = 1 << (itemId & 0x1F);
                    if (D_00139768[(unsigned int)itemId >> 2] & bit)
                        continue;
                }
                if (PushRequestQueue(D_L14_001BF700, itemId) == 0 && index == 0) {
                    STUB_printf(D_L14_002AA2C0, trigger->id, trigger->oclass, gCurrentMapIndex, vars->idx, itemId);
                    return;
                }
                fail = 0;
            }
        }
        /* Retail keeps missing in $s5 above fail: the test's do-while (a debug-print macro's
           shape) counts it at loop depth, its fourth reference. Its loop label is not aligned
           in retail, so the unit turns loop alignment off; the other loop's label is already
           on an 8-byte boundary. */
        do {
            if (missing != 0)
                STUB_printf(D_L14_001B15E0, gCurrentMapIndex, vars->idx);
        } while (0);
        if (fail != 0) {
            vars->tail.b.had = 0;
            SetMobyState(trigger, 4, -1);
            break;
        }
        vars->tail.b.had = 1;
        LaunchQueuedRequest(D_L14_001BF700);
        if (D_L14_001B20C8 < 5 || (gCurrentMapIndex == 6 && vars->idx == 0))
            SetSlowdownFactorAndLowFpsFade();
        SetMobyState(trigger, 3, -1);
        break;
    case 3:
        if (IsEitherModeTwo() == 0) {
            if (vars->link != -1) {
                char *linkedEntry = D_L14_001B268C + (vars->link << 7);
                ResetHeroPositionAndDirection(linkedEntry + 0x30, linkedEntry + 0x70, 0, 1);
            }
            SetMobyState(trigger, 4, -1);
        }
        if (gCurrentMapIndex != 0)
            break;
        if (vars->item == -1)
            break;
        if (IsEitherModeTwo() != 0)
            break;
        notify = 0;
        if (vars->item != -1) {
            MarkFlagAndAppendToList(vars->item);
            if (vars->item != 0x18)
                PlayIndexedSound(vars->item);
            notify = 1;
        }
        if (trigger->group != 0xFF && !(D_0019B2E8[trigger->group + gCurrentMapIndex * 16] & 0x80)) {
            MarkTableEntryFlagged(trigger->group);
            notify = 1;
        }
        if (vars->count != 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *linkedEntry = D_L14_001B268C + (vars->link << 7);
                CaptureCheckpointState(linkedEntry + 0x30, linkedEntry + 0x70);
            } else
                CaptureCheckpointState(trigger->pos, trigger->dir);
        }
        if (vars->tail.low != -1)
            SetSmallDataValueAndRefresh(vars->tail.low, 1);
        else if (notify != 0 || vars->tail.b.had != 0)
            MemcardSave(0, -1);
        break;
    case 4:
        played = 0;
        if (vars->item != -1) {
            MarkFlagAndAppendToList(vars->item);
            if (vars->item != 0x18)
                PlayIndexedSound(vars->item);
            played = 1;
        }
        if (trigger->group != 0xFF && !(D_0019B2E8[trigger->group + gCurrentMapIndex * 16] & 0x80)) {
            MarkTableEntryFlagged(trigger->group);
            played = 1;
        }
        if (vars->count > 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *linkedEntry = D_L14_001B268C + (vars->link << 7);
                CaptureCheckpointState(linkedEntry + 0x30, linkedEntry + 0x70);
            } else
                CaptureCheckpointState(gHeroPosition, gHeroPosition + 0x10);
        }
        if (vars->tail.low != -1)
            SetSmallDataValueAndRefresh(vars->tail.low, 1);
        else if ((played != 0 || vars->tail.b.had != 0) && vars->count != vars->tail.low)
            MemcardSave(0, -1);
        MarkMobySpawned(trigger);
        break;
    }
}
