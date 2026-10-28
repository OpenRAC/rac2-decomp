/* Retained nonmatching reconstruction, 27 October 2026.
 * Colour packing uses unsigned shifts before the target's signed 32-bit slot
 * conversion; this avoids signed-shift overflow and leaves the object unchanged.
 * Profile: default -O2 -G0 -ffunction-sections. Candidate and retail: 536 bytes. USA v1.01 rejects all 28 carrying places; USA v2.00 and PAL have no canonical row (ABSENT). The prologue, public soft-double helper interfaces, FP operations and final rendering call agree. Twelve integer words differ around the independent lower clamps and packed-colour register allocation. Opposite clamp order plus separate colour packing moved other registers. Reopen with a causal lifetime/statement model for those words.
 */
#include "common.h"
extern int func_0028E588(int, int);
extern double func_001234F0(float);
extern int func_00123028(double, double);
extern double func_00122A98(double, double);
extern double func_00122B00(double, double);
extern int func_00123130(double);
extern int func_0028EA58(int, int, int, int, int, int *);
typedef struct { char reserved[16]; int key; } MenuItem;
extern MenuItem D_0026CFD0[];
extern int D_001B23A0[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
int func_002D3D88(int index, int y)
{
    int colors[4];
    int first, second;
    int key;
    int x;
    int drawY = y + 2;
    int baseColor = 0xf0f0b0;
    float center;
    double distance;
    key = func_0028E588(0xea97, D_0026CFD0[index].key);
    distance = func_001234F0(256.0f - (float)drawY);
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    first = 128 - func_00123130(func_00122B00(distance, 0.75));
    distance = func_001234F0(256.0f - (float)(y + 40));
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    second = 128 - func_00123130(func_00122B00(distance, 0.75));
    if (second < 0)
        second = 0;
    if (first < 0)
        first = 0;
    colors[2] = colors[0] = (int)(((unsigned int)first << 24) | (unsigned int)baseColor);
    colors[3] = colors[1] = (int)(((unsigned int)second << 24) | (unsigned int)baseColor);
    center = D_001B23A4[0] * 334.0f + 0.5f;
    if (D_001B23A0[0] == 1)
        x = (int)(center + 4.0f);
    else
        x = (int)center;
    return func_0028EA58(key, drawY, x, 40, (int)(D_001B23A4[0] * 40.0f + 0.5f), colors);
}
