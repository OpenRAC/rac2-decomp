/* Nonmatching USA612/612 bytes, 0/27 places: five bounded source trials.
 * Initial typed-owner local retained its full pointer and gave604 bytes. Direct
 * canonical hero-field views and a real 32-bit flags local recover the exact
 * instruction count and every operation, but primary animation and duration use
 * s0/s1 instead of retail's s1/s0. Earlier duration initialization schedules the
 * constant before the definition lookup; declaration order and a bank-preserving
 * FP-first helper view tie. Retain the ordinary canonical helper bank spelling.
 * Reopen with original variable/type/lifetime evidence, not register pins.
 *
 * Actual contracts: 2ADEA0 returns int; AB3E0 void; A7820 int; D2168 void with
 * two signed32 GPR parameters plus one float; 310BC8 pointer;310C88/311080 void.
 * Current C definitions and D2168 retail body independently checked. Allocated
 * animation slots are the complete 64 bytes cleared by310C88. Item definitions
 * retain the full 224-byte stride. Matrix storage remains incomplete; no invented
 * small owner or GP bound. The two matrix views advance0xC00 and differ0x600.
 */
/* Adapted from RAC1 start_equipped_item_animation, hero_animation_slots.c at
 * 8bbc6b38 (GPL-3.0); its source credits Lombyte's shared/ui_help_0020c758.c,
 * FUN_L00_0020e4c8. RAC2 offsets, item translation, timing and scratch views
 * are independently measured. No donor assembler aliases are carried over. */
#include "common.h"

typedef struct {
    char reserved00[8];
    float weight;
    char reserved0C[0x2C];
    unsigned char *firstMatrices;
    unsigned char *secondMatrices;
} HeldAnimationSlot;
typedef struct {
    char reserved00[0xE98];
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
    char reserved22BC[0x24B0 - 0x22BC];
    int animation, item;
    char reserved24B8[0x34];
    short suppressed;
} HeldAnimationHeroPrefix;
typedef struct {
    char reserved00[0x1C];
    int category;
    char reserved20[8];
    int primaryAnimation, heldAnimation, alternateAnimation, flags;
    char reserved38[0xA8];
} HeldAnimationItem;
extern HeldAnimationHeroPrefix D_00189E20;
extern unsigned char D_00139568[];
extern HeldAnimationItem D_L00_00262570[];
/* Complete storage stays opaque; the two iteration views advance by0xC00,
 * and each pair of matrix workspaces begins0x600 bytes apart. */
extern unsigned char D_L00_001B7400[] __attribute__((aligned(16)));
extern int D_L00_001A7D00[] SDATA(D_L00_001A7D00) __attribute__((sda));
extern int func_L00_002ADEA0(int);
extern void func_L00_002AB3E0(void);
extern int func_002A7820(int, int);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_00310C88(void *, HeldAnimationSlot **);
extern HeldAnimationSlot *func_L00_00310BC8(void *, int);
extern void func_L00_00311080(void *, HeldAnimationSlot *, int, int, int, int);

void func_L00_002AF568(void)
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
        duration = 11;
    else if (primary == 0x36 || item == 0x24 || item == 0x1A)
        duration = 2;
    else if (item == 0x1E || item == 0x19 || item == 0x46)
        duration = 5;
    blendDuration = duration;
    if (blendDuration < 0)
        blendDuration = 11;
    func_L00_002AB3E0();
    D_00189E20.idleTimer = func_002A7820(90, 120);
    if (D_00189E20.controlMode == 0 && D_00189E20.suppressed == 0) {
        D_00189E20.animation = primary;
        func_L00_002D2168(primary, 0, (float)duration);
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
            slot->firstMatrices = D_L00_001B7400 + i * 0xC00;
            slot->secondMatrices = D_L00_001B7400 + 0x600 + i * 0xC00;
            func_L00_00311080(D_00189E20.moby, slot, D_00189E20.animation, 0, blendDuration, 1);
        }
    }
}
