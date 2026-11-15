#include "common.h"

extern const float ref_L11_00445DF8_00 __attribute__((sda));
extern const s32 ref_L11_00445DF8_01 __attribute__((sda));
extern float ref_L11_00445DF8_02 __attribute__((sda));
extern float ref_L11_00445DF8_03 __attribute__((sda));
extern s32 ref_L11_00445DF8_04 __attribute__((sda));
extern s32 D_001A7A00;
extern char D_001A63A8[];
extern char D_00189E20[];
extern s32 func_00282948(void *);
extern s32 func_002A77E0(s32);
extern int func_L11_00445D28(char *, int);

/* Collects the actions the Joba boss may use now and starts a random one after a random cooldown. */
void func_L11_00445DF8(char *moby, s32 countDelta, float accumDelta, float levelValue) {
    char *state = *(char **)(moby + 0x68);
    char *world = gMusicState;
    char *hero;
    char *hero2;
    s32 id23;
    s32 id24;
    s32 off;
    s32 candidates[12];
    s32 *listPtr;
    s32 numCandidates;
    s32 j;
    s32 k;
    s32 counter;
    float accum;

    if (*(s32 *)(world + 0x68) != 0)
        return;
    if (*(s32 *)(world + 0x24) != -1)
        return;
    if (*(s32 *)(state + 0x190) != 0)
        return;
    numCandidates = 0;
    accum = *(float *)(state + 0x194) + accumDelta;
    counter = *(s32 *)(state + 0x198) + countDelta;
    *(s32 *)(state + 0x198) = counter;
    *(float *)(state + 0x194) = accum;
    if (ref_L11_00445DF8_00 < accum || ref_L11_00445DF8_01 < counter) {
        listPtr = candidates;
        for (j = 0; j < 4; j++) {
            s32 id;

            id = j + 0x14;
            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                listPtr[numCandidates++] = id;
        }
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x194) = 0;
    }
    if (FastFloatHelperD(state + 0x1B0) != 0) {
        *(s32 *)(state + 0x198) = 0;
        *(s32 *)(state + 0x1B0) = 300;
        *(s32 *)(state + 0x194) = 0;
    }
    if (ref_L11_00445DF8_02 < levelValue) {
        listPtr = candidates;
        for (k = 0; k < 2; k++) {
            s32 id = k + 0x12;

            if (*(s16 *)(state + 0x2A0 + id * 2) == 0)
                listPtr[numCandidates++] = id;
        }
    }
    hero = gHeroState;
    if ((float)*(s32 *)(hero + 0x24CC) < (float)D_001A7A00 * ref_L11_00445DF8_03) {
        id23 = 0x18;
        if (*(s16 *)(state + 0x2D0) == 0)
            candidates[numCandidates++] = id23;
    }
    hero2 = gHeroState;
    if (*(s32 *)(hero2 + 0x24CC) <= 0) {
        id24 = RandomIntBelow(2) + 0x19;
        off = id24 * 2;
        if (*(s16 *)(state + off + 0x2A0) == 0)
            candidates[numCandidates++] = id24;
    }
    if (numCandidates != 0) {
        QueueArenaVoiceLine(moby, candidates[RandomIntBelow(numCandidates)]);
        *(s32 *)(state + 0x190) = ref_L11_00445DF8_04 + RandomIntBelow(ref_L11_00445DF8_04);
    }
}
