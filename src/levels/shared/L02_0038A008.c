/* Own unit for -mno-split-addresses. Case 2 keeps the three-way dispatch. State 1's two arms
   each make the calls: jump2 merges them from the first jal, which leaves the arguments
   before the completion-byte store and the jal's slot empty. */
#include "common.h"

extern int D_001A79F0[] __attribute__((sda));
extern char *D_L02_001B35A8[] __attribute__((sda));
extern int D_L02_001AEC78 SDATA(D_L02_001AEC78);
extern int D_L02_001B30C8[] __attribute__((sda));
extern unsigned char D_001A7A6E __attribute__((nosda));
extern unsigned char D_001A7A75 __attribute__((nosda));
extern int D_L02_001A903C __attribute__((nosda));
extern void func_002A7750(void *, int, int);
extern void func_002E5E58(int, int, int);
extern void func_002B0A18(int, int);

/* Update for the moby class 4815 trigger. It counts certain enemies in the level, then fires a one-time event when the count drops low enough. */
void func_L02_0038A008(unsigned char *object) {
    int state = object[0x20];
    switch (state) {
    case 2:
        break;
    case 0:
        object[0x30] = 0xFF;
        if (gCurrentMapIndex[0] == 2) {
            char *entry;
            int kind;
            for (entry = D_L02_001B35A8[0]; entry; entry = *(char **)(entry + 0x28)) {
                kind = *(short *)(entry + 0xAA);
                if ((kind == 0xA9C /* Slot Machine */ || kind == 0xD0D /* moby class 3341 */ || kind == 0xAA4 /* moby class 2724 */ || kind == 0xE93 /* moby class 3731 */ || kind == 0x1259 /* moby class 4697 */) && *(float *)(entry + 0x18) < 400.0f)
                    ++gHoveringObjectCount;
            }
        } else if (gCurrentMapIndex[0] == 3) {
            char *entry;
            int kind;
            int remaining;
            entry = D_L02_001B35A8[0];
            if (entry) {
                remaining = gHoveringObjectCount;
                do {
                    kind = *(unsigned short *)(entry + 0xAA);
                    if ((unsigned)(kind - 0xF37 /* moby class 3895 */) < 2 || (short)kind == 0xF3E /* moby class 3902 */)
                        ++remaining;
                    entry = *(char **)(entry + 0x28);
                } while (entry);
                gHoveringObjectCount = remaining;
            }
        }
        SetMobyState(object, 1, -1);
        break;
    case 1:
        if (gCurrentMapIndex[0] == 2) {
            if (gFrameCounter_L02[0] == 2) gHoveringObjectCount = 0x71;
            if (gHoveringObjectCount >= 11 || D_001A7A6E) return;
            D_001A7A6E = state;
            PlaySoundFromGlobalBank(1, 0, 0);
            SetEntryValueByIndex(0x1233, -1);
            D_L02_001A903C = state;
        } else if (gCurrentMapIndex[0] == 3) {
            if (gFrameCounter_L02[0] == 2) gHoveringObjectCount = 0x70;
            if (gHoveringObjectCount >= 12 || D_001A7A75) return;
            D_001A7A75 = state;
            PlaySoundFromGlobalBank(1, 0, 0);
            SetEntryValueByIndex(0x1233, -1);
            D_L02_001A903C = state;
        }
        break;
    }
}
