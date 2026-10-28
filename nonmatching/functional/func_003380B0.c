/* functional: high. Transcribed branch by branch; the formatting call gets the same register arguments as retail in each branch. */
extern int func_00115DA8(char *, const char *, ...);
extern void func_00280190(unsigned short *, unsigned long, char *, int);
extern void func_00280200(unsigned short *, unsigned long, char *, int);
extern void func_00280270(unsigned short *, unsigned long, char *, int);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_003384C0(void *, int, int, float, float, float, float);

extern char D_001ADB58[];
extern char D_001ADB68[];
extern char D_001ADB78[];
extern char D_001ADB90[];
extern char D_001ADBB0[];
extern char D_001ADBB8[];
extern char D_001ADBC8[];
extern int D_001A7344;

static void draw_text(int mode, unsigned short *r, unsigned long style, char *buf, int len)
{
    if (mode == 0)
        func_00280200(r, style, buf, len);
    else if (mode == 1)
        func_00280190(r, style, buf, len);
    else if (mode == 2)
        func_00280270(r, style, buf, len);
}

void func_003380B0(void *p, unsigned short *r, unsigned long style, int text, int mode, int center,
                   int len, int t3, int a9, int a10, int a11)
{
    char buf[0x300];
    int saved = (short)r[9];
    int x, h, hx, hy, x0, x1, y0, y1;

    r[9] |= 3;

    if (a9 == 0) {
        func_00115DA8(buf, D_001ADBC8, text, text, mode, center, a10, t3);
    } else if (a10 == 0) {
        if (t3 != 0)
            func_00115DA8(buf, D_001ADBB0, text, 1, a9, center, a10, t3);
        else
            func_00115DA8(buf, D_001ADBB8, text, 1, 1, a9, a10, t3);
    } else if (a11 == 0) {
        if (t3 != 0)
            func_00115DA8(buf, D_001ADB78, text, 1, a9, a10, a10, t3);
        else
            func_00115DA8(buf, D_001ADB90, text, 1, 1, a9, a10, t3);
    } else {
        if (t3 != 0)
            func_00115DA8(buf, D_001ADB58, text, 1, a9, 1, a10, t3);
        else
            func_00115DA8(buf, D_001ADB68, text, 1, 1, a9, 1, a10);
    }

    r[9] |= 4;
    draw_text(mode, r, style, buf, len);

    if (center != 0) {
        h = (short)r[7];
        x = (D_001A7344 - h) >> 1;
        r[1] = x + r[7];
        r[5] = x + (h >> 1);
        r[0] = x;
    }
    draw_text(mode, r, style, buf, len);

    hx = ((short)r[6] >> 1) + 10;
    hy = ((short)r[7] >> 1) + 5;
    x1 = (short)r[4] + hx;
    y1 = (short)r[5] + hy;
    y0 = (short)r[5] - hy;
    x0 = (short)r[4] - hx;
    r[9] &= 0xFFFB;
    func_0027EB88(y0, y1, x0, x1, 0x60, 0x60442D00);
    func_003384C0(p, 0x60, 0x55F0C070, (float)y0, (float)y1, (float)x0, (float)x1);

    draw_text(mode, r, style, buf, len);
    r[9] = saved;
}
