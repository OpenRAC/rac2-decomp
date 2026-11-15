#include "common.h"

extern float func_00283248(float f12, float f13);
extern float func_002A7878(float f12, float f13);
extern float func_00283180(float f12);
extern float func_00283198(float f12);

/* Picks a spot near a point for the robot to walk to, a little off to one side of the line between them. */
void func_L11_00449AD8(char *object, char *point)
{
    char *state = *(char **)(object + 0x68);

    if (*(s16 *)(state + 0x36E) != 0) {
        float dx = *(float *)(object + 0x10) - *(float *)(point + 0x0);
        float dy = *(float *)(object + 0x14) - *(float *)(point + 0x4);
        float base = FastMatrixHelperA(dx, dy) + RandomFloatRange(-0.17453295f, 0.17453295f);
        float scale = 15.0f;
        float heightJitter;

        qcopy((state + 0x330), point);
        *(float *)(state + 0x330) += FastSinOrCosA(base) * scale;
        *(float *)(state + 0x334) += FastSinOrCosB(base) * scale;
        heightJitter = RandomFloatRange(-4.0f, 4.0f);
        *(float *)(state + 0x338) = *(float *)(object + 0x18) + heightJitter;
    } else {
        float dx = *(float *)(object + 0x10) - *(float *)(point + 0x0);
        float dy = *(float *)(object + 0x14) - *(float *)(point + 0x4);
        float base = FastMatrixHelperA(dx, dy) + RandomFloatRange(-0.78539825f, 0.78539825f);
        float scale = RandomFloatRange(-2.0f, 2.0f) + 8.0f;

        qcopy((state + 0x330), point);
        *(float *)(state + 0x330) += scale * FastSinOrCosA(base);
        scale = scale * FastSinOrCosB(base);
        *(float *)(state + 0x334) += scale;
    }
}
