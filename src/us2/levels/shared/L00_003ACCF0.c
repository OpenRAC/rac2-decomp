#include "include_asm.h"

/* func_US2_L00_003ACCF0, the USA v2.00 copy of func_L00_003AB8B8: the same C, where the last call
 * becomes func_US2_L00_003AB8F8 and gains a fifth argument, 5. */

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
extern void func_US2_L00_003AB8F8(void *, void *, void *, void *, int);

void func_US2_L00_003ACCF0(char *a0, char *a1) {
    float buf[4];
    float angle;
    AngleRecord_262570 *e;
    Res_189E20 *g;
    void *p;

    e = &D_L00_00262570[D_00139580[0]];
    angle = e->angle * 0.01666666753590107f;
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
    func_US2_L00_003AB8F8(a0, buf, a1, p, 5);
}
