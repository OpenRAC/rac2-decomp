/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/game/0034AA30.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 480/480. US: 0/28; US2: 0/28; PAL: 0/28.
 * Residual and reopening condition: The two independent global-load pairs at the position calculation exchange order. The three real output-slot arguments to the empty retail stub are preserved; conversion and colour branches otherwise agree. Reopen with independently evidenced global attributes or source lifetimes.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern int func_00335E10(void *object);
extern void func_00335E68(void *object, int value);
/* Retail's disabled stub has no live inputs; this caller preserves its three output slots. */
extern void func_0026F808(int *first, int *second, int *third);
extern void func_00336B90(void *object, int value);
extern void func_00336B98(void *object, int value);
extern void func_00336498(void *object, int first, int second);
extern void func_003364B0(void *object, int first, int second);
extern int D_001A7A00 MACRO_ADDR;
extern int D_001A7A0C MACRO_ADDR;
typedef struct {
    unsigned char prefix[0x22B4];
    unsigned char enabled;
    unsigned char gap[0x277];
    int second;
    int first;
} MenuState;
extern char D_00189E20[];
extern float D_001AE798 MACRO_ADDR;
extern float D_001AE79C MACRO_ADDR;
extern float D_001B23A4 MACRO_ADDR;
extern int D_001B23A0 MACRO_ADDR;

void func_0034AA30(char *object)
{
    int first;
    int second;
    int third;
    float *out = (float *)func_00335E10(object + 0xF4);
    float y;
    float factor;
    float offsetY;
    int videoMode;
    int pixelY;
    if (D_001A7A00 < 80) {
        func_00335E68(object + 0xF4, 1);
        third = 0;
        first = ((MenuState *)D_00189E20)->first;
        second = ((MenuState *)D_00189E20)->second;
        if (first == 0)
            func_0026F808(&first, &second, &third);
        func_00336B90(object + 0xF4, second - first);
        func_00336B98(object + 0xF4, (D_001A7A0C >> 5) - first);
        factor = D_001B23A4;
        offsetY = D_001AE79C;
        videoMode = D_001B23A0;
        out[0] = D_001AE798 + **(float **)(object + 8);
        y = (offsetY + (*(float **)(object + 8))[1]) * factor + 0.5f;
        if (videoMode == 1)
            pixelY = (int)(y + -5.0f);
        else
            pixelY = (int)y;
        out[1] = (float)pixelY;
        if (((MenuState *)D_00189E20)->enabled == 1) {
            func_00336498(object + 0xF4, 0x60808080, 0x60808080);
            func_003364B0(object + 0xF4, 0x40808080, 0x40808080);
        } else {
            func_00336498(object + 0xF4, 0x8049C1FF, 0x80001EFF);
            func_003364B0(object + 0xF4, 0x50F0C070, 0x50F0C070);
        }
    } else {
        func_00335E68(object + 0xF4, 0);
    }
}
