/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L05_0037BF48.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 520/524. US: 0/4; US2: 0/4; PAL: 0/4.
 * Residual and reopening condition: Global-base rematerialization, grid-coordinate temporaries and termination branches differ. The signed random remainder, marked child walk, gating and grid placement are complete. Reopen with measured source aliases/lifetimes; do not add redundant arithmetic to force allocation.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern short *D_L05_001FB220[];
extern unsigned char *D_L05_001B251C;
extern signed char D_L05_002BA2B8[];
extern int func_002ED688(void *object);
extern int func_001163B0(void);
extern int func_L05_0037BBB8(void *object);
extern int func_L05_0037BB90(void *object);
extern float func_00283CE0(int value);

void func_L05_0037BF48(unsigned char *object)
{
    char *parent;
    char *child;
    short *entry;
    short *next;
    int choice;
    int counter = 1;
    int offset;
    int i;
    int seen;
    int row;
    int stop;
    if (D_L05_001FB220[object[0x21]] == 0)
        return;
    parent = (char *)func_002ED688(object);
    choice = func_001163B0() % 2;
    entry = D_L05_001FB220[object[0x21]];
    do {
        next = entry + 1;
        offset = ((unsigned short)*entry & 0x7FFF) * 256;
        child = (char *)func_002ED688(D_L05_001B251C + offset);
        if (func_L05_0037BBB8(D_L05_001B251C + offset) &&
            !func_L05_0037BB90(D_L05_001B251C + offset) &&
            *(int *)(child + 0x1C) == *(int *)(parent + 0x1C)) {
            *(int *)(child + 0x20) = counter;
            counter++;
            seen = -1;
            for (i = 0; i < 25; i++) {
                if (D_L05_002BA2B8[(*(int *)(parent + 0x18) - 3) * 50 + choice * 25 + i] != 0) {
                    seen++;
                    if (seen == *(int *)(child + 0x20)) {
                        *(int *)(child + 8) = 0;
                        row = i / 5;
                        *(float *)child = func_00283CE0(row) * -10.5f;
                        *(float *)(child + 4) = func_00283CE0(i % 5 - 2) * 10.5f;
                        break;
                    }
                }
            }
        }
        stop = *entry < 0 || counter == *(int *)(parent + 0x18);
        entry = next;
    } while (!stop);
}
