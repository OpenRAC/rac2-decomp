/* functional: high. Plain floats in place of VU0 vadd.xyz; retail stores the whole register back to a, so a's w word is rewritten unchanged. The first argument is unused by retail. */

/* a.xyz += b.xyz. */
void func_00282CD8(void *unused, void *a, void *b)
{
    float *p = a, *q = b;
    float x = p[0] + q[0], y = p[1] + q[1], z = p[2] + q[2];
    unsigned int w = ((unsigned int *)a)[3];

    p[0] = x;
    p[1] = y;
    p[2] = z;
    ((unsigned int *)a)[3] = w;
}
