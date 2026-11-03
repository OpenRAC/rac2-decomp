/* functional: high. Plain floats in place of VU0 vmulx.xyz; the first argument is unused by retail (it never reads $a0), and w is rewritten with the value loaded from v. */

/* v.xyz *= s in place; v.w kept. The first argument is ignored. */
void func_00282D48(void *unused, void *v, float s)
{
    float *p = v;
    float x = p[0] * s, y = p[1] * s, z = p[2] * s;

    (void)unused;
    p[0] = x;
    p[1] = y;
    p[2] = z;
}
