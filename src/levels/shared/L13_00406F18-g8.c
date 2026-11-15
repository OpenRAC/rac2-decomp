#include "include_asm.h"

#include "common.h"

extern float D_L13_001B1310 __attribute__((sda));

extern int D_L13_001B1300 __attribute__((sda));

extern int D_L13_001B1304 __attribute__((sda));

extern int D_L13_001B1308 __attribute__((sda));

extern int D_L13_001B130C __attribute__((sda));

extern float D_L13_001B1314 __attribute__((sda));

extern int func_003249F0(int, int);

extern float func_00324B10(void);

extern void ref_L13_0040DE50_00(void *, int, float, int, float, float, int, int, void *);

/* draws the two halves of the sign band, each from its own colour pair */
void part_draw_sign_band_sparkles(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = D_L13_001B1310;
    scale *= *(float *)(object + 0x2C);
    value = func_003249F0(95, 111);
    random = func_00324B10();
    ref_L13_0040DE50_00(object + 0x10, D_L13_001B1308, scale, value, random, 1.0f, D_L13_001B1300, 2, object);
    scale2 = D_L13_001B1310;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= D_L13_001B1314;
    value2 = func_003249F0(111, 127);
    random = func_00324B10();
    ref_L13_0040DE50_00(object + 0x10, D_L13_001B130C, scale2, value2, random, 1.0f, D_L13_001B1304, 2, object);
}
