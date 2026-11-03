/* functional: high. From the near miss, read against the assembly (jump table at 0x26D9D0: ids 12, 14, 17, 18, 53 are special): same reads, calls and draws in the same order; func_002F97A0 is called with its real prototype (color, text, limit, x, y, scale), the near miss had the arguments in register-class order; the distance maths are C doubles as retail's soft-double calls; the shop state is plain offsets from D_0021F240. */
extern char D_0021F240[];          /* the shop: +0x04 tick, +0x6C scroll, +0x80 selected,
                                      +0x140 rows of 0x18 (id, kind, ..., +0x14 locked), +0x740 row count */
extern unsigned char D_00139568[];
extern char D_00239BA0[];          /* 0xE0-byte item records: +0x04 colour kind, +0x3C icon */
extern float D_001B2280;           /* screen height scale */
extern int D_001A7B90;             /* +4 lines when set */
extern int D_001A7340, D_001A7344;
extern void func_002FC620(int, int, int, int);
extern int func_00282C30(int);
extern void func_00285548(int, int, int, int, int, int, unsigned int);
extern int func_0028E588(int, int);
extern unsigned int func_00336EF8(int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern char *func_00288FB8(int);
extern int func_0027F288(char *, int, float);
extern void func_002F97A0(unsigned long color, unsigned char *text, int limit, float x, float y, float scale);

#define S_I(o) (*(int *)(D_0021F240 + (o)))

/* The shop's icon strip: a pulsing frame, then up to twelve item icons around the selection,
   faded with their distance from the screen centre, with a "locked" or kind-1 caption. */
void func_002F9C80(void)
{
    int i, index, y, icon, kind, special, alpha0, alpha1, sy, width, id;
    unsigned int color, colors[4], pulse;
    char *text;
    double distance;

    sy = (int)(D_001B2280 * 382.0f + 0.5f);
    if (D_001A7B90 != 0) sy += 4;
    func_002FC620(58, 456, (int)(D_001B2280 * 320.0f + 0.5f), sy);

    if (S_I(0x6C) < 0)
        S_I(0x6C) = S_I(0x6C) + 4;
    else if (S_I(0x6C) > 0)
        S_I(0x6C) = S_I(0x6C) - 4;

    pulse = (unsigned int)((func_00282C30(((S_I(0x04) * 4) & 63) - 32) + 64) * 0x10202) | 0x80000000u;
    {
        int y0 = (int)(D_001B2280 * 325.0f + 0.5f), y1 = (int)(D_001B2280 * 381.0f + 0.5f);
        if (D_001A7B90 != 0) { y0 += 4; y1 += 4; }
        func_00285548(229, y0, 285, y1, D_001A7340, D_001A7344, pulse);
    }
    {
        int y0 = (int)(D_001B2280 * 327.0f + 0.5f), y1 = (int)(D_001B2280 * 379.0f + 0.5f);
        if (D_001A7B90 != 0) { y0 += 4; y1 += 4; }
        func_00285548(231, y0, 283, y1, D_001A7340, D_001A7344, 0x80442D00u);
    }

    y = S_I(0x6C) - 47;
    i = -5;
    do {
        index = i + S_I(0x80);
        if (index >= 0 && index < S_I(0x740)) {
            id = S_I(0x140 + index * 24);
            icon = func_0028E588(*(unsigned short *)(D_00239BA0 + D_00139568[id] * 224 + 60), 0);
            if (S_I(0x154 + index * 24) != 0) {
                kind = 2;
            } else {
                id = S_I(0x140 + index * 24);
                special = 0;
                kind = *(unsigned char *)(D_00239BA0 + D_00139568[id] * 224 + 4);
                switch (id) {
                case 12: case 14: case 17: case 18: case 53:
                    special = 1;
                    break;
                }
                if (special && kind == 1)
                    kind = 2;
            }
            color = func_00336EF8(kind) & 0xFFFFFF;
            distance = (double)(256.0f - (float)(y + 2));
            if (distance < 0)
                distance = 0 - distance;
            alpha0 = 128 - (int)(distance * 0.75);
            distance = (double)(256.0f - (float)(y + 40));
            if (distance < 0)
                distance = 0 - distance;
            alpha1 = 128 - (int)(distance * 0.75);
            if (alpha1 < 0) alpha1 = 0;
            if (alpha0 < 0) alpha0 = 0;
            colors[2] = (unsigned int)alpha0 << 24 | color;
            colors[3] = (unsigned int)alpha1 << 24 | color;
            colors[0] = (unsigned int)alpha0 << 24 | color;
            colors[1] = (unsigned int)alpha1 << 24 | color;
            sy = (int)(D_001B2280 * 329.0f + 0.5f);
            if (D_001A7B90 != 0) sy += 4;
            func_0028EA58(icon, y + 4, sy, 40, (int)(D_001B2280 * 40.0f + 0.5f), colors);
            text = 0;
            if (S_I(0x154 + index * 24) != 0)
                text = func_00288FB8(0x325F);
            else if (S_I(0x144 + index * 24) == 1)
                text = func_00288FB8(0x2DC9);
            else
                goto next;
            width = func_0027F288(text, -1, 0.75f);
            sy = (int)(D_001B2280 * 366.0f + 0.5f);
            if (D_001A7B90 != 0) sy += 4;
            func_002F97A0(0x80F0F0F0UL, (unsigned char *)text, -1, (float)(y - ((width >> 1) - 25)),
                          (float)sy, 0.75f);
        }
next:
        i++;
        y += 56;
    } while (i < 7);
}
