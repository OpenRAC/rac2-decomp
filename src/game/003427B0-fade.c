#include "names.h"
/* List-entry alpha falls off with scaled distance from the upper bound. */
extern double func_001234F0(float);
extern int func_00123028(double, double);
extern double func_00122A98(double, double);
extern double func_00122B00(double, double);
extern float func_00123298(double);

int func_003427C0(void *unused, int limit, float start, float offset, float end, float scale)
{
    double width = FloatToDouble(end - offset);
    float scaled;
    float ratio;
    double value;
    int result;

    if (CompareDoubles(width, 0.0) < 0)
        width = SubtractDoubles(0.0, width);
    scaled = DoubleToFloat(MultiplyDoubles(width, FloatToDouble(scale)));

    ratio = end - start;
    if (ratio < scaled)
        scaled = ratio;
    value = FloatToDouble(scaled / ratio);
    if (CompareDoubles(value, 0.0) < 0)
        value = SubtractDoubles(0.0, value);
    ratio = DoubleToFloat(value);

    scaled = (1.0f - ratio) * 255.0f;
    result = (int)scaled;
    return limit < result ? limit : result;
}

