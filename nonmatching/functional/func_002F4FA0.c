/* functional: high. Plain floats in place of VU0 code, in its order: ACC.y = dy2 + dx2, + 1*dz2, then - 1*(r1+r2)^2; the overlap test is the sign bit of that lane (retail's bgez on the 64-bit register whose top bit is lane y), so -0.0 counts as overlapping. */
extern char *D_001B21B4;
extern char *D_001B21B8;

static int neg_002F4FA0(float f)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.f = f;
    return u.i >> 31;
}

/* For each 32-byte light (D_001B21B4 .. D_001B21B8: xyz, w radius; u16 at +26 = four 4-bit slot ids, 0xF free) whose
   sphere overlaps `sphere` (xyz, w radius) and has a free slot, put id in its lowest free slot and append the light's
   index to out, until out reaches end. Returns the new out. */
unsigned short *func_002F4FA0(unsigned short *out, unsigned short *end, int id, void *sphere)
{
    float *s = sphere;
    char *p = D_001B21B4 - 32;
    int i = -1;

    for (;;) {
        float *l;
        unsigned int k;
        float dx, dy, dz, rr, acc;

        p += 32;
        if (p == D_001B21B8) {
            return out;
        }
        l = (float *)p;
        k = *(unsigned short *)(p + 26);
        i++;
        dx = s[0] - l[0];
        dy = s[1] - l[1];
        dz = s[2] - l[2];
        rr = s[3] + l[3];
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        rr = rr * rr;
        acc = dy + dx;
        acc = acc + 1.0f * dz;
        if (!neg_002F4FA0(acc - 1.0f * rr)) {
            continue;
        }
        if ((k & 0xFFFF) == 0xFFFF) {
            k = (k & 0xFFF0) | id;
        } else if ((k & 0xFFF0) == 0xFFF0) {
            k = (k & 0xFF0F) | (id << 4);
        } else if ((k & 0xFF00) == 0xFF00) {
            k = (k & 0xF0FF) | (id << 8);
        } else if ((k & 0xF000) == 0xF000) {
            k = (k & 0x0FFF) | (id << 12);
        } else {
            continue;
        }
        *out = i;
        out++;
        *(unsigned short *)(p + 26) = k;
        if (out == end) {
            return out;
        }
    }
}
