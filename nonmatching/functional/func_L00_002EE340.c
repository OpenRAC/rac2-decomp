/* functional: high. Plain floats in place of VU0 code, in its order; the test is retail's: the word of d2 - r*r as a signed integer is not positive (so +-0.0 and negatives count as inside), via its bgtz on the word shifted into the top of a 64-bit register. */

/* Is point a within the sphere b (xyz centre, w radius)? 1 if |a - b|^2 - r^2 <= 0 by its sign/zero bits, else 0. */
int func_L00_002EE340(void *a, void *b)
{
    float *p = a, *q = b;
    float dx = p[0] - q[0], dy = p[1] - q[1], dz = p[2] - q[2];
    float rr = q[3] * q[3];
    float acc;
    union {
        float f;
        int i;
    } u;

    dx = dx * dx;
    dy = dy * dy;
    dz = dz * dz;
    acc = dx + dy;
    acc = acc + 1.0f * dz;
    u.f = acc - rr;
    if (u.i > 0) {
        return 0;
    }
    return 1;
}
