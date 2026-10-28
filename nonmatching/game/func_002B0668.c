/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Emitted/retail size: 556/564 bytes.
 * us: 0 of 28 places match.
 * pal: 0 of 28 places match.
 * us2: 0 of 28 places match.
 * No strict linked build was run for this draft.
 * The head allocation, quadword scheduling and final call setup differ. The real two-input func_002BA8A0 interface is retained; no third parameter was invented to reproduce the caller's unused a2 zero. Reopen with an independently qualified call contract and memory-copy lifetime evidence.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern void *D_001B1A20[] MACRO_ADDR;
extern float D_001B1A18[] MACRO_ADDR;
extern float D_001B5348 NOT_SDA;
extern float D_001A9FCC __attribute__((sda));
extern void *D_001A9E74 __attribute__((sda));
extern Vector D_001BAFA0;
extern Vector D_001B5340;
extern float func_002B0520(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_002A7878(float, float);
extern void *func_002C19D8(void *, float, void *, float, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002BA8A0(void *, int);

void func_002B0668(Vector *position)
{
    Vector top, bottom, direction;
    float active = 0.0f;
    top.q = position->q;
    if (D_001B1A20[0] != 0) {
        top.f[2] = func_002B0520(&top) + D_001B1A18[0];
        if (top.f[2] < D_001B5348 + 5.0f) {
            bottom.q = top.q;
            bottom.f[2] = bottom.f[2] - (D_001B1A18[0] + D_001B1A18[0]) - 2.0f;
            active = 1.0f;
        }
    } else if (0.0f < top.f[0] && 0.0f < top.f[1] && top.f[0] < 1024.0f && top.f[1] < 1024.0f) {
        bottom.q = top.q;
        bottom.f[2] = D_001B5348 - 20.0f;
        active = 1.0f;
    }
    if (active != 0.0f && func_002761F8(&top, &bottom, 0x12, 0, 0)) {
        int material = func_00278E78();
        if (material == 0 || material == 4 || material == 3) {
            top.q = D_001BAFA0.q;
            top.f[2] += D_001A9FCC;
            func_002C19D8(&top, func_002A7878(0.4f, 0.6f), D_001A9E74, 5250.0f, -1);
        } else {
            func_00282CF0(&direction, &D_001BAFA0, &D_001B5340);
            func_002BA8A0(&D_001BAFA0, (unsigned char)(func_00282E20(&direction) * 3.1833334f + 64.0f));
        }
    }
}
