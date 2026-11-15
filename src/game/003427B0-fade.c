#include "names.h"
/* List-entry alpha falls off with scaled distance from the upper bound. */
extern double __extendsfdf2(float);
extern int __cmpdf2(double, double);
extern double __subdf3(double, double);
extern double __muldf3(double, double);
extern float __truncdfsf2(double);

int ComputeListEntryAlpha(void *unused, int limit, float start, float offset, float end, float scale)
{
    double width = __extendsfdf2(end - offset);
    float scaled;
    float ratio;
    double value;
    int result;

    if (__cmpdf2(width, 0.0) < 0)
        width = __subdf3(0.0, width);
    scaled = __truncdfsf2(__muldf3(width, __extendsfdf2(scale)));

    ratio = end - start;
    if (ratio < scaled)
        scaled = ratio;
    value = __extendsfdf2(scaled / ratio);
    if (__cmpdf2(value, 0.0) < 0)
        value = __subdf3(0.0, value);
    ratio = __truncdfsf2(value);

    scaled = (1.0f - ratio) * 255.0f;
    result = (int)scaled;
    return limit < result ? limit : result;
}

