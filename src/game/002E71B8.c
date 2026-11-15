#include "include_asm.h"
#include "common.h"
typedef struct { char pad00[0x20]; short active; short slot; } Sel52C00;

extern Sel52C00 D_00152C00;

extern float ref_L00_00360ED0_00 MACRO_ADDR;
extern int ref_L00_00360ED0_01 MACRO_ADDR;
extern int ref_L00_00360ED0_02 __attribute__((sda));

typedef struct { char pad00[0x0C]; int rangeStart; int rangeEnd; } World2E71B8;

typedef struct {
    char pad00[0x34];
    int frame;
    char pad38[0x34];
    int startWindow;
    int destinationWindow;
} State2E71B8;

extern World2E71B8 ref_L00_00360ED0_03;
extern State2E71B8 ref_L00_00360ED0_04;

extern void func_002FC138(void);
extern void func_002E6D88(int);

/* Starts a scene: resets the fade, sets up its memory block and marks the scene as running. */
void func_002E71B8(void)
{
    int base;

    ref_L00_00360ED0_00 = 1.0f;
    gHeroMoby_00152C00.active = 0;
    gHeroMoby_00152C00.slot = -1;
    SelectPacketBufferSetup();

    base = ref_L00_00360ED0_01 - 0x60000;
    ref_L00_00360ED0_04.startWindow = ref_L00_00360ED0_03.rangeStart + base;
    ref_L00_00360ED0_04.destinationWindow = ref_L00_00360ED0_03.rangeEnd + base;
    ref_L00_00360ED0_02 = base;
    StartTransitionScene(3);
    ref_L00_00360ED0_04.frame = 1;
}
