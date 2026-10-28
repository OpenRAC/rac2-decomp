/* Nonmatching Barlow/Joba racer-group setup: USA808/816 bytes under default
 * -O2 -G0; 0/2 placements. Nine bounded trials: struct/aggregate initialization
 * 764; explicit word-copy/zero loops804; no-split address model808; named member
 * view/reordered copy pointer declarations tied808; no first scheduling tied808;
 * no strength reduction804 with different allocation; -O1 gave800. The new G0
 * macro/explicit GP view gives808; disabling repeated loop optimization ties808.
 * No flags kept.
 * The two 24/16-byte copies remain scalar loops, as measured; the ten group
 * counters are all initialized before lookup, and all21 member entries are read.
 * The remaining miss is owner/array-base lifetime and allocation: retail keeps
 * the object in fp; compiler holds two array bases across inner copies and spills
 * the object. Integer loops and stores also have differing scheduling. Reopen on
 * original object/data view or loop-profile evidence, not synthetic dependencies.
 *
 * Real definitions verified: 2A7820 returns s32, 40A268 returns unsigned int,
 * 4029D8 returns void. Only one declaration per symbol, no aliases/volatile.
 * The controller prefix reaches70C, racer state2D4; neither is allocated here.
 * Table rows are full64-byte delay records; route prefix reads32bytes, with count
 * at0 and duration at1C. GP scalar addresses measured from gp001AEFF0+191C/1938.
 * Current RAC1 Oltanis racer tracking helpers8bbc6b38 and qualified RAC2 reset/
 * racer-state neighbors were inspected; none is an equivalent group initializer.
 */
#include "common.h"

typedef struct { int words[6]; } RacerPathLinks;
typedef struct { int words[4]; } RacerBranchLinks;
typedef struct {
    char reserved00[0x1A8];
    int primaryPath;
    char reserved1AC[0x38];
    int members[21];
    char reserved238[0x4A8];
    RacerPathLinks savedPaths;
    RacerBranchLinks savedBranches;
    int savedPathValue;
} RaceControllerPrefix;
typedef struct {
    char reserved00[0x54];
    RacerPathLinks paths;
    RacerBranchLinks branches;
    int pathValue;
    char reserved80[0x23];
    unsigned char participantCount;
    char reservedA4[0xC0];
    unsigned char *controller;
    char reserved168[0x40];
    int group;
    char reserved1AC[4];
    float initialDelay;
    float routeDuration;
    int value1B8;
    char reserved1BC[8];
    int value1C4, value1C8, value1CC, value1D0;
    float value1D4;
    int value1D8, value1DC, value1E0;
    char reserved1E4[0xEC];
    int value2D0;
} RacerStatePrefix;
typedef struct { int delay; char reserved04[0x3C]; } RaceDelayRow;
typedef struct { int count; char reserved04[0x18]; float duration; } RacePathPrefix;
extern unsigned char *D_L04_001B24DC MACRO_ADDR;
extern RaceDelayRow D_L04_002C63D4[] MACRO_ADDR;
extern RacePathPrefix *D_L04_001FE340[] MACRO_ADDR;
extern int D_L04_001B090C SDATA(D_L04_001B090C) __attribute__((sda));
extern float D_L04_001B0928 SDATA(D_L04_001B0928) __attribute__((sda));
extern int D_001A7B90 MACRO_ADDR;
extern int func_002A7820(int, int);
extern unsigned int func_L04_0040A268(unsigned char *);
extern void func_L04_004029D8(unsigned char *);

void func_L04_0040A628(unsigned char *object)
{
    int groups[10];
    int copied = 0;
    int count = 0;
    int i, remaining;
    int *member;
    RaceControllerPrefix *controller = *(RaceControllerPrefix **)(object + 0x68);
    int *members = controller->members;
    for (remaining = 20, member = members; remaining >= 0; member++, remaining--)
        if (*member != -1)
            count++;
    for (remaining = 9; remaining >= 0; remaining--)
        groups[remaining] = 0;
    for (i = 0; i < 21; i++) {
        if (members[i] != -1) {
            unsigned char *racer = D_L04_001B24DC + (members[i] << 8);
            RacerStatePrefix *state = *(RacerStatePrefix **)(racer + 0x68);
            int group, delay;
            if (!copied) {
                int *destination = controller->savedPaths.words;
                int *source = state->paths.words;
                int words;
                for (words = 5; words >= 0; words--)
                    *destination++ = *source++;
                source = state->branches.words;
                destination = controller->savedBranches.words;
                for (words = 3; words >= 0; words--)
                    *destination++ = *source++;
                controller->savedPathValue = state->pathValue;
                copied = 1;
            }
            state->participantCount = count;
            state->controller = object;
            do {
                group = func_002A7820(0, 9);
            } while (groups[group] >= 4);
            groups[group]++;
            state->group = group + 1;
            delay = D_L04_002C63D4[D_L04_001B090C].delay;
            state->value2D0 = 0;
            if (D_001A7B90) {
                delay = (int)((float)delay * 0.83333337306976318f + 0.010000000707805157f);
                if (D_L04_001B090C == 0)
                    delay += func_L04_0040A268(0) * 100;
                state->initialDelay = (float)delay * 0.0066666668280959129f;
            } else {
                if (D_L04_001B090C == 0)
                    delay += func_L04_0040A268(0) * 120;
                state->initialDelay = (float)delay * 0.0055555561557412148f;
            }
            {
                RacePathPrefix *path = D_L04_001FE340[controller->primaryPath];
                state->routeDuration = path->duration * (float)path->count;
                D_L04_001B0928 = state->routeDuration;
            }
            state->value1D4 = -1.0f;
            state->value1DC = 0;
            state->value1B8 = 0;
            state->value1C4 = -1;
            state->value1C8 = 0;
            state->value1CC = -1;
            state->value1D0 = -1;
            state->value1E0 = 0;
            state->value1D8 = 0;
            racer = D_L04_001B24DC + (members[i] << 8);
            func_L04_004029D8(racer);
            racer = D_L04_001B24DC + (members[i] << 8);
            racer[0x20] = 1;
        }
    }
}
