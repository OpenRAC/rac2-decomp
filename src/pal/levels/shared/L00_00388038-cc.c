#include "names.h"
/* func_PAL_L00_00388038, the PAL copy of func_L00_003851A0: the same C, where scale func_002A7820(D_L00_001AEE90, D_L00_001AEE94). */
#include "common.h"

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_hero_relative(void *, void *, unsigned int, int, int, int, float);
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
        vec_random_direction(buffer, 0.0f, 0.0333000011742115f);
        FastVecAdd(buffer, buffer, source);
        vec_random_direction(second, D_L00_001AEE70 * scale, D_L00_001AEE74 * scale);
        state = (unsigned char)(((int)(math_random_int_range(D_L00_001AEE90, D_L00_001AEE94)) * 5 + 2) / 6);
        random = (unsigned char)math_random_int_below(255);
        part_spawn_hero_relative(buffer, second, D_L00_001AEE6C, state, random, 0, D_L00_001AEE84);
    }
}

extern int D_L00_001AEE38 SDATA(D_L00_001AEE38);
extern float D_L00_001AEE10 SDATA(D_L00_001AEE10);
extern float D_L00_001AEE20 SDATA(D_L00_001AEE20);
extern unsigned int D_L00_001AEE28[4] SDATA(D_L00_001AEE28);

