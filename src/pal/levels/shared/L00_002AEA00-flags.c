#include "include_asm.h"

extern void func_PAL_L00_002D2668(void *a, void *b, float f);
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
extern int D_L00_001A7D00[2] __asm__("D_L00_001A7D00__gp") __attribute__((section(".sdata")));
extern int func_L00_002ADEA0(int);
extern void func_L00_002AB3E0(void);
extern int func_002A7820(int, int);
extern void func_L00_00310C88(void *, HeldAnimationSlot **);
extern HeldAnimationSlot *func_L00_00310BC8(void *, int);
extern void func_L00_00311080(void *, HeldAnimationSlot *, int, int, int, int);

/* func_L00_002AF3D8 is defined in a sibling unit. */

/* starts the equipped item's animation: the hero's own animation in the default control mode,
 * otherwise a held animation in one slot (two for a dual item) with its matrix workspaces */
void func_PAL_L00_002AF458(void)
{
    int duration, item, primary, held, blendDuration, i;
    HeldAnimationSlot *slot;
    HeldAnimationItem *definition;

    item = func_L00_002ADEA0(0);
    if (item == -1 || item == 0)
        return;
    D_00189E20.item = item;
    definition = &D_L00_00262570[D_00139568[item]];
    primary = definition->primaryAnimation;
    held = definition->heldAnimation;
    if (D_00189E20.controlMode == 12)
        held = definition->alternateAnimation;
    D_00189E20.active = 1;
    { int flags = definition->flags; D_00189E20.flags = flags; }
    duration = -1;
    if (D_L00_00262570[D_00139568[item]].category == 0)
        duration = 9;
    else if (primary == 0x36)
        duration = 2;
    else if (item == 0x24 || item == 0x1A)
        duration = 2;
    else if (item == 0x1E || item == 0x19 || item == 0x46)
        duration = 4;
    blendDuration = duration;
    if (blendDuration < 0)
        blendDuration = 9;
    func_L00_002AB3E0();
    D_00189E20.idleTimer = func_002A7820(75, 100);
    if (D_00189E20.controlMode == 0 && D_00189E20.suppressed == 0) {
        D_00189E20.animation = primary;
        func_PAL_L00_002D2668((void *)primary, 0, (float)duration);
        return;
    }
    if (held == -1)
        return;
    for (i = 0; i < 2 && (i != 1 || D_00189E20.dual == 2); i++) {
        if (D_00189E20.slots[i])
            func_L00_00310C88(D_00189E20.moby, &D_00189E20.slots[i]);
        slot = func_L00_00310BC8(D_00189E20.moby, D_L00_001A7D00[i]);
        D_00189E20.slots[i] = slot;
        if (slot) {
            D_00189E20.animation = held;
            D_00189E20.cancel = 0;
            slot->weight = 1.0f;
            slot->firstMatrices = D_L00_001B7400[i].first;
            slot->secondMatrices = D_L00_001B7400[i].second;
            func_L00_00311080(D_00189E20.moby, slot, D_00189E20.animation, 0, blendDuration, 1);
        }
    }
}
