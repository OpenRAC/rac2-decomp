/* functional: high. Plain floats in place of VU0 code, in its order. The sphere test takes the sign bit of d2 - r (as retail's srl 31 of the float word); vclipw against vf0.w = 1 is |c| > 1 per lane, written as retail's two strict compares. As retail, the sphere loop also tests the entry at index count (it compares before stepping), and a point inside a sphere but outside its box ends the search with 0. */
extern unsigned char D_001C1540[];
extern int D_001B199C;
extern unsigned char D_001C1740[];

static int neg_002A6640(float f)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.f = f;
    return u.i >> 31;
}

/* Find the first camera-environment sphere (D_001C1540: xyz centre, w radius squared; entries 0..D_001B199C) containing
   pos; then map pos (w = 1) through that region's 4x4 matrix (D_001C1740, 128-byte entries). Outside the unit box:
   return 0. Inside: *blend = (x + 1) * 0.5, *region = index, return 1. No sphere: return 0. */
int func_002A6640(void *position, float *blend, int *region)
{
    float *pos = position;
    float p[4];
    float *s = (float *)D_001C1540;
    float *end = (float *)(D_001C1540 + D_001B199C * 16);
    int i = -1;

    p[0] = pos[0];
    p[1] = pos[1];
    p[2] = pos[2];
    p[3] = 0.0f + 1.0f;
    for (;;) {
        float dx = p[0] - s[0], dy = p[1] - s[1], dz = p[2] - s[2];
        float r = 0.0f + s[3];
        float d;

        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        d = dx + dy;
        d = d + dz;
        i++;
        if (neg_002A6640(d - r)) {
            break;
        }
        if (s == end) {
            return 0;
        }
        s += 4;
    }
    {
        float *m = (float *)(D_001C1740 + i * 128);
        float c[4];
        int j;

        for (j = 0; j < 4; j++) {
            float acc = m[j] * p[0];
            acc = acc + m[4 + j] * p[1];
            acc = acc + m[8 + j] * p[2];
            c[j] = acc + m[12 + j] * p[3];
        }
        for (j = 0; j < 3; j++) {
            if (c[j] > 1.0f || c[j] < -1.0f) {
                return 0;
            }
        }
        *region = i;
        *blend = 0.5f * (c[0] + 1.0f);
        return 1;
    }
}
