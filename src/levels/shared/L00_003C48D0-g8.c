#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_002EBE88(void *, int, int, int, unsigned int, unsigned int, float, float, float);
extern short D_L00_001B2990[5] MACRO_ADDR;
extern short D_L00_001B29A0[5] MACRO_ADDR;
extern short D_L00_001B29B0[5] MACRO_ADDR;
extern float D_L00_001B29D4[] MACRO_ADDR;
extern Vector D_L00_00240080[5][10];
extern Vector D_L00_00240080_1[5][10];
extern float D_L00_001AFF8C __attribute__((sda));
extern unsigned int D_L00_001AFF20 __attribute__((sda));
extern unsigned int D_L00_001AFF24 __attribute__((sda));

void func_L00_003C48D0(unsigned char *object) {
    Vector origin;
    Vector differences[10];
    int i, j, k, alphaValue;
    Vector (*row)[10];
    Vector (*table)[10] = D_L00_00240080;
    float numerator, denominator;
    unsigned int colour;
    qcopy(&origin, *(unsigned char **)(object + 0x68) + 0x30);
    for (i = 0; i < 5; ++i) {
        if (D_L00_001B2990[i]) {
            for (j = 1; j < 10; ++j)
                func_00282CF0(&differences[j], &D_L00_00240080[i][j], &D_L00_00240080_1[i][j - 1]);
            qcopy(&D_L00_00240080[i][0], &origin);
            D_L00_00240080[i][0].f[3] = 0.04f;
            for (j = 1; j < 10; ++j) {
                func_00282CC0(&D_L00_00240080[i][j], &D_L00_00240080_1[i][j - 1], &differences[j]);
                row = table;
                row += i;
                (*row)[j].f[3] = 0.04f;
            }
            if (D_L00_001B2990[i] > 0) {
                numerator = func_00283CE0(D_L00_001B2990[i]);
                denominator = func_00283CE0(D_L00_001B29B0[i]);
                D_L00_001B29A0[i] = func_00283CF0(D_L00_001AFF8C * (numerator / denominator));
            } else D_L00_001B29A0[i] = 0;
        }
    }
    for (k = 0; k < 5; ++k) {
        if (D_L00_001B2990[k]) {
            alphaValue = func_00283CF0(func_00283CE0(D_L00_001B29A0[k]) * D_L00_001B29D4[0]);
            colour = D_L00_001AFF20;
            if (*(short *)(object + 0xAA) == 0x1192) colour = D_L00_001AFF24;
            func_L00_002EBE88(D_L00_00240080[k], 23, 14, 10,
                             ((unsigned int)alphaValue << 24) | 0x7F7F7F,
                             ((unsigned int)alphaValue << 24) | colour, 0.0f, 4.0f, 0.0f);
        }
    }
}
