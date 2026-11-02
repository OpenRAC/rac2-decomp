/* functional: high. Plain floats in place of VU0 vclipw.xyz: the six newest clip flags, as the VU sets them, from comparing x, y and z with +|w| and -|w|. */

/* Bit 0: x > |w|, bit 1: x < -|w|, bit 2: y > |w|, bit 3: y < -|w|, bit 4: z > |w|, bit 5: z < -|w|. */
int func_00282BE0(void *v)
{
    float *a = v;
    float w = a[3];
    int r = 0;
    int i;

    if (w < 0.0f) {
        w = -w;
    }
    for (i = 0; i < 3; i++) {
        if (a[i] > w) {
            r |= 1 << (i * 2);
        }
        if (a[i] < -w) {
            r |= 2 << (i * 2);
        }
    }
    return r;
}
