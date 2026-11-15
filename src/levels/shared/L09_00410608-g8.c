#include "common.h"

extern char D_00188660[];
typedef struct { char pad[0x33c]; char *object; int active; } Player10608;
extern Player10608 D_00189E20;
extern char D_L09_001B17F8[];
extern char *D_L09_001B294C;
extern int D_L09_001BFE58 NOT_SDA;
extern float D_L09_001B17F4 __attribute__((sda));
extern void func_0026FEB8(void *, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern float func_00282E48(const void *, const void *);
extern int func_00277258(void *, int, void *, float);
extern void func_L09_00410B40(void *);
extern void func_L09_00410BC8(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
#define WORD(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define BYTE(p,o) (*(u8 *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad[0x74]; u8 active; char gap[0x13]; char *owner; } SoundSlot;
#define SLOT(i) (D_00188660 + (i)*0x70)
#define SOUND_SLOT(i) ((SoundSlot *)SLOT(i))

/* Moves to the selected waypoint while ridden, then returns to its starting position. */
/* Update for moby class 3716, a moving platform. (Moves to the chosen waypoint while ridden and returns afterwards.) */
void func_L09_00410608(char *object)
{
    float old_position[4] __attribute__((aligned(16)));
    float old_rotation[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *slot;
    char *state = *(char **)(object + 0x68);
    qcopy(old_position, object + 0x10);
    qcopy(old_rotation, object + 0xf0);
    switch (BYTE(object,0x20)) {
    case 0:
        *(Quad *)(state+0x80) = *(Quad *)(object+0x10);
        FLOAT(state,0x64) *= 0.0166666675f;
        FLOAT(object,0x2c) *= 1.75f;
        if (WORD(state,0x60) == -1)
            STUB_printf(D_L09_001B17F8, HALF(object,0xaa), HALF(object,0xb2));
        WORD(state,0x6c) = -1;
        SetMobyState(object,1,-1);
        break;
    case 1:
        if (SetFirstPendingFlag(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    StopSoundVoice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(1,4,object);
        if (WORD(state,0x60) != -1 && gHeroState.object==object && gHeroState.active)
            SetMobyState(object,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    StopSoundVoice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(0,4,object);
        FastVecSub(delta,D_L09_001B294C+WORD(state,0x60)*0x80+0x30,object+0x10);
        vec_scale_to_length(delta,delta,FLOAT(state,0x64));
        FastVecAdd(object+0x10,object+0x10,delta);
        if (fast_vec_dist(object+0x10,D_L09_001B294C+WORD(state,0x60)*0x80+0x30)<=0.88f)
            SetMobyState(object,3,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    StopSoundVoice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(1,4,object);
        if (gHeroState.object!=object)
            SetMobyState(object,4,-1);
        break;
    case 4: {
        if (SetFirstPendingFlag(object)) {
            if (WORD(state,0x6c) != -1) {
                if (SOUND_SLOT(WORD(state,0x6c))->owner == object && SOUND_SLOT(WORD(state,0x6c))->active)
                    StopSoundVoice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        if (TestPointAgainstCollision(object+0x10,0x10,object,D_L09_001B17F4) && D_L09_001BFE58)
            break;
        if (SOUND_SLOT(WORD(state,0x6c))->owner != object || !SOUND_SLOT(WORD(state,0x6c))->active)
            WORD(state,0x6c) = PlayMobySound(0,4,object);
        FastVecSub(delta,state+0x80,object+0x10);
        vec_scale_to_length(delta,delta,FLOAT(state,0x64));
        FastVecAdd(object+0x10,object+0x10,delta);
        if (fast_vec_dist(object+0x10,state+0x80)<=0.88f)
            SetMobyState(object,1,-1);
        break;
    }
    }
    TurnPartsToTargetAngles(object);
    SpawnBelowObjectParticles(object);
    FastVecSub(delta,object+0x10,old_position);
    CombineTransformsAndStore(state+0x20,delta,old_rotation,object+0xf0);
}
