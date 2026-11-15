#include "include_asm.h"
#include "names.h"

/* func_L02_003D6A20 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 p0;
    TI128 t0;
    TI128 p1;
    TI128 t1;
    int e0;
    int e1;
    int e2;
    int e3;
    int z50;
    int z54;
    int z58;
    float f5c;
    float f60;
    int z64;
    float f68;
    float f6c;
    char pad70[0x20];
} L02_003D6A20_Seg;

extern int D_L02_001B0344 __attribute__((sda));

extern int D_L02_001B0370 __attribute__((sda));

extern int D_L02_001B0374 __attribute__((sda));

extern TI128 D_L02_002412A0[];

extern TI128 D_L02_002415C0[];

extern void func_00281DE8(void *, int, int, int);

extern float func_00283CE0(int);

extern int func_00283D38(int, int, float);

extern void func_00280B90(void *, int, int);

/* Draws a curved path as a chain of short segments, using the saved point and tangent tables. */
void func_L02_003D6A20(void) {
    L02_003D6A20_Seg segment;
    int i;
    int previousValue;
    float step;
    float fraction;
    int edgeValue;
    TI128 *pointRows;
    TI128 *tangentRows;

    if (gBladeTrailCount >= 2) {
        InitQuadPacketState(&segment, 0x2B, 1, 0x80);
        segment.z50 = 0;
        segment.z54 = 0;
        segment.z58 = 0;
        segment.f5c = 1.0f;
        segment.f60 = 1.0f;
        segment.z64 = 0;
        segment.f68 = 1.0f;
        segment.f6c = 1.0f;
        previousValue = 0;
        step = 1.0f / IntToFloat(gBladeTrailCount - 1);
        for (i = 0; i < gBladeTrailCount - 1; i++) {
            pointRows = D_L02_002415C0;
            tangentRows = D_L02_002412A0;
            segment.p0 = pointRows[i];
            segment.t0 = tangentRows[i];
            segment.p1 = pointRows[i + 1];
            segment.t1 = tangentRows[i + 1];
            fraction = IntToFloat(i) * step;
            edgeValue = FastTweenColor(D_L02_001B0374, D_L02_001B0370, fraction * fraction);
            segment.e1 = previousValue;
            segment.e0 = previousValue;
            segment.e3 = edgeValue;
            segment.e2 = edgeValue;
            previousValue = edgeValue;
            draw_world_quad(&segment, 0, 0);
        }
    }
}
