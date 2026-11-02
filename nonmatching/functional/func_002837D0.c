/* functional: high. Plain floats in place of VU0 code, in the assembly's order of operations. */

/* Quaternion product dst = q1 * q2 (x y z w): vector part q2.xyz*q1.w + q1.xyz*q2.w + q1 x q2, w = q1.w*q2.w - q1.xyz . q2.xyz. */
void func_002837D0(void *dst, void *first, void *second)
{
    float *d = dst, *a = first, *b = second;
    float ax = a[0], ay = a[1], az = a[2], aw = a[3];
    float bx = b[0], by = b[1], bz = b[2], bw = b[3];
    float dot, o[4];

    dot = bx * ax;
    dot = dot + by * ay;
    dot = dot + bz * az;
    o[0] = (bx * aw + ax * bw) + (ay * bz - by * az);
    o[1] = (by * aw + ay * bw) + (az * bx - bz * ax);
    o[2] = (bz * aw + az * bw) + (ax * by - bx * ay);
    o[3] = bw * aw - dot;
    d[0] = o[0];
    d[1] = o[1];
    d[2] = o[2];
    d[3] = o[3];
}
