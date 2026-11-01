/* functional: high. Plain floats and sqrtf in place of VU0 code; a sum of squares is never negative, so no absolute value is needed. */
extern float sqrtf(float);

/* Length of the xyz of the vector at v. */
float func_00282DF0(void *v)
{
    float *a = v;
    float s = a[0] * a[0];
    s = s + a[1] * a[1];
    s = s + a[2] * a[2];
    return sqrtf(s);
}
