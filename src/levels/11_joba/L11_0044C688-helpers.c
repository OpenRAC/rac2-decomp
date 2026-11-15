#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00283248(float f12, float f13);
extern float func_002A7878(float f12, float f13);
extern float func_00283180(float f12);
extern float func_00283198(float f12);

/* Picks a spot near a point for the smasher robot to walk to, a little off to one side of the line between them. */
void func_L11_0044C688(char *object, TI128 *point)
{
    char *state = *(char **)(object + 0x68);
    float dx, dy;
    if (*(s16 *)(state + 0x4D2) != 0) {
        float angle, scale;
        dx = *(float *)(object + 0x10) - *(float *)point;
        dy = *(float *)(object + 0x14) - *(float *)((char *)point + 4);
        angle = FastMatrixHelperA(dx, dy) + RandomFloatRange(-0.78539825f, 0.78539825f);
        scale = 15.0f;
        qcopy((state + 0x470), point);
        *(float *)(state + 0x470) += FastSinOrCosA(angle) * scale;
        *(float *)(state + 0x474) += FastSinOrCosB(angle) * scale;
        *(float *)(state + 0x478) = RandomFloatRange(0.0f, 4.0f) + 466.0f;
    } else {
        float angle, k;
        dx = *(float *)(object + 0x10) - *(float *)point;
        dy = *(float *)(object + 0x14) - *(float *)((char *)point + 4);
        angle = FastMatrixHelperA(dx, dy);
        angle += RandomFloatRange(-0.78539825f, 0.78539825f);
        k = RandomFloatRange(-2.0f, 2.0f);
        k += 8.0f;
        qcopy((state + 0x470), point);
        *(float *)(state + 0x470) = *(float *)(state + 0x470) + k * FastSinOrCosA(angle);
        k *= FastSinOrCosB(angle);
        *(float *)(state + 0x474) += k;
    }
}
