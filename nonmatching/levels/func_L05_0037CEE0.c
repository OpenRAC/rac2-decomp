/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L05_0037CEE0-g8.c
 * Game profile: -O2 -G8 -ffunction-sections
 * Compiled/retail bytes: 588/596. US: 0/4; US2: 0/4; PAL: 0/4.
 * Residual and reopening condition: Mixed absolute/GP base-pointer references and nested-loop spills/register lifetimes differ. The child walk, complete zone transforms and inner count reloads are retained. Reopen with measured owner/list/zone views and shorter genuine pointer lifetimes.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern short *D_L05_001FB220[];
extern unsigned char *D_L05_001B251C MACRO_ADDR;
extern unsigned char *D_L05_001B2614 MACRO_ADDR;
extern char D_L05_00221D10[];
extern float func_002A7940(void);
extern void func_002AF000(float *out, float a, float b, float c);
extern void func_00282CC0(void *out, void *a, void *b);
extern int func_002ACCA8(void *point, int index);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00283098(void *out, void *vector, void *matrix);
extern void func_00282F20(void *out, void *in, float scale);

void func_L05_0037CEE0(unsigned char *object, void *position, float magnitude)
{
    float randomVector[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float transformed[4] __attribute__((aligned(16)));
    short *entry = D_L05_001FB220[object[0x21]];
    short *next;
    unsigned char *zone;
    float first;
    float second;
    int offset;
    int i;
    int j;
    int *zones = (int *)(D_L05_00221D10 + 0x9C);
    if (entry == 0)
        return;
    do {
        next = entry + 1;
        offset = ((unsigned short)*entry & 0x7FFF) * 256;
        first = func_002A7940();
        second = func_002A7940();
        func_002AF000(randomVector, magnitude, first, second);
        func_00282CC0(D_L05_001B251C + offset + 0x10, randomVector, position);
        for (i = 0; i < *(int *)(D_L05_00221D10 + 0x90); i++) {
            if (func_002ACCA8(D_L05_001B251C + offset + 0x10, zones[i])) {
                zone = D_L05_001B2614 + zones[i] * 128;
                func_00282CF0(difference, D_L05_001B251C + offset + 0x10, zone + 0x30);
                difference[3] = 0.0f;
                func_00283098(transformed, difference, zone + 0x40);
                func_00282F20(transformed, transformed, 1.0499999523162842f);
                func_00283098(transformed, transformed, zone);
                func_00282CC0(D_L05_001B251C + offset + 0x10, transformed, zone + 0x30);
                for (j = 0; j < *(int *)(D_L05_00221D10 + 0x90); j++) {
                    if (func_002ACCA8(D_L05_001B251C + offset + 0x10, zones[j]))
                        qcopy(object + 0x10, D_L05_001B2614 + zones[j] * 128 + 0x30);
                }
            }
        }
        if (*entry < 0)
            break;
        entry = next;
    } while (1);
}
