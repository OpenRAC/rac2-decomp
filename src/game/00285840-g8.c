#include "include_asm.h"
#include "names.h"

/* -G8 sibling for src/game/00285840.c: func_002858C0 stores through $gp into the
   small-data word D_001A8A5C, which only comes out gp-relative in a file built
   with -G8. */

typedef int s32;
typedef short s16;

typedef struct {
    char reserved00[0x40];
    s32 mode;
    char reserved44[0x10];
    s32 modeArg;
    s32 field58;
    s32 field5C[4];
    s32 field6C[4];
    s16 field7C;
    s16 field7E;
    s32 field80;
    char reserved84[4];
    s32 field88;
} Limits_2858C0;

extern Limits_2858C0 D_001BAC80;
extern s32 D_0013955C[];
extern s32 D_001A8BB0;
extern s32 D_001A8A5C __attribute__((sda));

extern s32 func_002B4BE8(void);
extern void func_00132AF8(s32);
extern s32 func_00287E48(void);
extern void func_002B72E8(s32);
extern int func_002E5E58(int, unsigned int, void *);

/* Switches the menu to a new mode. It clears the menu counters, plays the menu sound and may start a pause. */
void func_002858C0(s32 newMode, s32 modeArg)
{
    s32 i;

    D_001A8A5C = newMode;
    if (newMode == 5) {
        gModalState.field80 = D_0013955C[0];
    } else {
        gModalState.field80 = 0;
    }
    gModalState.modeArg = modeArg;
    gModalState.mode = newMode;
    gModalState.field7C = 0;
    gModalState.field7E = 0;
    gModalState.field58 = 0;
    gModalState.field88 = (GetTopOfModeStack() != 3);
    if (gCurrentGameMode != 3) {
        SendSoundCommand22(0x5D);
        if (IsMenuStateSeven() == 0) {
            music_Pause(0);
        }
    }
    for (i = 0; i < 4; i++) {
        gModalState.field5C[i] = 0;
        gModalState.field6C[i] = 0;
    }
    if (newMode == 10) {
        PlaySoundFromGlobalBank(0x12, 0, 0);
    }
}
