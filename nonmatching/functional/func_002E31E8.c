/* functional: high. Plain floats in place of VU0 code; the overlap test reads the sign bit, so -0.0 counts as inside. */
extern unsigned char *D_001B2098;
extern unsigned char *D_001B209C;

static int negative_002E31E8(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

/* Walks the 32-byte records from D_001B2098 to D_001B209C (a sphere of x y z radius at +0, a 16-bit mask of four nibbles at +30) and, for each whose sphere overlaps the sphere at `sphere` (distance squared below the sum of the radii squared), takes the first nibble from the bottom whose upper nibbles and itself are all 0xF, sets it to `value`, writes the record's index at the cursor `out` and advances it. Stops once `out` reaches `end`. Returns the cursor. */
unsigned short *func_002E31E8(unsigned short *out, unsigned short *end, int value, float *sphere)
{
    float px = sphere[0], py = sphere[1], pz = sphere[2], pw = sphere[3];
    unsigned char *rec = D_001B2098 - 32;
    unsigned char *stop = D_001B209C;
    int index = -1;

    for (;;) {
        float *c;
        float dx, dy, dz, rr, d;
        unsigned int mask;

        c = (float *)(rec + 32);
        rec += 32;
        if (rec == stop) {
            return out;
        }
        mask = *(unsigned short *)(rec + 30);
        dx = px - c[0];
        dy = py - c[1];
        dz = pz - c[2];
        index++;
        rr = pw + c[3];
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        rr = rr * rr;
        d = dy + dx;
        d = d + dz;
        d = d - rr;
        if (!negative_002E31E8(d)) {
            continue;
        }
        if ((mask & 0xFFFF) == 0xFFFF) {
            *out++ = (unsigned short)index;
            *(unsigned short *)(rec + 30) = (unsigned short)((mask & 0xFFF0) | value);
        } else if ((mask & 0xFFF0) == 0xFFF0) {
            *out++ = (unsigned short)index;
            *(unsigned short *)(rec + 30) = (unsigned short)((mask & 0xFF0F) | (value << 4));
        } else if ((mask & 0xFF00) == 0xFF00) {
            *out++ = (unsigned short)index;
            *(unsigned short *)(rec + 30) = (unsigned short)((mask & 0xF0FF) | (value << 8));
        } else if ((mask & 0xF000) == 0xF000) {
            *out++ = (unsigned short)index;
            *(unsigned short *)(rec + 30) = (unsigned short)((mask & 0xFFF) | (value << 12));
        } else {
            continue;
        }
        if (out == end) {
            return out;
        }
    }
}
