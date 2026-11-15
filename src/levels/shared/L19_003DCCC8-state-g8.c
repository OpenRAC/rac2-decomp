/* State update of a level 19/20 object, the same instructions as func_L18_003F80A0. Its own unit
 * for the same reasons: -G8 for the $gp limit and -frac2-gcse-unsplit-edges, because the repeated
 * object+0x10 and state+0x700 are shared by PRE (no locals).
 */
#include "common.h"

extern int func_002B3868(u8 *);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_L09_0033E690(u8 *, int, float);
/* Defined in L18_003F8EA8-qcopy.c; the float takes its place among the integers here. */
extern int func_L18_003F8EA8(u8 *, u8 *, int, float, s16 *, int);
extern int func_L18_0033B628(u8 *, int, int);
extern int func_L18_003FA8E0(int);
extern void func_L18_003FA908(int);
extern float func_L02_002F21C0(u8 *, u8 *);
extern void func_L18_003FB5E8(u8 *, u8 *);
extern void func_00282F20(u8 *, u8 *, float);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern int func_L02_004127F8(u8 *);
extern void func_L18_003FB500(u8 *, int);
extern int func_002B1C20(u8 *, u8 *);
extern void func_002A6C58(u8 *, int, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(u8 *);
extern void func_L18_003F8FA8(u8 *);
extern int D_0018C0B4 NOT_SDA;
extern u8 D_00189EA0[];
extern u8 D_L19_001A8F20[] __attribute__((sda));
extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern int D_L19_001B2A38 __attribute__((sda));
extern u8 *D_L19_001B2B0C[] __attribute__((sda));

typedef struct { u8 pad[0x30]; u8 pos[0x10]; u8 rest[0x40]; } TargetRecord;

#define WORD(p,o) (*(int *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define UHALF(p,o) (*(u16 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))
#define PTR(p,o) (*(u8 **)((p)+(o)))

/* Updates a small flying enemy: it idles, patrols, chases a target, dives at a nearby object, and splits into pieces when hit. */
void func_L19_003DCCC8(u8 *object)
{
    u8 temp[16] __attribute__((aligned(16)));
    u8 position[16] __attribute__((aligned(16)));
    u8 *state = PTR(object, 0x68);
    u8 *entity;
    u16 *listEntry;
    float best, distance;
    int hit;
    switch (object[0x20]) {
    case 0: break;
    case 1:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2))
                StartAnimationBlended(object, RandomIntBelow(2), 0, 10);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(object)) {
            SetControllerSpeedLimits(object, 0.0022222223f, 0.06666667f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != RandomIntBelow(2))
                StartAnimationBlended(object, RandomIntBelow(2), 0, 10);
        } else if (HALF(state, 0x768)) {
            SetMobyState(object, 5, 2);
            SetMobyState(object, 4, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2) + 4)
                StartAnimationBlended(object, RandomIntBelow(2) + 4, 0, 10);
            object[0xBC] = RandomIntBelow(180) + 120;
        } else if (UHALF(object, 0x96) > object[0xBC])
            SetMobyState(object, object[0x94], -1);
        break;
    case 4:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2) + 2)
                StartAnimationBlended(object, RandomIntBelow(2) + 2, 0, 10);
        } else if (object[0x60] & 2)
            SetMobyState(object, object[0x94], -1);
        break;
    case 5:
        if (SetFirstPendingFlag(object)) {
            if (WORD(state, 0x714) == -1 || D_0018C0B4 == 0x6F) {
                goto enter_pause;
            }
            object[0xBC] = 0;
            SetControllerSpeedLimits(object, 0.004166667f, 0.125f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != RandomIntBelow(2) + 6)
                StartAnimationBlended(object, RandomIntBelow(2) + 6, 0, 10);
            HALF(state, 0x760) = MeasureMobyAgainstPathEntry(object+0x10, WORD(state, 0x714), 0.0f);
        } else if (object[0xBC] == 0) {
            AdvanceWaypointIndex(object, state+0x700, WORD(state, 0x714), 4.0f, (s16 *)(state+0x760), HALF(state, 0x76C));
            if (D_0018C0B4 == 0x6F || (UHALF(object, 0x96) % 180 == 0 && RandomIntBelow(4) == 0)) {
enter_pause:
                object[0xBC] = 1;
                if (object[0x43] != RandomIntBelow(2) + 4)
                    StartAnimationBlended(object, RandomIntBelow(2)+4, 0, 10);
            }
        } else if (object[0xBC] == 1 && (object[0x60] & 2)) {
            SetMobyState(object, 5, -1);
            SetMobyState(object, 4, -1);
        }
        if (!HALF(state, 0x768)) {
            if (WORD(state, 0x750)) SetMobyState(object, 7, -1);
            else if (WORD(state, 0x744) != -1) SetMobyState(object, 8, -1);
            else SetMobyState(object, 2, -1);
        } else if (WORD(state, 0x754) != -1) {
            if (RunSlotHandler(object+0x10, WORD(state, 0x754), 0) &&
                RunSlotHandler(gHeroPosition, WORD(state, 0x754), 0) &&
                TryUseCounter(WORD(object, 0xB8)))
                SetMobyState(object, 6, -1);
        } else if (TryUseCounter(WORD(object, 0xB8)))
            SetMobyState(object, 6, -1);
        break;
    case 6:
        if (SetFirstPendingFlag(object)) {
            object[0xBC] = 0;
            if (object[0x43] != RandomIntBelow(2)+2)
                StartAnimationBlended(object, RandomIntBelow(2)+2, 0, 10);
        } else if (object[0xBC] == 0 && (object[0x60] & 2)) {
            object[0xBC] = 1;
            SetControllerSpeedLimits(object, 0.004166667f, 0.125f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != RandomIntBelow(2)+6)
                StartAnimationBlended(object, RandomIntBelow(2)+6, 0, 10);
        } else if (object[0xBC] == 1) {
            qcopy(state+0x700, gHeroPosition);
            HALF(state, 0x76A) = 1;
            if (WORD(state, 0x754) != -1 &&
                (!RunSlotHandler(object+0x10, WORD(state, 0x754), 0) ||
                 !RunSlotHandler(gHeroPosition, WORD(state, 0x754), 0))) {
                IncrementCounter(WORD(object, 0xB8));
                SetMobyState(object, 5, -1);
            } else if (DistanceSquaredXY(object+0x10, state+0x700) < FLOAT(state, 0x72C)*FLOAT(state, 0x72C)) {
                object[0xBC] = 2;
                if (object[0x43] != RandomIntBelow(2)+4)
                    StartAnimationBlended(object, RandomIntBelow(2)+4, 0, 10);
            }
        } else if (object[0xBC] == 2 && (object[0x60] & 2))
            SetMobyState(object, 6, -1);
        if (!HALF(state, 0x768)) {
            IncrementCounter(WORD(object, 0xB8));
            if (WORD(state, 0x750)) SetMobyState(object, 7, -1);
            else if (WORD(state, 0x744) != -1) SetMobyState(object, 8, -1);
            else SetMobyState(object, 2, -1);
        }
        break;
    case 7:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2)+6)
                StartAnimationBlended(object, RandomIntBelow(2)+6, 0, 10);
            best = 1000.0f;
            for (listEntry=D_L19_001FB5A0[WORD(state, 0x74C)];
                 (WORD(state, 0x74C)&255)!=255 && WORD(state, 0x74C)<=D_L19_001B2A38 && listEntry &&
                 ((listEntry != 0 && (s16)listEntry[-1]>=0) || listEntry==D_L19_001FB5A0[WORD(state, 0x74C)]); listEntry++) {
                entity=gMobyArray_L19[0]+((*listEntry&0x7FFF)<<8);
                if (!entity) break;
                distance=DistanceSquaredXY(object+0x10, entity+0x10);
                if (distance<best) { PTR(state, 0x750)=entity; best=distance; }
            }
            CopySavedPointBelow(PTR(state, 0x750), position);
            vec_scale_to_length(temp, PTR(state, 0x750)+0xD0, -1.0f);
            FastVecAdd(state+0x700, position, temp);
        }
        HALF(state, 0x76A)=1;
        if (DistanceSquaredXY(object+0x10, state+0x700)<0.25f) {
            if (HALF(state, 0x76E)>=5) MarkMobySpawned(object);
            else { HALF(state, 0x76E)++; ResetToStartAnimation(object); }
        } else if (!IsMobyInStateTwo(PTR(state, 0x750))) {
            CopySavedPointBelow(PTR(state, 0x750), temp);
            if (DistanceSquaredXY(object+0x10, temp)<4.0f)
                EnterHitState(PTR(state, 0x750), 0);
        }
        break;
    case 8:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2)+6)
                StartAnimationBlended(object, RandomIntBelow(2)+6, 0, 10);
            qcopy(state+0x700, ((TargetRecord *)D_L19_001B2B0C[0])[WORD(state, 0x744)].pos);
        }
        HALF(state, 0x76A)=1;
        if (DistanceSquaredXY(object+0x10, state+0x700)<0.25f)
            SetMobyState(object, 2, -1);
        break;
    case 9:
        hit=DispatchActionByKind(object, state+0x60);
        if ((object[0x42]==9 && RandomIntBelow(30)==0) || (hit&1)) {
                if (object[0x94]==6) IncrementCounter(WORD(object, 0xB8));
                SetDeathBits(object, 0, 3);
                SpawnExplosionEffects(object, D_L19_001A8F20, object+0x10, 0.0f, 0.0f, 20, 0, 10,
                             0.0f, 0.0f, 9.0f, 1.0f, -1, 3.0f, 1, 5, -1, 0, 0x810001);
                if (HALF(state, 0x76E)>=4) MarkMobySpawned(object);
                else { HALF(state, 0x76E)++; ResetToStartAnimation(object); }
        } else if (hit&2) SetMobyState(object, object[0x94], 2);
        break;
    }
}
