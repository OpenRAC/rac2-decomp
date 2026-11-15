#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void func_L00_0042BAD0_3(u8 *);

extern void func_L00_0042BFF8_2(u8 *);

extern void func_L00_0042C290_3(u8 *);

extern void func_L00_004380E0_1(u8 *);

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_a2544d80ec96_AbiByte22;

extern void func_00342F70(QwenRecovery_a2544d80ec96_AbiByte22 *owner, const QwenRecovery_a2544d80ec96_AbiByte22 *table);

extern int func_00342BC0(unsigned char *owner);

extern void func_00343058(unsigned char *owner);

typedef int s32;

typedef unsigned int u32;

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_00343200(u8 *menu) {
    func_L00_0042BAD0_3(menu);
    func_L00_0042BAD0_3(menu + 76);
    func_L00_0042BAD0_3(menu + 152);
    func_L00_0042BFF8_2(menu + 228);
    func_L00_0042C290_3(menu + 432);
    func_L00_0042C290_3(menu + 504);
    func_L00_0042C290_3(menu + 576);
    func_L00_004380E0_1(menu + 664);
    return menu;
}

extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern char D_001ADC10[], D_001ADC18[], D_001ADC20[], D_001ADC30[], D_001ADC88[], D_001AE0C0[];
/* sda in this -G0 unit gives the one-instruction (macro) load of D_001A8CFC that retail has; a plain
   declaration splits it into lui/lw with two registers and shifts the register allocation */
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_003361E0(void *, void *, void *);
extern void func_003369A8(void *, void *, void *);
extern void func_00336710(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00336A38(void *, void *);
extern const char *func_00288FB8(int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_003428E0(void *, void *);
extern void func_00343028(void *, float, float);
extern void func_00343038(void *, float);
extern void func_00343798(void *, int);
extern void func_003435B0(u8 *, u32);

/* constructor: stores the owner at +0x28C, allocates the 16-byte position at +0x288 and initialises the
   sub-objects at +0x0, +0x4C, +0x98, +0xE4, +0x1B0, +0x1F8, +0x240 and +0x298 */
void func_00343260(char *self, void *argument)
{
    *(void **)(self + 0x28C) = argument;
    if (argument) {
        int *allocation = ReturnSecondArgument(16, AllocPoolCell(argument));
        *(int **)(self + 0x288) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(self + 0x290) = 1;
    **(float **)(self + 0x288) = 251.0f;
    (*(float **)(self + 0x288))[1] = 210.0f;
    InitDerivedArrays(self, D_001ADC10, argument);
    InitDerivedArrays(self + 0x4C, D_001ADC18, argument);
    InitDerivedArrays(self + 0x98, D_001ADC20, argument);
    InitWidgetDefaults(self + 0x1B0, D_001ADC30, argument);
    InitWidgetDefaults(self + 0x1F8, D_001ADC88, argument);
    InitWidgetDefaults(self + 0x240, D_001ADC88, argument);
    InitDerivedObjectC(self + 0xE4, D_001AE0C0, argument);
    *GetFieldC(self) = 0x60442D00;
    *GetFieldC(self + 0x4C) = 0x60241700;
    *GetFieldC(self + 0x98) = 0x55F0C070;
    *GetFieldC(self + 0x1B0) = 0x80F0F0F0;
    *GetFieldC(self + 0x240) = 0x80F0F0F0;
    *GetFieldC(self + 0x1F8) = 0x80F0F0F0;
    *GetFieldC(self + 0xE4) = 0x80F0F0F0;
    SetFieldAt40(self, D_001A8CFC[0] + 0x8710, 0x99);
    SetFieldAt40(self + 0x4C, D_001A8CFC[0] + 0x8710, 0x9A);
    SetFieldAt40(self + 0x98, D_001A8CFC[0] + 0x8710, 0x9B);
    SetWidgetField40(self + 0x1B0, self + 0x120);
    SetWidgetField40(self + 0x1F8, self + 0x160);
    SetWidgetField40(self + 0x240, (void *)GetLocalizedString(0x2D4F));
    SetMenuTitleMode((u8 *)self, 0);
    SetSecondFloat4(self + 0xE4, 32.0f, 32.0f, 0.0f, 0.0f);
    InitMenuList(self + 0x298, argument);
    SetMenuListSpacing(self + 0x298, 0.0f, 40.0f);
    SetMenuListIconSize(self + 0x298, 32.0f);
    *(int *)(self + 0x330) = 0;
    UpdateItemSelectMenu(self, 0);
}

/* Fills the menu's item list from a table of entries. */
void func_00343538(QwenRecovery_a2544d80ec96_AbiByte22 *menu, const QwenRecovery_a2544d80ec96_AbiByte22 *table)
{
    BuildMenuListIds(menu + 0x298, table);
}


/* Returns the id of the entry selected in the menu's list. */
int func_00343560(unsigned char *owner)
{
    return GetSelectedMenuListId(owner + 0x298);
}

/* Clears the state of the menu's list. */
void func_00343580(unsigned char *owner)
{
    ClearMenuListState(owner + 0x298);
}

/* Measured target: byte-identical across all 27 levels. */
/* Stores an extra value in the menu. */
void func_003435A0(u8 *menu, s32 value) { *(s32 *)(menu + 0x330) = value; }

/* Measured target: byte-identical across all 27 levels. */
/* Returns the extra value stored in the menu. */
s32 func_003435A8(u8 *menu) { return *(s32 *)(menu + 0x330); }

/* Sets which of the four title modes the menu uses and clears a field. */
void func_003435B0(u8 *menu, u32 mode) {
    if (mode < 4) *(u32 *)(menu + 0x294) = mode;
    *(s32 *)(menu + 0x1a0) = 0;
}



/* func_00343638 is matched in 00343200-g8.c (-G8 small data). */
