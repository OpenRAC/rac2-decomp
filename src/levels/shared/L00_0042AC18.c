#include "common.h"
extern char D_00188660[];
extern char D_L00_001B8DC0[];
extern char *D_L00_001B19EC __attribute__((section(".sdata")));
extern float func_00282E48(char *, char *);
extern int func_00282948(int *);
extern int func_L00_0035F640(int, int, char *, int);
extern int func_002A77E0(int);
extern void func_002E59F8(int);
/* Starts a looping sound when the hero comes near this sound emitter and stops it when the hero moves away. */
void func_L00_0042AC18(char *emitter) {
    int *state = *(int **)(emitter + 8);
    unsigned int flags;
    float distance;
    if (state[0] < 0) return;
    distance = fast_vec_dist(gCameraPosition_L00, emitter + 0x40);
    if (distance < *(float *)(emitter + 0xc)) {
        char *soundSlot;
        flags = 0;
        if (*(u8 *)(D_L00_001B19EC + state[0] * 32 + 0x18)) flags |= 4;
        soundSlot = gSoundState + state[4] * 0x70;
        if (*(char **)(soundSlot + 0x8c) == emitter && *(u8 *)(soundSlot + 0x74)) return;
        if (FastFloatHelperD(state + 3)) {
            state[4] = StartEffectFromTableEntry(state[0], flags, emitter, 0x400);
            if (state[2] > 0) state[3] = (int)((state[1] + RandomIntBelow(state[2] - state[1])) * 60.0f);
        }
    } else if (*(float *)(emitter + 0xc) + 1.0f < distance) {
        char *soundSlot;
        int index = state[4];
        if (index != -1) {
            soundSlot = gSoundState + index * 0x70;
            if (*(char **)(soundSlot + 0x8c) == emitter && *(u8 *)(soundSlot + 0x74)) StopSoundVoice(index);
        }
        state[4] = -1;
    }
}
