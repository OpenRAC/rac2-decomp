/* functional: high. Hand-written from the assembly: builds the 4x4 matrix at D_001B5200 from three vectors, accumulates three of its rows with scaled terms, runs the func_00283788/282D60/282D30 helpers on the fixed matrices and copies the results to D_001B92C0; same reads, writes and calls in retail order, only register use and quad-copy instructions differ. */
typedef struct { int w[4]; } Quad279D18;
extern float D_001B5570[];
extern float D_001B5200[];
extern float D_001B9040[];
extern float D_001B9100[];
extern float D_001B92C0[];
extern void func_00283788(void *, void *, void *);
extern void func_00282D60(void *, void *, float);
extern void func_00282D30(void *, void *, float);

void func_00279D18(void)
{
    float v[12];
    float *m = D_001B5200;
    float *p = D_001B5570;
    float *g = D_001B9040;
    float e0, e4, e8;
    float a, b, c, d;

    *(Quad279D18 *)(&v[0]) = *(Quad279D18 *)(&p[0]);
    *(Quad279D18 *)(&v[4]) = *(Quad279D18 *)(&p[4]);
    *(Quad279D18 *)(&v[8]) = *(Quad279D18 *)(&p[8]);

    m[0x00 / 4] = -v[4];
    m[0x10 / 4] = -v[5];
    m[0x20 / 4] = -v[6];
    m[0x04 / 4] = -v[8];
    m[0x14 / 4] = -v[9];
    m[0x24 / 4] = -v[10];
    m[0x08 / 4] = v[0];
    m[0x18 / 4] = v[1];
    m[0x28 / 4] = v[2];
    m[0x3C / 4] = 1.0f;
    m[0x30 / 4] = 0;
    m[0x34 / 4] = 0;
    m[0x38 / 4] = 0;
    m[0x0C / 4] = 0;
    m[0x1C / 4] = 0;
    m[0x2C / 4] = 0;
    func_00283788(D_001B5200 + 0x40 / 4, D_001B9100, m);
    func_00283788(D_001B5200 + 0x80 / 4, D_001B9100 + 0x40 / 4, m);

    e0 = g[0x1A0 / 4];
    e4 = g[0x1A4 / 4];
    e8 = g[0x1A8 / 4];
    a = m[0x8C / 4];
    b = m[0x9C / 4];
    c = m[0xAC / 4];
    d = m[0xBC / 4];
    m[0x80 / 4] = m[0x80 / 4] + a * e0;
    m[0x84 / 4] = m[0x84 / 4] + a * e4;
    m[0x88 / 4] = m[0x88 / 4] + a * e8;
    m[0x90 / 4] = m[0x90 / 4] + b * e0;
    m[0x94 / 4] = m[0x94 / 4] + b * e4;
    m[0xA0 / 4] = m[0xA0 / 4] + c * e0;
    m[0xA4 / 4] = m[0xA4 / 4] + c * e4;
    m[0xA8 / 4] = m[0xA8 / 4] + c * e8;
    m[0xB0 / 4] = m[0xB0 / 4] + d * e0;
    m[0xB4 / 4] = m[0xB4 / 4] + d * e4;
    m[0xB8 / 4] = m[0xB8 / 4] + d * e8;
    m[0x98 / 4] = m[0x98 / 4] + b * e8;
    func_00283788(D_001B5200 + 0xC0 / 4, D_001B9100 + 0x80 / 4, m);

    func_00282D60(D_001B5200 + 0x100 / 4, D_001B9100 + 0x80 / 4, g[0x1C0 / 4]);
    func_00282D60(D_001B5200 + 0x110 / 4, D_001B9100 + 0x90 / 4, g[0x1C0 / 4]);
    *(Quad279D18 *)(D_001B5200 + 0x120 / 4) = *(Quad279D18 *)(D_001B9100 + 0xA0 / 4);
    *(Quad279D18 *)(D_001B5200 + 0x130 / 4) = *(Quad279D18 *)(D_001B9100 + 0xB0 / 4);
    func_00283788(D_001B5200 + 0x100 / 4, D_001B5200 + 0x100 / 4, m);

    *(Quad279D18 *)(&D_001B92C0[0]) = *(Quad279D18 *)(&m[0]);
    *(Quad279D18 *)(&D_001B92C0[4]) = *(Quad279D18 *)(&m[4]);
    *(Quad279D18 *)(&D_001B92C0[8]) = *(Quad279D18 *)(&m[8]);
    func_00282D30(&D_001B92C0[12], D_001B5200 + 0x140 / 4, 1024.0f);
    D_001B92C0[0x3C / 4] = 1024.0f;
}
