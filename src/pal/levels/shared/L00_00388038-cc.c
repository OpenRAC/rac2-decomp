/* func_PAL_L00_00388038, the PAL copy of func_L00_003851A0: the same C, where scale func_002A7820(D_L00_001AEE90, D_L00_001AEE94). */
#include "common.h"

extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C3150(void *, void *, unsigned int, int, int, int, float);
extern int D_L00_001AEE68 SDATA(D_L00_001AEE68);
extern float D_L00_001AEE70 SDATA(D_L00_001AEE70);
extern unsigned int D_L00_001AEE6C SDATA(D_L00_001AEE6C);
extern float D_L00_001AEE74;
extern float D_L00_001AEE84;
extern int D_L00_001AEE90;
extern int D_L00_001AEE94;

void func_PAL_L00_00388038(void *unused, void *source)
{
    char buffer[0x20];
    int i;
    for (i = 0; i < D_L00_001AEE68; i++) {
        char *second = buffer + 0x10;
        float scale = 0.020000001f;
        int state, random;
        func_002A7A00(buffer, 0.0f, 0.0333000011742115f);
        func_00282CC0(buffer, buffer, source);
        func_002A7A00(second, D_L00_001AEE70 * scale, D_L00_001AEE74 * scale);
        state = (unsigned char)(((int)(func_002A7820(D_L00_001AEE90, D_L00_001AEE94)) * 5 + 2) / 6);
        random = (unsigned char)func_002A77E0(255);
        func_002C3150(buffer, second, D_L00_001AEE6C, state, random, 0, D_L00_001AEE84);
    }
}

extern int D_L00_001AEE38 SDATA(D_L00_001AEE38);
extern float D_L00_001AEE10 SDATA(D_L00_001AEE10);
extern float D_L00_001AEE20 SDATA(D_L00_001AEE20);
extern unsigned int D_L00_001AEE28[4] SDATA(D_L00_001AEE28);

