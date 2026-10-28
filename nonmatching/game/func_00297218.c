/* Nonmatching C reconstruction.
 * Profile: game -O2 -G0 -ffunction-sections -Wa,-G8.
 * Measured after restoring the truthful incomplete coordinate-pair table:
 * 484 emitted bytes versus 488 retail bytes.
 * US: 0/28 local places; PAL: 0/28; US2: 0/28. All rows are present.
 * No strict linked build was run for this draft.
 * GP/absolute accesses and float guard/load scheduling still differ.
 * Reopen with measured symbol models; preserve the two-FPR/three-GPR
 * func_00297FE8 interface and the independently measured 8-byte row stride.
 */
#include "common.h"
extern int D_001A8CC0[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern int D_001A79F0_1 __attribute__((sda));
extern int D_001C4F40[] __attribute__((sda));
extern float D_001A9670 __attribute__((sda));
extern float D_001A9674[] __attribute__((sda));
extern float D_001A9678 __attribute__((sda));
extern float D_001A967C[] __attribute__((sda));
extern float D_001A9680 __attribute__((sda));
extern float D_001A9684[] __attribute__((sda));
typedef struct { float x, y; } CoordinatePair;
extern CoordinatePair D_001A9688[] __attribute__((sda));
extern float D_001A9410 __attribute__((sda));
extern float D_001A9414[] __attribute__((sda));
extern float D_001A9418[] __attribute__((sda));
extern float D_001A941C[] __attribute__((sda));
extern float D_001A9420 __attribute__((sda));
extern float D_001A9424[] __attribute__((sda));
extern char D_00189E20[];
extern int func_003005A0(void);
extern void func_00297FE8(float, float, float *, float *, int);

int func_00297218(float *x, float *y)
{
    int changed = 0;
    if (D_001A8CC0[0] != 0) {
        if (D_001A79F0[0] == 2) {
            *x = D_001A9670;
            *y = D_001A9674[0];
            changed = 1;
        } else if (D_001A79F0[0] == 11) {
            *x = D_001A9678;
            *y = D_001A967C[0];
            changed = 1;
        }
    }
    if (D_001A79F0[0] == 7 && func_003005A0() >= 0 && func_003005A0() < 4) {
        changed = 1;
        *x = D_001A9688[func_003005A0()].x;
        *y = D_001A9688[func_003005A0()].y;
    } else if (D_001A79F0_1 == 20) {
        if (D_001C4F40[0] == 2) {
            changed = 1;
            *x = D_001A9680;
            *y = D_001A9684[0];
        } else if (D_001C4F40[0] == 0) {
            float px = *(float *)(D_00189E20 + 0x80);
            float py = *(float *)(D_00189E20 + 0x84);
            if (D_001A9410 <= px && py <= D_001A9414[0] && px <= D_001A9418[0] && D_001A941C[0] <= py) {
                changed = 1;
                func_00297FE8(px, py, x, y, 20);
                *x += D_001A9420;
                *y += D_001A9424[0];
            }
        }
    }
    return changed;
}
