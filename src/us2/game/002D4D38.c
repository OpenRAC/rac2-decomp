#include "include_asm.h"

extern int func_0028E588(int, int);
extern double func_001234F0(float);
extern int func_00123028(double, double);
extern double func_00122A98(double, double);
extern double func_00122B00(double, double);
extern int func_00123130(double);
extern int func_0028EA58(int, int, int, int, int, int *);
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];

/* func_US2_002D4D38, the USA v2.00 copy of func_002D3D88: the same C, without the display scaling. */
int func_US2_002D4D38(int index, int x)
{
    int colors[4];
    int leftAlpha;
    int rightAlpha;
    int right;
    int texture;
    int left = x + 2;
    int baseColor = 0xf0f0b0;
    double distance;

    texture = func_0028E588(0xea97, D_0026CFD0[index].icon);
    distance = func_001234F0(256.0f - (float)left);
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    leftAlpha = 128 - func_00123130(func_00122B00(distance, 0.75));
    distance = func_001234F0(256.0f - (float)(x + 40));
    if (func_00123028(distance, 0.0) < 0)
        distance = func_00122A98(0.0, distance);
    rightAlpha = 128 - func_00123130(func_00122B00(distance, 0.75));
    if (leftAlpha < 0)
        leftAlpha = 0;
    if (rightAlpha < 0)
        right = 0;
    else
        right = rightAlpha;
    leftAlpha <<= 24;
    right <<= 24;
    colors[2] = colors[0] = leftAlpha | baseColor;
    colors[3] = colors[1] = right | baseColor;
    return func_0028EA58(texture, left, 334, 40, 40, colors);
}

/* func_US2_002D4ED8 lives in 002D4ED8-g8.c. */

INCLUDE_ASM("asm/us2/game", func_US2_002D5540);
