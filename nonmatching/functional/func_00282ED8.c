/* functional: medium. Carried from Ratchet & Clank (func_L00_001FF468, bsphere_gap_squared); no addresses involved, the vector steps read the same in rac2's assembly. Sphere overlap test on two 4-float vectors a, b (xyz = centre, w = radius): returns 1 if dx*dx+dy*dy+dz*dz - (a.w+b.w)^2 is negative (sign bit set, as the 64-bit bgez on the vector word sees), else 0. Negative zero is counted as non-negative here. */
int func_00282ED8(float *a, float *b) {
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    float rw = a[3] + b[3];
    float acc = dy * dy + dx * dx;
    acc = acc + dz * dz;
    acc = acc - rw * rw;
    return acc < 0.0f;
}
