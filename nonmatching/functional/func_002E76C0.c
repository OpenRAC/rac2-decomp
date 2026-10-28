/* functional: medium. Hand-decoded from the assembly (not attempted as a match): the same calls in the same order with the same arguments, and the same stores into the 0x50-byte record at sp+0x80 that func_002ED2B8 reads. The record's fields are named by offset only; the unwritten words (0xB0, 0xB8, 0xC8) are left as they are. Argument types of the vector helpers are guessed from other callers. */
extern void func_00283130(void *dst, long src);
extern void func_00282D60(void *dst, void *src, float scale);
extern void func_00282CA8(void *dst, void *a, void *b);
extern void func_00283958(void *src, void *dst);
extern void func_00283738(void *dst, void *a, void *b);
extern void func_00283098(void *dst, void *a, void *b);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_00282D30(void *dst, void *src, float angle);
extern void func_00282C88(void *dst);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_002E7570(void *src, void *matrix, int count, unsigned int colour, float from, float to, float radius);
extern void func_002ED368(void *);
extern void func_002ED2B8(void *, void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern float D_001AC090[];   /* 16-byte entries, the float at +0xC is the scale */
extern int D_001B2150[];
extern int D_001B8874;

typedef struct {
    float v[4];       /* 0x80 */
    int q[4];         /* 0x90 */
    float f0;         /* 0xA0 */
    float f4;         /* 0xA4 */
    float f8;         /* 0xA8 */
    int fc;           /* 0xAC */
    int pad10;        /* 0xB0 */
    int a14;          /* 0xB4 */
    int pad18;        /* 0xB8 */
    int a1c;          /* 0xBC */
    int a20;          /* 0xC0 */
    int a24;          /* 0xC4 */
    int pad28;        /* 0xC8 */
    int a2c;          /* 0xCC */
} Rec2E76C0;

void func_002E76C0(unsigned char *obj, int idx, int flag)
{
    int m0[4];
    int m1[4];
    int m2[4];
    int d[4], e[4], f[4];
    Rec2E76C0 r;
    float *tab;
    float sc, a5, c04, c06;
    float p, q2, r2, s2, t2, u2, w2;
    int c1, c2, col0, col1, v;
    int i;

    func_00283130(d, *(long *)(*(int *)(obj + 0x58) + 0x10));
    func_00283130(e, *(long *)(*(int *)(obj + 0x5C) + 0x10));
    func_00282D60(d, d, (1.0f - *(float *)(obj + 0x44)) * 3.0517578125e-05f);
    func_00282D60(e, e, *(float *)(obj + 0x44) * 3.0517578125e-05f);
    func_00282CA8(f, d, e);
    func_00283958(f, m2);
    func_00283738(m2, obj + 0xC0, m2);
    tab = &D_001AC090[idx * 4];
    func_00283098(m0, tab, m2);
    func_00282CC0(m0, m0, obj + 0x10);

    sc = (float)obj[0x95] * (tab[3] * 0.0078125f);
    a5 = sc * 5.0f;
    c04 = 0.039999999f;
    c06 = 0.059999999f;
    p = sc * c04 + c04;           /* f27 */
    q2 = sc * c06 + c06;          /* f24 */
    c1 = func_00283CF0(a5 + 25.0f);
    c2 = func_00283CF0(a5 + 15.0f);
    {
        float k75 = 0.074999996f;          /* f28 */
        float x23 = sc * k75;
        float x22 = sc * 0.375f;
        float x21 = sc * 0.099999994f;
        float x1 = sc * 0.024999998f;
        float x0 = sc * 0.024999991f;
        x22 = x22 + 0.375f;
        x21 = x21 + 0.099999994f;
        s2 = x1 + 0.024999998f;            /* f26 */
        r2 = x0 + 0.175f;                  /* f25 */
        col0 = func_00283D38(0x40204080, 0x40205080, sc);
        x23 = x23 + k75;
        col1 = func_00283D38(-1, -1, sc);
        func_00282D30(m1, m2, -q2);
        func_002E7570(m0, m1, c1, col0, x22, x21, x23);
        if (idx == 0) {
            func_00282D30(m1, m2, -p);
            func_002E7570(m0, m1, c2, col1, r2, s2, k75);
        }
    }
    func_002ED368(obj);
    r.fc = func_00283D38(0x2F7F, 0x7F7F, func_002A7878(0.0f, 1.0f));
    if (flag != 0)
        r.a14 = func_002A7820(0x18, 0x28);
    else
        r.a14 = func_002A7820(0x1F, 0x3F);
    r.f8 = func_002A7878(1.0f, 2.0f);
    for (i = 0; i < 4; i++)
        ((int *)r.v)[i] = m0[i];
    r.v[0] += func_002A7878(-0.025f, 0.025f);
    r.v[1] += func_002A7878(-0.025f, 0.025f);
    r.v[2] += func_002A7878(-0.025f, 0.025f);
    func_00282C88(r.q);
    for (i = 0; i < 4; i++)
        r.q[i] = D_001B2150[i];
    r.f4 = func_002A7940();
    r.f0 = func_002A7878(90.0f, 180.0f) * 0.00029088825f;
    v = func_002A7820(0x46, 0x5A);
    r.a20 = v;
    r.a2c = 5;
    r.a1c = 1;
    r.a24 = v;
    if (flag == 0) {
        int x = D_001B8874;
        r.a1c = (((x % 2) + 1) << 1) | 1;
    }
    func_002ED2B8(obj, &r);
}
