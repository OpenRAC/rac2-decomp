/* functional: high. Plain floats in place of VU0 vsqrt: the VU takes the square root of |x|, written out here; the result is 0 + Q as vaddq computes it. */
extern float sqrtf(float);

/* Square root of |x|. */
float func_00282C10(float x)
{
    if (x < 0.0f) {
        x = -x;
    }
    return 0.0f + sqrtf(x);
}
