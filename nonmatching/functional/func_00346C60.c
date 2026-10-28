/* functional: medium (fcheck covers 1 call only; the button branches were not all exercised). Hand-decoded from the assembly (not attempted as a match): a 6x4 menu grid cursor (rows at +0x500, columns at +0x4FC), the same calls in the same order with the same arguments; the 8-byte copies from 0x1AE508.. are word copies here. The zero-initialised and copied pairs are positions (x, y) placed with func_00335E38. */
extern void func_002E5E58(int, int, int);
extern void func_00115484(void *, int, int);
extern int func_002A9588(int, int, int, int, int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);

extern float D_001AE508[2];
extern float D_001AE510[2];
extern float D_001AE518[2];
extern float D_001AE520[2];
extern char D_001AE528[];
extern char D_001AE530[];
extern char D_001AE538[];
extern char D_001ADF98[];
extern char D_001AE548[];
extern char D_001ADBC8[];
extern int D_001ADB10;
extern int D_001F2880;
extern unsigned char D_001A7AF8[];
extern unsigned char D_001A7B30[];
extern unsigned char D_00139568[];
extern int D_00139688[];

typedef struct {
    unsigned char pad0[4];
    unsigned char flag4;
    unsigned char pad5;
    short s6;
    int w8;
    unsigned char padC[0x88 - 0xC];
    unsigned short h88;
    unsigned char pad8a[4];
    unsigned short h8e;
    unsigned char pad90[0xE0 - 0x90];
} Rec346C60;
extern Rec346C60 D_00239BA0[];
extern unsigned char D_00259F58[];

int func_00346C60(unsigned char *obj, int buttons)
{
    float a[2], b[2], c[2], d[2], e[2], f[2], g[2], h[2];
    int old, fp, ret = -1;
    int *res;

    old = *(int *)(obj + 0x4FC) + *(int *)(obj + 0x500) * 4;
    if (buttons & 0x1000) {
        int r;
        func_002E5E58(3, 0, 0);
        r = *(int *)(obj + 0x500) - 1;
        *(int *)(obj + 0x500) = (-1 < r) ? r : 5;
    } else if (buttons & 0x4000) {
        int r;
        func_002E5E58(3, 0, 0);
        r = *(int *)(obj + 0x500) + 1;
        *(int *)(obj + 0x500) = (5 < r) ? 0 : r;
    } else if (buttons & 0x8000) {
        int r;
        func_002E5E58(3, 0, 0);
        r = *(int *)(obj + 0x4FC) - 1;
        *(int *)(obj + 0x4FC) = (-1 < r) ? r : 3;
    } else if (buttons & 0x2000) {
        int r;
        func_002E5E58(3, 0, 0);
        r = *(int *)(obj + 0x4FC) + 1;
        *(int *)(obj + 0x4FC) = (3 < r) ? 0 : r;
    }
    fp = *(int *)(obj + 0x4FC) + *(int *)(obj + 0x500) * 4;
    func_00115484(a, 0, 8);
    func_00115484(b, 0, 8);
    func_00115484(c, 0, 8);
    func_00115484(d, 0, 8);
    e[0] = D_001AE508[0]; e[1] = D_001AE508[1];
    func_00115484(f, 0, 8);
    g[0] = D_001AE510[0]; g[1] = D_001AE510[1];
    h[0] = D_001AE518[0]; h[1] = D_001AE518[1];
    {
        float k[2];
        k[0] = D_001AE520[0]; k[1] = D_001AE520[1];
        if (old != fp)
            func_002A9588(0, 0, 1, 0, 1);
        res = func_00335E20(obj + 0xE4);
        *res = func_002A9588(0x60442D00, 0x70FFFEED, 0x14, 0, 0);
        func_00335E38(obj + 0, a[0] + (*(float **)(obj + 0x498))[0], a[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0x4C, b[0] + (*(float **)(obj + 0x498))[0], b[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0x130, c[0] + (*(float **)(obj + 0x498))[0], c[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0x98, d[0] + (*(float **)(obj + 0x498))[0], d[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0xE4, e[0] + (*(float **)(obj + 0x498))[0] + (float)*(int *)(obj + 0x4FC) * 53.5f,
                      e[1] + (*(float **)(obj + 0x498))[1] + (float)*(int *)(obj + 0x500) * 47.0f, 0.0f, 0.0f);
        func_00335E38(obj + 0x17C, f[0] + (*(float **)(obj + 0x498))[0], f[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0x210, g[0] + (*(float **)(obj + 0x498))[0], g[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        D_001ADB10 = -1;
        if (fp >= 0) {
            int s5 = *(short *)(D_00259F58 + fp * 10 + 6);
            unsigned char *s3 = D_00139568 + s5;
            if (D_00239BA0[*s3].flag4 != 0) {
                D_001A7AF8[s5] = 1;
                D_001A7B30[s5] = 1;
            }
            if (D_001A7AF8[s5] != 0) {
                char *s0 = (char *)obj + 0x4B8;
                char *s1 = (char *)obj + 0x4A0;
                int val, val2, n;
                D_001ADB10 = D_00239BA0[*s3].s6;
                func_00115DA8(s0, func_00288FB8(D_00239BA0[*s3].w8));
                val = D_00139688[s5];
                val2 = D_00239BA0[*s3].h8e;
                if (D_00239BA0[*s3].h88 != 0) {
                    n = func_00115DA8(s1, D_001AE528, func_00288FB8(0x2DC9));
                    s1 += n;
                    if (val < 1000) {
                        n = func_00115DA8(s1, D_001AE530, val);
                    } else {
                        n = func_00115DA8(s1, D_001AE538, val / 1000, val % 1000);
                    }
                    s1 += n;
                    if (val2 < 1000)
                        func_00115DA8(s1, D_001ADF98, val2);
                    else
                        func_00115DA8(s1, D_001AE548, val2 / 1000, val2 % 1000);
                } else {
                    func_00115DA8(s1, D_001ADBC8, func_00288FB8(0x2DB9));
                }
                if (buttons & 0x40) {
                    func_002E5E58(4, 0, 0);
                    ret = fp;
                    D_001F2880 = s5;
                }
            } else {
                obj[0x4A0] = 0;
                obj[0x4B8] = 0;
                if (buttons & 0x40)
                    func_002E5E58(5, 0, 0);
            }
        }
        func_00335E38(obj + 0x258, h[0] + (*(float **)(obj + 0x498))[0], h[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
        func_00335E38(obj + 0x2A0, k[0] + (*(float **)(obj + 0x498))[0], k[1] + (*(float **)(obj + 0x498))[1], 0.0f, 0.0f);
    }
    return ret;
}
