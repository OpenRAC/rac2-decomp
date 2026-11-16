#include "include_asm.h"
#include "names.h"

extern void set_hero_animation_pal(void *a, void *b, float f);
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
extern HeldAnimationHero g_hero_state;
extern unsigned char g_item_slot_to_record[];
extern HeldAnimationItem g_weapon_l00_table[];
extern HeldMatrixBuffers g_item_matrix_buffers[];
extern int D_L00_001A7D00[2] __asm__("D_L00_001A7D00__gp") __attribute__((section(".sdata")));
extern int hero_slot_item_id(int);
extern void hero_clear_slot_records(void);
extern int math_random_int_range(int, int);
extern void release_moby_animation_slot(void *, HeldAnimationSlot **);
extern HeldAnimationSlot *allocate_moby_animation_slot(void *, int);
extern void initialize_moby_animation_blend(void *, HeldAnimationSlot *, int, int, int, int);

/* func_L00_002AF3D8 is defined in a sibling unit. */

/* starts the equipped item's animation: the hero's own animation in the default control mode,
 * otherwise a held animation in one slot (two for a dual item) with its matrix workspaces */
void start_equipped_item_animation_pal(void)
{
    int duration, item, primary, held, blendDuration, i;
    HeldAnimationSlot *slot;
    HeldAnimationItem *definition;

    item = hero_slot_item_id(0);
    if (item == -1 || item == 0)
        return;
    g_hero_state.item = item;
    definition = &g_weapon_l00_table[g_item_slot_to_record[item]];
    primary = definition->primaryAnimation;
    held = definition->heldAnimation;
    if (g_hero_state.controlMode == 12)
        held = definition->alternateAnimation;
    g_hero_state.active = 1;
    { int flags = definition->flags; g_hero_state.flags = flags; }
    duration = -1;
    if (g_weapon_l00_table[g_item_slot_to_record[item]].category == 0)
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
    hero_clear_slot_records();
    g_hero_state.idleTimer = math_random_int_range(75, 100);
    if (g_hero_state.controlMode == 0 && g_hero_state.suppressed == 0) {
        g_hero_state.animation = primary;
        set_hero_animation_pal((void *)primary, 0, (float)duration);
        return;
    }
    if (held == -1)
        return;
    for (i = 0; i < 2 && (i != 1 || g_hero_state.dual == 2); i++) {
        if (g_hero_state.slots[i])
            release_moby_animation_slot(g_hero_state.moby, &g_hero_state.slots[i]);
        slot = allocate_moby_animation_slot(g_hero_state.moby, g_hero_item_anim_ids[i]);
        g_hero_state.slots[i] = slot;
        if (slot) {
            g_hero_state.animation = held;
            g_hero_state.cancel = 0;
            slot->weight = 1.0f;
            slot->firstMatrices = g_item_matrix_buffers[i].first;
            slot->secondMatrices = g_item_matrix_buffers[i].second;
            initialize_moby_animation_blend(g_hero_state.moby, slot, g_hero_state.animation, 0, blendDuration, 1);
        }
    }
}
