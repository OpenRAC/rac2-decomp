#include "include_asm.h"
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


void func_L00_003851A0(void *unused, void *source)
{
    char buffer[0x20];
    int i;
    for (i = 0; i < D_L00_001AEE68; i++) {
        char *second = buffer + 0x10;
        float scale = 0.01666666753590107f;
        int state, random;
        func_002A7A00(buffer, 0.0f, 0.0333000011742115f);
        FastVecAdd(buffer, buffer, source);
        func_002A7A00(second, D_L00_001AEE70 * scale, D_L00_001AEE74 * scale);
        state = (unsigned char)func_002A7820(D_L00_001AEE90, D_L00_001AEE94);
        random = (unsigned char)func_002A77E0(255);
        func_002C3150(buffer, second, D_L00_001AEE6C, state, random, 0, D_L00_001AEE84);
    }
}

extern int D_L00_001AEE38 SDATA(D_L00_001AEE38);
extern int D_L00_001AEE3C;
extern int D_L00_001AEE40;
extern int D_L00_001AEE44;
extern float D_L00_001AEE10 SDATA(D_L00_001AEE10);
extern float D_L00_001AEE14;
extern float D_L00_001AEE20 SDATA(D_L00_001AEE20);
extern float D_L00_001AEE24;
extern unsigned int D_L00_001AEE28[4] SDATA(D_L00_001AEE28);

void func_L00_00384E08(unsigned char *object, void *position)
{
    char buffer[16];
    unsigned int *table = D_L00_001AEE28;
    void *data = *(void **)(object + 0x68);
    int state = (unsigned char)func_002A7820(D_L00_001AEE38, D_L00_001AEE3C);
    unsigned int *entry = table + object[0xBC] * 2;
    int random = (unsigned char)func_002A77E0(255);
    func_002C3150(position, data, entry[0], state, random, 0, D_L00_001AEE20);
    func_002A7A00(buffer, D_L00_001AEE10 * 0.01666666753590107f, D_L00_001AEE14 * 0.01666666753590107f);
    {
        int state2 = (unsigned char)func_002A7820(D_L00_001AEE40, D_L00_001AEE44);
        unsigned int *entry2 = (unsigned int *)((char *)table + ((object[0xBC] << 3) | 4));
        int random2 = (unsigned char)func_002A77E0(255);
        func_002C3150(position, buffer, entry2[0], state2, random2, 0, D_L00_001AEE24);
    }
}
