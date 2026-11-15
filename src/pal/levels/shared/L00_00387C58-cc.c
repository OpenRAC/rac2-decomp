#include "names.h"
/* func_PAL_L00_00387C58, the PAL copy of func_L00_00384E08: the same C, where scale func_002A7820(D_L00_001AEE38, D_L00_001AEE3C); wrap (unsigned char)func_002A77E0(255) (((int)({e}) * 5 + 2); wrap func_002A7820(D_L00_001AEE40, D_L00_001AEE44) (((int)({; rewrap func_002C3150(position, data, entry[0], state, random. */
#include "common.h"

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void *part_spawn_hero_relative(void *, void *, unsigned int, int, int, int, float);
extern int D_L00_001AEE68 SDATA(D_L00_001AEE68);
extern float D_L00_001AEE70 SDATA(D_L00_001AEE70);
extern unsigned int D_L00_001AEE6C SDATA(D_L00_001AEE6C);
extern int D_L00_001AEE38 SDATA(D_L00_001AEE38);
extern int D_L00_001AEE3C;
extern int D_L00_001AEE40;
extern int D_L00_001AEE44;
extern float D_L00_001AEE10 SDATA(D_L00_001AEE10);
extern float D_L00_001AEE14;
extern float D_L00_001AEE20 SDATA(D_L00_001AEE20);
extern float D_L00_001AEE24;
extern unsigned int D_L00_001AEE28[4] SDATA(D_L00_001AEE28);

void func_PAL_L00_00387C58(unsigned char *object, void *position)
{
    char buffer[16];
    unsigned int *table = D_L00_001AEE28;
    void *data = *(void **)(object + 0x68);
    int state = (unsigned char)(((int)(math_random_int_range(D_L00_001AEE38, D_L00_001AEE3C)) * 5 + 2) / 6);
    unsigned int *entry = table + object[0xBC] * 2;
    int random = (unsigned char)math_random_int_below(255);
    (((int)(part_spawn_hero_relative(position, data, entry[0], state, random, 0, D_L00_001AEE20)) * 5 + 2) / 6);
    vec_random_direction(buffer, D_L00_001AEE10 * 0.020000001f, D_L00_001AEE14 * 0.020000001f);
    {
        int state2 = (unsigned char)(((int)(math_random_int_range(D_L00_001AEE40, D_L00_001AEE44)) * 5 + 2) / 6);
        unsigned int *entry2 = (unsigned int *)((char *)table + ((object[0xBC] << 3) | 4));
        int random2 = (unsigned char)math_random_int_below(255);
        part_spawn_hero_relative(position, buffer, entry2[0], state2, random2, 0, D_L00_001AEE24);
    }
}
