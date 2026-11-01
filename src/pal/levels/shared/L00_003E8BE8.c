#include "include_asm.h"

#include "common.h"
extern void func_00282D30(void *, void *, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern char D_L00_001FE940[];
extern char D_L00_001A8F20[] __attribute__((sda));
#include "common.h"

void func_PAL_L00_003E8BE8(char *a0) {
    float a[3];
    float b[3];
    float c[3];
    float d[3];
    char *tbl;
    int n;
    char *r;
    char *v;
    float big;
    int i;

    v = *(char **)(a0 + 0x68);
    { float *p = (float *)(v + 0x14);
    a[0] = p[0];
    a[1] = p[1];
    a[2] = p[2]; }
    a[3] = 0.0f;
    func_00282D30(b, a0 + 0xD0, -0.1f);
    func_00282CC0(a, a, b);
    func_00282D30(c, a0 + 0xE0, 0.15f);
    func_00282CC0(a, a, c);
    func_00282D30(c, a0 + 0xE0, -0.033333335f);
    tbl = D_L00_001FE940;
    for (i = 8; i >= 0; i--) {
        d[0] = a[0] + func_002A78D8(0.0f, 0.1f);
        d[1] = a[1] + func_002A78D8(0.0f, 0.1f);
        d[2] = a[2] + func_002A78D8(0.0f, 0.1f);
        n = func_002A77E0(0xFF);
        big = 42000.0f;
        func_002C65A0(d, D_L00_001A8F20, 3, 0x808080, n, 0x7F, 0x7F, big, big, 0.0f, 1);
        big = 273000.0f;
        r = func_002C65A0(a, D_L00_001A8F20, 3, 0x406080, n, 0x10, 0x10, big, big, 0.0f, 1);
        if (r != 0)
            *(unsigned char *)(r + 2) = *(unsigned char *)(*(unsigned *)(tbl + 0xD4));
        func_00282CC0(a, a, c);
    }
}

