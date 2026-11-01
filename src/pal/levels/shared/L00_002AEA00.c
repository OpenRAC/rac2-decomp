#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002AEC50);



extern void *func_L00_002A4E48(void *p);
extern void func_L00_002D2168(void *a, void *b, float f);
extern unsigned char D_00189E20_26[];

/* guards a fixed data block on an enable byte, takes one of two early exits (setting a pending word and a flag, or skipping), calls two leaves with a scaled value when a byte field matches a threshold word, then clears a byte pair of the block */
void func_PAL_L00_002AF6C0(void)
{
    if (D_00189E20_26[8888] == 0)
        return;
    if (*(int *)(D_00189E20_26 + 3736) != 0) {
        *(int *)(D_00189E20_26 + 3748) = 1;
    } else if (*(int *)(D_00189E20_26 + 8852) == 0) {
        if (*(unsigned char *)(*(int *)(D_00189E20_26 + 8848) + 67) == *(int *)(D_00189E20_26 + 9392)) {
            func_L00_002D2168(func_L00_002A4E48(0), 0, -2.0f);
        }
    }
    D_00189E20_26[8888] = 0;
    D_00189E20_26[8890] = 0;
}

typedef int HeldQuad __attribute__((mode(TI)));
typedef union {
    HeldQuad q;
    float f[4];
} HeldVector;
typedef struct {
    char reserved00[5];
    unsigned char state;             
    char reserved06[2];
    float weight;
    char reserved0C[0x17];
    unsigned char animation;
    int reserved24;
    int loopCount;
    char reserved2C[0xC];
    unsigned char *firstMatrices;
    unsigned char *secondMatrices;
} HeldAnimationSlot;
typedef struct {
    char reserved00[0x80];
    float position[4];
    HeldVector rotation;
    char reservedA0[0x64C - 0xA0];
    float railYaw, railPitch;
    char reserved654[0x6A0 - 0x654];
    float railLean;
    char reserved6A4[4];
    float *lookTarget;               
    char reserved6AC[0x730 - 0x6AC];
    HeldVector basis[3];
    HeldVector facing;
    HeldVector pose;
    char reserved780[0xE98 - 0x780];
    HeldAnimationSlot *slots[2];
    char reservedEA0[4];
    int cancel;
    char reservedEA8[0x11A0 - 0xEA8];
    int idleTimer;
    char reserved11A4[0x2290 - 0x11A4];
    unsigned char *moby;
    char reserved2294[8];
    int controlMode;
    char reserved22A0[0x18];
    unsigned char active, reserved22B9, flags, dual;
    char reserved22BC[7];
    unsigned char transformed;
    char reserved22C4[0x24B0 - 0x22C4];
    int animation, item;
    char reserved24B8[0x34];
    short suppressed;
} HeldAnimationHero;
typedef struct {
    char reserved00[0x1C];
    int category;
    char reserved20[8];
    int primaryAnimation, heldAnimation, alternateAnimation, flags;
    char reserved38[0xA8];
} HeldAnimationItem;
typedef struct {
    unsigned char first[0x600];
    unsigned char second[0x600];
} HeldMatrixBuffers;
extern HeldAnimationHero D_00189E20;
extern unsigned char D_00139568[];
extern HeldAnimationItem D_L00_00262570[];
extern HeldMatrixBuffers D_L00_001B7400[];
extern int func_L00_002ADEA0(int);
extern int func_L00_002D4040(int);
extern void func_002AA2E8(float *, float, float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern void func_002833F0(void *, void *);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_00310C88(void *, HeldAnimationSlot **);
extern HeldAnimationSlot *func_L00_00310BC8(void *, int);
extern void func_L00_00310D30(void *, HeldAnimationSlot *);
extern void func_L00_00311080(void *, HeldAnimationSlot *, int, int, int, int);

/* advances the held-item slots (following the item's held animation, fading the weight in, or out
 * after a cancel and releasing the slot at zero), then rebuilds the hero's held-pose basis: from
 * the rail angles or look target in control mode 15, otherwise from the moby's matrix */
void func_PAL_L00_002AF750(void)
{
    HeldAnimationHero *owner = &D_00189E20;
    int i;

    if (owner->active != 0 && owner->flags != 0) {
        if (func_L00_002D4040(-1) == 0)
            func_PAL_L00_002AF6C0();
    }
    for (i = 0; i < 2; i++) {
        HeldAnimationHero *slotOwner = &D_00189E20;
        HeldAnimationSlot **slot = slotOwner->slots + i;
        HeldAnimationSlot **current;
        int item, animation;

        if (*slot == 0)
            continue;
        (*slot)->firstMatrices = D_L00_001B7400[i].first;
        (*slot)->secondMatrices = D_L00_001B7400[i].second;
        item = func_L00_002ADEA0(0);
        if (item == slotOwner->item) {
            HeldAnimationItem *definition = &D_L00_00262570[D_00139568[item]];
            animation = definition->heldAnimation;
            if (slotOwner->controlMode == 12)
                animation = definition->alternateAnimation;
            if (animation != -1 && (*slot)->animation != animation) {
                slotOwner->animation = animation;
                func_L00_00311080(slotOwner->moby, *slot, slotOwner->animation, 0, 7, 1);
            }
        }
        current = slotOwner->slots + i;
        {
            HeldAnimationHero *poseOwner = &D_00189E20;
            func_L00_00310D30(poseOwner->moby, *current);
            if (poseOwner->cancel != 0) {
                if (poseOwner->cancel == 2)
                    func_002AA2E8(&(*current)->weight, 0.0f, 0.3f);
                else
                    func_002AA2E8(&(*current)->weight, 0.0f, 0.08400001f);
                owner = &D_00189E20;
                if ((*slot)->weight != 0.0f)
                    continue;
                func_L00_00310C88(owner->moby, slot);
                return;
            } else {
                func_002AA2E8(&(*current)->weight, 1.0f, 0.24000001f);
                if (((*current)->state & 2) == 0)
                    continue;
                if (poseOwner->flags == 0) {
                    poseOwner->cancel = 1;
                    (*current)->loopCount = 0;
                    poseOwner->active = 0;
                    return;
                }
            }
        }
    }
    {
        HeldAnimationHero *poseOwner = &D_00189E20;
        if (poseOwner->controlMode == 15) {
            float *target = poseOwner->lookTarget;
            if (target != 0) {
                poseOwner->pose.q = poseOwner->rotation.q;
                poseOwner->pose.f[2] = func_00283248(target[4] - poseOwner->position[0],
                                                     target[5] - poseOwner->position[1]);
                poseOwner->pose.f[1] = -poseOwner->railPitch;
            } else {
                poseOwner->pose.q = poseOwner->rotation.q;
                poseOwner->pose.f[2] = func_00283B98(poseOwner->railYaw, poseOwner->railLean);
                poseOwner->pose.f[1] = -poseOwner->railPitch;
            }
            {
                char *basis = (char *)D_00189E20.basis;
                func_002833F0(basis, basis + 0x40);
                func_00282C88(basis + 0x30);
                *(float *)(basis + 0x30) = 1.0f;
                func_00283098(basis + 0x30, basis + 0x30, basis);
            }
        } else {
            unsigned char *moby = poseOwner->moby;
            HeldVector *basis = poseOwner->basis;
            float *offset = poseOwner->facing.f;
            basis[0].q = *(HeldQuad *)(moby + 0xC0);
            basis[1].q = *(HeldQuad *)(moby + 0xD0);
            basis[2].q = *(HeldQuad *)(moby + 0xE0);
            func_00282C88(offset);
            poseOwner->facing.f[0] = 1.0f;
            func_00283098(offset, offset, basis);
            poseOwner->pose.q = poseOwner->rotation.q;
            if (poseOwner->transformed == 0)
                poseOwner->pose.f[2] = func_00283B98(poseOwner->pose.f[2], 0.0f);
        }
    }
}

