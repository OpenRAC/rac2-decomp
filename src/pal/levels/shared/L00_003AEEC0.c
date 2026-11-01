#include "include_asm.h"

extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern char *func_PAL_002BE9A8(void *, int, void *, float, float, unsigned int, float, float, int);
extern char D_L00_001A8F20[] __attribute__((section(".sdata")));

void func_PAL_L00_003AEEC0(void *unused, void *position)
{
    int i, sign;
    char *p, *q;
    for (i=1; i>=0; i--) {
        int n=func_002A77E0(16);
        sign=func_002A77E0(2);
        p=func_PAL_002BE9A8(position, sign ? -n : n, D_L00_001A8F20, 0.04f, 1.0f, 0x7f204080, 0.9f, 50000.0f, 1);
        q=p+32;
        if(p) {
            *(short *)(p+10)=8;
            p[9]=func_00283CF0(4.0f)+64;
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    { int n=16;
    int j;
    for(j=0;j<2;j++) {
        p=func_PAL_002BE9A8(position,n,D_L00_001A8F20,0.02f,1.0f,0x7fffffff,0.97f,15000.0f,1);
        n=-n;
        q=p+32;
        if(p) {
            p[9]=func_00283CF0(4.0f)+64;
            *(short *)(p+10)=2;
            p[8]=func_002A77E0(255);
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    }
}


typedef struct {
    char pad[0x50];
    float angle;
    char tail[0x8C];
} AngleRecord_262570;
typedef struct {
    char pad[0x760];
    char pad2[0xBF8 - 0x760];
    void *pBF8;
    char pad3[0x2294 - 0xBFC];
    int i2294;
    char pad4[0x24EC - 0x2298];
    short h24EC;
} Res_189E20;
extern unsigned char D_00139580[];
extern AngleRecord_262570 D_L00_00262570[];
extern Res_189E20 D_00189E20;
extern char D_L00_001B8FF0[];
extern void func_00282F20(void *, void *, float);
extern void func_L00_0032A1A8(void *, void *, void *, int, float);
extern void func_PAL_L00_003ADC68(void *, void *, void *, void *);

void func_PAL_L00_003AF088(char *a0, char *a1) {
    float buf[4];
    float angle;
    AngleRecord_262570 *e;
    Res_189E20 *g;
    void *p;

    e = &D_L00_00262570[D_00139580[0]];
    angle = e->angle * 0.020000001f;
    if (D_00189E20.i2294 == 0x1D) {
        func_00282F20(buf, D_L00_001B8FF0, angle);
    } else if (D_00189E20.h24EC == 1) {
        func_00282F20(buf, a1 + 0xD0, -angle);
    } else {
        func_00282F20(buf, (char *)&D_00189E20 + 0x760, angle);
    }
    g = &D_00189E20;
    p = 0;
    if (g->pBF8 != 0) {
        func_L00_0032A1A8(g->pBF8, a0, buf, 0, angle);
        p = g->pBF8;
    }
    func_PAL_L00_003ADC68(a0, buf, a1, p);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003AF190);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003AF690);


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003B0230);
