/* functional: high. Plain floats in place of VU0 code, in its order; the cosine and sine retail starts by hand (vcallms 0xC80 / 0xC90 on the angle in vf1.x) are the boot routines that run the same microprogram (func_00283180, func_00283198). Retail's register helper func_L02_00364D3C (entered by bgezal, reads t1, t5 and vf20) is written inline as texture_00364A18. The visibility test reads the sign bits of the two differences as retail's bltz does; the VU's divide by zero is written out (largest float, sign of n xor d) so the host makes no infinity. Retail's first vdiv (D_L02_001BEC00.x / D_L02_001BEAB0.x into vf25.x) feeds nothing that is stored and is left out. */

extern unsigned char *D_L02_001B3B20;
extern unsigned int *D_L02_001B3D08;
extern unsigned int D_L02_001B303C;
extern unsigned int D_001A72D0;
extern unsigned int D_00101140;
extern unsigned int D_00101150;
extern unsigned int D_L02_001AC9C0[4];
extern unsigned int D_L02_001AC9D0[4];
extern unsigned int D_L02_001AC9E0[4];
extern unsigned int D_L02_001AC9F0[4];
extern unsigned int D_L02_001ACA00[4];
extern unsigned long D_L02_001AC130;
extern unsigned char D_L02_001BEA00[];
extern unsigned char D_L02_001BA3C0[];
extern unsigned char D_L02_001BED00[];

extern float func_00283180(float angle);
extern float func_00283198(float angle);

static float bits_00364A18(unsigned int u)
{
    union {
        unsigned int i;
        float f;
    } c;
    c.i = u;
    return c.f;
}

static unsigned int fbits_00364A18(float f)
{
    union {
        unsigned int i;
        float f;
    } c;
    c.f = f;
    return c.i;
}

/* VU0 vdiv: n / d, with the VU's result for a zero divisor. */
static float vdiv_00364A18(float n, float d)
{
    if ((fbits_00364A18(d) & 0x7FFFFFFFu) == 0) {
        return ((fbits_00364A18(n) ^ fbits_00364A18(d)) >> 31) ? -3.40282347e38f : 3.40282347e38f;
    }
    return n / d;
}

static void copyq_00364A18(unsigned int *d, const unsigned int *s)
{
    unsigned int a = s[0], b = s[1], c = s[2], e = s[3];

    d[0] = a;
    d[1] = b;
    d[2] = c;
    d[3] = e;
}

/* Retail's register helper func_L02_00364D3C: give the texture row a slot in the 16-byte entry table at D_L02_001BED00
   (counter D_L02_001B303C), allocate its space from D_001A72D0, and build its 64-bit TEX0 word from D_L02_001AC130's low
   doubleword. Returns the new TEX0, which it also stores in the row. */
static unsigned long texture_00364A18(unsigned char *row, unsigned int base)
{
    unsigned int n = D_L02_001B303C;
    unsigned char *e;
    unsigned int at, v0, v1, w, h, size, lw;
    unsigned long t0;

    D_L02_001B303C = n + 1;
    e = D_L02_001BED00 + n * 16;
    at = D_001A72D0;
    v0 = at >> 8;
    at = at + 1024;
    *(unsigned short *)(e + 6) = (unsigned short)v0;
    v1 = at >> 8;
    *(unsigned short *)(e + 14) = (unsigned short)v1;
    w = row[12];
    h = row[14];
    e[12] = (unsigned char)w;
    size = 1u << (w & 31);
    e[13] = (unsigned char)h;
    size = size << (h & 31);
    at = at + size;
    *(unsigned short *)(e + 4) = 0;
    D_001A72D0 = at;
    *(unsigned int *)(e + 0) = *(unsigned short *)(row + 10) * 16 + base;
    *(unsigned int *)(e + 8) = *(unsigned short *)(row + 8) * 16 + base;
    lw = (int)(w - 6) > 0 ? w - 6 : 0;
    t0 = D_L02_001AC130;
    t0 |= (unsigned long)v1;
    t0 |= (unsigned long)(long)(int)(1u << (lw & 31)) << 14;
    t0 |= (unsigned long)w << 26;
    t0 |= (unsigned long)h << 30;
    t0 |= (unsigned long)v0 << 37;
    *(unsigned long *)row = t0;
    return t0;
}

/* Close a run of items: the end tag after them, the start tag (with the run's length) in the slot at head. */
static unsigned int *close_00364A18(unsigned int *p, unsigned int *head, int items)
{
    unsigned int n;

    copyq_00364A18(p, D_L02_001AC9F0);
    n = (unsigned int)((unsigned char *)p - (unsigned char *)head) >> 4;
    p += 4;
    copyq_00364A18(head, D_L02_001AC9E0);
    *(unsigned short *)head = (unsigned short)n;
    ((unsigned char *)head)[14] = (unsigned char)(n - 1);
    head[15] = items;
    return p;
}

/* Build the DMA packet of the level's camera-facing sprites (D_L02_001B3B20's list) at D_L02_001B3D08: a header with the
   camera rows scaled by 1024, then runs of up to 30 visible items (position, colour bytes, size times cos and sin of
   the item's angle, texture word), each run between the D_L02_001AC9E0 / D_L02_001AC9F0 tags, the D_L02_001ACA00 tag last. */
void func_L02_00364A18(void)
{
    unsigned char *list = D_L02_001B3B20;
    unsigned char *item = *(unsigned char **)(list + 28);
    int left = *(unsigned short *)(list + 8);
    unsigned int base = *(unsigned int *)(list + 20);
    unsigned char *rows = *(unsigned char **)(list + 16);
    unsigned int *p, *head;
    float *cam = (float *)D_L02_001BA3C0;
    float *v25 = (float *)(D_L02_001BEA00 + 512);
    float *v26 = (float *)(D_L02_001BEA00 + 176);
    float *v27 = (float *)(D_L02_001BEA00 + 480);
    float k = bits_00364A18(0x44800000);
    int count;
    int i;

    if (left == 0) {
        return;
    }
    p = D_L02_001B3D08;
    item -= 32;

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[1] = (unsigned int)&D_00101150;
    p[0] = 0x30000000;
    *(unsigned short *)p = (unsigned short)D_00101140;
    p += 4;
    copyq_00364A18(p, D_L02_001AC9C0);
    copyq_00364A18(p + 28, D_L02_001AC9D0);
    copyq_00364A18(p + 20, (unsigned int *)(D_L02_001BEA00 + 528));
    copyq_00364A18(p + 24, (unsigned int *)(D_L02_001BEA00 + 416));
    for (i = 0; i < 3; i++) {
        float *r = (float *)(D_L02_001BA3C0 + 64 + 16 * i);
        float a = r[0] * k, b = r[1] * k, c = r[2] * k, d = r[3] * k;
        float *o = (float *)(p + 4 + 4 * i);
        o[0] = a;
        o[1] = b;
        o[2] = c;
        o[3] = d;
    }
    copyq_00364A18(p + 16, (unsigned int *)(D_L02_001BA3C0 + 112));
    p += 32;
    count = 0;
    head = p;
    p += 4;

    while (left > 0) {
        unsigned int pos[4];
        float x, y, z, w, vx, vy, vz, ax, ay, dx, dy, q, qx, qy, c, s;
        unsigned int flag, bytes, kind, angle;
        int index;
        unsigned char *row;
        unsigned long tex;

        item += 32;
        for (i = 0; i < 4; i++) {
            pos[i] = ((unsigned int *)(item + 16))[i];
        }
        left--;
        x = bits_00364A18(pos[0]);
        y = bits_00364A18(pos[1]);
        z = bits_00364A18(pos[2]);
        w = bits_00364A18(pos[3]);
        vx = (cam[0] * x + cam[4] * y) + cam[8] * z;
        vy = (cam[1] * x + cam[5] * y) + cam[9] * z;
        vz = (cam[2] * x + cam[6] * y) + cam[10] * z;
        flag = item[1];
        index = (signed char)item[2];
        bytes = *(unsigned int *)(item + 4);
        kind = item[3];
        if (index < 0) {
            if (flag != 0) {
                item[1] = 0;
            }
            continue;
        }
        angle = *(unsigned int *)(item + 8);
        ax = v27[0] * w;
        ay = v27[1] * w;
        w = w * v25[3];
        dx = vx < 0.0f ? -vx : vx;
        dy = vy < 0.0f ? -vy : vy;
        dx = dx - ax;
        dy = dy - ay;
        q = vdiv_00364A18(w, vz);
        dx = v26[0] * vz - dx;
        dy = v26[1] * vz - dy;
        row = rows + index * 16;
        tex = *(unsigned long *)row;
        if ((fbits_00364A18(dy) >> 31) != 0 || (fbits_00364A18(dx) >> 31) != 0) {
            if (flag != 0) {
                item[1] = 0;
            }
            continue;
        }
        for (i = 0; i < 4; i++) {
            p[i] = pos[i];
        }
        c = func_00283180(bits_00364A18(angle));
        if (flag == 0) {
            item[1] = 1;
        }
        qx = q * c;
        s = func_00283198(bits_00364A18(angle));
        qy = q * s;
        p[3] = 0;
        p[4] = bytes & 0xFF;
        p[5] = (bytes >> 8) & 0xFF;
        p[6] = (bytes >> 16) & 0xFF;
        p[7] = bytes >> 24;
        ((float *)p)[8] = qx;
        ((float *)p)[9] = qy;
        ((float *)p)[10] = q;
        ((float *)p)[11] = 1.0f + q;
        *(unsigned long *)(p + 10) = kind;
        if ((long)tex >= 0) {
            tex = texture_00364A18(row, base);
        }
        *(unsigned long *)(p + 12) = tex;
        count += 4;
        *(unsigned long *)(p + 14) = 0;
        p += 16;
        if (count - 120 >= 0) {
            p = close_00364A18(p, head, count);
            count = 0;
            head = p;
            p += 4;
        }
    }
    if (count != 0) {
        p = close_00364A18(p, head, count);
    } else {
        p -= 4;
    }
    copyq_00364A18(p, D_L02_001ACA00);
    p += 4;
    D_L02_001B3D08 = p;
}
