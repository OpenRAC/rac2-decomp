/* Nonmatching Todano tutorial controller: 600/600 USA bytes, 0/1 placements.
 * Seven bounded trials: plain scalars584; measured non-SDA scalars600;
 * macro-address scalars584; no-split addresses588; no-expensive584;
 * sign-extended mask expression tied600; -O1 gave596. No flags retained.
 * The core state machine and event/statistic logic are reconstructed. Remaining
 * differences are scalar-load scheduling/speculation and boolean mask lowering
 * (retail builds 1<<level then AND, compiler shifts the mask then tests bit0).
 * Reopen with original global-owner/type or compiler-profile evidence.
 *
 * Contracts verified in current definitions: 2A7750 void(u8*,s32,s32),
 * 2ACBC8 int(void*,int), 288E18 int(int,int). Retail 282948 reads/writes one
 * signed32 timer and returns integer status. No false unused void returns.
 * The target object stride is256, state20bytes, hero-position measured prefix
 * reaches+0x540; the save/progress owner remains an incomplete external array
 * viewed through its measured+450/+454/+458 fields. No local owner allocation.
 * RAC1 Eudora tutorial/statistics controller at8bbc6b38 was inspected as a family
 * reference; its field layout, hints and timing differ, so no donor code copied.
 */
#include "common.h"

typedef struct {
    int firstVolume, secondVolume, thirdVolume, targetIndex, timer;
} TutorialTriggerState;

typedef struct {
    char reserved00[0x10];
    float position[4];
    unsigned char mode;
    char reserved21[0x0F];
    unsigned char updateDistance;
    char reserved31[0x37];
    TutorialTriggerState *state;
    char reserved6C[0x3E];
    short classId;
    char reservedAC[0x54];
} TutorialTriggerObject;

typedef struct {
    float position[4];
    char reserved10[0x530];
    int vehicleState;
} TutorialHeroPositionPrefix;

typedef struct {
    char reserved00[0x450];
    unsigned short count;
    char reserved452[2];
    unsigned int lastTime;
    unsigned int levelMask;
} TutorialProgressPrefix;

extern float D_00189EA0[];
extern unsigned char D_0018C958[];
extern unsigned short D_0018CF04 NOT_SDA;
extern unsigned char D_001A7B2B NOT_SDA;
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0;
extern TutorialTriggerObject *D_L12_001B2E9C __attribute__((sda));
extern int D_0018CDBC NOT_SDA;
extern int D_0018CF54 NOT_SDA;
extern unsigned char D_001A7AFF NOT_SDA;
extern int D_0018C0B4 NOT_SDA;
extern void func_002A7750(unsigned char *, int, int);
extern int func_002ACBC8(void *, int);
extern int func_00288E18(int, int);
extern int func_00282948(int *);

/* These measured prefixes describe external owners, not local allocations. */
void func_L12_003EB470(TutorialTriggerObject *object)
{
    TutorialTriggerState *state = object->state;
    switch (object->mode) {
    case 0:
        object->updateDistance = 255;
        state->timer = -1;
        func_002A7750((unsigned char *)object, 1, -1);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, state->firstVolume) &&
            ((TutorialHeroPositionPrefix *)D_00189EA0)->vehicleState && !D_0018CF04)
            func_00288E18(0xA22, 0x79);
        if (func_002ACBC8(D_00189EA0, state->secondVolume) && !D_001A7B2B) {
            TutorialProgressPrefix *progress = (TutorialProgressPrefix *)D_0018C958;
            unsigned int now = D_001A7390;
            if (progress->count) {
                if (now - progress->lastTime > 0x438 || progress->lastTime == 0)
                    func_00288E18(0xA05, 0x5C);
                else if (progress->lastTime < now)
                    progress->lastTime = now;
            } else {
                progress->count++;
                if (progress->lastTime < now)
                    progress->lastTime = now;
                progress->levelMask = progress->levelMask | (1 << D_001A79F0) | 0x80000000U;
            }
        }
        if (func_002ACBC8(D_00189EA0, state->thirdVolume)) {
            TutorialTriggerObject *target = D_L12_001B2E9C + state->targetIndex;
            if (target && target->classId == 0xFB8 && target->mode != 0xFE &&
                target->mode != 0xFD) {
                if (state->timer < 0)
                    state->timer = 0x2A30;
                else if (state->timer == 0 && !(D_0018CDBC & (1 << D_001A79F0)))
                    func_00288E18(0xA06, 0x5D);
            }
        }
        if (D_001A7AFF && D_0018C0B4 != 0x6F && !(D_0018CF54 & (1 << D_001A79F0)))
            func_00288E18(0xA28, 0x7F);
        if (state->timer >= 0)
            func_00282948(&state->timer);
        break;
    }
}
