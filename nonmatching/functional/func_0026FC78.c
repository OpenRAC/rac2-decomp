/* functional: high. Near-miss draft that differs from retail in register allocation and scheduling only; fcheck SAME on all captured calls. */
/* func_0026FC78 (boot, 464 B): rac1 LoadPifAsPSMT8H twin. M29 2026-10-26: 9 lines off,
   register-only (a0/a1 swapped for the tbw, th and psm loads of the TEX0 chain); the
   or-chain grouping below reproduces retail's instruction order. -O2 -G0. */
typedef unsigned char u8;
extern int func_0011AEA0(int);
extern int func_001244B8(int, int);

/* Uploads a PIF image (header arg0, CLUT at +0x20 of 0x200 bytes when +0x14 is set, else
   0x400, then w * h pixels) to GS memory: the 16x16 CLUT to block cbp >> 8 and the pixels
   as PSMT8H to tbp >> 8 with a buffer width of w / 64 (at least 1), then writes the
   matching TEX0 plus 1, 0 to arg1 (rac1's LoadPifAsPSMT8H). */
typedef struct {
    long q[12];
} GsLoadImage26FC78 __attribute__((aligned(16)));

typedef struct {
    void *clut;
    void *image;
    int unk08[3];
    int clutSize;
    int imageSize;
    int unk1C[4];
    int tbp;
    int unk30[3];
    int tbw;
    int unk40[3];
    int tw;
    int th;
} PifTex26FC78;

typedef struct {
    char unk00[8];
    int w;
    int h;
    int unk10;
    int psm;
} PifHeader26FC78;

extern void func_00282A60(void *, int, int);
extern int func_00282A18(int);
extern int func_00126288(GsLoadImage26FC78 *, short, short, short, short, short, short, short);
extern int func_001265B0(GsLoadImage26FC78 *, void *);

void func_0026FC78(char *arg0, unsigned long long *out, int tbp, int cbp)
{
    PifTex26FC78 d;
    GsLoadImage26FC78 li;
    PifHeader26FC78 *pif = (PifHeader26FC78 *)arg0;
    int c;
    unsigned long tex0, hi, lo, cl;

    func_00282A60(&d, 0, sizeof(d));
    d.clut = (char *)pif + 0x20;
    if (pif->psm == 0) {
        d.clutSize = 0x400;
    } else {
        d.clutSize = 0x200;
    }
    c = cbp >> 8;
    d.tw = func_00282A18(pif->w);
    d.th = func_00282A18(pif->h);
    d.image = (char *)pif + (d.clutSize + 0x20);
    d.imageSize = pif->w * pif->h;
    func_00126288(&li, c, 1, pif->psm, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(&li, d.clut);
    func_001244B8(0, 0);
    d.tbw = pif->w >> 6;
    if (d.tbw <= 0) {
        d.tbw = 1;
    }
    d.tbp = tbp >> 8;
    func_00126288(&li, d.tbp, d.tbw, 0x1B, 0, 0, pif->w, pif->h);
    func_0011AEA0(0);
    func_001265B0(&li, d.image);
    func_001244B8(0, 0);
    lo = (unsigned long)d.tbp | ((unsigned long)d.tbw << 14);
    hi = ((unsigned long)0x1B << 20) | ((unsigned long)d.tw << 26);
    cl = ((unsigned long)1 << 34) | ((unsigned long)c << 37);
    tex0 = lo | hi;
    tex0 |= (unsigned long)d.th << 30;
    tex0 |= cl;
    tex0 |= (unsigned long)pif->psm << 51;
    tex0 |= (unsigned long)4 << 61;
    out[0] = tex0;
    out[1] = 1;
    out[2] = 0;
}
