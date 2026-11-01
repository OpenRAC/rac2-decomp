#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;
typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00283098(float *, const float *, const float *);
extern void func_00274B58(OozlaAppendObject164 *, float *, const float *);
extern void func_00282D08(float *out, float *a, float *b, float t);
extern void func_00282F20(float *out, float *in, float s);
extern void func_00282DD8(float *out, float *a, float *b);
extern void func_002AFFD8(float *a, float *b, int c);
extern void func_00283958(float *a, float *b);
extern void func_00283738(float *a, float *b, float *c);
extern void func_PAL_00274928(char *o, float *p, float *v);

void func_PAL_00274188(char *o)
{
    float a[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float h[4] __attribute__((aligned(16)));
    float i[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float g[3][4] __attribute__((aligned(16)));
    unsigned char *m = *(unsigned char **)(o + 0x68);
    float *w;

    if (m[0x5C] >= 2) {
        func_00282D08(a, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16), 0.5f);
        func_00282CF0(b, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16));
        func_00283098(b, b, (float *)(o + 0xC0));
        w = (float *)(o + 0xC0);
    } else {
        qcopy(a, *(char **)(m + 0x30) + m[0x59] * 16);
        w = (float *)(o + 0xC0);
    }
    func_00283098(c, a, w);
    func_002AFFD8((float *)(o + 0x10), d, 1);
    func_00282CF0(e, a, (float *)(m + 0x20));
    func_00283098(e, e, w);
    func_00282F20(e, e, 1.0f);
    func_00282DD8(f, e, d);
    func_00282F20(f, f, *(float *)(m + 0x4C));
    func_PAL_00274928(o, (float *)(m + 0x10), f);
    if (m[0x5C] >= 2)
        func_00274B58(o, (float *)(m + 0x10), b);
    func_00283958((float *)(m + 0x10), g[0]);
    func_00283738(w, g[0], w);
    func_00283098(h, a, w);
    func_00282CF0(i, h, c);
    func_00282CF0((float *)(o + 0x10), (float *)(o + 0x10), i);
}

