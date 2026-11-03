/* functional: high. Plain floats in place of VU0 code: only x*x + y*y goes into the vsqrt (z is squared but not added), a sum of squares so no absolute value is needed; the result is 0 + Q as vaddq computes it. */
extern float sqrtf(float);

/* Length of the xy of the vector at v. */
float func_00282E20(void *v)
{
    float *a = v;
    float s = a[0] * a[0] + a[1] * a[1];

    return 0.0f + sqrtf(s);
}
