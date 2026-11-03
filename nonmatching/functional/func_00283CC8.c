/* functional: high. Handwritten FPU routine (cvt.w.s, cvt.s.w): the whole part by truncation, as the EE converts; the EE clamps values past the int range, which the callers' fractions never reach. */

/* Splits value into its whole part, stored at whole, and the fraction it returns. */
float func_00283CC8(float *whole, float value)
{
    float w = (float)(int)value;

    *whole = w;
    return value - w;
}
