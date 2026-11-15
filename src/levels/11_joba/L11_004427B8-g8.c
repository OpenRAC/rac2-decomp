#include "include_asm.h"
#include "names.h"

extern unsigned char D_001395B8[0x100];

extern int D_001A7A08[2];

extern int D_001A79F8;

extern unsigned char D_001A7A60 __attribute__((sda));

extern int D_001A903C;

typedef struct {
    char pad0[0x22C8];
    int w22C8;
} L11_004427B8_Hero;

extern L11_004427B8_Hero D_00189E20;

extern int func_L11_0043E108(int);

extern int func_L11_00445D28(char *, int);

extern void func_00288308(int);

extern void func_002AD860(int);

extern int func_002A77E0(int);

extern int func_L02_003FCF08(int);

extern int func_L02_003FCDF8(int);

extern void func_L00_0030C7F8(int);

extern int func_002E5E58(int, unsigned int, void *);

extern void func_002B0A18(int, int);

extern void func_0029B3E0(int, int);

/* Starts the next scene for a1 and counts the entry, as func_L02_003FCCA0 does in level 2. For
   a1 == 0 and a1 == 1 with no count yet it plays scene 1 or 3 and keeps the hero's word at
   +0x22C8; otherwise it takes scene func_002A77E0(2) + 0x1E, adds the two scores and starts
   func_L00_0030C7F8(0x168). For a1 == 10
   with the once-only byte clear it sets it, starts func_002E5E58 and raises D_001A903C. */
/* Starts the scene that follows a finished challenge and records that the challenge was done. */
void func_L11_004427B8(char *obj, int challengeIndex) {
    char *state = *(char **)(obj + 0x68);
    int saved;
    int score;

    if (challengeIndex == 0 && D_001395B8[GetChallengeFlagIndex(0)] == 0) {
        saved = gHeroState.w22C8;
        QueueArenaVoiceLine(obj, 1);
        UnlockHelpEntry(0x13);
        HandleRequestSlotState(0x13);
        gHeroState.w22C8 = saved;
    } else if (challengeIndex == 1 && D_001395B8[GetChallengeFlagIndex(1)] == 0) {
        saved = gHeroState.w22C8;
        QueueArenaVoiceLine(obj, 3);
        UnlockHelpEntry(0x33);
        gHeroState.w22C8 = saved;
    } else {
        QueueArenaVoiceLine(obj, RandomIntBelow(2) + 0x1E);
        D_001A7A08[1] = D_001A7A08[1] + ComputeScaledEntryValueShifted(challengeIndex);
        score = ComputeScaledEntryValue(challengeIndex);
        *(int *)(state + 0x1E0) = score;
        gPlayerBolts = gPlayerBolts + score;
        CallLoadedModuleHandlerWithArg_0034B000(0x168);
    }
    if (challengeIndex == 10 && D_001A7A60 == 0) {
        D_001A7A60 = 1;
        PlaySoundFromGlobalBank(1, 0, 0);
        SetEntryValueByIndex(0x1233, -1);
        D_001A903C = 1;
    }
    D_001395B8[GetChallengeFlagIndex(challengeIndex)] += 1;
    MemcardSave(0, -1);
}
