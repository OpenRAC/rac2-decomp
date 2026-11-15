#include "include_asm.h"
#include "names.h"

extern void func_002FC560(int, int);
extern void func_0027DE50(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } D_001A6480;
extern void func_L04_00459408(void *, int, float, float, float, float, float, int);

/* Draws the on-screen fade and the glow effect for a timed object as its countdown runs. */
void func_L16_0041F950(char *object) {
    char *state = *(char **)(object + 0x68);
    if (*(short *)(state + 2) - *(short *)state < 2 && *(short *)(state + 4)) {
        if (*(int *)(state + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            DrawColoredRectangle(0, gScreenAdjustOffsets.y, 0, gScreenAdjustOffsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(state + 0x18)) {
        if (*(short *)(state + 2) - *(short *)state < 10) {
            float progress = (*(short *)(state + 2) - *(short *)state) * 0.1f;
            DrawBillboardQuadWithJitter(object + 0x10, 0x3C, *(float *)(state + 8) + (*(float *)(state + 12) - *(float *)(state + 8)) * progress, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)state - 0x2E) < 4) {
            float progress = (*(short *)state - 0x2D) * 0.1f;
            DrawBillboardQuadWithJitter(object + 0x10, 0x3C, *(float *)(state + 8) + (*(float *)(state + 12) - *(float *)(state + 8)) * progress, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}
