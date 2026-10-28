/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/game/00345B78-g8.c
 * Game profile: -O2 -G8 -ffunction-sections
 * Compiled/retail bytes: 472/476. US: 0/28; US2: 0/28; PAL: 0/28.
 * Residual and reopening condition: Failure-branch sound-constant speculation and global store addressing remain different. Distinct final-selection lifetime recovered the saved-register allocation; nested branches, direct failure labels and fno-sched-spec did not close it.
 * This unit also retains func_00345D58 (528/536 bytes; no matching placements).
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"

extern int func_002E5E58(int index, int value, void *object);
extern short D_001AA7D8[][5];
extern short D_001AA898[][5];
extern unsigned char D_001A7AF8[];
extern unsigned char D_00139568[];
typedef struct { char prefix[6]; short value; } SelectionRecord;
extern char D_00239BA0[];
extern int D_001F288C __attribute__((nosda));
extern int D_001F2884 __attribute__((nosda));
extern int D_001ADB10 __attribute__((sda));

void func_00345B78(char *object, unsigned int buttons)
{
    int selected;
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        (*(int *)(object + 0x48C))++;
        *(int *)(object + 0x490) = 1;
        *(int *)(object + 0x498) = 0;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        (*(int *)(object + 0x48C))++;
        *(int *)(object + 0x498) = 1;
        *(int *)(object + 0x490) = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--(*(int *)(object + 0x48C)) < 0)
            *(int *)(object + 0x48C) = 1;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++(*(int *)(object + 0x48C)) >= 2)
            *(int *)(object + 0x48C) = 0;
    } else if (buttons & 0x40) {
        selected = D_001AA7D8[*(int *)(object + 0x48C)][3];
        if (selected == 0)
            goto unavailable1;
        if (D_001A7AF8[selected] == 0)
            goto unavailable1;
        func_002E5E58(4, 0, 0);
        D_001F288C = selected;
        *(int *)(object + 0x494) = selected;
        goto finish1;
    unavailable1:
        func_002E5E58(5, 0, 0);
    }
finish1:
    {
    int finalSelection = D_001AA7D8[*(int *)(object + 0x48C)][3];
    *(int *)(object + 0x494) = finalSelection;
    if (finalSelection && D_001A7AF8[finalSelection])
        D_001ADB10 = ((SelectionRecord *)(D_00239BA0 + D_00139568[finalSelection] * 224))->value;
    }
}

void func_00345D58(char *object, unsigned int buttons)
{
    int selected;
    if (buttons & 0x1000) {
        int index;
        func_002E5E58(3, 0, 0);
        index = *(int *)(object + 0x48C) - 1;
        *(int *)(object + 0x490) = 0;
        *(int *)(object + 0x498) = 3;
        if (index < 0)
            index = 0;
        *(int *)(object + 0x48C) = index;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x490) = 0;
        *(int *)(object + 0x498) = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--(*(int *)(object + 0x48C)) < 0)
            *(int *)(object + 0x48C) = 2;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++(*(int *)(object + 0x48C)) >= 3)
            *(int *)(object + 0x48C) = 0;
    } else if (buttons & 0x40) {
        selected = D_001AA898[*(int *)(object + 0x48C)][3];
        if (selected && D_001A7AF8[selected]) {
            func_002E5E58(4, 0, 0);
            D_001ADB10 = *(short *)(D_00239BA0 + D_00139568[*(int *)(object + 0x494)] * 224 + 6);
            if (D_001F2884 == selected)
                D_001F2884 = 0;
            else
                D_001F2884 = selected;
        } else {
            func_002E5E58(5, 0, 0);
        }
    }
    {
    int finalSelection = D_001AA898[*(int *)(object + 0x48C)][3];
    *(int *)(object + 0x494) = finalSelection;
    if (finalSelection && D_001A7AF8[finalSelection])
        D_001ADB10 = ((SelectionRecord *)(D_00239BA0 + D_00139568[finalSelection] * 224))->value;
    }
}
