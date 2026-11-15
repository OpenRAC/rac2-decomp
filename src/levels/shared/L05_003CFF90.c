#include "common.h"

/* The fields this update uses in the object's own state and in the block func_002ED688 returns. */
typedef struct {
    char pad000[0x1B0];
    int target;                 /* 0x1B0: index of the object it aims at, or -1 */
    int hasCallback;            /* 0x1B4 */
    char block1B8[4];           /* 0x1B8 */
    int loopSound;              /* 0x1BC */
    int nearSound;              /* 0x1C0 */
} ObjVars003CFF90;

typedef struct {
    char pad000[0x104];
    int flag104;                /* 0x104 */
    int flag108;                /* 0x108 */
    char pad10C[4];
    int state110;               /* 0x110 */
    char pad114[8];
    int hasTarget;              /* 0x11C */
    char *targetObject;         /* 0x120 */
} ObjCommon003CFF90;

typedef struct {
    char pad00[0x74];
    unsigned char live;         /* 0x74 */
    char pad75[0x13];
    char *owner;                /* 0x88 */
    char pad8C[0x54];
} SoundSlot003CFF90;

extern ObjCommon003CFF90 *func_002ED688(char *);
extern int func_L00_00367720(void);
extern void func_L05_003D0320(char *);
extern void func_00282C88(void *);
extern void func_L05_00379E60(char *, void *, int, int);
extern void func_L05_003D02C8(void);
extern void func_L05_0037C160(char *);
extern int func_L05_0037B538(char *, int, int, int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_L05_0037B948(char *, int, float);
extern int D_L05_001B251C __attribute__((sda));
extern float func_00282E48(void *, void *);
extern int func_002A77E0(int);
extern void func_L05_003D0420(char *);
extern int func_L05_0037B888(char *);
extern void func_L05_0037B6D0(char *);
extern int func_00282948(void *);
extern int func_00283DB8(void *, float);
extern void func_L05_003D0538(char *);
extern char D_00188660[];

/* The object's three-state update. State 1 also aims at a target from the object table; states
   1 and 2 restart the looping sound when its slot no longer belongs to this object. */
/* Runs a creature's three states, aiming at its target, playing its sounds and attacking when
   it is ready. */
void func_L05_003CFF90(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    ObjVars003CFF90 *s = *(ObjVars003CFF90 **)(obj + 0x68);
    ObjCommon003CFF90 *p = GetMobyMotionData(obj);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned char *)(obj + 0x30) = 255;
        if (!GetStoredPointerValue()) return;
        InitObjectReachAndPosition(obj);
        ClearVector128(a);
        if (s->hasCallback) AppendLevelObject(obj, func_L05_003D02C8, 0, 0);
        return;
    case 1:
        UpdateObjectMovementState(obj);
        if (ProcessObjectCollisionHit(obj, 0, 0, 0) == 1) PlaySoundFromClassBank(1, 0, obj, 0x957);
        CheckPlayerInViewAndRange(obj, 0, 176.0f);
        if (p->state110 == 1) {
            if (s->target != -1) {
                char *target;
                p->hasTarget = 1;
                target = (char *)(D_L05_001B251C + (s->target << 8));
                p->targetObject = target;
                if (fast_vec_dist(target + 0x10, obj + 0x10) < 10.0f) {
                    SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(gSoundState + s->nearSound * 0x70);
                    if ((sound->owner != obj || sound->live == 0) && RandomIntBelow(400) == 0)
                        s->nearSound = PlaySoundFromClassBank(14, 0, obj, 0xFBF);
                }
            }
            if (p->flag108 && p->flag104) SpawnObjectEffectOnce(obj);
            if (CanObjectTakeNextStep(obj)) StartObjectMovementState(obj);
            FastFloatHelperD(s->block1B8);
            qcopy(b, obj + 0x10);
            b[3] = *(float *)(obj + 0xC) * 0.0009765599970705807f;
            if (FastMathHelperA(b, 100.0f) != -1) func_L05_003D0538(obj);
        }
        break;
    case 2:
        UpdateObjectMovementState(obj);
        if (ProcessObjectCollisionHit(obj, 0, 0, 0) == 1) PlaySoundFromClassBank(1, 0, obj, 0x957);
        CheckPlayerInViewAndRange(obj, 0, 176.0f);
        if (p->state110 == 1) {
            if (p->flag104) SpawnObjectEffectOnce(obj);
            if (CanObjectTakeNextStep(obj)) StartObjectMovementState(obj);
            FastFloatHelperD(s->block1B8);
            func_L05_003D0538(obj);
        }
        break;
    }
    {
        SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(gSoundState + s->loopSound * 0x70);
        if (sound->owner != obj || sound->live == 0)
            s->loopSound = PlaySoundFromClassBank(3, 6, obj, 0x957);
    }
}
