/* functional: medium. Written from the assembly, same reads, writes and calls in the same order. Retail's psubsb (saturating signed byte subtract) region test is written per byte; its `teq zero,zero` (moby missing from a cell it should be in) has no C spelling and is replaced by a return; retail's `qmtc2 zero,$vf0` writes the constant VU0 register and does nothing. Block copies go 32 bytes at a time, each read whole before it is written, as retail's lq/lq/sq/sq. */
extern char *D_001B1B5C;
extern unsigned char D_001D24E0[];
extern int func_002A0BE8(int count);
extern void func_002A0B88(int bit, int count);

static int subsb_002A0C68(unsigned int a, unsigned int b)
{
    int d = (int)(signed char)a - (int)(signed char)b;
    if (d > 127) {
        d = 127;
    }
    if (d < -128) {
        d = -128;
    }
    return d;
}

/* Is cell (x, y) outside the region packed in r (bytes x0, y0, x1, y1), by retail's saturating byte test? */
static int outside_002A0C68(unsigned int x, unsigned int y, unsigned int r)
{
    if (subsb_002A0C68(x, r) < 0 || subsb_002A0C68(y, r >> 8) < 0) {
        return 1;
    }
    if (subsb_002A0C68(x, r >> 16) > 0) {
        return 1;
    }
    return subsb_002A0C68(y, r >> 24) > 0;
}

static void copy_002A0C68(unsigned char *dst, unsigned char *src, int chunks)
{
    do {
        unsigned int t[8];
        int i;
        for (i = 0; i < 8; i++) {
            t[i] = ((unsigned int *)src)[i];
        }
        for (i = 0; i < 8; i++) {
            ((unsigned int *)dst)[i] = t[i];
        }
        chunks--;
        src += 32;
        dst += 32;
    } while (chunks > 0);
}

/* Move a moby's entry in the 64x64 cell grid D_001D24E0 (4-byte cells: u16 first 32-byte block, u8 count, u8 blocks)
   from its old region (moby+0xA4: bytes x0, y0, x1, y1; negative word = none) to the region `cell`: remove its index
   from cells only in the old region, shrinking or freeing their block runs, then add it to cells only in the new one,
   growing their block runs. The index lists live in 32-byte blocks of 16 halfwords at D_001D24E0 + 0x4000. */
void func_002A0C68(void *moby, int cell)
{
    unsigned char *m = moby;
    unsigned char *pool = D_001D24E0 + 0x4000;
    unsigned int idx = (unsigned int)((char *)moby - D_001B1B5C) >> 8;
    unsigned int r = (unsigned int)cell;
    unsigned int old;
    unsigned int x, y;

    if (*(int *)(m + 0xA4) >= 0) {
        x = m[0xA4];
        y = m[0xA5];
        for (;;) {
            if (outside_002A0C68(x, y, r)) {
                unsigned char *c = D_001D24E0 + x * 4 + y * 256;
                unsigned short *p = (unsigned short *)(pool + *(unsigned short *)c * 32);
                unsigned short *end = p + c[2];
                int count;
                unsigned int cap;

                for (;;) {
                    if (p == end) {
                        /* retail: teq zero,zero (the moby is not in the cell) */
                        return;
                    }
                    if (*p == idx) {
                        break;
                    }
                    p++;
                }
                *p = end[-1];
                end[-1] = 0;
                count = c[2];
                cap = c[3];
                count = count - 1;
                c[2] = count;
                if (count == 0 || (cap != 1 && (int)(cap * 8 - 4 - count) > 0)) {
                    int oldblock;
                    unsigned int half;

                    func_002A0B88(*(unsigned short *)c, c[3]);
                    half = c[3] >> 1;
                    oldblock = *(short *)c;
                    *(unsigned short *)c = 0;
                    c[3] = half;
                    if (half != 0) {
                        int nb = func_002A0BE8(half);
                        *(unsigned short *)c = nb;
                        copy_002A0C68(pool + (nb << 5), pool + (oldblock << 5), (signed char)c[3]);
                    }
                }
            }
            if (x != m[0xA6]) {
                x++;
                continue;
            }
            x = m[0xA4];
            if (y != m[0xA7]) {
                y++;
                continue;
            }
            break;
        }
    }

    old = *(unsigned int *)(m + 0xA4);
    *(unsigned int *)(m + 0xA4) = r;
    x = r & 0xFF;
    y = (r & 0xFF00) >> 8;
    if (cell < 0) {
        return;
    }
    for (;;) {
        if (outside_002A0C68(x, y, old)) {
            unsigned char *c = D_001D24E0 + x * 4 + y * 256;
            unsigned int cap = c[3];
            unsigned int count = c[2];

            if (cap == 0 || (int)(cap * 16 - count) <= 0) {
                unsigned int oldcap = c[3];
                int ncap = (int)(oldcap * 2);
                int nb;
                unsigned int oldblock;

                if (ncap < 1) {
                    ncap = 1;
                }
                c[3] = ncap;
                nb = func_002A0BE8(ncap);
                oldblock = *(unsigned short *)c;
                *(unsigned short *)c = nb;
                if (oldcap != 0) {
                    func_002A0B88(oldblock, oldcap);
                    copy_002A0C68(pool + (*(unsigned short *)c << 5), pool + (oldblock << 5), c[3] >> 1);
                }
                count = c[2];
            }
            c[2] = count + 1;
            *(unsigned short *)(pool + *(unsigned short *)c * 32 + count * 2) = idx;
        }
        if (x != m[0xA6]) {
            x++;
            continue;
        }
        x = m[0xA4];
        if (y != m[0xA7]) {
            y++;
            continue;
        }
        break;
    }
}
