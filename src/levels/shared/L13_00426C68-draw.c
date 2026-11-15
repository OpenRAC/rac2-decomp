#include "include_asm.h"
#include "names.h"

extern void func_002FC560(int, int);
extern void func_0027DE50(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } D_001A6480;
extern void func_L00_00416A38(void *, int, float, float, float, float, float, int);

/* Draws the screen flash and blends a sound effect while the object's countdown nears its end. */
void func_L13_00426C68(char *obj) {
    char *st = *(char **)(obj + 0x68);
    if (*(short *)(st + 2) - *(short *)st < 2 && *(short *)(st + 4)) {
        if (*(int *)(st + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            DrawColoredRectangle(0, gScreenAdjustOffsets.y, 0, gScreenAdjustOffsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(st + 0x18)) {
        if (*(short *)(st + 2) - *(short *)st < 10) {
            float t = (*(short *)(st + 2) - *(short *)st) * 0.1f;
            DrawJitteredBillboardQuadCopy(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)st - 0x2E) < 4) {
            float t = (*(short *)st - 0x2D) * 0.1f;
            DrawJitteredBillboardQuadCopy(obj + 0x10, 0x3C, *(float *)(st + 8) + (*(float *)(st + 12) - *(float *)(st + 8)) * t, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}
