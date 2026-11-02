/* functional: high. Plain floats and sqrtf in place of VU0 code; a sum of squares is never negative, so no absolute value is needed. */
extern float sqrtf(float);

/* Distance between the xyz of the vectors at a and b. */
float func_00282E48(void *a, void *b)
{
    float *p = a, *q = b;
    float x = p[0] - q[0], y = p[1] - q[1], z = p[2] - q[2];
    float s = x * x;
    s = s + y * y;
    s = s + z * z;
    return sqrtf(s);
}
