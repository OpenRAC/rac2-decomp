/* functional: high. Plain floats in place of VU0 vmr32.xyzw of $vf0 (0, 0, 0, 1) rotated one lane: (0, 0, 1, 0) stored as a quadword. */
void func_00282C98(void *dst)
{
    float *v = dst;

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 1.0f;
    v[3] = 0.0f;
}
